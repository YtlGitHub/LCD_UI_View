#include "../../apps.h"


//创建按键任务
grf_task_t *key_task10_01 = NULL;
grf_task_t *please_clean_the_dirty_water_tank_task = NULL;


//创建控件名
grf_ctrl_t *please_clean_the_dirty_water_tank_name_ID1 = NULL;  //请清理污水箱轮播图控件名


//自定义变量
static u8 i = 0;  //控制循环跑动变量


//自定义数组
static u8 *fault_image_name5[36] = {
	"/fault/5_00.png",
	"/fault/5_01.png",
	"/fault/5_02.png",
	"/fault/5_03.png",
	"/fault/5_04.png",
	"/fault/5_05.png",
	"/fault/5_06.png",
	"/fault/5_07.png",
	"/fault/5_08.png",
	"/fault/5_09.png",
	"/fault/5_10.png",
	"/fault/5_11.png",
	"/fault/5_12.png",
	"/fault/5_13.png",
	"/fault/5_14.png",
	"/fault/5_15.png",
	"/fault/5_16.png",
	"/fault/5_17.png",
	"/fault/5_18.png",
	"/fault/5_19.png",
	"/fault/5_20.png",
	"/fault/5_21.png",
	"/fault/5_22.png",
	"/fault/5_23.png",
	"/fault/5_24.png",
	"/fault/5_25.png",
	"/fault/5_26.png",
	"/fault/5_27.png",
	"/fault/5_28.png",
	"/fault/5_29.png",
	"/fault/5_30.png",
	"/fault/5_31.png",
	"/fault/5_32.png",
	"/fault/5_33.png",
	"/fault/5_34.png",
	"/fault/5_35.png"
};  //请清理污水箱


//第一次进入
static void first_display(void)
{
	i = 1;
}


//请清理污水箱,避免异味动图操作
void please_clean_the_dirty_water_tank_task_cb()
{
	if (isCmdCompletedBuf[12])
	{
		i++;
		if (i == 1) {
			//grf_printf("语言播报：请清理污水箱，避免异味\n");
		}
		else if (i > 0 && i <= 35)
		{
			grf_img_set_src(please_clean_the_dirty_water_tank_name_ID1, fault_image_name5[i]);
		}
		else if (i > 35 && i <= 51)
		{
			grf_img_set_src(please_clean_the_dirty_water_tank_name_ID1, fault_image_name5[i-16]);
		}
		else if (i > 51 && i <= 67)
		{
			grf_img_set_src(please_clean_the_dirty_water_tank_name_ID1, fault_image_name5[i-32]);
		}
		else if (i > 67 && i <= 80)
		{
			grf_img_set_src(please_clean_the_dirty_water_tank_name_ID1, fault_image_name5[88-i]);
		}
		else
		{
			i = 0;
			isCmdCompletedBuf[12] = GRF_FALSE;
		}
	}
}


//按键操作
void key_task10_01_cb(){
	if (ytl_self_cleaning) {
		ytl_self_cleaning = GRF_FALSE;
		//grf_printf("重新再次自清洁\n");
		grf_view_set_dis_view(GRF_VIEW09_SELF_CLEANING_MODE_ID);  //重新再次自清洁
	}
}

void task_create10_01()
{
	//grf_printf("task_create10_01\n");

	//获取控件
	please_clean_the_dirty_water_tank_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID,VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_IMAGE0_ID);

	first_display();

	//创建任务
	key_task10_01 = grf_task_create(key_task10_01_cb,100,NULL);
	please_clean_the_dirty_water_tank_task = grf_task_create(please_clean_the_dirty_water_tank_task_cb,100,NULL);

	//立即执行
	grf_task_ready(please_clean_the_dirty_water_tank_task);
}

void task_del10_01()
{
	//grf_printf("task_del10\n");
	grf_task_del(key_task10_01);
	grf_task_del(please_clean_the_dirty_water_tank_task);
}
