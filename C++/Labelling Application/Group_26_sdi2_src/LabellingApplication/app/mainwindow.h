#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rec.h"


#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QScrollArea>
#include <QtCore/QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Holds all UI elements and handles user input
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:




    /**
     * @brief Constructor for the MainWindow class
     *
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor for the MainWindow class
     *
     */
    ~MainWindow();


private slots:

    /**
     * @brief Load File explorer upon clicking button, Once user selects appropriate file the file is read line by line and loaded into listboxWidget.
     * If user does not select or selects the wrong file a dialog will inform the user of the error.
     *
     *
     */
    void on_classLoad_clicked();

    /**
     * @brief Open the class file user selected to load class names. Check if opened correctly else break. Get total of items
     *in listbox and loop till this total using iterator and add each line into the class file, Output save dialog and close file.
     *
     */
    void on_classSave_clicked();

    /**
     * @brief User inputs a word into the lineEdit and aslong as not blank the Add button becomes available the new class name is appeneded to bottom of the listview.
     *
     */
    void on_classAdd_clicked();

    /**
     * @brief From user selected row in the listview delete specific class name. This can be done at any time changes will not save in the class file unless save file is chosen.
     *
     */
    void on_classRemove_clicked();

    /**
     * @brief When user has completed entering string triggered by pressing enter or clicking to an external component activate the
     * aslong as the string entered is not blank.
     */
    void on_classEnter_editingFinished();

    /**
     * @brief load class into an QStringList using an iterating loop with a maximum from items run bubble sort function and order the items in alphabetical order.
     * output a list and update the listview with the sorted values.
     */
    void on_classAsc_clicked();

    /**
     * @brief open file explorer for the user to allow them to select multiple images to load into the list widget. Image names are stored in a linked list.
     * Iterates through list to display image names. Will display error if user tries to load an image more than once.
     *
     */
    void on_loadImagesButton_clicked();

    /**
     * @brief On double click of the image name in the list widget, the image will be displayed. Uses current row as index.
     * Scales image to fit the window with smooth transformation function.
     */
    void on_imageList_itemDoubleClicked();

    /**
     * @brief Will sort images by date downloaded.
     *
     */
    void on_dateSortButton_clicked();
    
    /**
    * @brief Will sort images alphabetically.
    *
    */

    void on_saveButton_clicked();

    /**
    * @brief Will save to json file
    *
    */

    void on_nameSortButton_clicked();

    /**
    * @brief Radio Button which when enabled allows the user to draw a shape to QgraphicsScene
    *
    */
    void on_drawShape_clicked(bool);

    /**
    * @brief Radio Button which when enabled allows the user to move items around the QgraphicsScene with mouse
    *
    */
    void on_moveShape_clicked(bool);


    /**
    * @brief Used to get the current class name the user has selected from the list.
    *
    */
    void on_classList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Call REC Loading function that reads selected .annotations file and draws the contained shapes back onto the image.
    *
    */
    void on_loadButton_clicked();

    /**
    * @brief Button to clear all items on qgraphicsscene
    *
    */
    void on_restoreButton_clicked();

    /**
    * @brief Produce the help screen
    *
    */

    void on_helpButton_clicked();

    /**
    * @brief Call copy paste function to copy and paste selected shape
    *
    */
    void on_copyButton_clicked();

private:
    
    QGraphicsView *view;
    QGraphicsScene *scene;
    Rec *rec;
    QString GLocation;
    QStringList fileNames;
    QStringList baseNames;
    QStringList classBaseNames;
    QString baseName;
    QStringList dateList;
    QStringList dateNameList;
    QString fileCreatedAt;

    bool isImage = false;
    bool nameClicked;
    bool dateClicked;
    bool buttonType;

    void swap(QString *xp, QString *yp)
    {
        QString temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    /**
    * @brief Initialises UI.
    *
    */
    Ui::MainWindow *ui; 
};
#endif // MAINWINDOW_H
