#include "key.h"
#include "delay.h"

unsigned char Key_Mode(){
unsigned char i=0;
  if(MODE==0)
{ 
  delay_ms(10);
  while(MODE==0)
 { 
    i=1;
  }
}
return i;
}
unsigned char Key_Select(){
unsigned char i=0;
		if(SELECT==0)
	{ 
	delay_ms(10);
		while(SELECT==0)
	 { 
			 i=1;
		}
	}
return i;

}
unsigned char Key_Add(){
unsigned char i=0;
		if(ADD==0)
	{ 
		delay_ms(10);
		while(ADD==0)
	 { 
			 i=1;
		}
	}
return i;
}
unsigned char Key_Sub(){
unsigned char i=0;
		if(SUB==0)
	{ 
		delay_ms(10);
		while(SUB==0)
	 { 
			i=1;
		}
	}
return i;
}
//unsigned char Key_OUTPUT(){
//unsigned char i=0;
//		if(OUTPUT==0)
//	{ 
//		delay_ms(10);
//		while(OUTPUT==0)
//	 { 
//			i=1;
//		}
//	}
//return i;

//}
