//khai bao ham
#include "datatype.h"
#ifndef FUNCTION_H
#define FUNCTION_H

void menu();
void menuBook();
void showMemberMenu();
//void showMenu(); 
void login();
void isIDBook();
void isTitle();

int isValidDate(int day, int month, int year); //ngay san xuat sach

//them sach
void addBook() ;

//hien thi sach
void showBook(int countBook);

//chinh sua sach
void editBook(int countBook);

//Xoa sach
void deleteBook(int *countBook);

//sap xep sach
void sortBooks(struct Book books[], int countBook);

//tim kiem sach
void searchBook(int countBook);

//void showMenuBook();
void writeBooksToFile(const char* filename, struct Book books[], int numBooks);
//void readBooksFromFile(const char* filename, struct Book books[], int *countBook);
void readBooksFromFile(const char* filename, struct Book books[], int *countBook);


void saveBooksToFile();
int loadBooksFromFile();
int isMemberIdUnique(char *id);

void addMember();//Ham them thong tin khach hang
void displayMembers();//Ham hien thi thong tin khach hang
void editMember();//Ham sua thong tin khach hang
void toggleMemberLock();//Ham khoa , mo khoa khach hang
void searchMember();


void loginAdmin();
#endif

