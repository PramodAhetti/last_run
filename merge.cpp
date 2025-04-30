#include <iostream>
#include <omp.h>
using namespace std;

// Merge function
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    // Merge
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    // Copy remaining
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(int arr[], int left, int right, int depth = 0) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        //Use parallelism only for top levels
        if (depth <= 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);

                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        } else
       {
            // Fallback to serial
            parallelMergeSort(arr, left, mid, depth + 1);
            parallelMergeSort(arr, mid + 1, right, depth + 1);
        }

        merge(arr, left, mid, right);
    }
}

// Print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 45, 36, 11, 99, 100, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:\n";
    printArray(arr, n);

    // Set number of threads
    omp_set_num_threads(4);

    // Start parallel region
    double start = omp_get_wtime();
    parallelMergeSort(arr, 0, n - 1);
    double end = omp_get_wtime();

    cout << "Sorted array:\n";
    printArray(arr, n);

    cout << "Time taken: " << (end - start) << " seconds\n";
    return 0;
}
