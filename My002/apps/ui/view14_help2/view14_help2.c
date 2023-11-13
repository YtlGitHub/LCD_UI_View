#include "../../apps.h"


//创建任务
grf_task_t *key_task14 = NULL;  //创建按键任务
grf_task_t *maintenance_strategy_task = NULL;  //创建保养攻略任务


//创建控件名
grf_ctrl_t *maintenance_strategy_img_name_ID1 = NULL;  //保养攻略顺序蓝色图片控件名
grf_ctrl_t *maintenance_strategy_label1_name_ID2 = NULL;  //保养攻略数字第几步控件名
grf_ctrl_t *maintenance_strategy_label2_name_ID3 = NULL;  //保养攻略第几步说明文字显示控件名

grf_ctrl_t *container0_img_name_ID6 = NULL;  //1/3容器控件名显示
grf_ctrl_t *CTRB_RBC_img_name_ID8 = NULL;  //请清理滚刷机身图控件名
grf_ctrl_t *CTRB_RBC_img_name_ID9 = NULL;  //滚刷图控件名
grf_ctrl_t *CTRB_RBC_img_name_ID10 = NULL;  //滚刷盖图控件名
grf_ctrl_t *CTRB_RBC_img_name_ID11 = NULL;  //向下箭头左图控件名
grf_ctrl_t *CTRB_RBC_img_name_ID12 = NULL;  //请向下箭头右图控件名
grf_ctrl_t *CTRB_RBC_img_name_ID13 = NULL;  //外圈围绕滚刷转图控件名

grf_ctrl_t *container1_img_name_ID7 = NULL;  //2/3容器控件名显示
grf_ctrl_t *clean_the_filter_and_dirty_water_tank_img_name_ID15 = NULL;  //清理滤网及污水箱轮播图控件名

grf_ctrl_t *container2_img_name_ID17 = NULL;  //3/3容器控件名显示
grf_ctrl_t *clean_the_pipe_img_name_ID18 = NULL;  //清理管道

grf_ctrl_t *maintenance_strategy_label_img_name_ID21 = NULL;  //保养攻略下方文字对应显示


//自定义变量
static u8 i = 0;  //控制循环播放轮播图


//自定义数组
//请清理滚刷
static u8 *fault_image_name3[36] = {
	"/fault/3_00.png",
	"/fault/3_01.png",
	"/fault/3_02.png",
	"/fault/3_03.png",
	"/fault/3_04.png",
	"/fault/3_05.png",
	"/fault/3_06.png",
	"/fault/3_07.png",
	"/fault/3_08.png",
	"/fault/3_09.png",
	"/fault/3_10.png",
	"/fault/3_11.png",
	"/fault/3_12.png",
	"/fault/3_13.png",
	"/fault/3_14.png",
	"/fault/3_15.png",
	"/fault/3_16.png",
	"/fault/3_17.png",
	"/fault/3_18.png",
	"/fault/3_19.png",
	"/fault/3_20.png",
	"/fault/3_21.png",
	"/fault/3_22.png",
	"/fault/3_23.png",
	"/fault/3_24.png",
	"/fault/3_25.png",
	"/fault/3_26.png",
	"/fault/3_27.png",
	"/fault/3_28.png",
	"/fault/3_29.png",
	"/fault/3_30.png",
	"/fault/3_31.png",
	"/fault/3_32.png",
	"/fault/3_33.png",
	"/fault/3_34.png",
	"/fault/3_35.png"
};
//请清理污水箱
static u8 *fault_image_name5[37] = {
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
	"/fault/5_35.png",
	"/fault/5_36.png"
};
//请清理滤网
static u8 *clean_filter_image_name[24] = {
	"/help/help_2_00.png",
	"/help/help_2_01.png",
	"/help/help_2_02.png",
	"/help/help_2_03.png",
	"/help/help_2_04.png",
	"/help/help_2_05.png",
	"/help/help_2_06.png",
	"/help/help_2_07.png",
	"/help/help_2_08.png",
	"/help/help_2_09.png",
	"/help/help_2_10.png",
	"/help/help_2_11.png",
	"/help/help_2_12.png",
	"/help/help_2_13.png",
	"/help/help_2_14.png",
	"/help/help_2_15.png",
	"/help/help_2_16.png",
	"/help/help_2_17.png",
	"/help/help_2_18.png",
	"/help/help_2_19.png",
	"/help/help_2_20.png",
	"/help/help_2_21.png",
	"/help/help_2_22.png",
	"/help/help_2_23.png",
};
//请清管道
static u8 *clean_pipe_image_name[22] = {
	"/help/help_2_30.png",
	"/help/help_2_31.png",
	"/help/help_2_32.png",
	"/help/help_2_33.png",
	"/help/help_2_34.png",
	"/help/help_2_35.png",
	"/help/help_2_36.png",
	"/help/help_2_37.png",
	"/help/help_2_38.png",
	"/help/help_2_39.png",
	"/help/help_2_40.png",
	"/help/help_2_41.png",
	"/help/help_2_42.png",
	"/help/help_2_43.png",
	"/help/help_2_44.png",
	"/help/help_2_45.png",
	"/help/help_2_46.png",
	"/help/help_2_47.png",
	"/help/help_2_48.png",
	"/help/help_2_49.png",
	"/help/help_2_50.png",
	"/help/help_2_51.png"
};


