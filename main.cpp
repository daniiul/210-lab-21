#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat
{
private:
    int age;
    string name;
    string color;
    string names[15] = {"Kelsie", "Reagan", "Triston", "Raphael", "Noel", "Sullivan", "Imani",
        "Daniella", "Katrina", "Alexis", "Brenda", "Alberto", "Sasha", "Ally", "Journey"};
    string colors[15] = {"Snow", "Coral", "Bisque", "Moccasin", "Lavender", "Peru", "Azure", "Amethyst",
        "Tan", "Dark Salmon", "Alice Blue", "Honeydew"};

public:
    Goat()
    {
        age = (rand() % 20) + 1;
        name = names[rand() % 16];
        color = colors[rand() % 16];
    }
    Goat(int a, string n, string c)
    {
        age = a;
        name = n;
        color = c;
    }

    int getAge() { return age; }
    string getName() { return name; }
    string getColor() { return color; }
};

class DoublyLinkedList {
private:
    struct Node {
        Goat* goat;
        Node* prev;
        Node* next;
        Node(Goat *g, Node* p = nullptr, Node* n = nullptr) {
            goat = g;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat *g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat *g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat *g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(string name) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && !name.compare(temp->goat->getName()))
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->goat->getName() << " (" << current->goat->getColor() << ", " << current->goat->getAge() << ")" << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->goat->getName() << " (" << current->goat->getColor() << ", " << current->goat->getAge() << ")" << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
    {
        Goat temp();
        list.push_back(temp);
    }

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
