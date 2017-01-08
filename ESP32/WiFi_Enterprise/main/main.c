/* Hello World Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "ca.h"

static EventGroupHandle_t wifi_event_group;

const int CONNECTED_BIT = BIT0;

static int evita_loop = 0;

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    ESP_LOGI("EH","%d", event->event_id);
    switch(event->event_id) {
      case SYSTEM_EVENT_STA_START:
          esp_wifi_connect();
          break;
      case SYSTEM_EVENT_STA_GOT_IP:
          xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          /* This is a workaround as ESP32 WiFi libs don't currently
             auto-reassociate. */
          if(evita_loop==0){
            evita_loop = 1;
            esp_wifi_connect();
          }
          xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
          break;
      default:
          break;
    }
    return ESP_OK;
}

void wifi_conn_init()
{
    tcpip_adapter_init();

    wifi_event_group = xEventGroupCreate();

    char username[]= "Admin";
    char password[]= "Admin";

    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "NoobsLand"
        }
    };
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_enable() );

    ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_ca_cert(ca, ca_len + 1) );
    ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_username((unsigned char *)username, strlen(username)) );
    ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_password((unsigned char *)password, strlen(password)) );

    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );

    ESP_ERROR_CHECK( esp_wifi_start() );

}

void app_main()
{
    nvs_flash_init();
    vTaskDelay(500 / portTICK_PERIOD_MS);
    wifi_conn_init();
}
