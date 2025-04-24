#include <stdio.h>
#include <stdlib.h>

void read_arr(int**, int, int);
void print_arr(int**, int, int);
void free_arr(int**, int);

int **alloc_arr(int, int);
int **transposition(int**, int, int);

int main(void) {
    int rows = 0;
    int columns = 0;

    printf("Podaj liczbe wierszy: ");
    scanf("%d", &rows);

    printf("Podaj liczbe kolumn: ");
    scanf("%d", &columns);

    int **arr = alloc_arr(rows, columns);

    read_arr(arr, rows, columns);

    int **transposed = transposition(arr, rows, columns);

    print_arr(transposed, columns, rows);

    free_arr(arr, rows);
    free_arr(transposed, columns);

    printf("\n");
    return EXIT_SUCCESS;
}

void read_arr(int** arr, const int rows, const int columns) {
    size_t i = 0;
    size_t j = 0;

    for (; i < rows; i++)
        for (j = 0; j < columns; j++)
            scanf("%d", *(arr + i) + j);
}

void print_arr(int **arr, const int rows, const int columns) {
    size_t i = 0;
    size_t j = 0;

    for (; i < rows; i++) {
        for (j = 0; j < columns; j++)
            printf("%d ", *(*(arr + i) + j));

        printf("\n");
    }
}

void free_arr(int **arr, const int rows) {
    size_t i = 0;

    for (; i < rows; i++)
        free(*(arr + i));

    free(arr);
}

int **alloc_arr(const int rows, const int columns) {
    int **arr = malloc(sizeof(int *) * rows);

    if (arr == NULL) {
        printf("Blad alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;

    for (; i < rows; i++) {
        *(arr + i) = (int *)malloc(columns * sizeof(int));

        if (*(arr + i) == NULL) {
            printf("Blad alokacji pamieci");
            exit(EXIT_FAILURE);
        }
    }

    return arr;
}

int **transposition(int **arr, const int rows, const int columns) {
    int **new_arr = malloc(columns * sizeof(int *));

    if (new_arr == NULL) {
        printf("Blad alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    size_t j = 0;

    for (; i < columns; i++)
        *(new_arr + i) = (int *)malloc(rows * sizeof(int));

    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            *(*(new_arr + j) + i) = *(*(arr + i) + j);

    return new_arr;
}