#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "city.h"
#include "fileWriter.h"
#include "UF.h"

typedef struct vertex Vertex;

//global variables
Vertex* vertex_vet;         //array to the used in the tour generation
int* tour;                  //array with the sequence of cities id 
int tour_index = 0;


//struct to represent an Arc of a graph
typedef struct arc{
    unsigned int weight;		//distance between the cities
    City cityA;
    City cityB;
}Arc;

//aux struct to generate the tour
struct vertex{
    int id;             //id of the vertex
    bool visited;       //check if the vertex was already discovered
    int Adj[6];         //list of adjacency
};

//struct to represent a graph based on a list of Arcs
struct graph{
    int size;			//number of arcs in the graph
    Arc* arc_array;	    //list of arcs of the graph
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


Vertex create_vertex(int id){
    Vertex new_vertex;

    new_vertex.id = id;
    new_vertex.visited = false;
    for(int i = 0; i < 6; i++)
        new_vertex.Adj[i] = 0;  //set to 0 cuz there is no city with id 0

    return new_vertex;
}


Vertex add_adj_vertex(Vertex vertex, int adj_id){
    for(int i = 0; i < 6; i++){
        if(vertex.Adj[i] == 0){
            vertex.Adj[i] = adj_id;
            break;
        }
    }
    return vertex;
}
 

void print_vertex(Vertex v){
    printf("vertex id: %d\n", v.id);
    printf("Adj: ");
    for(int i = 0; i < 6; i++){
        if(v.Adj[i] != 0)
            printf("%d ", v.Adj[i]);
    }
    printf("\n");
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


Graph* generate_graph(void* array, int dimension){
    City* city_array = (City*)array;
    Graph* graph = init_graph(((dimension*dimension)-dimension)/2); //graph with all arcs of the problem
    for(int i = 0; i < dimension-1; i++){ 
        for(int j = i+1; j < dimension; j++){
            //calculates the distance between two difenrent cities
            City a = city_array[i];
            City b = city_array[j];
            unsigned int distance = dist_city(a, b);

			//creates a new arc and inserts it on the array of arcs
            graph->arc_array[graph->size++] = create_arc(distance, a, b);
        }
    }

	return graph;
}


void sort_graph(Graph* graph){
	qsort(graph->arc_array, graph->size, sizeof(Arc), arc_compare);
}


void init_tour(int dimension){
    vertex_vet = malloc((dimension+1) * sizeof(Vertex));
  
    for(int i = 0; i < dimension+1; i++)     //init the array of vertex wich the id is the index 
        vertex_vet[i] = create_vertex(i);
}


Graph* generate_mst(Graph* graph, int mst_dimension){
    /*KRUSKAL ALGORITHM*/
    Graph* mst = init_graph(mst_dimension); //mst must contain the number of vertex-1 arcs 
    UF_init(mst_dimension+1); //union find must have an array with the size of vertex

    init_tour(mst_dimension+1); //init the array wich contains the sequence of the tour

    for(int i = 0; i < graph->size; i++){   
        int A_id = get_city_id(graph->arc_array[i].cityA);      //get the id of the first city of the arc
        int B_id = get_city_id(graph->arc_array[i].cityB);      //get the id of the second city of the arc

        if(!UF_connected(A_id, B_id)){  //verify if the components are in the same set 
            mst->arc_array[mst->size++] = graph->arc_array[i];

            //when its a arc adds the id of the city on the adj list of the other
            vertex_vet[A_id] = add_adj_vertex(vertex_vet[A_id], B_id);
            vertex_vet[B_id] = add_adj_vertex(vertex_vet[B_id], A_id);            


            UF_union(A_id, B_id); //unites the sets 
            if(mst->size == mst_dimension) break; //when mst is complete stop
        }
    }
    UF_free();

    return mst;
}


void dfs(Vertex v){
    vertex_vet[v.id].visited = true;    //mark as visited
    tour[tour_index++] = v.id;          //add the id of the vertex in the tour array
    
    for(int i = 0; i < 6; i++){
        //check  if there is connection to other vertex and if vertex is already visited
        int neighbor = vertex_vet[v.id].Adj[i];
        if( (neighbor != 0) && (!vertex_vet[neighbor].visited) )
            dfs(vertex_vet[neighbor]);
    }
}


void generate_tour(int dimension){
    tour = malloc(dimension * sizeof(*tour));

    dfs(vertex_vet[1]);     //depth-first-search in the graph
}


void write_mst(char* name, int dimension, Graph* mst){
    write_mst_info(name, dimension);
    for(int i = 0; i < mst->size; i++){
        int id1 = get_city_id(mst->arc_array[i].cityA);
        int id2 = get_city_id(mst->arc_array[i].cityB);
        write_mst_arc(id1, id2);
    }
    write_mst_eof();
}


void write_tour(char* name, int dimension){
    write_tour_info(name, dimension);
    for(int i = 0; i < tour_index; i++)
        write_tour_city(tour[i]);
    write_tour_eof();
}


void free_tour(){
    free(vertex_vet);
    free(tour);
}

void calc_tour_and_mst_cost(Graph* mst, void* tsp_city_array, int dimension){
    unsigned int tour_cost = 0;
    int mst_cost = 0;
    City* city_array = (City*)tsp_city_array;

    for(int i = 0; i < dimension; i++)
        mst_cost += mst->arc_array[i].weight; 
    printf("custo mst: %d\n", mst_cost);

    for(int i = 0; i < tour_index; i++){
        int city_id = tour[i];
        City a = city_array[city_id-1];     //get the city by the id in the city array
        City b;
        if(city_id == tour_index){
            b = city_array[tour[0]-1];
            tour_cost += dist_city(a,b);    //if is in the last position of array, get the first city of array
            break;
        }
        b = city_array[tour[i+1]-1];        //get the next city of the tour
        tour_cost += dist_city(a,b);    
    }
    printf("custo tour: %d\n", tour_cost);  //NOT GIVING CORRECT RESULTS
}