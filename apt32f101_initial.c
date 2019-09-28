/*
  ******************************************************************************
  * @file    apt32f101_initial.c
  * @author  APT AE Team
  * @version V1.0
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
  
/* Includes ------------------------------------------------------------------*/
#include "apt32f101.h"
#include "apt32f101_syscon.h"
//#include "apt32f101_coret.h"
#include "apt32f101_gpio.h"
#include "apt32f101_uart.h"
#include "apt32f101_gtc.h"
//#include "apt32f101_adc.h"
//#include "apt32f101_led.h"
#include "apt32f101_i2c.h"
#include "apt32f101_counta.h"
//#include "apt32f101_ifc.h"
#include "apt32f101_tkey.h"

/* define --------------------------------------------------------------------*/
#define debug_Mode
//#define EXReset_Mode
/* externs--------------------------------------------------------------------*/

/*************************************************************/
//software delay
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void delay_nms(unsigned int t)
{
    volatile unsigned int i,j ,k=0;
    j = 50* t;
    for ( i = 0; i < j; i++ )
    {
        k++;
    }
}
/*************************************************************/
//GPIO Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void GPIO_CONFIG(void)
{
	GPIO_Init(GPIOA0,0,0);
	GPIO_Write_High(GPIOA0,0);
	
	EXI4_Int_Enable();
	EXI4_WakeUp_Enable();										//ENABLE CPU INT Vector
	
	GPIO_IntGroup_Set(PA0);
	GPIO_EXTI_interrupt(GPIOA0,EXI_PIN12);						//GPIO PIN  EXI 中断
	EXTI_trigger_CMD(ENABLE,EXI_PIN12,_EXIFT);                   //ENABLE SYSCON falling edge
	EXTI_interrupt_CMD(ENABLE,EXI_PIN12);                		//ENbale SYSCON EXI
	
	
}

/*************************************************************/
//LED Init
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/  
/*void LED_CONFIG(void)  
{
	GPIOA0->PUDR = 0x00550000;												//PA0.8,P0.9,PA0.10,PA0.11  PULL_UP 
	LED_RESET_VALUE();                                                      //clear all led Register
	//LED_INT_CMD(IPEND,ENABLE);
	LED_Control_Config(LEDCLK_DIV32,LED_ComMode_4COM,DISKEY_SCEN,ENTkeyShare,0,LED_Bright_100,80,3,0);     //evey com time selected 3ms 
	LED_SEGDATX_data_write(SEGDAT_NUM0 , _CHAR_[0]);                        //show 0
	LED_SEGDATX_data_write(SEGDAT_NUM1 , _CHAR_[0]);                        //show 0
	LED_SEGDATX_data_write(SEGDAT_NUM2 , _CHAR_[0]);                        //show 0
	LED_SEGDATX_data_write(SEGDAT_NUM3 , _CHAR_[0]);                        //show 0
	LED_SCAN_ENABLE(ENABLE);                                                //LED Scan enable
	LED_Int_Enable();														//LED INT enable		
}*/

/*************************************************************/
//GCOUNTA Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void COUNTA_CONFIG(void)
{
    COUNT_DeInit();                                                                       //clear all countA Register
    //COUNTA_IO_Init(0);                                                                    //set PA0.07 as counter IO
    COUNTA_Init(1000,0,Period_H,DIV2,REPEAT_MODE,CARRIER_ON,OSP_LOW);                    //Data_H=Time/(1/sysclock)   100us
    COUNTA_Config(SW_STROBE,PENDREM_OFF,MATCHREM_OFF,REMSTAT_0,ENVELOPE_0);               //countA mode set  
    COUNTA_Start();                                                                       //countA start
    //COUNTA_Stop();                                                                      //countA stop  
    COUNTA_Int_Enable();                                                                //countA INT enable
}

