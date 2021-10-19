#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
#include<cstring>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
#include <fstream>


using namespace std;

void BG();
void Border();
void DrawSquares(int,int,int,int);
void Food(int[],int[]);
void PowerFood(int [],int[]);
void Collision(int[],int[],int,int);
void Scores(int);
void Hurdles(int[],int[]);
void Hurdles2(int[],int[]);
void Hurdles3(int[],int[]);
void SnakeBar();
void HighScores(int);
void Menu();
void Level(int);


/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


int startx=200,starty=200;
int counterX,counterY,newPosn,snakex[100],snakey[100],score1=0,score2=0,arrx[65],arry[65],eaten=4,PrevPosn;
int choice,bar=4,bar2=4,bar3=4;
int valuex[5],pfoodx;
int valuey[5],pfoody;
int x11=0,x22=0,y11=0,y22=0;
int maxscore; 
int x111=0,x222=0,y111=0,y222=0;
int x1111=0,x2222=0,y1111=0,y2222=0,vertx1=0,vertx2=0,verty1=0,verty2=0;
bool hit=0;
int enter=0,xyz;
int SBL=1;

time_t earlier_time=time(NULL);
time_t current_time;
time_t earlier_time1=time(NULL);
time_t current_time1;
time_t earlier_time2=time(NULL);
time_t current_time2;
time_t earlier_time3=time(NULL);
time_t current_time3;
time_t earlier_time4=time(NULL);
time_t current_time4;
time_t earlier_time5=time(NULL);
time_t current_time5;



void Menu()
{
	int n=300,m=360;
	DrawRoundRect( n-20 , m ,180,50,colors[53]);
	DrawString(n,m,"New Game ",colors[130]);
	DrawString(n,m-60,"Resume Game ",colors[130]);
	DrawString(n,m-120,"Change Level ",colors[130]);
	DrawString(n,m-180,"High Score ",colors[130]);
	DrawString(n,m-240,"Game History ",colors[130]);
	DrawString(n,m-300,"Exit ",colors[130]);
	
	
	
	if(newPosn==3)
	{
		m-=60;
		
		DrawRoundRect( n-20 , m ,180,50,colors[53]);
		
		//if(n==300&& m==300)
		//{
		//	DrawString(n,m,"New Game ",colors[130]);
		//	if (enter==1)
		//	choice=1;
			
		//}	
				
		 if(n==300&& m==300)
		{
			DrawString(n,m,"Resume Game ",colors[130]);
			if (enter==1)
			choice=2;
		}
		
		
		else if(n==300&& m==240)
		{
			DrawString(n,m,"Change Level ",colors[130]);
			if (enter==1)
			choice=3;
		}
		else if(n==300&& m==180)
		{
			DrawString(n,m,"High Score",colors[130]);
			if (enter==1)
			choice=4;
		}
		else if(n==300&& m==120)
		{
			DrawString(n,m,"Game History",colors[130]);
			if (enter==1)
			choice=5;
		}
		else if(n==300&& m==60)
		{
			DrawString(n,m,"Exit ",colors[130]);
			if (enter==1)
			exit(1);
		}
		
	}
	else if(newPosn==2)
	{
		
		m=m+60;
		DrawSquare( n-20 , m ,60,colors[53]);	
	}
	
}

void BG()
{
	for(int a=0;a<65;a++)
    	{
    		for(int b=0;b<65;b++)
    		{
    			DrawSquare( a*10 , b*10 ,11,colors[81]); 
    		}
    	}
}


void Border()
{
	DrawLine(0,0,0,650,650,colors[64]);
	DrawLine(0,0,650,0,650,colors[64]);
	DrawLine(650,0,650,650,650,colors[64]);
	DrawLine(650,650,0,650,650,colors[64]);
}

void DrawSquares(int counterX,int counterY,int startx,int starty)
{
	DrawSquare(counterX,counterY,10,colors[31]);
	startx+=counterX;
    	starty+=counterY;
}



void HighScores(int maxscore)
{

	ifstream HS;
	ofstream Scr;
	HS.open("highscores.txt",ios::app);
	HS>>maxscore;
	HS.close();
	if(maxscore <= score1)
	{
		Scr.open ("highscores.txt",ios::app);
		Scr<<score1<<endl;
		Scr.close();
	}
}

