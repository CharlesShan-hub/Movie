#include "movie.h"
#include "utils.h"
#include "auth.h"
#include "admin.h"
#include "cust.h"

/***************************************************************************
                                  MAIN
****************************************************************************/
int main()
{
    const char tip[] =
        "******* Movie Theater Ticketing System (Not Logged In) *******\n\n"
        "If you are a new user, please enter 1\n"
        "If you need to log in, please enter 2\n"
        "If you wish to exit, please enter 3\n";
    while (true)
    {
        init();
        switch (get_choice(1, 3, 2, tip, "Please enter your choice:"))
        {
        case 1:
            ui_regist();
            break;
        case 2:
            ui_login();
            break;
        case 3:
            return 0;
        }
    }
}

void ui_login()
{
    const char tip_base[] =
        "*********** Login Interface **********\n\n"
        "If you are an administrator, please enter 1\n"
        "If you are a customer, please enter 2\n"
        "To return to the previous menu, please enter 3\n";
    while (true)
    {
        switch (get_choice(1, 3, 2, tip_base, "Please enter your choice:"))
        {
        case 1:
            if (!ui_login_admin())
                return;
            break;
        case 2:
            if (!ui_login_cust())
                return;
            break;
        case 3:
            return;
        }
    }
}

void ui_regist()
{
    const char tip_base[] =
        "*********** Registration Interface **********\n\n"
        "If you are an administrator, please enter 1\n"
        "If you are a customer, please enter 2\n"
        "To return to the previous menu, please enter 3\n";
    while (true)
    {
        switch (get_choice(1, 3, 2, tip_base, "Please enter your choice:"))
        {
        case 1:
            if (!ui_regist_admin())
                return;
            break;
        case 2:
            if (!ui_regist_cust())
                return;
            break;
        case 3:
            return;
        }
    }
}

void ui_admin()
{
    RUNTIME_INFO.login = true;
    const char tip[] = "************ Administrator - Main ****************\n\n"
                       "If you want to operate personal information, please enter 1\n"
                       "If you want to enter the cinema hall system, please enter 2\n"
                       "If you want to manage sessions, please enter 3\n"
                       "If you want to view order status, please enter 4\n"
                       "If you want to exit, please enter 5\n";
    while (true)
    {
        switch (get_choice(1, 5, 2, tip, "Please enter your choice:"))
        {
        case 1:
            if (!ui_admin_profile())
                return;
            break;
        case 2:
            // ui_admin_screen(); /* Administrator Cinema Hall Management System */
            break;
        case 3:
            // ui_admin_session(); /* Administrator Session Management System */
            break;
        case 4:
            // ui_admin_order(); /* Administrator Order Management System */
            break;
        default:
            return;
        }
    }
}

void ui_cust()
{
    const char tip[] = "************ Customer - Main ****************\n\n"
                       "If you want to view your information, please enter 1\n"
                       "If you want to search for movies, please enter 2\n"
                       "If you want to view your orders, please enter 3\n"
                       "If you want to exit, please enter 4\n";
    while (true)
    {
        switch (get_choice(1, 4, 2, tip, "Please enter your choice:"))
        {
        case 1:
            // ui_cust_profile(); /* User Personal Information */
            break;
        case 2:
            // ui_cust_movie(); /* User Movie Search */
            break;
        case 3:
            // u_cust_order(); /* User Order Management */
            break;
        default:
            return;
        }
    }
}

/***************************************************************************
                                  AUTH - Login
****************************************************************************/
bool ui_login_admin()
{
    const char tip[] =
        "*********** Login Page - Administrator **********\n\n"
        "[Enter 'q' at any prompt to stop login]\n";
    char tip2[BUFFER_SIZE] = "";
    AdminProfile ap;
    enum User admin = Admin;
    for (int i = 1; i < 4; i++)
    {
        if (i == 1)
            strcpy(tip2, "");
        else
            sprintf(tip2, "You have %d times to try!\n", 4 - i);
        while (true)
        {
            if (i == 1 && !_login_get_id(ap.id, tip, admin))
                return true;
            if (!_login_get_code(ap.code, tip, tip2))
                return true;
            break;
        }
        if (_login_check_admin(ap.id, ap.code))
        {
            ui_admin();
            return false;
        }
    }
    return true;
}

