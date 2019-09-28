/*
  ******************************************************************************
  * @file    apt32f101_tkey_Parameter.c
  * @author  APT AE Team
  * @version V1.10
  * @date    2016/07/19
  ******************************************************************************
  *THIS SOFTWARE WHICH IS FOR ILLUSTRATIVE PURPOSES ONLY WHICH PROVIDES 
  *CUSTOMER WITH CODING INFORMATION REGARDING THEIR PRODUCTS.
  *APT CHIP SHALL NOT BE HELD RESPONSIBILITY ADN LIABILITY FOR ANY DIRECT, 
  *INDIRECT DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF 
  *SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION 
  *CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.AND APT CHIP RESERVES 
  *THE RIGHT TO MAKE CHANGES IN THE SOFTWARE WITHOUT NOTIFICATION
  ******************************************************************************
  */

#include "apt32f101_tkey.h"

/* externs--------- ----------------------------------------------------------*/
extern volatile U16_T 	R_I2C_TK_Trigglevel0,R_I2C_TK_Trigglevel1,R_I2C_TK_Trigglevel2,R_I2C_TK_Trigglevel3,R_I2C_TK_Trigglevel4,R_I2C_TK_Trigglevel5,R_I2C_TK_Trigglevel6,R_I2C_TK_Trigglevel7,R_I2C_TK_Trigglevel8,
						R_I2C_TK_Trigglevel9,R_I2C_TK_Trigglevel10,R_I2C_TK_Trigglevel11,R_I2C_TK_Trigglevel12,R_I2C_TK_Trigglevel13,R_I2C_TK_Trigglevel14,R_I2C_TK_Trigglevel15,R_I2C_TK_Debounce,R_I2C_TK_Longpress_T,
						R_I2C_TK_GSR,R_I2C_TK_MCONL,R_I2C_TK_Channel_EN,R_I2C_TK_MCONH,R_I2C_userID,R_I2C_FWID;
				
void WheelSlider_Parameter_Init(void)
{
/*************************************************************/
//Wheel/Slider Parameters(can modify from I2C)
/*************************************************************/  
	R_I2C_TK_Debounce		=	0x01;						//Key debounce
	R_I2C_TK_Longpress_T	=	0x03;						//long press time (x+1)*16
	R_I2C_TK_GSR			=	TK_GSR;						//setting in apt32f101_tkey_Parameter.h
	R_I2C_TK_MCONL			=	0xF4;						//Touch control register low byte
	R_I2C_TK_MCONH			=	0X10;						//Touch control register high byte
	R_I2C_TK_Channel_EN		=	TK_IO_ENABLE;				//IO enable/disable
	R_I2C_userID			=	0x55;						//user ID
	R_I2C_FWID				=	0x22;						//firmware
/*************************************************************/
//defines
/*************************************************************/ 
	R_I2C_TK_Trigglevel0	=	TK_Trigglevel_data[0];
	R_I2C_TK_Trigglevel1	=	TK_Trigglevel_data[1];
	R_I2C_TK_Trigglevel2	=	TK_Trigglevel_data[2];
	R_I2C_TK_Trigglevel3	=	TK_Trigglevel_data[3];
	R_I2C_TK_Trigglevel4	=	TK_Trigglevel_data[4];
	R_I2C_TK_Trigglevel5	=	TK_Trigglevel_data[5];
	R_I2C_TK_Trigglevel6	=	TK_Trigglevel_data[6];
	R_I2C_TK_Trigglevel7	=	TK_Trigglevel_data[7];
	R_I2C_TK_Trigglevel8	=	TK_Trigglevel_data[8];
	R_I2C_TK_Trigglevel9	=	TK_Trigglevel_data[9];
	R_I2C_TK_Trigglevel10	=	TK_Trigglevel_data[10];
	R_I2C_TK_Trigglevel11	=	TK_Trigglevel_data[11];
	R_I2C_TK_Trigglevel12	=	TK_Trigglevel_data[12];
	R_I2C_TK_Trigglevel13	=	TK_Trigglevel_data[13];
	R_I2C_TK_Trigglevel14	=	TK_Trigglevel_data[14];
	R_I2C_TK_Trigglevel15	=	TK_Trigglevel_data[15];
}


