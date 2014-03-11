/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

#include "iodefine.h"
#include <stdio.h>
#include <math.h>
#include "R_PG_PDG2.h"

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

//��{�ݒ�
#define ON 		1
#define OFF 		0

//LED
#define LED_0(X)		(PORT1.DR.BIT.B5 = (1 - (X)))
#define LED_1(X)		(PORT8.DR.BIT.B0 = (X))
#define LED_2(X)		(PORT8.DR.BIT.B1 = (X))

//�N���R���̃f�[�^�̂��肩
#define MASK_LX         		0x3F    // LX<5:0>
#define MASK_RX34      		0xC0    // RX<4:3>
#define MASK_LY         		0x3F    // LY<5:0>
#define MASK_RY         		0x1F    // RY<4:0>
#define MASK_LT34       		0x60    // LT<4:3>
#define MASK_RT         		0x1F    // RT<4:0>
#define MASK_BDU       		0x01    // DU
#define MASK_RC_DL      		0x02    // DL, RC
#define MASK_BSTART_ZR  	0x04    // ZR, START
#define MASK_BHOME_X    	0x08    // X, HOME
#define MASK_BSELECT_A  	0x10    // A, SELECT
#define MASK_LC_Y       		0x20    // LC, Y, LT<0>
#define MASK_BDD_B      		0x40    // B, DD, LT<1>, RX<1>
#define MASK_BDR_ZL     		0x80    // ZL, DR, LT<2>, RX<0>, RX<2>



//�ʐM
#define SLAVE_ADDRESS_W1			0xA4
#define SLAVE_ADDRESS_R1			0xA5

#define SLAVE_ADDRESS_W2			0x30
#define SLAVE_ADDRESS_R2			0x31

#define SLAVE_ADDRESS_W3			0x42
#define SLAVE_ADDRESS_R3			0x43

#define BITRATE	115200


//�V���A���ʐM
#define MODE_SCIDATA_BOX 		3
#define BLUETOOTH_MODE		OFF

	#if MODE_SCIDATA_BOX != OFF
char 	sc1[50],sc2[50],sc3[50],sc4[50],sc5[50],sc6[50],
	sc7[50],sc8[50],sc9[50],sc10[50],sc11[50],sc12[50],
	sc13[50],sc14[50],sc15[50],sc16[50],sc17[50],sc18[50],
	sc19[50],sc20[50];
float	g_sci1 = 0.0,g_sci2 = 0.0,g_sci3 = 0.0,g_sci4 = 0.0,
	g_sci5 = 0.0,g_sci6 = 0.0,g_sci7 = 0.0,g_sci8 = 0.0,
	g_sci9 = 0.0,g_sci10 = 0.0,g_sci11 = 0.0,g_sci12 = 0.0,
	g_sci13 = 0.0,g_sci14 = 0.0,g_sci15 = 0.0,g_sci16 = 0.0,
	g_sci17 = 0.0,g_sci18 = 0.0,g_sci19 = 0.0,g_sci20 = 0.0;
	#endif

void Init_Led(void)
{
	PORT8.DDR.BIT.B0 = 1;
	PORT8.DDR.BIT.B1 = 1;
	PORT1.DDR.BIT.B5 = 1;
}


