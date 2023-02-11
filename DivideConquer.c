/*+++++++++++++++++++++++++++++++++++

File Name: SequMatMul.c
Author: Edgar Rene Ramos Acosta
Lenguage: C
Purpose: Next code below shows how matrices can be multiplied by using the Divide and Conquer algorithm
Version: 1.0, 02-09-2023

--------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
   

const int MAX_SIZE= 256;

void multiplyMatrices_ijk(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
void multiplyMatrices_jik(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
void printMatrix(float Matrix[][MAX_SIZE], int n);
char *findArgument(int argc, char *argv[], char *cmd);
void divideMatrix(float A[][MAX_SIZE], float B[][MAX_SIZE], float A11[][MAX_SIZE],float A12[][MAX_SIZE],float A21[][MAX_SIZE],float A22[][MAX_SIZE],float B11[][MAX_SIZE],float B12[][MAX_SIZE],float B21[][MAX_SIZE],float B22[][MAX_SIZE],int n);
void add_matrices(float matrixA[][MAX_SIZE], float matrixB[][MAX_SIZE], float resultMatrix[][MAX_SIZE],int n);


int main(int argc, char *argv[]){
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE], subresultMatrixA[MAX_SIZE][MAX_SIZE],subresultMatrixB[MAX_SIZE][MAX_SIZE];
    float subA11[MAX_SIZE][MAX_SIZE], subA12[MAX_SIZE][MAX_SIZE],subA21[MAX_SIZE][MAX_SIZE],subA22[MAX_SIZE][MAX_SIZE],subB11[MAX_SIZE][MAX_SIZE],subB12[MAX_SIZE][MAX_SIZE],subB21[MAX_SIZE][MAX_SIZE],subB22[MAX_SIZE][MAX_SIZE], subresultMatrix[MAX_SIZE][MAX_SIZE];
    float subC11[MAX_SIZE][MAX_SIZE], subC12[MAX_SIZE][MAX_SIZE],subC21[MAX_SIZE][MAX_SIZE],subC22[MAX_SIZE][MAX_SIZE];
    int n=8, blkNumber=2, blk_size=0;
    
    int i, j,k;
    char *rank_cmd = "--rank";
    char *order_cmd= "--order";
    clock_t start, end;
    int count=0;
    float elapsed=0;
    
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

#pragma region "Divide and Conquer Algorithm for Matrix multiplication\n"  
   
    divideMatrix(A,B,subA11, subA12, subA21, subA22,subB11, subB12, subB21, subB22,n);
    printf("Prining subMatrices A\n");
    printMatrix(subA11,n/2);
    printMatrix(subA12,n/2);
    printMatrix(subA21,n/2);
    printMatrix(subA22,n/2);
    printf("Prining subMatrices B\n");
    printMatrix(subB11,n/2);
    printMatrix(subB12,n/2);
    printMatrix(subB21,n/2);
    printMatrix(subB22,n/2);



   /*
    //c11= a11*b11 + a12*b21
    //c12=a11*b12 + a12*b22
    //c21=a21*b11+ a22*b21
    //c22= a21*b12 + a22*b22 

    //On another hand
    P=(A11+A22)*(B11+B22)
    Q=(A21+A22)*B11
    R=A11(B12-B22)
    S=A22(B21-B11)
    T=(A11+A12)B22
    U=(A21-A11)(B11+B12)
    V=(A12-A22)(B21+B22)

    C11=P+S-T+V
    C12=R+T
    C21=Q+S
    C22=P+R-Q+U

    */


    start = clock();  
        if(strcmp(order, "ijk")==0)
        {
            while(count<30)
            {
                multiplyMatrices_ijk(subA11,subB11,subresultMatrixA, n/2);
                multiplyMatrices_ijk(subA12,subB21,subresultMatrixB, n/2);
                add_matrices(subresultMatrixA, subresultMatrixB, subC11,n/2);

                multiplyMatrices_ijk(subA11,subB12,subresultMatrixA, n/2);
                multiplyMatrices_ijk(subA12,subB22,subresultMatrixB, n/2);
                add_matrices(subresultMatrixA, subresultMatrixB, subC12,n/2);

                multiplyMatrices_ijk(subA21,subB11,subresultMatrixA, n/2);
                multiplyMatrices_ijk(subA22,subB21,subresultMatrixB, n/2);
                add_matrices(subresultMatrixA, subresultMatrixB, subC21,n/2);

                multiplyMatrices_ijk(subA21,subB12,subresultMatrixA, n/2);
                multiplyMatrices_ijk(subA22,subB22,subresultMatrixB, n/2);
                add_matrices(subresultMatrixA, subresultMatrixB, subC22,n/2);
                end = clock();  
               
                
                if(count==29)
                {
                printf("Printing MatriX C:\n");
                printMatrix(subC11,n/2);
                printMatrix(subC12,n/2);
                printMatrix(subC21,n/2);
                printMatrix(subC22,n/2);
                }
            
                count++;
                
            }
            count=0;
             


     
            
       

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

   
    elapsed = ((float) (end - start)) / CLOCKS_PER_SEC;
    float avg_exec_time=elapsed/30;
    printf("Elapsed time: %fs\n", elapsed);
    printf("Avg Execution time for matrix multiplication (Divide and Conquer Algorithm): %f s", avg_exec_time);

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

void divideMatrix(float A[][MAX_SIZE], float B[][MAX_SIZE], float A11[][MAX_SIZE],float A12[][MAX_SIZE],float A21[][MAX_SIZE],float A22[][MAX_SIZE],float B11[][MAX_SIZE],float B12[][MAX_SIZE],float B21[][MAX_SIZE],float B22[][MAX_SIZE],int n){

   
      
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n/2];
            A21[i][j] = A[i + n/2][j];
            A22[i][j] = A[i + n/2][j + n/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n/2];
            B21[i][j] = B[i + n/2][j];
            B22[i][j] = B[i + n/2][j + n/2];
        }
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