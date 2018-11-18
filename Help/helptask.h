#ifndef HELPTASK_H
#define HELPTASK_H

#include <QDialog>

namespace Ui {
class HelpTask;
}

class HelpTask : public QDialog
{
    Q_OBJECT

public:
    explicit HelpTask(QWidget *parent = 0);
    ~HelpTask();

private:
    Ui::HelpTask *ui;
};

#endif // HELPTASK_H
