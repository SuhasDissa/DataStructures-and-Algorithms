#include <iostream>
#include <vector>
using namespace std;

void heap_sort(vector<int> &arr)
{
    build_max_heap(arr);
    int n = arr.size();

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}

void build_max_heap(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, i, n);
    }
}

void heapify(vector<int> &arr, int i, int n)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int max;

    max = (left < n && arr[left] > arr[i]) ? left : i;
    max = (right < n && arr[right] > arr[max]) ? right : max;

    if (max != i)
    {
        swap(arr[i], arr[max]);
        heapify(arr, max, n);
    }
}