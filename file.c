/*
Name: Mathews Roy
Date: 10-10-2025
Description: 
            * Implementation of addressBook contact functions
            * Includes Create contact, search contact , edit contact and delete contact function
            * Validates mobile number and email for ensuring proper format and uniqueness
            * Data will be stored in files using file handling
            * Contacts will be displayed in a structured manner
            * Handles multiple contacts with same name during search , edit and delete
*/

#include <stdio.h>
#include "file.h"

void saveContactsToFile(struct AddressBook *addressBook) 
{
       FILE* fp = fopen("contacts.csv", "w");
       if(fp == NULL)
       {
            printf("File is not opened\n");
            return;
       }
       fprintf(fp, "#%d\n", addressBook -> contactCount); 

       for(int i = 0; i < addressBook -> contactCount; i++)
       {
            fprintf(fp, "%s,%s,%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook-> contacts[i].email);
       }
       fclose(fp);
}

void loadContactsFromFile(struct AddressBook *addressBook) 
{
    FILE* fp = fopen("contacts.csv", "r");
    if(fp == NULL)
    {
        printf("File is not available\n");
        return;
    }
    fscanf(fp,"#%d",&addressBook -> contactCount);
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fscanf(fp," %[^,],%[^,],%[^\n]\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
    fclose(fp);
}
