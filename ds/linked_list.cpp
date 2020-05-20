#include <iostream>
#include <string>
using namespace std;
struct Node {
    Node(int v): value(v) {}
    Node* daughter=NULL;
    int value;
};

struct List {
    Node* head=NULL;
    Node* tail=NULL;
    void append(Node& n) {
        if (head == NULL) {
            head = &n;
            tail = &n;
        }
        else {
            tail->daughter = &n;
            tail = &n;
        }
    }
    void print_list() {
        Node* current=head;
        while(true) {
            cout << current->value << " " ;
            if (current->daughter == NULL)
                break;
            current = current->daughter;
        }
        cout << endl;
    }
        
};

int main()
{
  List l;
  Node* a1 =new Node(5);
  //Node a2 = Node(4);
  //Node a3 = Node(3);
  l.append(*a1);
  a1 =new Node(4);
  l.append(*a1);
  a1 =new Node(6);
  l.append(*a1);
  l.print_list();
}





