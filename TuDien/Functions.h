#pragma once
#include"Struct.h"
#include"Console.h"

#define X_POS_MAIN_FRAME 10
#define Y_POS_MAIN_FRAME 3
#define WIDTH_MAIN_FRAME 25
#define HEIGHT_MAIN_FRAME 25

#define X_POS_MAIN_FRAME_2 40
#define Y_POS_MAIN_FRAME_2 3
#define WIDTH_MAIN_FRAME_2 80
#define HEIGHT_MAIN_FRAME_2 25

#define X_POS_MAIN_FRAME_3 10
#define Y_POS_MAIN_FRAME_3 31
#define WIDTH_MAIN_FRAME_3 110
#define HEIGHT_MAIN_FRAME_3 5

#define COLOR_HIGHTLIGHT 1
#define COLOR_DEFAULT 51
#define COLOR_BACKGROUND_DEFAULT 51
#define COLOR_RED 12

#define UP 72
#define DOWN 80
#define ANPHA -32




void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//============ Xoa Tu a den b ==============
void DeleteBySpace(int a, int b)
{
	cout << string(b - a, ' ');
}

//============= Ve khung ==================

void DrawFrameMore(int x, int y)
{
	char a = 205;
	gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 2);
	cout << string(y - x, a);
}

void DrawFrame(int x, int y, int width, int height)
{
	char a = 201, b = 187, c = 188, d = 200, e = 205, f = 186;
	gotoXY(x, y);
	cout << a;
	cout << string(width - 3, e);
	cout << b;
	for (int i = 0; i < height - 3; i++)
	{
		gotoXY(x + width - 2, y + i + 1);
		cout << f;
		gotoXY(x, y + i + 1);
		cout << f;
	}
	gotoXY(x, y + height - 3);
	cout << d;
	cout << string(width - 3, e);
	cout << c;
}
void DrawMainFrame()
{
	DrawFrame(X_POS_MAIN_FRAME, Y_POS_MAIN_FRAME, WIDTH_MAIN_FRAME, HEIGHT_MAIN_FRAME);
	DrawFrameMore(X_POS_MAIN_FRAME + 1, X_POS_MAIN_FRAME + WIDTH_MAIN_FRAME - 2);
	DrawFrame(X_POS_MAIN_FRAME_2, Y_POS_MAIN_FRAME_2, WIDTH_MAIN_FRAME_2, HEIGHT_MAIN_FRAME_2);
	DrawFrame(X_POS_MAIN_FRAME_3, Y_POS_MAIN_FRAME_3, WIDTH_MAIN_FRAME_3, HEIGHT_MAIN_FRAME_3);
}

//============= Them Tu ===================
void InsertWord(WordList& list, Word* newword)
{
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = newword;
	}
	else
	{
		if (list.pHead->tu > newword->tu)
		{
			newword->pNext = list.pHead;
			list.pHead->pPrev = newword;
			list.pHead = newword;
		}
		else if(list.pTail->tu < newword->tu)
		{
			newword->pPrev = list.pTail;
			list.pTail->pNext = newword;
			list.pTail = newword;
		}
		else
		{
			for (Word* k = list.pHead; k != NULL; k = k->pNext)
			{
				if (newword->tu < k->tu)
				{
					Word* temp = k->pPrev;
					newword->pNext = k;
					k->pPrev = newword;
					temp->pNext = newword;
					newword->pPrev = temp;
					return;
				}
			}
		}
	}
}

//================= Them Nghia ====================
void InsertMean(Mean*& pHead, Mean* mean)
{
	if (pHead == NULL)
	{
		pHead = mean;
	}
	else
	{
		for (Mean* k = pHead; k != NULL; k = k->pNext)
		{
			if (k->pNext == NULL)
			{
				k->pNext = mean;
				return;
			}
		}
	}
}

int HashCode(string key)
{
	return (int)key[0] - 97;
}

