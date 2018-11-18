#ifndef DIALOGGENETICALGORITHM_H
#define DIALOGGENETICALGORITHM_H

#include <QDialog>
#include "includes.h"
#include "ui_dialoggeneticalgorithm.h"

class DialogGeneticAlgorithm : public QDialog
{
    Q_OBJECT
public:
    explicit DialogGeneticAlgorithm(QWidget *parent = 0);
    int GetCountPopulation() const;
    int GetCountGenes() const;
    int GetChangeMutation() const;
    bool IsPrematureTermination() const;
private:
    int _countPopulation;
    int _countGenes;
    int _changeMutation;
    int _countPrematureTermination;
    bool _isPrematureTermination;
    unique_ptr<Ui_DialogGeneticAlgorithm> _ui;
public slots:
    void Accept();
};

#endif // DIALOGGENETICALGORITHM_H
