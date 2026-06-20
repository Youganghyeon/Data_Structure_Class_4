#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPoint>
#include <QFont>
#include <vector>
#include <set>
#include <cmath>
#include "wgraph.h"

// 각 노드의 화면 좌표
struct NodePos {
    int   idx;
    QPoint pos;
};

class GraphWidget : public QWidget {
public:
    WGraphDijkstra* graph = nullptr;

    std::vector<NodePos> nodePositions;
    std::vector<int>     highlightPath;   // Dijkstra 결과 경로
    int startNode = -1;
    int endNode   = -1;

    // 드래그 상태
    int dragIdx = -1;

    GraphWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumSize(600, 500);
        setMouseTracking(true);
        setStyleSheet("background-color: #1a1a2e; border-radius: 8px;");
    }

    // 노드 추가 시 위치 자동 배치 (원형)
    void addNodePosition(int idx) {
        // 원형 배치
        int n     = (int)nodePositions.size() + 1;
        int total = graph->getSize();
        double angle = 2.0 * M_PI * idx / std::max(total, 1);
        int cx = width()  / 2;
        int cy = height() / 2;
        int r  = std::min(width(), height()) / 2 - 70;
        QPoint p(cx + (int)(r * std::cos(angle - M_PI / 2)),
                 cy + (int)(r * std::sin(angle - M_PI / 2)));
        nodePositions.push_back({idx, p});
    }

    void rebuildPositions() {
        nodePositions.clear();
        int total = graph->getSize();
        int cx = width()  / 2;
        int cy = height() / 2;
        int r  = std::min(width(), height()) / 2 - 70;
        for (int i = 0; i < total; i++) {
            double angle = 2.0 * M_PI * i / std::max(total, 1);
            QPoint p(cx + (int)(r * std::cos(angle - M_PI / 2)),
                     cy + (int)(r * std::sin(angle - M_PI / 2)));
            nodePositions.push_back({i, p});
        }
    }

    QPoint posOf(int idx) const {
        for (auto& np : nodePositions)
            if (np.idx == idx) return np.pos;
        return {0, 0};
    }

    int nodeAt(QPoint p) const {
        for (auto& np : nodePositions) {
            if ((np.pos - p).manhattanLength() < 24)
                return np.idx;
        }
        return -1;
    }

    bool onHighlightPath(int u, int v) const {
        for (int i = 0; i + 1 < (int)highlightPath.size(); i++)
            if ((highlightPath[i] == u && highlightPath[i+1] == v) ||
                (highlightPath[i] == v && highlightPath[i+1] == u))
                return true;
        return false;
    }

protected:
    void paintEvent(QPaintEvent*) override {
        if (!graph) return;
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        int n = graph->getSize();

        // ── 엣지 그리기 ──
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!graph->hasEdge(i, j)) continue;

                QPoint pi = posOf(i);
                QPoint pj = posOf(j);
                bool   hi = onHighlightPath(i, j);

                if (hi) {
                    // 강조 경로: 굵은 주황 선
                    p.setPen(QPen(QColor("#f5a623"), 4));
                } else {
                    p.setPen(QPen(QColor("#3a3a5c"), 2));
                }
                p.drawLine(pi, pj);

                // 거리 라벨
                QPoint mid = (pi + pj) / 2;
                p.setPen(hi ? QColor("#f5a623") : QColor("#7a7a9a"));
                p.setFont(QFont("Arial", 9, hi ? QFont::Bold : QFont::Normal));
                p.drawText(mid + QPoint(4, -4),
                           QString::number(graph->getEdge(i, j)) + "km");
            }
        }

        // ── 노드 그리기 ──
        for (int i = 0; i < n; i++) {
            QPoint pos = posOf(i);
            bool isPath  = std::find(highlightPath.begin(), highlightPath.end(), i)
                           != highlightPath.end();
            bool isStart = (i == startNode);
            bool isEnd   = (i == endNode);

            // 그림자
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(0, 0, 0, 80));
            p.drawEllipse(pos + QPoint(3, 3), 20, 20);

            // 노드 원
            QColor nodeColor;
            if      (isStart) nodeColor = QColor("#00c896");
            else if (isEnd)   nodeColor = QColor("#ff6b6b");
            else if (isPath)  nodeColor = QColor("#f5a623");
            else              nodeColor = QColor("#4a4a7a");

            p.setBrush(nodeColor);
            p.setPen(QPen(nodeColor.lighter(140), 2));
            p.drawEllipse(pos, 20, 20);

            // 노드 라벨
            p.setPen(Qt::white);
            p.setFont(QFont("Arial", 9, QFont::Bold));
            QRect textRect(pos.x() - 30, pos.y() + 24, 60, 18);
            p.drawText(textRect, Qt::AlignCenter,
                       QString::fromUtf8(graph->getLabel(i)));

            // 시작/끝 표시
            if (isStart || isEnd) {
                p.setPen(Qt::white);
                p.setFont(QFont("Arial", 8, QFont::Bold));
                QString tag = isStart ? "출발" : "도착";
                p.drawText(pos.x() - 10, pos.y() + 8, tag);
            }
        }
    }

    void mousePressEvent(QMouseEvent* e) override {
        dragIdx = nodeAt(e->pos());
    }

    void mouseMoveEvent(QMouseEvent* e) override {
        if (dragIdx >= 0) {
            for (auto& np : nodePositions)
                if (np.idx == dragIdx) { np.pos = e->pos(); break; }
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent*) override {
        dragIdx = -1;
    }

    void resizeEvent(QResizeEvent*) override {
        if (graph) rebuildPositions();
    }
};