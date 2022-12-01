#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        throw invalid_argument("USAGE: ./copyImage <input filename.type> <output filename.type>");
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        throw invalid_argument("ERROR: Cannot copy to image with same name, Please choose another name for new image");
    }

    Mat toCopy = imread(argv[1]);

    if(!toCopy.data)
    {
        throw runtime_error("Could not open original image file. Check if it exists and is name is correct");
    }

    try 
    {
        Mat newImage(toCopy.rows, toCopy.cols, toCopy.type());

        for(int y = 0; y < toCopy.rows; y++)
        {
            for(int x = 0; x < toCopy.cols; x++)
            {
                for(int c = 0; c < toCopy.channels(); c++) 
                {
                    newImage.at<Vec3b>(y,x)[c] = toCopy.at<Vec3b>(y,x)[c];
                }
            }
        }

        imwrite(argv[2], newImage);
        cout << "A copy named " << argv[2] << " has been created!" << endl;
    }
    catch (const cv::Exception &e) 
    {
        if (e.code == -2)
        {
            cerr << "ERROR: Please specify a valid image type (png, jpg, jpeg, ppm, ...) for the new image \nUSAGE: ./copyImage <input filename.type> <output filename.type> \n";
        }

        else
        {
            cerr << e.err;
        }
    }
    return 0;
}