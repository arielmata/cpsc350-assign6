// main.cpp - main file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 6

// Assignment 6: A C++ program that implements 5 sorting algorithms and then
// times them on large input. This program will specifically implement
// Quick Sort, Merge Sort, Selection Sort, Insertion Sort and Bubble Sort.

#include "assign6.h"

int main(int argc, char **argv){
  Simulation *s = new Simulation();
  s->readFile(argc, argv);
  delete s;
  return 0;
}
