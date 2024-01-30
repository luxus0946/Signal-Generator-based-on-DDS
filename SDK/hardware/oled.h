#include "stc8h.h"
#include "intrins.h"
#ifndef __OLED_H__
#define __OLED_H__			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0


sbit OLED_SCL=P1^1;// P10 SCL
sbit OLED_SDIN=P1^0;//P11 SDA

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1





//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   




//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
//void OLED_Display_On(void);
//void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
//void OLED_DrawPoint(u8 x,u8 y,u8 t);
//                                                                                                                                                                    void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
void OLED_ShowChar2(u8 x,u8 y,u8 chr,u8 Char_Size);//ȡ��
void OLED_ShowNum2(u8 x,u8 y,u32 num,u8 len,u8 size2);//ȡ��
void OLED_ShowString2(u8 x,u8 y, u8 *p,u8 Char_Size);//ȡ��
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//void Delay50ms(unsigned int Del_50ms);
//void Delay1ms(unsigned int Del_1ms);
//void Delay_ms(unsigned int ms);
//void fill_picture(unsigned char fill_Data);
//void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();
#endif  
	 



