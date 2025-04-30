#include <stdio.h>
#include <omp.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int sum = 0;  // Shared variable

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        {
            sum += arr[i];  // Only one thread at a time can do this
        }
    }

    printf("Sum = %d\n", sum);
    return 0;
}
