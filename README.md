*This project has been created as part of the 42 curriculum by jocorral.*

# get_next_line

## Description

`get_next_line` is a C function that returns, on each call, the next line read
from a file descriptor. The goal of the project is to learn how to use
**static variables** to keep information between calls.

```c
char	*get_next_line(int fd);
```

It returns the line read (with its `\n`, if it has one) or `NULL` if there is nothing left to read
or an error occurs. The line is allocated with `malloc` and must be released with `free`.

**Algorithm.** `read` reads blocks of `BUFFER_SIZE` bytes that may contain half a
line or several, so whatever is left over is kept in a static variable (`stash`):

1. It reads and appends to the `stash` until it contains a `\n` or the end is reached.
2. It extracts the line from the `stash` (up to and including the `\n`) and returns it.
3. The rest stays in the `stash` for the next call.

This way it only reads what it needs, and it works with any `BUFFER_SIZE` and with descriptors
such as standard input. The bonus part uses one `stash` per descriptor to be able to
alternate between several at once.

## Instructions

The test `main` functions are commented out at the end of the `.c` files: in `get_next_line.c`,
main 1 reads from a file and main 2 from standard input (stdin); in
`get_next_line_bonus.c`, main 3 alternates lines from two files. Uncomment the one
you want to use and compile with the buffer size:

```sh
# Mandatory part
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c && ./a.out
# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c && ./a.out
```

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)

**Use of AI:** it was used as support for writing this README.
