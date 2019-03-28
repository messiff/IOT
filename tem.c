/****************************************************************************
* �� �� ��: tem.c
* ��    ��: M10F
* ��    ��: 2017-6-17
* ��    ��: 1.0
* ��    ��: ��ʪ�ȴ���
****************************************************************************/
#include "all.h"
#include "tem.h"
#include "uart1.h"


#define DATA_PIN P0_1

//��ʪ�ȶ���
uchar ucharFLAG,uchartemp;
uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge=4;
uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
uchar ucharcomdata;

//��ʱ����
void Delay_us() //1 us��ʱ
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

void Delay_10us() //10 us��ʱ
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

void Delay_ms(uint Time)//n ms��ʱ
{
    unsigned char i;
    while(Time--)
    {
        for(i=0;i<100;i++)
            Delay_10us();
    }
}

//��ʪ�ȴ���
void COM(void)    // ��ʪд��
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

void DHT11(void)   //��ʪ��������
{
    DATA_PIN=0;
    Delay_ms(19);  //>18MS
    DATA_PIN=1; 
    P0DIR &= ~0x02; //��������IO�ڷ���
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
    else //û�óɹ���ȡ������0
    {
        wendu_shi=0; 
        wendu_ge=0;
        
        shidu_shi=0; 
        shidu_ge=0;  
    } 
    
    P0DIR |= 0x02; //IO����Ҫ�������� 
}
void tem()
{
    uchar temp[3]; 
    uchar humidity[3];   
    uchar strTemp[13]="Temperature:";
    uchar strHumidity[10]="Humidity:";
    uchar tem;
    uchar hum;
    Delay_ms(1000);          //���豸�ȶ�
    InitUart();              //���ڳ�ʼ��
    
             
        memset(temp, 0, 3);
        memset(humidity, 0, 3);
        
        DHT11();             //��ȡ��ʪ��
        
        //����ʪ�ȵ�ת�����ַ���
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
        //��õ���ʪ��ͨ�����������������ʾ
        UartSendString(strTemp, 12);
        UartSendString(temp, 2);
        UartSendString("   ", 3);
        UartSendString(strHumidity, 9);
        UartSendString(humidity, 2);
        UartSendString("\n", 1);
        
        Delay_ms(2000);  //��ʱ��2S��ȡ1�� 
  
}