/**
 * @file iterative_merge_sort.cpp
 * @brief This program reads a list of integers from standard input, sorts them using the Recursive Merge Sort algorithm, and prints the sorted list.
 */
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Prints the elements of an integer vector.
 *
 * @param arr The vector containing integers to be printed.
 */
void print_arr(vector<int> arr)
{
    for (int i : arr)
    {
        printf("%i ", i);
    }
}

/**
 * @brief Read space separated integers from stdin and turn it into a vector
 *
 * @return A vector containing integers given by the user
 */
vector<int> read_arr()
{
    vector<int> numbers;
    int num;
    while (cin >> num)
    {
        numbers.push_back(num);
    }
    return numbers;
}

/**
 * @brief merge function, merges two sorted subarrays into a single sorted array
 *
 * @param arr vector containing the array to be sorted
 * @param m index of the middle element
 * @param l index of the first element of the left half
 * @param r index of the first element of the right half
 *
 */
void merge(vector<int> &arr, int m, int l, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

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

/**
 * @brief merge sort algorithm, sort the array in place
 *
 * @param arr vector containing the array to be sorted
 * @param l index of the first element of the left half
 * @param r index of the first element of the right half
 */
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

int main(int argc, char *argv[])
{
    vector<int> arr = read_arr();
    int n = arr.size();

    merge_sort(arr, 0, n - 1);
    print_arr(arr);
}