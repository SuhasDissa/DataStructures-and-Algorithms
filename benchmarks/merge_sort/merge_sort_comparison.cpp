#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void merge(vector<int> &arr, int m, int l, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int x = 0; x < n1; x++)
    {
        L[x] = arr[l + x];
    }
    for (int x = 0; x < n2; x++)
    {
        R[x] = arr[m + 1 + x];
    }

    int x = 0;
    int y = 0;
    int k = l;

    while (x < n1 && y < n2)
    {
        if (L[x] <= R[y])
        {
            arr[k] = L[x];
            x++;
        }
        else
        {
            arr[k] = R[y];
            y++;
        }
        k++;
    }

    // copy the remaining elements
    while (x < n1)
    {
        arr[k] = L[x];
        x++;
        k++;
    }

    while (y < n2)
    {
        arr[k] = R[y];
        y++;
        k++;
    }
}

void merge_sort(vector<int> &arr, int i, int j)
{
    if (i < j)
    {
        int m = (i + j) / 2;
        merge_sort(arr, i, m);
        merge_sort(arr, m + 1, j);
        merge(arr, m, i, j);
    }
}

void merge2(vector<int> &arr, vector<int> &temp, int l1, int r1, int l2, int r2)
{
    int i = l1;
    int j = l2;
    int k = l1;

    while (i <= r1 && j <= r2)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= r1)
    {
        temp[k++] = arr[i++];
    }

    while (j <= r2)
    {
        temp[k++] = arr[j++];
    }

    for (int x = l1; x <= r2; x++)
    {
        arr[x] = temp[x];
    }
}

void merge_sort2(vector<int> &arr)
{
    int n = arr.size();
    vector<int> temp(n);
    int len = 1;

    while (len < n)
    {
        for (int i = 0; i < n; i += 2 * len)
        {
            int l1 = i;
            int r1 = min(i + len - 1, n - 1);
            int l2 = i + len;
            int r2 = min(i + 2 * len - 1, n - 1);

            if (l2 < n)
            {
                merge2(arr, temp, l1, r1, l2, r2);
            }
        }
        len *= 2;
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
    auto start = high_resolution_clock::now();
    sort_func(arr);
    auto finish = high_resolution_clock::now();
    int duration = duration_cast<nanoseconds>(finish - start).count();
    outfile << duration << ", ";
}

void recursive_merge_sort(vector<int> arr)
{
    int n = arr.size();
    merge_sort(arr, 0, n - 1);
}

void iterative_merge_sort(vector<int> arr)
{
    merge_sort2(arr);
}

int main(int argc, char *argv[])
{
    vector<vector<int>> inputs;
    int max_items = 10000;
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

    outfile << "Array Size, Recursive Merge Sort, Iterative Merge Sort" << endl;

    int size = inputs.size();
    for (int i = 0; i < size; i++)
    {
        outfile << inputs[i].size() << " ,";
        run_and_print(inputs[i], recursive_merge_sort, outfile);
        run_and_print(inputs[i], iterative_merge_sort, outfile);
        outfile << endl;
    }
    outfile.close();
}
