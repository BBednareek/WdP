#include <stdio.h>
#include <stdlib.h>

int *read_ints(const char*, int*);
int write_ints(int*, int);
int print_file(const char*);
double avg(const int*, int);

const char* main_path = "digits.txt";
const char* bigger_path = "bigger.txt";
const char* lower_path = "lower.txt";

int main(void) {
    int size = 0;
    int *pSize = &size;

    int *arr = read_ints(main_path, pSize);

    if (!arr)
        return EXIT_FAILURE;

    if(write_ints(arr, size)) {
        free(arr);
        return EXIT_FAILURE;
    }

    printf("Srednia: %.2lf\n", avg(arr, size));

    printf("Liczby < od sredniej: \n");
    print_file(lower_path);

    printf("\n\nLiczby >= od sredniej: \n");
    print_file(bigger_path);

    free(arr);
    return EXIT_SUCCESS;
}

int *read_ints(const char *file_name, int *size) {
    FILE *file = fopen(file_name, "r");

    if (!file) {
        perror("Blad przy czytaniu pliki ze sciezki");
        return NULL;
    }

    int value = 0;
    int count = 0;

    while (fscanf(file, "%d", &value) == 1) count++;

    rewind(file);
    int *arr = malloc(sizeof(int) * count);

    if (!arr) {
        perror("Blad alokacji pamieci dla tablicy zawierajacej wczytane dane");
        fclose(file);
        return NULL;
    }

    size_t i = 0;
    while (fscanf(file, "%d", &value) == 1){
        *(arr + i) = value;
        i++;
    }

    fclose(file);
    *size = count;

    return arr;
}

int write_ints(int *arr, int size) {
    const double average = avg(arr, size);

    FILE* bigger = fopen (bigger_path, "w");
    if (!bigger) {
        perror("Blad przy otwieraniu pliku do wpisania liczb >= od sredniej");
        return 1;
    }

    FILE* lower = fopen (lower_path, "w");
    if (!lower) {
        perror("Blad przy otwieraniu pliku do wpisania liczb < od sredniej");
        fclose(bigger);
        return 1;
    }

    size_t i = 0;
    for (; i < size; i++) {
        if (*(arr + i) >= average)
            fprintf(bigger, "%d\n", *(arr + i));
        else
            fprintf(lower, "%d\n", *(arr + i));
    }

    fclose(bigger);
    fclose(lower);

    return 0;
}

int print_file(const char* path) {
    FILE* file = fopen(path, "r");

    if (!file) {
        perror("Blad przy probie otwarcia pliku do wypisania danych");
        return 1;
    }

    int value = 0;

    while (fscanf(file, "%d", &value) == 1)
        printf("%d ", value);

    fclose(file);
    return 0;
}

double avg(const int *arr, int size) {
    double res = 0.0;

    size_t i = 0;
    for (; i < size; i++)
        res += *(arr + i);


    if (size == 0)
        return 0.0;

    return res / size;
}