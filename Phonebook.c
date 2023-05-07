#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct
{
    char months[20];
    char year[5];
} date;
typedef struct
{
    char ISBN[50];
    char title [50];
    char author[50];
    char quantity[50];
    char price[50];
    date published;
} book;
typedef struct
{
    char username [50];
    char password [50];

} user;

book tempbook[100];
user users[100];
int usercount=0;
int tempBookCount=0;
int saveFlag=0;
int logOutflag;
int foundFlag=0;



void exitConfirm();
void addBook();
void modifyBook();
int searchBook();
void deleteBook();
void save();
void menu();
void loadCredentials();
void load();
char *changemonth();
void advanced_search();
void sortbyprice();
void sortbytitle();
void sortbydate();
void printbooks();



void loadCredentials()
{



    FILE*f=fopen("credentials.txt","r");
    if(f==NULL)
        printf("file is not found");
    else
    {
        while(!feof(f))
        {
            fscanf(f,"%[^\n]\n",users[usercount].username);
            fscanf(f,"%[^\n]\n",users[usercount].password);
            usercount++;
        }
    }
    fclose(f);


}
void login()
{
    int choice,n;
    char u[50];
    char p[50];
    int ok;
    while(1)
    {
        printf("Enter 1 to login OR 2 to quit:");
        scanf("%d",&choice);
        ok=1;
        if(choice==2)
            {
                printf("\n\n\n\t\t\t\t<<<<<\tBye!\t>>>>>\n\n\n");
                exit(1);
            }
        else if(choice==1)
        {

            printf("Enter your username:\n");
            scanf("%s",u);
            printf("Enter your password\n");
            scanf("%s",p);


            for(n=0; n<100; n++)
            {
                if(strcmp(users[n].username,u)==0&&strcmp(users[n].password,p)==0)
                {

                    load();
                    logOutflag=1;
                    ok=0;
                    system("cls");
                    printf("\n\n\n\t\t\t\t\t<<<<<Welcome!>>>>>\n\n\n");
                    while(logOutflag)
                        {
                              menu();
                        }

                }
            }
            if(ok==1)
            {
            printf("Username or Password is incorrect\n");
            }
        }
        printf("\n");
    }

}
void load()
{


    FILE *fp;
    fp=fopen("books.txt","r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%[^,],",tempbook[tempBookCount].ISBN);
            fscanf(fp,"%[^,],",tempbook[tempBookCount].title);
            fscanf(fp,"%[^,],",tempbook[tempBookCount].author);                          //In [^-]- the stopping delimiter is "-"
            fscanf(fp,"%[^,],",tempbook[tempBookCount].quantity);                             //In [^,], the stopping delimiter is ","
            fscanf(fp,"%[^,],",tempbook[tempBookCount].price);                               //In [^\n]\n the stopping delimiter is "\n"
            fscanf(fp,"%[^-]-",tempbook[tempBookCount].published.months);
            fscanf(fp,"%[^\n]\n",tempbook[tempBookCount].published.year);
            tempBookCount++;
        }

        fclose(fp);
    }
    else
        printf("FILE NOT FOUND!") ;

}
char *changemonth(const char *x)
{

    if(strcmp(x,"1")==0)
    {
        return "January";
    }
    if(strcmp(x,"2")==0)
    {
        return "February";
    }
    if(strcmp(x,"3")==0)
    {
        return "March";
    }
    if(strcmp(x,"4")==0)
    {
        return "April";
    }
    if(strcmp(x,"5")==0)
    {
        return "May";
    }
    if(strcmp(x,"6")==0)
    {
        return "June";
    }
    if(strcmp(x,"7")==0)
    {
        return "July";
    }
    if(strcmp(x,"8")==0)
    {
        return "August";
    }
    if(strcmp(x,"9")==0)
    {
        return "September";
    }
    if(strcmp(x,"10")==0)
    {
        return "October";
    }
    if(strcmp(x,"11")==0)
    {
        return "November";
    }
    if(strcmp(x,"12")==0)
    {
        return "December";
    }
}
void advanced_search()
{
    char x[20];
    int j;
    int flag=0;

    printf("Enter Keyword:");
    gets(x);
    printf("Search results:\n");


    for(j=0; j<tempBookCount; j++)
    {
        char *p=strstr(tempbook[j].title,x);

        if(p!=NULL)
        {
            flag=1;
            printf("ISBN:%s\n",tempbook[j].ISBN);
            printf("Title:%s\n",tempbook[j].title);
            printf("Author:%s\n",tempbook[j].author);
            printf("Quantity:%s\n",tempbook[j].quantity);
            printf("Price:%s\n",tempbook[j].price);
            printf("Published:%s %s\n",changemonth(tempbook[j].published.months),tempbook[j].published.year);
            printf("-----------------------------------------\n"); }

    }

    if(flag==0)
    {
        printf("Doesn't match,not found\n");
    }


}

