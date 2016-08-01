/********************************************************************************
** Form generated from reading UI file 'SGPU_InteractiveParticleSimulation.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SGPU_INTERACTIVEPARTICLESIMULATION_H
#define UI_SGPU_INTERACTIVEPARTICLESIMULATION_H

#include <QViewport.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SGPU_InteractiveParticleSimulationClass
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *toolFrame;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer;
    QPushButton *updateButton;
    QPushButton *startButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QToolButton *colorButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *particleSize;
    QPushButton *stopButton;
    QViewport *viewport;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SGPU_InteractiveParticleSimulationClass)
    {
        if (SGPU_InteractiveParticleSimulationClass->objectName().isEmpty())
            SGPU_InteractiveParticleSimulationClass->setObjectName(QStringLiteral("SGPU_InteractiveParticleSimulationClass"));
        SGPU_InteractiveParticleSimulationClass->resize(1264, 892);
        actionExit = new QAction(SGPU_InteractiveParticleSimulationClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(SGPU_InteractiveParticleSimulationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolFrame = new QWidget(splitter);
        toolFrame->setObjectName(QStringLiteral("toolFrame"));
        toolFrame->setMaximumSize(QSize(400, 16777215));
        gridLayout_4 = new QGridLayout(toolFrame);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(6, 6, 6, 6);
        verticalSpacer = new QSpacerItem(20, 320, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 0, 1, 1);

        updateButton = new QPushButton(toolFrame);
        updateButton->setObjectName(QStringLiteral("updateButton"));

        gridLayout_4->addWidget(updateButton, 1, 0, 1, 1);

        startButton = new QPushButton(toolFrame);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout_4->addWidget(startButton, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(toolFrame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(8);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(8, 8, 8, 8);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        colorButton = new QToolButton(groupBox_2);
        colorButton->setObjectName(QStringLiteral("colorButton"));

        horizontalLayout->addWidget(colorButton);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        particleSize = new QDoubleSpinBox(groupBox_2);
        particleSize->setObjectName(QStringLiteral("particleSize"));
        particleSize->setMinimum(0.1);
        particleSize->setMaximum(1);
        particleSize->setSingleStep(0.1);
        particleSize->setValue(0.5);

        horizontalLayout_2->addWidget(particleSize);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        stopButton = new QPushButton(toolFrame);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        gridLayout_4->addWidget(stopButton, 3, 0, 1, 1);

        splitter->addWidget(toolFrame);
        viewport = new QViewport(splitter);
        viewport->setObjectName(QStringLiteral("viewport"));
        splitter->addWidget(viewport);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        SGPU_InteractiveParticleSimulationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SGPU_InteractiveParticleSimulationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1264, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        SGPU_InteractiveParticleSimulationClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(SGPU_InteractiveParticleSimulationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SGPU_InteractiveParticleSimulationClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(SGPU_InteractiveParticleSimulationClass);
        QObject::connect(actionExit, SIGNAL(triggered()), SGPU_InteractiveParticleSimulationClass, SLOT(close()));
        QObject::connect(updateButton, SIGNAL(released()), SGPU_InteractiveParticleSimulationClass, SLOT(onUpdate()));
        QObject::connect(colorButton, SIGNAL(released()), SGPU_InteractiveParticleSimulationClass, SLOT(onColorButton()));
        QObject::connect(startButton, SIGNAL(released()), SGPU_InteractiveParticleSimulationClass, SLOT(onStart()));
        QObject::connect(stopButton, SIGNAL(released()), SGPU_InteractiveParticleSimulationClass, SLOT(onStop()));

        QMetaObject::connectSlotsByName(SGPU_InteractiveParticleSimulationClass);
    } // setupUi

    void retranslateUi(QMainWindow *SGPU_InteractiveParticleSimulationClass)
    {
        SGPU_InteractiveParticleSimulationClass->setWindowTitle(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "SGPU_InteractiveParticleSimulation", 0));
        actionExit->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Exit", 0));
        updateButton->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Update", 0));
        startButton->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Start", 0));
        groupBox_2->setTitle(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Visual Properties", 0));
        label->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Particle Color:", 0));
        colorButton->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "...", 0));
        label_2->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Particle Size:", 0));
        stopButton->setText(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "Stop", 0));
        menuFile->setTitle(QApplication::translate("SGPU_InteractiveParticleSimulationClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class SGPU_InteractiveParticleSimulationClass: public Ui_SGPU_InteractiveParticleSimulationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SGPU_INTERACTIVEPARTICLESIMULATION_H
