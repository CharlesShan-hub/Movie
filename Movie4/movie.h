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
    CustomerProfile customer;
} Profile;
Profile PROFILE;

/* utils */
void clear_screen();
void check_file(const char *path);
int get_choice(int start, int end, int count, ...);
void get_string(int count, ...);
bool judge_num(char num[BUFFER_SIZE]);
bool judge_space(char str[BUFFER_SIZE]);
bool judge_digit(char str[BUFFER_SIZE]);
bool judge_digit_and_letter(char str[BUFFER_SIZE]);
bool judge_only_digit_and_letter(char str[BUFFER_SIZE]);

/* Auth */
bool _id_duplicate_admin(char *user_id);
bool _id_duplicate_cust(char *user_id);
bool _regist_get_id(char *user_id, const char *tip);
bool _regist_get_code(char *code, const char *tip);
bool _regist_get_name(char *name, const char *tip);
bool _regist_get_cinema(char *cinema, const char *tip);
bool _regist_get_mail(char *mail, const char *tip);
bool _regist_get_sex(char *sex, const char *tip);
bool _regist_get_tele(char *tele, const char *tip);
bool _regist_check_admin(AdminProfile ap);
bool _regist_check_cust(CustomerProfile ap);
void regist_admin();
void regist_cust();

void init()
{
    check_file(ADMIN_PROFILE_PATH);
    check_file(CUSTOMER_PROFILE_PATH);
}