#include "../../apps.h"


//.c文件里面自定义函数
void task_create05();
void task_del05();



static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image9_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void bar0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void bar1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view05_sterilization_fluid_preparation_cc.h"
void view05_sterilization_fluid_preparation_init(void)
{
	grf_view_create(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view05_sterilization_fluid_preparation_entry(void)
{
	//如果是在充电自清洁模式跳转过来,就不赋值给视图变量
	if (ytl_view_get_cur_id != GRF_VIEW09_SELF_CLEANING_MODE_ID) {
		ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	}

	task_create05();

	//发送串口数据
	if (ytl_mode_select_uart == 1) {
		grf_reg_com_send(0x06, 0xA0, 0x04, 0x01, 0x01);
	}
	else if (ytl_mode_select_uart == 2) {
		grf_reg_com_send(0x06, 0xA0, 0x04, 0x02, 0x01);
	}
	else {
		grf_reg_com_send(0x05, 0xA0, 0x02, 0x01, 0);
	}
	//显示顶层音量和清扫图标
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
}

void view05_sterilization_fluid_preparation_exit(void)
{
	task_del05();
	//隐藏顶层音量和清扫图标
	grf_view_hide_layer(GRF_LAYER_TOP);
	view03_voice_icon_exit();
}

