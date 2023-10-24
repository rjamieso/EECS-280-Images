// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

TEST(test_fill_basic) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int value = 42;

  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; 
}

TEST(test_border_basic){
  Matrix *mat = new Matrix;
  
  const int width = 4;
  const int height = 3;
  const int value = 1;
  const int bordervalue= 0;

  Matrix_init(mat,width,height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat,bordervalue);
  Matrix_print(mat,cout);

  const int firstrow = 0;
  const int lastrow = (Matrix_height(mat)) - 1;
  const int firstcol = 0;
  const int lastcol = (Matrix_width(mat)) - 1;

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
     if((r == firstrow) || (r == lastrow)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
     if((c == firstcol) || (c == lastcol)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
    }
  }

  delete mat;

}

TEST(test_border_advanced){
  Matrix *mat = new Matrix;
  
  const int width = 2;
  const int height = 2;
  const int value = 1;
  const int bordervalue= 0;

  Matrix_init(mat,width,height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat,bordervalue);
  Matrix_print(mat,cout);

  const int firstrow = 0;
  const int lastrow = ((Matrix_height(mat)) - 1);
  const int firstcol = 0;
  const int lastcol = ((Matrix_width(mat)) - 1);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
     if((r == firstrow) || (r == lastrow)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
     if((c == firstcol) || (c == lastcol)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
    }
  }

  delete mat;

}

TEST(test_border_extraadvanced){
  Matrix *mat = new Matrix;
  
  const int width = 1;
  const int height = 1;
  const int value = 1;
  const int bordervalue= 0;

  Matrix_init(mat,width,height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat,bordervalue);
  Matrix_print(mat,cout);

  const int firstrow = 0;
  const int lastrow = ((Matrix_height(mat)) - 1);
  const int firstcol = 0;
  const int lastcol = ((Matrix_width(mat)) - 1);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
     if((r == firstrow) || (r == lastrow)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
     if((c == firstcol) || (c == lastcol)){
      ASSERT_EQUAL(*Matrix_at(mat,r,c),bordervalue);
     }
    }
  }

  delete mat;

}

TEST(test_width_height_row_column){
  Matrix *mat = new Matrix;
  
  const int width = 5;
  const int height = 3;

  Matrix_init(mat,width,height);
  Matrix_fill(mat,42);

  //width and height
  ASSERT_EQUAL(Matrix_width(mat),5);
  ASSERT_EQUAL(Matrix_height(mat),3);

  //row and column
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,1,4)),1);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,1,4)),4);

  //Matrix_row
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,0)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,1)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,2)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,3)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,4)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,1,0)),1);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,1,1)),1);

  delete mat;

}

TEST(test_col_of_min_val_and_min_val_of_row_and_max_of_matrix){
  Matrix *mat = new Matrix;

  const int width = 4;
  const int height = 3;
  const int testvalue = 33;
  const int testmin = 2;
  const int testmax = 100;

  Matrix_init(mat,width,height);
  Matrix_fill(mat,testvalue);

  *Matrix_at(mat,2,2) = testmin;
  *Matrix_at(mat,2,3) = 1;
  *Matrix_at(mat,2,1) = testmax;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,2,0,3),2);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat,2,0,3),testmin);

  ASSERT_EQUAL(Matrix_max(mat),testmax);

  cout << *Matrix_at(mat,0,0) << " and " << *Matrix_at(mat,2,2) << endl;

  delete mat;

}

TEST(at_function_test){
  Matrix *mat = new Matrix;

  const int height = 3;
  const int width = 5;
  const int basevalue = 0;


  Matrix_init(mat,width,height);
  Matrix_fill(mat,basevalue);

  ASSERT_EQUAL(*(Matrix_at(mat,2,1)),0);
  ASSERT_EQUAL(*(Matrix_at(mat,2,4)),0);
  ASSERT_EQUAL(*(Matrix_at(mat,0,0)),0);

  delete mat;
}

TEST(test_print_function){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 3;
  const int fillval = 1;

  Matrix_init(mat,width,height);
  Matrix_fill(mat,fillval);

  ostringstream s;
  Matrix_print(mat, s);

  ostringstream correct;

  correct << "5 3\n";
  correct << "1 1 1 1 1 \n";
  correct << "1 1 1 1 1 \n";
  correct << "1 1 1 1 1 \n";
  
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;

}

TEST(test_print_function_with_border){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 3;
  const int fillval = 1;
  const int borderval = 0;

  Matrix_init(mat,width,height);
  Matrix_fill(mat,fillval);
  Matrix_fill_border(mat,borderval);

  ostringstream s;
  Matrix_print(mat, s);

  ostringstream correct;

  correct << "5 3\n";
  correct << "0 0 0 0 0 \n";
  correct << "0 1 1 1 0 \n";
  correct << "0 0 0 0 0 \n";
  
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;

}

TEST(test_print_function_with_border_onepixel){
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 1;
  const int borderval = 0;
  Matrix_init(mat,width,height);
  Matrix_fill_border(mat,borderval);

  ostringstream s;
  Matrix_print(mat, s);

  ostringstream correct;

  correct << "1 1\n";
  correct << "0 \n";
  
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;

}

TEST(test_two_max_functions){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 3;
  const int val = 1;
  const int max = 400;

  Matrix_init(mat,width,height);

  Matrix_fill(mat,val);

  *(Matrix_at(mat,0,0)) = 4;
  *(Matrix_at(mat,0,1)) = 10;
  *(Matrix_at(mat,0,2)) = -10;
  *(Matrix_at(mat,1,0)) = 400;
  *(Matrix_at(mat,1,1)) = 10;
  *(Matrix_at(mat,1,2)) = 15;
  *(Matrix_at(mat,2,0)) = 2;
  *(Matrix_at(mat,2,1)) = 400;
  *(Matrix_at(mat,2,2)) = 240;

  ASSERT_EQUAL(Matrix_max(mat),max);

  delete mat;

}

TEST(test_for_cost_matrix_use_of_min){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 1;

  Matrix_init(mat,width,height);

  *(Matrix_at(mat,0,0)) = 10;
  *(Matrix_at(mat,0,1)) = 20;
  *(Matrix_at(mat,0,2)) = 3;
  *(Matrix_at(mat,0,3)) = 100;
  *(Matrix_at(mat,0,4)) = 50;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,2),10);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,1,4),3);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,3,5),50);

  delete mat;
}

TEST(test_column_of_min_for_processing){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 1;

  Matrix_init(mat,width,height);

  *(Matrix_at(mat,0,0)) = 4663;
  *(Matrix_at(mat,0,1)) = 4159;
  *(Matrix_at(mat,0,2)) = 4159;
  *(Matrix_at(mat,0,3)) = 4159;
  *(Matrix_at(mat,0,4)) = 4663;

  int seam[1];
  seam[0] = Matrix_column_of_min_value_in_row(mat,0,0,5);
  ASSERT_EQUAL(seam[0],1);

  delete mat;

}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
