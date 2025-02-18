
#ifndef DATATYPE_H  // N?u DATATYPE_H chua du?c d?nh nghia
#define DATATYPE_H  // ??nh nghia DATATYPE_H
#include <stdbool.h>
#define MAX_STUDENTS 100
#define MAX_BOOKS 100
#define MAX_MEMBERS 100
struct Date{
	int month,day,year;
};
struct Date date[100];
struct Book{
	char bookId[10]; //id book
	char title[30];  //ghi chu
	char author[20]; //tac gia
	int quantity;	//so luong
	int price;		//gia tien
	struct Date publication;
};
struct Book book[100];
//Book library[MAX_BOOKS];  // Khai báo bi?n library ch?a danh sách sách
struct Member{
	char memberId[10];
	char name[20];
	char phone[10];
	char status[10];
	struct Book BrrowedBooks[];
};
struct Admin {
    char username[50];
    char password[50];
    int loginAttempts;
    int isLocked; // 0: active, 1: locked
};


struct Member members[MAX_MEMBERS];
int memberCount = 0;
struct Member member[100];


#endif
