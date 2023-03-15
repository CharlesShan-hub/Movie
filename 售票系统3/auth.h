//*************************************注册**************************************
//用户、管理员ID的输入以及验证
bool regist_get_id(int type){
    char id_str[32];
    bool number_flag,letter_flag;
    while(true){
        // 初始化
        for(int i=0;i<32;i++) id_str[i]='\0';
        number_flag = letter_flag = false;
        // 获取用户输入
        printf("请输入您的ID:(六到十个字符,必须包含数字与字母)\n");
        fflush(stdin);
        scanf("%s",id_str);
        // 判断是否为EOF
        if(!strcmp(id_str,"EOF")) return true;
        // 判断ID长度达标
        if(strlen(id_str)<6||strlen(id_str)>10){
            printf("您的ID需要为六到十个字符，请重新输入\n");
            continue;
        }
        // 判断ID含有字母和数字
        for(int i=0;i<32 && id_str[i]!='\0'; i++){
            if ((id_str[i]<='Z'&&id_str[i]>='A')||(id_str[i]<='z'&&id_str[i]>='a')) letter_flag = true;
            if (id_str[i]<='9'&&id_str[i]>='0') number_flag = true;
            if(number_flag&&letter_flag) break;
        }
        if(!(number_flag&&letter_flag)){
            printf("您的ID需要含有字母和数字，请重新输入\n");
            continue;
        }
        //进行ID的查重
        if(id_duplicate_check(id_str,type)){
            printf("您的ID已被注册，请重新输入\n");
            continue;
        }
        break;
    }
    if(type==1)//将注册成功的ID赋值给全局变量
        strcpy(A_quanju.ID,id_str);
    else
        strcpy(U_quanju.ID,id_str);
    return false;
}

//用户、管理员密码的输入及验证
bool regist_get_code(int type){
    char code_str[32], again_str[32];
    while(true){
        // 初始化
        for(int i=0;i<32;i++) code_str[i]='\0';
        for(int i=0;i<32;i++) again_str[i]='\0';
        // 获取用户输入
        printf("请您输入您的密码:(6到10位)\n");
        fflush(stdin);
        scanf("%s",code_str);
        // 判断是否为EOF
        if(!strcmp(code_str,"EOF")) return true;
        // 判断ID长度达标
        if(strlen(code_str)<6||strlen(code_str)>10){
            printf("您的密码需要为六到十个字符，请重新输入\n");
            continue;
        }
        // 再次输入密码
        printf("请再次输入您的密码：\n");
        fflush(stdin);
        scanf("%s",again_str);
        if(strcmp(code_str,again_str)){
            printf("您的两次输入不一致，请重新输入\n");
        }
        break;
    }
    if(type==1)//将注册成功的ID赋值给全局变量
        strcpy(A_quanju.Code,code_str);
    else
        strcpy(U_quanju.Code,code_str);
    return false;
}

//管理员邮箱验证
bool regist_get_mail(int type){
    char mail_str[32]={'\0'};
    bool at_flag, point_flag;
    while(true){
        // 初始化
        for(int i=0;i<32;i++) mail_str[i]='\0';
        at_flag = point_flag = false;
        // 获取用户输入
        printf("请输入您的邮箱：（格式为***@***.***)\n");
        fflush(stdin);
        scanf("%s",mail_str);
        // 判断是否为EOF
        if(!strcmp(mail_str,"EOF")) return true;
        // 判断@与.(@之后需要有一个.,并且.不能在最后一个位置)
        for(int i=0;i<32&&mail_str[i]!='\0';i++){
            if(mail_str[i]=='@') at_flag = true;
            if(mail_str[i]=='.' && at_flag) point_flag = true;
            if(at_flag&&point_flag) break;
        }
        if(!(at_flag&&point_flag) || mail_str[strlen(mail_str)-1]=='.'){
            printf("你的邮箱不合法！\n");
            continue;
        }
        break;
    }
    if(type==1){
        strcpy(A_quanju.Mail,mail_str);
    }else{
        strcpy(U_quanju.Mail,mail_str);
    }
    return false;
}

//获取用户电话
bool regist_get_tel(){
    while(true){
        printf("请输入您的电话号码:\n");
        fflush(stdin);
        scanf("%s",U_quanju.Tele);
        if(!strcmp(U_quanju.Tele,"EOF")) return true;//EOF
        if(strlen(U_quanju.Tele)!=11){//保证电话11位
            printf("你的电话号码不合法！请重新输入：\n");
            continue;
        }
        for(int i=0;i<11;i++)
            if(U_quanju.Tele[i]<'0'||U_quanju.Tele[i]>'9'){ //保证电话11位均为数字
                printf("您的电话号码不合法，请重新输入！\n");
                continue;
            }
        break;
    }
    return false;
}

