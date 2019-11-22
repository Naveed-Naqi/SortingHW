// Homework 4
// Testing Sorting Algorithms
/*
Name: Naveed Naqi
Date: 11/12/19
Description: This file tests different sorting algorithms.
*/

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "CodeFromBook/Sort.h"
using namespace std;



namespace {

//Utility function that prints vectors to the console in a nicely formatted way.
void PrintVector(const vector<int> &arr) {

  for(int elem : arr) {
    std::cout << elem << "\t";
  }
  std::cout << "\n";
}

// Generates and returns sorted vector of size @size_of_vector.
vector<int> GenerateSortedVector(size_t size_of_vector) {
  vector<int> a;

  for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(i);
  return a;
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> a;
  for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(rand());
  return a;
}

//Verifies the order of a given input vector, where the order is defined by the comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {

  if(input.size() < 2) { return true; }

  Comparable prev_element = input[0];
  
  for(size_t i = 1; i < input.size(); ++i) {

    if(!less_than(prev_element, input[i]) && prev_element != input[i]) {
      return false;
    }

    prev_element = input[i];
  }

  return true;
}

void TestTiming(void (*f)(vector<int>&, const string& flag), vector<int>& input_vector, const string& flag) {
    auto begin = chrono::high_resolution_clock::now();
    (*f)(input_vector, flag);
    auto end = chrono::high_resolution_clock::now();    
    cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
}

void QuickSortTester(vector<int> &input_vector, const string& flag) {
    flag == "less" ? Quicksort(input_vector, less<int>{}) : Quicksort(input_vector, greater<int>{});
}

void HeapSortTester(vector<int> &input_vector, const string& flag) {
    flag == "less" ? Heapsort(input_vector, less<int>{}) : Heapsort(input_vector, greater<int>{});
}

void MergeSortTester(vector<int> &input_vector, const string& flag) {
    flag == "less" ? Mergesort(input_vector, less<int>{}) : Mergesort(input_vector, greater<int>{});
}

// Signature for quicksort (heapsort / mergesort similar signatures)
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator less_than) {
  // quicksort implementation
  // to be filled
}

}  // namespace
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);

  if (input_type != "random" && input_type != "sorted") {
    cout << "Invalid input type" << endl;
    return 0;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return 0;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return 0;
  }

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;

  vector<int> input_vector;

  if (input_type == "random") {
    input_vector = GenerateRandomVector(input_size);
    
  } else {
    input_vector = GenerateSortedVector(input_size);
  }

  if (comparison_type == "less") {

    vector<int> temp_vector = input_vector;
    
    cout << "HeapSort: " << "Runtime: ";
    TestTiming(HeapSortTester, input_vector, "less");
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    input_vector = temp_vector;
    cout << "MergeSort: " << "Runtime: ";
    TestTiming(MergeSortTester, input_vector, "less");
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    input_vector = temp_vector;
    cout << "Quicksort: Runtime: ";
    TestTiming(QuickSortTester, input_vector, "less");
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

  } else {

    vector<int> temp_vector = input_vector;

    cout << "HeapSort: " << "Runtime: ";
    TestTiming(HeapSortTester, input_vector, "greater");
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    input_vector = temp_vector;
    cout << "MergeSort: " << "Runtime: ";
    TestTiming(HeapSortTester, input_vector, "greater");
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    input_vector = temp_vector;
    cout << "QuickSort: " << "Runtime: ";
    TestTiming(HeapSortTester, input_vector, "greater");
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

  }

  return 0;
}
