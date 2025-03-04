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
 * @brief partition an array into two partitions. 
 *
 * @param arr vector containing the array to be partitioned
 * @param l leftmost index of the range to be partitioned
 * @param r rightmost index of the range to be partitioned
 */
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

/**
 * @brief quick sort algorithm, sorts the array in place
 *
 * @param l leftmost index of the range to be sorted
 * @param r rightmost index of the range to be sorted
 */
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


int main(int argc, char *argv[])
{
    vector<int> arr = read_arr();
    int n = arr.size();
    quick_sort(arr,0,n-1);
    print_arr(arr);
}