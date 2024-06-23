// dyn-str.h

#ifndef _DYNSTR_H_
#define _DYNSTR_H_ 

#include <stddef.h>

typedef struct DynStr_t DynStr_t;
typedef struct DynStrOptions_t DynStrOptions_t;

struct DynStr_t {
  char * content;
  size_t capacity;
  size_t count;
};

struct DynStrOptions_t {
  size_t offset;
  size_t count;
};

int DynStr_init (DynStr_t ** dStr);
int DynStr_end (DynStr_t ** dStr);

int DynStr_fromCStr (DynStr_t ** dStr, char * srcCStr);
int DynStr_fromDynStr (DynStr_t ** dStr, DynStr_t * srcDStr);
int DynStr_fromDynStrOpt (DynStr_t ** dStr, DynStr_t * srcDStr, DynStrOptions_t opt);

int DynStr_concatCStr (DynStr_t * dStr, char * srcCStr);
int DynStr_concatDynStr (DynStr_t * dStr, DynStr_t * srcDStr);
int DynStr_concatDynStrOpt (DynStr_t * dStr, DynStr_t * srcDStr, DynStrOptions_t opt);

int DynStr_compare (DynStr_t * dStr1, DynStr_t * dStr2, int * result);
int DynStr_toCStr (DynStr_t * dStr, char ** destCStr);

int DynStr_reserve (DynStr_t * dStr, size_t requiredCapacity);

#endif /* _DYNSTR_H_ */