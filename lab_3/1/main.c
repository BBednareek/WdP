#include "stdio.h"
#include "stdlib.h"

#ifdef _WIN32
    #include "windows.h"
#else
    #include "unistd.h"
#endif

int *read_ints(const char*, int*);
int write_ints(int*, int);
int print_file(const char*);

double avg(const int*, int);

const char* main_path = "../digits.txt";
const char* bigger_path = "../bigger.txt";
const char* lower_path = "../lower.txt";

int main(void) {
    int size = 1000;
    int *pSize = &size;

    int *arr = read_ints(main_path, pSize);

    if (arr == NULL)
        return EXIT_FAILURE;

    if(write_ints(arr, size) == 1) {
        perror("Blad przy rozdzielaniu danych do nowych plikow");

        free(arr);
        return EXIT_FAILURE;
    }

    printf("Zawartosc pliku bigger.txt - liczb wiekszych badz rownych od sredniej: ");

    if(print_file(bigger_path) == 1) {
        perror("Blad przy wypisywaniu liczb >= sredniej");

        free(arr);
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    Sleep(10000);
    system("cls");
#else
    sleep(10);
    system("clear");
#endif

    printf("Zawartosc pliku lower.txt - liczb mniejszych od sredniej: ");

    if(print_file(lower_path) == 1) {
        perror("Blad{ przy wypisywaniu liczb < sredniej");

        free(arr);
        return EXIT_FAILURE;
    }

    free(arr);
    return EXIT_SUCCESS;
}


int *read_ints (const char* file_name, int *size) {  //TODO Nie moglem znalezc rozwiazania na warning z Clang dotyczacy leaku w tej funkcji
    FILE* file = fopen (file_name, "r");

    if (!file) {
        perror("Blad przy otwieraniu pliku tekstowego");
        return NULL;
    }

    int *arr = malloc(sizeof(int) * 1000);

    if (arr == NULL) {
        perror("Blad alokacji pamieci dla tablicy pomocniczej przy zczytywaniu liczb z pliku tekstowego");

        fclose(file);
        return NULL;
    }

    int num = 0;
    int new_size = 0;

    while (fscanf(file, "%d", &num) == 1) {
        *(arr + new_size) = num;
        new_size++;
    }

    arr = realloc(arr, new_size * sizeof(int));

    if (arr == NULL) {
        perror("Blad realokacji pamieci");

        fclose(file);
        return NULL;
    }

    *size = new_size;
    fclose (file);

    return arr;
}

int write_ints(int *arr, int size) {
    size_t i = 0;

    const double average = avg(arr, size);

    FILE* bigger = fopen (bigger_path, "w");

    if (!bigger) {
        perror("Blad przy otwieraniu pliku tekstowego");
        return 1;
    }

    FILE* lower = fopen (lower_path, "w");

    if (!lower) {
        perror("Blad przy otwieraniu pliku tekstowego");

        fclose(bigger);
        return 1;
    }

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

    int num = 0;

    while (fscanf(file, "%d", &num) == 1)
        printf("%d ", num);

    fclose(file);
    return 0;
}


double avg(const int *arr, int size) {
    double res = 0.0;

    size_t i = 0;

    for (; i < size; i++)
        res += *(arr + i);

    return res / size;
}

