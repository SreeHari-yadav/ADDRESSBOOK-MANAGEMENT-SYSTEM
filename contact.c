#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *adb) 
{
    Contact temp;
    for(int i=0;i<adb->contactCount-1;i++)
    {
        for(int j=0;j<adb->contactCount-1-i;j++)
        {
            //for listing the contacts based on alphabetical order
            if(strcmp(adb->contacts[j].name,adb->contacts[j+1].name)>0)
            {
                temp=adb->contacts[j];
                adb->contacts[j]=adb->contacts[j+1];
                adb->contacts[j+1]=temp;
            }
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("\n%-5s %-20s %-15s %-30s\n","S.NO","NAME","PHONE NO","MAIL ID");
    printf("\n---------------------------------------------------------------------\n");
    for(int i=0;i<adb->contactCount;i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",i+1, adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
    }

    printf("\n---------------------------------------------------------------------\n");
    
}

void initialize(AddressBook *adb) {
    adb->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(adb);
}

void saveAndExit(AddressBook *adb) {
    saveContactsToFile(adb); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *str)
{
   for(int i=0;str[i];i++)
   {
        //for validating name 
        if(!((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122) || str[i]==' '||str[i]=='.'))
        {
            return 0;
        }
   }

    return 1; //
}

int validate_phone(char *str)
{
    //for validating mobile number
    int len=strlen(str);
    if(len!=10)
    {
        return 0;
    }
    for(int i=0;str[i];i++)
    {
        if(!((str[i]>=48 && str[i]<=57)))
        {
            return 0;
        }
   }
    return 1;
}

int validate_mail(char *str)
{
    //for validating mail
    int ind=-1;
    if(str[0]>=48 && str[0]<=57)
    {
        return 0;
    }
    for(int i=0;str[i];i++)
    {
        if(str[i]=='@')
        {
            ind=i;
            break;
        }
    }

    if(ind <=0)
    {
        return 0;
    }

    for(int i=0;i<ind;i++)
    {
        if(!((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90) ||(str[i]>=97 && str[i]<=122) || str[i]=='_'))
        {
            return 0;
        }
    }

    if(strstr(str,".com")==NULL)
    {
        return 0;
    }

    char *ptr=strstr(str,".com");
    if(ptr==NULL)
    {
        return 0;
    }
    char *str2=strchr(str,'@');
    if(str2==NULL)
    {
        return 0;
    }
    if(ptr<=str2+1)
    {
        return 0;
    }

    return 1;
}

int uniquness_phone(AddressBook *adb,char *str)
{
    //for checking the entered number is already present in our data or not
    for(int i=0;i<adb->contactCount;i++)
    {
        if(strcmp(adb->contacts[i].phone,str)==0)
        {
            return 0;
        }
    }
    return 1;
}

int uniquness_mail(AddressBook *adb,char *str)
{
    //for checking the entered mail is already present in our data or not
    for(int i=0;i<adb->contactCount;i++)
    {
        if(strcmp(adb->contacts[i].mail,str)==0)
        {
            return 0;
        }
    }
    return 1;
}


void createContact(AddressBook *adb)
{
	/* Defining  the logic to create a Contacts */
    int res;
    char str1[30], str2[11], str3[30];

    do
    {
        printf("Enter the name :");
        scanf(" %[^\n]",str1);
        res = validate_name(str1);
        
        if(res==0)
        {
            printf("**Please enter valid name...**\n");
        }
    }while(res == 0);
     
    do
    {
        printf("Enter the phone number :");
        scanf(" %[^\n]", str2);

        res = validate_phone(str2);
        if(res==0)
        {
            printf("**Please enter valid phone number...**\n");
        }
        else if(uniquness_phone(adb,str2)==0)
        {
            printf("**Phone number already exist so give another..**\n");
            res=0;
        }
    }while(res == 0);


    do
    {
        printf("Enter the mail:");
        scanf("  %[^\n]",str3);

        res = validate_mail(str3);
        if(res==0)
        {
            printf("**Please enter valid mail...**\n");
        }
        else if(uniquness_mail(adb,str3)==0)
        {
            printf("**mail already exist so give another..**\n");
            res=0;
        }
    }while(res == 0);

    //for creating contact into our data 
    int ind = adb->contactCount;
    strcpy(adb->contacts[ind].name, str1);
    strcpy(adb->contacts[ind].phone, str2);
    strcpy(adb->contacts[ind].mail, str3);

    adb->contactCount++;
    printf("                         \n");
    printf("##Contact created succesfully..");

}

int search_by_name(AddressBook *adb)
{
    char name[50];
    int ind=-1;
    int flag=0,c=0;
    printf("Enter name to search:");
    scanf("  %[^\n]",name);
    for(int i=0;i<adb->contactCount;i++)
    {
        //for searching a user entered name present in our data and printing contact
        if(strcmp(adb->contacts[i].name,name)==0)
        {
            flag=1;
            printf("%d.",c+1);
            printf("Name : %s   Phone : %s   Email : %s\n",adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
            ind=i;
            c++;
        }
    }
    if(c>1)
    {
        ind=search_by_phone(adb);
    }
    if(flag==0)
    {
        printf("#Contact not found...");
    }
    return ind;
}


int search_by_phone(AddressBook *adb)
{
    char phone[20];
    printf("Enter phone number to search:");
    scanf(" %[^\n]",phone);
    for(int i=0;i<adb->contactCount;i++)
    {
        //for searching a user entered mobile number present in our data and printing contact
        if(strcmp(adb->contacts[i].phone,phone)==0)
        {
            printf("Name : %s   Phone : %s   Email : %s\n",adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
            return i;
        }
    }
    printf("#contact not found\n");
    return -1;
    

}

int search_by_mail(AddressBook *adb)
{
    char mail[20];
    printf("Enter mail to search:");
    scanf(" %[^\n]",mail);
    for(int i=0;i<adb->contactCount;i++)
    {
        //for searching a user entered mail present in our data and printing contact
        if(strcmp(adb->contacts[i].mail,mail)==0)
        {
            printf("Name : %s   Phone : %s   Email : %s\n",adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
            return i;
        }
    }
    printf("#contact not found\n");
    return -1;
    
}


void searchContact(AddressBook *adb) 
{
    /* Define the logic for search */

    int choise;
    printf("1.Name\n2.phone\n3.mail\nentrer your choice:");

    scanf(" %d", &choise);
    //reading choice from user for searching contact based on different options
    switch(choise)
    {
        case 1:
            search_by_name(adb);
            break;
        case 2:
            search_by_phone(adb);
            break;
        case 3:
            search_by_mail(adb);
            break;
        case 4:
            return;
        default:
            printf("**invalid choice**");
    }

}

void editby_name(int ind,AddressBook *adb)
{
    int res;
    char s[50];
    do
    {
        printf("Enter new name :");
        scanf(" %[^\n]", s);

        res = validate_name(s);
        if(res==0)
        {
            printf("**Please enter valid name...**\n");
        }
        else
        {
            strcpy(adb->contacts[ind].name,s);//for editing the name of contact 
            printf("  \n");
            printf("#name edited successfully\n");

        }
    }while(res == 0);
}

void editby_phone(int ind,AddressBook *adb)
{
    int res;
    char p[50];
    do
    {
        printf("Enter the phone number:");
        scanf(" %[^\n]", p);

        res = validate_phone(p);
        if(res==0)
        {
            printf("**Please enter valid phone number...**");
        }
        else if(uniquness_phone(adb,p)==0)
        {
            printf("## Phone number  already exist..");
            res=0;
        }
        else
        {
            strcpy(adb->contacts[ind].phone,p);////for editing the mobile number of contact 
            printf("  \n");
            printf("#phone number edited successfully\n");

        }
    }while(res == 0);
}

void editby_mail(int ind,AddressBook *adb)
{
    int res;
    char m[50];
    do
    {
        printf("Enter the mail:");
        scanf(" %[^\n]", m);

        res = validate_mail(m);
        if(res==0)
        {
            printf("**Please enter valid mail...**\n");
        }
        else if(uniquness_mail(adb,m)==0)
        {
            printf("## Mail already exist..");
            res=0;
        }
        else
        {
            strcpy(adb->contacts[ind].mail,m);//for editing the mail of contact 
            printf("  \n");
            printf("#mail  edited successfully\n");

        }
    }while(res == 0);
}


void editContact(AddressBook *adb)
{
    int choise,ind=-1;
    printf("1.name\n2.phone\n3.mail\nentrer your choice:");

    scanf("%d", &choise);

    switch(choise)
    {
        case 1:
            ind=search_by_name(adb);
            break;
        case 2:
            ind=search_by_phone(adb);
            break;
        case 3:
            ind=search_by_mail(adb);
            break;
        case 4:
            return;
        default:
            printf("**invalid choice**");
    }
    if(ind==-1)
    {
        return;
    }
    printf("1.name\n2.phone\n3.mail\nenter the field to edit:\n ");
    int num;
    scanf("%d",&num);
    switch(num)
    {
        case 1:
            editby_name(ind,adb);
            break;
        case 2:
            editby_phone(ind,adb);
            break;
        case 3:
            editby_mail(ind,adb);
            break;
        default:
            printf("**Invalid choice**");
    }
	
    
}

void deleteContact(AddressBook *adb)
{

    int choise,ind=-1;
    printf("1.name\n2.phone\n3.mail\nentrer your choice:");

    scanf("%d", &choise);
    //reading choice from the user to delete contact based on different options
    switch(choise)
    {
        case 1:
            ind=search_by_name(adb);
            break;
        case 2:
            ind=search_by_phone(adb);
            break;
        case 3:
            ind=search_by_mail(adb);
            break;
        case 4:
            return;
        default:
            printf("**invalid choice**");
    }
    if(ind==-1)
    {
        printf("#Nothing found to delete");
        return;
    }
    for(int i=ind; i<adb->contactCount-1; i++)
    {
        adb->contacts[i]=adb->contacts[i+1];
    }
    adb->contactCount--;
    printf("  \n");
    printf("#Contact successfully deleted\n");
}
