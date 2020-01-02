#ifndef BOOL_H_INCLUDED
#define BOOL_H_INCLUDED

typedef enum {
	FALSE, TRUE
} Bool;

Bool and(Bool b1, Bool b2);
Bool or(Bool b1, Bool b2);
Bool xor(Bool b1, Bool b2);
Bool si(Bool b1, Bool b2);
Bool sii(Bool b1, Bool b2);
Bool not(Bool b);

#endif
