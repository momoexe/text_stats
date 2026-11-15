#!/bin/sh

set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$ROOT_DIR"

./build.sh

TEST_DIR=$(mktemp -d)
trap 'rm -rf "$TEST_DIR"' EXIT

check_file() {
    name=$1
    file=$2
    expected_chars=$3
    expected_words=$4
    expected_lines=$5

    output=$(./bin/textstats "$file")
    expected=$(printf '[TEXT STATS]\nchars: %5s\nwords: %5s\nlines: %5s' \
        "$expected_chars" "$expected_words" "$expected_lines")

    if [ "$output" != "$expected" ]; then
        printf 'FAIL: %s\n%s\n' "$name" "$output"
        exit 1
    fi

    printf 'PASS: %s\n' "$name"
}

: > "$TEST_DIR/empty.txt"
printf 'ciao' > "$TEST_DIR/no_newline.txt"
printf 'ciao\n' > "$TEST_DIR/newline.txt"
printf 'ciao\nmondo' > "$TEST_DIR/two_lines.txt"
printf 'ciao\n\nmondo' > "$TEST_DIR/blank_line.txt"

check_file "empty file" "$TEST_DIR/empty.txt" 0 0 0
check_file "one word without newline" "$TEST_DIR/no_newline.txt" 4 1 1
check_file "one word with newline" "$TEST_DIR/newline.txt" 5 1 1
check_file "two lines" "$TEST_DIR/two_lines.txt" 10 2 2
check_file "blank line" "$TEST_DIR/blank_line.txt" 11 2 3

if ./bin/textstats "$TEST_DIR/missing.txt" >/dev/null 2>&1; then
    printf 'FAIL: missing file should return an error\n'
    exit 1
fi

printf 'PASS: missing file\n'

check_usage_error() {
    name=$1
    shift

    if ./bin/textstats "$@" >"$TEST_DIR/stdout" 2>"$TEST_DIR/stderr"; then
        printf 'FAIL: %s should return an error\n' "$name"
        exit 1
    fi

    if [ -s "$TEST_DIR/stdout" ] ||
       ! grep -q 'Usage: textstats \[FILE\]' "$TEST_DIR/stderr"; then
        printf 'FAIL: %s should print usage on stderr\n' "$name"
        exit 1
    fi

    printf 'PASS: %s\n' "$name"
}

check_usage_error "too many arguments" "$TEST_DIR/empty.txt" extra

stdin_output=$(printf 'ciao\nmondo' | ./bin/textstats)
expected_stdin=$(printf '[TEXT STATS]\nchars: %5s\nwords: %5s\nlines: %5s' 10 2 2)

if [ "$stdin_output" != "$expected_stdin" ]; then
    printf 'FAIL: standard input\n%s\n' "$stdin_output"
    exit 1
fi

printf 'PASS: standard input\n'
