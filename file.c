#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *adb) 
{
    FILE *fptr=fopen("file.csv","w");
    if(fptr==NULL)
    {
        printf("Fopen Failed\n");
        return ;
    }
    printf("File opened succesfully\n");
    fprintf(fptr,"#%d\n",adb->contactCount);
    for(int i=0;i<adb->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
        //for saving the contacts to a csv.file for again getting the data
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *adb) 
{
    FILE *fptr=fopen("file.csv","r");
    if(fptr==NULL)
    {
        printf("Fopen Failed\n");
        return ;
    }
    printf("File opened succesfully\n");
    fscanf(fptr,"#%d\n",&adb->contactCount);
    for(int i=0;i<adb->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%s\n",adb->contacts[i].name,adb->contacts[i].phone,adb->contacts[i].mail);
        //for new execution ,the already saved contacts in the file will be loaded so we can access them
    }
    fclose(fptr);
    
    
}
