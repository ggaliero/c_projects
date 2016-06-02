/*
 * book.h
 *
 *  Created on: Feb 26, 2016
 *      Author: gabri
 */

#ifndef BOOK_H_
#define BOOK_H_

#define MAX_LEN		50
#define ISBN_LEN	18
#define MAX_NUM		20

typedef char StringBook		[MAX_LEN];
typedef char ISBN  			[ISBN_LEN];

typedef struct {
	StringBook 	title;			/// Title of the book
	StringBook 	author;			/// Author
	StringBook 	editorial;		/// Editorial
	ISBN   		isbn;			/// ISBN
	int	   		date;			/// Publication year
	int	   		num;			///	Number of copies
}Book;

extern void print_book(const Book book);

/* Setter functions */
extern void set_title(Book* book, StringBook title);
extern void set_author(Book* book, StringBook author);
extern void set_editorial(Book* book,  StringBook editorial);
extern void set_isbn(Book* book, StringBook isbn);
extern void set_date(Book* book, int date);
extern void set_num(Book* book, int num);

/* Getter functions */
extern void get_title(const Book book, StringBook title);
extern void get_author(const Book book, StringBook author);
extern void get_editorial(const Book book, StringBook editorial);
extern void get_isbn(const Book book, ISBN isbn);
extern int	get_date(const Book book);
extern int	get_num(const Book book);


#endif /* BOOK_H_ */
