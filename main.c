//my imports
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <malloc.h>
#include <sysinfoapi.h>
#include <winnt.h>
#include <tchar.h>
#define _GNU_SOURCE
#include <wchar.h>
#include <conio.h>
//
char *stockDataPath = "C:\\M.drive\\ProgramC.directory\\MarketAnalysis.repo\us-shareprices-daily.txt";
int userType,encodingType;
char *outputFile = "textout.txt";

//start function

void displayFancyMenu(char *title,int titleLength, char *options[],int optionLength,int optionCount);
void displayTextMenu(char *title, char *options[], int optionCount);
void displayFancyQuestion(char *title,int titleLength, char *question, int questionLength);
void displayTextQuestion(char *title, char *question);
void illegalOption();
void mainMenu();
void setDataPath();
void checkDataPath();
void setEncoding();
void checkOutputFile();
void setOutputFile();
void singleTickerAnalysis();

void startScreen(){
	system("cls");
	printf("Enter start type:\n");
	printf("1. User\n");
	printf("2. Admin\n:");
	int startType;
	scanf("%d",&startType);
	if(startType==1||startType==2){
		if(startType==2){
			if(strcmp(getenv("USERNAME"),"zkreu")){
				printf("FAILURE: You are not ADMIN");
				exit(0);
			}
		}
		userType=startType;
		
	}
	else{
		illegalOption();
	}
}
void charcterEncoding(){
	system("cls");
	printf("Choose display:\n");
	printf("1. Fancy Graphics (fancy tables)(WARNING: must set manually by program reset and chcp 65001)\n");
	printf("2. ASCII Encoding (default text display)\n:");
	int encodeType;
	scanf("%d",&encodeType);
	if(encodeType==1||encodeType==2){
		encodingType=encodeType;
		
	}
	else{
		printf("FAILURE: Cannot set display");
		exit(0);
	}
}

