/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_SCI_C1.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
* Limitations  : 
******************************************************************************
* History : 06.03.2014 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "R_PG_SCI_C1.h"


/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_SCI_Set_C1(void)
*
* Function Name: R_PG_SCI_Set_C1
*
* Description  : �V���A��I/O�`���l���̐ݒ�
*
* Arguments    : �Ȃ�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_SCI_Create
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_SCI_Set_C1(void)
{
	return R_SCI_Create(
		1,
		PDL_SCI_ASYNC | PDL_SCI_TX_CONNECTED | PDL_SCI_RX_DISCONNECTED | PDL_SCI_CLK_INT_IO | PDL_SCI_8_BIT_LENGTH | PDL_SCI_PARITY_NONE | PDL_SCI_STOP_1,
		BIT_31 | PDL_SCI_PCLK_DIV_1 | PDL_SCI_CYCLE_BIT_8 | 0x4d | (38461 & 0x00FFFF00ul),
		0
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_SCI_SendAllData_C1(uint8_t * data, uint16_t count)
*
* Function Name: R_PG_SCI_SendAllData_C1
*
* Description  : �V���A���f�[�^��S�đ��M
*
* Arguments    : uint8_t * data : ���M����f�[�^�̊i�[��̐擪�̃A�h���X
*              : uint16_t count : ���M����f�[�^��
*              :                : 0���w�肵���ꍇ��NULL�̃f�[�^�܂ő��M���܂�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_SCI_Send
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_SCI_SendAllData_C1(uint8_t * data, uint16_t count)
{
	if( data == 0 ){ return false; }

	return R_SCI_Send(
		1,
		PDL_SCI_DMAC_DTC_TRIGGER_DISABLE,
		data,
		count,
		PDL_NO_FUNC
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_SCI_StopCommunication_C1(void)
*
* Function Name: R_PG_SCI_StopCommunication_C1
*
* Description  : �V���A���f�[�^�̑���M��~
*
* Arguments    : �Ȃ�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_SCI_Control
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_SCI_StopCommunication_C1(void)
{
	return R_SCI_Control(
		1,
		PDL_SCI_STOP_TX_AND_RX
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_SCI_GetTransmitStatus_C1(bool * complete)
*
* Function Name: R_PG_SCI_GetTransmitStatus_C1
*
* Description  : �V���A���f�[�^���M��Ԃ̎擾
*
* Arguments    : bool * complete : ���M�I���t���O�i�[��
*
* Return Value : true  : �擾�ɐ��������ꍇ
*              : false : �擾�Ɏ��s�����ꍇ
*
* Calling Functions : R_SCI_GetStatus
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_SCI_GetTransmitStatus_C1(bool * complete)
{
	uint8_t status;
	bool res;

	res = R_SCI_GetStatus(
		1,
		&status,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR
	);

	if( complete ){ *complete = (status >> 2) & 0x01; }

	return res;
}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_SCI_StopModule_C1(void)
*
* Function Name: R_PG_SCI_StopModule_C1
*
* Description  : �V���A��I/O�`���l���̒�~
*
* Arguments    : �Ȃ�
*
* Return Value : true  : ��~�ɐ��������ꍇ
*              : false : ��~�Ɏ��s�����ꍇ
*
* Calling Functions : R_SCI_Destroy
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_SCI_StopModule_C1(void)
{
	return R_SCI_Destroy( 1 );

}



