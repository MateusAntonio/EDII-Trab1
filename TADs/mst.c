#include <stdio.h>
#include <stdlib.h>
#include "mst.h"
#include "City.h"

typedef struct arc{
    int weight;
    City* cityA;
    City* cityB;
}Arc;


struct mst{//TODO
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


int calc_arc_array_size(int dimension){
    int sum = 0;
    for(int cont = dimension-1; cont > 0; cont--){
      sum += cont;
    }
	return sum;
}

MST* generate_mst(TSP* tsp){ //TODO
    int dimension = get_tsp_dimension(tsp);
	int array_size = calc_arc_array_size(dimension);
    Arc** arc_array = malloc(array_size * sizeof(*arc_array));
    
    int k = 0;
    for(int i = 0; i < dimension-1; i++){   
        // printf("******************CIDADEEE*********************\n");
        // print_city(get_tsp_coord_section(tsp)[i]);
        for(int j = ++k; j < dimension; j++){
            // printf("CIDADEEE    ");
            // print_city(get_tsp_coord_section(tsp)[j]);

            //calculates the distance between two difenrent cities and creates a Arc struct
            City* a = get_tsp_coord_section(tsp)[i];
            City* b = get_tsp_coord_section(tsp)[j];

            int distance = dist_city(a, b);
            // printf("DISTANCIAAAAAAA: %d\n\n", distance);

            // Arc* arc = create_arc(distance, a, b);       //TODO INSERÇAO NO VETORZAO


        }
    }

	return NULL; //trocar pra retornar a mst
}


/*TODO
	*alocar vetorzao para todos os arcos da mst                                 OK  
	*calcular a distancia entre todas as cidades e inicializar a struct ARC     OK
	*inserir todos os arcos criados no vetorzao                                 
	*ordenar por ordem nao-decrescente                                          
	*union-find                                                                 
*/

// [c1,c2,c3,c4]
// [c1,c2,c3,c4]

// [c1->c2, c1->c3, c1->c4, c2->c3, c2->c4, c3->c4]

