/*
 * member.c
 *
 *  Created on: Feb 27, 2016
 *      Author: gabri
 */

#include "member.h"
#include <stdio.h>
#include <string.h>

void print_member(const Member member) {
	fprintf(stdout, "\nName: ");
	fputs(member.name, stdout);
	fprintf(stdout, "\nSurname: ");
	fputs(member.surname, stdout);
	fprintf(stdout, "\nID: %d", member.id);
}

void set_name(Member* member, StringMember name) {
	if(member != NULL) {
		strcpy(member->name, name);
	}
}

void set_surname(Member* member, StringMember surname) {
	if(member != NULL) {
		strcpy(member->surname, surname);
	}
}

void set_id(Member* member, int id) {
	if(member != NULL) {
		member->id = id;
	}
}

void get_name(const Member member, StringMember name) {
	strcpy(name, member.name);
}

void get_surname(const Member member, StringMember surname) {
	strcpy(surname, member.surname);
}

int get_id(const Member member) {
	return member.id;
}
