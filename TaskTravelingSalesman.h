#ifndef _TASK_TRAVELING_SALESMAN_H_
#define _TASK_TRAVELING_SALESMAN_H_
#include <QWidget>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>
#include <ctime>
#include "includes.h"
#include "Map/map.h"
#include "Graphics/statistics.h"
#include "GeneticAlgorithm/geneticAlgorithm.h"
#include "dialoggeneticalgorithm.h"
#include "Graphics/graphicsSceneCities.h"
#include "consts.h"
#include "Help/helpbyauthor.h"
#include "Help/helptask.h"
#include "Help/helpbygeneticalgorithm.h"
#include "ui_mainwindows.h"


class TaskTravelingSalesman : public QMainWindow{
    Q_OBJECT
public:
    explicit TaskTravelingSalesman(QWidget* parent = nullptr);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void resizeEvent(QResizeEvent* event) override;
private:
    unique_ptr<Ui_MainWindow> _ui;
    unique_ptr<GraphicsSceneCities> _scene;
    unique_ptr<DialogGeneticAlgorithm> _dialogGeneticAlgorithm;
    shared_ptr<Map> _map;
    vector<string> _nameCities;
    int _numberBeginCity = 0;
    int _sleep = 0;

    bool _isStop = false;
public slots:
    void SettingGeneration();
    void GenerationCities();
    void SetBeginCity(int index);
    void StopAlgorithm();
    void FindWay();
    void SetSleep();
    void ClearWays();
};

#endif
