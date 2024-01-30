#include "STC8H.h"
#include "intrins.h"
#include "oled.h"
#include "key.h"
#include "delay.h"
#include "AD9833.h"
#include "FLASH.h"
//宏定义
#define uint8_t unsigned char
#define uint16_t  unsigned int
#define uint32_t unsigned long

double FREQ=0;
#define Phase Ph 
//函数声明
void init_IO();//初始化IO
void Para_Set_page();//参数页
void Para_Setting_page();//参数设置页
void OPEN_page();    //开机动画
double Freq_Cal();
void Flash_read();
void Flash_save();
//参数定义

char *_WAVE[]={ "TRIA","SINE","SQUA"};
uint8_t Wave=1;

char *_UNIT[]={"Hz ","kHz","MHz"};

//ADC反馈
uint16_t VF_buf[10]={0};
char _i=0;
char i=0;
char j=0;
//amp
char AmpH=5;
char AmpL=0;
unsigned char amp=0;
//Ph
uint8_t Ph=0;
//FREQ
uint8_t _FREQ[]={0,0,0,0,0,0,0};//QBSGXU
uint8_t FR = 0;
uint8_t _FR = 0;

//Vf
uint8_t _Vf=0;
uint8_t Vf_H=0;
uint8_t Vf_L=0;
double Vf=0;
double Vf_b=0;
double Vf_Max=0 ;
//变量
uint8_t _mode =0;
uint8_t _select =0;
uint8_t refresh=0;


void main(){  
  P_SW2|= 0x80;  //扩展寄存器XFR访问使能
  init_IO(); //初始化IO
  OLED_Init();//初始化OLED
	OPEN_page();
	Flash_read();
	delay_ms(5000);
	Para_Setting_page();
	AD9833_WaveSeting(0,0,0,0);
	
  while(1){
	//OLED_ShowString2(64,0,_WAVE[wave],16);

		//刷新
		if(refresh){
				AD9833_WaveSeting(0,0,0,0);
				Para_Setting_page();
				refresh=0;
		}
	
  	_mode+=Key_Mode();
	  _mode%=4;
	
	

	switch(_mode){
		
		
	case 0:{
				OLED_ShowString(0,4,"FREQ:",16);
				if(_FREQ[0])
				OLED_ShowNum(48,4,_FREQ[0],1,16);
				else 
				OLED_ShowString(48,4," ",16);
				
				if(_FREQ[1]||_FREQ[0])
				OLED_ShowNum(56,4,_FREQ[1],1,16);
				else 
				OLED_ShowString(56,4," ",16);
				
				if(_FREQ[1]||_FREQ[0]||_FREQ[2])
				OLED_ShowNum(64,4,_FREQ[2],1,16);
				else 
				OLED_ShowString(64,4," ",16);
				
				OLED_ShowNum(72,4,_FREQ[3],1,16);
				
				OLED_ShowString(80,4,".",16);
				OLED_ShowNum(88,4,_FREQ[5],1,16);
				OLED_ShowString(104,4,_UNIT[_FREQ[6]],16);
         		
		Wave+=Key_Select();
		Wave%=3;
		OLED_ShowString2(64,0,_WAVE[Wave],16);
	
		break;
	}
	
		
		
  case 1:{
	  OLED_ShowString(64,0,_WAVE[Wave],16);
		_select+=Key_Select();
		_select%=2;
		if(_select==1){
			AmpH=5;
			AmpL=0;
			OLED_ShowNum2(32,2,AmpH,1,16);
			OLED_ShowString2(40,2,".",16);
			OLED_ShowNum2(48,2,AmpL,1,16);}
		else{
			AmpH=3;
			AmpL=3;
			OLED_ShowNum2(48,2,AmpL,1,16);
			OLED_ShowString2(40,2,".",16);
			OLED_ShowNum2(32,2,AmpH,1,16);}	
		
		break;	
	}
	
		
		
	case 2:{
		      OLED_ShowNum(48,2,AmpL,1,16);
		      OLED_ShowString(40,2,".",16);
			    OLED_ShowNum(32,2,AmpH,1,16);
		      OLED_ShowNum2(96,2,Ph,3,16);
		
		      Ph+=Key_Add();
		      Ph-=Key_Sub();
		
					if(Ph>360)
						Ph=Ph-360;
					else if(Ph<0)
						Ph=Ph-360;
					
					OLED_ShowNum2(96,2,Ph,3,16);
	        break;	
	}
	     
			
   case 3:{
		 
		      OLED_ShowNum(96,2,Ph,3,16);
		      FR+=Key_Select();
		      if(FR==7)
					OLED_ShowString(104,4,_UNIT[_FREQ[6]],16);
		      FR%=7;
		      if(FR==4){}
					else if(FR==6){
					OLED_ShowString2(104,4,_UNIT[_FREQ[6]],16);
					OLED_ShowNum(88,4,_FREQ[5],1,16);	
					}
					else{
					OLED_ShowNum2(48+8*FR,4,_FREQ[FR],1,16);
					if(_FR!=FR)
					OLED_ShowNum(48+8*_FR,4,_FREQ[_FR],1,16);
					_FR=FR;
				  }
					
					_FREQ[FR]+=Key_Add();
				  _FREQ[FR]-=Key_Sub();
					_FREQ[FR]%=10;
					_FREQ[6]%=3; 
          break;
	    }      
	  }

		
	    //OUTPUT
	    while(P33==0)
			{ FREQ=Freq_Cal(); 
				Flash_save();
				if(AmpH==5){
					if(Wave==SQU_WAVE)
						amp=30;
					else
					  amp=((FREQ*10)/1000000)+180;
				}
				else{
					if(Wave==SQU_WAVE)
						amp=15;
					else
					amp=((FREQ*15)/1000000)+130;
				}
				
		    Para_Set_page();
	      refresh=1;
	      AD9833_AmpSet(amp);
	      AD9833_WaveSeting(FREQ,0,Wave,Ph);
				while(P33==0){
	        }
			}
	 } 
}

