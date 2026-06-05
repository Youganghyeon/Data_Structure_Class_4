#include "graph.h"

int main()

{
	/*SrchAMGrpah g;
	WGraph c;
	char str[] = "graph.txt";
	c.load(str);
	c.display();

	for (int i = 0; i <= 3; i++)
		g.insertvector('A' + i);

	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);

	printf("graph\n");
	g.display();

	FILE* fp;
	fopen_s(&fp, "../text_out.txt", "w");
	if (fp != NULL) {
		c.display(fp);
		fclose(fp);
	}
	printf("DFS \n");
	g.display();
	printf("DFS --->");
	g.resetVisited();
	g.DFS(0);
	printf("\n");
	return 0;*/
	WGraphDijkstra g;
	char str[] = "graph.txt";
	g.load(str);
	printf("Shorted Path by Djksta Algorith \n");
	g.ShortestPath(0);
}