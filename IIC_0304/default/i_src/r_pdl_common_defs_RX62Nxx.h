/*""FILE COMMENT""*************************************************************
* System Name	: API for RX62Nxx
* File Name		: r_pdl_common_defs_RX62Nxx.h
* Version		: 1.10
* Contents		: API common definitions
* Customer		:
* Model			:
* Order			:
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	:
* Note			:
*******************************************************************************
* Copyright, 2013. Renesas Electronics Corporation and Renesas Solutions Corp.
*******************************************************************************
* History		: 2013.10.29
*				: Ver 1.10
*				: CS release
*""FILE COMMENT END""*********************************************************/

#ifndef R_PDL_COMMON_DEFS_RX62Nxx_H
#define R_PDL_COMMON_DEFS_RX62Nxx_H

#include <stdint.h>
#include <stdbool.h>
#include <machine.h>
#include <stddef.h>
#include "iodefine_RPDL.h"

/* Callback function type */
typedef void (* VoidCallBackFunc)(void);

/* The supported MCU group */
#define PDL_MCU_GROUP RX62N

/* The highest interrupt priority level */
#define IPL_MAX	15

/* Use the I/O register area to indicate that a callback function pointer is not to be used */
#define PDL_NO_FUNC	(VoidCallBackFunc)0x00080000ul
/* Use the ROM area to indicate that a data pointer is not to be used */
#define PDL_NO_PTR (void *)0xFFFFFFFCul
/* When no parameters options are required */
#define PDL_NO_DATA 0

/* Shared global variables */
extern volatile uint32_t rpdl_CGC_f_pclk;
extern volatile uint32_t rpdl_CGC_f_iclk;
extern volatile uint32_t rpdl_CGC_f_bclk;
extern volatile	 uint8_t rpdl_INTC_brk_command;
extern volatile	 uint8_t rpdl_INTC_brk_data8;
extern volatile uint32_t rpdl_INTC_saved_isp;

/* Shared functions */
uint8_t rpdl_DMAC_get_channel(const uint8_t);

/* Utility functions */
uint8_t rpdl_BCD8_to_dec(const uint8_t);
uint16_t rpdl_BCD16_to_dec(const uint16_t);
bool rpdl_common_BCD8_check(const uint8_t);
bool rpdl_common_BCD16_check(const uint16_t);
bool rpdl_common_BCD32_check(const uint32_t);
bool rpdl_wait_time(const double);

/* BRK handler command options */
typedef enum {
	BRK_NO_COMMAND,
	BRK_START_ADC_10,
	BRK_START_ADC_10_AND_SLEEP,
	BRK_SLEEP,
	BRK_ALL_MODULE_CLOCK_STOP,
	BRK_STANDBY,
	BRK_DEEP_STANDBY,
	BRK_LOAD_FINTV_REGISTER,
	BRK_WRITE_IPL,
	BRK_CMT_START,
	BRK_CMT_STOP
} brk_commands;

/* Bit definitions */
#define  BIT_0 0x00000001ul
#define  BIT_1 0x00000002ul
#define  BIT_2 0x00000004ul
#define  BIT_3 0x00000008ul
#define  BIT_4 0x00000010ul
#define  BIT_5 0x00000020ul
#define  BIT_6 0x00000040ul
#define  BIT_7 0x00000080ul
#define  BIT_8 0x00000100ul
#define  BIT_9 0x00000200ul
#define BIT_10 0x00000400ul
#define BIT_11 0x00000800ul
#define BIT_12 0x00001000ul
#define BIT_13 0x00002000ul
#define BIT_14 0x00004000ul
#define BIT_15 0x00008000ul
#define BIT_16 0x00010000ul
#define BIT_17 0x00020000ul
#define BIT_18 0x00040000ul
#define BIT_19 0x00080000ul
#define BIT_20 0x00100000ul
#define BIT_21 0x00200000ul
#define BIT_22 0x00400000ul
#define BIT_23 0x00800000ul
#define BIT_24 0x01000000ul
#define BIT_25 0x02000000ul
#define BIT_26 0x04000000ul
#define BIT_27 0x08000000ul
#define BIT_28 0x10000000ul
#define BIT_29 0x20000000ul
#define BIT_30 0x40000000ul
#define BIT_31 0x80000000ul

