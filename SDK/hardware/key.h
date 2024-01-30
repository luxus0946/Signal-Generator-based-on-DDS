#ifndef     __KEY_H__
#define     __KEY_H__
#include  "STC8H.H"

//包含编码器
sbit MODE     =  P3^5; // 模式选择循环单向
sbit SELECT  	=  P3^4; // 
sbit ADD      =  P3^7;
sbit SUB      =  P3^6;


sbit OUTPUT   =  P3^3;

unsigned char Key_Mode();
unsigned char Key_Select();
unsigned char Key_Add();
unsigned char Key_Sub();
//unsigned char Key_OUTPUT();
#endif