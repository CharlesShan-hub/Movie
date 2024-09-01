#include "movie.h"
#include "utils.h"
#include "auth.h"

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
            regist();
            break;
        case 2:
            login();
            break;
        case 3:
            return 0;
        }
    }
}