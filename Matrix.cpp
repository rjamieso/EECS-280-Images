// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include <iostream>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  mat->height = height;
  mat->width = width;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << Matrix_width(mat) << " " << Matrix_height(mat) << '\n';
  int col = 0;
  for(int row = 0; row < Matrix_height(mat); ++row){
    for(int tempcol = 0; tempcol < Matrix_width(mat); ++tempcol){
      os << mat->data[col] << " "; 
      ++col;
    }
    os << '\n';
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  int matrixwidth = mat->width;
  return matrixwidth;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  int matrixheight = mat->height;
  return matrixheight;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  int indexgap = ptr - mat->data;
  int row = indexgap / (Matrix_width(mat));
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  int indexgap = ptr - mat->data;
  int column = indexgap % (Matrix_width(mat)); 
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  int indexer = ((Matrix_width(mat)) * row) + column;
  int *ptr = &mat->data[indexer];
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  int indexer = ((Matrix_width(mat)) * row) + column;
  const int *ptr = &mat->data[indexer]; 
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for(int row = 0; row < Matrix_height(mat); ++row){
    for(int col = 0; col < Matrix_width(mat); ++col){
      *Matrix_at(mat,row,col) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int firstrow = 0;
  int lastrow = (Matrix_height(mat)) - 1;
  int firstcol = 0;
  int lastcol = (Matrix_width(mat)) - 1;

  for(int row = 0; row < Matrix_height(mat); ++row){
    for(int col = 0; col < Matrix_width(mat); ++col){
     if((row == firstrow) || (row == lastrow)){
      *Matrix_at(mat,row,col) = value;
     }
     if((col == firstcol) || (col == lastcol)){
      *Matrix_at(mat,row,col) = value;
     }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = *Matrix_at(mat,0,0);
  for(int row = 0; row < Matrix_height(mat); ++row){
    for(int col = 0; col < Matrix_width(mat); ++col){
      if(*Matrix_at(mat,row,col) > max){
        max = *Matrix_at(mat,row,col);
      }
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  int min = *Matrix_at(mat,row,column_start);
  int mincolumn = column_start;
  while(column_start != (column_end)){
    if(*Matrix_at(mat,row,column_start) < min){
      min = *Matrix_at(mat,row,column_start);
      mincolumn = column_start;
    }
    ++column_start;
  }
  return mincolumn;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  int min = *Matrix_at(mat,row,column_start);
  while(column_start != (column_end)){
    if(*Matrix_at(mat,row,column_start) < min){
      min = *Matrix_at(mat,row,column_start);
    }
    ++column_start;
  }
  return min;
}
