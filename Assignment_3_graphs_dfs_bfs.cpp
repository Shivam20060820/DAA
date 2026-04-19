#include <iostream>

using namespace std;

class node
{
public:
    int vertex;
    node* next;

    node(int v)
    {
        vertex = v;
        next = NULL;
    }
};

class graph
{
    node* head[20];
    int n;

public:
    graph()
    {
        for (int i = 0; i < 20; i++)
        {
            head[i] = NULL;
        }
        n = 0;
    }

    void create();
    void display();
    void BFS(int start);
    void DFS_NonRecursive(int start);
};

void graph::create()
{
    cout << "Enter total number of users: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        head[i] = new node(i);
        node* temp = head[i];

        char choice;
        cout << "\nAdding friends for User " << i << endl;
        cout << " Add friend? (y/n): ";
        cin >> choice;

        while (choice == 'y' || choice == 'Y')
        {
            int v;
            cout << " Enter Friend ID: ";
            cin >> v;

            if (v == i || v < 0 || v >= n)
            {
                cout << " Invalid friend ID!" << endl;
            }
            else
            {
                temp->next = new node(v);
                temp = temp->next;
            }

            cout << " Add another friend? (y/n): ";
            cin >> choice;
        }
    }
}

void graph::display()
{
    cout << "\n--- Friend Network Adjacency List ---" << endl;

    for (int i = 0; i < n; i++)
    {
        node* temp = head[i];

        while (temp != NULL)
        {
            cout << temp->vertex;
            if (temp->next != NULL)
            {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }
}

void graph::BFS(int v)
{
    if (v < 0 || v >= n)
    {
        cout << "Invalid starting ID!" << endl;
        return;
    }

    int visited[20];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    int q[20];
    int front = 0;
    int rear = 0;

    q[rear++] = v;
    visited[v] = 1;

    cout << "BFS Traversal: ";

    while (front < rear)
    {
        v = q[front++];
        cout << v << " ";

        node* temp = (head[v] != NULL) ? head[v]->next : NULL;

        while (temp != NULL)
        {
            int w = temp->vertex;

            if (!visited[w])
            {
                q[rear++] = w;
                visited[w] = 1;
            }
            temp = temp->next;
        }
    }
    cout << endl;
}


void graph::DFS_NonRecursive(int start)
{
    if (start < 0 || start >= n)
    {
        cout << "Invalid starting ID!" << endl;
        return;
    }

    bool visited[20] = { false };
    int st[20];
    int top = -1;

    visited[start] = true;
    st[++top] = start;

    cout << "DFS Traversal: ";

    while (top != -1)
    {
        int v = st[top--];
        cout << v << " ";

        node* temp = (head[v] != NULL) ? head[v]->next : NULL;

        while (temp != NULL)
        {
            int w = temp->vertex;
            if (!visited[w])
            {
                visited[w] = true;
                st[++top] = w;
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

int main()
{
    graph g;

    g.create();
    g.display();

    int startNode;
    cout << "\nEnter starting ID for traversals: ";
    cin >> startNode;

    g.BFS(startNode);
    g.DFS_NonRecursive(startNode);

    return 0;
}