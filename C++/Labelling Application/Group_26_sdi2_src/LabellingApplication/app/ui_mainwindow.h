/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QListWidget *imageList;
    QPushButton *loadImagesButton;
    QPushButton *dateSortButton;
    QPushButton *nameSortButton;
    QGroupBox *groupBox_2;
    QPushButton *classLoad;
    QListWidget *classList;
    QLineEdit *classEnter;
    QPushButton *classRemove;
    QPushButton *classAdd;
    QPushButton *classSave;
    QPushButton *classAsc;
    QGroupBox *groupBox_3;
    QPushButton *saveButton;
    QPushButton *restoreButton;
    QPushButton *loadButton;
    QGroupBox *groupBox_4;
    QPushButton *helpButton;
    QPushButton *copyButton;
    QGroupBox *groupBox_5;
    QRadioButton *drawShape;
    QRadioButton *moveShape;
    QLabel *imageDisplay;
    QGraphicsView *graphicsView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 771, 160));
        imageList = new QListWidget(groupBox);
        imageList->setObjectName(QString::fromUtf8("imageList"));
        imageList->setGeometry(QRect(180, 20, 571, 131));
        loadImagesButton = new QPushButton(groupBox);
        loadImagesButton->setObjectName(QString::fromUtf8("loadImagesButton"));
        loadImagesButton->setGeometry(QRect(10, 20, 151, 31));
        dateSortButton = new QPushButton(groupBox);
        dateSortButton->setObjectName(QString::fromUtf8("dateSortButton"));
        dateSortButton->setGeometry(QRect(10, 70, 151, 31));
        nameSortButton = new QPushButton(groupBox);
        nameSortButton->setObjectName(QString::fromUtf8("nameSortButton"));
        nameSortButton->setGeometry(QRect(10, 120, 151, 31));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(788, 0, 801, 160));
        classLoad = new QPushButton(groupBox_2);
        classLoad->setObjectName(QString::fromUtf8("classLoad"));
        classLoad->setGeometry(QRect(10, 20, 161, 31));
        classList = new QListWidget(groupBox_2);
        classList->setObjectName(QString::fromUtf8("classList"));
        classList->setGeometry(QRect(190, 40, 581, 111));
        classEnter = new QLineEdit(groupBox_2);
        classEnter->setObjectName(QString::fromUtf8("classEnter"));
        classEnter->setGeometry(QRect(10, 90, 161, 20));
        QFont font;
        font.setPointSize(7);
        classEnter->setFont(font);
        classRemove = new QPushButton(groupBox_2);
        classRemove->setObjectName(QString::fromUtf8("classRemove"));
        classRemove->setGeometry(QRect(90, 50, 91, 31));
        classAdd = new QPushButton(groupBox_2);
        classAdd->setObjectName(QString::fromUtf8("classAdd"));
        classAdd->setGeometry(QRect(0, 50, 91, 31));
        classSave = new QPushButton(groupBox_2);
        classSave->setObjectName(QString::fromUtf8("classSave"));
        classSave->setGeometry(QRect(10, 120, 161, 31));
        classAsc = new QPushButton(groupBox_2);
        classAsc->setObjectName(QString::fromUtf8("classAsc"));
        classAsc->setGeometry(QRect(190, 10, 75, 23));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(1580, 0, 331, 160));
        saveButton = new QPushButton(groupBox_3);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(10, 50, 151, 31));
        restoreButton = new QPushButton(groupBox_3);
        restoreButton->setObjectName(QString::fromUtf8("restoreButton"));
        restoreButton->setGeometry(QRect(90, 90, 151, 31));
        loadButton = new QPushButton(groupBox_3);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(170, 50, 150, 31));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 160, 1900, 51));
        helpButton = new QPushButton(groupBox_4);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(1740, 10, 150, 30));
        copyButton = new QPushButton(groupBox_4);
        copyButton->setObjectName(QString::fromUtf8("copyButton"));
        copyButton->setGeometry(QRect(270, 10, 231, 31));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 0, 251, 41));
        drawShape = new QRadioButton(groupBox_5);
        drawShape->setObjectName(QString::fromUtf8("drawShape"));
        drawShape->setGeometry(QRect(10, 10, 121, 31));
        moveShape = new QRadioButton(groupBox_5);
        moveShape->setObjectName(QString::fromUtf8("moveShape"));
        moveShape->setGeometry(QRect(130, 10, 121, 31));
        groupBox_5->raise();
        helpButton->raise();
        copyButton->raise();
        imageDisplay = new QLabel(centralwidget);
        imageDisplay->setObjectName(QString::fromUtf8("imageDisplay"));
        imageDisplay->setGeometry(QRect(10, 210, 1900, 840));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 210, 1901, 841));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(1901, 841));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSceneRect(QRectF(0, 0, 1901, 841));
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        MainWindow->setCentralWidget(centralwidget);
        groupBox_2->raise();
        groupBox->raise();
        groupBox_3->raise();
        groupBox_4->raise();
        imageDisplay->raise();
        graphicsView->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Image", nullptr));
        loadImagesButton->setText(QCoreApplication::translate("MainWindow", "Load Images", nullptr));
        dateSortButton->setText(QCoreApplication::translate("MainWindow", "Order By Date", nullptr));
        nameSortButton->setText(QCoreApplication::translate("MainWindow", "Order By Name", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Class", nullptr));
        classLoad->setText(QCoreApplication::translate("MainWindow", "Load Class", nullptr));
        classEnter->setPlaceholderText(QCoreApplication::translate("MainWindow", "Add Class Name Then Press \"Add\"", nullptr));
        classRemove->setText(QCoreApplication::translate("MainWindow", "Remove Class", nullptr));
        classAdd->setText(QCoreApplication::translate("MainWindow", "Add New Class", nullptr));
        classSave->setText(QCoreApplication::translate("MainWindow", "Save Classes", nullptr));
        classAsc->setText(QCoreApplication::translate("MainWindow", "Sort A-Z", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Files", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
        restoreButton->setText(QCoreApplication::translate("MainWindow", "Restore", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
        groupBox_4->setTitle(QString());
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        copyButton->setText(QCoreApplication::translate("MainWindow", "Copy/Paste", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Draw/Move", nullptr));
        drawShape->setText(QCoreApplication::translate("MainWindow", "Draw Shape", nullptr));
        moveShape->setText(QCoreApplication::translate("MainWindow", "Move Shape", nullptr));
        imageDisplay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
