#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Mean
{
	string data;
	Mean* pNext;
};

struct Word
{
	string tu;
	string loaitu;
	Mean* mean;
	string* Example[5];
	Word* pNext;
	Word* pPrev;
};

struct WordList
{
	Word* pHead = NULL;
	Word* pTail = NULL;
};