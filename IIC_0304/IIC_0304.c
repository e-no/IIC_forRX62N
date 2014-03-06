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
#include <math.h>
#include "R_PG_default.h"

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

//�ʐM
#define MODE_SCIDATA_BOX 		8
#define BITRATE_SCI_1   	 9600
#define SLAVE_ADDRESS_W			0xA4
#define SLAVE_ADDRESS_R			0xA5
#define SEND_ADDRESS1				0x00
#define SEND_ADDRESS2				0x40


	/*#if MODE_SCIDATA_BOX != OFF
char 	sc1[50],sc2[50],sc3[50],sc4[50],sc5[50],sc6[50],
	sc7[50],sc8[50];
float	g_sci1 = 0.0,g_sci2 = 0.0,g_sci3 = 0.0,g_sci4 = 0.0,
	g_sci5 = 0.0,g_sci6 = 0.0,g_sci7 = 0.0,g_sci8 = 0.0;
	#endif	
*/
char 	iic_R_data[20] = {0};
char 	iic_S_data[3] = {SEND_ADDRESS1,SEND_ADDRESS2};

void Init_Sci(void)
{
	int a = 0;
	
	MSTP(SCI1) = 0;	//���W���[���X�g�b�v���� �ȗ���
	//iodefine�̍ŏ��̕����ɋL�ڂ���Ă���
	
	//SCR.TIE, RIE, TE, RE, TEIE�r�b�g���g0�h�ɂ���
	SCI1.SCR.BIT.TIE = 0;
	SCI1.SCR.BIT.RIE = 0;
	SCI1.SCR.BIT.TE = 0;
	SCI1.SCR.BIT.RE = 0;
	SCI1.SCR.BIT.TEIE = 0;
	
	//PORTi.ICR.Bj�r�b�g���g1�h�ɂ���
	PORT3.DDR.BIT.B0 = 0;
	PORT3.ICR.BIT.B0 = 1;
	
	//SCR.CKE[1:0]�r�b�g��ݒ�
	SCI1.SCR.BIT.CKE = 0;
	
	//SMR�ASCMR�ɑ��M�^��M�t�H�[�}�b�g��ݒ�
	SCI1.SMR.BIT.CKS = 1;
	SCI1.SCMR.BIT.SMIF = 0;
	
	//BRR�ɒl������
	SCI1.BRR = 19;
	
	//1�r�b�g�҂�
	for(a = 0; a < 10000 ; a++){
	}
	
	//SCR.TE,RE�r�b�g���g1�h�ɂ����SCR.TIE,RIETEIE�r�b�g��ݒ�
	SCI1.SCR.BIT.TE = 1;
	SCI1.SCR.BIT.RE = 1;
	SCI1.SCR.BIT.TIE = 1;
	SCI1.SCR.BIT.RIE = 1;
	SCI1.SCR.BIT.TEIE = 1;
}


/******************************************************************************
*	�^�C�g�� �F �N���b�N���������[�h 1�������M
*	  �֐��� �F transmit_c_Serial_clock
*	  �߂�l �F void�^ 
*	   ����1 �F long�^ data  
*	  �쐬�� �F �^���N�G
*	  �쐬�� �F 2012/09/12
******************************************************************************/
void transmit_c_Serial_clock(long data)
{
	//���M�f�[�^�G���v�e�B�t���O��1�ɂȂ�܂ő҂�
	while(SCI1.SSR.BIT.TDRE != 1){
	}
	
	SCI1.TDR = data;
	
	SCI1.SCR.BIT.TIE = 0;
	
	//SSR.TEND�t���O��ǂݏo��
	while(SCI1.SSR.BIT.TEND != 1){
	}
	
}

/******************************************************************************
*	�^�C�g�� �F �N���b�N���������[�h �����񑗐M
*	  �֐��� �F transmit_s_Serial_clock
*	  �߂�l �F void�^ 
*	   ����1 �F char�^ s[]  
*	  �쐬�� �F �^���N�G
*	  �쐬�� �F 2012/09/12
******************************************************************************/
void transmit_s_Serial_clock(char s[])
{
	int x = 0;
	
	while(s[x]!='\0'){
		transmit_c_Serial_clock(s[x]);
		x++;
	}
	transmit_c_Serial_clock('\0');
}

void Init_Led(void)
{
	PORT8.DDR.BIT.B0 = 1;
	PORT8.DDR.BIT.B1 = 1;
	PORT1.DDR.BIT.B5 = 1;
}

void main(void)
{
	int i = 0;
	unsigned char cmd_send1[] = {0x40,0x00};
	unsigned char cmd_send2[] = {0x00};
	int send_f = 0;
	int f = 0;
	unsigned char format = 0;
		
	Init_Led();
	R_PG_Clock_Set();
	R_PG_I2C_Set_C1();
	Init_Sci();

	while(1){
		LED_0(ON);

	
		
			R_PG_I2C_MasterSend_C1(
			format,//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_W,//�X���[�u�A�h���X
			&cmd_send1[0], //���M�f�[�^�̊i�[��A�h���X
			2//���M�f�[�^��
			);
			send_f++;
		
			R_PG_I2C_MasterSend_C1(
			format,//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_W,//�X���[�u�A�h���X
			&cmd_send2[0], //���M�f�[�^�̊i�[��A�h���X
			1//���M�f�[�^��
			);
			send_f++;

			
			R_PG_I2C_MasterReceive_C1(
			format,			//�X���[�u�A�h���X�t�H�[�}�b�g
			SLAVE_ADDRESS_R,		//�X���[�u�A�h���X
			&iic_R_data[i],	//��M�f�[�^�̊i�[��A�h���X
			10 			//��M�f�[�^��
			);
		
			
		LED_1(ON);

		 transmit_s_Serial_clock(iic_R_data[i]);
		 
		LED_2(ON);
		i++;
		if(i == 20){
			i = 0;
		}
			
		}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
