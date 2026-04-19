#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX 10

class record {
public:
    int rno;
    string name;
    int marks;
};

class hashing {
public:
    int rno;
    int pos;

    hashing() {
        rno = -1;
        pos = -1;
    }
};

class student {
    record r;
    hashing h[MAX];

public:
    
    int insert_linear_prob(hashing hashtable[], int key, int position) {
        int loc = key % MAX;

        if (hashtable[loc].rno == -1) {
            hashtable[loc].rno = key;
            hashtable[loc].pos = position;
            return loc;
        } else {
            int i = (loc + 1) % MAX;
            while (i != loc) {
                if (hashtable[i].rno == -1) {
                    hashtable[i].rno = key;
                    hashtable[i].pos = position;
                    return i;
                }
                i = (i + 1) % MAX;
            }
            cout << "Hash table is full" << endl;
        }
        return -1;
    }

    void search_linear_probe(hashing hashtable[], int key) {
        int loc = key % MAX;

        if (hashtable[loc].rno == key) {
            cout << "Key found at index " << loc 
                 << " with file position " << hashtable[loc].pos << endl;
        } else {
            int i = (loc + 1) % MAX;
            bool found = false;

            while (i != loc) {
                if (hashtable[i].rno == key) {
                    cout << "Key found at index " << i 
                         << " with file position " << hashtable[i].pos << endl;
                    found = true;
                    break;
                }
                i = (i + 1) % MAX;
            }

            if (!found) {
                cout << "Key not found!" << endl;
            }
        }
    }

    // ✅ NEW FUNCTION (only added)
    void display_hashtable() {
        cout << "\nHash Table:\n";
        cout << "Index\tRollNo\tPosition\n";
        for (int i = 0; i < MAX; i++) {
            cout << i << "\t";
            if (h[i].rno != -1)
                cout << h[i].rno << "\t" << h[i].pos;
            else
                cout << "-\t-";
            cout << endl;
        }
    }

    void add_record() {
        ofstream fout("student.txt", ios::app);

        cout << "Enter Roll No: ";
        cin >> r.rno;
        cout << "Enter Name: ";
        cin >> r.name;
        cout << "Enter Marks: ";
        cin >> r.marks;

        int pos = fout.tellp(); 
        fout << r.rno << " " << r.name << " " << r.marks << endl;

        insert_linear_prob(h, r.rno, pos);

        fout.close();

        // ✅ JUST ADDED THIS CALL
        display_hashtable();
    }

    void search_record() {
        int key;
        cout << "Enter Roll No to search: ";
        cin >> key;

        int loc = key % MAX;
        int filepos = -1;

        if (h[loc].rno == key) {
            filepos = h[loc].pos;
        } else {
            int i = (loc + 1) % MAX;
            while (i != loc) {
                if (h[i].rno == key) {
                    filepos = h[i].pos;
                    break;
                }
                i = (i + 1) % MAX;
            }
        }

        if (filepos == -1) {
            cout << "Record not found!" << endl;
            return;
        }

        ifstream fin("student.txt");
        fin.seekg(filepos);

        fin >> r.rno >> r.name >> r.marks;

        cout << "\nRecord Found:\n";
        cout << "Roll No: " << r.rno << endl;
        cout << "Name: " << r.name << endl;
        cout << "Marks: " << r.marks << endl;

        fin.close();
    }
};

int main() {
    student s;
    int choice;

    do {
        cout << "\n1. Add Record\n2. Search Record\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.add_record();
                break;
            case 2:
                s.search_record();
                break;
        }
    } while (choice != 3);

    return 0;
}