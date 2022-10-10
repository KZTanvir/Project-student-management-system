#define SUBJECTS_TOTAL 7
const char subjects[SUBJECTS_TOTAL][30] = {"BANGLA","ENGLISH","MATH","ICT","CHEMISTRY","BIOLOGY","PHYSICS"};

typedef struct student{
    int roll,Class,year;
    char name[30];
    struct result{
        int final_marks;
        int mid_marks;
        char subjects[30];
    }result[SUBJECTS_TOTAL];
}s_info;
//return directory string
int dir(s_info *student, char *directory){
    //student info int to string
    char Class[4],roll[6],year[6];
    sprintf(Class, "%d", student->Class);
    sprintf(roll, "%d", student->roll);
    sprintf(year, "%d", student->year);
    //generating directory for creation of file//
    strcpy(directory,"./student/class_");
    strcat(directory,Class);
    strcat(directory,"/");
    strcat(directory,year);
    strcat(directory,"/");
    strcat(roll,".bin");
    strcat(directory,roll);
    //file existing work
    FILE *stats;
    stats = fopen(directory,"r");
    if(stats!=NULL){
        fclose(stats);
        return 1;
    }else return 0;
}
//giving grades based on the data info
int total(s_info *student){
    int MTotal=0;
    for(int i=0;i<SUBJECTS_TOTAL;i++){
        if(student->result[i].final_marks <0 || student->result[i].mid_marks<0 || student->result[i].mid_marks>=100 || student->result[i].final_marks>=100){
            return -1;
        }
        MTotal = MTotal + student->result[i].final_marks + student->result[i].mid_marks;
    }
    return MTotal;
}
char *grades(int marks){
    switch(marks){
    case 0 ... 32:
        return "F";
        break;
    case 33 ... 39:
        return "D";
        break;
    case 40 ... 49:
        return "C";
        break;
    case 50 ... 59:
        return "B";
        break;
    case 60 ... 69:
        return "A-";
        break;
    case 70 ... 79:
        return "A";
        break;
    case 80 ... 100:
        return "A+";
        break;
    default:
        return "I";
        break;
    }
    return NULL;
}
char *average_grade(s_info *student){
    int MTotal=0,count=0;
    for(int i = 0; i < SUBJECTS_TOTAL; i++){
        if(student->result[i].final_marks <0 || student->result[i].mid_marks<0 || student->result[i].mid_marks>=100 || student->result[i].final_marks>=100){
            return "I";
        }
        MTotal = MTotal + student->result[i].final_marks + student->result[i].mid_marks;
        if (student->result[i].final_marks + student->result[i].mid_marks< 33)
            count = count + 1;
    }
    if(count>0) return "F";
    else return grades(MTotal/SUBJECTS_TOTAL);
}
//register student  in the database
int student_register(s_info *student){
    printf("\t\t------------------------------------------\n");
    printf("\t\t|            REGISTER STUDENT            |\n");
    printf("\t\t------------------------------------------\n");
    printf("\n\t\t Enter student name   : ");
    gets(student->name); //getting pointer to structure..
    printf("\t\t Enter student class  : ");
    scanf("%d",&student->Class);
    printf("\t\t Enter student roll   : ");
    scanf("%d",&student->roll);
    printf("\t\t Enter student year   : ");
    scanf("%d",&student->year);
    //default information to  insert//
    //getting the directory for information
    char directory[100];
    int stats = dir(student,directory);

    if(stats==1 && student->Class > 10 && student->Class < 0 && student->roll > 100 && student->roll < 0){
        student->Class = 0;
        student->roll = 0;
        student->year = 0;
        student->name[0] = '\0';
        return -1;
    }
//creating file for importing the student information//
    FILE *student_info;
    student_info = fopen(directory, "w");
    if (student_info==NULL){
        fclose(student_info);
        student->Class = 0;
        student->roll = 0;
        student->year = 0;
        student->name[0] = '\0';
        fclose(student_info);
        return -2;
    }else{
        for(int i=0;i<SUBJECTS_TOTAL;i++){
            student->result[i].mid_marks = -1;
            student->result[i].final_marks = -1;
            strcpy(student->result[i].subjects,subjects[i]);
        }
        fwrite(student, sizeof(s_info), 1, student_info);
        fclose(student_info);
        return 1;
    }
}
//student list
int view_students(s_info *student,int conf){
    s_info std[100];
    char Class[4],year[6];
    if(conf){
    printf("\t\t------------------------------------------\n");
    printf("\t\t|            SELECT STUDENTS             |\n");
    printf("\t\t------------------------------------------\n");
    }else{
    printf("\t\t------------------------------------------\n");
    printf("\t\t|             VIEW STUDENTS              |\n");
    printf("\t\t------------------------------------------\n");
    }
    printf("\n\t\t Enter student class: ");
    scanf("%s",Class);
    printf("\n\t\t Enter student year : ");
    scanf("%s",year);

    char directory[100],tempdir[100];
    strcpy(directory,"student/class_");
    strcat(directory,Class);
    strcat(directory,"/");
    strcat(directory,year);
    strcat(directory,"/");

    struct dirent *dir;
    DIR *dp = opendir(directory);//opens current directory
    FILE *info;//a file pointer
    int i=1;
    if(dp){
        while((dir = readdir(dp))!= NULL && i<=100){
            if(dir->d_type == DT_REG){
                strcpy(tempdir,directory);
                strcat(tempdir,dir->d_name);
                info = fopen(tempdir,"r");
                fread(&std[i-1], sizeof(s_info), 1, info);
                printf("\n\t\t+------------[INDEX: %02d]-----------------+",i);
                printf("\n\t\t Name: %s  \n\t\t Roll: %d\t\t\tGrade: %s",std[i-1].name, std[i-1].roll, average_grade(&std[i-1]));//info of student need some work to do
                fclose(info);
                i++;
            }
        }
        printf("\n\t\t------------------END---------------------");
    closedir(dp);
    }else{return -1;}
    if(conf==0)return 1;
    int counter = 0;
    while(1){
        printf("\n\t\t Enter INDEX No. of student: ");
        scanf("%d",&counter);
        if(counter<i && counter>0){
            *student = std[counter-1];
            return 1;
        }else return 0;
    }
}
//select student from the files in the proper directory
int select_student(s_info *student){
    printf("\t\t------------------------------------------\n");
    printf("\t\t|             SELECT STUDENT             |\n");
    printf("\t\t------------------------------------------\n");
    printf("\n\t\t Enter student class: ");
    scanf("%d",&student->Class);
    printf("\n\t\t Enter student roll: ");
    scanf("%d",&student->roll);
    printf("\n\t\t Enter student year: ");
    scanf("%d",&student->year);

    char directory[100];
    dir(student,directory);
//creating file for importing the student information//
    FILE *student_info;
    student_info = fopen(directory, "r");
    if (student_info==NULL) {
        student->Class = 0;
        student->roll = 0;
        student->year = 0;
        student->name[0] = '\0';
        fclose(student_info);
        return 0;
    }else{
        fread(student, sizeof(s_info), 1, student_info);
        fclose(student_info);
        return 1;
    }
}
//save student information after console work
void save_data(s_info *student){
    char directory[100];
    dir(student,directory);
    //creating file for importing the student information//
    FILE *student_info;
    student_info = fopen(directory, "r+");
    if (student_info==NULL){
        fclose(student_info);
    }else{
        fwrite(student, sizeof(s_info), 1, student_info);
        fclose(student_info);
    }
}

