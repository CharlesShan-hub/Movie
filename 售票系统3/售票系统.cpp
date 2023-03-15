#include "movie.h"
#include "auth.h"
#include "admin.h"
#include "user.h"
#include "tool.h"

int main()
{
  char temp_str[] = "******* 电影院售票系统(未登录) *******\n\n"
 "如果您是新用户, 请您输入 1:\n"
 "如果您需要登录, 请您输入 2:\n"
 "如果您希望退出, 请您输入 3:\n";
  while(true)
  {
    init();
    switch(get_choice(temp_str,1,3)){
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
