#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/dynstr.h"

void DynStr_print (char * label, DynStr_t * dStr) {
  if (dStr == NULL) {
    printf("%s = Null\n\n", label);
  } else {
    printf(
      "%s = (count: %zu, capacity: %zu, content:", 
      label, dStr->count, dStr->capacity
    );

    if (dStr->count) {
      printf("\n  %.*s\n", (int) dStr->count, dStr->content);
    }

    printf(")\n\n");
  }
}

int main () {
  int retVal = 0;

  DynStr_t * dStr1 = NULL;
  DynStr_t * dStr2 = NULL;
  DynStr_t * dStr3 = NULL;
  DynStr_t * dStr4 = NULL;
  char * cStr = NULL;
  int result;

  printf("== DynStr Demo ==\n\n");
  
  printf("Let's go on a demo journey.\n\n");

  printf("Starting with an empty DynStr, dStr1.\n\n");

  DynStr_print("dStr1", dStr1);

  printf("Now, let's breathe life into it by initializing it with no source.\n\n");

  if (DynStr_init(&dStr1) != 0) {
    fprintf(stderr, "ERROR: Failed to initialize dStr1.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr1", dStr1);

  printf("Just for fun, let's finalize it immediately.\n\n");

  DynStr_end(&dStr1);
  
  DynStr_print("dStr1", dStr1);

  printf("Let's revive dStr1 with a C string: 'Oranges'.\n\n");

  if (DynStr_fromCStr(&dStr1, "Oranges") != 0) {
    fprintf(stderr, "ERROR: Failed to initialize dStr1.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr1", dStr1);

  printf("Time to spice things up! Adding ', Bananas' to dStr1.\n\n");

  if (DynStr_concatCStr(dStr1, ", Bananas") != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate C string to dStr1.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr1", dStr1);

  printf("Introducing dStr2, created from the dStr1.\n\n");

  if (DynStr_fromDynStr(&dStr2, dStr1) != 0) {
    fprintf(stderr, "ERROR: Failed to initialize dStr2.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr2", dStr2);

  printf("Adding more flavor: ', Apples and Pears.' to dStr2.\n\n");

  if (DynStr_concatCStr(dStr2, ", Apples and Pears. ") != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate C string to dStr2.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr2", dStr2);

  printf("Let's take a slice of dStr2 and add it to dStr1.\n\n");

  if (DynStr_concatDynStrOpt(dStr1, dStr2, (DynStrOptions_t) { .offset = 24, .count = 11 }) != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate dStr2 to dStr1.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr1", dStr1);

  printf("For the grand finale, let's concatenate dStr2 to itself.\n\n");

  if (DynStr_concatDynStr(dStr2, dStr2) != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate dStr2 to itself.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr2", dStr2);

  printf("Creating dStr3 from a part of dStr2. Watch its count and capacity!\n\n");

  if (DynStr_fromDynStrOpt(&dStr3, dStr2, (DynStrOptions_t) { .offset = 0, .count = 16 }) != 0) {
    fprintf(stderr, "ERROR: Failed to initialize dStr3.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr3", dStr3);

  printf("Let's ensure dStr3 is ready for more data by reserving additional memory.\n\n");

  if (DynStr_reserve(dStr3, dStr3->capacity + 5) != 0) {
    fprintf(stderr, "ERROR: Failed to reserve memory for dStr3.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr3", dStr3);

  printf("Adding more from dStr2 into dStr3.\n\n");

  if (DynStr_concatDynStrOpt(dStr3, dStr2, (DynStrOptions_t) { .offset = 15, .count = 20 }) != 0) {
    fprintf(stderr, "ERROR: Failed to concatenate dStr2 to dStr3.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr3", dStr3);

  printf("Let's generate a C string (cStr) from dStr3.\n\n");

  if (DynStr_toCStr(dStr3, &cStr) != 0) {
    fprintf(stderr, "ERROR: Failed to convert dStr3 to C string.\n");
    retVal = -1;
    goto cleanUp;
  }

  printf("cStr = %s\n\n", cStr);

  printf("Now, we'll initialize dStr4 with cStr as the source.\n\n");

  if (DynStr_fromCStr(&dStr4, cStr) != 0) {
    fprintf(stderr, "ERROR: Failed to initialize dStr4.\n");
    retVal = -1;
    goto cleanUp;
  }

  DynStr_print("dStr4", dStr4);

  printf("Let's compare dStr3 and dStr4 to see if they're equal.\n\n");

  if (DynStr_compare(dStr3, dStr4, &result) != 0) {
    fprintf(stderr, "ERROR: Failed to compare dStr3 and dStr4.\n");
    retVal = -1;
    goto cleanUp;
  }

  printf("dStr3 == dStr4: %s\n\n", result ? "Equal" : "Not Equal");

  printf("Our journey is complete!\n");

cleanUp:
  DynStr_end(&dStr1);
  DynStr_end(&dStr2);
  DynStr_end(&dStr3);
  DynStr_end(&dStr4);

  if (cStr != NULL) {
    free(cStr);
  }

  return retVal;
}
