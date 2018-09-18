#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileReader.h"


struct tsp{
    char* name;
    char* comment;
    char* type;
    int dimension;
    char* edge_weight_type;
    City** node_coord_section; //array of cities with size of dimension
};

TSP* init_tsp(char* name, char* comment, char* type, int dimension, char* edge_weight_type){
    TSP* new_tsp = malloc(sizeof(*new_tsp)); //mallocs the size of the struct

    new_tsp->name = malloc(strlen(name)+1); //mallocs the name string
    strcpy(new_tsp->name, name);

    new_tsp->comment = malloc(strlen(comment)+1); //mallocs the comment string
    strcpy(new_tsp->comment, comment);

    new_tsp->type = malloc(strlen(type)+1); //mallocs the type string
    strcpy(new_tsp->type, type);

    new_tsp->dimension = dimension;

    new_tsp->edge_weight_type = malloc(strlen(edge_weight_type)+1); //mallocs the edge weight type string
    strcpy(new_tsp->edge_weight_type, edge_weight_type);

    return new_tsp;
}

int get_tsp_dimension(TSP* tsp){
    return tsp->dimension;
}

City** get_tsp_coord_section(TSP* tsp){
    return tsp->node_coord_section;
}


void print_tsp(TSP* tsp){
    printf("NAME: %s\n", tsp->name);
    printf("COMMENT: %s\n", tsp->comment);
    printf("TYPE: %s\n", tsp->type);
    printf("DIMENSION: %d\n", tsp->dimension);
    printf("EDGE_WEIGHT_TYPE: %s\n", tsp->edge_weight_type);
    printf("NODE COORD SECTION\n");
    for(int i = 0; i < tsp->dimension; i++){
        print_city(tsp->node_coord_section[i]);
    }
}


void free_tsp_cities(TSP* tsp){
    for(int i = 0; i < tsp->dimension; i++){
        free_city(tsp->node_coord_section[i]);
    }
    free(tsp->node_coord_section);
}

void free_tsp(TSP* tsp){
    free(tsp->name);
    free(tsp->comment);
    free(tsp->type);
    free(tsp->edge_weight_type);
    free_tsp_cities(tsp);
    free(tsp);
}

TSP* read_tsp_file(char* filename){
    FILE* file = fopen(filename, "r");
    if(!file){
        printf("File %s does not exist! Aborting!\n", filename);
        return NULL;
    }  

    char name[32] = "";
    char comment[100] = "";
    char type[10] = "";
    char dimension_[10] = "";
    char edge_weight_type[32] = "";
    char buffer[52] = "";


    //reads the name of the problem
    fscanf(file, "%s ", name); //ignore the "NAME: " string
    fscanf(file, "%s", name);

    //reads the comment of the problem
    fscanf(file, "%s ", comment); //ignore the "COMMENT: " string
    fgets(comment, 100, file);
    comment[strcspn(comment, "\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //reads the type of the problem
    fscanf(file, "%s ", type); //ignore the "TYPE: " string
    fgets(type, 10, file);
    type[strcspn(type,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'
    
    //reads the dimension of the problem
    fscanf(file, "%s ", dimension_); //ignore the "DIMENSION: " string
    fgets(dimension_, 10, file);
    dimension_[strcspn(dimension_,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //reads the edge_weight_type of the problem
    fscanf(file, "%s ", edge_weight_type); //ignore the "EDGE_WEIGHT_TYPE: " string
    fgets(edge_weight_type, 32, file);
    edge_weight_type[strcspn(edge_weight_type, "\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //ignore the NODE_COORD_SECTION line 
    fgets(buffer, 52, file);

    //creates and initializes the TSP struct
    int dimension = atoi(dimension_);
    TSP* tsp = init_tsp(name, comment, type, dimension, edge_weight_type); 


    City** city_array = malloc(dimension * sizeof(*city_array));
    tsp->node_coord_section = city_array; //sets the node_coord_section as the array just allocated

    for(int i = 0; i < dimension; i++){
        fgets(buffer, 52, file); //read the line which contains the id and Xcoord and Ycoord

        char* token = strtok(buffer, " ");
        int city_id = atoi(token);

        token = strtok(NULL," ");
        float x = strtod(token, NULL);

        token = strtok(NULL," ");
        float y = strtod(token, NULL);

        //creates new city and inserts it on the array
        City* city = init_city(city_id, x, y); 
        city_array[i] = city;
    }

    fclose(file);

    return tsp;
}