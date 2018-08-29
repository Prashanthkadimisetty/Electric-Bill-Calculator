#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<windows.h>


void password();
void admin();
void addcustomer();
void generateBill();
void displaybill();
void deletebill();

char ch;

struct customer
{
    char name[30];
    int custom_id;
    double cost_per_unit;
    char phone[15];
}E;
struct Bill
{
     long int bill_id;
    char name_bill[30];
    double unit_consumed;
    double C_per_unit;
    double totbill;
}P;

int main()
{
	srand(time(NULL));
    mainmenu:
    char op;
    printf("*********************ELECTRIC BILL CALCULATOR*****************");
    printf("\n1.Add New Customer");
    printf("\n2.Generate Bill");
    printf("\n3.Display bill");
    printf("\n4.Delete Bill");
    printf("\n5.ADMIN LOGIN");
    printf("\n6.EXIT");
    printf("\n**************************************************************");
    printf("\n     CREATED & DEVELOPED BY PRASHANTH");
    printf("\n**************************************************************");

    printf("\nPlease Enter your choice:");
    op=getch();
    switch(op)
    {
      case '1':
          addcustomer();
          break;
      case '2':
           generateBill();
           break;
      case '3':
           displaybill();
           break;
      case '4':
           deletebill();
           break;
      case '5':
      	   admin();
      	   break;
      case '6':
            system("cls");
            printf("\n\n\n\n\n\n\n\t\t\tTHANKS FOR USING THIS CALCULATOR!! ");
            Sleep(1500);
            exit(0);
            break;
      default:
            printf("\nINVALID OPTION");
            Sleep(1000);
            system("cls");
            goto mainmenu;
            break;
     }
     if(ch=='*')
     {
     system("cls");
     goto mainmenu;
     }
     else
     {
     	system("cls");
     	printf("\n\n\n\n\n\n\n\n\t\t\t\tTHANKS FOR USING THIS CALCULATOR!!");
     	Sleep(1500);
     	exit(0);
	 }


}

