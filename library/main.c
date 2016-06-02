/*
 * main.c
 *
 *  Created on: May 24, 2016
 *      Author: gabri
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book_list.h"
#include "loan_list.h"

int menu();
void introduce_isbn(ISBN isbn);
void introduce_title(StringBook title);
void introduce_member_id(int* member_id);
void introduce_book_details(Book* book, ISBN isbn);
int subscribe_book(Book_List* list);
int unsubscribe_book(Book_List* books, Loan_List* loans);
int find_book(Book_List* list);
int loan_book(Book_List* books, Loan_List* loans);
int return_book(Loan_List* loans);

void read_books(FILE* pFile, Book_List* list);
void read_loans(FILE* pFile, Loan_List* list);
void write_books(FILE* pFile, Book_List* list);
void write_loans(FILE* pFile, Loan_List* list);

int main() {
	int option;
	int res;
	FILE* pFile_read_books;
	FILE* pFile_read_loans;
	FILE* pFile_write_books;
	FILE* pFile_write_loans;
	Book_List book_list;
	Loan_List loan_list;

	create_book_list(&book_list);
	create_loan_list(&loan_list);

//	res = find_book(&book_list);
//	if(res == 0) {
//		fprintf(stdout, "The book was not found.\n");
//	}
//	print_book_list(&book_list);

	pFile_read_books = fopen("books.dat", "rb");
	if(pFile_read_books == NULL) {
		fprintf(stdout, "\nError when reading the data base of books.\n");
	} else {
		pFile_read_loans = fopen("loans.dat", "rb");
		if(pFile_read_loans == NULL) {
			fprintf(stdout, "\nError when reading the data base of loans.\n");
		} else {
			read_books(pFile_read_books, &book_list);
			read_loans(pFile_read_loans, &loan_list);

			fclose(pFile_read_books);
			fclose(pFile_read_loans);

			do {
				option = menu();
				switch(option) {
					case 1:
						res = subscribe_book(&book_list);
						if(res == 1) {
							fprintf(stdout, "\nThe book was successfully added.\n");
						} else {
							fprintf(stdout, "\nThe book was not successfully added.\n");
						}
					break;
					case 2:
						res = unsubscribe_book(&book_list, &loan_list);
						if(res == -1) {
							fprintf(stdout, "\nThere are current loans with this book. It can't be removed.\n");
						} else if(res == 0) {
							fprintf(stdout, "\nThere is no book which matches the required ISBN.\n");
						} else {
							fprintf(stdout, "\nThe book was successfully removed.\n");
						}
					break;
					case 3:
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						fprintf(stdout, "\n\t\t\t\tLibrary Catalog");
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						print_book_list(&book_list);
					break;
					case 4:
						if(find_book(&book_list) == 0) {
							fprintf(stdout, "\nThe book desired is not in the library catalog.\n");
						}
					break;
					case 5:
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						fprintf(stdout, "\n\t\t\t\tLoan Book Menu");
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						res = loan_book(&book_list, &loan_list);
						if(res == -3) {
							fprintf(stdout, "\nThe loan was not successfully processed due to lack of memory.\n");
						} else if(res == -2) {
							fprintf(stdout, "\nThe loan was not successfully processed. There are no copies available.\n");
						} else if(res == -1) {
							fprintf(stdout, "\nThe loan was not successfully processed. There are no books matching the ISBN.\n");
						} else if (res == 0) {
							fprintf(stdout, "\nThe loan was not successfully processed. There are no books available.\n");
						} else {
							fprintf(stdout, "\nThe loan was successfully processed.\n");
						}
					break;
					case 6:
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						fprintf(stdout, "\n\t\t\t\tReturn Loan Menu");
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						res = return_book(&loan_list);
						if(res == -1) {
							fprintf(stdout, "\nThere are no loans matching the ISBN.\n");
						} else if(res == 0) {
							fprintf(stdout, "\nThere are currently no loans.\n");
						} else if(res == 1) {
							fprintf(stdout, "\nThe book was successfully returned.\n");
						}
					break;
					case 7:
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						fprintf(stdout, "\n\t\t\t\tList of Loans");
						fprintf(stdout, "\n--------------------------------------------------------------------------------");
						print_loan_list(loan_list);
					break;
				}
			} while (option != 8);

			pFile_write_books = fopen("books.dat", "wb");
			if(pFile_write_books != NULL) {
				write_books(pFile_write_books, &book_list);
				if(ferror(pFile_write_books)) {
					fprintf(stdout, "\nThere was an error handling the file to write the books.\n");
				}
				fclose(pFile_write_books);
			} else {
				fprintf(stdout, "\nThere was an error when writing book data to the file.\n");
			}

			pFile_write_loans = fopen("loans.dat", "wb");
			if(pFile_write_loans != NULL) {
				write_loans(pFile_write_loans, &loan_list);
				if(ferror(pFile_write_loans)) {
					fprintf(stdout, "\nThere was an error handling the file to write the loans.\n");
				}
				fclose(pFile_write_loans);
			} else {
				fprintf(stdout, "\nThere was an error when writing loan data to the file.\n");
			}
		}
	}

	return 0;
}

int menu() {
	int option;
	do {
		// Clear the console
		fprintf(stdout,"\n\n\n\n|______________________________________________________________________________|\n");
		fprintf(stdout,"                 - - - -  WELCOME TO THE LIBRARY CATALOG - - - -\n");
		fprintf(stdout,"\n------------------------------------MAIN MENU-----------------------------------\n");
		fprintf(stdout,"\n\n\t1.- Add a book");
		fprintf(stdout,"\n\n\t2.- Remove a book");
		fprintf(stdout,"\n\n\t3.- Print library catalog");
		fprintf(stdout,"\n\n\t4.- Search book by title");
		fprintf(stdout,"\n\n\t5.- Loan a book");
		fprintf(stdout,"\n\n\t6.- Return a book");
		fprintf(stdout,"\n\n\t7.- Print loans");
		fprintf(stdout,"\n\n\t8.- Exit the program");
		fprintf(stdout,"\n\n\n\tChoose the desired option: ");
		fscanf(stdin, "%d%*c", &option);
		fflush(stdin);
	} while(option < 1 || option > 8);
	return option;
}

void delete_char(char *string){
    char *aux;
    aux=strchr(string,'\n');
    if(aux!=NULL){
        *aux='\0';
    }
}

void introduce_isbn(ISBN isbn){
	fprintf(stdout, "\nIntroduce the ISBN: ");
	fgets(isbn, ISBN_LEN, stdin);
	fflush(stdin);
	delete_char(isbn);
}

void introduce_title(StringBook title){
	fprintf(stdout, "\nIntroduce the title: ");
	fgets(title, MAX_LEN, stdin);
	fflush(stdin);
	delete_char(title);
}

void introduce_member_id(int* member_id){
	do {
		fprintf(stdout, "\nIntroduce the memer ID: ");
		fscanf(stdin, "%d", member_id);
		fflush(stdin);
	} while(*member_id <= 0);
}

void introduce_book_details(Book* book, ISBN isbn){
	StringBook string;
	int date;

	fprintf(stdout, "Title: ");
	fgets(string, MAX_LEN, stdin);
	delete_char(string);
	fflush(stdin);
	set_title(book, string);
	fprintf(stdout, "Author: ");
	fgets(string, MAX_LEN, stdin);
	delete_char(string);
	fflush(stdin);
	set_author(book, string);
	fprintf(stdout, "Editorial: ");
	fgets(string, MAX_LEN, stdin);
	delete_char(string);
	fflush(stdin);
	set_editorial(book, string);
	set_isbn(book, isbn);
	fprintf(stdout, "Date: ");
	fscanf(stdin, "%d", &date);
	fflush(stdin);
	set_date(book, date);
	set_num(book, 1);
}

int subscribe_book(Book_List* list) {
	int result = 0;
	int found;
	int num_copies;
	Book book;
	ISBN book_isbn;

	fprintf(stdout, "\n-----------------------------------------------------------");
	fprintf(stdout, "\n\t\tIntroduce the book details");
	fprintf(stdout, "\n-----------------------------------------------------------");
	/*The ISBN is requested and introduced by the keyboard*/
	introduce_isbn(book_isbn);
	/*Check if the book is already in the list*/
	found = search_book_by_isbn(list, book_isbn);
	if(found != 0) {	// A book with the same ISBN was found in the list
		book = get_current_book(*list);
		num_copies = get_num(book);
		if(num_copies < MAX_NUM){
			num_copies++;
		}
		set_num(&book, num_copies);
		replace_book(list, book, book_isbn);
		result = 1;
	} else {
		introduce_book_details(&book, book_isbn);
		result = add_book_last(list, book);
	}
	return result;
}

