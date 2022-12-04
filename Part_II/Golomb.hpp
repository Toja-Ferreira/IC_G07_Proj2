#ifndef GOLOMB_H
#define GOLOMB_H

#include <math.h>
#include <string>

using namespace std;

class Golomb {

    private:
        int m; // Value of integer parameter m in Golomb Code

        /**
         * Auxiliary function to check if given string is a valid encoded value
         * @param s string to validate
         * @return True if s is a valid encoded value, otherwise False
        */ 
        bool isValidString(const string &s)
        {
            for(size_t i = 0; i < s.length(); i++)
            {
                if(s.at(i) != '0' && s.at(i) != '1')
                {
                    return false;
                }
            }
            return true;
        }

        /**
         * Auxiliary function that transforms integer into its binary form with a specified number of bits
         * @param n integer to transform
         * @param numBits number of bits to be used
         * @return integer binary form in form of string
        */ 
        string intToBinary(int n, int numBits)
        {
            string aux = "";
            for (int i = numBits-1; i >= 0; i--) 
            {
                int k = n >> i;
                if (k & 1)
                {
                    aux+="1";
                }
                else
                {
                    aux+="0";
                }   
            }
            return aux;
        }

        /**
         * Auxiliary function that transforms integer into its unary form
         * @param n integer to transform
         * @return integer unary form in form of string
        */ 
        string intToUnary(int n)
        {   
            if(n == 0)
            {
                return "0";
            }

            string un;
            while(n!=0) 
            {
                un+= "1"; 
                n--;
            }
            un+="0";

            return un;
        }

        /**
         * Auxiliary function that transforms binary string into integer 
         * @param stringOfBits string to transform
         * @return integer value of binary string
        */ 
        int binaryToInt(string stringOfBits)
        {
            string num = stringOfBits;
            int value = 0;
            int base = 1;
        
            int len = num.length();
            for (int i = len - 1; i >= 0; i--) 
            {
                if (num[i] == '1')
                {
                    value += base;
                }
                base = base * 2;
            }
            return value;
        }


    public:
        /**
         * Constructor for multiple use
        */
        Golomb();

        /**
         * Constructor for single use 
         * @param value value to be encoded/decoded 
         * @param modeIn 'e' for encoding | 'd' for decoding
         * @param mValue value of m (> 0) to be used in Golomb Code
        */
        Golomb(string value, char modeIn, int mValue);

        /**
         * Perform Golomb Encoding on a single value
         * @param n integer value (positive or negative) to be encoded
         * @return string of bits of the encoded value
        */
        string encode(int n);

        /**
         * Perform Golomb Decoding on single string
         * @param stringOfBits string of bits to be decoded
         * @return decoded integer
        */
        int decode(string stringOfBits);

        /**
         * Set value of m 
         * @param mValue new integer value of m
        */
        void setM(int mValue);

        /**
         * Auxiliary function to convert an integer (positive or negative) into unique positive integer
         * @param n integer to be converted
         * @return converted value
        */
        int transformInteger(int n)
        {
            if (n >= 0)
            {
                return n*2;
            }
            else
            {
                return (-2*n) - 1;
            }
        };

        /**
         * Auxiliary function to revert a unique positive integer (obtained from transformInteger function) into the original integer (positive or negative)
         * @param n value to be reverted
         * @return original integer
        */
        int revertInteger(int n)
        {
            if (n%2 == 0)
            {
                return n/2;
            }
            
            else
            {
                return (-1)*ceil(n/2)-1;
            }
        };

        /**
         * Auxiliary function to check if given integer m is a power of two
         * @param m integer to check
         * @return True if m is a power of two, otherwise False
        */
        bool isPowerOfTwo(int m)
        {
            if (m == 0)
            {
                return false;
            }
            return (ceil(log2(m)) == floor(log2(m)));
        }


        /**
         * Auxiliary function to check if given string is valid integer
         * @param s string to validate
         * @return True if s is valid integer, otherwise False
        */ 
        bool isInteger(const string &s)
        {
            if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            {
                return false;
            } 

            char * p;
            strtol(s.c_str(), &p, 10);

            return (*p == 0);
        }
};

#endif