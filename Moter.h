/*电机*/
#ifndef __MOTER_H__
#define __MOTER_H__

extern uchar WindowsFlag ; //窗帘开合标志
extern void MotorCW(uchar Speed);
extern void MotorCCW(uchar Speed);
extern void InitIO();
extern void MotorStop(void);
extern void moter(void);
extern void moterr();

extern void moterl();
#endif