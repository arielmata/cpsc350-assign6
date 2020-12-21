// assign6.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 6

// Assignment 6: A C++ program that implements 5 sorting algorithms and then
// times them on large input. This program will specifically implement
// Quick Sort, Merge Sort, Selection Sort, Insertion Sort and Bubble Sort.

#include "assign6.h"

//Default constructor
Simulation::Simulation(){}

//Destructor
Simulation::~Simulation(){
  delete []quickArr;
  delete []mergeArr;
  delete []selectionArr;
  delete []insertionArr;
  delete []bubbleArr;
}

//Reads file from command line argument, fills arrays, and then calls for the
//simulation to run
void Simulation::readFile(int argc, char **argv){
  string file;
  if(argc < 2){
    //No command line arguments were given
    cout << "\nNO FILE DETECTED." << endl;
    cout << "EXITING PROGRAM...\n" << endl;
    return;
  }else if(argc > 2){
    //More than one command line argument was given
    cout << "\nMORE THAN ONE FILE DETECTED." << endl;
    cout << "EXITING PROGRAM...\n" << endl;
    return;
  }

  //Command line argument is found
  file = argv[1];
  ifstream infile;
  infile.open(file);

  if(infile.fail()){
    //Can't open the file so close it and exit program
    cout << "\nFILE IS INACCESSIBLE." << endl;
    cout << "EXITING PROGRAM...\n" << endl;
    infile.close();
    return;
  }

  string line;
  int numElements, index = 0;
  getline(infile, line);
  try{
    numElements = stoi(line);
  }catch(invalid_argument ia){
    cerr << "\nFILE IS NOT IN CORRECT FORMAT." << endl;
    cerr << "EXITING PROGRAM...\n" << endl;
    infile.close();
    return;
  }

  quickArr = new double[numElements];
  mergeArr = new double[numElements];
  selectionArr = new double[numElements];
  insertionArr = new double[numElements];
  bubbleArr = new double[numElements];

  while(getline(infile,line) && index <= numElements){
    //add elements to all arrays
    double ele;
    try{
      ele = stod(line);
    }catch(invalid_argument ia){
      infile.close();
      cerr << "\nFILE IS NOT IN CORRECT FORMAT." << endl;
      cerr << "EXITING PROGRAM...\n" << endl;
      return;
    }
    quickArr[index] = ele;
    mergeArr[index] = ele;
    selectionArr[index] = ele;
    insertionArr[index] = ele;
    bubbleArr[index] = ele;
    ++index;
  }

  if(index != numElements){
    infile.close();
    cerr << "\nFILE IS NOT IN CORRECT FORMAT." << endl;
    cerr << "EXITING PROGRAM...\n" << endl;
    return;
  }

  //if we get here then file is in appropriate format and arrays are filled
  //so run the Simulation
  infile.close();
  runSimulation(numElements);
}

//Runs each of the 5 sorting algorithms and displays the start time, end time,
//and duration of each of the algorithms
void Simulation::runSimulation(int n){
  clock_t start, end;

  //Quick sort
  start = clock();
  quickSort(quickArr, 0, n - 1);
  end = clock();
  displayStats("\nQUICK", start, end);

  //Merge sort
  start = clock();
  mergeSort(mergeArr, 0, n - 1);
  end = clock();
  displayStats("MERGE", start, end);

  //Selection sort
  start = clock();
  selectionSort(selectionArr, n);
  end = clock();
  displayStats("SELECTION", start, end);

  //Insertion sort
  start = clock();
  insertionSort(insertionArr, n);
  end = clock();
  displayStats("INSERTION", start, end);

  //Bubble sort
  start = clock();
  bubbleSort(bubbleArr, n);
  end = clock();
  displayStats("BUBBLE", start, end);
}

//Outputs the algorithm name, start time, end time, and duration to
//standard output
void Simulation::displayStats(string alg, clock_t start, clock_t end){
  cout << alg << " SORT:" << endl;
  cout << "  START TIME: " << fixed << start/(long double)CLOCKS_PER_SEC << " s" << endl;
  cout << "  END TIME: "  << end/(long double)CLOCKS_PER_SEC << " s" << endl;
  cout << "  DURATION: "  << (end - start)/(long double)CLOCKS_PER_SEC << " s" << endl;
  cout << endl;
}

