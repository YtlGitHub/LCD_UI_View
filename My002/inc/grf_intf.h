#ifndef _GRF_INTF_H_
#define _GRF_INTF_H_

#include "grf_typedef.h"

/***************************base api****************************/
//获取SDK版本号
u8* grf_ver_get_str(void);
//获取固件(firmware)版本号
u8 *grf_fw_get_version(void);
//调试打印
int grf_printf(const char *format,...);
//延时函数,使用可能会减缓刷新,请谨慎使用
void grf_delay(int time_ms);
//获取系统时间片
u32 grf_sys_time_ms(void);
//剩余内存大小
int grf_freeram(void);
//系统重启
int grf_reboot(void);


/***************************grf color****************************/
#define GRF_COLOR_WHITE 	GRF_COLOR_GET(0xFF, 0xFF, 0xFF)
#define GRF_COLOR_SILVER 	GRF_COLOR_GET(0xC0, 0xC0, 0xC0)
#define GRF_COLOR_GRAY 		GRF_COLOR_GET(0x80, 0x80, 0x80)
#define GRF_COLOR_BLACK 	GRF_COLOR_GET(0x00, 0x00, 0x00)
#define GRF_COLOR_RED 		GRF_COLOR_GET(0xFF, 0x00, 0x00)
#define GRF_COLOR_MAROON 	GRF_COLOR_GET(0x80, 0x00, 0x00)
#define GRF_COLOR_YELLOW 	GRF_COLOR_GET(0xFF, 0xFF, 0x00)
#define GRF_COLOR_OLIVE 	GRF_COLOR_GET(0x80, 0x80, 0x00)
#define GRF_COLOR_LIME 		GRF_COLOR_GET(0x00, 0xFF, 0x00)
#define GRF_COLOR_GREEN 	GRF_COLOR_GET(0x00, 0x80, 0x00)
#define GRF_COLOR_CYAN 		GRF_COLOR_GET(0x00, 0xFF, 0xFF)
#define GRF_COLOR_TEAL 		GRF_COLOR_GET(0x00, 0x80, 0x80)
#define GRF_COLOR_BLUE 		GRF_COLOR_GET(0x00, 0x00, 0xFF)
#define GRF_COLOR_NAVY 		GRF_COLOR_GET(0x00, 0x00, 0x80)
#define GRF_COLOR_MAGENTA 	GRF_COLOR_GET(0xFF, 0x00, 0xFF)
#define GRF_COLOR_PURPLE 	GRF_COLOR_GET(0x80, 0x00, 0x80)
#define GRF_COLOR_ORANGE 	GRF_COLOR_GET(0xFF, 0xA5, 0x00)
/***************************grf task****************************/
typedef void *grf_task_t;
//任务回调函数类型
typedef void (*grf_task_cb_t)(grf_task_t *task_t);
//创建任务
grf_task_t *grf_task_create(grf_task_cb_t task_xcb, u32 period, void* user_data);
//删除任务
void grf_task_del(grf_task_t *task_t);
//获取该任务的用户参数
void* grf_task_get_user_data(grf_task_t *task_t);
//更改任务回调函数
void grf_task_set_cb(grf_task_t *task_t, grf_task_cb_t task_cb);
//设置任务回调周期
void grf_task_set_period(grf_task_t *task_t, u32 period);
//任务准备就绪,不等待时间,立即执行
void grf_task_ready(grf_task_t * task_t);
//使任务回调函数只运行一次
void grf_task_once(grf_task_t *task_t);
//复位任务
void grf_task_reset(grf_task_t * task_t);
/***************************grf resource****************************/
//根据ID获取图片名
u8* grf_j2s_res_img_get(u32 dirID,u32 fileID);

/***************************grf language****************************/
s32 grf_lang_set(u8* language);


#endif
