#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <conio.h>

//************************************定义部分***************************************
//订单
struct Order //订单
{
	char orderNum[20]; //订单号
	char userID[20];//用户ID
	char movieID[20];//场次号 
	char cinema[20];//电影院
	char movie[20];//电影名 
	char room[10];//影厅
	char row[10];//行号 	
	char line[10];//列号
	char beginTime[20];//开场时间 
	char endTime[20];//散场时间
	char type[20];//影片类型
	char language[20];//语言
	float ratio;//上座率 
	int restticket;//余票数
	int totalticket;//总票数
	float fee;//票价
};

//用户信息
struct U_Message
{
	char ID[20]; //用户ID
	char Name[20]; //用户名字
	char Sex[10]; //用户性别 
	char Tele[20]; //用户电话 
	char Code[20]; //用户密码
	double Money; //用户账户余额（初始为0）
	char Mail[50]; //用户邮箱
};

//管理员信息
struct A_Message 
{
	char ID[20]; //管理员ID
	char Name[20]; //管理员名字
	char Cinema[20]; //所属影院 
	char Code[20]; //管理员密码 
	char Mail[50]; //管理员邮箱
};

//电影影厅信息
struct ScreenMessage
{
 	char cinema[20];//电影院
 	char room[20];//厅号 
 	char type[20];//影厅类型  Imax/2D/3D/4D
};

//电影场次信息
struct MovieMessage
{
 	char movieID[20]; //场次编号
 	char cinema[20];//电影院 
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

//全局变量
FILE *fp5;
FILE *fp6;
FILE *fp7;
int arr100[10][10] = {0};
int arr150[10][15] = {0}; 
struct U_Message U_quanju;//定义一个全局用户信息变量 
struct A_Message A_quanju;//定义一个全局管理员信息变量
 
//注册时需要的函数 
void idcheck(int x);//注册并查询ID 
int chachong(char [],int );//ID的查重，保证不会成功注册两个相同的ID 
void codecheck(int x);//密码的查询 
void youxiangcheckA();//管理员邮箱 
void youxiangcheckU();//用户邮箱
void register1();//注册
void denglu();//登陆主界面 
void A_denglu();//管理员登录
void U_denglu();//用户登录

//管理员主函数 
void A_order();//管理员订单管理系统 
int A_screen();//管理员影厅管理系统
void A_screen_check();//管理员影厅查询
int A_screen_add();//管理员影厅添加 
int A_screen_add_valid(int);//管理员影厅添加影厅检查 
int A_session();//管理员场次管理系统
void A_session_check();//管理员场次查询
void A_session_add();//管理员场次添加
int A_session_room_valid(char[]);//判断添加片场厅号是否合法 
int A_session_add_valid(int,int,char[]);//判断添加片场时间是否合法 
void A_session_add_print(char[],char[],char[],char[],char[],char[]);//把增添场次信息打印进文件  
void A_information(char []);//管理员个人信息 
void A_change(char []);//管理员信息更改
void A_order(); //管理员查看订单 
void Cinemaquire();//按照已购票人数未放映升降序
void rangeTotalin();//按总收入已放映升序 
void shengjiang();//按照上座率升降序排列
  
//用户主函数 
void U_information(char []); //用户个人信息 
void U_change(char []);//用户基本信息更改 
void U_movie();//用户搜索电影
void U_order(char []);//用户订单管理
void rangetime(int);//按照时间排序 
void rangefeein(int);//按票价升序排序 
void rangefeede(int);//按票价降序排序 
void rangerestin(int);//按余票数升序排序 
void rangerestde(int);//按余票数降序排序 
void paixujiemian(int);//影片信息排序界面
void xuanpianchang();//用户选择电影片场
void userQueryMenu();//用户电影查询界面 
void MovieNamequire(int);//用户按照影片名查询影片 
void Languagequire(int);//用户按照语言类型查询影片 
void Doublequire(int);//用户按照影片名+影院名查询影片  
void MovieTypequire(int);//用户按照放映影厅类型查询影片 
void Cinemaquire(int);//用户按照影院名查询影片
void MovieRecom();//热门场次推荐 
void buy(char []);//用户选择购票界面 
void chazuo100(char []);//用户查询10*10座位 
void chazuo150(char []);//用户查询10*15座位 
void zuoweituijian100();//用户10*10座位推荐
void zuoweituijian150();//用户10*15座位推荐
int maipiao100(int,char []);//用户选择座位购票过程 
int maipiao150(int,char []);//用户选择座位购票过程

//工具函数 
int judge_num(char num[]);//判断用户输入是否为整数
int judge_kongge(char[]);//判断用户输入是否有空格
void U_modify();//修改用户文件 
void A_modify();//修改管理员文件
void rangeBuynumin();//按已购票人数还未放映升序
void rangeBuynumde();//按已购票人数还未放映降序
void yingtingzongjia();//计算并显示每个影厅的总票价 
void rangeratioin();//按上座率分日期所有已经放映升序 
void rangeratiode();//按上座率分日期所有已经放映降序
int U_valid(char[]);//测试影厅是否存在（存在返回0） 
void showtime();//显示当前时间 

//***************************************主函数*************************************
int main()
{
	system("color f5"); 
	int n;
	char a[20];
	while(1)
	{
		system("cls");
		printf("如果您是新用户, 请您输入 1:\n");
		printf("如果您需要登录, 请您输入 2:\n");
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)
			continue; 
		n = atoi(a);
		if(n!=1&&n!=2)
			continue;
		break;
	} 
	switch (n)
	{
		case 1:
			register1();
			break;//不用break因为注册完需要登录 
 		case 2:
	 		denglu();
	 		break;
	}
	return 0;
} 

//*************************************注册**************************************
void idcheck(int x)//用户、管理员ID的输入以及验证 
{
	int i=0,b=0,b1=0,b2=0,b3=0,j=0,shuzi=0,zimu=0,b4=0;
 	char ID1[20]={'\0'};
	while( b!=1 )//输入并验证ID 
	{
		printf("请输入您的ID:(六到十个字符,必须包含数字与字母)\n");
		scanf("%s",ID1);
         	for (i=0;i<=5;i++)//保证ID够长 
			if (ID1[i]=='\0')
			{
				printf("你的ID不合法，请重新输入！\n");
			 	b1=0;
			 	break;
		 	}
			else 
			b1=1;
          	if (ID1[11]!='\0')
   		{
   			printf("你的ID不合法，请重新输入！\n");
		   	b2=0;
	   	}//保证ID不过长	   
   		else
   		b2=1;
		b3=chachong(ID1,x);//进行ID的查重 
		while (ID1[j]!='\0')//确保ID中必须含有字母和数字 
		{
			if ((ID1[j]<='Z'&&ID1[j]>='A')||(ID1[j]<='z'&&ID1[j]>='a'))
				zimu+=1;	
			if (ID1[j]<='9'&&ID1[j]>='0')
				shuzi+=1;
			j++;
		} 
		if(zimu>0&&shuzi>0)
			b4=1;
		else{
			printf("你的ID不合法!\n");
			b4=0;
		} 
		if(b1==1&&b2==1&&b3==1&&b4==1)
			b=1;//当上述条件均符合要求，则注册成功 
		else
			b=0;
	}
	if (x==1)//将注册成功的ID赋值给全局变量 
		strcpy(A_quanju.ID,ID1);
	else
		strcpy(U_quanju.ID,ID1);
}

void codecheck(int x)//用户、管理员密码的输入及验证 
{
	int i=0,b=0;
	char code1[20]={'\0'},code2[20]={'\0'};
	FILE *AFile,*UFile;
	while ( b!=1 )//输入并验证密码 
 	{
  		printf("请您输入您的密码:(6到10位)\n");
  		scanf("%s",code1);
       	for (i=0;i<=5;i++)//确保密码足够长 
     		if (code1[i]=='\0')
  		{
  			printf("你的密码不合法，请重新输入！\n");
		  	b=0;
		  	break;
  		}
      	else
		b=1;
      	if(code1[11]!='\0')
		{
			printf("你的密码不合法，请重新输入！\n");
			b=0;
		}//确保密码不过长	
		else
			b=1;     
		printf("请确认您的密码：\n");
		scanf("%s",code2);
   		if(strcmp(code1,code2)==0)
			b=1;
		else
			b=0;                    
 	}
 	if (x==1)
	 	strcpy(A_quanju.Code,code1);
	else
		strcpy(U_quanju.Code,code1);
}

void youxiangcheckA()//管理员邮箱验证 
{
	char youxiang[50]={'\0'};
	int i=0,b=0,j=0,check1=0,check2=0,c1=0,c2=0;
	while (b!=1)
	{
		
		printf("请输入您的邮箱：（格式为***@***.***)\n");
		scanf("%s",youxiang);
		while(youxiang[j]!='\0')
		{
			if (youxiang[j]=='@') {c1++; check1=j;}//记录@的位置 
			if (youxiang[j]=='.') {c2++; check2=j;}//记录.的位置 
			if (c1==1&&c2==1)	b=1;	else b=0;//确保必须@和.的存在 
			j++;
		}
		if (check2<=check1+1||check1==1||check2==j-1) b=0;//确保@在.之前且@不在第一位，.不在最后一位 
		if (b==0)	printf("你的邮箱不合法！\n"); 
		else printf("你的邮箱合法！\n");
	}
	strcpy(A_quanju.Mail,youxiang);
}

void youxiangcheckU()//用户邮箱验证 
{
	char youxiang[50]={'\0'};
	int i=0,b=0,j=0,check1=0,check2=0,c1=0,c2=0;
	while (b!=1)
	{
		printf("请输入您的邮箱：（格式为***@***.***)\n");
		scanf("%s",youxiang);
		while (youxiang[j]!='\0')
		{
			if (youxiang[j]=='@') {c1++; check1=j;}//记录@的位置
			if (youxiang[j]=='.') {c2++; check2=j;}//记录.的位置 
			if (c1==1&&c2==1)	b=1;	else b=0;
			j++;
		}
		if (check2<=check1+1||check1==1||check2==j-1) b=0;//确保@在.之前且@不在第一位，.不在最后一位 
		if (b==0)	printf("你的邮箱不合法！\n"); 
		else printf("你的邮箱合法！\n");
	}
	strcpy(U_quanju.Mail,youxiang);
}

void register1()//注册函数 
{
	int i,n,a=0,b=0,zhuce,c=0;
	FILE *AFile,*UFile;
 	printf("如果您是一位管理员，请输入1：\n");
  	printf("如果您是一位用户，请输入2：\n");
   	scanf("%d",&zhuce);
   	switch (zhuce)
    	{  
	case 1: //注册管理员 
	{
		idcheck(zhuce);
		AFile=fopen("administrators.txt","a");
		printf("请输入您的姓名:\n");//输入姓名 
		scanf("%s",A_quanju.Name);
          	printf("请输入您的影院:\n");//输入所属影院 
		scanf("%s",A_quanju.Cinema);
		codecheck(zhuce);
		youxiangcheckA();
		fprintf(AFile,"%s  %s  %s  %s  %s\n",A_quanju.ID,A_quanju.Name,A_quanju.Cinema,A_quanju.Code,A_quanju.Mail);
		fclose(AFile);
		break;
	}
	case 2: //注册用户 
	{
		idcheck(zhuce); 
		UFile=fopen("users.txt","a");
		printf("请输入您的姓名:\n");//输入姓名 
		scanf("%s",U_quanju.Name);
		printf("请输入您的性别:\n");//输入性别 
 		scanf("%s",U_quanju.Sex);
		while ( b!=1 )//输入并验证电话 
		{
			printf("请输入您的电话号码:\n");
			scanf("%s",U_quanju.Tele);
 			if (U_quanju.Tele[11]!='\0') {printf("你的电话号码不合法！请重新输入：\n"); b=0;}//保证电话11位	
   			else b=1;
			for (i=0;i<11;i++)
			if (U_quanju.Tele[i]<'0'||U_quanju.Tele[i]>'9') //保证电话11位均为数字 
			{
				printf("您的电话号码不合法，请重新输入！\n");
				b=0;
				break;
			}                      
     		}
	 	codecheck(zhuce);
		youxiangcheckU();
		fprintf(UFile,"%s  %s  %s  %s  %s  %lf  %s\n\n",U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Code,U_quanju.Money,U_quanju.Mail);
		fclose(UFile);
		break;
	}
	}
 	printf("您已经注册成功啦！请登录：\n");
  	denglu();
}

//*************************************登录**************************************
void denglu()//登录 
{
   	char b[20]={'\0'};
   	system("cls");//清屏 
	printf("如果您是一位管理员，请输入1：\n");
	printf("如果您是一位用户，请输入2：\n");
	while(1){
		fflush(stdin);
		scanf("%s",b);
		if(judge_num(b)!=0)
			continue;
	 	break;
	}
	switch(atoi(b))
	{
		case 1: A_denglu();break;//管理员登陆
		case 2: U_denglu();break;//用户登陆
		default:denglu();		 
	}
}
void A_denglu()//管理员登录 
{
	int repeat = 1;//循环进行操作 
	int b,a=0,c,d,num1,num2;
	double money;
	FILE *AFile,*UFile;
 	char id1[20],id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20],cinema[20];
  	char choice[20];
	printf("请输入您的ID：\n");
	scanf ("%s",id1);
	AFile=fopen("administrators.txt","r");
	rewind(AFile); 
	while(fscanf(AFile,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail)!=EOF||a==1)
	{
		if(strcmp(id1,id2)==0)
		{
			a=1;
			printf("请输入您的密码：\n");
			scanf("%s",code1);
			if(strcmp(code1,code2)==0)
			{
				fclose(AFile);
				//这里把本次用户信息保存在 全 局 变 量 中！ 
				strcpy(A_quanju.ID,id2);
				strcpy(A_quanju.Name,name);
				strcpy(A_quanju.Cinema,cinema);
				strcpy(A_quanju.Code,code2);
				strcpy(A_quanju.Mail,mail);
				//显示用户功能选择提示 
				printf("\n***************************************\n\n");
				printf("亲爱的管理员! 您已成功登录! \n");
				repeat = 1;
				while(repeat == 1){
					printf("如果您想查看订单状况,请输入 1\n");
					printf("如果您想进入影厅系统,请输入 2\n");
					printf("如果您想进行场次管理,请输入 3\n");
					printf("如果您想查看个人信息,请输入 4\n");
					printf("如果您想要退出      ,请输入其他数字\n");
					while(1){
						fflush(stdin);
						scanf("%s",choice);
						if(judge_num(choice)!=0)
							continue;
					 	break;
					}
					switch(atoi(choice))
					{
						case 1:A_order();/*管理员订单管理系统*/
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
					  		break;
						case 2:repeat = A_screen();/*管理员影厅管理系统 */ 
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 3:repeat = A_session();/*管理员场次管理系统*/  
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 4:A_information(A_quanju.ID);/*管理员信息系统*/
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
							break;
						default:
							repeat = 0;//退出
							fflush(stdin); 
							break;
					}
					a = 2;//a=2说明进过switchcase 
				}	
			}
		}
		else
		{
			switch(a)
			{
				case 1:
					printf("输入错误！\n");
					printf("重新登陆请按1：\n");
					printf("找回密码请按2：\n");
					printf("请输入您的选择：");
					scanf("%d",&d);
					if (d==1)	denglu();
					else 
					{
						srand(time(0));
						num1=rand()%(10000-1000)+1000;
						printf("我们已经给您的邮箱发送了验证码\n");
						printf("请输入：\n");
						scanf("%d",num2);
						if(num1==num2)
						{
							printf("您的密码是%s\n",code2);
							printf("请及时更改\n");
							denglu();
						}
					}
					break;
				case 0://如果a=0 说明未找到用户名 
					//printf("*\n");//测试 
					break;
				default: 
					break;
			}
		}
	}
	if(a == 0){
		printf("您的ID不存在\n");
		printf("如果您想重新登录，请输入1：\n");
		printf("如果您想注册，请输入2：\n ");
		while(1){
			fflush(stdin);
			scanf("%s",choice);
			if(judge_num(choice)!=0)
				continue;
			 	break;
		}
		switch(atoi(choice))
		{
			case 1:
				denglu();
				break;
			case 2:
				register1();
				break;
			default:
				break;
		}
	}	
}
   
