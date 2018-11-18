#ifndef STATISTICS_H
#define STATISTICS_H

#include <QGraphicsView>
#include "includes.h"
#include "ui_Statistics.h"
#include "GeneticAlgorithm/gene.h"
#include "Map/map.h"

class Statistics : public QWidget
{
    Q_OBJECT
public:
    explicit Statistics(QWidget *parent = 0);
    void ShowStatistics(const vector<int>& results,
                        const Gene& bestGene,
                        const shared_ptr<Map> map);
    void DrawGraphic(const vector<int>& results);

    void ShowSequence(const Gene& bestGene,
                      const shared_ptr<Map> map);

    void ShowIndexEvolutionDegradation(const vector<int>& results);
private:
    shared_ptr<QGraphicsScene> _scene;
    unique_ptr<Ui_Statistics> _ui;
};

#endif // GRAPHIC_H
