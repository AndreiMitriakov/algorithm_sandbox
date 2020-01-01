'''
Binary tree search implementation
'''

class Node:
    def __init__(self, k, v, p=None):
        self.key = k
        self.value = v
        self.left = None
        self.right = None
        self.parent = p

    def swap_delete(self, node, children=False):
        self.key = node.key
        self.value= node.value
        self.parent = node.parent
        if children:
            if self.left == node:
                self.left = None
            elif self.right == node:
                self.right = None     
        else:
            self.left = None
            self.right = None            
        del node

class Tree:
    def __init__(self):
        self.root = None
        self.size = 0
        
    def __len__(self):
        return self.size
    
    def show_tree(self, current=None):
        if current == None:
            current = self.root
        print(current.key, end=" ")
        if current.left != None:
            self.show_tree(current.left)
        if current.right != None:
            self.show_tree(current.right)
    
    def insert(self, k, v, current=None):
        if current == None and self.root != None:
            current = self.root
        elif current == None and self.root == None:
            self.root = Node(k, v)
            return None
        if k > current.key:  
            if current.right == None:
                current.right = Node(k, v, current)
            else:
                self.insert(k, v, current.right)
        elif k < current.key:   
            if current.left == None:
                current.left = Node(k, v, current)
            else:
                self.insert(k, v, current.left)

    def find(self, k, current=None, mode="find"):
        if current == None and self.root != None:
            current = self.root
        elif current == None and self.root == None:
            return "Tree is empty"
        if k == current.key:
            if mode == "find":
                return current.value
            elif mode == "delete":
                return current
        elif k > current.key:  
            if current.right != None:
                result = self.find(k, current.right, mode)
        elif k < current.key:   
            if current.left != None:
                result = self.find(k, current.left, mode)
        if result != None:
            return result
        else:
            return "No results"
            
    def min_right(self, node):
        if node.left != None:
            self.min_right(node.left)
        else: 
            return node

    def delete(self, k):
        node = self.find(k, mode="delete")
        if node.left == None and node.right == None:
            if node.parent != None and node.parent.right == node:
                node.parent.right = None
            elif node.parent != None and node.parent.left == node:
                node.parent.left = None
            if node == self.root:
                self.root = None
        elif node.left == None and node.right != None:
            node.swap_delete(node.right)
        elif node.right == None and node.left != None:
            node.swap_delete(node.left)
        else:
            node.swap_delete(self.min_right(node.right), True)

if __name__ == '__main__':
    tree = Tree()
    tree.insert(25, 25)
    tree.insert(4, 4)
    tree.insert(1, 1)
    tree.insert(28, 28)
    tree.insert(27, 27)
    tree.insert(29, 29)
    tree.show_tree()

    

