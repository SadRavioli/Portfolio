SimSphere ball;

class Ball {

  Timer timer = new Timer();
  
  PVector location = new PVector(0, 0, 0);
  PVector velocity = new PVector(0, 0, 0);
  PVector acceleration = new PVector(0, 0, 0);
  PVector gravity = new PVector(0, 981, 0);
  private float mass = 1;
  float radius;
  float resistanceAmount = 0.1;
  float elapsedTime;
  float gravMult = 1;
  int lod;
  int boundary;
  
  float r = 0;
  float g = 0;
  float b = 0;

  Ball() {
  }
  
  
  
  void setMass(float m){
    // converts mass into surface area
    mass = m;
    radius = 60 * sqrt( mass / PI );
    
  }
  
  
  void update() {
    
    setMass(mass);
    
    elapsedTime = timer.getElapsedTime();

    addForce(gravity.mult(gravMult));
    
    
    checkForBounceOffEdges();
    
    applyResistance();
    
    // scale the acceleration by time elapsed
    PVector accelerationOverTime = PVector.mult(acceleration, 0.016);
    velocity.add(accelerationOverTime);
    
    // scale the movement by time elapsed
    PVector distanceMoved = PVector.mult(velocity, elapsedTime);
    location.add(distanceMoved);
    
    // now that you have "used" your accleration it needs to be re-zeroed
    acceleration = new PVector(0, 0, 0);
    gravity = new PVector(0, 981, 0);    
    
  }
  
  void addForce(PVector f){
    // use F= MA or (A = F/M) to calculated acceleration caused by force
    PVector accelerationEffectOfForce = PVector.div(f, mass);
    acceleration.add(accelerationEffectOfForce);
  }

  void display() {
    ball = new SimSphere(vec(location.x, location.y, location.z), radius);
    ball.setLevelOfDetail(lod);
    fill(r, g, b); 
    ball.drawMe();
  }
  
 
  
  void applyResistance(){
    // modify the acceleration by applying
    // a force in the opposite direction to its velociity
    // to simulate friction
    PVector reverseForce = PVector.mult( velocity, -resistance);
    addForce(reverseForce);
  }
  
  ////////////////////////////////////////////////////////////
  // new collision code
  // call collisionCheck just before or after update in the "main" tab
  
  boolean collisionCheck(Ball otherBall){
    
    if(otherBall == this) return false; // can't collide with yourself!
    
    float distance = otherBall.location.dist(this.location);
    float minDist = otherBall.radius + this.radius;
    if (distance < minDist)  return true;
    return false;
  }
  
  
  void collisionResponse(Ball otherBall) {
    // based on 
    // https://en.wikipedia.org/wiki/Elastic_collision
    
     if(otherBall == this) return; // can't collide with yourself!
     
     
    PVector v1 = this.velocity;
    PVector v2 = otherBall.velocity;
    
    PVector cen1 = this.location;
    PVector cen2 = otherBall.location;
    
    // calculate v1New, the new velocity of this mover
    float massPart1 = 2*otherBall.mass / (this.mass + otherBall.mass);
    PVector v1subv2 = PVector.sub(v1,v2);
    PVector cen1subCen2 = PVector.sub(cen1,cen2);
    float topBit1 = v1subv2.dot(cen1subCen2);
    float bottomBit1 = cen1subCen2.mag()*cen1subCen2.mag();
    
    float multiplyer1 = massPart1 * (topBit1/bottomBit1);
    PVector changeV1 = PVector.mult(cen1subCen2, multiplyer1);
    
    PVector v1New = PVector.sub(v1,changeV1);
    
    // calculate v2New, the new velocity of other mover
    float massPart2 = 2*this.mass/(this.mass + otherBall.mass);
    PVector v2subv1 = PVector.sub(v2,v1);
    PVector cen2subCen1 = PVector.sub(cen2,cen1);
    float topBit2 = v2subv1.dot(cen2subCen1);
    float bottomBit2 = cen2subCen1.mag()*cen2subCen1.mag();
    
    float multiplyer2 = massPart2 * (topBit2/bottomBit2);
    PVector changeV2 = PVector.mult(cen2subCen1, multiplyer2);
    
    PVector v2New = PVector.sub(v2,changeV2);
    
    this.velocity = v1New;
    otherBall.velocity = v2New;
    ensureNoOverlap(otherBall);
  }
  
 
  void ensureNoOverlap(Ball otherBall){
    // the purpose of this method is to avoid Movers sticking together:
    // if they are overlapping it moves this Mover directly away from the other Mover to ensure
    // they are not still overlapping come the next collision check 
    
    
    PVector cen1 = this.location;
    PVector cen2 = otherBall.location;
    
    float cumulativeRadii = (this.radius + otherBall.radius)+2; // extra fudge factor
    float distanceBetween = cen1.dist(cen2);
    
    float overlap = cumulativeRadii - distanceBetween;
    if(overlap > 0){
      // move this away from other
      PVector vectorAwayFromOtherNormalized = PVector.sub(cen1, cen2).normalize();
      PVector amountToMove = PVector.mult(vectorAwayFromOtherNormalized, overlap);
      this.location.add(amountToMove);
    }
  }
  
  
  
  void checkForBounceOffEdges() {
    
    if (location.x > boundary - ball.radius || location.x < -boundary + ball.radius) {
      velocity.x *= -1;
      if (location.x > boundary - ball.radius) {
        location.x = boundary - ball.radius;
      }
      if (location.x < -boundary + ball.radius) {
        location.x = -boundary + ball.radius;
      }
    }
    if (location.y > boundary - ball.radius || location.y < -boundary + ball.radius) {
      velocity.y *= -1;
      if (location.y > boundary - ball.radius) {
        location.y = boundary - ball.radius;
      }
      if (location.y < -boundary + ball.radius) {
        location.y = -boundary + ball.radius;
      }
    }
    if(location.z > boundary - ball.radius || location.z < -boundary + ball.radius) {
      velocity.z *= -1;
      if (location.z > boundary - ball.radius) {
        location.z = boundary - ball.radius;
      }
      if (location.z < -boundary + ball.radius) {
        location.z = -boundary + ball.radius;
      }
    }
  }
}
