# da.c
Dynamic Array implementation in c. 

## Features

- Easy to use, understand and extend, API. Few modifications can allow your own types to be used with the dynamic array,
- Featurfull API (contains all of the important std::vector methods),
- Some (simple) yet useful debugging tools out-of-the-box.

## Getting Started

- Clone this repo: `git clone https://github.com/giorgosathanasopoulos/da.c`,
- CD into the repo: `cd da.c`,
- Test the library: `make test`. If no assertion fails then everything is good!
- Build the library: `make`. This will create `bin/libda.a`,
- Copy `bin/libda.a` and `src/da.h` (and optionally specific implementations e.g. `src/da_int.h` for int dynamic array) into your project for use,
- Compile with extra flags `-L. -lda` if your compilation command is run within the same directory as the libda.a file. Otherwise change accordingly.

## API

Take a look at `src/da.h`/`src/da_int.h`/etc.

## Extending

1. In `src/da.h` add the name of your type to the enum definition DA_Type.

For example, to add floating point numbers:

```c
typedef enum DA_Type
{
    INT,
    FLOAT, 
    DOUBLE // new!
} DA_Type;
```

2. Referencing `src/da_int.h` and `src/da_int.c` (or other implementation, e.g. `src/da_float.h/c` for floats) make your own two files for your type implementing the required methods (e.g. `src/da_double.h`/`src/da_double.c`),

3. In `src/da.c` go to every switch(da->type) and add a case for your new type. For help with the implementation of the case look at previous types. There should only be 6 cases to implement.

3. Add your own test file in `test` (e.g. `test/da_test_double.c`), and test your functions. Reference `test/da_test_int.c` for more info. After that add it to the test makefile step and run `make test` to ensure everything works correctly,

4. Remember to add your c file to the makefile library build step in order for it to be added to the output library file,

5. To use it reference `##Getting Started`.
