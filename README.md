# textstats

`textstats` is a C program that counts characters, words, and lines in a text
file.

This project was created to practice:

- the C programming language;
- reading files;
- data structures;
- error handling;
- compiling from the terminal;
- automated testing;
- Git.

## Requirements

- a C compiler compatible with the C17 standard;
- a POSIX shell.

## Building

From the project's root directory:

```bash
./build.sh
```

The executable is created at `bin/textstats`.

Alternatively, compile the project manually:

```bash
gcc -g -std=c17 -Wall -Wextra -pedantic \
    src/*.c -Iinclude -o bin/textstats
```

## Usage

The program accepts one file and optional counting options:

```bash
./bin/textstats file.txt
```

Available counting options:

```bash
./bin/textstats -c file.txt      # characters
./bin/textstats -w file.txt      # words
./bin/textstats -l file.txt      # lines
./bin/textstats -c -w file.txt  # characters and words
```

Without options, all three statistics are shown. Options can be combined, but
only one file can be provided.

If no file is provided, the program reads from standard input:

```bash
cat file.txt | ./bin/textstats
```

Show the usage information with:

```bash
./bin/textstats --help
```

The short form `-h` is also supported.

Example output:

```text
[TEXT STATS]
chars:    42
words:     8
lines:     3
```

If the file does not exist, or if the number of arguments is incorrect, the
program prints an error message and returns a non-zero exit code.

## Testing

Run the automated tests with:

```bash
./tests/test_stats.sh
```

The tests cover:

- empty files;
- files without a trailing newline;
- files with a trailing newline;
- files with multiple lines;
- blank lines;
- missing files;
- an incorrect number of arguments;
- input from standard input;
- individual and combined counting options;
- help output.

<small>**Note**: The test file was written by AI.</small>

## Project structure

```text
.
├── build.sh
├── include/
│   └── stats.h
├── src/
│   ├── stats.c
│   └── textstats.c
└── tests/
    └── test_stats.sh
```

The `stats_analyze` function reads the file once and counts characters, words,
and lines at the same time.

## Current limitations

- only one file can be analyzed at a time;
- word counting follows a simple definition based on whitespace.
