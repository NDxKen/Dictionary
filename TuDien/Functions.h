#pragma once
#include"SubProcessing.h"

//================== Khoi Tao Tu ====================
Word* CreateWord()
{
	Word* word = new Word;
	word->pNext = NULL;
	word->pPrev = NULL;
	word->mean = NULL;
	for (int i = 0; i < 5; i++)
	{
		word->Example[i] = NULL;
	}
	return word;
}

//================== Them Tu Tu File==========================
void InsertWord(WordList &list, Word* newword)
{
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = newword;
	}
	else
	{
		if (list.pHead->word > newword->word)
		{
			newword->pNext = list.pHead;
			list.pHead->pPrev = newword;
			list.pHead = newword;
		}
		else if(list.pTail->word < newword->word)
		{
			newword->pPrev = list.pTail;
			list.pTail->pNext = newword;
			list.pTail = newword;
		}
		else
		{
			for (Word* k = list.pHead; k != NULL; k = k->pNext)
			{
				if (newword->word < k->word)
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

//================= Them Nghia Tu File ======================
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

//============ Tim Tu Ben Trai Va Phai Cua Tu Hien Tai =================
Word* FindWordLeft(WordList HashTable[], Word* wordPresent)
{
	if (wordPresent != NULL)
	{
		int index = HashFunction(wordPresent->word);
		if (wordPresent->pPrev != NULL)
		{
			return wordPresent->pPrev;
		}
		else
		{
			for (int i = index - 1; i >= 0; i--)
			{
				if (HashTable[i].pTail != NULL)
				{
					return HashTable[i].pTail;
				}
			}
		}
	}
	return NULL;
}

Word* FindWordRight(WordList HashTable[], Word* wordPresent)
{
	if (wordPresent != NULL)
	{
		int index = HashFunction(wordPresent->word);
		if (wordPresent->pNext != NULL)
		{
			return wordPresent->pNext;
		}
		else
		{
			for (int i = index + 1; i < 26; i++)
			{
				if (HashTable[i].pHead != NULL)
				{
					return HashTable[i].pHead;
				}
			}
		}
	}
	return NULL;
}

//=========== Tim Tu Dau Frame Và Cuoi Frame ==================
//============ Ham tim chuoi con trong chuoi cha =====================
int isMatching(string strMax, string strMin)
{
	if (strMin.length() == 0) return 0;
	for (int i = 0; i < strMax.length(); i++)
	{
		if (strMax[i] == strMin[0])
		{
			int count = 0;
			for (int j = 0; j < strMin.length(); j++)
			{
				if (strMin[j] == strMax[j + i])
				{
					count++;
				}
				else break;
			}
			if (count == strMin.length()) return i;
		}
	}
	return -1;
}

//Tim tu dau tien trong HashTable tu string
Word* FindWordFirstFrame(WordList HashTable[], string str)
{
	if (str.empty())
	{
		for (int i = 0; i < 26; i++)
		{
			if (HashTable[i].pHead != NULL) return HashTable[i].pHead;
		}
	}
	else
	{
		int index = HashFunction(str);
		for (Word* k = HashTable[index].pHead; k != NULL; k = k->pNext)
		{
			if (isMatching(k->word, str) == 0) return k;
		}
		return NULL;
	}
}

//Tim tu cuoi cung trong HashTable tu string
Word* FindWordLastFrame(WordList HashTable[], Word* wordBegin, string str)
{
	Word* run = wordBegin, * temp = NULL;
	for (int i = 0; i < HEIGHT_MAIN_FRAME - 7; i++)
	{
		temp = FindWordRight(HashTable, run);
		if (temp != NULL && isMatching(temp->word, str) == 0) run = temp;
		else return run;
	}
	return run;
}

//============== Hien Thi Danh Sach Tu ===================
void ShowWordList(WordList HashTable[], Word* wordPresent, Word* wordBegin, Word* wordEnd)
{
	int line = 0;
	for (Word* k = wordBegin; k != FindWordRight(HashTable, wordEnd); k = FindWordRight(HashTable, k))
	{
		gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 3 + line);
		if (k == wordPresent)
		{			
			setBackgroundColor(COLOR_HIGHTLIGHT);
			cout << k->word;
			DeleteBySpace(k->word.length(), WIDTH_MAIN_FRAME - 3);
			setBackgroundColor(51);			
		}
		else
		{
			cout << k->word;
			DeleteBySpace(k->word.length(), WIDTH_MAIN_FRAME - 3);
		}
		line++;
	}

	for (int i = line; i < HEIGHT_MAIN_FRAME - 6; i++)
	{
		gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 3 + i);
		DeleteBySpace(0, WIDTH_MAIN_FRAME - 3);
	}
	DeleteNoti();
}

//============ Hien Thi Thong Tin Cua Tu ==================
// Xoa Thong Tin Cua Tu
void RemoveInfoWord()
{
	for (int i = 0; i < HEIGHT_MAIN_FRAME - 4; i++)
	{
		gotoXY(X_POS_MAIN_FRAME_2 + 1, Y_POS_MAIN_FRAME_2 + 1 + i);
		DeleteBySpace(0, WIDTH_MAIN_FRAME_2 - 3);
	}
}

void ShowInfoWord(Word* wordPresent)
{
	if (wordPresent != NULL)
	{
		//In tu
		gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 2);
		cout << "Tu: ";
		if (wordPresent->word.empty())
		{
			setBackgroundColor(COLOR_RED);
			cout << "Rong!";
			setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		}
		else
		{
			cout << wordPresent->word;
		}
		DeleteBySpace(wordPresent->word.length() + 10, WIDTH_MAIN_FRAME_2 - 3);

		//In loai tu
		gotoXY(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME_2 + 6);
		cout << "Loai tu: ";
		if (wordPresent->typeWord.empty())
		{
			setBackgroundColor(COLOR_RED);
			cout << "Rong!";
			setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		}
		else
		{
			cout << wordPresent->typeWord;
		}
		DeleteBySpace(wordPresent->typeWord.length() + 15, WIDTH_MAIN_FRAME_2 - 3);

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
			line++;
		}
		else
		{
			int line2 = 0, line3 = 0;
			Mean* pul2 = NULL, * pul3 = NULL;
			for (Mean* k = wordPresent->mean; k != NULL; k = k->pNext)
			{
				gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 10 + line);
				cout << k->data;
				DeleteBySpace(k->data.length() + 8, WIDTH_MAIN_FRAME_2 - 3);
				line++;

				pul2 = k;
				if (line == 5) break;
			}
			for (Mean* k = pul2->pNext; k != NULL; k = k->pNext)
			{
				gotoXY(X_POS_MAIN_FRAME_2 + 30, Y_POS_MAIN_FRAME + 10 + line2);
				cout << k->data;
				line2++;

				pul3 = k;
				if (line2 == 5) break;
			}
			if (pul3 != NULL)
			{
				for (Mean* k = pul3->pNext; k != NULL; k = k->pNext)
				{
					gotoXY(X_POS_MAIN_FRAME_2 + 52, Y_POS_MAIN_FRAME_2 + 10 + line3);
					cout << k->data;
					line3++;
				}
			}
			
		}
		//xoa nghia thua tu lan chay truoc
		for (int i = line - 1; i < 4; i++)
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
			for (int i = 0; i < 5; i++)
			{
				if (wordPresent->Example[i] == NULL) break;
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
	else
	{
		DrawFrame(X_POS_MAIN_FRAME_2 + 2, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 40, 5);
		gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
		setBackgroundColor(COLOR_RED);
		cout << "TU KHONG TON TAI!";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		RemoveInfoWord();
	}
}

