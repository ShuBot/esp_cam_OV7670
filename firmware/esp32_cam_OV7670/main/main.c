/**
 * This example takes a picture every 5s and print its size on serial monitor.
 */

// ================================ CODE ======================================

//#include <esp_event_loop.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_camera.h"
/*#include <esp_wifi.h>
#include "esp_netif.h"
#include "esp_eth.h"
//#include "protocol_examples_common.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
*/
//#define BOARD_WROVER_KIT
#define BOARD_ESP32_DOIT_DEV_V1

// ESP32 DOIT DEV BOARD V1
#ifdef BOARD_ESP32_DOIT_DEV_V1

#define CAM_PIN_PWDN -1  //power down is not used
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 32 //21
#define CAM_PIN_SIOD 21 //26
#define CAM_PIN_SIOC 22 //27

#define CAM_PIN_D7 4 //35
#define CAM_PIN_D6 12 //34
#define CAM_PIN_D5 13 //39
#define CAM_PIN_D4 14 //36
#define CAM_PIN_D3 15 //19
#define CAM_PIN_D2 16 //18
#define CAM_PIN_D1 17 //5
#define CAM_PIN_D0 27 //4
#define CAM_PIN_VSYNC 34 //25
#define CAM_PIN_HREF 35 //23
#define CAM_PIN_PCLK 33 //22

#endif

static const char *TAG = "example:take_picture";

static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sscb_sda = CAM_PIN_SIOD,
    .pin_sscb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_RGB565, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QQVGA,    //QQVGA-UXGA Do not use sizes above QVGA when not JPEG

    .jpeg_quality = 60, //0-63 lower number means higher quality
    .fb_count = 1       //if more than one, i2s runs in continuous mode. Use only with JPEG
};

static esp_err_t init_camera()
{
    //initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

void app_main()
{
    init_camera();
    //start_serving();
    while (1)
    {
        //ESP_LOGI(TAG, "Server Running");
        ESP_LOGI(TAG, "Taking picture...");
        camera_fb_t *pic =esp_camera_fb_get();
        //jpg_stream_httpd_handler();
        // use pic->buf to access the image
        ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);

        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

/*// WROVER-KIT PIN Map
#ifdef BOARD_WROVER_KIT

#define CAM_PIN_PWDN -1  //power down is not used
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 32 //21
#define CAM_PIN_SIOD 21 //26
#define CAM_PIN_SIOC 22 //27

#define CAM_PIN_D7 4 //35
#define CAM_PIN_D6 12 //34
#define CAM_PIN_D5 13 //39
#define CAM_PIN_D4 14 //36
#define CAM_PIN_D3 15 //19
#define CAM_PIN_D2 16 //18
#define CAM_PIN_D1 17 //5
#define CAM_PIN_D0 27 //4
#define CAM_PIN_VSYNC 34 //25
#define CAM_PIN_HREF 35 //23
#define CAM_PIN_PCLK 33 //22

#endif

// ESP32Cam (AiThinker) PIN Map
#ifdef BOARD_ESP32CAM_AITHINKER

#define CAM_PIN_PWDN 32
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27

#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

#endif
*/