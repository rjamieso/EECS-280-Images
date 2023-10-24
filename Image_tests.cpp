// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image;
  
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);


  ostringstream s;
  Image_print(img, s);


  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

TEST(test_fill_function){
  Image *img = new Image;

  const Pixel red = {255,0,0};

  Image_init(img,2,2);
  Image_fill(img,red);

  ostringstream z;
  Image_print(img,z);

  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 255 0 0 \n";
  correct << "255 0 0 255 0 0 \n";
  ASSERT_EQUAL(z.str(), correct.str());

  for(int r = 0; r < Image_height(img); ++r){
    for(int c = 0; c < Image_width(img); ++c){
      int redtest = Image_get_pixel(img,r,c).r;
      ASSERT_EQUAL(redtest,red.r);
      int greentest = Image_get_pixel(img,r,c).g;
      ASSERT_EQUAL(greentest,red.g);
      int bluetest = Image_get_pixel(img,r,c).b;
      ASSERT_EQUAL(bluetest,red.b);
    }
  }
  delete img;
}

TEST(height_and_width_test){
  Image *img = new Image;

  const int width = 20;
  const int height = 10;

  Image_init(img,width,height);

  ASSERT_EQUAL(Image_width(img),width);
  ASSERT_EQUAL(Image_height(img),height);

  delete img;
}

TEST(height_and_width_test_advanced){
  Image *img = new Image;

  const int width = 1;
  const int height = 1;

  Image_init(img,width,height);

  ASSERT_EQUAL(Image_width(img),width);
  ASSERT_EQUAL(Image_height(img),height);

  delete img;
}

TEST(height_width_stretched){
  Image *img = new Image;

  const int width = 20;
  const int height = 1;

  Image_init(img,width,height);

  ASSERT_EQUAL(Image_width(img),20);
  ASSERT_EQUAL(Image_height(img),1);

  delete img;
}

TEST(test_get_pixel_function_single){
  Image *img = new Image;

  const int width = 1;
  const int height = 1;
  const Pixel color = {124,12,233};

  Image_init(img,width,height);
  Image_set_pixel(img,0,0,color);

  ASSERT_EQUAL(Image_get_pixel(img,0,0).r,124);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).g,12);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).b,233);

  delete img;

}

TEST(test_get_pixel_function_multiple){
  Image *img = new Image;

  const int width = 3;
  const int height = 1;
  const Pixel color1 = {123,1,64};
  const Pixel color2 = {0,255,0};
  const Pixel color3 = {255,0,255};

  Image_init(img,width,height);
  Image_set_pixel(img,0,0,color1);
  Image_set_pixel(img,0,1,color2);
  Image_set_pixel(img,0,2,color3);
  
  ASSERT_EQUAL(Image_get_pixel(img,0,0).r,123);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).g,1);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).b,64);

  ASSERT_EQUAL(Image_get_pixel(img,0,1).r,0);
  ASSERT_EQUAL(Image_get_pixel(img,0,1).g,255);
  ASSERT_EQUAL(Image_get_pixel(img,0,1).b,0);

  ASSERT_EQUAL(Image_get_pixel(img,0,2).r,255);
  ASSERT_EQUAL(Image_get_pixel(img,0,2).g,0);
  ASSERT_EQUAL(Image_get_pixel(img,0,2).b,255);

  delete img;
}

TEST(corner_pixels_of_image){
  Image *img = new Image;

  const int width = 4;
  const int height = 6;
  const Pixel basecolor = {125,125,125};
  const Pixel color1 = {0,1,2};
  const Pixel color2 = {253,254,255};
  const Pixel color3 = {40,41,42};
  const Pixel color4 = {60,61,62};

  Image_init(img,width,height);

  Image_fill(img,basecolor);

  Image_set_pixel(img,0,0,color1);
  Image_set_pixel(img,0,3,color3);
  Image_set_pixel(img,5,0,color4);
  Image_set_pixel(img,5,3,color2);

  ASSERT_EQUAL(Image_get_pixel(img,0,0).r,0);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).g,1);
  ASSERT_EQUAL(Image_get_pixel(img,0,0).b,2);

  ASSERT_EQUAL(Image_get_pixel(img,5,0).r,60);
  ASSERT_EQUAL(Image_get_pixel(img,5,0).g,61);
  ASSERT_EQUAL(Image_get_pixel(img,5,0).b,62);

  ASSERT_EQUAL(Image_get_pixel(img,0,3).r,40);
  ASSERT_EQUAL(Image_get_pixel(img,0,3).g,41);
  ASSERT_EQUAL(Image_get_pixel(img,0,3).b,42);

  ASSERT_EQUAL(Image_get_pixel(img,5,3).r,253);
  ASSERT_EQUAL(Image_get_pixel(img,5,3).g,254);
  ASSERT_EQUAL(Image_get_pixel(img,5,3).b,255);

  delete img;

}

TEST(test_image_init_from_stream) {
  Image *img = new Image;

  string input = "P3 2 1\t255 254 0 0\n0\n255 0 \n";
  std::istringstream read_input(input);
  Image_init(img, read_input);

  string correctoutput = "P3\n2 1\n255\n254 0 0 0 255 0 \n";
  std::ostringstream read_output;
  Image_print(img, read_output);
  string actual = read_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, correctoutput);

  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
