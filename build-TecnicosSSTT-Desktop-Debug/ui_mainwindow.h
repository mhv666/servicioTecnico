/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QRadioButton *pendienteDeValidacion;
    QRadioButton *preparadoParaLaValidacion;
    QRadioButton *reparado;
    QRadioButton *noReparado;
    QRadioButton *EnviadoAlaTienda;
    QPushButton *btnBuscar;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QPushButton *pushButton;
    QTableView *listaDeOrdenes;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(664, 436);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pendienteDeValidacion = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pendienteDeValidacion);
        pendienteDeValidacion->setObjectName(QStringLiteral("pendienteDeValidacion"));
        pendienteDeValidacion->setGeometry(QRect(450, 150, 171, 24));
        preparadoParaLaValidacion = new QRadioButton(centralWidget);
        buttonGroup->addButton(preparadoParaLaValidacion);
        preparadoParaLaValidacion->setObjectName(QStringLiteral("preparadoParaLaValidacion"));
        preparadoParaLaValidacion->setGeometry(QRect(450, 120, 201, 24));
        reparado = new QRadioButton(centralWidget);
        buttonGroup->addButton(reparado);
        reparado->setObjectName(QStringLiteral("reparado"));
        reparado->setGeometry(QRect(450, 90, 102, 24));
        noReparado = new QRadioButton(centralWidget);
        buttonGroup->addButton(noReparado);
        noReparado->setObjectName(QStringLiteral("noReparado"));
        noReparado->setGeometry(QRect(450, 60, 102, 24));
        EnviadoAlaTienda = new QRadioButton(centralWidget);
        buttonGroup->addButton(EnviadoAlaTienda);
        EnviadoAlaTienda->setObjectName(QStringLiteral("EnviadoAlaTienda"));
        EnviadoAlaTienda->setGeometry(QRect(450, 30, 141, 24));
        btnBuscar = new QPushButton(centralWidget);
        btnBuscar->setObjectName(QStringLiteral("btnBuscar"));
        btnBuscar->setGeometry(QRect(440, 200, 211, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 18));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(440, 300, 211, 26));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(520, 270, 58, 18));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 340, 211, 26));
        listaDeOrdenes = new QTableView(centralWidget);
        listaDeOrdenes->setObjectName(QStringLiteral("listaDeOrdenes"));
        listaDeOrdenes->setGeometry(QRect(10, 30, 411, 211));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 664, 23));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pendienteDeValidacion->setText(QApplication::translate("MainWindow", "Pendiente de &validacion", Q_NULLPTR));
        preparadoParaLaValidacion->setText(QApplication::translate("MainWindow", "Preparado para la &validacion", Q_NULLPTR));
        reparado->setText(QApplication::translate("MainWindow", "Reparado", Q_NULLPTR));
        noReparado->setText(QApplication::translate("MainWindow", "&No reparado", Q_NULLPTR));
        EnviadoAlaTienda->setText(QApplication::translate("MainWindow", "Enviado a la tienda", Q_NULLPTR));
        btnBuscar->setText(QApplication::translate("MainWindow", "Buscar", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Ordenes", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Estado", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Asignar nuevo estado", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