void sortbyprice()
{
    book temp ;
    int j,l,k;
    for(j=0; j<tempBookCount; j++)
    {
        for(l=j+1; l<tempBookCount; l++)
        {
            if(atof(tempbook[j].price)>atof(tempbook[l].price)) //changes the string of float to float type
            {
                temp = tempbook[j];
                tempbook[j] = tempbook[l];
                tempbook[l] = temp ;
            }
        }
    }
    for(k=0; k<tempBookCount; k++)
    {
        printf("ISBN:%s\n",tempbook[k].ISBN);
        printf("Title:%s\n",tempbook[k].title);
        printf("Author:%s\n",tempbook[k].author);
        printf("Quantity:%s\n",tempbook[k].quantity);
        printf("Price:%s\n",tempbook[k].price);
        printf("Published:%s %s\n",changemonth(tempbook[k].published.months),tempbook[k].published.year);
        printf("-----------------------------------------\n"); }
  }
void sortbytitle()
{
    book temp ;
    int k,j,n;
    for(k=0; k<tempBookCount; k++)
    {
        for(j=k+1; j<tempBookCount; j++)
        {
            if(strcmp(tempbook[k].title,tempbook[j].title)==1)
            {
                temp=tempbook[k];
                tempbook[k]=tempbook[j];
                tempbook[j]=temp;
            }
        }
    }

    for(n=0; n<tempBookCount ;n++)
    {
        printf("ISBN:%s\n",tempbook[n].ISBN);
        printf("Title:%s\n",tempbook[n].title);
        printf("Author:%s\n",tempbook[n].author);
        printf("Quantity:%s\n",tempbook[n].quantity);
        printf("Price:%s\n",tempbook[n].price);
        printf("Published:%s-%s\n",changemonth(tempbook[n].published.months),tempbook[n].published.year);
        printf("-----------------------------------------\n");
    }
}
void sortbydate()
{
    book temp ;
    int j,l;

    for(j=0; j<tempBookCount; j++)
    {
        for(l=j+1; l<tempBookCount; l++)
        {
            if(strcmp(tempbook[j].published.year,tempbook[l].published.year)==0)
            {

                if(strcmp(tempbook[j].published.months,tempbook[l].published.months)==-1)
                {

                    temp = tempbook[j];
                    tempbook[j] = tempbook[l];
                    tempbook[l] = temp ;
                }

            }
            else if(strcmp(tempbook[j].published.year,tempbook[l].published.year)==-1)
            {

                temp = tempbook[j];
                tempbook[j] = tempbook[l];
                tempbook[l] = temp ;
            }
        }
    }

    int k;
    for(k=0; k<tempBookCount; k++)
    {
        printf("ISBN:%s\n",tempbook[k].ISBN);
        printf("Title:%s\n",tempbook[k].title);
        printf("Author:%s\n",tempbook[k].author);
        printf("Quantity:%s\n",tempbook[k].quantity);
        printf("Price:%s\n",tempbook[k].price);
        printf("Published:%s %s\n",changemonth(tempbook[k].published.months),tempbook[k].published.year);
        printf("-----------------------------------------\n"); }
}
void printbooks()
{
    int n,loopFlag=1;
while(loopFlag){
printf ("1-Sort by Title\n\n2-Sort by Date\n\n3-Sort by Price\n\n4-Menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        system("cls");
        sortbytitle();
        break;
    }
    case 2:
    {
        system("cls");
        sortbydate();
        break;
    }
    case 3:
    {
        system("cls");
        sortbyprice();
        break;
    }
    case 4:
    {
        system("cls");
        loopFlag=0;
        break;
    }
    }
    }


}

/////////////////////////////
void advanced_searchOptions()
{
    int loopFlag=1;
   int n;
   advanced_search();
  while(loopFlag)
  {


    printf ("1-Another Search\n\n2-Menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        advanced_search();
        break;
    }
    case 2:
    {
        loopFlag=0;
        system("cls");
        break;
    }
    }
  }
}
void searchBookOptions()
{
    int loopFlag=1;
   int n;
   searchBook();
  while(loopFlag)
  {


    printf ("1-Another Search\n\n2-Menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        searchBook();
        break;
    }
    case 2:
    {
        loopFlag=0;
        system("cls");
        break;
    }
    }
  }
}
void addBookOptions()
{
    int loopFlag=1;
   int n;
   addBook();
  while(loopFlag)
  {


    printf ("1-Add Another Book\n\n2-Menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        addBook();
        break;
    }
    case 2:
    {
        loopFlag=0;
        system("cls");
        break;
    }
    }
  }
}
void deleteBookOptions()
{
    int loopFlag=1;
   int n;
   deleteBook();
  while(loopFlag)
  {


    printf ("1-Delete Another Book\n\n2-Menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        deleteBook();
        break;
    }
    case 2:
    {
        loopFlag=0;
        system("cls");
        break;
    }
    }
  }
}
///////////////////////////

