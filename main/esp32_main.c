//
// Created by thiagorigonatti on 07/04/26.
//

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "middleglyph.h"

#define I2C_PORT        0
#define I2C_SDA_IO      21
#define I2C_SCL_IO      22
#define OLED_ADDR       0x3C


static i2c_master_dev_handle_t dev_handle;
static SemaphoreHandle_t i2c_mutex;

static void ssd1306_cmd(const uint8_t cmd) {
    const uint8_t d[2] = {0x00, cmd};
    i2c_master_transmit(dev_handle, d, 2, -1);
}

static void ssd1306_update(void) {
    if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(20))) {
        ssd1306_cmd(0x21);
        ssd1306_cmd(0);
        ssd1306_cmd(127);
        ssd1306_cmd(0x22);
        ssd1306_cmd(0);
        ssd1306_cmd(7);
        uint8_t ctrl = 0x40;
        i2c_master_transmit_multi_buffer_info_t blks[2] = {
            {.write_buffer = &ctrl, .buffer_size = 1},
            {.write_buffer = buffer, .buffer_size = sizeof(buffer)}
        };
        i2c_master_multi_buffer_transmit(dev_handle, blks, 2, -1);
        xSemaphoreGive(i2c_mutex);
    }
}


void display_task(void *pv) {
    int p_scroll = 0;
    while (1) {

        draw_scrolling_row("abcdefghijklmnopqrstuvwxyzàáâãéêíóôõúç", 0, p_scroll, 24);
        draw_static_row("by Thiago", 36, 12);
        draw_static_row("Rigonatti", 48, 12);


        ssd1306_update();

        p_scroll += 2;
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}

void app_main(void) {
    i2c_mutex = xSemaphoreCreateMutex();

    const i2c_master_bus_config_t b_cfg = {
        .i2c_port = 0,
        .sda_io_num = 21,
        .scl_io_num = 22,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    i2c_master_bus_handle_t bus;

    ESP_ERROR_CHECK(i2c_new_master_bus(&b_cfg, &bus));

    const i2c_device_config_t d_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x3C,
        .scl_speed_hz = 400000
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &d_cfg, &dev_handle));

    ssd1306_cmd(0xAE);
    ssd1306_cmd(0x20);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x8D);
    ssd1306_cmd(0x14);
    ssd1306_cmd(0xAF);

    xTaskCreate(display_task, "oled_task", 4096, NULL, 5, NULL);
}
