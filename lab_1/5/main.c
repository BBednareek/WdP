#include <stdio.h>
#include <stdlib.h>

int count_unique(const int*, int);
int *delete_duplicates(const int*, int, int*);

int main() {
    int n = 0;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL) {
        perror("Blad przy alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;

    for (; i < n; i++) {
        printf("Podaj [%zu] element tablicy: ", i + 1);
        scanf("%d", arr + i);
    }

    int new_size = 0;
    int *unique_arr = delete_duplicates(arr, n, &new_size);

    if (unique_arr == NULL) {
        perror("Blad przy alokacji pamieci");
        free(arr);

        exit(EXIT_FAILURE);
    }

    printf("\nUnikalna tablica: ");

    for (i = 0; i < new_size; i++)
        printf("%d ", *(unique_arr + i));
    
    free(arr);
    free(unique_arr);

    printf("\n");
    return EXIT_SUCCESS;
}

int count_unique(const int *arr, const int n) {
    size_t i = 1;
    int counter = 1;

    for (; i < n; i++)
        if (*(arr + i) != *(arr + i - 1))
            ++counter;

    return counter;
}

int *delete_duplicates(const int *arr, const int n, int *new_size) {
    *new_size = count_unique(arr, n);

    int *res = malloc(*new_size * sizeof(int));

    int *res_ptr = res;
    const int *arr_ptr = arr;

    *res_ptr = *arr_ptr;
    res_ptr++;

    size_t i = 1;

    for (; i < n; i++)
        if (*(arr_ptr + i) != *(arr_ptr + i - 1)) {
            *res_ptr = *(arr_ptr + i);
            res_ptr++;
        }

    return res;
}
