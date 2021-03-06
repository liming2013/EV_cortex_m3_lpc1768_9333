/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           common.h
** Last modified Date:  2013-01-06
** Last Version:        No
** Descriptions:        系统参数定义及通用函数部分                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-06
** Version:             V0.1
** Descriptions:        The original version        
********************************************************************************************************/
#ifndef __COMMON_H 
#define __COMMON_H




#define MENU_LCD_SHOW   1 //是否选择LCD显示菜单


/******************************************屏幕显示行数*****************************************************/
#define LINE1                    0
#define LINE2                    1
#define LINE3                    2
#define LINE4                    3
#define LINE5                    4
#define LINE6                    5
#define LINE7                    6
#define LINE8                    7
#define LINE9                    8
#define LINE10                   9
#define LINE11                   10
#define LINE12                   11
#define LINE13                   12
#define LINE14                   13
#define LINE15                   14
#define LINE16                   15

#define MAXLANGUAGETYPE 5 //系统支持最大的语言种类，目前暂定5种，中文，英文，土耳其，俄罗斯，葡萄牙




//==============================货道有关宏定义========================================================

#define HUODAO_TYPE_ISOPEN   1
#define HUODAO_TYPE_STATE   2
#define HUODAO_TYPE_REMAIN   3
#define HUODAO_TYPE_PRICE   4
#define HUODAO_TYPE_TRADE_NUM   5
#define HUODAO_TYPE_TRADE_MAXCOUNT 6
#define HUODAO_TYPE_TRADE_LOGICNO 7
//======================================================================================




//==============================定时器计数变量结构体========================================================

typedef struct _timer_st_{

	volatile unsigned char secTimer;//定义秒级 定时
	volatile unsigned short printTimer;
	volatile unsigned short pcm_handle_timeout;
	volatile unsigned short checkDeviceTimeout;
	volatile unsigned short HpHandleTimer;
	volatile unsigned int bill_comunication_timeout;//MDB通讯超时时间
	volatile unsigned short led_paoma_timer;


	volatile unsigned short sec_usr_op_timer;//用户操作超时	
	volatile unsigned short sec_changer_timer;
	volatile unsigned short sec_hopper_state_timer;//hopper  定时复位
	
}TIMER_ST;
extern TIMER_ST Timer;


/************************************************************************************
*系统参数结构体
***************************************************************************************/
struct STSYSPARAM
{
	//语言类型
	unsigned char Language;
	//LCD类型 :1——LCD显示屏  2——LED显示屏
	unsigned char LCDSel;
	//硬币器类型：0——无硬币器    1——串行硬币器    2——并行硬币器
	unsigned char CoinType;
	//纸币器类型：0——无纸币器	 1——GBA纸币器	  2——MDB协议纸币器
	unsigned char BillType;
	//找零器类型：1——无找零器	1——Hopper找零器   2——MDB找零器
	unsigned char DispenceType;
	//当前系统设置小数点位数
	unsigned char nPoinValue;

	unsigned char TraceFlag;//调试开关

	unsigned char  armSN[2];
	unsigned char vmcType;//小机型
	unsigned int  macSN;

	unsigned char logo;
	unsigned char initOK;//系统初始化标志
	unsigned int  maxHuodaoPrice;//主柜货道最大单价
	
};

extern struct STSYSPARAM SYSPara;



/************************************************************************************
*纸币器硬币器 hopper通道面值结构体
***************************************************************************************/

struct STDevValue
{
	//纸币器相关参数
	uint32_t BillValue[8];	    
    uint8_t  BillLevel;			  //纸币器等级
	uint16_t BillCode;		  //国家代码
	uint16_t BillScale;			  //比例因子
	uint16_t BillDecimal;		  //10^小数位数
	uint16_t BillStkCapacity;	  //储币容量
	uint16_t BillSecurity;		  //安全等级
	uint8_t  BillEscrowFun;		  //暂存功能
	uint8_t  billIDENTITYBuf[36];  //Identification

	uint32_t hpBaseChange;
	uint16_t HpValue[3];
	uint32_t CoinValue[8];
};

extern struct STDevValue stDevValue;


/************************************************************************************
*设备状态结构体
***************************************************************************************/
typedef struct _st_dev_state_{
		unsigned char billState; // 1故障 0正常
		unsigned char coinState;
		unsigned short hopperState;

}ST_DEV_STATE;

extern ST_DEV_STATE stDevState;

/************************************************************************************
*总交易数据结构体
***************************************************************************************/
typedef struct _st_total_trade_sum_
{
	//收入纸币总金额
	unsigned int BillMoneySum;
	//收入硬币总金额
	unsigned int CoinMoneySum;
	//找零总金额
	unsigned int DispenceSum;
	//00地址Hopper找零总数量
	unsigned int Hopper1DispSum;
	//01地址Hopper找零总数量
	unsigned int Hopper2DispSum;
	//10地址Hopper找零总数量
	unsigned int Hopper3DispSum;
	unsigned int tradePageNo;//交易页号 0 表示没有交易记录 
	unsigned int tradeNums;//总交易数量
	unsigned int iouAmount;//欠费金额
	unsigned int tradeAmount;//交易总金额


	
	
}ST_TOTAL_TRADE_SUM;

extern ST_TOTAL_TRADE_SUM stTotalTrade;




