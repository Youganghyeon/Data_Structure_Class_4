#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QFrame>
#include <QString>
#include "graphwidget.h"
#include "wgraph.h"

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("한국 도시 최단경로 탐색기");
        resize(1100, 680);
        setStyleSheet(R"(
            QMainWindow, QWidget#centralWidget {
                background-color: #12122a;
            }
            QGroupBox {
                color: #a0a0c8;
                font-size: 12px;
                font-weight: bold;
                border: 1px solid #3a3a5c;
                border-radius: 6px;
                margin-top: 10px;
                padding-top: 6px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 4px;
            }
            QLineEdit {
                background: #1e1e3a;
                color: #e0e0ff;
                border: 1px solid #3a3a5c;
                border-radius: 4px;
                padding: 4px 8px;
                font-size: 12px;
            }
            QLineEdit:focus { border: 1px solid #6060a0; }
            QPushButton {
                background: #3a3a6a;
                color: #e0e0ff;
                border: none;
                border-radius: 5px;
                padding: 6px 12px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover  { background: #5050a0; }
            QPushButton:pressed{ background: #2a2a50; }
            QPushButton#btnRun {
                background: #00c896;
                color: #12122a;
                font-size: 13px;
                padding: 8px;
            }
            QPushButton#btnRun:hover { background: #00e0aa; }
            QPushButton#btnReset {
                background: #8a2a2a;
            }
            QPushButton#btnReset:hover { background: #c04040; }
            QComboBox {
                background: #1e1e3a;
                color: #e0e0ff;
                border: 1px solid #3a3a5c;
                border-radius: 4px;
                padding: 4px 8px;
            }
            QComboBox QAbstractItemView {
                background: #1e1e3a;
                color: #e0e0ff;
                selection-background-color: #3a3a6a;
            }
            QListWidget {
                background: #1a1a30;
                color: #c0c0e8;
                border: 1px solid #3a3a5c;
                border-radius: 4px;
                font-size: 11px;
            }
            QLabel { color: #c0c0e8; }
            QLabel#resultLabel {
                color: #f5a623;
                font-size: 13px;
                font-weight: bold;
            }
        )");

        // ── 중앙 위젯 ──
        auto* central = new QWidget(this);
        central->setObjectName("centralWidget");
        setCentralWidget(central);

        auto* mainLayout = new QHBoxLayout(central);
        mainLayout->setContentsMargins(12, 12, 12, 12);
        mainLayout->setSpacing(12);

        // ── 좌측 패널 ──
        auto* leftPanel = new QWidget;
        leftPanel->setFixedWidth(280);
        auto* leftLayout = new QVBoxLayout(leftPanel);
        leftLayout->setSpacing(10);
        leftLayout->setContentsMargins(0, 0, 0, 0);

        // 제목
        auto* titleLabel = new QLabel("🗺 도시 경로 탐색기");
        titleLabel->setStyleSheet("color: #a0a0ff; font-size: 16px; font-weight: bold; padding: 4px 0;");
        leftLayout->addWidget(titleLabel);

        // ── 그룹1: 도시 추가 ──
        auto* grpCity = new QGroupBox("도시 추가");
        auto* cityLayout = new QVBoxLayout(grpCity);

        edtCity = new QLineEdit;
        edtCity->setPlaceholderText("도시 이름 입력 (예: 서울)");
        cityLayout->addWidget(edtCity);

        auto* btnAddCity = new QPushButton("도시 추가");
        cityLayout->addWidget(btnAddCity);

        // 사전 정의 도시 버튼
        auto* presetLabel = new QLabel("빠른 추가:");
        presetLabel->setStyleSheet("color: #7070a0; font-size: 11px;");
        cityLayout->addWidget(presetLabel);

        auto* presetLayout = new QGridLayout;
        QStringList presets = {"서울","부산","대구","인천","광주","대전","울산","수원"};
        for (int i = 0; i < presets.size(); i++) {
            auto* b = new QPushButton(presets[i]);
            b->setStyleSheet("font-size: 11px; padding: 3px 6px;");
            presetLayout->addWidget(b, i / 4, i % 4);
            connect(b, &QPushButton::clicked, this, [this, presets, i]() {
                addCity(presets[i]);
            });
        }
        cityLayout->addLayout(presetLayout);
        leftLayout->addWidget(grpCity);

        // ── 그룹2: 경로(간선) 추가 ──
        auto* grpEdge = new QGroupBox("도로 연결 (거리 추가)");
        auto* edgeLayout = new QGridLayout(grpEdge);

        edgeLayout->addWidget(new QLabel("출발:"), 0, 0);
        cbxFrom = new QComboBox;
        edgeLayout->addWidget(cbxFrom, 0, 1);

        edgeLayout->addWidget(new QLabel("도착:"), 1, 0);
        cbxTo = new QComboBox;
        edgeLayout->addWidget(cbxTo, 1, 1);

        edgeLayout->addWidget(new QLabel("거리(km):"), 2, 0);
        edtDist = new QLineEdit;
        edtDist->setPlaceholderText("예: 325");
        edgeLayout->addWidget(edtDist, 2, 1);

        auto* btnAddEdge = new QPushButton("도로 연결");
        edgeLayout->addWidget(btnAddEdge, 3, 0, 1, 2);

        // 사전 정의 도로 버튼
        auto* presetEdgeBtn = new QPushButton(" 기본 데이터 로드");
        presetEdgeBtn->setStyleSheet("background:#2a2a5a; font-size:11px; padding:4px;");
        edgeLayout->addWidget(presetEdgeBtn, 4, 0, 1, 2);

        leftLayout->addWidget(grpEdge);

        // ── 그룹3: 최단경로 탐색 ──
        auto* grpDijk = new QGroupBox("최단경로 탐색 (Dijkstra)");
        auto* dijkLayout = new QGridLayout(grpDijk);

        dijkLayout->addWidget(new QLabel("출발 도시:"), 0, 0);
        cbxStart = new QComboBox;
        dijkLayout->addWidget(cbxStart, 0, 1);

        dijkLayout->addWidget(new QLabel("도착 도시:"), 1, 0);
        cbxEnd = new QComboBox;
        dijkLayout->addWidget(cbxEnd, 1, 1);

        btnRun = new QPushButton("최단경로 찾기 ");
        btnRun->setObjectName("btnRun");
        dijkLayout->addWidget(btnRun, 2, 0, 1, 2);

        resultLabel = new QLabel("결과가 여기에 표시됩니다");
        resultLabel->setObjectName("resultLabel");
        resultLabel->setWordWrap(true);
        resultLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        resultLabel->setMinimumHeight(60);
        dijkLayout->addWidget(resultLabel, 3, 0, 1, 2);

        leftLayout->addWidget(grpDijk);

        // ── 그룹4: 현재 도로 목록 ──
        auto* grpList = new QGroupBox("연결된 도로 목록");
        auto* listLayout = new QVBoxLayout(grpList);
        edgeList = new QListWidget;
        edgeList->setMaximumHeight(120);
        listLayout->addWidget(edgeList);
        leftLayout->addWidget(grpList);

        // 초기화 버튼
        auto* btnReset = new QPushButton("전체 초기화");
        btnReset->setObjectName("btnReset");
        leftLayout->addWidget(btnReset);

        leftLayout->addStretch();
        mainLayout->addWidget(leftPanel);

        // ── 우측: 그래프 위젯 ──
        gwidget = new GraphWidget(this);
        gwidget->graph = &graph;
        mainLayout->addWidget(gwidget, 1);

        // ── 시그널 연결 ──
        connect(btnAddCity, &QPushButton::clicked, this, [this]() {
            addCity(edtCity->text().trimmed());
            edtCity->clear();
        });

        connect(btnAddEdge, &QPushButton::clicked, this, [this]() {
            addEdge();
        });

        connect(presetEdgeBtn, &QPushButton::clicked, this, [this]() {
            loadPresetData();
        });

        connect(btnRun, &QPushButton::clicked, this, [this]() {
            runDijkstra();
        });

        connect(btnReset, &QPushButton::clicked, this, [this]() {
            graph.reset();
            gwidget->nodePositions.clear();
            gwidget->highlightPath.clear();
            gwidget->startNode = -1;
            gwidget->endNode   = -1;
            refreshCombos();
            edgeList->clear();
            resultLabel->setText("전체 초기화 완료");
            gwidget->update();
        });
    }

