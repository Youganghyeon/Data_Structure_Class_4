#pragma once
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

const int Max_vtxs = 20;  // 최대 노드(도시) 수
const int INF = INT_MAX / 2;  // 연결되지 않은 간선을 나타내는 무한대 값

/*
 * =====================================================================
 *  [클래스 구조 개요]
 *
 *  WGraph
 *  └─ 인접행렬(adj[][])을 사용하는 가중치 무방향 그래프 기반 클래스
 *  └─ 도시 이름(label), 도시 간 거리(adj) 저장 및 관리
 *  └─ 도시/간선 추가, 조회, 삭제 기능 제공
 *
 *  WGraphDijkstra : public WGraph
 *  └─ WGraph를 상속받아 Dijkstra 최단경로 알고리즘 기능 추가
 *  └─ dist[]: 출발지로부터 각 도시까지의 최단 거리
 *  └─ found[]: 해당 도시의 최단경로 확정 여부
 *  └─ prev[]: 최단경로 역추적을 위한 이전 노드 기록
 *
 *  DijkstraResult (구조체)
 *  └─ Dijkstra 실행 결과를 담는 구조체
 *  └─ reachable(도달 가능 여부), totalDist(총 거리), path(경로 순서)
 * =====================================================================
 */

// ─────────────────────────────────────────
//  인접행렬 가중치 그래프 (수업 코드 기반)
// ─────────────────────────────────────────
class WGraph {
protected:
    int  size;
    char label[Max_vtxs][32];   // 도시 이름 (한글 포함 대비 32바이트)
    int  adj[Max_vtxs][Max_vtxs];

public:
    WGraph() { reset(); }

    void reset() {
        size = 0;
        for (int i = 0; i < Max_vtxs; i++)
            for (int j = 0; j < Max_vtxs; j++)
                adj[i][j] = (i == j) ? 0 : INF;
    }

    int  getSize()              const { return size; }
    const char* getLabel(int i) const { return label[i]; }
    int  getEdge(int i, int j)  const { return adj[i][j]; }
    bool hasEdge(int i, int j)  const { return adj[i][j] < INF && i != j; }
    bool isEmpty()              const { return size == 0; }
    bool isFull()               const { return size >= Max_vtxs; }

    // 도시 추가 → 인덱스 반환, 실패 시 -1
    int insertVertex(const std::string& name) {
        if (isFull()) return -1;
        strncpy(label[size], name.c_str(), 31);
        label[size][31] = '\0';
        int idx = size++;
        // 새 노드 행/열 초기화
        for (int i = 0; i < size; i++) {
            adj[idx][i] = (idx == i) ? 0 : INF;
            adj[i][idx] = (idx == i) ? 0 : INF;
        }
        return idx;
    }

    // 이름으로 인덱스 조회 (-1: 없음)
    int findVertex(const std::string& name) const {
        for (int i = 0; i < size; i++)
            if (name == label[i]) return i;
        return -1;
    }

    // 무방향 간선 (양방향)
    void insertEdge(int u, int v, int weight) {
        if (u < 0 || v < 0 || u >= size || v >= size) return;
        adj[u][v] = weight;
        adj[v][u] = weight;
    }

    void removeEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= size || v >= size) return;
        adj[u][v] = INF;
        adj[v][u] = INF;
    }
};

// ─────────────────────────────────────────
//  Dijkstra 결과 구조체
// ─────────────────────────────────────────
struct DijkstraResult {
    bool  reachable;
    int   totalDist;
    std::vector<int> path;   // 노드 인덱스 순서
};

// ─────────────────────────────────────────
//  Dijkstra (수업 코드 WGraphDijkstra 기반)
// ─────────────────────────────────────────
class WGraphDijkstra : public WGraph {
    int  dist[Max_vtxs];
    bool found[Max_vtxs];
    int  prev[Max_vtxs];   // 경로 역추적용

    int chooseVertex() {
        int minDist = INF, minpos = -1;
        for (int i = 0; i < size; i++)
            if (!found[i] && dist[i] < minDist) {
                minDist = dist[i];
                minpos  = i;
            }
        return minpos;
    }

public:
    DijkstraResult shortestPath(int start, int end) {
        // 초기화
        for (int i = 0; i < size; i++) {
            dist[i]  = getEdge(start, i);
            found[i] = false;
            prev[i]  = (dist[i] < INF && i != start) ? start : -1;
        }
        found[start] = true;
        dist[start]  = 0;
        prev[start]  = -1;

        for (int i = 0; i < size - 1; i++) {
            int u = chooseVertex();
            if (u == -1) break;
            found[u] = true;
            for (int w = 0; w < size; w++) {
                if (!found[w] && getEdge(u, w) < INF) {
                    int newDist = dist[u] + getEdge(u, w);
                    if (newDist < dist[w]) {
                        dist[w] = newDist;
                        prev[w] = u;
                    }
                }
            }
        }

        // 결과 조합
        DijkstraResult result;
        result.reachable = (dist[end] < INF);
        result.totalDist = result.reachable ? dist[end] : -1;

        if (result.reachable) {
            // 역추적
            for (int v = end; v != -1; v = prev[v])
                result.path.push_back(v);
            std::reverse(result.path.begin(), result.path.end());
        }
        return result;
    }
};