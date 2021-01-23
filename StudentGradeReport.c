//hussain Mohsin
//FInal exam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	int studentId;
	char name[20];
	char streetAddress[30];
	char city[20];
	char state[2];
	int zipCode;
};
struct Grades{
	int studentId;
	int assignmentPts;
	int quizPts;
	int testPts;
	int finalExamPts;
};
void getStudentInfoFromFile(struct Student *student);
void getGradeInfoFromFile(struct Grades *grades);
int findStudentDataByName(struct Student student[]);
void getStudentGrades(int studentIdReturned, struct Grades grades[], int *assignments, int *quizzes, int *tests, int *finalExam);
void calculateStudentsGrades(int *assignments, int *quizzes, int *tests, int *finalExam, float *assignmentsPercentage, float *quizzesPercentage, float *testsPercentage, float *finalExamPercentage, float *overallPercentage);
void printStudentGradeReport(int studentId, struct Student student[], float *assignmentsPercentage, float *quizzesPercentage, float *testsPercentage, float *finalExamPercentage, float *overallPercentage);

int main(){
	
	struct Student student[20];
	struct Grades grades[20];
	int studentIdReturned, assignments, quizzes,tests, finalExam;
	float assignmentsPercentage, quizzesPercentage, testsPercentage, finalExamPercentage, overallPercentage;
	char searchAgain;

	getStudentInfoFromFile(student);
	getGradeInfoFromFile(grades);

	do{
		studentIdReturned = findStudentDataByName(student);
		
		if (studentIdReturned!=0){
			
			getStudentGrades(studentIdReturned, grades, &assignments, &quizzes, &tests, &finalExam);
			calculateStudentsGrades( &assignments, &quizzes, &tests, &finalExam, &assignmentsPercentage, &quizzesPercentage, &testsPercentage, &finalExamPercentage, &overallPercentage);	
			printf("here");
			printStudentGradeReport(studentIdReturned, student, &assignmentsPercentage, &quizzesPercentage, &testsPercentage, &finalExamPercentage, &overallPercentage );
		}
		
		printf("Would you like to search for another student? Y/N ");
		scanf(" %c", & searchAgain);
	} while (searchAgain == 'Y' || searchAgain == 'y');
	
	printf("Thank you, Have a great Day");
}

void getStudentInfoFromFile(struct Student *student){
	FILE *studentsInFile;
	studentsInFile= fopen("students.csv","r");

	if(studentsInFile == NULL){
		printf("[ERROR] Couldn't Open FIle");
		exit(0);
	}
	
	char *studentName, *streetAddress, *city, *state; 
	int studentId,zipCode;
	
	char line [200];
	char *sp;
	while(fgets(line,200,studentsInFile) != NULL){
		
		sp=strtok(line,",");
		student->studentId = atoi(sp);
		
		sp=strtok(NULL,",");
		strcpy(student->name,sp);
		
		sp=strtok(NULL,",");
		strcpy(student->streetAddress,sp);
		
		sp=strtok(NULL,",");
		strcpy(student->city,sp);
		
		sp=strtok(NULL,",");
		strcpy(student->state,sp);
		
		sp=strtok(NULL,",");
		student->zipCode = atoi(sp);
		
		student++;
	}
	fclose(studentsInFile);
		
	
}

void getGradeInfoFromFile(struct Grades *grades){
	FILE *gradesInFile;
	gradesInFile= fopen("grades.csv","r");
	
	if(gradesInFile == NULL){
		printf("[ERROR] Couldn't Open FIle");
		exit(0);
	}
	int x, studentId, assignmentPts, quizPts, testPts, finalExamPts;
	
	x=fscanf(gradesInFile, "%d,%d,%d,%d,%d", &studentId, &assignmentPts, &quizPts, &testPts, &finalExamPts);
	
	while(x != EOF){
		grades->studentId = studentId;
		grades->assignmentPts = assignmentPts;
		grades->quizPts = quizPts;
		grades->testPts = testPts;
		grades->finalExamPts = finalExamPts;
		
		x=fscanf(gradesInFile, "%d,%d,%d,%d,%d", &studentId, &assignmentPts, &quizPts, &testPts, &finalExamPts);
	
		grades++;
	}
	fclose(gradesInFile);
}

