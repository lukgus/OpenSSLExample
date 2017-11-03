#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

#include <openssl\conf.h>
#include <openssl\evp.h>
#include <openssl\err.h>
#include <openssl\sha.h>

using namespace std;

const char* PLAIN_TEXT_FILE = "plaintext.txt";
const char* HASH_FILE = "hash.txt";

const int MAX_LENGTH = 10;

ofstream plainTextFile;
ofstream hashTextFile;

SHA256_CTX ctx;

void WritePlainTextPasswordToFile(int length)
{
	char letters[MAX_LENGTH];
	for (int i = 0; i < length; i++)
	{
		letters[i] = 'a';
	}

	while (letters[length-1] <= 'z')
	{
		for (int i = 0; i < length; i++)
		{
			plainTextFile << letters[i];
		}

		plainTextFile << "\n";

		letters[0]++;

		for (int i = 0; i < length - 1; i++)
		{
			if (letters[i] <= 'z') break;

			letters[i] = 'a';
			letters[i + 1]++;
		}
	}
}

void PrintPlainTextToHash(const char* plainText)
{
	unsigned char digest[SHA256_DIGEST_LENGTH];
	SHA256_Update(&ctx, plainText, strlen(plainText));
	SHA256_Final(digest, &ctx);

	char hash[SHA256_DIGEST_LENGTH * 2 + 1];
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(&(hash[i * 2]), "%02x", (unsigned int)(digest[i]));
	}

	hashTextFile << hash;
}

void WriteHashPasswordToFile(int length)
{
	char letters[MAX_LENGTH];
	for (int i = 1; i < MAX_LENGTH; i++)
	{
		letters[i] = '\0';
	}
	for (int i = 0; i < length; i++)
	{
		letters[i] = 'a';
	}

	while (letters[length - 1] <= 'z')
	{
		for (int i = 0; i < length; i++)
		{
			hashTextFile << letters[i];
		}
		hashTextFile << "\t";
		PrintPlainTextToHash(&letters[0]);
		hashTextFile << "\n";

		letters[0]++;

		for (int i = 0; i < length - 1; i++)
		{
			if (letters[i] <= 'z') break;

			letters[i] = 'a';
			letters[i + 1]++;
		}
	}
}

void WritePlainTextValues()
{
	plainTextFile.open(PLAIN_TEXT_FILE);
	if (!plainTextFile.is_open())
	{
		printf("Failed to open plain text file.\n");
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		WritePlainTextPasswordToFile(i);
	}

	plainTextFile.close();
}

void WriteHashValues()
{
	hashTextFile.open(HASH_FILE);
	if (!hashTextFile.is_open())
	{
		printf("Failed to open hash text file.\n");
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		WriteHashPasswordToFile(i);
	}

	hashTextFile.close();
}

int main()
{
	SHA256_Init(&ctx);

	WriteHashValues();

	return 0;
}
