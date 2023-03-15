#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <stdbool.h>
#ifdef _WIN32
#define TYPE 1
#elif __APPLE__
#define TYPE 2
#endif
//#include <windows.h>
//#include <conio.h>


//************************************定义部分***************************************
//订单
typedef struct
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
}Order;

//用户信息
typedef struct
{
    char ID[32]; //用户ID
    char Name[32]; //用户名字
    char Sex[32]; //用户性别
    char Tele[32]; //用户电话
    char Code[32]; //用户密码
    double Money; //用户账户余额（初始为0）
    char Mail[32]; //用户邮箱
}U_Message;

//管理员信息
typedef struct
{
    char ID[32]; //管理员ID
    char Name[32]; //管理员名字
    char Cinema[32]; //所属影院
    char Code[32]; //管理员密码
    char Mail[32]; //管理员邮箱
}A_Message;

//电影影厅信息
typedef struct
{
    char cinema[20];//电影院
    int room;//厅号
    char type[20];//影厅类型  Imax/2D/3D/4D
}ScreenMessage;

//电影场次信息
typedef struct
{
    char movieID[20]; //场次编号
    char cinema[20];//电影院
    char moviename[20];//影片名
    int room;//厅号
    char beginTime[20];//开场时间(old)
    char endTime[20];//散场时间(old)
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int duration;
    char type[20];//影片类型
    char language[20];//语言
    int restticket;//余票数
    int totalticket;//总票数
    float ratio;//上座率
    float fee;//票价
}MovieMessage;

//全局变量
FILE *fp5;
FILE *fp6;
FILE *fp7;
int arr100[10][10] = {0};
int arr150[10][15] = {0};
U_Message U_quanju;//定义一个全局用户信息变量
A_Message A_quanju;//定义一个全局管理员信息变量

//注册时需要的函数
bool regist_get_id(int type);//注册并查询ID
int id_duplicate_check(char [],int );//ID的查重，保证不会成功注册两个相同的ID
bool regist_get_code(int type);//密码的查询
bool regist_get_mail(int type);//注册邮箱
bool regist_get_tel();//获取用户电话
void regist();//注册
void login();//登陆主界面
void A_function();//管理员登录
void U_function();//用户登录

//管理员主函数
void A_order();//管理员订单管理系统
void A_screen();//管理员影厅管理系统
void A_screen_check();//管理员影厅查询
void A_screen_add();//管理员影厅添加
bool A_screen_exist(int);//管理员影厅添加影厅检查
void A_screen_add_itoa(int room, char *str);//管理员添加的影厅工具函数
void A_session();//管理员场次管理系统
void A_session_check();//管理员场次查询
void A_session_add();//管理员场次添加
bool A_session_add_get_name(char name[]);//管理员场次添加 - 获取电影名
bool A_session_add_get_room(int &room);//管理员场次添加 - 获取放映厅号
bool A_session_add_get_len(int &choice);//管理员场次添加 - 获取语言
bool A_session_add_get_price(float &price);//管理员场次添加 - 获取票价
bool A_session_add_get_duration(int &duration);//管理员场次添加 - 获取影片时长
bool A_session_add_get_time_year(int &year);//管理员场次添加 - 获取开始时间 - 年
bool A_session_add_get_time_month(int &month);//管理员场次添加 - 获取开始时间 - 月
bool A_session_add_get_time_day(int &day);//管理员场次添加 - 获取开始时间 - 日
bool A_session_add_get_time_hour(int &hour);//管理员场次添加 - 获取开始时间 - 时
bool A_session_add_get_time_minute(int &minute);//管理员场次添加 - 获取开始时间 - 分
void A_screen_add_itoa(int, char);//管理员添加的影厅工具函数
bool A_session_add_valid(MovieMessage info);//判断添加片场时间是否合法
time_t A_session_add_valid_get_time(MovieMessage info);// 场次添加时间验证 - 时间转换工具
bool A_session_add_print(MovieMessage info);//把增添场次信息打印进文件
void A_information();//管理员个人信息
void A_check();//管理员信息查看
void A_change();//管理员信息更改
void A_order(); //管理员查看订单
void Cinemaquire();//按照已购票人数未放映升降序
void rangeTotalin();//按总收入已放映升序
void shengjiang();//按照上座率升降序排列

//用户主函数
bool U_information(); //用户个人信息
void U_check();//用户信息查看
bool U_change();//用户基本信息更改
void U_recharge();//用户充值
void U_movie();//用户搜索电影
void U_order();//用户订单管理
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
void init();//初始化函数
void clear_screen();//清屏
int get_choice(char* str, int start, int end);//获取正确用户数字选择
int get_choice_show_screen(char* str_title,char* str, int start, int end);//获取正确用户数字选择(显示影厅特别版)
int judge_num(char num[]);//判断用户输入是否为整数
int judge_choice(char* input, int start, int end);//判断是否为正确数字
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
bool is_leap_year(int year);//判断是闰年