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
struct Order //����
{
int orderNum; //������
char userID[20];//�û�ID
char movieID[20];//ӰƬ��� 
char cinema[20];//��ӰԺ
char movie[20];//��Ӱ�� 
char room[20];//Ӱ��
char row[20];//�к� 
char line[20];//�к� 
char beginTime[20];//����ʱ�� 
char endTime[20];//ɢ��ʱ��
char type[20];//ӰƬ���� 
char language[20];//����
float ratio;//������ 
int restticket;//��Ʊ��
int totalticket;//��Ʊ��
float fee;//Ʊ��
};


struct U_Message //�û���Ϣ
{
char ID[20]; //�û�ID
char Name[20]; //�û�����
char Sex[10]; //�û��Ա� 
char Tele[20]; //�û��绰 
char Code[20]; //�û�����
double Money; //�û��˻�����ʼΪ0��
char Mail[50]; //�û�����
};
struct U_Message U_quanju;//����һ��ȫ���û���Ϣ���� 

struct MovieMessage//��Ӱ������Ϣ
{ 
 char cinema[20];//��ӰԺ 
 char movieID[20];//ӰƬ��� 
 char moviename[20];//ӰƬ�� 
 char room[20];//���� 
 char beginTime[20];//����ʱ�� 
 char endTime[20];//ɢ��ʱ��
 char type[20];//ӰƬ���� 
 char language[20];//���� 
 int restticket;//��Ʊ��
 int totalticket;//��Ʊ��
 float ratio;//������ 
 float fee;//Ʊ�� 
};
//�����ı�����
//
int judge_num(char []);//�ж������Ƿ�Ϊ���� 
int rangetime(int);//����ʱ������ 
int rangefeein(int);//��Ʊ���������� 
int rangefeede(int);//��Ʊ�۽������� 
int rangerestin(int);//����Ʊ���������� 
int rangerestde(int);//����Ʊ���������� 
int paixujiemian(int);//ӰƬ��Ϣ�������
void xuanpianchang();//�û�ѡ���ӰƬ��
void userQueryMenu();//�û���Ӱ��ѯ���� 
int MovieNamequire(int);//�û�����ӰƬ����ѯӰƬ 
int Languagequire(int);//�û������������Ͳ�ѯӰƬ 
int Doublequire(int);//�û�����ӰƬ��+ӰԺ����ѯӰƬ  
int MovieTypequire(int);//�û����շ�ӳӰ�����Ͳ�ѯӰƬ 
int Cinemaquire(int);//�û�����ӰԺ����ѯӰƬ 
char buy(char []);//�û�ѡ��Ʊ���� 
char chazuo100(char []);//�û���ѯ10*10��λ 
char chazuo150(char []);//�û���ѯ10*15��λ 
void zuoweituijian100();//�û�10*10��λ�Ƽ�
void zuoweituijian150();//�û�10*15��λ�Ƽ�
int maipiao100(int,char []);//�û�ѡ����λ��Ʊ���� 
int maipiao150(int,char []);//�û�ѡ����λ��Ʊ���� 

int judge_num(char num[])//�ж������Ƿ�Ϊ���� 
{
	int flag = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(isdigit(num[i]))  continue;//��λ�ж��Ƿ�Ϊ����### 
		else 
		{
		printf("�����������֣�\n");
		flag = 1;
		break;
		} 
	} 
	return flag;//����ֵΪ0 �����������ȷ ###
}

