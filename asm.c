#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct addfield
{
    char fieldName[50];
    char fieldChange[50];
} typedef newField;

struct Info
{
    char firstName[20];
    char midName[20];
    char lastName[20];
    char company[20];
    char phone[20];
    char mail[30];
    char address[20];
    char birthday[20];
    char web[20];
    char note[20];
    bool favourContact;
    newField fields;
} typedef Info;

void delete (Info *contacts, int findPosition, int *currentIndex);
void addField(Info *contacts, int contactIndex);
void update(Info *contacts, int contactIndex);
void favour(Info newContact, int count);
int detailsMenu(Info *contacts, int contactIndex, int *contactLength);
void displayDetails(Info *contacts, int contactIndex, int *contactLength);
void contactDetails(Info *contacts, int currentIndex, int *contactLength);
void searchContact(Info contacts[], int currentIndex);
void favourContacts(Info contacts[], int currentIndex);
void addContact(Info contacts[], int *currentIndex);
void displayAll(Info contacts[], int currentIndex, int *contactLength);
void hienThiTT(Info newInfo, int count);
void line(Info newInfo, int count);
int writeFile(Info Contacts[], int ContactCount, const char *filename);
int readFile(Info Contacts[], int *ContactCount, const char *filename);
int mainMenu();

int main()
{
    int choice;
    Info contacts[100];
    int currentIndex = 0;
    readFile(contacts, &currentIndex, "Contacts.dat");

    fflush(stdin);
    do
    {
        choice = mainMenu(choice);
        switch (choice)
        {
        case 1:
            searchContact(contacts, currentIndex);
            break;
        case 2:
            addContact(contacts, &currentIndex);
            writeFile(contacts, currentIndex, "Contacts.dat");
            break;
        case 3:
            favourContacts(contacts, currentIndex);
            break;
        case 4:
            displayAll(contacts, currentIndex, &currentIndex);
            break;
        case 5:
            printf("\n GOOD BYE !!!\n");
            printf("\n===============================================");
            break;
        }
    } while (choice != 5);
    return 0;
}

int mainMenu()
{
    int choice;
    do
    {
        printf("\n===============================================\n\n");
        printf("     --- VTC ACADEMY CONTACT MANAGEMENT ---\n\n");
        printf("===============================================\n\n");
        printf("1. SEARCH YOUR CONTACT\n");
        printf("2. ADD CONTACT\n");
        printf("3. DISPLAY FAVOURITES CONTACT\n");
        printf("4. DISPLAY ALL CONTACT\n");
        printf("5. EXIT APPLICATION\n");
        printf("===============================================\n\n");

        printf(" #YOUR CHOICE: ");
        scanf("%d", &choice);
        fflush(stdin);

        printf("\n===============================================\n");

        if (choice > 5 || choice < 1)
        {
            printf("\nERROR, Choose 1-5 again!\n");
        }
    } while (choice > 5 || choice < 1);
    return choice;
}

Info addInfo()
{
    Info newInfo;
    printf("First Name:  ");
    scanf("%[^\n]s", newInfo.firstName);
    fflush(stdin);

    printf("Middle Name: ");
    scanf("%[^\n]s", newInfo.midName);
    fflush(stdin);

    printf("Last Name:   ");
    scanf("%[^\n]s", newInfo.lastName);
    fflush(stdin);

    printf("Company:     ");
    scanf("%[^\n]s", newInfo.company);
    fflush(stdin);

    printf("Phone:       ");
    scanf("%[^\n]s", newInfo.phone);
    fflush(stdin);

    printf("Email:       ");
    scanf("%[^\n]s", newInfo.mail);
    fflush(stdin);

    printf("Address:     ");
    scanf("%[^\n]s", newInfo.address);
    fflush(stdin);

    printf("Birthday:    ");
    scanf("%[^\n]s", newInfo.birthday);
    fflush(stdin);

    printf("Website:     ");
    scanf("%[^\n]s", newInfo.web);
    fflush(stdin);

    printf("Note:        ");
    scanf("%[^\n]s", newInfo.note);
    fflush(stdin);

    return newInfo;
}

