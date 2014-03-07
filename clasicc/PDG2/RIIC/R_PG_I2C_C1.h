/******************************************************************************
* DISCLAIMER
* Please refer to http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_I2C_C1.h
* Version      : 1.00
* Description  : 
******************************************************************************
* History : 07.03.2014 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_pdl_iic.h"
#include "r_pdl_iic_RX62NxnFP.h"
#include "R_PG_IntFuncsExtern.h"

bool R_PG_I2C_Set_C1(void);
bool R_PG_I2C_MasterReceive_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_I2C_MasterSend_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_I2C_MasterSendWithoutStop_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_I2C_GenerateStopCondition_C1(void);
bool R_PG_I2C_GetBusState_C1(bool * busy);
bool R_PG_I2C_GetEvent_C1(bool * nack, bool * stop, bool * start, bool * lost, bool * timeout);
bool R_PG_I2C_GetReceivedDataCount_C1(uint16_t * count);
bool R_PG_I2C_GetSentDataCount_C1(uint16_t * count);
bool R_PG_I2C_Reset_C1(void);
bool R_PG_I2C_StopModule_C1(void);



