#include "../../apps.h"


#include "../../../libs/appscc/view20_logo_cc.h"
void view20_logo_init(void)
{
	grf_view_create(GRF_VIEW20_LOGO_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view20_logo_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
}

void view20_logo_exit(void)
{

}
