/*
 * loan.c
 *
 *  Created on: Feb 27, 2016
 *      Author: gabri
 */

#include "loan.h"
#include <stdio.h>
#include <string.h>

void print_loan(const Loan loan) {
	fprintf(stdout, "\nISBN: ");
	fputs(loan.book_isbn, stdout);
	fprintf(stdout, "\nMember ID: %d", loan.member_id);
	fprintf(stdout, "\n--------------------------------------------------------------------------------");
}

void set_isbn_loan(Loan* loan, ISBN isbn) {
	if(loan != NULL) {
		strcpy(loan->book_isbn, isbn);
	}
}

void set_id_loan(Loan* loan, int id) {
	if(loan != NULL) {
		loan->member_id = id;
	}
}

void get_isbn_loan(const Loan loan, ISBN isbn) {
	strcpy(isbn, loan.book_isbn);
}

int get_id_loan(const Loan loan) {
	return loan.member_id;
}
