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
    chars=$(printf '%s\n' "$output" | awk '/^chars:/ { print $2 }')
    words=$(printf '%s\n' "$output" | awk '/^words:/ { print $2 }')
    lines=$(printf '%s\n' "$output" | awk '/^lines:/ { print $2 }')

    if [ "$chars" != "$expected_chars" ] ||
       [ "$words" != "$expected_words" ] ||
       [ "$lines" != "$expected_lines" ]; then
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
