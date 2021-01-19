// Testing app
//
// Have LEDs flash CCW/CW depending on what button is pressed and print state changes

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "nrf52840dk.h"

// counter clockwise LEDs
void ccw(int time){
  nrf_gpio_pin_toggle(LED1);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED3);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED4);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED2);
  nrf_delay_ms(time);

  return;
}

// clockwise LEDs
void cw(int time){
  nrf_gpio_pin_toggle(LED1);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED2);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED4);
  nrf_delay_ms(time);

  nrf_gpio_pin_toggle(LED3);
  nrf_delay_ms(time);

  return;
}

int main(void) {

  // Initialize.
  nrf_gpio_cfg_output(LED1);
  nrf_gpio_cfg_output(LED2);
  nrf_gpio_cfg_output(LED3);
  nrf_gpio_cfg_output(LED4);
  nrf_gpio_pin_set(LED1);
  nrf_gpio_pin_set(LED2);
  nrf_gpio_pin_set(LED3);
  nrf_gpio_pin_set(LED4);
  nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  // State
  // int state = 0;

  // Enter main loop.
  while (1) {
    if (nrf_gpio_pin_read(BUTTON1)){
      ccw(100);
      printf("counter clockwise");
    }
    else{
      cw(100);
      printf("clockwise");
    }
  }
}
