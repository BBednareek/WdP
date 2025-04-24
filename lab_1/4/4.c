#include <stdio.h>
#include <stdlib.h>

int sumDiagonal(const int*, int);

int main(void) {
    int n = 0;

    printf("Podaj rozmiar macierzy n: ");
    scanf("%d", &n);

    int *arr = malloc(n * n * sizeof *arr);

    if (arr == NULL) {
        perror("malloc");
         exit(EXIT_FAILURE);
    }

    printf("Wprowadz %d liczb:\n", n * n);

    size_t i = 0;

    for (; i < n * n; ++i)
        scanf("%d", arr + i);

    const int diag = sumDiagonal(arr, n);
    printf("Suma elementow na przekatnej: %d\n", diag);

    free(arr);
    return EXIT_SUCCESS;
}

int sumDiagonal(const int *arr, int n) {
    int sum = 0;
    size_t i = 0;

    const int *p = arr;

    for (; i < n; ++i)
        sum += *(p + i * n + i);

    return sum;
}