void Hurdles(int arrx[65],int arry[65])
{
	
	int count=0;
	int temp2;
	
	bool flag=true;
	
	current_time1=time(NULL);
	if(current_time1-earlier_time1==10)
	{
		while(flag)
		{
			x11=0,x22=1;
			while(x11!=x22)
			{
				x11=(rand()%65);
				x22=(rand()%65) ;
			
			y11=(rand()%65);
			y22=(rand()%65);
			}
			x11=(x11)*10;
			x22=(x22)*10;
			y11=(y11)*10;
			y22=(y22)*10;
	
				
			for(int k=0;k<5;k++)
			{
				if(valuex[k]!=x11 && valuey[k]!=y11 && valuey[k]!=y22)
				{
					
					count++;
					
				}
			}
			if(count==5)
			flag=false;
			else 
			count=0;
		}
	earlier_time1=time(NULL);	
	}
	if(y11>y22)
	{
		temp2=y11;
		y11=y22;
		y22=temp2;
	}
	
	
	DrawLine(x11+6,y11,x22+6,y22,10,colors[5]);
	arrx[x11/10]=2;
	for(int y=y11;y<y22;y+=10)
	{
		arry[y11/10]=2;
		arry[y22/10]=2;
		arry[y/10]=2;
		if (((starty==y)||(starty==y11)||(starty==y22)) && (startx==x11))
		{
			hit=1;
		 	
		}
	}
	
	
}
void Hurdles2(int arrx[65],int arry[65])
{
	
	int count=0,temp;
	bool flag=true;
	
	current_time3=time(NULL);
	if(current_time3-earlier_time3==10)
	{
		while(flag)
		{
			y111=0,y222=1;
		
			while(y111!=y222)
			{
				y111=(rand()%65) ;
				y222=(rand()%65);
			
			x111=(rand()%65) ;
			x222=(rand()%65) ;
			}
			x111=(x111)*10;
			x222=(x222)*10;
			y111=(y111)*10;
			y222=(y222)*10;
	
			for(int k=0;k<5;k++)
			{
				if(valuex[k]!=x111 && valuex[k]!=x222 && valuey[k]!=y111)
				{
					
					count++;
				}
			}
			if(count==5)
			flag=false;
			else
			count=0;
		}
	
	earlier_time3=time(0);
	}
	
	if(x111>x222)
	{	
		temp=x111;
		x111=x222;
		x222=temp;
		
	}
	if(score1>30)
	{
		SBL=2;
	DrawLine(x111,y111,x222,y222,10,colors[5]);
	
	arry[y111/10]=2;
	
	for(int x=x111;x<x222;x+=10)
	{
		arrx[x111/10]=2;
		arrx[x222/10]=2;
		arrx[x/10]=2;
		
		if (((startx==x)||(startx==x111)||(startx==x222)) && (starty==y111))
		{
			hit=1;
		}
	}
	}//if score
	
}
void Hurdles3(int arrx[65],int arry[65])
{
	int count=0,temp;
	bool flag=true;
	
	current_time5=time(NULL);
	if(current_time5-earlier_time5==10)
	{
		while(flag)
		{
			y1111=0,y2222=1;
		
			while(y1111!=y2222)
			{
				y1111=(rand()%65) ;
				y2222=(rand()%65);
			
			x1111=(rand()%65) ;
			x2222=(rand()%65) ;
			}
			x1111=(x1111)*10;
			x2222=(x2222)*10;
			y1111=(y1111)*10;
			y2222=(y2222)*10;
	
	
			for(int k=0;k<5;k++)
			{
				if(valuex[k]!=x1111 && valuex[k]!=x2222 && valuey[k]!=y1111 && valuex[k]!=y1111 && valuey[k]!=x1111 && valuey[k]!=x2222)
				{
					
					count++;
				}
			}
			if(count==5)
			flag=false;
			else
			count=0;
		}
	
	earlier_time5=time(0);
	}
	
	if(x1111>x2222)
	{	
		temp=x1111;
		x1111=x2222;
		x2222=temp;
	
	}
	vertx1=x1111;
	verty1=y1111;
	vertx2=x1111;
	verty2=x2222;
	if(verty1>verty2)
	{
		temp=verty1;
		verty1=verty2;
		verty2=temp;
	}
	
	if(score1>60)
	{
		SBL=3;
		DrawLine(x1111,y1111,x2222,y2222,10,colors[5]);
	
		DrawLine(vertx1,verty1,vertx2,verty2,10,colors[5]);
	
		arry[y1111/10]=2;
	
		for(int x=x1111;x<x2222;x+=10)
		{
			arrx[x1111/10]=2;
			arrx[x2222/10]=2;
			arrx[x/10]=2;
		
			if (((startx==x)||(startx==x1111)||(startx==x2222)) && (starty==y1111))
			{
				hit=1;
			}
		}
		arrx[vertx1/10]=2;
		for(int y=verty1;y<verty2;y+=10)
		{
			arry[verty1/10]=2;
			arry[verty2/10]=2;
			arry[y/10]=2;
			
			if (((starty==y)||(starty==verty1)||(starty==verty2)) && (startx==vertx1))
			{
				hit=1;
			}
		}
	
	}//if score
	
}




