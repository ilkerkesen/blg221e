/**********************************
Student Number : 040100411
Student Name   : İlker Kesen
Course         : BLG221E
CRN            : 20907
Term           : 2013 Spring
Homework       : #2
***********************************/

// headers and libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// constants
#define LEN 20
#define FILENAME "FRUITS.TXT"

// structs
struct Node {
  char word[LEN];
  int count;
  Node *next;
};

// namespaces
using namespace std;

// requested functions in homework
Node *build_linked_list(char array[][LEN], int N); 
Node *make_ordered_copy(Node * head);
void print_list(Node * head);

// main function
int main()
{
  // variable declarations
  FILE *fp; // file pointer
  int N; // elements size
  char hold[LEN]; // to find N

  Node *unordered; // unordered head
  Node *ordered; // ordered head
  Node *current; // counter for iteration

  // counters
  int i;
  int j;

  // open file to read
  fp = fopen(FILENAME, "r");

  // if file cannot be opened, exit
  if (fp == NULL) {
    cout << FILENAME << " cannot be opened." << endl;
    getchar();
    exit(0);
  }

  // find N
  for (N = 0; !feof(fp); N++)
    fscanf(fp, "%s", hold);

  // declare array[][LEN]
  char array[N][LEN];

  // return back to the beginning of the file
  rewind(fp);

  // fill array with elements
  for (i = 0; i < N; i++)
    fscanf(fp, "%s", array[i]);

  // close file
  fclose(fp);

  // get unordered list and print it
  unordered = build_linked_list(array, N);
  cout << "LINKED LIST 1 (UNORDERED):" << endl;
  print_list(unordered);

  // get ordered list and print it
  ordered = make_ordered_copy(unordered);
  cout << endl << "LINKED LIST 2 (ORDERED):" << endl;
  print_list(ordered);

  // free allocated memories
  while (unordered != NULL) {
    current = unordered->next;
    delete unordered;
    unordered = current;
  }

  while (ordered != NULL) {
    current = ordered->next;
    delete ordered;
    ordered = current;
  }

  // to see the output in windows with double click
  cout << endl << "Press enter to exit...";
  getchar();

  return 0;
}

// takes an array and its size, creates a linked list
Node *build_linked_list(char array[][LEN], int N)
{
  Node *head; // linked list head
  Node *temp; // temporary node

  int i; // counter
  bool exist; // existence

  // initially
  head = NULL;

  // scan every element of the array
  for (i = 0; i < N; i++) {
    exist = false;

    // scan current linked list for existence
    for (temp = head; temp != NULL; temp = temp->next) {
      // if array[i] exists in linked list
      if (!strcmp(temp->word, array[i])) {
    	exist = true;
    	temp->count += 1;
    	break;
      }
    }

    // if it does not exist, create it
    if (exist == false) {
      // allocate memory
      temp = new Node;

      // check memory allocation
      if (temp == NULL) {
	cout << "Memory cannot be allocated for unordered list.";
	getchar();
	exit(0);
      }

      // fill node fields
      strcpy(temp->word, array[i]);
      temp->count = 1;
      temp->next = head;
      head = temp;
    }
  }

  return head;
}

// takes a linked list, then sorts it
Node *make_ordered_copy(Node *head)
{
  Node *ordered; // the head of the ordered copy
  Node *temp_head; // temporary head for sorting
  Node *current; // counter node
  Node *temp; // node for allocation

  // variables for storing node instances
  char max_fruit[LEN];
  char max_count;

  // initially
  ordered = NULL;

  // copy linked list (reversed)
  for (current = head; current != NULL; current = current->next) {
    // allocate memory
    temp = new Node;

    // memory allocation check
    if (temp == NULL) {
      cout << "Memory cannot be allocated for ordered list." << endl;
      getchar();
      exit(0);
    }

    // fill node instances with values
    strcpy(temp->word, current->word);
    temp->count = current->count;
    temp->next = ordered;
    ordered = temp;
  }
  
  // make copied list ordered via selection sort
  for (temp_head = ordered; temp_head != NULL; temp_head = temp_head->next) {
    temp = temp_head;

    // find maximum
    for (current = temp_head; current != NULL; current = current->next) {
      if (current->count > temp->count) {
	temp = current;
      }
    }

    // swap max with temp_head
    if (temp != temp_head) {
      strcpy(max_fruit, temp->word);
      max_count = temp->count;

      strcpy(temp->word, temp_head->word);
      temp->count = temp_head->count;

      strcpy(temp_head->word, max_fruit);
      temp_head->count = max_count;
    }
  }
  
  return ordered;
  
}

// prints a linked list
void print_list(Node *head)
{
  Node *i; // counter

  for (i = head; i != NULL; i = i->next)
    cout << i->word << " = " << i->count << endl;
}
