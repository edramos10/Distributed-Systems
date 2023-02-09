#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 512 /* Number of rows and columns in the matrix */

void fill_matrix(double *matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i * n + j] = i + j;
    }
  }
}

void print_matrix(double *matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%f ", matrix[i * n + j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  int rank, size;
  double *a, *b, *c;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* Allocate memory for the matrices */
  a = (double *)malloc(N * N * sizeof(double));
  b = (double *)malloc(N * N * sizeof(double));
  c = (double *)malloc(N * N * sizeof(double));

  /* Fill the matrices with some data */
  if (rank == 0) {
    fill_matrix(a, N);
    fill_matrix(b, N);
  }

  /* Broadcast matrix B to all processes */
  MPI_Bcast(b, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Scatter matrix A to all processes */
  MPI_Scatter(a, N * N / size, MPI_DOUBLE, a, N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Perform local matrix multiplication */
  for (int i = 0; i < N / size; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        c[i * N + j] += a[i * N + k] * b[k * N + j];
      }
    }
  }

  /* Gather results from all processes */
  MPI_Gather(c, N * N / size, MPI_DOUBLE, c, N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Print the result on process 0 */
  if (rank == 0) {
    printf("Result matrix:\n");
    print_matrix(c, N);
  }

  MPI_Finalize();
  return 0;
}