void U_denglu()//用户登录 
{
	int repeat = 1;//循环进行操作 
	int b,a=0,c,d,num1,num2;
	double money;
	FILE *AFile,*UFile;
 	char id1[20],id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20],cinema[20];
  	char choice[20];
	printf("请输入您的ID：\n");
	scanf ("%s",id1);
	UFile=fopen("users.txt","r");
	rewind(UFile); 
	while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF||a==1)
	{
		if(strcmp(id1,id2)==0)
		{
			a=1;
			printf("请输入您的密码：\n");
			scanf("%s",code1);
			if(strcmp(code1,code2)==0)
			{
				fclose(UFile);
				//这里把本次用户信息保存在 全 局 变 量 中！ 
				strcpy(U_quanju.ID,id2);
				strcpy(U_quanju.Name,name);
				strcpy(U_quanju.Sex,sex);
				strcpy(U_quanju.Tele,tele);
				strcpy(U_quanju.Code,code2);
				U_quanju.Money = money;
				strcpy(U_quanju.Mail,mail);
				//显示用户功能选择提示 
				printf("\n***************************************\n\n");
				printf("亲爱的用户! 您已成功登录! \n");
				repeat = 1;
				while(repeat == 1){
					printf("如果您想查看您的信息，请输入1：\n");     
					printf("如果您想搜索电影，请输入2：\n");    
					printf("如果您想查看您的订单，请输入3：\n");
					printf("如果您想要退出      ,请输入其他数字\n");
					while(1){
						fflush(stdin);
						scanf("%s",choice);
						if(judge_num(choice)!=0)
							continue;
					 	break;
					}
					switch(atoi(choice))
					{
						case 1:U_information(id1); /*用户个人信息*/  
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
					  		break;
						case 2:U_movie();/*用户搜索电影*/
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 3:U_order(id1);/*用户订单管理*/  
							printf("按任意键继续\n");
			    				fflush(stdin);
			    				getchar();
							break;
						default:
							repeat = 0;//退出
							fflush(stdin); 
							break;
					}
					a = 2;//a=2说明进过switchcase 
				}	
			}
		}
		else
		{
			switch(a)
			{
				case 1:
					printf("输入错误！\n");
					printf("重新登陆请按1：\n");
					printf("找回密码请按2：\n");
					printf("请输入您的选择：");
					scanf("%d",&d);
					if (d==1)	denglu();
					else{
						srand(time(0));
						num1=rand()%(10000-1000)+1000;
						printf("我们已经给您的邮箱发送了验证码\n");
						printf("请输入：\n");
						scanf("%d",num2);
						if(num1==num2)
						{
							printf("您的密码是%s\n",code2);
							printf("请及时更改\n");
							denglu();
						}
					}
					break;
				case 0://如果a=0 说明未找到用户名 
					//printf("*\n");//测试 
					break;
				default: 
					break;
			}
		}
	}
	if(a == 0){
		printf("您的ID不存在\n");
		printf("如果您想重新登录，请输入1：\n");
		printf("如果您想注册，请输入2：\n ");
		while(1){
			fflush(stdin);
			scanf("%s",choice);
			if(judge_num(choice)!=0)
				continue;
			 	break;
		}
		switch(atoi(choice))
		{
			case 1:
				denglu();
				break;
			case 2:
				register1();
				break;
			default:
				break;
		}
	}	
}

//****************************************管理员操作***********************************

//*************************************管理员个人信息查询及修改********************************
void A_information(char id1[20])
{
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	double c;
	int b=0,a=0;
	
	printf("\n如果你想查看你的基本信息，请输入1\n");
	printf("如果你想更改你的基本信息，请输入2\n");
	printf("如果你想返回上一界面，请输入任意值\n");
	scanf("%d",&b);
	switch(b)
	{
		case 1://管理员查看基本信息 
			{
				FILE *AFile;
				AFile=fopen("administrators.txt","r");
				while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF||a==0)
				{
					if(strcmp(id1,id2)==0)
					{
						a=1;
						printf("id          name        cinema           mail \n");
						printf("%-12s%-12s%-6s%-12s",id1,name,cinema,mail);
					}
				}
				fclose(AFile);
				break;
			}
		case 2://管理员更改信息 
		{
			A_change(id1);
			break;
	    }
		default:denglu();break;
	}
}

void A_change(char id1[20])//管理员信息更改 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","r");
	fp=fopen("administrators1.txt","w");
	int a=0,b=0;
	char choice[20];
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	
	printf("\n如果你想更改你的姓名，请输入1\n");
	printf("如果你想更改你的邮箱，请输入2\n");
	printf("如果你想更改你的密码，请输入3\n");
	printf("如果你想返回上一界面，请输入任意值\n"); 
	while(1)
	{
		fflush(stdin);
		scanf("%s",choice);
		if(judge_num(choice)!=0)
			continue; 
		a = atoi(choice);
		if(a!=1&&a!=2&&a!=3)
			continue;
		break;
	} 
	
	switch(a)
	{	
		case 1://更改姓名 
		{
			while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
			{
				if(strcmp(id1,id2)==0)
 	  			{
					printf("\n请输入您的新姓名：\n");//输入姓名 
					scanf("%s",name);
					fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail);	
				}
				else
				{
					fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail);}
			 	} 
   		    	fclose(AFile);
			fclose(fp);
			A_modify();
			break;
		}
		case 2://更改邮箱 
		{
			while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
			{
			  	if(strcmp(id1,id2)==0)
			  	{
				youxiangcheckA();
				fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,A_quanju.Mail);
				}
			else
			{
				fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail);}
			}	
			fclose(AFile);
			fclose(fp);
			A_modify();
			break;
		}
		case 3://更改密码 
		{
			int x=1;
			while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)	
			{
			  	if(strcmp(id1,id2)==0)
			  	{
			  		codecheck(x);
					fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,A_quanju.Code,mail);	
				}
				else
			{
				fprintf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail);}
			}	
			fclose(AFile);
			fclose(fp);
			A_modify();break;
		}
		default:A_information(id1);break;//返回上一界面 
	}
}

//*************************************管理员订单查看**************************************
void A_order()
{
	Order A_kan;
	FILE *fp2;
	char changci[20];
	int xuanze=0;
	char choice[20];
	
	fp2=fopen("orderMessage.txt","r");
	if (fp2==NULL)
	{
		printf("Failed to open!");
		exit(1);
	}
	while (fscanf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_kan.orderNum,
	A_kan.userID,A_kan.movieID,A_kan.cinema,A_kan.movie,A_kan.room,A_kan.row,A_kan.line,
	A_kan.beginTime,A_kan.endTime,A_kan.type,A_kan.language,&A_kan.fee,
	&A_kan.restticket,&A_kan.totalticket,&A_kan.ratio)!=EOF)
	{
		if (strcmp(A_quanju.Cinema,A_kan.cinema)==0)
			printf("%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_kan.orderNum,
			A_kan.userID,A_kan.movieID,A_kan.cinema,A_kan.movie,A_kan.room,A_kan.row,A_kan.line,
			A_kan.beginTime,A_kan.endTime,A_kan.type,A_kan.language,A_kan.fee,
			A_kan.restticket,A_kan.totalticket,A_kan.ratio); 	
	}
	fclose(fp2);
	system("cls");
	printf("按照已购票人数未放映升降序请输入1:\n");
	printf("按照按总收入已放映升序请输入2:\n");
	printf("按照已购票人数未放映升降序请输入3:\n");
	while (xuanze!=1&&xuanze!=2&&xuanze!=3) 
	{
		while(1)
		{
			fflush(stdin);
			scanf("%s",choice);
			if(judge_num(choice)!=0)
				continue; 
			xuanze = atoi(choice);
			break;
		} 
		switch (xuanze)
		{
			case 1:
				Cinemaquire();
				break;
			case 2:
				rangeTotalin(); 
				break;
			case 3:
				shengjiang(); 
				break;
			default:
				printf("输入错误，请重新输入：\n");
				break;
		}
	}
}

//*************************************管理员按照已购票人数未放映升降序******************************* 
void Cinemaquire()//按照已购票人数未放映升降序
{
	FILE *fp;//读写MovieMessage.txt文件 
	FILE *gtemp;//读写gtemp.txt文件 
	struct MovieMessage quire;//表示场次信息内容  
	int a=0;//选择查询方式 
	
	system("cls");//清屏 
	printf("                 ********************************************\n");  
	printf("                 *                                          *\n");
	printf("                 *             管理员电影查询界面           *\n");
	printf("                 *                                          *\n");
	printf("                 *                电影院查询                *\n");
	printf("                 *                                          *\n");
	printf("                 ********************************************\n\n");
	printf("                 ********************************************\n");  
	printf("                 *                   影院                   *\n");
	printf("                 *                   Houde                  *\n");
	printf("                 *                   Boxue                  *\n");
	printf("                 *                   Mashi                  *\n");
	printf("                 ********************************************\n\n");
	printf("场次编号  |电影院  |影片名 |厅号 |开场时间 |散场时间 |影片类型|语言|余票数|总票数|上座率|票价 \n"); 
	fp=fopen("MovieMessage.txt","r");//读取场次信息文件 
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
	//把统一影院的场次信息放入gtemp.txt文件 
	gtemp=fopen("gtemp.txt","w"); 
 	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)	
 		if(strcmp(A_quanju.Cinema,quire.cinema)==0)//判断所查影院和管理员负责影院是否相同 
		{
			fprintf(gtemp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
			quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
			quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			fclose(gtemp);
		}
	  	rewind(fp);
		fclose(fp);
		printf("请输入查询方式：\n");
		printf("升序请按“1”\n");
		printf("降序请按“2”\n");
		while(a!=1&&a!=2)
		{
			scanf("%d",&a);	
			switch (a)
			{
				case 1://升序 
 					rangeBuynumin();
					break;
				case 2://降序
		 			rangeBuynumde();
		 			break;
				default:
					printf("输入错误，请重新输入：\n");
					break;	 
			}
		}
	}
	
void rangeBuynumin()//按已购票人数还未放映升序 
{
	struct MovieMessage buynum_total[500];//声明一个结构体数组 
	int n=0;//同一个影院的总场次数 
	FILE *fp;//读写gtemp.txt文件 
	struct MovieMessage quire;//表示场次信息内容
		 
	system("cls"); //清屏 
	fp=fopen("gtemp.txt","r");
	if(fp==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	//将场次信息对应存入结构体数组 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		buynum_total[n].fee=quire.fee;
		strcpy(buynum_total[n].movieID,quire.movieID);
		strcpy(buynum_total[n].cinema,quire.cinema);
		strcpy(buynum_total[n].moviename,quire.moviename);
		strcpy(buynum_total[n].room,quire.room);
		strcpy(buynum_total[n].beginTime,quire.beginTime);
		strcpy(buynum_total[n].endTime,quire.endTime);
		strcpy(buynum_total[n].type,quire.type);
		strcpy(buynum_total[n].language,quire.language);
		buynum_total[n].restticket=quire.restticket;
		buynum_total[n].totalticket=quire.totalticket;
		buynum_total[n].ratio=quire.ratio;
		n++;
	} 
 	//升序排序
	int i;//一次循环 
 	int j;//二次循环 
	struct MovieMessage t; //中间值 
        
	for (i=0;i<n-1;i++)  
	{
		for (j=0;j<n-1-i;j++)  
            {
			if ((buynum_total[j].totalticket-buynum_total[j].restticket)>(buynum_total[j+1].totalticket-buynum_total[j+1].restticket))
			{
				t=buynum_total[j];
				buynum_total[j]=buynum_total[j+1];
				buynum_total[j+1]=t; 
			}
            }
	}
	printf("编号  |电影院|    影片名    |  厅号 |    开场时间     |   散场时间    |影片类型|  语言 |余票数|总票数|   上座率    |      票价 \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",buynum_total[i].movieID,buynum_total[i].cinema,buynum_total[i].moviename,
		buynum_total[i].room,buynum_total[i].beginTime,buynum_total[i].endTime,buynum_total[i].type,buynum_total[i].language,
		buynum_total[i].restticket,
		buynum_total[i].totalticket,
		buynum_total[i].ratio,buynum_total[i].fee);
	}
	fclose(fp);  
}

