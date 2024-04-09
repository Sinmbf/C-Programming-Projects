#include<stdio.h>
#include<stdlib.h>
struct employee
{
	int id;
	char name[100];
	char job_title[100];
	long long int contact;
	int age;
}emp[100];
void add(struct employee emp[],FILE *fp);
void update();
void del();
void display();
void main()
{
	FILE *fp,*fp1;
	int i=0;
	int ch;
	char ci;
	fp=fopen("employee.txt","a+");
	if(fp==NULL)
	{
		printf("Error on opening file");
		exit(0);
	}
	do
	{
	printf("**********Employee Management System**********\n");
	printf("1.Add Employees\n");
	printf("2.Update Employees\n");
	printf("3.Delete Employees\n");
	printf("4.Display Employees\n");
	printf("5.Exit\n");
	printf("Enter Your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			add(emp,fp);
		break;
		
		case 2:
			update(emp,fp);
		break;
		
		case 3:
			del(emp);
		break;
		
    	case 4:
			display(emp);
		break;
		
		case 5:
			exit(0);
		break;
		
		default:
		printf("Invalid choice");
	}
	printf("Do You Want to Continue(y/n):");
	scanf(" %c",&ci);
  }while(ci=='y' || ci=='Y');
	fclose(fp);
}
void add(struct employee emp[],FILE *fp)
{
	int i=0;
	char ch;
	system("cls");
	do
	{
	printf("Please Enter your Id No:");
	scanf("%d",&emp[i].id);
	printf("Enter Your Name:");
	fflush(stdin);
	gets(emp[i].name);
	printf("Please Enter Your Job Title:");
	gets(emp[i].job_title);
	printf("Please provide your contact information:");
	scanf("%lld",&emp[i].contact);
	getchar();
	printf("Enter your age:");
	scanf("%d",&emp[i].age);
	getchar();
	fprintf(fp,"%d %s %s %lld %d\n",emp[i].id,emp[i].name,emp[i].job_title,emp[i].contact,emp[i].age);
	printf("\n*****Information added successfully*****");
	printf("\nDo you want to add more employee information(y/n):");
	scanf(" %c", &ch);
	system("cls");
	getchar();	
	i++;
}while(ch=='y' || ch=='Y');
  fclose(fp);
}
void update(struct employee emp[],FILE *fp)
{
	int id,i=0,found=0;
	system("cls");
	printf("Enter the employee ID to update:");
	scanf("%d", &id);
    rewind(fp);
	while(fscanf(fp,"%d %s %s %lld %d",&emp[i].id,&emp[i].name,&emp[i].job_title,&emp[i].contact,&emp[i].age)!=EOF)
	{
		if(emp[i].id==id)
		{
			printf("File Found Sucessfully\n");
        	printf("Please Enter Your Name:");
	        fflush(stdin);
	        gets(emp[i].name);
	        printf("Please Enter New Job Title:");
	        gets(emp[i].job_title);
	        printf("Enter New Contact:");
	        scanf("%lld",&emp[i].contact);
	        printf("Enter current age:");
	        scanf("%d",&emp[i].age);
	        printf("Update Successfully\n");
	        fseek(fp,0,0);
	        fprintf(fp,"%d %s %s %lld %d",emp[i].id,emp[i].name,emp[i].job_title,emp[i].contact,emp[i].age);
	        found=1;
	        
	        break;
		}
		i++;
	
	}
	if(found==0)
	{
		printf("Employee Record Not Found of ID NO:%d\n",id);
	}
	fclose(fp);
}
void del(struct employee emp[])
{
	
}
void display(struct employee emp[]) 
{
	FILE *fp;
    int i = 0;
    system("cls");
    fp = fopen("employee.txt", "r");
    if (fp == NULL) {
        printf("Error on opening file");
        exit(0);
    }
    printf("=================================================================================\n");
    printf("| %-6s | %-20s | %-20s | %-15s | %-5s |\n", "ID no.", "Name", "Job Title", "Contact no.", "Age");
    printf("=================================================================================\n");
    while (fscanf(fp, "%d %s %s %lld %d", &emp[i].id, emp[i].name, emp[i].job_title, &emp[i].contact, &emp[i].age) == 5) {
        printf("| %-6d | %-20s | %-20s | %-15lld | %-5d |\n", emp[i].id, emp[i].name, emp[i].job_title, emp[i].contact, emp[i].age);
        i++;
    }
    printf("=================================================================================\n");
    rewind(fp);
    fclose(fp);
}
