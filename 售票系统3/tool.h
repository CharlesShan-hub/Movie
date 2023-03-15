//*************************************工具函数**************************************
void init(){//初始化
  #ifdef _WIN32
    #define TYPE 1
  #elif __APPLE__
    #define TYPE 2
  #endif
  for(int i=0; i<32;i++){
    U_quanju.ID[i]='\0';
    U_quanju.Name[i]='\0';
    U_quanju.Sex[i]='\0';
    U_quanju.Tele[i]='\0';
    U_quanju.Code[i]='\0';
    U_quanju.Mail[i]='\0';
    A_quanju.ID[i]='\0';
    A_quanju.Name[i]='\0';
    A_quanju.Cinema[i]='\0';
    A_quanju.Code[i]='\0';
    A_quanju.Mail[i]='\0';
  }
  //检查文件存在
  FILE *f;
  f=fopen("ScreenMessage.txt","a+");//影厅信息表
  fclose(f);
  f=fopen("MovieMessage.txt","a+");//电影信息表
  fclose(f);
  f=fopen("OrderMessage.txt","a+");//订单信息表
  fclose(f);
}

void clear_screen(){//清屏
  if(TYPE==1){
    system("cls");
  }else if(TYPE==2){
    system("clear");
  }else{
    printf("Unknown System\n");
    system("cls");
  }
}
int get_choice(char* str, int start, int end){//获取正确用户数字选择
  int choice;      // 记录用户选择
  char input[32];  // 获取用户输入
  int num_temp=false,range_temp=false;//错误提示
  while(true){
    clear_screen();
    printf("%s",str);
    if(num_temp){printf("请输入数字!\n");num_temp=false;}
    if(range_temp){printf("请输入正确的数字!\n");range_temp=false;}
    fflush(stdin);
    scanf("%s",input);
    num_temp = judge_num(input);
    if(num_temp) continue;
    range_temp=!((choice=judge_choice(input,start,end))!=-1);
    if(range_temp) continue;
    return choice;
  }
}
int get_choice_show_screen(char* str_title,char* str, int start, int end){//获取正确用户数字选择(显示影厅特别版)
  int choice;      // 记录用户选择
  char input[32];  // 获取用户输入
  int num_temp=false,range_temp=false;//错误提示
  while(true){
    clear_screen();
    printf("%s",str_title);
    printf("您已开设以下影厅：\n");
    A_screen_check();//打印一遍影厅信息 
    printf("\n%s",str);
    if(num_temp){printf("请输入数字!\n");num_temp=false;}
    if(range_temp){printf("请输入正确的数字!\n");range_temp=false;}
    fflush(stdin);
    scanf("%s",input);
    num_temp = judge_num(input);
    if(num_temp) continue;
    range_temp=((choice=judge_choice(input,start,end))==-1);
    if(range_temp) continue;
    return choice;
  }
}


int judge_choice(char* input, int start, int end){//判断是否为正确数字
  int choice = atoi(input);
  if(choice>end||choice<start) return -1;
  else return choice;
}
int judge_num(char num[])//判断是否为数字 
{
  int valid = 0,i;
  for(i = 0;i<strlen(num);i++)
  {
    if(isdigit(num[i])) continue;
    else
    {
      //printf("请输入数字！\n");
      //getchar();
      //getchar();
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
  char id2[20],sex[10],tele[20],code2[20],mail[50],name[20],money[20];   
      while(fscanf(fp,"%s  %s  %s  %s  %s  %s  %s",id2,name,sex,tele,code2,money,mail)!=EOF)
      {
        fprintf(UFile,"%s  %s  %s  %s  %s  %s  %s\n",id2,name,sex,tele,code2,money,mail);
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
      while(fscanf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail)!=EOF)
      {
        fprintf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail);
    }
    fclose(AFile);
     fclose(fp);
}
int id_duplicate_check(char ID2[],int type)//注册时的信息查重 
{
  // 打开文件
  FILE *fp;
  if(type==1)
    fp = fopen("administrators.txt","r");
  else
    fp = fopen("users.txt","r");
  if(fp==NULL){
    printf("Failed to open the file\n");
    return 1; 
  }
  // 查重
  U_Message testU;
  A_Message testA;
  if(type==1){
    while (fscanf(fp,"%s  %s  %s  %s  %s",testA.ID,testA.Name,testA.Cinema,testA.Code,testA.Mail) != EOF){
      if (!strcmp(ID2,testA.ID)) {fclose(fp); return 1;}
    }
    fclose(fp);
    return 0;
  }else{
    while (fscanf(fp,"%s  %s  %s  %s  %s  %lf  %s",testU.ID,testU.Name,testU.Sex,testU.Tele,testU.Code,&testU.Money,testU.Mail) != EOF)
      if (!strcmp(ID2,testU.ID)) {fclose(fp); return 1;}
    fclose(fp);
    return 0;
  }
}

void showtime()
{
  time_t timep;
  struct tm *p;
  time (&timep);
  p=gmtime(&timep);
  printf("当前时间：%d年%d月%d日%d时%d分%d秒\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
}

// 判断是闰年
bool is_leap_year(int year){
  if(year%4) return false;
  if(year%400==0) return true;
  if(year%100==0) return false;
  return true;
}