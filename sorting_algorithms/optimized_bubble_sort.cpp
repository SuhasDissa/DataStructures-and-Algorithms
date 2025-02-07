/**
 * @file optimized_bubble_sort.cpp
 * @brief This program reads a list of integers from standard input, sorts them using the Optimized Bubble Sort algorithm, and prints the sorted list. This algorithm terminates early if the array is already sorted.
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
 * @brief optimized bubble sort algorithm, sorts the array in place
 *
 * @param arr vector containing the array to be sorted
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
                int temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
            }
        }
        if (!swapped)
        {
            break;
        }
        n--;
    }
}

int main(int argc, char *argv[])
{
    vector<int> arr = read_arr();
    optimized_bubble_sort(arr);
    print_arr(arr);
}