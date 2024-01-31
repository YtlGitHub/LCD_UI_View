#include "../../apps.h"


//创建按键任务
grf_task_t *key_task09 = NULL;


//创建控件名
static grf_ctrl_t *quick_ID2 = NULL;  //创建快速大图控件名
static grf_ctrl_t *super_strong_ID15 = NULL;  //创建超强大图控件名
static grf_ctrl_t *quick_countdown_ID11 = NULL;  //创建快速倒计时控件名
static grf_ctrl_t *super_strong_countdown_ID18 = NULL;  //创建超强倒计时控件名


//自定义变量
static grf_bool mode_select = GRF_FALSE;  //模式选择变量:GRF_FALSE快速GRF_TRUE超强
static u8 i = 1;  //倒计时图片变量


//自定义数组
static u8 *mode_select_countdown[22] = {
	"",
	"/self_cleaning_mode/daojishi01.png",
	"/self_cleaning_mode/daojishi02.png",
	"/self_cleaning_mode/daojishi03.png",
	"/self_cleaning_mode/daojishi04.png",
	"/self_cleaning_mode/daojishi05.png",
	"/self_cleaning_mode/daojishi06.png",
	"/self_cleaning_mode/daojishi07.png",
	"/self_cleaning_mode/daojishi08.png",
	"/self_cleaning_mode/daojishi09.png",
	"/self_cleaning_mode/daojishi10.png",
	"/self_cleaning_mode/daojishi11.png",
	"/self_cleaning_mode/daojishi12.png",
	"/self_cleaning_mode/daojishi13.png",
	"/self_cleaning_mode/daojishi14.png",
	"/self_cleaning_mode/daojishi15.png",
	"/self_cleaning_mode/daojishi16.png",
	"/self_cleaning_mode/daojishi17.png",
	"/self_cleaning_mode/daojishi18.png",
	"/self_cleaning_mode/daojishi19.png",
	"/self_cleaning_mode/daojishi20.png",
	"/self_cleaning_mode/daojishi21.png"
};


//第一次进入显示的界面
static void first_display()
{
	//第一次进入默认选择快速
	i = 1;
	grf_ctrl_set_hidden(quick_ID2,GRF_FALSE);
	grf_ctrl_set_hidden(super_strong_ID15,GRF_TRUE);
	grf_img_set_src(quick_countdown_ID11, mode_select_countdown[i]);
	mode_select = GRF_FALSE;
}


//进入自清洁模式时,先判断是否有故障
void ytl_fault_get()
{
	for (u8 i = 1; i < 7; ++i)
	{
		if(ytl_fault[i])
		{
			//grf_printf("task_create09 故障跳转\n");
			ytl_fault[11] = GRF_FALSE;
			ytl_fault[12] = GRF_FALSE;
			ytl_fault[13] = GRF_FALSE;
			ytl_fault[14] = GRF_FALSE;
			ytl_fault[15] = GRF_FALSE;
			ytl_fault[16] = GRF_FALSE;
			//grf_printf("ytl_fault[i] == %d,ytl_fault_val == %d",ytl_fault[i],ytl_fault_val);
			grf_view_set_dis_view(GRF_VIEW11_FAULT_ID);
			break;
		}
	}
}


//按键操作
static void key_task09_cb(){
	//按自清洁键选择模式
	if (ytl_self_cleaning) {
		ytl_self_cleaning = GRF_FALSE;
		//grf_printf("mode_select == %d",mode_select);

		if (mode_select) {
			grf_ctrl_set_hidden(quick_ID2,GRF_FALSE);
			grf_ctrl_set_hidden(super_strong_ID15,GRF_TRUE);
			i = 1;
			mode_select = GRF_FALSE;
		}
		else {
			grf_ctrl_set_hidden(quick_ID2,GRF_TRUE);
			grf_ctrl_set_hidden(super_strong_ID15,GRF_FALSE);
			i = 1;
			mode_select = GRF_TRUE;
		}
	}

	if (mode_select) {
		if (i >21) {
			//grf_printf("跳转到超强自清洁除菌液制备中\n");
			i = 1;
			ytl_mode_select_uart = 2;
			grf_view_set_dis_view(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID);
		}
		grf_img_set_src(super_strong_countdown_ID18, mode_select_countdown[i]);
		++i;
	}
	else {
		if (i >21) {
			//grf_printf("跳转到快速自清洁除菌液制备中\n");
			i = 1;
			ytl_mode_select_uart = 1;
			grf_view_set_dis_view(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID);
		}
		grf_img_set_src(quick_countdown_ID11, mode_select_countdown[i]);
		++i;
	}
}


void task_create09()
{
	//grf_printf("task_create9\n");

	//获取控件
	quick_ID2 = grf_ctrl_get_form_id(GRF_VIEW09_SELF_CLEANING_MODE_ID,VIEW09_SELF_CLEANING_MODE_IMAGE1_ID);
	super_strong_ID15 = grf_ctrl_get_form_id(GRF_VIEW09_SELF_CLEANING_MODE_ID,VIEW09_SELF_CLEANING_MODE_IMAGE3_ID);
	quick_countdown_ID11 = grf_ctrl_get_form_id(GRF_VIEW09_SELF_CLEANING_MODE_ID,VIEW09_SELF_CLEANING_MODE_IMAGE4_ID);
	super_strong_countdown_ID18 = grf_ctrl_get_form_id(GRF_VIEW09_SELF_CLEANING_MODE_ID,VIEW09_SELF_CLEANING_MODE_IMAGE5_ID);

	//第一次进入显示的界面
	first_display();

	//创建任务
	key_task09 = grf_task_create(key_task09_cb,100,NULL);

	//进入自清洁模式时,判断是否有故障
	ytl_fault_get();
}


void task_del09()
{
	j_self_cleaning_var = 0;
	uart_only_sent_once_self_cleaning_var = 2;
	//grf_printf("task_del09\n");
	grf_task_del(key_task09);
}
