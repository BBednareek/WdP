#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double distance(double, double, double, double);

struct Point {
    double x;
    double y;
};

int main(void) {
    struct Point point1;
    struct Point point2;

    printf("Podaj wspolrzedna X pierwszego punktu: ");
    scanf("%lf", &point1.x);

    printf("Podaj wspolrzedna Y pierwszego punktu: ");
    scanf("%lf", &point1.y);

    printf("Podaj wspolrzedna X drugiego punktu: ");
    scanf("%lf", &point2.x);

    printf("Podaj wspolrzedna Y drugiego punktu: ");
    scanf("%lf", &point2.y);


    printf("Podane punkty: ");
    printf("(%.2lf, %.2lf), (%.2lf, %.2lf)", point1.x, point1.y, point2.x, point2.y);

    const double result = distance(point1.x, point2.x, point1.y, point2.y);

    printf("\nOdleglosc pomiedzy punktami wynosi: %.2lf", result);

    return EXIT_SUCCESS;
}

double distance(double x1, double x2, double y1, double y2) {
    return sqrt(pow(2, x2 - x1) + pow(2, y2 - y1));
}