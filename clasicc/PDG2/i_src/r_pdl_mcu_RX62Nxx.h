/*""FILE COMMENT""*************************************************************
* System Name	: MCU API for RX62Nxx
* File Name		: r_pdl_mcu_RX62Nxx.h
* Version		: 1.10
* Contents		: MCU API header
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

#ifndef R_PDL_MCU_RX62Nxx_H
#define R_PDL_MCU_RX62Nxx_H

/* Library prototypes */
bool R_MCU_ControlAll(
	const uint8_t
);
bool R_MCU_GetStatusAll(
	volatile uint16_t * const
);

/* Macro definitions */
#define R_MCU_Control(a) \
( \
R_MCU_ControlAll( (a) ) \
)

#define R_MCU_GetStatus(a) \
( \
R_MCU_GetStatusAll( (a) ) \
)

#endif
/* End of file */
