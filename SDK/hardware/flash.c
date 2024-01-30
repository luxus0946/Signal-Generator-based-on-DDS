#include "flash.h"
#include "stc8h.h"
#include "intrins.h"
void IapIdle()
{
IAP_CONTR = 0; //�ر� IAP ����
IAP_CMD = 0; //�������Ĵ���
IAP_TRIG = 0; //��������Ĵ���
IAP_ADDRH = 0x80; //����ַ���õ��� IAP ����
IAP_ADDRL = 0;
}
char IapRead(int addr)
{
char dat;
IAP_CONTR = 0x80; //ʹ�� IAP
IAP_TPS = 33; //���õȴ����� 40MHz
IAP_CMD = 1; //���� IAP ������
IAP_ADDRL = addr; //���� IAP �͵�ַ
IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
IAP_TRIG = 0x5a; //д��������(0x5a)
IAP_TRIG = 0xa5; //д��������(0xa5)
_nop_();
dat = IAP_DATA; //�� IAP ����
IapIdle(); //�ر� IAP ����
return dat;
}
void IapProgram(int addr, char dat)
{
IAP_CONTR = 0x80; //ʹ�� IAP
IAP_TPS = 33; //���õȴ����� 12MHz
IAP_CMD = 2; //���� IAP д����
IAP_ADDRL = addr; //���� IAP �͵�ַ
IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
IAP_DATA = dat; //д IAP ����
IAP_TRIG = 0x5a; //д��������(0x5a)
IAP_TRIG = 0xa5; //д��������(0xa5)
_nop_();
IapIdle(); //�ر� IAP ����
}
void IapErase(int addr)
{
IAP_CONTR = 0x80; //ʹ�� IAP
IAP_TPS = 33; //���õȴ����� 12MHz
IAP_CMD = 3; //���� IAP ��������
IAP_ADDRL = addr; //���� IAP �͵�ַ
IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
IAP_TRIG = 0x5a; //д��������(0x5a)
IAP_TRIG = 0xa5; //д��������(0xa5)
_nop_(); //
IapIdle(); //�ر� IAP ����
}

//void Flash_init(){
//	   IapErase(0x0000);
//     IapProgram(wave_addr,1);
//	   IapProgram(unit_addr,1);
//	   IapProgram(AmpH_addr,5);
//	   IapProgram(AmpL_addr,0);
//	   IapProgram(Ph_addr,0);
//	   IapProgram(FR_Q_addr,0);
//	   IapProgram(FR_B_addr,1);
//	   IapProgram(FR_S_addr,0);
//	   IapProgram(FR_G_addr,0);
//	   IapProgram(FR_X_addr,1);
//}
