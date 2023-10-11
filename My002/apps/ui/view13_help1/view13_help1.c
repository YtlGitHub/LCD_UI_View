#include "../../apps.h"


//创建故障任务
grf_task_t *key_task13 = NULL;
grf_task_t *quick_guide_task = NULL;


//创建控件名
grf_ctrl_t *container0_ID1 = NULL;  //电源/暂停键
grf_ctrl_t *container1_ID4 = NULL;  //选择键
grf_ctrl_t *container2_ID7 = NULL;  //确认键
grf_ctrl_t *container3_ID10 = NULL;  //返回/帮助键
grf_ctrl_t *container4_ID13 = NULL;  //运行界面按选择键可以切换模式
grf_ctrl_t *container5_ID17 = NULL;  //切换模式时按确认键可以进入对应模式
grf_ctrl_t *container6_ID21 = NULL;  //长按帮助/返回键可以进入帮助界面,获取更多使用指导,短按帮助/返回键可以退出帮助
grf_ctrl_t *container7_ID29 = NULL;  //顶部是自清洁键,放回底座时按该键可以开启自清洁
grf_ctrl_t *container8_ID32 = NULL;  //背面是静音键,短按开/关语音。
grf_ctrl_t *container9_ID35 = NULL;  //机身背面是清水箱,倾斜机身开始清扫
grf_ctrl_t *container10_ID38 = NULL;  //清扫中,踩住底座,竖起机身,暂停清扫:机身正面是污水箱,每次使用完毕后请清洗污水箱,避免异味。


//自定义变量
static u16 i = 0;


//自定义数组


//第一次进入显示的界面
static void first_display()
{
	i = 0;
	grf_ctrl_set_hidden(container0_ID1,GRF_TRUE);
	grf_ctrl_set_hidden(container1_ID4,GRF_TRUE);
	grf_ctrl_set_hidden(container2_ID7,GRF_TRUE);
	grf_ctrl_set_hidden(container3_ID10,GRF_TRUE);
	grf_ctrl_set_hidden(container4_ID13,GRF_TRUE);
	grf_ctrl_set_hidden(container5_ID17,GRF_TRUE);
	grf_ctrl_set_hidden(container6_ID21,GRF_TRUE);
	grf_ctrl_set_hidden(container7_ID29,GRF_TRUE);
	grf_ctrl_set_hidden(container8_ID32,GRF_TRUE);
	grf_ctrl_set_hidden(container9_ID35,GRF_TRUE);
	grf_ctrl_set_hidden(container10_ID38,GRF_TRUE);
}


//快速指南
void quick_guide_task_cb(){
	i++;
	if (i > 440) {
		i = 1;
	}
	grf_printf("i == %d\n",i);

	if (i == 1) {
		grf_ctrl_set_hidden(container0_ID1,GRF_FALSE);
		grf_ctrl_set_hidden(container1_ID4,GRF_TRUE);
		grf_ctrl_set_hidden(container2_ID7,GRF_TRUE);
		grf_ctrl_set_hidden(container3_ID10,GRF_TRUE);
		grf_ctrl_set_hidden(container4_ID13,GRF_TRUE);
		grf_ctrl_set_hidden(container5_ID17,GRF_TRUE);
		grf_ctrl_set_hidden(container6_ID21,GRF_TRUE);
		grf_ctrl_set_hidden(container7_ID29,GRF_TRUE);
		grf_ctrl_set_hidden(container8_ID32,GRF_TRUE);
		grf_ctrl_set_hidden(container9_ID35,GRF_TRUE);
		grf_ctrl_set_hidden(container10_ID38,GRF_TRUE);
	}
	else if (i == 30) {
		grf_ctrl_set_hidden(container0_ID1,GRF_TRUE);
		grf_ctrl_set_hidden(container1_ID4,GRF_FALSE);
	}
	else if (i == 50) {
		grf_ctrl_set_hidden(container1_ID4,GRF_TRUE);
		grf_ctrl_set_hidden(container2_ID7,GRF_FALSE);
	}
	else if (i == 70) {
		grf_ctrl_set_hidden(container2_ID7,GRF_TRUE);
		grf_ctrl_set_hidden(container3_ID10,GRF_FALSE);
	}
	else if (i == 90) {
		grf_ctrl_set_hidden(container3_ID10,GRF_TRUE);
		grf_ctrl_set_hidden(container4_ID13,GRF_FALSE);
	}
	else if (i == 120) {
		grf_ctrl_set_hidden(container4_ID13,GRF_TRUE);
		grf_ctrl_set_hidden(container5_ID17,GRF_FALSE);
	}
	else if (i == 150) {
		grf_ctrl_set_hidden(container5_ID17,GRF_TRUE);
		grf_ctrl_set_hidden(container6_ID21,GRF_FALSE);
	}
	else if (i == 220) {
		grf_ctrl_set_hidden(container6_ID21,GRF_TRUE);
		grf_ctrl_set_hidden(container7_ID29,GRF_FALSE);
	}
	else if (i == 270) {
		grf_ctrl_set_hidden(container7_ID29,GRF_TRUE);
		grf_ctrl_set_hidden(container8_ID32,GRF_FALSE);
	}
	else if (i == 310) {
		grf_ctrl_set_hidden(container8_ID32,GRF_TRUE);
		grf_ctrl_set_hidden(container9_ID35,GRF_FALSE);
	}
	else if (i == 350) {
		grf_ctrl_set_hidden(container9_ID35,GRF_TRUE);
		grf_ctrl_set_hidden(container10_ID38,GRF_FALSE);
	}
}

//按键操作
void key_task13_cb(){
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("返回键\n");
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //返回帮助界面
	}
}

void task_create13()
{
	grf_printf("task_create13\n");

	//获取控件
	container0_ID1 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER0_ID);
	container1_ID4 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER1_ID);
	container2_ID7 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER2_ID);
	container3_ID10 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER3_ID);
	container4_ID13 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER4_ID);
	container5_ID17 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER5_ID);
	container6_ID21 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER6_ID);
	container7_ID29 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER7_ID);
	container8_ID32 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER8_ID);
	container9_ID35 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER9_ID);
	container10_ID38 = grf_ctrl_get_form_id(GRF_VIEW13_HELP1_ID,VIEW13_HELP1_CONTAINER10_ID);

	first_display();

	//创建任务
	key_task13 = grf_task_create(key_task13_cb,100,NULL);
	quick_guide_task = grf_task_create(quick_guide_task_cb,100,NULL);

	//立即执行
	grf_task_ready(quick_guide_task);
}

void task_del13()
{
	grf_printf("task_del13\n");
	grf_task_del(key_task13);
	grf_task_del(quick_guide_task);
}
