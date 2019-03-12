#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>

void menu();
void border();
void gborder();
void opening();
void patterns(int,int);
void load(int,int);
int password();
class chess;
class details;

class chess 			  		 //for chessboard
{
 int r,c,t[8][8];
 char coor,a[9][9];
 public:
 void createboard();
 int move(int ,int);
 void display();
 void reference(int ,int);
};

void chess::createboard()			 //creation of board
{
 int i,j;
 coor='0';
 a[0][0]='X';
 for(i=1;i<9;i++)
 {
  a[i][0]=coor;
  coor++;
 }
 coor='0';
 for(j=1;j<9;j++)
 {
  a[0][j]=coor;
  coor++;
 }
 for(i=1;i<9;i++)
 {
  for(j=1;j<9;j++)
  {
   if((i+j)%2==0)
    a[i][j]=176;
   else
    a[i][j]=219;
  }
 }
 display();
 for(i=0;i<8;i++)
 {
  for(j=0;j<8;j++)
   t[i][j]=0;
 }
}

int chess::move(int r,int c)			 //placing queen
{
 int i,j;
 char z;
 if(t[r][c]==1)
 {
  a[r+1][c+1]='Q';
  display();
  textcolor(RED+BLINK);
  gotoxy(66,20);
  cprintf("YOU LOSE");
  gotoxy(66,21);
  cprintf("GAME OVER!");
  cout<<endl;
  return -1;
 }
 else
 {
  a[r+1][c+1]='Q';
  cout<<endl;
  display();
  return 0;
 }
}

void chess::display()				 //displaying board
{
 int i,j;
 for(i=0;i<9;i++)
 {
  gotoxy(33,i+7);
  for(j=0;j<9;j++)
  {
   if(i==0||j==0)
    textcolor(YELLOW);
   else
    textcolor(WHITE);
   cprintf("%c",a[i][j]);
   cout<<" ";
  }
  cout<<endl;
 }
 cout<<endl<<endl;
}

void chess::reference(int r,int c)		 //reference board
{
 int i,j;
 t[r][c]=1;
 for(i=0;i<8;i++)
 {
  for(j=0;j<8;j++)
  {
   if(r<c)
   {
    if((i!=r && j==c) || (i==r && j!=c) ||(i+j==r+c) || j-i==c-r)
     t[i][j]=1;
   }
   else if(r==c)
   {
    if((i!=r && j==c) || (i==r && j!=c) ||(i+j==r+c) || i==j)
     t[i][j]=1;
   }
   else
   {
    if((i!=r && j==c) || (i==r && j!=c) ||(i+j==r+c) || i-j==r-c)
     t[i][j]=1;
   }
  }
 }
}

class details			  		 //for player info
{
 char name[30],date[30];
 public:
 void accept();
 void show();
 int retname(char []);
};

int details::retname(char t[30])  		 //comparing name
{
 if(strcmpi(name,t)==0)
  return 1;
 else
  return -1;
}

void details::accept() 				 //acepting info
{
 fstream id;
 id.open("name.txt",ios::out);
 textcolor(CYAN);
 gotoxy(5,3);
 cprintf("Enter Name: ");
 gets(name);
 id<<name<<'\n';
 id.close();
 gotoxy(5,4);
 cprintf("Enter Date(DD/MM/YYYY): ");
 gets(date);
}

void details::show()				 //showing info
{
 textcolor(YELLOW);
 cprintf(name);
 textcolor(9);
 cprintf(" played the game on ");
 textcolor(YELLOW);
 cprintf(date);
}



