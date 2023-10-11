#include "../../apps.h"


//.c文件里面自定义函数
void task_create10();
void task_del10();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view10_self_cleaning_cc.h"
void view10_self_cleaning_init(void)
{
	grf_view_create(GRF_VIEW10_SELF_CLEANING_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view10_self_cleaning_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	task_create10();
}

void view10_self_cleaning_exit(void)
{
	task_del10();
}