bool ui_login_cust()
{
    const char tip[] =
        "*********** Login Page - Customer **********\n\n"
        "[Enter 'q' at any prompt to stop login]\n";
    char tip2[BUFFER_SIZE] = "";
    CustomerProfile cp;
    enum User cust = Cust;
    for (int i = 1; i < 4; i++)
    {
        if (i == 1)
            strcpy(tip2, "");
        else
            sprintf(tip2, "You have %d times to try!\n", 4 - i);
        while (true)
        {
            if (i == 1 && !_login_get_id(cp.id, tip, cust))
                return true;
            if (!_login_get_code(cp.code, tip, tip2))
                return true;
            break;
        }
        if (_login_check_cust(cp.id, cp.code))
        {
            ui_cust();
            return false;
        }
    }
    return true;
}

/***************************************************************************
                                  AUTH - Regist
****************************************************************************/

bool ui_regist_admin()
{
    const char tip[] =
        "*********** Registration Page - Administrator **********\n\n"
        "[Enter 'q' at any prompt to stop registration]\n";
    RuntimeInfo p = {.type = ADMIN};
    while (true)
    {
        if (!_regist_get_id(p.profile.admin.id, tip, ADMIN))
            return true;
        if (!_regist_get_code(p.profile.admin.code, tip))
            return true;
        if (!_regist_get_name(p.profile.admin.name, tip))
            return true;
        if (!_regist_get_cinema(p.profile.admin.cinema, tip))
            return true;
        if (!_regist_get_mail(p.profile.admin.mail, tip))
            return true;
        if (!_regist_check_admin(p.profile.admin))
            return true;
        break;
    }
    set_admin_profile(p.profile);
    write_admin_profile(p.profile);
    ui_admin();
    return false;
}

bool ui_regist_cust()
{
    const char tip[] =
        "*********** Registration Page - Customer **********\n\n"
        "[Enter 'q' at any prompt to stop registration]\n";
    RuntimeInfo p = {.type = CUST};
    while (true)
    {
        if (!_regist_get_id(p.profile.cust.id, tip, CUST))
            return true;
        if (!_regist_get_code(p.profile.cust.code, tip))
            return true;
        if (!_regist_get_name(p.profile.cust.name, tip))
            return true;
        if (!_regist_get_sex(p.profile.cust.sex, tip))
            return true;
        if (!_regist_get_tele(p.profile.cust.tele, tip))
            return true;
        if (!_regist_get_mail(p.profile.cust.mail, tip))
            return true;
        p.profile.cust.money = NEW_CUST_INIT_MONEY;
        break;
    }
    set_cust_profile(p.profile);
    write_cust_profile(p.profile);
    ui_cust();
    return false;
}

/***************************************************************************
                                  ADMIN - Profile
****************************************************************************/
bool ui_admin_profile()
{
    char tip[] = "************ Administrator - Profile ****************\n\n"
                 "If you want to check personal information, please enter 1\n"
                 "If you want to modify personal information, please enter 2\n"
                 "If you want to goto back page, please enter 3\n"
                 "If you want to logout, please enter 4\n";
    while (true)
    {
        switch (get_choice(1, 4, 2, tip, "Please enter your choice:"))
        {
        case 1:
            ui_admin_profile_check();
            break;
        case 2:
            ui_admin_profile_modify();
            break;
        case 3:
            return true;
        case 4:
            return false;
        }
    }
}

void ui_admin_profile_check()
{
    clear_screen();
    printf("*********** Administrator - Profile - Check **********\n\n"
           " * ID: %s\n"
           " * Code: %s\n"
           " * Name: %s\n"
           " * Cinema: %s\n"
           " * Mail: %s\n"
           "[Enter any key to the last page.]\n",
           RUNTIME_INFO.profile.admin.id,
           RUNTIME_INFO.profile.admin.code,
           RUNTIME_INFO.profile.admin.name,
           RUNTIME_INFO.profile.admin.cinema,
           RUNTIME_INFO.profile.admin.mail);
    fflush(stdin);
    getchar();
}

void ui_admin_profile_modify()
{
    char tip[] = "*********** Administrator - Profile - Modify **********\n\n"
                 "If you want to change `id`, please enter 1\n"
                 "If you want to change `code`, please enter 2\n"
                 "If you want to change `name`, please enter 3\n"
                 "If you want to change `cinema`, please enter 4\n"
                 "If you want to change `mail`, please enter 5\n"
                 "If you want to goto back page, please enter 6\n"
                 "If you want to logout, please enter 7\n";
    while (true)
    {
        switch (get_choice(1, 4, 2, tip, "Please enter your choice:"))
        {
        case 1:
            ui_admin_profile_check();
            break;
        case 2:
            ui_admin_profile_modify();
            break;
        case 3:
            return true;
        case 4:
            return false;
        }
    }
}

/***************************************************************************
                                   CUST
****************************************************************************/