void init_IO(){
  RSTCFG=0x50;  //开启RST键进入ISP模式

			P1M1 = 0x08;   P1M0 = 0x00;   //设置P1口为准双向口 P1.3高阻输入
			P3M1 = 0x00;   P3M0 = 0x00;   //设置P3口为准双向口
      
			P3IM0 = 0x00; //低电平中断
      P3IM1 = 0xff;
	    
	    ADCTIM = 0x3f; //设置 ADC 内部时序
      ADCCFG = 0x2f; //右对齐
	    ADC_CONTR= 0x83; //P1.3
	
	   //	EA = 1;
}
	






double Freq_Cal(){
 
        switch(_FREQ[6]) {
				
				 case 0:return (_FREQ[0]*1000+_FREQ[1]*100+_FREQ[2]*10+_FREQ[3]+0.1*_FREQ[5]);
						break;	 
				 case 1:return (_FREQ[0]*1000+_FREQ[1]*100+_FREQ[2]*10+_FREQ[3]+0.1*_FREQ[5])*1000;
						break;		
				 case 2:return (_FREQ[0]*1000+_FREQ[1]*100+_FREQ[2]*10+_FREQ[3]+0.1*_FREQ[5])*1000000;
					  break;	
				}   
        return 0;
}       


void OPEN_page(){
  OLED_Clear();
	OLED_ShowString(40,5,"____ ",16);
	
	
	OLED_ShowCHinese(0,0,0);//基
  OLED_ShowCHinese(16,0,1);//于
	OLED_ShowCHinese(32,0,2);//D
	OLED_ShowCHinese(48,0,3);//D
	OLED_ShowCHinese(64,0,4);//S
	OLED_ShowCHinese(80,0,5);//的
	OLED_ShowCHinese(96,0,6);//多
	OLED_ShowCHinese(16,3,7);//功
	OLED_ShowCHinese(32,3,8);//能
	OLED_ShowCHinese(48,3,9);//信
	OLED_ShowCHinese(64,3,10);//号
	OLED_ShowCHinese(80,3,11);//发
	OLED_ShowCHinese(96,3,12);//生
	OLED_ShowCHinese(112,3,13);//器
	
	
	OLED_ShowCHinese(80,6,14);//C
	OLED_ShowCHinese(96,6,15);//0
	OLED_ShowCHinese(112,6,16);//6
}
void Para_Set_page(){
  OLED_Clear();
	OLED_ShowString(0,0,"WAVE:",16);
	OLED_ShowString(64,0,_WAVE[Wave],16);

	OLED_ShowString(0,2,"AMP:",16);
	OLED_ShowNum(32,2,AmpH,1,16);
	OLED_ShowString(40,2,".",16);
	OLED_ShowNum(48,2,AmpL,1,16);
	OLED_ShowString(56,2,"V",16);
	
	OLED_ShowString(72,2,"Ph:",16);
	OLED_ShowNum(96,2,Ph,3,16);
	OLED_ShowString(120,2,"d",16);
	
	
  OLED_ShowString(0,4,"FREQ:",16);
	if(_FREQ[0])
	OLED_ShowNum(48,4,_FREQ[0],1,16);
	else 
	OLED_ShowString(48,4," ",16);
	
	if(_FREQ[1]||_FREQ[0])
	OLED_ShowNum(56,4,_FREQ[1],1,16);
	else 
	OLED_ShowString(56,4," ",16);
	
	if(_FREQ[1]||_FREQ[0]||_FREQ[2])
	OLED_ShowNum(64,4,_FREQ[2],1,16);
	else 
	OLED_ShowString(64,4," ",16);
	
	OLED_ShowNum(72,4,_FREQ[3],1,16);
	
	OLED_ShowString(80,4,".",16);
	OLED_ShowNum(88,4,_FREQ[5],1,16);
	OLED_ShowString(104,4,_UNIT[_FREQ[6]],16);
	
  OLED_ShowString(0,6,"OUTPUT!",16);//SETTING/OUTPUT!
	
	
	
  OLED_ShowCHinese(80,6,14);//C
	OLED_ShowCHinese(96,6,15);//0
	OLED_ShowCHinese(112,6,16);//6

}

