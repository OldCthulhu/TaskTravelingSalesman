#include "helpbygeneticalgorithm.h"
#include "ui_helpbygeneticalgorithm.h"

HelpByGeneticAlgorithm::HelpByGeneticAlgorithm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogByGeneticAlgorithm)
{
    ui->setupUi(this);
    _image = new QMovie(":/imageGA.gif");
    ui->image->setMovie(_image);
}

HelpByGeneticAlgorithm::~HelpByGeneticAlgorithm()
{
    delete ui;
}

void HelpByGeneticAlgorithm::reject(){
    _image->stop();
    QDialog::reject();
}

int HelpByGeneticAlgorithm::exec(){
    _image->start();
   return QDialog::exec();
}
