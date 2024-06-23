# DynStr 

A simple C library for working with dynamically allocated strings.

## Usage

Include the [`dyn-str.h`](/lib/dyn-str.h) and [`dyn-str.c`](/lib/dyn-str.c) files in your project (located in the [`lib`](/lib) directory), then compile them with your source files.

For usage examples, please refer to the [`demo.c`](/demo.c) and [`test.c`](/test.c) programs provided in the project.

You may compile and execute them like this:

```bash
cc -o demo demo.c lib/dyn-str.c && ./demo 

cc -o test test.c lib/dyn-str.c && ./test 
```

For a more in depth explanation of the API, please refer to the [API Reference](/docs/api-ref.md).

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.