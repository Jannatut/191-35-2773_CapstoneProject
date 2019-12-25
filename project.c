#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

COORD coord = {0,0};


void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


int main()
{
    FILE *fp, *ft;
    char another, choice;


    struct tch
    {
        char name[40],dept[20];
        int age;
        int pnum;
    };

    struct tch t;

    char tchname[40],tchdept[20];

    long int recsize;

    fp = fopen("TCH.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("TCH.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }


    recsize = sizeof(t);


    while(1)
    {
        system("cls");
        gotoxy(30,10);
        printf("1. Add Record");
        gotoxy(30,12);
        printf("2. List Records");
        gotoxy(30,14);
        printf("3. Modify Records");
        gotoxy(30,16);
        printf("4. Delete Records");
        gotoxy(30,18);
        printf("5. Exit");
        gotoxy(30,20);
        printf("Your Choice: ");
        fflush(stdin);
        choice  = getche();
        switch(choice)
        {
        case '1':
            system("cls");
            fseek(fp,0,SEEK_END);


            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name: ");
                scanf("%s",t.name);
                printf("\nEnter age: ");
                scanf("%d", &t.age);
                printf("\nEnter department name: ");
                scanf("%s", t.dept);
                printf("\nEnter phone number:");
                scanf("%d",&t.pnum);

                fwrite(&t,recsize,1,fp);

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            printf("Teacher's name ");
            printf("\tTeacher's age ");
            printf("\tTeacher's department ");
            printf("\tTeacher's phone number");
            while(fread(&t,recsize,1,fp)==1)
            {
                printf("\n%s\t\t%d\t\t%s\t\t\t%d",t.name,t.age,t.dept,t.pnum);
            }
            getch();
            break;

        case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the teacher's name to modify: ");
                scanf("%s", tchname);
                rewind(fp);
                while(fread(&t,recsize,1,fp)==1)
                {
                    if(strcmp(t.name,tchname) == 0)
                    {
                        printf("\nEnter new name,age,department and phone number: ");
                        scanf("%s%d%s%d",t.name,&t.age,t.dept,&t.pnum);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&t,recsize,1,fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of teacher to delete: ");
                scanf("%s",tchname);
                ft = fopen("Temp.dat","wb");
                rewind(fp);
                while(fread(&t,recsize,1,fp) == 1)
                {
                    if(strcmp(t.name,tchname) != 0)
                    {
                        fwrite(&t,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("TCH.DAT");
                rename("Temp.dat","TCH.DAT");
                fp = fopen("TCH.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(fp);
            exit(0);
        }
    }
    return 0;
}

