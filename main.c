#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"



int main(int argc, char* argv[]){
    // printf("%d\n", calc_arc_array_size(18512)); //resulta do eh 171337816 MANO ISSO VAI DAR BOSTAAAAAAAAAA 
    TSP* tsp = read_tsp_file(argv[argc-1]);
    // print_tsp(tsp);

    Graph* g = generate_graph(get_tsp_coord_section(tsp), get_tsp_dimension(tsp));

    // printf("\n************ NOT SORTED ************\n");
    // print_graph(g);

    // printf("\n************ SORTED ************\n");
    // sort_graph(g);
    // print_graph(g);

    printf("\n************ MINIMAL SPANNING TREE ************\n");
    Graph* mst = generate_mst(g, get_tsp_dimension(tsp));
    // print_graph(mst);

    printf("\nliberando tsp..\n");
    free_tsp(tsp); 
    printf("liberando grafo..\n");
    free_graph(g);
    printf("liberando mst..\n");
    free_graph(mst);
    //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}