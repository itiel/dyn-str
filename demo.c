// demo.c

#include <stdio.h>
#include "dynstr.h"

int main() {
  int retVal = 0;

  DynStr_t * str1 = NULL;
  DynStr_t * str2 = NULL;
  DynStr_t * str3 = NULL;
  
  int compareResult;

  // Initialize dynamic str1 from a literal

  if (DynStr_fromLiteral(&str1, "Hello, ") != 0) {
    fprintf(stderr, "Failed to initialize dynamic string from literal.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Concatenate another literal

  if (DynStr_concatLiteral(str1, "World") != 0) {
    fprintf(stderr, "Failed to concatenate literal.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Print it

  printf("String 1: %.*s\n", (int) str1->count, str1->content);

  // Initialize str2 from str1

  if (DynStr_fromDynStr(&str2, str1) != 0) {
    fprintf(stderr, "Failed to initialize dynamic string from another dynamic string.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Concatenate a literal

  if (DynStr_concatLiteral(str2, "!!!") != 0) {
    fprintf(stderr, "Failed to concatenate literal.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Ensure null termination 

  if (DynStr_ensureNullTermination(str2) != 0) {
    fprintf(stderr, "Failed to ensure null termination.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Print it

  printf("String 2: %s\n", str2->content);

  // Initialize str3 from a literal

  if (DynStr_fromLiteral(&str3, "Hello, World!!!") != 0) {
    fprintf(stderr, "Failed to initialize dynamic string from literal.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  // Print it

  printf("String 3: %.*s\n", (int) str3->count, str3->content);

  // Compare str2 and str3

  if (DynStr_compare(str2, str3, &compareResult) != 0) {
    fprintf(stderr, "Failed to compare dynamic strings.\n");
    
    retVal = -1;
    goto cleanUp;
  }

  printf("String 2 == String 3: %s\n", compareResult ? "Equal" : "Not Equal");

  cleanUp:

  DynStr_end(&str1);
  DynStr_end(&str2);
  DynStr_end(&str3);

  return retVal;
}
