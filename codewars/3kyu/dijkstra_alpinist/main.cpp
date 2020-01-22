#include <queue>
#include <vector>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <sstream>

using namespace std;
/*
    Dijkstra algorithm implementation
*/

int INFINITY = std::numeric_limits<int>::max();

class Node {};

class Graph {
public:
    Node get_current()
    {}
};

// https://stackoverflow.com/questions/9178083/priority-queue-for-user-defined-types

struct Comp{
    bool operator()(const Node& a, const Node& b){
        return a.value<b.value;
    }
};
vector<pair<int, int>> find_dijkstra_path(pair<int, int> start, pair<int, int> end, Graph graph)
{
    pair<int, int> point;
    vector<pair<int, int>> path;
    Node cur;
    priority_queue< Node, vector<Node>, Comp> q;
    vector<Node> neighbors;
    q.push(graph.get_start())
    while (true)
    {
        cur = q.pop();
        cur.visited = true;
        neighbors = cur.get_neighbors();
        for (auto n: neighbors)
        {
            n.value = graph.cost_map(n.first, n.second) + cur.value;
            q.push(n);
        }
        if (graph.end.visited == true) {
            break;
        }
    }
    // create path back
    // return path, cost;
}

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

vector<vector<int>> get_maze(string maze) {
    vector<vector<int>> v;
    vector<int> d;
    for (auto x: maze) {
        if ((x>=48) && (x<=57)) {
            d.push_back((int)x-48);
        }
        else {
            if (d.size() != 0) {
                v.push_back(d);
                d.clear();
            }

        }
    }
    v.push_back(d);
    return v;
}

void print(vector<vector<int>> v)
{
    for (auto d: v) {
        for (auto c: d) {
            cout << c;
        }
        cout << endl;
    }
}

int main() {
    string maze = "000\n190\n000";
    vector<vector<int>> maze_;
    maze_ = get_maze(maze);
    Graph graph(maze_);
    pair<int, int> start(0, 0);
    pair<int, int> end(maze_.size(), maze_.size());
    vector<pair<int, int>> path = find_dijkstra_path(start, end, graph);
    for (auto p: path)
    {
        cout << p.first << " " << p.second;
    }
    std::priority_queue<int> q;
    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
    return 0;
}