int rangetime(int choice)//����ʱ������ 
	{
		struct MovieMessage time_total[500];//����һ���ṹ������ 
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
        int i;  //��ʱ��ӽ���Զ���� 
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
       	   	printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
int rangefeein(int choice)//��Ʊ���������� 
{
	    struct MovieMessage fee_total[500];//����һ���ṹ������ 
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
        int i; //�������� 
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
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

int rangefeede(int choice)//��Ʊ�۽������� 
{
 
	    struct MovieMessage fee_total[500];//����һ���ṹ������ 
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
        int i; //�������� 
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
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
int rangerestin(int choice)//����Ʊ���������� 
{
	    struct MovieMessage rest_total[500];//����һ���ṹ������ 
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
        int i; //�������� 
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
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n"); 
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
int rangerestde(int choice)//����Ʊ���������� 
{
	    struct MovieMessage rest_total[500];//����һ���ṹ������ 
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
        int i; //�������� 
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
 
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n"); 
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

int paixujiemian(int choice)//��Ӱ��Ϣ�������
{
	int op=0;
    int f=1;
        printf("\t\t\t***********************************\n");
        printf("\t\t\t*                                 *\n");
        printf("\t\t\t*       ��ѡ������Ҫ������      *\n");
        printf("\t\t\t*                                 *\n");
        printf("\t\t\t*       1.������ʱ������          *\n");
        printf("\t\t\t*                                 *\n");   
		printf("\t\t\t*       2.��Ʊ������              *\n");   
		printf("\t\t\t*                                 *\n"); 
		printf("\t\t\t*       3.��Ʊ�۽���              *\n");   
        printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       4.����Ʊ������            *\n");   	
		printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       5.����Ʊ������            *\n");   	
		printf("\t\t\t*                                 *\n");   	
		printf("\t\t\t*       6.����                    *\n"); 
		printf("\t\t\t*                                 *\n");   				       
        printf("\t\t\t***********************************\n");
        printf("\t\t\t��ѡ��:(1,2,3,4,5,6) \n");
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

void xuanpianchang()//�û�ѡƬ��
{
	FILE *fp1;
	char movieID[5];
	struct Order A_kan;	
	int count_[5]={0};
	int f=1;	
 	printf("\n\n");
	printf("\t\t**************************************************\n");
	printf("\t\t*                                                *\n");
	printf("\t\t*       ��ѡ������ۿ���Ƭ��������ӰƬ��ţ�     *\n");
	printf("\t\t*                                                *\n");        
	printf("\t\t*       ��ܰ��ʾ��������ҹ�����԰���Ż���!      *\n");        
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
				printf("�������ѹ�����5�����ε���Ʊ���Ѳ�����ѡ���ĳ��Σ�\n");
				printf("��ѡ������Ҫ�ۿ���Ƭ��������ӰƬ��ţ���");
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
  	printf("���ѹ�����ó��ε�ӰƱ\n");
  	system("pause");
  	fclose(fp1);*/
 	buy(movieID);
} 

void userQueryMenu()//�˿͵�Ӱ��ѯ���� 
{
	int f=1;
	while(f)
	{	
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("") ;
		printf("\t\t\t\t1. ��ӰƬ����ѯ\n\n");
		printf("\t\t\t\t2. ��ӰƬ��+ӰԺ����ѯ\n\n");
		printf("\t\t\t\t3. ���������Ͳ�ѯ\n\n");
		printf("\t\t\t\t4. ����ӳӰ�����Ͳ�ѯ\n\n");
		printf("\t\t\t\t5. ����ӰԺ��ѯ\n\n");
		printf("\t\t\t\t6. ����\n\n"); 
		printf("\t\t\t��ѡ�����Ĳ�ѯ��ʽ��");
		int choice;
		//choice=isValidChoice(5);
		fflush(stdin);
        scanf("%d",&choice);
        getchar();
		switch(choice)
		{//f=0���� 
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

int MovieNamequire(int choice)//����ӰƬ����ѯ 
 
{
	FILE *fp6;
	FILE *temp1;
	struct MovieMessage quire; 
	char typeinmoviename[10]; 
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *              1.ӰƬ����ѯ                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ����");
		scanf("%s",typeinmoviename);
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n"); 
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

int Languagequire(int choice)//����ӰƬ�������Ͳ�ѯ 

{
	FILE *fp6;
	FILE *temp3;
	struct MovieMessage quire; 
	char typeinlanguage[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *               3.���Բ�ѯ                 *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ�������ͣ�");
		scanf("%s",typeinlanguage);
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

int Doublequire(int choice)//����ӰƬ��+ӰԺ����ѯ 
 
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
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *            2.ӰƬ��+ӰԺ����ѯ           *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ����ӰԺ�����ÿո��������");
		scanf("%s%s",typeinmoviename,typeincinema);
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

int MovieTypequire(int choice)//���շ�ӳӰ�����Ͳ�ѯ 
 
{
	FILE *fp6;
	FILE *temp4;
	struct MovieMessage quire; 
	char typeinmovietype[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *            4.��ӳӰ�����Ͳ�ѯ            *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ�ķ�ӳӰ������");
		scanf("%s",typeinmovietype);
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

int Cinemaquire(int choice)//����ӰԺ����ѯ 
 
{
	FILE *fp6;
	FILE *temp5;
	struct MovieMessage quire; 
	char typeincinema[10];
	int i=0;
		system("cls");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *              5.��ӰԺ��ѯ                *\n");
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
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

char buy(char movieID[])//ѡ��Ʊ���� 
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
        printf("*            1. �� Ʊ             *\n");
        printf("*                                 *\n");
        printf("*            2. �� ��             *\n");
        printf("*                                 *\n");        
        printf("***********************************\n");
        printf("��ѡ��:(1,2) \n");
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
					//���� 
					break;
			default: break;							
		}
        
    }
}

char chazuo100(char movieID[])//��ѯ10*10��λ 
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
	printf("\n������ȡ����Ʊ��������0��");
	printf("\n��������Ҫ���Ʊ����:");
 	scanf("%d",&goupiao);
 	maipiao100(goupiao,movieID);
}

char chazuo150(char movieID[])//��ѯ10*15��λ 
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
	printf("\n������ȡ����Ʊ��������0��");
	printf("\n��������Ҫ���Ʊ����:");
 	scanf("%d",&goupiao);
 	maipiao150(goupiao,movieID);
}

void zuoweituijian100()//10*10��λ�Ƽ�
{
	int L=0;
	int I=0;
	int J=0;
	int i,j,k;
	int brr100[10][10]={0};
	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	brr100[i][j]=arr100[i][j];
	 
	for (k=0; k<10; k++) {      //�ҳ�10����ѵ���λ
    	int max=100;
    	for (i=0; i<10; i++) {      //������
    		for (j=0; j<10; j++) {  //������
        		if (brr100[i][j]!=1) {
        			L = (i-4)*(i-4)+(j-4)*(j-4);       //������λ�������λ�ľ���
                	if (max > L) {
                    	max = L;
                		I = i;
                		J = j;
            		}
         		}
      		}
   		}
   		brr100[I][J]=1;        //ѡ�е���λ�����Ϊ*
      printf("�Ƽ���λ��:%d�ţ�%d��\n",I+1,J+1);
	}
} 

void zuoweituijian150()//��λ�Ƽ�
{
	int L=0;
	int I=0;
	int J=0;
	int i,j,k;
	int brr150[10][15]={0};
	for(i=0;i<10;i++)
	for(j=0;j<15;j++)
	brr150[i][j]=arr150[i][j];
	 
	for (k=0; k<10; k++) {      //�ҳ�10����ѵ���λ
    	int max=150;
    	for (i=0; i<10; i++) {      //������
    		for (j=0; j<15; j++) {  //������
        		if (brr150[i][j]!=1) {
        			L = (i-4)*(i-4)+(j-7)*(j-7);       //������λ�������λ�ľ���
                	if (max > L) {
                    	max = L;
                		I = i;
                		J = j;
            		}
         		}
      		}
   		}
   		brr150[I][J]=1;        //ѡ�е���λ�����Ϊ*
      printf("�Ƽ���λ��:%d�ţ�%d��\n",I+1,J+1);
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
			if(strcmp(user.ID,��½�û�ID)==0)
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
		fp4=fopen("users�����.txt","r");
		while(fscanf(fp4,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
		user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
		{
			fprintf(fp3,"%s  %s  %s  %s  %S  %lf  %s",user.ID,
			user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
			i++;
		}
}
*/
int maipiao100(int goupiao,char movieID[])//ѡ����λ��Ʊ
{	
	
	FILE *fp2;
	int restticket;
	float fee;//float double
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//����Ƿ�ѡ����� 
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
		printf("��ѡ����ȡ����Ʊ����ESC������\n");
	else
	{
	 	if(restticket >= goupiao)
	    {
	    printf("��ϲ����ĿǰӰ����������\n");
	    }
	    else
	    {
	        printf("��Ʊʧ�ܡ���Ʊ����!��ESC������\n");
	        fflush(stdin);
	        int op=_getche();
			return 0;
	    }
		while(goupiao>3)
		{
		printf("�������޷�һ�ι��򳬹�����Ʊ���밴ESC������");
		fflush(stdin);
	  	int op=_getche();
		return 1;
		}
		
		printf("�������Ƿ�ѡ����λ�Ƽ�ϵͳ��1.�� 2.��");
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
			printf("�������к�:");
	   		scanf("%d",&row[goupiao]);
	    	printf("�������к�:");
	  		scanf("%d",&line[goupiao]);
			while(row[goupiao]<1 || row[goupiao] >10 || line[goupiao]<1 || line[goupiao] >10)
			{
				printf("ѡ�����淶��������ѡ�����λ\n");
				printf("�������к�:");
	            scanf("%d",&row[goupiao]);
	            printf("�������к�:");
	            scanf("%d",&line[goupiao]);
			}
		}
		goupiao = goupiao0;
	    if(row[1]==row[2] && line[1]==line[2] && row[1]!=0) 
		{
	   		printf("�ظ�ѡ������ESC������");
  			check=1; 
	    }
		else if(row[1]==row[3] && line[1]==line[3] && row[2]!=0) 
		{
			printf("�ظ�ѡ������ESC������");
			check=1; 
		}
	 	else if(row[2]==row[3] && line[2]==line[3] && row[3]!=0)		
		{
			printf("�ظ�ѡ������ESC������");
			check=1;
		}
		for(;goupiao > 0;goupiao--)
		{
			if (arr100[row[goupiao]-1][line[goupiao]-1]==1)
			{
				printf("��ѡ�������۳�����λ����ESC������\n"); 
				check=1;
			}
			else if (arr100[row[goupiao]-1][line[goupiao]-3]==1 && arr100[row[goupiao]-1][line[goupiao]-2]==0)
			{
				printf("������ѡ���淶����ESC������\n"); 
	 			check=1;
			}
		 	else if(arr100[row[goupiao]-1][line[goupiao]+1]==1 && arr100[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("������ѡ���淶����ESC������\n");
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
						if(row[goupiao]<10)//�ѵ�һ��movieID�ĳ�userID 
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
			printf("��Ʊ�ɹ�!��ESC������\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
int maipiao150(int goupiao,char movieID[])//ѡ����λ��Ʊ
{	
	
	FILE *fp2;
	int restticket;
	float fee;//float double
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//����Ƿ�ѡ����� 
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
		printf("��ѡ����ȡ����Ʊ����ESC������\n");
	else
	{
	 	if(restticket >= goupiao)
	    {
	    printf("��ϲ����ĿǰӰ����������\n");
	    }
	    else
	    {
	        printf("��Ʊʧ�ܡ���Ʊ����!��ESC������\n");
	        fflush(stdin);
	        int op=_getche();
			return 0;
	    }
		while(goupiao>3)
		{
		printf("�������޷�һ�ι��򳬹�����Ʊ���밴ESC������");
		fflush(stdin);
	  	int op=_getche();
		return 1;
		}
		
		printf("�������Ƿ�ѡ����λ�Ƽ�ϵͳ��1.�� 2.��");
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
			printf("�������к�:");
	   		scanf("%d",&row[goupiao]);
	    	printf("�������к�:");
	  		scanf("%d",&line[goupiao]);
			while(row[goupiao]<1 || row[goupiao] >10 || line[goupiao]<1 || line[goupiao] >10)
			{
				printf("ѡ�����淶��������ѡ�����λ\n");
				printf("�������к�:");
	            scanf("%d",&row[goupiao]);
	            printf("�������к�:");
	            scanf("%d",&line[goupiao]);
			}
		}
		goupiao = goupiao0;
	    if(row[1]==row[2] && line[1]==line[2] && row[1]!=0) 
		{
	   		printf("�ظ�ѡ������ESC������");
  			check=1; 
	    }
		else if(row[1]==row[3] && line[1]==line[3] && row[2]!=0) 
		{
			printf("�ظ�ѡ������ESC������");
			check=1; 
		}
	 	else if(row[2]==row[3] && line[2]==line[3] && row[3]!=0)		
		{
			printf("�ظ�ѡ������ESC������");
			check=1;
		}
		for(;goupiao > 0;goupiao--)
		{
			if (arr150[row[goupiao]-1][line[goupiao]-1]==1)
			{
				printf("��ѡ�������۳�����λ����ESC������\n"); 
				check=1;
			}
			else if (arr150[row[goupiao]-1][line[goupiao]-3]==1 && arr150[row[goupiao]-1][line[goupiao]-2]==0)
			{
				printf("������ѡ���淶����ESC������\n"); 
	 			check=1;
			}
		 	else if(arr150[row[goupiao]-1][line[goupiao]+1]==1 && arr150[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("������ѡ���淶����ESC������\n");
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
						if(row[goupiao]<10)//�ѵ�һ��movieID�ĳ�userID 
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
			printf("��Ʊ�ɹ�!��ESC������\n");
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
