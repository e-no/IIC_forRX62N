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
#define BITRATE	115200
#define SLAVE_ADDRESS		0x31

unsigned int iic_data[30] = {0};


void Init_Led(void)
{
	PORT8.DDR.BIT.B0 = 1;
	PORT8.DDR.BIT.B1 = 1;
	PORT1.DDR.BIT.B5 = 1;
}

void main(void)
{
	
	
	Init_Led();
	R_PG_Clock_Set();
	R_PG_I2C_Set_C1();
	
	LED_0(ON);
	R_PG_I2C_MasterReceive_C1(
	0,//�X���[�u�A�h���X�t�H�[�}�b�g
	0x18,//�X���[�u�A�h���X
	&iic_data, //��M�f�[�^�̊i�[��A�h���X
	50 //��M�f�[�^��
	);
	LED_1(ON);
	
	

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
