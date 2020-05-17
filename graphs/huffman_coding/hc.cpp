#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <unordered_map>
using namespace std;

unordered_map<char, int> get_freq(string s) {
    unordered_map<char, int> map;
    int cnt = 0;
    for (char c: s) {
        cnt = map.count(c);
        if (cnt == 0)
            map[c] = 1;
        else
            map[c] += 1;
    }
    return map;
}
struct Node {
    Node (char c_, int f): c(c_), freq(f) {}
    char c;
    int freq;
    Node* parent = NULL;
    Node* left = NULL;
    Node* right = NULL;
    string code = "";
};

bool sortf(Node* a, Node* b) {
    /*if (a->freq == b->freq)
        return (int)a->c <  (int)b->c;
    else*/
        return a->freq<b->freq;
}

bool sortf2(Node* a, Node* b) {
    if (a->freq == b->freq)
        return (int)a->c < (int)b->c;
    else
        return false;
}


void create_tree(vector<Node*>& tree, unordered_map<char, int>& map) {
    vector<Node*> nodes;
    for (auto it: map) {
        Node* a = new Node(it.first, it.second);
        nodes.push_back(a);
    }
    sort(nodes.begin(), nodes.end(), sortf);
    sort(nodes.begin(), nodes.end(), sortf2);
    while (nodes.size() > 1) {
        Node* a = new Node('_', nodes[0]->freq+nodes[1]->freq);
        nodes[0]->parent = a;
        nodes[1]->parent = a;
        a->left = nodes[0];
        a->right = nodes[1];
        tree.push_back(nodes[0]);
        tree.push_back(nodes[1]);
        nodes.erase(nodes.begin(), nodes.begin()+2);
        nodes.push_back(a);
        sort(nodes.begin(), nodes.end(), sortf);
        //if (nodes.size() == 1)
            //break;
    }
    tree.push_back(nodes[0]);
    /*for (auto x: nodes) 
        cout << x->freq << " "; */
}

void print(vector<Node*>& tree) {
    for (int i=0; i<tree.size(); i++) {
        cout << "Node " << tree[i] << " code " << tree[i]->code << " "<< tree[i]->c << endl;
        cout << "Daughters " << tree[i]->left << " "<< tree[i]->right << endl;
        cout << "Parent " << tree[i]->parent << endl << endl;
    }
}

unordered_map<char, string> get_codes(vector<Node*>& tree) {
    unordered_map<char, string> res;
    if (tree.size() == 1) {
        res[tree[0]->c] = "0";
        return res;
    }
        
    for (int i=0; i<tree.size(); i++) {
        if (tree[i]->c != '_')
        {
            Node* d = tree[i];
            Node* p = tree[i]->parent;
            while (true) 
            {
                if (d == p->left)
                    tree[i]->code += "0";
                else 
                    tree[i]->code += "1";
                if (p->parent == NULL)
                    break;
                
                d = p;
                p = p->parent;
            }
            reverse(tree[i]->code.begin(), tree[i]->code.end());
            res[tree[i]->c] = tree[i]->code;
        }
    }
    return res;
}

int count_bits (unordered_map<char, int>& map, unordered_map<char, string>& codes) {
    int res = 0;
    for (auto it: map) {
        res += it.second * codes[it.first].size();
    }
    return res;
}

bool sortf3(pair<char, string> A, pair<char, string> B) {
    return (int)A.first < (int)B.first;
}

void print_output(unordered_map<char, int>& map, unordered_map<char, string>& codes, string& s) 
{
    int bits = count_bits(map, codes);
    cout << map.size() << " " << bits << endl;
    vector<pair<char, string>> v;
    for (auto it: codes) 
        v.push_back(pair<char, string>(it.first, it.second));
        
    sort(v.begin(), v.end(), sortf3);
    for (auto it: v) 
        cout << it.first << ": "<< it.second << endl;
        
    for (auto c: s)
        cout << codes[c];
    cout << endl;
    
}

int main() {
    string s = "abacabad";
    //string s = "";
    // cin >> s;
    unordered_map<char, int> map = get_freq(s);
    vector<Node*> tree;
    create_tree(tree, map);
    unordered_map<char, string> codes = get_codes(tree);
    print(tree);
    print_output(map, codes, s);
    return 0;
}


