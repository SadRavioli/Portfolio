SimpleUI ui;

SimBox box;
SimSurfaceMesh floor;

SimObjectManager simObjectManager = new SimObjectManager();
SimCamera myCamera;

int nonePlanetObjects = 0;
ArrayList<Ball> balls = new ArrayList<Ball>();

float gravityMultiplier;
float resistance;
float noOfBalls;
float minMass;
float maxMass;
float lod;
float boxSize;

boolean started;


void setup(){
  size(1920, 1080, P3D);
  
  frameRate(165);
  
  gravityMultiplier = 1;
  resistance = 0.1;
  noOfBalls = 20;
  lod = 10;
  boxSize = 500;
  
  ////////////////////////////
  // create the SimCamera
  myCamera = new SimCamera();
  myCamera.setPositionAndLookat(vec(800, -100, 10),vec(0, 0, 0));
  myCamera.setHUDArea(50, 100, 250, 420);
  
  box = new SimBox(vec(boxSize, boxSize, boxSize), vec(0, 0, 0));
  box.setTransformAbs(1, 0, 0, 0, vec(-boxSize/2, -boxSize/2, -boxSize/2));
  simObjectManager.addSimObject(box, "box");
  
  floor = new SimSurfaceMesh(1, 1, boxSize);
  floor.setTransformAbs(1, 0, 0, 0, vec(-boxSize/2, boxSize/2, -boxSize/2));
  
  ui = new SimpleUI();
  //call Simple UI library
  
  ui.addPlainButton("Start", 70, 120);
  ui.addPlainButton("Reset", 150, 120);
  ui.addSlider("Gravity", 70, 170);
  ui.addSlider("No. Balls", 70, 220);
  ui.addSlider("Resistance", 70, 270);
  ui.addSlider("Quality", 70, 320);
  ui.addSlider("Box Size", 70, 370);
  
  ui.setSliderValue("Gravity", 0.2);
  ui.setSliderValue("No. Balls", 0.07);
  ui.setSliderValue("Resistance", resistance);
  ui.setSliderValue("Quality", 0.2);
  ui.setSliderValue("Box Size", 0.5);
  
}

void draw(){
  background(130);
  lights();
  noStroke();
  
  for(int n = 0; n < balls.size(); n++){
    Ball thisBall = balls.get(n);
    Ball otherBall = findCollisionWithOtherBall(thisBall, n);

    if(otherBall != null) {
      // if this mover collides with some other mover then...
      thisBall.collisionResponse(otherBall);
    }
    
    thisBall.gravMult = gravityMultiplier;
    thisBall.resistanceAmount = resistance;
    thisBall.lod = int(lod);
    thisBall.boundary = int(boxSize/2);
    
    thisBall.display();
    thisBall.update();
    
  }
  
  stroke(255);
  noFill();
  if (!(boxSize < 200)) {
    box = new SimBox(vec(boxSize, boxSize, boxSize), vec(0, 0, 0));
    box.setTransformAbs(1, 0, 0, 0, vec(-boxSize/2, -boxSize/2, -boxSize/2));
    floor = new SimSurfaceMesh(1, 1, boxSize);
    floor.setTransformAbs(1, 0, 0, 0, vec(-boxSize/2, boxSize/2, -boxSize/2));
  } else {
    boxSize = 200;
  }
  box.drawMe();
  fill(50, 50, 50);
  noStroke();
  floor.drawMe();
  
  stroke(255);
  myCamera.startDrawHUD();
  fill(50);
  textSize(30);
  text("Gravity Multiplier: " + int(gravityMultiplier * 100) + "%", 1500, 120);
  text("Number Of Balls: " + int(noOfBalls), 1500, 170);
  text("Resistance: " + int(resistance * 100) + "%", 1500, 220);
  text("Ball Quality: " + int(lod), 1500, 270);
  text("Box Size: " + int(boxSize), 1500, 320);
  textSize(18);
  text("FPS: " + int(frameRate), 50, 50);
  ui.update();
  myCamera.endDrawHUD();
  myCamera.update();
  
  

}

Ball findCollisionWithOtherBall(Ball thisBall, int thisBallListPos){
    // Returns null if no collision found, otherwise returns the other mover this one
    // is colliding with
    // This is optimised to only search for collisions with movers of a greater index in the otherMovers list
    // as lower ones have already calculated collision with this Ball
    for (int n = thisBallListPos + 1; n < balls.size(); n++) {
      Ball otherBall = balls.get(n);
      
      if( thisBall.collisionCheck(otherBall) ) return otherBall;
    }

    // if no collisions have been found return null;
    return null;

}

void spawnBalls(){
  nonePlanetObjects = simObjectManager.getNumSimObjects();
  for(int n = 0; n < int(noOfBalls); n++){
    Ball newBall = new Ball();
    newBall.location.x = random(-boxSize/2 + 30, boxSize/2 - 30);
    newBall.location.y = random(-boxSize/2 + 30, boxSize/2 - 30);
    newBall.location.z = random(-boxSize/2 + 30, boxSize/2 - 30);
    newBall.velocity = PVector.random3D();
    newBall.setMass(random(0.2, 2));
    newBall.r = random(0, 255);
    newBall.g = random(0, 255);
    newBall.b = random(0, 255);
    balls.add(newBall);    
  }
}

void handleUIEvent(UIEventData uied) 
{  
  gravityMultiplier = ui.getSliderValue("Gravity") * 5;
  noOfBalls = ui.getSliderValue("No. Balls") * 300;
  resistance = ui.getSliderValue("Resistance");
  lod = ui.getSliderValue("Quality") * 50;
  boxSize = ui.getSliderValue("Box Size") * 1000;
  //sliders for balloon mass and chosen force values

  if (uied.eventIsFromWidget("Start") && started == false) {
      spawnBalls();
      started = true;
  }
  
  if (uied.eventIsFromWidget("Reset")) {
      balls.clear();
      started = false;
  }
  
}
