#include <iostream>
#include <string>
#include <vector>

using namespace std;

double calc(string expression) {
    vector<char> exp;
    for (char e: expression)
    {
        if ((e == 50) || (e == 51) || (e == 50) ||(e == 52) || (e == 53) || (e == 57))
            res.push_back(e);
        if (e == 55) {
            res.push_back(e);
        }
            
        cout << (int)e << " " ;
    }
    return 0;
}

int main() {

    cout << calc("-7 * -(6 / 3)")<< endl;
    return 0;
}
