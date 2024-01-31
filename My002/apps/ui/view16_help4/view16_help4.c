#include "../../apps.h"


//创建故障任务
grf_task_t *key_task16 = NULL;


//创建控件名
static grf_ctrl_t *image_ID1 = NULL;  //电话号码背景图控件名
static grf_ctrl_t *label_ID2 = NULL;  //电话号码label显示控件名
static grf_ctrl_t *qrcode_ID3 = NULL;  //二维码显示控件名


//自定义变量


//自定义数组


//自定义函数


//第一次进入显示的界面
static void first_display(void)
{
	if (ytl3_switch_language == 3)
	{
		grf_qrcode_updata_data(qrcode_ID3,"https://hiberg.ru/servis");
		grf_label_set_txt(label_ID2,"8-800-700-12-25");
	}
	else
	{
		grf_qrcode_updata_data(qrcode_ID3,"https://www.baidu.com");
		grf_label_set_txt(label_ID2,"400-888-8888");
	}
}


//按键操作
void key_task16_cb(){
	control_ytl_mute_v_away();  //快速按静音键时,控制太快的按键丢掉
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //在帮助界面返回
	}
}

void task_create16()
{
	//grf_printf("task_create16\n");

	image_ID1 = grf_ctrl_get_form_id(GRF_VIEW16_HELP4_ID,VIEW16_HELP4_IMAGE0_ID);
	label_ID2 = grf_ctrl_get_form_id(GRF_VIEW16_HELP4_ID,VIEW16_HELP4_LABEL0_ID);
	qrcode_ID3 = grf_ctrl_get_form_id(GRF_VIEW16_HELP4_ID,VIEW16_HELP4_QRCODE0_ID);

	first_display();

	//创建任务
	key_task16 = grf_task_create(key_task16_cb,100,NULL);
}

void task_del16()
{
	//grf_printf("task_del16\n");
	grf_task_del(key_task16);
}
