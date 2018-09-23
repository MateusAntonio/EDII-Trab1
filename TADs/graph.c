#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "city.h"

int* id;
int* sz;
int N;


//struct to represent an Arc of a graph
typedef struct arc{
    unsigned int weight;		//distance between the cities
    City cityA;
    City cityB;
}Arc;

//struct to represent a graph based on a list of Arcs
struct graph{
    int size;			//number of arcs in the graph
    Arc* arc_array;	//list of arcs of the graph
};


Arc create_arc(unsigned int weight, City cityA, City cityB){
    Arc new_arc;

    new_arc.weight = weight;
    new_arc.cityA = cityA;
    new_arc.cityB = cityB;

    return new_arc;
}


int arc_compare(const void* arc1, const void* arc2){
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

    new_graph->arc_array = malloc(dimension * sizeof(Arc));

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


Graph* generate_graph(void* array, int dimension){
    City* city_array = (City*)array;
    Graph* graph = init_graph(calc_arc_array_size(dimension)); //graph with all arcs of the problem
    
    for(int i = 0; i < dimension-1; i++){   
        // printf("******************CIDADEEE*********************\n");
        // print_city(city_array[i]);
        for(int j = i+1; j < dimension; j++){
            // printf("CIDADEEE    ");
            // print_city(city_array[j]);

            //calculates the distance between two difenrent cities and creates an Arc struct
            City a = city_array[i];
            City b = city_array[j];

            unsigned int distance = dist_city(a, b);                 //TODO estoura o limite de inteiros no maior teste
            // printf("DISTANCIAAAAAAA: %d\n\n", distance);

			//creates a new arc and inserts it on the array of arcs
            Arc arc = create_arc(distance, a, b); 

            graph->arc_array[graph->size] = arc;
            graph->size++;
        }
    }

	return graph;
}


void sort_graph(Graph* graph){
	qsort(graph->arc_array, graph->size, sizeof(Arc), arc_compare);
}


//******************************************
// "Weighted QU + path compression" adapted from source code presented on class
void UF_init(int size){
    N = size;
    id = malloc(N * sizeof(*id));
    sz = malloc(N * sizeof(*sz));
    for(int i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
    }
}


int UF_find(int i){
    while(i != id[i])
        i = id[i];
    return i;
}


void UF_union(int p, int q){
    int i = UF_find(p);
    int j = UF_find(q);

    if(i == j)
        return;
    if(sz[i] < sz[j]){
        id[i] = j;
        sz[j] += sz[i];
    }else{
        id[j] = i;
        sz[i] += sz[j];
    }
}


bool UF_connected(int p, int q){
    return UF_find(p) == UF_find(q);
}
//******************************************


Graph* generate_mst(Graph* graph, int mst_dimension){
    /*KRUSKAL ALGORITHM*/
    Graph* mst = init_graph(mst_dimension); //mst must contain the number of vertex-1 arcs 
    UF_init(mst_dimension+1); //union find must have an array with the size of vertex

    for(int i = 0; i < graph->size; i++){   
        City a = graph->arc_array[i].cityA;
        City b = graph->arc_array[i].cityB;

        int A_id = get_city_id(a);
        int B_id = get_city_id(b);

        if(!UF_connected(A_id, B_id)){  //verify if the components are in the same set 
            Arc mst_arc = graph->arc_array[i];          
            mst->arc_array[mst->size] = mst_arc;        //TODO posso fazer tudo numa linha só
            mst->size++;

            UF_union(A_id, B_id); //unites the sets 
            if(mst->size == mst_dimension) break; //when mst is complete stop
        }
    }

    //freeds the allocated memory for the UF operation
    free(id);   
    free(sz);

    return mst;
}




/*TODO
	*alocar vetorzao para todos os arcos da graph								OK  
	*calcular a distancia entre todas as cidades e inicializar a struct ARC		OK
	*inserir todos os arcos criados no vetorzao									OK
	*ordenar por ordem nao-decrescente											OK
	*GERAR A MST                                                                OK
    *liberar os bagulho(ver direito pq acho q vai dar merda)                    RESPECT MY HISTORY
*/