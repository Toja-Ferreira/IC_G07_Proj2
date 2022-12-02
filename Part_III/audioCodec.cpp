#include "audioCodec.hpp"
#include "../Part_III/BitStream/BitStream.cpp"
#include "../Part_II/Golomb.cpp"
#include <sndfile.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <numeric>

using namespace std;

audioCodec::audioCodec(){};

void audioCodec::compress(const char *inFile, const char *outFile, int predOrder, char isLossy, int cutBits)
{
    clock_t begin = clock(); // Start of compression

    SndfileHandle audioFile = inFile;

    if (audioFile.error())
    {
        throw invalid_argument("ERROR! invalid input audio file\n");
    }

    if ((audioFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV)
    {
        throw invalid_argument("ERROR! audio file is not in WAV format\n");
    }

    if ((audioFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16)
    {
        throw invalid_argument("ERROR! audio file is not in PCM_16 format\n");
    }

    if (isLossy != '0' && isLossy != '1')
    {
        throw invalid_argument("ERROR! isLossy field can only be 0 (lossless) or 1 (lossy)");
    }

    if (predOrder > 3 || predOrder < 1)
    {
        throw invalid_argument("ERROR! predOrder field must be 1, 2 or 3");
    }

    if (cutBits > 15 || cutBits < 0)
    {
        throw invalid_argument("ERROR! cutBits field must be a positive integer lesser than 16");
    }

    else
    {
        cout << "Started encoding, please wait...." << endl;

        // Get audio file samples
        size_t nChannels = {static_cast<size_t>(audioFile.channels())};
        size_t nFrames = {static_cast<size_t>(audioFile.frames())};
        vector<short> samples(nChannels * nFrames);
        audioFile.readf(samples.data(), nFrames);

        try
        {
            // Write to binary file using BitStream class
            BitStream compressedFile(outFile, 'w');

            // Obtain encoding sequence of samples using predictor
            vector<short> sequence = audioCodec::predictor(samples, predOrder, isLossy, cutBits);

            // Create Golomb codec
            Golomb golombCodec;

            // Calculate the best value for m parameter of Golomb code
            double avg = 0;
            for (auto res : sequence)
            {
                avg += golombCodec.transformInteger(res);
            }
            avg = avg / sequence.size();

            int optimizedM = (int)ceil(-1 / (log2(avg / (avg + 1))));
            golombCodec.setM(optimizedM);

            // Write binary file header containing important info
            string hFrames = audioCodec::intToBinary(audioFile.frames(), 32);         // Frames              -> 32 bits
            string hSampleRate = audioCodec::intToBinary(audioFile.samplerate(), 32); // Sample Rate         -> 32 bits
            string hFormat = audioCodec::intToBinary(audioFile.format(), 32);         // Format              -> 32 bits
            string m = audioCodec::intToBinary(optimizedM, 32);                       // Value of m          -> 32 bits
            string hChannels = audioCodec::intToBinary(audioFile.channels(), 8);      // Audio Channels      -> 8 bits
            string bitsQ = audioCodec::intToBinary(cutBits, 8);                       // Quantized Bits      -> 8 bits
            string orderP = audioCodec::intToBinary(predOrder, 2);                    // Predictor Order     -> 2 bits
            string lossy = audioCodec::intToBinary(isLossy, 1);                       // Type of compression -> 1 bit
            compressedFile.writeNBits(hFrames.c_str(), 32);
            compressedFile.writeNBits(hSampleRate.c_str(), 32);
            compressedFile.writeNBits(hFormat.c_str(), 32);
            compressedFile.writeNBits(m.c_str(), 32);
            compressedFile.writeNBits(hChannels.c_str(), 8);
            compressedFile.writeNBits(bitsQ.c_str(), 8);
            compressedFile.writeNBits(orderP.c_str(), 2);
            compressedFile.writeNBits(lossy.c_str(), 1);

            // Encode sequence values using Golomb encoding and write in file
            for (short res : sequence)
            {
                string gol = golombCodec.encode(res);
                compressedFile.writeNBits(gol.c_str(), gol.length());
            }
            compressedFile.closeFile();

            clock_t end = clock(); // End of compression

            cout << "The audio file: " << inFile << " has been sucessfully compressed into the binary file " << outFile << endl;

            float originalEntropy = audioCodec::calculateEntropy(samples);
            float residualEntropy = audioCodec::calculateEntropy(sequence);

            cout << "-Type of Compression: " << (isLossy == '1' ? "Lossy" : "Lossless")
                 << "\n-Quantized Bits: " << (isLossy == '0' ? 0 : cutBits)
                 << "\n-Predictor Order: " << predOrder
                 << "\n-Original Entropy: " << originalEntropy
                 << "\n-Residual Entropy: " << residualEntropy
                 << "\n-Entropy Ratio: " << originalEntropy / residualEntropy
                 << "\n-Time Taken: " << (double(end - begin) / CLOCKS_PER_SEC) << "s\n\n"
                 << endl;
        }
        catch (exception const &e)
        {
            throw runtime_error("An error occurred while compressing the file. Check if it exists and is of a valid format");
        }
    }
};

void audioCodec::decompress(const char *inFile, const char *outFile)
{
    try
    {
        cout << "Started decoding, please wait...." << endl;

        // Get binary file size
        ifstream mybinfile(inFile, ios::binary);
        mybinfile.seekg(0, ios::end);
        int file_size = mybinfile.tellg();
        mybinfile.seekg(0, ios::beg);
        mybinfile.close();

        // Read from binary file using BitStream class
        BitStream binToDecode(inFile, 'r');

        // Read binary file header
        int hFrames = audioCodec::binaryToInt(binToDecode.readNBits(32));
        int hSampleRate = audioCodec::binaryToInt(binToDecode.readNBits(32));
        int hFormat = audioCodec::binaryToInt(binToDecode.readNBits(32));
        int optimizedM = audioCodec::binaryToInt(binToDecode.readNBits(32));
        int hChannels = audioCodec::binaryToInt(binToDecode.readNBits(8));
        int bitsQ = audioCodec::binaryToInt(binToDecode.readNBits(8));
        int orderP = audioCodec::binaryToInt(binToDecode.readNBits(2));
        int lossy = audioCodec::binaryToInt(binToDecode.readNBits(1));

        // Decode file data using Golomb decoding algorithm
        Golomb golombCodec;
        golombCodec.setM(optimizedM);
        vector<short> samples;
        int b = ceil(log2(optimizedM));

        for (int i = 0; i < hChannels * hFrames; i++)
        {
            // Parameter values
            int s;
            int x;
            vector<int> vectorOfBits;

            // Find unary part (consecutive number of 1s until first 0 is found)
            while(true)
            {
                if(binToDecode.readBit() == 0)
                {
                    break;
                }
                s++;
            }

            vectorOfBits = binToDecode.readNBits(b-1);
            x = audioCodec::binaryToInt(vectorOfBits);
            
            // Calculate value according to value of x
            if(x < (pow(2, b) - optimizedM))
            {
                samples.push_back(golombCodec.revertInteger(s*optimizedM + x));
            }
            else
            {
                x = x*x*2 + binToDecode.readBit();
                samples.push_back(golombCodec.revertInteger(s*optimizedM - (x - (pow(2, b) - optimizedM))));
            }
                                                                                                                                                  
        }
        binToDecode.closeFile();

        // Reconstruct original sequence of values
        vector<short> sequence = audioCodec::revertPredictor(samples, orderP, lossy, bitsQ);

        // Write values into audio file
        SndfileHandle sfhOut{outFile, SFM_WRITE, hFormat, hChannels, hSampleRate};
        sfhOut.writef(sequence.data(), hFrames);
        cout << "The binary file " << inFile << " has been sucessfully decompressed into the audio file " << outFile << "\n" << endl;
    }
    catch (exception const &e)
    {
        throw runtime_error("An error occurred while decompressing the file. Check if it exists and is of a valid format");
    }
};

vector<short> audioCodec::predictor(vector<short> samples, int order, char isLossy, int cutBits)
{
    vector<short> leftChannel, rightChannel;
    vector<short> estimateLeft, estimateRight;
    vector<short> residuals;

    // Divide samples into respective channels to perform inter-channel prediction
    for (int i = 0; i < samples.size() - 1; i += 2)
    {
        leftChannel.push_back(samples[i]);
        rightChannel.push_back(samples[i + 1]);
    }

    // Perform prediction according to order
    if (order == 1)
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i == 0)
            {
                estimateLeft.push_back(0);
                estimateRight.push_back(0);
            }
            else
            {
                estimateLeft.push_back(leftChannel[i - 1]);
                estimateRight.push_back(rightChannel[i - 1]);
            }
            residuals.push_back(leftChannel[i] - estimateLeft[i]);   // Residual for left channel
            residuals.push_back(rightChannel[i] - estimateRight[i]); // Residual for right channel
        }
    }

    else if (order == 2)
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i < 2)
            {
                estimateLeft.push_back(0);
                estimateRight.push_back(0);
            }
            else
            {
                estimateLeft.push_back(2 * leftChannel[i - 1] - leftChannel[i - 2]);
                estimateRight.push_back(2 * rightChannel[i - 1] - rightChannel[i - 2]);
            }
            residuals.push_back(leftChannel[i] - estimateLeft[i]);   // Residual for left channel
            residuals.push_back(rightChannel[i] - estimateRight[i]); // Residual for right channel
        }
    }

    else
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i < 3)
            {
                estimateLeft.push_back(0);
                estimateRight.push_back(0);
            }
            else
            {
                estimateLeft.push_back(3 * leftChannel[i - 1] - 3 * leftChannel[i - 2] + leftChannel[i - 3]);
                estimateRight.push_back(3 * rightChannel[i - 1] - 3 * rightChannel[i - 2] + rightChannel[i - 3]);
            }
            residuals.push_back(leftChannel[i] - estimateLeft[i]);   // Residual for left channel
            residuals.push_back(rightChannel[i] - estimateRight[i]); // Residual for right channel
        }
    }

    // If prediction is lossless ('0'), return residuals
    if (isLossy == '0')
    {
        return residuals;
    }

    // If prediction is lossy ('1'), perform quantization on residuals and return
    else
    {
        vector<short> residualsQuant;
        residualsQuant.resize(0);

        // Perform quantization on residuals
        for (auto res : residuals)
        {
            res = res >> cutBits;
            short tmp = res << cutBits;
            residualsQuant.insert(residualsQuant.end(), tmp);
        }

        return residualsQuant;
    }
};

