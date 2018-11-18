#ifndef HELPBYAUTHOR_H
#define HELPBYAUTHOR_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class HelpByAuthor;
}

class HelpByAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit HelpByAuthor(QWidget *parent = 0);
    virtual int exec() override;
    virtual void reject() override;
    ~HelpByAuthor();

private:
    Ui::HelpByAuthor *ui;
    QMovie* _image;
};

#endif // HELPBYAUTHOR_H
