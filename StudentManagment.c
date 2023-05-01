#include <stdio.h>

#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>

struct Student
{
    char name[40];
    int age;
    int stclass;
    char school[10];
    int id;
} st;

int i, another, Choice, count, studentId, ans, del;
char stname[40];

FILE *fp, *ft;
int HorizontalLine(int count)
{
    int i;
    printf("\n");
    for (i = 0; i < count; i++)
    {
        printf("_");
    }
    printf("\n");
    return (0);
}
void AddRecord()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    while (1)
    {

        system("cls"); // clears system screen

        printf("\nEnter The number of students you want to add : "); // user input
        scanf("%d", &count);

        for (i = 1; i <= count; i++)
        {
            st.id = st.id + 1; // always sets stid to plus 1 to keep it unique

            HorizontalLine(30); // a function to create lines for systematic looks

            printf("\nEnter your name : "); // entering details for the record
            scanf("%s", st.name);

            printf("\nEnter your age : ");
            scanf("%d", &st.age);

            printf("\nEnter your class : ");
            scanf("%d", &st.stclass);

            printf("\nEnter your school : ");
            scanf("%s", st.school);

            printf("\nStudent id is : %d", st.id);

            HorizontalLine(30); // a function to create lines for systematic looks

            fwrite(&st, sizeofstruct, 1, fp); // writes the value in the file
        }
        printf("\n\nDo you want to Add another record(press 1 for YES press 0 for NO) : "); // choice to add another record
        scanf("%d", &ans);
        if (ans == 0)
        {
            break;
        }
    }
}
void SearchRecord()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    while (1)
    {
        system("cls"); // clears system screen

        printf("\nEnter ID of Student to Search : "); // input id
        scanf("%d", &studentId);

        rewind(fp);                                  // goes to start of file
        while (fread(&st, sizeofstruct, 1, fp) == 1) // reads the value of student structure
        {
            if (st.id == studentId) // if id is matched it will show the record
            {
                printf("\n CURRENT RECORD \n\nName : %s \nAge : %d \nClass :  %d \nSchool : %s \nId : %d\n\n", st.name, st.age, st.stclass, st.school, st.id);
            }
        }

        printf("\nDo you want to Search another record(press 1 for YES press 0 for NO) : "); // choice to search another record
        scanf("%d", &ans);
        if (ans == 0)
        {
            break;
        }
    }
}
void ShowAllRecords()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    system("cls"); // clears system screen
    printf("\n\n ALL RECORDS \n\n");
    rewind(fp); // goes to start of file

    while (fread(&st, sizeofstruct, 1, fp) == 1) // reads the value of student structure
    {
        // prints the records
        printf("\nName : %s \nAge : %d \nClass :  %d \nSchool : %s \nId : %d\n\n", st.name, st.age, st.stclass, st.school, st.id);
    }
    system("\npause"); // stop the code to show the results
}
void ModifyRecords()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    while (1)
    {
        system("cls"); // clears system screen

        printf("Enter the Student id to modify : "); // input id
        scanf("%d", &studentId);

        rewind(fp); // goes to start of file

        while (fread(&st, sizeofstruct, 1, fp) == 1) // reads the value of student structure
        {
            if (st.id == studentId) // if id is matched it will show the record
            {
                // shows the current values in the record
                printf("\n CURRENT RECORD \n\nName : %s \nAge : %d \nClass :  %d \nSchool : %s \nId : %d\n\n", st.name, st.age, st.stclass, st.school, st.id);
                while (1)
                {
                    // choice to change the record or not
                    printf("\nDo you want to Modify This record(press 1 for YES press 0 for NO) : ");
                    scanf("%d", &ans);
                    if (ans == 1)
                    {
                        // entering new values
                        printf("\nEnter your new name : ");
                        scanf("%s", st.name);

                        printf("\nEnter your new age : ");
                        scanf("%d", &st.age);

                        printf("\nEnter your new class : ");
                        scanf("%d", &st.stclass);

                        printf("\nEnter your new school : ");
                        scanf("%s", st.school);

                        printf("\nYour New ID : %d", st.id);

                        fseek(fp, -sizeofstruct, SEEK_CUR); // goes a position behind

                        fwrite(&st, sizeofstruct, 1, fp); // writes the new value of student structure in file
                        // prints the new values of the record
                        printf("\n\n NEW RECORD \n\nName : %s \nAge : %d \nClass :  %d \nSchool : %s \nId : %d\n\n", st.name, st.age, st.stclass, st.school, st.id);
                    }

                    break;
                }
                break;
            }
        }
        printf("\nDo you want to Modify another record(press 1 for YES press 0 for NO) : "); // choice to modify another record
        scanf("%d", &ans);
        if (ans == 0)
        {
            break;
        }
    }
}
void DeleteSelectedRecord()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    while (1)
    {
        system("cls"); // clears system screen

        printf("\nEnter ID of Student to delete : "); // input id
        scanf("%d", &studentId);
        ft = fopen("Temp.dat", "wb"); // opens new file to add records
        rewind(fp);
        while (fread(&st, sizeofstruct, 1, fp) == 1) // reads the structure values of student from file
        {
            if (st.id == studentId) // if id is matched it will show the record and not enter it in new file
            {
                printf("\n DELETED RECORD \n\nName : %s \nAge : %d \nClass :  %d \nSchool : %s \nId : %d\n\n", st.name, st.age, st.stclass, st.school, st.id);
            }
            if (st.id != studentId) // if id not matched it will write the records in new file
            {

                fwrite(&st, sizeofstruct, 1, ft);
            }
        }

        fclose(fp); // close files
        fclose(ft);
        remove("Student1.dat");                                                              // deletes the original file
        rename("Temp.dat", "Student1.dat");                                                  // name change of new file to original file
        fp = fopen("Student1.dat", "rb+");                                                   // opens the new file
        printf("\nDo you want to Delete another record(press 1 for YES press 0 for NO) : "); // choice to delete another record
        scanf("%d", &ans);
        if (ans == 0)
        {
            break;
        }
    }
}
void DeleteAllRecords()
{
    while (1)
    {
        printf("\nDo you want to Delete All Records (press 1 for YES press 0 for NO) : "); // input
        scanf("%d", &ans);
        if (ans == 1)
        {

            fclose(fp);                      // first close the  file
            if (remove("Student1.dat") == 0) // if file is deleted
            {
                printf("\n\nDeleted successfully\n");
            }
            else
            {
                printf("Unable to delete the file");
            }
            system("\npause"); // pause the code to show results
        }
        break;
    }
}
int Menu()
{

    int FuncChoice;
    HorizontalLine(30); // a function to create lines for systematic looks
    printf("\nSTUDENT MANAGEMENT SYSTEM");
    HorizontalLine(30); // a function to create lines for systematic looks

    printf("\n\n1. Add a Student Record");
    printf("\n\n2. Search a Student Record");
    printf("\n\n3. List all Student Record");
    printf("\n\n4. Modify a Student Record");
    printf("\n\n5. Delete a Student Record");
    printf("\n\n6. Delete all Student Records");
    printf("\n\n7. EXIT");
    printf("\n\n\nEnter Your Choice(Press 1/2/3/4/5/6/7) : ");
    scanf("%d", &FuncChoice); // takes user input
    return (FuncChoice);      // returns it to main function
}
int main()
{
    long int sizeofstruct;
    sizeofstruct = sizeof(st);

    fp = fopen("Student1.dat", "rb+"); // opens file in read and write mode
    if (fp == NULL)                    // if there is no such file
    {
        st.id = 0;
        fp = fopen("Student1.dat", "wb+"); // creates new file and open it in read and write mode
        if (fp == NULL)                    // still no file
        {
            printf("Connot open file"); // displays error and exits
            exit(1);
        }
    }

    while (Choice != 7)
    {
        system("cls");

        Choice = Menu();        // calling menu function to take user input
        fseek(fp, 0, SEEK_END); // It checks wether there is any value in the file or not
        if (ftell(fp) == 0)
        {
            st.id = 0; // if no value in file its sets the st.id value to 0
        }
        fseek(fp, 0, SEEK_SET); // returns back to original position
        if (st.id != 0)         // if there is a value in file
        {

            fseek(fp, sizeofstruct, SEEK_END);  // goes to end of file
            fread(&st.id, sizeofstruct, 1, fp); // reads the value of st.id to keep it continuing and unique for each record
        }

        switch (Choice)
        {
        case 1:
            AddRecord(); // Calling Add Record function to add a record
            break;
        case 2:
            SearchRecord(); // Calling Search Record function to search a record
            break;
        case 3:
            ShowAllRecords(); // Calling Show All Records function to show all records
            break;

        case 4:
            ModifyRecords(); // Calling Modify Records function to modify a record
            break;

        case 5:
            DeleteSelectedRecord(); // Calling Delete Selected Record function to delete a particular record
            break;
        case 6:
            DeleteAllRecords(); // Calling Delete All Records function to delete all records
            break;
        default:
            if (Choice == 7) // Exit the software
            {
            }
            else // any input other than the given choice will lead to tryagain
            {
                printf("\nWrong Input Try Again\n");
                system("pause");
            }
            break;
        }
    }

    printf("\nThanks For Using Our Software\n\n");
    fclose(fp); // closing file
    return (0);
}
