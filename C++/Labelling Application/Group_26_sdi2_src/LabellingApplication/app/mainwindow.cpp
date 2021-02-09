#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_helpwindow.h"
#include "helpwindow.h"
#include "binarytree.h"
#include <QApplication>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QLabel>
#include <QColorSpace>
#include <QMessageBox>
#include <QImage>
#include <QTextStream>
#include <QDir>
#include <QStringListModel>
#include <string>
#include <iostream>
#include <QGraphicsScene>
#include <iostream>


BinaryTree Tree;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Labelling Application"));

    //setup qgraphics view and scene for painting.
    ui->setupUi(this);
    rec = new Rec(this);
    ui->graphicsView->setScene(rec);
    ui->graphicsView->setStyleSheet("background: transparent");

    //blank out some sections to avoid crashes.
    ui->classSave->setEnabled(false);
    ui->classRemove->setEnabled(false);
    ui->classAdd->setEnabled(false);
    ui->loadButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImagesButton_clicked()
{
    for (int z = 0; z < fileNames.size(); z++)
    {
        Tree.remove(fileNames[z]);
    }
    fileNames.clear();
    baseNames.clear();

    fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("Images (*.png *.tif *.jpg *.jpeg)"));

    if(fileNames.empty()) {
        QMessageBox::information(0,"Error", "File Missing Or Not Selected");
    }
    else
    {
        ui->imageList->clear();

        for (int i = 0; i < fileNames.size(); i++)
        {
            QFileInfo file(fileNames[i]);

            baseName = file.fileName();

            fileCreatedAt = file.created().toString();

            //place values in binary tree and arrays for sorting.
            Tree.insertNode(fileNames[i], fileCreatedAt);
            baseNames.append(baseName);
            dateNameList.append(baseName);
            dateList.append(fileCreatedAt);
            ui->imageList->addItem(baseName);
        }
    }
}



void MainWindow::on_nameSortButton_clicked()
{
    buttonType = false;

    ui->imageList->clear();
    if (!nameClicked) {
        nameClicked = true;
        for (int c = 0; c < baseNames.size(); c++)
            for (int d = 0; d < baseNames.size() - 1; d++)
            {
                if (baseNames[d] > baseNames[d+1])
                {
                QString const temp = baseNames[d];
                baseNames[d] = baseNames[d+1];
                baseNames[d+1] = temp;
                }

        }
        for (int e = baseNames.size(); e --> 0; )
        {
            ui->imageList->addItem(baseNames[e]);
        }
    }
    else
    {
        nameClicked = false;
        for (int c = 0; c < baseNames.size() - 1; c++)
        for (int d = 0; d < baseNames.size() - d - 1; d++)
        {
            if (baseNames[d] > baseNames[d+1])
                swap(&baseNames[d], &baseNames[d+1]);
        }
        for (int e = 0; e < baseNames.size(); e++)
        {
            ui->imageList->addItem(baseNames[e]);
        }
    }
    baseNames.empty();
}

void MainWindow::on_imageList_itemDoubleClicked()
{
    QStringList imageList;
    QImage image;

    int index = ui->imageList->currentRow();

    if (!buttonType)
    {
        if (nameClicked)
            Tree.showNodeInReverseOrder();


        if (!nameClicked)
            Tree.showNodeInOrder();

        imageList = Tree.returnTraversal();

    }
    if (buttonType)
    {
        imageList.append(fileNames);
        if (dateClicked)
            index = fileNames.size() - (index + 1);
    }

    image.load(imageList[index]);


    image = image.scaledToHeight(ui->imageDisplay->height(), Qt::SmoothTransformation);
    ui->imageDisplay->setPixmap(QPixmap::fromImage(image));

    isImage = true;
    ui->saveButton->setEnabled(true);
    ui->loadButton->setEnabled(true);
    rec->clearRec();
}

void MainWindow::on_dateSortButton_clicked()//bubble sort based on the dates on which the images where added to the computer
{
    buttonType = true;

    ui->imageList->clear();

    if (!dateClicked) {
        dateClicked = true;
        for (int c = 0; c < dateList.size() - 1; c++)
        for (int d = 0; d < dateList.size() - d - 1; d++)
        {
            if (dateList[d] > dateList[d+1])
                swap(&dateList[d], &dateList[d+1]);
                swap(&dateNameList[d], &dateNameList[d+1]);
                swap(&fileNames[d], &fileNames[d+1]);
        }
        for (int e = dateNameList.size(); e --> 0; )
        {
            ui->imageList->addItem(dateNameList[e]);
        }
    }
    else
    {
        dateClicked = false;
        for (int c = 0; c < dateList.size() - 1; c++)
        for (int d = 0; d < dateList.size() - d - 1; d++)
        {
            if (dateList[d] > dateList[d+1])
                swap(&dateList[d], &dateList[d+1]);
                swap(&dateNameList[d], &dateNameList[d+1]);
                swap(&fileNames[d], &fileNames[d+1]);
        }
        //add sorted list to qlist box.
        for (int e = 0; e < dateNameList.size(); e++)
        {
            ui->imageList->addItem(dateNameList[e]);
        }
    }
}

