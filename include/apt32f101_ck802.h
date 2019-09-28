/*
  ******************************************************************************
  * @file    apt32f101_ck802.h
  * @author  APT AE Team
  * @version V1.24
  * @date    2018/10/15
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _apt32f101_ck802_H
#define _apt32f101_ck802_H

/* Includes ------------------------------------------------------------------*/
#include "apt32f101.h"

//---------------------------------------------------------------------------- 
//                      Interrupt Controller
//---------------------------------------------------------------------------- 
#define INTC_ISER_WRITE(val)     *(volatile UINT32 *) (INTC_ISER  ) = val
#define INTC_IWER_WRITE(val)     *(volatile UINT32 *) (INTC_IWER  ) = val
#define INTC_ICER_WRITE(val)     *(volatile UINT32 *) (INTC_ICER  ) = val
#define INTC_IWDR_WRITE(val)     *(volatile UINT32 *) (INTC_IWDR  ) = val
#define INTC_ISPR_WRITE(val)     *(volatile UINT32 *) (INTC_ISPR  ) = val
#define INTC_ICPR_WRITE(val)     *(volatile UINT32 *) (INTC_ICPR  ) = val
#define INTC_IABR_WRITE(val)     *(volatile UINT32 *) (INTC_IABR  ) = val
#define INTC_IPR0_WRITE(val)   	 *(volatile UINT32 *) (INTC_IPR0  ) = val
#define INTC_IPR1_WRITE(val)     *(volatile UINT32 *) (INTC_IPR1  ) = val
#define INTC_IPR2_WRITE(val)     *(volatile UINT32 *) (INTC_IPR2  ) = val
#define INTC_IPR3_WRITE(val)     *(volatile UINT32 *) (INTC_IPR3  ) = val
#define INTC_IPR4_WRITE(val)     *(volatile UINT32 *) (INTC_IPR4  ) = val
#define INTC_IPR5_WRITE(val)     *(volatile UINT32 *) (INTC_IPR5  ) = val
#define INTC_IPR6_WRITE(val)     *(volatile UINT32 *) (INTC_IPR6  ) = val
#define INTC_IPR7_WRITE(val)     *(volatile UINT32 *) (INTC_IPR7  ) = val
#define INTC_ISR_WRITE(val)      *(volatile UINT32 *) (INTC_ISR   ) = val
#define INTC_IPTR_WRITE(val)     *(volatile UINT32 *) (INTC_IPTR  ) = val


#define INTC_ISER_READ(intc)   (intc->ISER  )
#define INTC_IWER_READ(intc)   (intc->IWER  )
#define INTC_ICER_READ(intc)   (intc->ICER  )
#define INTC_IWDR_READ(intc)   (intc->IWDR  )
#define INTC_ISPR_READ(intc)   (intc->ISPR  )
#define INTC_ICPR_READ(intc)   (intc->ICPR  )
#define INTC_IABR_READ(intc)   (intc->IABR  )
#define INTC_IPR0_READ(intc)   (intc->IPR0  )
#define INTC_IPR1_READ(intc)   (intc->IPR1  )
#define INTC_IPR2_READ(intc)   (intc->IPR2  )
#define INTC_IPR3_READ(intc)   (intc->IPR3  )
#define INTC_IPR4_READ(intc)   (intc->IPR4  )
#define INTC_IPR5_READ(intc)   (intc->IPR5  )
#define INTC_IPR6_READ(intc)   (intc->IPR6  )
#define INTC_IPR7_READ(intc)   (intc->IPR7  )
#define INTC_ISR_READ(intc)    (intc->ISR   )
#define INTC_IPTR_READ(intc)   (intc->IPTR  )

typedef enum IRQn
{
/******  CK802 Processor Exceptions Numbers ***************************************************/
        ISR_Restart                     = -32,
        ISR_Misaligned_Access           = -31,
        ISR_Access_Error                = -30,
        ISR_Divided_By_Zero             = -29,
        ISR_Illegal                     = -28,
        ISR_Privlege_Violation          = -27,
        ISR_Trace_Exection              = -26,
        ISR_Breakpoint_Exception        = -25,
        ISR_Unrecoverable_Error         = -24,
        ISR_Idly4_Error                 = -23,
        ISR_Auto_INT                 	= -22,
        ISR_Auto_FINT                   = -21,
        ISR_Reserved_HAI                = -20,
        ISR_Reserved_FP                 = -19,
        ISR_TLB_Ins_Empty               = -18,
        ISR_TLB_Data_Empty              = -17,
  
/******  CK802 specific Interrupt Numbers *********************************************************/
        INTC_CORETIM_IRQn               = 0,      
        INTC_TIME1_IRQn                	= 1,      
        INTC_UART0_IRQn                 = 2,
        INTC_GPIOA2_IRQn                = 8,
} IRQn_Type;


void INTC_Init(void);
void force_interrupt(IRQn_Type IRQn);

void CK_CPU_EnAllNormalIrq(void);
void CK_CPU_DisAllNormalIrq(void);

#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef uint32_t
#define uint32_t unsigned int
#endif

#ifndef uint8_t
#define uint8_t unsigned char
#endif

#ifndef uint16_t
#define uint16_t unsigned short
#endif


#endif   /**< apt32f101_ck802_H */

/******************* (C) COPYRIGHT 2016 APT Chip *****END OF FILE****/


