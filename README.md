# DynStr 

A simple C library for working with dynamically allocated strings.

## Features

- Create dynamic strings from C strings or other dynamic strings
- Create C strings and string slices from dynamic strings
- Concatenate literals or other dynamic strings
- Compare dynamic strings
- Automatically manage memory allocation and resizing

## Usage

To use this library, first include the [`dynstr.h`](/lib/dynstr.h) and [`dynstr.c`](/lib/dynstr.c) files in your project (located in the [`lib`](/lib) directory), then compile them together with your source files.

For usage examples, please refer to the [`demo.c`](/demo.c) and [`test.c`](/test.c) programs included in the project.

You can compile and run them like this:

```bash
cc -o demo demo.c lib/dynstr.c 
./demo 

cc -o test test.c lib/dynstr.c 
./test 
```

For a more in depth explanation of the API, please see the [API Reference](/docs/api.md).

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.