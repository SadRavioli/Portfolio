#include "rec.h"

Rec::Rec(QObject* parent): QGraphicsScene(parent)
{
    itemToDraw = 0;
    simpleTextToDraw = 0;
    sceneMode = NoMode;
    NoItems = 0;
}

void Rec::setMode(Mode mode)
{
    //mode defintions, if drawing mode cant drag, if select object can make items controllable and drag.
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawRec){
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject){
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }
}

void Rec::makeItemsControllable(bool areControllable)
{

    //sets all items moveable
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Rec::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //mouse press event to set origin point of mouse. to begin drawing
    if(sceneMode == DrawRec)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void Rec::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //only draw in draw mode enabled
    if(sceneMode == DrawRec)
    {
         if(!itemToDraw)
         {
             //add items to qgraphicsscene, and set colours and weights
             itemToDraw = new QGraphicsRectItem;
             this->addItem(itemToDraw);

             simpleTextToDraw = new QGraphicsSimpleTextItem;
             this->addItem(simpleTextToDraw);

             itemToDraw->setPen(QPen(Qt::red, 3, Qt::SolidLine));

             QFont font("Helvetica",20);
             simpleTextToDraw->setFont(font);
         }
         //if values go into negetive (moving mouse from bottom right to top left, set new values to allow for easy drawing.
         float top = qMin(origPoint.y(), event->scenePos().y());
         float left = qMin(origPoint.x(), event->scenePos().x());

         itemToDraw->setPos(left, top);

         //draw rectangle at origin and new points
         itemToDraw->setRect(0, 0, qAbs(event->scenePos().x() - origPoint.x()),
                    qAbs(event->scenePos().y() - origPoint.y()));


         //draw text and set to child of box to allow it to move with the box.
         simpleTextToDraw->setText(ClassName);
         simpleTextToDraw->QGraphicsItem::setParentItem(itemToDraw);

    }
    else
    {
         QGraphicsScene::mouseMoveEvent(event);
    }

}
void Rec::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //reset system to allow for multiple box drawing, increase number of items draw by 1
    if(sceneMode == DrawRec)
    {
        NoItems = NoItems + 1;     
    }
    itemToDraw = 0;
    simpleTextToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Rec::keyPressEvent(QKeyEvent *event){
    //when delete is pressed delete selected item.
    if(event->key() == Qt::Key_Delete)
    {
        foreach(QGraphicsItem* item, selectedItems())
        {
            removeItem(item);
            delete item;
            NoItems = NoItems - 1;
        }
    }

    else
    {
    QGraphicsScene::keyPressEvent(event);
    }

}

void Rec::readJson(QString Load)
   {
    //load json file from selection by user
    QFile jsonFile(Load);
    jsonFile.open(QFile::ReadOnly);
    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();

    //setup values corresponding to JSON values
    QJsonValue valueX = object.value("X");
    QJsonValue valueY = object.value("Y");
    QJsonValue valueHeight = object.value("Height");
    QJsonValue valueWidth = object.value("Width");
    QJsonValue valueAnno = object.value("Annotation");

    //setup arrays to take data.
    QJsonValue valueNoShapes = object.value("No of Shapes");
    QJsonArray arrayX = valueX.toArray();
    QJsonArray arrayY = valueY.toArray();
    QJsonArray arrayHeight = valueHeight.toArray();
    QJsonArray arrayWidth = valueWidth.toArray();
    QJsonArray arrayAnno = valueAnno.toArray();

    //iterate through the items up to the ammount of shapes drawn. reading each line by i number then calling draw jason to draw that box and text
    for(int i = 0; i < valueNoShapes.toInt(); i++)
    {
           int X = arrayX[i].toInt();
           int Y = arrayY[i].toInt();
           int Height = arrayHeight[i].toInt();
           int Width = arrayWidth[i].toInt();
           QString Annotation = arrayAnno[i].toString();

           drawJson(X,Y,Height,Width,Annotation);
       }
   }

