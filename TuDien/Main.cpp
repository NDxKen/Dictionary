#include"ReadWriteFile.h"

int main()
{
	SetConsoleTitle("Dictionary");
	resizeConsole(130, 35);
	ifstream FileIn;
	ofstream FileOut;
	WordList HashTable[26];
	ReadFile(FileIn, HashTable);
	Menu(HashTable);
	WriteFile(FileOut, HashTable);
}