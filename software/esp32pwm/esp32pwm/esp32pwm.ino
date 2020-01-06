#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "soc/rtc.h"
#include "driver/mcpwm.h"


#define GPIO_PWM0A_OUT 19   //Set GPIO 19 as PWM0A
#define GPIO_PWM0B_OUT 18   //Set GPIO 18 as PWM0B

static float duty = 0;
unsigned long previousMillisRefresh = 0;        // will store last time LED was updated
const long intervalRefresh = 1000; 

void setup() {
  Serial.begin(115200);
  while (!Serial);
  //pinMode(outPin, OUTPUT);

  // set GPIO
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);

  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50000;    //frequency = 1000Hz
  pwm_config.cmpr_a = 0;       //duty cycle of PWMxA = 60.0%
  pwm_config.cmpr_b = 0;       //duty cycle of PWMxb = 50.0%
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);   //Configure PWM0A & PWM0B with above settings
}

void loop() {
  if (millis() - previousMillisRefresh >= intervalRefresh) {
    previousMillisRefresh = millis();
    duty+=1;
    if(duty > 100.00) {
      duty=0;
    }
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A,duty);
  }
  yield();
}
