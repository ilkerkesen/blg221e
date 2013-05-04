/**********************************
Student Number : 040100411
Student Name   : İlker Kesen
Course         : BLG221E
CRN            : 20907
Term           : 2013 Spring
Homework       : #3
***********************************/

// headers and libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

// constants
#define N 6

// structs
struct Node
{
  char letter;
  float frequency;
  Node *left;
  Node *right;
};

// typedef
typedef struct Node Node;

// namespaces
using namespace std;

// function prototypes
void sort_by_frequency(Node *array[], int len);
void build_tree(Node *array[]);
void set_bits(Node *, char [], int*, char [][20], int*);
void free_tree(Node *root);
int nth_char(char c);

int main(int argc, char *argv[])
{
  char letters[N] = {'A', 'B', 'C', 'D', 'E', 'F'};
  float frequencies[N]= {8.1, 1.5, 2.8, 4.3, 12.8 ,2.3};

  Node *array[N];
  Node *root;

  int count;
  int stack_top;
  char bits_stack[20];
  char bits_code[N][20];

  int i;

  for (i = 0; i < N; i++) {
    array[i] = new Node;
    array[i]->letter = letters[i];
    array[i]->frequency = frequencies[i];
  }

  build_tree(array);
  root = array[0];

  count = 0;
  stack_top = 0;
  set_bits(root, bits_stack, &stack_top, bits_code, &count);

  cout << "Huffman Coding Bits Letter Frequency" << endl;

  for (i = 0; i < N; i++) {
    cout << setiosflags(ios::left) << setw(21) << bits_code[i];
    cout << setiosflags(ios::left) << setw(7) << letters[i];
    cout << frequencies[i] << endl;
  }

  free_tree(root);

  return 0;
}

void sort_by_frequency(Node *array[], int len)
{
  int max;
  Node *hold;

  int i;
  int j;

  for (i = 0; i < len; i++) {
    max = i;

    for (j = i; j < len; j++) {
      if (array[j]->frequency > array[max]->frequency) {
	max = j;
      }
    }

    hold = array[max];
    array[max] = array[i];
    array[i] = hold;
  }
}

void build_tree(Node *array[])
{
  Node *new_root;

  int len;
  int i;
  int j;

  len = N;

  for (i = 0; i < N-1; i++, len--) {
    sort_by_frequency(array, len);

    new_root = new Node;

    new_root->left = array[len-1];
    new_root->right = array[len-2];

    new_root->letter = '*';
    new_root->frequency = array[len-1]->frequency + array[len-2]->frequency;

    array[len-1] = NULL;
    array[len-2] = new_root;
  }
}

void set_bits(Node *root, char stack_bits[], int *stack_top, 
	      char bits_code[][20], int *count)
{
  if (root != NULL) {
    if (root->letter == '*') {
      stack_bits[stack_top] = '0';
      set_bits(root->left, stack_bits, stack_top + 1, bits_code, count);

      stack_bits[stack_top] = '1';
      set_bits(root->right, stack_bits, stack_top + 1, bits_code, count);
    }
    else {
      *count = nth_char(root->letter);
      strcpy(bits_code[*count], stack_bits);
      stack_top--;
    }
  }
}

void free_tree(Node *root)
{
  if (root != NULL) {
    free_tree(root->left);
    free_tree(root->right);
    delete root;
  }
}

int nth_char(char c)
{
  char letters[N] = {'A', 'B', 'C', 'D', 'E', 'F'};

  int i;

  for (i = 0; i < N; i++) {
    if (letters[i] == c)
      return i;
  }

  return -1;
}
