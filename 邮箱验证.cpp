#include <stdio.h>
void youxiangcheck();
int main()
{
	youxiangcheck();
	return 0;
}
void youxiangcheck()
{
	char youxiang[50]={'\0'};
	int i=0,b=0,j=0,check1=0,check2=0,c1=0,c2=0;
	
	while (b!=1)
		{
			printf("请输入您的邮箱：（格式为***@***.***)\n");
			scanf("%s",youxiang);
			while (youxiang[j]!='\0')
				{
					if (youxiang[j]=='@') {c1++; check1=j;}
					if (youxiang[j]=='.') {c2++; check2=j;}
					if (c1==1&&c2==1)	b=1;	else b=0;
					j++;
				}
			if (check2<=check1+1||check1==1||check2==j-1) b=0;
			if (b==0)	printf("你的邮箱不合法！\n"); 
				else printf("你的邮箱合法！\n");
		}
}
