#ifndef OLED_OLED_H_
#define OLED_OLED_H_

#include "main.h"
extern I2C_HandleTypeDef  hi2c2;

void OLED_WR_CMD(uint8_t cmd);
void OLED_WR_DATA(uint8_t data);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_On(void);
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2,uint8_t Color_Turn);
void OLED_Showdecimal(uint8_t x,uint8_t y,float num,uint8_t z_len,uint8_t f_len,uint8_t size2, uint8_t Color_Turn);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t Color_Turn);
void OLED_ShowString(uint8_t x,uint8_t y,char*chr,uint8_t Char_Size,uint8_t Color_Turn);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no,uint8_t Color_Turn);
void OLED_DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t *  BMP,uint8_t Color_Turn);
void OLED_HorizontalShift(uint8_t direction);
void OLED_Some_HorizontalShift(uint8_t direction,uint8_t start,uint8_t end);
void OLED_VerticalAndHorizontalShift(uint8_t direction);
void OLED_DisplayMode(uint8_t mode);
void OLED_IntensityControl(uint8_t intensity);


/*示例代码
 OLED_Init();                           //OLED初始
 OLED_Clear();                         //清屏
//上面的初始化以及清屏的代码在一开始处一定要写
 OLED_ShowString(0,0,"UNICORN_LI",16, 1);    //反相显示8X16字符串
 OLED_ShowString(0,2,"unicorn_li_123",12,0);//正相显示6X8字符串

 OLED_ShowCHinese(0,4,0,1); //反相显示汉字“独”
 OLED_ShowCHinese(16,4,1,1);//反相显示汉字“角”
 OLED_ShowCHinese(32,4,2,1);//反相显示汉字“兽”
 OLED_ShowCHinese(0,6,0,0); //正相显示汉字“独”
 OLED_ShowCHinese(16,6,1,0);//正相显示汉字“角”
 OLED_ShowCHinese(32,6,2,0);//正相显示汉字“兽”

 OLED_ShowNum(48,4,6,1,16, 0);//正相显示1位8X16数字“6”
 OLED_ShowNum(48,7,77,2,12, 1);//反相显示2位6X8数字“77”
 OLED_DrawBMP(90,0,122, 4,BMP1,0);//正相显示图片BMP1
 OLED_DrawBMP(90,4,122, 8,BMP1,1);//反相显示图片BMP1

 OLED_HorizontalShift(0x26);//全屏水平向右滚动播放

//显示正负浮点数的代码
//  float num1=-231.24;
//  float num2=23.375;

//OLED_ShowString(0,0,"Show Decimal",12,0);
//OLED_Showdecimal(0,4,num1,3,2,12, 0);
//OLED_Showdecimal(0,6,num2,2,3,16, 1);

*/


#endif /* OLED_OLED_H_ */

