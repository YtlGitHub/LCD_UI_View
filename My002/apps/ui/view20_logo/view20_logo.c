#include "../../apps.h"

/*
//创建任务名
grf_task_t *logo_task = NULL;  //工程测试模式任务


//创建控件名


//自定义变量


//自定义数组


//自定义调用函数


//logo任务
void logo_task_cb()
{
	if (ytl_battery_quantity_val) {
		if (cmdBuf[0] == 0xB0 && cmdBuf[1] == 0x01) {
			grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
		}
		else if (cmdBuf[0] == 0xB0 && cmdBuf[1] == 0x02) {
			grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
		}
	}
}


void task_create20(void)
{
	grf_printf("task_create18\n");

	//获取控件

	//创建任务
	logo_task = grf_task_create(logo_task_cb,10,NULL);  //创建logo任务

	//立即执行
	grf_task_ready(logo_task);
}


void task_del20(void)
{
	grf_printf("task_del20\n");
	grf_task_del(logo_task);
}
*/
