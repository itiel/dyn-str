// demo.c 

#include <stdio.h>
#include <stdlib.h>
#include "lib/dynstr.h"

int main () {
  int retVal = 0;

  DynStr_t * dStr1 = NULL;
  DynStr_t * dStr2 = NULL;
  DynStr_t * dStr3 = NULL;
  DynStr_t * dStr4 = NULL;
  DynStr_t * dStrSlice = NULL;
  char * cStr = NULL;

  int compareResult;

  printf("Creating a DynStr from a C string literal.\n");

  if (DynStr_fromCStr(&dStr1, "Hello, dynamic strings!") != 0) {
    fprintf(stderr, "ERROR: Failed to create dStr1.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("dStr1: %.*s\n\n", (int) dStr1->count, dStr1->content);

  printf("Creating another DynStr from a C string literal.\n");

  if (DynStr_fromCStr(&dStr2, " Another dynamic string!") != 0) {
    fprintf(stderr, "ERROR: Failed to create dStr2.\n");

    retVal = -1;
    goto cleanUp;
  }

  printf("dStr2: %.*s\n\n", (int) dStr2->count, dStr2->content);

  printf("Concatenating dStr2 to dStr1.\n");

  if (DynStr_concatDynStr(dStr1, dStr2) != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate dStr2 to dStr1.\n");
    
    retVal = -1;
    goto cleanUp;
  }
  
  printf("dStr1: %.*s\n\n", (int) dStr1->count, dStr1->content);

  printf("Concatenating part of dStr2 to dStr1.\n");

  if (
    DynStr_concatDynStrOpt(
      dStr1, dStr2, (DynStrOptions_t) {
        .offset = 16, 
        .count = 8, 
      }) != 0
  ) {
    fprintf(stderr, "ERROR: Failed to concatenate dStr2 to dStr1.\n");
    
    retVal = -1;
    goto cleanUp;
  }
  
  printf("dStr1: %.*s\n\n", (int) dStr1->count, dStr1->content);

  printf("Creating a slice from dStr1.\n");

  if (
    DynStr_fromDynStrOpt(
      &dStrSlice, dStr1, (DynStrOptions_t) {
        .offset = 7, 
        .count = 7, 
      }) != 0
  ) {
    fprintf(stderr, "ERROR: Failed to create slice from dStr1.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("dStrSlice: %.*s\n\n", (int) dStrSlice->count, dStrSlice->content);

  printf("Creating another DynStr from the slice.\n");

  if (DynStr_fromDynStr(&dStr3, dStrSlice) != 0) {
    fprintf(stderr, "ERROR: Failed to create dStr3 from dStrSlice.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("dStr3: %.*s\n\n", (int) dStr3->count, dStr3->content);

  printf("Comparing the last 2.\n");

  if (DynStr_compare(dStrSlice, dStr3, &compareResult) != 0) {
    fprintf(stderr, "ERROR: Failed to compare dStrSlice and dStr3.\n");

    retVal = -1;
    goto cleanUp;
  }

  printf("dStrSlice == dStr3: %s\n\n", compareResult ? "Equal" : "Not Equal");

  printf("Creating one last DynStr from a C string literal.\n");

  if (DynStr_fromCStr(&dStr4, "Thank you :)") != 0) {
    fprintf(stderr, "ERROR: Failed to create dStr4.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("dStr4: %.*s\n\n", (int) dStr4->count, dStr4->content);

  printf("Finally, creating a C string from dStr4.\n");

  if (DynStr_toCStr(dStr4, &cStr) != 0) {
    fprintf(stderr, "ERROR: Failed to create cStr from dStr4.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("cStr: %s\n\n", cStr);

  cleanUp:

  DynStr_end(&dStr1);
  DynStr_end(&dStr2);
  DynStr_end(&dStr3);
  DynStr_end(&dStr4);
  DynStr_end(&dStrSlice);

  if (cStr != NULL) {
    free(cStr);
  }

  return retVal;
}
