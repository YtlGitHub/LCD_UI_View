#include "../../apps.h"


//创建故障任务
grf_task_t *fault_task = NULL;


//创建控件名
grf_ctrl_t *fault_container_name1_ID2 = NULL;  //请安装清水箱容器控件名
grf_ctrl_t *fault_icon_name1_ID3 = NULL;  //请安装清水箱图标控件名
grf_ctrl_t *fault_name1_ID4 = NULL;  //请安装清水箱动图控件名

grf_ctrl_t *fault_container_name2_ID5 = NULL;  //请安装污水箱容器控件名
grf_ctrl_t *fault_icon_name2_ID6 = NULL;  //请安装污水箱图标控件名
grf_ctrl_t *fault_name2_ID7 = NULL;  //请安装污水箱动图控件名

grf_ctrl_t *fault_container_name3_ID8 = NULL;  //请清理滚刷容器控件名
grf_ctrl_t *fault_icon_name3_ID9 = NULL;  //请清理滚刷图标控件名
grf_ctrl_t *fault_name3_ID10 = NULL;  //请清理滚刷机身图控件名
grf_ctrl_t *fault_name3_ID11 = NULL;  //滚刷图控件名
grf_ctrl_t *fault_name3_ID12 = NULL;  //滚刷盖图控件名
grf_ctrl_t *fault_name3_ID13 = NULL;  //向下箭头左图控件名
grf_ctrl_t *fault_name3_ID14 = NULL;  //请向下箭头右图控件名
grf_ctrl_t *fault_name3_ID15 = NULL;  //外圈围绕滚刷转图控件名

grf_ctrl_t *fault_container_name4_ID16 = NULL;  //请加清水容器控件名
grf_ctrl_t *fault_icon_name4_ID17 = NULL;  //请加清水图标控件名
grf_ctrl_t *fault_name4_ID18 = NULL;  //请加清水波浪纹图控件名
grf_ctrl_t *fault_name4_ID19 = NULL;  //请加清水动图控件名

grf_ctrl_t *fault_container_name5_ID20 = NULL;  //请清理污水箱容器控件名
grf_ctrl_t *fault_icon_name5_ID21 = NULL;  //请清理污水箱图标控件名
grf_ctrl_t *fault_name5_ID22 = NULL;  //请清理污水箱动图控件名

grf_ctrl_t *fault_container_name6_ID23 = NULL;  //风机故障容器控件名
grf_ctrl_t *fault_icon_name6_ID24 = NULL;  //风机故障图标控件名

grf_ctrl_t *fault_label_name_ID25 = NULL;  //故障文字显示控件名


//自定义变量


//自定义数组
static u8 *fault_image_name1[12] = {
	"/fault/1_00.png",
	"/fault/1_01.png",
	"/fault/1_02.png",
	"/fault/1_03.png",
	"/fault/1_04.png",
	"/fault/1_05.png",
	"/fault/1_06.png",
	"/fault/1_07.png",
	"/fault/1_08.png",
	"/fault/1_09.png",
	"/fault/1_10.png",
	"/fault/1_11.png"
};  //请安装清水箱

static u8 *fault_image_name2[19] = {
	"/fault/2_00.png",
	"/fault/2_01.png",
	"/fault/2_02.png",
	"/fault/2_03.png",
	"/fault/2_04.png",
	"/fault/2_05.png",
	"/fault/2_06.png",
	"/fault/2_07.png",
	"/fault/2_08.png",
	"/fault/2_09.png",
	"/fault/2_10.png",
	"/fault/2_11.png",
	"/fault/2_12.png",
	"/fault/2_13.png",
	"/fault/2_14.png",
	"/fault/2_15.png",
	"/fault/2_16.png",
	"/fault/2_17.png",
	"/fault/2_18.png",
};  //请安装污水箱

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
};  //请清理滚刷

static u8 *fault_image_name4[15] = {
	"/fault/4_00.png",
	"/fault/4_01.png",
	"/fault/4_02.png",
	"/fault/4_03.png",
	"/fault/4_04.png",
	"/fault/4_05.png",
	"/fault/4_06.png",
	"/fault/4_07.png",
	"/fault/4_08.png",
	"/fault/4_09.png",
	"/fault/4_10.png",
	"/fault/4_11.png",
	"/fault/4_12.png",
	"/fault/4_13.png",
	"/fault/4_14.png"
};  //请加清水

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
};  //请清理污水箱


