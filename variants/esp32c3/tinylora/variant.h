#if defined(TINYLORA_V2)

#define BUTTON_PIN 9
#define LED_PIN 8
#define LED_STATE_ON 1

#define HAS_SCREEN 0
#define HAS_GPS 0
#undef GPS_RX_PIN 21
#undef GPS_TX_PIN 20

#define USE_LLCC68
#define USE_SX1262
#define USE_SX1268

#define LORA_SCK 10
#define LORA_MISO 6
#define LORA_MOSI 7
#define LORA_CS 8

#define LORA_DIO0 RADIOLIB_NC
#define LORA_DIO1 3
#define LORA_DIO2 RADIOLIB_NC
#define LORA_BUSY 4
#define LORA_RESET 5

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_BUSY
#define SX126X_RESET LORA_RESET
#define SX126X_DIO2_AS_RF_SWITCH

#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL

#undef  BATTERY_PIN
#define BATTERY_PIN           12            // GPIO1
#define ADC_CHANNEL            ADC1_GPIO1_CHANNEL

#undef  ADC_MULTIPLIER
#define ADC_MULTIPLIER         1.6f

#elif defined(TINYLORA_V3)

#define BUTTON_PIN 9
#define LED_PIN 0
#define LED_STATE_ON 1

#define HAS_SCREEN 0
// GPS

#ifdef TINYLORA_V3_GPS
#define HAS_GPS 1
#define GPS_RX_PIN 21
#define GPS_TX_PIN 20
#define PIN_GPS_EN 2
#define GPS_EN_ACTIVE 1
#endif

#ifdef TINYLORA_V3_I2C
#define HAS_I2C 1
#define WIRE_INTERFACES_COUNT (1)
#define I2C_SDA 20
#define I2C_SCL 21
#endif

#define USE_LLCC68
#define USE_SX1262
#define USE_SX1268

#define LORA_SCK 10
#define LORA_MISO 6
#define LORA_MOSI 7
#define LORA_CS 8

#define LORA_DIO0 RADIOLIB_NC
#define LORA_DIO1 3
#define LORA_DIO2 RADIOLIB_NC
#define LORA_BUSY 4
#define LORA_RESET 5

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_BUSY
#define SX126X_RESET LORA_RESET
#define SX126X_DIO2_AS_RF_SWITCH

#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL

#undef  BATTERY_PIN
#define BATTERY_PIN            1            // GPIO1
#define ADC_CHANNEL            ADC1_GPIO1_CHANNEL

#undef  ADC_MULTIPLIER
#define ADC_MULTIPLIER         2.0f

#else // TINYLORA_V4

#define BUTTON_PIN 9
#define LED_PIN 0
#define LED_STATE_ON 1

#define HAS_SCREEN 0

#define USE_LLCC68
#define USE_SX1262
#define USE_SX1268

#define LORA_SCK 10
#define LORA_MISO 6
#define LORA_MOSI 7
#define LORA_CS 8

#define LORA_DIO0 RADIOLIB_NC
#define LORA_DIO1 3
#define LORA_DIO2 RADIOLIB_NC
#define LORA_BUSY 4
#define LORA_RESET 5

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_BUSY
#define SX126X_RESET LORA_RESET
#define SX126X_RXEN 2
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_TXEN RADIOLIB_NC

#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL

#undef  BATTERY_PIN
#define BATTERY_PIN            1            // GPIO1
#define ADC_CHANNEL            ADC1_GPIO1_CHANNEL

#undef  ADC_MULTIPLIER
#define ADC_MULTIPLIER         2.0f

#endif
