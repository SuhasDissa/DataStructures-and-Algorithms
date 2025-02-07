/**
 * @file insertion_sort.cpp
 * @brief This program reads a list of integers from standard input, sorts them using the Insertion Sort algorithm, and prints the sorted list.
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Prints the elements of an integer vector.
 * 
 * @param arr The vector containing integers to be printed.
 */
void print_arr(vector<int> arr){
    for(int i:arr){
        printf("%i ",i);
    }
}

/**
 * @brief Read space separated integers from stdin and turn it into a vector
 * 
 * @return A vector containing integers given by the user
 */
vector<int> read_arr(){
    vector<int> numbers;
    int num;
    while (cin >> num) {  
        numbers.push_back(num);
    }
    return numbers;
}

/**
 * @brief insertion sort algorithm, sorts the array in place
 * 
 * @param arr vector containing the array to be sorted
 */
void insertion_sort(vector<int>& arr){
    int size = arr.size();
    
    for(int i=1; i<size; i++){
        int current = arr[i];
        
        int p = i - 1;
        
        while(p >= 0 && arr[p] > current){
            arr[p+1] = arr[p];
            
            p = p - 1;
        }
        arr[p+1] = current;
    }
}

int main(int argc, char *argv[]){
    vector<int> arr = read_arr();
    insertion_sort(arr);
    print_arr(arr);
}