#include <stdio.h>
#include <stdlib.h>
#include "mst.h"
#include "City.h"

typedef struct arc{
    int weight;
    City* cityA;
    City* cityB;
}Arc;


struct mst{
    int size;
    Arc** arc_array;
};


Arc* create_arc(int weight, City* cityA, City* cityB){
    Arc* new_arc = malloc(sizeof(*new_arc));

    new_arc->weight = weight;
    new_arc->cityA = cityA;
    new_arc->cityB = cityB;

    return new_arc;
}


void print_arc(Arc* arc){
    printf("\nweight %d\n",arc->weight);
    printf("ARC:\n");
    print_city(arc->cityA);
    print_city(arc->cityB);
}


MST* init_mst(int dimension){
    MST* new_mst = malloc(sizeof(*new_mst));
    
    new_mst->size = 0;

    int array_size = calc_arc_array_size(dimension);
    new_mst->arc_array = malloc(array_size * sizeof(Arc*));

    return new_mst;
}


int calc_arc_array_size(int dimension){ //calculates the max different arcs possible 
    int sum = 0;
    for(int cont = dimension-1; cont > 0; cont--){ // (dimension-1) + (dimension-2) + ... + 1
      sum += cont;
    }
	return sum;
}


MST* generate_mst(TSP* tsp){ //TODO
    int dimension = get_tsp_dimension(tsp);
    MST* graph = init_mst(dimension); //graph with all arcs of the problem
    
    for(int i = 0; i < dimension-1; i++){   
        // printf("******************CIDADEEE*********************\n");
        // print_city(get_tsp_coord_section(tsp)[i]);
        for(int j = i+1; j < dimension; j++){
            // printf("CIDADEEE    ");
            // print_city(get_tsp_coord_section(tsp)[j]);

            //calculates the distance between two difenrent cities and creates a Arc struct
            City* a = get_tsp_coord_section(tsp)[i];
            City* b = get_tsp_coord_section(tsp)[j];

            int distance = dist_city(a, b);
            // printf("DISTANCIAAAAAAA: %d\n\n", distance);

            Arc* arc = create_arc(distance, a, b);       
            graph->arc_array[graph->size] = arc;
            graph->size++;
        }
    }

	return graph; //trocar pra retornar a mst
}

void print_mst(MST* mst){
    for(int i = 0; i < mst->size; i++){
        print_arc(mst->arc_array[i]);
    }
}

/*TODO
	*alocar vetorzao para todos os arcos da mst                                 OK  
	*calcular a distancia entre todas as cidades e inicializar a struct ARC     OK
	*inserir todos os arcos criados no vetorzao                                 OK
	*ordenar por ordem nao-decrescente                                          
	*union-find                                                                 
    *liberar os bagulho(ver direito pq acho q vai dar merda)
*/