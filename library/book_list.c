/*
 * book_list.c
 *
 *  Created on: May 20, 2016
 *      Author: gabri
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_list.h"

Book_Node* create_book_node(const Book elem){
	Book_Node* node = (Book_Node*) malloc(sizeof(Book_Node));
	if(node != NULL){
		node->book = elem;
		node->next = NULL;
	}
	return node;
}

extern void create_book_list(Book_List* list){
	list->first   = NULL;
	list->current = NULL;
	list->last    = NULL;
}

extern int is_empty_book_list(const Book_List list){
	return (list.first == NULL);
}

extern void goto_first_book(Book_List* list){
	if(list != NULL){
		list->current = list->first;
	}
}

extern void goto_last_book(Book_List* list){
	if(list != NULL){
		list->current = list->last;
	}
}

extern int is_current_book(const Book_List list){
	return (list.current != NULL);
}

extern void goto_next_book(Book_List* list){
	if(list != NULL && (is_current_book(*list))){
		list->current = list->current->next;
	}
}

extern Book get_current_book(const Book_List list){
	Book elem;
	if(is_current_book(list)){
		elem = list.current->book;
	}
	return elem;
}

extern int add_book_first(Book_List* list, Book book){
	int result = 0;
	Book_Node* node = create_book_node(book);
	if(list != NULL){
		node->next = list->first;
		list->first = node;
		if(list->last == NULL){
			list->last = node;
		}
		result = 1;
	}
	return result;
}

extern int add_book_after_current(Book_List* list, Book book){
	int result = 0;
	Book_Node* node;
	if(is_current_book(*list)){
		node = create_book_node(book);
		if(node != NULL){
			node->next = list->current->next;
			list->current->next = node;
			if(list->current == list->last){
				list->last = node;
			}
			result = 1;
		}
	}
	return result;
}

extern int add_book_last(Book_List* list, Book book){
	int result = 0;
	if(is_empty_book_list(*list)){
		result = add_book_first(list, book);
	} else {
		goto_last_book(list);
		result = add_book_after_current(list, book);
	}
	return result;
}

extern void delete_first_book(Book_List* list){
	Book_Node* node;
	if(!is_empty_book_list(*list)){
		node = list->first;
		list->first = list->first->next;
		if(list->last == node){
			list->last = NULL;
		}
		free(node);
	}
}

extern void delete_after_current_book(Book_List* list) {
	Book_Node* node;
	if(is_current_book(*list) && list->current->next != NULL){
		node = list->current->next;
		list->current->next = node->next;
		if(list->last == node){
			list->last = list->current;
		}
		free(node);
	}
}

extern void delete_book_list(Book_List* list){
	if(list != NULL){
		while(!is_empty_book_list(*list)){
			delete_first_book(list);
		}
	}
}

extern void print_book_list(Book_List* list){
	Book book;
	goto_first_book(list);
	while(is_current_book(*list)){
		book = get_current_book(*list);
		print_book(book);
		goto_next_book(list);
	}
}

extern int search_book_by_title(Book_List* list, StringBook title){
	int found = 0;
	Book book;
	StringBook book_title;
	if(!is_empty_book_list(*list)){
		goto_first_book(list);
		while(is_current_book(*list) && !found){
			book = get_current_book(*list);
			get_title(book, book_title);
			if(strcmp(title, book_title) == 0){
				found = 1;
			} else {
				goto_next_book(list);
			}
		}
	}
	return found;
}

extern int search_book_by_isbn(Book_List* list, ISBN isbn){
	int found = 0;
	Book book;
	ISBN book_isbn;
	if(!is_empty_book_list(*list)){
		goto_first_book(list);
		book = get_current_book(*list);
		get_isbn(book, book_isbn);
		if(strcmp(isbn,book_isbn) == 0) {
			found = -1;
		} else {
			goto_next_book(list);
			while(is_current_book(*list) && !found){
				book = get_current_book(*list);
				get_isbn(book, book_isbn);
				if(strcmp(isbn, book_isbn) == 0){
					found = 1;
				} else {
					goto_next_book(list);
				}
			}
		}
	}
	return found;
}

extern void replace_book(Book_List* list, Book book, ISBN isbn){
	int found;
	if(!is_empty_book_list(*list)){
		found = search_book_by_isbn(list, isbn);
		if(found == -1){
			delete_first_book(list);
			add_book_first(list, book);
		} else if(found == 1){
			delete_after_current_book(list);
			add_book_after_current(list, book);
		}
	}
}
