#include "stdio.h"
#include "stdlib.h"
#include "math.h"

struct Point {
    double x;
    double y;
};

double distance(struct Point);

struct Point* read_arr(int);
struct Point* partition(struct Point* low, struct Point* high);

void display_arr(struct Point*, int);
void sort_by_distance(struct Point*, int);
void swap(struct Point* a, struct Point* b);
void quicksort(struct Point* low, struct Point* high);

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

    sort_by_distance(arr, n);

    printf("\nTablica po sortowaniu wedlug odleglosci: \n");
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

double distance(struct Point point) {
    return sqrt(pow(2, 0 - point.x) + pow(2, 0 - point.y));
}

void display_arr(struct Point* arr, const int n) {
    size_t i = 0 ;

    for(; i < n; i++)
        printf("Punkt nr %zu. (%.2lf, %.2lf)\n", i + 1, (arr + i) -> x, (arr + i) -> y);
}

void swap(struct Point* a, struct Point* b) {
    struct Point tmp = *a;
    *a = *b;
    *b = tmp;
}

struct Point* partition(struct Point* low, struct Point* high) {
    double pivot = distance(*high);
    struct Point* i = low - 1;

    for (struct Point* j = low; j < high; j++)
        if (distance(*j) >= pivot) {
            i++;
            swap(i, j);
        }

    i++;
    swap(i, high);

    return i;
}

void quicksort(struct Point* low, struct Point* high) {
    if (low < high) {
        struct Point* pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

void sort_by_distance(struct Point* arr, const int n) {
    if (n > 1)
        quicksort(arr, arr + n - 1);
}