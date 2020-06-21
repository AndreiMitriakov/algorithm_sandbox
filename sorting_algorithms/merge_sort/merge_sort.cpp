#include <iostream>
#include <vector>
#include <chrono> 
using namespace std::chrono; 
using namespace std;

void merge(vector<int>& arr, int l, int m, int r, int& inv) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(vector<int>& arr, int l, int r, int& inv) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m, inv); 
        mergeSort(arr, m+1, r, inv); 
  
        merge(arr, l, m, r, inv); 
    } 
} 

int main() {
    auto start = high_resolution_clock::now();
    vector<int> v = {2, 3, 9, 2, 9};
    int inv=0;
    mergeSort(v, 0, v.size()-1, inv);
    auto stop = high_resolution_clock::now();
    for (auto el: v)
        cout << el << " ";
    cout << endl;
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << duration.count() << endl; 
    return 0;
}
