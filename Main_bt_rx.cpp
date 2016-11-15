/*
 * H28_BT_RX_2.cpp
 *
 * Created: 2016/10/28
 * Author : sn
 */ 

//このプログラムを使用する際には、フォルダincludeにDirectriesを設定してください。

//#define __MODE_DEBUG_REAL__ 1
//対となるROBOBA_TX回路でこのプログラムを動かすとき、コメントアウトを解除してください

#include "Func_bt_rx.h"

//LED0 -> 初期設定完了
//LED1 -> Bluetooth確認
//LED2 -> Masterとの接続完了
//LED3 -> Link Lost からの復帰中

/************************************************************************/

ISR(TIMER1_OVF_vect)
{	
	cli();
	
	const T_DATA_8 _temp_data[__BT_DATA_NUM__] = {0x3f,0x7f,0x8f,0xc0};
	
	for (usint i = 0; i < BT_DATA_NUM; i++)
	{
		F_Uart_out_8(EU_UART0, _temp_data[i]);
		
		_delay_us(20);
	}
	
	sei();
}

/************************************************************************/

int main(void)
{
	/************************************************************************/
	//初期設定
	
	C_UART_T _uart_t_main(EU_UART0);
	
	F_Set_io_bt_rx_2();
	
	F_Set_uart_bt_rx_2();
	
	F_Set_timer_bt_rx_2();
	
	__LED0_ON__;
	
	/************************************************************************/
	
	/************************************************************************/
	//接続
	
	char _data_in[40] = {};
	
	E_BT_NUM _num_master = EB_BT0;
	
	BOOL _flag_success = FALSE;
	
	do 
	{
		_flag_success = F_In_bt_num_bt_rx_2(_num_master);
		
		if (_flag_success == FALSE)
		{
			static uint i = 0;
			
			if (i < 35000)	{	__LED0_ON__;	__LED1_ON__;	__LED2_ON__;	__LED3_ON__;	}
			else			{	__LED0_OFF__;	__LED1_OFF__;	__LED2_OFF__;	__LED3_OFF__;	}
			
			i ++;
			
			if (i == 120000)	i = 0;
		}
	}
	while (_flag_success == FALSE);
	
	__LED0_ON__;	__LED1_OFF__;	__LED2_OFF__;	__LED3_OFF__;
	
	sei();
	
	F_In_comp_bt_rx_2(_data_in, "\r\nOK\r\n");

	__LED1_ON__;
	
	F_Conect_bt_rx_2(_num_master); //Masterとの接続
	
	__LED2_ON__;
	
	__LINK_HIGH__;
	
	/************************************************************************/
	
	while (1)
	{		
		/************************************************************************/
		//データの転送
		
		F_Set_timer_bt_rx_2();
		
		F_In_bt_rx_2(_data_in);
		
		if 
		(		F_Str_comp("\r\n+LIN", _data_in)	//F_Str_comp("\r\n+LINK_LOST=", _data_in) 
			|	F_Str_comp("\r\n+DIS", _data_in)	//F_Str_comp("\r\n+DISCONNECTED=", _data_in)
			|	F_Str_comp("+LINK_LO", _data_in)	//F_Str_comp("+LINK_LOST=", _data_in)
		)
		{
			/************************************************************************/
			//接続断絶
			
			__LED1_OFF__;	__LED2_OFF__;	__LED3_ON__;
			
			__LINK_LOW__;
			
			F_BT_Cut(); //コマンドモードに復帰
			
			F_In_comp_bt_rx_2(_data_in, "\r\nOK\r\n");
			
			__LED1_ON__;
			
			F_Conect_bt_rx_2(_num_master);
			
			__LED2_ON__;
			
			__LED3_OFF__;
			
			__LINK_HIGH__;
			
			/************************************************************************/
		}
		else
		{
			/************************************************************************/
			//通常
			
			F_Out_main_bt_rx_2(_uart_t_main, _data_in);
			
			/************************************************************************/
		}
		
		/************************************************************************/
	}
}