//============== Doc Ghi File =================
Word* ReadLine(ifstream &FileIn)
{
	Word* p = new Word;
	p->pNext = NULL;
	p->pPrev = NULL;
	Mean* pHead = NULL;
	
	getline(FileIn, p->tu, '|');
	getline(FileIn, p->loaitu, '|');
	while (true)
	{
		string temp = "";
		getline(FileIn, temp, '|');
		if (temp == ".")
		{
			break;
		}
		else
		{
			Mean* mean = new Mean;
			mean->data = temp;
			mean->pNext = NULL;
			InsertMean(pHead, mean);
		}
	}
	p->mean = pHead;

	for (int i = 0; i < 5; i++)
	{
		string temp = "";
		getline(FileIn, temp, '|');
		if (temp.empty())
		{
			p->Example[i] = NULL;
		}
		else
		{
			p->Example[i] = new string;
			*(p->Example[i]) = temp;
		}
	}
	FileIn.ignore();
	return p;
}

void ReadFile(WordList HashTable[], ifstream &FileIn)
{
	FileIn.open("data.txt", ios_base::in);
	if (FileIn.fail())
	{
		cout << "Mo File khong thanh cong!";
		return;
	}
	while (!FileIn.eof())
	{
		Word* p = ReadLine(FileIn);
		int index = HashCode(p->tu);
		InsertWord(HashTable[index], p);	
	}
	FileIn.close();
}

void WriteFile(WordList HashTable[])
{
	ofstream FileOut;
	FileOut.open("data1.txt", ios_base::out);
	for (int i = 0; i < 26; i++)
	{
		for (Word* k = HashTable[i].pHead; k != NULL; k = k->pNext)
		{
			FileOut << k->tu << "|";
			FileOut << k->loaitu << "|";
			for (Mean* j = k->mean; j != NULL; j = j->pNext)
			{
				FileOut << j->data << "|";
			}
			FileOut << ".|";
			for (int i = 0; i < 5; i++)
			{
				if (k->Example[i] != NULL)
				{
					FileOut << *(k->Example[i]) << "|";
				}
				else
				{
					FileOut << "|";
				}
			}
			FileOut << "\n";
		}
	}
	FileOut.close();
}

//================= In ra console =====================
void OutputDisplay(WordList HashTable[])
{
	for (int i = 0; i < 26; i++)
	{
		for (Word* k = HashTable[i].pHead; k != NULL; k = k->pNext)
		{
			cout << "\n=====================\n";
			cout << "\ntu: " << k->tu;
			cout << "\nloai tu: " << k->loaitu;
			cout << "\nNghia: ";
			for (Mean* j = k->mean; j != NULL; j = j->pNext)
			{
				cout << j->data << "	";
			}
			cout << "\nVi du: ";
			for (int i = 0; i < 5; i++)
			{
				if (k->Example[i] != NULL)
				{
					cout << *(k->Example[i]) << "	";
				}
			}
		}
	}
}

//=============== Xoa Tu ==================
void FreeWord(Word*& word)
{
	Mean* del = NULL;
	Mean* mean = word->mean;
	while (!mean)
	{
		del = mean;
		mean = del->pNext;
		delete del;
	}
	for (int i = 0; i < 5; i++)
	{
		delete word->Example[i];
	}
	delete word;
}
void RemoveWord(WordList HashTable[], Word*& WordDel)
{
	int index = HashCode(WordDel->tu);
	Word* Head = HashTable[index].pHead;
	Word* Tail = HashTable[index].pTail;
	if (WordDel == Head)
	{
		if (!Head) return;
		else if (!Head->pNext)
		{
			Head = Tail = NULL;
		}
		else
		{
			Head = Head->pNext;
			Head->pPrev = NULL;
		}
	}
	else if (WordDel == Tail)
	{
		Tail->pPrev = Tail;
		Tail->pNext = NULL;
	}
	else
	{
		WordDel->pPrev->pNext = WordDel->pNext; //Thac mac..........
		WordDel->pNext->pPrev = WordDel->pPrev;
	}
	HashTable[index].pHead = Head;
	HashTable[index].pTail = Tail;
	FreeWord(WordDel);
}

