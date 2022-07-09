#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define right 77
#define left  75
#define up 72
#define down 80
#define lx 4
#define mx 76
#define ly 4
#define my 22
#define A 1
#define B 2
#define mtx 25
#define mty 18

void nokhtechin();
void getkey();
void check4square(int,int);
void updateresults();
bool check4defence();
bool moveB(int,int);
void cordinateintable(int&,int&,int,int);
void writeab(char,int,int&);
void writesline(char,int,int,int);
void showwinner(char,int,bool);
bool check4attack();

int x,y,tx,ty,bx,by,tbx,tby;
int pno = 0;
int zo = 10;
bool ift = true;

int ap = 0,bp = 0;
int noe = 484;

char t[mty + 1][mtx + 1];

void main()
{
   srand(time(0));
   updateresults();
   tx = ty = 0;
	textcolor(YELLOW);
	gotoxy(3,4);
   x = lx;
   y = ly;
	nokhtechin();
	textcolor(LIGHTRED);
   gotoxy(x,y);
   while(1)
   	getkey();
}
void nokhtechin()
{
	int i,j;
   for(i = 0;i < mty;i++)
   	for(j = 0;j > mtx;j++)
      	t[ty][tx] = NULL;
	for(i = 4;i < 14;i++)
	{
		for(j = 2;j < 27;j++)
			cprintf("O  ");
		cprintf("O");
		if(i != 13)
			printf("\n\n  ");
	}
}
void getkey()
{
	char ch = static_cast<char>(getch());
   switch(ch)
   {
   	case right:
			if(y % 2 == 0)
         {
         	if(x == mx)
            	x = lx;
            else
            	x += 3;
         }
         else
         {
         	if(x == mx + 2)
            	x = lx - 1;
            else
            	x += 3;
         }
         if(tx == mtx && ty % 2 != 0)
         	tx = 0;
         else if(tx == mtx - 1 && ty % 2 == 0)
         	tx = 0;
         else
         	tx++;
         break;
      case left:
			if(y % 2 == 0)
         {
         	if(x == lx)
            	x = mx;
            else
            	x -= 3;
         }
         else
         {
         	if(x == lx - 1)
            	x = mx + 2;
            else
            	x -= 3;
         }
         if(tx == 0)
            if(ty % 2 == 0)
         		tx = mtx - 1;
            else
            	tx = mtx;
         else
         	tx--;
         break;
      case up:
      	if(y == ly)
         	y = my;
         else
         {
         	if(y % 2 == 0)
            {
            	x--;
               y--;
            }
            else
            {
               if(x < mx + 2)
						x++;
               else
               {
               	x -= 2;
                  tx--;
               }
               y--;
            }
         }
         if(ty == 0)
         	ty = mty;
         else
         	ty--;
         break;
      case down:
      	if(y == my)
         	y = ly;
         else
         {
         	if(y % 2 == 0)
            {
            	x--;
               y++;
            }
            else
            {
               if(x < mx + 2)
						x++;
               else
               {
               	x -= 2;
                  tx--;
               }
            	y++;
            }
         }
         if(ty == mty)
         	ty = 0;
         else
         	ty++;
         break;
      case '\r':
         if(t[ty][tx] == NULL)
         {
            writesline('a',CYAN,tx,ty);
            check4square(tx,ty);
            if(check4defence() == false && check4attack() == false)
            {
            	int rtx,rty;
            	do
            	{
            		rtx = rand() % 26;
               	rty = rand() % 19;
            	}while(t[rty][rtx] != NULL || (rtx == mtx && rty % 2 == 0));
            	moveB(rtx,rty);
            	bx = rtx;
            	by = rty;
            }
			}
         updateresults();
			break;
   }
   if(noe == 0)
   {
   	gotoxy(8,24);
      if(ap > bp)
      	showwinner('A',CYAN,false);
      else if(ap < bp)
      	showwinner('B',LIGHTRED,false);
      else
      	showwinner(NULL,NULL,true);
      getch();
      exit(0);
   }
   gotoxy(x,y);
}
void check4square(int tx,int ty)
{
	if(ty % 2 == 0)
   {
      if(t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty-2][tx] && t[ty][tx] == t[ty-1][tx+1])
      {
      	switch(t[ty][tx])
         {
         	case 'a':
            	gotoxy(x,y-1);
               writeab('A',CYAN,ap);
               break;
            case 'b':
            	int gx = 3,gy = 4;
               cordinateintable(gx,gy,tx,ty);
               gotoxy(gx,gy-1);
               writeab('B',LIGHTRED,bp);
               break;
         }
      }
      if(t[ty][tx] == t[ty+1][tx] && t[ty][tx] == t[ty+2][tx] && t[ty][tx] == t[ty+1][tx+1])
      {
      	switch(t[ty][tx])
         {
         	case 'a':
            	gotoxy(x,y+1);
               writeab('A',CYAN,ap);
               break;
            case 'b':
            	int gx = 3,gy = 4;
               cordinateintable(gx,gy,tx,ty);
               gotoxy(gx,gy+1);
               writeab('B',LIGHTRED,bp);
               break;
         }
      }
   }
   else
   {
   	if(t[ty][tx] == t[ty][tx+1] && t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty+1][tx])
      {
      	switch(t[ty][tx])
         {
         	case 'a':
            	gotoxy(x+1,y);
               writeab('A',CYAN,ap);
               break;
            case 'b':
            	int gx = 3,gy = 4;
               cordinateintable(gx,gy,tx,ty);
               gotoxy(gx+1,gy);
               writeab('B',LIGHTRED,bp);
               break;
         }
      }
      if(t[ty][tx] == t[ty][tx-1] && t[ty][tx] == t[ty-1][tx-1] && t[ty][tx] == t[ty+1][tx-1])
      {
      	switch(t[ty][tx])
         {
         	case 'a':
            	gotoxy(x-2,y);
               writeab('A',CYAN,ap);
               break;
            case 'b':
            	int gx = 3,gy = 4;
               cordinateintable(gx,gy,tx,ty);
               gotoxy(gx-2,gy);
               writeab('B',LIGHTRED,bp);
               break;
         }
      }
   }
}
void updateresults()
{
   textcolor(CYAN);
   gotoxy(3,2);
   cprintf("A");
   textcolor(WHITE);
   cprintf(" : %.2d",ap);
   textcolor(LIGHTRED);
   gotoxy(12,2);
   cprintf("B");
   textcolor(WHITE);
   cprintf(" : %.2d",bp);
}
bool check4defence()
{
	if(ty % 2 == 0)
   {
   	if(t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty-2][tx])
      	return moveB(tx+1,ty-1);
   	else if(t[ty][tx] == t[ty+1][tx] && t[ty][tx] == t[ty+2][tx])
      	return moveB(tx+1,ty+1);
      else if(t[ty][tx] == t[ty-1][tx+1] && t[ty][tx] == t[ty-2][tx])
      	return moveB(tx,ty-1);
      else if(t[ty][tx] == t[ty+1][tx+1] && t[ty][tx] == t[ty+2][tx])
      	return moveB(tx,ty+1);
      else if(t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty-1][tx+1])
      	return moveB(tx,ty-2);
      else if(t[ty][tx] == t[ty+1][tx] && t[ty][tx] == t[ty+1][tx+1])
      	return moveB(tx,ty+2);
      else if(t[ty][tx] == t[ty+2][tx] && t[ty][tx] == t[ty][tx+1] && t[ty][tx] == t[ty+2][tx+1])
   		return moveB(tx+1,ty+1);
      else if(t[ty][tx] == t[ty+2][tx] && t[ty][tx] == t[ty][tx-1] && t[ty][tx] == t[ty+2][tx-1])
   		return moveB(tx,ty+1);
      else if(t[ty][tx] == t[ty-2][tx] && t[ty][tx] == t[ty][tx+1] && t[ty][tx] == t[ty-2][tx+1])
   		return moveB(tx+1,ty-1);
      else if(t[ty][tx] == t[ty-2][tx] && t[ty][tx] == t[ty][tx-1] && t[ty][tx] == t[ty-2][tx-1])
   		return moveB(tx,ty-1);
   }
   else
   {
      if(t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty+1][tx] && t[ty][tx+1] == NULL)
      	return moveB(tx+1,ty);
      else if(t[ty][tx] == t[ty-1][tx] && t[ty][tx] == t[ty][tx+1] && t[ty+1][tx] == NULL)
      	return moveB(tx,ty+1);
      else if(t[ty][tx] == t[ty+1][tx] && t[ty][tx] == t[ty][tx+1] && t[ty-1][tx] == NULL)
      	return moveB(tx,ty-1);
      else if(t[ty][tx] == t[ty-1][tx-1] && t[ty][tx] == t[ty+1][tx-1])
      	return moveB(tx-1,ty);
      else if(t[ty][tx] == t[ty-1][tx-1] && t[ty][tx] == t[ty][tx-1])
      	return moveB(tx-1,ty+1);
      else if(t[ty][tx] == t[ty+1][tx-1] && t[ty][tx] == t[ty][tx-1])
      	return moveB(tx-1,ty-1);
   }
   return false;
}
bool moveB(int xx,int yy)
{
	if(t[yy][xx] != NULL)
   	return false;
	t[yy][xx] = 'b';
   int gx = 3,gy = 4;
   cordinateintable(gx,gy,xx,yy);
   gotoxy(gx,gy);
   writesline('b',LIGHTRED,xx,yy);
   check4square(xx,yy);
   return true;
}
void cordinateintable(int& gx,int& gy,int xx,int yy)
{
   int i;
   for(i = 0;i < xx;i++)
   	gx += 3;
   for(i = 0;i < yy;i++)
   	gy++;
   if(yy % 2 == 0)
   	gx++;
}
void writeab(char ab,int color,int& p)
{
	textcolor(color);
	cprintf("%c",ab);
	p++;
}
void showwinner(char winner,int color,bool draw)
{
	if(draw == true)
   {
   	textcolor(YELLOW);
   	cprintf("*** DRAW ***");
      return;
   }
   textcolor(YELLOW);
   cprintf("*** ");
   textcolor(color);
   cprintf("%c",winner);
   textcolor(YELLOW);
   cprintf(" Won ***");
}
void writesline(char ab,int color,int x2,int y2)
{
   textcolor(color);
	t[y2][x2] = ab;
	if(y2 % 2 == 0)
		cprintf("--");
	else
		cprintf("|");
	noe--;
}
bool check4attack()
{
   if(ift == true)
   {
   	ift = false;
      return false;
   }
   int xrnd = rand() % 2;
   int yrnd = rand() % 2;
	if(by % 2 == 0)
   {
      if(pno == 0)
      {
      	if(by == 0)
      		pno = 1;
      	else if(by == mty)
      		pno = -1;
      	else if(t[by+1][bx] != 'a' && t[by+1][bx+1] != 'a' && t[by+2][bx] != 'a')
      	{
         	if(t[by-1][bx] == 'a' || t[by-1][bx+1] == 'a' || t[by-2][bx] == 'a')
      			pno = 1;
         	else
         	{
         		switch(rand() % 2)
            	{
            		case 0:
               		pno = 1;break;
               	case 1:
               		pno = -1;break;
         		}
         	}
      	}
      	else if(t[by-1][bx] != 'a' && t[by-1][bx+1] != 'a' && t[by-2][bx] != 'a')
      		pno = -1;
      }
      if(pno == 0)
      	return false;
   	if(t[by+pno][bx] != 'a' && t[by+pno][bx+1] != 'a' && t[by+2*pno][bx] != 'a')
      {
         if(t[by+pno][bx] == NULL && t[by+pno][bx+1] == NULL && t[by+2*pno][bx] == NULL)
         	return moveB(bx + xrnd,xrnd == 0 ? by + pno * (1 + yrnd):by + pno);
         else if(t[by+pno][bx] == 'b' && t[by+pno][bx+1] == NULL && t[by+2*pno][bx] == NULL)
         	return moveB(yrnd == 0 ? bx + 1 : bx,by + pno * (1 + yrnd));
         else if(t[by+pno][bx] == NULL && t[by+pno][bx+1] == 'b' && t[by+2*pno][bx] == NULL)
         	return moveB(bx,by + pno * (1 + yrnd));
         else if(t[by+pno][bx] == NULL && t[by+pno][bx+1] == NULL && t[by+2*pno][bx] == 'b')
				return moveB(bx + xrnd,by + pno);
         else if(t[by+pno][bx] == 'b' && t[by+pno][bx+1] == 'b' && t[by+2*pno][bx] == NULL)
         	return moveB(bx,by + pno * 2);
         else if(t[by+pno][bx] == 'b' && t[by+pno][bx+1] == NULL && t[by+2*pno][bx] == 'b')
         	return moveB(bx + 1,by + pno);
         else if(t[by+pno][bx] == NULL && t[by+pno][bx+1] == 'b' && t[by+2*pno][bx] == 'b')
         	return moveB(bx,by + pno);
         else if(t[by+pno][bx] == 'b' && t[by+pno][bx+1] == 'b' && t[by+2*pno][bx] == 'b')
         {
            pno *= -1;
            if(t[by+pno][bx] == 'a' || t[by+pno][bx+1] == 'a' || t[by+2*pno][bx] == 'a')
            	pno = 0;
         }
      }
      else
      	pno = 0;
   }
   else
   {
		if(yrnd == 0)
      	yrnd = -1;
      if(zo == 10)
      {
      	if(bx == 0)
      		zo = 0;
      	else if(bx == mtx)
      		zo = 1;
      	else if(t[by+1][bx] != 'a' && t[by-1][bx] != 'a' && t[by][bx+1] != 'a')
      	{
         	if(t[by+1][bx-1] == 'a' || t[by-1][bx-1] == 'a' || t[by][bx-2] == 'a')
      			zo = 0;
         	else
         	{
         		switch(rand() % 2)
            	{
            		case 0:
               		zo = 0;break;
               	case 1:
               		zo = 1;break;
         		}
         	}
      	}
      	else if(t[by+1][bx-1] != 'a' && t[by-1][bx-1] != 'a' && t[by][bx-2] != 'a')
      		zo = 1;
      }
      if(zo == 10)
      	return false;
   	if(t[by+1][bx-zo] != 'a' && t[by-1][bx-zo] != 'a' && t[by][bx+1-zo*2] != 'a')
      {
         if(t[by+1][bx-zo] == NULL && t[by-1][bx-zo] == NULL && t[by][bx+1-zo*2] == NULL)
         	return moveB(zo == 0 ? bx + xrnd : bx - 1,zo == 0 ? (xrnd == 0 ? by + yrnd : by) : by + yrnd);
         else if(t[by+1][bx-zo] == 'b' && t[by-1][bx-zo] == NULL && t[by][bx+1-zo*2] == NULL)
         	return moveB(zo == 0 ? bx + xrnd : bx - 1,xrnd == 0 ? by - 1 : by);
         else if(t[by+1][bx-zo] == NULL && t[by-1][bx-zo] == 'b' && t[by][bx+1-zo*2] == NULL)
         	return moveB(zo == 0 ? bx + xrnd : bx - 1,xrnd == 0 ? by + 1 : by);
         else if(t[by+1][bx-zo] == NULL && t[by-1][bx-zo] == NULL && t[by][bx+1-zo*2] == 'b')
				return moveB(zo == 0 ? bx : bx - 1,by + yrnd);
         else if(t[by+1][bx-zo] == 'b' && t[by-1][bx-zo] == 'b' && t[by][bx+1-zo*2] == NULL)
         	return moveB(bx + 1 - zo * 2,by);
         else if(t[by+1][bx-zo] == 'b' && t[by-1][bx-zo] == NULL && t[by][bx+1-zo*2] == 'b')
         	return moveB(bx - zo,by - 1);
         else if(t[by+1][bx-zo] == NULL && t[by-1][bx-zo] == 'b' && t[by][bx+1-zo*2] == 'b')
         	return moveB(bx - zo,by + 1);
         else if(t[by+1][bx-zo] == 'b' && t[by-1][bx-zo] == 'b' && t[by][bx+1-zo*2] == 'b')
            zo = 10;
      }
      else
      	zo = 10;
	}
   return false;
}

