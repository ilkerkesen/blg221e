/**********************************
Student Number : 040100411
Student Name   : İlker Kesen
Course         : BLG221E
CRN            : 20907
Term           : 2013 Spring
Homework       : #3 (project #1)
***********************************/

// headers and libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// constants
#define N 26

// structs
struct Node
{
  char letter;
  float frequency;
  Node *left;
  Node *right;
};

struct HuffmanTree
{
  // instances
  Node *root;
  Node *array[N];

  char stack_bits[20];
  int stack_top;
  char bits_code[N][20];

  // main methods
  void build();
  void set_bits();
  void destroy();

  // helper and utilize functions
  void build_array();
  void sort(Node *array[], int len);
  void shift(Node *array[], int len);
  void build_tree();
  void set_bits_helper(Node *node, int stack_top);
  void print_bits();
  void free_tree(Node *node);
  int nth_char(char c);
};

// type definitions
typedef struct Node Node;
typedef struct HuffmanTree HuffmanTree;

// namespaces
using namespace std;

// global variables
char letters[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
		   'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		   'W', 'X', 'Y', 'Z'};

float frequencies[N]= {8.1, 1.5, 2.8, 4.3, 12.8 ,2.3, 2.0, 6.1, 7.1, 0.2,
		       0.1, 4.0, 2.4, 6.9, 7.6, 2.0, 0.1, 6.1, 6.4, 9.1,
		       2.8, 1.0, 2.4, 0.1, 2.0, 0.1};

// main function
int main(int argc, char *argv[])
{
  HuffmanTree tree;

  // build, set, print and destroy
  tree.build();
  tree.set_bits();
  tree.print_bits();
  tree.destroy();

  // to see the output in windows with double click
  cout << "Press enter to exit...";
  getchar();

  return 0;
}

// HuffmanTree constructor
void HuffmanTree::build()
{
  build_array();
  build_tree();
}

// sets Huffman bit codes
void HuffmanTree::set_bits()
{
  set_bits_helper(root, 0);
}

// HuffmanTree deconstructor
void HuffmanTree::destroy()
{
  free_tree(root);
}

// initializes array
void HuffmanTree::build_array()
{
  int i;

  for (i = 0; i < N; i++) {
    array[i] = new Node;
    array[i]->letter = letters[i];
    array[i]->frequency = frequencies[i];
    array[i]->left = NULL;
    array[i]->right = NULL;
  }
}

// sorting method for Node *array[]
void HuffmanTree::sort(Node *array[], int len)
{
  // variables
  int min;
  Node *hold;

  // counters
  int i;
  int j;

  // selection sort implementation for Node *array[]
  for (i = 0; i < len; i++) {
    min = i;

    for (j = i; j < len; j++) {
      if (array[j]->frequency < array[min]->frequency) {
	min = j;
      }
      else if (array[j]->frequency == array[min]->frequency) {
	// alphabetical order
	if (nth_char(array[j]->letter) < nth_char(array[min]->letter))
	  min = j;
      }
    }

    hold = array[min];
    array[min] = array[i];
    array[i] = hold;
  }
}

// shifting method for Node *array[] 
void HuffmanTree::shift(Node *array[], int len)
{
  // counter
  int i;

  for (i = 2; i < len; i++) {
    array[i-2] = array[i];
    array[i] = NULL;
  }
}

void HuffmanTree::build_tree()
{
  // variables
  Node *new_node;
  Node *tmp1;
  Node *tmp2;

  // counters
  int len;
  int i;
  int j;

  for (i = 0, len = N; i < N-1; i++, len--) {
    sort(array, len);

    // store first and second node
    tmp1 = array[0];
    tmp2 = array[1];

    // remove them from array
    array[0] = NULL;
    array[1] = NULL;

    // shift array elements
    shift(array, len);

    // create a new node
    new_node = new Node;

    new_node->frequency = tmp1->frequency + tmp2->frequency;
    new_node->letter = '*';
    new_node->left = tmp1;
    new_node->right = tmp2;

    // add new node to the end of the array
    array[len-2] = new_node;
  }

  // make "root" first element of the array
  root = array[0];
}

// method for setting Huffman bit codes
void HuffmanTree::set_bits_helper(Node *node, int stack_top)
{
  if (node != NULL) {
    if (node->letter == '*') {
      stack_bits[stack_top] = '0';
      set_bits_helper(node->left, stack_top + 1);

      stack_bits[stack_top] = '1';
      set_bits_helper(node->right, stack_top + 1);
    }
    else {
      int n = nth_char(node->letter);
      strncpy(bits_code[n], stack_bits, stack_top);
      bits_code[n][stack_top] = '\0';
      stack_top--;
    }
  }
}

// prints Huffman bit codes
void HuffmanTree::print_bits()
{
  int i;

  cout << "Huffman Coding Bits Letter Frequency" << endl;

  for (i = 0; i < N; i++) {
    cout << setiosflags(ios::left) << setw(20) << bits_code[i];
    cout << setiosflags(ios::left) << setw(7) << letters[i];
    cout << frequencies[i] << endl;
  }
}

// remove tree from memory
void HuffmanTree::free_tree(Node *node)
{
  if (node != NULL) {
    free_tree(node->left);
    free_tree(node->right);
    delete node;
  }
}

// utilize function to get order of a character
int HuffmanTree::nth_char(char c)
{
  int i;

  for (i = 0; i < N; i++) {
    if (letters[i] == c)
      return i;
  }

  // '*' character has higher order according
  // to the output in instructions of homework
  if (c == '*')
    return 500;
  
  return -1;
}
