#include<stdio.h>
#include<string.h>
	
#include<zephyr/kernel.h>
#include"header.h"
#define SL_ADDR 0x50
int main()
{
	u8 data[3] = {0x22,0x02,0x66},read[3] = {0};
	if(i2c_init())
	{
		return 0;
	}
	if(i2c_start())
	{
		return 0;	
	}
	if(i2c_write(SL_ADDR,1,0,data))//sl addr
	{
		goto stop;
	}

	if(i2c_write(0x03,0,3,data))// mem addr

	{
		goto stop;
	}
	if(i2c_stop())
	{
		return 0;
	}

	//dummy write for read
	if(i2c_start())
	{
		return 0;
	}
	
	if(i2c_write(SL_ADDR,1,0,data))
	{
		goto stop;
	}
	if(i2c_write(0x03,0,0,data)) //dummy write
	{
		goto stop;
	}

	if(i2c_repeated_start())
	{
		return 0;
	}
	
	if(i2c_read(SL_ADDR,3,read))
	{
		goto stop;
	}	
stop:
	if(i2c_stop())
	{
		return 0;
	}	
	printf("%d %d %d ",read[0],read[1],read[2]);
	return 0;
		
}

