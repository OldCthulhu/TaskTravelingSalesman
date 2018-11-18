#include "TaskTravelingSalesman.h"
#include <windows.h>

TaskTravelingSalesman::TaskTravelingSalesman(QWidget* parent) : QMainWindow(parent), _ui(std::make_unique<Ui_MainWindow>()){
    _ui->setupUi(this);
    srand(0);

    ifstream fileNameCities;

    fileNameCities.open(NAME_FILE_LIST_CITIES);

    if(fileNameCities.is_open()){
        copy(std::istream_iterator<string>(fileNameCities),
         std::istream_iterator<string>(),
         std::back_inserter(_nameCities));
    }

    _scene = std::make_unique<GraphicsSceneCities>();
    //_scene->setSceneRect(0, 0, 1500, QApplication::desktop()->height() - 200);

    _dialogGeneticAlgorithm = std::make_unique<DialogGeneticAlgorithm>();

    _ui->graphicsView->setScene(_scene.get());

    _map = std::make_shared<Map>(25, _ui->graphicsView->sceneRect(), _nameCities);

    for(auto city : *_map){
        _scene->addItem(new GraphicsCity(city));
    }

    connect(_ui->b_generation, SIGNAL(clicked()), SLOT(GenerationCities()));
    connect(_ui->b_findWay, SIGNAL(clicked()), SLOT(FindWay()));
    connect(_ui->cb_beginCity, SIGNAL(activated(int)), SLOT(SetBeginCity(int)));
    connect(_scene.get(), SIGNAL(MoveCity()), SLOT(ClearWays()));
    connect(_ui->b_stop, SIGNAL(clicked()), SLOT(StopAlgorithm()));

    //Menu
    connect(_ui->m_settingGeneticAlgorithm_2, SIGNAL(triggered()), SLOT(SettingGeneration()));
    connect(_ui->m_settingSleep_2, SIGNAL(triggered()), SLOT(SetSleep()));
    connect(_ui->m_execGeneticAlgorithm_2, SIGNAL(triggered()), SLOT(FindWay()));
    connect(_ui->m_stop, SIGNAL(triggered()), SLOT(StopAlgorithm()));

    auto dialogHelpByAuthor = new HelpByAuthor();
    auto dialogHelpTask = new HelpTask();
    auto dialogHelpByGeneticAlgorithm = new HelpByGeneticAlgorithm();

    connect(_ui->m_helpByAuthor, SIGNAL(triggered()), dialogHelpByAuthor, SLOT(exec()));
    connect(_ui->m_helpTask, SIGNAL(triggered()), dialogHelpTask, SLOT(exec()));
    connect(_ui->m_helpGeneticAlgorithm_2, SIGNAL(triggered()), dialogHelpByGeneticAlgorithm, SLOT(exec()));

    GenerationCities();
}

void TaskTravelingSalesman::SettingGeneration(){
    _dialogGeneticAlgorithm->exec();
}

void TaskTravelingSalesman::GenerationCities(){
    int width = _ui->graphicsView->geometry().width() - 25;
    int height =_ui->graphicsView->geometry().height() - 25;

    width = width < 640 ? 640 : width;
    height = height < 480 ? 480 : height;

    QRect rect(0, 0, width - 50, height);

    _scene->clear();
    _scene->setSceneRect(rect);
    _map->SetRect(rect);

    _ui->graphicsView->resizeAnchor();

    _ui->te_log->append("***Генерация городов***");

    _scene->Clear();
    int countCities = _ui->sb_countCities->value();

    _map->Generation(countCities, _nameCities);

    _ui->cb_beginCity->clear();
    for(auto city : *_map){
        _ui->cb_beginCity->insertItem(city->id, city->name.c_str());
        _scene->addItem(new GraphicsCity(city));
    }

    SetBeginCity(0);

    _ui->graphicsView->repaint();
    _ui->graphicsView->update();

    _ui->te_log->append(QString("Сгенерированно %1 городов.").arg(QString::number(countCities)));


}

void TaskTravelingSalesman::SetBeginCity(const int index){
    ClearWays();

    _numberBeginCity = index;
    _map->SetBeginCity(index);
    _scene->update();
}

