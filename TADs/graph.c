#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "city.h"
#include "fileWriter.h"
#include "UF.h"


//struct to represent an Arc of a graph
typedef struct arc{
    unsigned int weight;		//distance between the cities
    City cityA;
    City cityB;
}Arc;

//struct to represent a graph based on a list of Arcs
struct graph{
    int size;			//number of arcs in the graph
    Arc* arc_array;	    //list of arcs of the graph
};

//aux struct to do a depth-first-search
struct vertex{
    int id;             //id of the vertex
    int* Adj;           //list of adjacency
    int color;          //color during the depth-first-search
    int father_id;      //father id
    int d;              //time the vertex was discovered
    int f;              //time the vertex was finished
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
        for(int j = i+1; j < dimension; j++){
            //calculates the distance between two difenrent cities
            City a = city_array[i];
            City b = city_array[j];
            unsigned int distance = dist_city(a, b);

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


Graph* generate_mst(Graph* graph, int mst_dimension){
    /*KRUSKAL ALGORITHM*/
    Graph* mst = init_graph(mst_dimension); //mst must contain the number of vertex-1 arcs 
    UF_init(mst_dimension+1); //union find must have an array with the size of vertex

    for(int i = 0; i < graph->size; i++){   
        City a = graph->arc_array[i].cityA;     //get the first city of the arc
        City b = graph->arc_array[i].cityB;     //get the second city of the arc

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
    UF_free();

    return mst;
}


void write_mst(char* name, char* type, int dimension, Graph* mst){
    write_mst_info(name, type, dimension);
    for(int i = 0; i < mst->size; i++){
        int id1 = get_city_id(mst->arc_array[i].cityA);
        int id2 = get_city_id(mst->arc_array[i].cityB);
        write_mst_arc(id1, id2);
    }
    write_mst_eof();
    // close_mst_file();
}


void write_tour(char* name, int dimension){ //TODO receber vetor de int com o tour
    write_tour_info(name, dimension);
    // for(int i = 0; i < AAAAAAAA;i++ ){
    //     //TODO
    // }
    write_tour_eof();
}


/*TODO
	*alocar vetorzao para todos os arcos da graph								OK  
	*calcular a distancia entre todas as cidades e inicializar a struct ARC		OK
	*inserir todos os arcos criados no vetorzao									OK
	*ordenar por ordem nao-decrescente											OK
	*GERAR A MST                                                                OK
    *pesquisa primeiro em profundidade ????
    *tour
    *liberar os bagulho(ver direito pq acho q vai dar merda)                    RESPECT MY HISTORY
*/