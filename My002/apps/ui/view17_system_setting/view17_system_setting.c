#include "../../apps.h"


#define mode_select_icon_x0 200  //模式选择图标img0x坐标
#define mode_select_icon_x1 400  //模式选择图标img1x坐标
#define mode_select_icon_x2 201  //模式选择图标img2x坐标
#define mode_select_icon_x3 0  //模式选择图标img3x坐标
#define mode_select_icon_y 0  //模式选择图标y坐标
#define switch_speed 300  //切换速度
#define scale 256  //图大小缩放:256原大小,128缩小一倍,512放大一倍
#define scaling 0.6  //缩放比例


//创建任务名
grf_task_t *key_task17 = NULL;  //创建按键任务名


//创建控件名
static grf_ctrl_t *img0 = NULL;  //滚刷照明
static grf_ctrl_t *img0_label = NULL;  //滚刷照明，开、关中间下方文字显示
static grf_ctrl_t *img1 = NULL;  //清洁方式：清水或溶液
static grf_ctrl_t *img1_label = NULL;  //清水或溶液中间下方文字显示
static grf_ctrl_t *img2 = NULL;  //语言音量
static grf_ctrl_t *img2_label = NULL;  //音量大小中间下方文字显示：关，低，中，高
static grf_ctrl_t *img3 = NULL;  //切换语言
static grf_ctrl_t *img3_label = NULL;  //语言中间下方文字显示
static grf_ctrl_t *cont0 = NULL;  //容器
static grf_ctrl_t *system_setting_label_name_ID1 = NULL;  //创建系统设置里面的下方文字显示控件名


//自定义变量
static u8 i = 1;  //控制系统设置1-4循环轮播图


//自定义数组
static u8 *select_mode_array1[9] =
{
		"/system_setting/1_1_off.png",
		"/system_setting/1_1_on.png",
		"/system_setting/2_1_water.png",
		"/system_setting/2_1_solution.png",
		"/system_setting/3_1_0.png",
		"/system_setting/3_1_1.png",
		"/system_setting/3_1_2.png",
		"/system_setting/3_1_3.png",
		"/system_setting/4_1.png",
};
static u8 *select_mode_array2[9] =
{
		"/system_setting/1_2_off.png",
		"/system_setting/1_2_on.png",
		"/system_setting/2_2_water.png",
		"/system_setting/2_2_solution.png",
		"/system_setting/3_2_0.png",
		"/system_setting/3_2_1.png",
		"/system_setting/3_2_2.png",
		"/system_setting/3_2_3.png",
		"/system_setting/4_2.png",
};
static u8 *system_setting_value_array[4] = {"#roller_brush_lighting","#cleaning_method","#voice_volume","#switch_language"};


//自定义函数
static void anim_img_pos(void* var, u16 v)
{
	grf_ctrl_set_pos(var, v, mode_select_icon_y);
}
static void anim_img_zoom(void* var, u32 v)
{
	grf_img_zoom_setting(var, v);
}
static void anim_label_zoom(void* var, u32 v)
{
	grf_ctrl_zoom_set(var, v);
}
//设置旋转或缩放中心
static void set_img_label_pivot()
{
	u8 img_pivot_x = 200;
	u16 img_pivot_y = 350;
	u16 label_pivot_x = 106;
	grf_img_set_pivot(img0, img_pivot_x, img_pivot_y);
	grf_img_set_pivot(img1, img_pivot_x, img_pivot_y);
	grf_img_set_pivot(img2, img_pivot_x, img_pivot_y);
	grf_img_set_pivot(img3, img_pivot_x, img_pivot_y);
	grf_ctrl_zoom_pivot(img0_label, img_pivot_x-grf_ctrl_get_x(img0_label), img_pivot_y - grf_ctrl_get_y(img0_label));
	grf_ctrl_zoom_pivot(img1_label, img_pivot_x-grf_ctrl_get_x(img1_label), img_pivot_y - grf_ctrl_get_y(img1_label));
	grf_ctrl_zoom_pivot(img2_label, img_pivot_x-grf_ctrl_get_x(img2_label), img_pivot_y - grf_ctrl_get_y(img2_label));
	grf_ctrl_zoom_pivot(img3_label, img_pivot_x-grf_ctrl_get_x(img3_label), img_pivot_y - grf_ctrl_get_y(img3_label));
}