//清理滚刷,滚刷盖:回调函数
static void clean_roller_brush_cover()
{
	if (i == 1)
	{
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label1_name_ID2, "1/3");
		grf_label_set_txt(maintenance_strategy_label2_name_ID3, "#CTRB_RBC");
		grf_ctrl_set_hidden(container0_img_name_ID6,GRF_TRUE);
		grf_ctrl_set_hidden(container1_img_name_ID7,GRF_TRUE);
		grf_ctrl_set_hidden(container2_img_name_ID17,GRF_TRUE);

		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_TRUE);
	}
	else if (i == 21)
	{
		//语音播报测试:"请分别取下滚刷盖和滚刷,用清水清洗后装回"
		switch_language_pack("14_01_help");
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_TRUE);
		grf_ctrl_set_hidden(container0_img_name_ID6,GRF_FALSE);
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID13,GRF_TRUE);
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID11,GRF_FALSE);
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID12,GRF_FALSE);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,300,280);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,455,325);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,322);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,230,350);

		//清理滚刷、滚刷盖
		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label_img_name_ID21, "#CTRB_RBC");
	}
	else if (i == 22)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,305,290);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,450,335);
	}
	else if (i == 23)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,310,300);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,445,345);
	}
	else if (i == 24)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,300,280);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,455,325);
	}
	else if (i == 25)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,305,290);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,450,335);
	}
	else if (i == 26)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,310,300);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,445,345);
	}
	else if (i == 27)
	{
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID11,GRF_TRUE);
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID12,GRF_TRUE);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,307);
	}
	else if (i == 28)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,292);
	}
	else if (i == 29)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,277);
	}
	else if (i == 30)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,250);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,220,355);
	}
	else if (i == 31)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,220,355);
	}
	else if (i == 31)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,200,360);
	}
	else if (i == 32)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,170,370);
	}
	else if (i == 33)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,135,385);
	}
	else if (i == 34)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,120,360);
	}
	else if (i == 35)
	{
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,100,340);
	}
	else if (i == 36)
	{
		grf_ctrl_set_hidden(CTRB_RBC_img_name_ID13,GRF_FALSE);
		grf_img_set_src(CTRB_RBC_img_name_ID13,fault_image_name3[1]);
	}
	else if (i > 36 && i < 69)
	{
		grf_img_set_src(CTRB_RBC_img_name_ID13,fault_image_name3[i-35]);
	}
	else if (i == 69)
	{
		grf_ctrl_set_hidden(container0_img_name_ID6,GRF_TRUE);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID11,300,280);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID12,455,325);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID10,216,322);
		grf_ctrl_set_pos(CTRB_RBC_img_name_ID9,230,350);
		grf_delay(1000);
	}
}