void searchContact(Info contacts[], int currentIndex)
{
    char firstName[20];
    Info newInfo[100];
    int newInfoIndex = 0;
    printf(" \n SEARCH YOUR INPUT: ");
    scanf("%s", firstName);
    printf("\n===============================================\n\n");
    printf("+---------------------------------------------+\n");
    printf("|%-5s|%-39s|\n", "No", "Name");
    printf("+---------------------------------------------+\n");
    int list = 0;
    for (int i = 0; i < currentIndex; i++)
    {
        if (strcmp(contacts[i].firstName, firstName) == 0)
        {
            line(contacts[i], newInfoIndex + 1);
            newInfoIndex++;
            list = 1;
        }
    }
    printf("+---------------------------------------------+\n");
    if (list == 0)
    {
        printf("\nNo contact with %s in list !\n", firstName);
    }
    getchar();
    fflush(stdin);
}
void displayAll(Info contacts[], int currentIndex, int *contactLength)
{
    printf(" \n ALL CONTACT\n");
    printf("\n===============================================\n\n");

    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|%-3s|%-12s|%-12s|%-12s|%-10s|%-12s|%-25s|%-15s|%-12s|%-12s|%-13s|\n",
           "No", "First name", "Middle name", "Last name", "Company", "Phone", "Email",
           "Address", "Birthday", "Website", "Note");
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------+\n");

    for (int i = 0; i < currentIndex; i++)
    {
        hienThiTT(contacts[i], i + 1);
    }
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    contactDetails(contacts, currentIndex, contactLength);
}
void addContact(Info contacts[], int *currentIndex)
{
    printf("===============================================\n\n");
    printf(" CREATE NEW CONTACT\n");
    printf("\n===============================================\n\n");

    contacts[*currentIndex] = addInfo();
    (*currentIndex)++;

    printf("\n===============================================\n\n");
    printf(" Create contact complete!\n");
    printf(" Press ENTER key to continue... \n");
    getchar();
    fflush(stdin);
}

void favourContacts(Info contacts[], int currentIndex)
{
    printf(" \n FAVOURITES CONTACT\n");
    printf("\n===============================================\n\n");
    printf("+---------------------------------------------+\n");
    printf("|%-5s|%-39s|\n", "No", "Name");
    printf("+---------------------------------------------+\n");

    for (int i = 0; i < currentIndex; i++)
    {
        if (contacts[i].favourContact == true)
            favour(contacts[i], i + 1);
    }
    printf("+---------------------------------------------+\n");
    getchar();
    fflush(stdin);
}
void contactDetails(Info *contacts, int currentIndex, int *contactLength)
{
    int choice;
    char list[50];
    do
    {
        do
        {
            printf("\n===============================================\n\n");
            printf("\nENTER NO TO VIEW DETAIL OR ENTER 0 TO BACK MAIN MENU: ");
            fgets(list, 50, stdin);
        } while (sscanf(list, "%d", &choice) == 0);
    } while (choice < 0 || choice > currentIndex);
    if (choice == 0)
    {
        return;
    }
    displayDetails(contacts, choice, contactLength);
}
void delete (Info *contacts, int findPosition, int *currentIndex)
{
    if (findPosition != *currentIndex - 1)
    {
        for (int i = 0; i < *currentIndex - 1; i++)
        {
            if (i == findPosition)
            {               
                Info temp = contacts[findPosition + 1];
                contacts[findPosition + 1] = contacts[findPosition];
                contacts[findPosition] = temp;
                findPosition++;
            }
        }
    }
    *currentIndex -= 1;
}  
void displayDetails(Info *contacts, int contactIndex, int *contactLength)
{
    int choice;
    while (1)
    {
        Info newContact = *(contacts + (contactIndex - 1));
        printf("\n===============================================\n\n");
        printf(" CONTACT DETAILS\n");
        printf("\n===============================================\n\n");
        printf(" First name:  %s\n", newContact.firstName);
        printf(" Middle name: %s\n", newContact.midName);
        printf(" Last name:   %s\n", newContact.lastName);
        printf(" Company :    %s\n", newContact.company);
        printf(" Phone :      %s\n", newContact.phone);
        printf(" Email :      %s\n", newContact.mail);
        printf(" Address :    %s\n", newContact.address);
        printf(" Birthday :   %s\n", newContact.birthday);
        printf(" Website :    %s\n", newContact.web);
        printf(" Note :       %s\n", newContact.note);

        if (strlen(newContact.fields.fieldName) && strlen(newContact.fields.fieldChange))
        {
            printf(" %s: ", newContact.fields.fieldName, "");
            printf(" %s\n", newContact.fields.fieldChange);
        }
        choice = detailsMenu(contacts, contactIndex-1, contactLength);
        if (choice == 5)
        {
            break;
        }
    }
}
int detailsMenu(Info *contacts, int contactIndex, int *contactLength)
{
    int choice;
    do
    {
        printf("\n===============================================\n\n");
        printf(" 1. ADD TO FAVOURITES\n");
        printf(" 2. UPDATE\n");
        printf(" 3. DELETE\n");
        printf(" 4. ADD FIELD\n");
        printf(" 5. BACK TO MAIN MENU\n");
        printf("===============================================\n");
        printf(" \n#YOUR CHOICE: ");
        scanf("%d", &choice);
        fflush(stdin);
        printf("\n===============================================\n\n");
        if (choice < 1 || choice > 5)
        {
            printf("Choose again!\n");
        }
        else
        {
            switch (choice)
            {
                case 1:
                    contacts[contactIndex].favourContact = true;
                    printf(" Completed add favourites contact!\n");
                    getchar();
                    fflush(stdin);
                    break;
                case 2:
                    update(contacts, contactIndex);
                    break;
                case 3:
                    delete (contacts, contactIndex, contactLength);
                    writeFile(contacts, *contactLength, "Contacts.dat");
                    return choice;
                case 4:
                    addField(contacts, contactIndex);
                    break;
                case 5:
                    break;
            }
        }
    } while (choice != 5);
    return choice;
}
void update(Info *contacts, int contactIndex)
{
    Info newInfo = contacts[contactIndex];
    printf("First name: ");
    scanf("%s", newInfo.firstName);
    fflush(stdin);
    printf("Middle name: ");
    scanf("%s", newInfo.midName);
    fflush(stdin);
    printf("Last name: ");
    scanf("%s", newInfo.lastName);
    fflush(stdin);
    printf("Company: ");
    scanf("%s", newInfo.company);
    fflush(stdin);
    printf("Phone: ");
    scanf("%s", newInfo.phone);
    fflush(stdin);
    printf("Email: ");
    scanf("%s", newInfo.mail);
    fflush(stdin);
    printf("Address: ");
    scanf("%s", newInfo.address);
    fflush(stdin);
    printf("Birthday: ");
    scanf("%s", newInfo.birthday);
    fflush(stdin);
    printf("Website: ");
    scanf("%s", newInfo.web);
    fflush(stdin);
    printf("Note: ");
    scanf("%s", newInfo.note);
    fflush(stdin);
    if (strlen(newInfo.firstName)){
        strcpy(contacts[contactIndex].firstName, newInfo.firstName);
    }
    if (strlen(newInfo.midName)){
        strcpy(contacts[contactIndex].midName, newInfo.midName);
    }
    if (strlen(newInfo.lastName)){
        strcpy(contacts[contactIndex].lastName, newInfo.lastName);
    }
    if (strlen(newInfo.company)){
        strcpy(contacts[contactIndex].company, newInfo.company);
    }
    if (strlen(newInfo.phone)){
        strcpy(contacts[contactIndex].phone, newInfo.phone);
    }
    if (strlen(newInfo.mail)){
        strcpy(contacts[contactIndex].mail, newInfo.mail);
    }
    if (strlen(newInfo.address)){
        strcpy(contacts[contactIndex].address, newInfo.address);
    }
    if (strlen(newInfo.birthday)){
        strcpy(contacts[contactIndex].birthday, newInfo.birthday);
    }
    if (strlen(newInfo.web)){
        strcpy(contacts[contactIndex].web, newInfo.web);
    }
    if (strlen(newInfo.note)){
        strcpy(contacts[contactIndex].note, newInfo.note);
    }
    getchar();
    fflush(stdin);
}

