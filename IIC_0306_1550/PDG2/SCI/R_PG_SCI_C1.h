/******************************************************************************
* DISCLAIMER
* Please refer to http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_SCI_C1.h
* Version      : 1.00
* Description  : 
******************************************************************************
* History : 06.03.2014 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_pdl_sci.h"
#include "r_pdl_sci_RX62Nxx.h"
#include "R_PG_IntFuncsExtern.h"

bool R_PG_SCI_Set_C1(void);
bool R_PG_SCI_SendAllData_C1(uint8_t * data, uint16_t count);
bool R_PG_SCI_StopCommunication_C1(void);
bool R_PG_SCI_GetTransmitStatus_C1(bool * complete);
bool R_PG_SCI_StopModule_C1(void);



