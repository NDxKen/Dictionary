#include"Functions.h"

int main()
{
	//resizeConsole(130, 35);
	ifstream FileIn;
	WordList HashTable[26];
	ReadFile(HashTable, FileIn);
	/*WriteFile(HashTable);*/
	DrawMainFrame();
	Menu(HashTable);
}