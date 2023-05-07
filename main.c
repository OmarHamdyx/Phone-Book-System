#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <strings.h>

typedef struct                                      //DOB structure which is used in main structure
{
    char days[5];
    char months[5];
    char year[5];
} DOBStruct;

typedef struct                                      // main structure of contacts
{
    char firstName[50];
    char lastName[50];
    DOBStruct DOB;
    char address[50];
    char email[50];
    char phoneNumber[50];
} contact;

int countLoad=0;                                    //Counter for the number of contacts in the text file
contact contacts[100];                              //Array of contact structure (the main array that all the contacts are saved in)
int countSearchResultsArray[50];                    //Array of search results(global because it's used in both delete,modify and search functions), it saves the index of the found contact in an array to be able to call it back when needed
int indexOfFinalSearchResult;                       //Represents the index of the previous array
int countSearchResults=0;                           //It's used for validation, to know if there's search results or not
char fileCall[50];                                  //scans the name of the text file the user wants to load from
int flagSave=1;                                     //It's used to ensure that the user knows that he didn't save before exiting the program

void load()                                         //LOAD(read)function
{
    printf("Please enter the name of the file you want to load:\n");
    scanf("%s",fileCall);
    FILE *fp;
    fp=fopen(fileCall,"r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%[^,],",contacts[countLoad].firstName);
            fscanf(fp,"%[^,],",contacts[countLoad].lastName);
            fscanf(fp,"%[^-]-",contacts[countLoad].DOB.days);                               //In [^-]- the stopping delimiter is "-"
            fscanf(fp,"%[^-]-",contacts[countLoad].DOB.months);                             //In [^,], the stopping delimiter is ","
            fscanf(fp,"%[^,],",contacts[countLoad].DOB.year);                               //In [^\n]\n the stopping delimiter is "\n"
            fscanf(fp,"%[^,],",contacts[countLoad].address);
            fscanf(fp,"%[^,],",contacts[countLoad].email);
            fscanf(fp,"%[^\n]\n",contacts[countLoad].phoneNumber);
            countLoad++;
        }
        fclose(fp);
    }
    else
    {
        printf("\a\n\nWe couldn't find a file with this name, please try again...\n");
        load();
    }
    system("cls");
    if(contacts[0].firstName[0]==NULL)              //This is when the file is empty, to decrease the count load by one
    {
        countLoad --;
    }
}

void returnMenu()
{
    printf("Press Enter to return to main menu\n");
    getchar();
    if (getchar() == '\n')
    {
        menu();
    }
    else
        returnMenu();
}

