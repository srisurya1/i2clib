#include"header.h"
#define scl(high_low)	set_clear(0,high_low)
#define sda(high_low) 	set_clear(1,high_low)

u8 i2c_start() 
{

	if(!sda(1) && !scl(1) && !sda(0))
	{
		return 0;
	}
	return 1;
	
}
u8 i2c_repeated_start()
{
	
	if( !scl(0) && !(i2c_start()))
	{
	return 0;
	}
	return 1;
}
u8 i2c_stop()
{

	if(!scl(0) && !sda(0) && !scl(1) && !sda(1))
	{
		return 0;
	}
	return 1;
}
u8 i2c_ack_check(void)
{

	if(scl(0))
	{
		return 1;
	
	}
	if(sda(1))
	{
		return 1;
	}
	if(scl(1))
	{
		return 1;
	}
	return sda_data();

}

u8 i2c_nack(void)
{

	if( !scl(0) && !sda(1) && !scl(1))
	{
		return 0;
	}
	return 1;
}
u8 i2c_ack(void)
{
	
	if( !scl(0) && !sda(0) && !scl(1))
	{
		return 0;
	}
	return 1;
}


u8 byte_format(u8 data)
{
	for(s8 i = 7 ; i >= 0 ; i--)
        {
                scl(0);
                if((data >> i)&1)
                {
                        sda(1);
                }
                else
                {
                        sda(0);
                }
                scl(1);

        }
        return i2c_ack_check();
}


u8 target_address(u8 sl_addr, u8 read)
{
	if(read)
	{
		
		sl_addr = (sl_addr << 1 )|1;
	}
	else
	{
		sl_addr = sl_addr << 1;
	}	
	if(byte_format(sl_addr))
	{
		return 1;
	}
	return 0;
}
u8 i2c_write(u8 addr, u8 addr_select, s8 len, u8 data[])
{
	
	u8 j = 0;
	if(addr_select)
	{
		if(target_address(addr,0))
		{
			return 1;
		}
	}
	else
	{
		if(byte_format(addr))
		{
			return 1;
		}
	}

	while(len > 0)
	{
		if(byte_format(data[j]))
		{
			return 1;
		}
		len--;
		j++;
	}
	return 0;
}
u8 i2c_read(u8 sl_addr,s8 len, u8 temp[])
{
	u8 j = 0;
	if(target_address(sl_addr,1))
	{
		return 1;
	}
	while(len > 0 )
	{
		for(s8 i = 7 ; i >= 0 ; i--)
		{
			scl(0);
			scl(1);
			if(sda_data())
			{
				temp[j] |=  (1<<i);
			}
		}
		if(i2c_ack())
		{
			return 1;
		}
		scl(0);
		sda(1);
		
		j++;
		len--;
	}
	return 0;
}


