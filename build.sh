set -eu
mkdir bin
gcc -g -std=c17 -Wall -Wextra -pedantic src/*.c -Iinclude -o bin/textstats


