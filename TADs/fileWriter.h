#ifndef FILE_WRITER_H
#define FILE_WRITER_H

void write_mst_info(char* name, int dimension);

void write_mst_arc(int id1, int id2);

void write_mst_eof();

void write_tour_info(char* name, int dimension);

void write_tour_city(int city);

void write_tour_eof();

#endif //FILE_WRITER_H