void rangeBuynumde()//按已购票人数还未放映降序 
{
	struct MovieMessage buynum_total[500];//声明一个结构体数组 
	int n=0;//同一个影院的总场次数 
	FILE *fp;//读写gtemp.txt文件 
	struct MovieMessage quire;//表示场次信息内容 
		
	system("cls");  //清屏 
	fp=fopen("gtemp.txt","r");
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
	//将场次信息对应存入结构体数组
 	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		buynum_total[n].fee=quire.fee;
		strcpy(buynum_total[n].movieID,quire.movieID);
		strcpy(buynum_total[n].cinema,quire.cinema);
		strcpy(buynum_total[n].moviename,quire.moviename);
		strcpy(buynum_total[n].room,quire.room);
		strcpy(buynum_total[n].beginTime,quire.beginTime);
		strcpy(buynum_total[n].endTime,quire.endTime);
		strcpy(buynum_total[n].type,quire.type);
		strcpy(buynum_total[n].language,quire.language);
		buynum_total[n].restticket=quire.restticket;
		buynum_total[n].totalticket=quire.totalticket;
		buynum_total[n].ratio=quire.ratio;
		n++;
	} 
	//降序排序
	int i;//一次循环 
	int j;//二次循环 
        
	struct MovieMessage t;//中间值 
	for (i=0;i<n-1;i++)  
 	{
		for (j=0;j<n-1-i;j++)  
            {
			if ((buynum_total[j].totalticket-buynum_total[j].restticket)<(buynum_total[j+1].totalticket-buynum_total[j+1].restticket))
			{
				t=buynum_total[j];
				buynum_total[j]=buynum_total[j+1];
				buynum_total[j+1]=t; 
			}
		}
	}
	printf("编号  |电影院|    影片名    |  厅号 |    开场时间     |   散场时间    |影片类型|  语言 |余票数|总票数|   上座率    |      票价 \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",buynum_total[i].movieID,buynum_total[i].cinema,buynum_total[i].moviename,
		buynum_total[i].room,buynum_total[i].beginTime,buynum_total[i].endTime,buynum_total[i].type,buynum_total[i].language,
		buynum_total[i].restticket,
		buynum_total[i].totalticket,
		buynum_total[i].ratio,buynum_total[i].fee);
	}
	fclose(fp);    
}

//****************************管理员按照管理员按照总票价排序*****************************
void rangeTotalin()//按总收入已放映升序 
{
	struct MovieMessage income_total[500];//声明一个结构的数组 
	int n=0;//表示九月五号的所有场次数 
	int m=0;//表示九月六号的所有场次数 
	int b=0;//表示九月七号的所有场次数 
	FILE *fp;//读写MovieMessage文件 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//表示场次信息内容 
		
	system("cls");//清屏 
	fp=fopen("MovieMessage.txt","r");
	if(fp==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day1,quire.beginTime,5)==0)
		{
			income_total[n].fee=quire.fee;
			strcpy(income_total[n].movieID,quire.movieID);
			strcpy(income_total[n].cinema,quire.cinema);
			strcpy(income_total[n].moviename,quire.moviename);
			strcpy(income_total[n].room,quire.room);
			strcpy(income_total[n].beginTime,quire.beginTime);
			strcpy(income_total[n].endTime,quire.endTime);
			strcpy(income_total[n].type,quire.type);
			strcpy(income_total[n].language,quire.language);
			income_total[n].restticket=quire.restticket;
			income_total[n].totalticket=quire.totalticket;
			income_total[n].ratio=quire.ratio;
			n++;
		}
	}
 	//升序排序
	int i;//一次循环  
	int j;//二次循环 
	struct MovieMessage t; //中间值 
        
	for (i=0;i<n-1;i++)  
	{
		for (j=0;j<n-1-i;j++)  
            {
                if (((income_total[j].totalticket-income_total[j].restticket)*income_total[j].fee)<((income_total[j+1].totalticket-income_total[j+1].restticket)*income_total[j+1].fee))
                {
                    t=income_total[j];
                    income_total[j]=income_total[j+1];
                    income_total[j+1]=t; 
                }
            }
	}
	printf("编号  |电影院|    影片名    |  厅号 |    开场时间     |   散场时间    |影片类型|  语言 |余票数|总票数|   上座率    |      票价 \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[i].movieID,income_total[i].cinema,income_total[i].moviename,
		income_total[i].room,income_total[i].beginTime,income_total[i].endTime,income_total[i].type,income_total[i].language,
		income_total[i].restticket,income_total[i].totalticket,
		income_total[i].ratio,income_total[i].fee);
	}
	rewind(fp);//光标回到文件开头 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day2,quire.beginTime,5)==0)
		{
			income_total[m].fee=quire.fee;
			strcpy(income_total[m].movieID,quire.movieID);
			strcpy(income_total[m].cinema,quire.cinema);
			strcpy(income_total[m].moviename,quire.moviename);
			strcpy(income_total[m].room,quire.room);
			strcpy(income_total[m].beginTime,quire.beginTime);
			strcpy(income_total[m].endTime,quire.endTime);
			strcpy(income_total[m].type,quire.type);
			strcpy(income_total[m].language,quire.language);
			income_total[m].restticket=quire.restticket;
			income_total[m].totalticket=quire.totalticket;
			income_total[m].ratio=quire.ratio;
			m++;
			}
	} 
	//升序排序 
	int q;//一次循环 
	int w;//二次循环 
	struct MovieMessage e; //中间值 
        
	for (q=0;q<m-1;q++)  
	{
		for (w=0;w<m-1-q;w++)  
		{
			if (((income_total[w].totalticket-income_total[w].restticket)*income_total[w].fee)<((income_total[w+1].totalticket-income_total[w+1].restticket)*income_total[w+1].fee))
			{
				e=income_total[w];
				income_total[w]=income_total[w+1];
				income_total[w+1]=e; 
			}
		}
	}  
	for(int q=0;q<m;q++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[q].movieID,income_total[q].cinema,income_total[q].moviename,
		income_total[q].room,income_total[q].beginTime,income_total[q].endTime,income_total[q].type,income_total[q].language,
		income_total[q].restticket,income_total[q].totalticket,
		income_total[q].ratio,income_total[q].fee);
	}
	rewind(fp);//光标回到文件开头 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day3,quire.beginTime,5)==0)
		{
			income_total[b].fee=quire.fee;
			strcpy(income_total[b].movieID,quire.movieID);
			strcpy(income_total[b].cinema,quire.cinema);
			strcpy(income_total[b].moviename,quire.moviename);
			strcpy(income_total[b].room,quire.room);
			strcpy(income_total[b].beginTime,quire.beginTime);
			strcpy(income_total[b].endTime,quire.endTime);
			strcpy(income_total[b].type,quire.type);
			strcpy(income_total[b].language,quire.language);
			income_total[b].restticket=quire.restticket;
			income_total[b].totalticket=quire.totalticket;
			income_total[b].ratio=quire.ratio;
			b++;
		}
	} 
	//升序排序
	int a;//一次循环  
	int s;//二次循环 
	struct MovieMessage d; //中间值
		 
	for (a=0;i<b-1;a++)  
	{
		for (s=0;s<b-1-a;s++)  
		{
			if (((income_total[s].totalticket-income_total[s].restticket)*income_total[s].fee)<((income_total[s+1].totalticket-income_total[s+1].restticket)*income_total[s+1].fee))
			{
				d=income_total[s];
				income_total[s]=income_total[s+1];
				income_total[s+1]=d; 
			}
		}
	} 
	for(int a=0;a<b;a++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[a].movieID,income_total[a].cinema,income_total[a].moviename,
		income_total[a].room,income_total[a].beginTime,income_total[a].endTime,income_total[a].type,income_total[a].language,
		income_total[a].restticket,income_total[a].totalticket,
		income_total[a].ratio,income_total[a].fee);
	}
	rewind(fp);
	fclose(fp);
	yingtingzongjia();//调用单个影厅总票价查询函数 	
}

int U_valid(char room[20])//验证影厅是否存在
{
	FILE * S_Message;//所有影厅的信息
	struct ScreenMessage SM;
 
	S_Message=fopen("ScreenMessage.txt","r");
	while(fscanf(S_Message,"%s %s %s",SM.cinema,SM.room,SM.type)!=EOF)
	{
		if(strcmp(room,SM.room)==0)
		return 0; //正确 
	}
	printf("未开设该影厅，请您重新输入\n");
	fflush(stdin);
	getchar();
	return 1; 
}

void yingtingzongjia()//影厅总价查询 
{
	FILE *fp3;//读写OrderMessage.txt文件 
	Order A_ji;//表示订单信息内容 
	int choice;//选择 
	double total=0;//总票价 
	char yingting[10];//输入影厅名
     	
 	while(1)
	{
	printf("                 ********************************************\n");  
	printf("                 *                                          *\n");
	printf("                 *           管理员影厅总票价查询           *\n");
	printf("                 *                                          *\n");
	printf("                 ********************************************\n\n");
	printf("请输入你想查询的影厅：");
	fflush(stdin);
	scanf("%s",yingting);
	if(judge_num(yingting)!=0)
		continue; 
	if(U_valid(yingting))
		continue;
	break;
	} 
     	fp3=fopen("OrderMessage.txt","r");
	if(fp3==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
 	while (fscanf(fp3,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_ji.orderNum,
	A_ji.userID,A_ji.movieID,A_ji.cinema,A_ji.movie,A_ji.room,A_ji.row,A_ji.line,
	A_ji.beginTime,A_ji.endTime,A_ji.type,A_ji.language,&A_ji.ratio,
	&A_ji.restticket,&A_ji.totalticket,&A_ji.fee)!=EOF)
	       if (strcmp(A_ji.cinema,A_quanju.Cinema)==0)
		      if (strcmp(A_ji.room,yingting)==0)	
			     total=total+A_ji.fee;
			     printf("影厅    总票价\n"); 
			     printf("%s    %f\n",yingting,total); 
			     printf("/是否继续查询其他影厅/(继续输入1/结束输入2):\n");
	while(choice!=1 && choice!=2)
	{
		scanf("%d",&choice);
		switch(choice)
		{
			case 1://继续查询其他影厅总票价 
			yingtingzongjia(); 
			break;
			case 2://结束查询 
			break; 
			default:
			printf("请重新选择：");
			break;	
		}
	}
	fclose(fp3);	
}

//****************************管理员按照管理员按照上座率排序*****************************
void shengjiang()//上座率升降序 
{
	int a=0;//选择 
	
	printf("请输入查询方式：\n");
	printf("升序请按“1”\n");
	printf("降序请按“2”\n");
	while(a!=1&&a!=2)
	{
		scanf("%d",&a);	
		switch (a)
		{
			case 1://升序 
				rangeBuynumin();
				break;
			case 2://降序
	 			rangeBuynumde();
	 			break;
			default:
				printf("输入错误，请重新输入：");
				break;	 
		}
	}
}

void rangeratioin()//按上座率分日期所有已经放映升序 
{
	struct MovieMessage ratio_total[500];//声明一个结构体数组 
	int n=0;//表示九月五号的所有场次数  
	int m=0;//表示九月六号的所有场次数
	int b=0;//表示九月七号的所有场次数
	FILE *fp;//读写MovieMessage.txt文件 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//表示场次信息 
		
	system("cls"); //清屏 
	fp=fopen("MovieMessage.txt","r");
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
 	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day1,quire.beginTime,5)==0)
		{
		ratio_total[n].fee=quire.fee;
		strcpy(ratio_total[n].movieID,quire.movieID);
		strcpy(ratio_total[n].cinema,quire.cinema);
		strcpy(ratio_total[n].moviename,quire.moviename);
		strcpy(ratio_total[n].room,quire.room);
		strcpy(ratio_total[n].beginTime,quire.beginTime);
		strcpy(ratio_total[n].endTime,quire.endTime);
		strcpy(ratio_total[n].type,quire.type);
		strcpy(ratio_total[n].language,quire.language);
		ratio_total[n].restticket=quire.restticket;
		ratio_total[n].totalticket=quire.totalticket;
		ratio_total[n].ratio=quire.ratio;
		n++;
		} 
	}
 	//升序排序
	int i;//一次循环 
	int j;//二次循环 
	struct MovieMessage t; //中间值 
    
	for (i=0;i<n-1;i++)  
	{
		for (j=0;j<n-1-i;j++)  
		{
			if (ratio_total[j].ratio>ratio_total[j+1].ratio)
			{
				t=ratio_total[j];
				ratio_total[j]=ratio_total[j+1];
				ratio_total[j+1]=t; 
			}
		}
	}
	printf("编号  |电影院|    影片名    |  厅号 |    开场时间     |   散场时间    |影片类型|  语言 |余票数|总票数|   上座率    |      票价 \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
		ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
		ratio_total[i].restticket,
		ratio_total[i].totalticket,
		ratio_total[i].ratio,ratio_total[i].fee);
	}
	rewind(fp);//光标回到文件开头 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day2,quire.beginTime,5)==0)
		{
			ratio_total[m].fee=quire.fee;
			strcpy(ratio_total[m].movieID,quire.movieID);
			strcpy(ratio_total[m].cinema,quire.cinema);
			strcpy(ratio_total[m].moviename,quire.moviename);
			strcpy(ratio_total[m].room,quire.room);
			strcpy(ratio_total[m].beginTime,quire.beginTime);
			strcpy(ratio_total[m].endTime,quire.endTime);
			strcpy(ratio_total[m].type,quire.type);
			strcpy(ratio_total[m].language,quire.language);
			ratio_total[m].restticket=quire.restticket;
			ratio_total[m].totalticket=quire.totalticket;
			ratio_total[m].ratio=quire.ratio;
			m++;
		} 
	}
	//升序排序 
	int q;//一次循环 
	int w;//二次循环 
	struct MovieMessage e;//中间值 
        
	for (q=0;q<m-1;q++)  
	{
		for (w=0;w<m-1-q;w++)  
		{
			if (ratio_total[w].ratio>ratio_total[w+1].ratio)
			{
				e=ratio_total[w];
				ratio_total[w]=ratio_total[w+1];
				ratio_total[w+1]=e; 
			}
		}
	}
	for(int q=0;q<m;q++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[q].movieID,ratio_total[q].cinema,ratio_total[q].moviename,
		ratio_total[q].room,ratio_total[q].beginTime,ratio_total[q].endTime,ratio_total[q].type,ratio_total[q].language,
		ratio_total[q].restticket,
		ratio_total[q].totalticket,
		ratio_total[q].ratio,ratio_total[q].fee);
	}
	rewind(fp);//光标回到文件开头 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)   
	{
		if(strncasecmp(day3,quire.beginTime,5)==0)
		{
			ratio_total[b].fee=quire.fee;
			strcpy(ratio_total[b].movieID,quire.movieID);
			strcpy(ratio_total[b].cinema,quire.cinema);
			strcpy(ratio_total[b].moviename,quire.moviename);
			strcpy(ratio_total[b].room,quire.room);
			strcpy(ratio_total[b].beginTime,quire.beginTime);
			strcpy(ratio_total[b].endTime,quire.endTime);
			strcpy(ratio_total[b].type,quire.type);
			strcpy(ratio_total[b].language,quire.language);
			ratio_total[b].restticket=quire.restticket;
			ratio_total[b].totalticket=quire.totalticket;
			ratio_total[b].ratio=quire.ratio;
			b++;
		    } 
	}
	//升序排序 
	int a;//一次循环 
	int s;//二次循环 
	struct MovieMessage d;//中间值 
        
	for (a=0;a<b-1;a++)  
	{
            for (s=0;s<b-1-a;s++)  
            {
			if (ratio_total[s].ratio>ratio_total[s+1].ratio)
			{
				d=ratio_total[s];
				ratio_total[s]=ratio_total[s+1];
				ratio_total[s+1]=d; 
			}
		}
	}
	for(int a=0;a<b;a++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[a].movieID,ratio_total[a].cinema,ratio_total[a].moviename,
		ratio_total[a].room,ratio_total[a].beginTime,ratio_total[a].endTime,ratio_total[a].type,ratio_total[a].language,
		ratio_total[a].restticket,
		ratio_total[a].totalticket,
		ratio_total[a].ratio,ratio_total[a].fee);
	}
	fclose(fp);
}

