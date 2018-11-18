#include <QApplication>
#include "TaskTravelingSalesman.h"

int main(int argv, char** argc){

    QApplication app(argv, argc);

    TaskTravelingSalesman task;
    task.show();

    return app.exec();
}
