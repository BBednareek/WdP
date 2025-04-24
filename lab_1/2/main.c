#include <stdio.h>
#include <stdlib.h>

void enter_array_data(int*, int);
void print_array(const int*, int);
int *concat_arrays(const int*, const int*, int, int);

int main(void) {
    int sizeA = 0;
    int sizeB = 0;

    printf("Podaj rozmiar tablicy A: ");
    scanf("%d", &sizeA);

    int *arrA = malloc(sizeA * sizeof(int));

    if (arrA == NULL) {
        perror("Blad alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    enter_array_data(arrA, sizeA);

    printf("Podaj rozmiar tablicy B: ");
    scanf("%d", &sizeB);

    int *arrB = malloc(sizeB * sizeof(int));

    if (arrB == NULL) {
        perror("Blad alokacji pamieci");

        free(arrA);
        exit(EXIT_FAILURE);
    }

    enter_array_data(arrB, sizeB);

    int *arrC = concat_arrays(arrA, arrB, sizeA, sizeB);

    if (arrC == NULL) {
        perror("Blad alokacji pamieci");

        free(arrA);
        free(arrB);
        exit(EXIT_FAILURE);
    }

    free(arrA);
    free(arrB);

    printf("Zlaczona tablica wynikowa: ");
    print_array(arrC, sizeA + sizeB);

    printf("\n");

    free(arrC);
    return 0;
}

int *concat_arrays(const int *arrA, const int *arrB, const int sizeA, const int sizeB) {
    size_t i = 0;

    const int res_arr_size = sizeA + sizeB;
    int *arr_res = malloc(res_arr_size * sizeof(int));

    if(arr_res == NULL) {
        perror("Blad alokacji pamieci");
        return NULL;
    }

    for(; i < sizeA; i++)
        *(arr_res + i)  = *(arrA + i);

    for (i = 0; i < sizeB; i++)
        *(arr_res + sizeA + i) = *(arrB + i);

    return arr_res;
}

void enter_array_data(int* arr, const int size) {
    size_t i = 0;

    for (; i < size; i++) {
        printf("Podaj %zu. element tablicy: ", i+1);
        scanf("%u", arr + i);
    }
}


void print_array(const int* arr, const int size) {
    size_t i = 0;

    for(; i < size; i++)
        printf("%d ", *(arr + i));
}