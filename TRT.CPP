#include<stdlib.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
#include<alloc.h>
#include<graphics.h>
#include<conio.h>
#include<iomanip.h>
#include<bios.h>
#include<iostream.h>
int  	o=0,x=320,y=240,a[2],x1=80,y1=0,score,max,xa,ya,xb,xl[4],yb,direction=2,direction2=1;//0-fuel 1-enemy 2-me 3-goose
int	directionb=0,directionb2=0,flag1=0,flag2=0,dir=1,flag=0;
void dispscore(int);
void loading()
{
		cleardevice();
		setcolor(11);
		settextstyle(10,0,9);
		outtextxy(100,100,"T");
		outtextxy(170,100,"A");
		outtextxy(265,100,"N");
		outtextxy(350,100,"K");
		outtextxy(430,100,"S");
		setcolor(12);
		putpixel(319,228,0);
		putpixel(319,229,0);
		putpixel(287,213,0);
		putpixel(286,213,0);
		putpixel(286,212,0);
		putpixel(286,211,0);
		putpixel(371,208,0);
		putpixel(371,207,0);
		putpixel(372,207,0);
		for(int k=279,flag=0,e;k>160;k-=3)
		{
			delay(1);
			flag=0;
			for(int i=0;i<500;i++)
			{
				if(getpixel(i,k)==11)
				{
					while(getpixel(i,k)==11)i++;
					e=i;
					while((getpixel(e,k)==0)&&flag%2==0)
					{
						putpixel(e,k,1);
						e++;
						delay(1);
					}
					flag++;
				 }
			 }
		}


}
void select();
void mainscreen()
{
		randomize();
		setcolor(11);
		rectangle(x-70,y-20,x+60,y+20);
		rectangle(x-70,y-80,x+60,y-40);
		rectangle(x-70,y+40,x+60,y+80);
		rectangle(x-70,y+100,x+60,y+140);
		settextstyle(1, 0,4);
		setcolor(WHITE);
		outtextxy(x-50, y-153,"Tanks");
		settextstyle(6, 0,2);
		outtextxy(x-24, y-75,"Start");
		outtextxy(x-47, y-15,"Highscores");
		outtextxy(x-20, y+45,"Help");
		outtextxy(x-20, y+105,"Quit");
		setcolor(11);
		rectangle(x-315,y-235,x+315,y+235);
		rectangle(x-310,y-230,x+310,y+230);
		setfillstyle(1,1);
		floodfill(x-313,y-233,11);
		select();
		getch();
		cleardevice();
}
void level(int l)
{
	char	s[10];
		setcolor(10);
		settextstyle(10,0,4);
		outtextxy(170,200,"L");
		outtextxy(220,200,"E");
		outtextxy(270,200,"V");
		outtextxy(320,200,"E");
		outtextxy(370,200,"L");
		itoa(l,s,10);
		outtextxy(440,200,s);
		setfillstyle(1,2)    ;
		floodfill(51,105,10);

}
void highscore(int);
void start()
{
		loading();
		cleardevice();
		level(1);
		void sound();
		sound();
		cleardevice();
		void move(int l);
		move(1);
		cleardevice();
		xl[0]=xl[1]=xl[2]=xl[3]=0;
		loading();
		cleardevice();
		level(2);
		sound();
		cleardevice();
		move(2);
		cleardevice();
		xl[0]=xl[1]=xl[2]=xl[3]=0;
		loading();
		cleardevice();
		level(3);
		sound();
		cleardevice();
		move(3);
		cleardevice();
		xl[0]=xl[1]=xl[2]=xl[3]=0;
		loading();
		cleardevice();
		level(4);
		sound();
		cleardevice();
		move(4);
		cleardevice();
		xl[0]=xl[1]=xl[2]=xl[3]=0;
		cleardevice();
		x=320;y=240;
		settextstyle(10,0,RED);
		setcolor(RED);
		outtextxy(205,200,"VICTORY");
		setfillstyle(1,7);
		floodfill(1,1,4);
		floodfill(330,250,4);
		floodfill(365,230,4);
		getch();
		cleardevice();
		highscore(score);
		cleardevice();
		mainscreen();
}
class high
{
	public:
		int 	rank;
		char 	na[50];
		int 	score;
};
void ranking()
{
	high		t;
	high ob;
	int l=1;
	ifstream 	f("high",ios::binary);
	ofstream	g("dummy2",ios::binary);
			f.read((char *)&ob,sizeof(ob));
			while(!f.eof())
			{
				t=ob;
				t.rank=l;
				l++;
				g.write((char *)&t,sizeof(t));
				f.read((char *)&ob,sizeof(ob));
			}
			f.close();
			g.close();
			int p=remove("high");
			p=rename("dummy2","high");
}
void sort()
{
	high 		t;
	high 		temp;
	high 		ob[100];
	int		n=0;
	ifstream	f("high",ios::binary);
			f.read((char *)&t,sizeof(t));
			while(!f.eof())
			{
				ob[n]=t;
				n++;
				f.read((char *)&t,sizeof(t));
			}
			f.close();
			for(int i=0;i<n-1;i++)
			{
				for(int j=0;j<n-1;j++)
				{
					if(ob[j].score < ob[j+1].score)
					{
						temp=ob[j];
						ob[j]=ob[j+1];
						ob[j+1]=temp;
					}
				 }
			}
	ofstream	g("dummy1",ios::binary);
	for(i=0;i<n;i++)
	{
		g.write((char*)&ob[i],sizeof(ob[i]));
	}
	g.close();
	int p=remove("high");
	p=rename("dummy1","high");
	ranking();
}

