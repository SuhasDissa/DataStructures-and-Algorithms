#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int arr_partition(vector<int> &arr, int l, int r)
{
    int chosen_pivot_idx = r;
    int pivot = arr[chosen_pivot_idx];

    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[chosen_pivot_idx]);
    return i + 1;
}

void quick_sort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int pivot_index = arr_partition(arr, l, r);

        // Sort left and right partitions separately
        quick_sort(arr, l, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, r);
    }
}

void quick_sort_iterative(vector<int> &arr, int l, int r)
{
    int stack[r - l + 1];
    stack[0] = l;
    stack[1] = r;

    int top = 1;

    while (top >= 0)
    {
        r = stack[top];
        top--;
        l = stack[top];
        top--;

        int p = arr_partition(arr, l, r);

        if (p - 1 > l)
        {
            top++;
            stack[top] = l;
            top++;
            stack[top] = p - 1;
        }

        if (p + 1 < r)
        {
            top++;
            stack[top] = p + 1;
            top++;
            stack[top] = r;
        }
    }
}

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
    vector<int> arr = original_arr;
    int n = arr.size();
    auto start = high_resolution_clock::now();
    sort_func(arr, 0, n - 1);
    auto finish = high_resolution_clock::now();
    int duration = duration_cast<nanoseconds>(finish - start).count();
    outfile << duration << ", ";
}

int main(int argc, char *argv[])
{
    vector<vector<int>> inputs;
    int max_items = 50000;
    int gap = 500;

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

    outfile << "Array Size, Recursive Quick Sort, Iterative Quick Sort" << endl;

    int size = inputs.size();
    for (int i = 0; i < size; i++)
    {
        outfile << inputs[i].size() << " ,";
        run_and_print(inputs[i], quick_sort, outfile);
        run_and_print(inputs[i], quick_sort_iterative, outfile);
        outfile << endl;
    }
    outfile.close();
}
