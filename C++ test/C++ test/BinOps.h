#include <iostream>
#include <string.h>
class BinOps
{
public:
	//Returns a pointer to an array of 8 bits.
	static char** decToBin(long num) {
		//Initialises number of bytes to be returned to 1.
		int bytes = 1;

		//Increments byte.
		while (pow(2, 8 * bytes) - 1 < num) bytes++;

		//Sets 2d pointer to number of bytes (Plus extra terminator char).
		char** output = new char* [bytes + 1];

		//Allocates 8 chars per byte.
		for (int i = 0; i < bytes; i++) {
			output[i] = new char[8];
		}

		//Char 'f' is terminator.
		output[bytes] = new char[] {'\0'};

		//Indexes for positions in byte and bit respectivily.
		int byteIndex = 0;
		int bitIndex = 0;
		for (long i = (8 * bytes) - 1; i >= 0; i--) {
			if (num >= pow(2, i)) {
				output[byteIndex][bitIndex] = '1';
				num -= pow(2, i);
			}
			else {
				output[byteIndex][bitIndex] = '0';
			}

			//Once bitIndex = 7 (8 digits long), we increment the byte index and set bitIndex to 0.
			if (bitIndex == 7) {
				byteIndex++;
				bitIndex = 0;
			}
			else {
				bitIndex++;
			}
		}
		return output;
	}

	static long binToDec(char* input) {
		int len = 0;
		long output = 0;
		while (input[len + 1] != '\0') len++;
		for (int i = 0; i <= len; i++) {
			if (input[i] == '1') {
				output += pow(2, len - i);
			}
		}
		return output;
	}

	static char* addMod(char* arr1, char* arr2, long modNum = pow(2, 32)) {
		//Converts binary to decimal.
		long decNum = binToDec(arr1) + binToDec(arr2);
		//Mod 32 of decNum
		decNum %= modNum;
		//Gets binary from decNum.
		char** converted = decToBin(decNum);
		int len = 0;
		while (converted[len][0] != '\0') len++;
		//Adds converted to output.
		char* output = new char[(len * 8) + 1];
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < 8; j++) {
				output[(i * 8) + j] = converted[i][j];
			}
		}
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
};
