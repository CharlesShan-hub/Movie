//****************************************管理员操作***********************************
//管理员主界面
void A_function(){
  char temp_str[] = "************ 管理员 - 主界面 ****************\n\n"
  "如果您想查看个人信息,请输入 1\n"
  "如果您想进入影厅系统,请输入 2\n"
  "如果您想进行场次管理,请输入 3\n"
  "如果您想查看订单状况,请输入 4\n"
  "如果您想要退出      ,请输入 5\n";
  while(true)
  {
    switch(get_choice(temp_str,1,5)){
      case 1:A_information();/*管理员信息系统*/
        break;
      case 2:A_screen();/*管理员影厅管理系统 */
        break;
      case 3:A_session();/*管理员场次管理系统*/  
        break;
      case 4:A_order();/*管理员订单管理系统*/
        break;
      default:
        return;
    }
  }
}

//*************************************管理员个人信息查询及修改********************************
// 管理员个人信息主函数
void A_information(){
  char temp_str[] = "************ 管理员 - 个人信息 ****************\n\n"
 "如果你想查看你的基本信息，请输入1\n"
 "如果你想更改你的基本信息，请输入2\n"
 "如果你想返回上一界面，请输入3\n";
  A_Message info;
  FILE *file;
  while(true)
  {
    switch(get_choice(temp_str,1,3)){
      case 1://管理员查看基本信息 
        A_check();
        break;
      case 2://管理员更改信息 
        A_change();
        break;
      default:
        return;
    }
  }
}

