/* ********************************GRADESHEET MANAGEMENT SYSTEM***************************** */

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

/* *********Structures*********** */

// *********Sub Structures******** //
struct subject {
	char subjectName[20];
	int marks;
} subject;

struct marks {
	int totalMarks;
	float percentage;
};

// ************MAIN STRUCTURE*************** //
typedef struct student {
	int registrationNum;
	char name[20];
	char faculty[20];
	int semester;
	struct subject subj[5];
	struct marks mrk;
} student;

/* *********Function Prototypes************ */
int home();
void confirmationDialogue(int,int,char *,char *);
void getStudentInfo(struct student *std);
char* calculateGrade(int marks);
void saveToFile(struct student *std);
void readFromFile();
int generateGradesheet(int,int,struct student *std);
int showGradesheet();
int searchGradesheet();
int deleteGradesheet();

/* *********Utility Functions Prototypes********* */
void gotoxy(int,int);
void printHorizontalLine(int,int,int);
void printVerticalLine(int,int,int);
void printRows(int,char *,int [],float);

/* *********Main Program********* */
int main() {
	char ch;
	int x=30,y=15;
	do {
		system("cls");
		y=home();
		y+=1;
		confirmationDialogue(x,++y,"Do you want to perform another operation?[y/n]: ",&ch);
	} while(ch=='y' || ch=='Y');
	return 0;
}

/* ********Function Definitions*********** */