void TaskTravelingSalesman::FindWay(){

    int countPopulation = _dialogGeneticAlgorithm->GetCountPopulation();
    int countGenes = _dialogGeneticAlgorithm->GetCountGenes();
    int changeMutation = _dialogGeneticAlgorithm->GetChangeMutation();
    bool isPrematureTermination = _dialogGeneticAlgorithm->IsPrematureTermination();

    _ui->te_log->clear();

    _ui->b_generation->setEnabled(false);
    _ui->b_findWay->setEnabled(false);
    _ui->sb_countCities->setEnabled(false);
    _ui->graphicsView->setEnabled(false);
    _ui->cb_beginCity->setEnabled(false);
    _ui->b_stop->setEnabled(true);
    _ui->m_stop->setEnabled(true);
    _ui->m_settingGeneticAlgorithm_2->setEnabled(false);
    _ui->m_execGeneticAlgorithm_2->setEnabled(false);

    _ui->progressBar->setMaximum(countPopulation);

    GeneticAlgorithm geneticAlgorithm{_numberBeginCity, _map, countGenes, countPopulation, changeMutation};
    geneticAlgorithm.Start();

    Statistics* graphic = new Statistics();

    Gene bestSolution;
    int counterUnchanging = 0;
    vector<int> result;

    while(geneticAlgorithm.IsNext()){
        geneticAlgorithm.NextPopulation();
        Gene newBestSolution = geneticAlgorithm.GetBestGene();

        if(newBestSolution.fitness < bestSolution.fitness ||
                /*first iteration*/ bestSolution.fitness == 0){
            bestSolution = newBestSolution;
        }

        if(newBestSolution.fitness == bestSolution.fitness && isPrematureTermination){
            ++counterUnchanging;
        }else{
            counterUnchanging = 0;
        }

        if(counterUnchanging >= 100){
            break;
        }

        _scene->SetWays(_map, newBestSolution.numberBeginCity, newBestSolution.solution);

        int lengthWay = _map->CalcLength(newBestSolution.solution, newBestSolution.numberBeginCity);

        result.push_back(lengthWay);

        _ui->l_lengthWay->setText("Длина пути: " + QString::number(lengthWay));
        _ui->progressBar->setValue(geneticAlgorithm.GetCurrentPopulation());

        QString listString;
        for(auto numberCity : bestSolution.solution){
           listString += QString::number(numberCity) + " ";
        }

        _ui->te_log->append(QString("%1 Популяция, Лучшая особь: %2, Последовательность: [%3]").
                                     arg(QString::number(geneticAlgorithm.GetCurrentPopulation())).
                                     arg(QString::number(lengthWay)).
                                     arg(listString));

        for(int i = 0; i < _sleep; ++i){
           QApplication::processEvents();
           Sleep(1);
        }

        QApplication::processEvents();

        if(_isStop){
            _isStop = false;
            break;
        }

    }

    _scene->SetWays(_map, bestSolution.numberBeginCity, bestSolution.solution);

    int bestLengthWay = _map->CalcLength(bestSolution.solution, bestSolution.numberBeginCity);
    _ui->l_lengthWay->setText("Длина пути: " + QString::number(bestLengthWay));


    graphic->ShowStatistics(result, bestSolution, _map);

    _ui->graphicsView->setEnabled(true);
    _ui->b_generation->setEnabled(true);
    _ui->b_findWay->setEnabled(true);
    _ui->sb_countCities->setEnabled(true);
    _ui->cb_beginCity->setEnabled(true);
    _ui->b_stop->setEnabled(false);
    _ui->m_stop->setEnabled(false);
    _ui->m_settingGeneticAlgorithm_2->setEnabled(true);
    _ui->m_execGeneticAlgorithm_2->setEnabled(true);
}

void TaskTravelingSalesman::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_T){
        SetSleep();
    }

    QWidget::keyPressEvent(event);
}

void TaskTravelingSalesman::SetSleep(){
    _sleep = QInputDialog::getInt(this, tr("Задержка"),
                                   tr("Задержка:"), _sleep, 0, 10000);
}

void TaskTravelingSalesman::StopAlgorithm(){
    _isStop = true;
}

void TaskTravelingSalesman::ClearWays(){
    _ui->progressBar->setValue(0);
    _ui->l_lengthWay->setText("Длина пути: ");
    _scene->ClearLines();
}

void TaskTravelingSalesman::resizeEvent(QResizeEvent* event){
}
