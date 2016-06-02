/*
 * loan_list.h
 *
 *  Created on: May 20, 2016
 *      Author: gabri
 */

#ifndef LOAN_LIST_H_
#define LOAN_LIST_H_

#include "loan.h"

typedef struct loan_node {
	Loan loan;
	struct loan_node* next;
}Loan_Node;

typedef struct {
	Loan_Node* first;
	Loan_Node* current;
	Loan_Node* last;
}Loan_List;

extern void create_loan_list(Loan_List* list);
extern int  is_empty_loan_list(const Loan_List list);
extern void goto_first_loan(Loan_List* list);
extern void goto_last_loan(Loan_List* list);
extern void goto_next_loan(Loan_List* list);
extern int  is_current_loan(const Loan_List list);
extern Loan get_current_loan(const Loan_List list);

extern int  add_loan_first(Loan_List* list, Loan loan);
extern int  add_loan_last(Loan_List* list, Loan loan);
extern int  add_loan_after_current(Loan_List* list, Loan loan);

extern void delete_first_loan(Loan_List* list);
extern void delete_after_current_loan(Loan_List* list);
extern void delete_loan_list(Loan_List* list);

extern void print_loan_list(const Loan_List list);
extern int  search_loan(Loan_List* list, ISBN isbn, int member_id);
extern int  loans_by_isbn(Loan_List* list, ISBN isbn);

#endif /* LOAN_LIST_H_ */
