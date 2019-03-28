/****************************************************************************
* �� �� ��: Moter.c
* ��    ��: M10F
* ��    ��: 2017-6-17
* ��    ��: 1.0
* ��    ��: ���ת�����Ƕȼ��ٶ� ����
****************************************************************************/
#include "all.h"
#include "Moter.h"

#define A1 P0_4 //���岽��������Ӷ˿�
#define B1 P0_5
#define C1 P0_6
#define D1 P0_7

uchar phasecw[4] ={0x80,0x40,0x20,0x10};//��ת �����ͨ���� D-C-B-A
uchar phaseccw[4]={0x10,0x20,0x40,0x80};//��ת �����ͨ���� A-B-C-D

uchar WindowsFlag = 0; //�������ϱ�־

void MotorData(uchar data)
{
  A1 = 1&(data>>4);
  B1 = 1&(data>>5);
  C1 = 1&(data>>6);
  D1 = 1&(data>>7);
}


//˳ʱ��ת��
void MotorCW(uchar Speed)
{
  uchar i;
  for(i=0;i<4;i++)
  {
    MotorData(phasecw[i]);
    Delay_ms(Speed);//ת�ٵ���
  }
}
//��ʱ��ת��
void MotorCCW(uchar Speed)
{
  uchar i;
  for(i=0;i<4;i++)
  {
    MotorData(phaseccw[i]);
    Delay_ms(Speed);//ת�ٵ���
  }
}

//ֹͣת��
void MotorStop(void)
{
  MotorData(0x00);
}

/****************************************************************************
* ��    ��: InitIO()
* ��    ��: ��ʼ��IO�ڳ���
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitIO(void)
{
  P0SEL &= 0x0F;  //P04 05 06 07����Ϊ��ͨIO
  P0DIR |= 0xF0;  //P04 05 06 07����Ϊ���
}

/****************************************************************************
* ������ں���
****************************************************************************/
void moter()
{
//  
//  uchar WindowsFlag = 0; //�������ϱ�־
  uint i;
  uchar ucSpeed;
  CLKCONCMD &= ~0x40;                        //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA & 0x40);                   //�ȴ������ȶ�Ϊ32M
  CLKCONCMD &= ~0x47;                        //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
  
  //  InitUart();
  Delay_ms(1000);          //���豸�ȶ�
  InitIO();
  uchar buf[2];
  //  
  //  //�ı�����������Ե������ת�٣�����ԽС��ת��Խ��,����ԽС
  ucSpeed = 3;    //�����ٶ�   ������2-10��Χ��
  //
//  while(1){
//    //MotorCW(500);
//    light();    //��ȡ��ǿֵ
//    Light = (buf[0] << 8) + buf[1];
    
    if(Light<2000&&WindowsFlag==0)//�����ر�&&����С
    {  
      for(i=0;i<200;i++)
      {
        MotorCW(ucSpeed); //˳ʱ��ת��
      } 
     
      WindowsFlag=1;
    }
    else if(Light>2000&&WindowsFlag==1) //���մ�&&������
    {  
      for(i=0;i<200;i++)
      {
        MotorCCW(ucSpeed);//��ʱ��ת��
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
  uchar WindowsFlag = 0; //�������ϱ�־
  uint i;
  uchar ucSpeed;
  CLKCONCMD &= ~0x40;                        //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA & 0x40);                   //�ȴ������ȶ�Ϊ32M
  CLKCONCMD &= ~0x47;                        //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
  
  //  InitUart();

  InitIO();
  //  
  //  //�ı�����������Ե������ת�٣�����ԽС��ת��Խ��,����ԽС
  ucSpeed = 3;    //�����ٶ�   ������2-10��Χ��
  //
  
  for(i=0;i<200;i++)
  {
    MotorCW(ucSpeed); //˳ʱ��ת��
  } 
  MotorStop();        //ֹͣת��   
     

}
void moterl()
{
    //  
    uchar WindowsFlag = 0; //�������ϱ�־
    uint i;
    uchar ucSpeed;
    CLKCONCMD &= ~0x40;                        //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);                   //�ȴ������ȶ�Ϊ32M
    CLKCONCMD &= ~0x47;                        //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
    
    //  InitUart();
    
    InitIO();
    //  
    //  //�ı�����������Ե������ת�٣�����ԽС��ת��Խ��,����ԽС
    ucSpeed = 3;    //�����ٶ�   ������2-10��Χ��
    //
    
    
    
    
    for(i=0;i<200;i++)
    {
        MotorCCW(ucSpeed); //˳ʱ��ת��
    } 
    MotorStop();        //ֹͣת��   
    
    
}