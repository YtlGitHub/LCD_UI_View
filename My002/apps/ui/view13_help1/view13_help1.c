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
static u8 timeBuf[13] = {0};  //在哪个时间点,播报对应语音


//第一次进入显示的界面
static void first_display()
{
	i = 0;
	if (ytl3_switch_language == 0) {
		timeBuf[2]= 25;  //在哪个时间点，“选择键”语音播报
		timeBuf[3]= 11;  //在哪个时间点，“确认键”语音播报
		timeBuf[4]= 11;  //在哪个时间点，“返回/帮助键”语音播报
		timeBuf[5]= 16;  //在哪个时间点，“运行界面按选择键可以切换模式”语音播报
		timeBuf[6]= 31;  //在哪个时间点，“切换模式时按确认键可以进入对应模式”语音播报
		timeBuf[7]= 37;  //在哪个时间点，“长按帮助/返回键可以进入帮助界面,获取更多使用指导,短按帮助/返回键可以退出帮助”语音播报
		timeBuf[8]= 74;  //在哪个时间点，“顶部是自清洁键,放回底座时按该键可以开启自清洁”语音播报
		timeBuf[9]= 47;  //在哪个时间点，“背面是静音键,短按开/关语音”语音播报
		timeBuf[10]= 29;  //在哪个时间点，“机身背面是清水箱,倾斜机身开始清扫”语音播报
		timeBuf[11]= 36;  //在哪个时间点，“清扫中,踩住底座,竖起机身,暂停清扫:机身正面是污水箱,每次使用完毕后请清洗污水箱,避免异味”语音播报
		timeBuf[12]= 101;  //在哪个时间点，重新开始“选择键”语音播报
	}
	else if (ytl3_switch_language == 1) {
		timeBuf[2]= 37;
		timeBuf[3]= 17;
		timeBuf[4]= 15;
		timeBuf[5]= 15;
		timeBuf[6]= 51;
		timeBuf[7]= 41;
		timeBuf[8]= 77;
		timeBuf[9]= 61;
		timeBuf[10]= 45;
		timeBuf[11]= 58;
		timeBuf[12]= 111;
	}
	else if (ytl3_switch_language == 2) {
		timeBuf[2]= 43;
		timeBuf[3]= 14;
		timeBuf[4]= 17;
		timeBuf[5]= 25;
		timeBuf[6]= 50;
		timeBuf[7]= 54;
		timeBuf[8]= 116;
		timeBuf[9]= 80;
		timeBuf[10]= 69;
		timeBuf[11]= 61;
		timeBuf[12]= 148;
	}
	else if (ytl3_switch_language == 3) {
		timeBuf[2]= 57;
		timeBuf[3]= 21;
		timeBuf[4]= 28;
		timeBuf[5]= 26;
		timeBuf[6]= 59;
		timeBuf[7]= 66;
		timeBuf[8]= 141;
		timeBuf[9]= 101;
		timeBuf[10]= 94;
		timeBuf[11]= 41;
		timeBuf[12]= 90;
	}
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
	control_ytl_mute_v_away();  //快速按静音键时,控制太快的按键丢掉
	i++;
	if (i > timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]+timeBuf[8]+timeBuf[9]+timeBuf[10]+timeBuf[11]+timeBuf[12]) {
		i = 1;
	}
	//grf_printf("i == %d\n",i);

	if (i == 1) {
		//语音播报:"把手正面是电源/暂停键"
		switch_language_pack("13_01_help");
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
	else if (i == timeBuf[2]) {
		//语音播报:"选择键"
		switch_language_pack("13_02_help");
		grf_ctrl_set_hidden(container0_ID1,GRF_TRUE);
		grf_ctrl_set_hidden(container1_ID4,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]) {
		//语音播报:"确认键"
		switch_language_pack("13_03_help");
		grf_ctrl_set_hidden(container1_ID4,GRF_TRUE);
		grf_ctrl_set_hidden(container2_ID7,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]) {
		//语音播报:"返回/帮助键"
		switch_language_pack("13_04_help");
		grf_ctrl_set_hidden(container2_ID7,GRF_TRUE);
		grf_ctrl_set_hidden(container3_ID10,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]) {
		//语音播报:"运行界面按选择键可以切换模式"
		switch_language_pack("13_05_help");
		grf_ctrl_set_hidden(container3_ID10,GRF_TRUE);
		grf_ctrl_set_hidden(container4_ID13,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]) {
		//语音播报:"切换模式时按确认键可以进入对应模式"
		switch_language_pack("13_06_help");
		grf_ctrl_set_hidden(container4_ID13,GRF_TRUE);
		grf_ctrl_set_hidden(container5_ID17,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]) {
		//语音播报:"长按帮助/返回键可以进入帮助界面,获取更多使用指导,短按帮助/返回键可以退出帮助"
		switch_language_pack("13_07_help");
		grf_ctrl_set_hidden(container5_ID17,GRF_TRUE);
		grf_ctrl_set_hidden(container6_ID21,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]+timeBuf[8]) {
		//语音播报:"顶部是自清洁键,放回底座时按该键可以开启自清洁"
		switch_language_pack("13_08_help");
		grf_ctrl_set_hidden(container6_ID21,GRF_TRUE);
		grf_ctrl_set_hidden(container7_ID29,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]+timeBuf[8]+timeBuf[9]) {
		//语音播报:"背面是静音键,短按开/关语音。"
		switch_language_pack("13_09_help");
		grf_ctrl_set_hidden(container7_ID29,GRF_TRUE);
		grf_ctrl_set_hidden(container8_ID32,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]+timeBuf[8]+timeBuf[9]+timeBuf[10]) {
		//语音播报:"机身背面是清水箱,倾斜机身开始清扫"
		switch_language_pack("13_10_help");
		grf_ctrl_set_hidden(container8_ID32,GRF_TRUE);
		grf_ctrl_set_hidden(container9_ID35,GRF_FALSE);
	}
	else if (i == timeBuf[2]+timeBuf[3]+timeBuf[4]+timeBuf[5]+timeBuf[6]+timeBuf[7]+timeBuf[8]+timeBuf[9]+timeBuf[10]+timeBuf[11]) {
		//语音播报:"清扫中,踩住底座,竖起机身,暂停清扫:机身正面是污水箱,每次使用完毕后请清洗污水箱,避免异味"
		switch_language_pack("13_11_help");
		grf_ctrl_set_hidden(container9_ID35,GRF_TRUE);
		grf_ctrl_set_hidden(container10_ID38,GRF_FALSE);
	}
}

//按键操作
void key_task13_cb(){
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		//grf_printf("返回键\n");
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //返回帮助界面
	}
}

void task_create13()
{
	//grf_printf("task_create13\n");

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
	//grf_printf("task_del13\n");
	grf_task_del(key_task13);
	grf_task_del(quick_guide_task);
}
