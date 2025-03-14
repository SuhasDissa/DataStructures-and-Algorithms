#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<int> rand_array(int size)
{
    vector<int> v(size);
    generate(v.begin(), v.end(), []()
             { return rand() % 1000; });
    return v;
}

template <typename SortFunction>
void run_and_print(const vector<int> original_arr, SortFunction sort_func, ofstream &outfile)
{
    vector<int> array = original_arr;
    int n = array.size();
    int *arr = array.data();
    auto start = high_resolution_clock::now();
    sort_func(arr,n);
    auto finish = high_resolution_clock::now();
    int duration = duration_cast<nanoseconds>(finish - start).count();
    outfile << duration << ", ";
}

// function to heapify the tree
void heapify(int arr[], int n, int root)
{
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max;

    if (left < n && arr[left] > arr[root])
    {
        max = left;
    }
    else
    {
        max = root;
    }

    if (right < n && arr[right] > arr[max])
    {
        max = right;
    }

    if (max != root)
    {
        swap(arr[root], arr[max]);
        heapify(arr, n, max);
    }
   
}
  
// implementing heap sort
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
   
}

int main(int argc, char *argv[])
{
    vector<vector<int>> inputs;
    int max_items = 100000;
    int gap = 100;

    for (int i = 1; i <= max_items; i += gap)
    {
        auto arr = rand_array(i);
        inputs.push_back(arr);
    }

    ofstream outfile("sorting_times.csv");

    if (!outfile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    outfile << "Array Size, Heap Sort" << endl;

    int size = inputs.size();
    for (int i = 0; i < size; i++)
    {
        outfile << inputs[i].size() << " ,";
        run_and_print(inputs[i], heapSort, outfile);
        outfile << endl;
    }
    outfile.close();
}