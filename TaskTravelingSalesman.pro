#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T17:00:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TaskTravelingSalesman
TEMPLATE = app


CONFIG += c++14

FORMS += \ 
         Graphics/statistics.ui \
    mainwindows.ui \
    dialoggeneticalgorithm.ui \
    Help/helptask.ui \
    Help/helpbyauthor.ui \
    Help/helpbygeneticalgorithm.ui

HEADERS += \
    GeneticAlgorithm/const.h \
    GeneticAlgorithm/evaluator.h \
    GeneticAlgorithm/gene.h \
    GeneticAlgorithm/geneticAlgorithm.h \
    GeneticAlgorithm/mutator.h \
    GeneticAlgorithm/reproductor.h \
    Graphics/graphicsSceneCities.h \
    Map/map.h \
    consts.h \
    includes.h \
    TaskTravelingSalesman.h \
    Math/mathq.h \
    Graphics/statistics.h \
    Graphics/qcustomplot.h \
    dialoggeneticalgorithm.h \
    Help/helptask.h \
    Help/helpbyauthor.h \
    Help/helpbygeneticalgorithm.h

SOURCES += \
    GeneticAlgorithm/evaluator.cpp \
    GeneticAlgorithm/geneticAlgorithm.cpp \
    GeneticAlgorithm/mutator.cpp \
    GeneticAlgorithm/reproductor.cpp \
    Graphics/graphicsSceneCities.cpp \
    Map/map.cpp \
    main.cpp \
    TaskTravelingSalesman.cpp \
    Math/mathq.cpp \
    Graphics/statistics.cpp \
    Graphics/qcustomplot.cpp \
    dialoggeneticalgorithm.cpp \
    Help/helptask.cpp \
    Help/helpbyauthor.cpp \
    Help/helpbygeneticalgorithm.cpp

RESOURCES += \
    res/res.qrc

RC_FILE = file.rc

