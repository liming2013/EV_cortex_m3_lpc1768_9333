/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           timer.c
** Last modified Date:  2013-01-07
** Last Version:         
** Descriptions:        定时器驱动程序                   
**------------------------------------------------------------------------------------------------------
** Created by:          sunway 
** Created date:        2013-01-07
** Version:             V0.1 
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"


extern volatile unsigned int EVBCONVERSATIONWAITACKTIMEOUT;
extern volatile unsigned int MDBCONVERSATIONWAITACKTIMEOUT;
extern volatile unsigned int MDBCONVERSATIONWAITACKTIMEOUT1;
extern volatile unsigned int UART3RECVACKMSGTIMEOUT;
extern volatile uint16_t RS232WAITRECVPACKTIME;
extern volatile unsigned int TestPluse;
extern volatile uint16_t Hptime1,Hptime2,Hptime3;
extern uint16_t ReEnableTime;
extern volatile uint16_t RecvCmdTimer;
extern volatile uint16_t WaitCmdTimer;
extern volatile uint16_t WaitMoneyInTimer;
extern volatile uint32_t WaitMoneyInTimer_1;
extern volatile unsigned short HpHandleTimer;






/*********************************************************************************************************
** Function name:     	InitTimer
** Descriptions:	    LPC1768内部4个定时器的初始化
** input parameters:    TimerNumb:定时器号(0~3);TimerInterval定时时间参数
** output parameters:   无
** Returned value:      无
** 定时时间计算方法：	定时时间(Second) = (TimerInterval*(PR+1))/FPCLK,其中FPCLK = 24000000,PR = 0;
						如定时10ms(0.01s),则TimerInterval = 240000
*********************************************************************************************************/
void InitTimer(unsigned char TimerNumb,unsigned int TimerInterval)
{
	switch(TimerNumb)
	{
		case 0:	T0TCR	= 0x02;
				T0IR	= 1;
				T0CTCR	= 0;
				T0TC	= 0;
				T0PR	= 0;
				T0MR0	= TimerInterval;
				T0MCR	= 0x03;
				zyIsrSet(NVIC_TIMER0,(unsigned long)TIMER0_IRQHandler,PRIO_TWO);
				T0TCR	= 0x01;
				break;
		case 1:	T1TCR	= 0x02;
				T1IR	= 1;
				T1CTCR	= 0;
				T1TC	= 0;
				T1PR	= 0;
				T1MR0	= TimerInterval;
				T1MCR	= 0x03;
				zyIsrSet(NVIC_TIMER1,(unsigned long)TIMER1_IRQHandler,PRIO_ELEVEN);
				T1TCR	= 0x01;
				break;
		case 2:	T2TCR	= 0x02;
				T2IR	= 1;
				T2CTCR	= 0;
				T2TC	= 0;
				T2PR	= 0;
				T2MR0	= TimerInterval;
				T2MCR	= 0x03;
				zyIsrSet(NVIC_TIMER2,(unsigned long)TIMER2_IRQHandler,PRIO_TWELVE);
				T2TCR	= 0x01;
				break;
		case 3:	T3TCR	= 0x02;
				T3IR	= 1;
				T3CTCR	= 0;
				T3TC	= 0;
				T3PR	= 0;
				T3MR0	= TimerInterval;
				T3MCR	= 0x03;
				zyIsrSet(NVIC_TIMER3,(unsigned long)TIMER3_IRQHandler,PRIO_THIRTEEN);
				T3TCR	= 0x01;
				break;
		default:break;
	}
}
/*********************************************************************************************************
* Function Name:        TIMER0_IRQHandler
* Description:          定时器0中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void TIMER0_IRQHandler (void)
{  
	OSIntEnter();
	T0IR = 1;
	//Hptime1++;
	//Hptime2++;
	//Hptime3++;
	ReEnableTime++;
	if(EVBCONVERSATIONWAITACKTIMEOUT)
		EVBCONVERSATIONWAITACKTIMEOUT--;
	if(MDBCONVERSATIONWAITACKTIMEOUT)
		MDBCONVERSATIONWAITACKTIMEOUT--;
	if(RS232WAITRECVPACKTIME)
		RS232WAITRECVPACKTIME--;
	if(UART3RECVACKMSGTIMEOUT)
		UART3RECVACKMSGTIMEOUT--;
	if(WaitMoneyInTimer)
		WaitMoneyInTimer--;
	if(WaitMoneyInTimer_1)
		WaitMoneyInTimer_1--;
	if(RecvCmdTimer)
		RecvCmdTimer--;
	if(TestPluse)
		TestPluse--;
	if(WaitCmdTimer)
		WaitCmdTimer--;		
	if(paomaLedTimer)
		paomaLedTimer--;
	if(Timer.printTimer)
		Timer.printTimer--;
	if(Timer.pcm_handle_timeout)
		Timer.pcm_handle_timeout--;
	if(Timer.checkDeviceTimeout)
		Timer.checkDeviceTimeout--;
	if(Timer.HpHandleTimer)
		Timer.HpHandleTimer--;
	if(Timer.bill_comunication_timeout)
		Timer.bill_comunication_timeout--;
	if(Timer.led_paoma_timer)
		Timer.led_paoma_timer--;

	if(Timer.secTimer)
	{
		Timer.secTimer--;
	}
	else
	{
		Timer.secTimer = 100;
		//处理秒级 定时变量
		if(Timer.sec_changer_timer)
			Timer.sec_changer_timer--;
		if(Timer.sec_usr_op_timer)
		Timer.sec_usr_op_timer--;
		if(Timer.sec_hopper_state_timer)
			Timer.sec_hopper_state_timer--;
	}
	OSIntExit();
}
/*********************************************************************************************************
* Function Name:        TIMER1_IRQHandler
* Description:          定时器1中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void TIMER1_IRQHandler (void)
{
	OSIntEnter();
	T1IR = 1;

#if 1 //changed by yoc 2014.03.24	
	if(SYSPara.CoinType == VMC_COIN_PARALLEL)
		ScanPPCoinChannel();
	else if(SYSPara.CoinType == VMC_COIN_SERIAL)	
		ScanSPCoinChannel(); 
#else
	if(GetParallelCoinAcceptorStatus() == 0x01)
		ScanPPCoinChannel();
	if(GetSerialCoinAcceptorStatus() == 0x01)
		ScanSPCoinChannel(); 
#endif
	OSIntExit();
}
/*********************************************************************************************************
* Function Name:        TIMER2_IRQHandler
* Description:          定时器2中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void TIMER2_IRQHandler (void)
{
	OSIntEnter();
	T2IR = 1;	
	OSIntExit();
}
/*********************************************************************************************************
* Function Name:        TIMER3_IRQHandler
* Description:          定时器3中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void TIMER3_IRQHandler (void)
{
	OSIntEnter();
	T3IR = 1;	
	OSIntExit();
}
/**************************************End Of File*******************************************************/
