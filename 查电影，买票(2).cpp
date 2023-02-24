#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <windows.h>
FILE *fp5;
FILE *fp6;
FILE *fp7;
int arr100[10][10] = {0};
int arr150[10][15] = {0};
struct Order //订单
{
int orderNum; //订单号
char userID[20];//用户ID
char movieID[20];//影片编号 
char cinema[20];//电影院
char movie[20];//电影名 
char room[20];//影厅
char row[20];//行号 
char line[20];//列号 
char beginTime[20];//开场时间 
char endTime[20];//散场时间
char type[20];//影片类型 
char language[20];//语言
float ratio;//上座率 
int restticket;//余票数
int totalticket;//总票数
float fee;//票价
};


struct U_Message //用户信息
{
char ID[20]; //用户ID
char Name[20]; //用户名字
char Sex[10]; //用户性别 
char Tele[20]; //用户电话 
char Code[20]; //用户密码
double Money; //用户账户余额（初始为0）
char Mail[50]; //用户邮箱
};
struct U_Message U_quanju;//定义一个全局用户信息变量 

struct MovieMessage//电影场次信息
{ 
 char cinema[20];//电影院 
 char movieID[20];//影片编号 
 char moviename[20];//影片名 
 char room[20];//厅号 
 char beginTime[20];//开场时间 
 char endTime[20];//散场时间
 char type[20];//影片类型 
 char language[20];//语言 
 int restticket;//余票数
 int totalticket;//总票数
 float ratio;//上座率 
 float fee;//票价 
};
//输入文本举例
//
int judge_num(char []);//判断输入是否为数字 
int rangetime(int);//按照时间排序 
int rangefeein(int);//按票价升序排序 
int rangefeede(int);//按票价降序排序 
int rangerestin(int);//按余票数升序排序 
int rangerestde(int);//按余票数降序排序 
int paixujiemian(int);//影片信息排序界面
void xuanpianchang();//用户选择电影片场
void userQueryMenu();//用户电影查询界面 
int MovieNamequire(int);//用户按照影片名查询影片 
int Languagequire(int);//用户按照语言类型查询影片 
int Doublequire(int);//用户按照影片名+影院名查询影片  
int MovieTypequire(int);//用户按照放映影厅类型查询影片 
int Cinemaquire(int);//用户按照影院名查询影片 
char buy(char []);//用户选择购票界面 
char chazuo100(char []);//用户查询10*10座位 
char chazuo150(char []);//用户查询10*15座位 
void zuoweituijian100();//用户10*10座位推荐
void zuoweituijian150();//用户10*15座位推荐
int maipiao100(int,char []);//用户选择座位购票过程 
int maipiao150(int,char []);//用户选择座位购票过程 

int judge_num(char num[])//判断输入是否为数字 
{
	int flag = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(isdigit(num[i]))  continue;//逐位判断是否为数字### 
		else 
		{
		printf("请您输入数字！\n");
		flag = 1;
		break;
		} 
	} 
	return flag;//返回值为0 则代表输入正确 ###
}

