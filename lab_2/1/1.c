#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    double x;
    double y;
} point_t;

double distance(point_t, point_t);

int main(void) {
    point_t point1;
    point_t point2;

    printf("Podaj wspolrzedne pierwszego punktu: ");
    scanf("%lf %lf", &point1.x, &point1.y);

    printf("\nPodaj wspolrzedne drugiego punktu: ");
    scanf("%lf %lf", &point2.x, &point2.y);

    printf("\nPodane punkty: ");
    printf("\n(%.2lf, %.2lf), (%.2lf, %.2lf)", point1.x, point1.y, point2.x, point2.y);

    const double result = distance(point1, point2);

    printf("\nOdleglosc pomiedzy punktami wynosi: %.2lf", result);

    return EXIT_SUCCESS;
}

double distance(point_t point1, point_t point2) {
    return sqrt(pow(2, point2.x - point1.x) + pow(2, point2.y - point2.y));
}