/******************************************************************************
*	�^�C�g�� �F sci�ʐM������
*	  �֐��� �F init_Sci
*	  �߂�l �F void�^ 
*	    ���� �F �Ȃ�
******************************************************************************/
void	Init_Sci(void)	//SCI1��
{
	int bit_count = 0;
	
	/*#if BLUETOOTH_MODE == ON
	SYSTEM.MSTPCRB.BIT.MSTPB29 = 0;	//SCI1���W���[��STOP��Ԃ�����
	SCI2.SCR.BYTE		= 0x00;		//�V���A���R���g���[�����W�X�^
										//�͌� 0x01��0x00 �ŒʐM���x���ő�ɁD����1
	PORT1.DDR.BIT.B2	= 0;		//
	PORT1.ICR.BIT.B2	= 1;		//
	PORT1.DDR.BIT.B3 	= 0;	//�ǉ�
	PORT1.ICR.BIT.B3 	= 1;	//�ǉ�
	SCI2.SMR.BYTE		= 0x00;		//�V���A�����[�h���W�X�^
	SCI2.BRR			= 12;		//�r�b�g���[�g���W�X�^77  9600bps�Ȃ�0x01��77
									//�͌�77��12 �ʐM���x��230400bps�ɐݒ�
	SCI2.SEMR.BIT.ABCS	= 1;		//����������{�N���b�N���W�T�C�N���̊��Ԃ��P�r�b�g���Ԃ̓]�����[�g�Ƃ���
	for( bit_count = 0; bit_count < 0x800000; bit_count++ ){	//�P�r�b�g�҂���
	}
	SCI2.SCR.BYTE		= 0x30;		//����M���������
	
	#else*/
	SYSTEM.MSTPCRB.BIT.MSTPB30 = 0;	//SCI1���W���[��STOP��Ԃ�����
	SCI1.SCR.BYTE		= 0x00;		//�V���A���R���g���[�����W�X�^
										//�͌� 0x01��0x00 �ŒʐM���x���ő�ɁD����1
	PORT3.DDR.BIT.B0	= 0;		//
	PORT3.ICR.BIT.B0	= 1;		//
	SCI1.SMR.BYTE		= 0x00;		//�V���A�����[�h���W�X�^
	//SCI1.BRR			= 77;		//�r�b�g���[�g���W�X�^77  9600bps�Ȃ�0x01��77
									//�͌�77��12 �ʐM���x��230400bps�ɐݒ�
	SCI1.SEMR.BIT.ABCS	= 1;		//����������{�N���b�N���W�T�C�N���̊��Ԃ��P�r�b�g���Ԃ̓]�����[�g�Ƃ���
	
	SCI1.BRR = ((48*1000000)/((64/(1+SCI1.SEMR.BIT.ABCS))*powf(2,2*SCI1.SMR.BIT.CKS-1)*BITRATE)-1);
	for( bit_count = 0; bit_count < 0x800000; bit_count++ ){	//�P�r�b�g�҂���
	}
	SCI1.SCR.BYTE		= 0x30;		//����M���������
	//#endif
}

/******************************************************************************
*	�^�C�g�� �F �������M
*	  �֐��� �F Transmit_uart_c
*	  �߂�l �F void�^ 
*	   ����1 �F char�^ character  
******************************************************************************/
void Transmit_uart_c(char character)
{
	while(SCI1.SSR.BIT.TDRE == 0);//��TDR�̒��Ƀf�[�^���c���Ă���΃t���O=1  �o�Ă��܂ő҂�
	SCI1.TDR=character;//�f�[�^���������݁i���C�g�j
	SCI1.SSR.BIT.TDRE = 0;
	while( SCI1.SSR.BIT.TEND == 0 );
}
/******************************************************************************
*	�^�C�g�� �F �������M(P12,P13)
*	  �֐��� �F Transmit_uart_c
*	  �߂�l �F void�^ 
*	   ����1 �F char�^ character  
******************************************************************************/
void Transmit_uart_c_2(char character)
{
	while(SCI2.SSR.BIT.TDRE == 0);//��TDR�̒��Ƀf�[�^���c���Ă���΃t���O=1  �o�Ă��܂ő҂�
		SCI2.TDR=character;//�f�[�^���������݁i���C�g�j
		SCI2.SSR.BIT.TDRE = 0;
	while( SCI2.SSR.BIT.TEND == 0 );
}
/******************************************************************************
*	�^�C�g�� �F ������𕶎����M�֐��֑���
*	  �֐��� �F String
*	  �߂�l �F void�^ 
*	   ����1 �F char�^ s[]  
******************************************************************************/
void String (char s[])
{
	int i=0;
	while(s[i] != '\0')
	{
		#if BLUETOOTH_MODE == ON
		Transmit_uart_c_2(s[i]);
		#else
		Transmit_uart_c(s[i]);
		#endif
		
		i++;
	}
}
/******************************************************************************
*	�^�C�g�� �F p12,p13�ŕ�����𕶎����M�֐��֑���
*	  �֐��� �F String
*	  �߂�l �F void�^ 
*	   ����1 �F char�^ s[]  
******************************************************************************/
void String_2(char s[])
{
	int i=0;
	while(s[i] != '\0')
	{
		Transmit_uart_c_2(s[i]);
		i++;
	}
}
/******************************************************************************
*	�^�C�g�� �Fp12,p13�œ�����M�f�[�^���i�[���Ԃ�
*	  �֐��� �F Receive_uart_c
*	  �߂�l �F char�^
*	    �����F �Ȃ�
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/01/22
******************************************************************************/
char Receive_uart_c(void)
{
	/*while (SCI1.SSR.BIT.RDRF == 0);		//RDRF = 0�FSCRDR �ɗL���Ȏ�M�f�[�^���i�[����Ă��Ȃ����Ƃ�\��
	SCI1.SSR.BIT.RDRF = 0;				//RDRF��ҋ@��ԂɕύX	
	return SCI1.RDR;*/
	while (SCI2.SSR.BIT.RDRF == 0);		//RDRF = 0�FSCRDR �ɗL���Ȏ�M�f�[�^���i�[����Ă��Ȃ����Ƃ�\��
	SCI2.SSR.BIT.RDRF = 0;				//RDRF��ҋ@��ԂɕύX	
	return SCI2.RDR;
}