void rangeratiode()//按上座率分日期所有已经放映降序 
{
	struct MovieMessage ratio_total[500];//声明一个结构体数组 
	int n=0;//表示九月五号的总场次数 
	int m=0;//表示九月六号的总场次数 
	int b=0;//表示九月五七的总场次数 
	FILE *fp;//读写MovieMessage.txt文件 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//描述场次信息 
		
	system("cls");//清屏 
	fp=fopen("MovieMessage.txt","r");
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day1,quire.beginTime,5)==0)
		{
			ratio_total[n].fee=quire.fee;
			strcpy(ratio_total[n].movieID,quire.movieID);
			strcpy(ratio_total[n].cinema,quire.cinema);
			strcpy(ratio_total[n].moviename,quire.moviename);
			strcpy(ratio_total[n].room,quire.room);
			strcpy(ratio_total[n].beginTime,quire.beginTime);
			strcpy(ratio_total[n].endTime,quire.endTime);
			strcpy(ratio_total[n].type,quire.type);
			strcpy(ratio_total[n].language,quire.language);
			ratio_total[n].restticket=quire.restticket;
			ratio_total[n].totalticket=quire.totalticket;
			ratio_total[n].ratio=quire.ratio;
			n++;
		} 
	}
	//降序排序 
	int i;//一次循环 
	int j;//二次循环 
	struct MovieMessage t;//中间值
		 
	for (i=0;i<n-1;i++)  
	{
		for (j=0;j<n-1-i;j++)  
		{
			if (ratio_total[j].ratio<ratio_total[j+1].ratio)
			{
				t=ratio_total[j];
				ratio_total[j]=ratio_total[j+1];
				ratio_total[j+1]=t; 
			}
		}
	}
	printf("编号  |电影院|    影片名    |  厅号 |    开场时间     |   散场时间    |影片类型|  语言 |余票数|总票数|   上座率    |      票价 \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
		ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
		ratio_total[i].restticket,
		ratio_total[i].totalticket,
		ratio_total[i].ratio,ratio_total[i].fee);
	}
 	rewind(fp);//光标回到文件开头 
 	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strncasecmp(day2,quire.beginTime,5)==0)
		{
			ratio_total[m].fee=quire.fee;
			strcpy(ratio_total[m].movieID,quire.movieID);
			strcpy(ratio_total[m].cinema,quire.cinema);
			strcpy(ratio_total[m].moviename,quire.moviename);
			strcpy(ratio_total[m].room,quire.room);
			strcpy(ratio_total[m].beginTime,quire.beginTime);
			strcpy(ratio_total[m].endTime,quire.endTime);
			strcpy(ratio_total[m].type,quire.type);
			strcpy(ratio_total[m].language,quire.language);
			ratio_total[m].restticket=quire.restticket;
			ratio_total[m].totalticket=quire.totalticket;
			ratio_total[m].ratio=quire.ratio;
			m++;
		} 
	}
	//降序排序
	int q;//一次循环 
	int w;//二次循环 
	struct MovieMessage e;//中间值
		 
	for (q=0;q<m-1;q++)  
	{
		for (w=0;w<m-1-q;w++)  
		{
			if (ratio_total[w].ratio<ratio_total[w+1].ratio)
			{
				e=ratio_total[w];
				ratio_total[w]=ratio_total[w+1];
				ratio_total[w+1]=e; 
			}
		}
	}
	for(int q=0;q<m;q++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[q].movieID,ratio_total[q].cinema,ratio_total[q].moviename,
		ratio_total[q].room,ratio_total[q].beginTime,ratio_total[q].endTime,ratio_total[q].type,ratio_total[q].language,
		ratio_total[q].restticket,
		ratio_total[q].totalticket,
		ratio_total[q].ratio,ratio_total[q].fee);
	}
	rewind(fp);//光标回到文件开头 
	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)   
	{
		if(strncasecmp(day3,quire.beginTime,5)==0)
		{
			ratio_total[b].fee=quire.fee;
			strcpy(ratio_total[b].movieID,quire.movieID);
			strcpy(ratio_total[b].cinema,quire.cinema);
			strcpy(ratio_total[b].moviename,quire.moviename);
			strcpy(ratio_total[b].room,quire.room);
			strcpy(ratio_total[b].beginTime,quire.beginTime);
			strcpy(ratio_total[b].endTime,quire.endTime);
			strcpy(ratio_total[b].type,quire.type);
			strcpy(ratio_total[b].language,quire.language);
			ratio_total[b].restticket=quire.restticket;
			ratio_total[b].totalticket=quire.totalticket;
			ratio_total[b].ratio=quire.ratio;
			b++;
		} 
	}
	//降序排序
	int a;//一次循环  
	int s;//二次循环 
	struct MovieMessage d;//中间值
		 
	for (a=0;a<b-1;a++)  
	{
            for (s=0;s<b-1-a;s++)  
            {
			if (ratio_total[s].ratio<ratio_total[s+1].ratio)
			{
				d=ratio_total[s];
				ratio_total[s]=ratio_total[s+1];
				ratio_total[s+1]=d; 
			}
		}
	}
	for(int a=0;a<b;a++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[a].movieID,ratio_total[a].cinema,ratio_total[a].moviename,
		ratio_total[a].room,ratio_total[a].beginTime,ratio_total[a].endTime,ratio_total[a].type,ratio_total[a].language,
		ratio_total[a].restticket,
		ratio_total[a].totalticket,
		ratio_total[a].ratio,ratio_total[a].fee);
	}	
	fclose(fp);
}

//*************************************场次添加和查看**************************************
void A_session_add()//管理员场次添加 
{
	FILE * M_Message;//所有影厅的信息
	struct MovieMessage MM1 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};//最终读取的管理员输入		
	char choice[20] = {'\0'};
	//输入的时间
	char date[5] = {'\0'},tIme[5] = {'\0'};
	int month=0,day=0,hour=0,minute=0;//输入的时间
	int min1_b=0,min1_e=0;//用户输入的开始时间和结束时间
	//文件的时间 
	int month2=0,day2=0,hour2=0,minute2=0;//文件中的时间
	int min2_b=0,min2_e=0;//文件中的开始时间和结束时间
	int a = 1,b = 1;
	
	//测试文件是否可以打开 
	if((M_Message=fopen("MovieMessage.txt","r"))!=NULL){
		fclose(M_Message);
	}else{
		printf("文本(MovieMessage.txt)打开错误\n");
		system("pause");
	}
	//开始获得用户正确输入
	system("cls");
	printf("\n 请您输入添加场次的信息：\n\n!!仔细阅读说明，"
			 "并按照规定格式输入，否则无效！！\n\n");
	//影片名 
	while(1){
		printf("请您输入 影片名\n");
		fflush(stdin);
		scanf("%s",MM1.moviename);
	 	if(judge_kongge(MM1.moviename)!=0)
			continue;	
	 	break;
	}
	//放映厅号 
	while(1){
	 	printf("请您输入 放映厅号（如 1 ）\n您已开设一下影厅：\n");
		A_screen_check();//打印一遍影厅信息
		fflush(stdin);
		scanf("%s",MM1.room);
	 	if(judge_num(MM1.room)!=0)
			continue;	
		if(A_session_room_valid(MM1.room)!=0)
			continue;
	 	break;
	}
	//语言 
	while(1){
	 	printf("请您输入播放的语言 中文输入1，英文输入2\n");
	 	fflush(stdin);
	 	scanf("%s",choice);
	 	if(judge_num(choice)!=0)
	 		continue;
		if(atoi(choice)!=1&&atoi(choice)!=2)
			continue;
		if(choice[0] == '1')
			strcpy(MM1.language,"Chinese");
		else if(choice[0] == '2')
			strcpy(MM1.language,"English");
		break;
	}
	//票价
	while(1){
	 	printf("请您输入电影的票价\n");
	 	fflush(stdin);
	 	scanf("%s",choice);
	 	if(judge_num(choice)!=0)
	 		continue;
 		break;//从此choice用来保存票价信息，不可以再被赋值！！！ 
	}
	//开场时间
	b = 1;
	while(b){//进入一段b就输入一次开场时间 
		a=1;
		//获取设定的开场时间
		while(a){
			a=0;
			date[0]='\0';date[1]='\0';date[2]='\0';date[3]='\0';date[4]='\0';date[5]='\0';
			printf("请您严格按照格式输入开场日期\n如：09/05,09/12\n");
			fflush(stdin);
			scanf("%s",date);//以后要记得加格式判断
			month = (int(date[0])-48)*10+ (int(date[1])-48);//月
			day = (int(date[3])-48)*10 + (int(date[4])-48);	//日
			if(day<0||day>31)
			{
				printf("日期输入有问题！");
				a=1;
			}
			if(int(date[2]) != 47)
			{
			printf("格式输入有问题！");
			a=1;
			}
			switch (month)//标准日位 
			{		
				case 1:
					break;	     
				case 2:
					day+=31;
					break;
				case 3:
					day+=60;
					break;
				case 4:
					day+=91;
					break;
				case 5:
					day+=121;
					break;
				case 6:
					day+=152;
					break;
				case 7:
					day+=182;
					break;
				case 8:
					day+=213;
					break;
				case 9:
					day+=244;
					break;
				case 10:
					day+=274;
					break;
				case 11:
					day+=305;
					break;
				case 12:
					day+=335;
					break;
				default:
					printf("月份输入有问题！");
					a=1;
					break;
			}
		}//while(a)的循环结束 (获得日期)
		a = 1;
		while(a==1){
			a = 0;
			tIme[0]='\0';tIme[1]='\0';tIme[2]='\0';tIme[3]='\0';tIme[4]='\0';tIme[5]='\0';
			printf("请您严格按照格式输入开场时间\n如：00:30,15:30\n");
	 		fflush(stdin);
		 	scanf("%s",tIme); //以后要记得加格式判断
	 		hour = (int(tIme[0])-48)*10+(int(tIme[1])-48);//小时
	 		if(hour<0||hour>23)
		 	{
				printf("小时输入有问题！\n");
				a = 1;
			}
	 		if(int(tIme[2]) != 58)
			{
				printf("格式输入有问题！");
				a=1;
			}
			minute = (int(tIme[3])-48)*10+(int(tIme[4])-48);//分钟 
			if(minute<0||minute>59)
			{
			printf("分钟输入有问题！\n");
			a = 1;
			}
			minute += hour*60 + 24*60*(day-1); //标准分钟位
			min1_b = minute;	
		}//while(a)的循环结束 (获得时间)
		if(A_session_add_valid(min1_b,-1,MM1.room))
		{
			strcpy(MM1.beginTime,date);
			strcat(MM1.beginTime,"/");
			strcat(MM1.beginTime,tIme);
			break;
		}
	}  //while(b)的循环结束
	//结束时间
	b = 1;
	while(b)
	{//进入一段b就输入一次开场时间 
		a=1;
		//获取设定的结束时间
		while(a)
		{
			a=0;
			date[0]='\0';date[1]='\0';date[2]='\0';date[3]='\0';date[4]='\0';date[5]='\0';
			printf("请您严格按照格式输入结束日期\n如：09/05,09/12\n");
			fflush(stdin);
			scanf("%s",date);//以后要记得加格式判断
			month = (int(date[0])-48)*10+ (int(date[1])-48);//月
			day = (int(date[3])-48)*10 + (int(date[4])-48);	//日
			if(day<0||day>31)
			{
				printf("日期输入有问题！");
				a=1;
			}
			if(int(date[2]) != 47)
			{
				printf("格式输入有问题！");
				a=1;
			}
			switch (month)
			{		//标准日位 
				case 1:
					break;	     
				case 2:
					day+=31 ;
					break;
				case 3:
					day+=60 ;
					break;
				case 4:
					day+=91 ;
					break;
				case 5:
					day+=121;
					break;
				case 6:
					day+=152;
					break;
				case 7:
					day+=182;
					break;
				case 8:
					day+=213;
					break;
				case 9:
					day+=244;
					break;
				case 10:
					day+=274;
					break;
				case 11:
					day+=305;
					break;
				case 12:
					day+=335;
					break;
				default:
					printf("月份输入有问题！");
					a=1;
					break;
			}
		}//while(a)的循环结束 (获得日期)
		a = 1;
		while(a==1)
		{
			a = 0;
			tIme[0]='\0';tIme[1]='\0';tIme[2]='\0';tIme[3]='\0';tIme[4]='\0';tIme[5]='\0';
			printf("请您严格按照格式输入结束时间\n如：00:30,15:30\n");
	 		fflush(stdin);
		 	scanf("%s",tIme);//以后要记得加格式判断
	 		hour = (int(tIme[0])-48)*10+(int(tIme[1])-48);//小时
	 		if(hour<0||hour>23){printf("小时输入有问题！\n");a = 1;}
	 		if(int(tIme[2]) != 58){printf("格式输入有问题！");a=1;}
			minute = (int(tIme[3])-48)*10+(int(tIme[4])-48);//分钟 
			if(minute<0||minute>59){printf("分钟输入有问题！\n");a = 1;}
			minute += hour*60 + 24*60*(day-1); //标准分钟位
			min1_e = minute;	
		}//while(a)的循环结束 (获得时间)
		if(A_session_add_valid(min1_b,min1_e,MM1.room)){
		strcpy(MM1.endTime,date);
		strcat(MM1.endTime,"/");
		strcat(MM1.endTime,tIme);
		break;
		} 
	}  //while(b)的循环结束
	//将信息打入文本
	A_session_add_print(MM1.moviename,MM1.room,MM1.beginTime,MM1.endTime,MM1.language,choice);//判断添加片场时间是否合法	 	 	
}

