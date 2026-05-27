#pragma once
#include "cstdio"
#define INF 9999
#define Max_vtxs 10
class AdjMatGrpah {
protected:
	int size;
	char vector[Max_vtxs];
	int adj[Max_vtxs][Max_vtxs];

public:
	AdjMatGrpah() { reset(); }
	char getVector(int i)
	{
		return vector[i];
	}
	int getEdge(int i, int j)
	{
		return adj[i][j];
	}
	void setEdge(int i, int j, int val)
	{
		adj[i][j] = val;
	}

	bool isEmpty()
	{
		return size == 0;
	}
	bool isFull()
	{
		return size >= Max_vtxs;
	}

	void reset()
	{
		size = 0;
		for (int i = 0; i < Max_vtxs; i++)
		{
			for (int j = 0; j < Max_vtxs; j++)
			{
				setEdge(i, j, 0);
			}
		}
	}

	void insertvector(char name)
	{
		if (!isFull()) vector[size++] = name;
		else printf("Error: overflow");
	}

	void insertEdge(int u, int k) {
		setEdge(u, k, 1);
		setEdge(k, u, 1);
	}
	void display(FILE* fp = stdout)
	{
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++)
		{
			fprintf(fp, "%c", getVector(i));
			for (int j = 0; j < size; j++)
			{
				fprintf(fp, "%3d", getEdge(i, j));	
			}
			fprintf(fp, "\n");
		}

	}
};

class SrchAMGrpah : public AdjMatGrpah
{
	bool visited[Max_vtxs];
public:
	void resetVisited() {
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v)
	{
		return getEdge(u,v) != 0;
	}

	void DFS(int v) {
		visited[v] = true;
		printf("%c", getVector(v));
		for (int w = 0; w < size; w++)
		{
			if (isLinked(v, w) && (visited[w] == false))
			{
				DFS(w);
			}
		}
	}
};

class WGraph : public AdjMatGrpah {
public:
	void insertEdge(int u, int v, int weight) {
		if (weight > INF) weight = INF;
		setEdge(u, v, weight);
	}
	bool hasEdge(int i, int j) {
		return (getEdge(i, j) < INF);
	}
	void load(char* filename)
	{
		FILE* fp;
		fopen_s(&fp, filename, "r");
		if (fp != NULL)
		{
			int n, val;
			fscanf_s(fp, "%d", &n);
			for (int i = 0; i < n; i++)
			{
				char str[80];
				int val;
				fscanf_s(fp, "%s", (str));
				insertvector(str[0]);
				for (int j = 0; j < n; j++)
				{
					fscanf_s(fp, "%d", &val);
					insertEdge(i, j, val);
				}
			}
		}
		fclose(fp);
	}

};