void Food(int arrx[65],int arry[65])
{
	
	int count1=0,count2=0,count3=0,count4=0,x,y;
	bool flag=true;
	
	
	current_time=time(0);
	if(current_time-earlier_time==15)
	{
		for(int a=0;a<5;a++)
		{
			valuex[a]=(rand()%60) *10;
			valuey[a]=(rand()%60) *10;
			
		}	
		while(flag)
		{
			//Limitations
      			for (int k=0;k<5;k++)
        		{
                		for (int l=0;l<5;l++)
                		{
                			if(k!=l)
                			{
                			        if (valuex[k]==valuex[l])
                			        {
                			                count1++;
                			                valuex[k]=(rand()%60) *10;
                			                if(valuex[k]!=valuex[l])
                			                count1=0;
                			        }
                			        if (valuey[k]==valuey[l])
                			        {
                			                count2++;
                			                valuey[k]=(rand()%60)*10;
                			                 if(valuey[k]!=valuey[l])
                			                count2=0;
                			        }
                		     	}
                		}
        		}
        		for(int y=0;y<5;y++)
        		{
        			for(int z=0;z<5;z++)
        			{
        				if(y!=z)
        				{
        					if (valuey[y]==valuex[z])
                	       			{
                	        	      		count3++;
                	        	      		valuex[y]=(rand()%60) *10;
                	        	      		if (valuey[y]!=valuex[z])
                	        	      		count3=0;
                				}
                				if(valuex[y]+valuey[z]==650)
                				{
                					count4++;
                					valuex[y]=(rand()%60)*10;
                					if (valuey[y]+valuex[z]!=650)
                					count4=0;
                				
                				}
        				}
        			}
        		}
        		 
        		if(count1==0 && count2==0 && count3==0 && count4==0)
			flag=false;
		}
		
		earlier_time=time(0);
	}	
		
			
	
	
	for(int i=0;i<5;i++)
	{
		arrx[valuex[i]/10]=1;
		arry[valuey[i]/10]=1;
	}
	
	
	
	for(int j=0;j<5;j++)
	{
		if(arrx[valuex[j]/10]==1 && arry[valuey[j]/10]==1)
		{
			
			x=valuex[j];
			y=valuey[j];
			DrawSquare(x,y,10,colors[6]);
			
		}
		

	}
	
	for(int k=0;k<5;k++)
	{
		if(valuex[k]==startx && valuey[k]==starty)
		{
			arrx[valuex[k]/10]=0;
			arry[valuey[k]/10]=0;
			x=valuex[k];
			y=valuey[k];
			
			DrawSquare(x,y,10,colors[81]);
			
			valuex[k]=(rand()%60) *10;
			valuey[k]=(rand()%60)*10; 
			flag=true;
		
			current_time2=time(0);
			if(current_time2-earlier_time2==15)
			{
				while(flag)
				{
				//Limitations
	      				for (int k=0;k<5;k++)
	        			{
	                			for (int l=0;l<5;l++)
	                			{
	                			 	if(k!=l)
	                			 	{
	                				        if (valuex[k]==valuex[l])
	                				        {
	                				                count1++;
	                				                valuex[k]=(rand()%60) *10;
	                				                if(valuex[k]!=valuex[l])
	                				                count1=0;
	                				        }
	                				        if (valuey[k]==valuey[l])
	                				        {
	                				                count2++;
	                				                valuey[k]=(rand()%60)*10;
	                				                 if(valuey[k]!=valuey[l])
	                				                count2=0;
	                				        }
	                			     
	                				}
	        				}
	        			}
	        			for(int y=0;y<5;y++)
	        			{
	        				for(int z=0;z<5;z++)
	        				{
	        					if(y!=z)
	        					{
	        						if (valuey[y]==valuex[z])
	                		       			{
	                		              			count3++;
	                		              			valuex[y]=(rand()%60) *10;
	                		              			if (valuey[y]!=valuex[z])
	                		              			count3=0;
	                					}
	                					if(valuex[y]+valuey[z]==650)
	                					{
	                						count4++;
	                						valuex[y]=(rand()%60)*10;
	                						if (valuey[y]+valuex[z]!=650)
	                						count4=0;
	                					
	                					}
	        					}
	        				}
	        			}
	        			if(count1==0 && count2==0 && count3==0 && count4==0)
					flag=false;
				}
				earlier_time2=time(0);
			}
			
				eaten++;
				bar++;
				score1+=10;
				if (score1>maxscore)
				maxscore=score1;
		}
	}
		
			
}
void PowerFood(int arrx[65],int arry[65])
{

	
	
	int count1=0,count2=0,count3=0,count4=0,x,y;
	bool flag=true;
	
	
	current_time4=time(NULL);
	if(current_time4-earlier_time4==20)
	{
		
		 pfoodx=(rand()%60) *10;
		 pfoody=rand()%60 *10;
		while(flag)
		{
			//Limitations
    	  		for (int k=0;k<5;k++)
        		{ 
        			 if (pfoodx==valuex[k])
        	        	 {
        	                     count1++;
        	                     pfoodx=(rand()%60) *10;
        	        	     if(pfoodx!=valuex[k])
        	                     count1=0;
        	        	 }
        	        	if (pfoody==valuey[k])
        	        	 {
       	 	                      count2++;
       			              pfoody=(rand()%60)*10;
        	        		if(pfoody!=valuey[k])
        	        	         count2=0;
        	        	 }
        	        		     
        	          }
        			 
        		for(int z=0;z<5;z++)
        		{
        			if (pfoody==valuex[z])
        	      		{
        	        	      	count3++;
        	          		pfoody=(rand()%60) *10;
        	               		if (pfoody!=valuex[z])
        	            		count3=0;
        	        	}
        	        	if(pfoodx+valuey[z]==650)
        	        	{
        	        		count4++;
        	        		pfoodx=(rand()%60)*10;
        	        		if (pfoodx+valuex[z]!=650)
        	      			count4=0;
        	        				
        	        	}
        		}
        			
        		if(count1==0 && count2==0 && count3==0 && count4==0)
			flag=false;
		}
		
		earlier_time4=time(NULL);
	}	
		
		
	
	
	for(int i=0;i<5;i++)
	{
		arrx[pfoodx/10]=1;
		arry[pfoody/10]=1;
	}
	
	
		if(arrx[pfoodx/10]==1 && arry[pfoody/10]==1)
		{
			
			x=pfoodx;
			y=pfoody;
			DrawSquare(x,y,10,colors[130]);
			
		}
	
	
	
		if(pfoodx==startx && pfoody==starty)
		{
			arrx[pfoodx/10]=0;
			arry[pfoody/10]=0;
			x=pfoodx;
			y=pfoody;
			
			DrawSquare(x,y,10,colors[81]);
			pfoodx=-5,pfoody=-5;
					
			eaten++;
			bar++;
			score1+=20;
			int score2=0;
			score2+=20;
			if(score1>maxscore)
			maxscore=score1;
		
		}
	
	
	
	
}
string int2string(int num)
{
    ostringstream str1; 
    str1 << num; 
    return str1.str(); 
    
}
void Scores(int score1)
{
	
	DrawString(10,630,"Score: "+ int2string(score1) ,colors[13]);
	
	
}
void Level (int SBL)
{
	DrawString(200,630,"Level: "+int2string(SBL),colors[13]);
}
void SnakeBar()
{
	int x_val=420,y_val=630;
	DrawString(320,630,"Snake : ",colors[13]);
	DrawLine(420,638,600,638,10,colors[124]);
	DrawLine(420,633,600,633,10,colors[124]);
	
	
	if (score1<=150)
	{
		bar=eaten;
		for(int a=0;a<bar;a++)
		{
			DrawSquare(x_val,y_val,11,colors[13]);
			x_val+=10;
			x_val+=score2;
			score2=0;		
		}
	
	
		xyz=eaten;
	}
	else if(score1>150 && score1<=250)
	{
		x_val=420;
		bar2=xyz;
		for(int a=0;a<bar2;a++)
		{
			DrawSquare(x_val,y_val,11,colors[13]);
			x_val+=10;
			x_val+=score2;
			score2=0;		
		}
	}
	
	if(score1>250)
	{
		x_val=420;
		bar3=xyz;
		for(int a=0;a<bar3;a++)
		{
			DrawSquare(x_val,y_val,11,colors[13]);
			x_val+=10;
			x_val+=score2;
			score2=0;		
		}
	}
}

