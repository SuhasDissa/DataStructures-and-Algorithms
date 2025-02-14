/**
 * @file sorting_algorithms.cpp
 * @brief Implements and benchmarks sorting algorithms.
 *
 * This program includes implementations of Insertion Sort, Bubble Sort,
 * Optimized Bubble Sort, and Selection Sort. It generates random arrays
 * of increasing sizes, measures execution times for each sorting algorithm,
 * and saves the results to a CSV file for analysis.
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

/**
 * @brief Performs Insertion Sort on a given array.
 *
 * Insertion Sort iterates through the array, inserting each element into its
 * correct position relative to previously sorted elements.
 *
 * @param arr The vector of integers to be sorted.
 */
void insertion_sort(vector<int> &arr)
{
    int size = arr.size();
    for (int i = 1; i < size; i++)
    {
        int current = arr[i];
        int p = i - 1;
        // Move elements greater than current one position ahead
        while (p >= 0 && arr[p] > current)
        {
            arr[p + 1] = arr[p];
            p = p - 1;
        }
        arr[p + 1] = current;
    }
}

/**
 * @brief Performs Bubble Sort on a given array.
 *
 * Bubble Sort repeatedly swaps adjacent elements if they are in the wrong order.
 * This implementation does not optimize for early termination.
 *
 * @param arr The vector of integers to be sorted.
 */
void bubble_sort(vector<int> &arr)
{
    int n = arr.size();
    while (n > 1)
    {
        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                swap(arr[i - 1], arr[i]);
            }
        }
        n--;
    }
}

/**
 * @brief Performs an optimized version of Bubble Sort.
 *
 * This optimized version terminates early if no swaps occur in a full pass,
 * improving efficiency for nearly sorted data.
 *
 * @param arr The vector of integers to be sorted.
 */
void optimized_bubble_sort(vector<int> &arr)
{
    int n = arr.size();
    bool swapped;
    while (n > 1)
    {
        swapped = false;
        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                swapped = true;
                swap(arr[i - 1], arr[i]);
            }
        }
        if (!swapped)
        {
            break; // Exit early if no swaps were made
        }
        n--;
    }
}

/**
 * @brief Performs Selection Sort on a given array.
 *
 * Selection Sort repeatedly finds the smallest element in the unsorted part
 * and swaps it with the first unsorted element.
 *
 * @param arr The vector of integers to be sorted.
 */
void selection_sort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

/**
 * @brief Generates a random array of a given size.
 *
 * The generated array contains random integers in the range [0, 999].
 *
 * @param size The number of elements in the array.
 * @return A vector containing the generated random integers.
 */
vector<int> rand_array(int size)
{
    vector<int> v(size);
    generate(v.begin(), v.end(), []()
             { return rand() % 1000; }); // Generates random numbers between 0 and 999
    return v;
}

/**
 * @brief Measures execution time of a sorting function and logs the result.
 *
 * @tparam SortFunction The sorting function to be measured.
 * @param original_arr The input array (remains unmodified).
 * @param sort_func The sorting function to execute.
 * @param outfile The output file stream to write the result.
 */
template <typename SortFunction>
void run_and_print(const vector<int> original_arr, SortFunction sort_func, ofstream &outfile)
{
    vector<int> arr = original_arr; // Copy input array to avoid modification
    auto start = high_resolution_clock::now();
    sort_func(arr);
    auto finish = high_resolution_clock::now();
    int duration = duration_cast<nanoseconds>(finish - start).count();
    outfile << duration << ", ";
}

int main(int argc, char *argv[])
{
    vector<vector<int>> inputs;
    int max_items = 10000;
    int gap = 100;

    // Generate random arrays of increasing size
    for (int i = 1; i <= max_items; i += gap)
    {
        auto arr = rand_array(i);
        inputs.push_back(arr);
    }

    // Open file for writing sorting times
    ofstream outfile("sorting_times.csv");
    if (!outfile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Write header row to CSV file
    outfile << "Array Size, Insertion Sort, Bubble Sort, Optimized Bubble Sort, Selection Sort" << endl;

    // Run sorting algorithms and log execution times
    for (const auto &input : inputs)
    {
        outfile << input.size() << " ,";
        run_and_print(input, insertion_sort, outfile);
        run_and_print(input, bubble_sort, outfile);
        run_and_print(input, optimized_bubble_sort, outfile);
        run_and_print(input, selection_sort, outfile);
        outfile << endl;
    }

    outfile.close(); // Close file
    return 0;
}
