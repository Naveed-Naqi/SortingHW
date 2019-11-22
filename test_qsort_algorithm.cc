// Homework 4
// Testing Sorting Algorithms (2nd program)
// YOUR NAME

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "CodeFromBook/Sort.h"
using namespace std;

namespace
{

//Utility function that prints vectors to the console in a nicely formatted way.
void PrintVector(const vector<int> &arr)
{

    for (int elem : arr)
    {
        std::cout << elem << "\t";
    }

    std::cout << "\n";
}

// Generates and returns sorted vector of size @size_of_vector.
vector<int> GenerateSortedVector(size_t size_of_vector)
{
    vector<int> a;

    for (size_t i = 0; i < size_of_vector; ++i)
        a.push_back(i);
    return a;
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector)
{
    vector<int> a;
    for (size_t i = 0; i < size_of_vector; ++i)
        a.push_back(rand());
    return a;
}

//Verifies the order of a given input vector, where the order is defined by the comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than)
{

    if (input.size() < 2)
    {
        return true;
    }

    Comparable prev_element = input[0];

    for (size_t i = 1; i < input.size(); ++i)
    {

        if (!less_than(prev_element, input[i]) && prev_element != input[i])
        {
            return false;
        }

        prev_element = input[i];
    }

    return true;
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable &median3(vector<Comparable> &a, int left, int right, Comparator less_than)
{
    int center = (left + right) / 2;

    if (less_than(a[center], a[left]))
        std::swap(a[left], a[center]);
    if (less_than(a[right], a[left]))
        std::swap(a[left], a[right]);
    if (less_than(a[right],  a[center]))
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksortHelper1(vector<Comparable> &a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        const Comparable &pivot = median3(a, left, right, less_than);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (less_than(a[++i], pivot))
            {
            }
            while (less_than(pivot, a[--j]))
            {
            }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]); // Restore pivot

        quicksortHelper1(a, left, i - 1, less_than);  // Sort small elements
        quicksortHelper1(a, i + 1, right, less_than); // Sort large elements
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right, less_than);
}

template <typename Comparable, typename Comparator>
int partition3 (vector<Comparable>& arr, int left, int right, Comparator less_than)  {  

  Comparable pivot = arr[left];
  int i = left+1;
  
  for (int j = left+1; j <= right; ++j) {

        if (less_than(arr[j],  pivot)) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
  }
  
  std::swap (arr[i-1], arr[left]);
  return i-1;   
}
  

template <typename Comparable, typename Comparator>
void quicksortHelper2(vector<Comparable> &arr, int left, int right, Comparator less_than) {

        if (left + 10 <= right) { 
            int middle = (left+right) / 2;
            int pivot = arr[middle];
            int i = left, j = right;

            while (i <= j)  {
                while (less_than(arr[i], pivot)) { i++; }
                while (less_than(pivot, arr[j])) { j--; }

                if (i <= j)  {
                    std::swap (arr[i], arr[j]);
                    i++;
                    j--;
                }
            }
            
            if (left < j){
                quicksortHelper2(arr, left, j, less_than);
            }
            if (right > i){
                quicksortHelper2(arr, i, right, less_than);
            }
        }
        else // Do an insertion sort on the subarray
            insertionSort(arr, left, right, less_than);
}

template <typename Comparable, typename Comparator>
void quicksortHelper3(vector<Comparable> &arr, int left, int right, Comparator less_than) {

    if(left + 10 <= right) {
        int pivot_index = partition3(arr, left, right, less_than);
        quicksortHelper3(arr, left, pivot_index-1, less_than);
        quicksortHelper3(arr, pivot_index+1, right, less_than);
    }
    else // Do an insertion sort on the subarray
        insertionSort(arr, left, right, less_than);
}

// Signature for quicksorts (3 implementations)
template <typename Comparable, typename Comparator>
void QuickSort1(vector<Comparable> &a, Comparator less_than)
{
    quicksortHelper1(a, 0, a.size() - 1, less_than);
}

template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than)
{
    quicksortHelper2(a, 0, a.size() - 1, less_than);
}

template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than)
{
    quicksortHelper3(a, 0, a.size() - 1, less_than);
}

} // namespace
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
        return 0;
    }
    const string input_type = string(argv[1]);
    const int input_size = stoi(string(argv[2]));
    const string comparison_type = string(argv[3]);
    if (input_type != "random" && input_type != "sorted")
    {
        cout << "Invalid input type" << endl;
        return 0;
    }
    if (input_size <= 0)
    {
        cout << "Invalid size" << endl;
        return 0;
    }
    if (comparison_type != "less" && comparison_type != "greater")
    {
        cout << "Invalid comparison type" << endl;
        return 0;
    }

    cout << "Testing quicksort: " << input_type << " " << input_size << " numbers " << comparison_type << endl;

    vector<int> input_vector;

    if (input_type == "random") {
        input_vector = GenerateRandomVector(input_size);
    } else {
        input_vector = GenerateSortedVector(input_size);
    }

    if (comparison_type == "less") {

        //Median of 3 Pivot Quicksort
        std::vector<int> temp_vector = input_vector;

        std::cout << "Median of three" << std::endl;
        std::cout << "Runtime: ";

        auto begin = chrono::high_resolution_clock::now();
        QuickSort1(input_vector, less<int>{});
        auto end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << std::endl;

        
        //Middle Pivot Quicksort
        input_vector = temp_vector;

        std::cout << "Middle" << std::endl;
        std::cout << "Runtime: ";

        begin = chrono::high_resolution_clock::now();
        QuickSort2(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << std::endl;
        

        
        //First Element Pivot Quicksort
        std::cout << "---- \n";
        input_vector = temp_vector;

        std::cout << "First" << std::endl;
        std::cout << "Runtime: ";

        begin = chrono::high_resolution_clock::now();
        QuickSort3(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << std::endl;

        std::cout << "---- \n";   
    } else {

       //Median of 3 Pivot Quicksort
        std::vector<int> temp_vector = input_vector;

        std::cout << "Median of three" << std::endl;
        std::cout << "Runtime: ";

        auto begin = chrono::high_resolution_clock::now();
        QuickSort1(input_vector, greater<int>{});
        auto end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << std::endl;

        
        //Middle Pivot Quicksort
        input_vector = temp_vector;

        std::cout << "Middle" << std::endl;
        std::cout << "Runtime: ";

        begin = chrono::high_resolution_clock::now();
        QuickSort2(input_vector, greater<int>{});
        end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << std::endl;
        

        
        //First Element Pivot Quicksort
        std::cout << "---- \n";
        input_vector = temp_vector;

        std::cout << "First" << std::endl;
        std::cout << "Runtime: ";

        begin = chrono::high_resolution_clock::now();
        QuickSort3(input_vector, greater<int>{});
        end = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
        std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << std::endl;

        std::cout << "---- \n";
    }

    return 0;
}
