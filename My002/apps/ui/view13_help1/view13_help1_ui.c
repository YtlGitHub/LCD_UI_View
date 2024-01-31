#include "../../apps.h"


static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

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

static void container1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label6_event(grf_ctrl_t *ctrl, grf_event_e event)
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

static void label7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label9_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image12_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label10_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image13_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container9_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label11_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label12_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image14_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image15_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container10_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image16_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image17_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label13_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label14_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view13_help1_cc.h"
void view13_help1_init(void)
{
	grf_view_create(GRF_VIEW13_HELP1_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view13_help1_entry(void)
{
	task_create13();
}

void view13_help1_exit(void)
{
	task_del13();
}
