PImage myImage;
PImage outImage;

SimpleUI myUI;

boolean image = false;

DrawingList drawingList;

String toolMode = "";

float weight = 1;
float red = 127;
float green = 127;
float blue = 127;

void setup(){
  size(1920,1080);
  // instantiate the UI
  myUI = new SimpleUI();
  
  // add two menus
  String[] fileMenuItems =  { "New", "Open", "Save"};
  myUI.addMenu("File", 5, 5, fileMenuItems);
  
  String[] filterMenuItems = { "Blur", "Sharpen", "Find Edges", "Emboss", "Unsharp Mask"};
  myUI.addMenu("Filter", 105, 5, filterMenuItems);  
  
  drawingList = new DrawingList();
  
  ButtonBaseClass  rectButton = myUI.addRadioButton("None", 5, 110, "group1");
  myUI.addRadioButton("draw rect", 5, 140, "group1");
  myUI.addRadioButton("draw circle", 5, 170, "group1");
  myUI.addRadioButton("draw line", 5, 200, "group1");
  myUI.addRadioButton("select", 5, 230, "group1");
  rectButton.selected = true;
  toolMode = rectButton.UILabel;
  
  
  myUI.addPlainButton("Greyscale", 5,320);
  myUI.addPlainButton("Contrast", 5,350);
  myUI.addPlainButton("Brightness", 5,380);
  myUI.addSlider("Hue", 5,410);
  myUI.addSlider("Saturation", 5,440);
  myUI.setSliderValue("Saturation", 1);
  
  myUI.addSlider("Red", 5, 620);
  myUI.setSliderValue("Red", 0.5);
  myUI.addSlider("Green", 5, 650);
  myUI.setSliderValue("Green", 0.5);
  myUI.addSlider("Blue", 5, 680);
  myUI.setSliderValue("Blue", 0.5);
  
  myUI.addCanvas(120, 50, (5*width)/6, (5*height)/6);
}


void draw(){
  background(200);
  
  if (myImage != null)
  {
    image(myImage, 120, 50);
  }
  

 
  // and draw your content afterwrds
  if( outImage != null ){
    myImage = outImage.copy();
    image(myImage, 120, 50);
  
  }
  
  fill(red, green, blue);
  rect(5, 710, 102, 102);
  
  drawingList.deleteMe();
  drawingList.setColour(red, green, blue);
  drawingList.drawMe();
  
  // you MUST update the UI in draw() like so
  myUI.update();
  
}


