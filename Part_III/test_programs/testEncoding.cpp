#include "../audioCodec.cpp"
#include "../../Part_II/Golomb.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 6)
    {
        throw invalid_argument("ERROR! Incorrect number of arguments\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }

    Golomb golombEncode;
    if(!golombEncode.isInteger(argv[3])){
        throw invalid_argument("ERROR! Predictor order can only be 1, 2 or 3\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }

    if(!golombEncode.isInteger(argv[4])){
        throw invalid_argument("ERROR! Compression can only be 0 (lossless) or 1 (lossy)\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }

    if(!golombEncode.isInteger(argv[5])){
        throw invalid_argument("ERROR! Bits to cut must be an integer in the interval [0-15]\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }
    
    if (atoi(argv[3]) > 3 || atoi(argv[3]) < 1)
    {
        throw invalid_argument("ERROR! Predictor order can only be 1, 2 or 3\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }
    if (atoi(argv[4]) != 0 && atoi(argv[4]) != 1)
    {
        throw invalid_argument("ERROR! Compression can only be 0 (lossless) or 1 (lossy)\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }
    if (atoi(argv[5]) > 15 || atoi(argv[5]) < 0)
    {
        throw invalid_argument("ERROR! Bits to cut must be an integer in the interval [0-15]\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }
    if(atoi(argv[4]) == 0 && atoi(argv[5]) != 0)
    {
        throw invalid_argument("ERROR! Cannot cut any bits if compression is lossless!\n"
        "USAGE: ./testEncoding <input audioFile.type> <output filename> <predictor order (1, 2 or 3)> <0 (lossless) | 1 (lossy)> <bits to cut (0-15)>");
    }
    else
    {
        audioCodec codec = audioCodec();
        codec.compress(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
}