#include <iostream>
using namespace std;

void sort(int* arr, int size) 
{ 
    int cnt[9] = {0,0,0,0,0,0,0,0,0};
    for (int i=0; i<size;i++) {
        cnt[arr[i]] += 1;
    }
    int k = 0;
    for (int i=0; i<size;i++){
        while(true) 
        {
            if (cnt[k]==0)
                k++;
            else
                break;
        }
        arr[i] = k;
        cnt[k]--;
    }
} 

int main() {
    int k, m;
    cin >> k;
    int arr[k];
    for (int i=0; i<k;i++) {
        cin >> m;
        arr[i] = m;
    }
    sort(arr, k);
    for (int i=0; i<k;i++)
        cout << arr[i]<<" ";
    return 0;
}