// you MUST have this function declared.. it receives all the user-interface events
void handleUIEvent(UIEventData uied){
  
  // here we just get the event to print its self
  // with "verbosity" set to 1, (1 = low, 3 = high, 0 = do not print anything)
  uied.print(2);
  
  
  
  if(uied.eventIsFromWidget("File")){
    if( uied.menuItem.equals("New")){
      myUI.addCanvas(120, 50, (5*width)/6, (5*height)/6);
      myImage = null;
      outImage = null;
      
    }
  }
  
  if(uied.eventIsFromWidget("File")){
    if( uied.menuItem.equals("Open")){
      myUI.openFileLoadDialog("load an image");
      outImage = null;
      image = true;
    }
  }
  
  if(uied.eventIsFromWidget("File")){
    if( uied.menuItem.equals("Save")){
      myUI.openFileSaveDialog("save an image");
    }
  }
  
  
  
  if(uied.eventIsFromWidget("Filter")){
    if( uied.menuItem.equals("Blur")){
      if(myImage != null) {
        outImage = createImage(myImage.width,myImage.height,RGB);
        myImage.loadPixels();
    
        int matrixSize = 3;
        for(int y = 0; y < myImage.height; y++){
          for(int x = 0; x < myImage.width; x++){
      
            color c = convolution(x, y, blurMatrix, matrixSize, myImage);
      
            outImage.set(x,y,c);
      
          }
        }
      }
    }
  }
  
  if(uied.eventIsFromWidget("Filter")){
    if( uied.menuItem.equals("Sharpen")){
      if(myImage != null) {
        outImage = createImage(myImage.width,myImage.height,RGB);
        myImage.loadPixels();
        int matrixSize = 3;
        for(int y = 0; y < myImage.height; y++){
          for(int x = 0; x < myImage.width; x++){
      
            color c = convolution(x, y, sharpenMatrix, matrixSize, myImage);
      
            outImage.set(x,y,c);
      
          }
        }
      }
    }
  }
  
  if(uied.eventIsFromWidget("Filter")){
    if( uied.menuItem.equals("Find Edges")){
      if(myImage != null) {
        outImage = createImage(myImage.width,myImage.height,RGB);
        myImage.loadPixels();
    
        int matrixSize = 3;
        for(int y = 0; y < myImage.height; y++){
          for(int x = 0; x < myImage.width; x++){
      
            color c = convolution(x, y, edgeMatrix, matrixSize, myImage);
      
            outImage.set(x,y,c);
      
          }
        }
      }
    }
  }
  
  if(uied.eventIsFromWidget("Filter")){
    if( uied.menuItem.equals("Emboss")){
      if(myImage != null) {
        outImage = createImage(myImage.width,myImage.height,RGB);
        myImage.loadPixels();
    
        int matrixSize = 3;
        for(int y = 0; y < myImage.height; y++){
          for(int x = 0; x < myImage.width; x++){
      
            color c = convolution(x, y, embossMatrix, matrixSize, myImage);
      
            outImage.set(x,y,c);
      
          }
        }
      }
    }
  }
  
  if(uied.eventIsFromWidget("Filter")){
    if( uied.menuItem.equals("Unsharp Mask")){
      if(myImage != null) {
        outImage = createImage(myImage.width,myImage.height,RGB);
        myImage.loadPixels();
    
        int matrixSize = 5;
        for(int y = 0; y < myImage.height; y++){
          for(int x = 0; x < myImage.width; x++){
      
            color c = convolution(x, y, unsharpMatrix, matrixSize, myImage);
      
            outImage.set(x,y,c);
      
          }
        }
      }
    }
  }
  
  
  
  
  //this catches the file load information when the file load dialogue's "open" button is hit
  if(uied.eventIsFromWidget("fileLoadDialog")){
    myImage = loadImage(uied.fileSelection);
    myUI.setSliderValue("Contrast", 0);
    myUI.setSliderValue("Brightness", 0);
    myUI.setSliderValue("Hue", 0);
    myUI.setSliderValue("Saturation", 1);
  }
  
  //this catches the file save information when the file save dialogue's "save" button is hit
  if(uied.eventIsFromWidget("fileSaveDialog")){
    myImage.save(uied.fileSelection);
  }
  
  if(uied.eventIsFromWidget("Line Weight")){
     weight = 10 * myUI.getSliderValue("Red");
  }
  if(uied.eventIsFromWidget("Red")){
    red = 255 * myUI.getSliderValue("Red");
  }
  if(uied.eventIsFromWidget("Green")){
    green = 255 * myUI.getSliderValue("Green");
  }
  if(uied.eventIsFromWidget("Blue")){
    blue = 255 * myUI.getSliderValue("Blue");
  }
  
  if(uied.eventIsFromWidget("Greyscale")){
    if(myImage != null){
      outImage = createImage(myImage.width,myImage.height,RGB);
      myImage.loadPixels();
      for (int y = 0; y < myImage.height; y++) {
      
        for (int x = 0; x < myImage.width; x++){
          
          color thisPix = myImage.get(x,y);
          int r = (int) red(thisPix);
          int g = (int) green(thisPix);
          int b = (int) blue(thisPix);
          float grey = (0.2126*r + 0.7152*g + 0.0722*b);
          color newColour = color(grey, grey, grey);
          outImage.set(x,y, newColour);
        }
      }
    }
  }
  
  if(uied.eventIsFromWidget("Contrast")){    
    if (myImage != null) {
      int[] lut = makeFunctionLUT("contrast",0,0);
      
      outImage = applyPointProcessing(lut,lut,lut, myImage);
    }
  }
  
  if(uied.eventIsFromWidget("Brightness")){    
    if (myImage != null) {
      int[] lut = makeFunctionLUT("bright", 2,0);
      
      outImage = applyPointProcessing(lut,lut,lut, myImage);
    }
  }
  
  if(uied.eventIsFromWidget("Hue")){
    float slider = myUI.getSliderValue("Hue");
    slider *= 10;
    if (myImage != null) {
      outImage = createImage(myImage.width,myImage.height,RGB);
      myImage.loadPixels();
      for (int y = 0; y < myImage.height; y++) {
      
        for (int x = 0; x < myImage.width; x++){
          
          color thisPix = myImage.get(x,y);
          int r = (int) (red(thisPix));
          int g = (int) (green(thisPix));
          int b = (int) (blue(thisPix));
          
          float[] hsv = RGBtoHSV(r,g,b);
          float hue = hsv[0];
          float sat = hsv[1];
          float val = hsv[2];
          
          
          constrain(hue, 0, 360);
          hue += slider;
          
          if( hue < 0 ) hue += 360;
          if( hue > 360 ) hue -= 360;
          
          color newRGB =   HSVtoRGB(hue,  sat,  val);
          outImage.set(x,y, newRGB);
        }
      
      }
    }
  }
  
  if(uied.eventIsFromWidget("Saturation")){
    float slider = myUI.getSliderValue("Saturation");
    if (myImage != null) {
      outImage = createImage(myImage.width,myImage.height,RGB);
      myImage.loadPixels();
      for (int y = 0; y < myImage.height; y++) {
      
        for (int x = 0; x < myImage.width; x++){
          
          color thisPix = myImage.get(x,y);
          int r = (int) (red(thisPix));
          int g = (int) (green(thisPix));
          int b = (int) (blue(thisPix));
          
          float[] hsv = RGBtoHSV(r,g,b);
          float hue = hsv[0];
          float sat = hsv[1];
          float val = hsv[2];
          
          constrain(sat, 0.01, 1);
          sat = slider;
          
          if( sat < 0.01 ) sat += 1;
          if( sat > 1 ) hue -= 1;
          
          color newRGB =   HSVtoRGB(hue,  sat,  val);
          outImage.set(x,y, newRGB);
        }
      
      }
    }
  }
  
  if(uied.uiComponentType == "RadioButton"){
    toolMode = uied.uiLabel;
    return;
  }
  
  if(uied.eventIsFromWidget("canvas")==false) return;
  PVector p =  new PVector(uied.mousex, uied.mousey);
  
  if( toolMode.contains("draw") ) {    
     drawingList.handleMouseDrawEvent(toolMode,uied.mouseEventType, p);
  }
   
  
  if( toolMode.equals("select") ) {    
      drawingList.trySelect(uied.mouseEventType, p);
    }
  
  
}
