#include "City.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define free_city(city) free(city)

struct city{
    int id;
    float x;
    float y;
};

City* init_city(int id, float x, float y){
    City* city = malloc(sizeof(*city));
    city->id = id;
    city->x = x;
    city->y = y;
    return city;
}

int dist_city(City* cityA, City* cityB){
    int xd = cityB->x - cityA->x;
    int yd = cityB->y - cityA->y;
    return round(sqrt((xd*xd) + (yd*yd)));
}

int main(int argc, char const *argv[]){
    City* cityA = init_city(0, 100, 200);
    City* cityB = init_city(1, 200, 400);

    printf("id: %d, x: %.1f e y: %.1f\n", cityA->id, cityA->x, cityA->y);
    printf("id: %d, x: %.1f e y: %.1f\n", cityB->id, cityB->x, cityB->y);

    printf("%d\n",dist_city(cityA, cityB));

    free_city(cityA);
    free_city(cityB);

    
    return 0;
}
