/****************************************************************************
* 文 件 名: tem.c
* 作    者: M10F
* 修    订: 2017-6-17
* 版    本: 1.0
* 描    述: 温湿度传感
****************************************************************************/
#include "all.h"
#include "tem.h"
#include "uart1.h"


#define DATA_PIN P0_1

//温湿度定义
uchar ucharFLAG,uchartemp;
uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge=4;
uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
uchar ucharcomdata;

//延时函数
void Delay_us() //1 us延时
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");    
    asm("nop");
    asm("nop");
    asm("nop");    
    asm("nop"); 
}

void Delay_10us() //10 us延时
{
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();
//  Delay_us();   
  uchar i = 0;
  for( i = 18; i > 0; i--);
}

void Delay_ms(uint Time)//n ms延时
{
    unsigned char i;
    while(Time--)
    {
        for(i=0;i<100;i++)
            Delay_10us();
    }
}

//温湿度传感
void COM(void)    // 温湿写入
{     
    uchar i;         
    for(i=0;i<8;i++)    
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);
        Delay_10us();
        Delay_10us();
        Delay_10us();
        uchartemp=0;
        if(DATA_PIN)uchartemp=1;
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++);   
        if(ucharFLAG==1)break;    
        ucharcomdata<<=1;
        ucharcomdata|=uchartemp; 
    }    
}

void DHT11(void)   //温湿传感启动
{
    DATA_PIN=0;
    Delay_ms(19);  //>18MS
    DATA_PIN=1; 
    P0DIR &= ~0x02; //重新配置IO口方向
    Delay_10us();
    Delay_10us();                        
    Delay_10us();
    Delay_10us();  
    if(!DATA_PIN) 
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++); 
        COM();
        ucharRH_data_H_temp=ucharcomdata;
        COM();
        ucharRH_data_L_temp=ucharcomdata;
        COM();
        ucharT_data_H_temp=ucharcomdata;
        COM();
        ucharT_data_L_temp=ucharcomdata;
        COM();
        ucharcheckdata_temp=ucharcomdata;
        DATA_PIN=1; 
        uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_temp+ucharRH_data_L_temp);
        if(uchartemp==ucharcheckdata_temp)
        {
            ucharRH_data_H=ucharRH_data_H_temp;
            ucharRH_data_L=ucharRH_data_L_temp;
            ucharT_data_H=ucharT_data_H_temp;
            ucharT_data_L=ucharT_data_L_temp;
            ucharcheckdata=ucharcheckdata_temp;
        }
        wendu_shi=ucharT_data_H/10; 
        wendu_ge=ucharT_data_H%10;
        
        shidu_shi=ucharRH_data_H/10; 
        shidu_ge=ucharRH_data_H%10;        
    } 
    else //没用成功读取，返回0
    {
        wendu_shi=0; 
        wendu_ge=0;
        
        shidu_shi=0; 
        shidu_ge=0;  
    } 
    
    P0DIR |= 0x02; //IO口需要重新配置 
}
void tem()
{
    uchar temp[3]; 
    uchar humidity[3];   
    uchar strTemp[13]="Temperature:";
    uchar strHumidity[10]="Humidity:";
    uchar tem;
    uchar hum;
    Delay_ms(1000);          //让设备稳定
    InitUart();              //串口初始化
    
             
        memset(temp, 0, 3);
        memset(humidity, 0, 3);
        
        DHT11();             //获取温湿度
        
        //将温湿度的转换成字符串
        temp[0]=wendu_shi+0x30;
        temp[1]=wendu_ge+0x30;
        humidity[0]=shidu_shi+0x30;
        humidity[1]=shidu_ge+0x30;
        
        tem=wendu_shi*10+wendu_ge;
        hum=shidu_shi*10+shidu_ge;
        if(tem>31||hum>60)
            P1_4=1;
        else{
            P1_4=0;
        }
        //获得的温湿度通过串口输出到电脑显示
        UartSendString(strTemp, 12);
        UartSendString(temp, 2);
        UartSendString("   ", 3);
        UartSendString(strHumidity, 9);
        UartSendString(humidity, 2);
        UartSendString("\n", 1);
        
        Delay_ms(2000);  //延时，2S读取1次 
  
}