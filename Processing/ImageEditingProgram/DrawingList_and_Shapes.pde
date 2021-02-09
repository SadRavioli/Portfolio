

class DrawnShape {
  // type of shape
  // line
  // circle
  // Rect .....
  String shapeType;

  // used to define the shape bounds during drawing and after
  PVector shapeStartPoint, shapeEndPoint;

  boolean isSelected = false;
  boolean isBeingDrawn = false;
  boolean isDeleted = false;
  boolean isDragged = false;
  
  float x1;
  float y1;
  float x2;
  float y2;
  float w;
  float h;
  
  float red;
  float green;
  float blue;
  float lineWeight;
  
  float distStartX;
  float distStartY;
  float distEndX;
  float distEndY;
  
  
  public DrawnShape(String shapeType) {
    this.shapeType  = shapeType;
  }


  public void startMouseDrawing(PVector startPoint) {
    this.isBeingDrawn = true;
    this.shapeStartPoint = startPoint;
    this.shapeEndPoint = startPoint;
  }



  public void duringMouseDrawing(PVector dragPoint) {
    if (this.isBeingDrawn) this.shapeEndPoint = dragPoint;
  }


  public void endMouseDrawing(PVector endPoint) {
    this.shapeEndPoint = endPoint;
    
    this.isBeingDrawn = false;
  }


  public boolean tryToggleSelect(PVector p) {
    
    UIRect boundingBox = new UIRect(shapeStartPoint, shapeEndPoint);
   
    if ( boundingBox.isPointInside(p)) {
      this.isSelected = !this.isSelected;
      return true;
    }
    return false;
  }



  public void drawMe() {

    if (this.isSelected) 
    {
      setSelectedDrawingStyle();
    } else if ((red != 127 || green != 127 || blue != 127) && this.isSelected) {
      setCustomColour();
    } else if (isBeingDrawn) {
      setDefaultDrawingStyle();
    } 
    
    x1 = this.shapeStartPoint.x;
    y1 = this.shapeStartPoint.y;
    x2 = this.shapeEndPoint.x;
    y2 = this.shapeEndPoint.y;
    w = x2-x1;
    h = y2-y1;
    
    if (!isDeleted)
    {
      if ( shapeType.equals("draw rect")) rect(x1 , y1, w, h);
      if ( shapeType.equals("draw circle")) ellipse(x1+ w/2, y1 + h/2, w, h);
      if ( shapeType.equals("draw line")) line(x1, y1, x2, y2);
    }
    
    setDefaultDrawingStyle();
  }
  
  public void dragMe() {
    if (this.isSelected && mousePressed)
    {
      isDragged = true;
      distStartX = mouseX - this.shapeStartPoint.x;
      distStartY = mouseY - this.shapeStartPoint.y;
      distEndX = mouseX - this.shapeEndPoint.x;
      distEndY = mouseY - this.shapeEndPoint.y;
      
    }
    else
      distStartX = 0;
      distStartY = 0;
      distEndX = 0;
      distEndY = 0;
  }
  
  
  public void deleteMe() {
    if (this.isSelected && keyPressed)
    {
      if (key == DELETE)
        isDeleted = true;
    }
  }

  void setSelectedDrawingStyle() {
    strokeWeight(3);
    stroke(255, 0, 0);
    setColour(127, 127, 127);
    
  }
  
  void setColour(float red, float green, float blue)
  {
    this.red = red;
    this.green = green;
    this.blue = blue;
  }
  
  void setCustomColour() {
    fill(red, green, blue);
  } 
  
  void setDefaultDrawingStyle() {
    strokeWeight(1);
    stroke(0, 0, 0);
    setColour(127, 127, 127);
  }
}     // end DrawnShape




////////////////////////////////////////////////////////////////////
// DrawingList Class
// this class stores all the drawn shapes during and after thay have been drawn
//
// 


class DrawingList {

  ArrayList<DrawnShape> shapeList = new ArrayList<DrawnShape>();

  // this references the currently drawn shape. It is set to null
  // if no shape is currently being drawn
  public DrawnShape currentlyDrawnShape = null;

  public DrawingList() {
  }
  
  public void drawMe() {
    for (DrawnShape s : shapeList) {
      s.drawMe();
    }
  }
  
  public void deleteMe() {
    for (DrawnShape s : shapeList) {
      s.deleteMe();
    }
  }
  
  public void dragMe() {
    for (DrawnShape s : shapeList) {
      s.dragMe();
    }
  }
  
  public void setColour(float red, float green, float blue) {
    for (DrawnShape s : shapeList) {
      s.setColour(red, green, blue);
    }
  }
  


  public void handleMouseDrawEvent(String shapeType, String mouseEventType, PVector mouseLoc) {

    if ( mouseEventType.equals("mousePressed")) {
      DrawnShape newShape = new DrawnShape(shapeType);
      newShape.startMouseDrawing(mouseLoc);
      shapeList.add(newShape);
      currentlyDrawnShape = newShape;
    }

    if ( mouseEventType.equals("mouseDragged")) {
      currentlyDrawnShape.duringMouseDrawing(mouseLoc);
    }

    if ( mouseEventType.equals("mouseReleased")) {
      currentlyDrawnShape.endMouseDrawing(mouseLoc);
    }
  }


  

  public void trySelect(String mouseEventType, PVector mouseLoc) {
    if( mouseEventType.equals("mousePressed")){
      for (DrawnShape s : shapeList) {
        boolean selectionFound = s.tryToggleSelect(mouseLoc);
        if (selectionFound){
          //s.editMe();
        }
      }
    }
    
  }
}
