#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char flag[9][9];
int click[9][9]={0};
char mine[9][9];
int i,j,gameover=0,bomb[9][9],num[9][9];
char c1,c2,c3;
int totalflag=0;

void mineinitialize()
{
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			mine[i][j]='#';
}

void base(int x,int y)
{
	printf("Total Bombs : 9\n");
	printf("Total Flag Inserted : %d\n  ",totalflag);
	for(i=0;i<9;i++)
	{
		printf("%d ",i+1);
	}
	printf("\n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if (j==0)
				printf("%d",i+1);	
			printf(" %c",mine[i][j]);
		}
		printf("\n");
	}
}

void bombinit()
{
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			bomb[i][j]=0;
			
			
	int x,y;
	srand(time(0));
	for(i=0;i<9;i++)
	{
		do{
			x=rand()%9;
			y=rand()%9;
		}while(bomb[x][y]==1);
		bomb[x][y]=1;
	}
	
}

void numinit()
{
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if (bomb[i][j]!=1)
				num[i][j] = bombcheck(i,j);	
}

int bombcheck(int x,int y)
{
	int count=0;
	if (x==0)
	{
		if (y==0)
		{
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x][y+1]==1)
				count++;
			if(bomb[x+1][y+1]==1)
				count++;
		}
		else if(y==8)
		{
			if(bomb[x][y-1]==1)
				count++;
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x+1][y-1]==1)
				count++;
		}
		else
		{
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x][y+1]==1)
				count++;
			if(bomb[x+1][y+1]==1)
				count++;
			if(bomb[x+1][y-1]==1)
				count++;
			if(bomb[x][y-1]==1)
				count++;
		}
	}
	else if(y==0)
	{
		if (x!=0)
		{
			if(bomb[x][y+1]==1)
				count++;
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x-1][y]==1)
				count++;
			if(bomb[x-1][y+1]==1)
				count++;
			if(bomb[x+1][y+1]==1)
				count++;
		}
		else if(x==8)
		{
			if(bomb[x-1][y]==1)
				count++;
			if(bomb[x][y+1]==1)
				count++;
			if(bomb[x-1][y+1]==1)
				count++;
		}
	}
	else if(x==8)
	{
		if(y==8)
		{
			if(bomb[x-1][y]==1)
				count++;
			if(bomb[x][y-1]==1)
				count++;
			if(bomb[x-1][y-1]==1)
				count++;
		}
//		else if(y==0)
//		{
//			if(bomb[x][y+1]==1)
//				count++;
//			if(bomb[x-1][y]==1)
//				count++;
//			if(bomb[x-1][y+1]==1)
//				count++;
//		}
		else
		{
			if(bomb[x-1][y]==1)
				count++;
			if(bomb[x-1][y-1]==1)
				count++;
			if(bomb[x-1][y+1]==1)
				count++;
			if(bomb[x][y+1]==1)
				count++;
			if(bomb[x][y-1]==1)
				count++;
		}
	}
	else if(y==8)
	{
		if(x==0)
		{
			if(bomb[x][y-1]==1)
				count++;
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x+1][y-1]==1)
				count++;
		}
		else
		{
			if(bomb[x][y-1]==1)
				count++;
			if(bomb[x-1][y]==1)
				count++;
			if(bomb[x+1][y]==1)
				count++;
			if(bomb[x-1][y-1]==1)
				count++;
			if(bomb[x+1][y-1]==1)
				count++;
		}
	}
	else
	{
		if(bomb[x][y+1]==1)
			count++;
		if(bomb[x+1][y]==1)
			count++;
		if(bomb[x-1][y]==1)
			count++;
		if(bomb[x-1][y+1]==1)
			count++;
		if(bomb[x+1][y+1]==1)
			count++;
		if(bomb[x][y-1]==1)
			count++;
		if(bomb[x-1][y-1]==1)
			count++;
		if(bomb[x+1][y-1]==1)
			count++;
	}
	return count;
}

void check(int x,int y)
{
	if(click[x][y]==0 && x>=0 && x<=8 && y>=0 && y<=8 && bomb[x][y]!=1)
	{
		if(num[x][y]==0)
		{
			click[x][y]=1;
			mine[x][y]=' ';
			check(x-1,y);	
			check(x-1,y+1);
			check(x,y+1);
			check(x+1,y+1);
			check(x+1,y);
			check(x+1,y-1);
			check(x,y-1);
			check(x-1,y-1);	
		}
		else
		{
			mine[x][y] = num[x][y] + 48;
			click[x][y]=1;
		}
	}
}

int main()
{
	mineinitialize();
	bombinit();
	numinit();
	int x=0,y=0;
	base(x,y);
	while(!gameover)
	{
		scanf("%c ",&c1);
		if (c1=='F')
		{
			totalflag++;
			scanf("%c %c",&c2,&c3);
			x = atoi(&c2);
			y = atoi(&c3);
			if(mine[x-1][y-1]=='F')
			{
//				if (bomb[x-1][y-1]==1)
//					mine[x-1][y-1]='B';
//				else
				totalflag--;
				mine[x-1][y-1]='#';
			}
			else if(mine[x-1][y-1]!='F')
				mine[x-1][y-1]='F';
		}
		else
		{
			scanf("%c",&c2);
			x = atoi(&c1);
			y = atoi(&c2); 
			if (num[x-1][y-1]!=0)
				mine[x-1][y-1]=num[x-1][y-1]+48;
			else 
				mine[x-1][y-1]=' ';
		}
		if (bomb[x-1][y-1]==1 && c1!='F')
		{
			for(i=0;i<9;i++)
				for(j=0;j<9;j++)
					if(bomb[i][j]==1)
						mine[i][j]='B';	
			mine[x-1][y-1]='X';
			gameover=1;
			system("cls");
			base(x,y);
			break;
		}
		if(num[x-1][y-1]==0 && c1!='F')
			check(x-1,y-1);
		system("cls");
		fflush(stdin);
		base(x,y);
	}
	printf("\nGAME OVER");
	return 0;
}