//创建故障函数
void fault_task_cb()
{
	//grf_printf("故障显示界面\n");
	//grf_printf("ytl_view_get_cur_id == %d\n",ytl_view_get_cur_id);
	//grf_printf("isCmdCompletedBuf[11] == %d\n",isCmdCompletedBuf[11]);
	if (ytl_help) {
		ytl_help = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);
	}
	if (isCmdCompletedBuf[11])
	{
		if (ytl_fault[1] || ytl_fault[2] || ytl_fault[3] || ytl_fault[4] || ytl_fault[5] || ytl_fault[6])
		{
			if (ytl_fault_val == 1)
			{
				//请安装清水箱
				if (ytl_fault[1])
				{
					//grf_printf("ytl_fault[1] == %d\n",ytl_fault[1]);
					if (ytl_fault[11] == 0)
					{
						grf_printf("语言播报：请安装清水箱\n");
						//发送串口数据
						grf_reg_com_send(0x05, 0xE0, 0x01, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#please_install_clean_water_tank");

						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name1_ID3,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name1_ID4,GRF_TRUE);
					}
					else if (ytl_fault[11] > 20)
					{
						grf_ctrl_set_hidden(fault_icon_name1_ID3,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name1_ID4,GRF_FALSE);
						grf_img_set_src(fault_name1_ID4,fault_image_name1[ytl_fault[11]-20]);
						if(ytl_fault[11] > 30)
						{
							ytl_fault[11] = 20;
						}
					}
					ytl_fault[11] += 1;
					grf_printf("ytl_fault[11] == %d\n",ytl_fault[11]);
				}
			}
			else if (ytl_fault_val == 2)
			{
				//请安装污水箱
				if (ytl_fault[2])
				{
					//grf_printf("ytl_fault[2] == %d\n",ytl_fault[2]);
					if (ytl_fault[12] == 0)
					{
						grf_printf("语言播报：请安装污水箱\n");
						grf_reg_com_send(0x05, 0xE0, 0x02, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#please_install_dirty_water_tank");

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);

						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name2_ID6,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name2_ID7,GRF_TRUE);
					}
					else if (ytl_fault[12] > 20)
					{
						grf_ctrl_set_hidden(fault_icon_name2_ID6,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name2_ID7,GRF_FALSE);
						grf_img_set_src(fault_name2_ID7,fault_image_name2[ytl_fault[12]-20]);
						if(ytl_fault[12] > 37)
						{
							ytl_fault[12] = 20;
						}
					}
					ytl_fault[12] += 1;
					grf_printf("ytl_fault[12] == %d\n",ytl_fault[12]);
				}
			}

			else if (ytl_fault_val == 3)
			{
				//请清理滚刷
				if (ytl_fault[3])
				{
					grf_printf("ytl_fault[3] == %d\n",ytl_fault[3]);
					if (ytl_fault[13] == 0)
					{
						grf_printf("语言播报：请清理滚刷\n");
						grf_reg_com_send(0x05, 0xE0, 0x03, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#please_clean_the_brush_roll");

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);

						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name3_ID9,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID10,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID11,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID12,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID13,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID14,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID15,GRF_TRUE);
					}
					else if (ytl_fault[13] == 21)
					{
						grf_ctrl_set_hidden(fault_icon_name3_ID9,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID10,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID11,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID12,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID13,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID14,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name3_ID15,GRF_TRUE);
						grf_ctrl_set_pos(fault_name3_ID13,300,280);
						grf_ctrl_set_pos(fault_name3_ID14,455,325);
						grf_ctrl_set_pos(fault_name3_ID12,216,322);
						grf_ctrl_set_pos(fault_name3_ID11,230,350);
					}
					else if (ytl_fault[13] == 22)
					{
						grf_ctrl_set_pos(fault_name3_ID13,305,290);
						grf_ctrl_set_pos(fault_name3_ID14,450,335);
					}
					else if (ytl_fault[13] == 23)
					{
						grf_ctrl_set_pos(fault_name3_ID13,310,300);
						grf_ctrl_set_pos(fault_name3_ID14,445,345);
					}
					else if (ytl_fault[13] == 24)
					{
						grf_ctrl_set_pos(fault_name3_ID13,300,280);
						grf_ctrl_set_pos(fault_name3_ID14,455,325);
					}
					else if (ytl_fault[13] == 25)
					{
						grf_ctrl_set_pos(fault_name3_ID13,305,290);
						grf_ctrl_set_pos(fault_name3_ID14,450,335);
					}
					else if (ytl_fault[13] == 26)
					{
						grf_ctrl_set_pos(fault_name3_ID13,310,300);
						grf_ctrl_set_pos(fault_name3_ID14,445,345);
					}
					else if (ytl_fault[13] == 27)
					{
						grf_ctrl_set_hidden(fault_name3_ID13,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name3_ID14,GRF_TRUE);
						grf_ctrl_set_pos(fault_name3_ID12,216,307);
					}
					else if (ytl_fault[13] == 28)
					{
						grf_ctrl_set_pos(fault_name3_ID12,216,292);
					}
					else if (ytl_fault[13] == 29)
					{
						grf_ctrl_set_pos(fault_name3_ID12,216,277);
					}
					else if (ytl_fault[13] == 30)
					{
						grf_ctrl_set_pos(fault_name3_ID12,216,250);
						grf_ctrl_set_pos(fault_name3_ID11,220,355);
					}
					else if (ytl_fault[13] == 31)
					{
						grf_ctrl_set_pos(fault_name3_ID11,220,355);
					}
					else if (ytl_fault[13] == 31)
					{
						grf_ctrl_set_pos(fault_name3_ID11,200,360);
					}
					else if (ytl_fault[13] == 32)
					{
						grf_ctrl_set_pos(fault_name3_ID11,170,370);
					}
					else if (ytl_fault[13] == 33)
					{
						grf_ctrl_set_pos(fault_name3_ID11,135,385);
					}
					else if (ytl_fault[13] == 34)
					{
						grf_ctrl_set_pos(fault_name3_ID11,120,360);
					}
					else if (ytl_fault[13] == 35)
					{
						grf_ctrl_set_pos(fault_name3_ID11,100,340);
					}
					else if (ytl_fault[13] == 36)
					{
						grf_ctrl_set_hidden(fault_name3_ID15,GRF_FALSE);
						grf_img_set_src(fault_name3_ID15,fault_image_name3[1]);
					}
					else if (ytl_fault[13] > 36)
					{
						grf_img_set_src(fault_name3_ID15,fault_image_name3[ytl_fault[13]-35]);
					}
					if(ytl_fault[13] > 69)
					{
						ytl_fault[13] = 20;
					}
					ytl_fault[13] += 1;
					grf_printf("ytl_fault[13] == %d\n",ytl_fault[13]);
				}
			}
			else if (ytl_fault_val == 4)
			{
				//请加清水
				if (ytl_fault[4])
				{
					grf_printf("ytl_fault[4] == %d\n",ytl_fault[4]);
					if (ytl_fault[14] == 0)
					{
						grf_printf("语言播报：请加清水\n");
						grf_reg_com_send(0x05, 0xE0, 0x04, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#please_add_water");

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);



						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name4_ID17,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name4_ID18,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name4_ID19,GRF_TRUE);
					}
					else if (ytl_fault[14] == 21) {
						grf_ctrl_set_hidden(fault_icon_name4_ID17,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name4_ID19,GRF_FALSE);
						grf_img_set_src(fault_name4_ID19,fault_image_name4[1]);
					}
					else if (ytl_fault[14] > 21)
					{
						grf_img_set_src(fault_name4_ID19,fault_image_name4[ytl_fault[14]-20]);
						if(ytl_fault[14] > 33)
						{
							ytl_fault[14] = 20;
						}
					}
					ytl_fault[14] += 1;
					grf_printf("ytl_fault[14] == %d\n",ytl_fault[14]);
				}
			}

			else if (ytl_fault_val == 5)
			{

				//请清理污水箱
				if (ytl_fault[5])
				{
					grf_printf("ytl_fault[5] == %d\n",ytl_fault[5]);
					if (ytl_fault[15] == 0)
					{
						grf_printf("语言播报：请清理污水箱\n");
						grf_reg_com_send(0x05, 0xE0, 0x05, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#please_clean_the_dirty_water_tank");

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);


						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name5_ID21,GRF_FALSE);
						grf_ctrl_set_hidden(fault_name5_ID22,GRF_TRUE);
					}
					else if (ytl_fault[15] == 21) {
						grf_ctrl_set_hidden(fault_icon_name5_ID21,GRF_TRUE);
						grf_ctrl_set_hidden(fault_name5_ID22,GRF_FALSE);
						grf_img_set_src(fault_name5_ID22,fault_image_name5[1]);
					}
					else if (ytl_fault[15] > 21  && ytl_fault[15] <= 55)
					{
						grf_img_set_src(fault_name5_ID22,fault_image_name5[ytl_fault[15]-20]);
					}
					else if (ytl_fault[15] > 55  && ytl_fault[15] <= 71)
					{
						grf_img_set_src(fault_name5_ID22,fault_image_name5[ytl_fault[15]-36]);
					}
					else if (ytl_fault[15] > 71  && ytl_fault[15] <= 87)
					{
						grf_img_set_src(fault_name5_ID22,fault_image_name5[ytl_fault[15]-52]);
					}
					else if (ytl_fault[15] > 87  && ytl_fault[15] <= 100)
					{
						grf_img_set_src(fault_name5_ID22,fault_image_name5[108-ytl_fault[15]]);
					}
					else if(ytl_fault[15] > 100)
					{
						ytl_fault[15] = 20;
					}
					ytl_fault[15] += 1;
					grf_printf("ytl_fault[15] == %d\n",ytl_fault[15]);
				}
			}

			else if (ytl_fault_val == 6)
			{
				//风机故障
				if (ytl_fault[6])
				{
					grf_printf("ytl_fault[6] == %d\n",ytl_fault[6]);
					if (ytl_fault[16] == 0)
					{
						grf_printf("语言播报：请清理污水箱\n");
						grf_reg_com_send(0x05, 0xE0, 0x06, 0x00, 0x00);

						grf_label_set_txt(fault_label_name_ID25, "#fan_failure");

						grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
						grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);

						grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_FALSE);
						grf_ctrl_set_hidden(fault_icon_name6_ID24,GRF_FALSE);
						ytl_fault[16] = GRF_TRUE;
					}
					else {
						grf_printf("ytl_fault[16] == %d\n",ytl_fault[16]);
					}
				}
			}

		}
		else
		{
			grf_ctrl_set_hidden(fault_container_name1_ID2,GRF_TRUE);
			grf_ctrl_set_hidden(fault_container_name2_ID5,GRF_TRUE);
			grf_ctrl_set_hidden(fault_container_name3_ID8,GRF_TRUE);
			grf_ctrl_set_hidden(fault_container_name4_ID16,GRF_TRUE);
			grf_ctrl_set_hidden(fault_container_name5_ID20,GRF_TRUE);
			grf_ctrl_set_hidden(fault_container_name6_ID23,GRF_TRUE);

			grf_view_set_dis_view(ytl_view_get_cur_id);

			isCmdCompletedBuf[11] = GRF_FALSE;
		}
	}
}

