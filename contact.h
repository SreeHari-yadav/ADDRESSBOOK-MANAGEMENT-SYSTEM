#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char mail[50];
} Contact;

typedef struct {
    Contact contacts[500];
    int contactCount; 
} AddressBook;

void createContact(AddressBook *adb);
void searchContact(AddressBook *adb);
void editContact(AddressBook *adb);
void deleteContact(AddressBook *adb);
void listContacts(AddressBook *adb);
void initialize(AddressBook *adb);
void saveContactsToFile(AddressBook *AddressBook);

void saveAndExit(AddressBook *adb);

int validate_name(char *str);
int validate_phone(char *str);
int validate_mail(char *str);

int uniquness_phone(AddressBook *adb,char *str);
int uniquness_mail(AddressBook *adb,char *str);

int search_by_name(AddressBook *adb);
int search_by_phone(AddressBook *adb);
int search_by_mail(AddressBook *adb);

void editby_name(int ind,AddressBook *adb);
void editby_phone(int ind,AddressBook *adb);
void editby_mail(int ind,AddressBook *adb);

#endif
