#include "../../apps.h"


//创建任务名
grf_task_t *key_task08 = NULL;
grf_task_t *background_red_yellow_green_task = NULL;


//控件名
grf_ctrl_t *battery_icon_5 = NULL;  //电池图标
grf_ctrl_t *label_name_ID6 = NULL;  //低电量文字提示:当前电量过低,请稍后自清洁
grf_ctrl_t *label_battery_name_ID7 = NULL;  //电量图标
//grf_ctrl_t *red_yellow_green_name_ID8 = NULL;  //红黄绿轮播图控件名



//自定义变量
static u8 i = 0;  //控制背景红黄绿圆圈动图显示变量
static u16 j = 0;  //控制息屏
static grf_bool label_name_ID6_bool = GRF_FALSE;  //控制低电量文本提示是否循环跑动
static u8 label_name_ID6_var = 0;  //控制低电量文本提示等多久之后消失


static u8 *image_name_background_red[15] = {
	"/charging/red_00.png",
	"/charging/red_01.png",
	"/charging/red_02.png",
	"/charging/red_03.png",
	"/charging/red_04.png",
	"/charging/red_05.png",
	"/charging/red_06.png",
	"/charging/red_07.png",
	"/charging/red_08.png",
	"/charging/red_09.png",
	"/charging/red_10.png",
	"/charging/red_11.png",
	"/charging/red_12.png",
	"/charging/red_13.png",
	"/charging/red_14.png"
};  //背景红圆圈图片文件名保存到数组里面
static u8 *image_name_background_yellow[15] = {
	"/charging/yellow_00.png",
	"/charging/yellow_01.png",
	"/charging/yellow_02.png",
	"/charging/yellow_03.png",
	"/charging/yellow_04.png",
	"/charging/yellow_05.png",
	"/charging/yellow_06.png",
	"/charging/yellow_07.png",
	"/charging/yellow_08.png",
	"/charging/yellow_09.png",
	"/charging/yellow_10.png",
	"/charging/yellow_11.png",
	"/charging/yellow_12.png",
	"/charging/yellow_13.png",
	"/charging/yellow_14.png"
};  //背景黄圆圈图片文件名保存到数组里面
static u8 *image_name_background_green[15] = {
	"/charging/green_00.png",
	"/charging/green_01.png",
	"/charging/green_02.png",
	"/charging/green_03.png",
	"/charging/green_04.png",
	"/charging/green_05.png",
	"/charging/green_06.png",
	"/charging/green_07.png",
	"/charging/green_08.png",
	"/charging/green_09.png",
	"/charging/green_10.png",
	"/charging/green_11.png",
	"/charging/green_12.png",
	"/charging/green_13.png",
	"/charging/green_14.png"
};  //背景绿圆圈图片文件名保存到数组里面
static u8 *image_name_battery_icon[7] = {
	"/charging/chong_icon_dian0.png",
	"/charging/chong_icon_dian0_1.png",
	"/charging/chong_icon_dian1.png",
	"/charging/chong_icon_dian2.png",
	"/charging/chong_icon_dian3.png",
	"/charging/chong_icon_dian4.png",
	"/charging/chong_icon_dian5.png"
};  //电池图标文件名保存到数组里面

static u8 label_battery_name_ID7_variable[1];  //电量消息值


