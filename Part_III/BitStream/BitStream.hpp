#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdexcept>
#include <fstream>

using namespace std;

class BitStream {

    private:
        unsigned char buffer;       // Buffer of bits equal to 1 byte -> [0] (LSB) to [7] (MSB)
        int mode;                   // Write (1) | Read (0)
        int pointer;                // Pointer to last accessed bit (0-7)
        fstream binFile;            // Binary file to read from | write to

    public:
        BitStream(const char *filename, char modeIn);

        void writeBit(char bit);

        void writeNBits(const char* bitsToWrite, int numBitsToWrite);

        auto readBit();

        auto readNBits(int numBitsToRead);

        void closeFile();
};

#endif