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

//基本設定
#define ON 		1
#define OFF 		0

//LED
#define LED_0(X)		(PORT1.DR.BIT.B5 = (1 - (X)))
#define LED_1(X)		(PORT8.DR.BIT.B0 = (X))
#define LED_2(X)		(PORT8.DR.BIT.B1 = (X))

//通信
#define MODE_SCIDATA_BOX 		8
#define BITRATE	115200
#define SLAVE_ADDRESS		0x62

	#if MODE_SCIDATA_BOX != OFF
char 	sc1[50],sc2[50],sc3[50],sc4[50],sc5[50],sc6[50],
	sc7[50],sc8[50];
float	g_sci1 = 0.0,g_sci2 = 0.0,g_sci3 = 0.0,g_sci4 = 0.0,
	g_sci5 = 0.0,g_sci6 = 0.0,g_sci7 = 0.0,g_sci8 = 0.0;
	#endif	

unsigned char iic_R_data[30] = {0};
unsigned char iic_S_data = 0;




void Init_Led(void)
{
	PORT8.DDR.BIT.B0 = 1;
	PORT8.DDR.BIT.B1 = 1;
	PORT1.DDR.BIT.B5 = 1;
}


/******************************************************************************
*	タイトル ： sci通信初期化
*	  関数名 ： init_Sci
*	  戻り値 ： void型 
*	    引数 ： なし
******************************************************************************/
void Init_Sci(void)	//SCI1版
{
	int bit_count = 0;
	

	SYSTEM.MSTPCRB.BIT.MSTPB30 = 0;	//SCI1モジュールSTOP状態を解除
	SCI1.SCR.BYTE		= 0x00;		//シリアルコントロールレジスタ
										//河原 0x01→0x00 で通信速度を最大に．分周1
	PORT3.DDR.BIT.B0	= 0;		//
	PORT3.ICR.BIT.B0	= 1;		//
	SCI1.SMR.BYTE		= 0x01;		//シリアルモードレジスタ
	//SCI1.BRR			= 77;		//ビットレートレジスタ77  9600bpsなら0x01の77
									//河原77→12 通信速度を230400bpsに設定
	SCI1.SEMR.BIT.ABCS	= 1;		//調歩同期基本クロックを８サイクルの期間を１ビット期間の転送レートとする
	
	SCI1.BRR = 77;//((48*1000000)/((64/(1+SCI1.SEMR.BIT.ABCS))*powf(2,2*SCI1.SMR.BIT.CKS-1)*BITRATE)-1);
	for( bit_count = 0; bit_count < 0x800000; bit_count++ ){	//１ビット待つため
	}
	SCI1.SCR.BYTE		= 0x30;		//送受信動作を許可
	//#endif
}

/******************************************************************************
*	タイトル ： 文字送信
*	  関数名 ： Transmit_uart_c
*	  戻り値 ： void型 
*	   引数1 ： char型 character  
******************************************************************************/
void Transmit_uart_c(char character)
{
	while(SCI1.SSR.BIT.TDRE == 0);//箱TDRの中にデータが残っていればフラグ=1  出てくまで待つ
	SCI1.TDR=character;//データを書き込み（ライト）
	SCI1.SSR.BIT.TDRE = 0;
	while( SCI1.SSR.BIT.TEND == 0 );
}
/******************************************************************************
*	タイトル ： 文字列を文字送信関数へ送る
*	  関数名 ： String
*	  戻り値 ： void型 
*	   引数1 ： char型 s[]  
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
*	タイトル ： Excel処理のためのデータをシリアル送信
*	  関数名 ： sci_transformer
*	  戻り値 ： void型 
*	    引数 ： なし
*	  作成者 ： 眞下康宏
*	  作成日 ： 2013/02/25
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


void main(void)
{
	int i = 0;
	int send_f = 0;
	unsigned char moji = 0;
		
	Init_Led();
	R_PG_Clock_Set();
	R_PG_I2C_Set_C1();
	Init_Sci();

	while(1){
		LED_0(ON);
		
		if(send_f == 0){
			iic_S_data = 0;
			send_f = 1;
		}
		R_PG_I2C_MasterSend_C1(
		0,//スレーブアドレスフォーマット
		0x31,//スレーブアドレス
		&iic_S_data, //送信データの格納先アドレス
		2//送信データ数
		);
		
		R_PG_I2C_MasterReceive_C1(
		0,//スレーブアドレスフォーマット
		0x31,//スレーブアドレス
		&iic_R_data[i], //受信データの格納先アドレス
		30 //受信データ数
		);
		LED_1(ON);
		
		//sprintf(moji,"  %d\n\r",(int)iic_R_data[i]);
		Transmit_uart_c(iic_R_data[i]);

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
