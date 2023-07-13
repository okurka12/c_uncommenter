#include <stdio.h>
#include <stdint.h>

/* states for the state machine (see diagram in this repo) */
enum state {
    INI,       // initial state
    SLASH,     // received first slash
    SLC,       // single-line comment (received second slash)
    MLC,       // multi-line comment (received asterisk)
    MLC_EXIT,  // potential MLC exit (received asterisk in MLC)
    STR,       // inside a string literal
    QESC       // quotation mark escape
};

/* handles state transitions and outputs characters accordingly */
void handle_state(enum state *state, char c) {
    switch (*state) {
        case INI:
            if (c == '/') {
                *state = 1;
            }
            else if (c == '"') {
                putchar('"');
                *state = 5;
            }
            else {
                putchar(c);
            }
            break;

        case SLASH:
            if (c == '/') {
                *state = 2;
            }
            else if (c == '*') {
                *state = 3;
            }
            else {
                putchar('/');
                putchar(c);
                *state = 0;
            }
            break;

        case SLC:
            if (c == '\n') {
				putchar('\n');
                *state = 0;
            }
            break;

        case MLC:
            if (c == '*') {
                *state = 4;
            }
            break;

        case MLC_EXIT:
            if (c == '/') {
                *state = 0;
            }
            else {
                *state = 3;
            }
            break;

        case STR:
            if (c == '\\') {
                putchar('\\');
                *state = 6;
            }
            else if (c == '"') {
                putchar('"');
                *state = 0;
            }
            else {
                putchar(c);
            }
            break;

        case QESC:
            putchar(c);
            *state = 5;
    }

}

int main() {
    int c;
    enum state state = 0;
    while ((c = getchar()) != EOF) {
        handle_state(&state, c);
    }
    return 0;
}