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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(struct AddressBook *addressBook) // Function Definition to list contacts
{
    /* Define the logic for print the contacts */
	printf("\t\t--- Contacts List ---\n\n");
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		printf("\t.........................................\n");
		printf("\n\tContact %d:\n", i + 1);

		printf("\n\tName     : %s\n", addressBook->contacts[i].name);
		printf("\tPhone no : %s\n", addressBook->contacts[i].phone);
		printf("\tEmail    : %s\n\n", addressBook->contacts[i].email);
	}
		printf("\t..........................................\n");
}

void initialize(struct AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(struct AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(struct AddressBook *addressBook) // Function definition for create contact
{
    /* Define the logic to create a Contacts */
	char temp_name[50];
	char temp_mob[20];
	char temp_email[50];

	// For getting name
	printf("\nEnter the name: ");
	scanf(" %[^\n]",temp_name);

	// For getting phone number
	do
	{
		printf("\nEnter the mobile number: ");
		scanf(" %[^\n]",temp_mob);
	}while(validate_phone(addressBook, temp_mob) == 0); // Function call for phone number validation

	// For getting email
	do
	{
		printf("\nEnter the email: ");
		scanf(" %[^\n]", temp_email);
	}while(validate_email(addressBook, temp_email) == 0); // Function call for email validation

	// Copying into array after all the inputs are valid
	strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);
	strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_mob);
	strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);

	printf(":::Contact created successfully:::\n");
    addressBook->contactCount++;	// incrementing total contactcount after adding contact
}

int validate_phone(struct AddressBook *addressBook, char* mob) // Subfunction for validating phone number
{
	if(strlen(mob) != 10) // Checking the length of string is 10
	{
		printf("\n>>>> Phone number should contain 10 digits <<<<\n\n");
		return 0;
	}

	int i = 0;
	while(mob[i] != '\0')
	{
		if((isdigit(mob[i]) == 0)) // check if digit or not
		{
			printf("\n>>>> Phone number should contain digits only <<<<\n\n");
			return 0;
		}
		i++;
	}

	for(int i = 0; i < addressBook -> contactCount; i++) // unique check
	{
		if(!(strcmp(addressBook -> contacts[i].phone, mob))) // if it exist strcmp will return 0 else non-zero value
		{
			printf("\n>>>> Phone number already exist! <<<<\n\n");
			return 0;
		}
	}
	return 1;
}

int validate_email(struct AddressBook *addressBook, char* email) // Subfunction
{
	// checking '@' and ".com" present and  checking before and after @ char is present 
	if( !strchr(email, '@') || !strstr(email,".com") ||
	email[0] == '@' || email[(strlen(email) - 1)] == '@' )
	{
		printf("\n>>>> Email should contain '@' and '.com'  and atleast one char should be present before and after '@' <<<<\n\n"); 
		return 0;
	}

	int i = 0;
	while(email[i] != '\0')
	{
		if(isupper(email[i])) // check if uppercase is present
		{
			printf("\n>>>> Email should contain only lower case characters <<<<\n\n");
			return 0;
		}
		i++;
	}
	// checking if .com is present in the last
	if(strcmp(email + (strlen(email) - 4), ".com"))
	{
		printf("\n>>>> '.com' should present in the last <<<<\n\n");
		return 0;
	}	

	for(int i = 0; i < addressBook->contactCount; i++) // unique check
	{
		if(!(strcmp(addressBook->contacts[i].email, email))) // if it exist strcmp will return 0 else non-zero value
		{
			printf("\n>>>> Email already exist! <<<<\n\n");
			return 0;
		}
	}
    return 1;
}


void searchContact(struct AddressBook *addressBook) // Function definition for searching contacts
{
    /* Define the logic for search */
	int op;
	do
	{
		printf("\n:::Search Menu:::\n");
		printf("\n1. Search by name\n");
		printf("2. Search by phone\n");
		printf("3. Search by email\n");
		printf("4. Exit\n\n");

		printf("\nChoose from the menu how you want to search: ");
		scanf("%d",&op);
		getchar(); // consumes newline

		switch(op)
		{
			case 1:
				search_by_name(addressBook); // Function call
				break;
			case 2:
				phone_search(addressBook);
				break;
			case 3:
				email_search(addressBook); 
				break;
			case 4:
				break;		
			default:
				printf("\n>>>> Invalid option!! Please choose a valid option from the menu <<<<\n\n");
		}
	}while(op != 4);
}


