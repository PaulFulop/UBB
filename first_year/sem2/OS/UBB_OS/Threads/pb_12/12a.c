#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int** mat;
    int row, cols, rowSum;
}data;

void *RowSum(void* arg){
    data* d = (data*) arg;
    for(int i = 0; i < d->cols; ++i)
        d->rowSum += d->mat[d->row][i];

    return NULL;
}

int main(int argc, char** argv){

    if(argc != 2){
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    FILE* stream = fopen(argv[1], "r");
    if(stream == NULL){
        printf("Error opening the file.\n");
        exit(1);
    }

    int rows, cols;
    fscanf(stream, "%d%d", &rows, &cols);

    int** mat = malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; ++i)
        mat[i] = malloc(cols * sizeof(int));


    for (int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            fscanf(stream, "%d", &mat[i][j]);

    pthread_t* th = malloc(sizeof(pthread_t) * rows); 
    data* args = malloc(sizeof(data) * rows);

    for(int i = 0; i < rows; ++i){
        args[i].mat = mat;
        args[i].row = i;
        args[i].cols = cols;
        args[i].rowSum = 0;
        pthread_create(&th[i], NULL, RowSum, (void*)&args[i]);
    }

    for(int i = 0; i < rows; ++i)
        pthread_join(th[i], NULL);

    for(int i = 0; i < rows; ++i)
        printf("Sum of row %d: %d\n", i, args[i].rowSum);
    
    fclose(stream);
    for(int i = 0; i < rows; ++i)
        free(mat[i]);
    free(mat);
    free(th);
    return 0;
}
