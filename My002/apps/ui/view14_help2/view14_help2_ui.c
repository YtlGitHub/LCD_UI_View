#include "../../apps.h"


//.c文件里面自定义函数
void task_create14();
void task_del14();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image9_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image10_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image11_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view14_help2_cc.h"
void view14_help2_init(void)
{
	grf_view_create(GRF_VIEW14_HELP2_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view14_help2_entry(void)
{
	task_create14();
}

void view14_help2_exit(void)
{
	task_del14();
}
