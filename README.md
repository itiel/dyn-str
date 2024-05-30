# DynStr 

A simple C library for working with dynamically allocated strings. This library provides functions to initialize, concatenate, and manage dynamic strings with ease.

## Features

- Initialize dynamic strings from literals or other dynamic strings
- Concatenate literals or other dynamic strings
- Ensure null termination of dynamic strings
- Compare dynamic strings
- Automatically manage memory allocation and resizing

## Installation

To use this library, include `dynstr.h` and `dynstr.c` in your project. Compile them together with your source files.

## Demo

Take for instance this example program.

```c
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
```

After successful compilation and execution,

```bash
cc -o demo demo.c dynstr.c 
./demo 
```

It should print this to the terminal:

```
String 1: Hello, World
String 2: Hello, World!!!
String 3: Hello, World!!!
String 2 == String 3: Equal
```

## API Reference

All methods in the API return `0` on success and `-1` on faliure.

### `int DynStr_init(DynStr_t **dStr)`

Initializes an empty dynamic string.

### `int DynStr_end(DynStr_t **dStr)`

Frees the memory associated with the dynamic string.

### `int DynStr_fromLiteral(DynStr_t **dStr, char *srcLit)`

Initializes a dynamic string from a literal.

### `int DynStr_fromDynStr(DynStr_t **dStr, DynStr_t *srcDStr)`

Initializes a dynamic string from another dynamic string.

### `int DynStr_concatLiteral(DynStr_t *dStr, char *srcLit)`

Concatenates a literal to the dynamic string.

### `int DynStr_concatDynStr(DynStr_t *dStr, DynStr_t *srcDStr)`

Concatenates another dynamic string to the dynamic string.

### `int DynStr_concat(DynStr_t *dStr, char *src, size_t srcSize)`

Concatenates a string with a specified size to the dynamic string.

### `int DynStr_reserve(DynStr_t *dStr, size_t requiredCapacity)`

Reserves memory for the dynamic string to ensure it can hold at least `requiredCapacity` bytes.

### `int DynStr_compare(DynStr_t *dStr1, DynStr_t *dStr2, int *result)`

Compares two dynamic strings. Sets `result` to 1 if they are equal, otherwise 0.

### `int DynStr_ensureNullTermination(DynStr_t *dStr)`

Ensures the dynamic string is null-terminated.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.