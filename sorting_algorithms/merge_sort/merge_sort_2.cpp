#include <iostream>
#include <vector>
#include <chrono> 
using namespace std::chrono; 
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) 
{ 
	vector<int> L;
	int lp = l;
	int rp = m+1;
	while (true) {
		if ((lp!=m+1)&&(rp!=r+1)){
			if (arr.at(lp)<arr.at(rp)) {
				L.push_back(arr.at(lp));
				lp++;
			}
			else {
				L.push_back(arr.at(rp));
				rp++;
			}
		}
		if ((lp==m+1)&&(rp<r+1)){
			L.push_back(arr.at(rp));
			rp++;
		}
		if ((lp<m+1)&&(rp==r+1)){
			L.push_back(arr.at(lp));
			lp++;
		}
		if ((lp==m+1)&&(rp==r+1))
			break;
	}
    if ((l != 0)||(r != arr.size()-1))
		for (int i=l; i<r+1; i++)
			arr.at(i) = L.at(i-l);
} 
  
void mergeSort(vector<int>& arr, int l, int r) 
{ 
	if (l < r) {
    	int m = l+(r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
} 

int main() {
	auto start = high_resolution_clock::now();
    vector<int> v = {1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,
1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,
1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,
1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,
1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7,1,2,54,8,3,4,-1,5,0,7};
    mergeSort(v, 0, v.size()-1);
	auto stop = high_resolution_clock::now();
    for (auto el: v)
        cout << el << " ";
    cout << endl;
	auto duration = duration_cast<microseconds>(stop - start); 
	cout << duration.count() << endl; 
    return 0;
}