//============ Tim Tu Ben Trai Va Phai Cua Tu Hien Tai =================
Word* FindWordLeft(WordList HashTable[], Word* wordPresent)
{
	int index = HashCode(wordPresent->tu);
	if (wordPresent->pPrev != NULL)
	{
		return wordPresent->pPrev;
	}
	for (int i = index - 1; i >= 0; i--)
	{
		if (HashTable[i].pTail != NULL)
		{
			return HashTable[i].pTail;
		}
	}
	return NULL;
}

Word* FindWordRight(WordList HashTable[], Word* wordPresent)
{
	if (wordPresent != NULL)
	{
		int index = HashCode(wordPresent->tu);
		if (wordPresent->pNext != NULL)
		{
			return wordPresent->pNext;
		}
		for (int i = index + 1; i < 26; i++)
		{
			if (HashTable[i].pHead != NULL)
			{
				return HashTable[i].pHead;
			}
		}
	}
	return NULL;
}

//=========== Tim Tu Dau Frame Và Cuoi Frame ==================
//Tim tu dau tien trong HashTable
Word* FindWordFirstFrame(WordList HashTable[])
{
	for (int i = 0; i < 26; i++)
	{
		if (HashTable[i].pHead != NULL)
		{
			return HashTable[i].pHead;
		}
	}
	return NULL;
}

//Tim tu dau tien trong HashTable tu string
Word* FindWordFirstFrameFromString(WordList HashTable[], string str)
{
	int index = HashCode(str);
	for (Word* k = HashTable[index].pHead; k != NULL; k = k->pNext)
	{
		if (k->tu.find(str) == 0)
		{
			return k;
		}
	}
	return NULL;
}

//Tim tu cuoi cung trong HashTable tu string
Word* FindWordLastFrameFromString(WordList HashTable[], Word* wordBegin, string str)
{
	Word* run = wordBegin, * temp = NULL;
	for (int i = 0; i < (HEIGHT_MAIN_FRAME - 7) && run != NULL; i++)
	{
		temp = FindWordRight(HashTable, run);
		if (temp != NULL && temp->tu.find(str) == 0)
		{
			run = temp;
		}
		else
		{
			return run;
		}
	}
	return run;
}

//Danh sach tu hien thi dung kich co Frame
void ShowWordList(WordList HashTable[], Word* wordPresent, Word* wordBegin, Word* wordEnd)
{
	int line = 0;
	for (Word* k = wordBegin; k != FindWordRight(HashTable, wordEnd); k = FindWordRight(HashTable, k))
	{
		gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 3 + line);
		if (k == wordPresent)
		{
			
			setBackgroundColor(COLOR_HIGHTLIGHT);
			cout << k->tu;
			DeleteBySpace(k->tu.length(), WIDTH_MAIN_FRAME - 3);			
			setBackgroundColor(51);
			
		}
		else
		{
			cout << k->tu;
			DeleteBySpace(k->tu.length(), WIDTH_MAIN_FRAME - 3);
		}
		line++;
	}

	for (int i = line; i < HEIGHT_MAIN_FRAME - 6; i++)
	{
		gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 3 + i);
		DeleteBySpace(0, WIDTH_MAIN_FRAME - 3);
	}
}

