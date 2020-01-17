#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int V;

struct PriorityQueue {
  public:
	vector<vector<Node>> queue;
	void add_node(Node node) {
	  bool not_inserted = true;
	  for (int i=queue.begin(); i<queue.end(); ++i) {
	    if (queue[i].value > node.value) {
	      queue.insert(queue.begin()+i, node);	    
	      inserted = false;
	      break;
	    }  
	  }
	  if (not_inserted)
	    queue.push_back(node);
	}
	Node pop() {
	  queue.pop_front();
	}
}

struct Node {
  public:
	  int value = numeric_limits<int>::max();
	  int x;
	  int y;
	  bool visited = false;
	  vector<vector<Node>> neighbors;
	  Node (int x_; int y_) {
	  	x = x_;
		y = y_;
		if ((x-1>=0)&&(y-1>=0))
		  neighbors.push_back(Node(x-1, y-1));
		if ((x<V)&&(y-1>=0))
		  neighbors.push_back(Node(x+1, y-1));
		if ((x-1>=0)&&(y<V))
		  neighbors.push_back(Node(x-1, y+1));
		if ((x<V)&&(y<V))
		  neighbors.push_back(Node(x+1, y+1));
	  }
};

struct Graph {
  public:
  	    vector<vector<Node>> nodes;
	    Node (vector<vector<int>> maze) {
            for (int i=0; i < V; ++i) {
                for (int j=0; j < V; ++j) {
                
                }
            }
	    }
};


int search (vector<vector<int>> maze)  {
  pq = PriorityQueue();
  pq.add_node(Node(0, 0));
  while true {
    
    
  }
  return 0;
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

int main () {
  std::string s5 = 
  "700000\n"
  "077770\n"
  "077770\n"
  "077770\n"
  "077770\n"
  "000007";

  vector<vector<int>> maze = get_maze(s5);
  V = maze.size(); 
  cout << search(maze) << end;
  return 0;
}