void mainMenu(){
	system("cls");
	int optionCount = 6;
	char *options[6];
	options[0] = "Check Dataset Path";
	options[1] = "Set Dataset Path";
	options[2] = "Set Encoding Type";
	options[3] = "Check Output File";
	options[4] = "Set Output File";
	options[5] = "Single Ticker Analysis";
	int optionLength = 100;
	char *title = "Stock Analysis Options";
	int titleLength = 30;

	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		checkDataPath();
	}else if(choice==2){
		setDataPath();
	}else if(choice ==3){
		setEncoding();
	}else if(choice ==4){
		checkOutputFile();
	}else if(choice==5){
		setOutputFile();
	}else if(choice==6){
		singleTickerAnalysis();
	}else{
		illegalOption();
	}

}
void displayFancyQuestion(char *title,int titleLength, char *question, int questionLength){
	system("cls");
	printf("┌─");
	for(int i =0;i<titleLength;i++){printf("─");}
	printf("─┐\n");
	printf("│ %-*s │\n",titleLength,title);
	printf("╞═");
	for(int i =0;i<titleLength;i++){printf("═");}
	printf("═╧═");
	for(int i =0;i<questionLength-titleLength+3;i++){printf("═");}
	printf("═╗\n");
	printf("│ %-*s ║\n",questionLength,question);
	printf("╞═");
	for(int i =0;i<questionLength;i++){printf("═");}
	printf("═╝\n");
	printf("└›");
}
void displayTextQuestion(char *title, char *question){
	system("cls");
	printf("%s:\n",title);
	printf("%s\n",question);
	printf(">");

}
void displayFancyMenu(char *title,int titleLength, char *options[],int optionLength,int optionCount){
	system("cls");
	printf("┌─");
	for(int i =0;i<titleLength;i++){printf("─");}
	printf("─┐\n");
	printf("│ %-*s │\n",titleLength,title);
	printf("╞════╤═");
	for(int i =0;i<titleLength-5;i++){printf("═");}
	printf("═╧");
	for(int i =0;i<optionLength-titleLength+3;i++){printf("═");}
	printf("═╗\n");
	printf("│ ## │ %-*s ║\n",optionLength,"Description");
	printf("╞════╪═");
	for(int i =0;i<optionLength;i++){printf("═");}
	printf("═╣\n");  
	printf("│ 1  │ %-*s ║\n",optionLength,options[0]);
	for(int j =1;j<optionCount;j++){if(j==optionCount) continue;
		printf("├────┼");
		for(int i =0;i<optionLength+2;i++){printf("─");}
		printf("╢\n");
		printf("│ %-2d │ %-*s ║\n",j+1,optionLength,options[j]);
	}
	printf("╘════╧═");
	for(int i =0;i<optionLength;i++){printf("═");}
	printf("═╝\n");
	printf("›");
}
void displayTextMenu(char *title, char *options[], int optionCount){
	system("cls");
	printf("%s:\n",title);
	for(int j =0;j<optionCount;j++){if(j==optionCount) continue;
		printf("%d: %s\n",j+1,options[j]);
	}
	printf(">");
}
void setDataPath(){
	system("cls");
	char *question = "Enter New Data Path";
	int questionLength = 20;
	char *title = "Set Data Path";
	int titleLength = 25;
	if(encodingType==1) displayFancyQuestion(title,titleLength,question,questionLength);
	if(encodingType==2) displayTextQuestion(title,question);
	char response[100];
	scanf("%s",response);
	strcpy(stockDataPath,response);
	mainMenu();
}
void checkDataPath(){
	system("cls");
	int optionCount = 2;
	char *options[2];
	options[0] = stockDataPath;
	options[1] = "Main Menu";
	int optionLength = 100;
	char *title = "Check Data Path";
	int titleLength = 30;
	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int choice;
	scanf("%d",&choice);
	if(choice==2){
		mainMenu();
	}else if(choice==1){
		checkDataPath();
	}else{
		illegalOption();
	}
	
}
void checkOutputFile(){
	system("cls");
	int optionCount = 2;
	char *options[2];
	options[0] = outputFile;
	options[1] = "Main Menu";
	int optionLength = 100;
	char *title = "Check Output File";
	int titleLength = 30;
	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int choice;
	scanf("%d",&choice);
	if(choice==2){
		mainMenu();
	}else if(choice==1){
		checkOutputFile();
	}else{
		illegalOption();
	}
}
void setOutputFile(){
	system("cls");
	char *question = "Enter New Output File";
	int questionLength = 20;
	char *title = "Set Output File";
	int titleLength = 25;
	if(encodingType==1) displayFancyQuestion(title,titleLength,question,questionLength);
	if(encodingType==2) displayTextQuestion(title,question);
	char response[100];
	scanf("%s",response);
	strcpy(outputFile,response);
	mainMenu();
}



void setEncoding(){
	system("cls");
	int optionCount = 3;
	char *options[3];
	options[0] = "1. Fancy Graphics (fancy tables)(WARNING: must set manually by program reset and chcp 65001)";
	options[1] = "2. ASCII Encoding (default text display)";
	options[2] = "Main Menu";
	int optionLength = 100;
	char *title = "Check Data Path";
	int titleLength = 30;
	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		encodingType=1;
		mainMenu();
	}else if(choice==2){
		encodingType=2;
		mainMenu();
	}else if(choice==3){
		mainMenu();
	}else{
		illegalOption();
	}
}


void illegalOption(){
	system("cls");
	int optionCount = 1;
	char *options[1];
	options[0] = "Main Menu";
	int optionLength = 100;
	char *title = "Failure Illegal Option";
	int titleLength = 30;
	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		mainMenu();
	}else{
		illegalOption();
	}
}
int main() {
	
	startScreen();
	
	charcterEncoding();
	
	mainMenu();
	
}
struct tickerData{
int d; //date
char t[5]; //ticker
double i; //increase
int ndc; // next day count
struct tickerData *nd; //nextdayreserved
};
struct tickerBucket{
char t[5]; //ticker
int dac; //data count
int ac; //analysis count
struct tickerData *da; //data array
struct tickerAnalysis *a; //analysis array
};

