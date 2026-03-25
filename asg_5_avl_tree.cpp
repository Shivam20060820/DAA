#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class avl_node
{
public:
    string word;
    string meaning;
    avl_node *left, *right;
};

class avlTree
{
    avl_node* root;

public:
    avlTree()
    {
        root = NULL;
    }

    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);

    void insert();
    avl_node* insert(avl_node*, avl_node*);

    avl_node* search(avl_node*, string);
    void update();

    void display(avl_node*, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);

    void show()
    {
        display(root, 1);
    }

    void traverse()
    {
        cout << "\nInorder: ";
        inorder(root);
        cout << "\nPreorder: ";
        preorder(root);
        cout << "\nPostorder: ";
        postorder(root);
    }
};

// ---------------- ROTATIONS ----------------

avl_node* avlTree::ll_rotation(avl_node* parent)
{
    avl_node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node* avlTree::rr_rotation(avl_node* parent)
{
    avl_node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node* avlTree::lr_rotation(avl_node* parent)
{
    parent->left = rr_rotation(parent->left);
    return ll_rotation(parent);
}

avl_node* avlTree::rl_rotation(avl_node* parent)
{
    parent->right = ll_rotation(parent->right);
    return rr_rotation(parent);
}

// ---------------- HEIGHT & BALANCE ----------------

int avlTree::height(avl_node* temp)
{
    if (temp == NULL)
        return 0;

    return 1 + max(height(temp->left), height(temp->right));
}

int avlTree::diff(avl_node* temp)
{
    return height(temp->left) - height(temp->right);
}

avl_node* avlTree::balance(avl_node* temp)
{
    int bal_factor = diff(temp);

    if (bal_factor > 1)
    {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bal_factor < -1)
    {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }

    return temp;
}

// ---------------- INSERT ----------------

void avlTree::insert()
{
    char ch;
    do
    {
        avl_node* temp = new avl_node;

        cout << "Enter word: ";
        cin >> temp->word;

        cout << "Enter meaning: ";
        cin >> temp->meaning;

        temp->left = temp->right = NULL;

        root = insert(root, temp);

        cout << "Continue? (Y/N): ";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
}

avl_node* avlTree::insert(avl_node* root, avl_node* temp)
{
    if (root == NULL)
        return temp;

    if (temp->word < root->word)
        root->left = insert(root->left, temp);
    else
        root->right = insert(root->right, temp);

    return balance(root);
}

// ---------------- SEARCH ----------------

avl_node* avlTree::search(avl_node* root, string key)
{
    if (root == NULL)
        return NULL;

    if (key == root->word)
        return root;
    else if (key < root->word)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// ---------------- UPDATE ----------------

void avlTree::update()
{
    string key, newMeaning;

    cout << "Enter word to update/search: ";
    cin >> key;

    avl_node* result = search(root, key);

    if (result != NULL)
    {
        cout << "Word found!\n";
        cout << "Current meaning: " << result->meaning << endl;

        cout << "Enter new meaning: ";
        cin >> newMeaning;

        result->meaning = newMeaning;

        cout << "Meaning updated successfully.\n";
    }
    else
    {
        cout << "Word not found. Adding new word.\n";

        avl_node* temp = new avl_node;
        temp->word = key;

        cout << "Enter meaning: ";
        cin >> temp->meaning;

        temp->left = temp->right = NULL;

        root = insert(root, temp);
    }
}

// ---------------- DISPLAY ----------------

void avlTree::display(avl_node* ptr, int level)
{
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);

        cout << endl;
        if (ptr == root)
            cout << "Root -> ";

        for (int i = 0; i < level && ptr != root; i++)
            cout << "   ";

        cout << ptr->word;

        display(ptr->left, level + 1);
    }
}

// ---------------- TRAVERSALS ----------------

void avlTree::inorder(avl_node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->word << " ";
        inorder(root->right);
    }
}

void avlTree::preorder(avl_node* root)
{
    if (root != NULL)
    {
        cout << root->word << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void avlTree::postorder(avl_node* root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->word << " ";
    }
}

// ---------------- MAIN ----------------

int main()
{
    avlTree t;
    int choice;

    do
    {
        cout << "\n===== AVL Dictionary Menu =====\n";
        cout << "1. Insert\n2. Update/Search\n3. Display Tree\n4. Traversals\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                t.insert();
                break;

            case 2:
                t.update();
                break;

            case 3:
                t.show();
                break;

            case 4:
                t.traverse();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