void Para_Setting_page(){
  OLED_Clear();
	OLED_ShowString(0,0,"WAVE:",16);
	OLED_ShowString(64,0,_WAVE[Wave],16);

	OLED_ShowString(0,2,"AMP:",16);
	OLED_ShowNum(32,2,AmpH,1,16);
	OLED_ShowString(40,2,".",16);
	OLED_ShowNum(48,2,AmpL,1,16);
	OLED_ShowString(56,2,"V",16);
	
	OLED_ShowString(72,2,"Ph:",16);
	OLED_ShowNum(96,2,Ph,3,16);
	OLED_ShowString(120,2,"d",16);
	
	
  OLED_ShowString(0,4,"FREQ:",16);
	if(_FREQ[0])
	OLED_ShowNum(48,4,_FREQ[0],1,16);
	else 
	OLED_ShowString(48,4," ",16);
	
	if(_FREQ[1]||_FREQ[0])
	OLED_ShowNum(56,4,_FREQ[1],1,16);
	else 
	OLED_ShowString(56,4," ",16);
	
	if(_FREQ[1]||_FREQ[0]||_FREQ[2])
	OLED_ShowNum(64,4,_FREQ[2],1,16);
	else 
	OLED_ShowString(64,4," ",16);
	
	OLED_ShowNum(72,4,_FREQ[3],1,16);
	
	OLED_ShowString(80,4,".",16);
	OLED_ShowNum(88,4,_FREQ[5],1,16);
	OLED_ShowString(104,4,_UNIT[_FREQ[6]],16);
	
	
  OLED_ShowString(0,6,"SETTING",16);//SETTING/OUTPUT!
	
	
  OLED_ShowCHinese(80,6,14);//C
	OLED_ShowCHinese(96,6,15);//0
	OLED_ShowCHinese(112,6,16);//6
}
 
void Flash_read(){
    Wave=IapRead(wave_addr);
	  Wave%=3;
	  _FREQ[6]=IapRead(unit_addr);
	  _FREQ[6]%=3;
	  AmpH=IapRead(AmpH_addr);
	  AmpH%=6;
	  AmpL=IapRead(AmpL_addr);
	  AmpL%=10;
	  _FREQ[0]=IapRead(FR_Q_addr);
	  _FREQ[0]%=10;
	
	  _FREQ[1]=IapRead(FR_B_addr);
	  _FREQ[1]%=10;
	
	  _FREQ[2]=IapRead(FR_S_addr);
	  _FREQ[2]%=10;
	
	  _FREQ[3]=IapRead(FR_G_addr);
	  _FREQ[3]%=10;
	
	  _FREQ[4]=IapRead(FR_X_addr);
	  _FREQ[4]%=10;
		
	  Ph=IapRead(Ph_addr);
	  Ph%=180;
} 

void Flash_save(){
	   IapErase(0x0400);
     IapProgram(wave_addr,Wave);
	   IapProgram(unit_addr,_FREQ[6]);
	   IapProgram(AmpH_addr,AmpH);
	   IapProgram(AmpL_addr,AmpL);
	   IapProgram(Ph_addr,Ph);
	   IapProgram(FR_Q_addr,_FREQ[0]);
	   IapProgram(FR_B_addr,_FREQ[1]);
	   IapProgram(FR_S_addr,_FREQ[2]);
	   IapProgram(FR_G_addr,_FREQ[3]);
	   IapProgram(FR_X_addr,_FREQ[4]);
}

