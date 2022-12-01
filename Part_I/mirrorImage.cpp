#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        throw invalid_argument("USAGE: ./mirrorImage <input filename.type> <output filename.type> <V | H>");
    }

    else if(strcmp(argv[3],"V")!=0 && strcmp(argv[3],"H")!=0)
    {
        throw invalid_argument("USAGE: ./mirrorImage <input filename.type> <output filename.type> <V | H>");
    }

    Mat toCopy = imread(argv[1]);

    if(!toCopy.data)
    {
        throw runtime_error("Could not open original image file. Check if it exists and is name is correct");
    }

    try 
    {
        Mat newImage(toCopy.rows, toCopy.cols, toCopy.type());
        
        // Mirror Image Vertically -> reverse rows
        if(strcmp(argv[3],"V")==0)
        {
            int k = toCopy.rows;
            for(int y = 0; y < toCopy.rows; y++)
            {
                for(int x = 0; x < toCopy.cols; x++)
                {   
                    newImage.at<Vec3b>(y,x) = toCopy.at<Vec3b>(k,x);
                }
                k--;
            }
        }

        // Mirror Image Horizontally -> reverse pixels in rows
        else
        {
            int k = toCopy.cols;
            for(int y = 0; y < toCopy.rows; y++)
            {
                for(int x = 0; x < toCopy.cols; x++)
                {   
                    newImage.at<Vec3b>(y,x) = toCopy.at<Vec3b>(y,k-x);
                }
            }
        }

        imwrite(argv[2], newImage);
        cout << "A mirrored image named " << argv[2] << " has been created!" << endl;
    }
    catch (const cv::Exception &e) 
    {
        if (e.code == -2)
        {
            cerr << "ERROR: Please specify a valid image type (png, jpg, jpeg, ppm, ...) for the new image \nUSAGE: ./mirrorImage <input filename.type> <output filename.type> <V | H> \n";
        }

        else
        {
            cerr << e.err;
        }
    }
    return 0;
}