#define INV_BIT_0  0xFFFFFFFEul
#define INV_BIT_1  0xFFFFFFFDul
#define INV_BIT_2  0xFFFFFFFBul
#define INV_BIT_3  0xFFFFFFF7ul
#define INV_BIT_4  0xFFFFFFEFul
#define INV_BIT_5  0xFFFFFFDFul
#define INV_BIT_6  0xFFFFFFBFul
#define INV_BIT_7  0xFFFFFF7Ful
#define INV_BIT_8  0xFFFFFEFFul
#define INV_BIT_9  0xFFFFFDFFul
#define INV_BIT_10 0xFFFFFBFFul
#define INV_BIT_11 0xFFFFF7FFul
#define INV_BIT_12 0xFFFFEFFFul
#define INV_BIT_13 0xFFFFDFFFul
#define INV_BIT_14 0xFFFFBFFFul
#define INV_BIT_15 0xFFFF7FFFul
#define INV_BIT_16 0xFFFEFFFFul
#define INV_BIT_17 0xFFFDFFFFul
#define INV_BIT_18 0xFFFBFFFFul
#define INV_BIT_19 0xFFF7FFFFul
#define INV_BIT_20 0xFFEFFFFFul
#define INV_BIT_21 0xFFDFFFFFul
#define INV_BIT_22 0xFFBFFFFFul
#define INV_BIT_23 0xFF7FFFFFul
#define INV_BIT_24 0xFEFFFFFFul
#define INV_BIT_25 0xFDFFFFFFul
#define INV_BIT_26 0xFBFFFFFFul
#define INV_BIT_27 0xF7FFFFFFul
#define INV_BIT_28 0xEFFFFFFFul
#define INV_BIT_29 0xDFFFFFFFul
#define INV_BIT_30 0xBFFFFFFFul
#define INV_BIT_31 0x7FFFFFFFul

