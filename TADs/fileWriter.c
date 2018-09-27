#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileWriter.h"

FILE* mst_file;
FILE* tour_file;

void write_mst_info(char* name, int dimension){
    char filename[52] = "mst/";
    sprintf(filename + strlen(filename), "%s", name); //creates a name to be the file name
    sprintf(filename + strlen(filename), ".mst");

    mst_file = fopen(filename, "w");
    if(!mst_file){
        printf("Could not open %s. Aborting!", filename);
        return;
    }

    fprintf(mst_file, "NAME: %s\n", name);
    fprintf(mst_file, "TYPE: MST\n");
    fprintf(mst_file, "DIMENSION: %d\n", dimension);
    fprintf(mst_file, "MST_SECTION\n");
}

void write_mst_arc(int id1, int id2){
    fprintf(mst_file, "%d %d\n", id1, id2);
}

void write_mst_eof(){
    fprintf(mst_file, "EOF");
    fclose(mst_file);
}

void write_tour_info(char* name, int dimension){
    char filename[52] = "tour/";
    sprintf(filename + strlen(filename), "%s", name); //creates a name to be the file name
    sprintf(filename + strlen(filename), ".tour");

    tour_file = fopen(filename, "w");
    if(!tour_file){
        printf("Could not open %s. Aborting!", filename);
        return;
    }

    fprintf(tour_file, "NAME: %s\n", name);
    fprintf(tour_file, "TYPE: TOUR\n");
    fprintf(tour_file, "DIMENSION: %d\n", dimension);
    fprintf(tour_file, "TOUR_SECTION\n");
}

void write_tour_city(int city){
    fprintf(tour_file, "%d\n", city);
}

void write_tour_eof(){
    fprintf(tour_file, "EOF");
    fclose(tour_file);
}