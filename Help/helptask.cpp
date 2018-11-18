#include "helptask.h"
#include "ui_helptask.h"

HelpTask::HelpTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpTask)
{
    ui->setupUi(this);
    QPixmap image(":/imageTask.jpg");
    ui->image->setPixmap(image);
}

HelpTask::~HelpTask()
{
    delete ui;
}