void A_session_add_print(char moviename[],char room[],char beginTime[],char endTime[],char language[],char choice[])//判断添加片场时间是否合法
{
	struct ScreenMessage SM3 = {{'\0'},{'\0'},{'\0'}};
	struct MovieMessage MM3 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};		
	FILE * M_Message;//所有场次的信息
	FILE * S_Message;//所有影厅的信息
	int count_=0,read_=0;//记录场次序号
	int num = 0;//余票数和总票数
	char choice_[20]={'\0'}; 
	
	//影片类型  为 SM3.type	
	S_Message=fopen("ScreenMessage.txt","r");
	while(fscanf(S_Message,"%s  %s  %sf",SM3.cinema,SM3.room,SM3.type)!=EOF) 
	{
		if(strcmp(SM3.cinema,A_quanju.Cinema) == 0)
		if(strcmp(SM3.room,room) == 0)
		break;
	} 
	fclose(S_Message);
	//场次序号   count_ 
	M_Message=fopen("MovieMessage.txt","r");
	while(fscanf(M_Message,"%d  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",
		&read_,MM3.cinema,MM3.moviename,MM3.room,MM3.beginTime,
		MM3.endTime,MM3.type,MM3.language,&MM3.restticket,&MM3.totalticket,
		&MM3.ratio,&MM3.fee)!=EOF)
	{
		if(count_<read_) count_=read_;
	}
	count_+=1;
	fclose(M_Message);
	//余票数与总票数  num 
	if(strcmp(SM3.type,"Imax") == 0)
		num = 150;
	else
		num = 100;
	//询问管理员是否要添加
	printf("\n影片名:%s\n影厅号:%s\n开场时间:%s\n离场时间:%s\n影片类型:%s\n语言:"
	"%s\n票价:%s\n",moviename,room,beginTime,endTime,SM3.type,language,choice);	
	while(1)
	{
	 	printf("\n上面是您这次添加片场的信息\n确定添加输入1，不添加输入其他数字\n");
	 	fflush(stdin);
 		scanf("%s",choice_);
	 	if(judge_num(choice_)!=0)
	 		continue;
 		break;
	}
	//进行添加或者放弃
	if(atoi(choice_) == 1)
	{
		M_Message=fopen("MovieMessage.txt","a");	
		fprintf(M_Message,"%d\t%s\t%s\t%s\t",count_,A_quanju.Cinema,moviename,room);
		fprintf(M_Message,"%s\t%s\t%s\t%s\t",beginTime,endTime,SM3.type,language);
		fprintf(M_Message,"%d\t%d\t0 \t%s\n",num,num,choice);
		fclose(M_Message);
		printf("您已成功添加！\n");
	}
	else
	{
		printf("您已取消添加！\n");
	}	
}

int A_session_add_valid(int min1_b,int min1_e,char room[])//场次添加时间验证 
{	
	int month=0,day=0,hour=0,minute=0;//读出来的开始时间 
	int month2=0,day2=0,hour2=0,minute2=0;//读出来的结束时间 
	FILE * M_Message;//所有影厅的信息
	
	struct MovieMessage MM2 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};		
	M_Message=fopen("MovieMessage.txt","r");
	while(fscanf(M_Message,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",//"\"是换行符，不能省略! 
	MM2.movieID,MM2.cinema,MM2.moviename,MM2.room,MM2.beginTime,
	MM2.endTime,MM2.type,MM2.language,&MM2.restticket,&MM2.totalticket,
	&MM2.ratio,&MM2.fee)!=EOF){
		if(strcmp(MM2.cinema,A_quanju.Cinema) == 0)
		if(strcmp(room,MM2.room) == 0)
		{
			//读出对影厅的一次开场时间 
			month =(int(MM2.beginTime[0])-48)*10+(int(MM2.beginTime[1])-48);//月
			day =(int(MM2.beginTime[3])-48)*10+(int(MM2.beginTime[4])-48);  //日
			hour=(int(MM2.beginTime[6])-48)*10+(int(MM2.beginTime[7])-48);//小时
			minute=(int(MM2.beginTime[9])-48)*10+(int(MM2.beginTime[10])-48);//分钟 
			switch (month)
			{
				case 1:
					break;
				case 2:
					day += 31;
					break;
				case 3:
					day += 60;
					break;
				case 4:
					day += 91;
					break;
				case 5:
					day += 121;
					break;
				case 6:
					day += 152;
					break;
				case 7:
					day += 182;
					break;
				case 8:
					day += 213;
					break;
				case 9:
					day += 244;
					break;
				case 10:
					day+= 274;
					break;
				case 11:
					day+= 305;
					break;
				case 12:
					day+= 335;
					break;
				default:
					printf("月份读取出现问题！\n");
					break;
			}
			minute += hour*60 + 24*60*(day-1);//转换为分钟
			//读出对影厅的一次结束时间 
			month2 =(int(MM2.endTime[0])-48)*10+(int(MM2.endTime[1])-48);//月
			day2 =(int(MM2.endTime[3])-48)*10+(int(MM2.endTime[4])-48);  //日
			hour2=(int(MM2.endTime[6])-48)*10+(int(MM2.endTime[7])-48);//小时
			minute2=(int(MM2.endTime[9])-48)*10+(int(MM2.endTime[10])-48);//分钟 
			switch (month2)
			{
				case 1:
					break;
				case 2:
					day2 += 31;
					break;
				case 3:
					day2 += 60;
					break;
				case 4:
					day2 += 91;
					break;
				case 5:
					day2 += 121;
					break;
				case 6:
					day2 += 152;
					break;
				case 7:
					day2 += 182;
					break;
				case 8:
					day2 += 213;
					break;
				case 9:
					day2 += 244;
					break;
				case 10:
					day2+= 274;
					break;
				case 11:
					day2+= 305;
					break;
				case 12:
					day2+= 335;
					break;
				default:
					printf("月份读取出现问题！\n");
					break;
			}
			minute2 += hour2*60 + 24*60*(day2-1);//转换为分钟
			//判断用户的输入是否合法 
			if(min1_e == -1)
			{//判断开始时间 
				if(min1_b<(minute2+20)&&min1_b>(minute-20))
				{
					printf("您的开场时间设置不合理！\n");
					fclose(M_Message);
					return 0;
				}
			}
			else
			{//判断结束时间 
				if(min1_e<(minute2+20)&&min1_e>(minute-20)||(min1_e-min1_b)<60||(min1_e-min1_b)>180){
					printf("您的结束时间设置不合理！\n");
					fclose(M_Message);
					return 0;//不合法返回0
				}
			}
		}			
	}
	fclose(M_Message);
	return 1;//合法返回1 
}

int A_session_room_valid(char room[])//判断添加片场时间是否合法
{
	FILE * S_Message;//所有影厅的信息
	struct ScreenMessage SM1;
	
	if((S_Message=fopen("ScreenMessage.txt","r"))!=NULL)
	{
		while(fscanf(S_Message,"%s %s %s",SM1.cinema,SM1.room,SM1.type)!=EOF)
		{
			if(strcmp(SM1.cinema,A_quanju.Cinema) == 0)
			if(strcmp(SM1.room,room) == 0)
			{
				fclose(S_Message);
				return 0;//返回值为0代表输入正确 
			}	
		}
		fclose(S_Message);
	}
	else
	{
		printf("文本(ScreenMessage.txt)打开错误\n");
		exit(1);
	}
	printf("您未开设该影厅！\n");
	getchar();
	getchar(); 
	fclose(S_Message);
	return 1;
}

int A_session()//管理员场次管理主函数 
{
	char a[20];
	int choice = 0;
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("您已经成功进入场次管理系统！\n");
		printf("请输入您的选择:\n"
 			 "场次查询       请输入 1\n"  //场次查询 
 			 "添加场次       请输入 2\n"  //场次管理 
 			 "返回           请输入 3\n"  //返回 
  			 "退出           请输入 4\n");//退出
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//判断用户输入是否为数字 
			continue;
		choice = atoi(a);
		switch(choice)
		{
    			case 1://场次查询
			    	A_session_check();
			    	printf("按任意键继续\n");
			    	fflush(stdin);
			    	getchar();
			    	break;
      		case 2://场次添加 
				A_session_add();  
				printf("按任意键继续\n");
			    	fflush(stdin);
			    	getchar();
				break;
       		case 3:	return 1;//返回 
        		case 4:	return 0;//退出 
        		default:	break;
    	 	} 	
	}	  	
}

void A_session_check()//管理员场次查询
{
	struct MovieMessage MM;
	FILE * M_Message;//所有场次的信息
	char a[20];	 //获取用户选择 
	int choice=0;//保存用户选择 
	
	//获取用户选择
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("请输入您想要查看的场次：\n");
		printf("1-20号厅       input 1-20\n"  
 			 "全部场次       input 0\n"); 
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//判断用户输入是否为数字 
			continue;
		choice = atoi(a);	
		if(choice<0||choice>20)//判断用户输入是否越界
			continue;
		break;
	}
	//打印表头 
	system("cls");
	if(choice == 0)
		printf("\n 这里是全部影厅的场次信息：\n");
	else
		printf("\n 这里是第%d影厅的场次信息：\n",choice);
	printf("场次号|电影名|影厅号|开场日期时间|结束日期时间|影片类型|播放语言|剩余票数|总票数|售出率|票价\n");
	//检索文件并打印内容 
	if((M_Message=fopen("MovieMessage.txt","r"))!=NULL)
	{
		while(fscanf(M_Message,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f", 
		MM.movieID,MM.cinema,MM.moviename,MM.room,MM.beginTime,
		MM.endTime,MM.type,MM.language,&MM.restticket,&MM.totalticket,
		&MM.ratio,&MM.fee)!=EOF)
		{
			if(strcmp(MM.cinema,A_quanju.Cinema) == 0)
			{
				if(choice == 0){//管理员查看全部场次 
					if(strcmp(MM.cinema,A_quanju.Cinema) == 0)
					printf("%-3s %-9s  %-4s %s   %-13s %-6s %s    %-3d    %-3d    %.2f%% %.2f\n",
					MM.movieID,MM.moviename,MM.room,MM.beginTime,
					MM.endTime,MM.type,MM.language,MM.restticket,MM.totalticket,
					MM.ratio*100,MM.fee);	
				}
				else
				{//管理员查看对应场次 
					if(strcmp(MM.cinema,A_quanju.Cinema) == 0)
						if(choice == atoi(MM.room))
						printf("%-3s %-9s  %-4s %s   %-13s %-6s %s    %-3d    %-3d    %.2f%% %.2f\n",
						MM.movieID,MM.moviename,MM.room,MM.beginTime,
						MM.endTime,MM.type,MM.language,MM.restticket,MM.totalticket,
						MM.ratio*100,MM.fee);	
				}
			}	
		}
	}
	else
	{
		printf("ScreenMessage.txt打开错误\n");
		system("pause");
	}	
}

//*************************************影厅添加和查看**************************************
int A_screen()	//影厅管理主函数 
{
	char a[20];
	int choice = 0;
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("You have entered screen management system!\n");
		printf("请输入您的选择:\n"
 			 "影厅查询:查询所有开设的影厅信息 请输入 1\n"  //影厅查询 
 			 "添加影厅:添加一个新的影厅       请输入 2\n"  //影厅管理 
 			 "返回                            请输入 3\n"  //返回 
  			 "退出                            请输入 4\n");//退出
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//判断输入是否为数字 
			continue;
		choice = atoi(a);
		switch(choice)
		{
    			case 1:
				A_screen_check();  
				printf("按任意键继续\n");
				fflush(stdin);
				getchar();
				break;//影厅查询
      		case 2:
				A_screen_add()  ;
				printf("按任意键继续\n");
				fflush(stdin);
				getchar();
				break;//影厅管理
       		case 3:
			 	return 1;//返回 
        		case 4:
			  	return 0;//退出 
        		default:
			  	break;
    	 	} 	
	}	  	
}	

void A_screen_check()	//管理员影厅查询
{
	struct ScreenMessage SM;
	FILE * S_Message;//所有影厅的信息
	
	if((S_Message=fopen("ScreenMessage.txt","r"))!=NULL)
	{
		printf("    影厅号   |  影厅类型 \n");
		while(fscanf(S_Message,"%s %s %s",SM.cinema,SM.room,SM.type)!=EOF)
		{
			if(strcmp(A_quanju.Cinema,SM.cinema) == 0)
				printf("      %s\t\t%s\n",SM.room,SM.type);
		}
	}
	else
	{
		printf("ScreenMessage.txt文本打开错误\n");
		system("pause");
	}
	fclose(S_Message);
}

int A_screen_add()//管理员影厅管理
{
	int choice1=0,choice2=0;
	char a[20],b[20];
	char Type[20] = {'\0'};
	FILE * S_Message;//所有影厅的信息
	while(1)//获得影厅号 
	{
		system("cls");
		printf("\n   您已开设一下影厅：\n");
		A_screen_check();//打印一遍影厅信息 
		printf("\n请各根据提示输入增添影厅的信息：\n"
			 "注意：影厅一旦增加不能更改！\n"
			 "您可以在未完成注册时输入 0 撤销对影厅的增加！\n\n");
 		printf("请您输入 要新开设影厅的编号 (不要超过 20)\n");
 		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//判断输入是否为数字
			continue;
		choice1 = atoi(a);
		if(A_screen_add_valid(choice1) ==0)//判断影厅是否已经存在 
			continue;
		if(choice1==0){//输入0时取消操作 
			return 0;
		}else if(choice1<0||choice1>20){//判断输入是否越界 
			continue;
		}else{
			printf("好的！您添加的是 %d号厅\n",choice1);
			break;
		}
	}
	while(1) //获得影厅类型 
	{
		system("cls");
		printf("\n   您已开设一下影厅：\n");
		A_screen_check();//打印一遍影厅信息 
	 	printf("\n请各根据提示输入增添影厅的信息：\n"
			 "注意：影厅一旦增加不能更改！\n"
			 "您可以在未完成注册时输入 0 撤销对影厅的增加！\n\n");
		printf("请输入厅的类型（Imax/2D/3D/4D）\n");
 		printf(" Imax 输入 1\n"   
 			 " 2D   输入 2\n"   
 			 " 3D   输入 3\n"  
  			 " 4D   输入 4\n");
		fflush(stdin);
		scanf("%s",b);
		if(judge_num(b)!=0)//判断输入是否为数字
			continue;
		choice2 = atoi(b);
		switch(choice2)
  		{
    		case 0:return 0;
    		case 1:strcpy(Type,"Imax");break;
      		case 2:strcpy(Type,"2D");  break;
      		case 3:strcpy(Type,"3D");  break;
      		case 4:strcpy(Type,"4D");  break;
        	default:continue;
 		}
		break;	
	}
	//添加影厅信息
	S_Message=fopen("ScreenMessage.txt","a");
	fprintf(S_Message,"%s  %d  %s\n",A_quanju.Cinema,choice1,Type);
	printf("已成功添加该影厅！\n");
	fclose(S_Message); 
	return 1;
}
 