void menu()			  		 //starting menu
{
 clrscr();
 border();
 char t[30];
 int l;
 char ch[1];
 fstream file,id;
 details d;
 textcolor(9);
 gotoxy(30,8);
 cprintf("1. New Game");
 gotoxy(30,9);
 cprintf("2. Play As Guest");
 gotoxy(30,10);
 cprintf("3. Show Players");
 gotoxy(30,11);
 cprintf("4. Delete Players");
 gotoxy(30,12);
 cprintf("5. How To Play");
 gotoxy(30,13);
 cprintf("6. Exit");
 gotoxy(28,15);
 textcolor(YELLOW);
 cprintf("Your Choice: ");
 ch[0]=getch();
 cout<<ch[0];
 delay(256);
 l=atoi(ch);
 switch(l)
 {
  case 1:
   clrscr();
   border();
   gotoxy(5,2);
   textcolor(12);
   cprintf("Please Enter Details");
   file.open("player",ios::app|ios::binary);
   d.accept();
   file.write((char*)&d,sizeof(d));
   file.close();
   break;
  case 2:
   id.open("name.txt",ios::out);
   id<<"Guest"<<'\n';
   id.close();
   break;
  case 3:
   border();
   gotoxy(28,5);
   cout<<"Loading Player List...";
   load(27,5);
   gotoxy(28,5);
   cout<<"\t\t\t\t";
   file.open("player",ios::in|ios::binary);
   int i=10;
   while(!file.eof())
   {
    file.read((char*)&d,sizeof(d));
    if(file.eof()) break;
    gotoxy(22,i);
    d.show();
    i++;
   }
   getch();
   file.close();
   menu();
   break;
  case 4:
   clrscr();
   int k;
   border();
   k=password();
   if(k==1)
   {
    textcolor(GREEN);
    gotoxy(34,13);
    cprintf("ACCESS GRANTED");
    delay(1000);
    border();
    fstream tfile;
    int flag=0;
    char t[30];
    char ch,a[100];
    fstream pass;
    cout<<endl;
    file.open("player",ios::in|ios::binary);
    i=14;
    while(!file.eof())
    {
     file.read((char*)&d,sizeof(d));
     if(file.eof()) break;
     gotoxy(3,i);
     d.show();
     i++;
    }
    delay(256);
    file.close();
    textcolor(12);
    gotoxy(5,2);
    cprintf("Enter Name to be deleted : ");
    gets(t);
    file.open("player",ios::in|ios::binary);
    tfile.open("temp",ios::out|ios::binary);
    while(!file.eof())
    {
     file.read((char*)&d,sizeof(d));
     if(file.eof()) break;
     if(d.retname(t)!=1)
      tfile.write((char*)&d,sizeof(d));
     else
      flag=1;
    }
    file.close();
    tfile.close();
    if(flag!=1)
    {
     gotoxy(32,12);
     textcolor(RED+BLINK);
     cprintf("NO MATCH FOUND");
     getch();
    }
    else
    {
     gotoxy(5,3);
     cout<<"Deleting...";
     load(4,3);
     gotoxy(5,3);
     cout<<"Deleted.\t";
    }
    remove("player");
    rename("temp","player");
    delay(256);
   }
   else
   {
    gotoxy(34,14);
    textcolor(RED+BLINK);
    cprintf("ACCESS DENIED!");
    getch();
   }
   menu();
   break;
  case 5:
   clrscr();
   border();
   patterns(200,5);
   textcolor(13);
   gotoxy(13,10);
   cprintf("Objective is to place 8 queens");
   cprintf(" on the chessboard so that no");
   gotoxy(13,11);
   cprintf("two queens attack each other.");
   cprintf(" A queen on a chessboard moves");
   gotoxy(13,12);
   cprintf("vertically, horizontally and");
   cprintf(" diagonally.");
   textcolor(YELLOW+BLINK);
   gotoxy(33,13);
   cprintf("ENJOY!!");
   getch();
   menu();
   break;
  case 6:
   border();
   patterns(500,2);
   exit(0);
  default:
   clrscr();
   border();
   gotoxy(28,12);
   cout<<"Please Enter a Valid Option";
   getch();
   menu();
 }
}

int password()			  		 //for password protection
{
 char e[25],pass[25]="projectx",ch;
 int i,j;
 gotoxy(24,12);
 cout<<"Enter Security Key: ";
 for(i=0;i<=25;i++)
 {
  gotoxy(i+45,12);
  ch=getch();
  cout<<"*";
  if(ch==13)
  {
   gotoxy(i+45,12);
   cout<<" ";
   break;
  }
  e[i]=ch;
 }
 e[i]='\0';
 if(strcmp(e,pass)==0)
  return 1;
 else
  return 0;
}

void opening()   		   		 //opening sequence
{
 clrscr();
 int i,c,z,r;
 char x,y;
 textcolor(WHITE);
 randomize();
 gotoxy(30,12);
 cprintf("EIGHT QUEENS PUZZLE");
 delay(500);
 textcolor(GREEN);
 while(!kbhit())
 {
  c=random(80);
  for(r=1;r<25;r++)
  {
   gotoxy(c,r);
   if((c>=30&&c<=48&&r==12)||c==0)
    continue;
   x=random(255);
   delay(5);
   cprintf("%c",x);
  }
 }
 getch();
}

void border() 			  		 //for border
{
 clrscr();
 int i;
 textcolor(GREEN);
 for(i=0;i<79;i++)
 {
  delay(5);
  cprintf("Í");		//205
 }
 cprintf("»");		//187
 for(i=2;i<25;i++)
 {
  delay(5);
  gotoxy(80,i);
  cprintf("º");		//186
 }
 gotoxy(80,i-1);
 cprintf("¼");		//188
 for(i=79;i>0;i--)
 {
  delay(5);
  gotoxy(i,24);
  cprintf("Í");		//205
 }
 gotoxy(i+1,24);
 cprintf("È");		//200
 for(i=23;i>1;i--)
 {
  delay(5);
  gotoxy(1,i);
  cprintf("º");		//186
 }
 gotoxy(1,1);
 cprintf("É");		//201
}