/******************************************************************************
*	�^�C�g�� �F Excel�����̂��߂̃f�[�^���V���A�����M
*	  �֐��� �F sci_transformer
*	  �߂�l �F void�^ 
*	    ���� �F �Ȃ�
*	  �쐬�� �F �����N�G
*	  �쐬�� �F 2013/02/25
******************************************************************************/
void sci_transformer(void)
{	
	#if MODE_SCIDATA_BOX >= 1
		sprintf(sc1,"%f",(float)g_sci1);
		String(",");
		String(sc1);
	#endif
	#if MODE_SCIDATA_BOX >= 2
		sprintf(sc2,"%f",(float)g_sci2);
		String(",");
		String(sc2);
	#endif
	#if MODE_SCIDATA_BOX >= 3
		sprintf(sc3,"%f",(float)g_sci3);
		String(",");
		String(sc3);
	#endif
	#if MODE_SCIDATA_BOX >= 4
		sprintf(sc4,"%f",(float)g_sci4);
		String(",");
		String(sc4);
	#endif
	#if MODE_SCIDATA_BOX >= 5
		sprintf(sc5,"%f",(float)g_sci5);
		String(",");
		String(sc5);
	#endif
	#if MODE_SCIDATA_BOX >= 6
		sprintf(sc6,"%5d",(long)g_sci6);
		String(",");
		String(sc6);		
	#endif
	#if MODE_SCIDATA_BOX >= 7
		sprintf(sc7,"%5d",(long)g_sci7);
		String(",");
		String(sc7);
	#endif
	#if MODE_SCIDATA_BOX >= 8
		sprintf(sc8,"%5d",(long)g_sci8);
		String(",");
		String(sc8);
	#endif
	#if MODE_SCIDATA_BOX >= 9
		sprintf(sc9,"%5d",(long)g_sci9);
		String(",");
		String(sc9);
	#endif
	#if MODE_SCIDATA_BOX >= 10
		sprintf(sc10,"%5d",(long)g_sci10);
		String(",");
		String(sc10);
	#endif
	#if MODE_SCIDATA_BOX >= 11
		sprintf(sc11,"%5d",(long)g_sci11);
		String(",");
		String(sc11);
	#endif
	#if MODE_SCIDATA_BOX >= 12
		sprintf(sc12,"%5d",(long)g_sci12);
		String(",");
		String(sc12);
	#endif
	#if MODE_SCIDATA_BOX >= 13
		sprintf(sc13,"%5d",(long)g_sci13);
		String(",");
		String(sc13);
	#endif
	#if MODE_SCIDATA_BOX >= 14
		sprintf(sc14,"%5d",(long)g_sci14);
		String(",");
		String(sc14);
	#endif
	#if MODE_SCIDATA_BOX >= 15
		sprintf(sc15,"%5d",(long)g_sci15);
		String(",");
		String(sc15);
	#endif
	#if MODE_SCIDATA_BOX >= 16
		sprintf(sc16,"%5d",(long)g_sci16);
		String(",");
		String(sc16);
	#endif
	#if MODE_SCIDATA_BOX >= 17
		sprintf(sc17,"%5d",(long)g_sci17);
		String(",");
		String(sc17);
	#endif
	#if MODE_SCIDATA_BOX >= 18
		sprintf(sc18,"%5d",(long)g_sci18);
		String(",");
		String(sc18);
	#endif
	#if MODE_SCIDATA_BOX >= 19
		sprintf(sc19,"%5d",(long)g_sci19);
		String(",");
		String(sc19);
	#endif
	#if MODE_SCIDATA_BOX >= 20
		sprintf(sc20,"%5d",(long)g_sci20);
		String(",");
		String(sc20);
	#endif
	String("\n\r");
}