//prints marks in the console/terminal
void show_marks(s_info *student){
    printf("\n\t\t------------------------------------------");
    printf("\n\t\t             ABC High School              ");
    printf("\n\t\t------------------------------------------");
    printf("\n\t\t NAME    : %s",student->name);
    printf("\n\t\t CLASS   : %02d          TOTAL MARKS : %4d",student->Class,total(student));
    printf("\n\t\t ROLL    : %2d",student->roll);
    printf("\n\t\t YEAR    : %4d        Grade       :   %2s",student->year,average_grade(student));
    printf("\n-------------------------------------------------------------------------------------");
    printf("\n|     MID MARK       |     FINAL MARK     |     TOTAL MARKS    |        GRADE       |");
    printf("\n-------------------------------------------------------------------------------------");
    int count=0;
    for(int i = 0; i < SUBJECTS_TOTAL; i++){
        printf("\n %s",student->result[i].subjects);
        printf("\n-------------------------------------------------------------------------------------");
        printf("\n|        %03d         |         %03d        |         %03d        |         %2s        |",student->result[i].mid_marks,student->result[i].final_marks,(student->result[i].final_marks+student->result[i].mid_marks),grades(student->result[i].mid_marks+student->result[i].final_marks));
        printf("\n---------------------|---------------------------------------------------------------");
        if (student->result[i].final_marks + student->result[i].mid_marks< 33)
            count = count + 1;
    }
    if(count>0) printf("\n\t\t\t\t RESULT : FAIL\n");
    else printf("\n\t\t\t\t RESULT : PASS\n");
    printf("\n\n\tEnter any Key to continue!");
    getch();
    system("cls");
}

