#ifndef CITY_H
#define CITY_H

struct city{
    int id;
    float x;
    float y;
};

typedef struct city City;

City init_city(int id, float x, float y);

unsigned int dist_city(City cityA, City cityB);

void print_city(City city);

int get_city_id(City city);

#endif //CITY_H