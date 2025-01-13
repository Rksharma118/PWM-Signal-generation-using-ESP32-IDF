#include "driver/mcpwm.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 2
#define PWM_FREQUENCY 1000
#define BUF_SIZE 1024

static const char *TAG = "MCPWM_LED";

// Initialize UART for console input
void init_uart(void)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));
}

// Initialize MCPWM
void mcpwm_init_gpio(void)
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, LED_PIN);
    mcpwm_config_t pwm_config = {
        .frequency = PWM_FREQUENCY, .cmpr_a = 0.0, .counter_mode = MCPWM_UP_COUNTER, .duty_mode = MCPWM_DUTY_MODE_0};
    ESP_ERROR_CHECK(mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config));
    ESP_ERROR_CHECK(mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0));
}

// Update duty cycle
void set_duty_cycle(float duty_cycle)
{
    ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle));
    ESP_LOGI(TAG, "Duty cycle: %.1f%%", duty_cycle);
}

// Read user input
int get_user_input(void)
{
    uint8_t data[10] = {0};
    int len = 0, value = -1;
    printf("Enter PWM duty cycle (0-100): "); // Ensures prompt is shown before input
    fflush(stdout); // Force the buffer to flush so the message appears immediately
    while (len < sizeof(data) - 1)
    {
        int rxBytes = uart_read_bytes(UART_NUM_0, &data[len], 1, portMAX_DELAY);
        if (rxBytes <= 0)
            continue;
        uart_write_bytes(UART_NUM_0, (const char *)&data[len], 1);
        if (data[len] == '\n' || data[len] == '\r')
        {
            data[len] = 0;
            break;
        }
        len++;
    }
    if (len > 0)
        value = atoi((char *)data);
    return value;
}

void app_main(void)
{
    init_uart();
    ESP_LOGI(TAG, "Initializing MCPWM for LED control");
    mcpwm_init_gpio();
    
    while (1)
    {
        int duty_cycle = get_user_input();
        if (duty_cycle >= 0 && duty_cycle <= 100)
        {
            set_duty_cycle((float)duty_cycle);
        }
        else
        {
            ESP_LOGW(TAG, "Invalid duty cycle! Enter a value between 0 and 100");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}