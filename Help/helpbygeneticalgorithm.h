#ifndef DIALOGBYGENETICALGORITHM_H
#define DIALOGBYGENETICALGORITHM_H

#include <QMovie>
#include <QDialog>

namespace Ui {
class DialogByGeneticAlgorithm;
}

class HelpByGeneticAlgorithm : public QDialog
{
    Q_OBJECT

public:
    explicit HelpByGeneticAlgorithm(QWidget *parent = 0);
    virtual int exec() override;
    virtual void reject() override;
    ~HelpByGeneticAlgorithm();

private:
    Ui::DialogByGeneticAlgorithm *ui;
    QMovie* _image;
};

#endif // DIALOGBYGENETICALGORITHM_H
