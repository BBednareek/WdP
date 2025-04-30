#include "stdio.h"
#include "stdlib.h"

typedef struct Point {
    double x;
    double y;
} point_t;

point_t* read_arr(int);
void display_arr(point_t*, int);

int main(void) {
    int n = 0;

    printf("Podaj ilosc punktow, ktore chcesz dodac do tablicy: ");
    scanf("%d", &n);

    point_t* arr = read_arr(n);

    if (arr == NULL) {
        free(arr);
        return EXIT_FAILURE;
    }

    display_arr(arr, n);

    free(arr);
    return EXIT_SUCCESS;
}

point_t* read_arr(const int n) {
    point_t* arr = (point_t*)malloc(sizeof(point_t) * n);

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

void display_arr(point_t* arr, const int n) {
    size_t i = 0 ;

    for(; i < n; i++)
        printf("Punkt nr %zu. (%.2lf, %.2lf)\n", i + 1, (arr + i) -> x, (arr + i) -> y);
}