//背景红橙绿动图显示
void background_red_yellow_green_task_cb()
{
	control_ytl_mute_v_away();  //快速按静音键时,控制太快的按键丢掉
	if (isCmdCompletedBuf[8])
	{
		i++;
		if (i > 14) {
			i=1;
		}
		//grf_printf("i == %d\n",i);

		sprintf(label_battery_name_ID7_variable, "%d",ytl_battery_quantity_val);
		grf_label_set_txt(label_battery_name_ID7, label_battery_name_ID7_variable);

		if (ytl_battery_quantity_val < 10 && ytl_battery_quantity_val >= 0)
		{
			grf_view_set_bg(GRF_VIEW08_CHARGING_ID,image_name_background_red[i]);
			grf_img_set_src(battery_icon_5, image_name_battery_icon[0]);
		}
		else if (ytl_battery_quantity_val < 20 && ytl_battery_quantity_val >= 10)
		{
			grf_view_set_bg(GRF_VIEW08_CHARGING_ID,image_name_background_yellow[i]);
			grf_img_set_src(battery_icon_5, image_name_battery_icon[1]);
		}
		else if (ytl_battery_quantity_val < 100 && ytl_battery_quantity_val >= 20)
		{
			grf_view_set_bg(GRF_VIEW08_CHARGING_ID,image_name_background_green[i]);
			if (ytl_battery_quantity_val < 40 && ytl_battery_quantity_val >= 20)
			{
				grf_img_set_src(battery_icon_5, image_name_battery_icon[2]);
			}
			else if (ytl_battery_quantity_val < 60 && ytl_battery_quantity_val >= 40)
			{
				grf_img_set_src(battery_icon_5, image_name_battery_icon[3]);
			}
			else if (ytl_battery_quantity_val < 80 && ytl_battery_quantity_val >= 60)
			{
				grf_img_set_src(battery_icon_5, image_name_battery_icon[4]);
			}
			else if (ytl_battery_quantity_val < 100 && ytl_battery_quantity_val >= 80)
			{
				grf_img_set_src(battery_icon_5, image_name_battery_icon[5]);
			}
		}
		else if (ytl_battery_quantity_val == 100)
		{
			grf_view_set_bg(GRF_VIEW08_CHARGING_ID,image_name_background_green[1]);
			grf_img_set_src(battery_icon_5, image_name_battery_icon[6]);
			isCmdCompletedBuf[8] = GRF_FALSE;
		}
	}
	//暗屏倒计时1分钟
	if(j <= 600)  //1minx60s = 60s x 1000ms = 60000ms / 100 = 600
	{
		if (j>550)
		{
			grf_disp_set_bright(650-j);
		}
		j++;
	}
	//电量满了100等4分钟就自动息屏 4minx60s = 240s x 1000ms = 240000ms / 100 = 2400
	if(ytl_battery_quantity_val == 100)
	{
		if (j > 600 && j <= 2400)
		{
			/*
			if(j >= 2351 && j <= 2400)
			{
				grf_disp_set_bright(2400-j);
			}
			*/
			if(j >= 2351 && j <= 2390)
			{
				grf_disp_set_bright(2400-j);
			}
			else if (j == 2400) {
				grf_disp_set_bright(0);
			}
			j++;
		}
	}
	//如果在充电界面且息屏状态，按任意键，背光亮起
	if (isCmdCompletedBuf[88])
	{
		isCmdCompletedBuf[88] = GRF_FALSE;
		grf_disp_set_bright(100);
		j = 0;
	}
}

//按键操作
void key_task08_cb(){
	//按自清洁键如果音量低于20%就提示，当前电量过低请稍后自清洁
	if (label_name_ID6_bool) {
		label_name_ID6_var++;
		if (label_name_ID6_var > 100) {
			grf_ctrl_set_hidden(label_name_ID6,GRF_TRUE);
			label_name_ID6_var = 0;
			label_name_ID6_bool = GRF_FALSE;
		}
	}

	if (ytl_self_cleaning) {
		ytl_self_cleaning = GRF_FALSE;
		if (ytl_battery_quantity_val >= 20  && ytl_battery_quantity_val <= 100) {
			grf_view_set_dis_view(GRF_VIEW09_SELF_CLEANING_MODE_ID);
		}
		else {
			//语音播报:"当前电量过低,请稍后自清洁。"
			switch_language_pack("08_01_Please_clean_yourself_later");
			grf_ctrl_set_hidden(label_name_ID6,GRF_FALSE);
			label_name_ID6_bool = GRF_TRUE;
		}
	}
}


void task_create08()
{
	//grf_printf("task_create8\n");

	//获取控件
	battery_icon_5 = grf_ctrl_get_form_id(GRF_VIEW08_CHARGING_ID, VIEW08_CHARGING_IMAGE4_ID);
	label_name_ID6 = grf_ctrl_get_form_id(GRF_VIEW08_CHARGING_ID, VIEW08_CHARGING_LABEL0_ID);
	label_battery_name_ID7 = grf_ctrl_get_form_id(GRF_VIEW08_CHARGING_ID, VIEW08_CHARGING_LABEL1_ID);


	//grf_img_set_rotate_angel(grf_view_get_cur_id(GRF_LAYER_UI),180);

	//创建任务
	key_task08 = grf_task_create(key_task08_cb,100,NULL);  //按键任务
	background_red_yellow_green_task = grf_task_create(background_red_yellow_green_task_cb, 100, NULL);  //背景红橙绿动图显示任务

	//不等待时间,立即执行
	grf_task_ready(background_red_yellow_green_task);
}


void task_del08()
{
	//grf_printf("task_del08\n");

	grf_task_del(key_task08);
	grf_task_del(background_red_yellow_green_task);
	grf_ctrl_set_hidden(label_name_ID6,GRF_TRUE);  //隐藏label低电量提示文字：当前电量过低，请稍后自清洁
}
