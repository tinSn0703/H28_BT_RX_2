
#pragma once

#define __CTS__ EI_IO4
#define __RTS__ EI_IO5
#define __RSE__ EI_IO6

/************************************************************************/

#include <H28_BT/H28_BT.h>
#include <H28_OTHERS/H28_C_COUNT.h>

#ifdef __MODE_DEBUG_REAL__
#	include <FallMoon/akilcd_tx.h>
#endif

/************************************************************************/

#define __EVEN__ 0
#define __ODD__  1

#define __SW_NATU__ __ODD__

#define __UART_BLUETOOTH__ EU_UART1

#if defined(__MODE_DEBUG_REAL__)

#	define __LED0_BIT__ (1 << PB0)
#	define __LED1_BIT__ (1 << PB1)
#	define __LED2_BIT__ (1 << PB2)
#	define __LED3_BIT__ (1 << PC6)

#	define __LED0_ON__ PORTB |= __LED0_BIT__
#	define __LED1_ON__ PORTB |= __LED1_BIT__
#	define __LED2_ON__ PORTB |= __LED2_BIT__
#	define __LED3_ON__ PORTC |= __LED3_BIT__

#	define __LED0_OFF__ PORTB &= ~__LED0_BIT__
#	define __LED1_OFF__ PORTB &= ~__LED1_BIT__
#	define __LED2_OFF__ PORTB &= ~__LED2_BIT__
#	define __LED3_OFF__ PORTC &= ~__LED3_BIT__

#	define __SW0_BIT__ (1 << PD1)
#	define __SW1_BIT__ (1 << PA1)
#	define __SW2_BIT__ (1 << PA2)
#	define __SW3_BIT__ (1 << PA3)
#	define __SW4_BIT__ (1 << PA4)
#	define __SW5_BIT__ (1 << PA5)
#	define __SW6_BIT__ (1 << PA6)
#	define __SW7_BIT__ (1 << PA7)

#	if __SW_NATU__ == __EVEN__

#		define __SW_READ__ ((~((PINA & 0xfe) | ((PIND >> 1) & 1))) & 0xff)

#	elif __SW_NATU__ == __ODD__

#		define __SW_READ__ ((((PINA & 0xfe) | ((PIND >> 1) & 1))) & 0xff)

#	endif

#else

#	if	 (__SW_NATU__ == __EVEN__)
#		define __LED0_BIT__ (1 << PB0)
#		define __LED1_BIT__ (1 << PB1)
#	elif (__SW_NATU__ == __ODD__)
#		define __LED0_BIT__ (1 << PB1)
#		define __LED1_BIT__ (1 << PB0)
#	endif

#	define __LED2_BIT__ (1 << PB2)
#	define __LED3_BIT__ (1 << PB3)

#	define __LED0_ON__ (PORTB |= __LED0_BIT__)
#	define __LED1_ON__ (PORTB |= __LED1_BIT__)
#	define __LED2_ON__ (PORTB |= __LED2_BIT__)
#	define __LED3_ON__ (PORTB |= __LED3_BIT__)

#	define __LED0_OFF__ (PORTB &= ~__LED0_BIT__)
#	define __LED1_OFF__ (PORTB &= ~__LED1_BIT__)
#	define __LED2_OFF__ (PORTB &= ~__LED2_BIT__)
#	define __LED3_OFF__ (PORTB &= ~__LED3_BIT__)

#	define __SW0_BIT__ (1 << PC0)
#	define __SW1_BIT__ (1 << PC1)
#	define __SW2_BIT__ (1 << PC2)
#	define __SW3_BIT__ (1 << PC3)
#	define __SW4_BIT__ (1 << PC4)
#	define __SW5_BIT__ (1 << PC5)
#	define __SW6_BIT__ (1 << PC6)
#	define __SW7_BIT__ (1 << PC7)

#	if   (__SW_NATU__ == __EVEN__)
#		define __SW_READ__ ((~PINC) & 0xff)
#	elif (__SW_NATU__ == __ODD__)
#		define __SW_READ__ ((PINC) & 0xff)
#	endif

#	define __LINK_BIT__ (1 << PA0)

#	define __LINK_READ__ ((BOOL)((PINA >> PA0) & 1))

#	define __LINK_HIGH__ (PORTA |=  __LINK_BIT__)
#	define __LINK_LOW__  (PORTA &= ~__LINK_BIT__)

#endif

/************************************************************************/

/** Made 2016 / 10 / 28 (Fri)
 * \brief
 *	IOレジスタの設定を行う
 */
void F_Set_io_bt_rx_2 ();

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetoothに使用するUARTを設定する。UART1。
 */
void F_Set_uart_bt_rx_2 ();

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 * Timerの設定を行う。Timer1。溢れ。割り込み許可。0.05[s]
 */
void F_Set_timer_bt_rx_2 ();

/**
 * \brief 2016 / 11 / 01 (Thu)
 *	Masterの番号をDIPスイッチから読み取る
 *	成功した場合はTRUE,失敗した場合はFALSEをreturnする 
 *
 * \param _arg_bt_master_num : 読み取ったMasterの番号
 * 
 * \return BOOL 読み取りの成功の通知
 */
BOOL F_In_bt_num_bt_rx_2(E_BT_NUM &_arg_bt_master_num);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	_arg_data_outをメイン回路へ送信する形に変換して送信する。
 *	送信には、_arg_uart_tを用いる。
 *
 * \param _arg_uart_t	: 使うUART
 * \param _arg_data_out : 送信するデータ。事前に、転送データかどうか確認してください。
 */
void F_Out_main_bt_rx_2 (C_UART_T &_arg_uart_t, const char _arg_data_out[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetoothへ_arg_data_outを送信する。UART1を使う。
 *	送信完了するまで続きます。プログラムが停止したら疑ってみてね。
 *
 * \param _arg_data_out : 送信するdata
 */
inline void F_Out_bt_rx_2 (const char _arg_data_out[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetoothから受信する。UART1を使います。
 *	受信したdataは_arg_re_data_inに格納される。
 *	受信完了するまで続きます。プログラムが停止したら疑ってみてね。 
 *
 * \param _arg_re_data_in	: 受信したdataを格納する所
 */
inline void F_In_bt_rx_2 (char _arg_re_data_in[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	受信したデータが_arg_data_compに一致するまで受信し続ける。UART1。
 *	仕様上、合わなかったら無限ループ状態になるので気を付けてね。 
 *
 * \param _arg_data_comp	: 比較対象
 */
inline void F_In_comp_bt_rx_2 (const char _arg_data_comp[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	受信したデータが_arg_data_compに一致するまで受信し続ける。UART1
 *	受信したデータは_arg_re_data_inに格納される。
 *	仕様上、合わなかったら無限ループ状態になるので気を付けてね。 
 *
 * \param _arg_re_data_in	: 受信したデータを格納する場所
 * \param _arg_data_comp	: 比較対象
 */
inline void F_In_comp_bt_rx_2 (char _arg_re_data_in[], const char _arg_data_comp[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	MasterのBluetoothと接続する。Bluetoothの緑のLEDが光ったら完了。 
 *
 * \param _arg_master_num : Masterの番号
 */
void F_Conect_bt_rx_2 (const E_BT_NUM _arg_master_num);

/************************************************************************/

#include "Func_bt_rx.cpp"