void addcustomer()
{
    char another='Y';
    FILE *fp;
    fp=fopen("CustomerList.txt","a+");
    while(toupper(another)=='Y')
    {
       fflush(stdin);
       system("cls");
       printf("\n\n\n\n\n\n\n\t\t\t******************************************************");
       printf("\n\t\t\t\tCUSTOMER NAME:");
       gets(E.name);
       printf("\n\t\t\t\tCONTACT NUMBER:");
       gets(E.phone);
       printf("\n\t\t\t\t COST PER UNIT:");
       scanf("%lf",&E.cost_per_unit);
       E.custom_id=1000+(rand()%9000);
       printf("\n\t\t\t\t UNIQUE CUSTOMER ID:%d",E.custom_id);
       fwrite(&E,sizeof(E),1,fp);
       printf("\nDo want to enter the details of another customer(Y/N):");
       another=getch();
       
    }
    ch='*';
    fclose(fp);
   
}
 void generateBill()
 {
 	FILE *ft,*fp;
 	int uni_id=0;
	int start=0,end=0,f=0;
	flag:
	system("cls");
	printf("\n\n\n\n\n\n\n\n\t\t\t**********************************************");
 	printf("\n\t\t\t\t PLEASE ENTER YOUR UNIQUE CUSTOMER ID:");
 	scanf("%d",&uni_id);
 	fp=fopen("CustomerList.txt","r+");
 	while(fread(&E,sizeof(E),1,fp)==1)
 	{
 	  if(E.custom_id==uni_id)
	   {
	   	  P.C_per_unit=E.cost_per_unit;
	   	  strcpy(P.name_bill,E.name);
	   	  f=1;
	   	  break;
	   }	
	 }
	 fclose(fp);
 	if(f==0)
 	{
 		system("cls");
 		printf("\n\n\n\n\n\n\n\t\t\t\tWRONG CUSTOMER ID");
 		Sleep(2000);
 		goto flag;
	 }
	printf("\n\t\t\t\t PLEASE ENTER THE OLD METER READING:");
	scanf("%d",&start);
	printf("\n\t\t\t\t PLEASE ENTER THE NEW METER READING:");
	scanf("%d",&end);
	P.unit_consumed=(end-start);
	P.totbill=P.unit_consumed*P.C_per_unit;
	printf("\n\t\t\t\t THE TOTAL AMOUNT OF ELECTRICITY BILL : %lf",P.totbill);
	P.bill_id=(rand()%900000)+100000;
	printf("\n\t\t\t\t BILL ID:%ld",P.bill_id);
	ft=fopen("Bills.txt","a+");
	fwrite(&P,sizeof(P),1,ft);
	printf("\n Press '*' For Main Menu,Press Any other key to exit");
	ch=getch();
	fclose(ft);
	fclose(fp);
 }
 
 void displaybill()
 {
 	int f=0;
	long int id;
	char tr;
	tent:
 	FILE *t1;
 	system("cls");
 	t1=fopen("Bills.txt","r+");
 	printf("\n\n\n\n\n\n\n\n\n\n\t\t\t*******************************************");
 	printf("\n\t\t\t\tPLEASE ENTER YOUR BILL ID:");
 	scanf("%ld",&id);
 	while(fread(&P,sizeof(P),1,t1)==1)
 	{
 		if(id==P.bill_id)
 		{
 		printf("\n\t\t\t\tNAME OF THE CUSTOMER:%s",P.name_bill);
 		printf("\n\t\t\t\tNO. OF UNITS CONSUMED: %lf",P.unit_consumed);
 		printf("\n\t\t\t\tTOTAL BILL AMOUNT: %lf",P.totbill);
 		f=1;
 		break;
 	    }
	 }
	 if(f==0)
	 {
	 	printf("\n\t\t\t\tWRONG BILL ID,BILL NOT FOUND!!");
	 	Sleep(1000);
	 	printf("\npress '$' to try again ,Press '*'for main menu,Press anyother key to exit" );
	 	tr=getch();
	 	if(tr=='$')
	 	  goto tent;
	 	else if(tr=='*')
	 	{
	 	  ch=tr;
	 	  goto dodo;
	    }
	 	else
	 	  goto dodo;
	 	
	 }
	 fclose(t1);
     printf("\nPress '*' for mainmenu, Press anyother key to exit");
	 ch=getch();
	 dodo:
	 	printf(".");
 }

void deletebill()
{
	int f=0;
	char tr;
	long int id;
	flag:
	system("cls");
	printf("\n\n\n\n\n\n\n\t\t\t\tPLEASE ENTER YOUR BILL ID:");
	scanf("%ld",&id);
	FILE *t2,*t3;
	t2=fopen("Bills.txt","r+");
	t3=fopen("temp.txt","w+");
	
	while(fread(&P,sizeof(P),1,t2)==1)
	{
		if(id==P.bill_id)
		{
			f=1;
		  continue;
	    }
	    fwrite(&P,sizeof(P),1,t3);
	}
	fclose(t2);
	fclose(t3);
	remove("Bills.txt");
	rename("temp.txt","Bills.txt");
	if(f==0)
	{
		system("cls");
		printf("\n\n\n\n\n\n\t\t\t\tBILL NOT FOUND!!!");
		Sleep(2000);
			printf("\npress '$' to try again ,Press '*'for main menu,Press anyother key to exit" );
	 	tr=getch();
	 	if(tr=='$')
	 	  goto flag;
	 	else if(tr=='*')
	 	{
	 	  ch=tr;
	 	  goto dodo;
	    }
	 	else
	 	  goto dodo;
		
	}
	else
	 printf("\nBILL DELETED SUCCESSFULLY!!!");
	 printf("\nPress '*' for mainmenu, Press anyother key to exit");
	 ch=getch();
	 dodo:
	 	printf(".");
	
}

