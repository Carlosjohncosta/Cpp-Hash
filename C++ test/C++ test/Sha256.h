#pragma once
#include <iostream>
#include <string.h>
#include "BinOps.h"
using namespace std;

class Sha256 : BinOps {
public:
	char* strIn;

	Sha256(char* _strIn) {
		strIn = _strIn;
		hash();
	}

	class hashVals {
	public:
		string h0 = "0x6a09e667";
		string h1 = "0xbb67ae85";
		string h2 = "0x3c6ef372";
		string h3 = "0xa54ff53a";
		string h4 = "0x510e527f";
		string h5 = "0x9b05688c";
		string h6 = "0x1f83d9ab";
		string h7 = "0x5be0cd19";
	};

	string* roundConsts = new string[]
	{
		"0x428a2f98", "0x71374491", "0xb5c0fbcf", "0xe9b5dba5", "0x3956c25b", "0x59f111f1", "0x923f82a4", "0xab1c5ed5",
		"0xd807aa98", "0x12835b01", "0x243185be", "0x550c7dc3", "0x72be5d74", "0x80deb1fe", "0x9bdc06a7", "0xc19bf174",
		"0xe49b69c1", "0xefbe4786", "0x0fc19dc6", "0x240ca1cc", "0x2de92c6f", "0x4a7484aa", "0x5cb0a9dc", "0x76f988da",
		"0x983e5152", "0xa831c66d", "0xb00327c8", "0xbf597fc7", "0xc6e00bf3", "0xd5a79147", "0x06ca6351", "0x14292967",
		"0x27b70a85", "0x2e1b2138", "0x4d2c6dfc", "0x53380d13", "0x650a7354", "0x766a0abb", "0x81c2c92e", "0x92722c85",
		"0xa2bfe8a1", "0xa81a664b", "0xc24b8b70", "0xc76c51a3", "0xd192e819", "0xd6990624", "0xf40e3585", "0x106aa070",
		"0x19a4c116", "0x1e376c08", "0x2748774c", "0x34b0bcb5", "0x391c0cb3", "0x4ed8aa4a", "0x5b9cca4f", "0x682e6ff3",
		"0x748f82ee", "0x78a5636f", "0x84c87814", "0x8cc70208", "0x90befffa", "0xa4506ceb", "0xbef9a3f7", "0xc67178f2"
	};

	static char** padding(char* str) {
		//Gets size of string.
		int strSize = 0;
		while (str[strSize] != '\0') strSize++;

		//Calculates size of output.
		int finalSize = strSize;
		while (((finalSize * 8) + 64) % 512 != 0) finalSize++;
		finalSize += 8;

		//Allocates rows of char array (plus one for teminator char), and size of big endian.
		char** output = new char* [finalSize + 1];
		char** bigEnd = decToBin(strSize * 8);

		//Gets size of big end.
		int bigEndSize = 0;
		while (bigEnd[bigEndSize][0] != '\0') bigEndSize++;

		//Gets binary string from input, adds it to output, and adds padding as per SHA-256
		for (int i = 0; i < finalSize - bigEndSize; i++) {
			if (i < strSize) {
				output[i] = decToBin((int)str[i])[0];
			}
			else if (i == strSize) {
				output[i] = new char[] {"10000000"};
			}
			else {
				output[i] = new char[] {"00000000"};
			}
		}

		//Adds bigEndian to output.
		int index = 0;
		for (int i = finalSize - bigEndSize; i < finalSize; i++) {
			output[i] = bigEnd[index];
			index++;
		}

		//Adds terminator char to output.
		output[finalSize] = new char[] {'\0'};

		return output;
	}

	char*** messages(char** binArr) {
		//Gets number of chunks.
		int chunkNum = 0;
		while (binArr[chunkNum * 64][0] != '\0') chunkNum++;

		//Tripple pointer for output (Number of chunks, number of messages, 32 bits per message.) +1 for terminator.
		char*** output = new char** [chunkNum + 1];

		//Allocates memory for output.
		for (int i = 0; i < chunkNum; i++) {
			output[i] = new char* [64];
			for (int j = 0; j < 65; j++) {
				output[i][j] = new char[] {"00000000000000000000000000000000"};
			}
		}

		//Adds terminator char
		output[chunkNum] = new char* [1];
		output[chunkNum][0] = new char [] {'\0'};

		//splits binArr into 32 bit words 
		for (int y = 0; y < chunkNum; y++) {
			int wordIndex = 0;
			int bitIndex = 0;
			for (int i = 0; i < 64; i++) {
				for (int j = 0; j < 8; j++) {
					output[y][wordIndex][bitIndex] = binArr[i + (y * 64)][j];
					//keeps track of output index.
					if (bitIndex == 31) {
						bitIndex = 0;
						wordIndex++;
					}
					else {
						bitIndex++;
					}
				}
				//Deallocates binArr.
				delete[] binArr[i + (y * 64)];
			}
		}
		//Deallocates binArr terminator.
		delete[] binArr[chunkNum * 64];

		//Mutates each chunk in output
		for (int i = 0; i < chunkNum; i++) {
			mutate(output[i]);
		}

		//debug
		/*for (int y = 0; y < chunkNum; y++) {
			for (int i = 0; i < 64; i++) {
				for (int j = 0; j < 32; j++) {
					cout << output[y][i][j];
				}
				cout << '\n';
			}
			cout << '\n';
		}*/
		return output;
	}

	void mutate(char** words) {
		cout << addMod(new char[] {"01101000011001010110110001101100"}, new char[] {"11001110111000011001010111001011"});
		for (int i = 16; i < 64; i++) {
			;

		}
	}

	char* hash() {
		char** binArr = padding(strIn);
		messages(binArr);
		return new char[] {""};
	}
};