void gborder()			 		 //for in-game border
{
 clrscr();
 int i;
 textcolor(GREEN);
 for(i=1;i<80;i++)
 {
  delay(5);
  if(i==55)
   cprintf("Ë");	//203
  else
   cprintf("Í");	//205
 }
 cprintf("»");		//187
 for(i=2;i<25;i++)
 {
  delay(5);
  gotoxy(80,i);
  if(i==5)
   cprintf("¹");	//185
  else
   cprintf("º");	//186
 }
 gotoxy(80,i-1);
 cprintf("¼");		//188
 for(i=79;i>0;i--)
 {
  delay(5);
  gotoxy(i,24);
  cprintf("Í");		//205
 }
 gotoxy(i+1,24);
 cprintf("È");		//200
 for(i=23;i>1;i--)
 {
  delay(5);
  gotoxy(1,i);
  if(i==5)
   cprintf("Ì");	//204
  else
   cprintf("º");	//186
 }
 gotoxy(1,1);
 cprintf("É");		//201
 for(i=2;i<80;i++)
 {
  delay(5);
  gotoxy(i,5);
  if(i==55)
   cprintf("Ê");	//202
  else
   cprintf("Í");	//205
 }
 for(i=2;i<5;i++)
 {
  delay(5);
  gotoxy(55,i);
  cprintf("º");		//186
 }
}

void load(int x,int y)		  		 //for loading animation
{
 textcolor(RED);
 for(int i=0;i<5;i++)
 {
  gotoxy(x,y);
  delay(33);
  cprintf("³");
  gotoxy(x,y);
  delay(33);
  cprintf("/");
  gotoxy(x,y);
  delay(33);
  cprintf("-");
  gotoxy(x,y);
  delay(33);
  cprintf("³");
  gotoxy(x,y);
  delay(33);
  cprintf("/");
  gotoxy(x,y);
  delay(33);
  cprintf("-");
  gotoxy(x,y);
  delay(33);
  cprintf("\\");
  gotoxy(x,y);
  delay(33);
 }
 gotoxy(x,y);
 cout<<" ";
}

void patterns(int x,int t)		         //random patterns on the screen
{
 int i,c,ch,m,n;
 randomize();
 for(i=0;i<x;i++)
 {
  m=random(81);
  n=random(25);
  c=random(16);
  ch=random(7);
  textcolor(c);
  gotoxy(m,n);
  cprintf("%c",ch);
  delay(t);
 }
}


void main() 				  	 //main
{
 static int m=-1;
 if(m==-1)
  opening();
 clrscr();
 chess q;
 char z,name[30],R[2],C[2];
 int r,c,w,f,flag=0;
 fstream id;
 menu();
 do
 {
  clrscr();
  gotoxy(35,12);
  cout<<"LOADING GAME";
  load(34,12);
  gborder();
  w=0;
  q.createboard();
  do
  {
   gotoxy(2,2);
   textcolor(RED);
   cprintf(" RULES");
   gotoxy(5,3);
   textcolor(CYAN);
   cprintf("INPUT IN THIS ORDER -");
   cprintf("(ROW NUMBER,COLUMN NUMBER)");
   gotoxy(5,4);
   cprintf("USING THE REFERENCE PROVIDED. ");
   cprintf("1 Point per Queen.");
   gotoxy(30,17);
   textcolor(YELLOW);
   cprintf("Enter Queen's Position");
   cout<<endl;
   textcolor(CYAN);
   gotoxy(60,2);
   cprintf("Welcome, ");
   id.open("name.txt",ios::in);
   while(!id.eof())
   {
    id.getline(name,30,'\n');
    if(id.eof()) break;
    textcolor(YELLOW);
    cprintf(name);
   }
   id.close();
   textcolor(CYAN);
   gotoxy(60,3);
   cprintf("Your Points: ");
   textcolor(GREEN);
   cprintf("%d",w);
   do
   {
    flag=0;
    delay(256);
    gotoxy(36,18);
    cout<<"(";
    R[0]=getch();
    R[1]='\0';
    r=atoi(R);
    cout<<r<<",";
    C[0]=getch();
    C[1]='\0';
    c=atoi(C);
    cout<<c<<")";
    delay(500);
    gotoxy(36,18);
    cout<<"\t\t\t";
    if(r<0||r>7||c<0||c>7)
    {
     gotoxy(28,19);
     textcolor(CYAN);
     cprintf("Please Enter A Valid Coordinate");
     getch();
     gotoxy(28,19);
     cout<<"\t\t\t\t\t";
     flag=-1;
    }
   }while(flag==-1);
   f=q.move(r,c);
   if(f==-1)
    break;
   q.reference(r,c);
   w++;
   if(w==8)
   {
    patterns(200,5);
    textcolor(GREEN+BLINK);
    gotoxy(73,3);
    cprintf("8");
    gotoxy(66,21);
    cprintf("YOU HAVE WON!!");
    break;
   }
  }while(w!=8);
  delay(500);
  textcolor(CYAN);
  gotoxy(66,23);
  cprintf("Retry??(y/n) ");
  cin>>z;
 }while(z!='n');
 border();
 textcolor(YELLOW+BLINK);
 gotoxy(32,12);
 cprintf("THANKS FOR PLAYING!!");
 m++;
 getch();
 main();
 getch();
}