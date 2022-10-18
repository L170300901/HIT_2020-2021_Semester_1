import pyspark
from pyspark import SparkContext
from pyspark import SparkFiles
import p003

map = [[0,0,0,1,1,0,1],
       [0,0,0,0,0,1,0],
       [0,0,0,1,0,1,0],
       [1,0,1,0,0,0,1],
       [1,0,0,0,0,1,1],
       [0,1,1,0,1,0,0],
       [0,0,0,1,1,0,0]]

def indexMap(a):
    return ord(a) - ord('a')

class vertex():
    def __init__(self):
        self.k = 0
        self.remainEdgesNum = 0
        self.edgesNode = {}
        self.states = {}

class MinHeap():
    def __init__(self):
        self.nodes = []

    def insert(self, newNode):
        index = len(self.nodes) + 1
        self.nodes.append(newNode)
        halfIndex = 0
        flag = 0
        while(1):
            if index == 1 or flag == 1:
                break
            if index % 2 == 1:
                halfIndex = (index + 1) / 2
            if index % 2 == 0:
                halfIndex = index / 2
            if self.nodes[halfIndex].remainEdgesNum <= self.nodes[index].remainEdgesNum:
                flag == 1
            if self.nodes[halfIndex].remainEdgesNum > self.nodes[index].remainEdgesNum:
                self.nodes[index] = self.nodes[halfIndex]
                index = halfIndex
        self.nodes[index] = newNode
            

    def popMinNode(self):
        if self.isEmpty():
            print("the MinHeap is empty")
            return -1
        index = 1
        minChild = 0
        answer = self.nodes[1]
        lastNode = self.nodes[len(self.nodes)-1]
        self.nodes.pop()
        if len(self.nodes) == 1:
            tmp = vertex()
            self.nodes.append(tmp)
            return answer
        while(1):
            if index * 2 > len(self.nodes) - 1:
                break
            minChild = index * 2
            if minChild != len(self.nodes) - 1 and self.nodes[minChild + 1].remainEdgesNum < self.nodes[minChild].remainEdgesNum:
                minChild += 1
            if(lastNode.remainEdgesNum > self.nodes[minChild].remainEdgesNum):
                self.nodes[index] = self.nodes[minChild]
            else:
                break
            index = minChild
        self.nodes[index] = lastNode
        return answer

    def isEmpty(self):
        if len(self.nodes) > 1:
            return False
        if len(self.nodes) == 1:
            return True

    def printMinHeap(self):
        for i in range(len(self.nodes)):
            if i == 0:
                continue
            else:
                print("remain edge to be coverd: " + self.nodes[i].remainEdgesNum)
                print("vertex can be used: " + self.nodes[i].k)


def sumofMax(edgesNode, states, k):
    count = 0
    sum = 0
    tmp = sorted(edgesNode.items(), key=lambda x:x[1], reverse=True)
    for key in edgesNode.keys():
        if states[key] == 0:
            sum += edgesNode[key]
            count += 1
        if count == k:
            break
    return sum

def verify(edgesNode, states, k, remainEdgesNum):
    sum = sumofMax(edgesNode, states, k)
    if (sum >= remainEdgesNum):
        return True
    return False

def genLeft(curNode, label):
    left = vertex()
    left.k = curNode.k - 1
    left.remainEdgesNum = curNode.remainEdgesNum
    for key in curNode.edgesNode.keys():
        left.edgesNode[key] = curNode.edgesNode[key]
    for key in curNode.states.keys():
        left.states[key] = curNode.states[key]
    sum = 0

    for key in left.edgesNode.keys():
        if label < key and left.states[key] != 1 and map[indexMap(label)][indexMap(key)]:
            sum += 1
            left.edgesNode[key] -= 1
    left.states[label] = 1
    left.edgesNode[label] = 0
    left.edgesNode = sorted(left.edgesNode.items(), key=lambda x:x[1], reverse=True)
    left.remainEdgesNum = left.remainEdgesNum - sum

    return left


def genRight(curNode, label):
    right = vertex()
    right.k = curNode.k
    right.remainEdgesNum = curNode.remainEdgesNum
    for key in curNode.edgesNode.keys():
        right.edgesNode[key] = curNode.edgesNode[key]
    for key in curNode.states.keys():
        right.states[key] = curNode.states[key]
    right.states[label] = -1
    return right

def greedFind(edges, k, remainEdgesNum):
    node = vertex()
    node.k = k
    node.remainEdgesNum = remainEdgesNum

    for key in edges.keys():
        node.edgesNode[key] = edges[key]
        node.states[key] = 0

    MH = MinHeap()
    MH.insert(node)
    while(len(MH.nodes) > 1):
        curNode = MH.popMinNode()
        if(curNode.remainEdgesNum == 0):
            points = k - curNode.remainEdgesNum
            print(points)
            count = 1
            for key in curNode.edgesNode.keys():
                if curNode.states[key] == 1:
                    count += 1
            return -1

        label = 'a'
        for key in curNode.edgesNode.keys():
            if curNode.states[key] == 0:
                label = key
        if (indexMap(label) <= len(map)):
            left = genLeft(curNode, label)
            right = genRight(curNode, label)
            if(verify(left.edgesNode, left.states, left.k, left.remainEdgesNum)):
                MH.insert(left)
            if(verify(right.edgesNode, right.states, right.k, right.remainEdgesNum)):
                MH.insert(right)


if __name__ == '__main__':
    k = input("输入k值：")
    n = len(map)
    remainEdgesNum = 0
    for i in map:
        for j in i:
            if j == 1:
                remainEdgesNum += 1
    remainEdgesNum /= 2
    finddistance = "/home/hadoop/examples_pyspark/data_D921.txt"
    finddistancename = "data_D921.txt"
    sc = SparkContext("local", "SparkFile App")
    sc.addFile(finddistance)
    print("Absolute Path -> %s" % SparkFiles.get(finddistancename))
    edges = {}
    states = {}
    sc = SparkContext("local", "Collect app")
    coll = edges.collect()
    for i in range(n):
        nodeChar = chr(ord('a') + i)
        edges[nodeChar] = 0
        states[nodeChar] = 0
        rdd1 = sc.parallelize([1,2])
        rdd1.persist( pyspark.StorageLevel.MEMORY_AND_DISK_2 )
        rdd1.getStorageLevel()
        print(rdd1.getStorageLevel())
    for i in range(len(map[0])):
        for j in range(len(map[0])):
            if i <= j:
                edges[chr(ord('a') + i)] += 1
                edges[chr(ord('a') + j)] += 1
    flag = verify(edges, states, k, remainEdgesNum)
    if not flag:
        print('wrong')

    else:
        greedFind(edges, k, remainEdgesNum)
