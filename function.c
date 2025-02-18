#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"
//#include "datatype.h"
#define MAX_BOOKS 100
int countBook =0;

struct Book books[MAX_BOOKS];

const char filebook[100] = "C:\\Users\\Admin\\Desktop\\projectC\\book.txt";


void readBooksFromFile(const char* filename, struct Book books[], int *countBook){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("Error opening file!");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %s %s %d %d %d/%d/%d",
                  books[i].bookId,
                  books[i].title,
                  books[i].author,
                  &books[i].quantity,
                  &books[i].price,
                  &books[i].publication.day,
                  &books[i].publication.month,
                  &books[i].publication.year) != EOF){
        i++;
    }
    *countBook = i;
    if (ferror(file)){
        perror("Error reading from file");
    }
    fclose(file);
}
//
void writeBooksToFile(const char* filename, struct Book books[], int countBook){
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        perror("Error opening file!");
        return;
    }
    int i; 
    for (i = 0; i < countBook; i++){
        fprintf(file, "%s %s %s %d %d %02d/%02d/%04d\n",
                books[i].bookId,
                books[i].title,
                books[i].author,
                books[i].quantity,
                books[i].price,
                books[i].publication.day,
                books[i].publication.month,
                books[i].publication.year);
    }
    fclose(file);
}

void login(){
    char email[50];
    char password[50];
    int loginSuccessful = 0;
    
    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-17s %-24s %s\n","|","LOGIN", "|");

        printf("+------------------------------------------+\n");
        
        // Y?u cau nhap email
        printf("Email: ");
        scanf("%s", email);
        
        // Yeu cau nhap mat khau
        printf("Password: ");
        scanf("%s", password);
        fflush (stdin);
        
        // Kiem tra th?ng tin dang nhap
        if (strcmp(email, "buixuanhuyduc") == 0 && strcmp(password, "1") == 0) {
            printf("Login successful!\n");
            loginSuccessful = 1;
        } else {
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);
}

