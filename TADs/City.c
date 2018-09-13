#include "City.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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


