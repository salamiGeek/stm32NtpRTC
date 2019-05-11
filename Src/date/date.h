#ifndef __DATE_H__
#define __DATE_H__
#include "stm32f4xx_hal.h"
#include "MacroAndConst.h"

typedef struct 
{
    uint8_t weekStr[10];
    uint8_t monthStr[10];
    uint8_t yearStr[10];
    uint8_t dayStr[10];
    uint8_t hourStr[10];
    uint8_t MinStr[10];
    uint8_t secStr[10];
    uint8_t week;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint16_t year;
}ntpDate;


void resultDate(ntpDate * Date);
void dateAnalysis(uint8_t * p, ntpDate * Date);
void syncNtp(uint8_t * ntp_buff);

#endif
