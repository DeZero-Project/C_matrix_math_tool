#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
int main(void)
{

    printf("Hello world!\n");
    int row = 2;
    int col = 3;


    Matrix *data_x = create_matrix(row, col);
    Matrix *data_y = create_matrix(row, col);

    for (int i = 0; i < row * col; i++)
    {
        data_x->data[i] = 2.7;
        data_y->data[i] = 5.5;
    }
    
    Matrix *result = add_matrix(data_x, data_y);
    if (result == NULL)
    {
        fprintf(stderr, "計算結果が正しく格納されませんでした。");
        exit(1);
    }
    print_matrix(result);
    free_matrix(data_x);
    free_matrix(data_y);
    free_matrix(result);
    return 0;
}