void task_create11()
{
	grf_printf("task_create11\n");

	//获取控件
	fault_container_name1_ID2 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER0_ID);
	fault_icon_name1_ID3 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE1_ID);
	fault_name1_ID4 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE2_ID);

	fault_container_name2_ID5 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER1_ID);
	fault_icon_name2_ID6 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE3_ID);
	fault_name2_ID7 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE4_ID);

	fault_container_name3_ID8 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER2_ID);
	fault_icon_name3_ID9 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE5_ID);
	fault_name3_ID10 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE6_ID);
	fault_name3_ID11 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE7_ID);
	fault_name3_ID12 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE8_ID);
	fault_name3_ID13 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE9_ID);
	fault_name3_ID14 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE10_ID);
	fault_name3_ID15 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE11_ID);

	fault_container_name4_ID16 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER3_ID);
	fault_icon_name4_ID17 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE12_ID);
	fault_name4_ID18 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE13_ID);
	fault_name4_ID19 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE14_ID);

	fault_container_name5_ID20 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER4_ID);
	fault_icon_name5_ID21 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE15_ID);
	fault_name5_ID22 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE16_ID);

	fault_container_name6_ID23 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_CONTAINER5_ID);
	fault_icon_name6_ID24 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_IMAGE17_ID);

	fault_label_name_ID25 = grf_ctrl_get_form_id(GRF_VIEW11_FAULT_ID,VIEW11_FAULT_LABEL0_ID);

	//创建任务
	fault_task = grf_task_create(fault_task_cb,100,NULL);
	grf_printf("故障任务创建完成\n");
}

void task_del11()
{
	grf_printf("task_del11\n");
	grf_task_del(fault_task);
}
