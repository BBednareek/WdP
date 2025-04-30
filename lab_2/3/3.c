#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct Point {
    double x;
    double y;
} point_t;

point_t* read_arr(int);
double distance(point_t);

void display_arr(point_t*, int);
void sort_by_distance(point_t*, int);

void swap(point_t* a, point_t* b);

point_t* partition(point_t* low, point_t* high);

void quicksort(point_t* low, point_t* high);


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

    sort_by_distance(arr, n);

    printf("\nTablica po sortowaniu wedlug odleglosci: \n");
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

double distance(point_t point) {
    return sqrt(pow(2, 0 - point.x) + pow(2, 0 - point.y));
}

void display_arr(point_t* arr, const int n) {
    size_t i = 0 ;

    for(; i < n; i++)
        printf("Punkt nr %zu. (%.2lf, %.2lf)\n", i + 1, (arr + i) -> x, (arr + i) -> y);
}

void swap(point_t* a, point_t* b) {
    point_t tmp = *a;
    *a = *b;
    *b = tmp;
}

point_t* partition(point_t* low, point_t* high) {
    double pivot = distance(*high);
    point_t* i = low - 1;

    for (point_t* j = low; j < high; j++)
        if (distance(*j) >= pivot) {
            i++;
            swap(i, j);
        }

    i++;
    swap(i, high);

    return i;
}

void quicksort(point_t* low, point_t* high) {
    if (low < high) {
        point_t* parted = partition(low, high);
        quicksort(low, parted - 1);
        quicksort(parted + 1, high);
    }
}

void sort_by_distance(point_t* arr, const int n) {
    if (n > 1)
        quicksort(arr, arr + n - 1);
}