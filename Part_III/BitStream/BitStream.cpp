#include "BitStream.hpp"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

BitStream::BitStream(const char *filename, char modeIn)
{
    if (modeIn == 'w' || modeIn == 'W') // Write to file
    { 
        binFile = fstream(filename, ios::binary | ios::out);
        if (!binFile.is_open())
        {
            throw runtime_error("ERROR! Could not create binary file to write on");
        }
        mode = 1;
        buffer = 0;
        pointer = 8;
    }

    else if (modeIn == 'r' || modeIn == 'R') // Read from file
    { 
        binFile = fstream(filename, ios::binary | ios::in);
        if (!binFile.is_open())
        {
            throw runtime_error("ERROR! Could not open binary file. Check if it exists");
        }
        mode = 0;
        buffer = 0;
        pointer = 0;
    }

    else
    {
        throw invalid_argument("ERROR! usage: <filename, 'w' | 'r'>");
    }
};

void BitStream::writeBit(char bit)
{   
    if (pointer == 1) // Needs to start writing in new byte
    {
        buffer = buffer | (bit & 0x01);
        try
        {
            binFile.write(reinterpret_cast<char *>(&buffer), sizeof buffer);
        }
        catch (exception const &e)
        {
            cout << "There was an error with the file: " << e.what() << endl;
        }
        buffer = 0;
        pointer = 8;
        return;
    }
    pointer--;
    buffer = buffer | ((bit & 0x01) << pointer);
};

void BitStream::writeNBits(const char *bitsToWrite, int numBitsToWrite)
{
    int i = 0;
    while (i < numBitsToWrite)
    {
        writeBit(bitsToWrite[i]);
        i++;
    }
};

auto BitStream::readBit()
{
    if (pointer == 0) // Start reading next byte
    {
        pointer = 8;
        try
        {
            binFile.read(reinterpret_cast<char *>(&buffer), sizeof buffer);
        }
        catch (exception const &e)
        {
            cout << "There was an error with the file: " << e.what() << endl;
        }
    }
    pointer--;
    return ((buffer >> pointer) & 0x01);
};

auto BitStream::readNBits(int numBitsToRead)
{
    int i = 0;
    vector<int> requestedBits;

    while (i < numBitsToRead)
    {
        requestedBits.push_back(readBit());
        i++;
    }
    return requestedBits;
};

void BitStream::closeFile()
{
    if (mode == 1 && pointer != 8) // Can only write in bytes, so pad the remaining bits
    { 
        binFile.write(reinterpret_cast<char *>(&buffer), sizeof buffer);
    }
    binFile.close();
};
