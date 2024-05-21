# da.c
Dynamic Array implementation in c. 

## Features

- Easy to use, understand and extend, API. Few modifications can allow your own types to be used with the dynamic array,
- Featurfull API as well as some extra debugging tools out-of-the-box!

## Getting Started

- Clone this repo: `git clone https://github.com/giorgosathanasopoulos/da.c`,
- Cd into the repo: `cd da.c`,
- Test the library: `make test`. If no assertion fails then everything is good!
- Build the library: `make`. This will create `bin/libda.a`,
- Copy `bin/libda.a` and `src/da.h` into your project for use,
- Compile with extra flags `-L. -lda` if your compilation command is run within the same directory as the libda.a file. Otherwise change accordingly.

## API

Take a look at `src/da.h`.

## Extending

Take a look at the first paragraph in `src/da.h`.

## TODO

- Implement da_insert.
