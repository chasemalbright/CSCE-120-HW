#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"
  
using namespace std;

// TODO Write this function
int energy(const Pixel *const*image, int col, int row, int width, int height){

  int energyPixel = 0;

  // calculate energy in X direction
  int gradient_x = 0;
  
  if (col == 0){ // border left
    gradient_x = pow(image[col+1][row].r-image[width-1][row].r,2) + pow(image[col+1][row].g-image[width-1][row].g,2) + pow(image[col+1][row].b-image[width-1][row].b,2);
  } else if(col == width-1){ // border right
    gradient_x = pow(image[0][row].r - image[col-1][row].r,2) + pow(image[0][row].g - image[col-1][row].g,2) + pow(image[0][row].b - image[col-1][row].b,2);
  } else { // non border pixels
    gradient_x = pow(image[col+1][row].r - image[col-1][row].r,2) + pow(image[col+1][row].g - image[col-1][row].g,2) + pow(image[col+1][row].b - image[col-1][row].b,2);
  }

  // calculate energy in y direction
  int gradient_y = 0;

  if (row == 0){ // top border
    gradient_y = pow(image[col][height-1].r - image[col][row+1].r,2) + pow(image[col][height-1].g - image[col][row+1].g,2) + pow(image[col][height-1].b - image[col][row+1].b,2);
  } else if (row == height-1){ // bottom border
    gradient_y = pow(image[col][row-1].r - image[col][0].r,2) + pow(image[col][row-1].g - image[col][0].g,2) + pow(image[col][row-1].b - image[col][0].b,2);
  } else { // non border pixels
    gradient_y = pow(image[col][row+1].r - image[col][row-1].r,2) + pow(image[col][row+1].g - image[col][row-1].g,2) + pow(image[col][row+1].b - image[col][row-1].b,2);
  }
  
  energyPixel = abs(gradient_y) + abs(gradient_x);

  return energyPixel;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
  //first set seam with start col
  seam[0] = start_col;

  // begin with the val at pix in start_col
  int totalEnergy = energy(image,start_col,0,width,height);

  // think about it as if you flipped array over and can only move forward(down on pic)
  // my options are to either go left rigth or center(straight down)

  int leftpx;     //[   ][STR][   ][   ]
  int rightpx;    //[LFT][CNT][RHT][   ]   // follow this schematic when going down a level
  int centerpx;   //[   ][   ][   ][   ]

  //start loop at 1 bec we alr set total to the energy of px in [start_col][0]
  for (int i = 1; i < height; i++) {
    if (start_col==0){ //left border
      centerpx = energy(image,start_col,i,width,height);
      rightpx = energy(image,start_col+1,i,width,height);
      //left is not possible so give it highest possible int so that it will never be chosen
      leftpx = INT32_MAX;
    } else if(start_col == width-1){ // right border
      centerpx = energy(image,start_col,i,width,height);
      leftpx = energy(image,start_col-1,i,width,height);
      //right is not possible out of bounds so give it highest again
      rightpx = INT32_MAX;
    } else { // happy middle cases :)
      centerpx = energy(image,start_col,i,width,height);
      leftpx = energy(image,start_col-1,i,width,height);
      rightpx = energy(image,start_col+1,i,width,height);
    }

    // begin logic for choosing direction
    if (leftpx < rightpx && leftpx < centerpx){
      totalEnergy += leftpx; // add in the min energy
      seam[i] = start_col -1; // add col to the array
      start_col = start_col-1; // minus to indicate col location for next loop
    } else if (centerpx < rightpx && centerpx < leftpx) {
      totalEnergy += centerpx;
      seam[i] = start_col; //dont increm or dcrem bc it is good
    } else if (rightpx < centerpx && rightpx < leftpx){
      totalEnergy += rightpx;
      seam[i] = start_col + 1;
      start_col = start_col +1; // increm bc it is in right col
    } else if (leftpx == centerpx && leftpx < rightpx) {
      // left and center are = , so we decide to go forward or straight down
      totalEnergy += centerpx;
      seam[i] = start_col;
    } else if (rightpx == centerpx && centerpx < leftpx){ // check***
      // rigth and center are =, again prefer to go down
      totalEnergy += centerpx;
      seam[i] = start_col;
    } else if (centerpx == rightpx && leftpx == centerpx){
      // all = so go down
      totalEnergy += centerpx;
      seam[i] = start_col;
    } else if (rightpx == leftpx && rightpx < centerpx && leftpx < centerpx){
      // left and rigth = and less than center i am right handed so i guess ill go right
      totalEnergy += rightpx;
      seam[i] = start_col + 1;
      start_col = start_col +1;
    }

  }

  return totalEnergy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  // function params give us array[][] | pass by ref width? | heigth | array[]
  // nested for loops??
  Pixel pixelHolder; // we need a place to store itermediate px values

  for (int row = 0; row < height; row++){ // traverse down each row
    // pixelHolder[0] = image[verticalSeam[row]][row].r;
    // pixelHolder[1] = image[verticalSeam[row]][row].g;  // store px color values for thr beginning px
    // pixelHolder[2] = image[verticalSeam[row]][row].b;
    pixelHolder = image[verticalSeam[row]][row];

    for (int col = verticalSeam[row]; col < width - 1; col++){ // traverse through each column# in array vertSeam
      image[col][row] = image[col + 1][row]; // this is the method for "remving" ** need to check
    }

    // image[width - 1][row].r = pixelHolder[0];  // replace with stored values 
    // image[width - 1][row].g = pixelHolder[1];
    // image[width - 1][row].b = pixelHolder[2];
    image[width - 1][row] = pixelHolder;

  }
  width--;

}

// TODO Write this function for extra credit
// int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
// {
//   return 0;
// }

// TODO Write this function for extra credit
// void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
// {
  
// }

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

// int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
// {
//   // initialize minSeam and minDistance to seam starting at first row (index 0)
//   int *minSeam = new int[width]{0};
//   int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

//   int *candidateSeam = new int[width]{0};
//   int candidateDistance = -1; // invalid distance

//   // start at second row (index 1) since we initialized with first row (index 0)
//   for (int row = 1; row < height; ++row)
//   {
//     candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

//     if (candidateDistance < minDistance)
//     { // new minimum
//       //  swap min and candidate seams
//       minDistance = candidateDistance;
//       int* temp = candidateSeam;
//       candidateSeam = minSeam;
//       minSeam = temp;
//     }
//   }

//     // clean up 
//   delete [] candidateSeam;

//   return minSeam;
// }

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}