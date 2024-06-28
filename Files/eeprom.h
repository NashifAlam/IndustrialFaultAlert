#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

void i2c_eeprom_bytewrite(u8,u8,u8);

u8 i2c_eeprom_randomread(u8,u8);

void i2c_eeprom_pagewrite(u8,u8,s8*,u8);

void i2c_eeprom_seqread(u8,u8,s8*,u8);
