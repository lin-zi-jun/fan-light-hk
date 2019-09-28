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

void TKey_Parameter_Init(void)
{
    TK_mode                 =   TK_EX_Mode;                     //TK_EX_Mode/TK_EX_LED_Mode
    TK_High_Anti            =   TK_High_Anti_EN;                //TK_High_Anti_EN/TK_High_Anti_DIS(more electrical current in this mode(more 30uA in deepsleep)é?
/*************************************************************/
//Touch Key basic Parameters
/*************************************************************/  
    TK_IO_ENABLE            =   0B001111001100110;              //IO Enable,bit15é«æit0=TCH15~TCH0
    TK_GSR                  =   0x02;                           //Touch key sensetivity
//    TK_Trigglevel_data[0]   =   0Xff;                           //CH0 Triggerlevel
//    TK_Trigglevel_data[1]   =   35;//0X35;   //CH1 Triggerlevel
//    TK_Trigglevel_data[2]   =   35;   //CH2 Triggerlevel
//    TK_Trigglevel_data[3]   =   0Xff;                           //CH3 Triggerlevel
//    TK_Trigglevel_data[4]   =   0Xff;                           //CH4 Triggerlevel
//    TK_Trigglevel_data[5]   =   74;   //CH5 Triggerlevel
//    TK_Trigglevel_data[6]   =   80;   //CH6 Triggerlevel
//    TK_Trigglevel_data[7]   =   0Xff;   //CH7 Triggerlevel
//    TK_Trigglevel_data[8]   =   0XFF;   //CH8 Triggerlevel
//    TK_Trigglevel_data[9]   =   25;   //CH9 Triggerlevel
//    TK_Trigglevel_data[10]  =   30;   //CH10 Triggerlevel
//    TK_Trigglevel_data[11]  =   33;   //CH11 Triggerlevel
//    TK_Trigglevel_data[12]  =   40;   //CH12 Triggerlevel
//    TK_Trigglevel_data[13]  =   0Xff;                           //CH13 Triggerlevel
//    TK_Trigglevel_data[14]  =   0Xff;                           //CH14 Triggerlevel
//    TK_Trigglevel_data[15]  =   0Xff;                           //CH15 Triggerlevel

    TK_Trigglevel_data[0]   =   0Xff;                           //CH0 Triggerlevel
    TK_Trigglevel_data[1]   =   26;//0X35;   //CH1 Triggerlevel
    TK_Trigglevel_data[2]   =   26;   //CH2 Triggerlevel
    TK_Trigglevel_data[3]   =   0Xff;                           //CH3 Triggerlevel
    TK_Trigglevel_data[4]   =   0Xff;                           //CH4 Triggerlevel
    TK_Trigglevel_data[5]   =   74;   //CH5 Triggerlevel
    TK_Trigglevel_data[6]   =   80;   //CH6 Triggerlevel
    TK_Trigglevel_data[7]   =   0Xff;   //CH7 Triggerlevel
    TK_Trigglevel_data[8]   =   0XFF;   //CH8 Triggerlevel
    TK_Trigglevel_data[9]   =   25;   //CH9 Triggerlevel
    TK_Trigglevel_data[10]  =   30;   //CH10 Triggerlevel
    TK_Trigglevel_data[11]  =   33;   //CH11 Triggerlevel
    TK_Trigglevel_data[12]  =   40;   //CH12 Triggerlevel
    TK_Trigglevel_data[13]  =   0Xff;                           //CH13 Triggerlevel
    TK_Trigglevel_data[14]  =   0Xff;                           //CH14 Triggerlevel
    TK_Trigglevel_data[15]  =   0Xff;                           //CH15 Triggerlevel


    Longpress_ctrl          =   TK_longpress_Enable;            //TK_longpress_Enable/TK_longpress_Disable
    Longpress_time          =   _64s;                           //longpress_time = _16s/_32s/_48s/_64s
    Key_mode                =   Multikey;                       //TK mode FirstKey/Multikey
    Key_Debounce            =   KEYDETDEB0;                     //KEYDETDEB0~3
/*************************************************************/
//Touch Key Special Control Parameters
/*************************************************************/ 
    TKPDIV                  =   TKPDIV0;                        //TK Scan clock divider TKPDIV0~5
    TKHYST                  =   TKHYST0;                        //TK release detection point TKHYST0~1
//HW0 works only at the condition that sampled data is not less than baseline value
    HW0_BLUPD_THR           =   BLUPD_THR0;                     //Baseline value update threshold BLUPD_THR0~3
    HW0_BLUPD_WCO0          =   BLUPD_WCO0_1;                   //Baseline update weight coefficient when sampling<BLUPD_THR BLUPD_WCO0_0~3
    HW0_BLUPD_WCO1          =   BLUPD_WCO1_1;                   //Baseline update weight coefficient when sampling>BLUPD_THR BLUPD_WCO0_0~3
    HW0_BLUPD_DEB0          =   0X2;                           //Baseline update debounce when sampling<BLUPD_THR 0x00~0xf
    HW0_BLUPD_DEB1          =   0X8;                           //Baseline update debounce when sampling>BLUPD_THR 0x00~0xff
    HW0_ABNFLT              =   ABNFLT0;                        //Abnormal data filter ABNFLT0~3
    HW0_BLUPD_THVAL         =   0x0A;                           //Automatic baseline update threshold 0x00~0xff
//HW1 works only at the condition that sampled data is less than baseline value
    HW1_BLUPD_THR           =   BLUPD_THR0;                     //Baseline value update threshold BLUPD_THR0~3
    HW1_BLUPD_WCO0          =   BLUPD_WCO0_1;                   //Baseline update weight coefficient when sampling<BLUPD_THR BLUPD_WCO0_0~3
    HW1_BLUPD_WCO1          =   BLUPD_WCO1_3;                   //Baseline update weight coefficient when sampling>BLUPD_THR BLUPD_WCO0_0~3
    HW1_BLUPD_DEB0          =   0X2;                           //Baseline update debounce when sampling<BLUPD_THR 0x00~0xf
    HW1_BLUPD_DEB1          =   0X8;                           //Baseline update debounce when sampling>BLUPD_THR 0x00~0xff
    HW1_ABNFLT              =   ABNFLT0;                        //Abnormal data filter in EX Mode ABNFLT0~3
    HW1_BLUPD_THVAL         =   0x0A;                           //Automatic baseline update threshold 0x00~0xff
//-------------------------------------------------------
   OFFSET_MUL				=	OFFSET0;						//OFFSET auto-multiply OFFSET0~3
	TOSCFREQ				=	TKFREQ0;						//TKFREQ0/2/25 (RC mode default=TKFREQ25)
	CMPFLT					=	CMPFLT0;						//digital filter configuration CMPFLT0~3
	BLUPDICNT				=	BLUPDICNT0;						//Detecting period of automatic baseline update  BLUPDICNT0~3
	TOSCFDIV				=	TOSCFDIV0;						//channel sensing oscillator pre-divider in RC mode TOSCFDIV0~15
	ICNTSWEN_ctrl			=	ICNTSWDIS;						//Interval scan period auto-switch configuration ICNTSWDIS/ICNTSWEN
	BLUPDIS_ctrl			=	BASE_EN;						//Baseline automatic update disable BASE_EN/BASE_DIS
	BLUPDIS_CYCLE_VAL		=	0x00;							//Disable baseline value updating cycles after release
}

