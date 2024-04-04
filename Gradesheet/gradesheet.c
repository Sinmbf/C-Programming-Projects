#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

/* *********Structures*********** */
struct subject {
	char subjectName[20];
	int marks;
} subject;

 struct marks{
	int totalMarks;
	float percentage;
};

typedef struct student {
	int registrationNum;
	char name[20];
	char faculty[20];
	int semester;
	struct subject subj[5];
	struct marks mrk;
} student;

/* *********Function Prototypes************ */
void home();
void confirmationDialogue(int,int,char *,char *);
void getStudentInfo(struct student *std);
char* calculateGrade(int marks);
void saveToFile(struct student *std);
void generateGradesheet(struct student *std);

/* *********Utility Functions Prototypes********* */
void gotoxy(int,int);
void printHorizontalLine(int,int,int);
void printVerticalLine(int,int,int);
void printRows(int,char *,int [],float);

/* *********Main Program********* */
int main() {
	char ch;
	int x=31,y=15;
	do {
		system("cls");
		home();
		confirmationDialogue(x,30,"Do you want to perform another operation?[y/n]: ",&ch);
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
void home() {
	system("Color 07");
	struct student std;
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
			generateGradesheet(&std);
			break;
		default:
			gotoxy(30,5);
			printf("Invalid choice");
	}

}

// Function to ask whether to continue program
void confirmationDialogue(int x,int y,char *dialogue,char *ch) {
	gotoxy(x,y);
	printf("%s",dialogue);
	scanf(" %c",ch);
}

// Function to get student information
void getStudentInfo(struct student *std) {
	int i,x=30,y=5;
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
	getchar(); // consume the new line character
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
char* calculateGrade(int marks){
	if(marks>=90 && marks<=100){
		return "A+";
	}
	else if(marks>=80){
		return "A";
	}
	else if(marks>=70){
		return "B+";
	}
	else if(marks>=60){
		return "B";
	}
	else if(marks>=50){
		return "C";
	}
	else{
		return "NG";
	}
}

// Function to save data to file
void saveToFile(student *std) {
	student std1;
	FILE *fptr;
	int i;
	fptr=fopen("student.txt","wb");
	if(fptr==NULL) {
		system("cls");
		printf("Error opening student.txt");
	}
	if(fwrite(std,sizeof(student),1,fptr)) {
		printf("Successfully written to file");
	} else {
		printf("Error writing into file");
	}
	fclose(fptr);
}

// Function to generateGradesheet
void generateGradesheet(struct student *std) {
	int i;
	int x=40,y=5;
	system("cls");
	gotoxy(x,y);
	printf("National College Of Computer Studies");
	x+=8;
	gotoxy(x,++y);
	printf("Paknajol, Kathmandu");
	x-=18;
	y+=2;
	printHorizontalLine(30,8,56);
	printVerticalLine(30,8,19);
	x+=3;
	gotoxy(x,++y);
	printf("Name: %s",std->name);
	gotoxy(x,++y);
	printf("NCCS Reg. No: %d",std->registrationNum);
	gotoxy(x,++y);
	printf("Faculty: %s",std->faculty);
	gotoxy(x,++y);
	printf("Semester: %d",std->semester);
	printHorizontalLine(31,++y,55);
	printVerticalLine(85,8,19);
	gotoxy(34,++y);
	printf("Subject Name");
	gotoxy(51,y);
	printf("Marks Obtained");
	gotoxy(69,y);
	printf("Grade Obtained");
	printHorizontalLine(31,++y,54);
	printVerticalLine(49,13,14);
	printVerticalLine(66,13,14);
	for(i=0; i<5; i++) {
		// Subject Name
		gotoxy(34,++y);
		printf("%s",std->subj[i].subjectName);
		// Marks obtained
		gotoxy(57,y);
		printf("%d",std->subj[i].marks);
		gotoxy(75,y);
		// Grade obtained
		printf("%s",calculateGrade(std->subj[i].marks));
		printHorizontalLine(31,++y,54);
	}
	printHorizontalLine(31,++y,54);
	// Percentage
	gotoxy(34,++y);
	printf("Percentage");
	gotoxy(73,y);
	printf("%.2f%%",std->mrk.percentage);
	printHorizontalLine(30,++y,56);
//	saveToFile(&std);
}

// Function to show gradesheet
void showGradesheet(struct student std) {
	int x=30,y=5;
	gotoxy(x,y);
	printf("National College Of Computer Studies");
	x+=8;
	gotoxy(48,++y);
	printf("Paknajol, Kathmandu");
	x-=18;
	y+=2;
	gotoxy(x,y);
	printf("Name: ");
}
