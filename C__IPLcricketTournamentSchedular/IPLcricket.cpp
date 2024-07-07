#include<stdio.h>
#include<conio.h> 
#include<stdlib.h>
#include<string.h>
#include "shape.h"

void menu();
void add();
void view();
void Schedule();
void modify();
void replaceAll(char *str, const char *oldWord, const char *newWord);
void deleterec();

struct student
{
    char name[30];
};


size_t len()
{
    struct student std;
    FILE* len = fopen("record.txt","r");
    size_t count = 0;
    while(fscanf(len, "%s", std.name)!=EOF){
        count++;
    }
    fclose(len);
    return count;
}


int main()
{
    
	welcome();
    menu();
    return 0;  
}
void menu()
{
	system("cls");
    int choice; 
    main_menu();
    printf("\tEnter your choice. ::>> ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
    	system("cls");
        add();
        break;
    case 2:
    	system("cls");
        view();
        break;
    case 3:
    	system("cls");
        Schedule();
        break;
    case 4:
		system("cls");	
        modify();
        break;
    case 5:
    	system("cls");
        deleterec();
        getch();
        menu();
        break;
    case 6:
    	system("cls");
        ex();
        break;

    default:
        printf("Invalid Choice.\n");
        printf("Enter your choice between 1-6 only.");
        getch();
        menu();
    }
}
void add()
{
	system("cls");
    FILE *fp;
    struct student std;
    fp = fopen("record.txt","a");
    char another ='y';
    
    if(fp == NULL){
        er_op_file();
    }
    else
    {
	    while (another=='y')
	    {
	    	system("cls");
	       add_team();
	       printf("\n\n\t\tEnter teams Name : ");
	       fflush(stdin);
	       scanf("%s",std.name);
	       
	       fprintf(fp,std.name);
	       
	       fprintf(fp, "\n");
	       printf("\n\n\n\n\n");
	       printf("\t\tWant to add of another record? Then press 'y' else 'n' ::>> ");
	       fflush(stdin);
	       another = getch();
	       
	       fflush(stdin);
	    }
	    fclose(fp);
	}
    printf("\n\n Press any key to return to main menu.....");
    getch();
    menu();
}

void view()
{
    FILE *fp;
    int i=1,j;
    struct student std;
    
    fp = fopen("record.txt","r+");
    if(fp == NULL){
       er_op_file();
    }
    else
    {
	    v_rec();
	    printf("\n\n");
	    printf("\t\t\t\t\t--------------------------------------------------------------------\n");
	    printf("\t\t\t\t\t|            S.No              |              Name of teamss        |\n");
	    printf("\t\t\t\t\t--------------------------------------------------------------------\n");
	    j=8;
	     while(fscanf(fp, "%s", std.name)!=EOF)
	   {
	   		printf("\t\t\t\t\t|              %d               |                 %s               |\n",i,std.name );
	   		printf("\t\t\t\t\t--------------------------------------------------------------------\n");
	        j++;											
	        i++;
	   }
	    fclose(fp);
	}
    printf("\n\n\n\n\n");
    printf("Press any key to return to main menu.....");
    getch();
    menu();
}

void Schedule ()
{
	int i,j;
    FILE *fp;
    struct student std;
    fp = fopen("record.txt","r");
    
    if(fp == NULL){
        er_op_file();
    }
    
    else
    {
	    char* a[30];
	    int ia = 0;
	
	    while(fscanf(fp, "%s", std.name)!=EOF){
	        int len = strlen(std.name);
	        a[ia] = (char*)malloc(sizeof(char)*len);
	        strcpy(a[ia],std.name);
	        ia++;
	    }
	    fclose(fp);
	    view_schedule();
	    int count = 1;
	    int date=2;
	    printf("\n\t\t\t\t\t\t--------------------------------------------------------------------\n");
	    printf("\t\t\t\t\t\t|              |                 |                                 |\n");
	    printf("\t\t\t\t\t\t|  Match no    |       Date      |       Team   Vs  Team           |\n");
	    printf("\t\t\t\t\t\t|              |                 |                                 |\n");
	    for(i = 0; i < len(); i++) 
		{
	        for (j = i + 1; j < len(); j++) {
	        	printf("\t\t\t\t\t\t--------------------------------------------------------------------\n");
	            printf("\t\t\t\t\t\t| Match    %d   |    2023-06-%d    |        %s    vs   %s          |\n", count,date, a[i], a[j]);
	            count++;
	            date+=2;
	        }
	    }
	    printf("\t\t\t\t\t\t--------------------------------------------------------------------\n");
	}
    printf("\n\n\nPress any key to return to main menu.....");
    getch();
    menu();

}
void modify()
{
    FILE * fPtr;
    FILE * fTemp;
    char *path = "record.txt";
    char buffer[1000];
    char oldWord[100], newWord[100];
    
    modify_record();
    
    printf("\n\n\t\t\t\tEnter team Name to replace: ");
    scanf("%s", &oldWord);
    printf("\n\n\n\t\t\t\tReplace '%s' with: ",oldWord);
    scanf("%s", newWord);
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 
    if (fPtr == NULL || fTemp == NULL)
    {  
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    while ((fgets(buffer, 1000, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove(path);
    rename("replace.tmp", path);
    printf("\n\n\n\t\t\t\tSuccessfully replaced teams Name of %s with %s", oldWord, newWord);
    printf("\n\n\n\n\n\n\n\t\t\tpress enter to retrn to main menu .... ");
    getch();
    menu();
}
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;
    owlen = strlen(oldWord);
    if (!strcmp(oldWord, newWord)) {
        return;
    }
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}
void deleterec()
{
    char* file_name = "record.txt", temp_file_name[50], str[100];
    FILE *fp, *temp_fp;
    
    
    del();
   
    printf("\n\n\n\t\t\t\tEnter the teams to be deleted: ");
    scanf("%s", str);

    fp = fopen(file_name, "r");
    if (fp == NULL) {
       
        printf("Error opening file!");
    }

    strcpy(temp_file_name, "temp.txt");
    temp_fp = fopen(temp_file_name, "w");
    if (temp_fp == NULL) {
       
        printf("Error creating temporary file!");
        exit(1);
    }

    char line[100];
    while (fgets(line, 100, fp)) {
        if (strstr(line, str) != NULL) {
            continue;
        }
        fputs(line, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    if (remove(file_name) != 0) {
       
        printf("Error deleting file!");
        exit(1);
    }

    if (rename(temp_file_name, file_name) != 0) {
       
        printf("Error renaming file!");
        exit(1);
    }
   
    printf("\n\n\n\n\t\t\t teams '%s' deleted successfully from file '%s'", str, file_name);
}

