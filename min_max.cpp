#include <iostream>
#include <omp.h>
#include <climits>  // For INT_MAX and INT_MIN
using namespace std;

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0; // sum could be big, so long long

    // Parallel Region
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum) num_threads(8)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];   // Minimum
        if (arr[i] > max_val) max_val = arr[i];   // Maximum
        sum += arr[i];                            // Sum
    }

    double avg = (double)sum / n;   // Average = Sum / Count

    cout << "Minimum value: " << min_val << endl;
    cout << "Maximum value: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;

    return 0;
}