void singleTickerAnalysis(){
	
	//enter ticker
	system("cls");
	char *question = "Enter Ticker";
	int questionLength = 20;
	char *title = "Single Ticker Analysis";
	int titleLength = 25;
	if(encodingType==1) displayFancyQuestion(title,titleLength,question,questionLength);
	if(encodingType==2) displayTextQuestion(title,question);
	char myTicker[5];
	scanf("%s",myTicker);
	
	//enter myticker cutoff
	system("cls");
        question = "Enter ticker increase Cutoff";
	questionLength = 25;
	title = "Single Ticker Analysis";
	titleLength = 20;
	if(encodingType==1) displayFancyQuestion(title,titleLength,question,questionLength);
	if(encodingType==2) displayTextQuestion(title,question);
	double cutoff;
	scanf("%lf",&cutoff);

	/**type of cutoff
	system("cls");
	int optionCount = 2;
	char *options[2];
	options[0] = "Cutoff Below";
	options[1] = "Cutoff Above";
	int optionLength = 100;
	title = "Single Ticker Analysis";
	titleLength = 30;
	if(encodingType==1) displayFancyMenu(title,titleLength,options,optionLength,optionCount);
	if(encodingType==2) displayTextMenu(title,options,optionCount);
	int cutoffType;
	scanf("%d",&cutoffType);
	if(!(cutoffType==1||cutoffType==2)){
		illegalOption();
	}**/
	
	//enter myticker cutoff
	system("cls");
        question = "Enter searchedTicker increase Cutoff";
	questionLength = 25;
	title = "Single Ticker Analysis";
	titleLength = 20;
	if(encodingType==1) displayFancyQuestion(title,titleLength,question,questionLength);
	if(encodingType==2) displayTextQuestion(title,question);
	double searchCutoff;
	scanf("%lf",&searchCutoff);
	printf("%s %lf %d %lf",myTicker,cutoff,cutoffType,searchCutoff);

	
	
	FILE *fptr;
	fptr = fopen(stockDataPath,"r");

	char l[256]; 
	fgets(l,sizeof(l),fptr);//read header out

	int rc=0;//record count
	struct tickerData *r = malloc(sizeof(struct tickerData));//init records array
	
	while(fgets(l,sizeof(l),fptr)){
	
		//extract values from line
		char *myticker = strtok(l,";");
		char *myid = strtok(NULL,";");
		char *mydate = strtok(NULL,";");
		char *myopen = strtok(NULL,";");
		char *mylow = strtok(NULL,";");
		char *myhigh = strtok(NULL,";");
		char *myclose = strtok(NULL,";");
		char *myadjclose = strtok(NULL,";");
		char *mydividend = strtok(NULL,";");
		char *myvolume = strtok(NULL,";");
		char *myoutstanding = strtok(NULL,";");
		//end extracting values
		double i = 0.0;
		double o;
		double c;
		if(myadjclose&&myopen){
			o= atof(myopen);
			c= atof(myadjclose);
		}else if(myclose&&myopen){
			o= atof(myopen);
			c= atof(myclose);
		}else{
			o=1.0;
			c =1.0;
		}
		i=(double)((c/o)-1);
		if(strcmp(myticker,myTicker)==0){
			
			if(i<searchCutoff) continue;
		}else{
			if(i<cutoff) continue;
		}

		//start tm processing
		struct tm mytm;
		mytm.tm_sec =0;
		mytm.tm_min =0;
		mytm.tm_hour = 0;
		mytm.tm_wday = 0;
		mytm.tm_yday =0;
		mytm.tm_isdst =-1;

		//extract ints
		char *nptr;
		char *dateyear = strtok(mydate,"-");
		mytm.tm_year = strtol(dateyear, &nptr, 10)-1900;
		char *datemonth = strtok(NULL,"-");
		mytm.tm_mon = strtol(datemonth, &nptr, 10);		
		char *dateday = strtok(NULL,"-");
		mytm.tm_mday = strtol(dateday, &nptr, 10);

		//final time int		
		int myfulltime = mktime(&mytm);
		
		if(strcmp(myticker,myTicker)==0){
			
			if(i<searchCutoff) continue;
		}else{
			if(i<cutoff) continue;
		}


		rc++;
		struct tickerData *tmpptr = (struct tickerData *)realloc(r,rc*sizeof(struct tickerData));
		r = tmpptr;
		r[rc-1].d = myfulltime;
	
		memcpy(r[rc-1].t, myticker, strlen(myticker)+1);
	
		r[rc-1].i =i;
	
		
	}

	fclose(fptr);
	printf("RC: %d\n",rc);
	

	
}
	