//注册函数
void regist(){
    FILE *file;
    char temp_str[] = "*********** 注册界面 **********\n\n"\
  "如果您是一位管理员，请输入1：\n"\
  "如果您是一位用户，请输入2：\n"\
  "返回上级界面，请输入3：\n";
    while(true){
        switch(get_choice(temp_str,1,3))
        {
            case 1://注册管理员
                // 清屏与打印提示
                clear_screen();
                printf("*********** 注册 - 管理员 **********\n\n");
                printf("[任何地方输入EOF可停止注册]\n");
                // 获取用户ID
                if(regist_get_id(1)) continue;
                // 获取姓名
                printf("请输入您的姓名:\n");
                fflush(stdin);
                scanf("%s",A_quanju.Name);
                if(!strcmp(A_quanju.Name,"EOF")) continue;
                // 获取所属影院名称
                printf("请输入您的影院:\n");
                fflush(stdin);
                scanf("%s",A_quanju.Cinema);
                if(!strcmp(A_quanju.Cinema,"EOF")) continue;
                // 获取用户密码
                if(regist_get_code(1)) continue;
                // 获取用户邮箱
                if(regist_get_mail(1)) continue;
                // 信息登记
                file=fopen("administrators.txt","a+");
                fprintf(file,"%s  %s  %s  %s  %s\n",A_quanju.ID,A_quanju.Name,A_quanju.Cinema,A_quanju.Code,A_quanju.Mail);
                fclose(file);
                // 直接登录
                printf("您已经注册成功啦！（回车自动登录）\n");
                fflush(stdin);
                getchar();
                A_function();
                break;
            case 2://注册用户
                // 清屏与打印提示
                clear_screen();
                printf("*********** 注册 - 用户 **********\n\n");
                printf("[任何地方输入EOF可停止注册]\n");
                // 获取用户ID
                if(regist_get_id(2)) continue;
                // 获取姓名
                printf("请输入您的姓名:\n");
                fflush(stdin);
                scanf("%s",U_quanju.Name);
                if(!strcmp(U_quanju.Name,"EOF")) continue;
                // 获取用户性别
                printf("请输入您的性别:\n");
                fflush(stdin);
                scanf("%s",U_quanju.Sex);
                if(!strcmp(U_quanju.Sex,"EOF")) continue;
                // 获取用户电话
                if(regist_get_tel()) continue;
                // 获取用户密码
                if(regist_get_code(2)) continue;
                // 获取用户邮箱
                if(regist_get_mail(2)) continue;
                // 信息登记
                file=fopen("users.txt","a");
                fprintf(file,"%s  %s  %s  %s  %s  %lf  %s\n",U_quanju.ID,U_quanju.Name,U_quanju.Sex,U_quanju.Tele,U_quanju.Code,U_quanju.Money,U_quanju.Mail);
                fclose(file);
                // 直接登录
                printf("您已经注册成功啦！（回车自动登录）\n");
                fflush(stdin);
                getchar();
                U_function();
                break;
            case 3://返回上一级
                return;
        }
        break;
    }
}

