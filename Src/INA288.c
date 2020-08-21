#include "INA288.h"
extern float current, voltage, power, energy;
void INA288_Reset (void)
{
INA288_write_16(REG_CONFIG_1,INA288_RESET);
}
// ghi vao thanh ghi 16 bit
void INA288_write_16 (unsigned char add, uint16_t data)
{
	uint8_t d[3];
	d[0]=add;
	d[1]=(data>>8)&0xff;
	d[2]=data&0xff;
	//HAL_I2C_Mem_Write(&hi2c1,(INA288_address<<1),add,I2C_MEMADD_SIZE_8BIT,d,2,100);
	HAL_I2C_Master_Transmit(&hi2c1,INA288_address<<1,d,3,500);
}
//doc thanh ghi 40 bit
uint64_t INA288_read_40(unsigned char add)
{
	uint64_t value;
	uint8_t d[5];
	HAL_I2C_Mem_Read(&hi2c1,(INA288_address<<1),add,I2C_MEMADD_SIZE_8BIT,d,5,100);
	value = d[4];
	value = value | (d[3] << 8);
	value = value | (d[2] << 16);
	value = value | (d[1] << 24);
	value = value | (d[0] << 32);
	return value;
}
// doc thanh ghi 24 bit
uint32_t INA288_read_24 (unsigned char add)
{
	uint32_t value;
	uint8_t d[3];
	//HAL_I2C_Mem_Read(&hi2c1,(INA288_address<<1),add,I2C_MEMADD_SIZE_8BIT,d,3,100);
	HAL_I2C_Master_Transmit(&hi2c1,INA288_address<<1,&add,1,100);
	HAL_I2C_Master_Receive(&hi2c1,INA288_address<<1,d,3,100);
	value = d[2];
	value = value | (d[1] << 8);
	value = value | (d[0] << 16);
	value=value>>4;
	return value;
}
// doc thanh ghi 16 bit
uint16_t INA288_read_16(unsigned char add)
{
	uint16_t value;
	uint8_t d[2];
	HAL_I2C_Mem_Read(&hi2c1,(INA288_address<<1),add,I2C_MEMADD_SIZE_8BIT,d,2,100);
	value = d[1];
	value = value | (d[0] << 8);
	return value;
}
// khoi tao sensor
void INA288_init (void)
{
INA288_write_16(REG_CONFIG_1,INA288_CONFIG_1);
INA288_write_16(REG_CURRLSBCALC_3,INA288_CURRLSBCALC_30);
INA288_write_16(REG_ADCCONFIG_2,INA288_ADCCONFIG_2);
INA288_write_16(REG_DIAG_ALRT,INA288_DIAG_ALRT);
}
// do dong & ap
void Measurement(void)
{
	if (INA288_read_16(REG_DIAG_ALRT) & 0x02)
	{
		current=(float)INA288_read_24(REG_CURRENT)*CURRENT_LSB0;
		voltage=(float)INA288_read_24(REG_VBUS)*INA288_VBus;
		power=(float)INA288_read_24(REG_POWER)*POWER_LSB;
		//energy=(float)INA288_read_40(REG_ENERGY)*ENERGY_LSB;
	}
	
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
	INA288_read_24(REG_DIAG_ALRT);
}
void UART_Trans_24(uint32_t dta)
{
	uint8_t d[3];
	d[0]=(dta>>16)&0xff;
	d[1]=(dta>>8)&0xff;
	d[2]=dta&0xff;
	HAL_UART_Transmit(&huart1,d,3,200);
}


