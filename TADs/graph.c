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

//aux struct to generate the tour
typedef struct vertex{
    int id;             //id of the vertex
    int Adj[6];         //list of adjacency
}Vertex;

Vertex* vertex_vet; //array to the used in the tour generation

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
    for(int i = 0; i < 6; i++)
        new_vertex.Adj[i] = 0;

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

void teste(){
    Vertex vet[2];

    Vertex v1 = create_vertex(1);
    Vertex v2 = create_vertex(2);
    Vertex v3 = create_vertex(3);

    v1 = add_adj_vertex(v1, 2);
    v1 = add_adj_vertex(v1, 3);

    v2 = add_adj_vertex(v2, 1);
    v2 = add_adj_vertex(v2, 3);


    vet[0] = v1;
    vet[1] = v2;
    vet[3] = v3;

    print_vertex(v1);
    print_vertex(v2);
    print_vertex(v3);
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


void init_tour(int dimension){
    vertex_vet = malloc(dimension+1 * sizeof(vertex_vet));

    for(int i = 1; i < dimension+1; i++)     //init the array of vertex wich the id is the index 
        create_vertex(i);
}


Graph* generate_mst(Graph* graph, int mst_dimension){
    /*KRUSKAL ALGORITHM*/
    Graph* mst = init_graph(mst_dimension); //mst must contain the number of vertex-1 arcs 
    UF_init(mst_dimension+1); //union find must have an array with the size of vertex

    // init_tour(mst_dimension);

    for(int i = 0; i < graph->size; i++){   
        City a = graph->arc_array[i].cityA;     //get the first city of the arc
        City b = graph->arc_array[i].cityB;     //get the second city of the arc

        int A_id = get_city_id(a);
        int B_id = get_city_id(b);

        if(!UF_connected(A_id, B_id)){  //verify if the components are in the same set 
            Arc mst_arc = graph->arc_array[i];          
            mst->arc_array[mst->size] = mst_arc;        //TODO posso fazer tudo numa linha só
            mst->size++;

            //when its a arc adds the id of the city on the adj list of the other
            // vertex_vet[A_id] = add_adj_vertex(vertex_vet[A_id], B_id);
            // vertex_vet[B_id] = add_adj_vertex(vertex_vet[B_id], A_id);            


            UF_union(A_id, B_id); //unites the sets 
            if(mst->size == mst_dimension) break; //when mst is complete stop
        }
    }
    UF_free();

    return mst;
}


int* generate_tour(Graph* mst){
    int dimension = mst->size;

    int j;
    init_tour(dimension);

    for ( j = 0; j < dimension; j++){
        int A_id = get_city_id(mst->arc_array[j].cityA);
        int B_id = get_city_id(mst->arc_array[j].cityB);

        vertex_vet[A_id] = add_adj_vertex(vertex_vet[A_id], B_id);
        vertex_vet[B_id] = add_adj_vertex(vertex_vet[B_id], A_id);            
    }


    for(int i = 1; i < dimension+1; i++) // TODO ta soh printando ainda
        print_vertex(vertex_vet[i]);

    free(vertex_vet);

    return NULL; //TODO mudar retorno
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