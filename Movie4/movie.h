#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef _WIN32
#define TYPE 1
#elif __APPLE__
#define TYPE 2
#endif

#define BUFFER_SIZE 128
const char ADMIN_PROFILE_PATH[] = "admin_profile.txt";
const char CUSTOMER_PROFILE_PATH[] = "cust_profile.txt";
#define NEW_CUST_INIT_MONEY 20.0

typedef struct
{
    char id[BUFFER_SIZE]; // key
    char code[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char sex[BUFFER_SIZE];
    char tele[BUFFER_SIZE];
    char mail[BUFFER_SIZE];
    double money;
} CustomerProfile;

typedef struct
{
    char id[BUFFER_SIZE]; // key
    char code[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char cinema[BUFFER_SIZE];
    char mail[BUFFER_SIZE];
} AdminProfile;

typedef union
{
    AdminProfile admin;
    CustomerProfile cust;
} Profile;

enum User
{
    Admin,
    Cust
};
User ADMIN = Admin;
User CUST = Cust;

typedef struct
{
    bool login;
    User type;
    Profile profile;
} RuntimeInfo;
RuntimeInfo RUNTIME_INFO;

/* data structure */
void set_admin_profile(Profile p);
void write_admin_profile(Profile p);
void set_cust_profile(Profile p);
void write_cust_profile(Profile p);

/* utils */
void clear_screen();
void check_file(const char *path);
void debug_print(const char *str);
int get_choice(int start, int end, int count, ...);
void get_string(int count, ...);
bool judge_num(char num[BUFFER_SIZE]);
bool judge_space(char str[BUFFER_SIZE]);
bool judge_digit(char str[BUFFER_SIZE]);
bool judge_digit_and_letter(char str[BUFFER_SIZE]);
bool judge_only_digit_and_letter(char str[BUFFER_SIZE]);

/* auth */
bool _id_duplicate_admin(char *user_id);
bool _id_duplicate_cust(char *user_id);
bool _regist_get_id(char *user_id, const char *tip, enum User user);
bool _regist_get_code(char *code, const char *tip);
bool _regist_get_name(char *name, const char *tip);
bool _regist_get_cinema(char *cinema, const char *tip);
bool _regist_get_mail(char *mail, const char *tip);
bool _regist_get_sex(char *sex, const char *tip);
bool _regist_get_tele(char *tele, const char *tip);
bool _regist_check_admin(AdminProfile ap);
bool _regist_check_cust(CustomerProfile ap);
bool _login_get_id(char *user_id, const char *tip, enum User user);
bool _login_get_code(char *code, const char *tip, const char *tip2);
bool _login_check_admin(char *user_id, char *code);
bool _login_check_cust(char *user_id, char *code);
bool ui_regist_admin(); // return whether to return
bool ui_regist_cust();
void ui_regist();
bool ui_login_admin();
bool ui_login_cust();
void ui_login();

/* admin */
void ui_admin();
bool ui_admin_profile();
void ui_admin_profile_check();
void ui_admin_profile_modify();

/* cust */
void ui_cust();

void init()
{
    RUNTIME_INFO.login = false;
    check_file(ADMIN_PROFILE_PATH);
    check_file(CUSTOMER_PROFILE_PATH);
}

void set_admin_profile(Profile p)
{
    strcpy(RUNTIME_INFO.profile.admin.cinema, p.admin.cinema);
    strcpy(RUNTIME_INFO.profile.admin.mail, p.admin.mail);
    strcpy(RUNTIME_INFO.profile.admin.name, p.admin.name);
    strcpy(RUNTIME_INFO.profile.admin.id, p.admin.id);
    strcpy(RUNTIME_INFO.profile.admin.code, p.admin.code);
}

void write_admin_profile(Profile p)
{
    FILE *file = fopen(ADMIN_PROFILE_PATH, "a+");
    fprintf(file, "%s  %s  %s  %s  %s\n",
            p.admin.id, p.admin.code, p.admin.name, p.admin.cinema, p.admin.mail);
    fclose(file);
}

void set_cust_profile(Profile p)
{

    strcpy(RUNTIME_INFO.profile.cust.id, p.cust.id);
    strcpy(RUNTIME_INFO.profile.cust.code, p.cust.code);
    strcpy(RUNTIME_INFO.profile.cust.mail, p.cust.mail);
    strcpy(RUNTIME_INFO.profile.cust.name, p.cust.name);
    strcpy(RUNTIME_INFO.profile.cust.sex, p.cust.sex);
    strcpy(RUNTIME_INFO.profile.cust.tele, p.cust.tele);
    RUNTIME_INFO.profile.cust.money = p.cust.money;
}

void write_cust_profile(Profile p)
{
    FILE *file = fopen(CUSTOMER_PROFILE_PATH, "a+");
    fprintf(file, "%s  %s  %s  %s  %s  %lf  %s\n",
            p.cust.id, p.cust.name, p.cust.sex, p.cust.tele, p.cust.code, p.cust.money, p.cust.mail);
    fclose(file);
}