//============================= Xu Ly Chinh Sua Tu ===============================
// Ham sua loai tu
void EditWordType(string& wordType, char& key, int &tab)
{
	//xu ly guide
	DeleteGuide();
	ShowGuideWordAndTypeWord();


	while (true)
	{
		string temp = wordType;
		Nocursortype(false);
		gotoXY(X_POS_MAIN_FRAME_2 + 11, Y_POS_MAIN_FRAME + 6);
		setBackgroundColor(COLOR_HIGHTLIGHT);
		if (temp.empty())
		{
			cout << "NHAP F3 DE THEM LOAI TU     ";
		}
		else
		{
			cout << temp;
			DeleteBySpace(temp.length(), 28);
		}
		setBackgroundColor(COLOR_DEFAULT);

		key = _getch();

		if (key == 0 || key == -32)
		{
			key = _getch();
			if (key == F2)
			{
				return;
			}
			else if (key == F4 || key == F3)
			{
				char x;
				while (true)
				{
					Nocursortype(true);
					gotoXY(X_POS_MAIN_FRAME_2 + 11 + temp.length(), Y_POS_MAIN_FRAME_2 + 6);
					x = _getch();
					if (x == -32 || x == 0)
					{
						x = _getch();
					}
					else if (x == BACKSPACE && !temp.empty())
					{
						temp.erase(temp.length() - 1, 1);
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << "\b ";
						setBackgroundColor(COLOR_DEFAULT);
					}
					else if (((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x == ' ')) && temp.length() < 28)
					{
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << x;
						temp += x;
						DeleteBySpace(temp.length(), 28);
						setBackgroundColor(COLOR_DEFAULT);
					}
					else if (x == ENTER && !temp.empty())
					{
						Nocursortype(false);
						Standardized(temp);
						wordType = temp;
						break;
					}
					else if (x == ESC)
					{
						break;
					}
				}
			}
		}
		else if (key == TAB)
		{
			return;
		}
		else if (key == ESC)
		{
			tab = -1;
			return;
		}
	}
}

