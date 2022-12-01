#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

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
        throw invalid_argument("USAGE: ./intensityImage <input filename.type> <output filename.type> <intensity constant (-255 to 255)>");
    }

    else if(!isInteger(argv[3]) || stoi(argv[3])%1 != 0)
    {
        cerr << ("ERROR: Intensity can only be changed in integer constants \nUSAGE: ./intensityImage <input filename.type> <output filename.type> <intensity constant (-255 to 255)>") << endl;
        return 1;
    }

    else if(stoi(argv[3]) < -255 || stoi(argv[3]) > 255)
    {
        cerr << ("ERROR: Intensity constant only takes values (-255 to 255) \nUSAGE: ./intensityImage <input filename.type> <output filename.type> <intensity constant (-255 to 255)>") << endl;
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
        int constantVal = stoi(argv[3]); 

        /* Increase Image Intensity -> add value to each pixel
           Decrease Image Intensity -> subtract value from each pixel
           - Since program accepts negative values, a sum will work for both cases
        */ 
        for(int y = 0; y < toCopy.rows; y++)
        {
            for(int x = 0; x < toCopy.cols; x++)
            {  
                for(int c = 0; c < toCopy.channels(); c++) 
                {
                    newImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(toCopy.at<Vec3b>(y,x)[c] + constantVal);
                }
            }
        }

        imwrite(argv[2], newImage);
        cout << "An image with altered intensity named " << argv[2] << " has been created!" << endl;
    }
    catch (const cv::Exception &e) 
    {
        if (e.code == -2)
        {
            cerr << "ERROR: Please specify a valid image type (png, jpg, jpeg, ppm, ...) for the new image \nUSAGE: ./intensityImage <input filename.type> <output filename.type> <intensity constant (-255 to 255)> \n";
        }

        else
        {
            cerr << e.err;
        }
    }
    return 0;
}