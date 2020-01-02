#include "bool.h"

Bool and(Bool b1, Bool b2){
	return b1 == TRUE && b2 == TRUE? TRUE : FALSE;
}
Bool or(Bool b1, Bool b2){
	return b1 == FALSE && b2 == FALSE? FALSE : TRUE;
}
Bool xor(Bool b1, Bool b2){
	return b1 != b2 ? TRUE : FALSE;
}
Bool si(Bool b1, Bool b2){
	return b1 == FALSE && b1 == TRUE? FALSE : TRUE;
}
Bool sii(Bool b1, Bool b2){
	return b1 == b2? TRUE : FALSE;
}
Bool not(Bool b){
	return b == TRUE? FALSE : TRUE;
}