void add_marks(s_info *student){
    for(int i=0; i<SUBJECTS_TOTAL; i++){
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t|               ADD MARKS                |");
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t NAME    : %s",student->name);
        printf("\n\t\t ROLL    : %2d",student->roll);
        printf("\n\t\t CLASS   : %02d          Total Marks : %4d",student->Class,total(student));
        printf("\n\t\t YEAR    : %4d        Grade       :   %2s",student->year,average_grade(student));
        printf("\n\t\t==========================================");
        printf("\n\t\t Subject Name: %s",student->result[i].subjects);
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t Mid Exam Mark   : ");
        scanf("%d",&student->result[i].mid_marks);
        printf("\n\t\t Final Exam Mark : ");
        scanf("%d",&student->result[i].final_marks);
        //Sleep(1000);
        system("cls");
    }
    save_data(student);
}
void edit_marks(s_info *student){
    char term = 'Y';
    int sb = -1;
    while(term=='Y' || term=='y'){
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t|               EDIT MARKS               |");
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t NAME    : %s",student->name);
        printf("\n\t\t ROLL    : %2d",student->roll);
        printf("\n\t\t CLASS   : %02d          Total Marks : %4d",student->Class,total(student));
        printf("\n\t\t YEAR    : %4d        Grade       :   %2s",student->year,average_grade(student));
        printf("\n\t\t==========================================");
        printf("\n\t\t|               SUBJECTS                 |");
        printf("\n\t\t------------------------------------------");
        for(int i=0;i<SUBJECTS_TOTAL;i++){
            printf("\n\t\t %d. %s",i+1,student->result[i].subjects);
        }
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t Select subject No. from list:");
        scanf("%d",&sb);sb--;
        system("cls");
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t|               EDIT MARKS               |");
        printf("\n\t\t------------------------------------------");
        printf("\n\t\t NAME    : %s",student->name);
        printf("\n\t\t ROLL    : %2d",student->roll);
        printf("\n\t\t CLASS   : %02d          Total Marks : %4d",student->Class,total(student));
        printf("\n\t\t YEAR    : %4d        Grade       :   %2s",student->year,average_grade(student));
        printf("\n\t\t==========================================");
        printf("\n\t\t|               ENTER MARKS              |");
        printf("\n\t\t------------------------------------------");

        printf("\n\t\t Selected: [ %s ]\n\n\t\t Mid Marks: ",student->result[sb].subjects);
        scanf("%d",&student->result[sb].mid_marks);
        printf("\n\t\t Final Marks: ");
        scanf("%d",&student->result[sb].final_marks);
        printf("\n\n\t\t Edit More Marks(Y/N): ");
        getchar();
        scanf("%c",&term);
        system("cls");
    }
    save_data(student);
}

