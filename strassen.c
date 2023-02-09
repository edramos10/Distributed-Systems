#include <stdio.h>
#include <math.h>
#define n 8

void add_matrix(int A[n][n], int B[n][n], int C[n][n]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract_matrix(int A[n][n], int B[n][n], int C[n][n]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen_matrix_mult(int A[n][n], int B[n][n], int C[n][n]) {
    int i, j, k;
    int P1[n][n], P2[n][n], P3[n][n], P4[n][n], P5[n][n], P6[n][n], P7[n][n];
    int A11[n/2][n/2], A12[n/2][n/2], A21[n/2][n/2], A22[n/2][n/2];
    int B11[n/2][n/2], B12[n/2][n/2], B21[n/2][n/2], B22[n/2][n/2];
    int C11[n/2][n/2], C12[n/2][n/2], C21[n/2][n/2], C22[n/2][n/2];

    int i1, j1;
    for (i = 0; i < n/2; i++) {
        for (j = 0; j < n/2; j++) {
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
  //On another hand
  /*
    P1=(A11+A22)*(B11+B22)
    P2=(A21+A22)*B11
    P3=A11(B12-B22)
    P4=A22(B21-B11)
    P5=(A11+A12)B22
    P6=(A21-A11)(B11+B12)
    P7=(A12-A22)(B21+B22)
    */
    add_matrix(A11, A22, A12);
    add_matrix(B11, B22, B12);
    strassen_matrix_mult(A12, B12, P1);

    add_matrix(A21, A22, A12);
    strassen_matrix_mult(A12,B11,P2);