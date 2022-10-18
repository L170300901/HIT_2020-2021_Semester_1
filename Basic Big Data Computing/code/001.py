import math
import random

'''
in the data file, the first line stands for the vertex set, the rest each line stands for a graph. 
each graph has several edges spilited by the symbol $, and each edges is standed by several vertexs.

near line 13 25 34 can each set the total number of hyper-graphs, the edge number of each graph and the vertexs on each edge.
'''
def generateData(sroad):
    #set how much graphs there
    total_number_graph = 100
    f = open(sroad, "w")
    ves = set('qwertyuioplkjhgfdsazxcvbnm')
    ves2 = []
    for i in range(26):
        ves2.append(chr(ord('a')+i))
        f.write(chr(ord('a')+i))
        f.write(' ')
    edge_list = []
    edge_set = set()
    for i in range(total_number_graph):
        #the edges of each graph
        individual_number_edge = random.randint(64, 128)
        individual_edge_list = []
        individual_edge_set = set()
        for j in range(individual_number_edge):

            individual_edge_list_vertex = []
            individual_edge_set_vertex = set()
            for k in range(26):
                #set the vertex on each edge
                seedt = random.randint(0, 1)
                if seedt == 1:
                    individual_edge_list_vertex.append(chr(ord('a')+k))
                    individual_edge_set_vertex.add(chr(ord('a')+k))
                    f.write(chr(ord('a')+k))
                    f.write(' ')
                else:
                    pass
            f.write('$ ')
            individual_edge_list.append(individual_edge_list_vertex)
            pass
        f.write('\n')
        edge_list.append(individual_edge_list)

    f.write('\n')
    #print(ves2)

    f.close()

def readData(sroad):
    f = open(sroad, "r")
    vertex_list = []
    h = f.readlines()
    vertex_list = h[0]
    graph_list = []
    vertsx_number = len(h[0])
    edge_number = len(h) - 1
    for i in range(1, edge_number):
        each_edge_list_pre = h[i].split('$')
        each_edge_list = []
        for j in range(len(each_edge_list_pre)):
            each_vertex_list = each_edge_list_pre[j].split(' ')
            each_edge_list.append(each_vertex_list)
        graph_list.append(each_edge_list)
    print(len(graph_list))
    print(len(graph_list[0]))
    print(len(graph_list[0][0]))
    return vertex_list, graph_list
        

if __name__ == "__main__":
    #generateData("/home/zsw/Documents/data0.txt")
    graph_listt = []
    vertex_listt = []
    vertex_listt, graph_listt =  readData("/home/zsw/Documents/data0.txt")
    print("successfully generate the data")
    print(math.pi)

    '''
    this can solve question 1. I have realized that add, delete, change operation on super graph. 
    In the program, I generate the data by myself. the edge are represented by a gruop of letters which stand for vertex.
    '''
    while(True):
        print("edge operation: input 1 to add and input 2 to change and input 3 to delete")
        '''
        super edge is the format that a group of letters that seperated by space(' '), like "a s d f g"
        '''
        x = input()
        if x == "1":
            y1 = input("please input the graph index:")
            y2 = input("please input the edge:")
            z1 = int(y1)
            y22 = []
            y22 = y2.split(' ')
            graph_listt[z1].append(y22)
        elif x == "2":
            y1 = input("please input the graph index:")
            y2 = input("please input the edge index:")
            y3 = input("please input the edge:")
            z1 = int(y1)
            z2 = int(y2)
            y33 = []
            y33 = y3.split(' ')
            graph_listt[z1][z2] = y33
        elif x == "3":
            y1 = input("please input the graph index:")
            y2 = input("please input the edge index:")
            z1 = int(y1)
            z2 = int(y2)
            del graph_listt[z1][z2]
        else:
            break
    while(True):
        print("vertex operation: input 1 to add and input 2 to change and input 3 to delete")
        x = input()
        if x == "1":
            y1 = input("please input the new vertex:")
            vertex_listt.append(y1)
        elif x == "2":
            y1 = input("please input the unused vertex:")
            vertex_listt.remove(y1)
            for i in range(len(graph_listt)):
                ii = 0
                while(True):
                    if(ii == len(graph_listt[i])):
                        break
                    if(y1 in graph_listt[i][ii]):
                        graph_listt[i].remove(graph_listt[i][ii])
                        ii -= 1
                    ii += 1

        elif x == "3":
            y1 = input("please input the old vertex:")
            y2 = input("please input the new vertex:")
            for i in range(len(vertex_listt)):
                if(vertex_listt[i] == y1):
                    vertex_listt[i] = y2
            for i in range(len(graph_listt)):
                for j in range(len(graph_listt[i])):
                    if(graph_listt[i][j] == y1):
                        graph_listt[i][j] = y2
        else:
            break