int validateISBNsecurity(const char *s)
{
  int i;
  for(i=0;i<100;i++)
  {
      if(strcmp(tempbook[i].ISBN,s)==0)
      {
          printf("Error:Invalid ISBN Already in Use!\n");
          return 0;
      }
  }
   return 1;
}
int validateISBNsize(const char *s)
{
    if(strlen(s)==13)
    {
        return 1;
    }
    else
    {
        printf("Error:Enter 13 digit Only,Try Again..\n");
        return 0;
    }

}
int  validateNumber(const char *s)
{
    while (*s)
    {
        if (isdigit(*s++) == 0)
        {
            printf("Error:Enter Numbers Only,Try Again..\n");
            return 0;
        }
    }

    return 1;
}
int  validatePrice(const char *s)
{
    int dotFlag=0;
    if(s[0]=='.')
    {
        printf("Error:Enter Correct Price,Try Again..\n");
        return 0;
    }
    while (*s)
    {
        if(*s=='.')
        {
            dotFlag++;
            s++;
        }
        else if (isdigit(*s++) == 0)
        {
            printf("Error:Enter Numbers Only,Try Again..\n");
            return 0;
        }
        else if (dotFlag>1)
        {
            printf("Error:Enter Correct Price,Try Again..\n");
            return 0;
        }
    }
    if(s[strlen(s)-1]=='.')
    {
        printf("Error:Enter Correct Price,Try Again..\n");
        return 0;
    }
    return 1;
}
int validateMonth(const char *s)
{
    if(strcmp(s,"1")==0||strcmp(s,"2")==0||strcmp(s,"3")==0||strcmp(s,"4")==0||strcmp(s,"5")==0||strcmp(s,"6")==0||strcmp(s,"7")==0||strcmp(s,"8")==0||strcmp(s,"9")==0||strcmp(s,"10")==0||strcmp(s,"11")==0||strcmp(s,"12")==0)
    {
        return 1;
    }
    else
    {
        printf("Error:Enter Correct Month Number(e.g Correct format '12')\n");
        return 0;
    }
}
int validateYear(const char *s)
{

    if(validateNumber(s)&&strlen(s)==4)
    {
        return 1;
    }
    else
    {
        if(strlen(s)!=4)
        {
            printf("Error:Enter a valid year Number e.g(1987)\n");
        }
        return 0;
    }

}


void addNewISBN(int index)
{

    char ISBNcheck[50];
    printf("Enter New ISBN\n");
validISBN:
    scanf("%[^\n]%*c", ISBNcheck);
    if(validateNumber(ISBNcheck) && validateISBNsize(ISBNcheck)&&validateISBNsecurity(ISBNcheck))
    {
        strcpy(tempbook[index].ISBN,ISBNcheck);
    }
    else
    {
        goto validISBN;
    }

}
void addNewTitle(int index)
{
    char titleCheck[50];
    printf("Enter New Title:\n");
    scanf("%[^\n]%*c", titleCheck);
    strcpy(tempbook[index].title,titleCheck);
}
void addNewAuthor(int index)
{

    char authorCheck[50];
    printf("Enter New Author:\n");
    scanf("%[^\n]%*c", authorCheck);
    strcpy(tempbook[index].author,authorCheck);

}
void addNewQuantity(int index)
{

    char quantityCheck[50];
    printf("Enter New Quantity:\n");
validQuantity:
    scanf("%[^\n]%*c", quantityCheck);
    if(validateNumber(quantityCheck))
    {
        strcpy(tempbook[index].quantity,quantityCheck);
    }
    else
    {
        goto validQuantity;
    }

}
void addNewPrice(int index)
{
    char priceCheck[50];
    printf("Enter New Price:\n");
validPrice:
    scanf("%[^\n]%*c", priceCheck);
    if(validatePrice(priceCheck))
    {
        strcpy(tempbook[index].price,priceCheck);
    }
    else
    {
        goto validPrice;
    }

}
void addNewDate(int index)
{
    char publishedCheckMonth [50];
    char publishedCheckYear [50];

    printf("Enter New Date(Month):\n");
validDate:
    scanf("%s",publishedCheckMonth);
    if(validateMonth(publishedCheckMonth))
    {
        strcpy(tempbook[index].published.months,publishedCheckMonth);
    }
    else
    {
        goto validDate;
    }
    printf("Enter New Date(Year)\n");
validyear:
    scanf("%s",publishedCheckYear);
    if(validateYear(publishedCheckYear))
    {
        strcpy(tempbook[index].published.year,publishedCheckYear);
    }
    else
    {
        goto validyear;
    }

}