//Partitions the data within the array, given the lowIndex and highIndex
int Simulation::partition(double arr[], int lowIndex, int highIndex){
  //Pick middle index as the pivot point
  int midpoint = lowIndex + (highIndex - lowIndex)/2;
  double pivot = arr[midpoint];

  bool isDone = false;
  while(!isDone){
    //Increment lowIndex while arr[lowIndex] < pivot
    while(arr[lowIndex] < pivot){
      ++lowIndex;
    }

    while(pivot < arr[highIndex]){
      //Decrement highIndex while pivot < arr[highIndex]
      --highIndex;
    }

    //zero or one elements remain, so all the numbers are partitioned
    if(lowIndex >= highIndex){
      isDone = true;
    }else{
      //Swap arr[lowIndex] and arr[highIndex]
      swap(arr, lowIndex, highIndex);

      //Update lowIndex and highIndex
      ++lowIndex;
      --highIndex;
    }
  }
  return highIndex;
}

//Implements the quick sort algorithm given the array, the lowest index, and
//the highest index in the array
void Simulation::quickSort(double arr[], int lowIndex, int highIndex){
  //Base case: If partition has 1 or 0 elements, then it is sorted
  if(lowIndex >= highIndex)
    return;

  //Partition the array and the result from partition is the index of the
  //low partition's last element
  int lowEndIndex = partition(arr, lowIndex, highIndex);

  //Recursively call quickSort to sort low and high partition
  quickSort(arr, lowIndex, lowEndIndex);
  quickSort(arr, lowEndIndex + 1, highIndex);
}

//Merges the left and right partitions in sorted order
void Simulation::merge(double arr[], int i, int j, int k){
  int mergedSize = k - i + 1; //size of the merged array
  int mergePos = 0, leftPos = i, rightPos = j+1;
  double *mergedArr = new double[mergedSize]; //dynamically allocates temp array

  //Add smallest element from left or right partition to mergedArr
  while(leftPos <= j && rightPos <= k){
    if(arr[leftPos] <= arr[rightPos]){
      mergedArr[mergePos] = arr[leftPos];
      ++leftPos;
    }else{
      mergedArr[mergePos] = arr[rightPos];
      ++rightPos;
    }
    ++mergePos;
  }

  //Left partition is not empty, so add them to mergedArr
  while(leftPos <= j){
    mergedArr[mergePos] = arr[leftPos];
    ++leftPos;
    ++mergePos;
  }

  //Right partition is not empty, so add them to mergedArr
  while(rightPos <= k){
    mergedArr[mergePos] = arr[rightPos];
    ++rightPos;
    ++mergePos;
  }

  //Copy merge number back to numbers
  for(mergePos = 0; mergePos < mergedSize; ++mergePos){
      arr[i + mergePos] = mergedArr[mergePos];
  }
}

//Implements the merge sort algorithm given the array, the lowest index, and
//the highest index in the array
void Simulation::mergeSort(double arr[], int i, int k){
  int j;

  if(i < k){
    j = (i+k)/2; //Finds midpoint

    //Recursively sort left and right partitions
    mergeSort(arr, i, j);
    mergeSort(arr, j + 1, k);

    // Merge left and right partition in sorted order
    merge(arr, i, j, k);
  }
}

//Implements the selection sort algorithm given the array and the number of
//items in the array
void Simulation::selectionSort(double arr[], int n){
  int minIndex;
  for(int i = 0; i < n-1; ++i){
    //Find the index of smallest remaining element
    minIndex = i;
    for(int j = i+1; j < n; ++j){
      if(arr[j] < arr[minIndex])
        minIndex = j;
    }

    //Swap arr[i] and arr[minIndex] if they are not equal
    if(minIndex != i){
      swap(arr, i, minIndex);
    }
  }
}

//Implements the insertion sort algorithm given the array and the number of
//items in the array
void Simulation::insertionSort(double arr[], int n){
  int j;
  for(int i = 0; i < n; ++i){
    j = i;
    //Insert arr[i] into sorted part and stop when it is in correct position
    while(j > 0 && arr[j] < arr[j-1]){
      swap(arr, j, j-1); //Swap arr[j] and arr[j-1]
      --j;
    }
  }
}

//Implements the bubble sort algorithm given the array and the number of
//items in the array
void Simulation::bubbleSort(double arr[], int n){
  for(int i = 0; i < n-1; ++i){
    for(int j = 0; j < n-1-i; ++j){
      if(arr[j] > arr[j+1])
        swap(arr, j+1, j);
    }
  }
}

//Swaps the places of two indeces, a and b, of an array
void Simulation::swap(double arr[], int a, int b){
  double temp = arr[a]; // Temporary variable for swap
  arr[a] = arr[b];
  arr[b] = temp;
}
