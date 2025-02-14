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

vector<int> merge2(vector<int> arr, int l1, int r1, int l2, int r2)
{
    vector<int> temp(r2 - l1 + 1);
    int index = 0;

    while (l1 <= r1 && l2 <= r2)
    {
        if (arr[l1] <= arr[l2])
        {
            temp[index] = arr[l1];
            index++;
            l1++;
        }
        else
        {
            temp[index] = arr[l2];
            index++;
            l2++;
        }
    }

    while (l1 <= r1)
    {
        temp[index] = arr[l1];
        index++;
        l1++;
    }

    while (l2 <= r2)
    {
        temp[index] = arr[l2];
        index++;
        l2++;
    }
    return temp;
}

vector<int> merge_sort2(vector<int> arr, int n)
{
    int len = 1;

    while (len < n)
    {
        int i = 0;

        while (i < n)
        {
            int l1 = i;
            int r1 = i + len - 1;
            int l2 = i + len;
            int r2 = i + 2 * len - 1;

            if (l2 >= n)
            {
                break;
            }

            if (r2 >= n)
            {
                r2 = n - 1;
            }

            auto temp = merge2(arr, l1, r1, l2, r2);

            for (int j = 0; j <= r2 - l1; j++)
            {
                arr[i + j] = temp[j];
            }

            i = i + 2 * len;
        }
        len = 2 * len;
    }
    return arr;
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
    int n = arr.size();
    merge_sort2(arr, n);
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
