void clear_screen()
{
    fflush(stdout);
    if (TYPE == 1)
        system("cls");
    else if (TYPE == 2)
        system("clear");
    else
        printf("Unknown System\n");
}

void check_file(const char path[])
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        fclose(fopen(path, "w+"));
    else
        fclose(f);
}

void get_string(char res[], int count, ...)
{
    va_list ap;
    va_start(ap, count);

    // Format Screen
    clear_screen();
    for (int i = 0; i < count; i++)
    {
        char *str = va_arg(ap, char *);
        printf("%s", str);
    }
    va_end(ap);

    // Get New Choice
    fflush(stdin);
    scanf("%s", res);
}

int get_choice(int start, int end, int count, ...)
{
    va_list ap;
    int choice;
    char input[BUFFER_SIZE];
    bool num_tip = false, range_tip = false;
    while (true)
    {
        // Format Screen
        clear_screen();
        va_start(ap, count);
        for (int i = 0; i < count - 1; i++)
            printf("%s", va_arg(ap, char *));

        // Wrong Tips
        if (num_tip)
            printf("Please Input numbers!\n");
        if (range_tip)
            printf("Please Input number in corrent range!\n");
        printf("%s", va_arg(ap, char *));

        // Get New Choice
        fflush(stdin);
        scanf("%s", input);

        // Input Analyse
        if (judge_num(input) == false)
        {
            num_tip = true;
            range_tip = false;
            continue;
        }
        choice = atoi(input);
        if (choice > end || choice < start)
        {
            num_tip = false;
            range_tip = true;
            continue;
        }
        break;
    }

    va_end(ap); // clear va_list
    return choice;
}

bool judge_num(char num[BUFFER_SIZE])
{
    for (size_t i = 0; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}

bool judge_space(char str[BUFFER_SIZE])
{
    for (size_t i = 0; i < strlen(str); i++)
        if (int(str[i]) == 32)
            return true;
    return false;
}

bool judge_digit(char str[BUFFER_SIZE])
{
    for (size_t i = 0; i < strlen(str); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

bool judge_digit_and_letter(char str[BUFFER_SIZE])
{
    bool number_flag = false, letter_flag = false;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
            letter_flag = true;
        else if (isalpha(str[i]))
            number_flag = true;
        if (number_flag && letter_flag)
            return true;
    }
    return false;
}

bool judge_only_digit_and_letter(char str[BUFFER_SIZE])
{
    for (size_t i = 0; i < strlen(str); i++)
        if (isalnum(str[i]) == false)
            return false;
    return true;
}
