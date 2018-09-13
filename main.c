#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"



int main(){

    TSP* t = init_tsp("berlin52", "52 locations in Berlin (Groetschel)", "TSP", 52, "EUC_2D");
    print_tsp(t);
    free_tsp(t);
    read_tsp_file("cleber");

    return 0;
}