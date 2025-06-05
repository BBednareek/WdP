#include "stdio.h"
#include "stdlib.h"

const char* main_path = "students.txt";
const char* highest_grade = "highest.txt";

typedef struct student {
    char* name;
    char* surname;
    int grade;
} student_t;

student_t *read_file(const char*, int*);
int write_file(student_t*, int);
int print_file();

int main(void) {
    int size = 0;
    int *pSize = &size;

    student_t *arr = read_file(main_path, pSize);

    if (arr == NULL)
        return EXIT_FAILURE;

    if(write_file(arr, size))
        return EXIT_FAILURE;

    printf("Nazwiska studentow z najwyzsza ocena: \n");
    print_file();

    int i = 0;
    for (; i < size; i++) {
        free((arr + i) -> name);
        free((arr + i) -> surname);
    }

    free(arr);
    return EXIT_SUCCESS;
}

student_t *read_file(const char* filepath, int *size) {
    FILE* file = fopen(filepath, "r");

    if (!file) {
        perror("Blad przy probie otwarcia pliku tekstowego do wczytania danych");
        return NULL;
    }

    int count = 0;

    char tmp_name[20] = {};
    char tmp_surname[20] = {};
    int tmp_grade;

    while(fscanf(file, "%s %s %d", tmp_name, tmp_surname, &tmp_grade) == 3) count++;

    rewind(file);

    student_t *arr = (student_t* ) malloc(sizeof(student_t) * count);

    if (arr == NULL) {
        perror("Blad alokacji pamieci dla listy studentow odczytywanej z pliku");

        fclose(file);
        return NULL;
    }

    size_t i = 0;
    for (i = 0; i < count; i++) {
        (arr + i) -> name = malloc(20);
        (arr + i) -> surname = malloc(20);
        fscanf(file, "%s %s %d", (arr + i) -> name, (arr + i) -> surname, &(arr + i) -> grade);
    }

    *size = count;

    fclose(file);
    return arr;
}

int write_file(student_t *arr, int size) {
    FILE* file = fopen(highest_grade, "w");

    if(!file) {
        perror("Blad przy otwieraniu pliku do wpisywania");
        return 1;
    }

    size_t i = 0;
    for(; i < size; i++)
        if ((arr + i)->grade == 5)
            fprintf(file, "%s\n", ((arr + i) -> surname));

    fclose(file);
    return 0;
}

int print_file() {
    FILE* file = fopen(highest_grade, "r");

    if(!file) {
        perror("Blad przy probie odczytania pliku z nazwiskami studentow o najwyzszej ocenie");
        return 1;
    }

    char surname[20] = {};
    while(fscanf(file, "%s", surname) == 1)
        printf("%s ", surname);

    fclose(file);
    return 0;
}