#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;
class BinOps {
public:
	//Returns a pointer to an array of 8 bits.
	static char** decToBin(long long num) {
		//Initialises number of bytes to be returned to 1.
		int bytes = 1;

		//Increments byte.
		while (pow(2, 8 * bytes) - 1 < num) bytes++;

		//Sets 2d pointer to number of bytes (Plus extra terminator char).
		char** output = new char* [bytes + 1];

		//Allocates 8 chars per byte (plus one for terminator).
		for (int i = 0; i < bytes; i++) {
			output[i] = new char[9];
		}

		//Char 'f' is terminator.
		output[bytes] = new char[] {'\0'};

		//Indexes for positions in byte and bit respectivily.
		int byteIndex = 0;
		int bitIndex = 0;
		for (int i = (8 * bytes) - 1; i >= 0; i--) {
			if (num >= pow(2, i)) {
				output[byteIndex][bitIndex] = '1';
				num -= pow(2, i);
			}
			else {
				output[byteIndex][bitIndex] = '0';
			}

			//Once bitIndex = 7 (8 digits long), we increment the byte index and set bitIndex to 0.
			if (bitIndex == 7) {
				output[byteIndex][8] = '\0';
				byteIndex++;
				bitIndex = 0;
			}
			else {
				bitIndex++;
			}
		}
		return output;
	}

	static long long binToDec(char* input) {
		int len = 0;
		long long output = 0;
		while (input[len + 1] != '\0') len++;
		for (int i = 0; i <= len; i++) {
			if (input[i] == '1') {
				output += pow(2, len - i);
			}
		}
		return output;
	}

	static char* addMod(char* arr1, char* arr2, long long modNum = pow(2, 32)) {
		//Converts binary to decimal.
		long long decNum = binToDec(arr1) + binToDec(arr2);

		//Mod 32 of decNum
		decNum = decNum % modNum;

		//Gets binary from decNum.
		char** converted = decToBin(decNum);
		int len = 0;
		while (converted[len][0] != '\0') len++;

		//pads with '0' if converted < 4 bytes.
		int startIndex = 0;
		char* output = new char[33];

		while (len < 4) {
			for (int i = 0; i < 8; i++) { output[startIndex] = '0'; startIndex++;}
			len++;
		}
		//Adds converted to output.
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < 8; j++) {
				output[(i * 8) + j + startIndex] = converted[i][j];
			}
		}
		//Deallocates pointers for converted.
		delete[] converted;
		output[len * 8] = '\0';
		return output;
	}

	//Rotates bits.
	static char* rotate(char* input, int rotNum) {
		//Gets length of input
		int len = 0;
		while (input[len] != '\0') len++;
		//Copies input values to temp (plus one for terminator).
		char* output = new char[len + 1];
		bool direction = false;
		//changes direction of rotate ('- = left, + = right')
		if (rotNum >= 0) {
			direction = true;
		}
		else {
			rotNum *= -1;
		}
		for (int i = 0; i < len; i++) output[i] = input[i];
		for (int i = 0; i < len; i++) {
			if (direction) {
				output[rotNum] = input[i];
			}
			else {
				output[i] = input[rotNum];
			}
			if (rotNum == len - 1) {
				rotNum = 0;
			}
			else {
				rotNum++;
			}
		}
		output[len] = '\0';
		return output;

	}

	//Shifts bits
	static char* shift(char* input, int num) {
		int len = 0;
		while (input[len] != '\0') len++;
		char* output = new char[len + 1];
		for (int i = 0; i < num; i++) {
			output[i] = '0';
		}
		for (int i = num; i < len; i++) {
			output[i] = input[i - num];
		}
		output[len] = '\0';
		return output;
	}

	//Bitwise XOR
	static char* XOR(char* arr1, char* arr2) {
		int len = 0;
		while (arr1[len] != '\0') len++;
		char* output = new char[len + 1];
		for (int i = 0; i < len; i++) {
			if (arr1[i] == arr2[i]) {
				output[i] = '0';
			}
			else if (arr1[i] == '1' || arr2[i] == '1') {
				output[i] = '1';
			}
			else {
				output[i] = '0';
			}
		}
		output[len] = '\0';
		return output;
	}

	static char* AND(char* arr1, char* arr2) {
		int len = 0;
		while (arr1[len] != '\0') len++;
		char* output = new char[len + 1];
		for (int i = 0; i < len; i++) {
			if (arr1[i] == '1' && arr2[i] == '1') output[i] = '1'; else output[i] = '0';
		}
		output[len] = '\0';
		return output;
	}

	static char* NOT(char* input) {
		int len = 0;
		while (input[len] != '\0') len++;
		char* output = new char[len + 1];
		for (int i = 0; i < len; i++) {
			if (input[i] == '1') output[i] = '0'; else output[i] = '1';
		}
		output[len] = '\0';
		return output;
	}
};

class Sha256 : BinOps {
public:
	char* strIn;

	Sha256(char* _strIn) {
		strIn = _strIn;
		hash();
	}

	struct hashVals {
		char a[33] = "01101010000010011110011001100111";
		char b[33] = "10111011011001111010111010000101";
		char c[33] = "00111100011011101111001101110010";
		char d[33] = "10100101010011111111010100111010";
		char e[33] = "01010001000011100101001001111111";
		char f[33] = "10011011000001010110100010001100";
		char g[33] = "00011111100000111101100110101011";
		char h[33] = "01011011111000001100110100011001";
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
		char*** output = new char** [chunkNum + 2];

		//Allocates memory for output.
		for (int i = 0; i < chunkNum; i++) {
			output[i] = new char* [64];
			for (int j = 0; j < 65; j++) {
				output[i][j] = new char[32];
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
						output[y][wordIndex][bitIndex + 1] = '\0';
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
				if (i % 2 == 0) cout << ' '; else cout << '\n';
			}
			cout << '\n';
		}*/
		return output;
	}

	void mutate(char** words) {
		for (int i = 16; i < 64; i++) {
			//Mutates message values.
			char* s0 = XOR(XOR(rotate(words[i - 15], 7), rotate(words[i - 15], 18)), shift(words[i - 15], 3));
			char* s1 = XOR(XOR(rotate(words[i - 2], 17), rotate(words[i - 2], 19)), shift(words[i - 2], 10));
			words[i] = addMod(words[i - 16], addMod(words[i - 7], addMod(s0, s1)));
		}
	}

	hashVals* chunkLoop(char*** chunks) {
		int chunkNum = 0;
		while (chunks[chunkNum][0][0] = '\0') chunkNum++;
		chunkNum++;
		hashVals* output = new hashVals;
		for (int i = 0; i < chunkNum; i++) {
			for (int j = 0; j < 64; j++) {
				char* s1 = XOR(rotate(output->e, 6), XOR(rotate(output->e, 25), rotate(output->e, 11)));
				
			}
		}
		cout << NOT(output->a);
		return output;
	}

	char* hash() {
		char** binArr = padding(strIn);
		char*** chunks = messages(binArr);
		hashVals* words = chunkLoop(chunks);
		return new char[] {""};
	}
};

int main()
{

	Sha256 test(new char[] {"hello world"});
}


