// dynstr.h

#ifndef _DYNSTR_H_
#define _DYNSTR_H_ 

#include <stddef.h>

typedef struct DynStr_t DynStr_t;

struct DynStr_t {
  size_t capacity;
  size_t count;
  char * content;
};

int DynStr_init (DynStr_t ** dStr);
int DynStr_end (DynStr_t ** dStr);
int DynStr_fromLiteral (DynStr_t ** dStr, char * srcLit);
int DynStr_fromDynStr (DynStr_t ** dStr, DynStr_t * srcDStr);
int DynStr_concatLiteral (DynStr_t * dStr, char * srcLit);
int DynStr_concatDynStr (DynStr_t * dStr, DynStr_t * srcDStr);
int DynStr_concat (DynStr_t * dStr, char * src, size_t srcSize);
int DynStr_reserve (DynStr_t * dStr, size_t requiredCapacity);
int DynStr_compare (DynStr_t * dStr1, DynStr_t * dStr2, int * result);
int DynStr_ensureNullTermination (DynStr_t * dStr);

#endif /* _DYNSTR_H_ */