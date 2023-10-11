#include "../../apps.h"


//创建故障任务
grf_task_t *key_task15 = NULL;
grf_task_t *remove_handle_task = NULL;


//创建控件名
grf_ctrl_t *remove_handle_img_name_ID2 = NULL;  //拆除手柄图控件名


//自定义变量
static u8 i = 0;


//自定义数组
static u8 *remove_handle_image_name[19] = {
	"/help/help_3_00.png",
	"/help/help_3_01.png",
	"/help/help_3_02.png",
	"/help/help_3_03.png",
	"/help/help_3_04.png",
	"/help/help_3_05.png",
	"/help/help_3_06.png",
	"/help/help_3_07.png",
	"/help/help_3_08.png",
	"/help/help_3_09.png",
	"/help/help_3_10.png",
	"/help/help_3_11.png",
	"/help/help_3_12.png",
	"/help/help_3_13.png",
	"/help/help_3_14.png",
	"/help/help_3_15.png",
	"/help/help_3_16.png",
	"/help/help_3_17.png",
	"/help/help_3_18.png"
};  //帮助模式四张选择图片文件名


//拆除手柄轮播图函数
void remove_handle_task_cb(){
	i++;
	if (i > 18) {
		i = 1;
		grf_delay(1000);
	}
	grf_img_set_src(remove_handle_img_name_ID2,remove_handle_image_name[i]);
}

//按键操作
void key_task15_cb(){
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("返回键\n");
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //在帮助界面返回
	}
}

void task_create15()
{
	grf_printf("task_create15\n");

	//获取任务
	remove_handle_img_name_ID2 = grf_ctrl_get_form_id(GRF_VIEW15_HELP3_ID,VIEW15_HELP3_IMAGE1_ID);

	//创建任务
	key_task15 = grf_task_create(key_task15_cb,100,NULL);
	remove_handle_task = grf_task_create(remove_handle_task_cb,100,NULL);

	//立即执行
	grf_task_ready(remove_handle_task);
}

void task_del15()
{
	grf_printf("task_del15\n");
	i = 0;
	grf_task_del(key_task15);
	grf_task_del(remove_handle_task);
}
