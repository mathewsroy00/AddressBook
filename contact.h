#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[100];
    int contactCount;
};

void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *AddressBook);

int validate_phone(struct AddressBook *addressBook, char* mob);
int validate_email(struct AddressBook *addressBook, char* email);

void search_by_name(struct AddressBook *addressBook);
int name_search(struct AddressBook *addressBook);
int phone_search(struct AddressBook *addressBook);
int email_search(struct AddressBook *addressBook);

void edit_field(struct AddressBook *addressBook, int index);
void edit_field_name(struct AddressBook *addressBook, int contact_index);
void edit_field_phone(struct AddressBook *addressBook, int contact_index);
void edit_field_email(struct AddressBook *addressBook, int contact_index); 
void display_edited_contact(struct AddressBook *addressBook, int contact_index);

void contact_delete(struct AddressBook *addressBook, int index);
#endif
