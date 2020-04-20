

#include <stdio.h>
#include <string.h>
#include "gizwits_protocol.h"
#include "usart3.h"


/**@} */
/**@name Gizwits 用户API接口
* @{
*/
extern dataPoint_t currentDataPoint;
/**
* @brief 事件处理接口

* 说明：

* 1.用户可以对WiFi模组状态的变化进行自定义的处理

* 2.用户可以在该函数内添加数据点事件处理逻辑，如调用相关硬件外设的操作接口

* @param[in] info : 事件队列
* @param[in] data : 协议数据
* @param[in] len : 协议数据长度
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)data;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)data;
  protocolTime_t *ptime = (protocolTime_t *)data;

  if((NULL == info) || (NULL == data))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
     /* case EVENT_RGB_ONOFF:
        currentDataPoint.valueRGB_OnOff = dataPointPtr->valueRGB_OnOff;
        GIZWITS_LOG("Evt: EVENT_RGB_ONOFF %d \n", currentDataPoint.valueRGB_OnOff);
        if(0x01 == currentDataPoint.valueRGB_OnOff)
        {
          //user handle
			 switch(currentDataPoint.valueRGB_Col)
			 {
				 case RGB_COL_VALUE0:  
					   RGBLED_Show(currentDataPoint.valueRGB_R, currentDataPoint.valueRGB_G, currentDataPoint.valueRGB_B);//显示自定义的颜色
				       break;
              	 case RGB_COL_VALUE1:
					   RGBLED_Show(254, 254, 0);//黄色 
				       break;
				 case RGB_COL_VALUE2:
					   RGBLED_Show(254, 0, 70);//紫色
				       break;
                 case RGB_COL_VALUE3:	
                       RGBLED_Show(238 ,30 ,30);//粉色	
                       break;				 
			 }
        }
        else
        {
          //user handle 
               RGBLED_Show(0,0,0);//关闭					
        }
        break;

      case EVENT_RGB_COL:
        currentDataPoint.valueRGB_Col = dataPointPtr->valueRGB_Col;
        GIZWITS_LOG("Evt: EVENT_RGB_COL %d\n", currentDataPoint.valueRGB_Col);
        switch(currentDataPoint.valueRGB_Col)
        {
          case RGB_COL_VALUE0:
            //user handle
		      if(currentDataPoint.valueRGB_OnOff==0x01)
		       RGBLED_Show(currentDataPoint.valueRGB_R,currentDataPoint.valueRGB_G,currentDataPoint.valueRGB_B);//自定义
            break;
          case RGB_COL_VALUE1:
            //user handle
		      if(currentDataPoint.valueRGB_OnOff==0x01)
		        RGBLED_Show(254, 254, 0);//黄色
            break;
          case RGB_COL_VALUE2:
            //user handle
		       if(currentDataPoint.valueRGB_OnOff==0x01)
		       RGBLED_Show(254, 0, 70);//紫色
            break;
          case RGB_COL_VALUE3:
            //user handle
		      if(currentDataPoint.valueRGB_OnOff==0x01)
		       RGBLED_Show(238 ,30 ,30);//粉色
            break;
          default:
            break;
        }
        break;

      case EVENT_RGB_R:
        currentDataPoint.valueRGB_R = dataPointPtr->valueRGB_R;
        GIZWITS_LOG("Evt:EVENT_RGB_R %d\n",currentDataPoint.valueRGB_R);
        //user handle
	     if((currentDataPoint.valueRGB_OnOff==0x01)&&(currentDataPoint.valueRGB_Col==RGB_COL_VALUE0))//在自定义下可调
	     RGBLED_Show(currentDataPoint.valueRGB_R,currentDataPoint.valueRGB_G,currentDataPoint.valueRGB_B);//控制RGB_R颜色
        break;
      case EVENT_RGB_G:
        currentDataPoint.valueRGB_G = dataPointPtr->valueRGB_G;
        GIZWITS_LOG("Evt:EVENT_RGB_G %d\n",currentDataPoint.valueRGB_G);
        //user handle
	     if((currentDataPoint.valueRGB_OnOff==0x01)&&(currentDataPoint.valueRGB_Col==RGB_COL_VALUE0))//在自定义下可调
	    RGBLED_Show(currentDataPoint.valueRGB_R,currentDataPoint.valueRGB_G,currentDataPoint.valueRGB_B);//控制RGB_G颜色
        break;
      case EVENT_RGB_B:
        currentDataPoint.valueRGB_B = dataPointPtr->valueRGB_B;
        GIZWITS_LOG("Evt:EVENT_RGB_B %d\n",currentDataPoint.valueRGB_B);
        //user handle
	     if((currentDataPoint.valueRGB_OnOff==0x01)&&(currentDataPoint.valueRGB_Col==RGB_COL_VALUE0))//在自定义下可调
	     RGBLED_Show(currentDataPoint.valueRGB_R,currentDataPoint.valueRGB_G,currentDataPoint.valueRGB_B);//控制RGB_B颜色
        break;*/
				
			case EVENT_Water_infusing:
        currentDataPoint.valueWater_infusing = dataPointPtr->valueWater_infusing;
        GIZWITS_LOG("Evt: EVENT_Water_infusing %d \n", currentDataPoint.valueWater_infusing);
        if(0x01 == currentDataPoint.valueWater_infusing)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;


      case EVENT_Target_temperature:
        currentDataPoint.valueTarget_temperature = dataPointPtr->valueTarget_temperature;
        GIZWITS_LOG("Evt:EVENT_Target_temperature %d\n",currentDataPoint.valueTarget_temperature);
        //user handle
        break;
      case EVENT_Block_using_number:
        currentDataPoint.valueBlock_using_number = dataPointPtr->valueBlock_using_number;
        GIZWITS_LOG("Evt:EVENT_Block_using_number %d\n",currentDataPoint.valueBlock_using_number);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
        break;
      case WIFI_DISCON_ROUTER:
        break;
      case WIFI_CON_M2M:
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      default:
        break;
    }
  }

  return 0;
}


/**@} */

/**
* @brief MCU复位函数

* @param none
* @return none
*/
void mcuRestart(void)
{
     __set_FAULTMASK(1);//关闭所有中断
     NVIC_SystemReset();//复位
}

/**@} */
/**
* @brief 系统毫秒计时维护函数,毫秒自增,溢出归零

* @param none
* @return none
*/
static uint32_t timerMsCount;
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief 读取系统时间毫秒计时数

* @param none
* @return 系统时间毫秒数
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief 定时器TIM3中断处理函数

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief USART2串口中断函数

* 接收功能，用于接收与WiFi模组间的串口协议数据
* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief 串口写操作，发送数据到WiFi模组
*
* @param buf      : 数据地址
* @param len       : 数据长度
*
* @return : 正确返回有效数据长度;-1，错误返回
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
#endif
    
    for(i=0; i<len; i++)
    {
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //实现串口发送函数,将buf[i]发送到模组
		USART_SendData(USART3,buf[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕 
#ifdef PROTOCOL_DEBUG
        GIZWITS_LOG("%02x ", buf[i]);
#endif
        if(i >=2 && buf[i] == 0xFF)
        {
          //实现串口发送函数,将0x55发送到模组
		USART_SendData(USART3,0x55);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕 
#ifdef PROTOCOL_DEBUG
        GIZWITS_LOG("%02x ", 0x55);
#endif
        }
    }
    
#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("\n");
#endif
    
    return len;
}


