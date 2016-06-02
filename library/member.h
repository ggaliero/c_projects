/*
 * member.h
 *
 *  Created on: Feb 27, 2016
 *      Author: gabri
 */

#ifndef MEMBER_H_
#define MEMBER_H_

#define STR_MEM_LEN		30
#define ID_LEN			10

typedef char StringMember 	[STR_MEM_LEN];

typedef struct {
	StringMember		name;			/// Memeber name
	StringMember		surname;		/// Member surname
	int					id;			/// Member identification number
}Member;

extern void print_member(const Member member);

/* Setter functions */
extern void set_name(Member* member, StringMember name);
extern void set_surname(Member* member, StringMember surname);
extern void set_id(Member* member, int id);

/* Getter functions */
extern void get_name(const Member member, StringMember name);
extern void get_surname(const Member member, StringMember surname);
extern int  get_id(const Member member);


#endif /* MEMBER_H_ */
