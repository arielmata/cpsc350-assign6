// assign6.h - header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 6

// Assignment 6: A C++ program that implements 5 sorting algorithms and then
// times them on large input. This program will specifically implement
// Quick Sort, Merge Sort, Selection Sort, Insertion Sort and Bubble Sort.

#include <iostream> //input and output
#include <fstream> //read and open files
#include <stdexcept> //invalid_argument exception
#include <ctime> //clock
using namespace std;

class Simulation{
  public:
    Simulation();
    ~Simulation();

    void readFile(int argc, char **argv);
    void runSimulation(int n);
    void displayStats(string alg, clock_t start, clock_t end);

    int partition(double arr[], int lowIndex, int highIndex);
    void quickSort(double arr[], int lowIndex, int highIndex);
    void merge(double arr[], int i, int j, int k);
    void mergeSort(double arr[], int i, int k);
    void selectionSort(double arr[], int n);
    void insertionSort(double arr[], int n);
    void bubbleSort(double arr[], int n);
    void swap(double arr[], int a, int b);
  private:
    double *quickArr;
    double *mergeArr;
    double *selectionArr;
    double *insertionArr;
    double *bubbleArr;
};
