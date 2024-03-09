#ifndef HEADER_H
#define HEADER_H
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;

u8 target_address(u8, u8 );
u8 i2c_init(void);
u8 i2c_start(void);
u8 i2c_stop(void);
u8 byte_format(u8);
u8 i2c_write(u8, u8, s8, u8 []);
u8 i2c_read( u8, s8, u8 []);
u8 page_erase(u8, u8);
u8 i2c_ack_check(void);
u8 i2c_ack(void);
u8 i2c_nack(void);
u8 sda_data(void);
u8 set_clear(u8, u8);
u8 i2c_repeated_start(void);
#endif    


