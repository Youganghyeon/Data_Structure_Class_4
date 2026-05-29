#pragma once
#include "cstdio"
#define INF 9999
#define Max_vtxs 10
#define MAX_ELEMENT 200

class AdjMatGrpah {
protected:
    int size;
    char vector[Max_vtxs];
    int adj[Max_vtxs][Max_vtxs];

public:
    AdjMatGrpah() { reset(); }
    char getVector(int i) { return vector[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= Max_vtxs; }

    void reset() {
        size = 0;
        for (int i = 0; i < Max_vtxs; i++)
            for (int j = 0; j < Max_vtxs; j++)
                setEdge(i, j, 0);
    }

    void insertvector(char name) {
        if (!isFull()) vector[size++] = name;
        else printf("Error: overflow");
    }

    void insertEdge(int u, int k) {
        setEdge(u, k, 1);
        setEdge(k, u, 1);
    }

    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);
        for (int i = 0; i < size; i++) {
            fprintf(fp, "%c", getVector(i));
            for (int j = 0; j < size; j++)
                fprintf(fp, "%3d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

class SrchAMGrpah : public AdjMatGrpah {
    bool visited[Max_vtxs];
public:
    void resetVisited() {
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }

    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    void DFS(int v) {
        visited[v] = true;
        printf("%c", getVector(v));
        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && !visited[w])
                DFS(w);
    }
};

class WGraph : public AdjMatGrpah {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }

    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }  

    void load(char* filename) {
        FILE* fp;
        fopen_s(&fp, filename, "r");
        if (fp != NULL) {
            int n, val;
            fscanf_s(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                fscanf_s(fp, "%s", str, sizeof(str));  
                insertvector(str[0]);
                for (int j = 0; j < n; j++) {
                    fscanf_s(fp, "%d", &val);
                    insertEdge(i, j, val);
                }
            }
        }
        fclose(fp);
    }
};

class VertexSets {
    int parent[Max_vtxs];
    int nSets;
public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < n; i++)
            parent[i] = -1;
    }

    bool isRoot(int i) { return parent[i] < 0; }

    int findSet(int v) {
        while (!isRoot(v)) v = parent[v];
        return v;
    }

    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }
};

class HeapNode {
    int key;
    int v1;
    int v2;
public:
    HeapNode(int k = 0, int u = 0, int v = 0) : key(k), v1(u), v2(v) {}  

    void setKey(int k) { key = k; }
    void setV1(int u) { v1 = u; }   
    void setV2(int v) { v2 = v; }   
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};

class MinHeap {
    HeapNode node[MAX_ELEMENT];
    int size;
public:
    MinHeap() : size(0) {}

    bool isFull() { return size == MAX_ELEMENT - 1; }
    bool isEmpty() { return size == 0; }

    HeapNode& getParent(int i) { return node[i / 2]; } // 이진트리

    void insert(int key, int u, int v) {
        if (isFull()) return;
        int i = ++size;
        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i); //부모노드를 자식노드에 대입
            i /= 2;                 //
        }
        node[i].setKey(key);
        node[i].setV1(u);   // 
        node[i].setV2(v);
    }

    HeapNode remove() {                        
        if (isEmpty()) return HeapNode();      
        HeapNode item = node[1];               
        HeapNode last = node[size--];         
        int parent = 1, child = 2;
        while (child <= size) {
            if (child < size &&
                node[child].getKey() > node[child + 1].getKey())  
                child++;
            if (last.getKey() <= node[child].getKey())  
                break;
            node[parent] = node[child];
            parent = child;
            child *= 2;   
        }
        node[parent] = last; 
        return item;        
    }
};

class WGraphMST : public WGraph {
public:
    void Kruskal() {
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j);

        VertexSets set(size);
        int edgeAccepted = 0;

        while (edgeAccepted < size - 1) {
            HeapNode e = heap.remove();          
            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());
            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVector(e.getV1()), getVector(e.getV2()), e.getKey());
                set.unionSets(uset, vset);
                edgeAccepted++;
            }
        }
    }
};