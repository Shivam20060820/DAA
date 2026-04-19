#include <iostream>
#include <cmath>
 
using namespace std;
 
int x[20];
int solutionCount = 0;
 
void printBoard(int n) {
    solutionCount++;
    cout << "\nSolution #" << solutionCount << ":" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == j) {
                cout << " Q ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;
}
 
bool place(int k, int i) {
    for (int j = 1; j <= k - 1; j++) {
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k))) {
            return false;
        }
    }
    return true;
}
 
void nqueen(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i;
            if (k == n) {
                printBoard(n);
            } else {
                nqueen(k + 1, n);
            }
        }
    }
}
 
int main() {
    int n;
    cout << "Enter the number of Queens: ";
    cin >> n;
 
    if (n <= 0 || n > 20) {
        cout << "Please enter a number (1-20)." << endl;
    } else {
        nqueen(1, n);
        if (solutionCount == 0) {
            cout << "No solutions found." << endl;
        } else {
            cout << "\nTotal solutions: " << solutionCount << endl;
        }
    }
 
    return 0;
}