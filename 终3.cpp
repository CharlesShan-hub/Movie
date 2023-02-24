#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <conio.h>

//************************************���岿��***************************************
//����
struct Order //����
{
	char orderNum[20]; //������
	char userID[20];//�û�ID
	char movieID[20];//���κ� 
	char cinema[20];//��ӰԺ
	char movie[20];//��Ӱ�� 
	char room[10];//Ӱ��
	char row[10];//�к� 	
	char line[10];//�к�
	char beginTime[20];//����ʱ�� 
	char endTime[20];//ɢ��ʱ��
	char type[20];//ӰƬ����
	char language[20];//����
	float ratio;//������ 
	int restticket;//��Ʊ��
	int totalticket;//��Ʊ��
	float fee;//Ʊ��
};

//�û���Ϣ
struct U_Message
{
	char ID[20]; //�û�ID
	char Name[20]; //�û�����
	char Sex[10]; //�û��Ա� 
	char Tele[20]; //�û��绰 
	char Code[20]; //�û�����
	double Money; //�û��˻�����ʼΪ0��
	char Mail[50]; //�û�����
};

//����Ա��Ϣ
struct A_Message 
{
	char ID[20]; //����ԱID
	char Name[20]; //����Ա����
	char Cinema[20]; //����ӰԺ 
	char Code[20]; //����Ա���� 
	char Mail[50]; //����Ա����
};

//��ӰӰ����Ϣ
struct ScreenMessage
{
 	char cinema[20];//��ӰԺ
 	char room[20];//���� 
 	char type[20];//Ӱ������  Imax/2D/3D/4D
};

//��Ӱ������Ϣ
struct MovieMessage
{
 	char movieID[20]; //���α��
 	char cinema[20];//��ӰԺ 
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

//ȫ�ֱ���
FILE *fp5;
FILE *fp6;
FILE *fp7;
int arr100[10][10] = {0};
int arr150[10][15] = {0}; 
struct U_Message U_quanju;//����һ��ȫ���û���Ϣ���� 
struct A_Message A_quanju;//����һ��ȫ�ֹ���Ա��Ϣ����
 
//ע��ʱ��Ҫ�ĺ��� 
void idcheck(int x);//ע�Ტ��ѯID 
int chachong(char [],int );//ID�Ĳ��أ���֤����ɹ�ע��������ͬ��ID 
void codecheck(int x);//����Ĳ�ѯ 
void youxiangcheckA();//����Ա���� 
void youxiangcheckU();//�û�����
void register1();//ע��
void denglu();//��½������ 
void A_denglu();//����Ա��¼
void U_denglu();//�û���¼

//����Ա������ 
void A_order();//����Ա��������ϵͳ 
int A_screen();//����ԱӰ������ϵͳ
void A_screen_check();//����ԱӰ����ѯ
int A_screen_add();//����ԱӰ����� 
int A_screen_add_valid(int);//����ԱӰ�����Ӱ����� 
int A_session();//����Ա���ι���ϵͳ
void A_session_check();//����Ա���β�ѯ
void A_session_add();//����Ա�������
int A_session_room_valid(char[]);//�ж����Ƭ�������Ƿ�Ϸ� 
int A_session_add_valid(int,int,char[]);//�ж����Ƭ��ʱ���Ƿ�Ϸ� 
void A_session_add_print(char[],char[],char[],char[],char[],char[]);//����������Ϣ��ӡ���ļ�  
void A_information(char []);//����Ա������Ϣ 
void A_change(char []);//����Ա��Ϣ����
void A_order(); //����Ա�鿴���� 
void Cinemaquire();//�����ѹ�Ʊ����δ��ӳ������
void rangeTotalin();//���������ѷ�ӳ���� 
void shengjiang();//��������������������
  
//�û������� 
void U_information(char []); //�û�������Ϣ 
void U_change(char []);//�û�������Ϣ���� 
void U_movie();//�û�������Ӱ
void U_order(char []);//�û���������
void rangetime(int);//����ʱ������ 
void rangefeein(int);//��Ʊ���������� 
void rangefeede(int);//��Ʊ�۽������� 
void rangerestin(int);//����Ʊ���������� 
void rangerestde(int);//����Ʊ���������� 
void paixujiemian(int);//ӰƬ��Ϣ�������
void xuanpianchang();//�û�ѡ���ӰƬ��
void userQueryMenu();//�û���Ӱ��ѯ���� 
void MovieNamequire(int);//�û�����ӰƬ����ѯӰƬ 
void Languagequire(int);//�û������������Ͳ�ѯӰƬ 
void Doublequire(int);//�û�����ӰƬ��+ӰԺ����ѯӰƬ  
void MovieTypequire(int);//�û����շ�ӳӰ�����Ͳ�ѯӰƬ 
void Cinemaquire(int);//�û�����ӰԺ����ѯӰƬ
void MovieRecom();//���ų����Ƽ� 
void buy(char []);//�û�ѡ��Ʊ���� 
void chazuo100(char []);//�û���ѯ10*10��λ 
void chazuo150(char []);//�û���ѯ10*15��λ 
void zuoweituijian100();//�û�10*10��λ�Ƽ�
void zuoweituijian150();//�û�10*15��λ�Ƽ�
int maipiao100(int,char []);//�û�ѡ����λ��Ʊ���� 
int maipiao150(int,char []);//�û�ѡ����λ��Ʊ����

//���ߺ��� 
int judge_num(char num[]);//�ж��û������Ƿ�Ϊ����
int judge_kongge(char[]);//�ж��û������Ƿ��пո�
void U_modify();//�޸��û��ļ� 
void A_modify();//�޸Ĺ���Ա�ļ�
void rangeBuynumin();//���ѹ�Ʊ������δ��ӳ����
void rangeBuynumde();//���ѹ�Ʊ������δ��ӳ����
void yingtingzongjia();//���㲢��ʾÿ��Ӱ������Ʊ�� 
void rangeratioin();//�������ʷ����������Ѿ���ӳ���� 
void rangeratiode();//�������ʷ����������Ѿ���ӳ����
int U_valid(char[]);//����Ӱ���Ƿ���ڣ����ڷ���0�� 
void showtime();//��ʾ��ǰʱ�� 

//***************************************������*************************************
int main()
{
	system("color f5"); 
	int n;
	char a[20];
	while(1)
	{
		system("cls");
		printf("����������û�, �������� 1:\n");
		printf("�������Ҫ��¼, �������� 2:\n");
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
			break;//����break��Ϊע������Ҫ��¼ 
 		case 2:
	 		denglu();
	 		break;
	}
	return 0;
} 

//*************************************ע��**************************************
void idcheck(int x)//�û�������ԱID�������Լ���֤ 
{
	int i=0,b=0,b1=0,b2=0,b3=0,j=0,shuzi=0,zimu=0,b4=0;
 	char ID1[20]={'\0'};
	while( b!=1 )//���벢��֤ID 
	{
		printf("����������ID:(����ʮ���ַ�,���������������ĸ)\n");
		scanf("%s",ID1);
         	for (i=0;i<=5;i++)//��֤ID���� 
			if (ID1[i]=='\0')
			{
				printf("���ID���Ϸ������������룡\n");
			 	b1=0;
			 	break;
		 	}
			else 
			b1=1;
          	if (ID1[11]!='\0')
   		{
   			printf("���ID���Ϸ������������룡\n");
		   	b2=0;
	   	}//��֤ID������	   
   		else
   		b2=1;
		b3=chachong(ID1,x);//����ID�Ĳ��� 
		while (ID1[j]!='\0')//ȷ��ID�б��뺬����ĸ������ 
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
			printf("���ID���Ϸ�!\n");
			b4=0;
		} 
		if(b1==1&&b2==1&&b3==1&&b4==1)
			b=1;//����������������Ҫ����ע��ɹ� 
		else
			b=0;
	}
	if (x==1)//��ע��ɹ���ID��ֵ��ȫ�ֱ��� 
		strcpy(A_quanju.ID,ID1);
	else
		strcpy(U_quanju.ID,ID1);
}

