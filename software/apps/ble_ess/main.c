// BLE Service example app
//
// Creates a BLE environmental sensing service

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

static simple_ble_service_t environmental_sensing_service = {{
  .uuid128 = {0xFB,0x34,0x9B,0x5F,0x80,0x00,0x00,0x80,
              0x00,0x10,0x00,0x00,0x1A,0x18,0x00,0x00}
}};

/*******************************************************************************
 *   State for this application
 ******************************************************************************/
// Main application state
simple_ble_app_t* simple_ble_app;

//// Char uuids  ////
// temp
static simple_ble_char_t temperature_char = {.uuid16=0x2A6E};
// elevation
static simple_ble_char_t elevation_char = {.uuid16 = 0x2A6C};
// humidity
static simple_ble_char_t humidity_char = {.uuid16 = 0x2A6F};
// true wind speed
static simple_ble_char_t wind_speed_char = {.uuid16 = 0x2A70};
// true wind direction
static simple_ble_char_t wind_direction_char = {.uuid16 = 0x2A71};

//// Initial states ////
static int temperature_state = -14; // measured in C
static int elevation_state = 185; // measured in meters
static int humidity_state = 60; // measured in percent
static int wind_speed_state = 3; // measured in m/s
static int wind_direction_state = 90; // measured in degrees


void ble_evt_write(ble_evt_t const* p_ble_evt) {
  printf("Got write to a characteristic!\n");
}

int main(void) {

  printf("Board started. Initializing BLE: \n");

  // Setup BLE
  simple_ble_app = simple_ble_init(&ble_config);

  // Add service
  simple_ble_add_service(&environmental_sensing_service);

  // Add chars
  // temperature
  simple_ble_add_characteristic(1, 0, 1, 0,
      sizeof(temperature_state), (uint8_t*)&temperature_state,
      &environmental_sensing_service, &temperature_char);

  // elevation
  simple_ble_add_characteristic(1, 0, 1, 0,
      sizeof(elevation_state), (uint8_t*)&elevation_state,
      &environmental_sensing_service, &elevation_char);

  // humidity
  simple_ble_add_characteristic(1, 0, 1, 0,
      sizeof(humidity_state), (uint8_t*)&humidity_state,
      &environmental_sensing_service, &humidity_char);

  // wind speed
  simple_ble_add_characteristic(1, 0, 1, 0,
      sizeof(wind_speed_state), (uint8_t*)&wind_speed_state,
      &environmental_sensing_service, &wind_speed_char);

  // wind direction
  simple_ble_add_characteristic(1, 0, 1, 0,
      sizeof(wind_direction_state), (uint8_t*)&wind_direction_state,
      &environmental_sensing_service, &wind_direction_char);


  // Start Advertising
  simple_ble_adv_only_name();

  while(1) {
    power_manage();
  }
}
