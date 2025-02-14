/**
 * @file iterative_merge_sort.cpp
 * @brief This program reads a list of integers from standard input, sorts them using the Iterative Merge Sort algorithm, and prints the sorted list.
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
 * @param l1 left index of the first subarray
 * @param r1 right index of the first subarray
 * @param l2 left index of the second subarray
 * @param r2 right index of the second subarray
 * 
 * @return A vector containing the merged sorted array
 */
vector<int> merge(vector<int> arr, int l1, int r1, int l2, int r2)
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
/**
 * @brief merge sort algorithm, sort the array and return the sorted array
 *
 * @param arr vector containing the array to be sorted
 * @param n size of the array
 * 
 * @return A vector containing the sorted array
 */
vector<int> merge_sort(vector<int> arr, int n)
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

            auto temp = merge(arr, l1, r1, l2, r2);

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

int main(int argc, char *argv[])
{
    vector<int> arr = read_arr();
    int n = arr.size();

    auto sorted = merge_sort(arr, n);
    print_arr(sorted);
}