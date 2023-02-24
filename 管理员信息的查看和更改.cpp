void A_change(char id1[20])//管理员信息更改 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","r");
	fp=fopen("administrators1.txt","w");
	int a=0,b=0;
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	printf("\n如果你想更改你的姓名，请输入1\n");
	printf("如果你想更改你的邮箱，请输入4\n");
	printf("如果你想更改你的密码，请输入5\n");
	printf("如果你想返回上一界面，请输入任意值\n"); 
	scanf("%d",&a);
	switch(a)
	{	case 1://更改姓名 
			{
				while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
				{
				if(strcmp(id1,id2)==0)
		 	  {	printf("\n请输入您的新姓名：\n");//输入姓名 
   			    scanf("%s",name);
		 		fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);	
			   }
			 else
			 {fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);}
			 } 
   		    	fclose(AFile);
		       fclose(fp);
		       modify();	break;
			}
		case 4://更改邮箱 
			{
			  while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
			  {
			  	if(strcmp(id1,id2)==0)
			  	{youxiangcheckA();
				fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,U_quanju.Mail);	}
				else
			   {fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);}
			  }	
			  fclose(AFile);
		       fclose(fp);
		       modify();
			   break;
			}
		case 5://更改密码 
			{ int x=1;
			while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)	
			{
			  	if(strcmp(id1,id2)==0)
			  	{
			  		codecheck(x);
					fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,U_quanju.Code,mail);	
				}
				else
			   {fprintf(fp,"%s  %s  %s  %s  %s",id2,name,cinema,code2,mail);}
			  }	
			  fclose(AFile);
		       fclose(fp);
		       modify();break;
			}
		default:A_information(id1);break;//返回上一界面 
	}
}