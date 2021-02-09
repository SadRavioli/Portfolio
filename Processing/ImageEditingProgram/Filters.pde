float[][] edgeMatrix = { { 0,  -2,  0 },
                          { -2,  8, -2 },
                          { 0,  -2,  0 } }; 
                     
float[][] blurMatrix = {  {0.1,  0.1,  0.1 },
                           {0.1,  0.1,  0.1 },
                           {0.1,  0.1,  0.1 } };                      

float[][] sharpenMatrix = {  { 0, -1, 0 },
                              {-1, 5, -1 },
                              { 0, -1, 0 } };  
                         
float[][] embossMatrix = {  { -2, -1, 0 },
                            { -1, 1, 1 },
                            { 0, 1, 2 } };
                            
float[][] unsharpMatrix = {  { -0.00390625, -0.015625, -0.0234375, -0.015625, -0.00390625 },
                            { -0.015625, -0.0625, -0.09375, -0.0625, -0.015625 },
                            { -0.0234375, -0.09375, 1.859375, -0.09375, -0.0234375 },
                            { -0.015625, -0.0625, -0.09375, -0.0625, -0.015625 },
                            { -0.00390625, -0.015625, -0.0234375, -0.015625, -0.00390625 } };  
                                  
color convolution(int x, int y, float[][] matrix, int matrixsize, PImage img)
{
  float rtotal = 0.0;
  float gtotal = 0.0;
  float btotal = 0.0;
  int offset = matrixsize / 2;
  for (int i = 0; i < matrixsize; i++){
    for (int j= 0; j < matrixsize; j++){
      // What pixel are we testing
      int xloc = x+i-offset;
      int yloc = y+j-offset;
      int loc = xloc + img.width*yloc;
      // Make sure we haven't walked off our image, we could do better here
      loc = constrain(loc,0,img.pixels.length-1);
      // Calculate the convolution
      rtotal += (red(img.pixels[loc]) * matrix[i][j]);
      gtotal += (green(img.pixels[loc]) * matrix[i][j]);
      btotal += (blue(img.pixels[loc]) * matrix[i][j]);
    }
  }
  // Make sure RGB is within range
  rtotal = constrain(rtotal, 0, 255);
  gtotal = constrain(gtotal, 0, 255);
  btotal = constrain(btotal, 0, 255);
  // Return the resulting color
  return color(rtotal, gtotal, btotal);
}