// Function to move cursor to specified position
void gotoxy(int x,int y) {
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to print horizontal line
void printHorizontalLine(int x,int y,int width) {
	int i;
	for(i=0; i<width; i++) {
		gotoxy(x++,y);
		printf("-");
	}
}

// Function to print vertical line
void printVerticalLine(int x,int y,int height) {
	int i;
	for(i=0; i<height; i++) {
		gotoxy(x,++y);
		printf("|");
	}
}

// Function to display starting point of program
int home() {
	system("Color 07");
	struct student std;
	char ch;
	int x=30,y=5;
	int choice;
	int width=46;
	printHorizontalLine(30,5,width);
	gotoxy(x,++y);
	printf("|********Gradesheet Management System********|");
	printHorizontalLine(30,7,width);
	y+=2;
	gotoxy(x,y);
	printf("1. Generate Gradesheet");
	gotoxy(x,++y);
	printf("2. Show all gradesheet");
	gotoxy(x,++y);
	printf("3. Search gradesheet");
	gotoxy(x,++y);
	printf("4. Delete gradesheet");
	gotoxy(x,++y);
	printf("5. Exit program");
	printHorizontalLine(30,++y,width);
	y+=2;
	gotoxy(x,y);
	printf("Which operation do you want to perform?[1-5]: ");
	scanf("%d",&choice);
	fflush(stdin);
	system("cls");
	switch(choice) {
		case 1:
			system("Color 02");
			getStudentInfo(&std);
			system("cls");
			y=generateGradesheet(40,5,&std);
			y+=1;
			confirmationDialogue(30,++y,"Do you want to save the gradesheet?[y/n]: ",&ch);
			if(ch=='y' || ch=='Y') {
				gotoxy(30,++y);
				saveToFile(&std);
			}
			break;
		case 2:
			system("cls");
			system("Color 07");
			y=showGradesheet();
			break;
		case 3:
			system("cls");
			system("Color 03");
			y=searchGradesheet();
			break;
		case 4:
			system("cls");
			system("Color 04");
			y=deleteGradesheet();
			break;
		case 5:
			exit(0);
		default:
			gotoxy(30,5);
			printf("Invalid choice");
	}
	return y;
}

// Function to ask whether to continue program
void confirmationDialogue(int x,int y,char *dialogue,char *ch) {
	gotoxy(x,y);
	printf("%s",dialogue);
	scanf(" %c",ch);
}

// Function to get student information
void getStudentInfo(struct student *std) {
	struct student std1;
	FILE *fptr;
	int i,x=30,y=5;
	fptr=fopen("student.txt","ab+");
	if(fptr==NULL) {
		printf("Error opening student.txt");
		exit(1);
	}
	std->mrk.totalMarks=0;
	gotoxy(x,y);
	printf("Enter student details:");
	y+=2;
	gotoxy(x,y);
	printf("Name: ");
	fgets(std->name,sizeof(std->name),stdin);
	gotoxy(x,++y);
	printf("NCCS reg. num: ");
	scanf("%d",&std->registrationNum);
	while(fread(&std1,sizeof(std1),1,fptr)) {
		while(std->registrationNum==std1.registrationNum) {
			y+=1;
			gotoxy(x,++y);
			printf("Record of student already exists!!");
			gotoxy(x,++y);
			printf("Enter NCCS reg. num again: ");
			scanf("%d",&std->registrationNum);
			// Reset file pointer to check reg No from the beginning
			rewind(fptr);
		}
	}
	fclose(fptr);
	getchar(); // consume the new line character
	y+=1;
	gotoxy(x,++y);
	printf("Faculty: ");
	fgets(std->faculty,sizeof(std->faculty),stdin);
	gotoxy(x,++y);
	printf("Semester(In number): ");
	scanf("%d",&std->semester);
	getchar(); // Consume the new line character
	// Input marks
	for(i=0; i<5; i++) {
		y+=2;
		gotoxy(x,y);
		printf("Enter subject name: ");
		fgets(std->subj[i].subjectName,sizeof(std->subj[i].subjectName),stdin);
		gotoxy(x,++y);
		printf("Enter marks: ");
		scanf("%d",&std->subj[i].marks);
		getchar(); // consume new line character
		std->mrk.totalMarks+=std->subj[i].marks;
	}
	std->mrk.percentage=(float)std->mrk.totalMarks/500*100;
}

// Function to calculate grade
char* calculateGrade(int marks) {
	if(marks>=90 && marks<=100) {
		return "A+";
	} else if(marks>=80) {
		return "A";
	} else if(marks>=70) {
		return "B+";
	} else if(marks>=60) {
		return "B";
	} else if(marks>=50) {
		return "C";
	} else {
		return "NG";
	}
}

// Function to save data to file
void saveToFile(student *std) {
	FILE *fptr;
	int i;
	fptr=fopen("student.txt","ab");
	if(fptr==NULL) {
		system("cls");
		printf("Error opening student.txt");
	}
	if(fwrite(std,sizeof(student),1,fptr)) {
		printf("Successfully saved to file");
	} else {
		printf("Error writing into file");
	}
	fclose(fptr);
}

// Function to generateGradesheet
int generateGradesheet(int x,int y,struct student *std) {
	char ch;
	int i;
	gotoxy(x,y);
	printf("National College Of Computer Studies");
	x+=8;
	gotoxy(x,++y);
	printf("Paknajol, Kathmandu");
	x-=18;
	y+=2;
	printHorizontalLine(x,y,56);
	printVerticalLine(x,y,19);
	x+=3;
	gotoxy(x,++y);
	printf("Name: %s",std->name);
	gotoxy(x,++y);
	printf("NCCS Reg. No: %d",std->registrationNum);
	gotoxy(x,++y);
	printf("Faculty: %s",std->faculty);
	gotoxy(x,++y);
	printf("Semester: %d",std->semester);
	printHorizontalLine(x-2,++y,55);
	printVerticalLine(x+52,y-5,19);
	gotoxy(x+1,++y);
	printf("Subject Name");
	gotoxy(x+18,y);
	printf("Marks Obtained");
	gotoxy(x+36,y);
	printf("Grade Obtained");
	printHorizontalLine(x-2,++y,54);
	printVerticalLine(x+16,y-2,14);
	printVerticalLine(x+33,y-2,14);
	for(i=0; i<5; i++) {
		// Subject Name
		gotoxy(x+1,++y);
		printf("%s",std->subj[i].subjectName);
		// Marks obtained
		gotoxy(x+24,y);
		printf("%d",std->subj[i].marks);
		gotoxy(x+42,y);
		// Grade obtained
		printf("%s",calculateGrade(std->subj[i].marks));
		printHorizontalLine(x-2,++y,54);
	}
	printHorizontalLine(x-2,++y,54);
	// Percentage
	gotoxy(x+1,++y);
	printf("Percentage");
	gotoxy(x+40,y);
	printf("%.2f%%",std->mrk.percentage);
	printHorizontalLine(x-3,++y,56);
	return y;
}

// Function to show gradesheet
int showGradesheet() {
	FILE *fptr;
	int x=40,y=5,flag;
	struct student std;
	fptr=fopen("student.txt","rb");
	if(fptr==NULL) {
		printf("Error opening student.txt");
		exit(1);
	}
	flag=fread(&std,sizeof(std),1,fptr);
	if(flag<1) {
		gotoxy(30,y);
		printf("No gradesheet found!!!");
		return y;
	} else {
		generateGradesheet(x,y,&std);
		printHorizontalLine(0,y+25,120);
		y+=26;
		while(fread(&std,sizeof(std),1,fptr)) {
			generateGradesheet(x,y,&std);
			printHorizontalLine(0,y+25,120);
			y+=26;
		}
	}
	fclose(fptr);
	return y;
}

// Function to search gradesheet by registration No
int searchGradesheet() {
	FILE *fptr;
	struct student std;
	int regNo;
	int x=40,y=5,flag=0;
	gotoxy(x-10,y);
	printf("Enter NCCS registration number of the student: ");
	scanf("%d",&regNo);
	y+=2;
	fptr=fopen("student.txt","rb");
	if(fptr==NULL) {
		printf("Error opening student.txt");
		exit(1);
	}
	while(fread(&std,sizeof(std),1,fptr)) {
		if(std.registrationNum==regNo) {
			y=generateGradesheet(x,++y,&std);
			flag=1;
			break;
		}
	}
	gotoxy(x,++y);
	if(flag==0) {
		printf("Record not found!!");
	}
	fclose(fptr);
	return y;
}

// Function to delete gradesheet by registration No
int deleteGradesheet() {
	FILE *fptr1,*fptr2;
	struct student std;
	int regNo,err=0,flag=0;
	int x=40,y=5;
	gotoxy(x-10,y);
	printf("Enter NCCS registration number of the student: ");
	scanf("%d",&regNo);
	y+=1;
	fptr1=fopen("student.txt","rb");
	fptr2=fopen("temp.txt","wb");
	if(fptr1==NULL) {
		printf("Error opening student.txt");
		exit(1);
	}
	if(fptr2==NULL) {
		printf("Error opening student.txt");
		exit(1);
	}
	while(fread(&std,sizeof(std),1,fptr1)) {
		if(std.registrationNum!=regNo) {
			fwrite(&std,sizeof(std),1,fptr2);
		} else {
			flag=1;
		}
	}
	if(flag==0) {
		gotoxy(x,++y);
		printf("Gradesheet not found!!!!");
		fclose(fptr1);
		fclose(fptr2);
		return y;
	}
	fclose(fptr1);
	fclose(fptr2);
	err=remove("student.txt");
	gotoxy(x-5,++y);
	if(err!=0) {
		printf("Error deleting student.txt");
		return y;
	}
	err=rename("temp.txt","student.txt");
	if(err!=0) {
		printf("Error deleting record");
		return y;
	} else {
		printf("Successfully deleted record");
	}
	return y;
}