int A_screen_add_valid(int room)//检查管理员添加的影厅是否合理 
{
	FILE * S_Message;//所有影厅的信息
	struct ScreenMessage SM;
	int a=0;
	S_Message=fopen("ScreenMessage.txt","r");
	while(fscanf(S_Message,"%s %s %s",SM.cinema,SM.room,SM.type)!=EOF)
	{
		if(strcmp(A_quanju.Cinema,SM.cinema) == 0){
			a = atoi(SM.room);
			if(room == a)
				return 0;	
		}
	}
	return 1;	
}

//*************************************用户操作**************************************

//*************************************用户个人信息查询及修改及充值****************************
void U_information(char id1[20])
{
	char id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20];
	double money,c;
	int b=0,a=0;
	char choice[20];
	printf("\n如果你想查看你的基本信息，请输入1\n");
	printf("如果你想更改你的基本信息，请输入2\n");
	printf("如果你想充值，请输入3\n ");
	printf("如果你想返回上一界面，请输入任意值\n");
	while(1)
	{
		fflush(stdin);
		scanf("%s",choice);
		if(judge_num(choice)!=0)
			continue; 
		b = atoi(choice);
		break;
	} 
	switch(b)
	{
		case 1://用户查看基本信息 
		{
			FILE *UFile;
			UFile=fopen("users.txt","r");
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF||a==0)
			{
				if(strcmp(id1,id2)==0)
				{
					a=1;
					printf("id          name        sex   tele        money        mail \n");
					printf("%-12s%-12s%-6s%-12s%lf%-12s",id1,name,sex,tele,money,mail);
				}
			}
			fclose(UFile);
			break;
		}
		case 2://用户更改信息 
		{
			U_change(id1);
			break;
		}
		case 3://充值
		{ 
			FILE *UFile,*fp;
			UFile=fopen("users.txt","r");
			fp=fopen("user1.txt","w");
			while(1)
			{
				printf("\n请输入你想充值的金额(充值可赠送充值金额的10%%)： ");
				fflush(stdin);
				scanf("%lf",&c);
				if(c<=0)
					continue;
				break;
			} 
			c=1.1*c;
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
			{
				if(strcmp(id1,id2)==0)
			 	{
			 		money+=c;
			 		fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
				else
				{
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
			}//将新的信息写入一个新的文件 
			fclose(UFile);
			fclose(fp);
			U_modify();
			break;
		} 
		default:
			denglu();
			break;
	}
}

void U_change(char id1[20])//用户信息更改 
{
	FILE *UFile,*fp,*forder;
	UFile=fopen("users.txt","r");
	fp=fopen("user1.txt","w");
	int a=0,b=0,i=0;
	double money;
	char id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20];
	int orderNum,row[20],line[20],restticket,totalticket;
	float fee,ratio;
	char cinema[20],movie1[20],movie2[20],room[20],begintime[20],endtime[20],type[20],language[20];
	char choice[20];//获得用户选择 
	
	printf("\n如果你想更改你的姓名，请输入1\n");
	printf("如果你想更改你的性别，请输入2\n");
	printf("如果你想更改你的电话，请输入3\n");
	printf("如果你想更改你的邮箱，请输入4\n");
	printf("如果你想更改你的密码，请输入5\n");
	printf("如果您想注销您的ID，请输入6\n");
	printf("如果你想返回上一界面，请输入任意值\n"); 
	while(1)
	{
		fflush(stdin);
		scanf("%s",choice);
		if(judge_num(choice)!=0)
			continue; 
		a = atoi(choice);
		break;
	} 
	switch(a)
	{	
		case 1:
		{
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
			{
				if(strcmp(id1,id2)==0)
  				{	
		   			printf("\n请输入您的新姓名：\n");//输入姓名 
   			    		scanf("%s",name);
	 				fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);	
	   			}
			 	else
	 			{
			 		fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
		 	} 
   		    	fclose(UFile);
			fclose(fp);
			U_modify();	break;
		}
		case 2:
		{
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
			{
				if(strcmp(id1,id2)==0)
 				{
			 		printf("\n请输入您的新性别：\n");//输入性别 
   					scanf("%s",sex);
 					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail); 
		 		}
	 			else
	 				fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
			}
			fclose(UFile);
			fclose(fp);
			U_modify();	
			break;				
		}
		case 3:
		{
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
 			{
  				if(strcmp(id1,id2)==0)
				{  
					while ( b!=1 )//输入并验证电话 
         				{
            				printf("请输入您的电话号码:\n");
               				scanf("%s",U_quanju.Tele);
                            		if (U_quanju.Tele[11]!='\0') {printf("你的电话号码不合法！请重新输入：\n"); b=0;}	
 						else b=1;
						for (i=0;i<11;i++)
							if (U_quanju.Tele[i]<'0'||U_quanju.Tele[i]>'9') 
							{
								printf("您的电话号码不合法，请重新输入！\n");
								b=0;
								break;
							}                      
					}       
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,U_quanju.Tele,code2,money,mail);               
 				}
 				else
 				{
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,U_quanju.Tele,code2,money,mail);
  				}
   		    	}
   		    	fclose(UFile);
			fclose(fp);
			U_modify();
			break;			      		
		}
		case 4:
		{
  			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
 			{
			 	if(strcmp(id1,id2)==0)
				{
					youxiangcheckU();
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,U_quanju.Mail);
				}
				else
				{
				fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
 			}	
			fclose(UFile);
			fclose(fp);
			U_modify();
			break;
		}
		case 5:
		{
			int x=0;
			
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)	
			{
			  	if(strcmp(id1,id2)==0)
			  	{
			  		codecheck(x);
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,U_quanju.Code,money,mail);	
				}
				else
			   	{
			   		fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
			}	
			fclose(UFile);
			fclose(fp);
			U_modify();break;
		}
		case 6:
		{
			while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
			{
				if(strcmp(id1,id2)!=0)
				{
					fprintf(fp,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
				}
			}
        		fclose(UFile);
			fclose(fp);
			U_modify();
	    		fp=fopen("OrderMessage.txt","r");
         		forder=fopen("order1.txt","w");
    			while(fscanf(fp,"%d  %s  %s  %s  %s  %d  %d  %s  %s  %s  %s  %lf  %d  %d  %lf",&orderNum,id2,cinema,movie1,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)
    			{
    				if(strcmp(id1,id2)!=0)
    				{
    					fprintf(fp,"%d  %s  %s  %s  %s  %d  %d  %s  %s  %s  %s  %lf  %d  %d  %lf\n",orderNum,id2,cinema,movie1,room,row,line,begintime,endtime,type,language,ratio,restticket,totalticket,fee);	
				}
			}
			fclose(fp);
			fclose(forder);
			fp=fopen("OrderMessage.txt","w");
        		forder=fopen("order1.txt","r");
        		while(fscanf(forder,"%d  %s  %s  %s  %s  %d  %d  %s  %s  %s  %s  %lf  %d  %d  %lf",&orderNum,id2,cinema,movie1,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)
        			fprintf(fp,"%d  %s  %s  %s  %s  %d  %d  %s  %s  %s  %s  %lf  %d  %d  %lf\n",orderNum,id2,cinema,movie1,room,row,line,begintime,endtime,type,language,ratio,restticket,totalticket,fee);
        		fclose(fp);
			fclose(forder);
			break;
		} 
		default:
			U_information(id1);
			break;
	}
}

//*************************************用户订单查询**************************************
void U_order(char id1[20])//订单查询 
{
	int a,b=0;
	FILE *fp10;
	char seat[20];
	int i,j;
	int row1,line1;
	int restticket,totalticket;
	float fee,ratio,money;
	MovieMessage quire;
	char row[3],line[3],orderNum1[20],orderNum2[20],id2[20],cinema[20],movie[20],room[20],begintime[20],endtime[20],type[20],language[20],movieid[20];
	
	printf("\n如果你想查询你的订单，请输入1\n");
	printf("如果你想取消订单，请输入2\n");
	printf("如果你想返回上一界面，请输入任意值\n");
	scanf("%d",&a); 
	switch(a)
	{
		case 1://查看订单信息 
			{
            FILE *fp;
	        fp=fopen("OrderMessage.txt","r");
			printf("Your orders are\n");
	         printf("订单号    用户ID  影片编号  电影院   电影名   影厅   行号  列号  开场时间         散场时间     影片类型  语言    票价\n");
				while(fscanf(fp,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)	
				{
					if(strcmp(id1,id2)==0)
			{
		         printf("%s  %s     %s    %s  %s  %s      %s    %s   %s     %s     %s   %s  %.2f\n",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,fee);
			}
			}
			fclose(fp);
			break;
			}
		case 2://取消订单 
			{
				float a;
                FILE *fp,*forder;
                fp=fopen("OrderMessage.txt","r");
                forder=fopen("order1.txt","w");
				printf("请输入您想要删除订单的订单号:\n");
				scanf("%s",orderNum1);
				while(fscanf(fp,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)
				{
					if(strcmp(id1,id2)==0)
					{
						if(strcmp(orderNum1,orderNum2)==0)
						{
							row1=atoi(row);
							line1=atoi(line);
						}
					}
				}
				rewind(fp);
				while(fscanf(fp,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)
				{
					if(strcmp(id1,id2)==0)
					{
						if(strcmp(orderNum1,orderNum2)!=0)
						{
							fprintf(forder,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,ratio,restticket,totalticket,fee);
						}
						else
						a=fee;
					}
				}
				fclose(fp);
				fclose(forder);
				fp=fopen("OrderMessage.txt","w");
                forder=fopen("order1.txt","r");
                while(fscanf(forder,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,&ratio,&restticket,&totalticket,&fee)!=EOF)
            	fprintf(fp,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",orderNum2,id2,movieid,cinema,movie,room,row,line,begintime,endtime,type,language,ratio,restticket,totalticket,fee);
				fclose(fp);
				fclose(forder);
				FILE *UFile,*fu;
				char id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20];
		        UFile=fopen("users.txt","r");
	           fu=fopen("user1.txt","w");
				while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
		      {
		 	if(strcmp(id1,id2)==0)
		 	{
		 		money+=a;
		 		fprintf(fu,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);	
			 }
			 else
			 {
			 	fprintf(fu,"%s  %s  %s  %s  %s  %lf  %s\n",id2,name,sex,tele,code2,money,mail);
			 }
		      }//将新的信息写入一个新的文件 
		    fclose(UFile);
		    fclose(fu);
		    U_modify();
		    FILE *fmovie,*fa;
		    fmovie=fopen("MovieMessage.txt","r");
		    fa=fopen("MovieMessage1.txt","w");
		    while(fscanf(fmovie,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee)!=EOF)
		    {
		    		if(strcmp(quire.movieID,movieid)!=0)
		    		{
		    			fprintf(fa,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					}
					else
					{
						quire.restticket=quire.restticket+1;
						quire.ratio=(quire.totalticket-quire.restticket)/quire.totalticket;
						fprintf(fa,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					}
			}//将新的信息写入一个新的文件
			fclose(fmovie);
		    fclose(fa);
		    fmovie=fopen("MovieMessage.txt","w");
		    fa=fopen("MovieMessage1.txt","r");
		    while(fscanf(fa,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee)!=EOF)
		    fprintf(fmovie,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
		    fclose(fmovie);
		    fclose(fa);
			sprintf(seat, "%s.txt", movieid);		
			if(type=="Imax")
			{
				fp10=fopen(seat,"r");
				for(i=0;i<10;i++)
   				{	
					for(j=0;j<15;j++)
    				{
    					fscanf(fp10,"%d",&arr150[i][j]);
        			}
    				fscanf(fp10,"\n");
 				}
				fclose(fp10); 			
				arr150[row1-1][line1-1]=0;
				fp10=fopen(seat,"w");
				for(i=0;i<10;i++)
				{
					for(j=0;j<15;j++)
					{
						fprintf(fp10,"%d ",arr150[i][j]);
					}
					fprintf(fp10,"\n");
				}
				fclose(fp10);
			}
			else
			{
				fp10=fopen(seat,"r");
				for(i=0;i<10;i++)
   				{	
					for(j=0;j<10;j++)
    				{
    					fscanf(fp10,"%d",&arr100[i][j]);
        			}
    				fscanf(fp10,"\n");
 				}
				fclose(fp10); 			
				arr100[row1-1][line1-1]=0;
				fp10=fopen(seat,"w");
				for(i=0;i<10;i++)
				{
					for(j=0;j<10;j++)
					{
						fprintf(fp10,"%d ",arr100[i][j]);
					}
					fprintf(fp10,"\n");
				}
				fclose(fp10);
			}		
			break;	
			}
			default:
			U_information(id1);
            break;
	}
}
//***********************************电影查询+购票******************************
void U_movie()
{	
	userQueryMenu();
} 
//**************按照时间排序********************
void rangetime(int choice)//按照时间排序 
	{
		struct MovieMessage time_total[500];//声明一个结构体数组 
		int n=0;//需要排序场次总数 
		FILE *fp6;//读写temp%d.txt文件 
		struct MovieMessage quire;//表示单个场次信息 
		char filename[20];
		
		system("cls");//清屏 
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
		//按时间从近到远排序
        int i; //一次循环 
        int j;//二次循环 
        struct MovieMessage t; //中间值  
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
       	   	printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
			for(i=0;i<n;i++)
		    {
		     	printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",time_total[i].movieID,time_total[i].cinema,time_total[i].moviename,
			    time_total[i].room,time_total[i].beginTime,time_total[i].endTime,time_total[i].type,time_total[i].language,
			    time_total[i].restticket,
			    time_total[i].totalticket,
			    time_total[i].ratio,time_total[i].fee);
		    }
		   fclose(fp6);
}
//*******************按票价升序排序**********************
void rangefeein(int choice)//按票价升序排序 
{
	    struct MovieMessage fee_total[500];//声明一个结构体数组 
		int n=0;//需要排序的总场次数 
		FILE *fp6;//读写temp&d.txt文件 
		struct MovieMessage quire;//表示单个场次信息 
		char filename[20];
		
		system("cls");//清屏 
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
		//升序排序
        int i; //一次循环 
        int j; //二次循环 
        struct MovieMessage t; //中间值
		 
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
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		for(int i=0;i<n;i++)
		{
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
			    fee_total[i].room,fee_total[i].beginTime,fee_total[i].endTime,fee_total[i].type,fee_total[i].language,
			    fee_total[i].restticket,
			    fee_total[i].totalticket,
			    fee_total[i].ratio,fee_total[i].fee);
		}
		fclose(fp6);
}
//**********************按票价降序排序*************************
void rangefeede(int choice)//按票价降序排序 
{
 
	    struct MovieMessage fee_total[500];//声明一个结构体数组 
		int n=0;//需要排序的总场次数 
		FILE *fp6;//读写temp&d.txt文件
		struct MovieMessage quire;//表示单个场次信息
		char filename[20];
		
		system("cls");//清屏 
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
		//降序排序 
        int i; //一次循环 
        int j; //二次循环 
        struct MovieMessage t;//中间值  
        
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
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		for(int i=0;i<n;i++)
		{
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
			    fee_total[i].room,fee_total[i].beginTime,fee_total[i].endTime,fee_total[i].type,fee_total[i].language,
			    fee_total[i].restticket,
			    fee_total[i].totalticket,
			    fee_total[i].ratio,fee_total[i].fee);
		}
		fclose(fp6);   
}
//**************************按余票数升序排序***********************
void rangerestin(int choice)//按余票数升序排序 
{
	    struct MovieMessage rest_total[500];//声明一个结构体数组 
		int n=0;//需要排序的总场次数 
		FILE *fp6;//读写temp&d.txt文件
		struct MovieMessage quire;//表示单个场次信息
		char filename[20];
		
		system("cls");//清屏  
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
		//升序排序
        int i; //一次循环 
        int j;//二次循环 
        struct MovieMessage t;//中间值  
        
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
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		for(int i=0;i<n;i++)
		{
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
			rest_total[i].room,rest_total[i].beginTime,rest_total[i].endTime,rest_total[i].type,rest_total[i].language,
			rest_total[i].restticket,
			rest_total[i].totalticket,
			rest_total[i].ratio,rest_total[i].fee);
		}
		fclose(fp6);     
}
//*****************************按余票数降序排序***********************
void rangerestde(int choice)//按余票数降序排序 
{
	    struct MovieMessage rest_total[500];//声明一个结构的数组 
		int n=0;//需要排序的总场次数 
		FILE *fp6;//读写temp&d.txt文件
		struct MovieMessage quire;//表示单个场次信息
		char filename[20];
		
		system("cls");//清屏 
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
		//降序排序 
        int i;//一次循环 
        int j;//二次循环 
        struct MovieMessage t;//中间值
		  
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
 
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
			for(int i=0;i<n;i++)
		{
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
   			rest_total[i].room,rest_total[i].beginTime,rest_total[i].endTime,rest_total[i].type,rest_total[i].language,
			rest_total[i].restticket,
			rest_total[i].totalticket,
			rest_total[i].ratio,rest_total[i].fee);
		}
		fclose(fp6);   
}

//**************************电影信息排序界面***********************
void paixujiemian(int choice)//电影信息排序界面
{
	int op=0;//选择 
    int f=1;//循环 
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
			case 1: rangetime(choice);//按时间 
					xuanpianchang();//用户选择场次 
					break;
			case 2: rangefeein(choice);//按票价升序 
					xuanpianchang();//用户选择场次 
					break;
			case 3: rangefeede(choice);//按票价降序 
					xuanpianchang();//用户选择场次 
					break;
			case 4: rangerestin(choice);//按余票数升序 
					xuanpianchang();//用户选择场次 
					break;
			case 5: rangerestde(choice);//按余票数降序 
					xuanpianchang();//用户选择场次 
					break;
			case 6: f=0;
					break;
			default:break;							
		}
    }
}

