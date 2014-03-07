
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

//基本設定
#define ON 		1
#define OFF 		0

//LED
#define LED_0(X)		(PORT1.DR.BIT.B5 = (1 - (X)))
#define LED_1(X)		(PORT8.DR.BIT.B0 = (X))
#define LED_2(X)		(PORT8.DR.BIT.B1 = (X))

//通信
#define SLAVE_ADDRESS_W			0xA4
#define SLAVE_ADDRESS_R			0xA5
#define SEND_ADDRESS1				0x00
#define SEND_ADDRESS2				0x40
#define BITRATE	115200

//シリアル通信
#define MODE_SCIDATA_BOX 		7
#define BLUETOOTH_MODE		OFF

	#if MODE_SCIDATA_BOX != OFF
char 	sc1[50],sc2[50],sc3[50],sc4[50],sc5[50],sc6[50],
	sc7[50],sc8[50];
float	g_sci1 = 0.0,g_sci2 = 0.0,g_sci3 = 0.0,g_sci4 = 0.0,
	g_sci5 = 0.0,g_sci6 = 0.0,g_sci7 = 0.0,g_sci8 = 0.0;
	#endif

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
void	Init_Sci(void)	//SCI1版
{
	int bit_count = 0;
	
	/*#if BLUETOOTH_MODE == ON
	SYSTEM.MSTPCRB.BIT.MSTPB29 = 0;	//SCI1モジュールSTOP状態を解除
	SCI2.SCR.BYTE		= 0x00;		//シリアルコントロールレジスタ
										//河原 0x01→0x00 で通信速度を最大に．分周1
	PORT1.DDR.BIT.B2	= 0;		//
	PORT1.ICR.BIT.B2	= 1;		//
	PORT1.DDR.BIT.B3 	= 0;	//追加
	PORT1.ICR.BIT.B3 	= 1;	//追加
	SCI2.SMR.BYTE		= 0x00;		//シリアルモードレジスタ
	SCI2.BRR			= 12;		//ビットレートレジスタ77  9600bpsなら0x01の77
									//河原77→12 通信速度を230400bpsに設定
	SCI2.SEMR.BIT.ABCS	= 1;		//調歩同期基本クロックを８サイクルの期間を１ビット期間の転送レートとする
	for( bit_count = 0; bit_count < 0x800000; bit_count++ ){	//１ビット待つため
	}
	SCI2.SCR.BYTE		= 0x30;		//送受信動作を許可
	
	#else*/
	SYSTEM.MSTPCRB.BIT.MSTPB30 = 0;	//SCI1モジュールSTOP状態を解除
	SCI1.SCR.BYTE		= 0x00;		//シリアルコントロールレジスタ
										//河原 0x01→0x00 で通信速度を最大に．分周1
	PORT3.DDR.BIT.B0	= 0;		//
	PORT3.ICR.BIT.B0	= 1;		//
	SCI1.SMR.BYTE		= 0x00;		//シリアルモードレジスタ
	//SCI1.BRR			= 77;		//ビットレートレジスタ77  9600bpsなら0x01の77
									//河原77→12 通信速度を230400bpsに設定
	SCI1.SEMR.BIT.ABCS	= 1;		//調歩同期基本クロックを８サイクルの期間を１ビット期間の転送レートとする
	
	SCI1.BRR = ((48*1000000)/((64/(1+SCI1.SEMR.BIT.ABCS))*powf(2,2*SCI1.SMR.BIT.CKS-1)*BITRATE)-1);
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
*	タイトル ： 文字送信(P12,P13)
*	  関数名 ： Transmit_uart_c
*	  戻り値 ： void型 
*	   引数1 ： char型 character  
******************************************************************************/
void Transmit_uart_c_2(char character)
{
	while(SCI2.SSR.BIT.TDRE == 0);//箱TDRの中にデータが残っていればフラグ=1  出てくまで待つ
		SCI2.TDR=character;//データを書き込み（ライト）
		SCI2.SSR.BIT.TDRE = 0;
	while( SCI2.SSR.BIT.TEND == 0 );
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
		#if BLUETOOTH_MODE == ON
		Transmit_uart_c_2(s[i]);
		#else
		Transmit_uart_c(s[i]);
		#endif
		
		i++;
	}
}
/******************************************************************************
*	タイトル ： p12,p13で文字列を文字送信関数へ送る
*	  関数名 ： String
*	  戻り値 ： void型 
*	   引数1 ： char型 s[]  
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
*	タイトル ：p12,p13で得た受信データを格納し返す
*	  関数名 ： Receive_uart_c
*	  戻り値 ： char型
*	    引数： なし
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/01/22
******************************************************************************/
char Receive_uart_c(void)
{
	/*while (SCI1.SSR.BIT.RDRF == 0);		//RDRF = 0：SCRDR に有効な受信データが格納されていないことを表示
	SCI1.SSR.BIT.RDRF = 0;				//RDRFを待機状態に変更	
	return SCI1.RDR;*/
	while (SCI2.SSR.BIT.RDRF == 0);		//RDRF = 0：SCRDR に有効な受信データが格納されていないことを表示
	SCI2.SSR.BIT.RDRF = 0;				//RDRFを待機状態に変更	
	return SCI2.RDR;
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



nunchuk_decode_byte (char x)
{
	  x = (x ^ 0x17) + 0x17;
	  return x;
}

void main(void)
{
	int cnt = 0;
	unsigned char cmd_send1[] = {0x40,0x00};
	unsigned char cmd_send2[] = {0x00};
	volatile 	int send_f = 0;
	volatile	int	s_f =0 ;
	volatile	int 	sci_f = 0;
	volatile 	int f = 0;
	char moji[50] = {0}; 	
	char moji_null[] = {0};
	uint16_t count[] = {0};
	uint16_t count_null[] = {0};
	unsigned char format = 0;
	
	unsigned char joy_x_axis = 0;
	unsigned char joy_y_axis = 0;
	int accel_x_axis = 0;
	int accel_y_axis = 0;
	int accel_z_axis = 0;
	unsigned char z_button = 0;
	unsigned char c_button = 0;
	char buffer[] = {0};
	
	Init_Sci();
	Init_Led();
	R_PG_Clock_Set();
	R_PG_I2C_Set_C1();
	
	while(1){
		
		LED_0(ON);
		
		R_PG_I2C_MasterSend_C1(
		format,//スレーブアドレスフォーマット
		SLAVE_ADDRESS_W,//スレーブアドレス
		cmd_send1, //送信データの格納先アドレス
		2//送信データ数
		);
		
		for(f = 0;f < 10000; f++);
	
		R_PG_I2C_MasterSend_C1(
		format,//スレーブアドレスフォーマット
		SLAVE_ADDRESS_W,//スレーブアドレス
		cmd_send2, //送信データの格納先アドレス
		1//送信データ数
		);
		
		for(f = 0;f < 10000; f++);
		
		R_PG_I2C_MasterReceive_C1(
		format,			//スレーブアドレスフォーマット
		SLAVE_ADDRESS_R,		//スレーブアドレス
		buffer,	//受信データの格納先アドレス
		7//受信データ数
		);
		
		for(cnt = 0;cnt < 8;cnt++){
			buffer[cnt] = nunchuk_decode_byte(buffer[cnt]) ;
		}
		
		LED_1(ON);
		
		joy_x_axis = buffer[0];
		joy_y_axis = buffer[1];
		accel_x_axis = (buffer[2]) << 2;
		accel_y_axis = (buffer[3]) << 2;
		accel_z_axis = (buffer[4]) << 2;
		
		if ((buffer[5] & 0x01) != 0){
			z_button = 1; 
		}else{
			z_button = 0; 
		}
		if ((buffer[5] & 0x02) != 0){
			c_button = 1; 
		}else{
			c_button = 0; 
		}
		accel_x_axis += ((buffer[5]) >> 2) & 0x03;
		accel_y_axis += ((buffer[5]) >> 4) & 0x03;
		accel_z_axis += ((buffer[5]) >> 6) & 0x03;
		
	
		
		
		
		//シリアル通信
		#if MODE_SCIDATA_BOX != OFF
		//座標データ
		g_sci1 = joy_x_axis;
		g_sci2 = joy_y_axis;
		g_sci3 = accel_x_axis;
		g_sci4 = accel_y_axis;
		g_sci5 = accel_z_axis;
		g_sci6 = c_button;
		g_sci7 = z_button;
		//PCにデータ送信
		sci_transformer();
		#endif
		LED_2(ON);
					
		}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
