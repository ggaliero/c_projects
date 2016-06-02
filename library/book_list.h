/*
 * book_list.h
 *
 *  Created on: Feb 27, 2016
 *      Author: gabri
 */

#ifndef BOOK_LIST_H_
#define BOOK_LIST_H_

#include "book.h"

typedef struct book_node {
	Book book;
	struct book_node *next;
} Book_Node;

typedef struct {
	Book_Node* first;
	Book_Node* current;
	Book_Node* last;
} Book_List;

extern void create_book_list(Book_List* list);
extern int	is_empty_book_list(const Book_List list);
extern void goto_first_book(Book_List* list);
extern void goto_last_book(Book_List* list);
extern void goto_next_book(Book_List* list);
extern int  is_current_book(const Book_List list);
extern Book get_current_book(const Book_List list);

extern int add_book_first(Book_List* list, Book book);
extern int add_book_after_current(Book_List* list, Book book);
extern int add_book_last(Book_List* list, Book book);

extern void delete_first_book(Book_List* list);
extern void delete_after_current_book(Book_List* list);
extern void delete_book_list_book(Book_List* list);

extern void print_book_list(Book_List* list);
extern int  search_book_by_title(Book_List* list, StringBook title);
extern int  search_book_by_isbn(Book_List* list, ISBN isbn);

extern void replace_book(Book_List* list, Book book, ISBN isbn);

#endif /* BOOK_LIST_H_ */
