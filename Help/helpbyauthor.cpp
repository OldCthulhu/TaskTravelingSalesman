#include "helpbyauthor.h"
#include "ui_helpbyauthor.h"

HelpByAuthor::HelpByAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpByAuthor)
{
    ui->setupUi(this);

   _image = new QMovie(":/imageHelp.gif");
    ui->image->setMovie(_image);
}

HelpByAuthor::~HelpByAuthor()
{
    delete ui;
}

void HelpByAuthor::reject(){
    _image->stop();
    QDialog::reject();
}

int HelpByAuthor::exec(){
    _image->start();
   return QDialog::exec();
}
