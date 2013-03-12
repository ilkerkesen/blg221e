/**********************************
Student Number : 040100411
Student Name   : İlker Kesen
Course         : BLG221E
CRN            : 20907
Term           : 2013 Spring
Homework       : #1
***********************************/

// headers and libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

// constants
#define FILENAME "DATA.TXT"

// namespaces
using namespace std;

// requested functions in homework
void solve_1(float *A[], int N, float *B, float *X);
float *solve_2(float *A[], int N, float *B);
void verify(float *A[], int N, float *X);

// main function
int main()
{
  // variable declarations
  FILE *fp; // file pointer
  int N; // row size for matrices
  float **A; // coefficients matrix
  float *B; // results matrix
  float *X; // roots matrix

  // counters
  int i;
  int j;

  // open file to read
  fp = fopen(FILENAME, "r");

  // if file cannot be opened, exit
  if (fp == NULL) {
    cout << FILENAME << " cannot be opened." << endl;
    exit(0);
  }

  // get row size of matrices
  fscanf(fp, "%d", &N);

  // allocate memory for A, B and X
  A = new float*[N];
  B = new float[N];
  X = new float[N];

  // read matrix from file
  for (i = 0; i < N; i++) {
    // allocate memory for A[i]
    A[i] = new float[N-i];

    // read elements of A[i]
    for (j = 0; j < N - i; j++) {
      fscanf(fp, "%f", &A[i][j]);
    }

    // read B[i]
    fscanf(fp, "%f", &B[i]);
  }

  // close file
  fclose(fp);

  // print matrix
  for (i = 0; i < N; i++) {
    // set width for upper triangular matrix
    cout << setw(16 * i) << "";

    // write every ith row element
    for (j = 0; j < N - i; j++) {
      cout << "A(" << i + 1 << "," << i + j + 1 << ") = ";
      cout << setiosflags(ios::left) << setw(7) << A[i][j];
    }
    
    // write ith B element
    cout << "B(" << i + 1 << ") = " << B[i] << endl;
  }

  cout << endl << endl;
  
  // solve with parameter method
  solve_1(A, N, B, X);

  cout << "X VALUE RESULTS (WITH PARAMETER METHOD):" << endl;

  for (i = 0; i < N; i++)
    cout << "X(" << i + 1 << ") = " << X[i] << endl;

  cout << endl;

  // free X and allocate it again
  // to be sure that solve_2 works correctly
  delete [] X;
  X = new float[N];

  // solve with return method
  X = solve_2(A, N, B);

  cout << "X VALUE RESULTS (WITH RETURN METHOD):" << endl;
  
  for (i = 0; i < N; i++)
    cout << "XALT(" << i + 1 << ") = " << X[i] << endl;

  cout << endl;

  // verification
  verify(A, N, X);

  // free allocated instances
  for (i = 0; i < N; i++)
    delete [] A[i];

  delete [] A;
  delete [] B;
  delete [] X;

  // to see the output in windows with double click
  cout << endl << "Press enter to exit...";
  getchar();

  return 0;
}

void solve_1(float *A[], int N, float *B, float *X)
{
  // counters
  int i;
  int j;

  // holder
  float hold;

  // scan every row
  for (i = N - 1; i > -1; i--) {
    hold = 0.0;

    // scan every column of ith row
    for (j = N - i - 1; j > 0; j--) {
      hold += X[i + j] * A[i][j];
    }

    // find ith root
    X[i] = (B[i] - hold) / A[i][0];
  }
}

float *solve_2(float *A[], int N, float *B)
{
  // counters
  int i;
  int j;

  // holder
  float hold;

  // roots matrix
  float *X;

  // allocate memory for roots matrix
  X = new float[N];

  // scan every row
  for (i = N - 1; i > -1; i--) {
    hold = 0.0;

    // scan every column of ith row
    for (j = N - (i + 1); j > 0; j--) {
      hold += X[i + j] * A[i][j];
    }

    // find ith root
    X[i] = (B[i] - hold) / A[i][0];
  }

  return X;
}

void verify(float *A[], int N, float *X)
{
  // counters
  int i;
  int j;

  // b for verification
  float b;
  
  cout << "VERIFICATION RESULTS:" << endl;

  // scan every row
  for (i = 0; i < N; i++) {
    b = 0.0;

    // scan every column
    for (j = 0; j < N - i; j++) {
      b += A[i][j] * X[i + j];
    }

    // write value of b
    cout << "BVERIFY(" << i + 1 << ") = " << b << endl;
  }
}
