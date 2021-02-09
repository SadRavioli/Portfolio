#ifndef REC_H
#define REC_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>
#include <QAction>
#include <QGraphicsView>
#include <QList>
#include <QKeyEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <QFileDialog>
#include <QVariant>

/**
* @brief Draw, Move, Save ,Load Boxes and annotations
*
*/
class Rec : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawRec};
    Rec(QObject* parent = 0);
    void setMode(Mode mode);
    QString ClassName;
    int NoItems;


    /**
    * @brief function to remove selected rectangle
    *
    */
    void clearRec();
    /**
    * @brief Create several JSON arrays and begin inserting each rectangles Image name, number of shapes x, y, Height, width and annotation names into a JSON file
    *
    */
    void saveJson(QString file,QString ImageName);
    /**
    * @brief Read Json file and pull outputs from the file by iterating through the number of shapes to assist in redrawing them to the scene.
    *
    */
    void readJson(QString Load);

    /**
    * @brief Copy selected item by storing data into variables and draw it at same postion of the selected box.
    *
    */

    void copyPaste();
protected:
    /**
    * @brief get mouses starting position when clicked
    *
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
    * @brief move mouse set X,Y values for qrectitem in reference to the origin point set by mouse click
    *
    */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
    * @brief Draw shape from origin point to mouses new set point.
    *
    */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /**
    * @brief Handler for button presses this will call ClearRec() function when the "Delete" key is pressed
    *
    */
    void keyPressEvent(QKeyEvent *event);
    /**
    * @brief Drawing system for the read JSON files, taking each aspect from the file and inserting them at relevent draw points.
    *
    */
    void drawJson(int x,int y,int Height,int Width,QString annotation);


private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsRectItem* itemToDraw;
    QGraphicsSimpleTextItem* simpleTextToDraw;

    void makeItemsControllable(bool areControllable);
};

#endif // REC_H
