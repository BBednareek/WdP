#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double distance(struct Point, struct Point);

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

    const double result = distance(point1, point2);

    printf("\nOdleglosc pomiedzy punktami wynosi: %.2lf", result);

    return EXIT_SUCCESS;
}

double distance(struct Point point1, struct Point point2) {
    return sqrt(pow(2, point2.x - point1.x) + pow(2, point2.y - point1.y));
}
