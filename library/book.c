/*
 * book.c
 *
 *  Created on: Feb 26, 2016
 *      Author: gabri
 */

#include "book.h"
#include <stdio.h>
#include <string.h>

void print_book(const Book book) {
	fprintf(stdout,"\nTitle: ");
	fputs(book.title, stdout);
	fprintf(stdout,"\nAuthor: ");
	fputs(book.author, stdout);
	fprintf(stdout,"\nEditorial: ");
	fputs(book.editorial, stdout);
	fprintf(stdout,"\nPublication date: %d", book.date);
	fprintf(stdout,"\nISBN: ");
	fputs(book.isbn, stdout);
	fprintf(stdout,"\nNumber of copies: %d", book.num);
	fprintf(stdout, "\n--------------------------------------------------------------------------------");
}

void set_title(Book* book, StringBook title) {
	if(book != NULL) {
		strcpy(book->title, title);
	}
}

void set_author(Book* book, StringBook author) {
	if(book != NULL) {
		strcpy(book->author, author);
	}
}

void set_editorial(Book* book, StringBook editorial) {
	if(book != NULL) {
		strcpy(book->editorial, editorial);
	}
}

void set_isbn(Book* book, ISBN isbn) {
	if(book != NULL) {
		strcpy(book->isbn, isbn);
	}
}

void set_date(Book* book, int date) {
	if(book != NULL) {
		book->date = date;
	}
}

void set_num(Book* book, int num) {
	if(book != NULL) {
		if(num > MAX_NUM) {
			num = MAX_NUM;
		}
		book->num = num;
	}
}

void get_title(const Book book, StringBook title) {
	strcpy(title, book.title);
}

void get_author(const Book book, StringBook author) {
	strcpy(author, book.author);
}

void get_editorial(const Book book, StringBook editorial) {
	strcpy(editorial, book.editorial);
}

void get_isbn(const Book book, ISBN isbn) {
	strcpy(isbn, book.isbn);
}

int	get_date(const Book book) {
	return book.date;
}

int get_num(const Book book) {
	return book.num;
}
