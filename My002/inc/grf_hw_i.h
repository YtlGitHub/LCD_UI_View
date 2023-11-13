#ifndef __GRF_HW_I_H_
#define __GRF_HW_I_H_

#include "grf_typedef.h"

/***************************grf lcd****************************/
s32 grf_disp_set_bright(u8 bright);
/***************************grf touch****************************/
typedef enum
{
    GRF_TOUCH_UP,
    GRF_TOUCH_DOWN
}grf_touch_state;
typedef struct 
{
    grf_touch_state t_state;
    u16 touch_x;
    u16 touch_y;
}grf_touch_t;
s32 grf_touch_get(grf_touch_t *_touch_t);
/***************************grf uart****************************/
typedef enum{
    UART_SPEED_2400,
    UART_SPEED_4800,
    UART_SPEED_9600,
    UART_SPEED_19200,
    UART_SPEED_38400,
    UART_SPEED_57600,
    UART_SPEED_115200,
    UART_SPEED_230400,
    UART_SPEED_460800,
    UART_SPEED_500000,
    UART_SPEED_576000,
    UART_SPEED_921600
}grf_uart_speed_e;
typedef enum{
    UART_BIT_7,
    UART_BIT_8
}grf_uart_bit_e;
typedef enum{
    UART_PARITY_NONE,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
}grf_uart_parity_e;
typedef enum{
    UART_STOP_1,
    UART_STOP_2
}grf_uart_stop_e;
typedef struct 
{
    s32 port;              //串口端口号,-1为默认端口
    grf_uart_speed_e speed_e;
    grf_uart_bit_e bit_e;
    grf_uart_parity_e parity_e;
    grf_uart_stop_e stop_e;
}grf_uart_cfg_t;
//串口打开
s32 grf_drv_uart_open(grf_uart_cfg_t cfg_t);
//串口关闭
s32 grf_drv_uart_close(void);
//串口发送
s32 grf_drv_uart_send(char* databuf, int datalen);
//设置串口接收中断处理函数,max_len-一次接收数据的最大值
typedef void (*uart_rev_bfun)(u8* databuf,u32 datalen);
s32 grf_drv_uart_rev_set_bfun(uart_rev_bfun rev_bfun,u32 max_len);
/****************************grf wdt*****************************/
//打开看门狗
s32 grf_wdt_open(void);
//关闭看门狗
s32 grf_wdt_close(void);
//设置看门狗超时时间,单位秒
s32 grf_wdt_set_timeout(u32 time);
//喂狗,刷新看门狗时间
s32 grf_wdt_keepalive(void);
/***************************grf gpio****************************/
typedef enum {
    GRF_GPIO_GROUP_A=0,
    GRF_GPIO_GROUP_B,
    GRF_GPIO_GROUP_C,
    GRF_GPIO_GROUP_D,
    GRF_GPIO_GROUP_E,
    GRF_GPIO_GROUP_F,
}grf_gpio_pin_e;
typedef enum {
    GRF_GPIO_INPUT=0,
    GRF_GPIO_OUTPUT,
}grf_gpio_mode_e;
typedef enum {
    GRF_GPIO_IRQ_RISING,
    GRF_GPIO_IRQ_FALLING,
    GRF_GPIO_IRQ_RISING_FALLING
}grf_gpio_irq_mode_e;
typedef void grf_gpio_irq_t;
typedef void(*gpio_irq_task)(grf_gpio_irq_t *irq_t);
typedef struct{
    u8 irq_group;
    u8* irq_pins;       
    u8 gpio_pin_num;
    grf_gpio_irq_mode_e mode_e;
    gpio_irq_task irq_task;
}grf_gpio_irq_para_t;
typedef struct
{
    u8 gpio_group;
    u8 gpio_pin;
    grf_gpio_mode_e gpio_mode;
}grf_gpio_para_t;


s32 grf_gpio_init(grf_gpio_para_t* para_t);
s32 grf_gpio_setPin(u8 gpio_group,u8 gpio_pin,u8 value);
s32 grf_gpio_readInputPin(u8 gpio_group,u8 gpio_pin);
s32 grf_gpio_readOutputPin(u8 gpio_group,u8 gpio_pin);
s32 grf_gpio_group_set_irq(grf_gpio_irq_para_t irq_para_t);
s32 grf_gpio_group_get_irq_pin(grf_gpio_irq_t *irq_t);
s32 grf_gpio_group_get_irq_mode(grf_gpio_irq_t *irq_t);
/***************************grf rtc****************************/
typedef  struct 
{
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
}grf_rtc_time_t;
s32 grf_rtc_get_time(grf_rtc_time_t* rtc_t);
s32 grf_rtc_set_time(grf_rtc_time_t* rtc_t);

/****************************grf flash*****************************/
//得到
u8 *grf_dir_get_ddisk();
u8 *grf_dir_get_tfdisk();
u8 *grf_dir_get_udisk();
/****************************SPI*****************************/
//需固件支持
#define SPI_CPHA		     0x01
#define SPI_CPOL		     0x02
#define SPI_WORK_MODE0		(0|0)
#define SPI_WORK_MODE1		(0|SPI_CPHA)
#define SPI_WORK_MODE2		(SPI_CPOL|0)
#define SPI_WORK_MODE3		(SPI_CPOL|SPI_CPHA)

typedef struct
{
	u32		work_clk;     //单位：HZ
    u32     work_mode;    //SPI工作模式 
	u8		nbits;        //位数
    u16		delay;        //发送时间间隔     
}grf_spi_para_t;

s32 grf_spi_init(grf_spi_para_t *para_t);
s32 grf_spi_transfer(u8 *tx,u8 *rx,u32 len);

/****************************IIC*****************************/
//需固件支持
typedef struct
{
    u8      slave_addr;  //设备地址
    u8      reg_addr;    //寄存器地址
    u8      reg_addr_width;  //寄存器字节个数
}grf_iic_para_t;

s32 grf_iic_init(grf_iic_para_t* para_t);
s32 grf_iic_read(u16 addr, u8 buff[], u16 len);
s32 grf_iic_write(u16 addr, u8 buff[], u16 len);














#endif
