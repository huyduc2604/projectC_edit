//void menuBook(){
//	int choice;
//	int countBook=0;
//	
//	do{
//		printf("\n===================MENU====================\n");
//	    printf("===========================================\n");
//	    printf("[1]. Them sach moi\n");
//	    printf("[2]. Hien thi sach\n");
//	    printf("[3]. Chinh sua thong tin sach\n");
//	    printf("[4]. Xoa sach\n");
//	    printf("[5]. Sap xep sach theo gia tien\n");
//	    printf("[6]. Tim kiem sach\n");
//	    printf("[0]. Thoat chuong trinh quay lai MENU chinh\n");
//	    printf("===========================================\n");
//	    printf("Nhap lua chon cua ban: ");
//	    scanf("%d",&choice);
//	    fflush(stdin); 
//	    switch (choice) {
//            case 1:
//				addBook(&countBook);                
//				break;
//            case 2:
//                showBook(countBook);
//                break;
//            case 3:
//                editBook(countBook);
//                break;
//                
//            case 4:
//            	deleteBook(&countBook);
//            	break;
//            	
//            case 5:
//				sortBooks(books, countBook);
//                break;
//				
//			case 6:
//				searchBook(countBook);
//				break;
//				
//            case 0:
//                printf("Exiting the program. Goodbye!\n");
//                return;
//            default:
//                printf("Invalid choice. Please try again.\n");
//                break;
//        }
//	} while(choice != 0);
//} 
//

//void manageCustomers() {
//    int choice;
//    do {
//        printf("\n========= QUAN LY KHACH HANG =========\n");
//        printf("[1]. Them khach hang moi\n");
//        printf("[2]. Hien thi danh sach khach hang\n");
//        printf("[3]. Chinh sua thong tin khach hang\n");
//        printf("[4]. Xoa khach hang\n");
//        printf("[0]. Quay lai menu chinh\n");
//        printf("=====================================\n");
//        printf("Nhap lua chon cua ban: ");
//        scanf("%d", &choice);
//        fflush(stdin);
//
//        switch (choice) {
//            case 1:
//                addCustomer();
//                break;
//            case 2:
//                showCustomers();
//                break;
//            case 3:
//                editCustomer();
//                break;
//            case 4:
//                deleteCustomer();
//                break;
//            case 0:
//                printf("Quay lai menu chinh...\n");
//                return;
//            default:
//                printf("Lua chon khong hop le. Vui long nhap lai!\n");
//                break;
//        }
//    } while (choice != 0);
//}
//

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

    fwrite(&memberCount, sizeof(int), 1, file); //Ghi so luong thanh vien

    for (int i = 0; i < memberCount; i++) {
        fwrite(&members[i], sizeof(struct member), 1, file); //Ghi tung thanh vien vao file
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
    fread(&memberCount, sizeof(int), 1, file); //Doc so luong khach hang 
    for (int i = 0; i < memberCount; i++) {
        if (fread(&members[i], sizeof(struct member), 1, file) != 1) {
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
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, id) == 0) {
            return 0; //ID da ton tai 
        }
    }
    return 1; //ID duy nhat
}

//**********Ham kiem tra xem nguoi dung co nhap trung voi ten da co san khong**********
int isMemberNameUnique(char *name) {
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            return 0; //Ten da ton tai
        }
    }
    return 1; //Ten duy nhat
}
//Ham them thong tin khach hang
void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Library is full!\n");
        return;
    }

    getchar(); //Xoa ky tu "\n"

    struct member newMember;

    //Nhap ID khach hang va kiem tra trung lap
    while (1) {
        printf("Enter member ID: ");
        fgets(newMember.memberId, sizeof(newMember.memberId), stdin);
        newMember.memberId[strcspn(newMember.memberId, "\n")] = '\0';

        if (isMemberIdUnique(newMember.memberId)) {
            break; //ID duy nhat, thoat vong lap
        } else {
            printf("ID already exists. Please enter a different ID.\n");
        }
    }

    //Nhap ten khach hang va kiem tra khong de trong
    while (1) {
        printf("Enter member name: ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = '\0';

        if (strlen(newMember.name) == 0) {
            printf("Name cannot be empty. Please re-enter.\n");
            continue;
        }

        if (isMemberNameUnique(newMember.name)) {
            break; //Thoat vong lap neu hop le
        } else {
            printf("Name already exists. Please enter a different name.\n");
        }
    }

    //Nhap so dien thoai
    printf("Enter phone number: ");
    fgets(newMember.phone, sizeof(newMember.phone), stdin);
    newMember.phone[strcspn(newMember.phone, "\n")] = '\0';

    //Nhap trang thai (0: khoa, 1: hoat dong)
    printf("Enter status (0: locked, 1: active): ");
    while (scanf("%d", &newMember.status) != 1 || (newMember.status != 0 && newMember.status != 1)) {
        printf("Invalid input. Please enter 0 for locked or 1 for active: ");
        while(getchar() != '\n'); //Xoa ky tu newline con lai trong buffer
    }

    //Them thanh vien vao danh sach va cap nhat so luong
    members[memberCount] = newMember;
    memberCount++;

    saveMembersToFile(); //Luu vao tep
    printf("Member has been successfully added!\n");

    if (memberCount == 0) {
        printf("The library has no members.\n");
        return;
    }
}

//**********Ham hien thi thong tin khach hang**********
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
    
    for (int i = 0; i < memberCount; i++) {
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
    for (int i = 0; i < memberCount; i++) {
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
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, memberId) == 0) { 
            // Thay doi trang thai tai khoan
            if (members[i].status == 1) {
                members[i].status = 0;  // Khoa tai khoan
                printf("Member account has been locked.\n");
            } else {
                members[i].status = 1;  // Mo khoa tai khoan
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
    for (int i = 0; i < memberCount; i++) {
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
