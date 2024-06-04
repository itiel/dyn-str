// test.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/dynstr.h"

int main () {
  DynStr_t * dStr1 = NULL;
  DynStr_t * dStr2 = NULL;
  DynStr_t * dStrSlice = NULL;

  char * cStr = NULL;
  
  int compareResult;

  printf("Test creation from C string: ");

  assert(DynStr_fromCStr(&dStr1, "Hello, dynamic strings!") == 0);
  assert(DynStr_toCStr(dStr1, &cStr) == 0);
  assert(strcmp(cStr, "Hello, dynamic strings!") == 0);

  free(cStr);
  
  printf("✅\n");

  printf("Test concatenation: ");
  
  assert(DynStr_fromCStr(&dStr2, " Another dynamic string!") == 0);
  assert(DynStr_concatDynStr(dStr1, dStr2) == 0);
  assert(DynStr_toCStr(dStr1, &cStr) == 0);
  assert(strcmp(cStr, "Hello, dynamic strings! Another dynamic string!") == 0);
  
  free(cStr);

  printf("✅\n");

  printf("Test slicing: ");
  
  assert(
    DynStr_fromDynStrOpt(&dStrSlice, dStr1, 
      (DynStrOptions_t) { .offset = 7, .count = 15 }) == 0);
  assert(DynStr_toCStr(dStrSlice, &cStr) == 0);
  assert(strcmp(cStr, "dynamic strings") == 0);
  
  free(cStr);

  printf("✅\n");

  printf("Test comparison: ");
  
  assert(DynStr_compare(dStr1, dStr2, &compareResult) == 0);
  assert(compareResult == 0);

  printf("✅\n");

  // Clean up

  DynStr_end(&dStr1);
  DynStr_end(&dStr2);
  DynStr_end(&dStrSlice);

  printf("All tests passed.\n");

  return 0;
}
