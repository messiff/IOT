/*���*/
#ifndef __MOTER_H__
#define __MOTER_H__

extern uchar WindowsFlag ; //�������ϱ�־
extern void MotorCW(uchar Speed);
extern void MotorCCW(uchar Speed);
extern void InitIO();
extern void MotorStop(void);
extern void moter(void);
extern void moterr();

extern void moterl();
#endif