int unsubscribe_book(Book_List* books, Loan_List* loans){
	int result = 0;
	int found;
	int search_loan;
	ISBN book_isbn;

	introduce_isbn(book_isbn);
	search_loan = loans_by_isbn(loans, book_isbn);

	if(search_loan == 0) {	// If there are no loans with this book, then it can be deleted
		found = search_book_by_isbn(books, book_isbn);
		if(found == -1) {
			delete_first_book(books);
			result = 1;
		} else if (found == 1) {
			delete_after_current_book(books);
			result = 1;
		}
	} else {
		result = -1;
	}
	return result;
}

int find_book(Book_List* list) {
	int result = 0;
	StringBook book_title;
	Book book;

	introduce_title(book_title);
	if(search_book_by_title(list, book_title)){
		result = 1;
		book = get_current_book(*list);
		print_book(book);
	}
	return result;
}

int loan_book(Book_List* books, Loan_List* loans){
	int result = 0;
	int search;
	Book book;
	Loan loan;
	ISBN book_isbn;
	int member_id;
	int num_loans;

	if(books != NULL && !is_empty_book_list(*books)) {
		introduce_isbn(book_isbn);
		search = search_book_by_isbn(books, book_isbn);
		if(search != 0) {
			book = get_current_book(*books);
			num_loans = loans_by_isbn(loans, book_isbn);
			if(num_loans < get_num(book)) {
				introduce_member_id(&member_id);
				if(search_loan(loans, book_isbn, member_id) == 0) {
					set_isbn_loan(&loan, book_isbn);
					set_id_loan(&loan, member_id);
					result = add_loan_last(loans, loan);
				} else {
					result = -3;
				}

			} else {
				result = -2;
			}
		} else {
			result = -1;
		}
	}
	return result;
}