//********************************购票部分******************************* 

//**************************用户选片场****************
void xuanpianchang()//用户选片场
{
	FILE *fp1;
	FILE *fp2;
	FILE *fp6;
	char movieID[5]={'/0'};
	struct Order A_kan;
	struct MovieMessage quire;
	int count_[5]={0};
	int f=1,q=1,i=0;
 	printf("\n\n");
	printf("\t\t**************************************************\n");
	printf("\t\t*                                                *\n");
	printf("\t\t*       请选择您想观看的片场（输入影片编号）     *\n");
	printf("\t\t*                                                *\n");        
	printf("\t\t*       温馨提示：购买午夜场可以半价优惠呦!      *\n");        
	printf("\t\t*                                                *\n");        
 	printf("\t\t**************************************************\n");		   
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
		i++;
	}
	rewind(fp6);
	fclose(fp6);
	while(1)
	{
		fflush(stdin);
		scanf("%s",movieID);//输入的片场编号
		if(judge_num(movieID)!=0)
 			continue;
 		if(atoi(movieID)<0 || atoi(movieID)>i)
		 	continue;	
		break;
	}
	
  	fp1=fopen("OrderMessage.txt","r");
	while(fscanf(fp1,"%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %f  %d  %d  %f\n",A_kan.orderNum,
	A_kan.userID,A_kan.movieID,A_kan.cinema,A_kan.movie,A_kan.room,A_kan.row,A_kan.line,
	A_kan.beginTime,A_kan.endTime,A_kan.type,A_kan.language,&A_kan.ratio,
	&A_kan.restticket,&A_kan.totalticket,&A_kan.fee)!=EOF)
	{
		if(strcmp(U_quanju.ID,A_kan.userID)==0 && strcmp(movieID,A_kan.movieID)==0)	
  		q=0;
	}
	fclose(fp1);//关闭文件 
	 if(q==0)
 	{
 		printf("提示：您已购买过该场次的影票\n");
  		system("pause");
 	}
 	buy(movieID);
} 

//**************************顾客电影查询界面************************ 
void userQueryMenu()//顾客电影查询界面 
{
	int f=1;//循环 
	
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
		printf("\t\t\t\t6. 热门场次推荐\n\n");
		printf("\t\t\t\t7. 返回\n\n"); 
		printf("\t\t\t请选择您的查询方式：");
		int choice;//选择
		fflush(stdin);
        scanf("%d",&choice);
        getchar();
		switch(choice)
		{
		case 1:
				MovieNamequire(choice);//按照影片名字搜索 
				break;
			case 2:
				Doublequire(choice);//按照影片名+影院名搜索 
				break;
			case 3:
				Languagequire(choice);//按照语言类型搜索 
				break;
			case 4:
				MovieTypequire(choice);//按照影片放映类型搜索 
				break;
			case 5:
				Cinemaquire(choice);//按照电影院搜索 
				break;
			case 6:
				MovieRecom();//热门场次推荐 
				break;
			case 7:
				denglu();//返回到登陆界面 
				break;
			default:
				break;
		}
	}
}
//*****************************按照影片名查询******************** 
void MovieNamequire(int choice)//按照影片名查询 
 
{
	FILE *fp6;//读写MovieMessagew.txt文件 
	FILE *temp1;//读写temp1.txt文件 
	struct MovieMessage quire;//表示单场电影信息 
	char typeinmoviename[10]; //用户输入电影名称 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *              1.影片名查询                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *          速度与激情      复仇者联盟      *\n");
		printf("                 *          银河补习班      海底总动员      *\n");
		printf("                 *          夏洛特烦恼      西红柿首富      *\n");
		printf("                 *          美女与野兽                      *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片名：");
		scanf("%s",typeinmoviename);
		if(strcmp(typeinmoviename,"速度与激情")!=0 &&  strcmp(typeinmoviename,"复仇者联盟")!=0 &&
		strcmp(typeinmoviename,"银河补习班")!=0 &&  strcmp(typeinmoviename,"海底总动员")!=0 &&
		strcmp(typeinmoviename,"夏洛特烦恼")!=0 &&  strcmp(typeinmoviename,"西红柿首富")!=0 &&
		strcmp(typeinmoviename,"美女与野兽")!=0)
		{
		printf("请您输入正确影片名\n"); 
		system("pause");
		userQueryMenu();
		}
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp1=fopen("temp1.txt","w");//把符合筛选条件的内容放入一个新文件 
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
	    if(strcmp(typeinmoviename,quire.moviename)==0)
			{
			fprintf(temp1,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%g\t%g\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);

			}
		}
		fclose(temp1);		
	  	rewind(fp6);	  	
		fclose(fp6);
		system("pause");
		paixujiemian(choice);		
}
//***************************按照影片语言类型查询*********************** 
void Languagequire(int choice)//按照影片语言类型查询 

{
	FILE *fp6;//读写MovieMessagew.txt文件 
	FILE *temp3;//读写temp3.txt文件 
	struct MovieMessage quire;//表示单场电影信息 
	char typeinlanguage[10]; //用户输入语言类型 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *               3.语言查询                 *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             	  Chinese                   *\n");
		printf("                 *                                          *\n");
		printf("                 *             	  English                   *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片语言类型：");
		scanf("%s",typeinlanguage);
		if(strcmp(typeinlanguage,"Chinese")!=0 &&  strcmp(typeinlanguage,"English")!=0)
		{
		printf("请您输入正确语言类型\n"); 
		system("pause");
		userQueryMenu();
		}
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
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
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			}
	  	rewind(fp6);
		fclose(fp6);
		fclose(temp3);
	 	paixujiemian(choice);
}
//******************************按照影片名+影院名查询********************** 
void Doublequire(int choice)//按照影片名+影院名查询 
 
{
	FILE *fp6;//读写MovieMessagew.txt文件 
	FILE *temp2;//读写temp2.txt文件 
	struct MovieMessage quire;//表示单场电影信息 
	char typeinmoviename[10]; //用户输入电影名称
	char typeincinema[10]; //用户输入影院名称 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *            2.影片名+影院名查询           *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");
		printf("                 *                                          *\n");
		printf("                 *          速度与激情      复仇者联盟      *\n");
		printf("                 *          银河补习班      海底总动员      *\n");
		printf("                 *          夏洛特烦恼      西红柿首富      *\n");
		printf("                 *          美女与野兽                      *\n");
		printf("                 *                                          *\n");
		printf("                 *      影院：  Houde    Boxue    Mashi     *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的影片名：");
		scanf("%s",typeinmoviename);
		printf("请输入您感兴趣的影院名：");
		scanf("%s",typeincinema);
		if(strcmp(typeinmoviename,"速度与激情")!=0 &&  strcmp(typeinmoviename,"复仇者联盟")!=0 &&
		strcmp(typeinmoviename,"银河补习班")!=0 &&  strcmp(typeinmoviename,"海底总动员")!=0 &&
		strcmp(typeinmoviename,"夏洛特烦恼")!=0 &&  strcmp(typeinmoviename,"西红柿首富")!=0 &&
		strcmp(typeinmoviename,"美女与野兽")!=0 )
		{
			printf("请您输入正确影片名\n");
			system("pause");
			userQueryMenu();
		}
		if(strcmp(typeincinema,"Houde")!=0 &&  strcmp(typeincinema,"Boxue")!=0 &&
		strcmp(typeincinema,"Mashi")!=0)
		{
			printf("请您输入正确的影院名");
			system("pause");
			userQueryMenu();
		}
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
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
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp2);		
	 	paixujiemian(choice);
}
//*************************按照放映影厅类型查询********************** 
void MovieTypequire(int choice)//按照放映影厅类型查询 
 
{
	FILE *fp6;//读写MovieMessagew.txt文件 
	FILE *temp4;//读写temp4.txt文件 
	struct MovieMessage quire;//表示单场电影信息 
	char typeinmovietype[10]; //用户输入影厅放映类型 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *            4.放映影厅类型查询            *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *            2D   3D    4D   Imax          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请输入您感兴趣的放映影厅类型：");
		scanf("%s",typeinmovietype);
		if(strcmp(typeinmovietype,"2D")!=0 &&  strcmp(typeinmovietype,"3D")!=0 &&
		strcmp(typeinmovietype,"4D")!=0 &&  strcmp(typeinmovietype,"Imax"))
		{
		printf("请输入正确的放映影厅类型"); 
		system("pause");
		userQueryMenu();
		}
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
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
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp4);		
	 	paixujiemian(choice);
}
//*************************按照影院名查询******************** 
void Cinemaquire(int choice)//按照影院名查询 
 
{
	FILE *fp6;//读写MovieMessagew.txt文件 
	FILE *temp5;//读写temp5.txt文件 
	struct MovieMessage quire;//表示单场电影信息 
	char typeincinema[10]; //用户输入语言类型 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *              5.电影院查询                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             Houde   Boxue   Mashi        *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("请选择您感兴趣的影院名：");
		scanf("%s",typeincinema);
		if(strcmp(typeincinema,"Houde")!=0 &&  strcmp(typeincinema,"Boxue")!=0 &&
		strcmp(typeincinema,"Mashi")!=0)
		{
			printf("请输入正确的电影院类型");
			system("pause");
			userQueryMenu();
		}
		printf("|场次编号 |电影院    |影片名    |厅号  |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
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
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			}
	  	rewind(fp6);
		fclose(fp6);	
		fclose(temp5);		
	 	paixujiemian(choice);
}
//*************************热门场次推荐******************** 
void MovieRecom()//热门场次推荐 

