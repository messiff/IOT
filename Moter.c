/****************************************************************************
* 文 件 名: Moter.c
* 作    者: M10F
* 修    订: 2017-6-17
* 版    本: 1.0
* 描    述: 电机转动，角度及速度 函数
****************************************************************************/
#include "all.h"
#include "Moter.h"

#define A1 P0_4 //定义步进电机连接端口
#define B1 P0_5
#define C1 P0_6
#define D1 P0_7

uchar phasecw[4] ={0x80,0x40,0x20,0x10};//正转 电机导通相序 D-C-B-A
uchar phaseccw[4]={0x10,0x20,0x40,0x80};//反转 电机导通相序 A-B-C-D

uchar WindowsFlag = 0; //窗帘开合标志

void MotorData(uchar data)
{
  A1 = 1&(data>>4);
  B1 = 1&(data>>5);
  C1 = 1&(data>>6);
  D1 = 1&(data>>7);
}


//顺时针转动
void MotorCW(uchar Speed)
{
  uchar i;
  for(i=0;i<4;i++)
  {
    MotorData(phasecw[i]);
    Delay_ms(Speed);//转速调节
  }
}
//逆时针转动
void MotorCCW(uchar Speed)
{
  uchar i;
  for(i=0;i<4;i++)
  {
    MotorData(phaseccw[i]);
    Delay_ms(Speed);//转速调节
  }
}

//停止转动
void MotorStop(void)
{
  MotorData(0x00);
}

/****************************************************************************
* 名    称: InitIO()
* 功    能: 初始化IO口程序
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitIO(void)
{
  P0SEL &= 0x0F;  //P04 05 06 07定义为普通IO
  P0DIR |= 0xF0;  //P04 05 06 07定义为输出
}

/****************************************************************************
* 程序入口函数
****************************************************************************/
void moter()
{
//  
//  uchar WindowsFlag = 0; //窗帘开合标志
  uint i;
  uchar ucSpeed;
  CLKCONCMD &= ~0x40;                        //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA & 0x40);                   //等待晶振稳定为32M
  CLKCONCMD &= ~0x47;                        //设置系统主时钟频率为32MHZ   
  
  //  InitUart();
  Delay_ms(1000);          //让设备稳定
  InitIO();
  uchar buf[2];
  //  
  //  //改变这个参数可以调整电机转速，数字越小，转速越大,力矩越小
  ucSpeed = 3;    //调整速度   建议在2-10范围内
  //
//  while(1){
//    //MotorCW(500);
//    light();    //读取光强值
//    Light = (buf[0] << 8) + buf[1];
    
    if(Light<2000&&WindowsFlag==0)//窗帘关闭&&光照小
    {  
      for(i=0;i<200;i++)
      {
        MotorCW(ucSpeed); //顺时针转动
      } 
     
      WindowsFlag=1;
    }
    else if(Light>2000&&WindowsFlag==1) //光照大&&窗帘开
    {  
      for(i=0;i<200;i++)
      {
        MotorCCW(ucSpeed);//逆时针转动
      } 
      
     
      WindowsFlag=0;
    }
    
//    else 
//    {
//      MotorStop(); 
//    }
    //    UartSenddata(buf,2);
    // CurtainOpen(500);
  }
//}
void moterr()
{
//  
  uchar WindowsFlag = 0; //窗帘开合标志
  uint i;
  uchar ucSpeed;
  CLKCONCMD &= ~0x40;                        //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA & 0x40);                   //等待晶振稳定为32M
  CLKCONCMD &= ~0x47;                        //设置系统主时钟频率为32MHZ   
  
  //  InitUart();

  InitIO();
  //  
  //  //改变这个参数可以调整电机转速，数字越小，转速越大,力矩越小
  ucSpeed = 3;    //调整速度   建议在2-10范围内
  //
  
  for(i=0;i<200;i++)
  {
    MotorCW(ucSpeed); //顺时针转动
  } 
  MotorStop();        //停止转动   
     

}
void moterl()
{
    //  
    uchar WindowsFlag = 0; //窗帘开合标志
    uint i;
    uchar ucSpeed;
    CLKCONCMD &= ~0x40;                        //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                   //等待晶振稳定为32M
    CLKCONCMD &= ~0x47;                        //设置系统主时钟频率为32MHZ   
    
    //  InitUart();
    
    InitIO();
    //  
    //  //改变这个参数可以调整电机转速，数字越小，转速越大,力矩越小
    ucSpeed = 3;    //调整速度   建议在2-10范围内
    //
    
    
    
    
    for(i=0;i<200;i++)
    {
        MotorCCW(ucSpeed); //顺时针转动
    } 
    MotorStop();        //停止转动   
    
    
}