void addISBN()
{

    char ISBNcheck[50];
    printf("Enter ISBN\n");
validISBN:
    scanf("%[^\n]%*c", ISBNcheck);
    if(validateNumber(ISBNcheck) && validateISBNsize(ISBNcheck)&&validateISBNsecurity(ISBNcheck))
    {
        strcpy(tempbook[tempBookCount].ISBN,ISBNcheck);
    }
    else
    {
        goto validISBN;
    }

}
void addTitle()
{
    char titleCheck[50];
    printf("Enter Title:\n");
    scanf("%[^\n]%*c", titleCheck);
    strcpy(tempbook[tempBookCount].title,titleCheck);
}
void addAuthor()
{

    char authorCheck[50];
    printf("Enter Author:\n");
    scanf("%[^\n]%*c", authorCheck);
    strcpy(tempbook[tempBookCount].author,authorCheck);

}
void addQuantity()
{

    char quantityCheck[50];
    printf("Enter Quantity:\n");
validQuantity:
    scanf("%[^\n]%*c", quantityCheck);
    if(validateNumber(quantityCheck))
    {
        strcpy(tempbook[tempBookCount].quantity,quantityCheck);
    }
    else
    {
        goto validQuantity;
    }

}
void addPrice()
{
    char priceCheck[50];
    printf("Enter Price:\n");
validPrice:
    scanf("%[^\n]%*c", priceCheck);
    if(validatePrice(priceCheck))
    {
        strcpy(tempbook[tempBookCount].price,priceCheck);
    }
    else
    {
        goto validPrice;
    }

}
void addDate()
{
    char publishedCheckMonth [50];
    char publishedCheckYear [50];


    printf("Enter Date(Month):\n");
validDate:
    scanf("%s",publishedCheckMonth);
    if(validateMonth(publishedCheckMonth))
    {
        strcpy(tempbook[tempBookCount].published.months,publishedCheckMonth);
    }
    else
    {
        goto validDate;
    }
    printf("Enter Date(Year)\n");
validyear:
    scanf("%s",publishedCheckYear);
    if(validateYear(publishedCheckYear))
    {
        strcpy(tempbook[tempBookCount].published.year,publishedCheckYear);
    }
    else
    {
        goto validyear;
    }

}
void addBook()
{
    saveFlag=0;
    addISBN();
    addTitle();
    addAuthor();
    addQuantity();
    addPrice();
    addDate();
    printf("Successfully Added Book!\n");
    ++tempBookCount;
    //1234567543212

};
int searchBook()
{
    int i;
    char ISBNcheck[50];
    printf("Enter Book ISBN you want to search for\n");
    scanf("%[^\n]%*c", ISBNcheck);
    for(i=0; i<100; i++)
    {
        if(strcmp(ISBNcheck,tempbook[i].ISBN)==0)
        {
            foundFlag=1;
            printf("Book found!\n");
            printf("ISBN:%s\n",tempbook[i].ISBN);
            printf("Title:%s\n",tempbook[i].title);
            printf("Author:%s\n",tempbook[i].author);
            printf("Quantity:%s\n",tempbook[i].quantity);
            printf("Price:%s$\n",tempbook[i].price);
            printf("Published:%s %s\n",changemonth(tempbook[i].published.months),tempbook[i].published.year);
            return i;
            break;
        }
    }

    foundFlag=0;
    printf("Book not found!\n");
}
void modifyBook()
{
    int loopFlag=1;
    int index,n;
    index=searchBook();
    if(foundFlag==1)
    {
    while(loopFlag)
    {
    printf("What do you want to modify?\n");
    printf ("1-ISBN\n\n2-Title\n\n3-Author\n\n4-Quantity\n\n5-Price\n\n6-Date\n\n7-menu\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        system("cls");
        addNewISBN(index);
        saveFlag=0;
        printf("Successfully updated ISBN!\n");
        break;
    }
    case 2:
    {
        system("cls");
        addNewTitle(index);
          saveFlag=0;
        printf("Successfully updated Title!\n");
        break;
    }
    case 3:
    {
        system("cls");
        addNewAuthor(index);
          saveFlag=0;
        printf("Successfully updated Author!\n");
        break;
    }
    case 4:
    {
        system("cls");
        addNewQuantity(index);
          saveFlag=0;
        printf("Successfully updated Quantity!\n");
        break;
    }
    case 5:
    {
        system("cls");
        addNewPrice(index);
          saveFlag=0;
        printf("Successfully updated Price!\n");
        break;
    }
    case 6:
    {
        system("cls");
        addNewDate(index);
          saveFlag=0;
        printf("Successfully updated Date!\n");
        break;
    }
    case 7:
    {

      system("cls");
      loopFlag=0;
    }
    }
    }
    }
}
void deleteBook()
{

    int index,i;
    index=searchBook();
    if(foundFlag==1)
    {
    saveFlag=0;
    for(i=index; i<tempBookCount; i++)
    {
        tempbook[i]=tempbook[i+1];
    }
    --tempBookCount;
    printf("Successfully Deleted Book\n");
    }
}
void save()
{
    saveFlag=1;

    FILE *fs;
    fs=fopen("books.txt","w");                                         // file call is the string that scans the name of the file the user loaded from
    int i ;
    for (i=0; i<tempBookCount; i++)
    {
        fprintf(fs,"%s,",tempbook[i].ISBN);
        fprintf(fs,"%s,",tempbook[i].title);
        fprintf(fs,"%s,",tempbook[i].author);
        fprintf(fs,"%s,",tempbook[i].quantity);
        fprintf(fs,"%s,",tempbook[i].price);
        fprintf(fs,"%s-",tempbook[i].published.months);
        fprintf(fs,"%s\n",tempbook[i].published.year);

    }
    fclose(fs);
    printf("Saved Successfuly!\n");

};
void exitConfirm()
{
    if (saveFlag==1)
    {
        logOutflag=0;
    }
    else if (saveFlag==0)
    {
        char confirm;
        printf ("Any changes you made are not saved, are you sure you want to exit without saving?(y/n)\n");
saveConfirm:
        scanf("%c",&confirm);
        getchar();
        if(confirm=='y')
        {
            system("cls");
            logOutflag=0;
        }
        else if(confirm=='n')
        {
            menu();
        }
        else
        {
            system("cls");
            printf("\aCouldn't recognize decision, please try again...\nEnter y to exit\nEnter n to return to menu\n");
            goto saveConfirm;
        }
    }
}
void exitConfirm2()
{
    if (saveFlag==1)
    {
        system("cls");
        printf("\n\n\n\t\t\t\t<<<<<\tBye!\t>>>>>\n\n\n");
        exit(1);
    }
    else if (saveFlag==0)
    {
        char confirm;
        printf ("Any changes you made are not saved, are you sure you want to exit without saving?(y/n)\n");
saveConfirm:
        scanf("%c",&confirm);
        getchar();
        if(confirm=='y')
        {
            system("cls");
        printf("\n\n\n\t\t\t\t<<<<<\tBye!\t>>>>>\n\n\n");
            exit(1);
        }
        else if(confirm=='n')
        {
            menu();
        }
        else
        {
            system("cls");
            printf("\aCouldn't recognize decision, please try again...\nEnter y to exit\nEnter n to return to menu\n");
            goto saveConfirm;
        }
    }
}
void menu()
{
    //system("cls");
    int n;

    printf ("\t\t\t\t<<<<<Library Management System\t>>>>>\n\n\n\n\n\n");
    printf ("1-ADD BOOk\n\n2-MODIFY Book\n\n3-SEARCH BOOKS\n\n4-DELETE BOOk\n\n5-SAVE\n\n6-Advanced Search\n\n7-Print Books\n\n8-Refresh Screen\n\n9-Log Out\n\n10-Exit Program\n\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        system("cls");
        addBookOptions();
        break;
    }
    case 2:
    {
        system("cls");
        modifyBook();
        break;
    }
    case 3:
    {
        system("cls");
        searchBookOptions();
        break;
    }
    case 4:
    {
        system("cls");
        deleteBookOptions();
        break;
    }
    case 5:
    {
        system("cls");
        save();
        break;
    }
    case 6:
    {
        system("cls");
        advanced_searchOptions();
        break;
    }
     case 7:
    {
        system("cls");
        printbooks();
        break;
    }
     case 8:
    {
        system("cls");
        break;
    }
     case 9:
    {
        system("cls");
        exitConfirm();
        break;
    }
    case 10:
    {
        system("cls");
        exitConfirm2();
        break;
    }
    default:
    {
        menu();
        break;
    }
    }

}
int  main()
{

     loadCredentials();
     login();

    return 0;
}