{
	FILE *tj;//读写MovieMessage.txt文件 
	struct MovieMessage quire; //表示单场电影信息 
	
		system("cls");//清屏 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             顾客电影查询界面             *\n");
		printf("                 *                                          *\n");
		printf("                 *               热门场次推荐               *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("             *Mashi影院新开业 推荐选择IMAX影厅场次体验巨幕带来的视听盛宴*\n");
		printf("                 ********************************************\n");
		printf("|场次编号 |电影院  |影片名    |厅号    |开场时间       |散场时间    |影片类型  |语言   |余票数|总票数  |上座率  |票价 \n");
		tj=fopen("MovieMessage.txt","r");
		if(tj==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
	    while((fscanf(tj,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		{
	    if(strcmp("Imax",quire.type)==0&&strcmp("Boxue",quire.cinema)==0)//Boxue改为Mashi 
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
		}
	  	rewind(tj);
		fclose(tj);
		system("pause");
}
//*************************选择购票界面********************* 
void buy(char movieID[])//选择购票界面 
{	
	struct MovieMessage quire;
	int op=0;//初始化 
	int judge;//判断是否为Imax 
	int i;//扫描下一行 
    int f=1;//跳出循环的条件 
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
        fflush(stdin);//缓冲数据
        scanf("%d",&op);
        getchar();
        fp6=fopen("MovieMessage.txt","r");//打开文件 
		if(fp6==NULL)//判断文件是否存在 
		{
		printf("The file was not successfully opened.\n");
		exit(1);
		}
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(movieID,quire.movieID)==0)//寻找与用户输入相同影片编号的影片信息 
		{
			if(quire.totalticket==100)
			judge=100;
			else
			judge=150;
			i++;
		}
	  	rewind(fp6);//把光标移到最初 
		fclose(fp6);//关闭文件 
        switch(op)
		{
			case 1:	if(judge==100)
					chazuo100(movieID);//进入座位为10*10的厅 
					else
					chazuo150(movieID);//进入座位为10*15的厅 
					break;
			case 2: U_movie();
					//返回
					break;
			default: break;//防止用户随意输数						
		}
        
    }
}
//**************************查询10*10座位********************* 
void chazuo100(char movieID[])//查询10*10座位 
{
	char a[20]={'\0'};//获得用户输入 
	system("cls");//清屏 
	int i,j;//循环数 
	int goupiao;//用户购票数 
	char seat[20]; 
	sprintf(seat, "%s.txt", movieID);//使得生成的座位号文件名与影片编号相同 
	if((fp5 = fopen(seat,"r")) == NULL)//判断文件是否存在 
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");//扫描文件 
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
	for(i=0;i<10;i++)//把座位信息打在界面上以供用户查询选座 
	{
		for(j=0;j<10;j++)
		{
		printf("[%d] ",arr100[i][j]);
		}
	printf("\n");
	}
	printf("\n（若想取消购票，请输入0）");
	printf("\n请问您需要买的票数是:");
 	while(1)	//输入购票数
	{
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)
			continue; 
		goupiao = atoi(a);
		break;
	} 
 	maipiao100(goupiao,movieID);//传递购票数和用户选择的影片编号 
}
//***************************查询10*15座位******************** 
void chazuo150(char movieID[])//查询10*15座位 
{
	char a[20]={'\0'};//获得用户输入 
	system("cls");//清屏 
	int i,j;//循环数 
	int goupiao;//用户购票数 
	char seat[20];
	sprintf(seat, "%s.txt", movieID);//使得生成的座位号文件名与影片编号相同 
	if((fp5 = fopen(seat,"r")) == NULL)//判断文件是个否存在 
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");//扫描文件 
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
	for(i=0;i<10;i++)//把座位信息打在界面上以供用户查询选座 
	{
		for(j=0;j<15;j++)
		{
		printf("[%d] ",arr150[i][j]);
		}
	printf("\n");
	}
	printf("\n（若想取消购票，请输入0）");
	printf("\n请问您需要买的票数是:");
 	while(1)	//输入购票数
	{
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)
			continue; 
		goupiao = atoi(a);
		break;
	} 
 	maipiao150(goupiao,movieID);//传递购票数和用户选择的影片编号
}
//**************************10*10座位推荐********************** 
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
//**********************10*15座位推荐*************************
void zuoweituijian150()//10*15座位推荐
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

//*****************************选择10*10座位购票************************* 
int maipiao100(int goupiao,char movieID[])//选择座位购票
{	
	FILE *fp3;
	FILE *fp4;
	FILE *fp2;
	FILE *fpc;
	int restticket;
	float fee,yue;//票价，票价*购票数，余额 
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
	if(fp6==NULL)//判断文件是否存在 
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strcmp(quire.movieID,movieID)==0)//比对用户选择的影片编号和信息中的影片编号 
		{restticket=quire.restticket;//找出该场电影的余票数 
		fee=quire.fee;//找出该场电影的票价 
		i++;}//扫描下一行 
	}
	rewind(fp6);
	fclose(fp6);//关闭文件 

	fpc=fopen("users.txt","r");
	while(fscanf(fpc,"%s  %s  %s  %s  %s  %lf  %s",user.ID,user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
	{
		if(strcmp(U_quanju.ID,user.ID)==0)
		yue=user.Money;//找出用户余额 
	}
	if(yue<(fee*goupiao))//比较用户余额和总票价 
	{
		printf("余额不足，请您充值后继续购买\n");		 
		system("pause");
		U_movie();
	} 

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
			case 1: zuoweituijian100();//进入10*10作为推荐系统 
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
				printf("不符合选座规范，按ESC键返回\n");//不能空一个空位选座 
	 			check=1;
			}
		 	else if(arr100[row[goupiao]-1][line[goupiao]+1]==1 && arr100[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("不符合选座规范，按ESC键返回\n");//不能空一个空位选座 
				check=1; 
			}
		}
		if(check == 0) //check=0成功购票 
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
				//先把用户信息复制到copyusers.txt里面	
				fp3=fopen("users.txt","r");//以只读的方式打开文件
				fp4=fopen("copyusers.txt","w");//以写的方式打开文件
				if(fp3==NULL)//判断文件是否为空 
				{
 					printf("The file was not successfully opened.\n");
		 			exit(1);
				}
				while(fscanf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					if(strcmp(user.ID,U_quanju.ID)==0)//找出该用户的个人信息 
					{
						user.Money=user.Money-fee;
					}
					fprintf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}				
				fclose(fp3);//关闭文件
				fclose(fp4);//关闭文件
				//把改过余额的的用户信息打回到users.txt 
				fp3=fopen("users.txt","w");
				fp4=fopen("copyusers.txt","r");
				while(fscanf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}
				fclose(fp3);//关闭文件
				fclose(fp4);//关闭文件
					//把MovieMessage.txt复制到copyMovieMessage.txt里面 
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
						}
						fprintf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					i++;
					}
					fclose(fp6);
					fclose(fp2);
					//把改好的余票信息再重新写回MovieMessage.txt里面 
					fp2=fopen("copyMovieMessage.txt","r");
					fp6=fopen("MovieMessage.txt","w");
					while((fscanf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						fprintf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),quire.fee);
					i++;
					}
					fclose(fp6);//关闭文件
					fclose(fp2);//关闭文件
					//生成总的订单 
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
						fprintf(fp7,"%s  %s  %s  %s  %s  ",U_quanju.ID,movieID,quire.cinema,quire.moviename,quire.room);
						if(row[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",row[goupiao]);
						if(line[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%s  %s  %s  %s  %5.2f  %d  %d  %.2f\n",quire.beginTime,quire.endTime,quire.type,
						quire.language,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),restticket,quire.totalticket,quire.fee);
						i++;
					}
		  			rewind(fp6);
					fclose(fp6);//关闭文件 
					fclose(fp7);//关闭文件 
			}
			printf("售票成功!按ESC键返回\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
//**************************选择10*15座位购票********************* 
int maipiao150(int goupiao,char movieID[])//选择座位购票
{	
	FILE *fp3;
	FILE *fp4;
	FILE *fp2;
	FILE *fpc;
	int restticket;//余票数 
	float fee,yue;//票价，余额 
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//检查是否选择错误 
	int i,j;//循环数 
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
		if(strcmp(quire.movieID,movieID)==0)//比对用户选择的影片编号和信息中的影片编号
		{restticket=quire.restticket;//找出余票数 
		fee=quire.fee;//找出票价 
		i++;}//扫描下一行 
	}
	rewind(fp6);//把光标移回文件开头 
	fclose(fp6);//关闭文件 
	fpc=fopen("users.txt","r");
	while(fscanf(fpc,"%s  %s  %s  %s  %s  %lf  %s",user.ID,user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
	{
		if(strcmp(U_quanju.ID,user.ID)==0)//找出该用户的个人信息 
		yue=user.Money;//找出该用户的余额 
	}
	if(yue<fee*goupiao)//比较用户余额和总票价
	{
		printf("余额不足，请您充值后继续购买");		 
		system("pause");
		U_movie();
	} 

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
				printf("不符合选座规范，按ESC键返回\n");//不能空一个空位选座 
	 			check=1;
			}
		 	else if(arr150[row[goupiao]-1][line[goupiao]+1]==1 && arr150[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("不符合选座规范，按ESC键返回\n");//不能空一个空位选座 
				check=1; 
			}
		}
		if(check == 0)//check=0购票成功 
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
				//先把用户信息复制到copyusers.txt里面，并修改余额 
				fp3=fopen("users.txt","r");//以只读的方式打开文件 
				fp4=fopen("copyusers.txt","w");//以写的方式打开文件 
				if(fp3==NULL)//判断文件是否为空 
				{
 					printf("The file was not successfully opened.\n");
		 			exit(1);
				}
				while(fscanf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					if(strcmp(user.ID,U_quanju.ID)==0)
					{
						user.Money=user.Money-fee;
					}
					fprintf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}				
				fclose(fp3);//关闭文件 
				fclose(fp4);//关闭文件 
				//把修改过的余额的个人信息写回到users.txt里 
				fp3=fopen("users.txt","w");//以写的方式打开文件
				fp4=fopen("copyusers.txt","r");//以只读的方式打开文件
				while(fscanf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}
				fclose(fp3);//关闭文件 
				fclose(fp4);//关闭文件 
				//把MovieMessage.txt复制到copyMovieMessage.txt里面 
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
							 quire.restticket--;//余票数减1 
						}
						fprintf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					i++;
					}
					fclose(fp6);//关闭文件 
					fclose(fp2);//关闭文件 
					//把修改过的copyMovieMessage.txt写回到MovieMessage.txt里面 
					fp2=fopen("copyMovieMessage.txt","r");
					fp6=fopen("MovieMessage.txt","w");
					while((fscanf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
					{
						fprintf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),quire.fee);
					i++;
					}
					fclose(fp6);//关闭文件 
					fclose(fp2);//关闭文件 
					//生成总订单 
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
						fprintf(fp7,"%s  %s  %s  %s  %s  ",U_quanju.ID,movieID,quire.cinema,quire.moviename,quire.room);
						if(row[goupiao]<10)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",row[goupiao]);
						if(line[goupiao]<15)
							fprintf(fp7,"0");
						fprintf(fp7,"%d  ",line[goupiao]);
						fprintf(fp7,"%s  %s  %s  %s  %5.2f  %d  %d  %.2f\n",quire.beginTime,quire.endTime,quire.type,
						quire.language,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),restticket,quire.totalticket,quire.fee);
						i++;
					}
		  			rewind(fp6);//把光标移回文件开始处 
					fclose(fp6);//关闭文件 
					fclose(fp7);//关闭文件 
			}
			printf("售票成功!按ESC键返回\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
//*************************************工具函数**************************************
int judge_num(char num[])//判断是否为数字 
{
	int valid = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(isdigit(num[i])) continue;
		else
		{
			printf("请输入数字！\n");
			valid = 1;
			break;
		}
	}
	return valid;//返回值为0，代表输入正确 
} 

int judge_kongge(char num[])//判断是否有空格 
{
	int valid = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(int(num[i]) == 32)
		{
			printf("请不要输入空格！\n");
			getchar();
			getchar();
			valid = 1;
			break;
		}
	}
	return valid;//返回值为0，代表输入正确 
}
void U_modify()//修改用户文件 
{
	FILE *UFile,*fp;
	UFile=fopen("users.txt","w");
	    fp=fopen("user1.txt","r");//声明两个文件，将修改后文件放入元文件 
	char id2[20],sex[10],tele[20],code2[20],mail[50],name[20];   
	double money; 
	    while(fscanf(fp,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
	    {
	    	fprintf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,money,mail);
		}
		fclose(UFile);
		 fclose(fp);
}
void A_modify()//修改用户文件 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","w");
 	fp=fopen("administrators1.txt","r");//声明两个文件，将修改后文件放入元文件 
	char id2[20],cinema[20],code2[20],mail[50],name[20];   
	    while(fscanf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
	    {
	    	fprintf(AFile,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);
		}
		fclose(AFile);
		 fclose(fp);
}
int chachong(char ID2[],int y)//注册时的信息查重 
{
	int c=0,d=0;
	FILE *fp;
	U_Message testU;
	A_Message testA;
	switch (y)
	{
		case 1:
			if((fp=fopen("administrators.txt","a+"))==NULL)
			{
				printf("Failed to open the file\n");
				return 0; 
			}
			while (fscanf(fp,"%s  %s  %s  %s  %s",testA.ID,testA.Name,testA.Cinema,testA.Code,testA.Mail) != EOF)
				c++;
			rewind(fp);
			while (fscanf(fp,"%s  %s  %s  %s  %s",testA.ID,testA.Name,testA.Cinema,testA.Code,testA.Mail) != EOF)
			{	
				if (strcmp(ID2,testA.ID) != 0)
					d++;
				if (d==c)
					break;
				else
				{
					printf("对不起，您的ID已经被注册，请重新输入新的ID：\n");
					return 0;
				}                   
   			}
			break;
		case 2:
			if((fp=fopen("users.txt","a+"))==NULL)
			{
				printf("Failed to open the file：users.txt\n");
				return 0;
			}
			while (fscanf(fp,"%s  %s  %s  %s  %s  %lf  %s",testU.ID,testU.Name,testU.Sex,testU.Tele,testU.Code,testU.Mail,&testU.Money) != EOF)
				c++;
			rewind(fp);
			while (fscanf(fp,"%s  %s  %s  %s  %s  %lf  %s",testU.ID,testU.Name,testU.Sex,testU.Tele,testU.Code,testU.Mail,&testU.Money) != EOF)
			{	
				if (strcmp(ID2,testU.ID) != 0)
					d++;
			}
				
				if (d==c)
					break;
					else
					{
						printf("对不起，您的ID已经被注册，请重新输入新的ID：\n");
						return 0;
					}                   	
			fclose(fp);
			break;	
	}
	return 1;
}

void showtime()
{
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	printf("当前时间：%d年%d月%d日%d时%d分%d秒\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
}
