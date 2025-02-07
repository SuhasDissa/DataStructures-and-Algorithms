/**
 * @file selection_sort.cpp
 * @brief This program reads a list of integers from standard input, sorts them using the Selection Sort algorithm, and prints the sorted list.
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
 * @brief selection sort algorithm, sorts the array in place
 *
 * @param arr vector containing the array to be sorted
 */
void selection_sort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        int current = arr[i];
        int min = current;
        int min_idx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                min_idx = j;
            }
        }

        arr[min_idx] = current;
        arr[i] = min;
    }
}

int main(int argc, char *argv[])
{
    vector<int> arr = read_arr();
    selection_sort(arr);
    print_arr(arr);
}