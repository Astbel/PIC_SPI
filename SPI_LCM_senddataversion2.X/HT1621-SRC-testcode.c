
#include "LCDDRIVE.h"
#include "KeyScan.h"
#include "Time.h"
#include "GPIO.h"
#include "YUYIN.h"
#include "adc.h"
#define  BIAS           0X52// 1/4 Duty  1/3Bias
#define  RC256                     0X30//内部时钟256K
#define  SYSTEN         0X02//打开系统振荡器
#define  SYSDIS         0X00//关闭系统振荡器
#define  LCDON                    0X06//打开LCD偏压
#define  LCDOFF                    0X04//off LCD 偏压
void DisplayFirstA(void);
void DisplayFirstB(void);
void LCDDisplayZero(void);
void LCDDisplayOne(void);
void LCDDisplayTwo(void);
void LCDDisplayThree(void);
void LCDDisplayFour(void);
void LCDDisplayFive(void);
void LCDDisplaySix(void);
void LCDDisplayseven(void);
void LCDDisplayEight(void);
void LCDDisplayNight(void);
void LCDDisplayTen(void);
void LCDDisplayElevent(void);
//void LCDDisplayUsbIn(void);
void MaiChong(void);
// const uint8_t DisplayCode[17]={0xfA,0x60,0xd6,0xf4,0x6C,0xbc,0x3e,0xe0,0xfe,0xec,0x00};
/*--------------------------- 0     1     2    3   4    5     6    7    8   9    NULL-----*/
const uint8_t DisplayCode[17]={0xaf,0x06,0x6d,0x4f,0xc6,0xcb,0xeB,0x0e,0xef,0xcf,0x00};
/*--------------------------- 0     1     2    3   4    5     6    7    8   9    NULL-----*/
uint8_t  Ht1621Tab[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t MINIA_ten = 0;   
uint8_t MINIA_ge  = 0;    //剩余时间显示分钟
uint8_t MESCA_ten = 0;
uint8_t MESCA_ge  = 0;    //剩余时间显示秒

uint8_t UsbTimeMin_ten=0;
uint8_t UsbTimeMin_ge=0;
uint8_t UsbTimeHour_ge=0;
uint8_t UsbTimeHour_ten=0;
void HT1621Init(void)
{       
    LcdCSOn;
        LcdDataOn;
        LcdWROn;
        SendComToHT1621(BIAS);   // 1/3 bais . 4 com            
        SendComToHT1621(RC256);  //启动內部256KRC 振蕩器
        SendComToHT1621(SYSDIS);         
        SendComToHT1621(SYSTEN);
        SendComToHT1621(LCDON);
        HT1621_all_off();
}

//-------------------------------------------------------------------------------------
void SendComToHT1621(uint8_t Command)
{        LcdCSOff;
        __nop();
        __nop();
        SendByteHT1621(0X80,4);//送命令模式
        SendByteHT1621(Command,8);
        LcdCSOn;//选择单次送命令。   
}
//-----------------------------------------------------------------------------------------
void SendByteHT1621(uint8_t DataReg,uint8_t CntReg)
{          uint8_t i;
        for(i=0;i<CntReg;i++)
        {       
            if(DataReg>=0x80)
                        LcdDataOn;
                else
                        LcdDataOff;
                LcdWROff;
                __nop();
                __nop();
                LcdWROn;
                __nop();
                __nop();
                DataReg <<= 1;
        }
}

//----------------------------------------------------------------------------------------------
void SendDataHT1621(uint16_t DataReg,uint8_t CntReg)
{        uint8_t i;
        for(i=0;i<CntReg;i++)
        {       
            if((DataReg&0x01)==0)
                         LcdDataOff;
                else
                         LcdDataOn;
                LcdWROff;
                __nop();
                __nop();
                LcdWROn;
                __nop();
                __nop();
                DataReg >>= 1;     
        }
}
//-----------------------------------------------------------------------------------------
void WriteByteHT1621(uint8_t AddrReg,uint8_t DataReg,uint8_t Times)
{       
    LcdCSOff;
        SendByteHT1621(0xa0,3);//送写命令模式
        SendByteHT1621(AddrReg<<2,6);
        SendDataHT1621(DataReg,Times);//
        LcdCSOn;
}
//----------------------------------------------------------------------------------------
void WriteAllDataHT1621(uint8_t AddrReg,uint8_t *p,uint8_t CntReg)
{        uint8_t i;
        LcdCSOff;
        SendByteHT1621(0xa0,3);
        SendByteHT1621(AddrReg<<2,6);
        for(i=0;i<CntReg;i++)
        {       
            SendDataHT1621(*p,8);
                p++;
        }
        LcdCSOn;
}
/**-------------------------------------------------------------------------
                          Name: all_off(清除1621显示)
---------------------------------------------------------------------------*/
void HT1621_all_off(void)
{ uint8_t i,j,t;
                          for (i=0;i<31;i++)
                {
                        t=0x00;
                        for (j=0;j<4;j++)
                        {
                           WriteByteHT1621(i,t,4);  
                        }
                }
}
/****************************************************************************
                 Name: all_on(全部点亮1621)
****************************************************************************/
void HT1621_all_on(void)
{ uint8_t i,j,t;
                          for (i=0;i<31;i++)
                {
                        t=0x01;
                                               
                        for (j=0;j<4;j++)
                        {                                                
                                WriteByteHT1621(i,t,4);
                                t<<=1;
                                t++;                     
                        }
                }
}