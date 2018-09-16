#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/City.h"



int main(int argc, char* argv[]){

    // TSP* t = init_tsp("berlin52", "52 locations in Berlin (Groetschel)", "TSP", 52, "EUC_2D");
    // print_tsp(t);
    // free_tsp(t);

    TSP* a = read_tsp_file(argv[argc-1]);
    print_tsp(a);

    // City* a = init_city(0, 100, 200);
    // City* b = init_city(1, 200, 400);
    // int d = dist_city(a, b);
    // printf("dist %d\n", d);
    // free_city(a);
    // free_city(b);

    return 0;
}