// Ham tra ve so luong nghia
int recCount(Mean* mean)
{
	int size = -1;
	for (Mean* k = mean; k != NULL; k = k->pNext)
	{
		size++;
	}
	return size;
}

// Ham tim tu ben trai va ben phai
Mean* FindMeanLeft(Mean* mean, Mean* meanPresent)
{
	Mean* g = NULL;
	for (Mean* k = mean; k != NULL; k = k->pNext)
	{
		if (k == meanPresent)
		{
			return g;
		}
		g = k;
	}
	return NULL;
}

Mean* FindMeanRight(Mean* meanPresent)
{
	if (meanPresent != NULL) return meanPresent->pNext;
	return NULL;
}

// Tim nghia dau va nghia cuoi bang kich thuoc khung
Mean* FindMeanFirstFrame(Mean* mean)
{
	return mean;
}

Mean* FindMeanLastFrame(Mean* meanBegin)
{
	Mean* k = meanBegin;
	int count = 0;
	for (; k != NULL && count < 2; k = k->pNext)
	{
		count++;
	}
	return k;
}

//tim nghia dau dua vao nghia cuoi
Mean* FindMeanFirstFrameBaseOnMeanLastFrame(Mean* mean, Mean* meanEnd)
{
	if (recCount(mean) < 2)
	{
		return mean;
	}
	else
	{
		for (Mean* k = mean; k != NULL; k = k->pNext)
		{
			if (k->pNext->pNext == meanEnd)
			{
				return k;
			}
		}
	}
}

// Ham hien thi danh sach nghia
void ShowMeanList(Mean* mean, Mean* meanBegin, Mean* meanEnd, Mean* meanPresent)
{
	int line = -1;
	if (meanBegin != NULL)
	{
		for (Mean* k = meanBegin; k != FindMeanRight(meanEnd); k = FindMeanRight(k))
		{
			line++;
			gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 11 + line);
			if (k == meanPresent)
			{
				setBackgroundColor(COLOR_HIGHTLIGHT);
				cout << k->data;
				DeleteBySpace(k->data.length(), 30);
				setBackgroundColor(COLOR_DEFAULT);
			}
			else
			{
				cout << k->data;
				DeleteBySpace(k->data.length(), 30);
			}
		}
		for (int i = line + 1; i < 3; i++)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 8, Y_POS_MAIN_FRAME_2 + 11 + i);
			DeleteBySpace(0, 40);
		}
	}
	else
	{
		gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 10);
		setBackgroundColor(COLOR_HIGHTLIGHT);
		cout << "NHAP F3 DE THEM NGHIA     ";
		setBackgroundColor(COLOR_DEFAULT);
	}
}

