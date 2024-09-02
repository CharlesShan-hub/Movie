bool _id_duplicate_admin(char *user_id)
{
    FILE *fp = fopen(ADMIN_PROFILE_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to open the file\n");
        return true; // true means duplicate
    }
    AdminProfile ap;
    while (fscanf(fp, "%s  %*s  %*s  %*s  %*s", ap.id) != EOF)
    {
        if (!strcmp(user_id, ap.id))
        {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

bool _id_duplicate_cust(char *user_id)
{
    FILE *fp = fopen(CUSTOMER_PROFILE_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to open the file\n");
        return true; // true means duplicate
    }
    CustomerProfile cp;
    while (fscanf(fp, "%s  %*s  %*s  %*s  %*s  %*lf  %*s", cp.id) != EOF)
    {
        if (!strcmp(user_id, cp.id))
        {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

bool _regist_get_id(char *user_id, const char *tip, enum User user)
{
    bool length_tip, multiple_tip, wrong_type_tip, duplicate_tip;
    length_tip = multiple_tip = wrong_type_tip = duplicate_tip = false;
    while (true)
    {
        // Format Screen
        clear_screen();
        printf("%s", tip);

        // Wrong Tips
        if (length_tip)
            printf("Length should between 6 and 10!\n");
        else if (multiple_tip)
            printf("The id should both have letter and digit!\n");
        else if (wrong_type_tip)
            printf("The id should only contain letter and digit!\n");
        else if (duplicate_tip)
            printf("This id is duplicated, change another one!\n");

        printf("%s", "ID:");

        // Get New Choice
        fflush(stdin);
        scanf("%s", user_id);

        // Input Analyse
        if (!strcmp(user_id, "q"))
            return false;
        if (length_tip = (strlen(user_id) < 6 || strlen(user_id) > 10))
            continue;
        if (multiple_tip = !judge_digit_and_letter(user_id))
            continue;
        if (wrong_type_tip = !judge_only_digit_and_letter(user_id))
            continue;
        switch (user)
        {
        case Admin:
            if (duplicate_tip = _id_duplicate_admin(user_id))
                continue;
            break;
        case Cust:
            if (duplicate_tip = _id_duplicate_cust(user_id))
                continue;
            break;
        }
        break;
    }

    return true;
}

bool _regist_get_code(char *code, const char *tip)
{
    bool length_tip, same_tip;
    length_tip = same_tip = false;
    char again_str[BUFFER_SIZE];
    char tip_str[BUFFER_SIZE];
    while (true)
    {
        // Wrong Tips
        if (length_tip)
            strncpy(tip_str, "Length should between 6 and 10!\n", BUFFER_SIZE);
        else if (same_tip)
            strncpy(tip_str, "The two pasword should be same!\n", BUFFER_SIZE);
        else
            strncpy(tip_str, "", BUFFER_SIZE);

        // Input and Analyse
        get_string(code, 3, tip, tip_str, "Password:");
        if (!strcmp(code, "q"))
            return false;
        if (length_tip = (strlen(code) < 6 || strlen(code) > 10))
            continue;
        get_string(again_str, 2, tip, "Password Again:");
        if (!strcmp(again_str, "q"))
            return false;
        if (same_tip = strcmp(again_str, code))
            continue;
        break;
    }

    return true;
}

bool _regist_get_name(char *name, const char *tip)
{
    get_string(name, 2, tip, "Name: ");
    return strcmp(name, "q");
}

bool _regist_get_cinema(char *cinema, const char *tip)
{
    get_string(cinema, 2, tip, "Cinema: ");
    return strcmp(cinema, "q");
}

bool _regist_get_mail(char *mail, const char *tip)
{
    bool format_tip = false;
    bool at_flag, point_flag;
    while (true)
    {
        // Init
        at_flag = point_flag = false;
        // Format Screen
        clear_screen();
        printf("%s", tip);

        // Wrong Tips
        if (format_tip)
            printf("Format should be ***@***.***\n");

        printf("%s", "Mail:");

        // Get New Choice
        fflush(stdin);
        scanf("%s", mail);

        // Input Analyse
        if (!strcmp(mail, "q"))
            return false;
        // Verify that a period follows the at symbol in the string,
        // with the condition that the period must not be the final character.
        for (size_t i = 0; i < strlen(mail) && mail[i] != '\0'; i++)
        {
            if (mail[i] == '@')
                at_flag = true;
            if (mail[i] == '.' && at_flag)
                point_flag = true;
            if (at_flag && point_flag)
                break;
        }
        if (!(at_flag && point_flag) || mail[strlen(mail) - 1] == '.')
        {
            format_tip = true;
            continue;
        }
        else
            format_tip = false;
        break;
    }

    return true;
}

bool _regist_get_tele(char *tele, const char *tip)
{
    bool digit_tip = false;
    while (true)
    {
        // Format Screen
        clear_screen();
        printf("%s", tip);

        // Wrong Tips
        if (digit_tip)
            printf("Tele should only include numbers!\n");

        printf("%s", "Tele:");

        // Get New Choice
        fflush(stdin);
        scanf("%s", tele);

        // Input Analyse
        if (!strcmp(tele, "q"))
            return false;
        if (digit_tip = !judge_digit(tele))
            continue;
        return true;
    }
}

bool _regist_get_sex(char *sex, const char *tip)
{
    bool char_tip = false;
    while (true)
    {
        // Format Screen
        clear_screen();
        printf("%s", tip);

        // Wrong Tips
        if (char_tip)
            printf("You should input Man('m'), Woman('w') or Secret('s')\n");

        printf("%s", "Sex:");

        // Get New Choice
        fflush(stdin);
        scanf("%s", sex);

        // Input Analyse
        if (!strcmp(sex, "q"))
            return false;
        if (char_tip = (strlen(sex) > 1 || (sex[0] != 'm' && sex[0] != 'w' && sex[0] != 's')))
            continue;
        return true;
    }
}

bool _regist_check_admin(AdminProfile ap)
{
    const char tip1[] = "*********** Registration Page - Administrator **********\n";
    char show_profile[BUFFER_SIZE];
    sprintf(show_profile, "ID: %s\n"
                          "Name: %s\n"
                          "Cinema: %s\n"
                          "Mail: %s\n",
            ap.id, ap.name, ap.cinema, ap.mail);
    const char tip2[] = "If you wish to add and login, please enter 1\n"
                        "If you do not wish to add, please enter 2\n";
    switch (get_choice(1, 2, 3, tip1, show_profile, tip2, "Weather to regist:"))
    {
    case 1:
        return true;
    case 2:
        return false;
    }
    return true;
}

bool _regist_check_cust(CustomerProfile cp)
{
    const char tip1[] = "*********** Registration Page - Customer **********\n";
    char show_profile[BUFFER_SIZE];
    sprintf(show_profile, "ID: %s\n"
                          "Name: %s\n"
                          "Sex: %s\n"
                          "Tele: %s\n"
                          "Mail: %s\n",
            cp.id, cp.name, cp.sex, cp.tele, cp.mail);
    const char tip2[] = "If you wish to add and login, please enter 1\n"
                        "If you do not wish to add, please enter 2\n";
    switch (get_choice(1, 2, 3, tip1, show_profile, tip2, "Weather to regist:"))
    {
    case 1:
        return true;
    case 2:
        return false;
    }
}

bool ui_regist_admin()
{
    const char tip[] =
        "*********** Registration Page - Administrator **********\n\n"
        "[Enter 'q' at any prompt to stop registration]\n";
    AdminProfile ap;
    User admin = Admin;
    while (true)
    {
        if (!_regist_get_id(ap.id, tip, admin))
            return true;
        if (!_regist_get_code(ap.code, tip))
            return true;
        if (!_regist_get_name(ap.name, tip))
            return true;
        if (!_regist_get_cinema(ap.cinema, tip))
            return true;
        if (!_regist_get_mail(ap.mail, tip))
            return true;
        if (!_regist_check_admin(ap))
            return true;
        break;
    }
    strcpy(PROFILE.admin.cinema, ap.cinema);
    strcpy(PROFILE.admin.mail, ap.mail);
    strcpy(PROFILE.admin.name, ap.name);
    strcpy(PROFILE.admin.id, ap.id);
    strcpy(PROFILE.admin.code, ap.code);
    FILE *file = fopen(ADMIN_PROFILE_PATH, "a+");
    fprintf(file, "%s  %s  %s  %s  %s\n",
            ap.id, ap.code, ap.name, ap.cinema, ap.mail);
    fclose(file);
    ui_admin();
    return false;
}

bool ui_regist_cust()
{
    const char tip[] =
        "*********** Registration Page - Customer **********\n\n"
        "[Enter 'q' at any prompt to stop registration]\n";
    CustomerProfile cp;
    User cust = Cust;
    while (true)
    {
        if (!_regist_get_id(cp.id, tip, cust))
            return true;
        if (!_regist_get_code(cp.code, tip))
            return true;
        if (!_regist_get_name(cp.name, tip))
            return true;
        if (!_regist_get_sex(cp.sex, tip))
            return true;
        if (!_regist_get_tele(cp.tele, tip))
            return true;
        if (!_regist_get_mail(cp.mail, tip))
            return true;
        break;
    }
    strcpy(PROFILE.cust.id, cp.id);
    strcpy(PROFILE.cust.code, cp.code);
    strcpy(PROFILE.cust.mail, cp.mail);
    strcpy(PROFILE.cust.name, cp.name);
    strcpy(PROFILE.cust.sex, cp.sex);
    strcpy(PROFILE.cust.tele, cp.tele);
    PROFILE.cust.money = cp.money = 0.0;
    FILE *file = fopen(CUSTOMER_PROFILE_PATH, "a+");
    fprintf(file, "%s  %s  %s  %s  %s  %lf  %s\n",
            cp.id, cp.name, cp.sex, cp.tele, cp.code, cp.money, cp.mail);
    fclose(file);
    ui_cust();
    return false;
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

bool _login_get_id(char *user_id, const char *tip, enum User user)
{
    bool unexist_tip = false;
    while (true)
    {
        // Format Screen
        clear_screen();
        printf("%s", tip);

        // Wrong Tips
        if (unexist_tip)
            printf("ID is not exist!\n");

        printf("%s", "ID:");

        // Get New Choice
        fflush(stdin);
        scanf("%s", user_id);

        // Input Analyse
        if (!strcmp(user_id, "q"))
            return false;
        switch (user)
        {
        case Admin:
            if (unexist_tip = !_id_duplicate_admin(user_id))
                continue;
            break;
        case Cust:
            if (unexist_tip = !_id_duplicate_cust(user_id))
                continue;
            break;
        }
        break;
    }

    return true;
}

bool _login_get_code(char *code, const char *tip, const char *tip2)
{
    get_string(code, 3, tip, tip2, "Code:");
    return strcmp(code, "q");
}

bool _login_check_admin(char *user_id, char *code)
{
    AdminProfile tmp;
    FILE *file = fopen(ADMIN_PROFILE_PATH, "r");
    rewind(file);
    while (fscanf(file, "%s  %s  %s  %s  %s",
                  tmp.id, tmp.code, tmp.name, tmp.cinema, tmp.mail) != EOF)
    {
        if (!strcmp(user_id, tmp.id) && !strcmp(code, tmp.code))
        {
            strcpy(PROFILE.admin.cinema, tmp.cinema);
            strcpy(PROFILE.admin.mail, tmp.mail);
            strcpy(PROFILE.admin.name, tmp.name);
            strcpy(PROFILE.admin.id, tmp.id);
            strcpy(PROFILE.admin.code, tmp.code);
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

bool _login_check_cust(char *user_id, char *code)
{
    CustomerProfile tmp;
    FILE *file = fopen(CUSTOMER_PROFILE_PATH, "r");
    rewind(file);
    while (fscanf(file, "%s  %s  %s  %s  %s  %lf  %s\n",
                  tmp.id, tmp.name, tmp.sex, tmp.tele, tmp.code, &tmp.money, tmp.mail) != EOF)
    {
        if (!strcmp(user_id, tmp.id) && !strcmp(code, tmp.code))
        {
            strcpy(PROFILE.cust.id, tmp.id);
            strcpy(PROFILE.cust.code, tmp.code);
            strcpy(PROFILE.cust.mail, tmp.mail);
            strcpy(PROFILE.cust.name, tmp.name);
            strcpy(PROFILE.cust.sex, tmp.sex);
            strcpy(PROFILE.cust.tele, tmp.tele);
            PROFILE.cust.money = tmp.money;
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

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