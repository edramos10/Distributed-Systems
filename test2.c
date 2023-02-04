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
#include <conio.h> /*for getch()*/ 


#define MAX_SIZE 256

void multiplyMatrices(float A[][MAX_SIZE], float B[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < n; k++) {
                resultMatrix[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void main() {
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE];
    int n;
    int i, j,k;
    printf("Enter the size of matrices: ");
    scanf("%d", &n);
    printf("--Autofilling matrix wuth random numbers--\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //scanf("%d", &A[i][j]);
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

        multiplyMatrices(A, B, resultMatrix, n);
      /* for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < n; k++) {
                resultMatrix[i][j] += A[i][k] * B[k][j];
            }
        }
        }*/

        printf("Product of matrices:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%f\t", resultMatrix[i][j]);
            }
            printf("\n");
        }
        getch();    
    
    //return 0;
}