void Collisions(int snakex[100],int snakey[100],int startx,int starty)
{
	for (int a=0;a<eaten;a++)
	{
		if(snakex[a]==startx and snakey[a]==starty)
		{
			hit=1;
		}
	}
}

void Display(){

    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    

    	
    	BG();
	Border();
	//Menu();
	
//if(choice==1)
//{
	int tempx,tempy;
	counterX=snakex[0];
	counterY=snakey[0];
	
	snakex[0]=startx;
	snakey[0]=starty;

	for(int a=0;a<eaten;a++)
	{
		tempx=snakex[a];
		tempy=snakey[a];
		snakey[a]=counterY;
		snakex[a]=counterX;
		counterX=tempx;
		counterY=tempy;
		
		DrawSquares(counterX,counterY,startx,starty);
	}
		
		switch(newPosn)
		{
			case 0:
				if(PrevPosn==1)
				{
					PrevPosn=1;
					startx+=10;
					break;
				}
				else
				{
					PrevPosn=newPosn;
					startx-=10;
					
				}
				break;
		
			case 1:
				if (PrevPosn==0)
				{
					PrevPosn=0;
					startx-=10;
					break;
				}
				else 
				{
					PrevPosn=newPosn;
					startx+=10;	
				}
				break;
					
			case 2:
				if(PrevPosn==3)
				{	
					PrevPosn=3;
					starty-=10;
					break;
				}
				else
				{
					PrevPosn=newPosn;
					starty+=10;	
				}
				break;
					
			case 3:
				if(PrevPosn==2)
				{
					PrevPosn=2;
					starty+=10;
					break;
				}
				else
				{
					PrevPosn=newPosn;
					starty-=10;
						
				}	
				break;	
		}
		    	
    	
    	DrawCircle(startx+5,starty+5,5,colors[67]);
	Collisions(snakex,snakey,startx,starty); 
	
	Food(arrx,arry);
	PowerFood(arrx,arry);
	
	Level(SBL);
	SnakeBar();
	
		Hurdles(arrx,arry);
		Hurdles2(arrx,arry);
		Hurdles3(arrx,arry);
	
	
	
	if(hit==1)
	{
		
		HighScores(maxscore);
		DrawString(300,360,"GAME OVER",colors[13]);
		//if(maxscore>score1)
		//DrawString(300,330, int2string(maxscore) ,colors[13]);
		
		
		//Menu();
		startx=0;
		starty=0;
	}
	    
	Scores(score1);	
    	
    	
	
	if(starty>=650)
	starty=0 ; 
	else if(starty<=0)
	starty=650;
	if (startx>=650)
	startx=0;
	else if(startx<=0)
	startx=650;   
	  
   glutSwapBuffers(); // do not modify this line..
}



void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
											// what to do when left key is pressed...
	newPosn=0;
	
	
      
    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	
	newPosn=1;
	
	
		
    } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
	
	newPosn=2;
	
	
        
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
	
	newPosn=3;
	
	
    }
    

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
    	enter=1;
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

	
// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
	
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("Adil's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);
    

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    
    return 1;
    
    
}
#endif /* Snake Game */

