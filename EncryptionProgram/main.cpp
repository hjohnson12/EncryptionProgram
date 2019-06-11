/*
Programmer: Hunter Johnson
Name: Encryption/Decryption Program
Info: Template for Encrypting/Decrypting files.
	  Just edit the Encrypt/Decrypt functions to be able to test your encryption. 
Class: CIS 167-01
Date: 1/24/17
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function Prototypes
char* encrypt(char [], long);
char* decrypt(char [], long);

int main() {
	long size;					// size of the file, uses tellg() to get file size - Open with ios::binary | ios::ate
	fstream dataFile;			// file stream object
	string fileName;			// name of file
	bool reading, writing;		// flags
	char choice;				// Users selection
	char * memblock = nullptr;	// Holds the contents of the file in memory

	do{
		reading = false;
		do {
			// fileName input
			cout << "Enter the name of the file to encrypt or decrypt: ";
			getline(cin, fileName);
			dataFile.open(fileName.c_str(), ios::in | ios::binary | ios::ate);	// Open file in input, binary, and ate mode

			if (!dataFile) // if it's unable to open
				cout << "Unable to open the file " << fileName << endl;
			else
			{
				reading = true;					// read flag ON
				cout << "File opened... Processing file..." << endl;
				size = dataFile.tellg();		// Gets the file size - Has to be opened with ios::binary | ios::ate
				memblock = new char[size];		// Dynamically Allocate a char array to hold the contents
				dataFile.seekg(0, ios::beg);	// Seek to beginning of the file
				dataFile.read(memblock, size);	// Read the contents from the file into the Dynamically Allocated array
				dataFile.close();				// Close the file
				cout << "The entire file content is in memory.";
			}
		} while (!reading);

		cout << endl;

		// Process the content in memblock
		// Encrypt/Decrypt the content
		cout << "Encrypt or Decrypt(e or d)?: ";
		cin >> choice;
		if (choice == 'e' | choice == toupper('e'))
		{
			// Encrypt file
			while (dataFile.good())
			{
				cout << "Encrypting..." << endl;
				encrypt(memblock, size);		// Encrypt the contents
				break;
			}
		}
		else {
			// Decrypt file
			while (dataFile.good())
			{
				cout << "Decrypting..." << endl;
				decrypt(memblock, size);		// Decrypt the contents
				break;
			}
		}
		
		writing = false;
		do {
			cout << "Enter the name of the file to send the output to: "; // to test the output
			cin.ignore();
			getline(cin, fileName);
			dataFile.open(fileName.c_str(), ios::out | ios::binary);	  // Open file in output and binary mode
			if (!dataFile)
				cout << "ERROR: File not opened." << endl;
			else {
				writing = true;						// write flag ON
				dataFile.clear();					// Optional
				dataFile.seekg(0, ios::beg);		// Seek to beginning of the file
				dataFile.write(memblock, size);		// Write contents to the file
				dataFile.close();					// Close the file
				cout << "Content written to file successful.\n";
				delete[] memblock;					// Free the Dynamically Allocated space
				memblock = nullptr;					// Keep this?
			}
		} while (!writing);

		// Get Input
		cout << "Would you like to continue?(y or n): ";
		cin >> choice;
		cin.ignore(); // Avoid the Phantom Line Error

	} while (choice == 'y' || choice == toupper('y'));

	cout << endl;
	cout << "Operations Successful!\n\n";
	system("pause");
	return 0;
}

//*******************************************************************************************************************
// encrypt - Accepts a pointer to a char array. It contains the contents of a datafile in memory, and its size.		*
//           This function will encrypt the data stored in the array, and then returns a pointer to the array.		*
//*******************************************************************************************************************
 char* encrypt(char contents[], long size) 
 {
	 // Simple Caesars Cypher
	 for (int i = 0; i < size; i++) 
	 {
	  contents[i] = static_cast<char>(contents[i] + 15); 
	 }

	return contents;
}

//*******************************************************************************************************************
// decrypt - Accepts a pointer to a char array. It contains the contents of a datafile in memory, and its size.		*
//			 This function will  decrypt the data stored in the array, and then return a pointer to the array.		*
//*******************************************************************************************************************
 char* decrypt(char contents[], long size) 
{
	 // Simple Caesars Cipher
	 for (int i = 0; i < size; i++) 
	 {
		 contents[i] = static_cast<char>(contents[i] - 15);
	 }
	 
	return contents;
}