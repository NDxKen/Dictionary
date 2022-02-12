#pragma once
#include"Functions.h"

Word* ReadOneLine(ifstream &FileIn)
{
	Word* p = CreateWord();
	getline(FileIn, p->word, '|');
	getline(FileIn, p->typeWord, '|');
	while (true)
	{
		string temp;
		getline(FileIn, temp, '|');
		if (temp == ".") break;
		else
		{
			Mean* k = new Mean;
			k->data = temp;
			k->pNext = NULL;
			InsertMean(p->mean, k);
		}
	}

	for(int i = 0; i < 6; i++)
	{
		string temp;
		getline(FileIn, temp, '|');
		if (temp == ".") break;
		else
		{
			p->Example[i] = new string;
			*(p->Example[i]) = temp;
		}
	}
	FileIn.ignore();
	return p;
}

void ReadFile(ifstream& FileIn, WordList HashTable[])
{
	FileIn.open("test.txt", ios::in);
	if (FileIn.fail()) return;
	while (!FileIn.eof())
	{
		Word* p = ReadOneLine(FileIn);
		int idx = HashFunction(p->word);
		InsertWord(HashTable[idx], p);
	}
	FileIn.close();
}

void WriteFile(ofstream& FileOut, WordList HashTable[])
{
	FileOut.open("test.txt", ios::out);
	for (int i = 0; i < 26; i++)
	{
		for (Word* k = HashTable[i].pHead; k != NULL; k = k->pNext)
		{
			FileOut << k->word << "|";
			FileOut << k->typeWord << "|";
			for (Mean* j = k->mean; j != NULL; j = j->pNext)
			{
				FileOut << j->data << "|";
			}
			FileOut << ".|";
			for (int i = 0; i < 5 && k->Example[i] != NULL; i++)
			{
				FileOut << (*k->Example[i]) << "|";
			}
			FileOut << ".|";
			if(FindWordRight(HashTable, k) != NULL)
				FileOut << endl;
		}
	}
	FileOut.close();
}