// Ham xoa tu
void RemoveMean(Mean*& mean, string meanDel)
{
	Mean* pTemp = mean, *g = NULL;
	if (mean == NULL) return;
	else
	{
		if (mean->data == meanDel)
		{
			mean = mean->pNext;
			delete pTemp;
		}
		else
		{
			for (Mean* k = mean; k != NULL; k = k->pNext)
			{
				if (k->data == meanDel)
				{
					g->pNext = k->pNext;
					return;
				}
				g = k;
			}
		}
	}
}

// Ham xu ly chinh chinh sua tu
void EditMean(Mean*& mean, char& key, int& tab)
{
	//xu ly guide
	DeleteGuide();
	ShowGuideMeanAndExample();

	Mean *meanBegin = FindMeanFirstFrame(mean), *meanPresent = meanBegin, *meanEnd = FindMeanLastFrame(meanBegin);
	int linePosPresent = 0, linePosBegin = 0;
	while (true)
	{
		// xoa console nghia
		for (int i = 0; i < 6; i++)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 8, Y_POS_MAIN_FRAME_2 + 10 + i);
			DeleteBySpace(0, WIDTH_MAIN_FRAME_2 - 11);
		}

		if (meanBegin != NULL)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME_2 + 10);
			setBackgroundColor(COLOR_GREEN_LIGHT);
			cout << " ^ ";
			gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME_2 + 14);
			cout << " v ";
			setBackgroundColor(COLOR_DEFAULT);
		}

		ShowMeanList(mean, meanBegin, meanEnd, meanPresent);

		key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
			if (key == UP)
			{
				if (FindMeanLeft(mean, meanPresent) != NULL)
				{
					if (meanBegin == meanPresent)
					{
						meanBegin = FindMeanLeft(mean, meanBegin);
						meanEnd = FindMeanLeft(mean, meanEnd);
						linePosBegin--;
					}	
					meanPresent = FindMeanLeft(mean, meanPresent);
					linePosPresent--;
				}
			}
			else if (key == DOWN)
			{
				if (FindMeanRight(meanPresent) != NULL)
				{
					if (meanEnd == meanPresent)
					{
						meanBegin = FindMeanRight(meanBegin);
						meanEnd = FindMeanRight(meanEnd);
						linePosBegin++;
					}
					meanPresent = FindMeanRight(meanPresent);
					linePosPresent++;
				}
			}
			else if (key == F2)
			{
				return;
			}
			else if (key == F3)
			{
				string meanMore;
				Nocursortype(true);
				gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 15);
				cout << "THEM NGHIA: ";
				char k;
				while (true)
				{
					k = _getch();
					if (k == 0 || k == -32)
					{
						k = _getch();
					}
					if (((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z') || k == ' ') && meanMore.length() < 30)
					{
						cout << k;
						meanMore += k;
					}
					else if (k == BACKSPACE && !meanMore.empty())
					{
						meanMore.erase(meanMore.length() - 1, 1);
						cout << "\b \b";
					}
					else if (k == ENTER && !meanMore.empty())
					{
						Nocursortype(false);
						Standardized(meanMore);
						Mean* temp = new Mean;
						temp->data = meanMore;
						temp->pNext = NULL;
						InsertMean(mean, temp);

						// cap nhat vi tri nghia moi them
						meanEnd = meanPresent = temp;
						meanBegin = FindMeanFirstFrameBaseOnMeanLastFrame(mean, meanEnd);

						linePosPresent = recCount(mean);
						if (recCount(mean) <= 2) linePosBegin = 0;
						else linePosBegin = linePosPresent - 2;
						break;
					}
					else if (k == ESC)
					{
						Nocursortype(false);
						break;
					}
				}
			}
			else if (key == F4)
			{
				string meanEdit = meanPresent->data;
				Nocursortype(true);
				gotoXY(X_POS_MAIN_FRAME_2 + 9 + meanEdit.length(), Y_POS_MAIN_FRAME_2 + 11 + linePosPresent - linePosBegin);
				char k;
				while (true)
				{
					k = _getch();
					if (k == 0 || k == -32)
					{
						k = _getch();
					}
					else if (((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z') || k == ' ') && meanEdit.length() < 30)
					{
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << k;
						meanEdit += k;
						setBackgroundColor(COLOR_DEFAULT);
					}
					else if (k == BACKSPACE && !meanEdit.empty())
					{
						setBackgroundColor(COLOR_HIGHTLIGHT);
						meanEdit.erase(meanEdit.length() - 1, 1);
						cout << "\b \b";
						setBackgroundColor(COLOR_DEFAULT);
					}
					else if (k == ENTER && !meanEdit.empty())
					{
						Nocursortype(false);
						Standardized(meanEdit);
						meanPresent->data = meanEdit;
						break;
					}
					else if (k == ESC)
					{
						break;
					}
				}

			}
			else if (key == DELETE && meanBegin != NULL)
			{
				if (ShowMenuConfirmDelete() == ENTER)
				{
					RemoveMean(mean, meanPresent->data);

					meanBegin = FindMeanFirstFrame(mean);
					meanPresent = meanBegin;
					meanEnd = FindMeanLastFrame(meanBegin);

					linePosBegin = linePosPresent = 0;
				}
			}
		}
		else if (key == TAB)
		{
			return;
		}
		else if (key == ESC)
		{
			tab = -1;
			return;
		}
	}
}

// Ham hien thi danh sach vi du
void ShowExampleList(string* Example[], int posExPresent, int &ExMax)
{
	if (Example[0] != NULL)
	{
		for (int i = 0; i < 5 && Example[i] != NULL; i++)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 16 + i);
			if (posExPresent == i)
			{
				setBackgroundColor(COLOR_HIGHTLIGHT);
				cout << *Example[i];
				DeleteBySpace((*Example[i]).length(), 60);
				setBackgroundColor(COLOR_DEFAULT);
			}
			else
			{
				cout << *Example[i];
				DeleteBySpace((*Example[i]).length(), 60);
			}
			ExMax++;
		}
	}
	else
	{
		gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 16);
		setBackgroundColor(COLOR_HIGHTLIGHT);
		cout << "NHAP F3 DE THEM VI DU     ";
		setBackgroundColor(COLOR_DEFAULT);
	}
}

