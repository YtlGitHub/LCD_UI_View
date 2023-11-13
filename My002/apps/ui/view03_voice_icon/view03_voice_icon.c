#include "../../apps.h"


//创建任务
grf_task_t *voice_task3 = NULL;


//创建控件名
grf_ctrl_t* voice_image1 = NULL;


//创建数组：里面保存图片位置及名字
//u8 *img_src1[] = {"/icon/yingliangguan.png","/icon/foot-icon-volume1.png"};
u8 *img_src1[] = {"/icon/volume0.png","/icon/volume1.png","/icon/volume2.png","/icon/volume3.png"};


//音量图标
void voice_image_cb()
{
	if (isCmdCompletedBuf[3])
	{
		if (ytl2_voice_image_val == 1)
		{
			grf_img_set_src(voice_image1,img_src1[ytl2_voice_image_val]);
		}
		else if (ytl2_voice_image_val == 2)
		{
			grf_img_set_src(voice_image1,img_src1[ytl2_voice_image_val]);
		}
		else if (ytl2_voice_image_val == 3)
		{
			grf_img_set_src(voice_image1,img_src1[ytl2_voice_image_val]);
		}
		else
		{
			grf_img_set_src(voice_image1,img_src1[ytl2_voice_image_val]);
		}
		isCmdCompletedBuf[3] = GRF_FALSE;
	}
	if (ytl_help) {
		ytl_help = GRF_FALSE;
		if (ytl_view_get_cur_id != GRF_VIEW09_SELF_CLEANING_MODE_ID) {
			grf_view_set_dis_view(GRF_VIEW12_HELP_ID);
		}
	}
}


//创建任务
void task_create03()
{
	grf_printf("task_create3\n");

	//获取控件名
	voice_image1 = grf_ctrl_get_form_id(GRF_VIEW03_VOICE_ICON_ID, VIEW03_VOICE_ICON_IMAGE0_ID);

	//创建任务名
	voice_task3 = grf_task_create(voice_image_cb,100,NULL);  //创建音量图标任务

	//立即刷新页面,不显示默认页面
	grf_task_ready(voice_task3);
}


//删除任务
void task_del03()
{
	grf_printf("task_create3\n");
	grf_task_del(voice_task3);
}