void search_by_name(struct AddressBook *addressBook) // Sub function for only searching and printing name
{
	char temp_name[50]; // temporary
	printf("\nEnter the name of contact: ");
	scanf(" %[^\n]",temp_name);

	int count = 0;
	for(int i = 0; i < addressBook->contactCount; i++) // prints multiple contacts 
	{
		if(strcmp(addressBook->contacts[i].name, temp_name) == 0)
		{
			printf("\n\tContact %d\n\n", count + 1);

			printf("\tName     : %s\n", addressBook->contacts[i].name);
			printf("\tPhone no : %s\n", addressBook->contacts[i].phone);
			printf("\tEmail    : %s\n\n", addressBook->contacts[i].email);
			printf("\t..........................................\n\n");
			count++;

		}
	}
	if(count == 0) // If it is zero contact is not available 
	{
		printf("\n>>>> Contact not found <<<<\n\n");
	}
}

int name_search(struct AddressBook *addressBook) // sub function for handling multiple name cases for edit and delete
{
	char temp_name[50];
	printf("\nEnter the name: ");
	scanf(" %[^\n]",temp_name);

	int count = 0;
	int index_arr[addressBook -> contactCount]; // Array for storing the original index of contacts
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].name, temp_name) == 0)
		{
			printf("\n\tContact %d\n", count + 1);

			printf("\n\tName     : %s\n", addressBook->contacts[i].name);
			printf("\tPhone no : %s\n", addressBook->contacts[i].phone);
			printf("\tEmail    : %s\n\n", addressBook->contacts[i].email);
			printf("\t..........................................\n");

			index_arr[count] = i;
			count++;
		}
	}
	if(count == 0)
	{
		printf("\n>>>> Contact not found <<<<\n");
		return -1;
	}
	else if(count > 1) // Multiple contact
	{
		int selected_index = 0; // For storing the index of the selected contact by user
		do
		{
			printf("\n%d contacts are found for %s\nFrom these select one contact: ", count, temp_name);
			scanf("%d", &selected_index);
			
			if(selected_index < 1 || selected_index > count)
			{
				printf(">>>> Invalid index please try again <<<<\n");
			}
			else
			{
				return index_arr[selected_index - 1];
			}
		}while(selected_index < 1 || selected_index > count); // only exit do while when selected index is valid
	}
	else
	{
		return index_arr[0]; // If it is single contact returns the index
	}
	return -1; 
}

int phone_search(struct AddressBook * addressBook) // sub function for searching phone and returns index and prints
{
	char temp_phone[20]; // Temporary 
	printf("\nEnter the phone number: ");
	scanf("%s",temp_phone);

	int index = 0;
	int flag = 0;
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].phone, temp_phone) == 0) // if it exist strcmp will return 0 else non-zero value
		{
			flag = 1;
			printf("\n\t::::Contact Found:::\t\n");
			printf("\t..........................................\n");

			printf("\n\tName     : %s\n", addressBook->contacts[i].name);
			printf("\tPhone no : %s\n", addressBook->contacts[i].phone);
			printf("\tEmail    : %s\n\n", addressBook->contacts[i].email);
			printf("\t..........................................\n");

			index = i; // storing the original index value of the contact
			break;
		}
	}
	if(flag == 1)
	{	
		return index; // returning the index of the contact
	}
	else 
	{
		printf("\n>>>> Contact not found <<<<\n");
		return -1;
	}
}

int email_search(struct AddressBook * addressBook) // sub function for searching email
{
	char temp_email[50];
	printf("\nEnter the Email: ");
	scanf("%s",temp_email);

	int index = 0;
	int flag = 0;
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].email, temp_email) == 0)
		{
			flag = 1;
			printf("\n\t::::Contact Found:::\t\n");
			printf("\t..........................................\n");

			printf("\n\tName     : %s\n", addressBook -> contacts[i].name);
			printf("\tPhone no : %s\n", addressBook -> contacts[i].phone);
			printf("\tEmail    : %s\n\n", addressBook -> contacts[i].email);
			printf("\t..........................................\n");

			index = i;
			break;
		}
	}
	if(flag == 1)
	{	
		return index; // returning the index of the contact
	}
	else 
	{
		printf("\n>>>> Contact not found <<<<\n");
		return -1;
	}
}

void editContact(struct AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
	int op, index = 0;
	do
	{
		printf("\n:::Search Menu:::\n");
		printf("\n1. Search by name\n");
		printf("2. Search by phone\n");
		printf("3. Search by email\n");
		printf("4. Exit\n\n");

		printf("\nChoose from the menu how you want to search: ");
		scanf("%d",&op);

		switch(op)
		{
			case 1:
				index = name_search(addressBook); // If contact not found returns -1
				if(index != -1)
					edit_field(addressBook, index); // Function calls if contact found
				break;

			case 2:
				index = phone_search(addressBook);  
				if(index != -1)
					edit_field(addressBook, index);
				break;

			case 3:
				index = email_search(addressBook); 
				if(index != -1)
					edit_field(addressBook, index);
				break;

			case 4:
				break;

			default:
				printf("\n>>>> Invalid option choose correct option <<<<\n");
				break;
		}
	}while(op != 4);
}


