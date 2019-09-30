/* Includes ------------------------------------------------------------------*/
#include "apt32f101.h"
#include "apt32f101_gpio.h"
#include "apt32f101_uart.h"
#include "apt32f101_counta.h"
#include "apt32f101_i2c.h"
#include "apt32f101_gtc.h"
#include "apt32f101_syscon.h"
#include "apt32f101_tkey.h"
/* defines -------------------------------------------------------------------*/


#define LED_GPIO_DATA_INIT	GPIO_Init(GPIOB0,0,0);      //data_in
#define	LED_GPIO_CLK_INIT   GPIO_Init(GPIOB0,1,0); 		//CLK
#define	LED_GPIO_STB_INIT   GPIO_Init(GPIOA0,0,0);		///STB
	
#define	LED_GPIO_PWM1_INIT  GPIO_Init(GPIOA0,5,0);		//PWM1
#define	LED_GPIO_PWM2_INIT  GPIO_Init(GPIOC0,0,0);		//PWM2

#define	LED_GPIO_RLY1_INIT  GPIO_Init(GPIOB0,2,0); 		//RLY1
#define	LED_GPIO_RLY2_INIT  GPIO_Init(GPIOB0,3,0); 		//RLY2

#define  clk_H GPIO_Write_High(GPIOB0,1);
#define  dio_H GPIO_Write_High(GPIOB0,0);
#define  stb_H GPIO_Write_High(GPIOA0,0);

#define  clk_L GPIO_Write_Low(GPIOB0,1);
#define  dio_L GPIO_Write_Low(GPIOB0,0);
#define  stb_L GPIO_Write_Low(GPIOA0,0);

#define  PWM_HIGH_Fan GPIO_Write_High(GPIOA0,5);
#define  PWM_LOW_Fan  GPIO_Write_Low(GPIOA0,5);
#define  PWM_HIGH_Light GPIO_Write_High(GPIOC0,0);
#define  PWM_LOW_Light  GPIO_Write_Low(GPIOC0,0);

#define	 FAN_RELAY_HIGH GPIO_Write_High(GPIOB0,3); 
#define  FAN_RELAY_LOW  GPIO_Write_Low(GPIOB0,3); 
#define	 LED_RELAY_HIGH GPIO_Write_High(GPIOB0,2);
#define  LED_RELAY_LOW  GPIO_Write_Low(GPIOB0,2);

#define ROW_LED  0x01
#define ROW_FAN  0x02

#define CLOSE   0X00
#define OPEN    0X01

#define COM_MASTER   3
#define COM_FAN      2
#define COM_LED      1
#define NO_COM       0

#define MCU_VER  "mcu ver:V1.0.2"

#define  LIGHT_TIMER_PARA 39000
#define  LIGHT_SEG_PARA 380



/* externs prg--------- ------------------------------------------------------*/
extern void UART_CONFIG(void);
U8_T YSZSendBuf[32];
extern void APT32F101_init(void);
extern void TK_WheelSlider_prg(void);
extern void WheelSliderRG_setting(void);
extern void WheelSliderRG_Initial(void);


volatile U8_T	R_TK_Calibration,R_TK_Debouce,R_TK_Longpress_T,R_TK_MCONL,R_TK_GSR,R_TK_MCONH,R_TK_Trigglevel[16];
volatile U16_T	R_TK_Channel_EN,KEY_MAP_16BIT,R_TK_Offset[16];
volatile S16_T	R_TK_Wheel_Value,R_TK_Slider_Value;
/*-------------------------------------------------------------------*/
volatile U8_T Flag = 0;
volatile U8_T Send_cmd_Flag = 0;
volatile U8_T receive_cmd_Flag = 0;
#define MS_1  4000
volatile U32_T bright_level_fan = 8*MS_1;
volatile U32_T bright_level_light = 8*MS_1;
char uart_receive_buf[4];
char uart_send_buf[4];
volatile U8_T Fan_rly_status=0;
volatile U8_T Light_rly_status=0;
volatile U8_T pwm_fan_status=0;
volatile U8_T pwm_led_status=0;
volatile U8_T Led_SVal;
volatile U8_T Fan_WVal;
volatile U8_T P_Led_SVal;
volatile U8_T P_Fan_WVal;
volatile U16_T OFFSET_TEST[16];
volatile U8_T Noffset_cont[16];

char light[15]={0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7f,0x01,0x02,0x04,0x08,0x010,0x20,0x40};

/*************************************************************/
void delay_50us(void){
	volatile unsigned int i,j ,k=0;
    j = 48* 1;
    for ( i = 0; i < j; i++ )
    {
        k++;
    }
}

