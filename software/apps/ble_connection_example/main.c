// BLE Service example app
//
// Creates a BLE service and blinks an LED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "simple_ble.h"

#include "nrf52840dk.h"

// Intervals for advertising and connections
static simple_ble_config_t ble_config = {
  // c0:98:e5:4e:xx:xx
  .platform_id       = 0x4E,    // used as 4th octect in device BLE address
  .device_id         = 0xAABB,
  .adv_name          = "CS397/497", // used in advertisements if there is room
  .adv_interval      = MSEC_TO_UNITS(1000, UNIT_0_625_MS),
  .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
  .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
};

static simple_ble_service_t connection_service = {{
  .uuid128 = {0x70,0x6C,0x98,0x41,0xCE,0x43,0x14,0xA9,
              0xB5,0x4D,0x22,0x2B,0x88,0x10,0xE6,0x32}
}};


// Char uuids
static simple_ble_char_t led_state_char = {.uuid16 = 0x1089};
static simple_ble_char_t print_state_char = {.uuid16 = 0x1090};
// static simple_ble_char_t test_char = {.uuid16 = 0x1091};

static bool led_state = false;
static char print_state[16];
static int test_state[10];

/*******************************************************************************
 *   State for this application
 ******************************************************************************/
// Main application state
simple_ble_app_t* simple_ble_app;

void ble_evt_write(ble_evt_t const* p_ble_evt) {

  // Check LED characteristic
  if (simple_ble_is_char_event(p_ble_evt, &led_state_char)) {
    printf("LED Rotation changed!\n");

    // Use value written to control LED
    if (led_state != 0) {
      printf("starting LED rotation!\n");
    } else {
      printf("ending LED rotation!\n");
    }
  }

  // Check print characteristic
  if (simple_ble_is_char_event(p_ble_evt, &print_state_char)){
    printf("Received some text:\n");
    printf("%s\n", print_state);
  }
}

int main(void) {

  printf("Board started. Initializing BLE: \n");

  // Setup LED GPIO
  nrf_gpio_cfg_output(LED1);

  // Setup BLE
  simple_ble_app = simple_ble_init(&ble_config);

  simple_ble_add_service(&connection_service);

  // LED char
  // simple_ble_add_characteristic(1, 1, 0, 0,
  //     sizeof(led_state), (uint8_t*)&led_state,
  //     &connection_service, &led_state_char);

  // print char
  simple_ble_add_characteristic(1, 1, 0, 0,
      sizeof(print_state), (uint8_t*)&print_state,
      &connection_service, &print_state_char);

  // test char
  // simple_ble_add_characteristic(1, 1, 0, 0,
  //     sizeof(test_state), (uint8_t*)&test_state,
  //     &connection_service, &test_char);

  // Start Advertising
  simple_ble_adv_only_name();

  while(1) {

    // power_manage();

    // initialize
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);


    if (led_state){
      nrf_gpio_pin_toggle(LED1);
      nrf_delay_ms(100);

      nrf_gpio_pin_toggle(LED2);
      nrf_delay_ms(100);

      nrf_gpio_pin_toggle(LED4);
      nrf_delay_ms(100);

      nrf_gpio_pin_toggle(LED3);
      nrf_delay_ms(100);
    }
    else{
      nrf_gpio_pin_set(LED1);
      nrf_gpio_pin_set(LED2);
      nrf_gpio_pin_set(LED3);
      nrf_gpio_pin_set(LED4);
    }
  }
}
