#include <stdio.h>
#include <stdlib.h>

void enter_tab(int*, int);
void print_tab(const int*, int);
int *reverse_tab(const int*, int);

int main() {
    int n = 0;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &n);

    int *arr = malloc(sizeof(int*) * n);

    if (arr == NULL){
        perror("Blad alokacji pamieci");
        exit(EXIT_FAILURE);
    }

    enter_tab(arr, n);

    printf("\nWprowadzone elementy do tablicy: ");
    print_tab(arr, n);

    int *res_arr = reverse_tab(arr, n);

    if (res_arr == NULL) {
        perror("\nBlad alokacji pamieci");
        free(arr);
        exit(EXIT_FAILURE);
    }

    free(arr);

    printf("\nOdwrocona tablica: ");
    print_tab(res_arr, n);

    free(res_arr);

    printf("\n");
    return EXIT_SUCCESS;
}

void enter_tab(int *arr, const int n) {
    int i = 0;

    for (; i < n; i++) {
        printf("Podaj %d. element tablicy: ", i + 1);
        scanf("%d", arr + i);
    }
}

void print_tab(const int *arr, const int n) {
    int i = 0;

    for (; i < n; i++)
        printf("%d ", *(arr + i));
}

int *reverse_tab(const int *arr, const int n) {
    int *res_arr = malloc(sizeof(int) * n);

    if (res_arr == NULL) {
        perror("\nBlad alokacji pamieci");
        return NULL;
    }

    int *left = res_arr;
    const int *right = arr + n - 1;

    while (right >= arr) {
        *left = *right;
        left++;
        right--;
    }

    return res_arr;
}