int return_book(Loan_List* loans) {
	int result = 0;
	int find;
	ISBN book_isbn;
	int member_id;
	if(loans != NULL && !is_empty_loan_list(*loans)) {
		introduce_isbn(book_isbn);
		introduce_member_id(&member_id);
		find = search_loan(loans, book_isbn, member_id);
		if(find != 0){
			if(find == 1) {
				delete_after_current_loan(loans);
				result = 1;
			} else if(find == -1) {
				delete_first_loan(loans);
				result = 1;
			}
		} else {
			result = -1;
		}
	}
	return result;
}

void read_books(FILE* pFile, Book_List* list) {
	int insert = 1;
	Book book;

	if(list != NULL) {
		fread(&book ,sizeof(Book) ,1, pFile);
		while(!feof(pFile) && !ferror(pFile) && insert) {
			insert = add_book_first(list, book);
			fread(&book ,sizeof(Book) ,1, pFile);
		}
	}
}

void read_loans(FILE *pFile, Loan_List* list) {
	int insert = 1;
	Loan loan;

	if(list != NULL) {
		fread(&loan, sizeof(Loan), 1, pFile);
		while(!feof(pFile) && !ferror(pFile) && insert) {
			insert = add_loan_first(list, loan);
			fread(&loan, sizeof(Loan), 1, pFile);
		}
	}
}

void write_books(FILE* pFile, Book_List* list) {
	Book book;
	if(pFile != NULL && list != NULL && !is_empty_book_list(*list)) {
		goto_first_book(list);
		while(!ferror(pFile) && is_current_book(*list)) {
			book = get_current_book(*list);
			fwrite(&book, sizeof(Book), 1, pFile);
			goto_next_book(list);
		}
	}
}

void write_loans(FILE* pFile, Loan_List* list) {
	Loan loan;
	if(pFile != NULL && list != NULL && !is_empty_loan_list(*list)) {
		goto_first_loan(list);
		while(!ferror(pFile) && is_current_loan(*list)) {
			loan = get_current_loan(*list);
			fwrite(&loan, sizeof(Loan), 1, pFile);
			goto_next_loan(list);
		}
	}
}