/************************************************************************************
*详细交易数据结构体
***************************************************************************************/
typedef struct _detail_trade_info_{

	RTC_DATE tradeTime;//交易时间  
	unsigned int billIncome;//本交易收币  
	unsigned int coinIncome;//本交易收硬币
	unsigned int tradePayout;//本交易找零
	unsigned char tradeNum;//单笔购买次数  最大8笔
	unsigned char columnNo[8];//货道号
	unsigned char tradeResult[8];//出货结果
	unsigned short tradePrice[8];//售卖金额
	
	//8 + 12 + 1 + 16 + 16 =  	
}DETAIL_TRADE_INFO;




/************************************************************************************
*货道信息结构体  changed by yoc
***************************************************************************************/

#define COLUMN_LEVEL_NUM   2   //定义货道的层数
#define COLUMN_ONE_LEVEL_NUM 8//定义单层货道的最大货道数



#define HUODAO_STATE_NORMAL		1 
#define HUODAO_STATE_EMPTY		3     
#define HUODAO_STATE_FAULT		2 
#define HUODAO_STATE_N_A		0  





/************************************************************************************
*货道按键灯 与按键号一一对应
***************************************************************************************/
#if 0 //样机灯格式
#define HUODAO_SELCET_LED1	(1ul<<18)//灯1	
#define HUODAO_SELCET_LED2	(1ul<<19)//灯2	
#define HUODAO_SELCET_LED3	(1ul<<20)//灯3	
#define HUODAO_SELCET_LED4	(1ul<<31)//灯4

#else //正式机灯格式

#define HUODAO_SELCET_LED1	(1ul<<31)//灯1	
#define HUODAO_SELCET_LED2	(1ul<<18)//灯2	
#define HUODAO_SELCET_LED3	(1ul<<19)//灯3	
#define HUODAO_SELCET_LED4	(1ul<<20)//灯4	


#endif





struct STChannel
{
	unsigned char isOpen;//货道开启标志 1开启 0关闭
	unsigned char addr;	//货道实际物理地址
	unsigned char physicNo;//物理货道编号
	unsigned char logicNo;//货道的逻辑编号		
	unsigned char state;//货道状态 :1——可用  3——缺货   2——故障	
	unsigned char selectNo;//货道选货按键号		
	
	unsigned char remainCount;//商品存货余量
	unsigned char maxCount;//最大储货量
	unsigned int  price;//货道商品单价
	unsigned int  tradeCount;//货道成功交易次数
	unsigned char canShip;//可以出货标志 1表示可以出货 0 表示不能出货
};

typedef struct _st_column_level_{
	
	unsigned char isOpen;
	struct STChannel stColumn[COLUMN_ONE_LEVEL_NUM];
		
}ST_COLUMN_LEVEL;

extern ST_COLUMN_LEVEL stHuodao[COLUMN_LEVEL_NUM];//定义两层货道 结构体


//======================================================================================


//================================系统故障码======================================================

#define SYS_ERR_NO_NORMAL  (unsigned short)(0)  //正常
#define SYS_ERR_NO_HOPPER  (unsigned short)(0x01 << 0)  //Hopper故障
#define SYS_ERR_NO_BILL    (unsigned short)(0x01 << 1)  //纸币器故障
#define SYS_ERR_NO_HUODAO_PRICE   (unsigned short)(0x01 << 2)  //货道自检全部货道单价为零
#define SYS_ERR_NO_HUODAO_EMPTY   (unsigned short)(0x01 << 3)  //货道系统参数中的储货量全为0
#define SYS_ERR_NO_HUODAO_FAULT  (unsigned short)(0x01 << 4)  //货道自检全部货道不可用
#define SYS_ERR_NO_COIN			(unsigned short)(0x01 << 5)  //硬币器故障
#define SYS_ERR_NO_CHANGER_FAULT (unsigned short)(0x01 << 6)  //非hopper找零器故障

//================================hopper故障码======================================================

#define HP_ERR_NO_NORMAL  (unsigned short)(0)//正常
#define HP_ERR_NO_HOPPER1_FAULT  (unsigned short)(0x01 << 0)//hopper1故障
#define HP_ERR_NO_HOPPER1_EMPTY  (unsigned short)(0x01 << 1)//hopper1缺币
#define HP_ERR_NO_HOPPER2_FAULT  (unsigned short)(0x01 << 2)//hopper2故障
#define HP_ERR_NO_HOPPER2_EMPTY  (unsigned short)(0x01 << 3)//hopper2缺币
#define HP_ERR_NO_HOPPER3_FAULT  (unsigned short)(0x01 << 4)//hopper3故障
#define HP_ERR_NO_HOPPER3_EMPTY  (unsigned short)(0x01 << 5)//hopper3缺币
#define HP_ERR_NO_HOPPER4_FAULT  (unsigned short)(0x01 << 6)//hopper4故障
#define HP_ERR_NO_HOPPER4_EMPTY  (unsigned short)(0x01 << 7)//hopper4缺币


//hopper故障码
extern unsigned int hopperErrNo;
//售货机故障码
extern uint16_t HardWareErr;







//======================================================================================









void setColumnLedON(unsigned int price);
unsigned char XorCheck(unsigned char *pstr,unsigned short len);
unsigned short CrcCheck(unsigned char *msg, unsigned short len);

char *PrintfMoney(uint32_t dispnum);


extern unsigned short paomaLedTimer;

void msleep(unsigned int msec);
void idlePaoMaLed(void);

#endif
/**************************************End Of File*******************************************************/
