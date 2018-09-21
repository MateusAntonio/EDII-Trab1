#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "city.h"

//struct to represent an Arc of a graph
typedef struct arc{
    int weight;		//distance between the cities
    City cityA;
    City cityB;
}Arc;

//struct to represent a graph based on a list of Arcs
struct graph{
    int size;			//number of arcs in the graph
    Arc* arc_array;	//list of arcs of the graph
};


Arc create_arc(int weight, City cityA, City cityB){
    Arc new_arc;

    new_arc.weight = weight;
    new_arc.cityA = cityA;
    new_arc.cityB = cityB;

    return new_arc;
}

int arc_compare(const void* arc1, const void* arc2){ //TODO mudar isso dps
	Arc a1 = *(Arc*)arc1;
	Arc a2 = *(Arc*)arc2;

	return (a1.weight - a2.weight);
}

void print_arc(Arc arc){
    printf("\nweight %d\n",arc.weight);
    printf("ARC:\n");
    print_city(arc.cityA);
    print_city(arc.cityB);
}


Graph* init_graph(int dimension){
    Graph* new_graph = malloc(sizeof(*new_graph));
    
    new_graph->size = 0;

    int array_size = calc_arc_array_size(dimension);
    new_graph->arc_array = malloc(array_size * sizeof(Arc));

    return new_graph;
}


void print_graph(Graph* graph){
    for(int i = 0; i < graph->size; i++){
        print_arc(graph->arc_array[i]);
    }
}


void free_graph(Graph* graph){
    free(graph->arc_array);
    free(graph);
}

int calc_arc_array_size(int dimension){ //calculates the max different arcs possible 
    int sum = 0;
    for(int cont = dimension-1; cont > 0; cont--){ // (dimension-1) + (dimension-2) + ... + 1
      sum += cont;
    }
	return sum;
}


Graph* generate_graph(TSP* tsp){	//TODO  necessario importrar TSP?? pq nao só passar como param o array e tamanho??
    int dimension = get_tsp_dimension(tsp);
    Graph* graph = init_graph(dimension); //graph with all arcs of the problem
    
    for(int i = 0; i < dimension-1; i++){   
        // printf("******************CIDADEEE*********************\n");
        // print_city(get_tsp_coord_section(tsp)[i]);
        for(int j = i+1; j < dimension; j++){
            // printf("CIDADEEE    ");
            // print_city(get_tsp_coord_section(tsp)[j]);

            //calculates the distance between two difenrent cities and creates a Arc struct
            City a = get_tsp_coord_section(tsp)[i];
            City b = get_tsp_coord_section(tsp)[j];

            printf("cleber\n");
            int distance = dist_city(a, b);
            printf("distance: %d", distance);
            // printf("DISTANCIAAAAAAA: %d\n\n", distance);

			//creates a new arc and inserts it on the array of arcs
            Arc arc = create_arc(distance, a, b); 
            printf("size: %d", graph->size);
            graph->arc_array[graph->size] = arc;
            graph->size++;
        }
    }

	return graph; //trocar pra retornar a graph
}




void sort_graph(Graph* graph){ //TODO algo acontece aq q nao sei explicar
	qsort(graph->arc_array, graph->size, sizeof(Arc), arc_compare);
}

// void teste(Graph* g){
// 	printf("maiooooooooooooor %d\n", arc_compare(g->arc_array[0], g->arc_array[1]) );
// 	printf("maiooooooooooooor %d\n", arc_compare(g->arc_array[1], g->arc_array[2]) );
// 	printf("maiooooooooooooor %d\n", arc_compare(g->arc_array[2], g->arc_array[3]) );
// }

/*TODO
	*alocar vetorzao para todos os arcos da graph								OK  
	*calcular a distancia entre todas as cidades e inicializar a struct ARC		OK
	*inserir todos os arcos criados no vetorzao									OK
	*ordenar por ordem nao-decrescente											OK
	*union-find																	
    *liberar os bagulho(ver direito pq acho q vai dar merda)
*/