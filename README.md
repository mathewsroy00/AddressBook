# Address Book Management System

A simple C program to manage contacts with add, search, edit, delete, and view functionality. All data is saved in a CSV file (contacts.csv).

## Features

- Add new contacts with name, phone, and email
- Search contacts by name, phone, or email
- Edit and delete existing contacts
- View all saved contacts
- Automatic data storage in contacts.csv

## Validation Rules

**Phone Number:**
- Must be 10 digits
- Numbers only
- Must be unique

**Email:**
- Must contain @
- Must end with .com
- Lowercase only
- Must be unique

**Name:**
- Can include any characters

## How to Compile and Run
```
gcc *.c
./a.out
```

## Main Menu Options
```
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
```

## Data Storage Format
```
#10
John Doe,1234567890,john@example.com
Jane Smith,9876543210,jane@example.com
```

## What I Learned

- Structures and pointers in C
- File handling with CSV
- Input validation
- Modular programming using multiple files

## Author

**Mathews Roy** – October 2025
