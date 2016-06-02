/*
 * loan.h
 *
 *  Created on: Feb 27, 2016
 *      Author: gabri
 */

#ifndef LOAN_H_
#define LOAN_H_

#include "book.h"

typedef struct {
	ISBN		book_isbn;
	int			member_id;
}Loan;

extern void print_loan(const Loan loan);

extern void set_isbn_loan(Loan* loan, ISBN isbn);
extern void set_id_loan(Loan* loan, int id);

extern void get_isbn_loan(const Loan loan, ISBN isbn);
extern int	get_id_loan(const Loan loan);

#endif /* LOAN_H_ */
