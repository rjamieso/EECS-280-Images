// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {


  int width = Image_width(img);
  int height = Image_height(img);

 
  Image *aux = new Image;
  Image_init(aux, height, width); 


  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

 
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

 
  int width = Image_width(img);
  int height = Image_height(img);


  Image *aux = new Image;
  Image_init(aux, height, width); 


  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }


  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
 
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  Matrix_init(energy,Image_width(img),Image_height(img));

  Matrix_fill(energy,0);

  for(int row = 1; row < ((Matrix_height(energy)) - 1); ++row){
    for(int col = 1; col < ((Matrix_width(energy)) - 1); ++col){
        Pixel N = Image_get_pixel(img,(row - 1),col);
        Pixel S = Image_get_pixel(img,(row + 1),col);
        Pixel E = Image_get_pixel(img,row,(col + 1));
        Pixel W = Image_get_pixel(img,row,(col - 1));
        *(Matrix_at(energy,row,col)) = squared_difference(N,S) + squared_difference(E,W); 
    }
  }

  int max = Matrix_max(energy);
  Matrix_fill_border(energy,max);

}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  Matrix_init(cost,Matrix_width(energy),Matrix_height(energy));
  const int leftbordercol = 0;
  const int rightbordercol = ((Matrix_width(cost)) - 1);

  for(int col = 0; col < (Matrix_width(cost)); ++col){
    *(Matrix_at(cost,0,col)) = *(Matrix_at(energy,0,col));
  }

  for(int row = 1; row < (Matrix_height(cost)); ++row){
    for(int col = 0; col < (Matrix_width(cost)); ++col){
      if(col == leftbordercol){
        int plachold1 = Matrix_min_value_in_row(cost,(row - 1),col,(col + 2));
        *(Matrix_at(cost,row,col)) = *(Matrix_at(energy,row,col)) + plachold1; 
      }
      if(col == rightbordercol){
        int plachold2 = Matrix_min_value_in_row(cost,(row - 1),(col - 1),(col + 1));
        *(Matrix_at(cost,row,col)) = *(Matrix_at(energy,row,col)) + plachold2;
      }
      if((col != leftbordercol) && (col != rightbordercol)){
        int plachold3 = Matrix_min_value_in_row(cost,(row - 1),(col - 1),(col + 2));
        *(Matrix_at(cost,row,col)) = *(Matrix_at(energy,row,col)) + plachold3;
      }
    }
  }

}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {

  int startcol = 0;
  int endcol = (Matrix_width(cost));
  int initrow = Matrix_height(cost) - 1;

  int initmin = Matrix_column_of_min_value_in_row(cost,initrow,startcol,endcol); 
  
  int tracker = (Matrix_height(cost)) - 1;
  seam[tracker--] = initmin;
  
  for(int row = ((Matrix_height(cost)) - 2); row >= 0; --row){

    if(initmin == ((Matrix_width(cost)) - 1)){ 
      startcol = (initmin - 1);
      endcol = ((initmin) + 1);
    }
    else if(!initmin){ 
      startcol = initmin;
      endcol = (initmin + 2);
    }
    else{
      startcol = ((initmin) - 1);
      endcol = ((initmin) + 2);
    }
    initmin = Matrix_column_of_min_value_in_row(cost,row,startcol,endcol); 
    seam[tracker] = initmin;
    --tracker;
  }

}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  Image *aux = new Image;
  Image_init(aux,((Image_width(img)) - 1),Image_height(img));
  int coltracker = 0;

  for(int row = 0; row < (Image_height(img)); ++row){
    for(int col = 0; col < (Image_width(img)); ++col){
       if(col != seam[row]){
        Image_set_pixel(aux,row,col,(Image_get_pixel(img,row,coltracker)));
      }
      else{
        coltracker++;
        Image_set_pixel(aux,row,col,(Image_get_pixel(img,row,coltracker)));
      }
      coltracker++;
    }
    coltracker = 0;
  }
  *img = *aux;
  delete aux;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {

  for(int col = (Image_width(img)); col > newWidth; --col){

    Matrix *energymat = new Matrix;
    compute_energy_matrix(img,energymat);


    Matrix *costmat = new Matrix;
    compute_vertical_cost_matrix(energymat,costmat);


    int placseam[MAX_MATRIX_HEIGHT];
    find_minimal_vertical_seam(costmat,placseam);

 
    remove_vertical_seam(img,placseam);

    delete energymat;
    delete costmat;
  }

}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  
  rotate_left(img);
  seam_carve_width(img,newHeight);
  rotate_right(img);

}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {

  seam_carve_width(img,newWidth);
  seam_carve_height(img,newHeight);
  
}

