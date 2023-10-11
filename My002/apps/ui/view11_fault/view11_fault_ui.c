#include "../../apps.h"


//.c文件里面自定义函数
void task_create11();
void task_del11();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container2_event(grf_ctrl_t *ctrl, grf_event_e event)
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

static void image10_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image11_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image12_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image13_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image14_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image15_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image16_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image17_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view11_fault_cc.h"
void view11_fault_init(void)
{
	grf_printf("view11_fault_init\n");
	grf_view_create(GRF_VIEW11_FAULT_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view11_fault_entry(void)
{
	task_create11();
}

void view11_fault_exit(void)
{
	task_del11();
}
