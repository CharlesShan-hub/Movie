void A_change(char id1[20])//����Ա��Ϣ���� 
{
	FILE *AFile,*fp;
	AFile=fopen("administrators.txt","r");
	fp=fopen("administrators1.txt","w");
	int a=0,b=0;
	char id2[20],cinema[20],code1[20],code2[20],mail[50],name[20];
	printf("\n�������������������������1\n");
	printf("����������������䣬������4\n");
	printf("����������������룬������5\n");
	printf("������뷵����һ���棬����������ֵ\n"); 
	scanf("%d",&a);
	switch(a)
	{	case 1://�������� 
			{
				while(fscanf(AFile,"%s  %s  %s  %s  %s\n",id2,name,cinema,code2,mail)!=EOF)
				{
				if(strcmp(id1,id2)==0)
		 	  {	printf("\n������������������\n");//�������� 
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
		case 4://�������� 
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
		case 5://�������� 
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
		default:A_information(id1);break;//������һ���� 
	}
}