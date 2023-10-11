#include "../../apps.h"


//创建故障任务
grf_task_t *key_task16 = NULL;


//创建控件名


//自定义变量


//自定义数组


//按键操作
void key_task16_cb(){
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("返回键\n");
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //在帮助界面返回
	}
}

void task_create16()
{
	grf_printf("task_create16\n");

	//创建任务
	key_task16 = grf_task_create(key_task16_cb,100,NULL);
}

void task_del16()
{
	grf_printf("task_del16\n");
	grf_task_del(key_task16);
}
