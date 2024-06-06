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
  
  int result;

  printf("== DynStr Demo ==\n\n");

  printf("Dynamic string creation and destruction\n");

  assert(DynStr_init(&dStr1) == 0);
  assert(dStr1->count == 0);
  assert(DynStr_end(&dStr1) == 0);
  assert(dStr1 == NULL);
  
  printf("Result: ✅\n");

  printf("Dynamic string creation from C string\n");

  assert(DynStr_fromCStr(&dStr1, "Hello, World!") == 0);
  assert(dStr1->count > 0);
  assert(memcmp(dStr1->content, "Hello, World!", dStr1->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  
  printf("Result: ✅\n");

  printf("Dynamic string creation from another dynamic string\n");

  assert(DynStr_fromCStr(&dStr1, "Dynamica allocation!") == 0);
  assert(DynStr_fromDynStr(&dStr2, dStr1) == 0);
  assert(dStr1->count == dStr2->count);
  assert(memcmp(dStr1->content, dStr2->content, dStr1->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  assert(DynStr_end(&dStr2) == 0);
  
  printf("Result: ✅\n");

  printf("Dynamic string creation from another dynamic string with options\n");

  assert(DynStr_fromCStr(&dStr1, "Not a C string.") == 0);
  assert(
    DynStr_fromDynStrOpt(&dStr2, dStr1, (DynStrOptions_t) {
      .offset = 8,
      .count = 6,
    }) == 0
  );
  assert(memcmp(dStr2->content, "string", dStr2->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  assert(DynStr_end(&dStr2) == 0);
  
  printf("Result: ✅\n");

  printf("Concatenation of C string to dynamic string\n");

  assert(DynStr_fromCStr(&dStr1, "Segmentation") == 0);
  assert(DynStr_concatCStr(dStr1, " fault.") == 0);
  assert(memcmp(dStr1->content, "Segmentation fault.", dStr1->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  
  printf("Result: ✅\n");

  printf("Concatenation of dynamic string to another dynamic string\n");

  assert(DynStr_fromCStr(&dStr1, "Heap") == 0);
  assert(DynStr_fromCStr(&dStr2, " allocation.") == 0);
  assert(DynStr_concatDynStr(dStr1, dStr2) == 0);
  assert(memcmp(dStr1->content, "Heap allocation.", dStr1->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  assert(DynStr_end(&dStr2) == 0);
  
  printf("Result: ✅\n");

  printf("Concatenation of dynamic string to another dynamic string with options\n");

  assert(DynStr_fromCStr(&dStr1, "String") == 0);
  assert(DynStr_fromCStr(&dStr2, " concatenation.") == 0);
  assert(
    DynStr_concatDynStrOpt(dStr1, dStr2, (DynStrOptions_t) {
      .offset = 0,
      .count = 7,
    }) == 0
  );
  assert(memcmp(dStr1->content, "String concat", dStr1->count) == 0);
  assert(DynStr_end(&dStr1) == 0);
  assert(DynStr_end(&dStr2) == 0);
  
  printf("Result: ✅\n");

  printf("Dynamic strings comparison\n");

  assert(DynStr_fromCStr(&dStr1, "Memory leak.") == 0);
  assert(DynStr_fromCStr(&dStr2, "Memory leak.") == 0);
  assert(DynStr_compare(dStr1, dStr2, &result) == 0);
  assert(result);
  assert(DynStr_end(&dStr1) == 0);
  assert(DynStr_end(&dStr2) == 0);
  
  printf("Result: ✅\n");

  printf("C string creation from dynamic string\n");

  assert(DynStr_fromCStr(&dStr1, "String copy.") == 0);
  assert(DynStr_toCStr(dStr1, &cStr) == 0);
  assert(cStr != NULL);
  assert(strcmp(cStr, "String copy.") == 0);
  assert(DynStr_end(&dStr1) == 0);

  free(cStr);
  
  printf("Result: ✅\n");

  printf("Dynamic string memory reservation\n");

  assert(DynStr_init(&dStr1) == 0);
  assert((result = (int) dStr1->capacity) == 0 || result > 0);
  assert(DynStr_reserve(dStr1, result + 1028) == 0);
  assert(dStr1->capacity > result);
  assert(DynStr_end(&dStr1) == 0);
  
  printf("Result: ✅\n");

  printf("All tests passed.\n");

  return 0;
}
