#include "../../apps.h"


//创建故障任务
grf_task_t *key_task12 = NULL;


//创建控件名
grf_ctrl_t *help_img_name_ID1 = NULL;  //帮助模式四张选择图片控件名
grf_ctrl_t *help_label_name_ID3 = NULL;  //帮助模式四张选择图片下方文字控件名
grf_ctrl_t *help_label_name_ID4 = NULL;  //帮助模式四张选择图片下方1/4控件名
grf_ctrl_t *help_qrcode_name_ID5 = NULL;  //帮助模式二维码控件名


//自定义变量
static u8 i = 1;  //控制循环轮播帮助模式里面的四张图


//自定义数组
static u8 *help_image_name[4] = {
	"/help/0.png",
	"/help/help_1_00.png",
	"/help/help_2_00.png",
	"/help/help_3_00.png"
};  //帮助模式四张选择图片文件名


//第一次进入显示的界面
static void first_display()
{
	//图片/二维码,显示
	if (i >= 1 && i < 4) {
		grf_ctrl_set_hidden(help_qrcode_name_ID5, GRF_TRUE);  //隐藏二维码
		grf_ctrl_set_hidden(help_img_name_ID1, GRF_FALSE);  //显示图片
		grf_img_set_src(help_img_name_ID1, help_image_name[i]);
	}
	else if (i == 4) {
		grf_ctrl_set_hidden(help_img_name_ID1, GRF_TRUE);  //隐藏图片
		grf_ctrl_set_hidden(help_qrcode_name_ID5, GRF_FALSE);  //显示二维码
	}

	//图片/二维码,下方1/4和文字显示
	if (i == 1)
	{
		grf_label_set_txt(help_label_name_ID3,"#quick_guide");
		grf_label_set_txt(help_label_name_ID4,"1/4");
	}
	else if (i == 2)
	{
		grf_label_set_txt(help_label_name_ID3,"#maintenance_strategy");
		grf_label_set_txt(help_label_name_ID4,"2/4");
	}
	else if (i == 3)
	{
		grf_label_set_txt(help_label_name_ID3,"#removing_handle");
		grf_label_set_txt(help_label_name_ID4,"3/4");
	}
	else if (i == 4)
	{
		grf_label_set_txt(help_label_name_ID3,"#contact_after_sales");
		grf_label_set_txt(help_label_name_ID4,"4/4");
	}
}


//按键操作
void key_task12_cb(){
	if (ytl_right)
	{
		ytl_right = GRF_FALSE;
		grf_printf("右键\n");

		i++;
		if (i > 4)
		{
			i = 1;
		}

		if (i > 0 && i < 4) {
			grf_ctrl_set_hidden(help_img_name_ID1, GRF_FALSE);
			grf_ctrl_set_hidden(help_qrcode_name_ID5, GRF_TRUE);
			grf_img_set_src(help_img_name_ID1,help_image_name[i]);
		}
		else if (i == 4) {
			grf_ctrl_set_hidden(help_img_name_ID1, GRF_TRUE);
			grf_ctrl_set_hidden(help_qrcode_name_ID5, GRF_FALSE);
		}

		if (i == 1)
		{
			grf_label_set_txt(help_label_name_ID3,"#quick_guide");
			grf_label_set_txt(help_label_name_ID4,"1/4");
		}
		else if (i == 2)
		{
			grf_label_set_txt(help_label_name_ID3,"#maintenance_strategy");
			grf_label_set_txt(help_label_name_ID4,"2/4");
		}
		else if (i == 3)
		{
			grf_label_set_txt(help_label_name_ID3,"#removing_handle");
			grf_label_set_txt(help_label_name_ID4,"3/4");
		}
		else if (i == 4)
		{
			grf_label_set_txt(help_label_name_ID3,"#contact_after_sales");
			grf_label_set_txt(help_label_name_ID4,"4/4");
		}
	}
	else if (ytl_confirmation)
	{
		ytl_confirmation = GRF_FALSE;
		if (i == 1)
		{
			grf_view_set_dis_view(GRF_VIEW13_HELP1_ID);  //快速指南
			grf_printf("快速指南 \n");
		}
		else if (i == 2)
		{
			grf_view_set_dis_view(GRF_VIEW14_HELP2_ID);  //保养攻略
			grf_printf("保养攻略 \n");
		}
		else if (i == 3)
		{
			grf_view_set_dis_view(GRF_VIEW15_HELP3_ID);  //拆除手柄
			grf_printf("拆除手柄 \n");
		}
		else if (i == 4)
		{
			grf_view_set_dis_view(GRF_VIEW16_HELP4_ID);  //联系售后
			grf_printf("联系售后 \n");
		}
	}
	else if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("view12:返回键\n");
		grf_view_set_dis_view(ytl_view_get_cur_id);  //在帮助界面返回
	}
}

void task_create12()
{
	grf_printf("task_create12\n");

	//获取控件
	help_img_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW12_HELP_ID,VIEW12_HELP_IMAGE0_ID);
	help_label_name_ID3 = grf_ctrl_get_form_id(GRF_VIEW12_HELP_ID,VIEW12_HELP_LABEL0_ID);
	help_label_name_ID4 = grf_ctrl_get_form_id(GRF_VIEW12_HELP_ID,VIEW12_HELP_LABEL1_ID);
	help_qrcode_name_ID5 = grf_ctrl_get_form_id(GRF_VIEW12_HELP_ID,VIEW12_HELP_QRCODE0_ID);

	first_display();

	//创建任务
	key_task12 = grf_task_create(key_task12_cb,100,NULL);
}

void task_del12()
{
	grf_printf("task_del12\n");
	grf_task_del(key_task12);
}
