#include <omp.h>
#include <iostream>
using namespace std;

void seq_bubble_sort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void par_bubble_sort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        #pragma omp parallel for num_threads(4)
        for (int j = first; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];
    int* arr_copy = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr_copy[i] = arr[i];
    }

    double start, end;

    start = omp_get_wtime();
    seq_bubble_sort(arr, n);
    end = omp_get_wtime();
    cout << "Sorted (Sequential): ";
    display(arr, n);
    cout << "Sequential Time: " << (end - start) * 1000 << " ms\n";

    for (int i = 0; i < n; i++) arr[i] = arr_copy[i];

    start = omp_get_wtime();
    par_bubble_sort(arr, n);
    end = omp_get_wtime();
    cout << "Sorted (Parallel): ";
    display(arr, n);
    cout << "Parallel Time: " << (end - start) * 1000 << " ms\n";

    delete[] arr;
    delete[] arr_copy;
    return 0;
}
