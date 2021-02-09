public void greyScale(PImage img) {
  image(img, 230, 80);
  filter(GRAY);
}

float[] RGBtoHSV(float r, float g, float b){
  
  
  float minRGB = min( r, g, b );
  float maxRGB = max( r, g, b );
    
    
  float value = maxRGB/255.0; 
  float delta = maxRGB - minRGB;
  float hue = 0;
  float saturation;
  
  float[] returnVals = {0f,0f,0f};
  

   if( maxRGB != 0 ) {
    // saturation is the difference between the smallest R,G or B value, and the biggest
      saturation = delta / maxRGB; }
   else { // it’s black, so we don’t know the hue
       return returnVals;
       }
       
  if(delta == 0){ 
         hue = 0;
        }
   else {
    // now work out the hue by finding out where it lies on the spectrum
      if( b == maxRGB ) hue = 4 + ( r - g ) / delta;   // between magenta, blue, cyan
      if( g == maxRGB ) hue = 2 + ( b - r ) / delta;   // between cyan, green, yellow
      if( r == maxRGB ) hue = ( g - b ) / delta;       // between yellow, Red, magenta
    }
  // the above produce a hue in the range -6...6, 
  // where 0 is magenta, 1 is red, 2 is yellow, 3 is green, 4 is cyan, 5 is blue and 6 is back to magenta 
  // Multiply the above by 60 to give degrees
   hue = hue * 60;
   if( hue < 0 ) hue += 360;
   
   returnVals[0] = hue;
   returnVals[1] = saturation;
   returnVals[2] = value;
   
   return returnVals;
}

// HSV to RGB
//
//
// expects values in range hue = [0,360], saturation = [0,1], value = [0,1]
color HSVtoRGB(float hue, float sat, float val)
{
  
    hue = hue/360.0;
    int h = (int)(hue * 6);
    float f = hue * 6 - h;
    float p = val * (1 - sat);
    float q = val * (1 - f * sat);
    float t = val * (1 - (1 - f) * sat);

    float r,g,b;


    switch (h) {
      case 0: r = val; g = t; b = p; break;
      case 1: r = q; g = val; b = p; break;
      case 2: r = p; g = val; b = t; break;
      case 3: r = p; g = q; b = val; break;
      case 4: r = t; g = p; b = val; break;
      case 5: r = val; g = p; b = q; break;
      default: r = val; g = t; b = p;
    }
    
    return color(r*255,g*255,b*255);
}

int[] makeFunctionLUT(String functionName, float parameter1, float parameter2){
  
  int[] lut = new int[256];
  for(int n = 0; n < 256; n++) {
    
    float p = n/255.0f;  // ranges between 0...1
    float val = 0;
    
    switch(functionName) {
      case "bright":
        val = gammaCurve(p, parameter1);
        println(val);
      case "contrast":
        val = sigmoidCurve(p);
      
      }// end of switch statement

   
    lut[n] = (int)(val*255);
  }
  
  return lut;
}

PImage applyPointProcessing(int[] redLUT, int[] greenLUT, int[] blueLUT, PImage inputImage){
  PImage outputImage = createImage(inputImage.width,inputImage.height,RGB);
  
  
  inputImage.loadPixels();
  outputImage.loadPixels();
  int numPixels = inputImage.width*inputImage.height;
  for(int n = 0; n < numPixels; n++){
    
    color c = inputImage.pixels[n];
    
    int r = (int)red(c);
    int g = (int)green(c);
    int b = (int)blue(c);
    
    r = redLUT[r];
    g = greenLUT[g];
    b = blueLUT[b];
    
    outputImage.pixels[n] = color(r,g,b);
    
    
  }
  
  return outputImage;
}