// Ham xoa vidu
void RemoveExample(string *Example[], int &posExPresent, int&posExMax)
{
	string* temp = Example[posExPresent];
	for (int i = posExPresent; i < 4; i++)
	{
		Example[i] = Example[i + 1];
	}
	Example[posExMax - 1] = NULL;
	posExMax--;
	delete temp;
}

// Ham chinh sua vi du
void EditExample(string *Example[], int &tab, char &key)
{
	//xu ly guide
	DeleteGuide();
	ShowGuideMeanAndExample();

	int posExPresent = 0;
	while (true)
	{
		for (int i = 0; i < 6; i++)
		{
			gotoXY(X_POS_MAIN_FRAME_2 + 9, Y_POS_MAIN_FRAME_2 + 16 + i);
			DeleteBySpace(0, 60);
		}
		int ExMax = 0; // so luong vidu
		ShowExampleList(Example, posExPresent, ExMax);

		key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
			if (key == UP)
			{
				if (posExPresent > 0)
				{
					posExPresent--;
				}
			}
			else if (key == DOWN)
			{
				if (posExPresent < ExMax - 1)
				{
					posExPresent++;
				}
			}
			else if (key == F2)
			{
				return;
			}
			else if (key == F3)
			{
				if (Example[4] != NULL)
				{
					DrawFrame(X_POS_MAIN_FRAME_2, Y_POS_MAIN_FRAME_2 + HEIGHT_MAIN_FRAME - 1, 43, 5);
					gotoXY(X_POS_MAIN_FRAME_2 + 5, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
					setBackgroundColor(COLOR_RED);
					cout << "  KHONG THE THEM, TOI DA 5 VI DU  ";
					setBackgroundColor(COLOR_DEFAULT);
					Sleep(1000);
					DeleteNoti();
				}
				else
				{
					string ExMore;
					gotoXY(X_POS_MAIN_FRAME_2 + 15, Y_POS_MAIN_FRAME_2 + 21);
					cout << "THEM VI DU: ";
					char k;
					while (true)
					{
						Nocursortype(true);
						k = _getch();
						if (k == -32 || k == 0)
						{
							k = _getch();
						}
						else if (((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z') || (k >= '1' && k <= '9') || (k == ' ') || (k == '.') || (k == ',') || (k == '?') || (k == '!')) && ExMore.length() <= 60)
						{
							cout << k;
							ExMore += k;
						}
						else if (k == BACKSPACE && !ExMore.empty())
						{
							ExMore.erase(ExMore.length() - 1, 1);
							cout << "\b \b";
						}
						else if (k == ENTER && !ExMore.empty())
						{
							Nocursortype(false);
							Standardized(ExMore);
							Example[ExMax] = new string;
							(*Example[ExMax]) = ExMore;
							posExPresent = ExMax;
							ExMax++;
							break;
						}
						else if (k == ESC)
						{
							Nocursortype(false);
							break;
						}
					}
				}
			}
			else if (key == F4)
			{
				gotoXY(X_POS_MAIN_FRAME_2 + 9 + (*Example[posExPresent]).length(), Y_POS_MAIN_FRAME_2 + 16 + posExPresent);
				Nocursortype(true);
				char x;
				while (true)
				{
					Nocursortype(true);
					x = _getch();
					if (x == 0 || x == -32)
					{
						x = _getch();
					}
					if (((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x <= '0' && x >= '9') || (x == ' ') || (x == '.') || (x == ',') || (x == '!') || (x == '?')) && (*Example[posExPresent]).length() < 60)
					{
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << x;
						setBackgroundColor(COLOR_DEFAULT);
						(*Example[posExPresent]) += x;
					}
					else if (x == BACKSPACE && !(*Example[posExPresent]).empty())
					{
						(*Example[posExPresent]).erase((*Example[posExPresent]).length() - 1, 1);
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << "\b \b";
						setBackgroundColor(COLOR_DEFAULT);
					}
					else if (x == ENTER && !(*Example[posExPresent]).empty())
					{
						Nocursortype(false);
						Standardized(*Example[posExPresent]);
						break;
					}
					else if (x == ESC)
					{
						Nocursortype(false);
						break;
					}
				}
			}
			else if (key == DELETE && Example[posExPresent] != NULL)
			{
				if (ShowMenuConfirmDelete() == ENTER)
				{
					RemoveExample(Example, posExPresent, ExMax);
					if (posExPresent > 0) posExPresent--;
				}
			}
			else if (key == ESC)
			{
				break;
			}
		}
		else if (key == TAB)
		{
			return;
		}
		else if (key == ESC)
		{
			tab = -1;
			return;
		}
	}
}

// Ham xu ly hieu chinh tu
void HandleEditWord(Word*& wordPresent)
{
	int tab = 0;
	char key;
	while (true)
	{
		if (tab == -1)
		{
			break;
		}
		else if (tab == 0)
		{
			ShowInfoWord(wordPresent);
			EditWordType(wordPresent->typeWord, key, tab);
		}
		else if (tab == 1)
		{
			ShowInfoWord(wordPresent);
			EditMean(wordPresent->mean, key, tab);
		}
		else if (tab == 2)
		{
			ShowInfoWord(wordPresent);
			EditExample(wordPresent->Example, tab, key);
		}

		if (key == TAB)
		{
			if (tab < 2) tab++;
			else tab = 0;
		}
	}
}

//==================================== XU LY THEM TU ======================================
// Ham kiem tra trung tu da co
bool CheckWordExist(WordList HashTable[], string temp)
{
	if (temp[0] >= 'A' && temp[0] <= 'Z') temp[0] += 32; //xu ly neu ki tu dau nhap vao la ki tu in hoa
	if (temp.empty())
	{
		return NULL;
	}
	else
	{
		int idx = HashFunction(temp);
		for (Word* k = HashTable[idx].pHead; k != NULL; k = k->pNext)
		{
			if (temp == k->word)
			{
				return true;
			}
		}
		return false;
	}
}

// Ham them tu moi
void addWordNew(WordList HashTable[], Word*& wordNew, int &tab, char &key)
{
	//xu ly guide
	DeleteGuide();
	ShowGuideWordAndTypeWord();

	while (true)
	{
		string wordMore = wordNew->word;
		Nocursortype(false);
		gotoXY(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME_2 + 2);
		setBackgroundColor(COLOR_HIGHTLIGHT);
		if (wordMore.empty())
			cout << "NHAP F3 DE THEM TU    ";
		else
			cout << wordMore;
		setBackgroundColor(COLOR_DEFAULT);

		key = _getch();
		if (key == -32 || key == 0)
		{
			key = _getch();
			if (key == F2 && !wordMore.empty())
			{
				return;
			}
			else if (key == F3 || key == F4)
			{
				char x;
				Nocursortype(true);
				while (true)
				{
					gotoXY(X_POS_MAIN_FRAME_2 + 6 + wordMore.length(), Y_POS_MAIN_FRAME_2 + 2);
					x = _getch();
					if (x == -32 || x == 0)
					{
						x = _getch();
					}
					else if (((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) && wordMore.length() < WIDTH_MAIN_FRAME - 3)
					{
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << x;
						DeleteBySpace(wordMore.length(), 21);
						setBackgroundColor(COLOR_DEFAULT);
						wordMore += x;
						if (CheckWordExist(HashTable, wordMore))
						{
							DrawFrame(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 30, 5);
							gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
							setBackgroundColor(COLOR_RED);
							cout << "TU DA TON TAI!";
							setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
						}
						else
						{
							DeleteNoti();
						}
					}
					else if (x == BACKSPACE && !wordMore.empty())
					{
						wordMore.erase(wordMore.length() - 1, 1);
						setBackgroundColor(COLOR_HIGHTLIGHT);
						cout << "\b \b";
						setBackgroundColor(COLOR_DEFAULT);

						if (CheckWordExist(HashTable, wordMore))
						{
							DrawFrame(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 30, 5);
							gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
							setBackgroundColor(COLOR_RED);
							cout << "TU DA TON TAI!";
							setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
						}
						else
						{
							DeleteNoti();
						}
					}
					else if (x == ENTER && !wordMore.empty())
					{
						Nocursortype(false);
						Standardized(wordMore);
						wordNew->word = wordMore;
						break;
					}
					else if (x == ESC)
					{
						break;
					}
				}				
			}
		}		
		else if (key == TAB)
		{
			return;
		}
		else if (key == ESC)
		{
			tab = -1;
			return;
		}
	}
}

// Ham Chinh xu ly them tu
void HandleInsertWord(WordList HashTable[], Word*& wordNew, Word*& wordBegin, Word*& wordEnd, Word*& wordPresent, string &str)
{
	int tab = 0;
	char key;
	while (true)
	{
		if (tab == -1)
		{
			break;
		}
		if (tab == 0)
		{
			ShowInfoWord(wordNew);
			addWordNew(HashTable, wordNew, tab, key);
		}
		else if (tab == 1)
		{
			ShowInfoWord(wordNew);
			EditWordType(wordNew->typeWord, key, tab);
		}
		else if (tab == 2)
		{
			ShowInfoWord(wordNew);
			EditMean(wordNew->mean, key, tab);
		}
		else if (tab == 3)
		{
			ShowInfoWord(wordNew);
			EditExample(wordNew->Example, tab, key);
		}

		if (key == TAB)
		{
			if (tab < 3)
				tab++;
			else
				tab = 0;
		}

		if (key == F2 && CheckWordExist(HashTable, wordNew->word) == false)
		{
			if (wordNew->word.empty())
			{
				DrawFrame(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 40, 5);
				gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
				setBackgroundColor(COLOR_RED);
				cout << " TU KHONG DUOC DE TRONG  ";
				setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
				_getch();
				DeleteNoti();
			}
			else
			{
				StandardizedWord(wordNew->word);
				int idx = HashFunction(wordNew->word);
				InsertWord(HashTable[idx], wordNew);

				str = "";
				wordBegin = wordNew;
				wordEnd = FindWordLastFrame(HashTable, wordBegin, str);
				wordPresent = wordNew;

				DrawFrame(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 40, 5);
				gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
				setBackgroundColor(COLOR_GREEN_LIGHT);
				cout << "  THEM TU THANH CONG!  ";
				setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
				Sleep(500);
				DeleteNoti();
				return;
			}
		}
		else if (key == ESC)
		{
			if (ShowMenuConfirmCancel() == ENTER)
			{
				tab = 0;
			}
			DeleteNoti();
		}
	}
}

//================================ XU LY XOA TU =====================================
// Ham giai phong tu
void FreeWord(Word*& wordPresent)
{
	Mean* meanDel = NULL;
	while (wordPresent->mean != NULL)
	{
		meanDel = wordPresent->mean;
		wordPresent->mean = wordPresent->mean->pNext;
		delete meanDel;
	}

	for (int i = 0; i < 5 && wordPresent->Example[i] != NULL; i++)
	{
		delete wordPresent->Example[i];
	}
	delete wordPresent;
}

// Ham xu ly xoa
void HandleRemoveWord(WordList HashTable[], Word*& wordPresent, string &str)
{
	if (wordPresent != NULL && ShowMenuConfirmDelete() == ENTER)
	{
		int idx = HashFunction(wordPresent->word);
		if (wordPresent == HashTable[idx].pHead)
		{
			if (HashTable[idx].pHead->pNext == NULL) 
			{
				HashTable[idx].pHead = HashTable[idx].pTail = NULL;
			}
			else
			{
				HashTable[idx].pHead = HashTable[idx].pHead->pNext;
				HashTable[idx].pHead->pPrev = NULL;
			}
		}
		else if (HashTable[idx].pTail == wordPresent)
		{
			HashTable[idx].pTail = HashTable[idx].pTail->pPrev;
			HashTable[idx].pTail->pNext = NULL;
		}
		else
		{
			wordPresent->pPrev->pNext = wordPresent->pNext;
			wordPresent->pNext->pPrev = wordPresent->pPrev;
		}
		FreeWord(wordPresent);
		str = "";

		//xoa tu thua tren o tim kiem
		gotoXY(X_POS_MAIN_FRAME + 1, Y_POS_MAIN_FRAME + 1);
		DeleteBySpace(0, WIDTH_MAIN_FRAME - 3);

		//Thong bao xoa thanh cong
		DrawFrame(X_POS_MAIN_FRAME_2 + 6, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME - 1, 40, 5);
		gotoXY(X_POS_MAIN_FRAME_2 + 13, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
		setBackgroundColor(COLOR_GREEN_LIGHT);
		cout << "  XOA TU THANH CONG!  ";
		setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
		Sleep(500);
		DeleteNoti();
	}
}

//============ MENU Chinh =================
void Menu(WordList HashTable[])
{
	string str;
	Word* wordBegin = CreateWord(), * wordEnd = CreateWord(), * wordPresent = CreateWord();
	bool checkStr = true;

	DrawMainFrame();

	while (true)
	{
		if (checkStr)
		{
			wordBegin = FindWordFirstFrame(HashTable, str);
			wordPresent = wordBegin;
			wordEnd = FindWordLastFrame(HashTable, wordBegin, str);
		}

		ShowWordList(HashTable, wordPresent, wordBegin, wordEnd);
		ShowInfoWord(wordPresent);
		DeleteGuide();
		ShowGuideMain();

		Nocursortype(true);
		gotoXY(X_POS_MAIN_FRAME + 1 + str.length(), Y_POS_MAIN_FRAME + 1);

		char key = _getch();
		if (key == -32 || key == 0)
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
				checkStr = false;
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
				checkStr = false;
			}
			else if (key == F3)
			{
				Word* wordNew = CreateWord();
				HandleInsertWord(HashTable, wordNew, wordBegin, wordEnd, wordPresent, str);
				checkStr = false;
			}
			else if (key == F4)
			{
				HandleEditWord(wordPresent);
				checkStr = false;
			}
			else if (key == DELETE)
			{
				HandleRemoveWord(HashTable, wordPresent, str);
				checkStr = true;
			}
		}
		else if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) && str.length() < WIDTH_MAIN_FRAME - 3)
		{
			cout << key;
			str += key;
			StandardizedWord(str);
			checkStr = true;
		}
		else if (key == BACKSPACE && !str.empty())
		{
			cout << "\b ";
			str.erase(str.length() - 1, 1);
			checkStr = true;
		}
		else if (key == ESC)
		{
			system("cls");
			return;
		}
	}
}