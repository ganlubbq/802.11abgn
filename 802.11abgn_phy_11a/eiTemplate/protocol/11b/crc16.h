typedef unsigned __int16    INT16U;
#define CRC_SEED   0xFFFF   // 该位称为预置值，使用人工算法（长除法）时 需要将除数多项式先与该与职位 异或 ，才能得到最后的除数多项式
#define POLY16 0x1021  // 该位为简式书写 实际为0x11021
INT16U crc16(unsigned char *buf,int length)
{
  INT16U shift,data,val;
  int i;
  shift = CRC_SEED;
  for(i=0;i<length;i++) {
    if((i % 8) == 0)
      data = (*buf++)<<8;
    val = shift ^ data;
    shift = shift<<1;
    data = data <<1;
    if(val&0x8000)
      shift = shift ^ POLY16;
  }
  return ~shift;
} 