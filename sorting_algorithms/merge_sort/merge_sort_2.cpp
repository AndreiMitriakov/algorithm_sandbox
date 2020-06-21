#include <iostream>
#include <vector>
#include <chrono> 
using namespace std::chrono; 
using namespace std;

void merge(vector<int>& arr, int l, int m, int r, int& counter) 
{ 
	int L[m-l+1];
	int R[r-m];
	for (int i=0; i<m-l+1; i++)
	    L[i] = arr.at(l+i);
	for (int i=0; i<r-m; i++)
	    R[i] = arr.at(m+1+i);
    int ll = 0;
    int rr = 0;
    for (int i=0; i<-l+r+1; i++){
        if (ll == m-l+1) {
            arr.at(l+i) = R[rr];
            rr++;         
        }   
        else if (rr == r-m) {
            arr.at(l+i) = L[ll];
            ll++;         
            counter += m-l +1 - ll;
        }   
        else {
            if (L[ll]>R[rr]) {
                arr.at(l+i) = R[rr];
                rr++;
                counter += m-l + 1 - ll;
            }
            else {
                arr.at(l+i) = L[ll];
                ll++;   
            }
        }
    }
} 

  
void mergeSort(vector<int>& arr, int l, int r, int& counter) 
{ 
	if (l < r) {
    	int m = l+(r-l)/2;
		mergeSort(arr, l, m, counter);
		mergeSort(arr, m+1, r, counter);
		merge(arr, l, m, r, counter);
	}
} 

int main() {
	auto start = high_resolution_clock::now();
    // vector<int> v = {1,2,3,4,5,6,7,8,3,4,3}; // 11 digeits, ans.15
    vector<int> v;// = {2,3,9,2,9};
    int k, m;
    cin >> k;
    for (int i=0; i<k;i++) {
        cin >> m;
        v.push_back(m);
    }
    //cout << endl;
    int counter = 0;
    mergeSort(v, 0, v.size()-1, counter);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
	// cout << duration.count() << endl; 
	cout << counter << endl; 
    return 0;
}
