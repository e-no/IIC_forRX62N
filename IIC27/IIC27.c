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
#include "stdio.h"
#include "math.h"
#include "R_PG_PDG.h"

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

//�ʐM�֘A
#define MODE_SCIDATA_BOX 		8
#define BITRATE	115200
#define SLAVE_ADDRESS		0x31

	#if MODE_SCIDATA_BOX != OFF
char 	sc1[50],sc2[50],sc3[50],sc4[50],sc5[50],sc6[50],
	sc7[50],sc8[50];
float	g_sci1 = 0.0,g_sci2 = 0.0,g_sci3 = 0.0,g_sci4 = 0.0,
	g_sci5 = 0.0,g_sci6 = 0.0,g_sci7 = 0.0,g_sci8 = 0.0;
	#endif	

unsigned char iic_data[50] = {0};



/******************************************************************************
*	�^�C�g�� �F sci�ʐM������
*	  �֐��� �F init_Sci
*	  �߂�l �F void�^ 
*	    ���� �F �Ȃ�
******************************************************************************/
void Init_Sci(void)	//SCI1��
{
	int bit_count = 0;
	

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
		Transmit_uart_c(s[i]);		
		i++;
	}
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
	
	String("\n\r");
}

/******************************************************************************
*	�^�C�g�� �F LED�ɂȂ����Ă���|�[�g�̓��o�͂�����
*	  �֐��� �F init_led
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2013/10/14
******************************************************************************/
void Init_Led(void)
{
	PORT8.DDR.BIT.B0 = 1;
	PORT8.DDR.BIT.B1 = 1;
	PORT1.DDR.BIT.B5 = 1;
}
void main(void)
{
	int i = 0;
	char moji[50] = {0};
	
	Init_Led();
	Init_Sci();
	R_PG_Clock_Set(); //�N���b�N�̐ݒ�
	R_PG_I2C_Set_C1(); //RIIC0��ݒ�
	LED_0(ON);
	//�}�X�^��M
	while(1){
	
		R_PG_I2C_MasterReceive_C1(
		//�X���[�u�A�h���X�t�H�[�}�b�g
		SLAVE_ADDRESS,//�X���[�u�A�h���X
		&iic_data, //��M�f�[�^�̊i�[��A�h���X
		50 //��M�f�[�^��
		);
		LED_1(ON);
		
		sprintf(moji,"  %d\n\r",(int)iic_data);
		Transmit_uart_c(moji);
		
		LED_2(ON);
		i++;
		if(i == 21)i = 0;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
