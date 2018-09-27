#include "city.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


City init_city(int id, float x, float y){
    City city;
    city.id = id;
    city.x = x;
    city.y = y;
    return city;
}

unsigned int dist_city(City cityA, City cityB){
    unsigned int xd = cityB.x - cityA.x;
    unsigned int yd = cityB.y - cityA.y;
    return round(sqrt((xd*xd) + (yd*yd)));
}

void print_city(City city){
    printf("city id: %d\n", city.id);
    // printf("Xcoord: %.1f\n", city->x);
    // printf("Ycoord: %.1f\n", city->y);
}

int get_city_id(City city){
    return city.id;
}
