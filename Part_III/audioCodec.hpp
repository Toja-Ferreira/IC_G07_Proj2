#ifndef AUDIOCODEC_H
#define AUDIOCODEC_H

#include <sndfile.hh>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class audioCodec
{
    private:

        /**
         * The codec Predictor 
         * @param samples vector containing the data to be predicted
         * @param order order of the predictor (1-3) 
         * @param isLossy '0' for lossless prediction | '1' for lossy prediction
         * @param cutBits number of bits (0-15) to be quantized [0 -> lossless predictor | cutBits -> lossy predictor]
         * @return vector containing the encoding sequence
        */        
        vector<short> predictor(vector<short> samples, int order, char isLossy, int cutBits);

        /**
         * The codec revertPredictor, to reconstruct the values obtained from the predictor
         * @param samples vector containing all the residuals to reconstruct
         * @param order order of the predictor (1-3) 
         * @param isLossy '0' if lossless | '1' if lossy 
         * @param cutBits number of bits (0-15) that were quantized
         * @return vector containing the reconstructed sequence
        */        
        vector<short> revertPredictor(vector<short> samples, int order, char isLossy, int cutBits);

        /**
         * Auxiliary function to convert an integer value into binary with specified number of bits
         * @param value value to be transformed
         * @param numBits number of bits to used 
         * @return string containing binary value of integer
        */    
        string intToBinary(int value, int numBits)
        {
            string aux = "";
            for (int i = numBits-1; i >= 0; i--)
            {
                int k = value >> i;
                if (k & 1)
                {
                    aux+="1";
                }
                else
                    aux+="0";
                }
            return aux;
        }

        /**
         * Auxiliary function to convert a binary value (in form of vector<int>) into integer value
         * @param bin vector of bits to be converted
         * @return integer value
        */   
        int binaryToInt(vector<int> bin)
        {
            reverse(begin(bin), end(bin));
            int val = 0;

            for(int i = 0; i < bin.size(); i++)
            {
                if (bin[i] == 1)
                {
                    val += pow(2, i);
                }
            }
            return val;
        }

        /**
         * Auxiliary function to calculate Shannon entropy value
         * @param values values to analyze
         * @return entropy value
        */
        float calculateEntropy(vector<short> values);

        /**
         * Auxiliary function to calculate compression ratio value between 2 files
         * @param uncompressedFile uncompressed file
         * @param compressedFile compressed file
         * @return compression ratio 
        */
        float calculateCompression(const char *uncompressedFile, const char *compressedFile);

    public:
    
        /**
         * Initialize audioCodec object
        */
        audioCodec();

        /**
         * Compress audio file
         * @param inFile name of audio file to compress
         * @param outfFile name of output binary file containing compressed audio data
         * @param predOrder order of predictor (1-3)
         * @param isLossy 0 for lossless compression (default) | 1 for lossy compression
         * @param cutBits number of bits (0-15) to be quantized (default=0)
        */
        void compress(const char *inFile, const char *outFile, int predOrder, int isLossy=0, int cutBits=0);

        /**
         * Decompress binary file into audio file
         * @param inFile name of binary file that contains the compressed audio data
         * @param outFile name of audio file to be created
        */
        void decompress(const char *inFile, const char *outFile);
};

#endif
