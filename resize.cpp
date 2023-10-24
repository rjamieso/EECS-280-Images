// Project UID af1f95f547e44c8ea88730dfb185559d


#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

using namespace std;

int main(int argc, char *argv[]){

    string inputfile = argv[1];
    string outputfile = argv[2];

    ifstream fin;
    fin.open(inputfile);

    if(!fin.is_open()){
        cout << "Error opening file: " << inputfile << endl;
        return 1;
    }
    Image *tempimg = new Image;
    Image_init(tempimg,fin);
    fin.close();

    if(!((argc == 4) || (argc == 5))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete tempimg;
        return 1;
    }

    int intendedwidth = atoi(argv[3]);

    if((intendedwidth < 0) || (intendedwidth > Image_width(tempimg))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete tempimg;
        return 1;
    }

        int intendedheight;
    if(argc == 5){
        intendedheight = atoi(argv[4]);
    } else {
        intendedheight = Image_height(tempimg);
    }

    if((intendedheight < 0) || (intendedheight > Image_height(tempimg))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete tempimg;
        return 1;
    }

    seam_carve(tempimg,intendedwidth,intendedheight);

    ofstream fout;
    fout.open(outputfile);
    if(!fout.is_open()){
        cout << "Error opening file: " << outputfile << endl;
        delete tempimg;
        return 1;
    }
    Image_print(tempimg,fout);
    fout.close();
    delete tempimg;

}