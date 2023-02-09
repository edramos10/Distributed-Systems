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
#include <conio.h>


const long int MAX_SIZE= 256;

void multiplyMatrices_ijk(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
void multiplyMatrices_jik(float Matrix1[][MAX_SIZE], float Matrix2[][MAX_SIZE], float resultMatrix[][MAX_SIZE], int n);
void printMatrix(float Matrix[][MAX_SIZE], int n);
char *findArgument(int argc, char *argv[], char *cmd);


int main(int argc, char *argv[]){
    float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], resultMatrix[MAX_SIZE][MAX_SIZE];
    float subA[MAX_SIZE][MAX_SIZE], subB[MAX_SIZE][MAX_SIZE], subresultMatrix[MAX_SIZE][MAX_SIZE];
    int n=8, blkNumber=0, blk_size=0;
    int i, j,k;
    char *rank_cmd = "--rank";
    char *order_cmd= "--order";
    clock_t start, end;
    int count=0;
    double elapsed=0;
    printf("Hi! Welcome...\n");


    if(strcmp(argv[1],("--help"))==0)
    {
        printf("--help: Arguments:\n --rank stands for ranknumber or size of squared matrix\n--order: type ijk, jik, kij, kji, ikj, jki\n");
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




 start = clock();  
        if(strcmp(order, "ijk")==0)
        {
           
            while(count<30)
            {
               
                multiplyMatrices_ijk(A, B, resultMatrix, n);
                if(count==29)
                {
                printf("Printing MatriX C:\n");
                printMatrix(resultMatrix,n);
                }
            
                count++;
                
            }
            count=0;
          

        }
        if(strcmp(order, "jik")==0)
        {
            while(count<30)
            {
               
                multiplyMatrices_jik(A, B, resultMatrix, n);
                
               
                    

              
                count++;
                
            }
            
          
        }
        end =clock();
        printf("Printing MatriX C:\n");
        printMatrix(resultMatrix,n);
    
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    double avg_exec_time=elapsed/30;
    printf("Elapsed time: %fs\n", elapsed);
    printf("Avg Execution time for matrix multiplication (Sequential Algorithm): %f s", avg_exec_time);


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
}


#pragma endregion