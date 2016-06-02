/*
 * loan_list.c
 *
 *  Created on: May 20, 2016
 *      Author: gabri
 */

#include "loan_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Loan_Node* create_loan_node(Loan elem){
	Loan_Node* node = (Loan_Node* ) malloc(sizeof(Loan_Node));
	if(node != NULL){
		node->loan = elem;
		node->next = NULL;
	}
	return node;
}

extern void create_loan_list(Loan_List* list){
	list->first   = NULL;
	list->current = NULL;
	list->last    = NULL;
}

extern int is_empty_loan_list(const Loan_List list){
	return (list.first == NULL);
}

extern void goto_first_loan(Loan_List* list){
	if(list != NULL){
		list->current = list->first;
	}
}

extern void goto_last_loan(Loan_List* list){
	if(list != NULL){
		list->current = list->last;
	}
}

extern int is_current_loan(const Loan_List list){
	return (list.current != NULL);
}

extern void goto_next_loan(Loan_List* list){
	if(list != NULL && is_current_loan(*list)){
		list->current = list->current->next;
	}
}

extern Loan get_current_loan(const Loan_List list){
	Loan loan;
	if(is_current_loan(list)){
		loan = list.current->loan;
	}
	return loan;
}

extern int add_loan_first(Loan_List* list, Loan loan){
	int result = 0;
	Loan_Node* node;
	if(list != NULL){
		node = create_loan_node(loan);
		if(node != NULL){
			node->next = list->first;
			list->first = node;
			if(list->last == NULL){
				list->last = list->first;
			}
			result = 1;
		}
	}
	return result;
}

extern int  add_loan_after_current(Loan_List* list, Loan loan){
	int result = 0;
	Loan_Node* node;
	if(list != NULL && is_current_loan(*list)) {
		node = create_loan_node(loan);
		if(node != NULL) {
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

extern int  add_loan_last(Loan_List* list, Loan loan){
	int result = 0;
	if(list != NULL) {
		if(is_empty_loan_list(*list)){
			result = add_loan_first(list, loan);
		} else {
			goto_last_loan(list);
			result = add_loan_after_current(list, loan);
		}
	}
	return result;
}

extern void delete_first_loan(Loan_List* list){
	Loan_Node* node;
	if(list != NULL && !is_empty_loan_list(*list)){
		node = list->first;
		list->first = list->first->next;
		if(node == list->last){
			list->last = NULL;
		}
		free(node);
	}
}

extern void delete_after_current_loan(Loan_List* list){
	Loan_Node* node;
	if(list != NULL && is_current_loan(*list) && (list->current->next != NULL)){
		node = list->current->next;
		list->current->next = list->current->next->next;
		if(node == list->last){
			list->last = list->current;
		}
		free(node);
	}
}

extern void delete_loan_list(Loan_List* list){
	if(list != NULL){
		while(!is_empty_loan_list(*list)){
			delete_first_loan(list);
		}
	}
}

//Another way to code this function is Loan_List* list and using goto functions
extern void print_loan_list(const Loan_List list){
	Loan loan;
	Loan_Node* node;

	if(!is_empty_loan_list(list)){
		node = list.first;
		while(node != NULL){
			loan = node->loan;
			print_loan(loan);
			node = node->next;
		}
	}
}

extern int  search_loan(Loan_List* list, ISBN isbn, int member_id){
	int found = 0;
	int id;
	Loan_Node* node;
	Loan loan;
	ISBN isbn_loan;

	if(list != NULL && !is_empty_loan_list(*list)){
		goto_first_loan(list);
		if(is_current_loan(*list)){
			loan = get_current_loan(*list);
			get_isbn_loan(loan,isbn_loan);
			id = get_id_loan(loan);
			if(strcmp(isbn, isbn_loan) == 0 && id == member_id) {
				found = -1;
			} else {
				node = list->current->next;
				while(is_current_loan(*list) && node != NULL && found == 0){
					loan = get_current_loan(*list);
					get_isbn_loan(loan,isbn_loan);
					id = get_id_loan(loan);
					if(strcmp(isbn, isbn_loan) == 0 && id == member_id){
						found = 1;
					} else {
						goto_next_loan(list);
						node = list->current->next;
					}
				}
			}
		}
	}
	return found;
}

extern int  loans_by_isbn(Loan_List* list, ISBN isbn){
	int num_loans = 0;
	ISBN loan_isbn;
	Loan loan;
	if(list != NULL && !is_empty_loan_list(*list)){
		goto_first_loan(list);
		while(is_current_loan(*list)){
			loan = get_current_loan(*list);
			get_isbn_loan(loan, loan_isbn);
			if(strcmp(isbn, loan_isbn) == 0){
				num_loans++;
			}
			goto_next_loan(list);
		}
	}
	return num_loans;
}
