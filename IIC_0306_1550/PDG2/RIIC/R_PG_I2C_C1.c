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
* File Name    : R_PG_I2C_C1.c
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
#include "R_PG_I2C_C1.h"


/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_Set_C1(void)
*
* Function Name: R_PG_I2C_Set_C1
*
* Description  : I2C�o�X�C���^�t�F�[�X�`���l���̐ݒ�
*
* Arguments    : �Ȃ�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_Create
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_Set_C1(void)
{
	return R_IIC_Create(
		1,
		PDL_IIC_MODE_IIC | PDL_IIC_INT_PCLK_DIV_8 | PDL_IIC_TIMEOUT_DISABLE | PDL_IIC_SDA_DELAY_0 | PDL_IIC_NF_DISABLE,
		PDL_IIC_NTALD_DISABLE | PDL_IIC_SALD_DISABLE | PDL_IIC_SLAVE_0_DISABLE | PDL_IIC_SLAVE_1_DISABLE | PDL_IIC_SLAVE_2_DISABLE | PDL_IIC_SLAVE_GCA_DISABLE | PDL_IIC_DEVICE_ID_DISABLE | PDL_IIC_HOST_ADDRESS_DISABLE,
		0,
		0,
		0,
		( 1 << 31 ) | ( 29 << 8 ) | 29,
		0
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_MasterReceive_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
*
* Function Name: R_PG_I2C_MasterReceive_C1
*
* Description  : �}�X�^�̃f�[�^��M
*
* Arguments    : bool addr_10bit : �X���[�u�A�h���X�t�H�[�}�b�g (1:10�r�b�g  0:7�r�b�g)
*              : uint16_t slave : �X���[�u�A�h���X
*              : uint8_t * data : ��M�����f�[�^�̊i�[��̐擪�̃A�h���X
*              : uint16_t count : ��M����f�[�^��
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_MasterReceive
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_MasterReceive_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
{
	uint16_t addr_size = PDL_NO_DATA;

	if( addr_10bit )
	{
		addr_size = PDL_IIC_10_BIT_SLAVE_ADDRESS;
	}
	
	if( data == 0 )
	{
		return false;
	}

	return R_IIC_MasterReceive(
		1,
		addr_size | PDL_IIC_DMAC_DTC_TRIGGER_DISABLE,
		slave,
		data,
		count,
		PDL_NO_FUNC,
		0
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_MasterSend_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
*
* Function Name: R_PG_I2C_MasterSend_C1
*
* Description  : �}�X�^�̃f�[�^���M
*
* Arguments    : bool addr_10bit : �X���[�u�A�h���X�t�H�[�}�b�g (1:10�r�b�g  0:7�r�b�g)
*              : uint16_t slave : �X���[�u�A�h���X
*              : uint8_t * data : ���M����f�[�^�̊i�[��̐擪�̃A�h���X
*              : uint16_t count : ���M����f�[�^��
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_MasterSend
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_MasterSend_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
{
	uint16_t addr_size = PDL_NO_DATA;

	if( addr_10bit )
	{
		addr_size = PDL_IIC_10_BIT_SLAVE_ADDRESS;
	}
	
	if( data == 0 )
	{
		return false;
	}

	return R_IIC_MasterSend(
		1,
		PDL_IIC_START_ENABLE | PDL_IIC_STOP_ENABLE | addr_size | PDL_IIC_DMAC_DTC_TRIGGER_DISABLE,
		slave,
		data,
		count,
		PDL_NO_FUNC,
		0
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_MasterSendWithoutStop_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
*
* Function Name: R_PG_I2C_MasterSendWithoutStop_C1
*
* Description  : �}�X�^�̃f�[�^���M (STOP��������)
*
* Arguments    : bool addr_10bit : �X���[�u�A�h���X�t�H�[�}�b�g (1:10�r�b�g  0:7�r�b�g)
*              : uint16_t slave : �X���[�u�A�h���X
*              : uint8_t * data : ���M����f�[�^�̊i�[��̐擪�̃A�h���X
*              : uint16_t count : ���M����f�[�^��
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_MasterSend
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_MasterSendWithoutStop_C1(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count)
{
	uint16_t addr_size = PDL_NO_DATA;

	if( addr_10bit )
	{
		addr_size = PDL_IIC_10_BIT_SLAVE_ADDRESS;
	}
	
	if( data == 0 )
	{
		return false;
	}

	return R_IIC_MasterSend(
		1,
		PDL_IIC_START_ENABLE | PDL_IIC_STOP_DISABLE | addr_size | PDL_IIC_DMAC_DTC_TRIGGER_DISABLE,
		slave,
		data,
		count,
		PDL_NO_FUNC,
		0
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_GenerateStopCondition_C1(void)
*
* Function Name: R_PG_I2C_GenerateStopCondition_C1
*
* Description  : �}�X�^��STOP��������
*
* Arguments    : �Ȃ�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_Control
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_GenerateStopCondition_C1(void)
{
	return R_IIC_Control(
		1,
		PDL_IIC_STOP
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_GetBusState_C1(bool * busy)
*
* Function Name: R_PG_I2C_GetBusState_C1
*
* Description  : �o�X��Ԃ̎擾
*
* Arguments    : bool * busy : �o�X�r�W�[���o�t���O�̊i�[��
*
* Return Value : true  : �擾�ɐ��������ꍇ
*              : false : �擾�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_GetStatus
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_GetBusState_C1(bool * busy)
{
	uint32_t data;
	bool res;

	res = R_IIC_GetStatus(
		1,
		&data,
		PDL_NO_PTR,
		PDL_NO_PTR
	);

	if( busy ){ *busy = (data >> 15) & 0x01; }

	return res;
}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_GetEvent_C1(bool * nack, bool * stop, bool * start, bool * lost, bool * timeout)
*
* Function Name: R_PG_I2C_GetEvent_C1
*
* Description  : ���o�C�x���g�̎擾
*
* Arguments    : bool * nack : NACK���o�t���O�i�[��
*              : bool * stop : STOP�������o�t���O�i�[��
*              : bool * start : START�������o�t���O�i�[��
*              : bool * lost : �A�[�r�g���[�V���������X�g���o�t���O�i�[��
*              : bool * timeout : �^�C���A�E�g���o�t���O�i�[��
*
* Return Value : true  : �擾�ɐ��������ꍇ
*              : false : �擾�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_GetStatus
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_GetEvent_C1(bool * nack, bool * stop, bool * start, bool * lost, bool * timeout)
{
	uint32_t data;
	bool res;

	res = R_IIC_GetStatus(
		1,
		&data,
		PDL_NO_PTR,
		PDL_NO_PTR
	);

	if( nack ){
		*nack = (data >> 12) & 0x01;
	}
	if( stop ){
		*stop = (data >> 11) & 0x01;
	}
	if( start ){
		*start = (data >> 10) & 0x01;
	}
	if( lost ){
		*lost = (data >> 9) & 0x01;
	}
	if( timeout ){
		*timeout = (data >> 8) & 0x01;
	}

	return res;
}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_GetReceivedDataCount_C1(uint16_t * count)
*
* Function Name: R_PG_I2C_GetReceivedDataCount_C1
*
* Description  : ��M�ς݃f�[�^���̎擾
*
* Arguments    : uint16_t * count : ��M�f�[�^���̊i�[��
*
* Return Value : true  : �擾�ɐ��������ꍇ
*              : false : �擾�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_GetStatus
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_GetReceivedDataCount_C1(uint16_t * count)
{
	if( count == 0 )
	{
		return false;
	}

	return R_IIC_GetStatus(
		1,
		PDL_NO_PTR,
		PDL_NO_PTR,
		count
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_GetSentDataCount_C1(uint16_t * count)
*
* Function Name: R_PG_I2C_GetSentDataCount_C1
*
* Description  : ���M�ς݃f�[�^���̎擾
*
* Arguments    : uint16_t * count : ���M�f�[�^���̊i�[��
*
* Return Value : true  : �擾�ɐ��������ꍇ
*              : false : �擾�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_GetStatus
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_GetSentDataCount_C1(uint16_t * count)
{
	if( count == 0 )
	{
		return false;
	}

	return R_IIC_GetStatus(
		1,
		PDL_NO_PTR,
		count,
		PDL_NO_PTR
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_Reset_C1(void)
*
* Function Name: R_PG_I2C_Reset_C1
*
* Description  : �o�X�̃��Z�b�g
*
* Arguments    : �Ȃ�
*
* Return Value : true  : �ݒ肪�������s��ꂽ�ꍇ
*              : false : �ݒ�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_Control
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_Reset_C1(void)
{
	return R_IIC_Control(
		1,
		PDL_IIC_RESET
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_I2C_StopModule_C1(void)
*
* Function Name: R_PG_I2C_StopModule_C1
*
* Description  : I2C�o�X�C���^�t�F�[�X�`���l���̒�~
*
* Arguments    : �Ȃ�
*
* Return Value : true  : ��~�ɐ��������ꍇ
*              : false : ��~�Ɏ��s�����ꍇ
*
* Calling Functions : R_IIC_Destroy
*
* Details      : �ڍׂɂ��Ă̓��t�@�����X�}�j���A�����Q�Ƃ��Ă��������B
******************************************************************************/
bool R_PG_I2C_StopModule_C1(void)
{
	return R_IIC_Destroy( 1 );

}



