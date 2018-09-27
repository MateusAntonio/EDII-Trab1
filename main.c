#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"

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

    //sorts the graph by its edges weight
    sort_graph(graph);

    //uses the sorted edges to create the MST using the kruskal algorithm
    Graph* mst = generate_mst(graph, tsp_dimension);

    //free the complete graph that wont be used anymore
    free_graph(graph);

    //generates the .mst file
    write_mst(tsp_name, tsp_dimension, mst);

    //generates the tour and .tour file
    generate_tour(tsp_dimension);
    write_tour(tsp_name, tsp_dimension);

    //calculates the cost of the tour and the mst
    //(function just prints the costs)
    // calc_tour_and_mst_cost(mst, city_array, tsp_dimension);


    //frees the allocated memory :)
    free_tour();
    free_graph(mst);
    free_tsp(tsp); 
    
    return 0;
}