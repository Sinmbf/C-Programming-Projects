#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
void admission();
void stuinfo();
void search();
void sort();
void del_rec();
void head();
void displayDetail(char regis[], char name[],int clas, char address[],char contact[]);
struct student {
	char name[100];
	int clas;
	char address[60];
	char contact[20];
	char regist[20];
};

void main() {
	char ans;
	int n;
//do{
	system("cls");
	system("color 70");
	printf("\n\n\n");
	printf("\t       **** WELCOME TO THE SCHOOL MANAGEMENT SYSTEM *****");
	printf("\n\n");
	printf("\n\t\t -------- Please choose your operation: --------");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      1.Student Admission\t\t|");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      2.Student Informations\t\t|");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      3.Search Student \t\t\t|");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      4.Sort\t\t\t\t|");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      5.Delete\t\t\t\t|");
	printf("\n\t\t|\t\t\t\t\t\t|\n\t\t|\t      6.Exit\t\t\t\t|");
	printf("\n");
	printf("\t\t -----------------------------------------------");
	printf("\n\n\t\tEnter yout choice:");
	scanf("%d",&n);
	fflush(stdin);
	switch(n) {
		case 1:
			admission();
			break;
		case 2:
			stuinfo();
			break;
		case 3:
			search();
			break;
		case 4:
			sort();
			break;
		case 5:
			del_rec();
			break;
		case 6:
			printf("\n");
			printf("\t\tOperation ended\n\n \t\tPress any key to exit");
			exit(0);
		default:
			printf("\n\n\t\t\tInvalid input Please select the given choice");
			getch();
			main();
	}
}

