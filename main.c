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

#include "contact.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
	printf("\n\t::::Address Book Menu::::\n");
	printf("\n\t1. Create contact\n");
	printf("\t2. Search contact\n");
	printf("\t3. Edit contact\n");
	printf("\t4. Delete contact\n");
	printf("\t5. List all contacts\n");
	printf("\t6. Exit\n");
	printf("\nEnter your choice: ");
	scanf("%d", &choice);
	getchar();

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}
