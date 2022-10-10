#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
//custom library
#include "./lib/dirent.txt"
//my library
#include "student.c"
void headtitle(){
    printf("\n\t\t==========================================\n");
    printf("\t\t|        MarksSheet Generation In C      |\n");
    printf("\t\t------------------------------------------\n");
    printf("\t\t|     Student 1      |      Student 2    |\n");
    printf("\t\t------------------------------------------\n");
    printf("\t\t|   MD.Kamruzzman    |    MD.Amir Hamza  |\n");
    printf("\t\t|--------------------|-------------------|\n");
    printf("\t\t|   ID: 201400059    |    ID: 201400069  |\n");
    printf("\t\t==========================================\n\n");
}
int main(){
    int option;
    s_info info;

    system("color 9e");

    while(option!=4){
        headtitle();
        printf("\t\t::::::::::::::::::::::::::::::::::::::::::\n");
        printf("\t\t|             SELECT OPTIONS             |\n");
        printf("\t\t::::::::::::::::::::::::::::::::::::::::::\n");
        printf("\n\t\t 1.Register Students.");
        printf("\n\t\t 2.Select Student");
        printf("\n\t\t 3.View All Students information");
        printf("\n\t\t 4.Exit");
        printf("\n\n\t\t Enter selected No. : ");
        scanf("%d",&option);
        getchar();
        system("cls");
        if(option==1){
            headtitle();
            if(student_register(&info)==1){
                printf("\n\n\t\t Student %s registered!",info.name);
            }else printf("\n\t\t Error! student registration failed!");
            printf(" \n\t\t Enter any key to exit: ");
            getch();
            system("cls");
        }else if(option == 2){
            headtitle();
            if(view_students(&info,1)==1){
                system("cls");
                while(1){
                    printf("\n\t\t------------------------------------------");
                    printf("\n\t\t|      ABC High School,Brahmanbaria.     |");
                    printf("\n\t\t------------------------------------------");
                    printf("\n\t\t NAME    : %s",info.name);
                    printf("\n\t\t ROLL    : %d",info.roll);
                    printf("\n\t\t CLASS   : %02d          Total Marks : %4d",info.Class,total(&info));
                    printf("\n\t\t YEAR    : %4d        Grade       :   %2s",info.year,average_grade(&info));
                    printf("\n\t\t==========================================");
                    printf("\n\t\t 1.Add Marks");
                    printf("\n\t\t 2.Edit Marks");
                    printf("\n\t\t 3.Export/Generate Marks");
                    printf("\n\t\t 4.Show/Generate marks");
                    printf("\n\t\t 5.Exit");
                    printf("\n\n\t\t Select Any From Below Options: ");
                    scanf("%d",&option);
                    system("cls");
                    if(option==1){
                        add_marks(&info);
                    }else if(option==2){
                        edit_marks(&info);
                    }else if(option==3){
                        show_marks(&info);
                    }else if(option==5){
                        break;
                    }else printf("\n\t\tPlease select valid option!");
                    option = 2;
                }
            }else printf("\n\t\tStudent not found!");
            printf("\n\t\t Enter any key to exit: ");
            //system("cls");
            //headtitle();

            getch();
            system("cls");
        }else if(option == 3){
            headtitle();
            if(view_students(&info,0)!=1){
                printf("\n\t\tStudent not found!");
            }
            printf("\n\t\tEnter any key to exit: ");
            getch();
            system("cls");
        }else printf("\n\t\tPlease select valid option!");
    }
    int slp=3;
    while(slp--){
        system("cls");
        headtitle();
        printf("\n\t\tExiting in %d seconds!\n",slp);
        Sleep(1000);
    }
    return 0;
}
