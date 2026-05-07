#ifndef LASALLIANOS_KEYBOARD_H
#define LASALLIANOS_KEYBOARD_H

#include "types.h"

#define KEYBOARD_ENTER '\n'
#define KEYBOARD_BACKSPACE '\b'

void keyboard_initialize(void);
char keyboard_read_char(void);
void keyboard_read_line(char *buffer, uint32_t buffer_size);

#endif
