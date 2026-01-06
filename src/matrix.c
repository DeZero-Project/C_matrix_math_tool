#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

Matrix *create_matrix(int rows, int cols){
    if (rows <=0 || cols <= 0){
        fprintf(stderr,"引数で値が渡されませんでした。");
        exit(1);

    };
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    if (m == NULL)
    {
       fprintf(stderr,"メモリ確保に失敗しました。");
       exit(1);
    }
    
    m->data = (double *)malloc(sizeof(double) * rows  * cols);
    if (m->data == NULL)
    {
        fprintf(stderr,"領域の確保に失敗しました。");
        exit(1);
    }
    /*初期化処理*/
    for (int i = 0; i < rows * cols; i++)
    {
        m->data[i] = 0.0;
    }
    m->rows = rows;
    m->cols = cols;
    return m;
};


int print_matrix(Matrix *data){
    if (data == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。");
        exit(1);
    }
    for (int i = 0; i < data->rows; i++)
    {
       for (int j = 0; j < data->cols; j++)
       {
        printf("%f\n", data->data[i * data->cols + j]);

       }
       
    }
    
    return 0;
};

Matrix *add_matrix(Matrix *data_x, Matrix *data_y){
    if (data_x == NULL || data_y == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。");
        exit(1);
    }
    if (data_x->rows != data_y->rows || data_x->cols != data_y->cols)
    {
        fprintf(stderr,"行列の形状が一致しませんでした。");
        exit(1);
    }
    Matrix *y = create_matrix(data_x->rows, data_x->cols);
    for (int i = 0; i < data_x->rows; i++)
    {
        for (int j = 0; j < data_x->cols; j++)
        {
            y->data[i * y->cols + j] = data_x->data[i * data_x->cols + j] + data_y->data[i * data_y->cols + j];
        }
        
    }
    return y;

    
};
void free_matrix(Matrix *data){
    if (data == NULL)
    {
        fprintf(stderr,"引数でポインタが渡されませんでした。");
        exit(1);
    }
    free(data->data);
    free(data);    
};