//管理员信息查看
void A_check(){
  // 定义变量与打开文件
  A_Message info,temp;
  FILE *file = fopen("administrators.txt","r");
  if(file==NULL){
    printf("Failed to Open administrators.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  // 打印提示信息与个人信息
  clear_screen();
  char temp_str[] = "************ 管理员 - 个人信息 - 查看****************\n\n"
 "如果你想查看你的基本信息，请输入1\n"
 "如果你想更改你的基本信息，请输入2\n"
 "如果你想返回上一界面，请输入3\n";
  printf("%s",temp_str);
  while(fscanf(file,"%s  %s  %s  %s  %s\n",\
    info.ID,info.Name,info.Cinema,info.Code,info.Mail)!=EOF)
    if(!strcmp(A_quanju.ID,info.ID)){
      printf("id          name        cinema           mail \n");
      printf("%-12s%-12s%-6s  %-12s\n",info.ID,info.Name,info.Cinema,info.Mail);
      break;
    }
  fclose(file);
  printf("按任意键继续\n");
  fflush(stdin);
  getchar();
}

//管理员信息更改 
void A_change(){
  // 定义变量与打开文件
  A_Message info,temp;
  FILE *file_from = fopen("administrators.txt","r");
  FILE *file_to = fopen("administrators1.txt","w");
  if(file_from==NULL){
    printf("Failed to Open administrators.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  if(file_to==NULL){
    printf("Failed to Open administrators1.txt\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return;
  }
  // 选择信息修改内容
  clear_screen();
  char temp_str[] = "************ 管理员 - 个人信息 - 修改 ****************\n\n"
 "如果你想更改你的姓名，请输入1\n"
 "如果你想更改你的邮箱，请输入2\n"
 "如果你想更改你的密码，请输入3\n"
 "如果你想返回上一界面，请输入4\n"
 "任意位置输入EOF可以取消修改\n";
  while(true)
  {
    // 更新信息
    switch(get_choice(temp_str,1,4)){
      case 1://修改姓名
        printf("\n请输入您的新姓名：\n");//输入姓名 
        fflush(stdin);
        scanf("%s",temp.Name);
        if(!strcmp(temp.Name,"EOF")) continue;
        strcpy(A_quanju.Name,temp.Name);
        break;
      case 2://修改邮箱
        if(regist_get_mail(1)) continue;
        break;
      case 3://修改密码
        if(regist_get_code(1)) continue;
        break;
      default:
        return;
    }
    // 保存信息
    while(fscanf(file_from,"%s  %s  %s  %s  %s\n",\
      info.ID,info.Name,info.Cinema,info.Code,info.Mail)!=EOF)
      if(strcmp(A_quanju.ID,info.ID)==0)
        fprintf(file_to,"%s  %s  %s  %s  %s\n",\
          A_quanju.ID,A_quanju.Name,A_quanju.Cinema,A_quanju.Code,A_quanju.Mail);
      else
        fprintf(file_to,"%s  %s  %s  %s  %s\n",\
          info.ID,info.Name,info.Cinema,info.Code,info.Mail);
    fclose(file_to);
    fclose(file_from);
    A_modify();
    // 显示修改后信息
    printf("id          name        cinema           mail \n");
    printf("%-12s%-12s%-6s  %-12s\n",A_quanju.ID,A_quanju.Name,A_quanju.Cinema,A_quanju.Mail);
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
  }
}

//*************************************影厅添加和查看**************************************
//影厅管理主函数
void A_screen(){
  char temp_str[] = "************ 管理员 - 影厅系统 ****************\n\n"
  "影厅查询:查询所有开设的影厅信息 请输入 1\n"
  "添加影厅:添加一个新的影厅       请输入 2\n"
  "返回                            请输入 3\n";
  while(true)
  {
    switch(get_choice(temp_str,1,3)){
      case 1:
        A_screen_check();//影厅查询
        printf("按任意键继续\n");
        fflush(stdin);
        getchar();
        break;
      case 2:
        A_screen_add();//影厅添加
        printf("按任意键继续\n");
        fflush(stdin);
        getchar();
        break;
      default:
        return;
    }
  }    
} 

//管理员影厅查询
void A_screen_check(){
  ScreenMessage SM;
  FILE * S_Message=fopen("ScreenMessage.txt","r");//所有影厅的信息
  
  if(S_Message==NULL){
    printf("当前没有开设的影厅\n");
    return;
  }
  printf("    影厅号   |  影厅类型 \n");
  while(fscanf(S_Message,"%s %d %s",SM.cinema,&SM.room,SM.type)!=EOF)
    if(strcmp(A_quanju.Cinema,SM.cinema) == 0)
      printf("      %d\t\t%s\n",SM.room,SM.type);
  fclose(S_Message);
}

//管理员影厅添加
void A_screen_add(){
  ScreenMessage info;
  char title_str[] = "************ 管理员 - 影厅系统 - 影厅管理 ****************\n\n";
  char tip_str[256] = "请各根据提示输入增添影厅的信息：\n"
       "注意：影厅一旦增加不能更改！\n"
       "您可以在未完成注册时输入 0 撤销对影厅的增加！\n";
  // 影厅号
  char temp_str1[256]="";
  strcpy(temp_str1,tip_str);
  strcat(temp_str1,"请您输入要新开设影厅的编号 (1到20的整数)\n");
  while(true){
    info.room = get_choice_show_screen(title_str,temp_str1,0,20);
    if(info.room==0){printf("您已取消本次影厅添加\n");return;}
    if(A_screen_exist(info.room)) continue;//判断影厅是否已经存在 
    break;
  }
  printf("好的！您添加的是 %d号厅\n",info.room);
  // 影厅类型
  char temp_str2[256]="";
  strcpy(temp_str2,tip_str);
  strcat(temp_str2,"好的！您添加的是 ");
  char temp_str2_room[8]="";A_screen_add_itoa(info.room,temp_str2_room);
  strcat(temp_str2,temp_str2_room);
  strcat(temp_str2,"号厅\n请输入厅的类型（Imax/2D/3D/4D）\n"
  " Imax 输入 1\n"   
  " 2D   输入 2\n"   
  " 3D   输入 3\n"  
  " 4D   输入 4\n");
  switch(get_choice_show_screen(title_str,temp_str2,0,4)){
    case 0:printf("您已取消本次影厅添加\n");return;
    case 1:strcpy(info.type,"Imax");break;
    case 2:strcpy(info.type,"2D");  break;
    case 3:strcpy(info.type,"3D");  break;
    case 4:strcpy(info.type,"4D");  break;
  }
  printf("您计划添加的是 %d号厅为 %s厅\n",info.room,info.type);
  // 确认添加
  char temp_str3[256];
  strcpy(temp_str3,tip_str);
  strcat(temp_str3,"您计划添加的是 ");
  strcat(temp_str3,temp_str2_room);
  strcat(temp_str3,"号厅, 类型为 ");
  strcat(temp_str3,info.type);
  strcat(temp_str3,"\n请您确认添加该影厅(输入1添加,输入0取消)\n");
  if(get_choice_show_screen(title_str,temp_str3,0,1)==0){
    printf("您已取消本次影厅添加\n");
    return;
  }
  FILE *S_Message=fopen("ScreenMessage.txt","a+");
  fprintf(S_Message,"%s  %d  %s\n",A_quanju.Cinema,info.room,info.type);
  fclose(S_Message);
  clear_screen();
  printf("%s",title_str);
  printf("已成功添加该影厅！您已开设以下影厅：\n");
  A_screen_check();//打印一遍影厅信息 
  return;
}
 
//管理员添加的影厅是否存在
bool A_screen_exist(int room){
  FILE * S_Message;//所有影厅的信息
  ScreenMessage SM;
  S_Message=fopen("ScreenMessage.txt","r");
  while(fscanf(S_Message,"%s %d %s",SM.cinema,&SM.room,SM.type)!=EOF)
    if(strcmp(A_quanju.Cinema,SM.cinema) == 0)
      if(room == SM.room)
        return 1; 
  return 0; 
}

//管理员添加的影厅工具函数
void A_screen_add_itoa(int room, char *str){
  str[0] = (char)(room/10+48);
  str[1] = (char)(room%10+48);
  str[2] = '\0';
}

//*************************************场次添加和查看**************************************
//管理员场次管理主函数 
void A_session(){
  char temp_str[] = "************ 管理员 - 场次系统 ****************\n\n"
  "场次查询       请输入 1\n"
  "添加场次       请输入 2\n"
  "返回           请输入 3\n";
  while(true)
  {
    switch(get_choice(temp_str,1,3)){
      case 1:
        A_session_check();//场次查询
        break;
      case 2:
        A_session_add();//场次添加
        break;
      default:
        return;
    }
  }  
}

//管理员场次查询
void A_session_check(){
  char title_str[] = "************ 管理员 - 场次系统 - 场次查询 ****************\n\n";
  char temp_str[] = "请输入您想要查看的场次\n输入 0 返回上一级\n";
  int room;
  MovieMessage MM;
  FILE * M_Message;//所有场次的信息
  while(true){
    room = get_choice_show_screen(title_str,temp_str,0,20);
    if(room==0)return;
    if(!A_screen_exist(room)){//判断影厅是否已经存在 
      printf("该影厅未安排场次\n"); //-->可以去添加该场次
      printf("按任意键继续\n");
      fflush(stdin);
      getchar();
      continue;
    }
    printf(" 这里是第%d影厅的场次信息：\n",room);
    printf("场次号|电影名|影厅号|开场日期时间|影片时间|影片类型|播放语言|剩余票数|总票数|售出率|票价\n");
    if((M_Message=fopen("MovieMessage.txt","r"))==NULL){
      printf("MovieMessage.txt 程序出错!\n");
      return;
    }
    while(fscanf(M_Message,"%s  %s  %s  %d  %d  %d  %d  %d  %d  %d  %s  %s  %d  %d  %f  %f",\
    MM.movieID,MM.cinema,MM.moviename,&MM.room,&MM.year,&MM.month,
    &MM.day,&MM.hour,&MM.minute,&MM.duration,MM.type,MM.language,
    &MM.restticket,&MM.totalticket,&MM.ratio,&MM.fee)!=EOF)
      if(strcmp(MM.cinema,A_quanju.Cinema) == 0 && room == MM.room)
            printf("%-3s %-9s  %-4d %d/%d/%d %d:%d   %d  %-6s %s    %-3d    %-3d    %.2f %.2f\n",
            MM.movieID,MM.moviename,MM.room,MM.year,MM.month,MM.day,MM.hour,MM.minute,
            MM.duration,MM.type,MM.language,MM.restticket,MM.totalticket,
            MM.ratio*100,MM.fee); //改到这一行
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
  }
}

//管理员场次添加 - 获取电影名
bool A_session_add_get_name(char name[]){
  while(true){
    printf("请您输入影片名\n");
    fflush(stdin);
    scanf("%s",name);
    if(!strcmp(name,"EOF"))return false;
    if(judge_kongge(name))continue;
    break;
  }
  return true;
}

//管理员场次添加 - 获取放映厅号
bool A_session_add_get_room(int &room){
  char temp_str[32];
  while(true){
    printf("请您输入 放映厅号（如 1 ）\n您已开设一下影厅：\n");
    A_screen_check();//打印一遍影厅信息
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    room = atoi(temp_str);
    if(!A_screen_exist(room)){
      printf("该影厅未开设!(取消排片可以输入EOF)\n");
      continue;
    }
    break;
  }
  return true;
}

//管理员场次添加 - 获取语言
bool A_session_add_get_len(char lan[]){
  char temp_str[32];
  int choice;
  while(true){
    printf("请您输入影片语言(1:中文, 2:英文)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    choice = atoi(temp_str);
    if(choice!=1 && choice!=2){
      printf("请输入1或2\n");
      continue;
    }
    break;
  }
  if(choice==1) strcpy(lan,"Chinese");
  else strcpy(lan,"English");
  return true;
}

//管理员场次添加 - 获取票价
bool A_session_add_get_price(float &price){
  char temp_str[32];
  while(true){
    printf("请您输入票价\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    price = (float)atoi(temp_str);
    break;
  }
  return true;
}

//管理员场次添加 - 获取影片时长
bool A_session_add_get_duration(int &duration){
  char temp_str[32];
  while(true){
    printf("请您输入电影时长(分钟)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    duration = (float)atoi(temp_str);
    if(duration<30||duration>240){printf("请输入30-240之间的数");continue;}
    break;
  }
  return true;
}

//管理员场次添加 - 获取开始时间 - 年
bool A_session_add_get_time_year(int &year){
  char temp_str[32];
  while(true){
    printf("请您输入开演日期：年(2023-2100)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    if(atoi(temp_str)>2100||atoi(temp_str)<2023){printf("请输入2023到2100的一个数!\n");continue;}
    year = (float)atoi(temp_str);
    break;
  }
  return true;
}

//管理员场次添加 - 获取开始时间 - 月
bool A_session_add_get_time_month(int &month){
  char temp_str[32];
  while(true){
    printf("请您输入开演日期：月(1-12)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    if(atoi(temp_str)>12||atoi(temp_str)<1){printf("请输入1到12的一个数!\n");continue;}
    month = (float)atoi(temp_str);
    break;
  }
  return true;
}

//管理员场次添加 - 获取开始时间 - 日
bool A_session_add_get_time_day(int &day,int month,int year){
  char temp_str[32];
  int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  if(is_leap_year(year)) days[2]=29;
  while(true){
    printf("请您输入开演日期：日(0-31)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    day = atoi(temp_str);
    if(day>days[month]||day<1){printf("请输入1到%d的一个数!\n",days[month]);continue;}
    break;
  }
  return true;
}

//管理员场次添加 - 获取开始时间 - 时
bool A_session_add_get_time_hour(int &hour){
  char temp_str[32];
  while(true){
    printf("请您输入开演时间：时(0-23)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    if(atoi(temp_str)>23||atoi(temp_str)<0){printf("请输入0到23的一个数!\n");continue;}
    hour = (float)atoi(temp_str);
    break;
  }
  return true;
}

//管理员场次添加 - 获取开始时间 - 分
bool A_session_add_get_time_minute(int &minute){
  char temp_str[32];
  while(true){
    printf("请您输入开演时间：分(0-59)\n");
    fflush(stdin);
    scanf("%s",temp_str);
    if(!strcmp(temp_str,"EOF"))return false;
    if(judge_num(temp_str)){printf("请输入数字!\n");continue;}
    if(atoi(temp_str)>59||atoi(temp_str)<0){printf("请输入0到59的一个数!\n");continue;}
    minute = (float)atoi(temp_str);
    break;
  }
  return true;
}

//管理员场次添加 
void A_session_add(){
  // 文件
  FILE * M_Message;//所有影厅的信息
  if((M_Message=fopen("MovieMessage.txt","r"))==NULL){
    printf("MovieMessage.txt不能打开，程序出错！\n");return;
  }
  fclose(M_Message);

  // 循环添加电影
  MovieMessage info;//最终读取的管理员输入
  while(true){
    clear_screen();
    printf("************ 管理员 - 场次系统 - 场次添加 ****************\n\n"
      " 请您输入添加场次的信息：\n\n您在任何地方输入EOF可以终止添加\n"
      "!!仔细阅读说明，并按照规定格式输入，否则无效！！\n");
    // 获取影片名
    if(!A_session_add_get_name(info.moviename)) break;
    // 获取放映厅号 
    if(!A_session_add_get_room(info.room)) break;
    // 获取语言种类
    if(!A_session_add_get_len(info.language)) break;
    // 获取票价
    if(!A_session_add_get_price(info.fee)) break;
    // 获取影片时长
    if(!A_session_add_get_duration(info.duration)) break;
    // 获取影片开始时间 - 年
    if(!A_session_add_get_time_year(info.year)) break;
    // 获取影片开始时间 - 月
    if(!A_session_add_get_time_month(info.month)) break;
    // 获取影片开始时间 - 日
    if(!A_session_add_get_time_day(info.day,info.month,info.year)) break;
    // 获取影片开始时间 - 时
    if(!A_session_add_get_time_hour(info.hour)) break;
    // 获取影片开始时间 - 分
    if(!A_session_add_get_time_minute(info.minute)) break;
    // 验证
    if(!A_session_add_valid(info)){
      // 验证失败
      printf("您输入的时间不合法,请您查看当前厅其他场次信息并重新输入\n"
        "请注意，两场相邻场次需要间隔至少20分钟！\n");
      continue;
    }else{
      // 验证成功
      if(!A_session_add_print(info)) break;
    }
    printf("已成功添加电影：%s\n",info.moviename);
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
  }
}

//判断添加片场
bool A_session_add_print(MovieMessage info){
  ScreenMessage SM;
  MovieMessage MM;    
  FILE * M_Message;//所有场次的信息
  FILE * S_Message;//所有影厅的信息
  int count_=0;//记录场次序号
  int num = 0;//余票数和总票数
  char choice_[20]={'\0'}; 
  
  //影片类型  为 SM.type
  S_Message=fopen("ScreenMessage.txt","r");
  while(fscanf(S_Message,"%s  %d  %s",SM.cinema,&SM.room,SM.type)!=EOF) 
    if(strcmp(SM.cinema,A_quanju.Cinema) == 0 && SM.room==info.room)break;
  fclose(S_Message);
  //场次序号   count_ 
  M_Message=fopen("MovieMessage.txt","r");
  while(fscanf(M_Message,"%s  %s  %s  %d  %d  %d  %d  %d  %d  %d  %s  %s  %d  %d  %f  %f",\
    MM.movieID,MM.cinema,MM.moviename,&MM.room,&MM.year,&MM.month,
    &MM.day,&MM.hour,&MM.minute,&MM.duration,MM.type,MM.language,
    &MM.restticket,&MM.totalticket,&MM.ratio,&MM.fee)!=EOF)
      if(count_<atoi(MM.movieID)) count_=atoi(MM.movieID);
  count_++;
  fclose(M_Message);
  //余票数与总票数  num 
  if(strcmp(SM.type,"Imax") == 0)
    num = 150;
  else
    num = 100;
  //询问管理员是否要添加
  printf("\n影片名:%s\n影厅号:%d\n开场时间:%d-%d-%d %d:%d\n影片时长:%d\n影片类型:%s\n语言:"
    "%s\n票价:%f\n",info.moviename,info.room,info.year,info.month,info.day,info.hour,
    info.minute,info.duration,SM.type,info.language,info.fee); 
  while(true){
    printf("\n上面是您这次添加片场的信息\n确定添加输入1，不添加输入其他数字(等同于EOF)\n");
    fflush(stdin);
    scanf("%s",choice_);
    if(judge_num(choice_)!=0)
      continue;
    break;
  }
  //进行添加或者放弃
  if(atoi(choice_) != 1){
    printf("您已取消添加！\n");
    printf("按任意键继续\n");
    fflush(stdin);
    getchar();
    return false;
  }
  M_Message=fopen("MovieMessage.txt","a");  
  fprintf(M_Message,"%d  %s  %s  %d  ",count_,A_quanju.Cinema,info.moviename,info.room);
  fprintf(M_Message,"%d  %d  %d  %d  %d  %d  ",info.year,info.month,info.day,info.hour,info.minute,info.duration);
  fprintf(M_Message,"%s  %s  %d  %d  0  %f\n",SM.type,info.language,num,num,info.fee);
  fclose(M_Message);
  printf("您已成功添加！\n");
  printf("按任意键继续\n");
    fflush(stdin);
    getchar();
  return true;
}

// 场次添加时间验证 - 时间转换工具
time_t A_session_add_valid_get_time(MovieMessage info){
  struct tm *time;
  time->tm_year = info.year - 1900;
  time->tm_mon = info.month - 1;
  time->tm_mday = info.day;
  time->tm_hour = info.hour;
  time->tm_min = info.minute;
  time->tm_sec = 0;
  time->tm_isdst = 0;
  return mktime(time);
}

// 场次添加时间验证 
bool A_session_add_valid(MovieMessage info){
  time_t start = A_session_add_valid_get_time(info);//要添加的时间 - 开始时间
  time_t end = start + 60*info.duration;//要添加的时间 - 结束时间
  time_t start_temp,end_temp;
  MovieMessage MM;
  bool flag = true;
  FILE * file = fopen("MovieMessage.txt","r");//所有影厅的信息
  while(fscanf(file,"%s  %s  %s  %d  %d  %d  %d  %d  %d  %d  %s  %s  %d  %d  %f  %f",\
    MM.movieID,MM.cinema,MM.moviename,&MM.room,&MM.year,&MM.month,
    &MM.day,&MM.hour,&MM.minute,&MM.duration,MM.type,MM.language,
    &MM.restticket,&MM.totalticket,&MM.ratio,&MM.fee)!=EOF){
      start_temp = A_session_add_valid_get_time(MM);
      end_temp = start_temp + 60*info.duration;
      if(start+20*60 >= end_temp || end+20*60 <= end_temp) continue;
      flag = false;
  }
  fclose(file);
  return flag;
}

//*************************************管理员订单查看**************************************
void A_order()
{
  Order A_kan;
  FILE *fp2;
  char changci[20];
  int xuanze=0;
  char choice[20];
  
  fp2=fopen("OrderMessage.txt","r");
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
  MovieMessage quire;//表示场次信息内容  
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
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF) 
    if(strcmp(A_quanju.Cinema,quire.cinema)==0)//判断所查影院和管理员负责影院是否相同 
    {
      fprintf(gtemp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
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
  MovieMessage buynum_total[500];//声明一个结构体数组 
  int n=0;//同一个影院的总场次数 
  FILE *fp;//读写gtemp.txt文件 
  MovieMessage quire;//表示场次信息内容
     
  system("cls"); //清屏 
  fp=fopen("gtemp.txt","r");
  if(fp==NULL)
  {
    printf("The file was not successfully opened.\n");
    exit(1);
  }
  //将场次信息对应存入结构体数组 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    buynum_total[n].fee=quire.fee;
    strcpy(buynum_total[n].movieID,quire.movieID);
    strcpy(buynum_total[n].cinema,quire.cinema);
    strcpy(buynum_total[n].moviename,quire.moviename);
    buynum_total[n].room=quire.room;
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
  MovieMessage t; //中间值 
        
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",buynum_total[i].movieID,buynum_total[i].cinema,buynum_total[i].moviename,
    buynum_total[i].room,buynum_total[i].beginTime,buynum_total[i].endTime,buynum_total[i].type,buynum_total[i].language,
    buynum_total[i].restticket,
    buynum_total[i].totalticket,
    buynum_total[i].ratio,buynum_total[i].fee);
  }
  fclose(fp);  
}

void rangeBuynumde()//按已购票人数还未放映降序 
{
  MovieMessage buynum_total[500];//声明一个结构体数组 
  int n=0;//同一个影院的总场次数 
  FILE *fp;//读写gtemp.txt文件 
  MovieMessage quire;//表示场次信息内容 
    
  system("cls");  //清屏 
  fp=fopen("gtemp.txt","r");
  if(fp==NULL)
  {
      printf("The file was not successfully opened.\n");
    exit(1);
  }
  //将场次信息对应存入结构体数组
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    buynum_total[n].fee=quire.fee;
    strcpy(buynum_total[n].movieID,quire.movieID);
    strcpy(buynum_total[n].cinema,quire.cinema);
    strcpy(buynum_total[n].moviename,quire.moviename);
    buynum_total[n].room=quire.room;
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
        
  MovieMessage t;//中间值 
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",buynum_total[i].movieID,buynum_total[i].cinema,buynum_total[i].moviename,
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
  MovieMessage income_total[500];//声明一个结构的数组 
  int n=0;//表示九月五号的所有场次数 
  int m=0;//表示九月六号的所有场次数 
  int b=0;//表示九月七号的所有场次数 
  FILE *fp;//读写MovieMessage文件 
  char day1[10]="09/05";
  char day2[10]="09/06";
  char day3[10]="09/07";
  MovieMessage quire;//表示场次信息内容 
    
  system("cls");//清屏 
  fp=fopen("MovieMessage.txt","r");
  if(fp==NULL)
  {
    printf("The file was not successfully opened.\n");
    exit(1);
  }
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day1,quire.beginTime,5)==0)
    {
      income_total[n].fee=quire.fee;
      strcpy(income_total[n].movieID,quire.movieID);
      strcpy(income_total[n].cinema,quire.cinema);
      strcpy(income_total[n].moviename,quire.moviename);
      income_total[n].room=quire.room;
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
  MovieMessage t; //中间值 
        
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[i].movieID,income_total[i].cinema,income_total[i].moviename,
    income_total[i].room,income_total[i].beginTime,income_total[i].endTime,income_total[i].type,income_total[i].language,
    income_total[i].restticket,income_total[i].totalticket,
    income_total[i].ratio,income_total[i].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day2,quire.beginTime,5)==0)
    {
      income_total[m].fee=quire.fee;
      strcpy(income_total[m].movieID,quire.movieID);
      strcpy(income_total[m].cinema,quire.cinema);
      strcpy(income_total[m].moviename,quire.moviename);
      income_total[m].room=quire.room;
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
  MovieMessage e; //中间值 
        
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[q].movieID,income_total[q].cinema,income_total[q].moviename,
    income_total[q].room,income_total[q].beginTime,income_total[q].endTime,income_total[q].type,income_total[q].language,
    income_total[q].restticket,income_total[q].totalticket,
    income_total[q].ratio,income_total[q].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day3,quire.beginTime,5)==0)
    {
      income_total[b].fee=quire.fee;
      strcpy(income_total[b].movieID,quire.movieID);
      strcpy(income_total[b].cinema,quire.cinema);
      strcpy(income_total[b].moviename,quire.moviename);
      income_total[b].room=quire.room;
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
  MovieMessage d; //中间值
     
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",income_total[a].movieID,income_total[a].cinema,income_total[a].moviename,
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
  ScreenMessage SM;
 
  S_Message=fopen("ScreenMessage.txt","r");
  while(fscanf(S_Message,"%s %d %s",SM.cinema,&SM.room,SM.type)!=EOF)
  {
    if(atoi(room)==SM.room)
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
  MovieMessage ratio_total[500];//声明一个结构体数组 
  int n=0;//表示九月五号的所有场次数  
  int m=0;//表示九月六号的所有场次数
  int b=0;//表示九月七号的所有场次数
  FILE *fp;//读写MovieMessage.txt文件 
  char day1[10]="09/05";
  char day2[10]="09/06";
  char day3[10]="09/07";
  MovieMessage quire;//表示场次信息 
    
  system("cls"); //清屏 
  fp=fopen("MovieMessage.txt","r");
  if(fp==NULL)
  {
      printf("The file was not successfully opened.\n");
    exit(1);
  }
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day1,quire.beginTime,5)==0)
    {
    ratio_total[n].fee=quire.fee;
    strcpy(ratio_total[n].movieID,quire.movieID);
    strcpy(ratio_total[n].cinema,quire.cinema);
    strcpy(ratio_total[n].moviename,quire.moviename);
    ratio_total[n].room=quire.room;
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
  MovieMessage t; //中间值 
    
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
    ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
    ratio_total[i].restticket,
    ratio_total[i].totalticket,
    ratio_total[i].ratio,ratio_total[i].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day2,quire.beginTime,5)==0)
    {
      ratio_total[m].fee=quire.fee;
      strcpy(ratio_total[m].movieID,quire.movieID);
      strcpy(ratio_total[m].cinema,quire.cinema);
      strcpy(ratio_total[m].moviename,quire.moviename);
      ratio_total[m].room=quire.room;
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
  MovieMessage e;//中间值 
        
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[q].movieID,ratio_total[q].cinema,ratio_total[q].moviename,
    ratio_total[q].room,ratio_total[q].beginTime,ratio_total[q].endTime,ratio_total[q].type,ratio_total[q].language,
    ratio_total[q].restticket,
    ratio_total[q].totalticket,
    ratio_total[q].ratio,ratio_total[q].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)   
  {
    if(strncasecmp(day3,quire.beginTime,5)==0)
    {
      ratio_total[b].fee=quire.fee;
      strcpy(ratio_total[b].movieID,quire.movieID);
      strcpy(ratio_total[b].cinema,quire.cinema);
      strcpy(ratio_total[b].moviename,quire.moviename);
      ratio_total[b].room=quire.room;
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
  MovieMessage d;//中间值 
        
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[a].movieID,ratio_total[a].cinema,ratio_total[a].moviename,
    ratio_total[a].room,ratio_total[a].beginTime,ratio_total[a].endTime,ratio_total[a].type,ratio_total[a].language,
    ratio_total[a].restticket,
    ratio_total[a].totalticket,
    ratio_total[a].ratio,ratio_total[a].fee);
  }
  fclose(fp);
}

void rangeratiode()//按上座率分日期所有已经放映降序 
{
  MovieMessage ratio_total[500];//声明一个结构体数组 
  int n=0;//表示九月五号的总场次数 
  int m=0;//表示九月六号的总场次数 
  int b=0;//表示九月五七的总场次数 
  FILE *fp;//读写MovieMessage.txt文件 
  char day1[10]="09/05";
  char day2[10]="09/06";
  char day3[10]="09/07";
  MovieMessage quire;//描述场次信息 
    
  system("cls");//清屏 
  fp=fopen("MovieMessage.txt","r");
  if(fp==NULL)
  {
      printf("The file was not successfully opened.\n");
    exit(1);
  }
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day1,quire.beginTime,5)==0)
    {
      ratio_total[n].fee=quire.fee;
      strcpy(ratio_total[n].movieID,quire.movieID);
      strcpy(ratio_total[n].cinema,quire.cinema);
      strcpy(ratio_total[n].moviename,quire.moviename);
      ratio_total[n].room=quire.room;
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
  MovieMessage t;//中间值
     
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[i].movieID,ratio_total[i].cinema,ratio_total[i].moviename,
    ratio_total[i].room,ratio_total[i].beginTime,ratio_total[i].endTime,ratio_total[i].type,ratio_total[i].language,
    ratio_total[i].restticket,
    ratio_total[i].totalticket,
    ratio_total[i].ratio,ratio_total[i].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)
  {
    if(strncasecmp(day2,quire.beginTime,5)==0)
    {
      ratio_total[m].fee=quire.fee;
      strcpy(ratio_total[m].movieID,quire.movieID);
      strcpy(ratio_total[m].cinema,quire.cinema);
      strcpy(ratio_total[m].moviename,quire.moviename);
      ratio_total[m].room=quire.room;
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
  MovieMessage e;//中间值
     
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[q].movieID,ratio_total[q].cinema,ratio_total[q].moviename,
    ratio_total[q].room,ratio_total[q].beginTime,ratio_total[q].endTime,ratio_total[q].type,ratio_total[q].language,
    ratio_total[q].restticket,
    ratio_total[q].totalticket,
    ratio_total[q].ratio,ratio_total[q].fee);
  }
  rewind(fp);//光标回到文件开头 
  while((fscanf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",quire.movieID,quire.cinema,
  quire.moviename,&quire.room,quire.beginTime,quire.endTime,quire.type,
  quire.language,&quire.restticket,&quire.totalticket,&quire.ratio,&quire.fee))!=EOF)   
  {
    if(strncasecmp(day3,quire.beginTime,5)==0)
    {
      ratio_total[b].fee=quire.fee;
      strcpy(ratio_total[b].movieID,quire.movieID);
      strcpy(ratio_total[b].cinema,quire.cinema);
      strcpy(ratio_total[b].moviename,quire.moviename);
      ratio_total[b].room=quire.room;
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
  MovieMessage d;//中间值
     
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
    printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\n",ratio_total[a].movieID,ratio_total[a].cinema,ratio_total[a].moviename,
    ratio_total[a].room,ratio_total[a].beginTime,ratio_total[a].endTime,ratio_total[a].type,ratio_total[a].language,
    ratio_total[a].restticket,
    ratio_total[a].totalticket,
    ratio_total[a].ratio,ratio_total[a].fee);
  } 
  fclose(fp);
}
