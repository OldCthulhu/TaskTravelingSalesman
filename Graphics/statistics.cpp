#include "statistics.h"

Statistics::Statistics(QWidget *parent) : QWidget(parent), _ui(std::make_unique<Ui_Statistics>()) {
    _ui->setupUi(this);
}

void Statistics::ShowStatistics(const vector<int>& results,
                                const Gene& bestGene,
                                const shared_ptr<Map> map){

    DrawGraphic(results);
    ShowIndexEvolutionDegradation(results);
    ShowSequence(bestGene, map);

    _ui->le_countPopulation->setText(QString::number(results.size()));
    _ui->line->setStyleSheet("color: green;");
    _ui->line_2->setStyleSheet("color: red;");
    _ui->line_3->setStyleSheet("color: blue;");

    show();
}

void Statistics::ShowSequence(const Gene& bestGene,
                              const shared_ptr<Map> map){

    int countSolutions = bestGene.solution.size();
    for(int i = 0; i < countSolutions; ++i){
        QString nameCity = map->GetCity(bestGene.solution[i]).name.c_str();
        nameCity = QString::number(i) + " - " + nameCity;
        _ui->l_sequence->addItem(nameCity);
    }
}

void Statistics::ShowIndexEvolutionDegradation(const vector<int>& results){
    float indexEvolution = 0;
    float indexDegradation = 0;
    int countEvolution = 0;
    int countDegradation = 0;
    for(int i = 0; i < results.size() - 1; ++i){
        int resultOne = results[i];
        int resultTwo = results[i + 1];

        if(resultOne < resultTwo){
            indexDegradation += std::abs(resultOne - resultTwo);
            ++countDegradation;
        }

        if(resultOne > resultTwo){
            indexEvolution += std::abs(resultTwo - resultOne);
            ++countEvolution;
        }
    }

    indexEvolution == 0 ? 0 : indexEvolution /= countEvolution;
    indexDegradation == 0 ? 0 : indexDegradation /= countDegradation;

    _ui->le_index_e->setText(QString::number(indexEvolution));
    _ui->le_index_d->setText(QString::number(indexDegradation));

}

void Statistics::DrawGraphic(const vector<int>& results){
    QVector<double> g_x;
    QVector<double> g_y;

    int maximum = 0;
    int minimum = results[0];

    for(int i = 0; i < results.size(); i+=1){
        if(maximum < results[i]){
            maximum = results[i];
        }

        if(minimum > results[i]){
            minimum = results[i];
        }

        g_x.push_back(i);
        g_y.push_back(results[i]);
    }

    QCPItemLine *line1 = new QCPItemLine(_ui->graphic);

    _ui->graphic->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    for(int i = 0; i < results.size() - 1; ++i){
        int resultOne = results[i];
        int resultTwo = results[i + 1];

        QCPItemLine *line = new QCPItemLine(_ui->graphic);
        line->start->setCoords(i, resultOne);
        line->end->setCoords(i + 1, resultTwo);

        QPen pen;

        pen.setWidth(3);

        if(resultOne == resultTwo){
            pen.setColor(QColor(Qt::blue));
        }else if(resultOne < resultTwo){
            pen.setColor(QColor(Qt::red));
        }else if(resultOne > resultTwo){
            pen.setColor(Qt::green);
        }

        line->setPen(pen);
    }

    //_ui->graphic->clearGraphs();
    //_ui->graphic->addGraph();
    //_ui->graphic->graph(0)->setData(g_x, g_y);

    //_ui->graphic->graph(0)->setName("gfg");

    QPen pen;
    pen.setColor(Qt::red);

    //_ui->graphic->graph(0)->setPen(pen);
    //_ui->graphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    QFont font;
    font.setPixelSize(16);
    _ui->graphic->xAxis->setLabel("Популяции");
    _ui->graphic->xAxis->setTickLabelFont(font);
    _ui->graphic->xAxis->setLabelFont(font);

    _ui->graphic->yAxis->setTickLabelFont(font);
    _ui->graphic->yAxis->setLabel("Расстояние");
    _ui->graphic->yAxis->setLabelFont(font);

    _ui->graphic->xAxis->setRange( -2, results.size() + 2);
    _ui->graphic->yAxis->setRange(minimum - 300, maximum);

    _ui->graphic->replot();

    //0-----
    _ui->le_best->setText(QString::number(minimum));

}


