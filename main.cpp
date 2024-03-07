#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <omp.h>
#include <vector>
#include <chrono>
#define N 10000 // Define the size of the array
#define MOD 20 // Define the modulus for random number generation



int main() {

    auto start = std::chrono::high_resolution_clock::now();
    
    int arr[N]; // Define the array and the number to search for

    // Fill the array with random numbers
    for(int i = 0; i < N; i++) {
        arr[i] = rand(); 
    }
    
    // Print the first 50 elements of the unsorted array
    for (int i = 0; i < 50; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Sort the array using selection sort
    for (int i = 0; i < N-1; i++){
        int minIndex = i;
        int minimum = arr[i];

        // Start of the parallel region
        // Each thread will be assigned a chunk of the array to sort
        #pragma omp parallel for schedule(guided, 10)
        for (int j = i+1; j < N; j++){
            // Critical section to ensure that only one thread updates minIndex and minimum at a time
            #pragma omp critical
            {
                if (arr[j] < minimum){
                    minIndex = j;
                    minimum =  arr[j];
                }
            }
        }
        // End of the parallel region
        std::swap(arr[i], arr[minIndex]);
    }
    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    for (int i = 0; i < 50; i++) {
        std::cout << arr[i] << " ";
    }

}
