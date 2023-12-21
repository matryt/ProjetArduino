//
// Created by mathi on 17/12/2023.
//

#include "esp_camera.h"
#include <WiFi.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h"  //disable brownout problems
#include "esp_http_server.h"
#include "src/modules/Constants.h"

class LiveStream {
    const char* ssid = WIFI::ssidMat2;
    const char* password = WIFI::passwordMat2;

    #define PART_BOUNDARY "123456789000000000000987654321"

    static const char* _STREAM_CONTENT_TYPE;
    static const char* _STREAM_BOUNDARY;
    static const char* _STREAM_PART;

    httpd_handle_t stream_httpd = NULL;

    static esp_err_t stream_handler(httpd_req_t *req){
        camera_fb_t * fb = NULL;
        esp_err_t res = ESP_OK;
        size_t _jpg_buf_len = 0;
        uint8_t * _jpg_buf = NULL;
        char * part_buf[64];

        res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
        if(res != ESP_OK){
            return res;
        }

        while(true){
            fb = esp_camera_fb_get();
            if (!fb) {
                Serial.println("Camera capture failed");
                res = ESP_FAIL;
            } else {
                if(fb->width > 400){
                    if(fb->format != PIXFORMAT_JPEG){
                        bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
                        esp_camera_fb_return(fb);
                        fb = NULL;
                        if(!jpeg_converted){
                            Serial.println("JPEG compression failed");
                            res = ESP_FAIL;
                        }
                    } else {
                        _jpg_buf_len = fb->len;
                        _jpg_buf = fb->buf;
                    }
                }
            }
            if(res == ESP_OK){
                size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
                res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
            }
            if(res == ESP_OK){
                res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
            }
            if(res == ESP_OK){
                res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
            }
            if(fb){
                esp_camera_fb_return(fb);
                fb = NULL;
                _jpg_buf = NULL;
            } else if(_jpg_buf){
                free(_jpg_buf);
                _jpg_buf = NULL;
            }
            if(res != ESP_OK){
                break;
            }
        }
        return res;
    }

    void startCameraServer(){
        httpd_config_t config = HTTPD_DEFAULT_CONFIG();
        config.server_port = 80;

        httpd_uri_t index_uri = {
                .uri       = "/",
                .method    = HTTP_GET,
                .handler   = stream_handler,
                .user_ctx  = NULL
        };

        if (httpd_start(&stream_httpd, &config) == ESP_OK) {
            httpd_register_uri_handler(stream_httpd, &index_uri);
        }
    }

    public:
        static void init();

        int main() {
            WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

            Serial.begin(115200);
            Serial.setDebugOutput(false);

            camera_config_t config;
            config.ledc_channel = LEDC_CHANNEL_0;
            config.ledc_timer = LEDC_TIMER_0;
            config.pin_d0 = ARDUCAM::Y2_GPIO_NUM;
            config.pin_d1 = ARDUCAM::Y3_GPIO_NUM;
            config.pin_d2 = ARDUCAM::Y4_GPIO_NUM;
            config.pin_d3 = ARDUCAM::Y5_GPIO_NUM;
            config.pin_d4 = ARDUCAM::Y6_GPIO_NUM;
            config.pin_d5 = ARDUCAM::Y7_GPIO_NUM;
            config.pin_d6 = ARDUCAM::Y8_GPIO_NUM;
            config.pin_d7 = ARDUCAM::Y9_GPIO_NUM;
            config.pin_xclk = ARDUCAM::XCLK_GPIO_NUM;
            config.pin_pclk = ARDUCAM::PCLK_GPIO_NUM;
            config.pin_vsync = ARDUCAM::VSYNC_GPIO_NUM;
            config.pin_href = ARDUCAM::HREF_GPIO_NUM;
            config.pin_sscb_sda = ARDUCAM::SIOD_GPIO_NUM;
            config.pin_sscb_scl = ARDUCAM::SIOC_GPIO_NUM;
            config.pin_pwdn = ARDUCAM::PWDN_GPIO_NUM;
            config.pin_reset = ARDUCAM::RESET_GPIO_NUM;
            config.xclk_freq_hz = 20000000;
            config.pixel_format = PIXFORMAT_JPEG;

            if(psramFound()){
                config.frame_size = FRAMESIZE_UXGA;
                config.jpeg_quality = 10;
                config.fb_count = 2;
            } else {
                config.frame_size = FRAMESIZE_SVGA;
                config.jpeg_quality = 12;
                config.fb_count = 1;
            }

            // Camera init
            esp_err_t err = esp_camera_init(&config);
            if (err != ESP_OK) {
                Serial.printf("Camera init failed with error 0x%x", err);
                return 1;
            }
            // Wi-Fi connection
            WiFi.begin(ssid, password);
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }
            Serial.println();
            Serial.println("WiFi connected");

            Serial.print("To start video streaming go to: http://");
            Serial.print(WiFi.localIP());

            // Start streaming web server
            startCameraServer();
            return 0;
        }
};

const char* LiveStream::_STREAM_CONTENT_TYPE;
const char* LiveStream::_STREAM_BOUNDARY;
const char* LiveStream::_STREAM_PART;

void LiveStream::init() {
    _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
    _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
    _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
}