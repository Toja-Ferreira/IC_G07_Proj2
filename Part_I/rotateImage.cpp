#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

// Function to check if string is valid integer
auto isInteger(const string &s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
   {
    return false;
   } 

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        throw invalid_argument("USAGE: ./rotateImage <input filename.type> <output filename.type> <rotation value>");
    }

    else if(!isInteger(argv[3]) || stoi(argv[3])%90 !=0)
    {
        cerr << ("ERROR: Image can only be rotated in integer multiples of 90º \nUSAGE: ./rotateImage <input filename.type> <output filename.type> <rotation value>") << endl;
        return 1;
    }

    Mat toCopy = imread(argv[1]);

    if(!toCopy.data)
    {
        throw runtime_error("Could not open original image file. Check if it exists and is name is correct");
    }

    try 
    {
        Mat newImage(toCopy.rows, toCopy.cols, toCopy.type());
        
        // Rotate image -> Get point of rotation, get rotation matrix, perform transformation
        Point2f rotationPoint(toCopy.cols/2., toCopy.rows/2.);     
        Mat rotationMatrix = getRotationMatrix2D(rotationPoint, stoi(argv[3]), 1.0); 
        warpAffine(toCopy, newImage, rotationMatrix, Size(toCopy.cols, toCopy.rows));

        imwrite(argv[2], newImage);
        cout << "A rotated image named " << argv[2] << " has been created!" << endl;
    }
    catch (const cv::Exception &e) 
    {
        if (e.code == -2)
        {
            cerr << "ERROR: Please specify a valid image type (png, jpg, jpeg, ppm, ...) for the new image \nUSAGE: ./rotateImage <input filename.type> <output filename.type> <rotation value>\n";
        }

        else
        {
            cerr << e.err;
        }
    }
    return 0;
}
