#ifndef __FLASH_H__
#define __FLASH_H__

#define wave_addr  0x0400
#define unit_addr  0x0401
#define AmpH_addr  0x0402
#define AmpL_addr  0x0403
#define Ph_addr    0x0404
#define FR_Q_addr  0x0405
#define FR_B_addr  0x0406
#define FR_S_addr  0x0407
#define FR_G_addr  0x0408
#define FR_X_addr  0x0409

char IapRead(int addr);
void IapProgram(int addr, char dat);
void IapErase(int addr);
void IapIdle();


#endif
