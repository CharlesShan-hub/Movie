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