void edit_field(struct AddressBook *addressBook, int contact_index) // For selecting which field to edit
{
	int op;
	do
	{
		printf("\n:::Edit Menu:::\n");
		printf("\n1. Name\n");
		printf("2. Phone\n");
		printf("3. Email\n");
		printf("4. Exit\n\n");

		printf("\nselect the  field you want to edit: ");
		scanf("%d",&op);

		switch(op)
		{
			case 1:
				edit_field_name(addressBook, contact_index); // Function call to edit name
				break;

			case 2:
				edit_field_phone(addressBook, contact_index); // Function call to edit phone number
				break;

			case 3:
				edit_field_email(addressBook, contact_index); // Function call to edit email
				break;
			case 4:
				break;
			default:
				printf("\n>>>> Invalid option choose correct option from the above menu <<<<\n");
		}
	}while(op != 4);
 }

void edit_field_name(struct AddressBook *addressBook, int contact_index) // Function defintion for edit name
{
	char temp_name[50]; // Temporary
	printf("\nEnter the new name: ");
	scanf(" %[^\n]", temp_name);

	strcpy(addressBook->contacts[contact_index].name , temp_name); // Overwriting the old name
	printf("\n>>>> Name edited succesfully <<<<\n\n");
	display_edited_contact(addressBook, contact_index); // For displaying the contact after editing

}

void edit_field_phone(struct AddressBook *addressBook, int contact_index)// Function defintion for edit phone
{
	char temp_phone[20]; // Temporary
	do
	{
		printf("\nEnter the new phone number: ");
		scanf(" %[^\n]",temp_phone);

	}while(validate_phone(addressBook, temp_phone) == 0); // Function call for validating phone number

	strcpy(addressBook->contacts[contact_index].phone, temp_phone); // copying to contacts
	printf("\n>>>> Phone number edited succesfully <<<<\n\n");
	display_edited_contact(addressBook, contact_index); // Function call for displaying contact
	
}

void edit_field_email(struct AddressBook *addressBook, int contact_index)// Function defintion for edit email
{
	char temp_email[50]; // Temporary
	do
	{
		printf("\nEnter the new email: ");
		scanf(" %[^\n]",temp_email);
	}while(validate_email(addressBook, temp_email) == 0); // Function call for validating email

	strcpy(addressBook->contacts[contact_index].email, temp_email); // copying to contacts
	printf("\n>>>> Email edited succesfully <<<<\n\n");
	display_edited_contact(addressBook, contact_index); // Function call for displaying contact

}

void display_edited_contact(struct AddressBook *addressBook, int contact_index) // Fucntion for displaying contact
{
	printf("\nEdited Contact details is: \n");
	printf("\t..........................................\n");

	printf("\n\tName     : %s\n", addressBook->contacts[contact_index].name);
	printf("\tPhone no : %s\n", addressBook->contacts[contact_index].phone);
	printf("\tEmail    : %s\n\n", addressBook->contacts[contact_index].email);

	printf("\t..........................................\n");
}

void deleteContact(struct AddressBook *addressBook) // Function definition for deleting contact
{
    /* Define the logic for deletecontact */
	int op, index = 0;
	do
	{
		printf("\n:::Delete Menu:::\n");
		printf("\n1. search by name\n");
		printf("2. search by phone\n");
		printf("3. search by email\n");
		printf("4. Exit\n\n");

		printf("\nChoose how you want to search the contact to delete: ");
		scanf("%d",&op);

		switch(op)
		{
			case 1:
				index = name_search(addressBook); // Functions returns -1 if contact is not found else returns the index value
				if(index != -1) 
					contact_delete(addressBook, index); // call for deletion
				break;

			case 2:
				index = phone_search(addressBook); 
				if(index != -1)
					contact_delete(addressBook, index);
				break;

			case 3:
				index = email_search(addressBook);
				if(index != -1)
					contact_delete(addressBook, index);
				break;
			case 4:
				break;

			default:
				printf("\n>>>> Invalid option <<<<\n");
		}
	}while(op != 4);
}

void contact_delete(struct AddressBook *addressBook, int index) // Function for deleting contact after getting index
{
	int opt;
	printf("\nDo you want to delete this contact (1-Yes / 0-No): ");
	scanf("%d",&opt);

	if(opt == 1)
	{
		// shifting all the contacts to the left from deleted contact index 
		for(int i = index; i < addressBook->contactCount - 1; i++)
		{
			addressBook->contacts[i] = addressBook->contacts[i + 1];
		}
		printf("\n>>>> The contact is deleted <<<<\n\n");
		addressBook->contactCount--; // Decrementing the contact count
	}
	else
	{
		return;
	}
}