int findStudentDataByName(struct Student student[]){
	char fullName[20];
	int x;
	int found = -1;
	
	printf("Enter the student's full name: ");
	gets(fullName);
	
	for(x=0; x<20; x++){
		if (strcmp(fullName, student[x].name) == 0){
			found=1;
			break;
		}
	}
	
	if (found == 1){
		return student[x].studentId;
		
	}else{
		printf("\nStudent does not exist!");
		return 0;	
	}
}

void getStudentGrades(int studentIdReturned, struct Grades grades[], int *assignments, int *quizzes, int *tests, int *finalExam){
	int x;
	for(x=0; x<20; x++){
		if(studentIdReturned == grades[x].studentId){
			
			*assignments= grades[x].assignmentPts;
			*quizzes= grades[x].quizPts;
			*tests= grades[x].testPts;
			*finalExam= grades[x].finalExamPts;
			break;
		}
	}
}

void calculateStudentsGrades(int *assignments, int *quizzes, int *tests, int *finalExam, float *assignmentsPercentage, float *quizzesPercentage, float *testsPercentage, float *finalExamPercentage, float *overallPercentage){
	int assignmentsMax= 400, quizzesMax=100, testsMax=200, finalExamMax=100;
	int assignmentsWorth = 30, quizzesWorth = 10, testWorth = 40, finalExamWorth = 20;
	
	*assignmentsPercentage= (*assignments/assignmentsMax) * assignmentsWorth; 
	*quizzesPercentage= (*quizzes/quizzesMax) * quizzesWorth;
	*testsPercentage= (*tests/testsMax) * testWorth;
	*finalExamPercentage= (*finalExam/finalExamMax) * finalExamWorth;
	*overallPercentage = *assignmentsPercentage + *quizzesPercentage + *testsPercentage + *finalExamPercentage;
}

void printStudentGradeReport(int studentId, struct Student student[], float *assignmentsPercentage, float *quizzesPercentage, float *testsPercentage, float *finalExamPercentage, float *overallPercentage){
	int x;
	char outputChoice;
	
	for(x=0; x<20; x++){
		if(studentId == student[x].studentId)
		break;
	}
	
	do{	
		printf("Do you wish to print to a file? Y/N ");
		scanf(" %c", &outputChoice);
		
	} while(outputChoice != 'N' && outputChoice != 'n' && outputChoice != 'Y' && outputChoice != 'y' );
	
	if(outputChoice == 'N' || outputChoice == 'n'){
		printf("\nStudent Number: %d", student[x].studentId);
		printf("\n%d",student[x].streetAddress);
		printf("\n%s", student[x].name);
		printf("\n%s, %s %d",student[x].city, student[x].state, student[x].zipCode);
		
		printf("\n\nAssignments	: %.2f %", *assignmentsPercentage);
		printf("\nQuizzes	: %.2f %",quizzesPercentage );
		printf("\nTests	: %.2f %", *testsPercentage);
		printf("\nFinal Exam	: %.2f %", *finalExamPercentage);	
		
		printf("\n\nOverall Grade	: %.2f %", *overallPercentage);
		
	}else if(outputChoice == 'Y' || outputChoice == 'y'){
		
		char fileName[50];
		FILE *outputFile;
		int x;
		
		getchar();
		printf("\nEnter a file name you would like to save too: ");
		gets(fileName);
		strcat(fileName, ".txt");
		
	
		outputFile=fopen(fileName, "w");
		if(outputFile==NULL){
			printf("[ERROR] Can't Write to File");
			exit(0);
		} 

		fprintf(outputFile, "\nStudent Number: %d", student[x].studentId);
		fprintf(outputFile,"\n%d",student[x].streetAddress);
		fprintf(outputFile,"\n%s", student[x].name);
		fprintf(outputFile,"\n%s, %s %d",student[x].city, student[x].state, student[x].zipCode);
		
		fprintf(outputFile,"\n\nAssignments	: %.2f %", *assignmentsPercentage);
		fprintf(outputFile,"\nQuizzes	: %.2f %",quizzesPercentage );
		fprintf(outputFile,"\nTests	: %.2f %", *testsPercentage);
		fprintf(outputFile,"\nFinal Exam	: %.2f %", *finalExamPercentage);	
		
		fprintf(outputFile,"\n\nOverall Grade	: %.2f %", *overallPercentage);
		
		printf("\n\n%s Successfully Created!", fileName);
		
		fclose(outputFile);
			
	}
}
