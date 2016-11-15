
#pragma once

#include "Func_bt_rx.h"

inline void
F_Set_io_bt_rx_2 ()
{
	
#if defined(__MODE_DEBUG_REAL__)
	
	DDRA  = 0x00;
	PORTA = (__SW1_BIT__ | __SW2_BIT__ | __SW3_BIT__ | __SW4_BIT__ | __SW5_BIT__ | __SW6_BIT__ | __SW7_BIT__);
	DDRB  = (__LED0_BIT__ | __LED1_BIT__ | __LED2_BIT__);
	PORTB = 0x00;
	DDRC  = __LED3_BIT__;
	PORTC = 0x00;
	DDRD  = (__CTS_BIT__ | __RSE_BIT__);
	PORTD = (__CTS_BIT__ | __RSE_BIT__ | __SW0_BIT__);
	
	INI_LCD();

#	if __SW_NATU__ == __EVEN__
	
	Lcd_put_str(0x00, "Slave ver.2 Even");
	
#	elif __SW_NATU__ == __ODD__
	
	Lcd_put_str(0x00, "Slave ver.2 Odd ");
	
#	endif

#else
	
	DDRA  = __LINK_BIT__;
	PORTA = 0x00;
	DDRB  = (__LED0_BIT__ | __LED1_BIT__ | __LED2_BIT__ | __LED3_BIT__);
	PORTB = 0x00;
	DDRC  = 0x00;
	PORTC = (__SW0_BIT__ | __SW1_BIT__ | __SW2_BIT__ | __SW3_BIT__ | __SW4_BIT__ | __SW5_BIT__ | __SW6_BIT__ | __SW7_BIT__);
	DDRD  = (__CTS_BIT__ | __RSE_BIT__);
	PORTD = (__CTS_BIT__ | __RSE_BIT__);
	
#endif

}

inline void
F_Set_uart_bt_rx_2 ()
{	
	//115.2kbps double-on parity-off
	//rec,tra-mode 8bit interrupt-off
	
	UBRR1H = 0x00;
	UBRR1L = 0x0a;
	UCSR1A = (1 << U2X);
	UCSR1B = ((1 << RXEN) | (1 << TXEN));
	UCSR1C = ((1 << UCSZ0) | (1 << UCSZ1));
}

inline void
F_Set_timer_bt_rx_2 ()
{
	
#ifndef __MODE_DEBUG_REAL__

	TCCR1A = 0;
	TIMSK1 = (1 << TOIE1);					//溢れ
	TCNT1  = 64560;							//0.1s
	TCCR1B = ((1 << CS12) | (1 << CS10));	//1024
	
#endif

}

inline void
F_Out_bt_rx_2 (const char _arg_data_out[])
{
	F_BT_Out(__UART_BLUETOOTH__, _arg_data_out);
}

inline void
F_In_bt_rx_2 (char _arg_re_data_in[])
{
	F_BT_In(__UART_BLUETOOTH__, _arg_re_data_in);
}

inline void
F_In_comp_bt_rx_2 (const char _arg_data_comp[])
{
	F_BT_In_comp(__UART_BLUETOOTH__, _arg_data_comp);
}

inline void
F_In_comp_bt_rx_2
(
	char		_arg_re_data_in[],
	const char	_arg_data_comp[]
)
{
	F_BT_In_comp(__UART_BLUETOOTH__, _arg_re_data_in, _arg_data_comp);
}

inline void
F_Out_main_bt_rx_2 (C_UART_T &_arg_uart_t , const char _arg_data_out[])
{
	
#if defined(__MODE_DEBUG_REAL__)

	Lcd_put_str(0x40, _arg_data_out);

#else
	
	T_DATA_8 _out_data[__BT_DATA_NUM__] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	for (usint i = 0; i < __BT_DATA_NUM__; i++)
	{		
		if (_arg_data_out[i * 2 + 0] <= 0x39)
		{
			_out_data[i]  = (((_arg_data_out[i * 2 + 0] & 0x0f) + 0) << 4);
		}
		else
		{
			_out_data[i]  = (((_arg_data_out[i * 2 + 0] & 0x0f) + 9) << 4);
		}
		
		if (_arg_data_out[i * 2 + 1] <= 0x39)
		{
			_out_data[i] |= (((_arg_data_out[i * 2 + 1] & 0x0f) + 0) << 0);
		}
		else
		{
			_out_data[i] |= (((_arg_data_out[i * 2 + 1] & 0x0f) + 9) << 0);
		}
	}
	
	for (usint i = 0; i < __BT_DATA_NUM__; i++)
	{		
		_arg_uart_t.Out(_out_data[i]);
		
		_delay_us(20);
	}
	
#endif
		
}