//第一次进入显示的界面
static void first_display()
{
	grf_printf("第一次进入显示的界面\n");
	i = 1;
	grf_ctrl_move_forground(img0);
	grf_ctrl_move_background(img3);

	grf_img_zoom_setting(img0,scale);
	grf_img_zoom_setting(img1,scale*scaling);
	grf_img_zoom_setting(img2,scale*scaling);
	grf_img_zoom_setting(img3,scale*scaling);

	anim_label_zoom(img0_label,scale);
	anim_label_zoom(img1_label,scale*scaling);
	anim_label_zoom(img2_label,scale*scaling);
	anim_label_zoom(img3_label,scale*scaling);

	grf_ctrl_set_pos(img0,mode_select_icon_x0,mode_select_icon_y);
	grf_ctrl_set_pos(img1,mode_select_icon_x1,mode_select_icon_y);
	grf_ctrl_set_pos(img2,mode_select_icon_x2,mode_select_icon_y);
	grf_ctrl_set_pos(img3,mode_select_icon_x3,mode_select_icon_y);

	//滚刷照明
	if (ytl0_roller_brush_lighting) {
		grf_img_set_src(img0, select_mode_array1[1]);
		grf_label_set_txt(img0_label, "#on");
		grf_label_set_txt_color(img0_label, GRF_COLOR_WHITE);
	}
	else {
		grf_img_set_src(img0, select_mode_array1[0]);
		grf_label_set_txt(img0_label, "#off");
		grf_label_set_txt_color(img0_label, GRF_COLOR_GET(0x52,0x84,0xdd));
	}

	//清洁方式
	if (ytl1_cleaning_method) {
		grf_img_set_src(img1, select_mode_array2[3]);
		grf_label_set_txt(img1_label, "#solution");
		grf_label_set_txt_color(img1_label, GRF_COLOR_GET(0xb0,0xfe,0xff));
	}
	else {
		grf_img_set_src(img1, select_mode_array2[2]);
		grf_label_set_txt(img1_label, "#water");
		grf_label_set_txt_color(img1_label, GRF_COLOR_GET(0xb0,0xce,0xdf));
	}

	//语音音量
	if (ytl2_voice_image_val == 0) {
		grf_img_set_src(img2, select_mode_array2[4]);
		grf_label_set_txt(img2_label, "#off");
		grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
	}
	else if (ytl2_voice_image_val == 1) {
		grf_img_set_src(img2, select_mode_array2[5]);
		grf_label_set_txt(img2_label, "#low");
		grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
	}
	else if (ytl2_voice_image_val == 2){
		grf_img_set_src(img2, select_mode_array2[6]);
		grf_label_set_txt(img2_label, "#medium");
		grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xf9,0x8a,0x13));
	}
	else if (ytl2_voice_image_val == 3){
		grf_img_set_src(img2, select_mode_array2[7]);
		grf_label_set_txt(img2_label, "#high");
		grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xdb,0x50,0x5b));
	}

	//切换语言
	if (ytl3_switch_language == 0) {
		grf_img_set_src(img3, select_mode_array2[8]);
		grf_label_set_txt(img3_label, "#language");
	}
	else if (ytl3_switch_language == 1) {
		grf_img_set_src(img3, select_mode_array2[8]);
		grf_label_set_txt(img3_label, "#language");
	}

	set_img_label_pivot();

	grf_label_set_txt(system_setting_label_name_ID1, system_setting_value_array[i-1]);  //1滚刷照明,2语音音量,3清洁方式,4切换语言
}


//切换高亮显示
static void switch_highlight()
{
	if (i == 1) {
		//滚刷照明
		if (ytl0_roller_brush_lighting) {
			grf_img_set_src(img0, select_mode_array1[1]);
		}
		else {
			grf_img_set_src(img0, select_mode_array1[0]);
		}

		//切换语言
		grf_img_set_src(img3, select_mode_array2[8]);
	}
	else if (i == 2) {
		//清洁方式
		if (ytl1_cleaning_method) {
			grf_img_set_src(img1, select_mode_array1[3]);
			grf_label_set_txt_size(img1_label,50);
		}
		else {
			grf_img_set_src(img1, select_mode_array1[2]);
			grf_label_set_txt_size(img1_label,50);
		}

		//滚刷照明
		if (ytl0_roller_brush_lighting) {
			grf_img_set_src(img0, select_mode_array2[1]);
		}
		else {
			grf_img_set_src(img0, select_mode_array2[0]);
		}
	}
	else if (i == 3)
	{
		//语言音量
		if (ytl2_voice_image_val == 0)
		{
			grf_img_set_src(img2, select_mode_array1[4]);
		}
		if (ytl2_voice_image_val == 1)
		{
			grf_img_set_src(img2, select_mode_array1[5]);
		}
		else if (ytl2_voice_image_val == 2)
		{
			grf_img_set_src(img2, select_mode_array1[6]);
		}
		else if (ytl2_voice_image_val == 3)
		{
			grf_img_set_src(img2, select_mode_array1[7]);
		}

		//清洁方式
		if (ytl1_cleaning_method)
		{
			grf_img_set_src(img1, select_mode_array2[3]);
		}
		else
		{
			grf_img_set_src(img1, select_mode_array2[2]);
		}
	}
	else if (i == 4)
	{
		//切换语言
		grf_img_set_src(img3, select_mode_array1[8]);

		//语言音量
		if (ytl2_voice_image_val == 0)
		{
			grf_img_set_src(img2, select_mode_array2[4]);
		}
		if (ytl2_voice_image_val == 1)
		{
			grf_img_set_src(img2, select_mode_array2[5]);
		}
		else if (ytl2_voice_image_val == 2)
		{
			grf_img_set_src(img2, select_mode_array2[6]);
		}
		else if (ytl2_voice_image_val == 3)
		{
			grf_img_set_src(img2, select_mode_array2[7]);
		}
	}
	set_img_label_pivot();
}