void delay_10ms(void){
	volatile unsigned int i,j ,k=0;
    j = 79* 200;
    for ( i = 0; i < j; i++ )
    {
        k++;
    }
}

void delay_300ms(void){
	volatile unsigned int i,j ,k=0;
    j = 79* 6000;
    for ( i = 0; i < j; i++ )
    {
        k++;
    }
}


/*************************************************************/
//定时器延迟改变pwd调光时间
void TIMER_INIT(void){            
	COUNT_DeInit();
	if(bright_level_light == bright_level_fan){			//灯亮度等于风扇亮度 取其中一值作为时基
			COUNTA_Init(bright_level_fan,0,Period_H,DIV4,ONESHOT_MODE,CARRIER_ON,OSP_LOW);			
	}
	else{
			if(Flag==0){							
				if(bright_level_light>bright_level_fan){	//前半段如果灯亮度大于风扇亮度
					COUNTA_Init(bright_level_fan,0,Period_H,DIV4,ONESHOT_MODE,CARRIER_ON,OSP_LOW);
				}
				else{
					COUNTA_Init(bright_level_light,0,Period_H,DIV4,ONESHOT_MODE,CARRIER_ON,OSP_LOW);
				}
			}else{
				if(bright_level_light>bright_level_fan){
					COUNTA_Init(bright_level_light - bright_level_fan,0,Period_H,DIV4,ONESHOT_MODE,CARRIER_ON,OSP_LOW);
				}else
				{
					COUNTA_Init(bright_level_fan - bright_level_light,0,Period_H,DIV4,ONESHOT_MODE,CARRIER_ON,OSP_LOW);
				}	
			}
	
	}
	
	COUNTA_Config(SW_STROBE,PENDREM_OFF,MATCHREM_OFF,REMSTAT_0,ENVELOPE_0);
	COUNTA_Start();
	COUNTA_Int_Enable();
}

//风扇端可控硅触发
void tim1_int_cb(void)    
{
	if(pwm_fan_status==OPEN){
		PWM_HIGH_Fan;
		delay_50us();	  
		PWM_LOW_Fan; 
	}
}

//灯端可控硅触发
void tim2_int_cb(void)		
{
	if(pwm_led_status==OPEN){
	  PWM_HIGH_Light;
	  delay_50us();	  
	  PWM_LOW_Light;
	}
}

/*************************************************************/
//60HZ市电零点检测中断
void EXTI_PC01_INIT(void){    
	GPIO_Init(GPIOC0,1,0); 
	GPIO_PullLow_Init(GPIOC0,0);
	
	GPIO_IntGroup_Set(PC0);
	GPIOC0_EXI_Init(EXI1);
	EXTI_trigger_CMD(ENABLE,EXI_PIN1,_EXIFT);
	EXTI_trigger_CMD(ENABLE,EXI_PIN1,_EXIRT);
	EXTI_interrupt_CMD(ENABLE,EXI_PIN1);
	GPIO_EXTI_interrupt(GPIOC0,0b00000000000010); 
	EXI1_Int_Enable(); 
	EXI1_WakeUp_Enable(); 
}

/*************************************************************/
//tm1616调光接口
void tm1616write(U8_T wr_date)     
{
	unsigned char i;
	stb_L;
	nop;
	for(i = 0; i < 8; i++)
	{
		clk_L;
		nop;
		if((wr_date&0x01) != 0)
		{
			dio_H;
		}
		else
		{
			dio_L;
		}
		nop;
		clk_H;
		nop;
		wr_date = wr_date >> 1;
	}	
}


//风扇端调光灯排 与 灯端调光灯排
void tm1616show(U8_T light_data,U8_T row)
{
	clk_H; 
	dio_H;
	stb_H; 
	
	tm1616write(0x00);  			//显示模式
	stb_H;							
	tm1616write(0x44);  			//数据命令设置
	stb_H;	

	if(row==ROW_LED){
		tm1616write(0xC0);			//设置显示地址1  00
		tm1616write(light_data); 		
		stb_H;		
	}else if(row==ROW_FAN){
		tm1616write(0xC2);			//设置显示地址1  00
		tm1616write(light_data); 		
		stb_H;	
	}else{}
	
	tm1616write(0x8f);				//控制命令设置，设置显示开、显示脉冲宽度4/16  1000 1010
	stb_H;
}