inline BOOL
F_In_bt_num_bt_rx_2 (E_BT_NUM &_arg_re_bt_master_num)
{
	switch (__SW_READ__)
	{
		case 0xfe:	_arg_re_bt_master_num = EB_BT0;	break;
		case 0x01:	_arg_re_bt_master_num = EB_BT1;	break;
		case 0xfd:	_arg_re_bt_master_num = EB_BT2;	break;
		case 0x02:	_arg_re_bt_master_num = EB_BT3;	break;
		case 0xfb:	_arg_re_bt_master_num = EB_BT4;	break;
		case 0x04:	_arg_re_bt_master_num = EB_BT5;	break;
		case 0xf7:	_arg_re_bt_master_num = EB_BT6;	break;
		case 0x08:	_arg_re_bt_master_num = EB_BT7;	break;
		case 0xef:	_arg_re_bt_master_num = EB_BT8;	break;
		case 0x10:	_arg_re_bt_master_num = EB_BT9;	break;
		case 0xdf:	_arg_re_bt_master_num = EB_BTA;	break;
		case 0x20:	_arg_re_bt_master_num = EB_BTB;	break;
		case 0xbf:	_arg_re_bt_master_num = EB_BTC;	break;
		case 0x40:	_arg_re_bt_master_num = EB_BTD;	break;
		case 0x7f:	_arg_re_bt_master_num = EB_BTE;	break;
		case 0x80:	_arg_re_bt_master_num = EB_BTF;	break;
		
		default:
		{

#ifdef __MODE_DEBUG_REAL__
			
			Lcd_put_str(0x40, "Select Master  ")

#endif
			
			return FALSE;
		}
	}
	
	return TRUE;
}

inline void
F_Conect_bt_rx_2 (const E_BT_NUM _arg_master_num)
{
	char _master_addr[__BT_ADDR_BYTE__] = {};
	
	char _CONNECTING_[33] = "\r\n+CONNECTING=000190xxxxxx\r\n";
	char _CONNECTED_[32]  = "\r\n+CONNECTED=000190xxxxxx\r\n";
	
	switch (_arg_master_num)
	{
		case EB_BT0:	F_Str_copy(_master_addr, "000190EAD4B5"); break;
		case EB_BT1:	F_Str_copy(_master_addr, "000190EAD491"); break;
		case EB_BT2:	F_Str_copy(_master_addr, "000190E53F09"); break;
		case EB_BT3:	F_Str_copy(_master_addr, "000190EAD491"); break;
		case EB_BT4:	F_Str_copy(_master_addr, "000190EAD49A"); break;
		case EB_BT5:	F_Str_copy(_master_addr, "000190E53A7B"); break;
		case EB_BT6:	F_Str_copy(_master_addr, "000190EB1273"); break;
		case EB_BT7:	F_Str_copy(_master_addr, "000190EB1416"); break;
		case EB_BT8:	F_Str_copy(_master_addr, "000190EB105D"); break;
		case EB_BT9:	F_Str_copy(_master_addr, "000190EB1057"); break;
		case EB_BTA:	F_Str_copy(_master_addr, "000190EB105A"); break;
		case EB_BTB:	F_Str_copy(_master_addr, "000190EB1052"); break;
		case EB_BTC:	F_Str_copy(_master_addr, "000190EB1050"); break;
		case EB_BTD:	F_Str_copy(_master_addr, "000190EB105C"); break;
		case EB_BTE:	F_Str_copy(_master_addr, "000190EB104F"); break;
		case EB_BTF:	F_Str_copy(_master_addr, "000190EB104E"); break;
	}
	
	for (usint i = 0; i < __BT_ADDR_BYTE__; i++)
	{
		_CONNECTING_[14 + i] = _master_addr[i];
		_CONNECTED_[13 + i]  = _master_addr[i];
	}
	
#ifdef __MODE_DEBUG_REAL__

	Lcd_put_str(0x40, "Connecting_     ");
	Lcd_put_num(0x4b, _arg_master_num+ 1, 2, ED_10);

#endif
	
	char _data_in[40] = {};
	
	F_Out_bt_rx_2("AT+CONSLAVE=1,0\r\n");
	
	F_In_comp_bt_rx_2(_data_in, "\r\nACK\r\n");
	
	F_In_comp_bt_rx_2(_data_in, _CONNECTING_);
	
	F_In_comp_bt_rx_2(_data_in, "\r\n+ACCEPT?\r\n");
	
	Go_start_connect:
	
	F_Out_bt_rx_2("AT+RESCON=1\r\n");
	
	do
	{
		F_In_bt_rx_2(_data_in);
		
		if (F_Str_comp("\r\nTIMEOUT\r\n", _data_in))
		{
			goto Go_start_connect;
		}
	}
	while (F_Str_comp(_CONNECTED_, _data_in) != TRUE);
	
	F_In_comp_bt_rx_2(_data_in, "\r\nOK\r\n");
	
#ifdef __MODE_DEBUG_REAL__

	Lcd_put_str(0x40, LCD_SEMI_CLEAR);

#endif
	
}
