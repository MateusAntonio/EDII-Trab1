#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"


/*TODO
    *ler arquivo de entrada                                 OK
    *armazenar dados necessarios em variaveis               OK
    *gerar grafo completo                                   OK
    *gerar a MST                                            OK
    *gerar tour pela lista de adjacencias                   
    *
    *
    *
*/

int main(int argc, char* argv[]){

    // teste();
    //reads the input file
    TSP* tsp = read_tsp_file(argv[argc-1]);

    //keep the useful data in variables
    char* tsp_name = get_tsp_name(tsp);
    char* tsp_type = get_tsp_type(tsp); 
    int tsp_dimension = get_tsp_dimension(tsp);
    City* city_array = get_tsp_coord_section(tsp);


    //gerenates the graph based on the cities read from the input file
    Graph* graph = generate_graph(city_array, tsp_dimension);
    printf("gerou grafo!!!!!!!!!\n");


    //sorts the graph by its edges weight
    sort_graph(graph);
    printf("ordenou o grafo!!!!!!!!!\n");


    //uses the sorted edges to create the MST using the kruskal algorithm
    Graph* mst = generate_mst(graph, tsp_dimension);
    printf("gerou MST!!!!!!!!!\n");


    //free the complete graph that wont be used anymore
    free_graph(graph);
    printf("liberando grafo..\n");


    printf("GERANDO ARQ SAIDA!!!!!!!!!\n");
    //generates the .mst file
    write_mst(tsp_name, tsp_type, tsp_dimension, mst);


    // generate_tour(mst);
    //generates the .tour file
    // write_tour(tsp_name, tsp_dimension);


    printf("\nliberando tsp..\n");
    free_tsp(tsp); 

    printf("liberando mst..\n");
    free_graph(mst);
    //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}