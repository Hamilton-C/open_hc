#define CPU_CLOCK_FREQUENCY     40000000
#define DEVICE_ADDRESS          0x44
#define I2C_WRITE               0
#define I2C_READ                1
#define device_address_wr       ((DEVICE_ADDRESS << 1) | I2C_WRITE)
#define device_address_rd       ((DEVICE_ADDRESS << 1) | I2C_READ)
#define command                 0xFD


void I2Cconf_master(void);
void delay_ms(unsigned int us);
void I2C2_write(unsigned char data);
uint8_t I2C2_read();
void I2C2_start(void);
void I2C2_stop(void);
