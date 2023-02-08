/*+++++++++++++++++++++++++++++++++++

File Name: SequentialMatrixMultiplication.c
Author: Edgar Rene Ramos Acosta
Lenguage: C
Purpose: Next code below shows how matrices can be multiplied by using the sequential algorithm
Version: 1.0, 02-02-2023

--------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <curses.h>   

const int MAX_SIZE= 512;

void multiplyMatrices_ijk(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
void multiplyMatrices_jik(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
char *findArgument(int argc, char *argv[], char *cmd);


int main(int argc, char *argv[]){
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE];
    float subA[MAX_SIZE][MAX_SIZE], subB[MAX_SIZE][MAX_SIZE], subresultMatrix[MAX_SIZE][MAX_SIZE];
    int n=8, blkNumber=0, blk_size=0;
    int i, j,k;
    char *rank_cmd = "--rank";
    char *block_cmd= "--block-num";
    char *order_cmd= "--order";
    
#pragma region "arguments management"

    if(strcmp(argv[1],("--help"))==0)
    {
        printf("--help: Arguments:\n --rank stands for ranknumber\n--order: type ijk, jik, kij, kji, ikj, jki\n--block-num: stands for size of process blocks which matrix will be divided,\nresulting block size equals rank/block-num");
        exit(0);

    }
    if(strcmp(argv[1],("--info"))==0)
    {
   
        printf("--info: File Name: multest.c\nAuthor: Edgar Rene Ramos Acosta\nDate: 02-02-2023 \nLenguage: C\nPurpose: Next code below shows how matrices can be multiplied by using the sequential algorithm\n");
        printf("get repository by entering next commands in your terminal: ");
        printf("\033[0;32m"); //Set the text to the color green
        printf("git clone https://github.com/edramos10/Distributed-Systems.git \nmain app is task1, while source code is multest.c");
        printf("\033[0m"); //Resets the text to default color
        exit(0);

    }
   

        
    char *rankNumber = findArgument(argc, argv, rank_cmd);
    if (strlen(rankNumber) > 0) {
        printf("rankNumber: %s\n", rankNumber);
        n=atoi(rankNumber);
    } else {
        printf("\033[0;31m"); //Set the text to the color red
        printf("rankNumber not found\n");
        printf("\033[0m"); //Resets the text to default color
        printf("Exiting from program...");
        exit(0);
    }
    char *blockNumber = findArgument(argc, argv, block_cmd);
    if (strlen(blockNumber) > 0) {
        
        blkNumber=atoi(blockNumber);
        blk_size=n/blkNumber;
        printf("blockNumber: %s / block size: %d\n", blockNumber, blk_size);
    } else {
        printf("\033[0;31m"); //Set the text to the color red
        printf("blockNumber not found\n");
        printf("\033[0m"); //Resets the text to default color
        printf("Exiting from program...");
        exit(0);
    }

    char *order = findArgument(argc, argv, order_cmd);
    if (strlen(order) > 0) {
        printf("order: %s\n", order);
    
    } else {
        printf("\033[0;31m"); //Set the text to the color red
        printf("order which matrices would be multiplied (ijk, jik, ...etc) not found\n");
        printf("\033[0m"); //Resets the text to default color
        printf("Exiting from program...");
        exit(0);
    }

  


#pragma endregion

#pragma region "Autofilling matrices with random float numbers"
    printf("--Autofilling matrix with random numbers--\n");
    for (i = 0; i < n; i++) {
       for (j = 0; j < n; j++) {
    
            A[i][j]=(float)rand() / RAND_MAX;
            B[i][j]=(float)rand() / RAND_MAX;
        }
    }

    #pragma endregion 

    printf("Printing MatriX A:\n");
    for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%f\t", A[i][j]);
            }
            printf("\n");
        }
    printf("Printing MatriX B:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
                printf("%f\t", B[i][j]);
            }
            printf("\n");
        }

    if (blkNumber==1)
    {
        /* code */
   
   
        if(strcmp(order, "ijk")==0)
        {
            multiplyMatrices_ijk(A, B, resultMatrix, n);
        }
        if(strcmp(order, "jik")==0)
        {
            multiplyMatrices_jik(A, B, resultMatrix, n);
        }
            printf("Product of matrices:\n");
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    printf("%f\t", resultMatrix[i][j]);
                }
                printf("\n");
            }
    }
    return (0);
}