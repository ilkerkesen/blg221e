/**********************************
Student Number : 040100411
Student Name   : İlker Kesen
Course         : BLG221E
CRN            : 20907
Term           : 2013 Spring
Project        : #2
***********************************/

// headers and libraries
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>

// constants
#define FILENAME "input.txt"

// namespaces
using namespace std;

// global variables
string colors[20] = {("Red"), ("Black"), ("White"), ("Green"), ("Blue"),
		     ("Yellow"), ("Orange"), ("Gray"), ("Brown"), ("Purple"),
		     ("Pink"), ("Cyan"), ("Violet"), ("Mint"), ("Melon"),
		     ("Lava"), ("Cinnamon"), ("Denim"), ("Coffee"), ("Bronze")};

// Graph Struct
struct Graph {
  // instances
  int students; // number of students
  int courses; // number of courses
  int chromatic; // chromatic number

  // data structures
  vector < vector<int> > stdcrs; // courses of students
  vector < vector<int> > matrix; // graph matrix
  multimap <int, int, greater<int> > degrees; // degrees of nodes
  multimap <int, string> course_colors; // colors of courses
  map <string, vector<int> > colors_course; // courses of colors

  // public methods
  void build();
  void print_input();
  void print_graph_matrix();
  void print_course_degrees();
  void print_course_colors();
  void print_colors_course();
  void print_chromatic_number();

  // private methods
  void read_file();
  void set_matrix();
  void set_degrees();
  void set_colors();
};

// main function
int main()
{
  Graph g;
  g.build();
  g.print_input();
  g.print_graph_matrix();
  g.print_course_degrees();
  g.print_course_colors();
  g.print_colors_course();
  g.print_chromatic_number();

  // to see the output in windows with double click
  cout << endl << "Press enter to exit...";
  getchar();

  return 0;
}

void Graph::build()
{
  chromatic = 0;

  read_file();
  set_matrix();
  set_degrees();
  set_colors();
}

void Graph::print_input()
{
  // counters
  int i;
  int j;

  cout << "Number of students: " << students << endl;
  cout << "Number of courses: " << courses << endl;

  // print courses of students
  for (i = 0; i < stdcrs.size(); i++) {
    cout << endl << "Student " << i << " => Courses: ";

    for (j = 0; j < stdcrs[i].size(); j++)
      cout << stdcrs[i][j] << " ";
  }

  cout << endl << endl;
}

void Graph::print_graph_matrix()
{
  // counters
  int i;
  int j;

  cout << "Graph Matrix:" << endl;

  // print matrix 
  for (i = 0; i < matrix.size(); i++) {
    for (j = 0; j < matrix[i].size(); j++)
      cout << matrix[i][j] << " ";
    
    cout << endl;
  }

  cout << endl;
}

void Graph::print_course_degrees()
{
  // counter
  multimap <int, int>::iterator i;

  cout << "Course Degrees:" << endl;

  for (i = degrees.begin(); i != degrees.end(); i++)
    cout << "Course: " << i->second << " Degree: " << i->first << endl;

  cout << endl;
}


void Graph::print_course_colors()
{
  // iterator
  map <int, string>::iterator i;

  cout << "Course Colors (course->color):" << endl;

  for (i = course_colors.begin(); i != course_colors.end(); i++)
    cout << "Course: " << i->first << " Color: " << i->second << endl;

  cout << endl;
}

void Graph::print_colors_course()
{
  // counters
  int i;
  int j;

  cout << "Color Courses (color->courses):" << endl;

  for (i = 0; i < chromatic; i++) {
    cout << "Color: " << colors[i] << " => Courses: ";
    
    for (j = 0; j < (colors_course[colors[i]]).size(); j++) {
      cout << colors_course[colors[i]][j] << " ";
    }

    cout << endl;
  }

  cout << endl;
}

void Graph::print_chromatic_number()
{
  cout << "Chromatic Number: " << chromatic << endl;
}