//清理滤网及污水箱；调用函数
static void clean_filter_water_tank()
{
	//清理污水箱
	if (i == 69) {
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label1_name_ID2, "2/3");
		grf_label_set_txt(maintenance_strategy_label2_name_ID3, "#clean_the_filter_and_dirty_water_tank");

		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_TRUE);
	}
	else if (i == 89) {
		//语音播报测试:"取下污水桶后再取下过滤器,分别清洗过滤器和污水桶,清洗完毕后,请将过滤器,污水桶依次装回"
		switch_language_pack("14_02_help");
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_TRUE);
		grf_ctrl_set_hidden(container1_img_name_ID7,GRF_FALSE);
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,fault_image_name5[1]);
		grf_ctrl_set_pos(clean_the_filter_and_dirty_water_tank_img_name_ID15,125,0);

		//清理滤网及污水箱
		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label_img_name_ID21, "#clean_the_filter_and_dirty_water_tank");
	}
	else if (i > 89  && i <= 123)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,fault_image_name5[i-88]);
	}
	else if (i > 123  && i <= 139)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,fault_image_name5[i-104]);
	}
	else if (i > 139  && i <= 155)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,fault_image_name5[i-120]);
	}
	else if (i > 155  && i <= 167)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,fault_image_name5[176-i]);
	}
	else if (i == 168) {
		grf_delay(1000);
	}

	//清理滤网
	else if (i == 169)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,clean_filter_image_name[i-168]);
		grf_ctrl_set_pos(clean_the_filter_and_dirty_water_tank_img_name_ID15,260,85);
	}
	else if (i > 169 && i <= 191)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,clean_filter_image_name[i-168]);
	}
	else if (i == 192)
	{
		grf_img_set_src(clean_the_filter_and_dirty_water_tank_img_name_ID15,clean_filter_image_name[1]);
	}
	else if (i == 193)
	{
		grf_ctrl_set_hidden(container1_img_name_ID7,GRF_TRUE);
		grf_delay(1000);
	}
}

//清理管道
static void clean_pipe()
{
	if (i == 193)
	{
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label1_name_ID2, "3/3");
		grf_label_set_txt(maintenance_strategy_label2_name_ID3, "#clean_the_pipe");

		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_TRUE);
	}
	else if (i == 214) {
		//语音播报测试:"取下污水桶,用清洁刷清洁管道"
		switch_language_pack("14_03_help");
		grf_ctrl_set_hidden(maintenance_strategy_img_name_ID1,GRF_TRUE);
		grf_ctrl_set_hidden(container2_img_name_ID17,GRF_FALSE);
		grf_img_set_src(clean_the_pipe_img_name_ID18,clean_pipe_image_name[i-213]);

		//清理管道
		grf_ctrl_set_hidden(maintenance_strategy_label_img_name_ID21,GRF_FALSE);
		grf_label_set_txt(maintenance_strategy_label_img_name_ID21, "#clean_the_pipe");
	}
	else if (i > 214 && i <= 234) {
		grf_img_set_src(clean_the_pipe_img_name_ID18,clean_pipe_image_name[i-213]);
	}
	else if (i == 250) {
		//grf_delay(1000);
	}
}

//保养攻略
void maintenance_strategy_task_cb()
{
	i++;
	grf_printf("保养攻略：i == %d\n",i);
	if(i > 250)
	{
		i = 1;
	}
	clean_roller_brush_cover();
	clean_filter_water_tank();
	clean_pipe();
}

//按键操作
void key_task14_cb()
{
	if (ytl_back)
	{
		ytl_back = GRF_FALSE;
		grf_printf("返回键\n");
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);  //返回帮助界面
	}
}

void task_create14()
{
	grf_printf("task_create14\n");

	//获取控件
	maintenance_strategy_img_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE0_ID);
	maintenance_strategy_label1_name_ID2 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_LABEL0_ID);
	maintenance_strategy_label2_name_ID3 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_LABEL1_ID);

	container0_img_name_ID6 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_CONTAINER0_ID);
	CTRB_RBC_img_name_ID8 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE3_ID);
	CTRB_RBC_img_name_ID9 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE4_ID);
	CTRB_RBC_img_name_ID10 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE5_ID);
	CTRB_RBC_img_name_ID11 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE6_ID);
	CTRB_RBC_img_name_ID12 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE7_ID);
	CTRB_RBC_img_name_ID13 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE8_ID);

	container1_img_name_ID7 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_CONTAINER1_ID);
	clean_the_filter_and_dirty_water_tank_img_name_ID15 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE9_ID);

	container2_img_name_ID17 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_CONTAINER2_ID);
	clean_the_pipe_img_name_ID18 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_IMAGE10_ID);

	maintenance_strategy_label_img_name_ID21 = grf_ctrl_get_form_id(GRF_VIEW14_HELP2_ID,VIEW14_HELP2_LABEL5_ID);

	//创建任务
	key_task14 = grf_task_create(key_task14_cb,100,NULL);
	maintenance_strategy_task = grf_task_create(maintenance_strategy_task_cb,100,NULL);

	//立即执行
	grf_task_ready(maintenance_strategy_task);
}

void task_del14()
{
	grf_printf("task_del14\n");
	i = 0;
	grf_task_del(key_task14);
	grf_task_del(maintenance_strategy_task);
}
