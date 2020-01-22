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
void print_2D(vector<array<int, 2>> v);

class Node {
public:
    Node(int x_, int y_, int N)
    {
        x = x_;
        y = y_;
        value = INFINITY;
        visited = false;
        if(y-1 >= 0)
            friends.push_back({x, y-1});        
        if (x+1 < N)
            friends.push_back({x+1, y});        
        if(x-1 >= 0)
            friends.push_back({x-1, y});        
        if(y+1 < N)
            friends.push_back({x, y+1});        
    }
    vector<array<int, 2>> get_friends(){
        return friends;    
    }
    int x;
    int y;
    int value;
    bool visited;
    vector<array<int, 2>> friends;
};

class Graph 
{
    public: 
        Graph (vector<vector<int>> maze_)
        {
            maze = maze_;
            size = maze_.size();
            vector<Node> row;
            
            for (int i=0; i<size; ++i)
            {
                row = {};
                for (int j=0; j<size; ++j)
                {   
                    Node node(i, j, size);
                    row.push_back(node);
                    unvisited_nodes.push_back({i, j});
                }
                nodes.push_back(row);
            }
        }

        vector<array<int, 2>> get_friends(array<int, 2> a)
        {
            return nodes[a[0]][a[1]].get_friends();
        }
        
        void remove_visited(array<int, 2> a)
        {
            for (int i=0; i<unvisited_nodes.size(); ++i)
            {
                if((unvisited_nodes[i][0]==a[0])&&(unvisited_nodes[i][1]==a[1])) {
                    unvisited_nodes.erase(unvisited_nodes.begin()+i);
                    break;
                }
                    
            }
        }
        
        array<int, 2> unvisited_min() {
            array<int, 2> cur = unvisited_nodes[0];
            for (auto n: unvisited_nodes) {
                if (nodes[n[0]][n[1]].value < nodes[cur[0]][cur[1]].value) {
                    cur = n;
                }
            }                
            return cur;
        }
        
        void set_value(int x, int y, int value)
        {
            nodes[x][y].value = value;
        }
        
        void set_visit(int x, int y, bool visit)
        {
            nodes[x][y].visited = visit;
        }
        
        void print()
        {
            for  (int i=0; i<size; ++i) {
                for (int j=0; j<size; ++j) {
                    cout << nodes[i][j].value << " ";
                }            
                cout << endl;
            }
        }
        int size;
        vector<array<int, 2>> unvisited_nodes;
        vector<vector<Node>> nodes;
        vector<vector<int>> maze;
};


// https://stackoverflow.com/questions/9178083/priority-queue-for-user-defined-types

struct Comp{
    bool operator()(const Node& a, const Node& b){
        return a.value<b.value;
    }
};

int find_dijkstra_path(array<int, 2> start, array<int, 2> end, Graph graph)
{

    array<int, 2> current;

    current = {0, 0};
    graph.set_value(current[0], current[1], 0);

    int tentative_dist_new; 
    int tentative_dist_old;
    vector<array<int, 2>> friends;
    int cnt = 0;
    while (true){
        friends = graph.get_friends(current);
        
        for (auto f: friends) {
            if (graph.nodes[f[0]][f[1]].visited == false) {
                tentative_dist_old = graph.nodes[f[0]][f[1]].value;
                tentative_dist_new = graph.maze[f[0]][f[1]] + graph.nodes[current[0]][current[1]].value;
                if (tentative_dist_new < tentative_dist_old)
                    graph.nodes[f[0]][f[1]].value = tentative_dist_new;
            }
        }
        graph.nodes[current[0]][current[1]].visited = true;
        graph.remove_visited(current);
        if (graph.nodes[end[0]][end[1]].visited == true)
        {
            break;        
        }
        array<int, 2> m = graph.unvisited_min();
        if (graph.nodes[m[0]][m[1]].value == INFINITY)
        {
            break;        
        }
        current = m;
    }
                    
    graph.print();
    return graph.nodes[end[0]][end[1]].value;
    
}

void print_2D(vector<array<int, 2>> v) {
    for (auto row: v)
        for (auto el: row)
            cout << el << " ";
    cout << endl;
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

    string maze = "023\n595\n220";
    vector<vector<int>> maze_;

    maze_ = get_maze(maze);
    Graph graph(maze_);
    array<int, 2> start = {0, 0};
    array<int, 2> end = {maze_.size()-1, maze_.size()-1};
    int path_cost = find_dijkstra_path(start, end, graph);
    cout << "Path cost " << path_cost << endl;

    return 0;
}
