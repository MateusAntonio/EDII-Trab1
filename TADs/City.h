#ifndef CITY_H
#define CITY_H

typedef struct city City;

City* init_city(int id, float x, float y);

int dist_city(City* cityA, City* cityB);

void print_city(City* city);

#define free_city(city) free(city)

#endif //CITY_H