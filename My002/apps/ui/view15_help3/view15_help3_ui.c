#include "../../apps.h"


//.c文件里面自定义函数
void task_create15();
void task_del15();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view15_help3_cc.h"
void view15_help3_init(void)
{
	grf_view_create(GRF_VIEW15_HELP3_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view15_help3_entry(void)
{
	//语音播报"请翻转机身找到拆手柄孔,并使用十字螺丝刀,顶住孔内弹片进行拆除。"
	switch_language_pack("15_help");
	task_create15();
}

void view15_help3_exit(void)
{
	task_del15();
}
