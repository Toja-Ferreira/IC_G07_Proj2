#include "../audioCodec.cpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        throw invalid_argument("ERROR! Incorrect number of arguments\n"
        "USAGE: ./testDecoding <input filename> <output audioFile.type>)>");
    }
    else
    {
        audioCodec codec = audioCodec();
        codec.decompress(argv[1], argv[2]);
    }
}