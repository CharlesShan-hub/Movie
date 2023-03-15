//*************************************用户操作**************************************

void U_function()//用户主界面
{
  char temp_str[] = "************ 用户 - 主界面 ****************\n\n"
 "如果您想查看您的信息, 请输入1\n"
 "如果您想搜索电影, 请输入2\n"
 "如果您想查看您的订单, 请输入3\n"
 "如果您想要退出      ,请输入4\n";
 bool loop = true;
  while(loop)
  {
    switch(get_choice(temp_str,1,4)){
      case 1:loop = U_information(); /*用户个人信息*/  
        break;
      case 2: U_movie();/*用户搜索电影*/
        break;
      case 3: U_order();/*用户订单管理*/  
        break;
      default:
        return;
    }
  }
}

//*************************************用户个人信息查询及修改及充值****************************
//用户个人信息主函数
bool U_information(){
  char temp_str[] = "************ 用户 - 个人信息 ****************\n\n"
 "如果你想查看你的基本信息，请输入1\n"
 "如果你想更改你的基本信息，请输入2\n"
 "如果你想充值，请输入3\n"
 "如果你想返回上一界面，请输入4\n";
  bool loop=true;
  while(loop)
  {
    switch(get_choice(temp_str,1,4)){
      case 1://用户查看基本信息 
        U_check();
        break;
      case 2://用户更改信息 
        loop = U_change();
        break;
      case 3://充值
        U_recharge();
        break;
      default:
        return true;
    }
  }
  return false;
}

