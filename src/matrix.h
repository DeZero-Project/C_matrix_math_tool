#ifndef MATRIX_H
#define MATRIX_H

typedef struct { 
    size_t rows; 
    size_t cols;
    double *data;
 } Matrix;

Matrix *create_matrix(size_t rows, size_t cols);
int print_matrix(Matrix *data);
Matrix *add_matrix(Matrix *data_x, Matrix *data_y);
void free_matrix(Matrix *data);

#endif