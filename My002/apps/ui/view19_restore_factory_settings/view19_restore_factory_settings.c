#include "../../apps.h"


//创建任务名
grf_task_t *key_task19 = NULL;  //按键任务


//创建控件名


//自定义变量


//自定义数组


//自定义调用函数


//按键任务
/*void key_task19_cb()
{
	grf_printf("key_task19_cb\n");
	if (ytl_back)
	{
		grf_printf("task_create19 == ytl_back\n");
		ytl_back = GRF_FALSE;
		grf_view_set_dis_view(ytl_view_get_cur_id);
	}
}


void task_create19(void)
{
	grf_printf("task_create19\n");

	//获取控件

	//创建任务
	key_task19 = grf_task_create(key_task19_cb,100,NULL);  //创建按键任务
}


void task_del19(void)
{
	grf_printf("task_del19\n");
	grf_task_del(key_task19);
}*/
