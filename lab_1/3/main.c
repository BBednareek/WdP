#include <stdio.h>
#include <stdlib.h>

void add_elements_arr(int*, int);
void print_arr(const int*, int);
int sum(const int*, int);

int main(void) {
    int sizeA = 0;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &sizeA);

    int *arr = malloc(sizeA * sizeof(int));

    if (arr == NULL) {
        perror("Blad alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    add_elements_arr(arr, sizeA);

    printf("Podana tablica: ");
    print_arr(arr, sizeA);

    printf("\nSuma elementow w tablicy wynosi %d", sum(arr, sizeA));

    free(arr);

    printf("\n");
    return EXIT_SUCCESS;
}

void add_elements_arr(int* arr, const int size) {
    size_t i = 0;

    for (; i < size; i++) {
        printf("Podaj %zu. element tablicy: ", i+1);
        scanf("%d", arr + i);
    }
}

void print_arr(const int* arr, const int size) {
    size_t i = 0;

    for (; i < size; i++)
        printf("%d ", *(arr + i));
}

int sum(const int* arr, const int size) {
    int res = 0;
    size_t i = 0;

    for (; i < size; i++)
        res += *(arr + i);

    return res;
}