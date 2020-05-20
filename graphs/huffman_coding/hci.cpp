#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int k, l;
    k = stoi(s1);
    l = stoi(s2);
    vector<pair<string, string>> counts;
    for (int i=0; i<k; i++) {
        cin >> s1 >> s2;
        s1 = s1.substr(0, 1);
        counts.push_back(pair<string, string>(s1, s2));
    }
    cin >> s1;
    int f;
    for (int i=counts.size()-1; i>=0;i--) {
        pair<string, string> p = counts[i];
        while (true) 
        {
            f = s1.find(p.second);
            if (f == -1) 
                break;
            s1.replace(s1.begin()+f, s1.begin()+f+p.second.size(), p.first);
        }
    }
    cout << s1;
    return 0;
}


