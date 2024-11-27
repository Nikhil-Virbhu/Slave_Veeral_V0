/*
 * error_display.h
 *
 *  Created on: APR 18, 2024
 *      Author: Savan Sutariya
 */

void one(void);
void two(void);
void three(void);
void four(void);
void five(void);
void six(void);
void seven(void);
void eight(void);
void nine(void);
void zero(void);
void no_error(void);

uint8_t get_error_list_length(uint8_t error_list[]);
uint8_t check_errorlist(uint8_t error_code);
void add_error_to_list(uint8_t new_error);
void remove_error_from_list(uint8_t error_to_remove);
void saprate_digit(uint8_t number);
void display_errors();
void error_display();
