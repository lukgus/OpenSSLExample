#include <fstream>
#include <iostream>

using namespace std;

const char* PLAIN_TEXT_FILE = "plaintext.txt";
const char* HASH_FILE = "hash.txt";

const int MAX_LENGTH = 10;

ofstream plainTextFile;
ofstream hashTextFile;

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
			// printf("%c", letters[i]);
			plainTextFile << letters[i];
		}

		// printf("\n");
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

void PlainTextToHash()
{

}

void WriteHashPasswordToFile(int length)
{
	char letters[MAX_LENGTH];
	for (int i = 0; i < length; i++)
	{
		letters[i] = 'a';
	}

	while (letters[length - 1] <= 'z')
	{
		for (int i = 0; i < length; i++)
		{
			printf("%c", letters[i]);
		}

		printf("\n");
		// hashTextFile << "\n";


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

	for (int i = 0; i <= 4; i++)
	{
		WriteHashPasswordToFile(i);
	}

	hashTextFile.close();
}

int main()
{
	WritePlainTextValues();

	return 0;
}