void add(int score)
{
			settextstyle(4,0,0);
			ofstream f("high",ios::binary|ios::app);
			if(!f)
			{
					outtextxy(4,200,"Please copy the highscores file to the directory");
					outtextxy(105,250,"specified in the source code .");
					return;
			}
			else
			{
				high	ob;
					cout<<"\nNAME  : ";
					gets(ob.na);
					strupr(ob.na);
					ob.score=score;
					f.write((char *)&ob,sizeof(ob));
			}
			f.close();
			cleardevice();
}
void disp()
{
	cleardevice();
	sort();
	int i=0;
	ifstream	g("high",ios::binary);
	char		score[10],rank[5];
	high		ob;
			if(!g)
			{
				outtextxy(4,200,"Please copy the highscores file to the directory");
				outtextxy(105,250,"specified in the source code .");
				getch();
				cleardevice();
				return;
			}
			else
			{
				setcolor(11);
				settextstyle(8,0,2);
				outtextxy(270,40,"RANKING");
				setcolor(1);
				line(268,70,369,70);
				g.read((char*)&ob,sizeof(ob));
				setcolor(10);
				settextstyle(2,0,5);
				outtextxy(150,102,"Rank");
				outtextxy(275,102,"Name");
				outtextxy(400,102,"Score");
				setcolor(2);
				line(145,95,442,95);
				line(145,125,442,125);
				line(145,95,145,125);
				line(442,95,442,125);
				line(183,95,183,125);
				line(395,95,395,125);
				while((!g.eof())&&i<10)
				{
					setcolor(15);
					itoa(ob.score,score,10);
					itoa(ob.rank,rank,10);
					outtextxy(160,132+i*30,rank);
					outtextxy(200,132+i*30,ob.na);
					outtextxy(403,132+i*30,score);
					setcolor(2);
					line(145,125+i*30,145,125+(i+1)*30);
					line(183,125+i*30,183,125+(i+1)*30);
					line(395,125+i*30,395,125+(i+1)*30);
					line(442,125+i*30,442,125+(i+1)*30);
					line(145,125+(i+1)*30,442,125+(i+1)*30);
					i++;
					g.read((char*)&ob,sizeof(ob));
				}
			}
			g.close();
			getch();
}
void highscore(int score)
{
	add(score);
	sort();
	disp();
}
void highscores()
{
	sort();
	disp();
}
void credits()
{
		cleardevice();
		cout<<"\n\n"<<setw(20)<<" "<<"Thank you for playing,Hope you enjoyed\n\n";
		cout<<"\n\n"<<setw(30)<<" "<<"  Credits \n\n\n";
		cout<<"\n\n This Project is done by : \n\n";
		cout<<setw(25)<<" " <<"Adithya Viswanathan \t\t Nitin P. Shankar\n\n"
			<<setw(20)<<"  " <<"     Rohith P. \t\t         Venkat Praveen\n\n\n\n"
				<<setw(35)<<"  "<<"Of class 12 'B' BATCH 2015-16 ";
}
void fuel(int x,int y)
{
	setfillstyle(1,14);
	setcolor(6);
	bar(x+11,y+8,x+29,y+32);
	sector(x+20,y+33,180,360,10,2);
	sector(x+20,y+8,0,180,10,2);
	setcolor(14);
	line(x+10,y+33,x+30,y+33);
	setcolor(15);
	arc(x+20,y+24,180,360,3);
	line(x+17,y+23,x+20,y+17);
	line(x+23,y+23,x+20,y+17);
	setcolor(6);
	line(x+10,y+8,x+10,y+33);
	line(x+30,y+8,x+30,y+33);
	setcolor(15);
	line(x+19,y+23,x+19,y+25);
	setfillstyle(1,0);
	floodfill(x+20,y+20,15);
}
void tank1a(int x,int y)
{
		setcolor(2);
		rectangle(x-10,y+16,x+10,y-14);
		setfillstyle(6,4);
		floodfill(x,y-1,2);
		rectangle(x-7,y+11,x+7,y-9);
		setfillstyle(4,14);
		floodfill(x,y-1,2);
		ellipse(x-12,y+1,0,360,2,16);
		setfillstyle(9,8);
		floodfill(x-12,y+1,2);
		ellipse(x+12,y+1,0,360,2,16);
		setfillstyle(9,8);
		floodfill(x+12,y+1,2);
		setcolor(1);
		rectangle(x-1,y-17,x+1,y+4);
		setfillstyle(1,1);
		floodfill(x,y-1,1);
		setcolor(2);
		line(x-1,y-17,x+1,y-17);
		line(x-2,y-17,x-2,y-14);
		line(x+2,y-17,x+2,y-14);
}
void tank1b(int x,int y)
{
		setcolor(2);
		rectangle(x-14,y+10,x+16,y-10);
		setfillstyle(6,4);
		floodfill(x+1,y-2,2);
		rectangle(x+11,y-7,x-9,y+7);
		setfillstyle(4,14);
		floodfill(x+1,y-2,2);
		ellipse(x+1,y-12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x+1,y-13,2);
		ellipse(x+1,y+12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x+1,y+13,2);
		setcolor(1);
		rectangle(x-18,y-1,x+2,y+1);
		setfillstyle(1,1);
		floodfill(x,y,1);
		setcolor(2);
		line(x-18,y-1,x-18,y+1);
		line(x-18,y+2,x-15,y+2);
		line(x-18,y-2,x-15,y-2);
}
void tank1c(int x,int y)
{
		setcolor(2);
		rectangle(x-10,y+14,x+10,y-16);
		setfillstyle(6,4);
		floodfill(x,y-1,2);
		rectangle(x-7,y+9,x+7,y-11);
		setfillstyle(4,14);
		floodfill(x,y-1,2);
		ellipse(x-12,y-1,0,360,2,16);
		setfillstyle(9,8);
		floodfill(x-12,y,2);
		ellipse(x+12,y-1,0,360,2,16);
		setfillstyle(9,8);
		floodfill(x+12,y-1,2);
		setcolor(1);
		rectangle(x-1,y+17,x+1,y-4);
		setfillstyle(1,1);
		floodfill(x,y+2,1);
		setcolor(2);
		line(x-1,y+17,x+1,y+17);
		line(x-2,y+17,x-2,y+14);
		line(x+2,y+17,x+2,y+14);
}
void tank1d(int x,int y)
{
		setcolor(2);
		rectangle(x-15,y+10,x+15,y-10);
		setfillstyle(6,4);
		floodfill(x,y-2,2);
		rectangle(x+10,y-7,x-10,y+7);
		setfillstyle(4,14);
		floodfill(x,y-2,2);
		ellipse(x,y-12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x,y-13,2);
		ellipse(x,y+12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x,y+13,2);
		setcolor(1);
		rectangle(x+18,y-1,x-1,y+1);
		setfillstyle(1,1);
		floodfill(x+2,y,1);
		setcolor(2);
		line(x+18,y-1,x+18,y+1);
		line(x+18,y+2,x+15,y+2);
		line(x+18,y-2,x+15,y-2);
}
void tank2a(int x,int y,int a,int b,int c,int d)
{
		setcolor(a);
		rectangle(x-10,y+16,x+10,y-14);
		setfillstyle(6,b);
		floodfill(x,y-1,a);
		rectangle(x-7,y+11,x+7,y-9);
		setfillstyle(5,d);
		floodfill(x,y-1,a);
		ellipse(x-12,y+1,0,360,2,17);
		setfillstyle(9,8);
		floodfill(x-12,y+1,a);
		ellipse(x+12,y+1,0,360,2,17);
		setfillstyle(9,8);
		floodfill(x+12,y+1,a);
		setcolor(c);
		rectangle(x-1,y-17,x+1,y+4);
		setfillstyle(1,c);
		floodfill(x,y-2,c);
		setcolor(a);
		line(x-1,y-17,x+1,y-17);
		line(x-2,y-17,x-2,y-14);
		line(x+2,y-17,x+2,y-14);
}
void tank2b(int x,int y,int a,int b,int c,int d)
{
		setcolor(a);
		rectangle(x-14,y+10,x+16,y-10);
		setfillstyle(6,b);
		floodfill(x+1,y-2,a);
		rectangle(x+11,y-7,x-9,y+7);
		setfillstyle(5,d);
		floodfill(x+1,y-2,a);
		ellipse(x+1,y-12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x+1,y-13,a);
		ellipse(x+1,y+12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x+1,y+13,a);
		setcolor(c);
		rectangle(x-18,y-1,x+2,y+1);
		setfillstyle(1,c);
		floodfill(x,y,c);
		setcolor(a);
		line(x-18,y-1,x-18,y+1);
		line(x-18,y+2,x-15,y+2);
		line(x-18,y-2,x-15,y-2);
}
void tank2c(int x,int y,int a,int b,int c,int d)
{
		setcolor(a);
		rectangle(x-10,y+14,x+10,y-16);
		setfillstyle(6,b);
		floodfill(x,y-1,a);
		rectangle(x-7,y+9,x+7,y-11);
		setfillstyle(5,d);
		floodfill(x,y-1,a);
		ellipse(x-12,y-1,0,360,2,17);
		setfillstyle(9,8);
		floodfill(x-12,y,a);
		ellipse(x+12,y-1,0,360,2,17);
		setfillstyle(9,8);
		floodfill(x+12,y-1,a);
		setcolor(c);
		rectangle(x-1,y+17,x+1,y-4);
		setfillstyle(1,c);
		floodfill(x,y+2,c);
		setcolor(a);
		line(x-1,y+17,x+1,y+17);
		line(x-2,y+17,x-2,y+14);
		line(x+2,y+17,x+2,y+14);
}
void tank2d(int x,int y,int a,int b,int c,int d)
{
		setcolor(a);
		rectangle(x-15,y+10,x+15,y-10);
		setfillstyle(6,b);
		floodfill(x,y-2,a);
		rectangle(x+10,y-7,x-10,y+7);
		setfillstyle(5,d);
		floodfill(x,y-2,a);
		ellipse(x,y-12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x,y-13,a);
		ellipse(x,y+12,0,360,17,2);
		setfillstyle(9,8);
		floodfill(x,y+13,a);
		setcolor(c);
		rectangle(x+18,y-1,x-1,y+1);
		setfillstyle(1,c);
		floodfill(x+2,y,c);
		setcolor(a);
		line(x+18,y-1,x+18,y+1);
		line(x+18,y+2,x+15,y+2);
		line(x+18,y-2,x+15,y-2);
}
void heart(int x,int y)
{
		y=y-2;
	int 	a[6];
		setcolor(15);
		ellipse(x+10,y,360,180,4,1);
		ellipse(x-37,y-17,305,327,55,55);
		ellipse(x+15,y+12,95,180,6,7);
		putpixel(x+14,y+1,15);
		setcolor(6);
		setfillstyle(1,6);
		a[0]=x+14;
		a[1]=y+2;
		a[2]=x+14;
		a[3]=y+4;
		a[4]=x+19;
		a[5]=y+3;
		fillpoly(3,a);
		line(x+14,y+2,x+19,y+3);
		setcolor(15);
		line(x+6,y+1,x+2,y+6);
		line(x+2,y+6,x+2,y-6);
		setfillstyle(1,15);
		ellipse(x+2,y+16,90,150,10,23);
		line(x-16,y-1,x,y+10);
		ellipse(x-7,y-1,180,270,10,20);
		line(x-7,y+19,x-10,y+24);
		line(x-10,y+24,x-17,y+26);
		line(x-17,y+26,x-14,y+30);
		line(x-14,y+30,x-7,y+28);
		line(x+13,y+2,x+13,y+4);
		floodfill(x,y,15);
		putpixel(x+10,y+2,0);
		putpixel(x+10,y+1,0);
		putpixel(x+11,y+2,0);
		putpixel(x+11,y+1,0);
		setcolor(6);
		line(x,y+25,x+2,y+27);
		line(x+2,y+27,x+2,y+29);
		line(x+2,y+27,x+5,y+27);
		line(x+2,y+27,x+4,y+29);
		x+=3;
		y-=3;
		line(x,y+25,x+2,y+27);
		line(x+2,y+27,x+2,y+29);
		line(x+2,y+27,x+5,y+27);
		line(x+2,y+27,x+4,y+29);
		setcolor(11);
		line(x-23,y+33,x-23,y-4);
		line(x-23,y-5,x+16,y-5);
		line(x+16,y-4,x+16,y+33);
		line(x-23,y-4,x+16,y-4);
}
void brick2(int x, int y)
{
	int	d=0,e=0,sizeb;
		setfillstyle(1,12);
		bar(x-20,y-20,x,y);
		setfillstyle(1,7);
		sizeb=imagesize(x-20,y-20,x,y);
	void	*brick;
		brick=(char*)malloc(sizeb);
		bar(x-11,y-11,x-10,y-1);
		bar(x-1,y-20,x,y-10);
		bar(x-20,y-20,x-19,y-10);
		do
		{
			bar(x-20,y-11+d,x,y-10+d);
			d+=10;
		}while(d<=10);
		setfillstyle(1,4);
		e=0;
		d=1;
		bar(x-18,y-20+e,x-2,y-19+e);
		bar(x-18,y-20+e+d,x-17,y-13+e+d);
		bar(x-9,y-10+e+d,x-8,y-3+e+d);
		bar(x-20,y-10+e+d,x-12,y-9+e+d);
		bar(x-8,y-10+e+d,x,y-9+e+d);
		setcolor(0);
		line(x-20,y,x,y);
		line(x,y-20,x,y);
		getimage(x-20,y-20,x,y,brick);
		putimage(x-20,y-20,brick,0);
		delete brick;
}
void brick1(int x, int y)
{
		brick2(x,y);
		brick2(x+20,y);
		brick2(x,y+20);
		brick2(x+20,y+20);
}
void stone1(int x,int y)
{
	int 	sizes,p1[6],p2[6];
		sizes=imagesize(x-20,y-20,x,y);
	void 	*stone;
		stone=(char*)malloc(sizes);
		setfillstyle(1,15);
		bar(x-16,y-16,x-4,y-4);
		setfillstyle(1,8);
		bar(x-16,y-20,x-4,y-17);
		bar(x-20,y-20,x-17,y-4);
		setfillstyle(1,8);
		bar(x-20,y-3,x,y );
		bar(x-3,y-20,x,y-4);
		setfillstyle(1,15);
		setcolor(8);
		p1[0]=x-20;p1[1]=y-3;
		p1[2]=x-17;p1[3]=y-3;
		p1[4]=x-20;p1[5]=y;
		fillpoly(3,p1);
		p2[0]=x-3;p2[1]=y-20;
		p2[2]=x;p2[3]=y-20;
		p2[4]=x-3;p2[5]=y-17;
		fillpoly(3,p2);
		setcolor(8);
		line(x-20,y-20,x-20,y);
		line(x-20,y-20,x,y-20);
		getimage(x-20,y-20,x,y,stone);
		putimage(x-20,y-20,stone,0);
		delete stone;
}
void stone2(int x,int y)
{
		stone1(x,y);
		stone1(x+20,y);
		stone1(x,y+20);
		stone1(x+20,y+20);
}
void level1()
{
		setfillstyle(1,15);
		bar(0,0,60,479);
		bar(580,0,640,479);
		setcolor(0);
		settextstyle(2,0,4);
		outtextxy(10,215,"Level 1");
		line(8,227,50,227);
		setfillstyle(1,0);
		bar(7,210,51,206);
		bar(7,232,51,235);
		rectangle(6,204,52,237);
		setcolor(3);
		settextstyle(2,0,4);
		outtextxy(5,300,"Press 'p'");
		outtextxy(5,320,"to pause");
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<3;j++)
			{
				brick1(x1+80+i*80,y1+60+j*40);
			}
		}
		for(int j=0;j<3;j++)
		{
			brick1(x1+200+j*40,y1+100);
		}
		for( i=0;i<2;i++)
		{
			for(int j=0;j<3;j++)
			{
				brick1(x1+320+i*80,y1+60+j*40);
			}
		}
		for(i=0;i<2;i++)
		{
			for(int j=0;j<3;j++)
			{
				brick1(x1+80+i*80,y1+300+j*40);
			}
		}
		for(j=0;j<3;j++)
		{
			brick1(x1+200+j*40,y1+340);
		}
		for(i=0;i<2;i++)
		{
			for(int j=0;j<3;j++)
			{
				brick1(x1+320+i*80,y1+300+j*40);
			}
		}
		brick1(x1+160,220);
		brick1(x1+320,220);
		for(i=0;i<5;i++)
		{
			stone1(x1+20+i*20,230);
		}
		for(i=0;i<5;i++)
		{
			stone1(x1+400+i*20,230);
		}
		for(i=0;i<=40;i+=20)
		{
			brick2(x1+220,440+i);
		}
		brick2(x1+240,440);
		brick2(x1+260,440);
		for(i=0;i<=40;i+=20)
		{
			brick2(x1+280,440+i);
		}
		heart(x,y+210);
		fuel(x1+180,y1+280);
		fuel(x1+260,y1+280);
		fuel(x1+180,y1+40);
		fuel(x1+260,y1+40);
		fuel(x1-20,y1+160);
		fuel(x1+460,y1+160);
}
void level2()
{
		setfillstyle(1,15);
		bar(0,0,59,479);
		bar(580,0,639,479);
		setcolor(0);
		settextstyle(2,0,4);
		outtextxy(10,215,"Level 2");
		line(8,227,50,227);
		setfillstyle(1,0);
		bar(7,210,51,206);
		bar(7,232,51,235);
		rectangle(6,204,52,237);
		setcolor(3);
		settextstyle(2,0,4);
		outtextxy(5,300,"Press 'p'");
		outtextxy(5,320,"to pause");
		for(int i=0;i<=40;i+=20)
		{
			 brick2(x1+220,440+i);
		}
		brick2(x1+240,440);
		brick2(x1+260,440);
		for(i=0;i<=40;i+=20)
		{
			 brick2(x1+280,440+i);
		}
		stone1(x1,y1+100);
		stone1(x1+20,y1+100);
		brick1(x1,y1+180);
		brick1(x1,y1+260);
		brick1(x1+40,y1+260);
		brick1(x1+40,y1+280);
		brick2(x1,y1+300);
		brick2(x1+20,y1+300);
		stone1(x1+40,y1+360);
		stone1(x1+60,y1+360);
		brick1(x1+40,y1+380);
		stone2(x1+120,y1+380);
		brick1(x1+120,y1+420);
		brick1(x1+120,y1+260);
		brick1(x1+120,y1+280);
		stone1(x1+40,y1+420);
		stone1(x1+60,y1+420);
		for(i=0;i<=2;i++)
		{
			brick1(x1+80,y1+100+i*40);
		}
		for(i=0;i<=3;i+=2)
		{
			stone2(x1+120,y1+100+i*40);
		}
		brick1(x1+160,y1+180);
		brick1(x1+360,y1+300);
		brick1(x1+360,y1+140);
		brick1(x1+280,y1+300);
		for(i=0;i<=3;i+=2)
		{
			stone2(x1+360,y1+260+i*40);
		}
		stone2(x1+280,y1+260);
		stone2(x1+240,y1+340);
		for(i=0;i<=3;i+=2)
		{
			stone2(x1+440,y1+340+i*40);
		}
		brick1(x1+280,y1+340);
		for(i=0;i<=3;i+=2)
		{
			brick1(x1+440,y1+380+i*40);
		}
		for(i=0;i<=1;i++)
		{
			brick1(x1+200,y1+300+i*40);
		}
		brick1(x1,y1+60);
		brick1(x1+80,y1+60);
		brick1(x1+200,y1+60);
		stone2(x1+200,y1+260);
		for(i=0;i<=5;i++)
		{
			brick2(x1+200+i*20,y1+380);
		}
		for(i=0;i<=3;i++)
		{
			brick2(x1+440+i*20,y1+280);
		}
		brick1(x1+440,y1+300);
		stone2(x1+360,y1+420);
		brick1(x1+360,y1+460);
		for(i=0;i<=3;i++)
		{
			stone1(x1+440+i*20,y1+260);
		}
		brick1(x1+480,y1+180);
		brick1(x1+320,y1+60);
		for(i=0;i<=1;i++)
		{
			brick1(x1+280,y1+100+i*40);
		}
		brick1(x1+400,y1+60);
		stone2(x1+400,y1+60);
		stone2(x1+240,y1+60);
		stone2(x1+200,y1+100);
		heart(x,y+210);
		for(i=0;i<=3;i+=2)
		{
			stone2(x1+280+i*40,y1+180);
		}
		fuel(x1-20,y1+120);
		fuel(x1-20,y1+200);
		fuel(x1+460,y1+200);
		fuel(x1+460,y1+120);
		fuel(x1+260,y1+40);
		fuel(x1-20,y1+440);
}
void level3()
{

		setfillstyle(1,15);
		bar(0,0,59,479);
		bar(580,0,639,479);
		setcolor(0);
		settextstyle(2,0,4);
		outtextxy(10,215,"Level 3");
		line(8,227,50,227);
		setfillstyle(1,0);
		bar(7,210,51,206);
		bar(7,232,51,235);
		rectangle(6,204,52,237);
		setcolor(3);
		settextstyle(2,0,4);
		outtextxy(5,300,"Press 'p'");
		outtextxy(5,320,"to pause");
		brick1(x1,y1+380);
		stone2(x1,y1+300);
		stone2(x1+480,y1+300);
		stone2(x1+480,y1+420);
		brick1(x1+360,y1+300);
		for(int i=0;i<5;i++)
		{
			brick1(x1+40,y1+300+i*40);
		}
		brick1(x1+40,y1+60);
		brick1(x1+40,y1+100);
		brick1(x1+120,y1+100);
		stone2(x1+40,y1+140);
		stone2(x1+120,y1+20);
		stone2(x1+120,y1+60);
		int l=0;
		for(i=0;i<4;i++)
		{
			if(i!=3)
			{
				brick1(x1+40+i*40,y1+220);
				if(i!=0)
				brick1(x1+120,y1+300+i*40);
				brick1(x1+200+i*40,y1+340);
				brick1(x1+200+i*40,y1+380);
				brick1(x1+360+i*40,y1+460);
			}
			if(l!=3)
			{
				if(l!=2)
				{
					stone2(x1+120,y1+260+l*40);
					brick1(x1+200,y1+260+l*40);
					brick1(x1+280,y1+260+l*40);
					brick1(x1+440,y1+300+l*40);
					brick1(x1+280,y1+60+l*40);
					brick1(x1+200,y1+140+l*40);
				}
				setcolor(0);
				line(x1+141,y1+280,x1+141,y1+320);
				line(x1+141,y1,x1+141,y1+80);
				if(l!=3&&l!=1)
				{
					stone2(x1+400,y1+220-l*40);
					brick1(x1+360,y1+220-l*40);
				}
				l++;
				if(l==1)
				brick1(x1+240,y1+120);
				stone2(x1+280,y1+20);
				stone2(x1+400,y1+60);
				stone2(x1+240,y1+140);
				stone2(x1+280,y1+220);
				stone2(x1+480,y1+140);
				stone2(x1+400,y1+340);
				stone1(x1+240,y1+100);
				stone1(x1+260,y1+100);
				stone2(x1+240,y1+340);
				stone2(x1+120,y1+140);
				brick1(x1+440,y1+60);
				brick1(x1+360,y1+340);
				brick1(x1+360,y1+420);
				brick1(x1+440,y1+420);
				brick1(x1+360,y1+60 );
				brick1(x1+440,y1+220);
				brick1(x1+440,y1+140);
				brick1(x1+320,y1+220);
			}
			brick1(x1+120,y1+460);
			for(int i=0;i<=40;i+=20)
			{
				brick2(x1+220,440+i);
			}
			brick2(x1+240,440);
			brick2(x1+260,440);
			for(i=0;i<=40;i+=20)
			{
				brick2(x1+280,440+i);
			}
			heart(x,y+210);
		}
		stone2(x1,y1+460);
		setcolor(0);
		line(x1+301,y1,x1+301,y1+40);
		stone2(x1+80,y1+460);
		fuel(x1+380,y1+400);
		fuel(x1-20,y1+400);
		fuel(x1+220,y1+280);
		fuel(x1+380,y1+280);
		brick1(x1+240,y1+260);
}
void level4()
{

		setfillstyle(1,15);
		bar(0,0,59,479);
		bar(580,0,639,479);
		setcolor(0);
		settextstyle(2,0,4);
		outtextxy(10,215,"Level 4");
		line(8,227,50,227);
		setfillstyle(1,0);
		bar(7,210,51,206);
		bar(7,232,51,235);
		rectangle(6,204,52,237);
		setcolor(3);
		settextstyle(2,0,4);
		outtextxy(5,300,"Press 'p'");
		outtextxy(5,320,"to pause");
		brick2(x1+80,y1+300);
		brick2(x1+100,y1+300);
		brick1(x1+340,y1+460);
		brick1(x1+140,y1+460);
		brick2(x1+400,y1+300);
		brick2(x1+420,y1+300);
		brick2(x1+40,y1+420);
		brick2(x1+60,y1+420);
		brick2(x1+440,y1+420);
		brick2(x1+460,y1+420);
		for(int i=0;i<7;i++)
		{
			brick1(x1+120+i*40,y1+60);
		}
		for( i=0;i<4;i++)
		{
			brick1(x1+200,y1+220+i*40);
			brick1(x1+280,y1+220+i*40);
		}
		for(i=0;i<3;i++)
		{
			brick1(x1+360,y1+300+i*40);
			brick1(x1+120,y1+300+i*40);
			brick1(x1+440,y1+300+i*40) ;
			brick1(x1+40,y1+300+i*40) ;
		}
		brick1(x1+40,y1+60);
		brick1(x1+440,y1+60);
		brick1(x1+120,y1+140);
		brick1(x1+200,y1+140);
		brick1(x1+280,y1+140);
		brick1(x1+360,y1+140);
		stone2(x1+40,y1+100);
		stone2(x1+440,y1+100);
		stone2(x1+400,y1+140);
		stone2(x1+80,y1+140);
		stone2(x1+40,y1+220);
		stone2(x1+120,y1+220);
		stone2(x1+360,y1+220);
		stone2(x1+440,y1+220);
		stone2(x1+360,y1+400);
		stone2(x1+120,y1+400);
		brick1(x1+400,y1+220);
		brick1(x1+80,y1+220);
		stone2(x1+240,y1+140);
		brick1(x1+400,y1+400);
		brick1(x1+80,y1+400);
		brick1(x1+240,y1+340);
		brick1(x1+40,y1+140);
		for(i=0;i<2;i++)
		{
			stone1(x1+120+i*20,y1+80);
			stone1(x1+200+i*20,y1+80);
			stone1(x1+280+i*20,y1+80);
			stone1(x1+360+i*20,y1+80);
			stone1(x1+240+i*20,y1+320);
			stone1(x1+40+i*20,y1+440);
			stone1(x1+440+i*20,y1+440);
			stone1(x1+140+i*20,y1+440);
			stone1(x1+340+i*20,y1+440);
			stone1(x1+80+i*20,y1+380);
			stone1(x1+400+i*20,y1+380);
		}
		for(i=0;i<=40;i+=20)
		{
			 brick2(x1+220,440+i);
		}
		brick2(x1+240,440);
		brick2(x1+260,440);
		for(i=0;i<=40;i+=20)
		{
			 brick2(x1+280,440+i);
		}
		heart(x,y+210);
		fuel(x-20,y);
		fuel(x-180,y+80);
		fuel(x+140,y+80);
		fuel(x-180,y-80);
		fuel(x+140,y-80);
		fuel(x-20,y-160);
}
void clearblt(int x,int y)
{
		sound(523);
		randomize();
		setfillstyle(9,random(16));
		bar(x+1,y+1,x+7,y+7);
		delay(100);
		setfillstyle(1,0);
		bar(x+1,y+1,x+7,y+7);
		nosound();
		if(x==xa&&y==ya)
		{
			xa=-100;
			ya=-200;
			flag1=0;
		}
		else if(x==xb&&y==yb)
		{
			xb=-100;
			yb=-200;
			flag2=0;
		}
}
void bullet(int x,int y)
{
	if(y>471)
	{
		clearblt(x,y-1);
		if(x==xb&&y==yb)
		{
			xb=-100;
			yb=-200;
			flag2=0;
		}
		else if(x==xa&&y==ya)
		{
			xa=-100;
			ya=-200;
			flag1=0;
		}
	}
	else if(y<1)
	{
		clearblt(x,y+1);
		if(x==xb&&y==yb)
		{
			xb=-100;
			yb=-200;
			flag2=0;
		}
		else if(x==xa&&y==ya)
		{
			xa=-100;
			ya=-200;
			flag1=0;
		}
	}
	else
	{
		x+=4;
		y+=4;
		setfillstyle(1,0);
		bar(x-4,y-4,x+4,y+4);
		setfillstyle(1,11);
		setcolor(9);
		circle(x,y,3);
		circle(x,y,2);
		floodfill(x,y,9);
	}
}
void collect(int d)
{
	setfillstyle(1,0);
	if(d==0)return;
	switch(d)
	{
		case 1: bar(a[0]-a[0]%40+30,a[1],a[0]-a[0]%40+50,a[1]+30);xl[0]++;score+=20;break;
		case 2: bar(a[0]+1,a[1]-a[1]%40+5,a[0]-19,a[1]-a[1]%40+35);xl[0]++;score+=20;break;
		case 3: bar(a[0]-a[0]%40+30,a[1],a[0]-a[0]%40+50,a[1]-30);xl[0]++;score+=20;break;
		case 4: bar(a[0],a[1]-a[1]%40+5,a[0]+20,a[1]-a[1]%40+35);xl[0]++;score+=20;break;
		default :break;
	}
	sound(261);
	delay(100);
	nosound();
	dispscore(3);
}
int checkpixelt(int constant,int variable,int condt,int extent,int d) //
{
	int	v=variable,pixel,c=constant;
		if(condt==0)
		{
			while(constant<=c+1)
			{
				variable=v;
				while(variable<=v+extent)
				{
					pixel = getpixel(constant,variable);
					switch(pixel)
					{
						case 0:break;
						default:return 0;
						case 6:case 14:
						{
							a[0]=constant;
							a[1]=variable;
							collect(d);
							return 0;
						};
					}
					variable++;
				}
				constant++;
			}
		}
		if(condt==1)
		{
			while(constant<=c+1)
			{
				variable=v;
				while(variable<=v+extent)
				{
					pixel = getpixel(variable,constant);
					switch(pixel)
					{
						case 0:break;
						case 6:case 14:
						{
							a[1]=constant;
							a[0]=variable;
							collect(d);
							return 0;
						};
						default:return 0;
					}
					variable++;
				}
				constant++;
			}
		}
		return 1;
}
void cleartank(int a,int b)
{
	setfillstyle(1,0);
	bar(a,b,a+38,b+38);
}