void addContact()                                                   //Adding contact function
{
    int j=3;                                                        //Used to scan the date of birth
    int i;
    char temporaryDate[11];
    char *token;
    int counterEmailAt=0;
    int counterEmailDot=0;
    int indexOfAt;
    int indexOfDot;
    int counterDOBOfDashes=0;
    char T[50];                                                                                               //this is for the condition and it's equal to contacts[countLoad].phoneNumber, contacts[countLoad].firstName and contacts[countLoad].lastName (this is only to make it easier to read)
    printf("Please enter the first name\n");
labelFirstNameConfirmation:
    scanf(" %[^\n]s",contacts[countLoad].firstName);                                                        //We wanted to give the user the freedom with naming, but we sticked with the sample text submitted
    strcpy(T,contacts[countLoad].firstName);
    for (i=0 ; i<strlen(T) ; i++)
    {
        if ( (T[i]<32)  ||  (T[i]>32 && T[i]<45)  ||  (T[i]>45 && T[i]<65)  ||  (T[i]>90 && T[i]<97)  ||  (T[i]>122) )                //these are ascii codes for space and "-" as these are the only chars that can be put in a name in addition to [a-z]
        {
            printf ("\aYou entered an invalid First Name, please try again:\n");
            goto labelFirstNameConfirmation;
        }
    }
    printf("Please enter the last name\n");
labelLastNameConfirmation:
    scanf(" %[^\n]s",contacts[countLoad].lastName);
    strcpy(T,contacts[countLoad].lastName);
    for (i=0 ; i<strlen(T) ; i++)
    {
        if ( (T[i]<32)  ||  (T[i]>32 && T[i]<45)  ||  (T[i]>45 && T[i]<65)  ||  (T[i]>90 && T[i]<97)  ||  (T[i]>122) )              //same as the first name
        {
            printf ("\aYou entered an invalid Last Name, please try again:\n");
            goto labelLastNameConfirmation;
        }
    }
    printf("Please enter the Date of birth in the following form DD-MM-YYYY\n");                             // Receive the date and store it in a temporary string to be convert it into tokens
labelDOBConfirmation:                                                                                        //This is a validation for when a user enters the DOB in a format other than DD-MM-YYYY
    scanf(" %[^\n]s",temporaryDate);
    for(i=0,counterDOBOfDashes=0; i<strlen(temporaryDate); i++)
    {
        if (temporaryDate[i]=='-')
            counterDOBOfDashes++;
    }
    if (temporaryDate[2]!='-' || temporaryDate[5]!='-' || counterDOBOfDashes!=2 || strlen(temporaryDate)!=10)                                     //CounterDOB condition is when user enters DOB in format other than DD-MM-YYYY that includes more that 2 dashes
    {
        printf("\aWe couldn't recognize the Date of Birth you entered, please enter it in this format only DD-MM-YYYY\n");
        goto labelDOBConfirmation;
    }
    printf("Please enter the Address\n");
    scanf(" %[^\n]s",contacts[countLoad].address);
    printf("Please enter the E-mail\n");
labelEmailConfirmation:                                                                                       //This is a validation for when a user enters an email that contains more than one "@"
    scanf("%s",contacts[countLoad].email);
    for (i=0,counterEmailAt=0,counterEmailDot=0,indexOfAt=0,indexOfDot=0 ; i<strlen(contacts[countLoad].email) ; i++)
    {
        if(contacts[countLoad].email[i] == '@')
        {
            counterEmailAt++;
            indexOfAt = i;
        }
        if(contacts[countLoad].email[i]=='.')
        {
            counterEmailDot++;
            indexOfDot = i;
        }
    }
    if(counterEmailAt!=1 || counterEmailDot<1 || (indexOfAt>indexOfDot && counterEmailDot>=1) || contacts[countLoad].email[0]=='@' )    //No emails with :1*more than one @ sign 2*No dots 3*No dots after the one @ sign 4*@ sign at beginning of email                                         //Second condition is a validation for when user enters email starting by "@"
    {
        printf("\aYou entered an invalid E-mail, please try again:\n");                                                                  //In the validation of the E-mail we didn't put any restrictions on the ".com" because some E-mails don't end this way like ".alexu.edu.eg"
        goto labelEmailConfirmation;
    }
    printf("Please enter the Phone number\n");
labelPhoneNumberConfirmation:
    scanf(" %[^\n]s",contacts[countLoad].phoneNumber);
    strcpy(T,contacts[countLoad].phoneNumber);
    for(i=0; i<strlen(T) ; i++)
    {
        if( (T[i]<32)  ||  (T[i]>32&&T[i]<43)  ||  (T[i]>43&&T[i]<45)  ||  (T[i]>45&&T[i]<48)  || (T[i]>57) )       //these are ascii codes for space,"+" and "-" as these are the only chars that can be put in a phone number in addition to [0-9]
        {
            printf("\aYou entered an invalid Phone Number, please try again:\n");
            goto labelPhoneNumberConfirmation;
        }
    }
    token = strtok(temporaryDate,"-");
    while (token!=NULL)
    {
        if(j==3)
            strcpy(contacts[countLoad].DOB.days,token);
        if(j==2)
            strcpy(contacts[countLoad].DOB.months,token);
        if(j==1)
            strcpy(contacts[countLoad].DOB.year,token);
        token=strtok(NULL,"-");
        j--;
    }
    ++countLoad ;
    printf ("successfully added\n");
    flagSave=0;
    returnMenu();
}

void printElement(int i)                                            //Print one element function that takes the number of the element as an argument
{
    printf("First name: %s\n",contacts[i].firstName);
    printf("Last name: %s\n",contacts[i].lastName);
    printf("Date of birth: %s/%s/%s\n",contacts[i].DOB.days,contacts[i].DOB.months,contacts[i].DOB.year);
    printf("Address: %s\n",contacts[i].address);
    printf("E-mail: %s\n",contacts[i].email);
    printf("Phone number: %s\n",contacts[i].phoneNumber);
    printf("_____________________________________________________________________________________________________\n");
}

