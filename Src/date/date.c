#include "date.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx_it.h"
#include "rtc.h"
#include "usart.h"


//---------------------------解析星期----------------------------------------
uint8_t weekAnalysis(ntpDate * Date)
{
    uint8_t week;

    switch (Date->weekStr[0])
      {
        case 'S':
        week = 0;                     // 星期日
        switch (Date->weekStr[1])
        {
          case 'a':
            week = 6;                 // 星期六
            break;
          
          default:
            break;
        }
        break;
        
        case 'M':
        week = 1;
        break;

        case 'T':
        week = 2;
        switch (Date->weekStr[1])
        {
          case 'h':
          week = 4;
          break;
        
        default:
          break;
        }
        break;

        case 'W':
        week = 3;
        break;

        case 'F':
        week = 5;
        break;
      
        default:
          break;
      }

      return week;
}

//---------------------解析月份--------------------------------------------------
uint8_t monthAnalysis(ntpDate * Date)
{
    uint8_t month;

    switch (Date->monthStr[0])
    {
    case 'J':
        month = 1;
        switch (Date->monthStr[1])
        {
        case 'u':
            month = 6;
            switch (Date->monthStr[2])
            {
            case 'l':
                month = 7;
                break;
            
            default:
                break;
            }
            break;
        
        default:
            break;
        }
        break;
    
    case 'F':
        month = 2;
        break;

    case 'M':
        month = 3;
        switch (Date->monthStr[2])
        {
        case 'y':
            month = 5;
            break;
        
        default:
            break;
        }
        break;
    
    case 'A':
        month = 4;
        switch (Date->monthStr[1])
        {
        case 'u':
            month = 8;
            break;
        
        default:
            break;
        }
        break;
    
    case 'S':
        month = 9;
        break;

    case 'O':
        month = 10;
        break;

    case 'N':
        month = 11;
        break;
    
    case 'D':
        month = 12;
        break;
    
    default:
        break;
    }

    return month;
}

//------------------解析年份---------------------------------------------------------------------
uint16_t yearAnalysis(ntpDate * Date)
{
    return (uint16_t)strtol((const char *)Date->yearStr,NULL,10);
}

//------------------解析日子---------------------------------------------------------------------
uint8_t dayAnalysis(ntpDate * Date)
{
    return (uint8_t)strtol((const char *)Date->dayStr,NULL,10);
}

//------------------解析时---------------------------------------------------------------------
uint8_t hourAnalysis(ntpDate * Date)
{
    return (uint8_t)strtol((const char *)Date->hourStr,NULL,10);
}

//------------------解析分---------------------------------------------------------------------
uint8_t minAnalysis(ntpDate * Date)
{
    return (uint8_t)strtol((const char *)Date->MinStr,NULL,10);
}
//------------------解析秒---------------------------------------------------------------------
uint8_t secAnalysis(ntpDate * Date)
{
    return (uint8_t)strtol((const char *)Date->secStr,NULL,10);
}

//------------------填入年月日时分秒------------------------------------------------------------------
void resultDate(ntpDate * Date)
{
    Date->week = weekAnalysis(Date);
    Date->year = yearAnalysis(Date);
    Date->month = monthAnalysis(Date);
    Date->day = dayAnalysis(Date);
    Date->hour = hourAnalysis(Date);
    Date->min = minAnalysis(Date);
    Date->sec = secAnalysis(Date);
}

//-----------------从字符串中解析出各部分分段-----------------------------------------------------------
void dateAnalysis(uint8_t * p, ntpDate * Date)
{
    uint8_t last_n=0,n=0;
    do
    {
        n++;
    } while (p[n] != ' ');
    memcpy(Date->weekStr,&p[last_n],n-last_n);
    last_n = n+1;

    do
    {
        n++;
    } while (p[n] != ' ');
    memcpy(Date->monthStr,&p[last_n],n-last_n);
    last_n = n+1;

    // do
    // {
    //     n++;
    // } while (p[n] != ' ');
    n +=2;
    memcpy(Date->dayStr,&p[last_n],2);
    last_n = n+1;

    do
    {
        n++;
    } while (p[n] != ':');
    memcpy(Date->hourStr,&p[last_n],n-last_n);
    last_n = n+1;

    do
    {
        n++;
    } while (p[n] != ':');
    memcpy(Date->MinStr,&p[last_n],n-last_n);
    last_n = n+1;
    
    do
    {
        n++;
    } while (p[n] != ' ');
    memcpy(Date->secStr,&p[last_n],n-last_n);
    last_n = n+1;

    do
    {
        n++;
    } while (p[n] != 0x0A);
    memcpy(Date->yearStr,&p[last_n],n-last_n);
    
}

//-----------------------------------------------------------
void syncNtp(uint8_t * ntp_buff)
{
	uint32 lastRunTime = runTimeCount;
	do
	{
		HAL_UART_Receive(&huart4,ntp_buff,25,100);
		printf("syncNtp--------->tme:%d\r\n",runTimeCount);
	}while(ntp_buff[24] != 0x0A && runTimeCount-lastRunTime < 10);
	HAL_UART_Receive_IT(&huart4,ntp_buff,25);
	
}