void admin()
{
	int f=1,i=0;
	char c,y;
	int count=0;
	char temp[11];
	char pass[10];
	char check[10];
	system("cls");
	printf("\n\n\n\n\n\n\n\n\t\t\t********************ADMIN LOGIN*************************");
	tryagain:
	printf("\n\t\t\t\tPASSWORD:");
	for(i=0;i<11;i++)
	{
		temp[i]=getch();
		if(temp[i]=='\b')
		{
			printf("\b");
			printf(" ");
			printf("\b");
			i--;
			continue;
		}
		if(temp[i]==13)
		{
		temp[i]='\0';
		break;
	    }
		printf("*");
	}
	strcpy(pass,temp);
	FILE *fp;
	fp=fopen("PASSWORD.txt","r+");
	fgets(check,10,fp);
	if(strcmp(pass,check)==0)
	{
		goto hulk;
	}
	else
	{
	 f=0;
	 count++;
    }
	if(f==0)
	{
		printf("\n\t\t\t\tWRONG PASSWORD ENTERED!!");
		printf("\n\t\t\t\t%d Trails left:",(3-count));
		if(count<3)
		{
			goto tryagain;
		}
		else{
			printf("\n\t\t\t\tSORRY PLEASE TRY AGAIN....");
			Sleep(2000);
			ch='*';
			goto doom;
		}
	    
	}
	fclose(fp);
	hulk:
	mainmenu1:
	system("cls");
	printf("********************WELCOME ADMIN*********************");
	printf("\n1.VIEW CUSTOMER LIST");
	printf("\n2.VIEW BILLS LIST");
	printf("\n3.CHANGE ADMIN PASSWORD");
	printf("\n4.LOGOUT");
	printf("\n5.EXIT");
	printf("\n*******************************************************");
	printf("\nPlease ENter ur choice:");
	c=getch();
	switch(c)
	{
		case '1':
			system("cls");
			FILE *t1;
			t1=fopen("CustomerList.txt","r+");
			while(fread(&E,sizeof(E),1,t1)==1)
			{
	          printf("\n%s\t%s\t%d\t%lf",E.name,E.phone,E.custom_id,E.cost_per_unit);
			}
			fclose(t1);
			printf("\nPRESS ANY KEY FOR MAINMENU");
			y=getch();
			goto mainmenu1;
		case '2':
			system("cls");
		    FILE *t2;
		    t2=fopen("Bills.txt","r+");
		    while(fread(&P,sizeof(P),1,t2)==1)
		    {
		    	printf("\n%s\t%ld\t%lf\t%lf\t%lf",P.name_bill,P.bill_id,P.C_per_unit,P.unit_consumed,P.totbill);
			}
			fclose(t2);
			printf("\nPRESS ANY KEY FOR MAINMENU");
			y=getch();
			goto mainmenu1;
		case '3':
			char tem[11];
			char pass1[10];
			char pass2[10];
			FILE *t3;
			tent3:
			system("cls");
		    printf("\n\n\n\n\n\n\t\t\t\tENTER NEW PASSWORD:");
		    for(i=0;i<11;i++)
        	{
	        	tem[i]=getch();
		        if(tem[i]==13)
		        break;
		        printf("*");
		        pass1[i]=tem[i];
        	}
			printf("\n\t\t\t\tCONFIRM NEW PASSWORD:");  
			 for(i=0;i<11;i++)
        	{
	        	tem[i]=getch();
		        if(tem[i]==13)
		        break;
		        printf("*");
		        pass2[i]=tem[i];
        	}
        	if(strcmp(pass1,pass2)==0)
        	{
        		t3=fopen("PASSWORD.txt","w+");
        		fputs(pass2,t3);
        		fclose(t3);
        		printf("\n\t\t\t\tPASSWORD CHANGED SUCCESSFULLY!!");
        		printf("\nPress any key for main menu.....");
        		y=getch();
        		goto mainmenu1;
        		
			}
			else
			{
				printf("\n\n\t\t\t\tPASSWORDS DID NOT MATCH");
				Sleep(3000);
				printf("\n\t\t\t\tPress '*' to go to TRYAGAIN,Press any other key for mainmenu....");
				y=getch();
				if(y=='*')
				 goto tent3;
				else
				 goto mainmenu1;
			}
	    case '4':
	    	system("cls");
	    	printf("\n\n\n\n\n\n\n\n\n\t\t\t\tLOGGING OUT......");
	    	Sleep(5000);
	    	ch='*';
	    	goto doom;
	    case '5':
	    	ch='/';
	    	goto doom;
		    
			  
	}
	
	doom:
		printf(".");
		
}

