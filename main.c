#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/City.h"
#include "TADs/mst.h"



int main(int argc, char* argv[]){
    TSP* tsp = read_tsp_file(argv[argc-1]);
    // print_tsp(tsp);
    MST* mst = generate_mst(tsp);
    print_mst(mst);
    free_tsp(tsp); //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}