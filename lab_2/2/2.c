#include "stdio.h"
#include "stdlib.h"

struct Point {
    double x;
    double y;
};

struct Point* read_arr(int);
void display_arr(struct Point*, int);

int main(void) {
    int n = 0;

    printf("Podaj ilosc punktow, ktore chcesz dodac do tablicy: ");
    scanf("%d", &n);

    struct Point* arr = read_arr(n);

    if (arr == NULL) {
        free(arr);
        return EXIT_FAILURE;
    }

    display_arr(arr, n);

    free(arr);
    return EXIT_SUCCESS;
}

struct Point* read_arr(const int n) {
    struct Point* arr = (struct Point*)malloc(sizeof(struct Point) * n);

    if (arr == NULL) {
        perror("Blad podczas alokacji pamieci dla tablicy punktow");
        free(arr);
        return NULL;
    }

    size_t i = 0;

    for(; i < n; i++) {
        printf("Podaj wspolrzedne (x, y) %zu. punktu: ", i + 1);
        scanf("%lf %lf", &(arr + i)->x, &(arr + i)->y);
    }

    return arr;
}

void display_arr(struct Point* arr, const int n) {
    size_t i = 0 ;

    for(; i < n; i++)
        printf("Punkt nr %zu. (%.2lf, %.2lf)\n", i + 1, (arr + i) -> x, (arr + i) -> y);
}