/*************************************************************/
//pwm 、 继电器 、 调光芯片引脚初始化
void GPIO_INIT(void){
	
	LED_GPIO_DATA_INIT;	    //data_in
	LED_GPIO_CLK_INIT;    	//CLK
	LED_GPIO_STB_INIT;   	///STB
		
	LED_GPIO_PWM1_INIT;  	//PWM1
	LED_GPIO_PWM2_INIT;  	//PWM2

	LED_GPIO_RLY1_INIT;  	//RLY1
	LED_GPIO_RLY2_INIT;  	//RLY2

	PWM_LOW_Fan;
	PWM_LOW_Light;
	FAN_RELAY_LOW;
	LED_RELAY_LOW;
}


/*************************************************************/
//保持 电灯滑条 当前触摸点的值
S16_T Read_Slider_Value(S16_T SVal){

	static S16_T _SVal=0;
	static U8_T num;
	
	if((SVal!=0)&&(SVal!=_SVal)){
		
		if(SVal>=253){
			SVal = 255;
		}
		
		_SVal = SVal*100/255;
		
		num =_SVal;
			
		if(num==0)
		{
			num=1;
		}
		if((0<num)&&(num<101)){
			num=101-num;
		}
			
	}

	return num;
}

//保持 风扇滑条 当前触摸点的值
S16_T Read_Wheel_Value(S16_T WVal){

	static S16_T _WVal=0;
	static U8_T num;
	
	if((WVal != 0) && (WVal!=_WVal)){
		
		if(WVal>=253){
			WVal = 255;
		}
		
		_WVal = WVal*100/255; 
		num =_WVal;
		
		if(num==0)
		{
			num=1;
		}

		if((0<num)&&(num<101)){
			num=101-num;
		}
		
	}
	
	return num;
}

/*************************************************************/
//根据触摸值 调触摸面板led
void led_dimmer(unsigned char Led_S,unsigned char Fan_W){

	int i = 0;
	static unsigned char _Led_S = 0;
	static unsigned char _Fan_W = 0;
	static unsigned char Light_led_num,Fan_led_num;
	static unsigned char RLY_F_Flag=0;
	static unsigned char RLY_L_Flag=0;
	static unsigned char fix_one=0;
	
	if(_Led_S!=Led_S&&(Led_S!=200)){         //灯端 触摸值 调光换算
		
		if(Fan_W==200){			
			 
		}
		
		_Led_S=Led_S;
		
		if (_Led_S > 0){

				if(0<_Led_S&&_Led_S<=13){
					Light_led_num=1;
				}else if(13<_Led_S&&_Led_S<=25){
					Light_led_num=2;
				}else if(25<_Led_S&&_Led_S<=35){
					Light_led_num=3;
				}else if(35<_Led_S&&_Led_S<=52){
					Light_led_num=4;
				}else if(52<_Led_S&&_Led_S<=70){
					Light_led_num=5;
				}else if(70<_Led_S&&_Led_S<=91){
					Light_led_num=6;
				}else if(91<_Led_S&&_Led_S<=100){
					Light_led_num=7;
				}
		}	
		
	}
	
	if(_Fan_W!=Fan_W&&(Fan_W!=200)){    //风扇端 触摸值 调光换算
			
		if(Led_S==200){

		}
			_Fan_W=Fan_W;
			

		if (_Fan_W > 0){

				if(0<_Fan_W&&_Fan_W<=13){
					Fan_led_num=1;
				}else if(13<_Fan_W&&_Fan_W<=25){
					Fan_led_num=2;
				}else if(25<_Fan_W&&_Fan_W<=35){
					Fan_led_num=3;
				}else if(35<_Fan_W&&_Fan_W<=52){
					Fan_led_num=4;
				}else if(52<_Fan_W&&_Fan_W<=79){
					Fan_led_num=5;
				}else if(79<_Fan_W&&_Fan_W<=86){
					Fan_led_num=6;
				}else if(86<_Fan_W&&_Fan_W<=100){
					Fan_led_num=7;
				}
		}



	
	}
		
		
	if((Fan_rly_status&0x80)==0x80)
	{
		if(RLY_F_Flag==0){								//风扇端继电器打开 逐渐点亮到之前的led灯点
			RLY_F_Flag = 1;
			FAN_RELAY_HIGH;
			delay_300ms();
			pwm_fan_status=OPEN;
			
			for(i=0;i<=Fan_led_num;i++){
				tm1616show(light[i],ROW_FAN);
				delay_nms(5000);
			}
		}
	
		tm1616show(light[Fan_led_num],ROW_FAN);			//根据触摸值换算后 轮询 亮灯
		
	}else
	{
		if(RLY_F_Flag==1){
			RLY_F_Flag = 0;
			pwm_fan_status=CLOSE;
			delay_300ms();
			FAN_RELAY_LOW;
		}
		
		tm1616show(light[7+Fan_led_num],ROW_FAN);	 //关闭继电器后 亮一颗保持之前状态的灯
	}
	
	
		
	if((Light_rly_status&0x80)==0x80)				//灯端继电器打开 逐渐点亮到之前的led灯点
	{
		if(RLY_L_Flag==0){
			RLY_L_Flag = 1;
			LED_RELAY_HIGH;
			delay_300ms();
			pwm_led_status=OPEN;
			
			for(i=0;i<=Light_led_num;i++){
				tm1616show(light[i],ROW_LED);
				delay_nms(5000);
			}
		}
		
		tm1616show(light[Light_led_num],ROW_LED);
		
	}else
	{
		if(RLY_L_Flag==1){
			RLY_L_Flag = 0;
			pwm_led_status=CLOSE;
			delay_300ms();
			LED_RELAY_LOW;
		}
		tm1616show(light[7+Light_led_num],ROW_LED);
	}
		
	if( Send_cmd_Flag>0){     					//有触摸值改变时 向主机 发送 两路触摸值
			
			uart_send_buf[0]='$';
			uart_send_buf[1]=_Fan_W;//_Fan_W
			uart_send_buf[2]=_Led_S;//_Led_S
			uart_send_buf[3]='#';
			UARTTransmit(UART1,uart_send_buf,4);
			Send_cmd_Flag--;
	}
}


