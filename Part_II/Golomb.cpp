#include "Golomb.hpp"
#include <math.h>
#include <iostream>

using namespace std;

Golomb::Golomb(){};

Golomb::Golomb(string value, char modeIn, int mValue)
{
    if (modeIn != 'e' && modeIn != 'd')
    {
        throw invalid_argument("ERROR! usage: <value to encode/decode> <e' | 'd'> <value of m>");
    }
    
    else if(!Golomb::isInteger(value) && !Golomb::isValidString(value))
    {
        throw invalid_argument("ERROR! Please input a valid integer/bit string \nUsage: <value to encode/decode> <e' | 'd'> <value of m>");
    }

    else
    {
        m = mValue;
        if (modeIn == 'e')
        {   
            string encoded = encode(stoi(value));
            cout << "Encoded Value: " << encoded << endl;
        }
        else
        {
            int decoded = decode(value);
            cout << "Decoded Value: " << decoded << endl;
        }
    }
};

string Golomb::encode(int n)
{
    // Since n can be negative, transform every value into a unique positive integer
    int i = Golomb::transformInteger(n);

    // Calculate parameter values
    int q = floor((int)(i / m));
    int r = i - q * m;
    int b = ceil(log2(m));

    string binPart;
    string unPart;

    // Choose method according to value of m
    if (Golomb::isPowerOfTwo(m))
    {   
        binPart = Golomb::intToBinary(r, b);
        unPart = Golomb::intToUnary(q);

        return unPart + binPart;
    }
    else
    {
        int value;
        int maxNumBits;
        unPart = Golomb::intToUnary(q);

        if (r < pow(2, b) - m)
        {
            value = r; 
            maxNumBits = b-1;
            binPart = Golomb::intToBinary(value, maxNumBits);
        }
        else
        {
            value = r + pow(2, b) - m;
            maxNumBits = b;
            binPart = Golomb::intToBinary(value, maxNumBits);
        }

        return unPart + binPart;
    }
};

int Golomb::decode(string stringOfBits)
{
    // Calculate parameter values
    int b = ceil(log2(m));
    int s = stringOfBits.substr(0, stringOfBits.find("0")).length();
    int x = Golomb::binaryToInt(stringOfBits.substr(stringOfBits.find("0")+1, b-1));
    
    // Choose method according to value of x
    if(x < pow(2, b) - m)
    {
        s = s*m + x;

        // Revert unique positive integer into the original integer value (negative or positive)
        return Golomb::revertInteger(s);
    }
    else
    {
        x = x*x*2 + Golomb::binaryToInt(stringOfBits.substr(stringOfBits.find("0")+b, 1));
        s = s*m + (x-(pow(2, b) - m));
        
        // Revert unique positive integer into the original integer value (negative or positive)
        return Golomb::revertInteger(s);
    }
};

void Golomb::setM(int mValue)
{
    this->m = mValue;
};


