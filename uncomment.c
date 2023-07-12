#include <stdio.h>
#include <stdint.h>

void handle_state(uint8_t *state, char c) {
    /**
     * to make sense of this long switch, look at the states graph at
     * https://imgur.com/a/JDG4rpf
    */
    switch (*state) {
        case 0:
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

        case 1:
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

        case 2:
            if (c == '\n') {
				putchar('\n');
                *state = 0;
            }
            break;

        case 3:
            if (c == '*') {
                *state = 4;
            }
            break;

        case 4:
            if (c == '/') {
                *state = 0;
            }
            else {
                *state = 3;
            }
            break;

        case 5:
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

        case 6:
            putchar(c);
            *state = 5;
    }

}

int main() {
    int16_t c;
    uint8_t state = 0;
    while ((c = getchar()) != EOF) {
        handle_state(&state, c);
    }
    return 0;
}