// ===============================
//      Pin Definitions
// ===============================

// Wifi / Receiver
#define WIFI_UART_BLOCK  1
#define WIFI_RX         16
#define WIFI_TX         17

#define I2C_BLK         i2c0 // for both Barometer & Magnetometer

// Barometer
#define BAR_SDA          0
#define BAR_SCL          1
#define BAR_INT          8

// Magnetometer
#define MG_SDA           0
#define MG_SCL           1
#define MG_INT           9
#define MG_DRDY         10

// Accelerometer / Gyroscope
#define IMU_SCL          2
#define IMU_MOSI         3
#define IMU_MISO         4
#define IMU_CSB          5
#define IMU_INT1         6
#define IMU_INT2         7

// Motor drivers / ESC connection
#define MOTOR1          11
#define MOTOR2          12
#define MOTOR3          13
#define MOTOR4          14

// Battery info
#define BAT_SENSE_EN    25
#define BAT_SENSE_VD    26

// MISC
#define STAT_LED        15


// ===============================
//      Battery Config
// ===============================

#define BOOT_MIN_BAT    15
#define MIN_BAT_REQ     5


// ===============================
//      Motor Config
// ===============================

#define MOTOR_MAX_VAL   6249


// ===============================
//      IMU Config
// ===============================

#define I2C_SPEED       400 // kHz

// Barometer
#define BAR_I2C_ADDR    0x77
#define BAR_PRODID      0x10
#define BAR_IDREG       0x8D

// Magnetometer
#define MG_I2C_ADDR     0x10
#define MG_PRODID       0x32
#define MG_IDREG        0x40