void menu(){
	login();
	int choice;
	do{
	
	printf("\n|=========== MENU ===========|\n");

	printf("|============================|\n");

	printf("| [1]. Book Management       |\n");
	printf("| [2]. Customer Management   |\n");
	printf("| [3]. Admin                 |\n");
	printf("| [0]. Exit The Program      |\n");
	printf("|============================|\n");
	printf(" Enter The Choice: ");
	scanf("%d", &choice);
	switch (choice) {
            case 1:
            	
                menuBook();
                break;
            case 2:
                showMemberMenu();
                break;
            case 3:
               	loginAdmin();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

void menuBook(){
	int choice;
	int countBook=0;
	
	do{
		printf("\n===================MENU====================\n");
	    printf("===========================================\n");
	    printf("[1]. Them sach moi\n");
	    printf("[2]. Hien thi sach\n");
	    printf("[3]. Chinh sua thong tin sach\n");
	    printf("[4]. Xoa sach\n");
	    printf("[5]. Sap xep sach theo gia tien\n");
	    printf("[6]. Tim kiem sach\n");
	    printf("[0]. Thoat chuong trinh quay lai MENU chinh\n");
	    printf("===========================================\n");
	    printf("Nhap lua chon cua ban: ");
	    scanf("%d",&choice);
	    fflush(stdin); 
	    switch (choice) {
            case 1:
				addBook(&countBook);                
				break;
            case 2:
                showBook(countBook);
                break;
            case 3:
                editBook(countBook);
                break;
                
            case 4:
            	deleteBook(&countBook);
            	break;
            	
            case 5:
				sortBooks(books, countBook);
                break;
				
			case 6:
				searchBook(countBook);
				break;
				
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
	} while(choice != 0);
} 

int isValidDate(int day, int month, int year) {
    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1) {
        return 0;
    }
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        daysInMonth[2] = 29;
    }
    return day <= daysInMonth[month];
}

void addBook(int *countBook) {
    do {
        printf("Moi ban nhap ID: ");
        fgets(book[*countBook].bookId, sizeof(book[*countBook].bookId), stdin);
        book[*countBook].bookId[strcspn(book[*countBook].bookId, "\n")] = '\0';
        if (strlen(book[*countBook].bookId) == 0){
            printf("ID khong duoc de trong!\n");
        }else if (strlen(book[*countBook].bookId) > 9) {
            printf("ID qua dai toi da 9 ky tu\n");
        }
    }while(strlen(book[*countBook].bookId) == 0 || strlen(book[*countBook].bookId) > 9);

    do {
        printf("Moi ban nhap tieu de: ");
        fgets(book[*countBook].title, sizeof(book[*countBook].title), stdin);
        book[*countBook].title[strcspn(book[*countBook].title, "\n")] = '\0';
        if (strlen(book[*countBook].title) == 0) {
            printf("Tieu de khong duoc de trong\n");
        } else if (strlen(book[*countBook].title) > 29) {
            printf("Tieu de qua dai toi da 29 ky tu\n");
        }
    } while (strlen(book[*countBook].title) == 0 || strlen(book[*countBook].title) > 29);

    do {
        printf("Moi ban nhap tac gia: ");
        fgets(book[*countBook].author, sizeof(book[*countBook].author), stdin);
        book[*countBook].author[strcspn(book[*countBook].author, "\n")] = '\0';
        if (strlen(book[*countBook].author) == 0) {
            printf("Tac gia khong duoc de trong!\n");
        } else if (strlen(book[*countBook].author) > 19) {
            printf("Ten tac gia qua dai toi da 19 ky tu\n");
        }
    } while (strlen(book[*countBook].author) == 0 || strlen(book[*countBook].author) > 19);

    do {
        printf("Moi ban nhap so luong: ");
        if (scanf("%d", &book[*countBook].quantity) != 1 || book[*countBook].quantity <= 0) {
            getchar();
            printf("So luong phai la so nguyen duong\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    do {
        printf("Moi ban nhap gia: ");
        if (scanf("%d", &book[*countBook].price) != 1 || book[*countBook].price <= 0) {
            getchar();
            printf("Gia phai la so nguyen duong\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    do {
        printf("Moi ban nhap ngay xuat ban (dd mm yyyy): ");
        scanf("%d %d %d", &book[*countBook].publication.day, &book[*countBook].publication.month, &book[*countBook].publication.year);
        getchar();
        if (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year)) {
            printf("Ngay khong hop le\n");
        }
    } while (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year));

    (*countBook)++;
//    saveToFile(countBook);
	
    printf("Them sach thanh cong\n");
}



void showBook(int countBook){
    if (countBook == 0) {
        printf("Khong co sach de hien thi\n");
        return;
    }
    printf("\n=============================== All Book ==============================\n\n");
    printf("|======|==============|===============|========|==========|===============|\n");
    printf("|%-6s|%-14s|%-15s|%-8s|%-10s|%-15s|\n", "ID", "TIEU DE", "TAC GIA", "SO LUONG", "GIA", "NGAY XUAT BAN");
    printf("|======|==============|===============|========|==========|===============|\n");
    int i; 
    for (i = 0; i < countBook; i++) {
        printf("|%-6s|%-14s|%-15s|%-8d|%-10d|%02d/%02d/%04d%-5s|\n", book[i].bookId, book[i].title, book[i].author, book[i].quantity, book[i].price, book[i].publication.day, book[i].publication.month, book[i].publication.year,"     ");
        printf("|======|==============|===============|========|==========|===============|\n");
    }
}

void editBook(int countBook){
    char id[10];
    printf("Nhap ID sach can chinh sua: ");
    scanf("%s", id);
    getchar();
    int i;
    for (i = 0; i < countBook; i++){
        if (strcmp(book[i].bookId, id) == 0){
            printf("Chinh sua thong tin sach %s\n", book[i].title);
            printf("Nhap ten moi: ");
            fgets(book[i].title, sizeof(book[i].title), stdin);
            book[i].title[strcspn(book[i].title, "\n")] = '\0';
            printf("Nhap ngay xuat ban moi (dd mm yyyy): ");
            scanf("%d %d %d", &book[i].publication.day, &book[i].publication.month, &book[i].publication.year);
            getchar();
            printf("Nhap ten tac gia moi: ");
            fgets(book[i].author, sizeof(book[i].author), stdin);
            book[i].author[strcspn(book[i].author, "\n")] = '\0';
            printf("Nhap so luong moi: ");
			scanf("%d",&book[i].quantity);
            printf("Nhap gia tien moi: ");
            scanf("%d", &book[i].price);
            getchar();
            printf("Chinh sua thong tin thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sach voi ID %s!\n", id);
}

void deleteBook(int *countBook){
    char id[10];
    printf("Nhap ID sach can xoa: ");
    scanf("%s", id);
    getchar();
    int i;
    for (i = 0; i < *countBook; i++){
        if (strcmp(book[i].bookId, id) == 0){
            char confirm;
            printf("Ban co chac chan muon xoa sach voi ID %s? (y/n): ", id);
            scanf(" %c", &confirm);
            getchar();
            if (confirm == 'y' || confirm == 'Y'){
            	int j;
                for (j = i; j < *countBook - 1; j++){
                    book[j] = book[j + 1];
                }
                (*countBook)--;
                printf("Xoa sach thanh cong!\n");
            }else{
                printf("Huy thao tac xoa sach.\n");
            }
            return;
        }
        printf("Khong tim thay sach voi ID %s!\n", id);
}
//    printf("Khong tim thay sach voi ID %s!\n", id);
}

void sortBooks(struct Book books[], int countBook){
    if (countBook < 2){
        printf("Khong co du lieu de sap xep!\n");
        return;
    }
    int order;
    printf("Chon thu tu sap xep: 1. Tang dan 2. Giam dan: ");
    if (scanf("%d", &order) != 1 || (order != 1 && order != 2)){
        printf("Lua chon khong hop le!\n");
        while (getchar() != '\n'); // Xóa b? nh? ð?m ð?u vào
        return;
	}
    getchar(); // Tranh loi nhap sau scanf

    // Thuat toan sap xep(Bubble Sort)
    int i, j;
    
    for ( i = 0; i < countBook - 1; i++){
        for (j = i + 1; j < countBook; j++){
            if ((order == 1 && book[i].price > book[j].price)|| 
                (order == 2 && book[i].price < book[j].price)){
                struct Book temp = book[i];
                book[i] = book[j];
                book[j] = temp;
            }
        }
    }
    printf("Sap xep sach theo gia tien thanh cong!\n");
}



void searchBook(int countBook){
    char temp[30];
    int check=1;
    printf("Nhap ten sach muon tim: ");
    fgets(temp,sizeof(temp),stdin);
    temp[strcspn(temp,"\n")]='\0';
    printf("============================== Search Results =============================\n");
    printf("|======|==============|===============|========|==========|===============|\n");
    printf("|%-6s|%-14s|%-15s|%-6s|%-10s|%-15s|\n","ID","TIEU DE","TAC GIA","SO LUONG","GIA","ngay xuat ban");
    printf("|======|==============|===============|========|==========|===============|\n");
    int i; 
    for(i=0;i<countBook;i++){
        if(strstr(book[i].title,temp)!=NULL){
            printf("|%-6s|%-14s|%-15s|%-8d|%-10d|%02d/%02d/%04d%-5s|\n",book[i].bookId,book[i].title,book[i].author,book[i].quantity,book[i].price,book[i].publication.day,book[i].publication.month,book[i].publication.year,"     ");
            printf("|======|==============|===============|========|==========|===============|\n");
            check=0;
        	}
    }
	if(check){
        printf("Khong tim thay sach\n");
    }
    return;
}

//**********Ham show menu quan li khach hang**********
void showMemberMenu(){
    int choice;
    do {
        printf("\n************MEMBER MANAGEMENT MENU***********\n");
        printf("---------------------------------------------\n");
        printf("|%-43s|\n","1. Add new member."); //Them khach hang 
        printf("|%-43s|\n","2. Display member list."); //Hien thi danh sach khach hang 
        printf("|%-43s|\n","3. Edit member information"); //Chinh sua thong tin khach hang 
        printf("|%-43s|\n","4. Search member by name."); //Tim kiem khach hang theo ten 
        printf("|%-43s|\n","5. Lock/Unlock member account."); //Khoa/mo khoa khach hang 
        printf("|%-43s|\n","6. Back to main menu!!!"); // Quay ve menu chinh 
        printf("---------------------------------------------\n");
        printf("Choose your option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMember(); //Them khach hang 
                break;
            case 2:
                displayMembers(); //Hien thi danh sach khach hang 
                break;
            case 3:
                editMember(); //Chinh sua thong tin khach hang 
                break;
            case 4:
                searchMember(); //Tim kiem khach hang 
                break;
            case 5:
                toggleMemberLock(); //Khoa/mo khoa khach hang 
                break;
            case 6:
                printf("Returning to main menu...\n");
                return; //Quay ve menu chinh 
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (choice != 6);
} 

//**********Ham luu thong tin kahch hang vao file**********
void saveMembersToFile() {
    FILE *file = fopen("member.bin", "wb"); //Mo file nhi phan de ghi
    if (file == NULL) {
        printf("Cannot open file to write!\n"); //Neu khong the mo file
        return;
    }

    fwrite(book, sizeof(int), 1, file); //Ghi so luong thanh vien
	int i;
    for (i = 0; i < countBook; i++) {
        fwrite(book, sizeof(struct Book), 1, file); //Ghi tung thanh vien vao file
    }

    fclose(file);
    printf("Member list has been saved to 'member.bin'.\n"); //Danh sach thanh vien da duoc luu vao 'member.bin'
}
//**********Ham load thong tin khach hang tu file********** 
int loadMembersFromFile() {
    FILE *file = fopen("member.bin", "rb");
    if (file == NULL) {
        printf("Cannot open file to read 'member.bin'!\n");
        return 0; //Khong thanh cong
    }
    fread(book, sizeof(int), 1, file); //Doc so luong khach hang 
    int i;
    for (i = 0; i < countBook; i++) {
        if (fread(book, sizeof(struct Book), 1, file) != 1) {
            printf("Error reading member data from file!\n");
            fclose(file);
            return 0; //Khong thanh cong
        }
    }
    fclose(file); //Dong file 
    printf("Member list has been loaded from 'member.bin'.\n");
    return 1; //Thanh cong
}

//**********Ham kiem tra xem nguoi dung nhap ID co trung voi ID da co san khong**********
int isMemberIdUnique(char *id) {
	int i;
    for (i = 0; i < countBook; i++) {
        if (strcmp(members[i].memberId, id) == 0) {
            return 0; //ID da ton tai 
        }
    }
    return 1; //ID duy nhat
}
//
////**********Ham kiem tra xem nguoi dung co nhap trung voi ten da co san khong**********
int isMemberNameUnique(char *name) {
	int i;
    for (i = 0; i < countBook; i++) {
        if (strcmp(members[i].name, name) == 0) {
            return 0; //Ten da ton tai
        }
    }
    return 1; //Ten duy nhat
}
////Ham them thong tin khach hang
void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Library is full!\n");
        return;
    }

    struct Member newMember;
    getchar();

    while (1) {
        printf("Enter member ID: ");
        fgets(newMember.memberId, sizeof(newMember.memberId), stdin);
        newMember.memberId[strcspn(newMember.memberId, "\n")] = '\0';

        if (isMemberIdUnique(newMember.memberId)){
            break;
        } else {
            printf("ID already exists. Please enter a different ID.\n");
        }
    }

    // Nh?p s? ði?n tho?i
    printf("Enter phone number: ");
    fgets(newMember.phone, sizeof(newMember.phone), stdin);
    newMember.phone[strcspn(newMember.phone, "\n")] = '\0';

    // Nh?p tr?ng thái (0: khóa, 1: ho?t ð?ng)
    printf("Enter status (0: locked, 1: active): ");
    while (scanf("%d", &newMember.status) != 1 || (newMember.status != 0 && newMember.status != 1)) {
        printf("Invalid input. Please enter 0 for locked or 1 for active: ");
        while (getchar() != '\n'); // Xóa b? nh? ð?m
    }

    // Thêm thành viên vào m?ng
    members[memberCount++] = newMember;
    printf("Member has been successfully added!\n");
}
//
////**********Ham hien thi thong tin khach hang**********
void displayMembers() {
	loadMembersFromFile();
    if (memberCount == 0) {
        printf("The library has no member to display.\n");
        return;
    }
    
    printf("\n*************************MEMBER LIST*************************\n");
    printf("-------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-10s | %-8s |\n", "ID", "Name", "Phone", "Status");
    printf("-------------------------------------------------------------\n");
    int i; 
    for (i = 0; i < memberCount; i++) {
        //In thong tin tung khach hang 
        printf("| %-10s | %-20s | %-10s | %-8s |\n", 
            members[i].memberId, members[i].name, members[i].phone, (members[i].status == 1) ? "Active" : "Locked");
            printf("-------------------------------------------------------------\n");
    }
}

//*********Ham sua thong tin khach hang********** 
void editMember() {
    if (memberCount == 0) {
        printf("The library has no members.\n");
        return;
    }
    getchar(); 
    char memberId[10]; 
    printf("Enter the member ID to edit: ");
    fgets(memberId, sizeof(memberId), stdin);
    memberId[strcspn(memberId, "\n")] = '\0'; //Loai bo ky tu newline

    //Tim khach hang theo ID
    int i; 
    for (i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, memberId) == 0) { 
            printf("Enter new member name: ");
            fgets(members[i].name, sizeof(members[i].name), stdin);
            members[i].name[strcspn(members[i].name, "\n")] = '\0'; //Loai bo ky tu newline

            printf("Enter new phone number: ");
            fgets(members[i].phone, sizeof(members[i].phone), stdin);
            members[i].phone[strcspn(members[i].phone, "\n")] = '\0'; //Loai bo ky tu newline

            printf("Enter new status (1 for Active, 0 for Locked): ");
            while (scanf("%d", &members[i].status) != 1 || (members[i].status != 0 && members[i].status != 1)) {
                printf("Invalid status! Please enter 1 for Active or 0 for Locked: ");
                while (getchar() != '\n'); //Xoa ky tu '\n' con lai trong bo dem
            }
            getchar(); //Loai bo ky tu newline con lai trong bo dem

            printf("Member has been successfully edited!\n");
            saveMembersToFile(); //Luu thong tin khach hang da chinh sua vao file
            return;
        }
    }

    printf("Member ID does not exist.\n"); //Neu khong tim thay khach hang 
}

//**********Ham khoa , mo khoa khach hang**********
void toggleMemberLock() {
	loadMembersFromFile();
    if (memberCount == 0) {
        printf("The library has no members.\n");
        return;
    }
    
    char memberId[10]; 
    printf("Enter the member ID to lock/unlock: ");
    scanf(" %[^\n]", memberId);
    memberId[strcspn(memberId, "\n")] = '\0';

    // Loai bo ky tu newline neu co
    memberId[strcspn(memberId, "\n")] = '\0'; 

    // Kiem tra neu ID kahch hang rong sau khi loai bo newline
    if (strlen(memberId) == 0) {
        printf("Member ID cannot be empty!\n");
        return;
    }

    // Tim khach hang theo ID
    int i; 
    for (i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, memberId) == 0) { 
            // Thay doi trang thai tai khoan
            if (members[i].status == 1) {
                members[i].status == 0;  // Khoa tai khoan
                printf("Member account has been locked.\n");
            } else {
                members[i].status == 1;  // Mo khoa tai khoan
                printf("Member account has been unlocked.\n");
            }
            saveMembersToFile(); // Luu thay doi vao file
            return;
        }
    }

    printf("ID thanh vien khong ton tai.\n"); // Neu khong tim thay thanh vien
}

//*********Ham tim kiem khach hang**********
void searchMember() {
	loadMembersFromFile();
    if (memberCount == 0) {
        printf("The library has no members.\n");
        return;
    }

    char name[30];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", name);
    name[strcspn(name, "\n")] = '\0'; // Loai bo ky tu newline 
    if (strlen(name) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }

    int found = 0; // Bien kiem tra xem co thay khach hang khong 
    int i; 
    for (i = 0; i < memberCount; i++) {
        // Kiem tra ten nhap vao co ten cua khach hang trong danh sach khong 
        if (strstr(members[i].name, name) != NULL) {
            printf("\n**********************MEMBER INFORMATION*********************\n");
            printf("-------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-10s | %-8s |\n", members[i].memberId, members[i].name, members[i].phone, (members[i].status == 1) ? "Active" : "Locked");
            printf("-------------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No member found with the name '%s'.\n", name);
    }
}

void loginAdmin(){
    FILE *file=fopen("admin.dat","wb");
    if(file==NULL){
        printf("loi mo file de ghi\n");
        return;
    }
    struct Admin admin;
	strcpy(admin.username,"admin@gmail.com");
	strcpy(admin.password,"123456");
    fwrite(&admin,sizeof(admin),1,file);
    fclose(file);
}

void accountAdmim(int *countAdmin){
	if(*countAdmin==0){
	loginAdmin();
	(*countAdmin)++;
	}
	struct Admin admin;
    FILE *file=fopen("admin.dat","rb");
    if(file==NULL){
        printf("khong the mo file de doc\n");
        return;
    }
    fread(&admin,sizeof(struct Admin),1,file);
    fclose(file);
    char username[20];
	char password[20];
    do{
        printf("moi ban nhap ten tai khoang: ");
        fgets(username,sizeof(username),stdin);
        username[strcspn(username,"\n")]='\0';
        if(strcmp(username,admin.username)!=0){
            printf("sai tai khoan\n");
        }
    }while(strcmp(username,admin.username)!=0);
    do{
        printf("moi ban nhap mat khau: ");
        fgets(password,sizeof(password),stdin);
        password[strcspn(password,"\n")]='\0';
        if(strcmp(password,admin.password)!=0){
            printf("sai mat khau\n");
        }
    }while(strcmp(password,admin.password)!=0);
    printf("dang nhap admin thanh cong");
}


