#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define DRAW
#ifdef DRAW

VOID KeyEventProc(KEY_EVENT_RECORD ker);
void mouseEventProc(MOUSE_EVENT_RECORD mouse);
void setCursor(COORD pos);

HANDLE output,input;

int main(int argc, char *argv[]) 
{
	
	INPUT_RECORD inBuffer[128];
	DWORD cNumRead, fdwMode, i, counter=0;
	LPCSTR str = {"TEST FUN"};
	
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output,74);
	SetConsoleTitleA(str);
	printf("Draw\nuse left click and move to set pix Right click to erase");
	SetConsoleTextAttribute(output,7);

	input = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
	while(1)
	{
		if(!ReadConsoleInputA(input,inBuffer,128,&cNumRead))
		printf("Error");
		
		for(i = 0; i < cNumRead; i++)
		{
			if(inBuffer[i].EventType == KEY_EVENT) 
			{
				KeyEventProc(inBuffer[i].Event.KeyEvent); 
			}
			
			else if(inBuffer[i].EventType == MOUSE_EVENT) 
			{
				mouseEventProc(inBuffer[i].Event.MouseEvent);
			}
		}	
	}
	
	
	return 0;                                           
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    printf("Key event: ");

    if(ker.bKeyDown)
        printf("key pressed\n");
    else printf("key released\n");
}

void mouseEventProc(MOUSE_EVENT_RECORD mouse)
{
	if(/*mouse.dwEventFlags == MOUSE_MOVED && */mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		//printf("Mouse moved %d %d\n",mouse.dwMousePosition.X,mouse.dwMousePosition.Y);
		SetConsoleTextAttribute(output,7);
		setCursor(mouse.dwMousePosition);
		printf(".");
	}
	else if(/*mouse.dwEventFlags == MOUSE_MOVED && */mouse.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		setCursor(mouse.dwMousePosition);
		SetConsoleTextAttribute(output,0);
		printf(".");
	}
}


void setCursor(COORD pos)
{
	HANDLE output;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output,pos);
}

#endif
