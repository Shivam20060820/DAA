// a business house has several offices in different countries they want to list phone lines connect them with each other and the phone company charges different rate to connect
// different pairs of cities, business house wants to connect all its offices with a minimum total cost,solve the  problem using prim's algo

#include <iostream>
#include <stack>
using namespace std;

#define INF 9999999
#define MAX 100

void findMST(int n, int cost[MAX][MAX]) {
    stack<int> TV;
    bool visited[MAX] = {false};
    int totalCost = 0;
    int edgesCount = 0;

    // start from vertex 0
    TV.push(0);
    visited[0] = true;

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    cout << "Edge \t: Cost" << endl;

    while (edgesCount < n - 1) {
        int min = INF;
        int u = -1, v = -1;

        // traverse stack elements using a temporary stack
        stack<int> temp = TV;
        while (!temp.empty()) {
            int curr_u = temp.top();
            temp.pop();

            for (int curr_v = 0; curr_v < n; curr_v++) {
                if (!visited[curr_v] && cost[curr_u][curr_v] != 0) {
                    if (cost[curr_u][curr_v] < min) {
                        min = cost[curr_u][curr_v];
                        u = curr_u;
                        v = curr_v;
                    }
                }
            }
        }

        if (u == -1) {
            break;
        }

        cout << u << " - " << v << "\t: " << min << endl;
        totalCost += min;
        TV.push(v);
        visited[v] = true;
        edgesCount++;
    }

    if (edgesCount < n - 1) {
        cout << "\nNo spanning tree exists (Graph is disconnected)." << endl;
    } else {
        cout << "\nTotal Minimum Leasing Cost: " << totalCost << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of offices (min 5): ";
    cin >> n;

    if (n < 5) {
        cout << "Please enter at least 5 offices." << endl;
        return 0;
    }

    int cost[MAX][MAX];

    cout << "Enter the adjacency matrix (rental costs between cities):\n";
    cout << "(Enter 0 if there is no direct connection)\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    findMST(n, cost);

    return 0;
}