void printList()                                                    //Print all (list) contacts functions (loop of the print element function
{
    int i;
    if(contacts[0].firstName[0]==NULL)
    {
        printf("\aThere are no contacts yet\n\n\n\n\n");
        returnMenu();
    }
    else
    {
        sort();
        for(i=0; i<countLoad; i++)
        {
            printElement(i);
        }
        returnMenu();
    }
}

void save()                                                         //Save function: saves the array of structures into a text file to be able to access it again
{
    FILE *fs;
    fs=fopen(fileCall,"w");                                         // file call is the string that scans the name of the file the user loaded from
    int i ;
    for (i=0; i<countLoad; i++)
    {
        fprintf(fs,"%s,",contacts[i].firstName);
        fprintf(fs,"%s,",contacts[i].lastName);
        fprintf(fs,"%s-%s-%s,",contacts[i].DOB.days,contacts[i].DOB.months,contacts[i].DOB.year);
        fprintf(fs,"%s,",contacts[i].address);
        fprintf(fs,"%s,",contacts[i].email);
        fprintf(fs,"%s\n",contacts[i].phoneNumber);
    }
    fclose(fs);
    printf("Successfully saved!\n");
    flagSave=1;
    returnMenu();
}

void searchForDelete()                       //searches by first and last name instead of last name only
{
    int i;
    char last[50];
    char first[50];
    char wrongConfirmation[50];
    printf("Please enter the last name of the contact\n");
    scanf("%s",last);
    printf("Now please enter his/her first name\n");
    scanf("%s",first);
    printf("\n\n");
labelSearchConfirmation:
    for (i=0,countSearchResults=0 ; i<countLoad ; i++)
    {
        if (strcasecmp(last,contacts[i].lastName)==0 && strcasecmp(first,contacts[i].firstName)==0)
        {
            ++countSearchResults;
            countSearchResultsArray[countSearchResults-1]=i;            //countSearchResultsArray holds the index of the found elements of the main array of struct in an array of integers
            if (countSearchResults==1 && i==(countLoad-1))              //This two condition prevent it from printing contact number:%d when the search has only 1 contact result
            {
                printElement(i);
                break;
            }
            else if (countSearchResults>=1)
            {
                printf("Contact number: %d\n\n",countSearchResults);
            }
            printElement(i);
        }
    }
    if (countSearchResults!=0 && countSearchResults!=1)                          //The second condition is to prevent it from printing we found %d elements when the search results is one only
    {
        printf("\nWe found %d contacts having the same last name...\n",countSearchResults);
        printf("Please choose the contact you want by typing its number\n");
        if (scanf("%d",&indexOfFinalSearchResult))
        {
            system("cls");
            printElement(countSearchResultsArray[indexOfFinalSearchResult-1]);
        }
        else if (scanf("%s",wrongConfirmation))
        {
            system("cls");
            printf("\a\n\n\nWe couldn't recognize your decision, please enter a valid number...\n\n\n");
            goto labelSearchConfirmation ;
        }
    }
    else if(countSearchResults==0)
        printf("\aWe didn't find any contacts having the last name...\n");
}

void searchByLastName()
{
    int i;
    char last[50];
    char wrongConfirmation[50];
    printf("Please enter the last name of the contact\n");
    scanf("%s",last);
    printf("\n\n");
labelSearchConfirmation :
    for (i=0,countSearchResults=0 ; i<countLoad ; i++)
    {
        if (strcasecmp(last,contacts[i].lastName)==0)
        {
            ++countSearchResults;
            countSearchResultsArray[countSearchResults-1]=i;            //countSearchResultsArray holds the index of the found elements of the main array of struct in an array of integers
            if (countSearchResults==1 && i==(countLoad-1))              //This two condition prevent it from printing contact number:%d when the search has only 1 contact result
            {
                printElement(i);
                break;
            }
            else if (countSearchResults>=1)
            {
                printf("Contact number: %d\n\n",countSearchResults);
            }
            printElement(i);
        }
    }
    if (countSearchResults!=0 && countSearchResults!=1)                          //The second condition is to prevent it from printing we found %d elements when the search results is one only
    {
        printf("\nWe found %d contacts having the same last name...\n",countSearchResults);
        printf("Please choose the contact you want by typing its number\n");
        if (scanf("%d",&indexOfFinalSearchResult))
        {
            system("cls");
            printElement(countSearchResultsArray[indexOfFinalSearchResult-1]);
        }
        else if (scanf("%s",wrongConfirmation))
        {
            system("cls");
            printf("\a\n\n\nWe couldn't recognize your decision, please enter a valid number...\n\n\n");
            goto labelSearchConfirmation ;
        }
    }
    else if(countSearchResults==0)
        printf("\aWe didn't find any contacts having the last name...\n");
}

