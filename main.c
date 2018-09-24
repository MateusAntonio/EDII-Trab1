#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"


/*TODO
    *ler arquivo de entrada                                 OK
    *armazenar dados necessarios em variaveis               +/-
    *gerar grafo completo                                   OK
    *gerar a MST                                            OK
    *fazer busca primeiro em profundidade                   
    *gerar tour pelos tempos de vertices encontrados
    *
    *
    *
*/

int main(int argc, char* argv[]){

    //reads the input file
    TSP* tsp = read_tsp_file(argv[argc-1]);

    //keep the useful data in variables
    char* tsp_name = get_tsp_name(tsp);
    char* tsp_type = get_tsp_type(tsp); 
    int tsp_dimension = get_tsp_dimension(tsp);
    City* city_array = get_tsp_coord_section(tsp);


    //gerenates the graph based on the cities read from the input file
    Graph* graph = generate_graph(city_array, tsp_dimension);
                    // printf("\n************ NOT SORTED ************\n");
                    // print_graph(graph);


    //sorts the graph by its edges weight
    sort_graph(graph);
                    // printf("\n************ SORTED ************\n");
                    // print_graph(graph);


    //uses the sorted edges to create the MST using the kruskal algorithm
    Graph* mst = generate_mst(graph, tsp_dimension);
                    // printf("\n************ MINIMAL SPANNING TREE ************\n");
                    // print_graph(mst);


    //free the complete graph that wont be used anymore
    free_graph(graph);
    printf("liberando grafo..\n");


    write_mst(tsp_name, tsp_type, tsp_dimension, mst);
    //execute a depth-first-search in the mst to generate the tour
    //TODO





    printf("\nliberando tsp..\n");
    free_tsp(tsp); 

    printf("liberando mst..\n");
    free_graph(mst);
    //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}