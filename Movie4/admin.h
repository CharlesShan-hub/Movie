void ui_admin()
{
    const char tip[] = "************ Administrator - Main ****************\n\n"
                       "If you want to view personal information, please enter 1\n"
                       "If you want to enter the cinema hall system, please enter 2\n"
                       "If you want to manage sessions, please enter 3\n"
                       "If you want to view order status, please enter 4\n"
                       "If you want to exit, please enter 5\n";
    while (true)
    {
        switch (get_choice(1, 5, 2, tip, "Please enter your choice:"))
        {
        case 1:
            // ui_admin_information(); /* Administrator Information System */
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