//用户信息查看
void U_check(){
  // 定义变量与打开文件
  U_Message info,temp;
  FILE *file = fopen("users.txt","r");
  if(file==NULL){
    printf("Failed to Open users.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  // 打印提示信息与个人信息
  clear_screen();
  char temp_str[] = "************ 用户 - 个人信息 - 查看****************\n\n"
 "如果你想查看你的基本信息，请输入1\n"
 "如果你想更改你的基本信息，请输入2\n"
 "如果你想充值，请输入3\n"
 "如果你想返回上一界面，请输入4\n";
  printf("%s",temp_str);
  // 显示充值后的信息
  printf("id          name        sex   tele        money          mail \n");
  printf("%-12s%-12s%-6s%-12s%lf  %-12s\n",U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Money,U_quanju.Mail);
  printf("按任意键继续\n");
  fflush(stdin);
  getchar();
}

//用户充值
void U_recharge(){
  // 定义变量与打开文件
  U_Message info;
  info.Money = 0;
  FILE *file_from = fopen("users.txt","r");
  FILE *file_to = fopen("user1.txt","w");
  if(file_from==NULL){
    printf("Failed to Open users.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  if(file_to==NULL){
    printf("Failed to Open user1.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  // 选择信息修改内容
  clear_screen();
  char temp_str[] = "************ 用户 - 个人信息 - 充值 ****************\n\n"
 "请输入你想充值的金额\n"
 "(一次性充值大于200，可赠送超出部分的10%%)\n"
 "(一次性最多充值1000元，请您理智消费)\n"
 "返回可以输入1\n";
  double addition=0;
  while(true){
    addition = (double)(get_choice(temp_str,1,1000));
    if(addition<2)
      break;
    else if(addition>200)
      addition += (double)(addition-200) * 0.1;
    U_quanju.Money += addition;
    while(fscanf(file_from,"%s  %s  %s  %s  %s  %lf  %s\n",\
      info.ID,info.Name,info.Sex,info.Tele,info.Code,&info.Money,info.Mail)!=EOF)
      if(strcmp(U_quanju.ID,info.ID)==0)
        fprintf(file_to,"%s  %s  %s  %s  %s  %lf  %s\n",\
        info.ID,info.Name,info.Sex,info.Tele,info.Code,U_quanju.Money,info.Mail);
      else
        fprintf(file_to,"%s  %s  %s  %s  %s  %lf  %s\n",\
        info.ID,info.Name,info.Sex,info.Tele,info.Code,info.Money,info.Mail);
    fclose(file_to);
    fclose(file_from);
    U_modify();
    // 显示充值后的信息
    printf("id          name        sex   tele        money          mail \n");
    printf("%-12s%-12s%-6s%-12s%lf  %-12s\n",U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Money,U_quanju.Mail);
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
  }
}

//用户信息更改 
bool U_change(){
  // 定义变量与打开文件
  U_Message info,temp;
  int delete_flag = false;
  FILE *file_from = fopen("users.txt","r");
  FILE *file_to = fopen("user1.txt","w");
  if(file_from==NULL){
    printf("Failed to Open users.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return true;
  }
  if(file_to==NULL){
    printf("Failed to Open user1.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return true;
  }
  // 选择信息修改内容
  clear_screen();
  char temp_str[] = "************ 用户 - 个人信息 - 修改 ****************\n\n"
  "如果你想更改你的姓名，请输入1\n"
  "如果你想更改你的性别，请输入2\n"
  "如果你想更改你的电话，请输入3\n"
  "如果你想更改你的邮箱，请输入4\n"
  "如果你想更改你的密码，请输入5\n"
  "如果你想注销您的ID，请输入6\n"
  "如果你想返回上一界面，请输入7\n"
  "任意位置输入EOF可以取消修改\n";
  char temp_str2[] = "************ 用户 - 个人信息 - 修改 ****************\n\n"
  "如果你[确][认][注][销]ID，请输入1\n"
  "如果你想再看看，请输入2\n";
  while(true){
    // 更新信息
    delete_flag = false;
    switch(get_choice(temp_str,1,7)){
      case 1://修改姓名
        printf("\n请输入您的新姓名：\n");//输入姓名 
        fflush(stdin);
        scanf("%s",temp.Name);
        if(!strcmp(temp.Name,"EOF")) continue;
        strcpy(U_quanju.Name,temp.Name);
        break;
      case 2://修改性别
        printf("\n请输入您的新性别：\n");//输入性别
        fflush(stdin);
        scanf("%s",temp.Sex);
        if(!strcmp(temp.Sex,"EOF")) continue;
        strcpy(U_quanju.Sex,temp.Sex);
        break;
      case 3://修改电话
        if(regist_get_tel()) continue;
      case 4://修改邮箱
        if(regist_get_mail(1)) continue;
        break;
      case 5://修改密码
        if(regist_get_code(1)) continue;
        break;
      case 6://注销账户 - 直接退出登录
        while(!delete_flag)
          switch(get_choice(temp_str2,1,2)){
            case 1:delete_flag = true;break;
            case 2:break;
          }
        break;
      default:
        return true;
    }
    // 保存信息
    while(fscanf(file_from,"%s  %s  %s  %s  %s  %lf  %s\n",\
      info.ID,info.Name,info.Sex,info.Tele,info.Code,&info.Money,info.Mail)!=EOF)
      if(strcmp(U_quanju.ID,info.ID)==0)
        if(delete_flag)continue;
        else fprintf(file_to,"%s  %s  %s  %s  %s  %lf  %s\n",\
          U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Code,U_quanju.Money,U_quanju.Mail);
      else
        fprintf(file_to,"%s  %s  %s  %s  %s  %lf  %s\n",\
        info.ID,info.Name,info.Sex,info.Tele,info.Code,info.Money,info.Mail);
    fclose(file_to);
    fclose(file_from);
    U_modify();
    if(delete_flag)return false;
    // 显示充值后的信息
    printf("id          name        sex   tele        money          mail \n");
    printf("%-12s%-12s%-6s%-12s%lf  %-12s\n",U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Money,U_quanju.Mail);
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return true;
  }
}

//*************************************用户订单查询**************************************
//订单查询 
void U_order(){
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
          if(strcmp(U_quanju.ID,id2)==0)
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
          if(strcmp(U_quanju.ID,id2)==0)
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
          if(strcmp(U_quanju.ID,id2)==0)
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
        while(fscanf(UFile,"%s  %s  %s  %s  %s  %f  %s",id2,name,sex,tele,code2,&money,mail)!=EOF)
          {
      if(strcmp(U_quanju.ID,id2)==0)
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
        while(fscanf(fmovie,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee)!=EOF)
        {
            if(strcmp(quire.movieID,movieid)!=0)
            {
              fprintf(fa,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
          }
          else
          {
            quire.restticket=quire.restticket+1;
            quire.ratio=(quire.totalticket-quire.restticket)/quire.totalticket;
            fprintf(fa,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
          }
      }//将新的信息写入一个新的文件
      fclose(fmovie);
        fclose(fa);
        fmovie=fopen("MovieMessage.txt","w");
        fa=fopen("MovieMessage1.txt","r");
        while(fscanf(fa,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee)!=EOF)
        fprintf(fmovie,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f\n",quire.movieID,quire.cinema,quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
        fclose(fmovie);
        fclose(fa);
      sprintf(seat, "%s.txt", movieid);   
      if(strcmp(type,"Imax")==0)
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
      printf("删除订单操作完成，请您自行核对订单信息\n");  
      break;  
      }
      default:
      U_information();
            break;
  }
}

//***********************************电影查询+购票******************************
void U_movie(){ 
  userQueryMenu();
} 
//**************按照时间排序********************
void rangetime(int choice)//按照时间排序 
  {
    MovieMessage time_total[500];//声明一个结构体数组 
    int n=0;//需要排序场次总数 
    FILE *fp6;//读写temp%d.txt文件 
    MovieMessage quire;//表示单个场次信息 
    char filename[20];
    
    system("cls");//清屏 
    sprintf(filename, "temp%d.txt",choice);
    fp6=fopen(filename,"r");
    if(fp6==NULL)
    {
        printf("The file was not successfully opened.\n");
      exit(1);
    }
    while((fscanf(fp6,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    { 
      strcpy(time_total[n].movieID,quire.movieID);
      strcpy(time_total[n].cinema,quire.cinema);
      strcpy(time_total[n].moviename,quire.moviename);
      time_total[n].room=quire.room;
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
        MovieMessage t; //中间值  
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
          printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",time_total[i].movieID,time_total[i].cinema,time_total[i].moviename,
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
    MovieMessage fee_total[500];//声明一个结构体数组 
    int n=0;//需要排序的总场次数 
    FILE *fp6;//读写temp&d.txt文件 
    MovieMessage quire;//表示单个场次信息 
    char filename[20];
    
    system("cls");//清屏 
    sprintf(filename, "temp%d.txt",choice); 
    fp6=fopen(filename,"r");
    if(fp6==NULL)
    {
        printf("The file was not successfully opened.\n");
      exit(1);
    }
      while((fscanf(fp6,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      fee_total[n].fee=quire.fee;
      strcpy(fee_total[n].movieID,quire.movieID);
      strcpy(fee_total[n].cinema,quire.cinema);
      strcpy(fee_total[n].moviename,quire.moviename);
      fee_total[n].room=quire.room;
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
        MovieMessage t; //中间值
     
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
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
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
 
    MovieMessage fee_total[500];//声明一个结构体数组 
    int n=0;//需要排序的总场次数 
    FILE *fp6;//读写temp&d.txt文件
    MovieMessage quire;//表示单个场次信息
    char filename[20];
    
    system("cls");//清屏 
    sprintf(filename, "temp%d.txt",choice); 
    fp6=fopen(filename,"r");
    if(fp6==NULL)
    {
        printf("The file was not successfully opened.\n");
      exit(1);
    }
      while((fscanf(fp6,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      fee_total[n].fee=quire.fee;
      strcpy(fee_total[n].movieID,quire.movieID);
      strcpy(fee_total[n].cinema,quire.cinema);
      strcpy(fee_total[n].moviename,quire.moviename);
      fee_total[n].room=quire.room;
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
        MovieMessage t;//中间值  
        
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
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",fee_total[i].movieID,fee_total[i].cinema,fee_total[i].moviename,
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
    MovieMessage rest_total[500];//声明一个结构体数组 
    int n=0;//需要排序的总场次数 
    FILE *fp6;//读写temp&d.txt文件
    MovieMessage quire;//表示单个场次信息
    char filename[20];
    
    system("cls");//清屏  
    sprintf(filename, "temp%d.txt",choice); 
    fp6=fopen(filename,"r");
    if(fp6==NULL)
    {
        printf("The file was not successfully opened.\n");
      exit(1);
    }
      while((fscanf(fp6,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      rest_total[n].fee=quire.fee;
      strcpy(rest_total[n].movieID,quire.movieID);
      strcpy(rest_total[n].cinema,quire.cinema);
      strcpy(rest_total[n].moviename,quire.moviename);
      rest_total[n].room=quire.room;
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
        MovieMessage t;//中间值  
        
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
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
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
    MovieMessage rest_total[500];//声明一个结构的数组 
    int n=0;//需要排序的总场次数 
    FILE *fp6;//读写temp&d.txt文件
    MovieMessage quire;//表示单个场次信息
    char filename[20];
    
    system("cls");//清屏 
    sprintf(filename, "temp%d.txt",choice); 
    fp6=fopen(filename,"r");
    if(fp6==NULL)
    {
        printf("The file was not successfully opened.\n");
      exit(1);
    }
      while((fscanf(fp6,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      rest_total[n].fee=quire.fee;
      strcpy(rest_total[n].movieID,quire.movieID);
      strcpy(rest_total[n].cinema,quire.cinema);
      strcpy(rest_total[n].moviename,quire.moviename);
      rest_total[n].room=quire.room;
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
        MovieMessage t;//中间值
      
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
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",rest_total[i].movieID,rest_total[i].cinema,rest_total[i].moviename,
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
  char movieID[5]="";
  Order A_kan;
  MovieMessage quire;
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
  while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
  char str[] = ""
    "                 ********************************************\n"
    "                 *                                          *\n"
    "                 *             顾客电影查询界面             *\n"
    "                 *                                          *\n"
    "                 *                                          *\n"
    "                 ********************************************\n"
    "\t\t\t\t1. 按影片名查询\n\n"
    "\t\t\t\t2. 按影片名+影院名查询\n\n"
    "\t\t\t\t3. 按语言类型查询\n\n"
    "\t\t\t\t4. 按放映影厅类型查询\n\n"
    "\t\t\t\t5. 按电影院查询\n\n"
    "\t\t\t\t6. 热门场次推荐\n\n"
    "\t\t\t\t7. 返回\n\n"
    "\t\t\t请选择您的查询方式：";
  while(true){
    switch(get_choice(str,1,7))
    {
    case 1:
        MovieNamequire(1);//按照影片名字搜索 
        break;
      case 2:
        Doublequire(2);//按照影片名+影院名搜索 
        break;
      case 3:
        Languagequire(3);//按照语言类型搜索 
        break;
      case 4:
        MovieTypequire(4);//按照影片放映类型搜索 
        break;
      case 5:
        Cinemaquire(5);//按照电影院搜索 
        break;
      case 6:
        MovieRecom();//热门场次推荐 
        break;
      default:
        return;
    }
  }
}
//*****************************按照影片名查询******************** 
void MovieNamequire(int choice)//按照影片名查询
{
  FILE *fp6;//读写MovieMessagew.txt文件 
  FILE *temp1;//读写temp1.txt文件 
  MovieMessage quire;//表示单场电影信息 
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %3d  %3d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      if(strcmp(typeinmoviename,quire.moviename)==0)
      {
      fprintf(temp1,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%g\t%g\n",quire.movieID,quire.cinema,
    quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire;//表示单场电影信息 
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
    printf("                 *                Chinese                   *\n");
    printf("                 *                                          *\n");
    printf("                 *                English                   *\n");
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    
      if(strcmp(typeinlanguage,quire.language)==0)
      {
      fprintf(temp3,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire;//表示单场电影信息 
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    
      if(strcmp(typeinmoviename,quire.moviename)==0&&strcmp(typeincinema,quire.cinema)==0)
      {
      fprintf(temp2,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire;//表示单场电影信息 
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    
      if(strcmp(typeinmovietype,quire.type)==0)
      {
    fprintf(temp4,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire;//表示单场电影信息 
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    
      if(strcmp(typeincinema,quire.cinema)==0)
      {
    fprintf(temp5,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire; //表示单场电影信息 
  
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
      while((fscanf(tj,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
    quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
    {
      if(strcmp("Imax",quire.type)==0&&strcmp("Boxue",quire.cinema)==0)//Boxue改为Mashi 
      printf("    %3s     %s    %s    %d\t%s\t%s    %4s     %s   %3d    %3d    %.3f   %.2f\n",quire.movieID,quire.cinema,
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
  MovieMessage quire;
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
      while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
    quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
      case 1: if(judge==100)
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
  int i,j;//循环数 
  for(i=0;i<10;i++)
    { 
      for(j=0;j<10;j++)
      {
      arr100[i][j]=0;
    }
    }
  char a[20]={'\0'};//获得用户输入 
  system("cls");//清屏 
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
  while(1)  //输入购票数
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
  int i,j;//循环数   
    for(i=0;i<10;i++)
    { 
      for(j=0;j<15;j++)
      {
      arr100[i][j]=0;
    }
    }
  char a[20]={'\0'};//获得用户输入 
  system("cls");//清屏 
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
  while(1)  //输入购票数
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
  Order order;
  MovieMessage quire;
  U_Message user;
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
  while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
          //int op=_getche();
          char op=getchar();
      return 0;
      }
    while(goupiao>3)
    {
    printf("但是您无法一次购买超过三张票，请按ESC键返回");
    fflush(stdin);
      //int op=_getche();
    char op=getchar();
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
          fprintf(fp4,"%s  %s  %s  %s  %s  %lf  %s\n",user.ID,
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
          fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s\n",user.ID,
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
          while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
          {
            if(strcmp(quire.movieID,movieID)==0)
            {
               quire.restticket--;
            }
            fprintf(fp2,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
          quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
          i++;
          }
          fclose(fp6);
          fclose(fp2);
          //把改好的余票信息再重新写回MovieMessage.txt里面 
          fp2=fopen("copyMovieMessage.txt","r");
          fp6=fopen("MovieMessage.txt","w");
          while((fscanf(fp2,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
          {
            fprintf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
          quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),quire.fee);
          i++;
          }
          fclose(fp6);//关闭文件
          fclose(fp2);//关闭文件
          //生成总的订单 
          fp6=fopen("MovieMessage.txt","r");    
          fp7=fopen("OrderMessage.txt","a");
          while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
            fprintf(fp7,"%s  %s  %s  %s  %d  ",U_quanju.ID,movieID,quire.cinema,quire.moviename,quire.room);
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
    //int op=_getche();
    char op=getchar();
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
  Order order;
  MovieMessage quire;
  U_Message user;
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
  while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
          //int op=_getche();
          char op=getchar();
      return 0;
      }
    while(goupiao>3)
    {
    printf("但是您无法一次购买超过三张票，请按ESC键返回");
    fflush(stdin);
    //int op=_getche();
    char op=getchar();
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
      while(row[goupiao]<1 || row[goupiao] >15 || line[goupiao]<1 || line[goupiao] >15)
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
          fprintf(fp4,"%s  %s  %s  %s  %s  %lf  %s\n",user.ID,
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
          fprintf(fp3,"%s  %s  %s  %s  %s  %lf  %s\n",user.ID,
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
          while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
          {
            if(strcmp(quire.movieID,movieID)==0)
            {
               quire.restticket--;//余票数减1 
            }
            fprintf(fp2,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f\n",quire.movieID,quire.cinema,
          quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,quire.restticket,quire.totalticket,quire.ratio,quire.fee);
          i++;
          }
          fclose(fp6);//关闭文件 
          fclose(fp2);//关闭文件 
          //把修改过的copyMovieMessage.txt写回到MovieMessage.txt里面 
          fp2=fopen("copyMovieMessage.txt","r");
          fp6=fopen("MovieMessage.txt","w");
          while((fscanf(fp2,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
          {
            fprintf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %.3f  %.2f\n",quire.movieID,quire.cinema,
          quire.moviename,quire.room,quire.beginTime,quire.endTime,quire.type,
          quire.language,quire.restticket,quire.totalticket,((float)(quire.totalticket-quire.restticket)/(float)quire.totalticket),quire.fee);
          i++;
          }
          fclose(fp6);//关闭文件 
          fclose(fp2);//关闭文件 
          //生成总订单 
          fp6=fopen("MovieMessage.txt","r");    
          fp7=fopen("OrderMessage.txt","a");
          while((fscanf(fp6,"%s  %s  %s  %d  %s  %s  %s  %s  %d  %d  %f  %f",quire.movieID,quire.cinema,
          quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
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
            fprintf(fp7,"%s  %s  %s  %s  %d  ",U_quanju.ID,movieID,quire.cinema,quire.moviename,quire.room);
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
            rewind(fp6);//把光标移回文件开始处 
          fclose(fp6);//关闭文件 
          fclose(fp7);//关闭文件 
      }
      printf("售票成功!按ESC键返回\n");
    }
  }
    fflush(stdin);
    //int op=_getche();
    char op=getchar();
  return 0;
}