vector<short> audioCodec::revertPredictor(vector<short> samples, int order, char isLossy, int cutBits)
{
    vector<short> leftChannel, rightChannel;
    vector<short> estimateLeft, estimateRight;
    vector<short> originalValues;

    // Divide samples into respective channels to revert the prediction made on each channel
    for (int i = 0; i < samples.size() - 1; i += 2)
    {
        leftChannel.push_back(samples[i]);
        rightChannel.push_back(samples[i + 1]);
    }

    // Revert prediction according to order
    if (order == 1)
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i == 0)
            {
                estimateLeft.push_back(leftChannel[0]);
                estimateRight.push_back(rightChannel[0]);

                originalValues.push_back(leftChannel[0]);
                originalValues.push_back(rightChannel[0]);
            }
            else
            {
                estimateLeft.push_back((short)leftChannel[i] + estimateLeft[i - 1]);
                estimateRight.push_back((short)rightChannel[i] + estimateRight[i - 1]);

                originalValues.push_back(estimateLeft[i]);
                originalValues.push_back(estimateRight[i]);
            }
        }
    }

    else if (order == 2)
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i < 2)
            {
                estimateLeft.push_back(0);
                estimateRight.push_back(0);

                originalValues.push_back(estimateLeft[i]);
                originalValues.push_back(estimateRight[i]);
            }
            else
            {
                estimateLeft.push_back((short)leftChannel[i] + (2 * estimateLeft[i - 1] - estimateLeft[i - 2]));
                estimateRight.push_back((short)rightChannel[i] + (2 * estimateRight[i - 1] - estimateRight[i - 2]));

                originalValues.push_back(estimateLeft[i]);
                originalValues.push_back(estimateRight[i]);
            }
        }
    }

    else
    {
        for (int i = 0; i < leftChannel.size(); i++)
        {
            if (i < 3)
            {
                estimateLeft.push_back(0);
                estimateRight.push_back(0);

                originalValues.push_back(estimateLeft[i]);
                originalValues.push_back(estimateRight[i]);
            }
            else
            {
                estimateLeft.push_back((short)leftChannel[i] + (3 * estimateLeft[i - 1] - 3 * estimateLeft[i - 2] + estimateLeft[i - 3]));
                estimateRight.push_back((short)rightChannel[i] + (3 * estimateRight[i - 1] - 3 * estimateRight[i - 2] + estimateRight[i - 3]));

                originalValues.push_back(estimateLeft[i]);
                originalValues.push_back(estimateRight[i]);
            }
        }
    }

    return originalValues;
};

float audioCodec::calculateEntropy(vector<short> values)
{
    float entropy = 0;
    map<short, long> counts;
    typename map<short, long>::iterator it;

    for (int i = 0; i < values.size(); ++i)
    {
        counts[values[i]]++;
    }

    it = counts.begin();
    while (it != counts.end())
    {
        float p_x = (float)it->second / values.size();
        if (p_x > 0)
        {
            entropy -= p_x * log(p_x) / log(2);
        }
        it++;
    }

    return entropy;
};