//============ Thong Tin Cua Tu ==================
void ShowInfoWord(Word* wordPresent)
{
	//In tu
	gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 2);
	cout << "Tu: ";
	if (wordPresent->tu.empty())
	{
		setBackgroundColor(COLOR_RED);
		cout << "Rong!";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	}
	else
	{
		cout << wordPresent->tu;
	}
	DeleteBySpace(wordPresent->tu.length() + 5, WIDTH_MAIN_FRAME_2 - 3);

	//In loai tu
	gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 6);
	cout << "Loai tu: ";
	if (wordPresent->loaitu.empty())
	{
		setBackgroundColor(COLOR_RED);
		cout << "Rong!";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	}
	else
	{
		cout << wordPresent->loaitu;
	}
	DeleteBySpace(wordPresent->loaitu.length() + 10, WIDTH_MAIN_FRAME_2 - 3);

	//In nghia
	int line = 0;
	gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 10);
	cout << "Nghia: ";
	if (wordPresent->mean == NULL)
	{
		setBackgroundColor(COLOR_RED);
		cout << "Rong!";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		DeleteBySpace(13, WIDTH_MAIN_FRAME_2 - 3);
	}
	else
	{
		for (Mean* k = wordPresent->mean; k != NULL; k = k->pNext)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 10 + line);
			cout << k->data;
			DeleteBySpace(k->data.length() + 8, WIDTH_MAIN_FRAME_2 - 3);
			line++;
		}
	}

	//xoa nghia thua tu lan chay truoc
	for (int i = line - 1; i < 5; i++)
	{
		gotoXY(X_POS_MAIN_FRAME_2 + 1, Y_POS_MAIN_FRAME_2 + 11 + i);
		DeleteBySpace(0, WIDTH_MAIN_FRAME_2 - 3);
	}

	//In vi du
	int count = 0;
	gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 16);
	cout << "Vi du: ";
	if (wordPresent->Example[0] == NULL)
	{
		setBackgroundColor(COLOR_RED);
		cout << "Rong!";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		DeleteBySpace(13, WIDTH_MAIN_FRAME_2 - 3);
	}
	else
	{
		for (int i = 0; i < 5 && wordPresent->Example[i] != NULL; i++)
		{
			count = i;
			gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 16 + i);
			cout << *(wordPresent->Example[i]);
			DeleteBySpace((wordPresent->Example[i])->length() + 8, WIDTH_MAIN_FRAME_2 - 3);
		}
	}

	//xoa vidu thua tu lan chay truoc
	for (int i = count + 1; i < 5; i++)
	{
		gotoXY(X_POS_MAIN_FRAME_2 + 1, Y_POS_MAIN_FRAME_2 + 16 + i);
		DeleteBySpace(0, WIDTH_MAIN_FRAME_2 - 3);
	}
}

//============ MENU Chinh =================
void Menu(WordList HashTable[])
{
	string str = "";
	Word* wordBegin = NULL, * wordEnd = NULL, * wordPresent = NULL;
	bool check = true;

	while (true)
	{
		if (check)
		{
			if (str.empty())
			{
				wordBegin = FindWordFirstFrame(HashTable);
				wordPresent = wordBegin;
				wordEnd = FindWordLastFrameFromString(HashTable, wordBegin, str);
			}
			else
			{
				wordBegin = FindWordFirstFrameFromString(HashTable, str);
				wordPresent = wordBegin;
				wordEnd = FindWordLastFrameFromString(HashTable, wordBegin, str);
			}
		}
		ShowWordList(HashTable, wordPresent, wordBegin, wordEnd);
		ShowInfoWord(wordPresent);

		gotoXY(X_POS_MAIN_FRAME + 1 + str.length(), Y_POS_MAIN_FRAME + 1);

		char key = _getch();
		if (key == -32)
		{
			key = _getch();
			if (key == UP)
			{
				if (FindWordLeft(HashTable, wordPresent) != NULL)
				{
					if (wordPresent == wordBegin)
					{
						wordBegin = FindWordLeft(HashTable, wordBegin);
						wordEnd = FindWordLeft(HashTable, wordEnd);
					}
					wordPresent = FindWordLeft(HashTable, wordPresent);
				}
				check = false;
			}
			else if (key == DOWN)
			{
				if (FindWordRight(HashTable, wordPresent) != NULL)
				{
					if (wordPresent == wordEnd)
					{
						wordBegin = FindWordRight(HashTable, wordBegin);
						wordEnd = FindWordRight(HashTable, wordEnd);
					}
					wordPresent = FindWordRight(HashTable, wordPresent);
				}
				check = false;
			}
		}
		else if (((key >= 'a' && key <= 'z') || ('A' <= key <= 'Z')))
		{
			cout << key;
			str += key;
			check = true;
		}
		
	}
}