private:
    WGraphDijkstra  graph;
    GraphWidget*    gwidget;

    QLineEdit*  edtCity;
    QComboBox*  cbxFrom;
    QComboBox*  cbxTo;
    QLineEdit*  edtDist;
    QComboBox*  cbxStart;
    QComboBox*  cbxEnd;
    QPushButton* btnRun;
    QLabel*     resultLabel;
    QListWidget* edgeList;

    // ── 도시 추가 ──
    void addCity(const QString& name) {
        if (name.isEmpty()) return;
        std::string sname = name.toUtf8().constData();
        if (graph.findVertex(sname) >= 0) {
            resultLabel->setText("이미 존재하는 도시입니다.");
            return;
        }
        int idx = graph.insertVertex(sname);
        if (idx < 0) { resultLabel->setText("도시 수 초과 (최대 20개)"); return; }
        gwidget->addNodePosition(idx);
        refreshCombos();
        gwidget->update();
    }

    // ── 간선 추가 ──
    void addEdge() {
        if (cbxFrom->count() < 2 || cbxTo->count() < 2) {
            resultLabel->setText("도시를 먼저 2개 이상 추가하세요.");
            return;
        }
        QString fromName = cbxFrom->currentText();
        QString toName   = cbxTo->currentText();
        bool ok;
        int  dist = edtDist->text().trimmed().toInt(&ok);
        if (!ok || dist <= 0) {
            resultLabel->setText("올바른 거리(양수 정수)를 입력하세요.");
            return;
        }
        if (fromName == toName) {
            resultLabel->setText("출발과 도착이 같습니다.");
            return;
        }
        int u = graph.findVertex(fromName.toUtf8().constData());
        int v = graph.findVertex(toName.toUtf8().constData());
        graph.insertEdge(u, v, dist);

        // 목록 갱신
        edgeList->addItem(QString("%1 ↔ %2 : %3km").arg(fromName, toName).arg(dist));
        edtDist->clear();
        gwidget->highlightPath.clear();
        gwidget->update();
    }

    // ── 콤보박스 갱신 ──
    void refreshCombos() {
        auto refresh = [&](QComboBox* cb) {
            int prev = cb->currentIndex();
            cb->clear();
            for (int i = 0; i < graph.getSize(); i++)
                cb->addItem(QString::fromUtf8(graph.getLabel(i)));
            if (prev >= 0 && prev < cb->count()) cb->setCurrentIndex(prev);
        };
        refresh(cbxFrom);
        refresh(cbxTo);
        refresh(cbxStart);
        refresh(cbxEnd);
    }

    // ── Dijkstra 실행 ──
    void runDijkstra() {
        if (graph.getSize() < 2) {
            resultLabel->setText("도시를 2개 이상 추가하세요.");
            return;
        }
        int s = graph.findVertex(cbxStart->currentText().toUtf8().constData());
        int e = graph.findVertex(cbxEnd->currentText().toUtf8().constData());
        if (s == e) { resultLabel->setText("출발과 도착이 같습니다."); return; }

        DijkstraResult res = graph.shortestPath(s, e);
        gwidget->highlightPath = res.path;
        gwidget->startNode = s;
        gwidget->endNode   = e;
        gwidget->update();

        if (!res.reachable) {
            resultLabel->setText("⚠ 경로를 찾을 수 없습니다.");
            return;
        }

        // 경로 문자열
        QString pathStr;
        for (int i = 0; i < (int)res.path.size(); i++) {
            if (i > 0) pathStr += " → ";
            pathStr += QString::fromUtf8(graph.getLabel(res.path[i]));
        }
        resultLabel->setText(
            QString(" 경로: %1\n 총 거리: %2 km").arg(pathStr).arg(res.totalDist));
    }

    // ── 기본 데이터 로드 (한국 주요 도시) ──
    void loadPresetData() {
        graph.reset();
        gwidget->nodePositions.clear();
        gwidget->highlightPath.clear();
        edgeList->clear();

        // 도시 추가
        QStringList cities = {"서울","부산","대구","인천","광주","대전","울산","수원","전주","청주"};
        for (auto& c : cities) {
            int idx = graph.insertVertex(c.toUtf8().constData());
            (void)idx;
        }
        gwidget->rebuildPositions();

        // 실제 도로 거리 (km, 고속도로 기준 근사치)
        struct Edge { const char* a; const char* b; int d; };
        Edge edges[] = {
            {"서울","인천",  40},  {"서울","수원",  47},
            {"서울","대전", 160},  {"서울","청주", 140},
            {"서울","전주", 240},  {"서울","대구", 300},
            {"서울","부산", 420},  {"대전","청주",  55},
            {"대전","전주", 120},  {"대전","광주", 220},
            {"대전","대구", 155},  {"대구","울산",  89},
            {"대구","부산", 115},  {"부산","울산",  72},
            {"광주","전주",  92},  {"광주","부산", 290},
            {"수원","청주",  99},  {"인천","수원",  54},
        };
        for (auto& e : edges) {
            int u = graph.findVertex(e.a);
            int v = graph.findVertex(e.b);
            graph.insertEdge(u, v, e.d);
            edgeList->addItem(QString("%1 ↔ %2 : %3km")
                .arg(e.a, e.b).arg(e.d));
        }
        refreshCombos();
        resultLabel->setText("기본 데이터가 로드되었습니다.\n출발/도착을 선택하고 탐색하세요!");
        gwidget->update();
    }
};