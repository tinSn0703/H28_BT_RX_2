
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
 *	IO���W�X�^�̐ݒ���s��
 */
void F_Set_io_bt_rx_2 ();

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetooth�Ɏg�p����UART��ݒ肷��BUART1�B
 */
void F_Set_uart_bt_rx_2 ();

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 * Timer�̐ݒ���s���BTimer1�B���B���荞�݋��B0.05[s]
 */
void F_Set_timer_bt_rx_2 ();

/**
 * \brief 2016 / 11 / 01 (Thu)
 *	Master�̔ԍ���DIP�X�C�b�`����ǂݎ��
 *	���������ꍇ��TRUE,���s�����ꍇ��FALSE��return���� 
 *
 * \param _arg_bt_master_num : �ǂݎ����Master�̔ԍ�
 * 
 * \return BOOL �ǂݎ��̐����̒ʒm
 */
BOOL F_In_bt_num_bt_rx_2(E_BT_NUM &_arg_bt_master_num);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	_arg_data_out�����C����H�֑��M����`�ɕϊ����đ��M����B
 *	���M�ɂ́A_arg_uart_t��p����B
 *
 * \param _arg_uart_t	: �g��UART
 * \param _arg_data_out : ���M����f�[�^�B���O�ɁA�]���f�[�^���ǂ����m�F���Ă��������B
 */
void F_Out_main_bt_rx_2 (C_UART_T &_arg_uart_t, const char _arg_data_out[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetooth��_arg_data_out�𑗐M����BUART1���g���B
 *	���M��������܂ő����܂��B�v���O��������~������^���Ă݂ĂˁB
 *
 * \param _arg_data_out : ���M����data
 */
inline void F_Out_bt_rx_2 (const char _arg_data_out[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Bluetooth�����M����BUART1���g���܂��B
 *	��M����data��_arg_re_data_in�Ɋi�[�����B
 *	��M��������܂ő����܂��B�v���O��������~������^���Ă݂ĂˁB 
 *
 * \param _arg_re_data_in	: ��M����data���i�[���鏊
 */
inline void F_In_bt_rx_2 (char _arg_re_data_in[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	��M�����f�[�^��_arg_data_comp�Ɉ�v����܂Ŏ�M��������BUART1�B
 *	�d�l��A����Ȃ������疳�����[�v��ԂɂȂ�̂ŋC��t���ĂˁB 
 *
 * \param _arg_data_comp	: ��r�Ώ�
 */
inline void F_In_comp_bt_rx_2 (const char _arg_data_comp[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	��M�����f�[�^��_arg_data_comp�Ɉ�v����܂Ŏ�M��������BUART1
 *	��M�����f�[�^��_arg_re_data_in�Ɋi�[�����B
 *	�d�l��A����Ȃ������疳�����[�v��ԂɂȂ�̂ŋC��t���ĂˁB 
 *
 * \param _arg_re_data_in	: ��M�����f�[�^���i�[����ꏊ
 * \param _arg_data_comp	: ��r�Ώ�
 */
inline void F_In_comp_bt_rx_2 (char _arg_re_data_in[], const char _arg_data_comp[]);

/** Made 2016 / 10 / 28 (Fri)
 * \brief 
 *	Master��Bluetooth�Ɛڑ�����BBluetooth�̗΂�LED���������犮���B 
 *
 * \param _arg_master_num : Master�̔ԍ�
 */
void F_Conect_bt_rx_2 (const E_BT_NUM _arg_master_num);

/************************************************************************/

#include "Func_bt_rx.cpp"