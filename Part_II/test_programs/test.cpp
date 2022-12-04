#include "../Golomb.cpp"
#include <iostream>

using namespace std;

int main(){ 

    cout << "--------------------------------Testing encoding-----------------------------\n";

    cout << "Original value: 8 \n";
    cout << "m: 4 \n";
    Golomb golombEncode("8", 'e', 4);

    cout << "--------------------------";
    
    cout << "\nOriginal value: 8 \n";
    cout << "m: 5 \n";
    Golomb golombEncode2("8", 'e', 5);

    cout << "--------------------------";

    cout << "\nOriginal value: -12 \n";
    cout << "m: 9 \n";
    Golomb golombEncode3("-12", 'e', 9);

    cout << "\n--------------------------------Testing decoding-----------------------------\n";

    cout << "Encoded String: 1111000 \n";
    cout << "m: 4 \n";
    Golomb golombDecode("1111000", 'd', 4);

    cout << "--------------------------";

    cout << "\nEncoded String: 111001 \n";
    cout << "m: 5 \n";
    Golomb golombDecode2("111001", 'd', 5);

    cout << "--------------------------";

    cout << "\nEncoded String: 110101 \n";
    cout << "m: 9 \n";
    Golomb golombDecode3("110101", 'd', 9);

}