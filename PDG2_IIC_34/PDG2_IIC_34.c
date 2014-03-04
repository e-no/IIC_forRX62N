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
#include "R_PG_PDG2.h"

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

//基本設定
#define ON 		1
#define OFF 		0

//LED
#define LED_0(X)		(PORT1.DR.BIT.B5 = (1 - (X)))
#define LED_1(X)		(PORT8.DR.BIT.B0 = (X))
#define LED_2(X)		(PORT8.DR.BIT.B1 = (X))

unsigned int iic_data[30] = {0};

/******************************************************************************
*	タイトル ： LEDにつながっているポートの入出力を許可
*	  関数名 ： init_led
*	  戻り値 ： void型
*	    引数 ： なし
*	  作成者 ： 坂下文彦
*	  作成日 ： 2013/10/14
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
	
	Init_Led();
	R_PG_Clock_Set(); //クロックの設定
	R_PG_I2C_Set_C1(); //RIIC0を設定
	LED_0(ON);
	//マスタ受信
	while(1){
	
		R_PG_I2C_MasterReceive_C1(
		0, //スレーブアドレスフォーマット
		0x31,//スレーブアドレス
		&iic_data, //受信データの格納先アドレス
		50 //受信データ数
		);
		LED_1(ON);
		
				
		LED_2(ON);
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