void destroyme()
{
	setfillstyle(4,2);
	bar(x1,y1,x1+38,y1+38);
	sound(500);
	delay(100);
	nosound();
	cleartank(x1,y1);
	x1=241,y1=441;
	xl[2]++;
	score-=10;
	dispscore(3);
	dispscore(1);
}
void destroyhim()
{
	setfillstyle(4,1);
	bar(x,y,x+38,y+38);
	sound(500);
	delay(100);
	nosound();
	cleartank(x,y);
	xl[1]++;
	score+=30;
	dispscore(3);
	dispscore(2);
	y=0;
	if(flag==0)
	{
		flag=1;
		x=61;
	}
	else
	{
		flag=0;
		x=541;
	}
}

int checkpixelb(int constant,int variable,int condt,int extent,int direction)
{
	int	v=variable,pixel,c=constant,c1=constant,p=0,flag=0,pi=100,k;
	int 	xc,yc;
		if(condt==0)
		{
			if(direction==2)
			while(constant>=c-1&&flag==0)
			{
				variable=v;
				while(variable<=v+extent&&flag==0)
				{
					pixel = getpixel(constant,variable);
					switch(pixel)
					{
						case 0:break;
						case 11:xl[3]=1;break;
						case 2:
						{
							destroyme();
							if(c==xa-2)
							{
								clearblt(xa,ya);

							}
							else if(c==xb-2)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 1:
						{
							destroyhim();
							if(c==xa-2)
							{
								clearblt(xa,ya);

							}
							else if(c==xb-2)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 9:
						{
							clearblt(xa,ya);
							clearblt(xb,yb);
							return 0;
						}
						case 12:case 4:case 7:
						{
							setfillstyle(1,0);
							xc=constant;
							yc=variable;
							while(pi!=0)
							{
								variable=v;
								pi=0;
								while(variable<=v+extent)
								{
									if(getpixel(c1,variable)!=0)pi=getpixel(c1,variable);
									variable++;
								}
								c1++;
							}
							flag=1;
							c1--;
							bar(c1-20,yc-(yc%20),c1-1,yc-(yc%20)+20);
							if(c==xa-2)
							{
								clearblt(xa,ya);

							}
							else if(c==xb-2)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
					}
					if(pixel!=0)p=pixel;
					variable++;
				}
				constant--;
			}
			if(direction==4)
			while(constant<=c+1)
			{
				variable=v;
				while(variable<=v+extent)
				{
					pixel = getpixel(constant,variable);
					switch(pixel)
					{
						case 0:break;
						case 11:xl[3]=1;break;
						case 2:
						{
							destroyme();
							if(c==xa+8)
							{
								clearblt(xa,ya);

							}
							else if(c==xb+8)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 1:
						{
							destroyhim();
							if(c==xa+8)
							{
								clearblt(xa,ya);

							}
							else if(c==xb+8)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 9:
						{
							clearblt(xa,ya);
							clearblt(xb,yb);
							return 0;
						}
						case 12:case 4:case 7:
						{
							setfillstyle(1,0);
							xc=constant;
							yc=variable;
							while(pi!=0)
							{
								variable=v;
								pi=0;
								while(variable<=v+extent)
								{
									if(getpixel(c1,variable)!=0)pi=getpixel(c1,variable);
									variable++;
								}
								c1--;
							}
							flag=1;
							c1++;
							bar(c1+1,yc-(yc%20),c1+20,yc-(yc%20)+20);
							if(c==xa+8)
							{
								clearblt(xa,ya);

							}
							else if(c==xb+8)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
					}
					if(pixel!=0)p=pixel;
					variable++;
				}
				constant++;
			}
		}
		if(condt==1)
		{
			if(direction==1)
			while(constant<=c+1)
			{
				variable=v;
				while(variable<=v+extent)
				{
					pixel = getpixel(variable,constant);
					switch(pixel)
					{
						case 0:break;
						case 11:xl[3]=1;break;
						case 2:
						{
							destroyme();
							if(c==ya+8)
							{
								clearblt(xa,ya);

							}
							else if(c==yb+8)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 1:
						{
							destroyhim();
							if(c==ya+8)
							{
								clearblt(xa,ya);

							}
							else if(c==yb+8)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 9:
						{
							clearblt(xa,ya);
							clearblt(xb,yb);
							return 0;
						}
						case 12:case 4:case 7:
						{
							setfillstyle(1,0);
							xc=variable;
							yc=constant;
							while(pi!=0)
							{
								variable=v;
								pi=0;
								while(variable<=v+extent)
								{
									if(getpixel(variable,c1)!=0)pi=getpixel(variable,c1);
									variable++;
								}
								c1--;
							}
							c1++;
							bar(xc-(xc%20),c1+1,xc-(xc%20)+20,c1+20);
							if(c==ya+8)
							{
								clearblt(xa,ya);

							}
							else if(c==yb+8)
							{
								clearblt(xb,yb);

							}
						}
					}
					variable++;
					if(pixel!=0)p=pixel;
				}
				constant++;
			}
			if(direction==3)
			while(constant>=c-1)
			{
				variable=v;
				while(variable<=v+extent)
				{
					pixel = getpixel(variable,constant);
					switch(pixel)
					{
						case 0:break;
						case 11:xl[3]=1;break;
						case 2:
						{
							destroyme();
							if(c==ya-2)
							{
								clearblt(xa,ya);

							}
							else if(c==yb-2)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 1:
						{
							destroyhim();
							if(c==ya-2)
							{
								clearblt(xa,ya);

							}
							else if(c==yb-2)
							{
								clearblt(xb,yb);

							}
							return 0;
						}
						case 9:
						{
							clearblt(xa,ya);
							clearblt(xb,yb);
							return 0;
						}
						case 12:case 4:case 7:
						{
							setfillstyle(1,0);
							xc=variable;
							yc=constant;
							while(pi!=0)
							{
								variable=v;
								pi=0;
								while(variable<=v+extent)
								{
									if(getpixel(variable,c1)!=0)pi=getpixel(variable,c1);
									variable++;
								}
								c1++;
							}
							flag=1;
							bar(xc-(xc%20),c1-2,xc-(xc%20)+20,c1-21);
							if(c==ya-2)
							{
								clearblt(xa,ya);

							}
							else if(c==yb-2)
							{
								clearblt(xb,yb);

							}
						}
					}
					variable++;
					if(pixel!=0)p=pixel;
				}
				constant--;
			}
		}
		if(p==0)return 1;
			else return 0;
}
void sound()
{
		int     s[30],i=0;
		s[0]=261;s[1]=293;s[2]=311;
		s[3]=261;s[4]=293;s[5]=311;
		s[6]=293;s[7]=311;s[8]=349;
		s[9]=293;s[10]=311;s[11]=349;
		s[12]=311;s[13]=349;s[14]=391;
		s[15]=311;s[16]=349;s[17]=391;
		s[18]=349;s[19]=391;s[20]=440;
		s[21]=391;s[22]=440;s[23]=494;
		s[24]=523;
		while(i<=23)
		{
			sound(s[i]);
			delay(150);
			nosound();
			i++;
		}
		sound(s[24]);
		delay(100);
		nosound();
		delay(350);
		i++;
		s[25]=s[26]=s[27]=s[28]=523;
		while(i<=28)
		{

			sound(s[i]);
			delay(80);
			nosound();
			delay(80);
			i++;
		}
}
void pause()
{
	char 	c=0;
	setfillstyle(1,15);
	setcolor(4);
	bar(5,300,55,340);
	settextstyle(2,0,4);
	outtextxy(12,300,"Paused");
	while(c!='p')
	{
		c=getch();
	}
	bar(12,300,46,320);
	setcolor(3);
	outtextxy(5,300,"Press 'p'");
	outtextxy(5,320,"to pause");
}
void t1move(int &x1,int &y1,int &direction2,int c)
{
		if(y1>=440&&c==20480)return;
		else if(y1<=0&&c==18432)return;
		switch(c)
		{
			case 18432:
			{
				if((checkpixelt(y1-2,x1,1,38,direction2))||direction2!=3)
				{
					if(direction2==3)y1-=2;
					setfillstyle(1,0);
					bar(x1,y1,x1+38,y1+38);
					tank1a(x1+19,y1+19);
					direction2=3;
				}
			}break;
			case 19200:
			{
				if((checkpixelt(x1-2,y1,0,38,direction2))||direction2!=2)
				{
					if(direction2==2)x1-=2;
					setfillstyle(1,0);
					bar(x1,y1,x1+38,y1+38);
					tank1b(x1+19,y1+19);
					direction2=2;
				}
			}break;
			case 20480:
			{
				if((checkpixelt(y1+39,x1,1,38,direction2))||direction2!=1)
				{
					if(direction2==1)y1+=2;
					setfillstyle(1,0);
					bar(x1,y1,x1+38,y1+38);
					tank1c(x1+19,y1+19);
					direction2=1;
				}
			}break;
			case 19712:
			{
				if((checkpixelt(x1+39,y1,0,38,direction2))||direction2!=4)
				{
					if(direction2==4)x1+=2;
					setfillstyle(1,0);
					bar(x1,y1,x1+38,y1+38);
					tank1d(x1+19,y1+19);
					direction2=4;
				}
			}break;
			case 283:
			{
				exit(0);
			}break;
			case 6512:
			{
				pause();
			}
		}
}
void dispscore(int r)
{
	settextstyle(2,0,4);
	char dummy[23];
	char dum[20];
	if(r==0)
	{
		setcolor(8);
		rectangle(585,150,635,180);
		rectangle(585,195,635,245);
		rectangle(585,260,635,290);
		setfillstyle(0,0);
		bar(585,200,635,240);
		bar(585,155,635,175);
		bar(585,265,635,285);
		setcolor(15);
		outtextxy(588,160,"Life  :");
		outtextxy(629,160,"3");
		itoa(max,dum,10);
		outtextxy(588,270,"Enemy :");
		outtextxy(629,270,dum);
		outtextxy(595,200,"Score");
		line(594,212,624,212);
		outtextxy(601,220,"000");

	}
	else
	{
		setfillstyle(1,0);
		setcolor(15);
		switch(r)
		{
			case 1:
			{
				bar(628,161,633,170);
				itoa	(3-xl[2],dummy,10);
				outtextxy(629,160,dummy);
			}break;
			case 2:
			{
				if(max-xl[1]>=0)
				{
					bar(628,271,633,280);
					itoa (max-xl[1],dummy,10);
					outtextxy(629,270,dummy);
				}
			}break;
			case 3:
			{
				itoa(score,dummy,10);
				if(score>=100)
				{
					bar(600,221,617,230);
					outtextxy(601,220,dummy);
				}
				else if(score>=10)
				{
					bar(606,221,617,230);
					outtextxy(607,220,dummy);
				}
				else if(score==0)
				{
					bar(600,221,617,230);
					outtextxy(601,220,"000");
				}
			}break;
		}
	}
}
void t2move(int &x,int &y,int &direction,int a,int b,int c,int d)
{
		o++;
		int t,p;
		t=200;
		if(y<441)dir=1;
		if(y>=441&&dir==1)
		{
			switch(random(50))
			{
				case 0:direction=3;break;
				default :
				{
					switch(random(2))
					{
						case 0:direction=4;break;
						case 1:direction=2;break;
					}
				}
			}
			dir=0;
		}
		if(y<0)direction=1;
		switch(direction)
		{

			case 1:
			{
				if(checkpixelt(y+38,x,1,38,0)&&o%t!=0)
				{
					y+=1;
					setfillstyle(1,0);
					bar(x,y,x+38,y+38);
					tank2c(x+19,y+19,a,b,c,d);
					direction=1;
					delay(20);
				}
				else
				{
					p=random(5);
					switch(p)
					{
						case 0:
						{
							p=random(2);
							switch(p)
							{
								case 0: direction=1;break;
								case 1: direction=4;
							}
						}break;
						default:
						{
							if(dir==1)direction=1;
							if((y>=440&&random(4)==0)||random(30)==1)direction=4;
						}
					}
				}
			}break;
			case 4:
			{
				if(checkpixelt(x+38,y,0,38,0)&&o%t!=0)
				{
					x+=1;
					setfillstyle(1,0);
					bar(x,y,x+38,y+38);
					tank2d(x+19,y+19,a,b,c,d);
					direction=4;
					delay(20);
				}
				else
				{
					p=random(5);
					switch(p)
					{
						case 0:
						{
							p=random(2);
							switch(p)
							{
								case 0: direction=2;break;
								case 1: direction=4;
							}
						}break;
						default:
						{
							if(dir==1)direction=1;
							if((y>=440&&random(4)==0)||random(30)==1)direction=3;
						}
					}
				}
			}break;
			case 3:
			{
				if(checkpixelt(y-1,x,1,38,0)&&o%t!=0)
				{
					y-=1;
					setfillstyle(1,0);
					bar(x,y,x+38,y+38);
					tank2a(x+19,y+19,a,b,c,d);
					direction=3;
					delay(20);
				}
				else
				{
					p=random(5);
					switch(p)
					{
						case 0:
						{
							p=random(2);
							switch(p)
							{
								case 0: direction=2;break;
								case 1: direction=4;
							}
						}break;
						default :
						{
							if(dir==1)direction=1;
							if((y>=440&&random(4)==0)||random(30)==1)direction=2;
						}
					}
				}
			}break;
			case 2:
			{
				if(checkpixelt(x-1,y,0,38,0)&&o%t!=0)
				{
					x-=1;
					setfillstyle(1,0);
					bar(x,y,x+38,y+38);
					tank2b(x+19,y+19,a,b,c,d);
					direction=2;
					delay(20);
				}
				else
				{
					p=random(5);
					switch(p)
					{
						case 0:
						{
							p=random(2);
							switch(p)
							{
								case 0: direction=2;break;
								case 1: direction=4;
							}
						}break;
						default:
						{
							if(dir==1)direction=1;
							if((y>=440&&random(4)==0)||random(30)==1)direction=3;
						}
					}
				}
			}break;
		}
}
void select()
{
	int 	size,b,f=0,d,x2=450,y2=200,x3=300,y3=420,direction3=2;
	char	*a;
		setfillstyle(1,9);
		setcolor(1);
		rectangle(x-50,y-100,x-60,y-105);
		line(x-50,y-105,x-50,y-108);
		line(x-50,y-100,x-50,y-97);
		line(x-46,y-102,x-50,y-108);
		line(x-46,y-102,x-50,y-97);
		setcolor(0);
		line(x-50,y-104,x-50,y-101);
		floodfill(x-50,y-102,1);
		size=imagesize(x-60,y-97,x-46,y-108);
		a = (char*)malloc(size);
		getimage(x-60,y-97,x-46,y-108,a);
		setfillstyle(1,0);
		bar(x-60,y-97,x-46,y-108);
		d=y-65;
		putimage(x-66,d,a,0);
		x1=100;
		y1=200;
		do
		{
			while(bioskey(1)==0)
			{
				t2move(x1,y1,direction,1,3,4,10);
				t2move(x2,y2,direction2,2,4,14,6);
				t2move(x3,y3,direction3,4,5,1,13);
			}
			b=bioskey(0);
			switch(b)
			{
				case 7181   :
				{
					if(d==y-65)
					{
						void start();
						start();
						f++;
					}
					else if(d==y-4)
					{
						disp();
						f++;
						getch();
						cleardevice();
						mainscreen();
					}
					else if(d==y+57)
					{
						void help();
						help();
						f++;
						getch();
						cleardevice();
						mainscreen();
					}
					else if(d==y+118)
					{       credits();
						getch();
						getch();
						exit(0);
					}
				}break;
				case 20480  :
				{
					setfillstyle(1,0);
					bar(x-66,d,x-51,d+12);
					if(d==y+118)d=y-65;
					else  d=d+61;
					putimage(x-66,d,a,0);
				}break; 				//down
				case 18432  :
				{
					setfillstyle(1,0);
					bar(x-66,d,x-51,d+12);
					if(d==y-65)d=y+118;
					else	d=d-61;
					putimage(x-66,d,a,0);break;  	//up
				}
				case 283   :
				{
					exit(0);
				}
			}
		}while(f==0);
		delete a;
}
void moveall(int &xa,int &ya,int &xb,int &yb)
{
	int k=0,c;
	switch(directionb)
	{
		case 1:
		{
			switch(directionb2)
			{
				case 1:
				{
					for(int i=1;checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1))
						{
							if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1)
							{
								yb+=1;
								bullet(xb,yb);
							}
							if(yb!=y1+37&&checkpixelb(yb+8,xb-2,1,10,1)==0&&flag2==1)
							{
								clearblt(xb,yb);
								
							}
							if(checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								ya+=1;
								bullet(xa,ya);
							}
							if(ya!=y+37&&checkpixelb(ya+8,xa-2,1,10,1)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 2:
				{
					for(;checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1;)
					{
						while(bioskey(1)==0&&(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1))
						{
							if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1)
							{
								xb-=1;
								bullet(xb,yb);
							}
							if(xb!=x1-8&&checkpixelb(xb-2,yb-2,0,10,2)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								ya+=1;
								bullet(xa,ya);
							}
							if(ya!=y+37&&checkpixelb(ya+8,xa-2,1,10,1)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 3:
				{
					for(int i=1;checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1))
						{
							if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1)
							{
								yb-=1;
								bullet(xb,yb);
							}
							if(yb!=y1-7&&checkpixelb(yb-2,xb-2,1,10,3)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								ya+=1;
								bullet(xa,ya);
							}
							if(ya!=y+37&&checkpixelb(ya+8,xa-2,1,10,1)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 4:
				{
					for(int i=1;checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag2==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag2==1))
						{
							if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1)
							{
								xb+=1;
								bullet(xb,yb);
							}
							if(xb!=x1+37&&checkpixelb(xb+8,yb-2,0,10,4)==0&&flag2==1)
							{
								clearblt(xb,yb);
								
							}
							if(checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								ya+=1;
								bullet(xa,ya);
							}
							if(ya!=y+37&&checkpixelb(ya+8,xa-2,1,10,1)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya+8,xa-2,1,10,1)&&flag2==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
			}
		}break;
		case 2:
		{
			switch(directionb2)
			{
				case 1:
				{
					for(int i=1;checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1))
						{
							if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1)
							{
								yb+=1;
								bullet(xb,yb);
							}
							if(yb!=y1+37&&checkpixelb(yb+8,xb-2,1,10,1)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{
								xa--;
								bullet(xa,ya);
							}
							if(xa!=x-8&&checkpixelb(xa-2,ya-2,0,10,2)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 2:
				{
					for(int i=1;checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1))
						{
							if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1)
							{
								xb-=1;
								bullet(xb,yb);
							}
							if(xb!=x1-8&&checkpixelb(xb-2,yb-2,0,10,2)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{
								xa--;
								bullet(xa,ya);
							}
							if(xa!=x-8&&checkpixelb(xa-2,ya-2,0,10,2)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 3:
				{
					for(int i=1;checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1))
						{
							if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1)
							{
								yb-=1;
								bullet(xb,yb);
							}
							if(yb!=y1-7&&checkpixelb(yb-2,xb-2,1,10,3)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{
								xa--;
								bullet(xa,ya);
							}
							if(xa!=x-8&&checkpixelb(xa-2,ya-2,0,10,2)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 4:
				{
					for(int i=1;checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1))
						{
							if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1)
							{
								xb+=1;
								bullet(xb,yb);
							}
							if(xb!=x1+37&&checkpixelb(xb+8,yb-2,0,10,4)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{
								xa--;
								bullet(xa,ya);
							}
							if(xa!=x-8&&checkpixelb(xa-2,ya-2,0,10,2)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
			}
		}break;
		case 3:
		{
			switch(directionb2)
			{
				case 1:
				{
					for(int i=1;checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1))
						{
							if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1)
							{
								yb+=1;
								bullet(xb,yb);
							}
							if(yb!=y1+37&&checkpixelb(yb+8,xb-2,1,10,1)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								ya--;
								bullet(xa,ya);
							}
							if(ya!=y-7&&checkpixelb(ya-2,xa-2,1,10,3)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 2:
				{
					for(int i=1;checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1))
						{
							if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1)
							{
								xb-=1;
								bullet(xb,yb);
							}
							if(xb!=x1-8&&checkpixelb(xb-2,yb-2,0,10,2)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								ya--;
								bullet(xa,ya);
							}
							if(ya!=y-7&&checkpixelb(ya-2,xa-2,1,10,3)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 3:
				{
					for(int i=1;checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1))
						{
							if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1)
							{
								yb-=1;
								bullet(xb,yb);
							}
							if(yb!=y1-7&&checkpixelb(yb-2,xb-2,1,10,3)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								ya--;
								bullet(xa,ya);
							}
							if(ya!=y-7&&checkpixelb(ya-2,xa-2,1,10,3)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 4:
				{
					for(int i=1;checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1))
						{
							if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1)
							{
								xb+=1;
								bullet(xb,yb);
							}
							if(xb!=x1+37&&checkpixelb(xb+8,yb-2,0,10,4)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								ya--;
								bullet(xa,ya);
							}
							if(ya!=y-7&&checkpixelb(ya-2,xa-2,1,10,3)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
			}
		}break;
		case 4:
		{
			switch(directionb2)
			{
				case 1:
				{
					for(int i=1;checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1))
						{
							if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1)
							{
								yb+=1;
								bullet(xb,yb);
							}
							if(yb!=y1+37&&checkpixelb(yb+8,xb-2,1,10,1)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								xa+=1;
								bullet(xa,ya);
							}
							if(xa!=x+37&&checkpixelb(xa+8,ya-2,0,10,4)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 2:
				{
					for(int i=1;checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1))
						{
							if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1)
							{
								xb-=1;
								bullet(xb,yb);
							}
							if(xb!=x1-8&&checkpixelb(xb-2,yb-2,0,10,2)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								xa+=1;
								bullet(xa,ya);
							}
							if(xa!=x+37&&checkpixelb(xa+8,ya-2,0,10,4)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb-2,yb-2,0,10,2)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 3:
				{
					for(int i=1;checkpixelb(yb-2,xb-2,1,10,direction2)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1))
						{
							if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1)
							{
								yb-=1;
								bullet(xb,yb);
							}
							if(yb!=y1-7&&checkpixelb(yb-2,xb-2,1,10,3)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								xa+=1;
								bullet(xa,ya);
							}
							if(xa!=x+37&&checkpixelb(xa+8,ya-2,0,10,4)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}break;
				case 4:
				{
					for(int i=1;checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1;i++)
					{
						while(bioskey(1)==0&&(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1))
						{
							if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1)
							{
								xb+=1;
								bullet(xb,yb);
							}
							if(xb!=x1+37&&checkpixelb(xb+8,yb-2,0,10,4)==0&&flag2==1)
							{
								clearblt(xb,yb);

							}
							if(checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								xa+=1;
								bullet(xa,ya);
							}
							if(xa!=x+37&&checkpixelb(xa+8,ya-2,0,10,4)==0&&flag1==1)
							{
								clearblt(xa,ya);

							}
							if(k%5==0)t2move(x,y,direction,1,3,4,10);
							k++;
						}
						if(checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1||checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
						{
							c=bioskey(0);
							t1move(x1,y1,direction2,c);
						}
					}
				}
			}
		}
	}
}
void move(int l)
{
	int	c,a,i;
		cleardevice();
		x1=80;y1=0;
		x=320;y=240;
		switch(l)
		{
			case 1:level1();max=2;break;
			case 2:level2();max=3;break;
			case 3:level3();max=4;break;
			case 4:level4();max=5;break;
		}
		x1=241;y1=441;x=61;y=0;
		direction=4;
		dispscore(0);
		randomize();
		do
		{
			while(bioskey(1)==0)
			{
				t2move(x,y,direction,1,3,4,10);
				if(random(50)==2)
				{
					int 	b,c,j=0;
						flag1=1;
					if(direction==1)
					{
						directionb=1;
						xa=x+15;
						ya=y+37;

						for(;checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1;)
						{
							while(bioskey(1)==0&&checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								ya+=1;
								bullet(xa,ya);
								if(j%5==0)t2move(x,y,direction,1,3,4,10);
								j++;
							}
							if(checkpixelb(ya+8,xa-2,1,10,1)&&flag1==1)
							{
								c=bioskey(0);
								t1move(x1,y1,direction2,c);
								if(c==14624)
								{
									flag2=1;
									if(direction2==1)
									{
										directionb2=1;

										xb=x1+15;
										yb=y1+37;
										moveall(xa,ya,xb,yb);
										if(yb!=y1+37&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==2)
									{
										directionb2=2;

										yb=y1+15;
										xb=x1-8;
										moveall(xa,ya,xb,yb);
										if(xb!=x1-8&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==3)
									{
										directionb2=3;

										xb=x1+15;
										yb=y1-7;
										moveall(xa,ya,xb,yb);
										if(yb!=y1-7&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==4)
									{
										directionb2=4;

										yb=y1+15;
										xb=x1+37;
										moveall(xa,ya,xb,yb);
										if(xb!=x1+37&&flag2==0)
										{
											clearblt(xb,yb);

										}
									}
								}
							}
						}
						if(ya!=y+37&&flag1==1)
						{
							clearblt(xa,ya);
							
						}
					}
					if(direction==2)
					{
						directionb=2;

						ya=y+15;
						xa=x-8;
						int k=x;
						for(;checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1;)
						{
							while(bioskey(1)==0&&checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{

								xa-=1;
								bullet(xa,ya);
								if(j%5==0)t2move(x,y,direction,1,3,4,10);
								j++;
							}
							if(checkpixelb(xa-2,ya-2,0,10,2)&&flag1==1)
							{
								c=bioskey(0);
								t1move(x1,y1,direction2,c);
								if(c==14624)
								{
									flag2=1;
									if(direction2==1)
									{
										directionb2=1;

										xb=x1+15;
										yb=y1+37;
										moveall(xa,ya,xb,yb);
										if(yb!=y1+37&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==2)
									{
										directionb2=2;

										yb=y1+15;
										xb=x1-8;
										moveall(xa,ya,xb,yb);
										if(xb!=x1-8&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==3)
									{
										directionb2=3;

										xb=x1+15;
										yb=y1-7;
										moveall(xa,ya,xb,yb);
										if(yb!=y1-7&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==4)
									{
										directionb2=4;

										yb=y1+15;
										xb=x1+37;
										moveall(xa,ya,xb,yb);
										if(xb!=x1+37&&flag2==0)
										{
											clearblt(xb,yb);

										}
									}
								}
							}
						}
						if(xa!=k-8&&flag1==1)
						{
							clearblt(xa,ya);

						}
					}
					if(direction==3)
					{
						directionb=3;

						xa=x+15;
						ya=y-7;
						for(;checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1;)
						{
							while(bioskey(1)==0&&checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								ya-=1;
								bullet(xa,ya);
								if(j%5==0)t2move(x,y,direction,1,3,4,10);
								j++;
							}
							if(checkpixelb(ya-2,xa-2,1,10,3)&&flag1==1)
							{
								c=bioskey(0);
								t1move(x1,y1,direction2,c);
								if(c==14624)
								{
									flag2=1;
									if(direction2==1)
									{
										directionb2=1;

										xb=x1+15;
										yb=y1+37;
										moveall(xa,ya,xb,yb);
										if(yb!=y1+37&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==2)
									{
										directionb2=2;

										yb=y1+15;
										xb=x1-8;
										moveall(xa,ya,xb,yb);
										if(xb!=x1-8&&flag2==1)
										{
											clearblt(xb,yb);
											
										}
									}
									if(direction2==3)
									{
										directionb2=3;

										xb=x1+15;
										yb=y1-7;
										moveall(xa,ya,xb,yb);
										if(yb!=y1-7&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==4)
									{
										directionb2=4;

										yb=y1+15;
										xb=x1+37;
										moveall(xa,ya,xb,yb);
										if(xb!=x1+37&&flag2==0)
										{
											clearblt(xb,yb);

										}
									}
								}
							}
						}
						if(ya!=y-7&&flag1==1)
						{
							clearblt(xa,ya);

						}
					}
					if(direction==4)
					{
						directionb=4;

						ya=y+15;
						xa=x+37;
						for(;checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1;)
						{
							while(bioskey(1)==0&&checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								xa+=1;
								bullet(xa,ya);
								if(j%5==0)t2move(x,y,direction,1,3,4,10);
								j++;
							}
							if(checkpixelb(xa+8,ya-2,0,10,4)&&flag1==1)
							{
								c=bioskey(0);
								t1move(x1,y1,direction2,c);
								if(c==14624)
								{
									flag2=1;
									if(direction2==1)
									{
										directionb2=1;

										xb=x1+15;
										yb=y1+37;
										moveall(xa,ya,xb,yb);
										if(yb!=y1+37&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==2)
									{
										directionb2=2;

										yb=y1+15;
										xb=x1-8;
										moveall(xa,ya,xb,yb);
										if(xb!=x1-8&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==3)
									{
										directionb2=3;

										xb=x1+15;
										yb=y1-7;
										moveall(xa,ya,xb,yb);
										if(yb!=y1-7&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
									if(direction2==4)
									{
										directionb2=4;

										yb=y1+15;
										xb=x1+37;
										moveall(xa,ya,xb,yb);
										if(xb!=x1+37&&flag2==1)
										{
											clearblt(xb,yb);

										}
									}
								}
							}
						}
						if(xa!=x+37&&flag1==1)
						{
							clearblt(xa,ya);

						}
					}
				}
			}
			c=bioskey(0);
			t1move(x1,y1,direction2,c);
			if(c==14624)
			{
				int 	j=0;
					flag2=1;
				if(direction2==1)
				{
					directionb2=1;

					xb=x1+15;
					yb=y1+37;
					for(;checkpixelb(yb+8,xb-2,1,10,1)&&flag2==1;)
					{
						yb+=1;
						bullet(xb,yb);
						if(j%5==0)
						{
							t2move(x,y,direction,1,3,4,10);
							if(random(5)==2)
							{
								flag1=1;
								if(direction==1)
								{
									directionb=1;
									xa=x+15;
									ya=y+37;

									moveall(xa,ya,xb,yb);
									if(ya!=y+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==2)
								{
									directionb=2;

									ya=y+15;
									xa=x-8;
									moveall(xa,ya,xb,yb);
									if(xa!=x-8&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==3)
								{
									directionb=3;

									xa=x+15;
									ya=y-7;
									moveall(xa,ya,xb,yb);
									if(ya!=y-7&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==4)
								{
									directionb=4;

									ya=y+15;
									xa=x+37;
									moveall(xa,ya,xb,yb);
									if(xa!=x+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
							}
						}
						j++;
					}
					if(yb!=y1+37&&flag2==1)
					{
						clearblt(xb,yb);

					}
				}
				if(direction2==2)
				{
					directionb2=2;

					yb=y1+15;
					xb=x1-8;
					for(;checkpixelb(xb-2,yb-2,0,10,direction2)&&flag2==1;)
					{
						xb-=1;
						bullet(xb,yb);
						if(j%5==0)
						{
							t2move(x,y,direction,1,3,4,10);
							if(random(5)==2)
							{
								flag1=1;
								if(direction==1)
								{
									directionb=1;
									xa=x+15;
									ya=y+37;

									moveall(xa,ya,xb,yb);
									if(ya!=y+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==2)
								{
									directionb=2;

									ya=y+15;
									xa=x-8;
									moveall(xa,ya,xb,yb);
									if(xa!=x-8&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==3)
								{
									directionb=3;

									xa=x+15;
									ya=y-7;
									moveall(xa,ya,xb,yb);
									if(ya!=y-7&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==4)
								{
									directionb=4;

									ya=y+15;
									xa=x+37;
									moveall(xa,ya,xb,yb);
									if(xa!=x+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
							}
						}
						j++;
					}
					if(xb!=x1-8&&flag2==1)
					{
						clearblt(xb,yb);

					}
				}
				if(direction2==3)
				{
					directionb2=3;

					xb=x1+15;
					yb=y1-7;
					for(;checkpixelb(yb-2,xb-2,1,10,3)&&flag2==1;)
					{
						yb-=1;
						bullet(xb,yb);
						if(j%5==0)
						{
							t2move(x,y,direction,1,3,4,10);
							if(random(5)==2)
							{
								flag1=1;
								if(direction==1)
								{
									directionb=1;
									xa=x+15;
									ya=y+37;

									moveall(xa,ya,xb,yb);
									if(ya!=y+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==2)
								{
									directionb=2;

									ya=y+15;
									xa=x-8;
									moveall(xa,ya,xb,yb);
									if(xa!=x-8&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==3)
								{
									directionb=3;

									xa=x+15;
									ya=y-7;
									moveall(xa,ya,xb,yb);
									if(ya!=y-7&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==4)
								{
									directionb=4;

									ya=y+15;
									xa=x+37;
									moveall(xa,ya,xb,yb);
									if(xa!=x+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
							}
						}
						j++;
					}
					if(yb!=y1-7&&flag2==1)
					{
						clearblt(xb,yb);

					}
				}
				if(direction2==4)
				{
					directionb2=4;

					yb=y1+15;
					xb=x1+37;
					for(;checkpixelb(xb+8,yb-2,0,10,4)&&flag2==1;)
					{
						xb+=1;
						bullet(xb,yb);
						if(j%5==0)
						{
							t2move(x,y,direction,1,3,4,10);
							if(random(5)==2)
							{
								flag1=1;
								if(direction==1)
								{
									directionb=1;
									xa=x+15;
									ya=y+37;

									moveall(xa,ya,xb,yb);
									if(ya!=y+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==2)
								{
									directionb=2;

									ya=y+15;
									xa=x-8;
									moveall(xa,ya,xb,yb);
									if(xa!=x-8&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==3)
								{
									directionb=3;

									xa=x+15;
									ya=y-7;
									moveall(xa,ya,xb,yb);
									if(ya!=y-7&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
								if(direction==4)
								{
									directionb=4;

									ya=y+15;
									xa=x+37;
									moveall(xa,ya,xb,yb);
									if(xa!=x+37&&flag1==1)
									{
										clearblt(xa,ya);

									}
								}
							}
						}
						j++;
					}
					if(xb!=x1+37&&flag2==1)
					{
						clearblt(xb,yb);

					}
				}
			}
		if(xl[0]>=max&&xl[1]>=max)
		{
			cleardevice();
			setfillstyle(1,1);
			setcolor(11);
			settextstyle(10,0,4);
			outtextxy(210,200,"You Win");
			floodfill(2,2,11);
			floodfill(255,250,11);
			getch();
			delay(1000);
			score+=50;
			dispscore(3);
			return;
		}
		if(xl[2]==3||xl[3]==1)
		{
			cleardevice();
			settextstyle(10,0,4);
			setfillstyle(1,12);
			setcolor(4);
			outtextxy(190,200,"You Loose");
			floodfill(145,332,4);
			floodfill(235,250,4);
			floodfill(425,240,4) ;
			floodfill(345,245,4);
			floodfill(370,245,4);
			getch();
			delay(1000);
			cleardevice();
			highscore(score);
			exit(0);
		}
	} while(a!=283);

}
void help()
{
	cleardevice();
	settextstyle(9,0,2);
	setcolor(4);
	line(190,68,430,68);
	line(190,70,430,70);
	outtextxy(200,30,"INSTRUCTIONS");
	settextstyle(8,0,1);
	setcolor(15);
	outtextxy(40,80,"To pass each level you must collect a certain number of");
	outtextxy(40,100,"fuel barrels and destroy certain number of enemy tanks.");
	outtextxy(40,140,"First level: Collect 2 fuel and Desrtroy 2 tanks.");
	outtextxy(40,180,"Second level: Collect 3 fuel and Desrtroy 3 tanks.");
	outtextxy(40,220,"Third level: Collect 4 fuel and Desrtroy 4 tanks.");
	outtextxy(40,260,"Last level: Collect 5 fuel and Desrtroy 5 tanks.");
	outtextxy(40,300,"If you are destroyed three times or if the dove is killed,");
	outtextxy(300,340,"You Loose");
	outtextxy(40,380,"GOOD LUCK for your mission!!!!");
}
void main()
{
	int 	a = 9,b = 2;
		initgraph(&a,&b,"c:\\turboc3\\bgi");
		mainscreen();
		getch();
}




















































































































































































































































































































































































































































































































































































































