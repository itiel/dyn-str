# DynStr API Reference

## Overview

This reference provides a detailed overview of the functions and types defined in [`dynstr.h`](/lib/dynstr.h). 

For usage examples, please refer to the [`demo.c`](/demo.c) and [`test.c`](/test.c) programs included in the project.

## Terminology

### `DynStr_t`

`DynStr_t` is a struct that represents a dynamic string. The array of characters contained in a `DynStr_t` is not null-terminated.

### C String

A C String (or C-style string) is a null-terminated character array, a sequence of characters followed by a null character (`'\0'`). In the context of this library, it could either be a literal or dynamically allocated.

## Types

### `[struct] DynStr_t`

Represents a dynamic string.

- **Fields**:
  - `char * content`: Pointer to the string array (not null-terminated).
  - `size_t capacity`: The allocated capacity.
  - `size_t count`: The current length of the string.

### `[struct] DynStrOptions_t`

Options for creating a `DynStr_t` slice from another `DynStr_t`.

- **Fields**:
  - `size_t offset`: The starting offset.
  - `size_t count`: The number of bytes.

## Functions

### Initialization and Cleanup

#### `int DynStr_init (DynStr_t ** dStr)`

Initializes a new `DynStr_t`.

- **Parameters**: 
  - `dStr`: A pointer to a `DynStr_t` pointer.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

#### `int DynStr_end (DynStr_t ** dStr)`

Cleans up and frees memory used by a `DynStr_t`.

- **Parameters**: 
  - `dStr`: A pointer to a `DynStr_t` pointer.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

### Creation from reference

#### `int DynStr_fromCStr (DynStr_t ** dStr, char * srcCStr)`

Creates a `DynStr_t` from a C string.

- **Parameters**: 
  - `dStr`: A pointer to a `DynStr_t` pointer.
  - `srcCStr`: The source C string.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

#### `int DynStr_fromDynStr (DynStr_t ** dStr, DynStr_t * srcDStr)`

Creates a `DynStr_t` from another `DynStr_t`.

- **Parameters**: 
  - `dStr`: A pointer to a `DynStr_t` pointer.
  - `srcDStr`: The source `DynStr_t`.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

#### `int DynStr_fromDynStrOpt (DynStr_t ** dStr, DynStr_t * srcDStr, DynStrOptions_t opt)`

Creates a `DynStr_t` from a slice of another `DynStr_t`.

- **Parameters**: 
  - `dStr`: A pointer to a `DynStr_t` pointer.
  - `srcDStr`: The source `DynStr_t`.
  - `opt`: A `DynStrOptions_t` struct specifying the offset and count.
- **Returns**: 
  - `0` on success.
  - `-1` on failure (`opt.offset + opt.count > srcDStr->count`).

### Concatenation

#### `int DynStr_concatCStr (DynStr_t * dStr, char * srcCStr)`

Concatenates a C string to a `DynStr_t`.

- **Parameters**: 
  - `dStr`: The destination `DynStr_t`.
  - `srcCStr`: The source C string.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

#### `int DynStr_concatDynStr (DynStr_t * dStr, DynStr_t * srcDStr)`

Concatenates another `DynStr_t` to a `DynStr_t`.

- **Parameters**: 
  - `dStr`: The destination `DynStr_t`.
  - `srcDStr`: The source `DynStr_t`.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

#### `int DynStr_concatDynStrOpt (DynStr_t * dStr, DynStr_t * srcDStr, DynStrOptions_t opt)`

Concatenates another `DynStr_t` to a `DynStr_t`.

- **Parameters**: 
  - `dStr`: The destination `DynStr_t`.
  - `srcDStr`: The source `DynStr_t`.
  - `opt`: A `DynStrOptions_t` struct specifying the offset and count.
- **Returns**: 
  - `0` on success.
  - `-1` on failure (`opt.offset + opt.count > srcDStr->count`).

### Memory Management

#### `int DynStr_reserve (DynStr_t * dStr, size_t requiredCapacity)`

Ensures that a `DynStr_t` has at least the specified capacity.

- **Parameters**: 
  - `dStr`: The `DynStr_t`.
  - `requiredCapacity`: The required capacity.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

### Comparison

#### `int DynStr_compare (DynStr_t * dStr1, DynStr_t * dStr2, int * result)`

Compares two `DynStr_t` objects.

- **Parameters**: 
  - `dStr1`: The first `DynStr_t`.
  - `dStr2`: The second `DynStr_t`.
  - `result`: Pointer to an integer to store the result (`1` if equal, `0` if not).
- **Returns**: 
  - `0` on success.
  - `-1` on failure.

### Conversion

#### `int DynStr_toCStr (DynStr_t * dStr, char ** destCStr)`

Creates a dynamically allocated, null-terminated C string from a `DynStr_t`. The user is responsible for deallocating this string.

- **Parameters**: 
  - `dStr`: The `DynStr_t`.
  - `destCStr`: Pointer to a char pointer to store the result.
- **Returns**: 
  - `0` on success.
  - `-1` on failure.
