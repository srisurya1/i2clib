include"header.h" 
#include<zephyr/kernel.h>
#define GPIO_BS_ADDR   0x40020000
#define GPIOB_MODE_OFF  0x00    
#define OTYPER_OFF      0x04
#define ODR_OFF         0x14
#define IDR_OFF		0x10
#define PUPR_OFF        0x0C
#define D_TIME          5
#define SDA_PIN         5
#define SCL_PIN         6
#define SDA_REG_SET     1 << SDA_PIN
#define SCL_REG_SET	1 << SCL_PIN
#define SDA_MOD_OUT     1 << (SDA_PIN *2)
#define SCL_MOD_OUT     1 << (SCL_PIN*2)

u8 i2c_init(void)
{
	u32 *mod_reg = GPIO_BS_ADDR + GPIOB_MODE_OFF;
	*mod_reg |= SDA_MOD_OUT |SCL_MOD_OUT;
     volatile u16 *odr = GPIO_BS_ADDR + ODR_OFF;
	*odr |= SCL_REG_SET | SDA_REG_SET;	
	
	u32 *otype = GPIO_BS_ADDR + OTYPER_OFF;
	*otype |= SCL_REG_SET | SDA_REG_SET;
	
	return 0;
}

u8 set_clear(u8 bus_select, u8 high)
{
	volatile *odr = GPIOB_BS_ADDR + ODR_OFF;
	if(bus_select){
		bus_select = SDA_PIN;
	}
	else{
		bus_select = SCL_PIN;
	}

	if(high)
	{
		*odr |= 1 << bus_select;
		k_sleep(K_USEC(D_TIME));
	else
	{
		*odr &= ~(1 << bus_select);
		k_sleep(K_USEC(D_TIME));
	}    
	return 0;
}



u8 sda_data(void)
{
	volatile u16 *idr = GPIOB_BS_ADDR + IDR_OFF;
	return ( *idr >> SDA_PIN) & 1;
}