void Lamp_init(){  //上电两排ed灯初始化
	
	U8_T i;

	for(i=0;i<=7;i++){
		tm1616show(light[i],ROW_LED);
		tm1616show(light[i],ROW_FAN);
		delay_nms(5000);
	}
	
	for(i=7;i>0;i--){
		tm1616show(light[i],ROW_LED);
		tm1616show(light[i],ROW_FAN);
		delay_nms(5000);
	}
	tm1616show(light[1],ROW_LED);
	tm1616show(light[1],ROW_FAN);
}
/*************************************************************/

void IWD_INIT(void){
	SYSCON_IWDCNT_Config(DISABLE_IWDT_SHORT,IWDT_TIME_8S,IWDT_INTW_DIV_1);
	SYSCON_WDT_CMD(ENABLE);
	SYSCON_IWDCNT_Reload();
	SYSCON_WakeUp_Enable();
	IWDT_Int_Enable();
}
/*************************************************************/
//解析主机发送过来的信息
void UART_Analytic(void){     
	char c = 0,t1=0,t2=0;
	static U8_T i = 0,Flag=0;
	UARTRxByte(UART1, &c);
	
	if(c!=0){
	
		if(c=='$'||Flag==1){
			Flag=1;
			uart_receive_buf[i]=c;
			i++;
			if(c=='#'){
				i=0;
				Flag=0;
				
				Fan_rly_status = 0x80&uart_receive_buf[1];
				Light_rly_status = 0x80&uart_receive_buf[2];
				
				t1 = 0x7F&uart_receive_buf[1]; 
				if(0<t1&&t1<=100){
					P_Fan_WVal =  t1;
				}
				
				t2 = 0x7F&uart_receive_buf[2]; 
				if(0<t2&&t2<=100){
					P_Led_SVal =  t2;
				}
				t1=0;
				t2=0;
				receive_cmd_Flag = COM_MASTER;
			}
		}
  }
}
/*************************************************************/
//获取滑条值  根据滑条值设立定时器斩波时间与调光
 
void light_control(void)
{
	static U8_T _Light_Val = 0;
	static U8_T _Fan_Val = 0;
	
	static unsigned char timer1;
	static unsigned char timer2;
	timer1++;
	timer2++;

	if(((Fan_rly_status&0x80)==0x80)&&(timer1%11==0)){			//如果读取太快，发往app串口跟不上
		Fan_WVal = Read_Wheel_Value(R_TK_Wheel_Value);  //R_TK_Wheel_Value
	}
	

	if(_Fan_Val!=Fan_WVal){
	    receive_cmd_Flag=COM_FAN;
	    Send_cmd_Flag++;  
	   	_Fan_Val=Fan_WVal;
	}
	

	if((Light_rly_status&0x80)==0x80&&(timer2%11==0)){
		Led_SVal = Read_Slider_Value(R_TK_Slider_Value);  //R_TK_Slider_Value
	}
 
	if(_Light_Val != Led_SVal){
	   receive_cmd_Flag=COM_LED;
	   Send_cmd_Flag++;  
	    _Light_Val =  Led_SVal;
	}
	
	
	if(receive_cmd_Flag == COM_MASTER){
		led_dimmer(P_Led_SVal,P_Fan_WVal);
		bright_level_fan = LIGHT_TIMER_PARA-P_Fan_WVal*LIGHT_SEG_PARA;
		bright_level_light = LIGHT_TIMER_PARA-P_Led_SVal*LIGHT_SEG_PARA;
		receive_cmd_Flag = NO_COM;
	}
	else if(receive_cmd_Flag == COM_LED){
		led_dimmer(_Light_Val,200);
		bright_level_light = LIGHT_TIMER_PARA-_Light_Val*LIGHT_SEG_PARA;
		receive_cmd_Flag = NO_COM;
	}
	else if(receive_cmd_Flag == COM_FAN){
		led_dimmer(200,_Fan_Val);
		bright_level_fan = LIGHT_TIMER_PARA-_Fan_Val*LIGHT_SEG_PARA;
		receive_cmd_Flag = NO_COM;
	}
}