//*************************************登录**************************************
//登录
void login(){
    char temp_str[] = "*********** 登录界面 **********\n\n"\
  "如果您是一位管理员，请输入1：\n"\
  "如果您是一位用户，请输入2：\n"\
  "返回上级界面，请输入3：\n";
    U_Message uinfo_temp,uinfo_read;
    A_Message ainfo_temp,ainfo_read;
    FILE *file;
    bool booked_flag = false;
    bool EOF_flag = false;
    bool logined_flag = false;

    while(true){
        // 初始化
        EOF_flag=false;
        logined_flag=false;

        // 具体操作
        switch(get_choice(temp_str,1,3)){
            case 1: //管理员登陆-----------------------------------------------------------------------
                // 清屏与打印提示
                clear_screen();
                printf("*********** 登陆 - 管理员 **********\n\n");
                printf("[任何地方输入EOF可停止登陆]\n");
                // 获取ID
                while(true){
                    booked_flag=false;
                    // 获取输入
                    printf("请输入您的ID：\n");
                    fflush(stdin);
                    scanf("%s",ainfo_temp.ID);
                    if(!strcmp(ainfo_temp.ID,"EOF")){
                        EOF_flag = true;
                        break;
                    }
                    // 判断是否为注册的ID
                    file=fopen("administrators.txt","r");
                    rewind(file);
                    while(fscanf(file,"%s  %s  %s  %s  %s",\
          ainfo_read.ID,ainfo_read.Name,ainfo_read.Cinema,ainfo_read.Code,ainfo_read.Mail)!=EOF){
                        if(!strcmp(ainfo_read.ID,ainfo_temp.ID)){
                            booked_flag = true;
                            break;
                        }
                    }
                    fclose(file);
                    if(!booked_flag){
                        printf("用户名错误或该用户尚未注册，请重新输入：\n");
                        continue;
                    }
                    break;
                }// 获取ID结束
                if(EOF_flag) continue;//希望选择其他功能

                // 获取密码
                while(true){//重复输入密码
                    // 获取用户输入
                    printf("请输入您的密码：\n");
                    fflush(stdin);
                    scanf("%s",ainfo_temp.Code);
                    if(!strcmp(ainfo_temp.Code,"EOF")){
                        EOF_flag = true;
                        break;
                    }
                    //密码输入正确 - 这里把本次用户信息保存在 全 局 变 量 中！并进入登陆后状态
                    if(strcmp(ainfo_temp.Code,ainfo_read.Code)==0){
                        strcpy(A_quanju.ID,ainfo_read.ID);
                        strcpy(A_quanju.Name,ainfo_read.Name);
                        strcpy(A_quanju.Cinema,ainfo_read.Cinema);
                        strcpy(A_quanju.Code,ainfo_read.Code);
                        strcpy(A_quanju.Mail,ainfo_read.Mail);
                        A_function();
                        logined_flag = true;
                        break;
                    }
                    //密码输入错误
                    printf("密码输入错误，请重新输入\n");
                }
                // EOF
                if(EOF_flag) break;//希望选择其他功能
                break;
            case 2: //用户登陆-----------------------------------------------------------------------
                // 清屏与打印提示
                clear_screen();
                printf("*********** 登陆 - 用户 **********\n\n");
                printf("[任何地方输入EOF可停止登陆]\n");
                // 获取ID
                while(true){
                    booked_flag=false;
                    // 获取输入
                    printf("请输入您的ID：\n");
                    fflush(stdin);
                    scanf("%s",uinfo_temp.ID);
                    if(!strcmp(uinfo_temp.ID,"EOF")){
                        EOF_flag = true;
                        break;
                    }
                    // 判断是否为注册的ID
                    file=fopen("users.txt","r");
                    rewind(file);
                    while(fscanf(file,"%s  %s  %s  %s  %s  %lf  %s",\
            uinfo_read.ID,uinfo_read.Name,uinfo_read.Sex,uinfo_read.Tele,\
            uinfo_read.Code,&uinfo_read.Money,uinfo_read.Mail)!=EOF){
                        if(!strcmp(uinfo_read.ID,uinfo_temp.ID)){
                            booked_flag = true;
                            break;
                        }
                    }
                    fclose(file);
                    if(!booked_flag){
                        printf("用户名错误或该用户尚未注册，请重新输入：\n");
                        continue;
                    }
                    break;
                }// 获取ID结束
                if(EOF_flag) continue;//希望选择其他功能

                // 获取密码
                while(true){//重复输入密码
                    // 获取用户输入
                    printf("请输入您的密码：\n");
                    fflush(stdin);
                    scanf("%s",uinfo_temp.Code);
                    if(!strcmp(uinfo_temp.Code,"EOF")){
                        EOF_flag = true;
                        break;
                    }
                    //密码输入正确 - 这里把本次用户信息保存在 全 局 变 量 中！并进入登陆后状态
                    if(strcmp(uinfo_temp.Code,uinfo_read.Code)==0){
                        strcpy(U_quanju.ID,uinfo_read.ID);
                        strcpy(U_quanju.Name,uinfo_read.Name);
                        strcpy(U_quanju.Sex,uinfo_read.Sex);
                        strcpy(U_quanju.Tele,uinfo_read.Tele);
                        strcpy(U_quanju.Code,uinfo_read.Code);
                        U_quanju.Money = uinfo_read.Money;
                        strcpy(U_quanju.Mail,uinfo_read.Mail);
                        U_function();
                        logined_flag = true;
                        break;
                    }
                    //密码输入错误
                    printf("密码输入错误，请重新输入\n");
                }
                // EOF
                if(EOF_flag) break;//希望选择其他功能
                break;
            case 3: return; //返回上一级
        }
        if(logined_flag) break;
    }
}