void MainWindow::on_classLoad_clicked()//failed load still opens buttons
{
    //open windows file diolouge and set it to open.
    QString filter ="Text File(*.txt)";
    QString selectFile = QFileDialog::getOpenFileName(this,"Please Select A Class File","C://",filter);
    QFile classesFile(selectFile);

    GLocation = selectFile;

    if(!classesFile.open(QFile::ReadOnly))
    {
        QMessageBox::information(0,"Error","File Missing Or Not Selected");
    }

    else
    {
        QStringList textList;

        QTextStream textStream(&classesFile);
    //run through line by line to selected document
    while (true)
    {

        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            textList.append(line);

    }

    //iterate through the newly created list and add to binary tree and display
    for (int i = 0; i < textList.size(); i++)
    {
        baseName = textList[i];
        Tree.insertNode(textList[i], fileCreatedAt);
        classBaseNames.append(baseName);
        ui->classList->addItem(baseName);
    }

    classesFile.close();

    //allow access to buttons
    ui->classSave->setEnabled(true);
    ui->classRemove->setEnabled(true);

    }

}

void MainWindow::on_classSave_clicked()//iterate through qlistboxitem for each item, and store them to the already opened global file.
{
    QFile saveFile(GLocation);

    if(!saveFile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::information(0,"File Loading Failed",saveFile.errorString());
    }
    //save items through iteration into new file
    QTextStream saveStream(&saveFile);
    int classCount = ui->classList->count();
    for(int i = 0; i < classCount; i++)
    {
        saveStream << ui->classList->item(i)->text() + "\n";
  }

     QMessageBox::information(0,"File Saved","File Saved");

    saveFile.close();
}

void MainWindow::on_classAdd_clicked()//add classnames to sorting list and add new item to list from textbox
{
        ui->classList->addItem(ui->classEnter->text());
        classBaseNames.append(ui->classEnter->text());

}

void MainWindow::on_classRemove_clicked()//remove, current selected item when button is clicked
{
   if (ui->classList->selectedItems().size() !=0)
   {
    QList<QListWidgetItem*> items = ui->classList->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->classList->takeItem(ui->classList->row(item));
    }
   }
   else
   {
        QMessageBox::information(0,"Error","Please Select A Class To Remove");
    }
}

void MainWindow::on_classEnter_editingFinished()
{
    //allows the input of a file if text field is entered.
    QString classInput = ui->classEnter->text();
     if (classInput == "")
     {
         ui->classAdd->setEnabled(false);
     }
     else
         ui->classAdd->setEnabled(true);
}

void MainWindow::on_classAsc_clicked()//bubble sort for both ascending and descending alphabetical order. once the button is clicked set
                                      //nameclicked to false to prep reverse
{
    buttonType = true;

    ui->classList->clear();

    if (!nameClicked) {
        nameClicked = true;
        for (int c = 0; c < classBaseNames.size(); c++)
            for (int d = 0; d < classBaseNames.size() - 1; d++)
            {
                if (classBaseNames[d] > classBaseNames[d+1])
                {
                QString const temp = classBaseNames[d];
                classBaseNames[d] = classBaseNames[d+1];
                classBaseNames[d+1] = temp;
                }

        }
        for (int e = classBaseNames.size(); e --> 0; )
        {
            ui->classList->addItem(classBaseNames[e]);
        }
    }
    else
    {
        nameClicked = false;
        for (int c = 0; c < classBaseNames.size() - 1; c++)
        for (int d = 0; d < classBaseNames.size() - d - 1; d++)
        {
            if (classBaseNames[d] > classBaseNames[d+1])
                swap(&classBaseNames[d], &classBaseNames[d+1]);
        }
        for (int e = 0; e < classBaseNames.size(); e++)
        {
            ui->classList->addItem(classBaseNames[e]);
        }
    }
}

void MainWindow::on_drawShape_clicked(bool checked)
{
    //set mode for draw on button click
    if (checked == true)
    {
        rec->setMode(Rec::Mode(int(Rec::DrawRec)));

    }
}

void MainWindow::on_moveShape_clicked(bool checked)
{
    //set mode for move and select on button click
    if (checked == true)
    {
        rec->setMode(Rec::Mode(int(Rec::SelectObject)));
    }
}



void MainWindow::on_classList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    rec->ClassName = ui->classList->currentItem()->text();
}

void MainWindow::on_saveButton_clicked()
{
    //pass file location through to allow the file to save to that new location
    QString Save = QFileDialog::getSaveFileName(this,tr("Please Name And Select Location"),tr("C://*.annotations"));
    rec->saveJson(Save, ui->imageList->currentItem()->text());
}

void MainWindow::on_loadButton_clicked()
{
    //pass file location through to allow the file to read
    QString Load = QFileDialog::getOpenFileName(this,tr("Please Choose an Annotation File"),tr("C://*.annotations"));
    rec->readJson(Load);
}

void MainWindow::on_restoreButton_clicked()//call clear rec function to remove all items on scene
{
    rec->clearRec();
}


void MainWindow::on_helpButton_clicked()//open help window ontop of screen
{
    helpwindow helpWindow;
    helpWindow.setModal(true);
    helpWindow.exec();
}

void MainWindow::on_copyButton_clicked()//call rec function to copy paste shapes
{
    rec->copyPaste();
}

