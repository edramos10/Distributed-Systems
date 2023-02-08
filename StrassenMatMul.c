/*+++++++++++++++++++++++++++++++++++

File Name: SequMatMul.c
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
void printMatrix(float Matrix[][MAX_SIZE], int n);
char *findArgument(int argc, char *argv[], char *cmd);
void strassenize(float mainMatrix[][MAX_SIZE], float subMatrix1[][MAX_SIZE], float subMatrix2[][MAX_SIZE],float subMatrix3[][MAX_SIZE],float subMatrix4[][MAX_SIZE],int n, int blkNumber);
void add_matrices(float matrixA[][MAX_SIZE], float matrixB[][MAX_SIZE], float resultMatrix[][MAX_SIZE],int n);


int main(int argc, char *argv[]){
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE], subresultMatrixA[MAX_SIZE][MAX_SIZE],subresultMatrixB[MAX_SIZE][MAX_SIZE];
    float subA11[MAX_SIZE][MAX_SIZE], subA12[MAX_SIZE][MAX_SIZE],subA21[MAX_SIZE][MAX_SIZE],subA22[MAX_SIZE][MAX_SIZE],subB11[MAX_SIZE][MAX_SIZE],subB12[MAX_SIZE][MAX_SIZE],subB21[MAX_SIZE][MAX_SIZE],subB22[MAX_SIZE][MAX_SIZE], subresultMatrix[MAX_SIZE][MAX_SIZE];
    float subC11[MAX_SIZE][MAX_SIZE], subC12[MAX_SIZE][MAX_SIZE],subC21[MAX_SIZE][MAX_SIZE],subC22[MAX_SIZE][MAX_SIZE];
    int n=8, blkNumber=2, blk_size=0;
    int i, j,k;
    char *rank_cmd = "--rank";
    char *order_cmd= "--order";
    
#pragma region "arguments management"

    if(strcmp(argv[1],("--help"))==0)
    {
        printf("--help: Arguments:\n --rank stands for ranknumber or size of squared matrix\n--order: type ijk, jik\n");
        exit(0);

    }
    if(strcmp(argv[1],("--info"))==0)
    {
   
        printf("--info: File Name: multest.c\nAuthor: Edgar Rene Ramos Acosta\nDate: 02-02-2023 \nLenguage: C\nPurpose: Next code below shows how matrices can be multiplied by using the sequential algorithm\n");
        printf("get repository by entering next commands in your terminal: ");
        printf("\033[0;32m"); //Set the text to the color green
        printf("git clone https://github.com/edramos10/Distributed-Systems.git \napp is seqmatmul, while source code is seqmatmul.c");
        printf("\033[0m"); //Resets the text to default color
        exit(0);

    }
   

        
    char *rankNumber = findArgument(argc, argv, rank_cmd);
    if (strlen(rankNumber) > 0) {
        printf("rankNumber: %s\n", rankNumber);
        n=atoi(rankNumber);
        blk_size=n/blkNumber;
    } else {
        printf("\033[0;31m"); //Set the text to the color red
        printf("rankNumber not found\n");
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


    printf("Printing MatriX A:\n");
    printMatrix(A,n);
    printf("Printing MatriX B:\n");
    printMatrix(B,n);

  #pragma endregion 

#pragma region "Strassen Algorithm for Matrix multiplication"  
   
    strassenize(A,subA11, subA12, subA21, subA22, n, blkNumber);
    strassenize(B,subB11, subB12, subB21, subB22, n, blkNumber);
    //c11= a11*b11 + a12*b21
    //c12=a11*b12 + a12*b22
    //c21=a21*b11+ a22*b21
    //c22= a21*b12 + a22*b22
    
getchar();


        
        if(strcmp(order, "ijk")==0)
        {
            /*
            multiplyMatrices_ijk(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_ijk(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_ijk(subA11, subB12, subresultMatrixA, n/blkNumber);
            multiplyMatrices_ijk(subA12, subB22, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_ijk(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_ijk(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_ijk(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_ijk(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);
            */
       

        }
        if(strcmp(order, "jik")==0)
        {
           /*
            multiplyMatrices_jik(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_jik(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_jik(subA11, subB12, subresultMatrixA, n/blkNumber);
            multiplyMatrices_jik(subA12, subB22, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_jik(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_jik(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);

            multiplyMatrices_jik(subA11, subB11, subresultMatrixA, n/blkNumber);
            multiplyMatrices_jik(subA12, subB21, subresultMatrixB, n/blkNumber);
            add_matrices(subresultMatrixA,subresultMatrixB,subresultMatrix,n/blkNumber);
            printMatrix(subresultMatrix,n/blkNumber);
            */
          
        }
#pragma endregion     
            
   
    return (0);
}

#pragma region "Functions"
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

void multiplyMatrices_ijk(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n) {
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

void multiplyMatrices_jik(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < n; k++) {
                resultMatrix[i][j] += Matrix1[j][k] * Matrix2[k][i];
            }
        }
    }
}
void printMatrix(float Matrix[][MAX_SIZE], int n){

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%f\t", Matrix[i][j]);
                }
                printf("\n");
            }
            printf("\n");
}

void strassenize(float mainMatrix[][MAX_SIZE], float subMatrix1[][MAX_SIZE], float subMatrix2[][MAX_SIZE],float subMatrix3[][MAX_SIZE],float subMatrix4[][MAX_SIZE],int n, int blkNumber){

    int blk_size=n/2;
      
            printf("Printing subMatriX p0:\n");
            for (int i = 0; i < blk_size; i++) {
                for (int j = 0; j < blk_size; j++) {
                    printf("%f\t", mainMatrix[i][j]);
                    subMatrix1[i][j]=mainMatrix[i][j];

                }
                 printf("\n");
            }
            printf("Printing subMatriX p1:\n");
            for (int i = 0; i < blk_size; i++) {
                for (int j = blk_size; j < blk_size*2; j++) {
                    printf("%f\t", mainMatrix[i][j]);
                    subMatrix2[i][j]=mainMatrix[i][j];

                }
                 printf("\n");
            }
            printf("Printing subMatriX p2:\n");
            for (int i = blk_size; i < blk_size*2; i++) {
                for (int j = 0; j < blk_size; j++) {
                    printf("%f\t", mainMatrix[i][j]);
                    subMatrix3[i][j]=mainMatrix[i][j];

                }
                 printf("\n");
            }
            printf("Printing subMatriX p3:\n");
            for (int i = blk_size; i < blk_size*2; i++) {
                for (int j = blk_size; j < blk_size*2; j++) {
                    printf("%f\t", mainMatrix[i][j]);
                    subMatrix4[i][j]=mainMatrix[i][j];

                }
                 printf("\n");
            }

}
void add_matrices(float matrixA[][MAX_SIZE], float matrixB[][MAX_SIZE], float resultMatrix[][MAX_SIZE],int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
    }
  }
}   


#pragma endregion