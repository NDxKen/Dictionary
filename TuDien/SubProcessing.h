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
#define COLOR_GREEN_LIGHT 2

#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ESC 27
#define TAB 9
#define ENTER 13
#define F2 60
#define F3 61
#define F4 62
#define DELETE 83

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

//================ Cac Ham Xu Ly Phu ===================
// Xoa Tu a den b
void DeleteBySpace(int a, int b)
{
	cout << string(b - a, ' ');
}

// Xoa Thong Bao
void DeleteNoti()
{
	for (int i = 0; i < 3; i++)
	{
		gotoXY(0, Y_POS_MAIN_FRAME + WIDTH_MAIN_FRAME - 1 + i);
		DeleteBySpace(0, 130);
	}
}

// Ham Tra Ve Vi Tri Mang Bam
int HashFunction(string key)
{
	return key[0] - 97;
}

// Ham Chuan Hoa
void Standardized(string& str)
{
	while (str[0] == ' ')
	{
		str.erase(str.begin());
	}
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.length() - 1, 1);
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			str.erase(i, 1);
			i--;
		}
	}
}

// Ham Chuan Hoa Tu
void StandardizedWord(string& str)
{
	while (str[0] == ' ')
	{
		str.erase(str.begin());
	}
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.length() - 1, 1);
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str.erase(i, 1);
			i--;
		}
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
}

//=================== Ham Hien Thi Cac Thong Bao ===================
int ShowMenuConfirmDelete()
{
	char k;
	DrawFrame(X_POS_MAIN_FRAME_2, Y_POS_MAIN_FRAME_2 + HEIGHT_MAIN_FRAME - 1, 50, 5);
	gotoXY(X_POS_MAIN_FRAME_2 + 5, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
	cout << "Nhan ";
	setBackgroundColor(COLOR_RED);
	cout << "ENTER";
	setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	cout << " De Xoa, Nhan ";
	setBackgroundColor(COLOR_RED);
	cout << "ESC";
	setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	cout << " De Tro Lai";
	Nocursortype(false);
	do
	{
		k = _getch();
	} while (k != ENTER && k != ESC);
	DeleteNoti();
	return k;
}

int ShowMenuConfirmCancel()
{
	char k;
	DrawFrame(X_POS_MAIN_FRAME_2, Y_POS_MAIN_FRAME_2 + HEIGHT_MAIN_FRAME - 1, 70, 5);
	gotoXY(X_POS_MAIN_FRAME_2 + 5, Y_POS_MAIN_FRAME + HEIGHT_MAIN_FRAME);
	cout << "Tu Chua Duoc Luu, Nhan ";
	setBackgroundColor(COLOR_RED);
	cout << "ENTER";
	setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	cout << " De Tro Lai, Nhan ";
	setBackgroundColor(COLOR_RED);
	cout << "ESC";
	setBackgroundColor(COLOR_BACKGROUND_DEFAULT);
	cout << " De Thoat";
	Nocursortype(false);

	do
	{
		k = _getch();
	} while (k != ENTER && k != ESC);
	return k;
}

//====================== Ham hien thi huong dan =========================
void ShowGuideMain()
{
	Nocursortype(false);
	gotoXY(X_POS_MAIN_FRAME_3 + 5, Y_POS_MAIN_FRAME_3 + 1);
	cout << "F3: Them             F4: Hieu Chinh             Delete: Xoa             ESC: Thoat Chuong Trinh";
}

void ShowGuideWordAndTypeWord()
{
	Nocursortype(false);
	gotoXY(X_POS_MAIN_FRAME_3 + 3, Y_POS_MAIN_FRAME_3 + 1);
	cout << "F2:Luu Khi Them Tu Moi      F3:Them      F4:Hieu Chinh      Enter:Luu      TAB:Chuyen      ESC:Tro Ve";
}

void ShowGuideMeanAndExample()
{
	Nocursortype(false);
	gotoXY(X_POS_MAIN_FRAME_3 + 3, Y_POS_MAIN_FRAME_3 + 1);
	cout << "F2:Luu Khi Them Tu Moi   F3:Them   F4:Hieu Chinh   Enter:Luu   Delete:Xoa   TAB:Chuyen   ESC:Tro Ve";
}

void DeleteGuide()
{
	gotoXY(X_POS_MAIN_FRAME_3 + 3, Y_POS_MAIN_FRAME_3 + 1);
	DeleteBySpace(0, 103);
}