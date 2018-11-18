#include "dialoggeneticalgorithm.h"

DialogGeneticAlgorithm::DialogGeneticAlgorithm(QWidget *parent) :
    QDialog(parent),
    _ui(std::make_unique<Ui_DialogGeneticAlgorithm>())
{
    _ui->setupUi(this);

   _countPopulation = _ui->sb_countPopulation->value();
   _countGenes= _ui->sb_countGenes->value();
   _changeMutation = _ui->sb_changeMutation->value();
   _isPrematureTermination = _ui->cb_prematureTermination->checkState() == Qt::Unchecked ? 0 : 1;

   connect(_ui->b_ok, SIGNAL(clicked()), SLOT(Accept()));
}

int DialogGeneticAlgorithm::GetCountPopulation() const{
    return _countPopulation;
}

int DialogGeneticAlgorithm::GetCountGenes() const{
    return _countGenes;
}

int DialogGeneticAlgorithm::GetChangeMutation() const{
    return _changeMutation;
}

bool DialogGeneticAlgorithm::IsPrematureTermination() const{
    return _isPrematureTermination;
}

void DialogGeneticAlgorithm::Accept(){
   _countPopulation = _ui->sb_countPopulation->value();
   _countGenes= _ui->sb_countGenes->value();
   _changeMutation = _ui->sb_changeMutation->value();
   _isPrematureTermination = _ui->cb_prematureTermination->checkState() == Qt::Unchecked ? 0 : 1;

   emit accept();
}