void Graph::read_file()
{
  // variables
  FILE *fp; // file pointer
  char line[300]; // a line of the file
  char *buffer; // buffer (split)

  // counters
  int i;
  int j;

  // open file
  fp = fopen(FILENAME, "r");

  // if file cannot be opened, exit
  if (fp == NULL) {
    cout << "File cannot be opened.";
    getchar();
    exit(0);
  }

  // get first line
  fgets(line, 200, fp);
  sscanf(line, "%d %d", &students, &courses);

  // read file content, line by line
  for (i = 0; fgets(line, 200, fp); i++) {
    // push new row to the stdcrs
    stdcrs.push_back(vector<int>());

    // split integers
    for (buffer = strtok(line, " "); buffer != NULL; buffer = strtok(NULL, " "))
      stdcrs[i].push_back(atoi(buffer));
  }

  // check number of students
  if (i != students) {
    cout << "Input file is not correct. Check the number of the students.";
    getchar();
    exit(0);
  }

  // close the file
  fclose(fp);
}

void Graph::set_matrix()
{
  // counters
  int i;
  int j;
  int k;

  // course index
  int c1;
  int c2;

  // initialize matrix with zeros
  for (i = 0; i < courses; i++) {
    matrix.push_back(vector<int>());
    for (j = 0; j < courses; j++) {
      matrix[i].push_back(0);
    }
  }

  // scan students
  for (i = 0; i < stdcrs.size(); i++) {
    // scan courses of the student
    for (j = 0; j < stdcrs[i].size() - 1; j++) {
      // keep course1
      c1 = stdcrs[i][j];

      // scan rest of the courses of the student
      for (k = j + 1; k < stdcrs[i].size(); k++) {
	// keep course2
	c2 = stdcrs[i][k];

	// make them connected
	matrix[c1][c2] = 1;
	matrix[c2][c1] = 1;
      }
    }
  }
}

void Graph::set_degrees()
{
  int degree; // degree

  // counters
  int i;
  int j;

  // iterate rows
  for (i = 0; i < matrix.size(); i++) {
    // set degree to zero
    degree = 0;

    // iterate elements in the row
    for (j = 0; j < matrix[i].size(); j++) {
      // if two node is connected to each other, increment degree
      if (matrix[i][j] == 1)
	degree++;
    }

    degrees.insert(make_pair(degree, i));
  }
}

void Graph::set_colors()
{
  vector<int> nodes;
  bool is_neighbour;

  // counters
  int i;
  int j;
  int k;

  // iterators
  multimap<int, int>::iterator c;

  // helper instances in iteration
  int course;

  chromatic = 0;

  for (c = degrees.begin(); c != degrees.end(); c++) {
    // clear vector
    nodes.clear();
    
    // hold course number
    course = c->second;

    // if course is not colored
    if (course_colors.count(course) == 0) {
      // add course number to nodes
      nodes.push_back(course);

      // scan connections
      for (i = 0; i < matrix[course].size(); i++) {
	// if not neighbour, not itself and not colored
	if (matrix[course][i] == 0 && i != course && course_colors.count(i) == 0) {
	  is_neighbour = false;

	  // scan nodes
	  for (j = 0; j < nodes.size(); j++) {
	    // if they are neighbours
	    if (matrix[i][nodes[j]] == 1 && i != nodes[j]) {
	      is_neighbour = true;
	      break;
	    }
	  }

	  // if they are not neighbour, push it to nodes
	  if (!is_neighbour)
	    nodes.push_back(i);
	}
      }

      // color nodes (course_colors)
      for (i = 0; i < nodes.size(); i++)
	course_colors.insert(make_pair(nodes[i], colors[chromatic]));

      // color nodes (colors_course)
      colors_course.insert(make_pair(colors[chromatic], nodes));

      // chromatic number increment
      chromatic++;
    }
  } 
}