/*************************************************************/
//ADC12_Init
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
/*void ADC12_CONFIG(void)
{
    ADC12_RESET_VALUE();
    ADC12_CLK_CMD(ADC_CLK_CR , ENABLE);                                                 //ENABLE ADC CLK
    ADC12_Software_Reset();                                                             //software reset
    ADC12_Configure_Mode(ADC12_12BIT , ADC12_8CYCLES , Continuous_mode , 2 , 1);        //select 12BIT ADC ,SAMPLEING CYCLE=3 , one shot mode, ADC_CLK=PCLK/2*1 , NumConver=2
    ADC12_ConversionChannel_Config(ADC12_ADCIN12,1);                                     //set ADC2 ,1st scan channel
    //ADC12_ConversionChannel_Config(ADC12_ADCIN3,2);                                     //set ADC3 ,end scan channel
    ADC12_CMD(ENABLE);                                                                  //ENABLE ADC
    ADC12_ready_wait();                                                                 // Waiting for ADC Ready
    //adc date output=last number of Conversions
    //ADC12_Control(ADC12_START);                                                       // Start conversion
    //ADC12_EOC_wait();                                                                   //End of conversion wait
    //adc_dr=ADC12_DATA_OUPUT();                                                          //ADC =ADC1 data
    //ADC12_Control(ADC12_STOP);	
    //ADC_Int_Enable();                                                                 //INT Vector
}*/

/*************************************************************/
//UART Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void UART_CONFIG(void)
{
	UART_DeInit();                                                              //clear all UART Register
//	UART_IO_Init(IO_UART0 ,0);                                                  //use UART0 group 1
//	UARTInitRxTxIntEn(UART0,174);	                                            //baudrate=sysclock/173=38400
//	UART0_Int_Enable();														    //uart0 INT Enable
//	UART0_WakeUp_Enable();                                                      //uart0 wakeup Enable
	 
	UART_IO_Init(IO_UART1 ,1);
	UARTInitRxTxIntEn(UART1,174);
	UART1_Int_Enable();	
//	UART1_WakeUp_Enable();
}

