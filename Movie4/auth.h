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
    Profile p;
    FILE *file = fopen(ADMIN_PROFILE_PATH, "r");
    rewind(file);
    while (fscanf(file, "%s  %s  %s  %s  %s",
                  p.admin.id, p.admin.code, p.admin.name, p.admin.cinema, p.admin.mail) != EOF)
    {
        if (!strcmp(user_id, p.admin.id) && !strcmp(code, p.admin.code))
        {
            set_admin_profile(p);
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

bool _login_check_cust(char *user_id, char *code)
{
    Profile p;
    FILE *file = fopen(CUSTOMER_PROFILE_PATH, "r");
    rewind(file);
    while (fscanf(file, "%s  %s  %s  %s  %s  %lf  %s\n",
                  p.cust.id, p.cust.name, p.cust.sex, p.cust.tele, p.cust.code, &p.cust.money, p.cust.mail) != EOF)
    {
        if (!strcmp(user_id, p.cust.id) && !strcmp(code, p.cust.code))
        {
            set_cust_profile(p);
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}
