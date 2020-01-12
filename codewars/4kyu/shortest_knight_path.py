#!/usr/bin/env python3

class Knight:
    '''
    Dijkstra algorithm implementation for shortest knight path searching.
    '''   
    class Node:
        def __init__(self, x, y):
            self.unvisited = True
            self.distance = float('inf')
            self.x = x
            self.y = y               
    
    def __init__(self):
        self.desk = [ [ self.Node(i, j) for i in range(8)] for j in range(8)]
        self.actions = (
            (2, 1), (2,-1), (-2, 1), (-2,-1),
            (1, 2), (-1, 2), (1, -2), (-1, -2)
        )
    
    def xy(self, p):
        x = ord(p[0])-97
        y = int(p[1])-1
        return x, y
        
    def get_min(self):
        node = None
        for i in range(8):
            for j in range(8):
                if node == None and self.desk[j][i].unvisited == True:
                    node = self.desk[j][i]
                if node != None:
                    cur = self.desk[j][i]
                    if cur.unvisited == True and node.distance > cur.distance:
                        node = cur
        return node
        
    def get_neighbors(self, node):
        l = []
        for action in self.actions:
            x = node.x+action[0]
            y = node.y+action[1]
            
            if  x < 8 and x >= 0 and y < 8 and y >= 0:
                if self.desk[y][x].unvisited == True:
                    l.append(self.desk[y][x])
        return l
    
    def calc(self, p1, p2):
        x, y = self.xy(p1)
        self.desk[y][x].distance = 0
        x, y = self.xy(p2)
        end = {'x': x, 'y': y}
        while True:
            cur = self.get_min()
            neighbors = self.get_neighbors(cur)
            for n in neighbors:
                n.distance = cur.distance + 1
            cur.unvisited = False
            if self.desk[end['y']][end['x']].unvisited == False:
                return self.desk[end['y']][end['x']].distance

def knight(p1, p2):
    return Knight().calc(p1, p2)
    
if __name__ == '__main__':
    arr = [['a1', 'c1', 2], ['a1', 'f1', 3], ['a1', 'f3', 3], ['a1', 'f4', 4], ['a1', 'f7', 5], ['a3', 'a8', 3], ['g4', 'c5', 3]]
    for x in arr:
        z = knight(x[0], x[1])
        print(z == x[2], "{} to {}: expected {}, got {}".format(x[0], x[1], x[2], z))
  
    
    
