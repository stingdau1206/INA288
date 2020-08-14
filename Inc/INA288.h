#ifndef INA288_H
#define INA288_H
// register address
#define	REG_CONFIG_1					0x00
#define	REG_ADCCONFIG_2				0x01
#define	REG_CURRLSBCALC_3			0x02
#define	REG_TEMPCOCONFIG_4		0x03
#define REG_VSHUNT						0x04
#define REG_VBUS							0x05
#define REG_DIETEMP						0x06
#define REG_CURRENT						0x07
#define REG_POWER							0x08
#define REG_ENERGY						0x09
#define REG_CHARGE						0x0A
#define REG_DIAG_ALRT					0x0B
#define REG_SOVL							0x0C
#define REG_SUVL							0x0D
#define REG_BOVL							0x0E
#define REG_BUVL							0x0F
#define REG_TEMP_LIMIT				0x10
#define REG_PWR_LIMIT					0x11
#define REG_MANUFACTURER_ID		0x3E
#define REG_DEVICE_ID					0x3F
//Config Value
#define INA288_CONFIG_1				0x0040 // normal mode, delay ADC=2ms, shunt full scale 163.84
#define INA288_ADCCONFIG_2		0xBB6C //Avg ADC = 128 sample, continuous shunt & bus, time convert =1.052ms
#define INA288_CURRLSBCALC_30	0x1000 
#define INA288_CURRLSBCALC_31 0x0400
#define INA288_TEMPCOCONFIG_4 0x0000
#define INA288_DIAG_ALRT			0x8001 // Latch mode, Normal operation
#define INA288_address				0x40 // A0,A1 -> GND
#define INA288_Shunt_Fs0			163.84 // (mV)
#define INA288_Shunt_Fs1			40.96	// (mV)
#define INA288_Vshunt0				312.5 // (nV/LSB)
#define INA288_Vshunt1				78.125 //	(nV/LSB)
#define INA288_VBus						195.3125 // (uV/LSB)
#define INA288_CURRLSBCALC0		4096000
#define INA288_CURRLSBCALC1		1024000
#define INA288_RESET          0x8040
#define Rshunt                0.002
#define CURRENT_LSB0          0.15625 // (mA/LSB)
#define CURRENT_LSB1          0.0390625 // (mA/LSB)
#define POWER_LSB							0.0005 // (W/LSB)
#define ENERGY_LSB						0.008	// (J/LSB)
#include "stm32f1xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
void INA288_init (void);  

void INA288_write_16 (unsigned char add, uint16_t data);

uint64_t INA288_read_40(unsigned char add);

uint32_t INA288_read_24 (unsigned char add);   

uint16_t INA288_read_16(unsigned char add);  

void Measurement(void);

void INA288_Reset (void);
#endif 
