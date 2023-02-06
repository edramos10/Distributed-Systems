/*+++++++++++++++++++++++++++++++++++

File Name: multest.c
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

void multiplyMatrices(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
char *findArgument(int argc, char *argv[], char *cmd);





int main(int argc, char *argv[]){
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE];
    int n, blkNumber=0;
    int i, j,k;
    char *rank_cmd = "--rank";
    char *block_cmd="--block-size";
    
#pragma region "arguments management"

    char *rankNumber = findArgument(argc, argv, rank_cmd);
    if (strlen(rankNumber) > 0) {
        printf("rankNumber: %s\n", rankNumber);
        n=atoi(rankNumber);
    } else {
        printf("rankNumber not found\n");
    }
    char *blockNumber = findArgument(argc, argv, block_cmd);
    if (strlen(blockNumber) > 0) {
        printf("blockNumber: %s\n", blockNumber);
        blkNumber=atoi(blockNumber);
    } else {
        printf("blockNumber not found\n");
    }
    if(strcmp(argv[1],("--help"))==0)
    {
            printf("--help: Arguments: --rank ranknumber --block-size blkNumber");

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
#pragma endregion 
   
        multiplyMatrices(A, B, resultMatrix, n);
   
        printf("Product of matrices:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%f\t", resultMatrix[i][j]);
            }
            printf("\n");
        }
      
    return 0;
   
}

char *findArgument(int argc, char *argv[], char *cmd) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], cmd) == 0) {
      if (i + 1 < argc) {
        return argv[i + 1];
      } else {
          
          
            return "";
            
        
      }
    }
  }
  return "";
}

void multiplyMatrices(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < n; k++) {
                resultMatrix[i][j] += Matrix1[i][k] * Matrix2[k][j];
            }
        }
    }
}