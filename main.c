#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/City.h"
#include "TADs/mst.h"



int main(int argc, char* argv[]){
    TSP* tsp = read_tsp_file(argv[argc-1]);
    // print_tsp(tsp);
    generate_mst(tsp);
    free_tsp(tsp);
    
    return 0;
}