void sortByLastName()                                               // Sorting by last name function
{
    contact temporaryContact;
    int j,i;
    for (i=0; i<countLoad-1; i++)
    {
        for (j=i+1; j<countLoad; j++)
        {
            if (strcasecmp(contacts[i].lastName, contacts[j].lastName) > 0)                 //We use strcasecmp()
            {
                temporaryContact = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temporaryContact;
            }
        }
    }
}

void sortByDOB()
{
    contact temporaryContact;
    int j,i;
    for (i=0; i<countLoad; i++)
    {
        for (j=i+1; j<countLoad; j++)
        {
            if (strcasecmp(contacts[i].DOB.year, contacts[j].DOB.year) > 0)                 //We use strcasecmp()
            {
                temporaryContact = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temporaryContact;
            }
            else if (strcasecmp(contacts[i].DOB.year,contacts[j].DOB.year)==0 && strcasecmp(contacts[i].DOB.months,contacts[j].DOB.months)>0)
            {
                temporaryContact = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temporaryContact;
            }
            else if (strcasecmp(contacts[i].DOB.year,contacts[j].DOB.year)==0 && strcasecmp(contacts[i].DOB.months,contacts[j].DOB.months)==0 && strcasecmp(contacts[i].DOB.days,contacts[j].DOB.days)>0)
            {
                temporaryContact = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temporaryContact;
            }
        }
    }
}

void sort()                                                        // Main sort function (calls both sortByDOB and sortByLastName)
{
    int n;
    char wrongConfirmation [50];
    printf("Do you want to sort the contacts by the Last Name or the Date of Birth\n\n\n");
    printf("To sort by Last name: enter 1\nTo sort by Date of birth: enter 2\n");
    if (scanf("%d",&n))
    {
        system("cls");
        if (n==1)
            sortByLastName();
        else if (n==2)
            sortByDOB();
        else
        {
            printf("\a\nYou entered an invalid number, please try again...\n");
            sort();
        }
    }
    else if (scanf("%s",wrongConfirmation))
    {
        system("cls");
        printf("\a\n\n\nWe couldn't recognize your decision, please enter a valid number...\n\n\n");
        sort();
    }
}

void deleteContact()
{
    searchForDelete();
    if(countSearchResults>0)
    {
        char confirm[50];
        printf("\nThis is the information of the contact you want to delete...\n");
        printf("Are you sure you want to delete it? (y/n)\n");
        scanf(" %c",&confirm);                                                          //There must be a space before %c as the scanf  gets the newline character from the previous data entry
        if (strcasecmp(confirm,"y")==0)
        {
            contacts[countSearchResultsArray[indexOfFinalSearchResult]] = contacts[--countLoad];
            printf ("\n\n\nSuccessfully deleted\n");
            flagSave=0;
            returnMenu();
        }
        else if(strcasecmp(confirm,"n")==0)
        {
            returnMenu();
        }
        else
        {
labelConfirmation:                      //Here is the label of goto
            system("cls");
            printf("\aWe couldn't recognize your decision, enter y to delete another contact or enter n to return to menu\n");
            scanf(" %s",&confirm);
            if(strcasecmp(confirm,"y")==0)
            {
                deleteContact();
            }
            else if (strcasecmp(confirm,"n")==0)
            {
                returnMenu();
            }
            else
            {
                goto labelConfirmation;                     // here we used the goto to make a loop to ensure the user to enter y or n
            }
        }
    }
    else
    {
        returnMenu();
    }
}