int rangetime(int choice)//按照时间排序 
	{
		struct MovieMessage time_total[500];//声明一个结构的数组 
		int n=0;
		FILE *fp6;
		struct MovieMessage quire;
		system("cls"); 
		char filename[20];
		sprintf(filename, "temp%d.txt",choice);
		fp6=fopen(filename,"r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		while((fscanf(fp6,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{	
			strcpy(time_total[n].movieID,quire.movieID);
			strcpy(time_total[n].cinema,quire.cinema);
			strcpy(time_total[n].moviename,quire.moviename);
			strcpy(time_total[n].room,quire.room);
			strcpy(time_total[n].beginTime,quire.beginTime);
			strcpy(time_total[n].endTime,quire.endTime);
			strcpy(time_total[n].type,quire.type);
			strcpy(time_total[n].language,quire.language);
			time_total[n].restticket=quire.restticket;
			time_total[n].totalticket=quire.totalticket;
			time_total[n].ratio=quire.ratio;
		    time_total[n].fee=quire.fee;
			n++;
		}
        int i;  //按时间从近到远排序 
        int j;
        struct MovieMessage t;    
        for (i=0;i<n-1;i++)  
        {
            for (j=0;j<n-1-i;j++)  
            {
                
                	if(strcmp(time_total[j].beginTime,time_total[j+1].beginTime)<=0)
                	{
						continue;
                	}
             	   	else if(strcmp(time_total[j].beginTime,time_total[j+1].beginTime)>0)
              	   	{
                		t=time_total[j];
                 		time_total[j]=time_total[j+1];
                		time_total[j+1]=t;                      
                	}
     		}                                
		}
       	   	printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
			for(i=0;i<n;i++)
		    {
		     	printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",time_total[i].movieID,time_total[i].cinema,time_total[i].moviename,
			    time_total[i].room,time_total[i].beginTime,time_total[i].endTime,time_total[i].type,time_total[i].language,
			    time_total[i].restticket,
			    time_total[i].totalticket,
			    time_total[i].ratio,time_total[i].fee);
		    }
		   fclose(fp6);
}
int rangefeein(int choice)//按票价升序排序 
{
	    struct MovieMessage fee_total[500];//声明一个结构的数组 
		int n=0;
		FILE *fp6;
		struct MovieMessage quire;
		system("cls");
		char filename[20];
		sprintf(filename, "temp%d.txt",choice); 
		fp6=fopen(filename,"r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
	    while((fscanf(fp6,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
			fee_total[n].fee=quire.fee;
			strcpy(fee_total[n].movieID,quire.movieID);
			strcpy(fee_total[n].cinema,quire.cinema);
			strcpy(fee_total[n].moviename,quire.moviename);
			strcpy(fee_total[n].room,quire.room);
			strcpy(fee_total[n].beginTime,quire.beginTime);
			strcpy(fee_total[n].endTime,quire.endTime);
			strcpy(fee_total[n].type,quire.type);
			strcpy(fee_total[n].language,quire.language);
			fee_total[n].restticket=quire.restticket;
			fee_total[n].totalticket=quire.totalticket;
			fee_total[n].ratio=quire.ratio;
			n++;
		} 
        int i; //升序排序 
        int j;
        struct MovieMessage t;  
        for (i=0;i<n-1;i++)  
        {
            for (j=0;j<n-1-i;j++)  
            {
                if (fee_total[j].fee>fee_total[j+1].fee)
                {
                    t=fee_total[j];
                    fee_total[j]=fee_total[j+1];
                    fee_total[j+1]=t; 
                }
            }
        }
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		for(int i=0;i<n;i++)
		{
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
			    fee_total[i].room,fee_total[i].beginTime,fee_total[i].endTime,fee_total[i].type,fee_total[i].language,
			    fee_total[i].restticket,
			    fee_total[i].totalticket,
			    fee_total[i].ratio,fee_total[i].fee);
		}
		fclose(fp6);
		return 0;
}

int rangefeede(int choice)//按票价降序排序 
{
 
	    struct MovieMessage fee_total[500];//声明一个结构的数组 
		int n=0;
		FILE *fp6;
		struct MovieMessage quire;
		system("cls"); 
		char filename[20];
		sprintf(filename, "temp%d.txt",choice); 
		fp6=fopen(filename,"r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
	    while((fscanf(fp6,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
			fee_total[n].fee=quire.fee;
			strcpy(fee_total[n].movieID,quire.movieID);
			strcpy(fee_total[n].cinema,quire.cinema);
			strcpy(fee_total[n].moviename,quire.moviename);
			strcpy(fee_total[n].room,quire.room);
			strcpy(fee_total[n].beginTime,quire.beginTime);
			strcpy(fee_total[n].endTime,quire.endTime);
			strcpy(fee_total[n].type,quire.type);
			strcpy(fee_total[n].language,quire.language);
			fee_total[n].restticket=quire.restticket;
			fee_total[n].totalticket=quire.totalticket;
			fee_total[n].ratio=quire.ratio;
			n++;
		} 
        int i; //降序排序 
        int j;
        struct MovieMessage t;  
        for (i=0;i<n-1;i++)  
        {
            for (j=0;j<n-1-i;j++)  
            {
                if (fee_total[j].fee<fee_total[j+1].fee)
                {
                    t=fee_total[j];
                    fee_total[j]=fee_total[j+1];
                    fee_total[j+1]=t; 
                }
            }
        }
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		for(int i=0;i<n;i++)
		{
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
			    fee_total[i].room,fee_total[i].beginTime,fee_total[i].endTime,fee_total[i].type,fee_total[i].language,
			    fee_total[i].restticket,
			    fee_total[i].totalticket,
			    fee_total[i].ratio,fee_total[i].fee);
		}
		fclose(fp6);
		return 0;
     
}
int rangerestin(int choice)//按余票数升序排序 
{
	    struct MovieMessage rest_total[500];//声明一个结构的数组 
		int n=0;
		FILE *fp6;
		struct MovieMessage quire;
		system("cls"); 
		char filename[20];
		sprintf(filename, "temp%d.txt",choice); 
		fp6=fopen(filename,"r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
	    while((fscanf(fp6,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
			rest_total[n].fee=quire.fee;
			strcpy(rest_total[n].movieID,quire.movieID);
			strcpy(rest_total[n].cinema,quire.cinema);
			strcpy(rest_total[n].moviename,quire.moviename);
			strcpy(rest_total[n].room,quire.room);
			strcpy(rest_total[n].beginTime,quire.beginTime);
			strcpy(rest_total[n].endTime,quire.endTime);
			strcpy(rest_total[n].type,quire.type);
			strcpy(rest_total[n].language,quire.language);
			rest_total[n].restticket=quire.restticket;
			rest_total[n].totalticket=quire.totalticket;
			rest_total[n].ratio=quire.ratio;
			n++;
		} 
        int i; //升序排序 
        int j;
        struct MovieMessage t;  
        for (i=0;i<n-1;i++)  
        {
            for (j=0;j<n-1-i;j++)  
            {
                if (rest_total[j].restticket>rest_total[j+1].restticket)
                {
                    t=rest_total[j];
                    rest_total[j]=rest_total[j+1];
                    rest_total[j+1]=t; 
                }
            }
        }
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n"); 
		for(int i=0;i<n;i++)
		{
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
			rest_total[i].room,rest_total[i].beginTime,rest_total[i].endTime,rest_total[i].type,rest_total[i].language,
			rest_total[i].restticket,
			rest_total[i].totalticket,
			rest_total[i].ratio,rest_total[i].fee);
		}
		fclose(fp6);
		return 0;
     
}
int rangerestde(int choice)//按余票数降序排序 
{
	    struct MovieMessage rest_total[500];//声明一个结构的数组 
		int n=0;
		FILE *fp6;
		struct MovieMessage quire;
		system("cls");
		char filename[20];
		sprintf(filename, "temp%d.txt",choice); 
		fp6=fopen(filename,"r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
	    while((fscanf(fp6,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
			rest_total[n].fee=quire.fee;
			strcpy(rest_total[n].movieID,quire.movieID);
			strcpy(rest_total[n].cinema,quire.cinema);
			strcpy(rest_total[n].moviename,quire.moviename);
			strcpy(rest_total[n].room,quire.room);
			strcpy(rest_total[n].beginTime,quire.beginTime);
			strcpy(rest_total[n].endTime,quire.endTime);
			strcpy(rest_total[n].type,quire.type);
			strcpy(rest_total[n].language,quire.language);
			rest_total[n].restticket=quire.restticket;
			rest_total[n].totalticket=quire.totalticket;
			rest_total[n].ratio=quire.ratio;
			n++;
		} 
        int i; //降序排序 
        int j;
        struct MovieMessage t;  
        for (i=0;i<n-1;i++)  
        {
            for (j=0;j<n-1-i;j++)  
            {
                if (rest_total[j].restticket<rest_total[j+1].restticket)
                {
                    t=rest_total[j];
                    rest_total[j]=rest_total[j+1];
                    rest_total[j+1]=t; 
                }
            }
        }
 
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n"); 
		for(int i=0;i<n;i++)
		{
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
   			rest_total[i].room,rest_total[i].beginTime,rest_total[i].endTime,rest_total[i].type,rest_total[i].language,
			rest_total[i].restticket,
			rest_total[i].totalticket,
			rest_total[i].ratio,rest_total[i].fee);
		}
		fclose(fp6);
		return 0;
     
}

int paixujiemian(int choice)//电影信息排序界面
{
	int op=0;
    int f=1;
        printf("\t\t\t***********************************\n");
        printf("\t\t\t*                                 *\n");
        printf("\t\t\t*       请选择您想要的排序：      *\n");
        printf("\t\t\t*                                 *\n");
        printf("\t\t\t*       1.按开场时间升序          *\n");
        printf("\t\t\t*                                 *\n");   
		printf("\t\t\t*       2.按票价升序              *\n");   
		printf("\t\t\t*                                 *\n"); 
		printf("\t\t\t*       3.按票价降序              *\n");   
        printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       4.按余票数升序            *\n");   	
		printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       5.按余票数降序            *\n");   	
		printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       6.返回                    *\n"); 
		printf("\t\t\t*                                 *\n");   				       
        printf("\t\t\t***********************************\n");
        printf("\t\t\t请选择:(1,2,3,4,5,6) \n");
	while(f)
	{        
		fflush(stdin);
        scanf("%d",&op);
        getchar();
        switch(op)
		{
			case 1: rangetime(choice);
					xuanpianchang();
					break;
			case 2: rangefeein(choice);
					xuanpianchang();
					break;
			case 3: rangefeede(choice);
					xuanpianchang();
					break;
			case 4: rangerestin(choice);
					xuanpianchang();
					break;
			case 5: rangerestde(choice);
					xuanpianchang();
					break;
			case 6: f=0;
					break;
			default:f=0; 
					break;							
		}
    }
}

void xuanpianchang()//用户选片场
{
	FILE *fp1;
	char movieID[5];
	struct Order A_kan;	
	int count_[5]={0};
	int f=1;	
 	printf("\n\n");
	printf("\t\t**************************************************\n");
	printf("\t\t*                                                *\n");
	printf("\t\t*       请选择您想观看的片场（输入影片编号）     *\n");
	printf("\t\t*                                                *\n");        
	printf("\t\t*       温馨提示：购买午夜场可以半价优惠呦!      *\n");        
	printf("\t\t*                                                *\n");        
 	printf("\t\t**************************************************\n");
  	scanf("%s",movieID);
  	fp1=fopen("OrderMessage.txt","r");
 /* 	while(f)
  	{
  		while(fscanf(fp1,"%s  %s  %d  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_kan.orderNum,
		A_kan.userID,movieID,A_kan.cinema,A_kan.movie,A_kan.room,A_kan.row,A_kan.line,
		A_kan.beginTime,A_kan.endTime,A_kan.type,A_kan.language,&A_kan.ratio,
		&A_kan.restticket,&A_kan.totalticket,&A_kan.fee)!=EOF)
		if (strcmp(U_quanju.ID,A_kan.userID)==0)
		{
			if(count_[0]==0){
				count_[0] = atoi(movieID);
			}else if(count_[0]!=atoi(movieID)&&count_[1]==0){
				count_[1] = atoi(movieID);
			}else if(count_[0]!=atoi(movieID)&&count_[1]!=atoi(movieID)&&count_[2]==0){
				count_[2] = atoi(movieID);
			}else if(count_[0]!=atoi(movieID)&&count_[1]!=atoi(movieID)&&count_[2]!=atoi(movieID)&&count_[3]==0){
				count_[3] = atoi(movieID);
			}else if(count_[0]!=atoi(movieID)&&count_[1]!=atoi(movieID)&&count_[2]!=atoi(movieID)&&count_[3]!=atoi(movieID)&&count_[4]==0){
				count_[4] = atoi(movieID);
			}else if(count_[0]!=atoi(movieID)&&count_[1]!=atoi(movieID)&&count_[2]!=atoi(movieID)&&count_[3]!=atoi(movieID)&&count_[4]!=atoi(movieID)&&count_[5]==0){
				count_[5] = atoi(movieID);
			}else{
				printf("您今天已购买了5个场次的门票，已不能再选择别的场次！\n");
				printf("请选择您想要观看的片场（输入影片编号）：");
				scanf("%s",movieID);
				f=1;
			}
		}
  	}
  	fclose(fp1);
  	fp1=fopen("OrderMessage.txt","r");
	while(fscanf(fp1,"%s  %s  %d  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_kan.orderNum,
	A_kan.userID,movieID,A_kan.cinema,A_kan.movie,A_kan.room,A_kan.row,A_kan.line,
	A_kan.beginTime,A_kan.endTime,A_kan.type,A_kan.language,&A_kan.ratio,
	&A_kan.restticket,&A_kan.totalticket,&A_kan.fee)!=EOF)
	if (strcmp(U_quanju.ID,A_kan.userID)==0 && strcmp(movieID,A_kan.movieID))
  	printf("您已购买过该场次的影票\n");
  	system("pause");
  	fclose(fp1);*/
 	buy(movieID);
} 

void userQueryMenu()//顾客电影查询界面 
{
	int f=1;
	while(f)
	{	
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("") ;
		printf("\t\t\t\t1. 按影片名查询\n\n");
		printf("\t\t\t\t2. 按影片名+影院名查询\n\n");
		printf("\t\t\t\t3. 按语言类型查询\n\n");
		printf("\t\t\t\t4. 按放映影厅类型查询\n\n");
		printf("\t\t\t\t5. 按电影院查询\n\n");
		printf("\t\t\t\t6. 返回\n\n"); 
		printf("\t\t\t请选择您的查询方式：");
		int choice;
		//choice=isValidChoice(5);
		fflush(stdin);
        scanf("%d",&choice);
        getchar();
		switch(choice)
		{//f=0待定 
			case 1:
				MovieNamequire(choice);
				break;
			case 2:
				Doublequire(choice);
				break;
			case 3:
				Languagequire(choice);
				break;
			case 4:
				MovieTypequire(choice);
				break;
			case 5:
				Cinemaquire(choice);
				break;
			case 6:
				f=0;
				break;
			default:
				break;
		}
	}
}

int MovieNamequire(int choice)//按照影片名查询 
 
{
	FILE *fp6;
	FILE *temp1;
	struct MovieMessage quire; 
	char typeinmoviename[10]; 
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *              1.影片名查询                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片名：");
		scanf("%s",typeinmoviename);
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n"); 
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp1=fopen("temp1.txt","w");
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
	    if(strcmp(typeinmoviename,quire.moviename)==0)
			{
			fprintf(temp1,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%g\t%g\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);

			i++;
			}
		}
		fclose(temp1);		
	  	rewind(fp6);	  	
		fclose(fp6);
		system("pause");
		paixujiemian(choice);		
}

int Languagequire(int choice)//按照影片语言类型查询 

{
	FILE *fp6;
	FILE *temp3;
	struct MovieMessage quire; 
	char typeinlanguage[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *               3.语言查询                 *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片语言类型：");
		scanf("%s",typeinlanguage);
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp3=fopen("temp3.txt","w");
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(typeinlanguage,quire.language)==0)
			{
			fprintf(temp3,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			i++;
			}
	  	rewind(fp6);
		fclose(fp6);
		fclose(temp3);
	 	paixujiemian(choice);
}

int Doublequire(int choice)//按照影片名+影院名查询 
 
{
	FILE *fp6;
	FILE *temp2;
	struct MovieMessage quire; 
	char typeinmoviename[10];
	char typeincinema[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *            2.影片名+影院名查询           *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片名和影院名（用空格隔开）：");
		scanf("%s%s",typeinmoviename,typeincinema);
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp2=fopen("temp2.txt","w");
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(typeinmoviename,quire.moviename)==0&&strcmp(typeincinema,quire.cinema)==0)
			{
			fprintf(temp2,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			i++;
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp2);		
	 	paixujiemian(choice);
}

int MovieTypequire(int choice)//按照放映影厅类型查询 
 
{
	FILE *fp6;
	FILE *temp4;
	struct MovieMessage quire; 
	char typeinmovietype[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *            4.放映影厅类型查询            *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的放映影厅类型");
		scanf("%s",typeinmovietype);
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp4=fopen("temp4.txt","w");		
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(typeinmovietype,quire.type)==0)
			{
		fprintf(temp4,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			i++;
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp4);		
	 	paixujiemian(choice);
}

int Cinemaquire(int choice)//按照影院名查询 
 
{
	FILE *fp6;
	FILE *temp5;
	struct MovieMessage quire; 
	char typeincinema[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *              5.电影院查询                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("Please type in the cinema you are interested in:");
		scanf("%s",typeincinema);
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp5=fopen("temp5.txt","w");	
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(typeincinema,quire.cinema)==0)
			{
		fprintf(temp5,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %s     %s    %s  %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			i++;
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp5);		
	 	paixujiemian(choice);
}

char buy(char movieID[])//选择购票界面 
{	
	struct MovieMessage quire;
	int op=0;
	int judge;
	int i;
    int f=1;
    while(f)
    {
        system("cls");
        printf("***********************************\n");
        printf("*                                 *\n");
        printf("*            1. 购 票             *\n");
        printf("*                                 *\n");
        printf("*            2. 返 回             *\n");
        printf("*                                 *\n");        
        printf("***********************************\n");
        printf("请选择:(1,2) \n");
        fflush(stdin);
        scanf("%d",&op);
        getchar();
        fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		printf("The file was not successfully opened.\n");
		exit(1);
		}
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(movieID,quire.movieID)==0)
		{
			if(quire.totalticket==100)
			judge=100;
			else
			judge=150;
			i++;
		}
	  	rewind(fp6);
		fclose(fp6);
        switch(op)
		{
			case 1:	if(judge==100)
					chazuo100(movieID);
					else
					chazuo150(movieID);
					break;
			case 2: //title();
					//返回 
					break;
			default: break;							
		}
        
    }
}

char chazuo100(char movieID[])//查询10*10座位 
{
	system("cls");
	int i,j;
	int goupiao;	
	char seat[20];
	sprintf(seat, "%s.txt", movieID);
	if((fp5 = fopen(seat,"r")) == NULL)
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");
	for(i=0;i<10;i++)
   	{	
  		for(j=0;j<10;j++)
    	{
    	fscanf(fp5,"%d",&arr100[i][j]);
        }
    fscanf(fp5,"\n");
 	}
  	fclose(fp5);
	fp5=fopen(seat,"w");
 	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
		fprintf(fp5,"%d ",arr100[i][j]);
		}
		fprintf(fp5,"\n");}
	fclose(fp5);
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
		printf("[%d] ",arr100[i][j]);
		}
	printf("\n");
	}
	printf("\n（若想取消购票，请输入0）");
	printf("\n请问您需要买的票数是:");
 	scanf("%d",&goupiao);
 	maipiao100(goupiao,movieID);
}

char chazuo150(char movieID[])//查询10*15座位 
{
	system("cls");
	int i,j;
	int goupiao;	
	char seat[20];
	sprintf(seat, "%s.txt", movieID);
	if((fp5 = fopen(seat,"r")) == NULL)
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");
	for(i=0;i<10;i++)
   	{	
  		for(j=0;j<15;j++)
    	{
    	fscanf(fp5,"%d",&arr150[i][j]);
        }
    fscanf(fp5,"\n");
 	}
  	fclose(fp5);
	fp5=fopen(seat,"w");
 	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
		fprintf(fp5,"%d ",arr150[i][j]);
		}
		fprintf(fp5,"\n");}
	fclose(fp5);
	for(i=0;i<10;i++)
	{
		for(j=0;j<15;j++)
		{
		printf("[%d] ",arr150[i][j]);
		}
	printf("\n");
	}
	printf("\n（若想取消购票，请输入0）");
	printf("\n请问您需要买的票数是:");
 	scanf("%d",&goupiao);
 	maipiao150(goupiao,movieID);
}

void zuoweituijian100()//10*10座位推荐
{
	int L=0;
	int I=0;
	int J=0;
	int i,j,k;
	int brr100[10][10]={0};
	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	brr100[i][j]=arr100[i][j];
	 
	for (k=0; k<10; k++) {      //找出10个最佳的座位
    	int max=100;
    	for (i=0; i<10; i++) {      //遍历行
    		for (j=0; j<10; j++) {  //遍历列
        		if (brr100[i][j]!=1) {
        			L = (i-4)*(i-4)+(j-4)*(j-4);       //计算座位据最佳座位的距离
                	if (max > L) {
                    	max = L;
                		I = i;
                		J = j;
            		}
         		}
      		}
   		}
   		brr100[I][J]=1;        //选中的座位被标记为*
      printf("推荐座位是:%d排，%d号\n",I+1,J+1);
	}
} 

void zuoweituijian150()//座位推荐
{
	int L=0;
	int I=0;
	int J=0;
	int i,j,k;
	int brr150[10][15]={0};
	for(i=0;i<10;i++)
	for(j=0;j<15;j++)
	brr150[i][j]=arr150[i][j];
	 
	for (k=0; k<10; k++) {      //找出10个最佳的座位
    	int max=150;
    	for (i=0; i<10; i++) {      //遍历行
    		for (j=0; j<15; j++) {  //遍历列
        		if (brr150[i][j]!=1) {
        			L = (i-4)*(i-4)+(j-7)*(j-7);       //计算座位据最佳座位的距离
                	if (max > L) {
                    	max = L;
                		I = i;
                		J = j;
            		}
         		}
      		}
   		}
   		brr150[I][J]=1;        //选中的座位被标记为*
      printf("推荐座位是:%d排，%d号\n",I+1,J+1);
	}
} 
/*
void changemoney() 
{
		struct U_Message user;
		float fee;//float double
		FILE *fp3;
		FILE *fp4;
		fp3=fopen("users.txt","r");
		fp4=fopen("copyusers.txt","w");
		if(fp3==NULL)
		{
 			printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		while(fscanf(fp3,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
		user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
		{
			if(strcmp(user.ID,登陆用户ID)==0)
			{
				user.Money=user.Money-fee;
			}
			fprintf(fp4,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
			user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
			i++;
		}				
		fclose(fp3);
		fclose(fp4);
		fp3=fopen("users.txt","w");
		fp4=fopen("users改余额.txt","r");
		while(fscanf(fp4,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
		user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
		{
			fprintf(fp3,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
			user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
			i++;
		}
}
*/
int maipiao100(int goupiao,char movieID[])//选择座位购票
{	
	
	FILE *fp2;
	int restticket;
	float fee;//float double
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//检查是否选择错误 
	int i,j;
 	int row[4]={0};
    int line[4]={0};
	int row1 =0;
    int line1 =0;
   	
 	fp6=fopen("MovieMessage.txt","r");
	if(fp6==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strcmp(quire.movieID,movieID)==0)
		restticket=quire.restticket;
		i++;
	}
	rewind(fp6);
	fclose(fp6);
	
	if(goupiao==0)
		printf("您选择了取消购票，按ESC键返回\n");
	else
	{
	 	if(restticket >= goupiao)
	    {
	    printf("恭喜您，目前影厅尚有余座\n");
	    }
	    else
	    {
	        printf("售票失败—余票不足!按ESC键返回\n");
	        fflush(stdin);
	        int op=_getche();
			return 0;
	    }
		while(goupiao>3)
		{
		printf("但是您无法一次购买超过三张票，请按ESC键返回");
		fflush(stdin);
	  	int op=_getche();
		return 1;
		}
		
		printf("请问您是否选择座位推荐系统：1.是 2.否");
		int option;
		scanf("%d",&option);
		switch(option)
		{
			case 1: zuoweituijian100();
			default: break;
		}
		
		int goupiao0 = goupiao;
		for(;goupiao > 0;goupiao--)
		{
			printf("请输入行号:");
	   		scanf("%d",&row[goupiao]);
	    	printf("请输入列号:");
	  		scanf("%d",&line[goupiao]);
			while(row[goupiao]<1 || row[goupiao] >10 || line[goupiao]<1 || line[goupiao] >10)
			{
				printf("选作不规范，请重新选择此座位\n");
				printf("请输入行号:");
	            scanf("%d",&row[goupiao]);
	            printf("请输入列号:");
	            scanf("%d",&line[goupiao]);
			}
		}
		goupiao = goupiao0;
	    if(row[1]==row[2] && line[1]==line[2] && row[1]!=0) 
		{
	   		printf("重复选座，按ESC键返回");
  			check=1; 
	    }
		else if(row[1]==row[3] && line[1]==line[3] && row[2]!=0) 
		{
			printf("重复选座，按ESC键返回");
			check=1; 
		}
	 	else if(row[2]==row[3] && line[2]==line[3] && row[3]!=0)		
		{
			printf("重复选座，按ESC键返回");
			check=1;
		}
		for(;goupiao > 0;goupiao--)
		{
			if (arr100[row[goupiao]-1][line[goupiao]-1]==1)
			{
				printf("您选中了已售出的座位，按ESC键返回\n"); 
				check=1;
			}
			else if (arr100[row[goupiao]-1][line[goupiao]-3]==1 && arr100[row[goupiao]-1][line[goupiao]-2]==0)
			{
				printf("不符合选座规范，按ESC键返回\n"); 
	 			check=1;
			}
		 	else if(arr100[row[goupiao]-1][line[goupiao]+1]==1 && arr100[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("不符合选座规范，按ESC键返回\n");
				check=1; 
			}
		}
		if(check == 0) 
		{	
			goupiao = goupiao0;
			for(;goupiao > 0;goupiao--)
			{	
				arr100[row[goupiao]-1][line[goupiao]-1]=1;
				fp5=fopen(seat,"w");
					for(i=0;i<10;i++)
					{
						for(j=0;j<10;j++)
						{
							fprintf(fp5,"%d ",arr100[i][j]);
						}
						fprintf(fp5,"\n");
					}
					fclose(fp5);
					
					fp2=fopen("copyMovieMessage.txt","w");
					fp6=fopen("MovieMessage.txt","r");
					if(fp6==NULL)
					{
					  	printf("The file was not successfully opened.\n");
					 	exit(1);
					}
					while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						if(strcmp(quire.movieID,movieID)==0)
						{
							 quire.restticket--;
							 fee=quire.fee;
						}
						fprintf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					i++;
					}
					fclose(fp6);
					fclose(fp2);
					fp2=fopen("copyMovieMessage.txt","r");
					fp6=fopen("MovieMessage.txt","w");
					while((fscanf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						fprintf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-restticket)/(float)quire.totalticket),quire.fee);
					i++;
					}
					fclose(fp6);
					fclose(fp2);
					fp6=fopen("MovieMessage.txt","r");		
					fp7=fopen("OrderMessage.txt","a");
					while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					if(strcmp(quire.movieID,movieID)==0)
					{
						fprintf(fp7,"d%s",quire.movieID);
						if(row[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d",row[goupiao]);
						if(line[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%s  %s  %s  %s  %s  ",movieID,movieID,quire.cinema,quire.moviename,quire.room);
						if(row[goupiao]<10)//把第一个movieID改成userID 
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",row[goupiao]);
						if(line[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%7s  %s  %s  %s  %5.2f  %d  %d  %.2f\n",quire.beginTime,quire.endTime,quire.type,
						quire.language,((float)(quire.totalticket-restticket)/(float)quire.totalticket),restticket,quire.totalticket,quire.fee);
						i++;
					}
		  			rewind(fp6);
					fclose(fp6);
					fclose(fp7);
			}
			printf("售票成功!按ESC键返回\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
int maipiao150(int goupiao,char movieID[])//选择座位购票
{	
	
	FILE *fp2;
	int restticket;
	float fee;//float double
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//检查是否选择错误 
	int i,j;
 	int row[4]={0};
    int line[4]={0};
	int row1 =0;
    int line1 =0;
   	
 	fp6=fopen("MovieMessage.txt","r");
	if(fp6==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strcmp(quire.movieID,movieID)==0)
		restticket=quire.restticket;
		i++;
	}
	rewind(fp6);
	fclose(fp6);
	
	if(goupiao==0)
		printf("您选择了取消购票，按ESC键返回\n");
	else
	{
	 	if(restticket >= goupiao)
	    {
	    printf("恭喜您，目前影厅尚有余座\n");
	    }
	    else
	    {
	        printf("售票失败—余票不足!按ESC键返回\n");
	        fflush(stdin);
	        int op=_getche();
			return 0;
	    }
		while(goupiao>3)
		{
		printf("但是您无法一次购买超过三张票，请按ESC键返回");
		fflush(stdin);
	  	int op=_getche();
		return 1;
		}
		
		printf("请问您是否选择座位推荐系统：1.是 2.否");
		int option;
		scanf("%d",&option);
		switch(option)
		{
			case 1: zuoweituijian150();
			default: break;
		}
		
		int goupiao0 = goupiao;
		for(;goupiao > 0;goupiao--)
		{
			printf("请输入行号:");
	   		scanf("%d",&row[goupiao]);
	    	printf("请输入列号:");
	  		scanf("%d",&line[goupiao]);
			while(row[goupiao]<1 || row[goupiao] >10 || line[goupiao]<1 || line[goupiao] >10)
			{
				printf("选作不规范，请重新选择此座位\n");
				printf("请输入行号:");
	            scanf("%d",&row[goupiao]);
	            printf("请输入列号:");
	            scanf("%d",&line[goupiao]);
			}
		}
		goupiao = goupiao0;
	    if(row[1]==row[2] && line[1]==line[2] && row[1]!=0) 
		{
	   		printf("重复选座，按ESC键返回");
  			check=1; 
	    }
		else if(row[1]==row[3] && line[1]==line[3] && row[2]!=0) 
		{
			printf("重复选座，按ESC键返回");
			check=1; 
		}
	 	else if(row[2]==row[3] && line[2]==line[3] && row[3]!=0)		
		{
			printf("重复选座，按ESC键返回");
			check=1;
		}
		for(;goupiao > 0;goupiao--)
		{
			if (arr150[row[goupiao]-1][line[goupiao]-1]==1)
			{
				printf("您选中了已售出的座位，按ESC键返回\n"); 
				check=1;
			}
			else if (arr150[row[goupiao]-1][line[goupiao]-3]==1 && arr150[row[goupiao]-1][line[goupiao]-2]==0)
			{
				printf("不符合选座规范，按ESC键返回\n"); 
	 			check=1;
			}
		 	else if(arr150[row[goupiao]-1][line[goupiao]+1]==1 && arr150[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("不符合选座规范，按ESC键返回\n");
				check=1; 
			}
		}
		if(check == 0) 
		{	
			goupiao = goupiao0;
			for(;goupiao > 0;goupiao--)
			{
				arr150[row[goupiao]-1][line[goupiao]-1]=1;
				fp5=fopen(seat,"w");
					for(i=0;i<10;i++)
					{
						for(j=0;j<15;j++)
						{	
							fprintf(fp5,"%d ",arr150[i][j]);
						}
						fprintf(fp5,"\n");
					}
					fclose(fp5);
					
					fp2=fopen("copyMovieMessage.txt","w");
					fp6=fopen("MovieMessage.txt","r");
					if(fp6==NULL)
					{
					  	printf("The file was not successfully opened.\n");
					 	exit(1);
					}
					while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						if(strcmp(quire.movieID,movieID)==0)
						{
							 quire.restticket--;
							 fee=quire.fee;
						}
						fprintf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					i++;
					}
					fclose(fp6);
					fclose(fp2);
					fp2=fopen("copyMovieMessage.txt","r");
					fp6=fopen("MovieMessage.txt","w");
					while((fscanf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						fprintf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-restticket)/(float)quire.totalticket),quire.fee);
					i++;
					}
					fclose(fp6);
					fclose(fp2);
					fp6=fopen("MovieMessage.txt","r");		
					fp7=fopen("OrderMessage.txt","a");
					while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					if(strcmp(quire.movieID,movieID)==0)
					{
						fprintf(fp7,"d%s",quire.movieID);
						if(row[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d",row[goupiao]);
						if(line[goupiao]<15)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%s  %s  %s  %s  %s  ",movieID,movieID,quire.cinema,quire.moviename,quire.room);
						if(row[goupiao]<10)//把第一个movieID改成userID 
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",row[goupiao]);
						if(line[goupiao]<15)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%7s  %s  %s  %s  %5.2f  %d  %d  %.2f\n",quire.beginTime,quire.endTime,quire.type,
						quire.language,((float)(quire.totalticket-restticket)/(float)quire.totalticket),restticket,quire.totalticket,quire.fee);
						i++;
					}
		  			rewind(fp6);
					fclose(fp6);
					fclose(fp7);
			}
			printf("售票成功!按ESC键返回\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
int main()
{	
	system("color f5"); 	
	userQueryMenu();
	return 0;
}