/*************************************************************/
//gtc0 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void GTC0_CONFIG(void)
{
    GTC_RESET_VALUE(GTC0);                                                        //GTC0 all register reset value
    //GTC0_IO_Init(GTC_IO_TXOUT , 0 );                                              //set tcout
    GTC_Configure(GTC0 , GTC_FIN_PCK , 1 , 11 , Counter_Size_32BIT  , 100 , 1);   //TCCLK=sysclock/2^1/12，24m-->1us
    GTC_ControlSet_Configure(GTC0,GTC_ControlSet_REPEAT,ENABLE);                  //loop mode
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_PWMEN,ENABLE);                 //pwm Enable
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_IDLEST,ENABLE);                //Idle status high enable
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_OUTST,ENABLE);                 //output status
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_HWTRIG,ENABLE);                //hardware auto-trigger enable
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_CAPT_F,ENABLE);                //capture down enable
    //GTC_ControlSet_Configure(GTC0,GTC_ControlSet_CAPT_TCAP0,ENABLE);            //capture up enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_STARTI, ENABLE);                          //counter start int Enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_STOPI, ENABLE);                           //counter stop int Enable
    GTC_ConfigInterrupt_CMD(GTC0 , GTC_PSTARTI, ENABLE);                           //counter period start int Enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_PENDI, ENABLE);                           //counter period stop int Enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_MATI, ENABLE);                            //counter pulse matched int Enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_OVFI, ENABLE);                            //counter overflow int Enable
    //GTC_ConfigInterrupt_CMD(GTC0 , GTC_CAPTI, ENABLE);                           //counter capture int Enable
    GTC_Start(GTC0);                                                               //start counter
    GTC0_Int_Enable();                                                             //enable GTC0 int
}
/*************************************************************/
//gtc1 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void GTC1_CONFIG(void)
{
    GTC_RESET_VALUE(GTC1);                                                        //GTC1 all register reset value
    //GTC1_IO_Init(GTC_IO_TXOUT , 0 );                                            //set tcout
    GTC_Configure(GTC1 , GTC_FIN_PCK , 1 , 11 , Counter_Size_32BIT  , 100 , 1);   //TCCLK=sysclock/2^1/12，24m-->1us
    GTC_ControlSet_Configure(GTC1,GTC_ControlSet_REPEAT,ENABLE);                  //loop mode
    GTC_ControlSet_Configure(GTC1,GTC_ControlSet_PWMEN,ENABLE);                   //pwm Enable
    GTC_ControlSet_Configure(GTC1,GTC_ControlSet_IDLEST,ENABLE);                //Idle status high enable
    GTC_ControlSet_Configure(GTC1,GTC_ControlSet_OUTST,ENABLE);                 //output status
    //GTC_ControlSet_Configure(GTC1,GTC_ControlSet_HWTRIG,ENABLE);                //hardware auto-trigger enable
    //GTC_ControlSet_Configure(GTC1,GTC_ControlSet_CAPT_F,ENABLE);                //capture down enable
    //GTC_ControlSet_Configure(GTC1,GTC_ControlSet_CAPT_TCAP0,ENABLE);            //capture up enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_STARTI, ENABLE);                          //counter start int Enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_STOPI, ENABLE);                           //counter stop int Enable
    GTC_ConfigInterrupt_CMD(GTC1 , GTC_PSTARTI, ENABLE);                           //counter period start int Enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_PENDI, ENABLE);                           //counter period stop int Enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_MATI, ENABLE);                            //counter pulse matched int Enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_OVFI, ENABLE);                            //counter overflow int Enable
    //GTC_ConfigInterrupt_CMD(GTC1 , GTC_CAPTI, ENABLE);                           //counter capture int Enable
    GTC_Start(GTC1);                                                               //start counter
    GTC0_Int_Enable();                                                             //enable GTC1 int
}
/*************************************************************/
//gtc2 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void GTC2_CONFIG(void)
{
    GTC_RESET_VALUE(GTC2);                                                        //GTC2 all register reset value
    //GTC2_IO_Init(GTC_IO_TXOUT , 0 );                                              //set tcout
    GTC_Configure(GTC2 , GTC_FIN_PCK , 1 , 11 , Counter_Size_32BIT  , 1000 , 300);   //TCCLK=sysclock/2^1/12，24m-->1us
    GTC_ControlSet_Configure(GTC2,GTC_ControlSet_REPEAT,ENABLE);                  //loop mode
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_PWMEN,ENABLE);                 //pwm Enable
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_IDLEST,ENABLE);                //Idle status high enable
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_OUTST,ENABLE);                 //output status
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_HWTRIG,ENABLE);                //hardware auto-trigger enable
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_CAPT_F,ENABLE);                //capture down enable
    //GTC_ControlSet_Configure(GTC2,GTC_ControlSet_CAPT_TCAP0,ENABLE);            //capture up enable
    //GTC_ConfigInterrupt_CMD(GTC2 , GTC_STARTI, ENABLE);                          //counter start int Enable
    //GTC_ConfigInterrupt_CMD(GTC2 , GTC_STOPI, ENABLE);                           //counter stop int Enable
    GTC_ConfigInterrupt_CMD(GTC2 , GTC_PSTARTI, ENABLE);                           //counter period start int Enable
    //GTC_ConfigInterrupt_CMD(GTC2, GTC_PENDI, ENABLE);                           //counter period stop int Enable
    //GTC_ConfigInterrupt_CMD(GTC2 , GTC_MATI, ENABLE);                            //counter pulse matched int Enable
    //GTC_ConfigInterrupt_CMD(GTC2 , GTC_OVFI, ENABLE);                            //counter overflow int Enable
    //GTC_ConfigInterrupt_CMD(GTC2 , GTC_CAPTI, ENABLE);                           //counter capture int Enable
    GTC_Start(GTC2);                                                               //start counter
    GTC0_Int_Enable();                                                             //enable GTC2 int
}
/*************************************************************/
//gtc3 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void GTC3_CONFIG(void)
{
    GTC_RESET_VALUE(GTC3);                                                        //GTC3 all register reset value
    //GTC3_IO_Init(GTC_IO_TXOUT , 0 );                                              //set tcout
    GTC_Configure(GTC3 , GTC_FIN_PCK , 1 , 11 , Counter_Size_32BIT  , 1000 , 500);   //TCCLK=sysclock/2^1/12，24m-->1us
    GTC_ControlSet_Configure(GTC3,GTC_ControlSet_REPEAT,ENABLE);                  //loop mode
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_PWMEN,ENABLE);                 //pwm Enable
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_IDLEST,ENABLE);                //Idle status high enable
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_OUTST,ENABLE);                 //output status
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_HWTRIG,ENABLE);                //hardware auto-trigger enable
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_CAPT_F,ENABLE);                //capture down enable
    //GTC_ControlSet_Configure(GTC3,GTC_ControlSet_CAPT_TCAP0,ENABLE);            //capture up enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_STARTI, ENABLE);                          //counter start int Enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_STOPI, ENABLE);                           //counter stop int Enable
    GTC_ConfigInterrupt_CMD(GTC3 , GTC_PSTARTI, ENABLE);                           //counter period start int Enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_PENDI, ENABLE);                           //counter period stop int Enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_MATI, ENABLE);                            //counter pulse matched int Enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_OVFI, ENABLE);                            //counter overflow int Enable
    //GTC_ConfigInterrupt_CMD(GTC3 , GTC_CAPTI, ENABLE);                           //counter capture int Enable
    GTC_Start(GTC3);                                                               //start counter
    GTC0_Int_Enable();                                                             //enable GTC3 int
}
/*************************************************************/
//I2C MASTER Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
/*void I2C_MASTER_CONFIG(void)
{
    I2C_DeInit();                                           //clear all I2C Register
    I2C_Master_Init(I2C_G1,FAST_MODE,0x040,0x20);           //use I2C group 1，fast mode，speed=sysclock/0x040,0x20=setup time
    I2C_Int_Enable();                                       //use interrupt mode 
}*/
/*************************************************************/
//I2C SLAVE Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
/*void I2C_SLAVE_CONFIG(void)
{
    I2C_DeInit();                                           //clear all I2C Register
    I2C_Slave_Init(I2C_G0,FAST_MODE,0x4A,0x20,0xAE);        //slave address=0xac(8bit)，standard mode，speed=sysclock/0x138,0x78=setup time
    I2C_Int_Enable();                                       //use interrupt mode 
}*/
/*************************************************************/
//CORET Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
/*void CORET_CONFIG(void)
{
	CORET_DeInit();
	SYSCON_General_CMD(ENABLE,ENDIS_SYSTICK);
	CK802->CORET_RVR=0x2a2fcd;								//CORETCLK=sysclock/8=22.118M/8=0.362us  e.g:1s=(CORET_RVR+1)*(8/22.118M);CORET_RVR=0x2a2fce-1=0x2a2fcd
	CORET_reload();																
	CORET_CLKSOURCE_EX();									//use ex clock
	CORET_TICKINT_Enable();									//clear CORET counter
	//CORET_stop();	
	CORET_start();	
	CORET_Int_Enable();
	CORET_WakeUp_Enable();									
}*/
/*************************************************************/
//TK Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void TK_CONFIG(void)
{
	TKey_Parameter_Init();
    TK_Init();                                                 //TK initial
}
/*************************************************************/
//syscon Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_CONFIG(void)
{
//------SYSTEM CLK AND PCLK FUNTION---------------------------/
    SYSCON_RST_VALUE();                                                         //reset value
    SYSCON_General_CMD(ENABLE,ENDIS_ISOSC);                                     //enable ISOSC，ISOSC=internal sub crystal
    SYSCON_General_CMD(ENABLE,ENDIS_IMOSC);	                                    //enable IMOSC or EMOSC，IMOSC=internal crystal，ENDIS_EMOSC=external crystal
    //SYSCON_General_CMD(ENABLE,ENDIS_EMOSC);
	SystemCLK_HCLKDIV_PCLKDIV_Config(SYSCLK_IMOSC,HCLK_DIV_1,PCLK_DIV_1);       //system clock set, Hclk div ,Pclk div  set system clock=SystemCLK/Hclk div/Pclk div
//------------  WDT FUNTION  --------------------------------/
    SYSCON_IWDCNT_Config(DISABLE_IWDT_SHORT,IWDT_TIME_1S,IWDT_INTW_DIV_7);      //WDT TEIM:2S*7/8=1.75S
	//SYSCON_WDT_CMD(DISABLE);                                                   	//disable WDT	
	//SYSCON_WDT_CMD(ENABLE);                                                   	//enable WDT		
    //SYSCON_IWDCNT_Reload();                                                   //reload WDT
	//IWDT_Int_Enable();														//Enable WDT INT
	//SYSCON_WakeUp_Enable();													//Enable WDT wakeup INT
//------------  LVD FUNTION  --------------------------------/ 
    //SYSCON_LVD_Config(DISABLE_LVDEN,INTDET_LVL_3_0V,RSTDET_LVL_2_7V,DISABLE_LVD_INT);
    //LVD_Int_Enable();
} 
/*********************************************************************************/  
/*********************************************************************************/
//APT32F101_init                                                                  /
//EntryParameter:NONE                                                             /
//ReturnValue:NONE                                                                /
/*********************************************************************************/
/*********************************************************************************/  
/*********************************************************************************/
void APT32F101_init(void) 
{
//------------------------------------------------------------/
//IO mode clr all register 
//------------------------------------------------------------/
    //GPIO_DeInit();                                                //GPIO register clear,ALL IO set as output
//------------------------------------------------------------/
//IO debug mode for IC
//------------------------------------------------------------/
#if defined (debug_Mode) 
    GPIO_Debug_IO_12_13();                                          //PA0.12,PA0.13 as debug IO
    //GPIO_Debug_IO_01_02();                                        //PA0.1,PA0.2 as debug IO
#endif
//------------------------------------------------------------/
//IO PA0.O AS RESET for IC
//------------------------------------------------------------/
#if defined EXReset_Mode
	GPIOA00_Set_ResetPin();                                      	//PA0.0 as Reset PIN
	//SIFC_CMR_Set(Option_Erase);									//user option Exreset function Erase
	IFC_CMR_Set(ExRST_EN);											//user option Exreset function enable
#endif	
//------------------------------------------------------------/
//Peripheral clock enable and disable
//EntryParameter:NONE
//ReturnValue:NONE
//------------------------------------------------------------/
    SYSCON_WDT_CMD(DISABLE);                                        //Disable Watchdog
    SYSCON->PCER0=0xFFFFFFF;                                        //PCLK Enable  0x00410071
    SYSCON->PCER1=0xFFFFFFF;                                        //PCLK Enable
    while(!(SYSCON->PCSR0&0x1));                                    //Wait PCLK enabled	
//------------------------------------------------------------/
//ISOSC/IMOSC/EMOSC/SYSCLK/IWDT/LVD/EM_CMFAIL/EM_CMRCV/CMD_ERR OSC stable interrupt
//EntryParameter:NONE
//ReturnValue:NONE
//------------------------------------------------------------/
    SYSCON_Int_Enable();                                             //INT Vector
    SYSCON->IECR=ISOSC_ST|IMOSC_ST|EMOSC_ST|SYSCLK_ST;               //enable ISOSC Statues INT,IMOSC Statues INT,EMOSC Status INT
    CK_CPU_EnAllNormalIrq();                                         //enable all IRQ
    SYSCON_CONFIG();                                                 //syscon  initial
//------------------------------------------------------------/
//Other IP config
//------------------------------------------------------------/

    GPIO_CONFIG();                                               	//GPIO initial 
	//CORET_CONFIG();													//CORET initial
    //LED_CONFIG();                                                 //Led initial                    
    //COUNTA_CONFIG();                                              //CountA initial
    //GTC0_CONFIG();                                                //GTC0 initial 
    //GTC1_CONFIG();                                                //GTC1 initial 
    //GTC2_CONFIG();                                                //GTC2 initial 
    //GTC3_CONFIG();                                                //GTC3 initial  
    //ADC12_CONFIG();                                               //ADC initial 
    //I2C_MASTER_CONFIG();                                          //I2C harware master initial 
	//I2C_SLAVE_CONFIG();                                           //I2C harware slave initial 
	                                               //UART initial 
	
    TK_CONFIG();                                                  	//Touch key initial 
}

/******************* (C) COPYRIGHT 2016 APT Chip *****END OF FILE****/