void codecheck(int x)//�û�������Ա��������뼰��֤ 
{
	int i=0,b=0;
	char code1[20]={'\0'},code2[20]={'\0'};
	FILE *AFile,*UFile;
	while ( b!=1 )//���벢��֤���� 
 	{
  		printf("����������������:(6��10λ)\n");
  		scanf("%s",code1);
       	for (i=0;i<=5;i++)//ȷ�������㹻�� 
     		if (code1[i]=='\0')
  		{
  			printf("������벻�Ϸ������������룡\n");
		  	b=0;
		  	break;
  		}
      	else
		b=1;
      	if(code1[11]!='\0')
		{
			printf("������벻�Ϸ������������룡\n");
			b=0;
		}//ȷ�����벻����	
		else
			b=1;     
		printf("��ȷ���������룺\n");
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

void youxiangcheckA()//����Ա������֤ 
{
	char youxiang[50]={'\0'};
	int i=0,b=0,j=0,check1=0,check2=0,c1=0,c2=0;
	while (b!=1)
	{
		
		printf("�������������䣺����ʽΪ***@***.***)\n");
		scanf("%s",youxiang);
		while(youxiang[j]!='\0')
		{
			if (youxiang[j]=='@') {c1++; check1=j;}//��¼@��λ�� 
			if (youxiang[j]=='.') {c2++; check2=j;}//��¼.��λ�� 
			if (c1==1&&c2==1)	b=1;	else b=0;//ȷ������@��.�Ĵ��� 
			j++;
		}
		if (check2<=check1+1||check1==1||check2==j-1) b=0;//ȷ��@��.֮ǰ��@���ڵ�һλ��.�������һλ 
		if (b==0)	printf("������䲻�Ϸ���\n"); 
		else printf("�������Ϸ���\n");
	}
	strcpy(A_quanju.Mail,youxiang);
}

void youxiangcheckU()//�û�������֤ 
{
	char youxiang[50]={'\0'};
	int i=0,b=0,j=0,check1=0,check2=0,c1=0,c2=0;
	while (b!=1)
	{
		printf("�������������䣺����ʽΪ***@***.***)\n");
		scanf("%s",youxiang);
		while (youxiang[j]!='\0')
		{
			if (youxiang[j]=='@') {c1++; check1=j;}//��¼@��λ��
			if (youxiang[j]=='.') {c2++; check2=j;}//��¼.��λ�� 
			if (c1==1&&c2==1)	b=1;	else b=0;
			j++;
		}
		if (check2<=check1+1||check1==1||check2==j-1) b=0;//ȷ��@��.֮ǰ��@���ڵ�һλ��.�������һλ 
		if (b==0)	printf("������䲻�Ϸ���\n"); 
		else printf("�������Ϸ���\n");
	}
	strcpy(U_quanju.Mail,youxiang);
}

void register1()//ע�ắ�� 
{
	int i,n,a=0,b=0,zhuce,c=0;
	FILE *AFile,*UFile;
 	printf("�������һλ����Ա��������1��\n");
  	printf("�������һλ�û���������2��\n");
   	scanf("%d",&zhuce);
   	switch (zhuce)
    	{  
	case 1: //ע�����Ա 
	{
		idcheck(zhuce);
		AFile=fopen("administrators.txt","a");
		printf("��������������:\n");//�������� 
		scanf("%s",A_quanju.Name);
          	printf("����������ӰԺ:\n");//��������ӰԺ 
		scanf("%s",A_quanju.Cinema);
		codecheck(zhuce);
		youxiangcheckA();
		fprintf(AFile,"%s  %s  %s  %s  %s\n",A_quanju.ID,A_quanju.Name,A_quanju.Cinema,A_quanju.Code,A_quanju.Mail);
		fclose(AFile);
		break;
	}
	case 2: //ע���û� 
	{
		idcheck(zhuce); 
		UFile=fopen("users.txt","a");
		printf("��������������:\n");//�������� 
		scanf("%s",U_quanju.Name);
		printf("�����������Ա�:\n");//�����Ա� 
 		scanf("%s",U_quanju.Sex);
		while ( b!=1 )//���벢��֤�绰 
		{
			printf("���������ĵ绰����:\n");
			scanf("%s",U_quanju.Tele);
 			if (U_quanju.Tele[11]!='\0') {printf("��ĵ绰���벻�Ϸ������������룺\n"); b=0;}//��֤�绰11λ	
   			else b=1;
			for (i=0;i<11;i++)
			if (U_quanju.Tele[i]<'0'||U_quanju.Tele[i]>'9') //��֤�绰11λ��Ϊ���� 
			{
				printf("���ĵ绰���벻�Ϸ������������룡\n");
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
 	printf("���Ѿ�ע��ɹ��������¼��\n");
  	denglu();
}

//*************************************��¼**************************************
void denglu()//��¼ 
{
   	char b[20]={'\0'};
   	system("cls");//���� 
	printf("�������һλ����Ա��������1��\n");
	printf("�������һλ�û���������2��\n");
	while(1){
		fflush(stdin);
		scanf("%s",b);
		if(judge_num(b)!=0)
			continue;
	 	break;
	}
	switch(atoi(b))
	{
		case 1: A_denglu();break;//����Ա��½
		case 2: U_denglu();break;//�û���½
		default:denglu();		 
	}
}
void A_denglu()//����Ա��¼ 
{
	int repeat = 1;//ѭ�����в��� 
	int b,a=0,c,d,num1,num2;
	double money;
	FILE *AFile,*UFile;
 	char id1[20],id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20],cinema[20];
  	char choice[20];
	printf("����������ID��\n");
	scanf ("%s",id1);
	AFile=fopen("administrators.txt","r");
	rewind(AFile); 
	while(fscanf(AFile,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail)!=EOF||a==1)
	{
		if(strcmp(id1,id2)==0)
		{
			a=1;
			printf("�������������룺\n");
			scanf("%s",code1);
			if(strcmp(code1,code2)==0)
			{
				fclose(AFile);
				//����ѱ����û���Ϣ������ ȫ �� �� �� �У� 
				strcpy(A_quanju.ID,id2);
				strcpy(A_quanju.Name,name);
				strcpy(A_quanju.Cinema,cinema);
				strcpy(A_quanju.Code,code2);
				strcpy(A_quanju.Mail,mail);
				//��ʾ�û�����ѡ����ʾ 
				printf("\n***************************************\n\n");
				printf("�װ��Ĺ���Ա! ���ѳɹ���¼! \n");
				repeat = 1;
				while(repeat == 1){
					printf("�������鿴����״��,������ 1\n");
					printf("����������Ӱ��ϵͳ,������ 2\n");
					printf("���������г��ι���,������ 3\n");
					printf("�������鿴������Ϣ,������ 4\n");
					printf("�������Ҫ�˳�      ,��������������\n");
					while(1){
						fflush(stdin);
						scanf("%s",choice);
						if(judge_num(choice)!=0)
							continue;
					 	break;
					}
					switch(atoi(choice))
					{
						case 1:A_order();/*����Ա��������ϵͳ*/
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
					  		break;
						case 2:repeat = A_screen();/*����ԱӰ������ϵͳ */ 
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 3:repeat = A_session();/*����Ա���ι���ϵͳ*/  
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 4:A_information(A_quanju.ID);/*����Ա��Ϣϵͳ*/
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
							break;
						default:
							repeat = 0;//�˳�
							fflush(stdin); 
							break;
					}
					a = 2;//a=2˵������switchcase 
				}	
			}
		}
		else
		{
			switch(a)
			{
				case 1:
					printf("�������\n");
					printf("���µ�½�밴1��\n");
					printf("�һ������밴2��\n");
					printf("����������ѡ��");
					scanf("%d",&d);
					if (d==1)	denglu();
					else 
					{
						srand(time(0));
						num1=rand()%(10000-1000)+1000;
						printf("�����Ѿ����������䷢������֤��\n");
						printf("�����룺\n");
						scanf("%d",num2);
						if(num1==num2)
						{
							printf("����������%s\n",code2);
							printf("�뼰ʱ����\n");
							denglu();
						}
					}
					break;
				case 0://���a=0 ˵��δ�ҵ��û��� 
					//printf("*\n");//���� 
					break;
				default: 
					break;
			}
		}
	}
	if(a == 0){
		printf("����ID������\n");
		printf("����������µ�¼��������1��\n");
		printf("�������ע�ᣬ������2��\n ");
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
   
void U_denglu()//�û���¼ 
{
	int repeat = 1;//ѭ�����в��� 
	int b,a=0,c,d,num1,num2;
	double money;
	FILE *AFile,*UFile;
 	char id1[20],id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20],cinema[20];
  	char choice[20];
	printf("����������ID��\n");
	scanf ("%s",id1);
	UFile=fopen("users.txt","r");
	rewind(UFile); 
	while(fscanf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF||a==1)
	{
		if(strcmp(id1,id2)==0)
		{
			a=1;
			printf("�������������룺\n");
			scanf("%s",code1);
			if(strcmp(code1,code2)==0)
			{
				fclose(UFile);
				//����ѱ����û���Ϣ������ ȫ �� �� �� �У� 
				strcpy(U_quanju.ID,id2);
				strcpy(U_quanju.Name,name);
				strcpy(U_quanju.Sex,sex);
				strcpy(U_quanju.Tele,tele);
				strcpy(U_quanju.Code,code2);
				U_quanju.Money = money;
				strcpy(U_quanju.Mail,mail);
				//��ʾ�û�����ѡ����ʾ 
				printf("\n***************************************\n\n");
				printf("�װ����û�! ���ѳɹ���¼! \n");
				repeat = 1;
				while(repeat == 1){
					printf("�������鿴������Ϣ��������1��\n");     
					printf("�������������Ӱ��������2��\n");    
					printf("�������鿴���Ķ�����������3��\n");
					printf("�������Ҫ�˳�      ,��������������\n");
					while(1){
						fflush(stdin);
						scanf("%s",choice);
						if(judge_num(choice)!=0)
							continue;
					 	break;
					}
					switch(atoi(choice))
					{
						case 1:U_information(id1); /*�û�������Ϣ*/  
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
					  		break;
						case 2:U_movie();/*�û�������Ӱ*/
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
							break;
						case 3:U_order(id1);/*�û���������*/  
							printf("�����������\n");
			    				fflush(stdin);
			    				getchar();
							break;
						default:
							repeat = 0;//�˳�
							fflush(stdin); 
							break;
					}
					a = 2;//a=2˵������switchcase 
				}	
			}
		}
		else
		{
			switch(a)
			{
				case 1:
					printf("�������\n");
					printf("���µ�½�밴1��\n");
					printf("�һ������밴2��\n");
					printf("����������ѡ��");
					scanf("%d",&d);
					if (d==1)	denglu();
					else{
						srand(time(0));
						num1=rand()%(10000-1000)+1000;
						printf("�����Ѿ����������䷢������֤��\n");
						printf("�����룺\n");
						scanf("%d",num2);
						if(num1==num2)
						{
							printf("����������%s\n",code2);
							printf("�뼰ʱ����\n");
							denglu();
						}
					}
					break;
				case 0://���a=0 ˵��δ�ҵ��û��� 
					//printf("*\n");//���� 
					break;
				default: 
					break;
			}
		}
	}
	if(a == 0){
		printf("����ID������\n");
		printf("����������µ�¼��������1��\n");
		printf("�������ע�ᣬ������2��\n ");
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

//****************************************����Ա����***********************************

//*************************************����Ա������Ϣ��ѯ���޸�********************************
void A_information(char id1[20])
{
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	double c;
	int b=0,a=0;
	
	printf("\n�������鿴��Ļ�����Ϣ��������1\n");
	printf("������������Ļ�����Ϣ��������2\n");
	printf("������뷵����һ���棬����������ֵ\n");
	scanf("%d",&b);
	switch(b)
	{
		case 1://����Ա�鿴������Ϣ 
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
		case 2://����Ա������Ϣ 
		{
			A_change(id1);
			break;
	    }
		default:denglu();break;
	}
}

void A_change(char id1[20])//����Ա��Ϣ���� 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","r");
	fp=fopen("administrators1.txt","w");
	int a=0,b=0;
	char choice[20];
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	
	printf("\n�������������������������1\n");
	printf("����������������䣬������2\n");
	printf("����������������룬������3\n");
	printf("������뷵����һ���棬����������ֵ\n"); 
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
		case 1://�������� 
		{
			while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
			{
				if(strcmp(id1,id2)==0)
 	  			{
					printf("\n������������������\n");//�������� 
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
		case 2://�������� 
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
		case 3://�������� 
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
		default:A_information(id1);break;//������һ���� 
	}
}

//*************************************����Ա�����鿴**************************************
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
	printf("�����ѹ�Ʊ����δ��ӳ������������1:\n");
	printf("���հ��������ѷ�ӳ����������2:\n");
	printf("�����ѹ�Ʊ����δ��ӳ������������3:\n");
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
				printf("����������������룺\n");
				break;
		}
	}
}

//*************************************����Ա�����ѹ�Ʊ����δ��ӳ������******************************* 
void Cinemaquire()//�����ѹ�Ʊ����δ��ӳ������
{
	FILE *fp;//��дMovieMessage.txt�ļ� 
	FILE *gtemp;//��дgtemp.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ϣ����  
	int a=0;//ѡ���ѯ��ʽ 
	
	system("cls");//���� 
	printf("                 ********************************************\n");  
	printf("                 *                                          *\n");
	printf("                 *             ����Ա��Ӱ��ѯ����           *\n");
	printf("                 *                                          *\n");
	printf("                 *                ��ӰԺ��ѯ                *\n");
	printf("                 *                                          *\n");
	printf("                 ********************************************\n\n");
	printf("                 ********************************************\n");  
	printf("                 *                   ӰԺ                   *\n");
	printf("                 *                   Houde                  *\n");
	printf("                 *                   Boxue                  *\n");
	printf("                 *                   Mashi                  *\n");
	printf("                 ********************************************\n\n");
	printf("���α��  |��ӰԺ  |ӰƬ�� |���� |����ʱ�� |ɢ��ʱ�� |ӰƬ����|����|��Ʊ��|��Ʊ��|������|Ʊ�� \n"); 
	fp=fopen("MovieMessage.txt","r");//��ȡ������Ϣ�ļ� 
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
	//��ͳһӰԺ�ĳ�����Ϣ����gtemp.txt�ļ� 
	gtemp=fopen("gtemp.txt","w"); 
 	while((fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)	
 		if(strcmp(A_quanju.Cinema,quire.cinema)==0)//�ж�����ӰԺ�͹���Ա����ӰԺ�Ƿ���ͬ 
		{
			fprintf(gtemp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
			quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
			quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
			fclose(gtemp);
		}
	  	rewind(fp);
		fclose(fp);
		printf("�������ѯ��ʽ��\n");
		printf("�����밴��1��\n");
		printf("�����밴��2��\n");
		while(a!=1&&a!=2)
		{
			scanf("%d",&a);	
			switch (a)
			{
				case 1://���� 
 					rangeBuynumin();
					break;
				case 2://����
		 			rangeBuynumde();
		 			break;
				default:
					printf("����������������룺\n");
					break;	 
			}
		}
	}
	
void rangeBuynumin()//���ѹ�Ʊ������δ��ӳ���� 
{
	struct MovieMessage buynum_total[500];//����һ���ṹ������ 
	int n=0;//ͬһ��ӰԺ���ܳ����� 
	FILE *fp;//��дgtemp.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ϣ����
		 
	system("cls"); //���� 
	fp=fopen("gtemp.txt","r");
	if(fp==NULL)
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	//��������Ϣ��Ӧ����ṹ������ 
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
 	//��������
	int i;//һ��ѭ�� 
 	int j;//����ѭ�� 
	struct MovieMessage t; //�м�ֵ 
        
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
	printf("���  |��ӰԺ|    ӰƬ��    |  ���� |    ����ʱ��     |   ɢ��ʱ��    |ӰƬ����|  ���� |��Ʊ��|��Ʊ��|   ������    |      Ʊ�� \n");  
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

void rangeBuynumde()//���ѹ�Ʊ������δ��ӳ���� 
{
	struct MovieMessage buynum_total[500];//����һ���ṹ������ 
	int n=0;//ͬһ��ӰԺ���ܳ����� 
	FILE *fp;//��дgtemp.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ϣ���� 
		
	system("cls");  //���� 
	fp=fopen("gtemp.txt","r");
	if(fp==NULL)
	{
	  	printf("The file was not successfully opened.\n");
	 	exit(1);
	}
	//��������Ϣ��Ӧ����ṹ������
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
	//��������
	int i;//һ��ѭ�� 
	int j;//����ѭ�� 
        
	struct MovieMessage t;//�м�ֵ 
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
	printf("���  |��ӰԺ|    ӰƬ��    |  ���� |    ����ʱ��     |   ɢ��ʱ��    |ӰƬ����|  ���� |��Ʊ��|��Ʊ��|   ������    |      Ʊ�� \n");  
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

//****************************����Ա���չ���Ա������Ʊ������*****************************
void rangeTotalin()//���������ѷ�ӳ���� 
{
	struct MovieMessage income_total[500];//����һ���ṹ������ 
	int n=0;//��ʾ������ŵ����г����� 
	int m=0;//��ʾ�������ŵ����г����� 
	int b=0;//��ʾ�����ߺŵ����г����� 
	FILE *fp;//��дMovieMessage�ļ� 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//��ʾ������Ϣ���� 
		
	system("cls");//���� 
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
 	//��������
	int i;//һ��ѭ��  
	int j;//����ѭ�� 
	struct MovieMessage t; //�м�ֵ 
        
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
	printf("���  |��ӰԺ|    ӰƬ��    |  ���� |    ����ʱ��     |   ɢ��ʱ��    |ӰƬ����|  ���� |��Ʊ��|��Ʊ��|   ������    |      Ʊ�� \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[i].movieID,income_total[i].cinema,income_total[i].moviename,
		income_total[i].room,income_total[i].beginTime,income_total[i].endTime,income_total[i].type,income_total[i].language,
		income_total[i].restticket,income_total[i].totalticket,
		income_total[i].ratio,income_total[i].fee);
	}
	rewind(fp);//���ص��ļ���ͷ 
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
	//�������� 
	int q;//һ��ѭ�� 
	int w;//����ѭ�� 
	struct MovieMessage e; //�м�ֵ 
        
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
	rewind(fp);//���ص��ļ���ͷ 
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
	//��������
	int a;//һ��ѭ��  
	int s;//����ѭ�� 
	struct MovieMessage d; //�м�ֵ
		 
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
	yingtingzongjia();//���õ���Ӱ����Ʊ�۲�ѯ���� 	
}

int U_valid(char room[20])//��֤Ӱ���Ƿ����
{
	FILE * S_Message;//����Ӱ������Ϣ
	struct ScreenMessage SM;
 
	S_Message=fopen("ScreenMessage.txt","r");
	while(fscanf(S_Message,"%s %s %s",SM.cinema,SM.room,SM.type)!=EOF)
	{
		if(strcmp(room,SM.room)==0)
		return 0; //��ȷ 
	}
	printf("δ�����Ӱ����������������\n");
	fflush(stdin);
	getchar();
	return 1; 
}

void yingtingzongjia()//Ӱ���ܼ۲�ѯ 
{
	FILE *fp3;//��дOrderMessage.txt�ļ� 
	Order A_ji;//��ʾ������Ϣ���� 
	int choice;//ѡ�� 
	double total=0;//��Ʊ�� 
	char yingting[10];//����Ӱ����
     	
 	while(1)
	{
	printf("                 ********************************************\n");  
	printf("                 *                                          *\n");
	printf("                 *           ����ԱӰ����Ʊ�۲�ѯ           *\n");
	printf("                 *                                          *\n");
	printf("                 ********************************************\n\n");
	printf("�����������ѯ��Ӱ����");
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
			     printf("Ӱ��    ��Ʊ��\n"); 
			     printf("%s    %f\n",yingting,total); 
			     printf("/�Ƿ������ѯ����Ӱ��/(��������1/��������2):\n");
	while(choice!=1 && choice!=2)
	{
		scanf("%d",&choice);
		switch(choice)
		{
			case 1://������ѯ����Ӱ����Ʊ�� 
			yingtingzongjia(); 
			break;
			case 2://������ѯ 
			break; 
			default:
			printf("������ѡ��");
			break;	
		}
	}
	fclose(fp3);	
}

//****************************����Ա���չ���Ա��������������*****************************
void shengjiang()//������������ 
{
	int a=0;//ѡ�� 
	
	printf("�������ѯ��ʽ��\n");
	printf("�����밴��1��\n");
	printf("�����밴��2��\n");
	while(a!=1&&a!=2)
	{
		scanf("%d",&a);	
		switch (a)
		{
			case 1://���� 
				rangeBuynumin();
				break;
			case 2://����
	 			rangeBuynumde();
	 			break;
			default:
				printf("����������������룺");
				break;	 
		}
	}
}

void rangeratioin()//�������ʷ����������Ѿ���ӳ���� 
{
	struct MovieMessage ratio_total[500];//����һ���ṹ������ 
	int n=0;//��ʾ������ŵ����г�����  
	int m=0;//��ʾ�������ŵ����г�����
	int b=0;//��ʾ�����ߺŵ����г�����
	FILE *fp;//��дMovieMessage.txt�ļ� 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//��ʾ������Ϣ 
		
	system("cls"); //���� 
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
 	//��������
	int i;//һ��ѭ�� 
	int j;//����ѭ�� 
	struct MovieMessage t; //�м�ֵ 
    
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
	printf("���  |��ӰԺ|    ӰƬ��    |  ���� |    ����ʱ��     |   ɢ��ʱ��    |ӰƬ����|  ���� |��Ʊ��|��Ʊ��|   ������    |      Ʊ�� \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
		ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
		ratio_total[i].restticket,
		ratio_total[i].totalticket,
		ratio_total[i].ratio,ratio_total[i].fee);
	}
	rewind(fp);//���ص��ļ���ͷ 
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
	//�������� 
	int q;//һ��ѭ�� 
	int w;//����ѭ�� 
	struct MovieMessage e;//�м�ֵ 
        
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
	rewind(fp);//���ص��ļ���ͷ 
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
	//�������� 
	int a;//һ��ѭ�� 
	int s;//����ѭ�� 
	struct MovieMessage d;//�м�ֵ 
        
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

void rangeratiode()//�������ʷ����������Ѿ���ӳ���� 
{
	struct MovieMessage ratio_total[500];//����һ���ṹ������ 
	int n=0;//��ʾ������ŵ��ܳ����� 
	int m=0;//��ʾ�������ŵ��ܳ����� 
	int b=0;//��ʾ�������ߵ��ܳ����� 
	FILE *fp;//��дMovieMessage.txt�ļ� 
	char day1[10]="09/05";
	char day2[10]="09/06";
	char day3[10]="09/07";
	struct MovieMessage quire;//����������Ϣ 
		
	system("cls");//���� 
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
	//�������� 
	int i;//һ��ѭ�� 
	int j;//����ѭ�� 
	struct MovieMessage t;//�м�ֵ
		 
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
	printf("���  |��ӰԺ|    ӰƬ��    |  ���� |    ����ʱ��     |   ɢ��ʱ��    |ӰƬ����|  ���� |��Ʊ��|��Ʊ��|   ������    |      Ʊ�� \n");  
	for(int i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
		ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
		ratio_total[i].restticket,
		ratio_total[i].totalticket,
		ratio_total[i].ratio,ratio_total[i].fee);
	}
 	rewind(fp);//���ص��ļ���ͷ 
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
	//��������
	int q;//һ��ѭ�� 
	int w;//����ѭ�� 
	struct MovieMessage e;//�м�ֵ
		 
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
	rewind(fp);//���ص��ļ���ͷ 
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
	//��������
	int a;//һ��ѭ��  
	int s;//����ѭ�� 
	struct MovieMessage d;//�м�ֵ
		 
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

//*************************************������ӺͲ鿴**************************************
void A_session_add()//����Ա������� 
{
	FILE * M_Message;//����Ӱ������Ϣ
	struct MovieMessage MM1 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};//���ն�ȡ�Ĺ���Ա����		
	char choice[20] = {'\0'};
	//�����ʱ��
	char date[5] = {'\0'},tIme[5] = {'\0'};
	int month=0,day=0,hour=0,minute=0;//�����ʱ��
	int min1_b=0,min1_e=0;//�û�����Ŀ�ʼʱ��ͽ���ʱ��
	//�ļ���ʱ�� 
	int month2=0,day2=0,hour2=0,minute2=0;//�ļ��е�ʱ��
	int min2_b=0,min2_e=0;//�ļ��еĿ�ʼʱ��ͽ���ʱ��
	int a = 1,b = 1;
	
	//�����ļ��Ƿ���Դ� 
	if((M_Message=fopen("MovieMessage.txt","r"))!=NULL){
		fclose(M_Message);
	}else{
		printf("�ı�(MovieMessage.txt)�򿪴���\n");
		system("pause");
	}
	//��ʼ����û���ȷ����
	system("cls");
	printf("\n ����������ӳ��ε���Ϣ��\n\n!!��ϸ�Ķ�˵����"
			 "�����չ涨��ʽ���룬������Ч����\n\n");
	//ӰƬ�� 
	while(1){
		printf("�������� ӰƬ��\n");
		fflush(stdin);
		scanf("%s",MM1.moviename);
	 	if(judge_kongge(MM1.moviename)!=0)
			continue;	
	 	break;
	}
	//��ӳ���� 
	while(1){
	 	printf("�������� ��ӳ���ţ��� 1 ��\n���ѿ���һ��Ӱ����\n");
		A_screen_check();//��ӡһ��Ӱ����Ϣ
		fflush(stdin);
		scanf("%s",MM1.room);
	 	if(judge_num(MM1.room)!=0)
			continue;	
		if(A_session_room_valid(MM1.room)!=0)
			continue;
	 	break;
	}
	//���� 
	while(1){
	 	printf("�������벥�ŵ����� ��������1��Ӣ������2\n");
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
	//Ʊ��
	while(1){
	 	printf("���������Ӱ��Ʊ��\n");
	 	fflush(stdin);
	 	scanf("%s",choice);
	 	if(judge_num(choice)!=0)
	 		continue;
 		break;//�Ӵ�choice��������Ʊ����Ϣ���������ٱ���ֵ������ 
	}
	//����ʱ��
	b = 1;
	while(b){//����һ��b������һ�ο���ʱ�� 
		a=1;
		//��ȡ�趨�Ŀ���ʱ��
		while(a){
			a=0;
			date[0]='\0';date[1]='\0';date[2]='\0';date[3]='\0';date[4]='\0';date[5]='\0';
			printf("�����ϸ��ո�ʽ���뿪������\n�磺09/05,09/12\n");
			fflush(stdin);
			scanf("%s",date);//�Ժ�Ҫ�ǵüӸ�ʽ�ж�
			month = (int(date[0])-48)*10+ (int(date[1])-48);//��
			day = (int(date[3])-48)*10 + (int(date[4])-48);	//��
			if(day<0||day>31)
			{
				printf("�������������⣡");
				a=1;
			}
			if(int(date[2]) != 47)
			{
			printf("��ʽ���������⣡");
			a=1;
			}
			switch (month)//��׼��λ 
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
					printf("�·����������⣡");
					a=1;
					break;
			}
		}//while(a)��ѭ������ (�������)
		a = 1;
		while(a==1){
			a = 0;
			tIme[0]='\0';tIme[1]='\0';tIme[2]='\0';tIme[3]='\0';tIme[4]='\0';tIme[5]='\0';
			printf("�����ϸ��ո�ʽ���뿪��ʱ��\n�磺00:30,15:30\n");
	 		fflush(stdin);
		 	scanf("%s",tIme); //�Ժ�Ҫ�ǵüӸ�ʽ�ж�
	 		hour = (int(tIme[0])-48)*10+(int(tIme[1])-48);//Сʱ
	 		if(hour<0||hour>23)
		 	{
				printf("Сʱ���������⣡\n");
				a = 1;
			}
	 		if(int(tIme[2]) != 58)
			{
				printf("��ʽ���������⣡");
				a=1;
			}
			minute = (int(tIme[3])-48)*10+(int(tIme[4])-48);//���� 
			if(minute<0||minute>59)
			{
			printf("�������������⣡\n");
			a = 1;
			}
			minute += hour*60 + 24*60*(day-1); //��׼����λ
			min1_b = minute;	
		}//while(a)��ѭ������ (���ʱ��)
		if(A_session_add_valid(min1_b,-1,MM1.room))
		{
			strcpy(MM1.beginTime,date);
			strcat(MM1.beginTime,"/");
			strcat(MM1.beginTime,tIme);
			break;
		}
	}  //while(b)��ѭ������
	//����ʱ��
	b = 1;
	while(b)
	{//����һ��b������һ�ο���ʱ�� 
		a=1;
		//��ȡ�趨�Ľ���ʱ��
		while(a)
		{
			a=0;
			date[0]='\0';date[1]='\0';date[2]='\0';date[3]='\0';date[4]='\0';date[5]='\0';
			printf("�����ϸ��ո�ʽ�����������\n�磺09/05,09/12\n");
			fflush(stdin);
			scanf("%s",date);//�Ժ�Ҫ�ǵüӸ�ʽ�ж�
			month = (int(date[0])-48)*10+ (int(date[1])-48);//��
			day = (int(date[3])-48)*10 + (int(date[4])-48);	//��
			if(day<0||day>31)
			{
				printf("�������������⣡");
				a=1;
			}
			if(int(date[2]) != 47)
			{
				printf("��ʽ���������⣡");
				a=1;
			}
			switch (month)
			{		//��׼��λ 
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
					printf("�·����������⣡");
					a=1;
					break;
			}
		}//while(a)��ѭ������ (�������)
		a = 1;
		while(a==1)
		{
			a = 0;
			tIme[0]='\0';tIme[1]='\0';tIme[2]='\0';tIme[3]='\0';tIme[4]='\0';tIme[5]='\0';
			printf("�����ϸ��ո�ʽ�������ʱ��\n�磺00:30,15:30\n");
	 		fflush(stdin);
		 	scanf("%s",tIme);//�Ժ�Ҫ�ǵüӸ�ʽ�ж�
	 		hour = (int(tIme[0])-48)*10+(int(tIme[1])-48);//Сʱ
	 		if(hour<0||hour>23){printf("Сʱ���������⣡\n");a = 1;}
	 		if(int(tIme[2]) != 58){printf("��ʽ���������⣡");a=1;}
			minute = (int(tIme[3])-48)*10+(int(tIme[4])-48);//���� 
			if(minute<0||minute>59){printf("�������������⣡\n");a = 1;}
			minute += hour*60 + 24*60*(day-1); //��׼����λ
			min1_e = minute;	
		}//while(a)��ѭ������ (���ʱ��)
		if(A_session_add_valid(min1_b,min1_e,MM1.room)){
		strcpy(MM1.endTime,date);
		strcat(MM1.endTime,"/");
		strcat(MM1.endTime,tIme);
		break;
		} 
	}  //while(b)��ѭ������
	//����Ϣ�����ı�
	A_session_add_print(MM1.moviename,MM1.room,MM1.beginTime,MM1.endTime,MM1.language,choice);//�ж����Ƭ��ʱ���Ƿ�Ϸ�	 	 	
}

void A_session_add_print(char moviename[],char room[],char beginTime[],char endTime[],char language[],char choice[])//�ж����Ƭ��ʱ���Ƿ�Ϸ�
{
	struct ScreenMessage SM3 = {{'\0'},{'\0'},{'\0'}};
	struct MovieMessage MM3 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};		
	FILE * M_Message;//���г��ε���Ϣ
	FILE * S_Message;//����Ӱ������Ϣ
	int count_=0,read_=0;//��¼�������
	int num = 0;//��Ʊ������Ʊ��
	char choice_[20]={'\0'}; 
	
	//ӰƬ����  Ϊ SM3.type	
	S_Message=fopen("ScreenMessage.txt","r");
	while(fscanf(S_Message,"%s  %s  %sf",SM3.cinema,SM3.room,SM3.type)!=EOF) 
	{
		if(strcmp(SM3.cinema,A_quanju.Cinema) == 0)
		if(strcmp(SM3.room,room) == 0)
		break;
	} 
	fclose(S_Message);
	//�������   count_ 
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
	//��Ʊ������Ʊ��  num 
	if(strcmp(SM3.type,"Imax") == 0)
		num = 150;
	else
		num = 100;
	//ѯ�ʹ���Ա�Ƿ�Ҫ���
	printf("\nӰƬ��:%s\nӰ����:%s\n����ʱ��:%s\n�볡ʱ��:%s\nӰƬ����:%s\n����:"
	"%s\nƱ��:%s\n",moviename,room,beginTime,endTime,SM3.type,language,choice);	
	while(1)
	{
	 	printf("\n��������������Ƭ������Ϣ\nȷ���������1�������������������\n");
	 	fflush(stdin);
 		scanf("%s",choice_);
	 	if(judge_num(choice_)!=0)
	 		continue;
 		break;
	}
	//������ӻ��߷���
	if(atoi(choice_) == 1)
	{
		M_Message=fopen("MovieMessage.txt","a");	
		fprintf(M_Message,"%d\t%s\t%s\t%s\t",count_,A_quanju.Cinema,moviename,room);
		fprintf(M_Message,"%s\t%s\t%s\t%s\t",beginTime,endTime,SM3.type,language);
		fprintf(M_Message,"%d\t%d\t0 \t%s\n",num,num,choice);
		fclose(M_Message);
		printf("���ѳɹ���ӣ�\n");
	}
	else
	{
		printf("����ȡ����ӣ�\n");
	}	
}

int A_session_add_valid(int min1_b,int min1_e,char room[])//�������ʱ����֤ 
{	
	int month=0,day=0,hour=0,minute=0;//�������Ŀ�ʼʱ�� 
	int month2=0,day2=0,hour2=0,minute2=0;//�������Ľ���ʱ�� 
	FILE * M_Message;//����Ӱ������Ϣ
	
	struct MovieMessage MM2 = {{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},{'\0'},0,0,0.0,0.0};		
	M_Message=fopen("MovieMessage.txt","r");
	while(fscanf(M_Message,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",//"\"�ǻ��з�������ʡ��! 
	MM2.movieID,MM2.cinema,MM2.moviename,MM2.room,MM2.beginTime,
	MM2.endTime,MM2.type,MM2.language,&MM2.restticket,&MM2.totalticket,
	&MM2.ratio,&MM2.fee)!=EOF){
		if(strcmp(MM2.cinema,A_quanju.Cinema) == 0)
		if(strcmp(room,MM2.room) == 0)
		{
			//������Ӱ����һ�ο���ʱ�� 
			month =(int(MM2.beginTime[0])-48)*10+(int(MM2.beginTime[1])-48);//��
			day =(int(MM2.beginTime[3])-48)*10+(int(MM2.beginTime[4])-48);  //��
			hour=(int(MM2.beginTime[6])-48)*10+(int(MM2.beginTime[7])-48);//Сʱ
			minute=(int(MM2.beginTime[9])-48)*10+(int(MM2.beginTime[10])-48);//���� 
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
					printf("�·ݶ�ȡ�������⣡\n");
					break;
			}
			minute += hour*60 + 24*60*(day-1);//ת��Ϊ����
			//������Ӱ����һ�ν���ʱ�� 
			month2 =(int(MM2.endTime[0])-48)*10+(int(MM2.endTime[1])-48);//��
			day2 =(int(MM2.endTime[3])-48)*10+(int(MM2.endTime[4])-48);  //��
			hour2=(int(MM2.endTime[6])-48)*10+(int(MM2.endTime[7])-48);//Сʱ
			minute2=(int(MM2.endTime[9])-48)*10+(int(MM2.endTime[10])-48);//���� 
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
					printf("�·ݶ�ȡ�������⣡\n");
					break;
			}
			minute2 += hour2*60 + 24*60*(day2-1);//ת��Ϊ����
			//�ж��û��������Ƿ�Ϸ� 
			if(min1_e == -1)
			{//�жϿ�ʼʱ�� 
				if(min1_b<(minute2+20)&&min1_b>(minute-20))
				{
					printf("���Ŀ���ʱ�����ò�����\n");
					fclose(M_Message);
					return 0;
				}
			}
			else
			{//�жϽ���ʱ�� 
				if(min1_e<(minute2+20)&&min1_e>(minute-20)||(min1_e-min1_b)<60||(min1_e-min1_b)>180){
					printf("���Ľ���ʱ�����ò�����\n");
					fclose(M_Message);
					return 0;//���Ϸ�����0
				}
			}
		}			
	}
	fclose(M_Message);
	return 1;//�Ϸ�����1 
}

int A_session_room_valid(char room[])//�ж����Ƭ��ʱ���Ƿ�Ϸ�
{
	FILE * S_Message;//����Ӱ������Ϣ
	struct ScreenMessage SM1;
	
	if((S_Message=fopen("ScreenMessage.txt","r"))!=NULL)
	{
		while(fscanf(S_Message,"%s %s %s",SM1.cinema,SM1.room,SM1.type)!=EOF)
		{
			if(strcmp(SM1.cinema,A_quanju.Cinema) == 0)
			if(strcmp(SM1.room,room) == 0)
			{
				fclose(S_Message);
				return 0;//����ֵΪ0����������ȷ 
			}	
		}
		fclose(S_Message);
	}
	else
	{
		printf("�ı�(ScreenMessage.txt)�򿪴���\n");
		exit(1);
	}
	printf("��δ�����Ӱ����\n");
	getchar();
	getchar(); 
	fclose(S_Message);
	return 1;
}

int A_session()//����Ա���ι��������� 
{
	char a[20];
	int choice = 0;
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("���Ѿ��ɹ����볡�ι���ϵͳ��\n");
		printf("����������ѡ��:\n"
 			 "���β�ѯ       ������ 1\n"  //���β�ѯ 
 			 "��ӳ���       ������ 2\n"  //���ι��� 
 			 "����           ������ 3\n"  //���� 
  			 "�˳�           ������ 4\n");//�˳�
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//�ж��û������Ƿ�Ϊ���� 
			continue;
		choice = atoi(a);
		switch(choice)
		{
    			case 1://���β�ѯ
			    	A_session_check();
			    	printf("�����������\n");
			    	fflush(stdin);
			    	getchar();
			    	break;
      		case 2://������� 
				A_session_add();  
				printf("�����������\n");
			    	fflush(stdin);
			    	getchar();
				break;
       		case 3:	return 1;//���� 
        		case 4:	return 0;//�˳� 
        		default:	break;
    	 	} 	
	}	  	
}

void A_session_check()//����Ա���β�ѯ
{
	struct MovieMessage MM;
	FILE * M_Message;//���г��ε���Ϣ
	char a[20];	 //��ȡ�û�ѡ�� 
	int choice=0;//�����û�ѡ�� 
	
	//��ȡ�û�ѡ��
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("����������Ҫ�鿴�ĳ��Σ�\n");
		printf("1-20����       input 1-20\n"  
 			 "ȫ������       input 0\n"); 
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//�ж��û������Ƿ�Ϊ���� 
			continue;
		choice = atoi(a);	
		if(choice<0||choice>20)//�ж��û������Ƿ�Խ��
			continue;
		break;
	}
	//��ӡ��ͷ 
	system("cls");
	if(choice == 0)
		printf("\n ������ȫ��Ӱ���ĳ�����Ϣ��\n");
	else
		printf("\n �����ǵ�%dӰ���ĳ�����Ϣ��\n",choice);
	printf("���κ�|��Ӱ��|Ӱ����|��������ʱ��|��������ʱ��|ӰƬ����|��������|ʣ��Ʊ��|��Ʊ��|�۳���|Ʊ��\n");
	//�����ļ�����ӡ���� 
	if((M_Message=fopen("MovieMessage.txt","r"))!=NULL)
	{
		while(fscanf(M_Message,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f", 
		MM.movieID,MM.cinema,MM.moviename,MM.room,MM.beginTime,
		MM.endTime,MM.type,MM.language,&MM.restticket,&MM.totalticket,
		&MM.ratio,&MM.fee)!=EOF)
		{
			if(strcmp(MM.cinema,A_quanju.Cinema) == 0)
			{
				if(choice == 0){//����Ա�鿴ȫ������ 
					if(strcmp(MM.cinema,A_quanju.Cinema) == 0)
					printf("%-3s %-9s  %-4s %s   %-13s %-6s %s    %-3d    %-3d    %.2f%% %.2f\n",
					MM.movieID,MM.moviename,MM.room,MM.beginTime,
					MM.endTime,MM.type,MM.language,MM.restticket,MM.totalticket,
					MM.ratio*100,MM.fee);	
				}
				else
				{//����Ա�鿴��Ӧ���� 
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
		printf("ScreenMessage.txt�򿪴���\n");
		system("pause");
	}	
}

//*************************************Ӱ����ӺͲ鿴**************************************
int A_screen()	//Ӱ������������ 
{
	char a[20];
	int choice = 0;
	while(1)
	{
		system("cls");
		printf("******************************************\n");
		printf("You have entered screen management system!\n");
		printf("����������ѡ��:\n"
 			 "Ӱ����ѯ:��ѯ���п����Ӱ����Ϣ ������ 1\n"  //Ӱ����ѯ 
 			 "���Ӱ��:���һ���µ�Ӱ��       ������ 2\n"  //Ӱ������ 
 			 "����                            ������ 3\n"  //���� 
  			 "�˳�                            ������ 4\n");//�˳�
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//�ж������Ƿ�Ϊ���� 
			continue;
		choice = atoi(a);
		switch(choice)
		{
    			case 1:
				A_screen_check();  
				printf("�����������\n");
				fflush(stdin);
				getchar();
				break;//Ӱ����ѯ
      		case 2:
				A_screen_add()  ;
				printf("�����������\n");
				fflush(stdin);
				getchar();
				break;//Ӱ������
       		case 3:
			 	return 1;//���� 
        		case 4:
			  	return 0;//�˳� 
        		default:
			  	break;
    	 	} 	
	}	  	
}	

void A_screen_check()	//����ԱӰ����ѯ
{
	struct ScreenMessage SM;
	FILE * S_Message;//����Ӱ������Ϣ
	
	if((S_Message=fopen("ScreenMessage.txt","r"))!=NULL)
	{
		printf("    Ӱ����   |  Ӱ������ \n");
		while(fscanf(S_Message,"%s %s %s",SM.cinema,SM.room,SM.type)!=EOF)
		{
			if(strcmp(A_quanju.Cinema,SM.cinema) == 0)
				printf("      %s\t\t%s\n",SM.room,SM.type);
		}
	}
	else
	{
		printf("ScreenMessage.txt�ı��򿪴���\n");
		system("pause");
	}
	fclose(S_Message);
}

int A_screen_add()//����ԱӰ������
{
	int choice1=0,choice2=0;
	char a[20],b[20];
	char Type[20] = {'\0'};
	FILE * S_Message;//����Ӱ������Ϣ
	while(1)//���Ӱ���� 
	{
		system("cls");
		printf("\n   ���ѿ���һ��Ӱ����\n");
		A_screen_check();//��ӡһ��Ӱ����Ϣ 
		printf("\n���������ʾ��������Ӱ������Ϣ��\n"
			 "ע�⣺Ӱ��һ�����Ӳ��ܸ��ģ�\n"
			 "��������δ���ע��ʱ���� 0 ������Ӱ�������ӣ�\n\n");
 		printf("�������� Ҫ�¿���Ӱ���ı�� (��Ҫ���� 20)\n");
 		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)//�ж������Ƿ�Ϊ����
			continue;
		choice1 = atoi(a);
		if(A_screen_add_valid(choice1) ==0)//�ж�Ӱ���Ƿ��Ѿ����� 
			continue;
		if(choice1==0){//����0ʱȡ������ 
			return 0;
		}else if(choice1<0||choice1>20){//�ж������Ƿ�Խ�� 
			continue;
		}else{
			printf("�õģ�����ӵ��� %d����\n",choice1);
			break;
		}
	}
	while(1) //���Ӱ������ 
	{
		system("cls");
		printf("\n   ���ѿ���һ��Ӱ����\n");
		A_screen_check();//��ӡһ��Ӱ����Ϣ 
	 	printf("\n���������ʾ��������Ӱ������Ϣ��\n"
			 "ע�⣺Ӱ��һ�����Ӳ��ܸ��ģ�\n"
			 "��������δ���ע��ʱ���� 0 ������Ӱ�������ӣ�\n\n");
		printf("�������������ͣ�Imax/2D/3D/4D��\n");
 		printf(" Imax ���� 1\n"   
 			 " 2D   ���� 2\n"   
 			 " 3D   ���� 3\n"  
  			 " 4D   ���� 4\n");
		fflush(stdin);
		scanf("%s",b);
		if(judge_num(b)!=0)//�ж������Ƿ�Ϊ����
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
	//���Ӱ����Ϣ
	S_Message=fopen("ScreenMessage.txt","a");
	fprintf(S_Message,"%s  %d  %s\n",A_quanju.Cinema,choice1,Type);
	printf("�ѳɹ���Ӹ�Ӱ����\n");
	fclose(S_Message); 
	return 1;
}
 
int A_screen_add_valid(int room)//������Ա��ӵ�Ӱ���Ƿ���� 
{
	FILE * S_Message;//����Ӱ������Ϣ
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

//*************************************�û�����**************************************

//*************************************�û�������Ϣ��ѯ���޸ļ���ֵ****************************
void U_information(char id1[20])
{
	char id2[20],sex[10],tele[20],code1[20],code2[20],mail[50],name[20];
	double money,c;
	int b=0,a=0;
	char choice[20];
	printf("\n�������鿴��Ļ�����Ϣ��������1\n");
	printf("������������Ļ�����Ϣ��������2\n");
	printf("��������ֵ��������3\n ");
	printf("������뷵����һ���棬����������ֵ\n");
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
		case 1://�û��鿴������Ϣ 
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
		case 2://�û�������Ϣ 
		{
			U_change(id1);
			break;
		}
		case 3://��ֵ
		{ 
			FILE *UFile,*fp;
			UFile=fopen("users.txt","r");
			fp=fopen("user1.txt","w");
			while(1)
			{
				printf("\n�����������ֵ�Ľ��(��ֵ�����ͳ�ֵ����10%%)�� ");
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
			}//���µ���Ϣд��һ���µ��ļ� 
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

void U_change(char id1[20])//�û���Ϣ���� 
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
	char choice[20];//����û�ѡ�� 
	
	printf("\n�������������������������1\n");
	printf("��������������Ա�������2\n");
	printf("������������ĵ绰��������3\n");
	printf("����������������䣬������4\n");
	printf("����������������룬������5\n");
	printf("�������ע������ID��������6\n");
	printf("������뷵����һ���棬����������ֵ\n"); 
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
		   			printf("\n������������������\n");//�������� 
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
			 		printf("\n�������������Ա�\n");//�����Ա� 
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
					while ( b!=1 )//���벢��֤�绰 
         				{
            				printf("���������ĵ绰����:\n");
               				scanf("%s",U_quanju.Tele);
                            		if (U_quanju.Tele[11]!='\0') {printf("��ĵ绰���벻�Ϸ������������룺\n"); b=0;}	
 						else b=1;
						for (i=0;i<11;i++)
							if (U_quanju.Tele[i]<'0'||U_quanju.Tele[i]>'9') 
							{
								printf("���ĵ绰���벻�Ϸ������������룡\n");
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

//*************************************�û�������ѯ**************************************
void U_order(char id1[20])//������ѯ 
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
	
	printf("\n��������ѯ��Ķ�����������1\n");
	printf("�������ȡ��������������2\n");
	printf("������뷵����һ���棬����������ֵ\n");
	scanf("%d",&a); 
	switch(a)
	{
		case 1://�鿴������Ϣ 
			{
            FILE *fp;
	        fp=fopen("OrderMessage.txt","r");
			printf("Your orders are\n");
	         printf("������    �û�ID  ӰƬ���  ��ӰԺ   ��Ӱ��   Ӱ��   �к�  �к�  ����ʱ��         ɢ��ʱ��     ӰƬ����  ����    Ʊ��\n");
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
		case 2://ȡ������ 
			{
				float a;
                FILE *fp,*forder;
                fp=fopen("OrderMessage.txt","r");
                forder=fopen("order1.txt","w");
				printf("����������Ҫɾ�������Ķ�����:\n");
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
		      }//���µ���Ϣд��һ���µ��ļ� 
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
			}//���µ���Ϣд��һ���µ��ļ�
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
//***********************************��Ӱ��ѯ+��Ʊ******************************
void U_movie()
{	
	userQueryMenu();
} 
//**************����ʱ������********************
void rangetime(int choice)//����ʱ������ 
	{
		struct MovieMessage time_total[500];//����һ���ṹ������ 
		int n=0;//��Ҫ���򳡴����� 
		FILE *fp6;//��дtemp%d.txt�ļ� 
		struct MovieMessage quire;//��ʾ����������Ϣ 
		char filename[20];
		
		system("cls");//���� 
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
		//��ʱ��ӽ���Զ����
        int i; //һ��ѭ�� 
        int j;//����ѭ�� 
        struct MovieMessage t; //�м�ֵ  
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
       	   	printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//*******************��Ʊ����������**********************
void rangefeein(int choice)//��Ʊ���������� 
{
	    struct MovieMessage fee_total[500];//����һ���ṹ������ 
		int n=0;//��Ҫ������ܳ����� 
		FILE *fp6;//��дtemp&d.txt�ļ� 
		struct MovieMessage quire;//��ʾ����������Ϣ 
		char filename[20];
		
		system("cls");//���� 
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
		//��������
        int i; //һ��ѭ�� 
        int j; //����ѭ�� 
        struct MovieMessage t; //�м�ֵ
		 
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
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//**********************��Ʊ�۽�������*************************
void rangefeede(int choice)//��Ʊ�۽������� 
{
 
	    struct MovieMessage fee_total[500];//����һ���ṹ������ 
		int n=0;//��Ҫ������ܳ����� 
		FILE *fp6;//��дtemp&d.txt�ļ�
		struct MovieMessage quire;//��ʾ����������Ϣ
		char filename[20];
		
		system("cls");//���� 
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
		//�������� 
        int i; //һ��ѭ�� 
        int j; //����ѭ�� 
        struct MovieMessage t;//�м�ֵ  
        
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
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//**************************����Ʊ����������***********************
void rangerestin(int choice)//����Ʊ���������� 
{
	    struct MovieMessage rest_total[500];//����һ���ṹ������ 
		int n=0;//��Ҫ������ܳ����� 
		FILE *fp6;//��дtemp&d.txt�ļ�
		struct MovieMessage quire;//��ʾ����������Ϣ
		char filename[20];
		
		system("cls");//����  
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
		//��������
        int i; //һ��ѭ�� 
        int j;//����ѭ�� 
        struct MovieMessage t;//�м�ֵ  
        
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
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//*****************************����Ʊ����������***********************
void rangerestde(int choice)//����Ʊ���������� 
{
	    struct MovieMessage rest_total[500];//����һ���ṹ������ 
		int n=0;//��Ҫ������ܳ����� 
		FILE *fp6;//��дtemp&d.txt�ļ�
		struct MovieMessage quire;//��ʾ����������Ϣ
		char filename[20];
		
		system("cls");//���� 
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
		//�������� 
        int i;//һ��ѭ�� 
        int j;//����ѭ�� 
        struct MovieMessage t;//�м�ֵ
		  
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
 
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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

//**************************��Ӱ��Ϣ�������***********************
void paixujiemian(int choice)//��Ӱ��Ϣ�������
{
	int op=0;//ѡ�� 
    int f=1;//ѭ�� 
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
			case 1: rangetime(choice);//��ʱ�� 
					xuanpianchang();//�û�ѡ�񳡴� 
					break;
			case 2: rangefeein(choice);//��Ʊ������ 
					xuanpianchang();//�û�ѡ�񳡴� 
					break;
			case 3: rangefeede(choice);//��Ʊ�۽��� 
					xuanpianchang();//�û�ѡ�񳡴� 
					break;
			case 4: rangerestin(choice);//����Ʊ������ 
					xuanpianchang();//�û�ѡ�񳡴� 
					break;
			case 5: rangerestde(choice);//����Ʊ������ 
					xuanpianchang();//�û�ѡ�񳡴� 
					break;
			case 6: f=0;
					break;
			default:break;							
		}
    }
}

//********************************��Ʊ����******************************* 

//**************************�û�ѡƬ��****************
void xuanpianchang()//�û�ѡƬ��
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
	printf("\t\t*       ��ѡ������ۿ���Ƭ��������ӰƬ��ţ�     *\n");
	printf("\t\t*                                                *\n");        
	printf("\t\t*       ��ܰ��ʾ��������ҹ�����԰���Ż���!      *\n");        
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
		scanf("%s",movieID);//�����Ƭ�����
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
	fclose(fp1);//�ر��ļ� 
	 if(q==0)
 	{
 		printf("��ʾ�����ѹ�����ó��ε�ӰƱ\n");
  		system("pause");
 	}
 	buy(movieID);
} 

//**************************�˿͵�Ӱ��ѯ����************************ 
void userQueryMenu()//�˿͵�Ӱ��ѯ���� 
{
	int f=1;//ѭ�� 
	
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
		printf("\t\t\t\t6. ���ų����Ƽ�\n\n");
		printf("\t\t\t\t7. ����\n\n"); 
		printf("\t\t\t��ѡ�����Ĳ�ѯ��ʽ��");
		int choice;//ѡ��
		fflush(stdin);
        scanf("%d",&choice);
        getchar();
		switch(choice)
		{
		case 1:
				MovieNamequire(choice);//����ӰƬ�������� 
				break;
			case 2:
				Doublequire(choice);//����ӰƬ��+ӰԺ������ 
				break;
			case 3:
				Languagequire(choice);//���������������� 
				break;
			case 4:
				MovieTypequire(choice);//����ӰƬ��ӳ�������� 
				break;
			case 5:
				Cinemaquire(choice);//���յ�ӰԺ���� 
				break;
			case 6:
				MovieRecom();//���ų����Ƽ� 
				break;
			case 7:
				denglu();//���ص���½���� 
				break;
			default:
				break;
		}
	}
}
//*****************************����ӰƬ����ѯ******************** 
void MovieNamequire(int choice)//����ӰƬ����ѯ 
 
{
	FILE *fp6;//��дMovieMessagew.txt�ļ� 
	FILE *temp1;//��дtemp1.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ӱ��Ϣ 
	char typeinmoviename[10]; //�û������Ӱ���� 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *              1.ӰƬ����ѯ                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *          �ٶ��뼤��      ����������      *\n");
		printf("                 *          ���Ӳ�ϰ��      �����ܶ�Ա      *\n");
		printf("                 *          �����ط���      �������׸�      *\n");
		printf("                 *          ��Ů��Ұ��                      *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ����");
		scanf("%s",typeinmoviename);
		if(strcmp(typeinmoviename,"�ٶ��뼤��")!=0 &&  strcmp(typeinmoviename,"����������")!=0 &&
		strcmp(typeinmoviename,"���Ӳ�ϰ��")!=0 &&  strcmp(typeinmoviename,"�����ܶ�Ա")!=0 &&
		strcmp(typeinmoviename,"�����ط���")!=0 &&  strcmp(typeinmoviename,"�������׸�")!=0 &&
		strcmp(typeinmoviename,"��Ů��Ұ��")!=0)
		{
		printf("����������ȷӰƬ��\n"); 
		system("pause");
		userQueryMenu();
		}
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
		fp6=fopen("MovieMessage.txt","r");
		if(fp6==NULL)
		{
		  	printf("The file was not successfully opened.\n");
		 	exit(1);
		}
		temp1=fopen("temp1.txt","w");//�ѷ���ɸѡ���������ݷ���һ�����ļ� 
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
//***************************����ӰƬ�������Ͳ�ѯ*********************** 
void Languagequire(int choice)//����ӰƬ�������Ͳ�ѯ 

{
	FILE *fp6;//��дMovieMessagew.txt�ļ� 
	FILE *temp3;//��дtemp3.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ӱ��Ϣ 
	char typeinlanguage[10]; //�û������������� 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *               3.���Բ�ѯ                 *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             	  Chinese                   *\n");
		printf("                 *                                          *\n");
		printf("                 *             	  English                   *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ�������ͣ�");
		scanf("%s",typeinlanguage);
		if(strcmp(typeinlanguage,"Chinese")!=0 &&  strcmp(typeinlanguage,"English")!=0)
		{
		printf("����������ȷ��������\n"); 
		system("pause");
		userQueryMenu();
		}
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//******************************����ӰƬ��+ӰԺ����ѯ********************** 
void Doublequire(int choice)//����ӰƬ��+ӰԺ����ѯ 
 
{
	FILE *fp6;//��дMovieMessagew.txt�ļ� 
	FILE *temp2;//��дtemp2.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ӱ��Ϣ 
	char typeinmoviename[10]; //�û������Ӱ����
	char typeincinema[10]; //�û�����ӰԺ���� 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *            2.ӰƬ��+ӰԺ����ѯ           *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");
		printf("                 *                                          *\n");
		printf("                 *          �ٶ��뼤��      ����������      *\n");
		printf("                 *          ���Ӳ�ϰ��      �����ܶ�Ա      *\n");
		printf("                 *          �����ط���      �������׸�      *\n");
		printf("                 *          ��Ů��Ұ��                      *\n");
		printf("                 *                                          *\n");
		printf("                 *      ӰԺ��  Houde    Boxue    Mashi     *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ��ӰƬ����");
		scanf("%s",typeinmoviename);
		printf("������������Ȥ��ӰԺ����");
		scanf("%s",typeincinema);
		if(strcmp(typeinmoviename,"�ٶ��뼤��")!=0 &&  strcmp(typeinmoviename,"����������")!=0 &&
		strcmp(typeinmoviename,"���Ӳ�ϰ��")!=0 &&  strcmp(typeinmoviename,"�����ܶ�Ա")!=0 &&
		strcmp(typeinmoviename,"�����ط���")!=0 &&  strcmp(typeinmoviename,"�������׸�")!=0 &&
		strcmp(typeinmoviename,"��Ů��Ұ��")!=0 )
		{
			printf("����������ȷӰƬ��\n");
			system("pause");
			userQueryMenu();
		}
		if(strcmp(typeincinema,"Houde")!=0 &&  strcmp(typeincinema,"Boxue")!=0 &&
		strcmp(typeincinema,"Mashi")!=0)
		{
			printf("����������ȷ��ӰԺ��");
			system("pause");
			userQueryMenu();
		}
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//*************************���շ�ӳӰ�����Ͳ�ѯ********************** 
void MovieTypequire(int choice)//���շ�ӳӰ�����Ͳ�ѯ 
 
{
	FILE *fp6;//��дMovieMessagew.txt�ļ� 
	FILE *temp4;//��дtemp4.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ӱ��Ϣ 
	char typeinmovietype[10]; //�û�����Ӱ����ӳ���� 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *            4.��ӳӰ�����Ͳ�ѯ            *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *            2D   3D    4D   Imax          *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("������������Ȥ�ķ�ӳӰ�����ͣ�");
		scanf("%s",typeinmovietype);
		if(strcmp(typeinmovietype,"2D")!=0 &&  strcmp(typeinmovietype,"3D")!=0 &&
		strcmp(typeinmovietype,"4D")!=0 &&  strcmp(typeinmovietype,"Imax"))
		{
		printf("��������ȷ�ķ�ӳӰ������"); 
		system("pause");
		userQueryMenu();
		}
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//*************************����ӰԺ����ѯ******************** 
void Cinemaquire(int choice)//����ӰԺ����ѯ 
 
{
	FILE *fp6;//��дMovieMessagew.txt�ļ� 
	FILE *temp5;//��дtemp5.txt�ļ� 
	struct MovieMessage quire;//��ʾ������Ӱ��Ϣ 
	char typeincinema[10]; //�û������������� 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *              5.��ӰԺ��ѯ                *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             Houde   Boxue   Mashi        *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("��ѡ��������Ȥ��ӰԺ����");
		scanf("%s",typeincinema);
		if(strcmp(typeincinema,"Houde")!=0 &&  strcmp(typeincinema,"Boxue")!=0 &&
		strcmp(typeincinema,"Mashi")!=0)
		{
			printf("��������ȷ�ĵ�ӰԺ����");
			system("pause");
			userQueryMenu();
		}
		printf("|���α�� |��ӰԺ    |ӰƬ��    |����  |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
//*************************���ų����Ƽ�******************** 
void MovieRecom()//���ų����Ƽ� 

{
	FILE *tj;//��дMovieMessage.txt�ļ� 
	struct MovieMessage quire; //��ʾ������Ӱ��Ϣ 
	
		system("cls");//���� 
		printf("                 ********************************************\n");  
		printf("                 *                                          *\n");
		printf("                 *             �˿͵�Ӱ��ѯ����             *\n");
		printf("                 *                                          *\n");
		printf("                 *               ���ų����Ƽ�               *\n");
		printf("                 *                                          *\n");
		printf("                 ********************************************\n\n");
		printf("                 ********************************************\n");  
		printf("             *MashiӰԺ�¿�ҵ �Ƽ�ѡ��IMAXӰ�����������Ļ����������ʢ��*\n");
		printf("                 ********************************************\n");
		printf("|���α�� |��ӰԺ  |ӰƬ��    |����    |����ʱ��       |ɢ��ʱ��    |ӰƬ����  |����   |��Ʊ��|��Ʊ��  |������  |Ʊ�� \n");
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
	    if(strcmp("Imax",quire.type)==0&&strcmp("Boxue",quire.cinema)==0)//Boxue��ΪMashi 
			printf("    %3s     %s    %s    %s\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
		}
	  	rewind(tj);
		fclose(tj);
		system("pause");
}
//*************************ѡ��Ʊ����********************* 
void buy(char movieID[])//ѡ��Ʊ���� 
{	
	struct MovieMessage quire;
	int op=0;//��ʼ�� 
	int judge;//�ж��Ƿ�ΪImax 
	int i;//ɨ����һ�� 
    int f=1;//����ѭ�������� 
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
        fflush(stdin);//��������
        scanf("%d",&op);
        getchar();
        fp6=fopen("MovieMessage.txt","r");//���ļ� 
		if(fp6==NULL)//�ж��ļ��Ƿ���� 
		{
		printf("The file was not successfully opened.\n");
		exit(1);
		}
	    while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
		quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
		quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
		
	    if(strcmp(movieID,quire.movieID)==0)//Ѱ�����û�������ͬӰƬ��ŵ�ӰƬ��Ϣ 
		{
			if(quire.totalticket==100)
			judge=100;
			else
			judge=150;
			i++;
		}
	  	rewind(fp6);//�ѹ���Ƶ���� 
		fclose(fp6);//�ر��ļ� 
        switch(op)
		{
			case 1:	if(judge==100)
					chazuo100(movieID);//������λΪ10*10���� 
					else
					chazuo150(movieID);//������λΪ10*15���� 
					break;
			case 2: U_movie();
					//����
					break;
			default: break;//��ֹ�û���������						
		}
        
    }
}
//**************************��ѯ10*10��λ********************* 
void chazuo100(char movieID[])//��ѯ10*10��λ 
{
	char a[20]={'\0'};//����û����� 
	system("cls");//���� 
	int i,j;//ѭ���� 
	int goupiao;//�û���Ʊ�� 
	char seat[20]; 
	sprintf(seat, "%s.txt", movieID);//ʹ�����ɵ���λ���ļ�����ӰƬ�����ͬ 
	if((fp5 = fopen(seat,"r")) == NULL)//�ж��ļ��Ƿ���� 
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");//ɨ���ļ� 
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
	for(i=0;i<10;i++)//����λ��Ϣ���ڽ������Թ��û���ѯѡ�� 
	{
		for(j=0;j<10;j++)
		{
		printf("[%d] ",arr100[i][j]);
		}
	printf("\n");
	}
	printf("\n������ȡ����Ʊ��������0��");
	printf("\n��������Ҫ���Ʊ����:");
 	while(1)	//���빺Ʊ��
	{
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)
			continue; 
		goupiao = atoi(a);
		break;
	} 
 	maipiao100(goupiao,movieID);//���ݹ�Ʊ�����û�ѡ���ӰƬ��� 
}
//***************************��ѯ10*15��λ******************** 
void chazuo150(char movieID[])//��ѯ10*15��λ 
{
	char a[20]={'\0'};//����û����� 
	system("cls");//���� 
	int i,j;//ѭ���� 
	int goupiao;//�û���Ʊ�� 
	char seat[20];
	sprintf(seat, "%s.txt", movieID);//ʹ�����ɵ���λ���ļ�����ӰƬ�����ͬ 
	if((fp5 = fopen(seat,"r")) == NULL)//�ж��ļ��Ǹ������ 
	fp5=fopen(seat,"w");				
	else
	fp5=fopen(seat,"r");//ɨ���ļ� 
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
	for(i=0;i<10;i++)//����λ��Ϣ���ڽ������Թ��û���ѯѡ�� 
	{
		for(j=0;j<15;j++)
		{
		printf("[%d] ",arr150[i][j]);
		}
	printf("\n");
	}
	printf("\n������ȡ����Ʊ��������0��");
	printf("\n��������Ҫ���Ʊ����:");
 	while(1)	//���빺Ʊ��
	{
		fflush(stdin);
		scanf("%s",a);
		if(judge_num(a)!=0)
			continue; 
		goupiao = atoi(a);
		break;
	} 
 	maipiao150(goupiao,movieID);//���ݹ�Ʊ�����û�ѡ���ӰƬ���
}
//**************************10*10��λ�Ƽ�********************** 
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
//**********************10*15��λ�Ƽ�*************************
void zuoweituijian150()//10*15��λ�Ƽ�
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

//*****************************ѡ��10*10��λ��Ʊ************************* 
int maipiao100(int goupiao,char movieID[])//ѡ����λ��Ʊ
{	
	FILE *fp3;
	FILE *fp4;
	FILE *fp2;
	FILE *fpc;
	int restticket;
	float fee,yue;//Ʊ�ۣ�Ʊ��*��Ʊ������� 
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
	if(fp6==NULL)//�ж��ļ��Ƿ���� 
	{
		printf("The file was not successfully opened.\n");
		exit(1);
	}
	while((fscanf(fp6,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
	quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
	quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
	{
		if(strcmp(quire.movieID,movieID)==0)//�ȶ��û�ѡ���ӰƬ��ź���Ϣ�е�ӰƬ��� 
		{restticket=quire.restticket;//�ҳ��ó���Ӱ����Ʊ�� 
		fee=quire.fee;//�ҳ��ó���Ӱ��Ʊ�� 
		i++;}//ɨ����һ�� 
	}
	rewind(fp6);
	fclose(fp6);//�ر��ļ� 

	fpc=fopen("users.txt","r");
	while(fscanf(fpc,"%s  %s  %s  %s  %s  %lf  %s",user.ID,user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
	{
		if(strcmp(U_quanju.ID,user.ID)==0)
		yue=user.Money;//�ҳ��û���� 
	}
	if(yue<(fee*goupiao))//�Ƚ��û�������Ʊ�� 
	{
		printf("���㣬������ֵ���������\n");		 
		system("pause");
		U_movie();
	} 

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
			case 1: zuoweituijian100();//����10*10��Ϊ�Ƽ�ϵͳ 
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
				printf("������ѡ���淶����ESC������\n");//���ܿ�һ����λѡ�� 
	 			check=1;
			}
		 	else if(arr100[row[goupiao]-1][line[goupiao]+1]==1 && arr100[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("������ѡ���淶����ESC������\n");//���ܿ�һ����λѡ�� 
				check=1; 
			}
		}
		if(check == 0) //check=0�ɹ���Ʊ 
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
				//�Ȱ��û���Ϣ���Ƶ�copyusers.txt����	
				fp3=fopen("users.txt","r");//��ֻ���ķ�ʽ���ļ�
				fp4=fopen("copyusers.txt","w");//��д�ķ�ʽ���ļ�
				if(fp3==NULL)//�ж��ļ��Ƿ�Ϊ�� 
				{
 					printf("The file was not successfully opened.\n");
		 			exit(1);
				}
				while(fscanf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					if(strcmp(user.ID,U_quanju.ID)==0)//�ҳ����û��ĸ�����Ϣ 
					{
						user.Money=user.Money-fee;
					}
					fprintf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}				
				fclose(fp3);//�ر��ļ�
				fclose(fp4);//�ر��ļ�
				//�ѸĹ����ĵ��û���Ϣ��ص�users.txt 
				fp3=fopen("users.txt","w");
				fp4=fopen("copyusers.txt","r");
				while(fscanf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}
				fclose(fp3);//�ر��ļ�
				fclose(fp4);//�ر��ļ�
					//��MovieMessage.txt���Ƶ�copyMovieMessage.txt���� 
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
					//�Ѹĺõ���Ʊ��Ϣ������д��MovieMessage.txt���� 
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
					fclose(fp6);//�ر��ļ�
					fclose(fp2);//�ر��ļ�
					//�����ܵĶ��� 
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
					fclose(fp6);//�ر��ļ� 
					fclose(fp7);//�ر��ļ� 
			}
			printf("��Ʊ�ɹ�!��ESC������\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
//**************************ѡ��10*15��λ��Ʊ********************* 
int maipiao150(int goupiao,char movieID[])//ѡ����λ��Ʊ
{	
	FILE *fp3;
	FILE *fp4;
	FILE *fp2;
	FILE *fpc;
	int restticket;//��Ʊ�� 
	float fee,yue;//Ʊ�ۣ���� 
	char seat[20];
	struct Order order;
	struct MovieMessage quire;
	struct U_Message user;
	sprintf(seat, "%s.txt", movieID);
	int check = 0;//����Ƿ�ѡ����� 
	int i,j;//ѭ���� 
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
		if(strcmp(quire.movieID,movieID)==0)//�ȶ��û�ѡ���ӰƬ��ź���Ϣ�е�ӰƬ���
		{restticket=quire.restticket;//�ҳ���Ʊ�� 
		fee=quire.fee;//�ҳ�Ʊ�� 
		i++;}//ɨ����һ�� 
	}
	rewind(fp6);//�ѹ���ƻ��ļ���ͷ 
	fclose(fp6);//�ر��ļ� 
	fpc=fopen("users.txt","r");
	while(fscanf(fpc,"%s  %s  %s  %s  %s  %lf  %s",user.ID,user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
	{
		if(strcmp(U_quanju.ID,user.ID)==0)//�ҳ����û��ĸ�����Ϣ 
		yue=user.Money;//�ҳ����û������ 
	}
	if(yue<fee*goupiao)//�Ƚ��û�������Ʊ��
	{
		printf("���㣬������ֵ���������");		 
		system("pause");
		U_movie();
	} 

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
				printf("������ѡ���淶����ESC������\n");//���ܿ�һ����λѡ�� 
	 			check=1;
			}
		 	else if(arr150[row[goupiao]-1][line[goupiao]+1]==1 && arr150[row[goupiao]-1][line[goupiao]]==0)
			{
				printf("������ѡ���淶����ESC������\n");//���ܿ�һ����λѡ�� 
				check=1; 
			}
		}
		if(check == 0)//check=0��Ʊ�ɹ� 
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
				//�Ȱ��û���Ϣ���Ƶ�copyusers.txt���棬���޸���� 
				fp3=fopen("users.txt","r");//��ֻ���ķ�ʽ���ļ� 
				fp4=fopen("copyusers.txt","w");//��д�ķ�ʽ���ļ� 
				if(fp3==NULL)//�ж��ļ��Ƿ�Ϊ�� 
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
				fclose(fp3);//�ر��ļ� 
				fclose(fp4);//�ر��ļ� 
				//���޸Ĺ������ĸ�����Ϣд�ص�users.txt�� 
				fp3=fopen("users.txt","w");//��д�ķ�ʽ���ļ�
				fp4=fopen("copyusers.txt","r");//��ֻ���ķ�ʽ���ļ�
				while(fscanf(fp4,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
				user.Name,user.Sex,user.Tele,user.Code,&user.Money,user.Mail)!=EOF)
				{
					fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s",user.ID,
					user.Name,user.Sex,user.Tele,user.Code,user.Money,user.Mail);
					i++;
				}
				fclose(fp3);//�ر��ļ� 
				fclose(fp4);//�ر��ļ� 
				//��MovieMessage.txt���Ƶ�copyMovieMessage.txt���� 
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
							 quire.restticket--;//��Ʊ����1 
						}
						fprintf(fp2,"%s  %s  %s  %s  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
					quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
					quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
					i++;
					}
					fclose(fp6);//�ر��ļ� 
					fclose(fp2);//�ر��ļ� 
					//���޸Ĺ���copyMovieMessage.txtд�ص�MovieMessage.txt���� 
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
					fclose(fp6);//�ر��ļ� 
					fclose(fp2);//�ر��ļ� 
					//�����ܶ��� 
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
		  			rewind(fp6);//�ѹ���ƻ��ļ���ʼ�� 
					fclose(fp6);//�ر��ļ� 
					fclose(fp7);//�ر��ļ� 
			}
			printf("��Ʊ�ɹ�!��ESC������\n");
		}
	}
    fflush(stdin);
    int op=_getche();
	return 0;
} 
//*************************************���ߺ���**************************************
int judge_num(char num[])//�ж��Ƿ�Ϊ���� 
{
	int valid = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(isdigit(num[i])) continue;
		else
		{
			printf("���������֣�\n");
			valid = 1;
			break;
		}
	}
	return valid;//����ֵΪ0������������ȷ 
} 

int judge_kongge(char num[])//�ж��Ƿ��пո� 
{
	int valid = 0,i;
	for(i = 0;i<strlen(num);i++)
	{
		if(int(num[i]) == 32)
		{
			printf("�벻Ҫ����ո�\n");
			getchar();
			getchar();
			valid = 1;
			break;
		}
	}
	return valid;//����ֵΪ0������������ȷ 
}
void U_modify()//�޸��û��ļ� 
{
	FILE *UFile,*fp;
	UFile=fopen("users.txt","w");
	    fp=fopen("user1.txt","r");//���������ļ������޸ĺ��ļ�����Ԫ�ļ� 
	char id2[20],sex[10],tele[20],code2[20],mail[50],name[20];   
	double money; 
	    while(fscanf(fp,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
	    {
	    	fprintf(UFile,"%s  %s  %s  %s  %s  %lf  %s",id2,name,sex,tele,code2,money,mail);
		}
		fclose(UFile);
		 fclose(fp);
}
void A_modify()//�޸��û��ļ� 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","w");
 	fp=fopen("administrators1.txt","r");//���������ļ������޸ĺ��ļ�����Ԫ�ļ� 
	char id2[20],cinema[20],code2[20],mail[50],name[20];   
	    while(fscanf(fp,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
	    {
	    	fprintf(AFile,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);
		}
		fclose(AFile);
		 fclose(fp);
}
int chachong(char ID2[],int y)//ע��ʱ����Ϣ���� 
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
					printf("�Բ�������ID�Ѿ���ע�ᣬ�����������µ�ID��\n");
					return 0;
				}                   
   			}
			break;
		case 2:
			if((fp=fopen("users.txt","a+"))==NULL)
			{
				printf("Failed to open the file��users.txt\n");
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
						printf("�Բ�������ID�Ѿ���ע�ᣬ�����������µ�ID��\n");
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
	printf("��ǰʱ�䣺%d��%d��%d��%dʱ%d��%d��\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
}
