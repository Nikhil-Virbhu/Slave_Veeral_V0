/*
 * error_display.c
 * common anode display used to indicate faults
 *
 *  Created on: APR 18, 2024
 *      Author: Savan Sutariya
 */

#include "main.h"
#include "error_display.h"

#define total_errors 29

uint8_t toggleFlag = 0;
//uint8_t error_list[total_errors]= {99,23,56,78,45,12};
uint8_t error_list[total_errors] = {99};
uint8_t display_digit[2];
uint8_t count_error = 0;

void one(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 1);
}

void two(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void three(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void four(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void five(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void six(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void seven(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 1);
}

void eight(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void nine(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void zero(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 0);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 1);
}

void no_error(void) {
//  HAL_GPIO_WritePin(Seven_Seg_A_GPIO_Port, Seven_Seg_A_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_B_GPIO_Port, Seven_Seg_B_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_C_GPIO_Port, Seven_Seg_C_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_D_GPIO_Port, Seven_Seg_D_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_E_GPIO_Port, Seven_Seg_E_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_F_GPIO_Port, Seven_Seg_F_Pin, 1);
//  HAL_GPIO_WritePin(Seven_Seg_G_GPIO_Port, Seven_Seg_G_Pin, 0);
}

void digit_1(uint8_t number) {
//  HAL_GPIO_WritePin(Digit_2_GPIO_Port, Digit_2_Pin, 1);
//  HAL_GPIO_WritePin(Digit_1_GPIO_Port, Digit_1_Pin, 0);
  switch (number)
  {
	case 1: one(); break;
	case 2: two(); break;
	case 3: three(); break;
	case 4: four(); break;
	case 5: five(); break;
	case 6: six(); break;
	case 7: seven(); break;
	case 8: eight(); break;
	case 9: nine(); break;
	case 0: zero(); break;
	case 99: no_error(); break;
  }
}

void digit_2(uint8_t number) {
//  HAL_GPIO_WritePin(Digit_2_GPIO_Port, Digit_2_Pin, 0);
//  HAL_GPIO_WritePin(Digit_1_GPIO_Port, Digit_1_Pin, 1);
  switch (number)
  {
	case 1: one(); break;
	case 2: two(); break;
	case 3: three(); break;
	case 4: four(); break;
	case 5: five(); break;
	case 6: six(); break;
	case 7: seven(); break;
	case 8: eight(); break;
	case 9: nine(); break;
	case 0: zero(); break;
	case 99: no_error(); break;
  }
}

/**
 * @brief Calculates the length of an error list array.
 *
 * This function calculates the length of an error list array by iterating through
 * the array until it encounters a zero value or reaches the end of the array.
 *
 * @param error_list The error list array to calculate the length of.
 * @return The length of the error list array.
 */
uint8_t get_error_list_length(uint8_t error_list[]) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < total_errors; i++) {
    if (error_list[i] == 0) {
      break;
    }
    count++;
  }
  return count;
}

uint8_t check_errorlist(uint8_t error_code) {
  for (uint8_t i = 0; i < total_errors; i++) {
    if (error_list[i] == error_code) {
      return 0;
    }
  }
  return 1;
}
/**
 * @brief Adds a new error code to the error list array.
 *
 * This function adds a new error code to the end of the error list array.
 *
 * @param new_error The new error code to be added to the error list array.
 * @return None
 */
void add_error_to_list(uint8_t new_error) {
  if (check_errorlist(new_error)) {
    uint8_t length = get_error_list_length(error_list);
    error_list[length] = new_error;
  }
  else{}
}

/**
 * @brief Removes a specific error code from the error list array.
 *
 * This function removes a specific error code from the error list array,
 * if it exists within the array. It searches for the error code to remove,
 * and if found, shifts the subsequent elements to fill the gap created by
 * the removed error code.
 *
 * @param error_to_remove The error code to be removed from the error list array.
 * @return None
 */
void remove_error_from_list(uint8_t error_to_remove) {
  uint8_t pos, j, i, found = 0;

  for (i = 0; i < total_errors; i++) {
    if (error_list[i] == error_to_remove) {
      found = 1;
      pos = i;
      break;
    }
  }
  if (found == 1) {
    for (j = pos; j < total_errors - 1; j++) {
    	error_list[j] = error_list[j + 1];
    }
    error_list[j] = 0;
  }
}

/**
 * @brief Separates a two-digit number into individual digits.
 *
 * This function separates a two-digit number into its individual digits
 *
 * @param number The two-digit number to be separated.
 * @return None
 */
void saprate_digit(uint8_t number) {
  if (number == 99) {
	  display_digit[1] = 99;
	  display_digit[0] = 99;
  } else {
	  display_digit[1] = number % 10;
	  display_digit[0] = number / 10;
  }
}

/**
 * @brief Controls the display of error digits on a segmented display.
 *
 * This function controls the display of error digits on a segmented display
 * by alternating between two digits. It uses a toggle flag to determine which
 * digit to display on each invocation.
 *
 * @return None
 */
void error_display() {

  if (toggleFlag == 0)
	  digit_1(display_digit[0]);
  else if (toggleFlag == 1)
	  digit_2(display_digit[1]);

  toggleFlag ^= 1; // Toggling the flag

}

/**
 * @brief Displays errors from an error list array on a segmented display.
 *
 * This function displays errors from an error list array on a segmented display.
 *
 * @return None
 */
void display_errors() {
  uint8_t error_list_length;
    error_list_length = get_error_list_length(error_list);
    if (error_list_length != 0) {
    	saprate_digit(error_list[count_error]);
      count_error++;
      if (error_list_length == count_error) {
        count_error = 0;
    }
  }
}