void addField(Info *contacts, int contactIndex)
{
    char fieldName[50];
    char fieldChange[50];
    newField field;
    printf("Field name: ");
    scanf("%s", fieldName);
    printf("Field Change: ");
    scanf("%s", fieldChange);

    strcpy(field.fieldName, fieldName);
    strcpy(field.fieldChange, fieldChange);
    contacts[contactIndex].fields = field;
    printf("Completed add field!");
    getchar();
    fflush(stdin);
}

void line(Info newInfo, int count)
{
    printf("|%-5d|%s %-34s|\n", count, newInfo.firstName, newInfo.lastName);
}
void hienThiTT(Info newInfo, int count)
{
    printf("|%-3d|%-12s|%-12s|%-12s|%-10s|%-12s|%-25s|%-15s|%-12s|%-12s|%-13s|\n",
           count, newInfo.firstName, newInfo.midName, newInfo.lastName,
           newInfo.company, newInfo.phone, newInfo.mail,
           newInfo.address, newInfo.birthday,
           newInfo.web, newInfo.note);
}
void favour(Info newContact, int count)
{
    printf("|%-5d|%s %-34s|\n", count, newContact.firstName, newContact.lastName);
}

int readFile(Info Contacts[], int *ContactCount, const char *filename)
{
    FILE *f;
    int result = 0;
    f = fopen(filename, "rb");
    if (f != NULL)
    {
        fread(ContactCount, sizeof(int), 1, f);
        if (*ContactCount > 0)
        {
            fread(Contacts, sizeof(Info), *ContactCount, f);
            result = 1;
        }
        fclose(f);
    }
    return result;
}
int writeFile(Info Contacts[], int ContactCount, const char *filename)
{
    FILE *f;
    int result = 0;
    f = fopen(filename, "wb");
    if (f != NULL)
    {
        fwrite(&ContactCount, sizeof(int), 1, f);
        fwrite(Contacts, sizeof(Info), ContactCount, f);
        fclose(f);
        result = 1;
    }
    return result;
}