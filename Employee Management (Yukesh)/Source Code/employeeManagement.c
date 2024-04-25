#include<stdio.h>
#include<stdlib.h>
struct employee {
	int id;
	char name[100];
	char job_title[100];
	long long int contact;
	int age;
};
void add(struct employee *emp, FILE *fp);
void update(struct employee *emp);
void del(struct employee *emp);
void display();
void main() {
	struct employee emp;
	FILE *fp,*fp1;
	int ch;
	char ci;
	fp=fopen("employee.txt","ab");
	if(fp==NULL) {
		printf("Error on opening file");
		exit(0);
	}
	do {
		system("color 71");
	 printf("**************************************************\n");
        printf("*            Employee Management System           *\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*  1. Add Employees                              *\n");
        printf("*  2. Update Employees                           *\n");
        printf("*  3. Delete Employees                           *\n");
        printf("*  4. Display Employees                          *\n");
        printf("*  5. Exit                                       *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");
		printf("Enter Your choice:");
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				add(&emp,fp);
				break;

			case 2:
				update(&emp);
				break;

			case 3:
				del(&emp);
				break;

			case 4:
				display();
				break;

			case 5:
				exit(0);
				break;

			default:
				printf("Invalid choice\n");
		}
		printf("Do You Want to Continue(y/n):");
		scanf(" %c",&ci);
	} while(ci=='y' || ci=='Y');
	fclose(fp);
}
void add(struct employee *emp,FILE *fp)
{
	char ch;
	system("cls");
	do 
	{
		 printf("**************************************************\n");
        printf("*             Add Employee Information           *\n");
        printf("**************************************************\n");

		printf("Please Enter your Id No:");
		scanf("%d",&emp->id);
		printf("Enter Your Name:");
		fflush(stdin);
		gets(emp->name);
		printf("Please Enter Your Job Title:");
		gets(emp->job_title);
		printf("Please provide your contact information:");
		scanf("%lld",&emp->contact);
		getchar();
		printf("Enter your age:");
		scanf("%d",&emp->age);
		getchar();
		fwrite(emp,sizeof(struct employee),1,fp);
		printf("\n*****Information added successfully*****");
		printf("\nDo you want to add more employee information(y/n):");
		scanf(" %c", &ch);
		system("cls");
		getchar();
	} 
	while(ch=='y' || ch=='Y');
	printf("Successfully saved to file\n");
	fclose(fp);
}
void update(struct employee *emp) 
{
	FILE *fp,*ft1;
	char ch;
	fp=fopen("employee.txt","r+");
	ft1=fopen("update.txt","w");
	if(ft1==NULL)
	{
		printf("Error on opening file");
		exit(0);
	}
	if(fp==NULL)
	{
		printf("Error on opening file");
		exit(0);
	}
	int idu,i=0,found=0;
	system("cls");
	 printf("**************************************************\n");
    printf("*           Update Employee Information          *\n");
    printf("**************************************************\n");

	printf("Enter the employee ID to update:");
	scanf("%d", &idu);
	rewind(fp);
	while(fread(emp,sizeof(struct employee),1,fp)==1)
	{
		if(emp->id==idu) 
		{
			found=1;
			printf("File Found Sucessfully\n");
			printf("Please Enter Your Name:");
			fflush(stdin);
			gets(emp->name);
			printf("Please Enter New Job Title:");
			gets(emp->job_title);
			printf("Enter New Contact:");
			scanf("%lld",&emp->contact);
			printf("Enter current age:");
			scanf("%d",&emp->age);
			printf("Update Successfully\n");
			fwrite(&emp,sizeof(struct employee),1,ft1);
		}
		else
		{
		fwrite(&emp,sizeof(struct employee),1,ft1);
     	}
	}
	if(found==0) 
	{
		printf("Employee Record Not Found of ID NO:%d\n",idu);
	}
	fclose(fp);
	fclose(ft1);
	remove("employee.txt");
	rename("update.txt","employee.txt");
 system("cls");
}
void del(struct employee *emp)  
{
	system("cls");
    FILE *ft,*fp;
    int temp, found = 0;
    char ch;
    do
	{
    ft=fopen("temp.txt", "w"); 
    fp=fopen("employee.txt","r+");
    if (ft == NULL)
	{
        printf("Error on opening temp file");
        exit(0);
    }
    if(fp==NULL)
    {
    	printf("Error on opening file");
    	exit(0);
	}
    rewind(fp);
    printf("**************************************************\n");
    printf("*           Delete Employee Information           *\n");
    printf("**************************************************\n");

    printf("Enter the ID to delete: ");
    scanf("%d", &temp);
    fflush(stdin);
    while (fread(emp, sizeof(struct employee), 1, fp) == 1)
	 {
	 	printf("Checking record with ID: %d\n", emp->id);
        if (temp==emp->id) 
		{
           found=1;
           continue;
        }
        fwrite(emp,sizeof(struct employee),1,ft);
    }

    if (found==0) 
	{
        printf("ID %d not found.\n", temp); 
    }

    fclose(fp);
    fclose(ft);
    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (found) 
	{
        printf("Record with ID %d deleted successfully.\n", temp);
    } else 
	{
        printf("ID %d not found.\n", temp); 
    }
    printf("DO YOU WANT TO DELETE MORE RECORDS(Y/N):");
    scanf(" %c", &ch);
}while(ch=='Y'||ch=='y');
system("cls");
}
void display()
 {
	struct employee emp;
	FILE *fp;
	system("cls");
	fp = fopen("employee.txt", "rb");
	if (fp == NULL)
	 {
		printf("Error on opening file");
		exit(0);
	}
	printf("=================================================================================\n");
	printf("| %-6s | %-20s | %-20s | %-15s | %-5s |\n", "ID no.", "Name", "Job Title", "Contact no.", "Age");
	printf("=================================================================================\n");
	while (fread(&emp,sizeof(emp),1,fp))
	 {
		printf("| %-6d | %-20s | %-20s | %-15lld | %-5d |\n", emp.id, emp.name, emp.job_title, emp.contact, emp.age);
	}
	printf("=================================================================================\n");
	fclose(fp);
}