void modifyContact()
{
    searchByLastName();
    if(countSearchResults>0)
    {
        int n,j=3,i,counterDOBOfDashes,counterEmailAt,counterEmailDot;
        char tempModify[50];
        char temporaryDate[16];
        char *token;
        char confirmation[50];
        char wrongConfirmation[50];
        char T[50];
        int indexOfAt;
        int indexOfDot;
labelConfirmation:
        printf ("\nTo change the first name enter: 1\nTo change the last name enter: 2\nTo change the date of birth enter: 3\n");
        printf ("To change the address enter: 4\nTo change the E-mail enter: 5\nTo change the phone number enter:6\n");
        if (scanf("%d",&n))
        {
            switch (n)
            {
            case 1:
            {
                printf("\nEnter the new first name:\n");
labelFirstNameConfirmation:
                scanf(" %[^\n]s",T);                                                        //We wanted to give the user the freedom with naming, but we sticked with the sample text submitted
                for (i=0 ; i<strlen(T) ; i++)
                {
                    if ( (T[i]<32)  ||  (T[i]>32 && T[i]<45)  ||  (T[i]>45 && T[i]<65)  ||  (T[i]>90 && T[i]<97)  ||  (T[i]>122) )                //these are ascii codes for space and "-" as these are the only chars that can be put in a name in addition to [a-z]
                    {
                        printf ("\aYou entered an invalid First Name, please try again:\n");
                        goto labelFirstNameConfirmation;
                    }
                }
                strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].firstName,T);
                system("cls");
                printf("First name successfully modified\n");
                break;
            }
            case 2:
            {
                printf("\nEnter the new last name:\n");
labelLastNameConfirmation:
                scanf(" %[^\n]s",T);
                for (i=0 ; i<strlen(T) ; i++)
                {
                    if ( (T[i]<32)  ||  (T[i]>32 && T[i]<45)  ||  (T[i]>45 && T[i]<65)  ||  (T[i]>90 && T[i]<97)  ||  (T[i]>122) )
                    {
                        printf ("\aYou entered an invalid Last Name, please try again:\n");
                        goto labelLastNameConfirmation;
                    }
                }
                strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].lastName,T);
                system("cls");
                printf("Last name successfully modified\n");
                break;
            }
            case 3:
            {
                printf("\nEnter the Date of birth in the following format DD-MM-YYYY\n");
labelDOBConfirmation:
                scanf(" %[^\n]s",temporaryDate);
                for(i=0,counterDOBOfDashes=0; i<strlen(temporaryDate); i++)
                {
                    if (temporaryDate[i]=='-')
                        counterDOBOfDashes++;
                }
                if (temporaryDate[2]!='-' || temporaryDate[5]!='-' || counterDOBOfDashes!=2 || strlen(temporaryDate)!=10)                                     //CounterDOB condition is when user enters DOB in format other than DD-MM-YYYY that includes more that 2 dashes
                {
                    printf("We couldn't recognize the Date of Birth you entered, please enter it in this format only DD-MM-YYYY\n");
                    goto labelDOBConfirmation;
                }
                token = strtok(temporaryDate,"-");
                while (token!=NULL)
                {
                    if(j==3)
                        strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].DOB.days,token);
                    if(j==2)
                        strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].DOB.months,token);
                    if(j==1)
                        strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].DOB.year,token);
                    token=strtok(NULL,"-");
                    j--;
                }
                system("cls");
                printf("Date of birth successfully modified\n");
                break;
            }
            case 4:
            {
                printf("\nEnter the new address:\n");
                scanf(" %[^\n]s",tempModify);
                strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].address,tempModify);
                system("cls");
                printf("Address successfully modified\n");
                break;
            }
            case 5:
            {
                printf("\nEnter the new E-mail:\n");
labelEmailConfirmation:                                                                                       //This is a validation for when a user enters an email that contains more than one "@"
                scanf("%s",tempModify);
                for (i=0,counterEmailAt=0,counterEmailDot=0,indexOfAt=0,indexOfDot=0; i<strlen(tempModify) ; i++)
                {
                    if(tempModify[i] == '@')
                    {
                        counterEmailAt++;
                        indexOfAt=i;
                    }
                    if(tempModify[i]=='.')
                    {
                        counterEmailDot++;
                        indexOfDot = i;
                    }
                }
                //if(counterEmailAt!=1 || counterEmailDot<1 || (indexOfAt>indexOfDot && counterEmailDot>=1) || contacts[countLoad].email[0]=='@')    SAME CONDITIONS AS ADD CONTACT
                if(counterEmailAt!=1 || counterEmailDot<1 || tempModify[0]=='@' || (indexOfAt>indexOfDot && counterEmailDot>=1))    //No emails with :1*more than one @ sign 2*No dots 3*No dots after the one @ sign 4*@ sign at beginning of email
                {
                    printf("You entered a wrong email, please try again:\n");
                    goto labelEmailConfirmation;
                }

                strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].email,tempModify);
                system("cls");
                printf("E-mail successfully modified\n");
                break;
            }
            case 6:
            {
                printf("\nEnter the new Phone Number:\n");
labelPhoneNumberConfirmation:
                scanf(" %[^\n]s",T);
                for(i=0; i<strlen(T) ; i++)
                {
                    if( (T[i]<32)  ||  (T[i]>32&&T[i]<43)  ||  (T[i]>43&&T[i]<45)  ||  (T[i]>45&&T[i]<48)  || (T[i]>57) )       //these are ascii codes for space,"+" and "-" as these are the only chars that can be put in a phone number in addition to [0-9]
                    {
                        printf("You entered a wrong Phone Number, please try again:\n");
                        goto labelPhoneNumberConfirmation;
                    }
                }
                strcpy(contacts[countSearchResultsArray[indexOfFinalSearchResult]].phoneNumber,T);
                system("cls");
                printf("Phone number successfully modified\n");
                break;
            }
            default:
            {
                system("cls");
                printf("\a\n\n\nWe couldn't recognize your decision, please enter a valid number...\n\n\n");
                printElement(countSearchResultsArray[indexOfFinalSearchResult]);
                goto labelConfirmation;
                break;
            }
            }
            printf ("Do you want to modify anything else (y/n)\n");
