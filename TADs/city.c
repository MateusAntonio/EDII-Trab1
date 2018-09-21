#include "city.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// struct city{
//     int id;
//     float x;
//     float y;
// };

City init_city(int id, float x, float y){
    City city;
    city.id = id;
    city.x = x;
    city.y = y;
    return city;
}

int dist_city(City cityA, City cityB){
    int xd = cityB.x - cityA.x;
    int yd = cityB.y - cityA.y;
    return round(sqrt((xd*xd) + (yd*yd))); //TODO isso vai dar merda no maior caso de teste
}

void print_city(City city){
    printf("city id: %d\n", city.id);
    // printf("Xcoord: %.1f\n", city->x);
    // printf("Ycoord: %.1f\n", city->y);
}