nunchuk_decode_byte (char x)
{
	  x = (x ^ 0x17) + 0x17;
	  return x;
}

void main(void)
{
	int cnt = 0;
	
	volatile 	int 	send_f = 0;
	volatile	int	s_f 	=0 ;
	volatile	int 	sci_f 	= 0;
	volatile 	int 	f 	= 0;
	
	unsigned char format = 0;
		
	unsigned int LjoyX = 0;
	unsigned int LjoyY = 0;
	unsigned int RjoyX = 0;
	unsigned int RjoyY = 0;
	unsigned int buttonY = 0;
	unsigned int buttonX = 0;
	unsigned int buttonB = 0;
	unsigned int buttonA = 0;
	unsigned int buttonLT = 0;
	unsigned int buttonRT = 0;
	unsigned int buttonLC = 0;
	unsigned int buttonRC = 0;
	unsigned int buttonZL = 0;
	unsigned int buttonZR = 0;
	unsigned int buttonSELECT = 0;
	unsigned int buttonHOME = 0;
	unsigned int buttonSTART = 0;
	unsigned int buttonDU = 0;
	unsigned int buttonDD = 0;
	unsigned int buttonDL = 0;
	unsigned int buttonDR = 0;
	unsigned int X_kx = 0;
	unsigned int Y_kx = 0;
	unsigned int Z_kx = 0;
	
	unsigned char cmd_send1[] = {0x40,0x00};
	unsigned char cmd_send2[] = {0x00};
	unsigned char cmd_send3[] = {"A"};
	
	char readBuf_1[] = {0};
	char readBuf_2[] = {0};	
	char readBuf_3[] = {0};
	
	R_PG_Clock_Set();
	Init_Sci();
	Init_Led();
	R_PG_I2C_Set_C1();
	
	while(1){
		
		LED_0(ON);
		
		if( s_f == 0){
			
			R_PG_I2C_MasterSend_C1(
			format,//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_W3,//�X���[�u�A�h���X
			cmd_send3, //���M�f�[�^�̊i�[��A�h���X
			2//���M�f�[�^��
			);
			
		}else if(s_f == 1){	
			/*	
			R_PG_I2C_MasterSend_C1(
			format,//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_R3,//�X���[�u�A�h���X
			cmd_send2, //���M�f�[�^�̊i�[��A�h���X
			1//���M�f�[�^��
			);
			*/
			LED_1(OFF);
			LED_2(ON);
		}else if(s_f == 2){
			R_PG_I2C_MasterReceive_C1(
			format,			//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_R3,		//�X���[�u�A�h���X
			readBuf_3,	//��M�f�[�^�̊i�[��A�h���X
			2//��M�f�[�^��
			);
			LED_1(ON);
			LED_2(OFF);
		}else if(s_f == 3){
			/*R_PG_I2C_MasterSend_C1(
			format,//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_W2,//�X���[�u�A�h���X
			cmd_send2, //���M�f�[�^�̊i�[��A�h���X
			1//���M�f�[�^��
			);
		}else if(s_f == 4){
			R_PG_I2C_MasterReceive_C1(
			format,			//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_R2,		//�X���[�u�A�h���X
			readBuf_2,	//��M�f�[�^�̊i�[��A�h���X
			6//��M�f�[�^��
			);
			*/
		}else{
		}
		

		/*
		for(cnt = 0;cnt < 6;cnt++){
			readBuf_1[cnt] = nunchuk_decode_byte(readBuf_1[cnt]) ;
		}
		
		LjoyX = ((int)readBuf_1[0] & MASK_LX);
		LjoyY = ((int)readBuf_1[1] & MASK_LY);
		RjoyX = ((int)(( readBuf_1[ 2 ] & 0x80 ) >> 7 ) | ( ( readBuf_1[ 1 ] & 0xC0 ) >> 5 ) | ( ( readBuf_1[ 0 ] & 0xC0 ) >> 3 ));
		RjoyY = ((int)readBuf_1[2] & MASK_RY);
		
		buttonSTART = ((int)readBuf_1[4] & MASK_BSTART_ZR) >> 2;
		buttonHOME = ((int)readBuf_1[4] & MASK_BHOME_X) >> 3;
		buttonSELECT = ((int)readBuf_1[4] & MASK_BSELECT_A)>> 4;
		
		buttonDD = ((int)readBuf_1[4] & MASK_BDD_B)>>6;
		buttonDR = ((int)readBuf_1[4] & MASK_BDR_ZL)>>7;
		buttonDU = ((int)readBuf_1[5] & MASK_BDU);
		buttonDL = ((int)readBuf_1[5] & MASK_RC_DL)>>1;
		
		buttonX = ((int)readBuf_1[5] & MASK_BHOME_X) >> 3;
		buttonA = ((int)readBuf_1[5] & MASK_BSELECT_A) >> 4;
		buttonY = ((int)readBuf_1[5] & MASK_LC_Y) >> 5;
		buttonB = ((int)readBuf_1[5] & MASK_BDD_B) >> 6;
		buttonZL = ((int)readBuf_1[5] & MASK_BDR_ZL) >> 7;    
		buttonZR = ((int)readBuf_1[5] & MASK_BSTART_ZR) >> 2;
		buttonRT = (int)(readBuf_1[4] & 0x02) >> 1;		
		buttonLT = (int)(readBuf_1[4] & 0x20 ) >> 5;
		*/
		
		X_kx	= (int)((readBuf_2[0] << 4) + (readBuf_2[1] >> 4));
		Y_kx 	= (int)((readBuf_2[2] << 4) + (readBuf_2[3] >> 4));
		Z_kx	= (int)((readBuf_2[4] << 4) + (readBuf_2[5] >> 4));
		
	
		
		if( (readBuf_3[0] > 0) || (readBuf_3[1] > 0)){
			//�V���A���ʐM
			#if MODE_SCIDATA_BOX != OFF
			//���W�f�[�^
			g_sci1 = (readBuf_3[0] / 10);
			g_sci2 = (readBuf_3[1] / 10);
			g_sci3 = Z_kx;
			/*
			g_sci4 = 0;
			g_sci5 = buttonY;
			g_sci6 = buttonX;
			g_sci7 = buttonB;
			g_sci8 = buttonA;
			g_sci9 = buttonLT;
			g_sci10 = buttonRT;
			g_sci11 = buttonZL;
			g_sci12 = buttonZR;
			g_sci13 = buttonSELECT;
			g_sci14 = buttonHOME;
			g_sci15 = buttonSTART;
			g_sci16 = buttonDU;
			g_sci17 = buttonDD;
			g_sci18 = buttonDL;
			g_sci19 = buttonDR;
	                   */                                                                                                               
			//PC�Ƀf�[�^���M
			sci_transformer();
			#endif
		}
		s_f++;
		
		if(s_f < 0){
			s_f = 0;
		}else if(s_f > 4){
			s_f = 0;
		}
		for(f = 0;f < 100000; f++);
		}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