labelSecondConfirmation:
            scanf(" %s",confirmation);
            if (strcasecmp(confirmation,"y")==0)
            {
                system("cls");
                printElement(countSearchResultsArray[indexOfFinalSearchResult]);
                goto labelConfirmation;
            }
            else if (strcasecmp(confirmation,"n")==0)
            {
                flagSave=0;
                returnMenu();
            }
            else
            {
                system("cls");
                printf("\a\n\n\nWe couldn't recognize your decision, enter y to modify the contact or n to return to menu\n\n\n");
                printElement(countSearchResultsArray[indexOfFinalSearchResult]);
                goto labelSecondConfirmation;
            }
        }

        else if (scanf("%s",wrongConfirmation))
        {
            system("cls");
            printf("\a\n\n\nWe couldn't recognize your decision, please enter a valid number...\n\n\n");
            printElement(countSearchResultsArray[indexOfFinalSearchResult]);
            goto labelConfirmation;
        }
    }
    else
    {
        returnMenu();
    }
}

void menu()
{
    system("cls");
    int n;
    char wrongConfirmation[50];
    printf ("\t\t\t\t<<<<<\tWelcome to the Phonebook application\t>>>>>\n\n\n\n\n\n");
    printf ("1-ADD CONTACT\n\n2-MODIFY CONTACT\n\n3-PRINT CONTACTS\n\n4-SEARCH CONTACTS\n\n5-DELETE CONTACT\n\n6-SAVE\n\n7-EXIT\n");
    if (scanf("%d",&n))
    {
        switch (n)
        {
        case 1:
        {
            system("cls");
            addContact();
            break;
        }
        case 2:
        {
            system("cls");
            modifyContact();
            break;
        }
        case 3:
        {
            system("cls");
            printList();
            break;
        }
        case 4:
        {
            system("cls");
            searchByLastName();
            returnMenu();
            break;
        }
        case 5:
        {
            system("cls");
            deleteContact();
            break;
        }
        case 6:
        {
            system("cls");
            save();
            break;
        }
        case 7:
        {
            system("cls");
            exitConfirmation();
            break;
        }
        default:
        {
            printf("\a");
            menu();
        }
        }
    }
    else if (scanf("%s",wrongConfirmation))
    {
        printf("\a");                       //\a Makes alert noise
        menu();
    }
}

void exitConfirmation()                                              //ensures that the user saves before exiting
{
    if (flagSave==1)
    {
        exit(0);
    }
    else if (flagSave==0)
    {
        char confirm[50];
        printf ("Any changes you made are not saved, are you sure you want to exit without saving?(y/n)\n");
labelSaveConfirmationValidation:
        scanf(" %s",&confirm);
        if(strcasecmp(confirm,"y")==0)
        {
            exit(0);
        }
        else if(strcasecmp(confirm,"n")==0)
        {
            returnMenu();
        }
        else
        {
            system("cls");
            printf("\aWe couldn't recognize your decision, please try again...\nEnter y to exit\nEnter n to return to menu\n");
            goto labelSaveConfirmationValidation;
        }
    }
}

int main()
{
    load();
    menu();
    return 0;
}