//开关语音播报
static void on_off_Voice_broadcast()
{
	//语音播报
	if (ytl2_voice_image_val == 0)
	{
		switch_language_pack("17_00");  //关闭语音
	}
	else if (ytl2_voice_image_val == 1)
	{
		switch_language_pack("17_01");  //开启语音
	}
}
static u8 ytl_confirmation_v = 0;  //确认键设置按键太快的失灵掉
//按键任务
void key_task17_cb()
{
	control_key_failure();
	if (ytl_confirmation_v <= 2) {
		ytl_confirmation = GRF_FALSE;
		ytl_confirmation_v++;
		grf_printf("ytl_confirmation_v\n",ytl_confirmation_v);
	}
	else if (ytl_confirmation_v > 2 && ytl_confirmation)
	{
		ytl_confirmation_v = 0;
	}
	if (ytl_right)
	{
		grf_printf("grf_ctrl_get_child_sum(cont0); == %d\n",grf_ctrl_get_child_sum(cont0));
		//grf_printf("ytl_right == %d",ytl_right);
		ytl_right = GRF_FALSE;

		for(u8 var=0;var<4;var++)
		{
			grf_ctrl_t *obj=grf_ctrl_get_child(cont0,var);
			grf_printf("grf_ctrl_get_x(%d)==%d\n",var,grf_ctrl_get_x(obj));
			grf_printf("grf_ctrl_get_y(%d)==%d\n",var,grf_ctrl_get_y(obj));

			//图片缩放
			if(grf_ctrl_get_x(obj)==mode_select_icon_x0)
				grf_animation_set(obj, switch_speed,0,0,mode_select_icon_x0,mode_select_icon_x3,anim_img_pos,scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x1)
				grf_animation_set(obj, switch_speed,0,0,mode_select_icon_x1,mode_select_icon_x0,anim_img_pos,scaling*scale,scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x2)
				grf_animation_set(obj, switch_speed,0,0,mode_select_icon_x2,mode_select_icon_x1,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x3)
				grf_animation_set(obj, switch_speed,0,0,mode_select_icon_x3,mode_select_icon_x2,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
			//文字缩放
			if(grf_ctrl_get_x(img0)==mode_select_icon_x0)
				grf_animation_set(img0_label, switch_speed, 0,0,0,0,NULL, scale, scale*scaling, anim_label_zoom);
			else if(grf_ctrl_get_x(img0)==mode_select_icon_x1)
				grf_animation_set(img0_label, switch_speed, 0,0,0,0,NULL, scale*scaling, scale, anim_label_zoom);

			if(grf_ctrl_get_x(img1)==mode_select_icon_x0)
				grf_animation_set(img1_label, switch_speed, 0,0,0,0,NULL, scale, scale*scaling, anim_label_zoom);
			else if(grf_ctrl_get_x(img1)==mode_select_icon_x1)
				grf_animation_set(img1_label, switch_speed, 0,0,0,0,NULL, scale*scaling, scale, anim_label_zoom);

			if(grf_ctrl_get_x(img2)==mode_select_icon_x0)
				grf_animation_set(img2_label, switch_speed, 0,0,0,0,NULL, scale, scale*scaling, anim_label_zoom);
			else if(grf_ctrl_get_x(img2)==mode_select_icon_x1)
				grf_animation_set(img2_label, switch_speed, 0,0,0,0,NULL, scale*scaling, scale, anim_label_zoom);

			if(grf_ctrl_get_x(img3)==mode_select_icon_x0)
				grf_animation_set(img3_label, switch_speed, 0,0,0,0,NULL, scale, scale*scaling, anim_label_zoom);
			else if(grf_ctrl_get_x(img3)==mode_select_icon_x1)
				grf_animation_set(img3_label, switch_speed, 0,0,0,0,NULL, scale*scaling, scale, anim_label_zoom);

			grf_ctrl_update_location(obj);
		}
		grf_ctrl_update_location(cont0);
		for(u8 var=0;var<4;var++)
		{
			grf_ctrl_t *obj=grf_ctrl_get_child(cont0,var);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x2)
			{
				grf_ctrl_move_background(obj);

			}
			if(grf_ctrl_get_x(obj)==mode_select_icon_x1)
			{
				grf_ctrl_move_forground(obj);
			}
		}
		i++;
		if (i > 4) {
			i = 1;
		}
		grf_printf("右键值i == %d\n",i);
		switch_highlight();
		grf_label_set_txt(system_setting_label_name_ID1, system_setting_value_array[i-1]);  //1滚刷照明,2语音音量,3清洁方式,4切换语言
	}
	else if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("ytl_back_task1 == %d",ytl_back);
		grf_view_set_dis_view(ytl_view_get_cur_id);
	}
	else if (ytl_confirmation)
	{
		ytl_confirmation = GRF_FALSE;
		if (i == 1)
		{
			//滚刷照明
			if (ytl0_roller_brush_lighting)
			{
				grf_printf("ytl0_roller_brush_lighting == GRF_FALSE \n");
				grf_img_set_src(img0, select_mode_array1[0]);
				grf_label_set_txt(img0_label, "#off");
				grf_label_set_txt_color(img0_label, GRF_COLOR_GET(0x52,0x84,0xdd));
				ytl0_roller_brush_lighting = GRF_FALSE;
				//发送串口数据
				grf_reg_com_send(0x05, 0xC0, 0x01, 0x00, 0);
			}
			else
			{
				grf_printf("ytl0_roller_brush_lighting == GRF_TRUE \n");
				grf_img_set_src(img0, select_mode_array1[1]);
				grf_label_set_txt(img0_label, "#on");
				grf_label_set_txt_color(img0_label, GRF_COLOR_WHITE);
				ytl0_roller_brush_lighting = GRF_TRUE;
				//发送串口数据
				grf_reg_com_send(0x05, 0xC0, 0x01, 0x01, 0);
			}

		}
		else if (i == 2)
		{
			//清洁方式
			if (ytl1_cleaning_method)
			{
				grf_img_set_src(img1, select_mode_array1[2]);
				grf_label_set_txt(img1_label, "#water");
				grf_label_set_txt_color(img1_label, GRF_COLOR_GET(0xb0,0xce,0xdf));
				ytl1_cleaning_method = GRF_FALSE;
			}
			else
			{
				grf_img_set_src(img1, select_mode_array1[3]);
				grf_label_set_txt(img1_label, "#solution");
				grf_label_set_txt_color(img1_label, GRF_COLOR_GET(0xb0,0xfe,0xff));

				ytl1_cleaning_method = GRF_TRUE;
			}
		}
		else if (i == 3)
		{
			//语音音量
			if (ytl2_voice_image_val == 0)
			{
				grf_img_set_src(img2, select_mode_array1[5]);  //音量低
				grf_label_set_txt(img2_label, "#low");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 1;
			}
			else if (ytl2_voice_image_val == 1)
			{
				grf_img_set_src(img2, select_mode_array1[6]);  //音量中
				grf_label_set_txt(img2_label, "#medium");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xf9,0x8a,0x13));
				ytl2_voice_image_val = 2;
			}
			else if (ytl2_voice_image_val == 2)
			{
				grf_img_set_src(img2, select_mode_array1[7]);  //音量高
				grf_label_set_txt(img2_label, "#high");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xdb,0x50,0x5b));
				ytl2_voice_image_val = 3;
			}
			else if (ytl2_voice_image_val == 3)
			{
				grf_img_set_src(img2, select_mode_array1[4]);  //音量关
				grf_label_set_txt(img2_label, "#off");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 0;
			}
			//如果是从高音量到关,就高音量播报关闭语音,如果是从关音量到底音量就底音量播报开启语音,否则其他音量就当前音量播报按键音效
			if (ytl2_voice_image_val == 0)
			{
				on_off_Voice_broadcast();
				volume_size();
			}
			else if(ytl2_voice_image_val == 1)
			{
				volume_size();
				on_off_Voice_broadcast();
			}
			else
			{
				volume_size();
				key_sound_tr660r_wavplay("dongPart002");  //按键音效
			}
		}
		else if (i == 4)
		{
			//语言切换
			if (ytl3_switch_language == 0)
			{
				grf_lang_set("en");
				ytl3_switch_language = 1;
			}
			else if (ytl3_switch_language == 1)
			{
				grf_lang_set("zh");
				ytl3_switch_language = 0;
			}
		}
		save_system_settings_var();
	}
	else if (ytl_help) {
		ytl_help = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);
	}
	else if (ytl_mute)
	{
		ytl_mute = GRF_FALSE;
		if (i == 3)
		{
			//语音音量
			if (ytl2_voice_image_val == 0)
			{
				grf_img_set_src(img2, select_mode_array1[5]);  //音量低
				grf_label_set_txt(img2_label, "#low");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 1;
			}
			else if (ytl2_voice_image_val == 1)
			{
				grf_img_set_src(img2, select_mode_array1[6]);  //音量中
				grf_label_set_txt(img2_label, "#medium");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xf9,0x8a,0x13));
				ytl2_voice_image_val = 2;
			}
			else if (ytl2_voice_image_val == 2)
			{
				grf_img_set_src(img2, select_mode_array1[7]);  //音量高
				grf_label_set_txt(img2_label, "#high");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xdb,0x50,0x5b));
				ytl2_voice_image_val = 3;
			}
			else if (ytl2_voice_image_val == 3)
			{
				grf_img_set_src(img2, select_mode_array1[4]);  //音量关
				grf_label_set_txt(img2_label, "#off");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 0;
			}
		}
		else {
			if (ytl2_voice_image_val == 0)
			{
				grf_img_set_src(img2, select_mode_array2[5]);  //音量低
				grf_label_set_txt(img2_label, "#low");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 1;
			}
			else if (ytl2_voice_image_val == 1)
			{
				grf_img_set_src(img2, select_mode_array2[6]);  //音量中
				grf_label_set_txt(img2_label, "#medium");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xf9,0x8a,0x13));
				ytl2_voice_image_val = 2;
			}
			else if (ytl2_voice_image_val == 2)
			{
				grf_img_set_src(img2, select_mode_array2[7]);  //音量高
				grf_label_set_txt(img2_label, "#high");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0xdb,0x50,0x5b));
				ytl2_voice_image_val = 3;
			}
			else if (ytl2_voice_image_val == 3)
			{
				grf_img_set_src(img2, select_mode_array2[4]);  //音量关
				grf_label_set_txt(img2_label, "#off");
				grf_label_set_txt_color(img2_label, GRF_COLOR_GET(0x38,0xb2,0xef));
				ytl2_voice_image_val = 0;
			}
			//设置旋转或缩放中心
			grf_img_set_pivot(img2,200,350);
			grf_ctrl_zoom_pivot(img2_label, 200-grf_ctrl_get_x(img2_label), 350 - grf_ctrl_get_y(img2_label));
		}
		//如果是从高音量到关,就高音量播报关闭语音,如果是从关音量到底音量就底音量播报开启语音,否则其他音量就当前音量播报按键音效
		if (ytl2_voice_image_val == 0)
		{
			on_off_Voice_broadcast();
			volume_size();
		}
		else if(ytl2_voice_image_val == 1)
		{
			volume_size();
			on_off_Voice_broadcast();
		}
		else
		{
			volume_size();
			key_sound_tr660r_wavplay("dongPart002");  //按键音效
		}
		save_system_settings_var();
	}
}


void task_create17()
{
	grf_printf("task_create17--key_task17 == %p\n",key_task17);

	//获取控件
	img0 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_IMAGE0_ID);
	img0_label = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_LABEL3_ID);
	img1 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_IMAGE1_ID);
	img1_label = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_LABEL4_ID);
	img2 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_IMAGE2_ID);
	img2_label = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_LABEL5_ID);
	img3 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_IMAGE3_ID);
	img3_label = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_LABEL6_ID);
	cont0 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_CONTAINER0_ID);
	system_setting_label_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW17_SYSTEM_SETTING_ID, VIEW17_SYSTEM_SETTING_LABEL0_ID);  //获取系统设置里面的下方文字显示控件

	first_display();

	//创建按键任务
	key_task17 = grf_task_create(key_task17_cb,100,NULL);
}


void task_del17(void)
{
	grf_printf("task_del017\n");
	grf_task_del(key_task17);
}