void admission() {
	FILE *fp;
	struct student info,check;
	char ans;
	system("cls");
	printf("\n");
	printf("\t \t\t****** STUDENT ADMISSION *****");
	do {
		printf("\n");
		printf("\n");
		fflush(stdin);
		printf("\t-----------------------------");
		printf("\n\tName: ");
		gets(info.name);
		fflush(stdin);
		printf("\n\tClass: ");
		scanf("%d",&info.clas);
		fflush(stdin);
		printf("\n\tContact: ");
		gets(info.contact);
		printf("\n\tAddress: ");
		gets(info.address);
		fflush(stdin);
		printf("\n\tRegistration No: NCCSHSS");
		gets(info.regist);
		fp=fopen("student.txt","r");
		while(fread(&check,sizeof(struct student),1,fp)) {
			while(strcmp(info.regist,check.regist)==0) {
				printf("\n\tRegistration No already exist: ");
				printf("\n\tPlease enter another registration no: NCCSHSS");
				gets(info.regist);
			}
		}
		fclose(fp);
		printf("\t-----------------------------");
		fp=fopen("student.txt","a+");
		fwrite(&info,sizeof(struct student),1,fp);
		if(fwrite!=0) {
			printf("\n\n\tSuccessfully saved!");
		} else {
			printf("\n\tError saving the file!");
		}
		fclose(fp);
		printf("\n\tDo you want to continue admission process(y/n): ");
		scanf("%c",&ans);

	} while(ans=='y'|| ans=='Y');
	main();
}
void stuinfo() {
	system("cls");
	struct student infor;
	FILE *fp;
	printf("\n");
	printf("\t \t\t****** STUDENT INFORMATION *****");
	printf("\n");
	fp=fopen("student.txt","r");
	if(fread(&infor,sizeof(infor),1,fp)) {
		rewind(fp);
		head();
		while(fread(&infor,sizeof(struct student),1,fp)) {
			displayDetail(infor.regist,infor.name,infor.clas,infor.address,infor.contact);
		}
	} else {
		printf("\n\t\t\t\t No available records: \n");
	}
	fclose(fp);
	printf("\n\t\t\tPress any key to return back to main menu");
	getch();
	main();
}
void search() {
	system("cls");
	int n,check=0;
	char num[20],name[50];
	struct student infor;
	FILE *fp;
	printf("\n");
	printf("\t \t\t****** SEARCH STUDENT *****");
	printf("\n");
	printf("\n\t\t 1.Search based on name");
	printf("\n\n\t\t 2.Search based on registration no.");
	printf("\n\n\t\t 3.Main Menu");
	printf("\n\n\t\t Enter your choice: ");
	scanf("%d",&n);
	switch(n) {
		case 1:
			system("cls");
			printf("\n\n\t \t\t **** NAME SEARCH *****");
			fflush(stdin);
			printf("\n\n \n\t\t\t  Enter Students Name: ");
			gets(name);
			fp=fopen("student.txt","r");
			while(fread(&infor,sizeof(struct student),1,fp)) {
				if(strcmp(name,infor.name)==0) {
					check=1;
					printf("\n");
					printf("\n\t\t\tDetails of Students '%s': ",name);
					printf("\n");
					head();
					break;
				}
			}
			fclose(fp);
			fp=fopen("student.txt","r");
			while(fread(&infor,sizeof(struct student),1,fp)) {
				if(strcmp(name,infor.name)==0) {
					displayDetail(infor.regist,infor.name,infor.clas,infor.address,infor.contact);
				}
			}
			fclose(fp);
			if(check==0) {
				printf(" \n\n\t\t\tNo name found ??");
			}
			printf("\n\n\t\t\tPress any key to return to search menu ");
			getch();
			search();




		case 2:
			system("cls");
			printf("\n\n\t\t\t     **** REGISTRATION NO SEARCH *****");
			fflush(stdin);
			printf("\n\n \n\t\t\tEnter Student's Registration no: NCCSHSS");
			gets(num);
			fp=fopen("student.txt","r");
			while(fread(&infor,sizeof(struct student),1,fp)) {
				if(strcmp(num,infor.regist)==0) {
					check=1;
					printf("\n");
					printf("\n\t\t\t  Details of Registered no 'NCCSHSS%s': ",num);
					printf("\n");
					head();
					break;
				}
			}
			fclose(fp);
			fp=fopen("student.txt","r");
			while(fread(&infor,sizeof(struct student),1,fp)) {

				if(strcmp(num,infor.regist)==0) {
					displayDetail(infor.regist,infor.name,infor.clas,infor.address,infor.contact);
				}
			}
			if(check==0) {
				printf(" \n\n\t\t\tRegistration no not found ??");
			}
			fclose(fp);
			printf("\n\n\t\t\tPress any key to return to search menu ");
			getch();
			search();
		case 3:
			main();
		default:
			fflush(stdin);
			printf("\n\n\t\t\tInvalid input Please select the given choice");
			getch();
			search();
	}
}
void sort() {
	system("cls");

	int c=0,i,ans,j;
	struct student infor,copy[100],t;
	FILE *fp;
	printf("\n");
	printf("\t \t\t****** SORT STUDENT RECORD *****");
	printf("\n");
	fflush(stdin);
	printf("\n\n\t\t 1. Ascending order");
	printf("\n\n\t\t 2. Descending order");
	printf("\n\n\t\t 3. Main menu ");
	printf("\n\n\t\t Enter your choice: ");
	scanf("%d",&ans);
	switch(ans) {
		case 1:
			system("cls");
			printf("\n");
			printf("\t \t  **** STUDENT RECORD IN ASCENDING ORDER *****");
			fp=fopen("student.txt","r");
			if(fread(&infor,sizeof(infor),1,fp)) {
				rewind(fp);
				head();

				while(fread(&infor,sizeof(struct student),1,fp)) {
					copy[c]=infor;
					c=c+1;
				}
				for(i=0; i<c; i++) {
					for(j=i+1; j<c; j++) {
						if(strcmp(copy[i].name,copy[j].name)>0) {
							t=copy[i];
							copy[i]=copy[j];
							copy[j]=t;
						}
					}
				}
				for(i=0; i<c; i++) {
					displayDetail(copy[i].regist,copy[i].name,copy[i].clas,copy[i].address,copy[i].contact);
				}
			} else {
				printf("\n\n\t\t\t No available records: ");
			}
			fclose(fp);
			printf("\n\n\t\tPress any key to return to sort menu ");
			getch();
			sort();

		case 2:
			system("cls");
			printf("\n");
			printf("\t \t  **** STUDENT RECORD IN DESCENDING ORDER *****");
			fp=fopen("student.txt","r");
			if(fread(&infor,sizeof(infor),1,fp)) {
				rewind(fp);
				head();
				while(fread(&infor,sizeof(struct student),1,fp)) {
					copy[c]=infor;
					c=c+1;
				}

				for(i=0; i<c; i++) {
					for(j=i+1; j<c; j++) {
						if(strcmp(copy[i].name,copy[j].name)<0) {
							t=copy[i];
							copy[i]=copy[j];
							copy[j]=t;
						}
					}
				}
				for(i=0; i<c; i++) {
					displayDetail(copy[i].regist,copy[i].name,copy[i].clas,copy[i].address,copy[i].contact);
				}
			}

			else {
				printf("\n\n\t\t\t No available records: ");
			}
			fclose(fp);
			printf("\n\n\t\tPress any key to return to sort menu ");
			getch();
			sort();
		case 3:
			main();
		default:
			printf("\n\n\t\t\tInvalid input Please select the given choice");
			getch();
			sort();
	}

}
void head() {
	printf("\n  ----------------------------------------------------------------------------");
//	printf("\n  |  Registration No \t Name              Class     Address     Contact  |");
	printf("\n | %-26s %-10s %8s %11s %13s","Registration NO   | ","Name         |","Class |","Address  |","contact  |");
	printf("\n |----------------------------------------------------------------------------|");
}
void displayDetail(char regis[], char name[],int clas, char address[],char contact[]) {
	printf("\n |  NCCSHSS%-10s| %-19s | %4d   | %-10s| %-12s|",regis,name,clas,address,contact);
	printf("\n %s %19s %21s %8s %11s %13s","|","|","|","|","|","|");
	printf("\n |----------------------------------------------------------------------------|");
}
void del_rec() {

	FILE *fp,*fp1;
	char no[10];
	int count=0;
	struct student s,infor;
	fp=fopen("student.txt","r");
	fp1=fopen("copy.txt","w+");
	if(fread(&infor,sizeof(infor),1,fp)) {
		do {
			system("cls");
			count=0;
			printf("\t \t\t****** DELETE STUDENT RECORD *****");
			rewind(fp);
			printf("\n\n\t\t\t  ");
			printf("The available records: \n");
			head();
			while(fread(&infor,sizeof(infor),1,fp)) {
				displayDetail(infor.regist,infor.name,infor.clas,infor.address,infor.contact);
			}
			printf("\n\n\tEnter the registration no of the student you want to delete: NCCSHSS");
			gets(no);
			rewind(fp);
			while(fread(&s,sizeof(s),1,fp)) {
				if(strcmp(no,s.regist)==0) {
					count++;
					break;
				}
			}
			if(count==0) {
				printf("\n\t\t\t Please enter a valid registration no: ");
				getch();
			}
		} while(count==0);

		rewind(fp);
		while(fread(&s,sizeof(s),1,fp)) {
			if(strcmp(no,s.regist)!=0) {
				fwrite(&s,sizeof(s),1,fp1);
			}
		}
		fclose(fp);
		fclose(fp1);
		if(remove("student.txt")==0) {
			printf("\n\t\t\t\t Successfully Deleted!");
			getch();
			system("cls");
			rename("copy.txt","student.txt");
			fp=fopen("student.txt","r");
			printf("\n\t\t\t *** THE RECORDS AFTER DELETION : ******\n");
			if(fread(&infor,sizeof(infor),1,fp)) {
				rewind(fp);
				head();
				while(fread(&infor,sizeof(infor),1,fp)) {
					displayDetail(infor.regist,infor.name,infor.clas,infor.address,infor.contact);
				}
			} else {
				printf("\n\n\t\t\t No available records: ");
			}
			fclose(fp);
			printf("\n\n\t\t Press any key to return to the main menu: ");
			getch();
			main();

		} else {
			printf("\n\n\t\t\tError deleting the record!");
			main();
		}
	}

	else {
		system("cls");
		printf("\t \t\t****** DELETE STUDENT RECORD *****");
		printf("\n\n\t\t\t No available records: ");
		printf("\n\n\t\t Press any key to return to the main menu: ");
		getch();
		main();
	}
}