void Rec::drawJson(int x,int y,int Height,int Width, QString annotation)
    {
    //similar to drawing above just automatically genrated from json files.
    itemToDraw = new QGraphicsRectItem;
    this->addItem(itemToDraw);

    simpleTextToDraw = new QGraphicsSimpleTextItem;
    this->addItem(simpleTextToDraw);


    itemToDraw->setPen(QPen(Qt::red, 3, Qt::SolidLine));


    QFont font("Helvetica",20);
    simpleTextToDraw->setFont(font);
    itemToDraw->setPos(x,y);
    itemToDraw->setRect(0,0, Width,Height);
    simpleTextToDraw->setText(annotation);
    simpleTextToDraw->QGraphicsItem::setParentItem(itemToDraw);
    NoItems = NoItems + 1;
    }

void Rec::saveJson(QString Save, QString ImageName)
{
    //insert data for image name and the number of items
        QJsonObject recordObject;
        recordObject.insert("Image Name", ImageName);
        recordObject.insert("No of Shapes", NoItems);
    //establish item arrays to store data
        QJsonArray arrayPosX;
        QJsonArray arrayPosY;
        QJsonArray arrayHeight;
        QJsonArray arrayWidth;
        QJsonArray arrayAnnotation;

            foreach(QGraphicsItem* item, items())
            {
                //store data only if qrectbox this is to stop text from creating null values
                if(QGraphicsRectItem* rect_item = qgraphicsitem_cast<QGraphicsRectItem *>(item))
                {
                arrayPosX.push_back(item->x());
                arrayHeight.push_back(item->boundingRect().height());
                arrayWidth.push_back(item->boundingRect().width());
                arrayPosY.push_back(item->y());
                }
                //store data only if simpletext item this pointer is used to get the text from the simpletextitem
                if(QGraphicsSimpleTextItem* text_item = qgraphicsitem_cast<QGraphicsSimpleTextItem *>(item))
                {
                    arrayAnnotation.push_back(text_item->text());
                }
            }

        //insert arrays into json file
        recordObject.insert("X",arrayPosX);
        recordObject.insert("Y",arrayPosY);
        recordObject.insert("Height",arrayHeight);
        recordObject.insert("Width",arrayWidth);
        recordObject.insert("Annotation",arrayAnnotation);

        QJsonDocument doc(recordObject);

        //open file and save generated contents
        QFile jsonFile(Save);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(doc.toJson());
}

void Rec::clearRec()
{
    //remove all items from scene and set number of items to zero
        foreach(QGraphicsItem* item, items()){
            removeItem(item);
            NoItems = 0;
        }

}

void Rec::copyPaste()
{
    //establish variables
    int X;
    int Y;
    int H;
    int W;
    QList<QGraphicsItem*> AnnoSelect;
    QString Anno;

    //also select to child annotation image
    foreach(QGraphicsItem* item, selectedItems()){
        if(QGraphicsRectItem* rect_item = qgraphicsitem_cast<QGraphicsRectItem *>(item))
        {
            AnnoSelect = rect_item->childItems();
            AnnoSelect[0]->setSelected(true);
        }
    }

    foreach(QGraphicsItem* item, selectedItems())
    {
        //only load data if it is a Qgraphics rect item
        if(QGraphicsRectItem* rect_item = qgraphicsitem_cast<QGraphicsRectItem *>(item))
        {
            X = item->pos().x();
            H = item->boundingRect().height();
            W = item->boundingRect().width();
            Y = item->y();
        }
        //only load data if it is a QgraphicSimpleTextItem
        if(QGraphicsSimpleTextItem* text_item = qgraphicsitem_cast<QGraphicsSimpleTextItem *>(item))
        {
           Anno = text_item->text();

        }
        //Draw stored shape
        drawJson(X,Y,H,W,Anno);
    }
}



