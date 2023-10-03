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
                *state = SLASH;
            }
            else if (c == '"') {
                putchar('"');
                *state = STR;
            }
            else {
                putchar(c);
            }
            break;

        case SLASH:
            if (c == '/') {
                *state = SLC;
            }
            else if (c == '*') {
                *state = MLC;
            }
            else {
                putchar('/');
                putchar(c);
                *state = INI;
            }
            break;

        case SLC:
            if (c == '\n') {
				putchar('\n');
                *state = INI;
            }
            break;

        case MLC:
            if (c == '*') {
                *state = MLC_EXIT;
            }
            break;

        case MLC_EXIT:
            if (c == '/') {
                *state = INI;
            }
            else {
                *state = MLC;
            }
            break;

        case STR:
            if (c == '\\') {
                putchar('\\');
                *state = QESC;
            }
            else if (c == '"') {
                putchar('"');
                *state = INI;
            }
            else {
                putchar(c);
            }
            break;

        case QESC:
            putchar(c);
            *state = STR;
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