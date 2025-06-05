#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *surname;
    float percent;
} student_t;

char *next(char**);
char *load_answers(FILE*, int*);
int count_answers(FILE*);
int compare_students(const void*, const void*);

void write_student(FILE*, student_t*);
void process_line(char*, char*, int, FILE*, FILE*);
void process_all(FILE *, char*, int, FILE*, FILE*);
void read_students_from_bin(const char*);

int main() {
    FILE *res = fopen("results.txt", "r");
    FILE *ans = fopen("answers.txt", "r");
    FILE *txt = fopen("passed.txt", "w");
    FILE *bin = fopen("passed.bin", "wb");

    if (!res || !ans || !txt || !bin) {
        perror("Blad przy otwarciu pliku");
        return 1;
    }

    int n = 0;
    char *key = load_answers(ans, &n);

    if (!key) {
        perror("Blad ladowania odpowiedzi");
        fclose(res); fclose(ans); fclose(txt); fclose(bin);
        return 1;
    }

    process_all(res, key, n, txt, bin);

    fclose(res);
    fclose(ans);
    fclose(txt);
    fclose(bin);
    free(key);

    printf("Lista osob, ktore zdaly egzamin:\n");
    read_students_from_bin("passed.bin");

    return 0;
}

char *next(char **p) {
    while (**p == ' ' || **p == '\n') (*p)++;
    if (**p == '\0') return NULL;
    char *start = *p;
    while (**p && **p != ' ' && **p != '\n') (*p)++;
    if (**p) *((*p)++) = '\0';
    return start;
}

int count_answers(FILE *f) {
    int n = 0;
    char c;
    while (fscanf(f, " %c", &c) == 1) n++;
    rewind(f);
    return n;
}

char *load_answers(FILE *f, int *n) {
    *n = count_answers(f);
    char *a = malloc(*n);
    if (!a) return NULL;
    char *p = a;
    while (fscanf(f, " %c", p++) == 1);
    return a;
}

void write_student(FILE *bin, student_t *s) {
    size_t len_name = strlen(s->name);
    size_t len_surname = strlen(s->surname);

    fwrite(&len_name, sizeof(size_t), 1, bin);
    fwrite(s->name, sizeof(char), len_name, bin);

    fwrite(&len_surname, sizeof(size_t), 1, bin);
    fwrite(s->surname, sizeof(char), len_surname, bin);

    fwrite(&s->percent, sizeof(float), 1, bin);
}

void process_line(char *line, char *key, int n, FILE *txt, FILE *bin) {
    char *p = line;
    char *name = next(&p);
    char *surname = next(&p);
    if (!name || !surname) return;

    int correct = 0;
    for (char *a = key; *p && a - key < n; a++)
        if (*next(&p) == *a) correct++;

    float percent = 100.f * (float)correct / (float)n;

    if (percent >= 50.f) {
        fprintf(txt, "%s %s %.2f%%\n", surname, name, percent);

        student_t s;
        s.name = malloc(strlen(name) + 1);
        s.surname = malloc(strlen(surname) + 1);

        if (!s.name || !s.surname) {
            perror("Blad alokacji pamieci dla danych z pliku results.txt");
            exit(1);
        }

        strcpy(s.name, name);
        strcpy(s.surname, surname);
        s.percent = percent;

        write_student(bin, &s);

        free(s.name);
        free(s.surname);
    }
}

void process_all(FILE *res, char *key, int n, FILE *txt, FILE *bin) {
    char *buf = malloc(512);
    if (!buf) return;
    while (fgets(buf, 512, res)) process_line(buf, key, n, txt, bin);
    free(buf);
}

int compare_students(const void *a, const void *b) {
    float pa = (*(student_t**)a)->percent;
    float pb = (*(student_t**)b)->percent;
    return (pa < pb) - (pa > pb);
}

void read_students_from_bin(const char *path) {
    FILE *bin = fopen(path, "rb");
    if (!bin) {
        perror("Blad otwarcia pliku binarnego do odczytu");
        return;
    }

    student_t **list = NULL;
    size_t count = 0;

    while (1) {
        size_t len_name = 0, len_surname = 0;
        if (fread(&len_name, sizeof(size_t), 1, bin) != 1) break;

        char *name = malloc(len_name + 1);
        if (!name || fread(name, sizeof(char), len_name, bin) != len_name) break;
        *(name + len_name) = '\0';

        if (fread(&len_surname, sizeof(size_t), 1, bin) != 1) break;

        char *surname = malloc(len_surname + 1);
        if (!surname || fread(surname, sizeof(char), len_surname, bin) != len_surname) break;
        *(surname + len_surname) = '\0';

        float percent = 0.0f;
        if (fread(&percent, sizeof(float), 1, bin) != 1) break;

        student_t *s = malloc(sizeof(student_t));
        if (!s) break;

        s->name = name;
        s->surname = surname;
        s->percent = percent;

        student_t **tmp = realloc(list, sizeof(student_t *) * (count + 1));
        if (!tmp) break;

        list = tmp;
        *(list + count) = s;
        count++;
    }

    fclose(bin);

    if (list && count > 0) {
        qsort(list, count, sizeof(student_t *), compare_students);

        student_t **p = list;
        student_t **end = list + count;

        while (p < end) {
            printf("%s %s %.2f%%\n", (*p)->surname, (*p)->name, (*p)->percent);
            free((*p)->name);
            free((*p)->surname);
            free(*p);
            p++;
        }

        free(list);
    }
}