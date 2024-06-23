// test.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/dyn-str.h" 
 
#define TEST(desc, test) \
  ({ \
    if (test) { \
      printf("✅ %s\n", desc); \
    } else { \
      printf("❌ %s\n", desc); \
      exit(EXIT_FAILURE); \
    } \
  }) 

#define TEST_STEP(test) \
  ({ \
    int __result = (test); \
    if (!__result) { \
      fprintf(stderr, "Assestion failed: (%s)\n", #test); \
    } \
    __result; \
  })

int main () {
  DynStr_t * dStr1 = NULL;
  DynStr_t * dStr2 = NULL;
  DynStr_t * dStrSlice = NULL;

  char * cStr = NULL;
  
  int result;

  printf("== DynStr Test ==\n\n");

  TEST("Dynamic string creation and destruction",
    TEST_STEP(DynStr_init(&dStr1) == 0) &&
    TEST_STEP(dStr1->count == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(dStr1 == NULL)
  );

  TEST("Dynamic string creation from C string",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Hello, World!") == 0) &&
    TEST_STEP(dStr1->count > 0) &&
    TEST_STEP(memcmp(dStr1->content, "Hello, World!", dStr1->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0)
  );

  TEST("Dynamic string creation from another dynamic string",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Dynamica allocation!") == 0) &&
    TEST_STEP(DynStr_fromDynStr(&dStr2, dStr1) == 0) &&
    TEST_STEP(dStr1->count == dStr2->count) &&
    TEST_STEP(memcmp(dStr1->content, dStr2->content, dStr1->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(DynStr_end(&dStr2) == 0)
  );

  TEST("Dynamic string creation from another dynamic string with options",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Not a C string.") == 0) &&
    TEST_STEP(
      DynStr_fromDynStrOpt(&dStr2, dStr1, (DynStrOptions_t) {
        .offset = 8,
        .count = 6,
      }) == 0
    ) &&
    TEST_STEP(memcmp(dStr2->content, "string", dStr2->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(DynStr_end(&dStr2) == 0)
  );

  TEST("Concatenation of C string to dynamic string",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Segmentation") == 0) &&
    TEST_STEP(DynStr_concatCStr(dStr1, " fault.") == 0) &&
    TEST_STEP(memcmp(dStr1->content, "Segmentation fault.", dStr1->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) 
  );

  TEST("Concatenation of dynamic string to another dynamic string",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Heap") == 0) &&
    TEST_STEP(DynStr_fromCStr(&dStr2, " allocation.") == 0) &&
    TEST_STEP(DynStr_concatDynStr(dStr1, dStr2) == 0) &&
    TEST_STEP(memcmp(dStr1->content, "Heap allocation.", dStr1->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(DynStr_end(&dStr2) == 0) 
  );

  TEST("Concatenation of dynamic string to another dynamic string with options",
    TEST_STEP(DynStr_fromCStr(&dStr1, "String") == 0) &&
    TEST_STEP(DynStr_fromCStr(&dStr2, " concatenation.") == 0) &&
    TEST_STEP(
      DynStr_concatDynStrOpt(dStr1, dStr2, (DynStrOptions_t) {
        .offset = 0,
        .count = 7,
      }) == 0
    ) &&
    TEST_STEP(memcmp(dStr1->content, "String concat", dStr1->count) == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(DynStr_end(&dStr2) == 0) 
  );

  TEST("Dynamic strings comparison",
    TEST_STEP(DynStr_fromCStr(&dStr1, "Memory leak.") == 0) &&
    TEST_STEP(DynStr_fromCStr(&dStr2, "Memory leak.") == 0) &&
    TEST_STEP(DynStr_compare(dStr1, dStr2, &result) == 0) &&
    TEST_STEP(result) &&
    TEST_STEP(DynStr_end(&dStr1) == 0) &&
    TEST_STEP(DynStr_end(&dStr2) == 0)
  );

  TEST("C string creation from dynamic string",
    TEST_STEP(DynStr_fromCStr(&dStr1, "String copy.") == 0) &&
    TEST_STEP(DynStr_toCStr(dStr1, &cStr) == 0) &&
    TEST_STEP(cStr != NULL) &&
    TEST_STEP(strcmp(cStr, "String copy.") == 0) &&
    TEST_STEP(DynStr_end(&dStr1) == 0)
  );

  free(cStr);

  TEST("Dynamic string memory reservation", 
    TEST_STEP(DynStr_init(&dStr1) == 0) &&
    TEST_STEP((result = (int) dStr1->capacity) == 0 || result > 0) &&
    TEST_STEP(DynStr_reserve(dStr1, result + 1028) == 0) &&
    TEST_STEP(dStr1->capacity > result) &&
    TEST_STEP(DynStr_end(&dStr1) == 0)
  );

  printf("\nAll tests passed.\n");

  return 0;
}
