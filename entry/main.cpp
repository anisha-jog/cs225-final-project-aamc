// Read file and create adjacency list
#include <iostream>
#include <fstream>
using namespace std;
    
int main() {
    ifstream dataset("web-Google.txt");
    string dataread;
    if (dataset.is_open()) {
        dataset >> dataread;
        cout << dataread << endl;
    }
    return 0;
}