void TK_Negative_rebuild(void)
{
	U8_T i,j;
	Read_Sampling();
	Read_Baseline();
	for(i=0;i<15;i++)
	{
		if(Sampling_Data[i]>Baseline_Data[i])
		{
			OFFSET_TEST[i]=Sampling_Data[i]-Baseline_Data[i];
		}
		else
		{
			OFFSET_TEST[i]=0;
		}
		if(OFFSET_TEST[i]>TK_Trigglevel_data[i]*3/4)
		{
			Noffset_cont[i]++;
			if(Noffset_cont[i]>=20) 
			{
				TK_Rebuild();
				for(j=0;j<15;j++)
				{
					Noffset_cont[i]=0;
				}
			}
		}
		else
		{
			Noffset_cont[i]=0;
		}
	}
}
void YSZ_Send_prg(void)
{
	 YSZSendBuf[0]=0x0d;
	 YSZSendBuf[1]=0x0a;
	 
	 YSZSendBuf[2]=R_TK_Offset[1]>>8;
	 YSZSendBuf[3]=R_TK_Offset[1]&0xff;  
	 YSZSendBuf[4]=R_TK_Offset[2]>>8;	
	 YSZSendBuf[5]=R_TK_Offset[2]&0xff;

	 YSZSendBuf[6]=R_TK_Offset[5]>>8;
	 YSZSendBuf[7]=R_TK_Offset[5]&0xff;
	 YSZSendBuf[8]=R_TK_Offset[6]>>8;
	 YSZSendBuf[9]=R_TK_Offset[6]&0xff;

	 YSZSendBuf[10]=R_TK_Offset[7]>>8;
	 YSZSendBuf[11]=R_TK_Offset[7]&0xff;
	 YSZSendBuf[12]=R_TK_Offset[8]>>8; 
	 YSZSendBuf[13]=R_TK_Offset[8]&0xff;   

	 YSZSendBuf[14]=R_TK_Offset[9]>>8; 
	 YSZSendBuf[15]=R_TK_Offset[9]&0xff;
	 YSZSendBuf[16]=R_TK_Offset[10]>>8;
	 YSZSendBuf[17]=R_TK_Offset[10]&0xff;

	 YSZSendBuf[18]=R_TK_Offset[11]>>8;
	 YSZSendBuf[19]=R_TK_Offset[11]&0xff;
	 YSZSendBuf[20]=R_TK_Offset[12]>>8;
	 YSZSendBuf[21]=R_TK_Offset[12]&0xff;		

	 YSZSendBuf[22]=R_TK_Slider_Value>>8;
	 YSZSendBuf[23]=R_TK_Slider_Value&0xff;	
	 YSZSendBuf[24]=R_TK_Wheel_Value>>8;
	 YSZSendBuf[25]=R_TK_Wheel_Value&0xff;		

	 YSZSendBuf[26]=KEY_MAP_16BIT>>8;
	 YSZSendBuf[27]=KEY_MAP_16BIT&0xff;		
	 
	 UARTTransmit(UART0,YSZSendBuf,28);
	 delay_nms(1000);
}
/*************************************************************/
int main(void)
{
	delay_nms(20000);
	APT32F101_init();	
	
	WheelSlider_Parameter_Init();				 
	WheelSliderRG_Initial();
	WheelSliderRG_setting();	
	GPIO_INIT();
	EXTI_PC01_INIT();
	Lamp_init();
	IWD_INIT();
	UART_CONFIG(); 
    					
	UARTTransmit(UART1,"reset\r\n",7);		
	UARTTransmit(UART1,MCU_VER,14);	
    while(1)
	{ 
		SYSCON_IWDCNT_Reload();	
		TK_Negative_rebuild	();	
		TK_WheelSlider_prg();					
			
		light_control();
    }
}



