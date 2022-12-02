#include "../audioCodec.cpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    audioCodec codec = audioCodec();

    cout << "------------------------------------------Testing decompression---------------------------------------\n";
    codec.decompress("coded_lossless_01_a", "decoded_lossless_01_a.wav");
    codec.decompress("coded_lossless_01_b", "decoded_lossless_01_b.wav");
    codec.decompress("coded_lossless_01_c", "decoded_lossless_01_c.wav");

}