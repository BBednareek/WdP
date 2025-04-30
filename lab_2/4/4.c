#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct Point {
    double x;
    double y;
} point_t;

double distance(point_t, point_t);
double distance_from_origin(point_t);

point_t* read_arr(int);
point_t* partition(point_t*, point_t*);
point_t* check_if_in_circle(point_t*, point_t, double, int, int*);

void display_arr(point_t*, int);
void sort_by_distance(point_t*, int);
void swap(point_t*, point_t*);
void quicksort(point_t*, point_t*);

int main(void) {
    int n = 0;

    double x_circle_center = 0.0;
    double y_circle_center = 0.0;
    double radius = 0.0;

    printf("Podaj ilosc punktow, ktore chcesz dodac do tablicy: ");
    scanf("%d", &n);

    point_t* arr = read_arr(n);

    if (arr == NULL) {
        free(arr);
        return EXIT_FAILURE;
    }

    sort_by_distance(arr, n);

    printf("Podaj wspolrzedne srodka okregu: ");
    scanf("%lf %lf", &x_circle_center, &y_circle_center);

    const point_t circle = {.x = x_circle_center, .y = y_circle_center};

    printf("Podaj dlugosc promienia okregu: ");
    scanf("%lf", &radius);

    int res_arr_size = 0;
    int *press_arr_size = &res_arr_size;
    point_t* res_arr = check_if_in_circle(arr, circle, radius, n, press_arr_size);

    if (res_arr == NULL) {
        free(arr);
        free(res_arr);
        return EXIT_FAILURE;
    }

    if (res_arr_size > 0) {
        printf("Lista punktow znajdujacych sie w danym okregu: \n");
        display_arr(res_arr, res_arr_size);
    } else
        printf("Brak punktow znajdujacych sie w danym okregu");

    free(arr);
    free(res_arr);
    return EXIT_SUCCESS;
}


double distance_from_origin(point_t point) {
    return sqrt(pow(2, 0 - point.x) + pow(2, 0 - point.y));
}

double distance(point_t point1, point_t point2) {
    return sqrt(pow(2, point2.x - point1.x) + pow(2, point2.y - point1.y));
}

point_t* read_arr(int n) {
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

point_t* check_if_in_circle(point_t* arr, const point_t circle, const double radius, const int n, int *res_arr_size) {
    point_t* new_arr = (point_t *)malloc(sizeof(point_t) * n);

    if (new_arr == NULL) {
        perror("Blad przy alokowaniu pamieci dla tablicy pomocniczej przy wyznaczaniu punktow zawierajacych sie w okregu");
        return NULL;
    }

    size_t i = 0;

    for(; i < n; i++)
        if (distance(circle, *(arr + i)) <= radius){
            *(new_arr + i) = *(arr + i);
            (*res_arr_size)++;
        }

    point_t* tmp = realloc(new_arr, sizeof(point_t) * (*res_arr_size));

    if (tmp == NULL && *res_arr_size > 0) {
        free(new_arr);
        perror("Blad przy realokacji pamieci");
        return NULL;
    }

    new_arr = tmp;

    return new_arr;
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
    double pivot = distance_from_origin(*high);
    point_t* i = low - 1;
    point_t* j = low;

    for (; j < high; j++)
        if (distance_from_origin(*j) >= pivot) {
            i++;
            swap(i, j);
        }

    i++;
    swap(i, high);

    return i;
}

void quicksort(point_t* low, point_t* high) {
    if (low < high) {
        point_t* pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

void sort_by_distance(point_t* arr, const int n) {
    if (n > 1)
        quicksort(arr, arr + n - 1);
}