/* Interrupt vector numbers */
#define PDL_INTC_VECTOR_BUSERR		VECT_BSC_BUSERR
#define PDL_INTC_VECTOR_FIFERR		VECT_FCU_FIFERR
#define PDL_INTC_VECTOR_FRDYI		VECT_FCU_FRDYI
#define PDL_INTC_VECTOR_SWINT		VECT_ICU_SWINT
#define PDL_INTC_VECTOR_CMT0		VECT_CMT0_CMI0
#define PDL_INTC_VECTOR_CMT1		VECT_CMT1_CMI1
#define PDL_INTC_VECTOR_CMT2		VECT_CMT2_CMI2
#define PDL_INTC_VECTOR_CMT3		VECT_CMT3_CMI3
#define PDL_INTC_VECTOR_EINT		VECT_ETHER_EINT
#define PDL_INTC_VECTOR_D0FIFO0		VECT_USB0_D0FIFO0
#define PDL_INTC_VECTOR_D1FIFO0		VECT_USB0_D1FIFO0
#define PDL_INTC_VECTOR_USBI0		VECT_USB0_USBI0
#define PDL_INTC_VECTOR_USBR0		VECT_USB_USBR0
#define PDL_INTC_VECTOR_D0FIFO1		VECT_USB1_D0FIFO1
#define PDL_INTC_VECTOR_D1FIFO1		VECT_USB1_D1FIFO1
#define PDL_INTC_VECTOR_USBI1		VECT_USB1_USBI1
#define PDL_INTC_VECTOR_USBR1		VECT_USB_USBR1
#define PDL_INTC_VECTOR_SPEI0		VECT_RSPI0_SPEI0
#define PDL_INTC_VECTOR_SPRI0		VECT_RSPI0_SPRI0
#define PDL_INTC_VECTOR_SPTI0		VECT_RSPI0_SPTI0
#define PDL_INTC_VECTOR_SPII0		VECT_RSPI0_SPII0
#define PDL_INTC_VECTOR_SPEI1		VECT_RSPI1_SPEI1
#define PDL_INTC_VECTOR_SPRI1		VECT_RSPI1_SPRI1
#define PDL_INTC_VECTOR_SPTI1		VECT_RSPI1_SPTI1
#define PDL_INTC_VECTOR_SPII1		VECT_RSPI1_SPII1
#define PDL_INTC_VECTOR_ERS0		VECT_CAN0_ERS0
#define PDL_INTC_VECTOR_RXF0		VECT_CAN0_RXF0
#define PDL_INTC_VECTOR_TXF0		VECT_CAN0_TXF0
#define PDL_INTC_VECTOR_RXM0		VECT_CAN0_RXM0
#define PDL_INTC_VECTOR_TXM0		VECT_CAN0_TXM0
#define PDL_INTC_VECTOR_PRD			VECT_RTC_PRD
#define PDL_INTC_VECTOR_CUP			VECT_RTC_CUP
#define PDL_INTC_VECTOR_ALM			VECT_RTC_ALM
#define PDL_INTC_VECTOR_IRQ0		VECT_ICU_IRQ0
#define PDL_INTC_VECTOR_IRQ1		VECT_ICU_IRQ1
#define PDL_INTC_VECTOR_IRQ2		VECT_ICU_IRQ2
#define PDL_INTC_VECTOR_IRQ3		VECT_ICU_IRQ3
#define PDL_INTC_VECTOR_IRQ4		VECT_ICU_IRQ4
#define PDL_INTC_VECTOR_IRQ5		VECT_ICU_IRQ5
#define PDL_INTC_VECTOR_IRQ6		VECT_ICU_IRQ6
#define PDL_INTC_VECTOR_IRQ7		VECT_ICU_IRQ7
#define PDL_INTC_VECTOR_IRQ8		VECT_ICU_IRQ8
#define PDL_INTC_VECTOR_IRQ9		VECT_ICU_IRQ9
#define PDL_INTC_VECTOR_IRQ10		VECT_ICU_IRQ10
#define PDL_INTC_VECTOR_IRQ11		VECT_ICU_IRQ11
#define PDL_INTC_VECTOR_IRQ12		VECT_ICU_IRQ12
#define PDL_INTC_VECTOR_IRQ13		VECT_ICU_IRQ13
#define PDL_INTC_VECTOR_IRQ14		VECT_ICU_IRQ14
#define PDL_INTC_VECTOR_IRQ15		VECT_ICU_IRQ15
#define PDL_INTC_VECTOR_WOVI		VECT_WDT_WOVI
#define PDL_INTC_VECTOR_ADI0		VECT_AD0_ADI0
#define PDL_INTC_VECTOR_ADI1		VECT_AD1_ADI1
#define PDL_INTC_VECTOR_ADI12_0		VECT_S12AD_ADI
#define PDL_INTC_VECTOR_TGIA0		VECT_MTU0_TGIA0
#define PDL_INTC_VECTOR_TGIB0		VECT_MTU0_TGIB0
#define PDL_INTC_VECTOR_TGIC0		VECT_MTU0_TGIC0
#define PDL_INTC_VECTOR_TGID0		VECT_MTU0_TGID0
#define PDL_INTC_VECTOR_TCIV0		VECT_MTU0_TCIV0
#define PDL_INTC_VECTOR_TGIE0		VECT_MTU0_TGIE0
#define PDL_INTC_VECTOR_TGIF0		VECT_MTU0_TGIF0
#define PDL_INTC_VECTOR_TGIA1		VECT_MTU1_TGIA1
#define PDL_INTC_VECTOR_TGIB1		VECT_MTU1_TGIB1
#define PDL_INTC_VECTOR_TCIV1		VECT_MTU1_TCIV1
#define PDL_INTC_VECTOR_TCIU1		VECT_MTU1_TCIU1
#define PDL_INTC_VECTOR_TGIA2		VECT_MTU2_TGIA2
#define PDL_INTC_VECTOR_TGIB2		VECT_MTU2_TGIB2
#define PDL_INTC_VECTOR_TCIV2		VECT_MTU2_TCIV2
#define PDL_INTC_VECTOR_TCIU2		VECT_MTU2_TCIU2
#define PDL_INTC_VECTOR_TGIA3		VECT_MTU3_TGIA3
#define PDL_INTC_VECTOR_TGIB3		VECT_MTU3_TGIB3
#define PDL_INTC_VECTOR_TGIC3		VECT_MTU3_TGIC3
#define PDL_INTC_VECTOR_TGID3		VECT_MTU3_TGID3
#define PDL_INTC_VECTOR_TCIV3		VECT_MTU3_TCIV3
#define PDL_INTC_VECTOR_TGIA4		VECT_MTU4_TGIA4
#define PDL_INTC_VECTOR_TGIB4		VECT_MTU4_TGIB4
#define PDL_INTC_VECTOR_TGIC4		VECT_MTU4_TGIC4
#define PDL_INTC_VECTOR_TGID4		VECT_MTU4_TGID4
#define PDL_INTC_VECTOR_TCIV4		VECT_MTU4_TCIV4
#define PDL_INTC_VECTOR_TGIU5		VECT_MTU5_TGIU5
#define PDL_INTC_VECTOR_TGIV5		VECT_MTU5_TGIV5
#define PDL_INTC_VECTOR_TGIW5		VECT_MTU5_TGIW5
#define PDL_INTC_VECTOR_TGIA6		VECT_MTU6_TGIA6
#define PDL_INTC_VECTOR_TGIB6		VECT_MTU6_TGIB6
#define PDL_INTC_VECTOR_TGIC6		VECT_MTU6_TGIC6
#define PDL_INTC_VECTOR_TGID6		VECT_MTU6_TGID6
#define PDL_INTC_VECTOR_TCIV6		VECT_MTU6_TCIV6
#define PDL_INTC_VECTOR_TGIE6		VECT_MTU6_TGIE6
#define PDL_INTC_VECTOR_TGIF6		VECT_MTU6_TGIF6
#define PDL_INTC_VECTOR_TGIA7		VECT_MTU7_TGIA7
#define PDL_INTC_VECTOR_TGIB7		VECT_MTU7_TGIB7
#define PDL_INTC_VECTOR_TCIV7		VECT_MTU7_TCIV7
#define PDL_INTC_VECTOR_TCIU7		VECT_MTU7_TCIU7
#define PDL_INTC_VECTOR_TGIA8		VECT_MTU8_TGIA8
#define PDL_INTC_VECTOR_TGIB8		VECT_MTU8_TGIB8
#define PDL_INTC_VECTOR_TCIV8		VECT_MTU8_TCIV8
#define PDL_INTC_VECTOR_TCIU8		VECT_MTU8_TCIU8
#define PDL_INTC_VECTOR_TGIA9		VECT_MTU9_TGIA9
#define PDL_INTC_VECTOR_TGIB9		VECT_MTU9_TGIB9
#define PDL_INTC_VECTOR_TGIC9		VECT_MTU9_TGIC9
#define PDL_INTC_VECTOR_TGID9		VECT_MTU9_TGID9
#define PDL_INTC_VECTOR_TCIV9		VECT_MTU9_TCIV9
#define PDL_INTC_VECTOR_TGIA10		VECT_MTU10_TGIA10
#define PDL_INTC_VECTOR_TGIB10		VECT_MTU10_TGIB10
#define PDL_INTC_VECTOR_TGIC10		VECT_MTU10_TGIC10
#define PDL_INTC_VECTOR_TGID10		VECT_MTU10_TGID10
#define PDL_INTC_VECTOR_TCIV10		VECT_MTU10_TCIV10
#define PDL_INTC_VECTOR_TGIU11		VECT_MTU11_TGIU11
#define PDL_INTC_VECTOR_TGIV11		VECT_MTU11_TGIV11
#define PDL_INTC_VECTOR_TGIW11		VECT_MTU11_TGIW11
#define PDL_INTC_VECTOR_OEI1		VECT_POE_OEI1
#define PDL_INTC_VECTOR_OEI2		VECT_POE_OEI2
#define PDL_INTC_VECTOR_OEI3		VECT_POE_OEI3
#define PDL_INTC_VECTOR_OEI4		VECT_POE_OEI4
#define PDL_INTC_VECTOR_CMIA0		VECT_TMR0_CMIA0
#define PDL_INTC_VECTOR_CMIB0		VECT_TMR0_CMIB0
#define PDL_INTC_VECTOR_OVI0		VECT_TMR0_OVI0
#define PDL_INTC_VECTOR_CMIA1		VECT_TMR1_CMIA1
#define PDL_INTC_VECTOR_CMIB1		VECT_TMR1_CMIB1
#define PDL_INTC_VECTOR_OVI1		VECT_TMR1_OVI1
#define PDL_INTC_VECTOR_CMIA2		VECT_TMR2_CMIA2
#define PDL_INTC_VECTOR_CMIB2		VECT_TMR2_CMIB2
#define PDL_INTC_VECTOR_OVI2		VECT_TMR2_OVI2
#define PDL_INTC_VECTOR_CMIA3		VECT_TMR3_CMIA3
#define PDL_INTC_VECTOR_CMIB3		VECT_TMR3_CMIB3
#define PDL_INTC_VECTOR_OVI3		VECT_TMR3_OVI3
#define PDL_INTC_VECTOR_DMAC0I		VECT_DMAC_DMAC0I
#define PDL_INTC_VECTOR_DMAC1I		VECT_DMAC_DMAC1I
#define PDL_INTC_VECTOR_DMAC2I		VECT_DMAC_DMAC2I
#define PDL_INTC_VECTOR_DMAC3I		VECT_DMAC_DMAC3I
#define PDL_INTC_VECTOR_EXDMAC0I	VECT_EXDMAC_EXDMAC0I
#define PDL_INTC_VECTOR_EXDMAC1I	VECT_EXDMAC_EXDMAC1I
#define PDL_INTC_VECTOR_ERI0		VECT_SCI0_ERI0
#define PDL_INTC_VECTOR_RXI0		VECT_SCI0_RXI0
#define PDL_INTC_VECTOR_TXI0		VECT_SCI0_TXI0
#define PDL_INTC_VECTOR_TEI0		VECT_SCI0_TEI0
#define PDL_INTC_VECTOR_ERI1		VECT_SCI1_ERI1
#define PDL_INTC_VECTOR_RXI1		VECT_SCI1_RXI1
#define PDL_INTC_VECTOR_TXI1		VECT_SCI1_TXI1
#define PDL_INTC_VECTOR_TEI1		VECT_SCI1_TEI1
#define PDL_INTC_VECTOR_ERI2		VECT_SCI2_ERI2
#define PDL_INTC_VECTOR_RXI2		VECT_SCI2_RXI2
#define PDL_INTC_VECTOR_TXI2		VECT_SCI2_TXI2
#define PDL_INTC_VECTOR_TEI2		VECT_SCI2_TEI2
#define PDL_INTC_VECTOR_ERI3		VECT_SCI3_ERI3
#define PDL_INTC_VECTOR_RXI3		VECT_SCI3_RXI3
#define PDL_INTC_VECTOR_TXI3		VECT_SCI3_TXI3
#define PDL_INTC_VECTOR_TEI3		VECT_SCI3_TEI3
#define PDL_INTC_VECTOR_ERI5		VECT_SCI5_ERI5
#define PDL_INTC_VECTOR_RXI5		VECT_SCI5_RXI5
#define PDL_INTC_VECTOR_TXI5		VECT_SCI5_TXI5
#define PDL_INTC_VECTOR_TEI5		VECT_SCI5_TEI5
#define PDL_INTC_VECTOR_ERI6		VECT_SCI6_ERI6
#define PDL_INTC_VECTOR_RXI6		VECT_SCI6_RXI6
#define PDL_INTC_VECTOR_TXI6		VECT_SCI6_TXI6
#define PDL_INTC_VECTOR_TEI6		VECT_SCI6_TEI6
#define PDL_INTC_VECTOR_ICEEI0		VECT_RIIC0_ICEEI0
#define PDL_INTC_VECTOR_ICRXI0		VECT_RIIC0_ICRXI0
#define PDL_INTC_VECTOR_ICTXI0		VECT_RIIC0_ICTXI0
#define PDL_INTC_VECTOR_ICTEI0		VECT_RIIC0_ICTEI0
#define PDL_INTC_VECTOR_ICEEI1		VECT_RIIC1_ICEEI1
#define PDL_INTC_VECTOR_ICRXI1		VECT_RIIC1_ICRXI1
#define PDL_INTC_VECTOR_ICTXI1		VECT_RIIC1_ICTXI1
#define PDL_INTC_VECTOR_ICTEI1		VECT_RIIC1_ICTEI1

#endif

/* End of file */
