#include "../../apps.h"


//创建任务
grf_task_t *voice_task3 = NULL;


//创建控件名
grf_ctrl_t* voice_image0 = NULL;
grf_ctrl_t* voice_image1 = NULL;
grf_ctrl_t* voice_image2 = NULL;


//自定义变量
u8 ytl_mute_v = 0;  //静音键设置按键太快的丢掉


//创建数组：里面保存图片位置及名字
u8 *img_src1[] = {"/icon/volume0.png","/icon/volume1.png","/icon/volume2.png","/icon/volume3.png"};
//电池图标文件名保存到数组里面
static u8 *image_name_battery_icon[7] = {
	"/charging/chong_icon_dian0.png",
	"/charging/chong_icon_dian0_1.png",
	"/charging/chong_icon_dian1.png",
	"/charging/chong_icon_dian2.png",
	"/charging/chong_icon_dian3.png",
	"/charging/chong_icon_dian4.png",
	"/charging/chong_icon_dian5.png"
};


//快速按静音键时,控制太快的按键丢掉
void control_ytl_mute_v_away(void)
{
	//丢掉太快静音键
	if (ytl_mute_v <= 9) {
		ytl_mute = GRF_FALSE;
		ytl_mute_v++;
//		grf_printf("ytl_mute_v == %d\n",ytl_mute_v);
	}
	else if (ytl_mute_v > 9 && ytl_mute)
	{
		ytl_mute_v = 0;
	}
}


//第一次进入显示的界面
static void first_display()
{
	grf_img_zoom_setting(voice_image2,128);
	if (ytl_view_get_cur_id == GRF_VIEW09_SELF_CLEANING_MODE_ID)
	{
		grf_ctrl_set_hidden(voice_image1,GRF_TRUE);
		grf_ctrl_set_hidden(voice_image2,GRF_FALSE);
		grf_ctrl_set_pos(voice_image0,416,40);
		grf_ctrl_set_pos(voice_image2,350,9);
	}
}


//音量图标
void voice_image_cb()
{
	control_ytl_mute_v_away();  //快速按静音键时,控制太快的按键丢掉
	if (isCmdCompletedBuf[3])
	{
		//grf_printf("ytl2_voice_image_val == %d\n",ytl2_voice_image_val);
		grf_img_set_src(voice_image0,img_src1[ytl2_voice_image_val]);
		isCmdCompletedBuf[3] = GRF_FALSE;
	}
	if (isCmdCompletedBuf[33])
	{
		//grf_printf("isCmdCompletedBuf[33] =ytl_battery_quantity_val= %d\n",ytl_battery_quantity_val);
		if (ytl_view_get_cur_id == GRF_VIEW09_SELF_CLEANING_MODE_ID ||
			ytl_view_get_cur_id == GRF_VIEW10_SELF_CLEANING_ID ||
			ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
		{
			//自清洁模式时显示电量图标和音量图标
			if (ytl_battery_quantity_val < 10 && ytl_battery_quantity_val >= 0)
			{
				grf_img_set_src(voice_image2, image_name_battery_icon[0]);
			}
			else if (ytl_battery_quantity_val < 20 && ytl_battery_quantity_val >= 10)
			{
				grf_img_set_src(voice_image2, image_name_battery_icon[1]);
			}
			else if (ytl_battery_quantity_val < 100 && ytl_battery_quantity_val >= 20)
			{
				if (ytl_battery_quantity_val < 40 && ytl_battery_quantity_val >= 20)
				{
					grf_img_set_src(voice_image2, image_name_battery_icon[2]);
				}
				else if (ytl_battery_quantity_val < 60 && ytl_battery_quantity_val >= 40)
				{
					grf_img_set_src(voice_image2, image_name_battery_icon[3]);
				}
				else if (ytl_battery_quantity_val < 80 && ytl_battery_quantity_val >= 60)
				{
					grf_img_set_src(voice_image2, image_name_battery_icon[4]);
				}
				else if (ytl_battery_quantity_val < 100 && ytl_battery_quantity_val >= 80)
				{
					grf_img_set_src(voice_image2, image_name_battery_icon[5]);
				}
			}
			else if (ytl_battery_quantity_val == 100)
			{
				grf_img_set_src(voice_image2, image_name_battery_icon[6]);
			}
		}
		isCmdCompletedBuf[33] = GRF_FALSE;
	}
}


//创建任务
void task_create03()
{
	//grf_printf("task_create3\n");

	//获取控件名
	voice_image0 = grf_ctrl_get_form_id(GRF_VIEW03_VOICE_ICON_ID, VIEW03_VOICE_ICON_IMAGE0_ID);
	voice_image1 = grf_ctrl_get_form_id(GRF_VIEW03_VOICE_ICON_ID, VIEW03_VOICE_ICON_IMAGE1_ID);
	voice_image2 = grf_ctrl_get_form_id(GRF_VIEW03_VOICE_ICON_ID, VIEW03_VOICE_ICON_IMAGE2_ID);

	first_display();

	//创建任务名
	voice_task3 = grf_task_create(voice_image_cb,100,NULL);  //创建音量图标任务

	//立即刷新页面,不显示默认页面
	grf_task_ready(voice_task3);
}


//删除任务
void task_del03()
{
	//grf_printf("task_del3\n");
	grf_task_del(voice_task3);
}
