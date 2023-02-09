# C Uncommenter
Simple program that removes comments from C code.
## Usage
It takes input on stdin and outputs to stdout. Hence it can be used like so:

`cat input.c | ./uncomment > output.c`

on GNU/Linux's Bash or similarly

`type input.c | .\uncomment.exe > output.c` 

on Windows' cmd.

## Build
I have not used anything compiler-specific or any features of new C standards, therefore it can be compiled simply like:
`gcc -o uncomment uncomment.c`
