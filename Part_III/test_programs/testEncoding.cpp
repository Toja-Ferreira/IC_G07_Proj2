#include "../audioCodec.cpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    audioCodec codec = audioCodec();

    cout << "------------------------------------------Testing lossless compression---------------------------------------\n";
    codec.compress("sample01.wav", "coded_lossless_01_a", 1);
    codec.compress("sample01.wav", "coded_lossless_01_b", 2);
    codec.compress("sample01.wav", "coded_lossless_01_c", 3);


    cout << "\n------------------------------------------Testing lossy compression---------------------------------------\n";
    codec.compress("sample01.wav", "coded_lossy_01_a", 1, '1', 3);
    codec.compress("sample01.wav", "coded_lossy_01_b", 2, '1', 6);
    codec.compress("sample01.wav", "coded_lossy_01_c", 3, '1', 9);

}