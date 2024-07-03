#include "MQ2.h"
#include <LPC21xx.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>
#include "lcd.h"
#include "kpm.h"
#include "delay.h"
#include "I2C.h"
#include "eeprom.h"
#include "LED.h"
#include "interrupt.h" 
#include "GSM.h"

int interSwitch(void);
int ackSwitch(void);
