#include "../../apps.h"


//创建任务名
grf_task_t *engineering_test_mode_task18 = NULL;  //工程测试模式任务
grf_task_t *engineering_test_mode_task18_aging_countdown = NULL;  //工程测试模式老化倒计时任务


//创建控件名
grf_ctrl_t *engineering_test_mode_label0_name_ID1 = NULL;  //创建工程测试模式下方白色色字体说明文字控件名
grf_ctrl_t *engineering_test_mode_label1_pass_fail_name_ID2 = NULL;  //创建工程测试模式中间“测试中”、“PASS”或“FAIL”显示控件名
grf_ctrl_t *engineering_test_mode_label2_key_name_ID3 = NULL;  //创建按键显示文字控件名
grf_ctrl_t *countdown_arc0_name_ID4 = NULL;  //老化倒计时arc控件名


//自定义变量
static u8 i = 0;  //控制工程测试模式循环变量
static u16 j = 0;  //控制在老化模式倒计时时间显示
grf_bool under_testing_var = GRF_FALSE;  //如果是在污浊度测试，把under_testing_var = GRF_TRUE，不然跳转到故障界面


//自定义数组
static u8 *key_display_name_array[10] =
{
	"",
	"开关键",
	"左键",
	"#select_button_engineering_test_mode",
	"#back_button_engineering_test_mode",
	"#help_button_engineering_test_mode",
	"#confirm_button_engineering_test_mode",
	"#self_cleaning_button_engineering_test_mode",
	"#mute_button_engineering_test_mode",
	"#factory_settings_have_been_restored_engineering_test_mode"
};

static u8 *language_chinese_display[EXTERNAL_BUFFER_SIZE_languageBuf] =
{
	"#chinese",
	"#english",
	"#turkish",
	"#russian"
};


//控制显示时间
static void control_display_time(void)
{
	i++;
	//grf_printf("i == %d\n",i);
	if (i == 100)
		{
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"");
			i = 0;
			isCmdCompletedBuf[19] = GRF_FALSE;
		}
}


static u8 countdown_array[255];  //倒计时数组
static u8 countdown_value = 5;  //倒计时变量值
void engineering_test_mode_task18_aging_countdown_cb()
{
	//grf_printf("j == %d\n",j);
	if (j == 0) {
		countdown_value = 5;
	}
	else if (j == 60) {
		countdown_value = 4;
	}
	else if (j == 120) {
		countdown_value = 3;
	}
	else if (j == 180) {
		countdown_value = 2;
	}
	else if (j == 240) {
		countdown_value = 1;
	}
	else if (j == 300) {
		countdown_value = 0;
	}
	grf_arc_set_value(countdown_arc0_name_ID4,300-j);
	sprintf(countdown_array,"%d", countdown_value);
	grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, countdown_array);
	j++;
}


static u8 ytl_get_default_language = 1;  //获取默认语言（0中文1英语2土耳其语3俄语）
static grf_bool language_mode = GRF_FALSE;  //当到了切换语言模式时，把他改为GRF_TRUE，这样在按选择键时，就可以切换语言
//按键显示自定义调用函数
static void key_display_test(u8 data1,u8 data2)
{
	//control_display_time();
	if (data1 == 0x08)
	{
		if (data2 == 0x00 || data2 == 0x01) {
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,key_display_name_array[8]);
			grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
		}
		else if (data2 == 0x03) {
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,key_display_name_array[9]);
			grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
		}
	}
	else {
		if (language_mode)
		{
			if (data1 == 0x03) {
				//语言切换
				ytl3_switch_language++;
				if (ytl3_switch_language >= sizeof(languageBuf)/sizeof(u8*)) {
					ytl3_switch_language = 0;
				}
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, language_chinese_display[ytl_get_default_language]);  //把按键显示改为当前什么语言中文文字显示
				grf_lang_set(languageBuf[ytl3_switch_language]);
				save_system_settings_var();
			}
		}
		else {
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, key_display_name_array[data1]);
		}
		grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
	}
}


//工程测试模式任务
void engineering_test_mode_task18_cb()
{
	//grf_printf("cmdBuf[0] == %02x,cmdBuf[1] == %02x\n",cmdBuf[0],cmdBuf[1]);
	if (isCmdCompletedBuf[19])
	{
		//grf_printf("cmdBuf[0] == %02x,cmdBuf[1] == %02x,cmdBuf[2] == %02x\n",cmdBuf[0],cmdBuf[1],cmdBuf[2]);
		if (cmdBuf[0] == 0xD0)
		{
			switch (cmdBuf[1])
			{
				case 0xf0:
					//grf_printf("FAIL\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "FAIL");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_RED);
					break;
				case 0xf1:
					//grf_printf("PASS\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "PASS");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_GREEN);
					break;
				case 0x00:
					//grf_printf("button test\n");  //按键测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");  //测试中
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);  //把文字颜色改为黄色
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#key_test");  //按键测试
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, "#please_press_all_buttons");  //请按完所有按键文字显示
					break;
				case 0x01:
					//grf_printf("Fan test\n");  //风机测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#air_blower_test");
					break;
				case 0x02:
					//grf_printf("//electrolytic water test\n");  //电解水测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#electrolyzed_water_test");
					break;
				case 0x03:
					//grf_printf("Clean water tank sewage tank in place test\n");  //清水箱污水箱在位测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#clean_water_dirty_water_tank");
					break;
				case 0x04:
					//grf_printf("Clean water tank with no water test\n");  //清水箱有水无水测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#clear_water_tank_test__have_water_or_not");
					break;
				case 0x05:
					//grf_printf("Turbidity test\n");  //污浊度测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#turbidity_degree_of_water_test");
					break;
				case 0x06:
					//grf_printf("Sewage tank full test\n");  //污水箱满测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#dirty_water_full_tank_test");
					break;
				case 0x07:
					//grf_printf("Machine tilt switch test\n");  //机器倾斜测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#on_off_test_when_device_tilt");
					break;
				case 0x08:
					//grf_printf("Rolling brush test\n");  //滚刷测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#brush_test");
					break;
				case 0x09:
					//grf_printf("Pump test\n");  //水泵测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#water_pump_test");
					break;
				case 0x10:
					//grf_printf("Left and right round test\n");  //左右轮测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#left_right_wheel_test");
					break;
				case 0x11:
					//grf_printf("LED lighting test\n");  //LED灯照明测试
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#led_lighting_test");
					break;
				case 0x12:
					//grf_printf("Floor washer aging test\n");  //洗地机老化测试
					j = 0;
					engineering_test_mode_task18_aging_countdown = grf_task_create(engineering_test_mode_task18_aging_countdown_cb,1000,NULL);  //创建工程测试模式任务
					grf_task_ready(engineering_test_mode_task18_aging_countdown);
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#under_testing");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#aging_test");
					break;
				case 0x13:
					//grf_printf("Floor washer charging test\n");  //切换语音
					ytl_get_default_language = ytl3_switch_language;  //获取默认语言
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#select_language");  //“测试中”文字改为当前是什么语言
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "#language");
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, language_chinese_display[ytl3_switch_language]);  //把按键显示改为当前什么语言中文文字显示
					//恢复默认设置
					ytl0_roller_brush_lighting = GRF_TRUE;
					ytl1_cleaning_method = GRF_FALSE;
					ytl2_voice_image_val = 2;
					save_system_settings_var();
					break;
			}
			//进入下一个模式，把按键显示文字改为null不显示
			if (cmdBuf[1] != 0xf0 && cmdBuf[1] != 0xf1 && cmdBuf[1] != 0x00 && cmdBuf[1] != 0x13)
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, "");
			}

			//如果是在脏污检测模式，发生故障不会跳转故障界面，其他模式就都可以跳转故障界面
			if (cmdBuf[1] == 0x05)
			{
				under_testing_var = GRF_TRUE;
			}else
			{
				ytl_dirty_degree = 0;  //不在脏污检测模式，就把跑马灯关闭
				under_testing_var = GRF_FALSE;
			}

			//老化倒计时
			if (cmdBuf[1] == 0x12)
			{
				grf_ctrl_set_hidden(countdown_arc0_name_ID4, GRF_FALSE);
				//红色外圈旋转90度
				grf_arc_set_rotation(countdown_arc0_name_ID4,90);
				grf_arc_set_value(countdown_arc0_name_ID4,300);
			}
			else
			{
				grf_ctrl_set_hidden(countdown_arc0_name_ID4, GRF_TRUE);
				if (engineering_test_mode_task18_aging_countdown)
				{
					grf_task_del(engineering_test_mode_task18_aging_countdown);
					engineering_test_mode_task18_aging_countdown = NULL;
				}
			}

			//到了最后一个充电测试模式改成语言切换模式完之后再去充电测试时，按选择键可以切换语言
			if (cmdBuf[1] == 0x13)
			{
				language_mode = GRF_TRUE;
			}
			else
			{
				language_mode = GRF_FALSE;
			}
			isCmdCompletedBuf[19] = GRF_FALSE;
		}
		else if(cmdBuf[0] == 0x80)
		{
			if (cmdBuf[1] == 0x09)
			{
				/*
				grf_delay(1000);
				grf_printf("按键测试\n");
				grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
				grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
				grf_label_set_txt(engineering_test_mode_label0_name_ID1, "按键测试");
				*/
				grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "#factory_testing_mode");  //已进入工程测试模式
				grf_ctrl_set_hidden(countdown_arc0_name_ID4, GRF_TRUE);  //隐藏老化倒计时arc
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, "");
				grf_label_set_txt(engineering_test_mode_label0_name_ID1, "");
			}
			else {
				//grf_printf("Key Display test\n");  //按键显示测试
				key_display_test(cmdBuf[1],cmdBuf[2]);
			}
			isCmdCompletedBuf[19] = GRF_FALSE;
		}
		else if(cmdBuf[0] == 0xF0)
		{
			if (cmdBuf[1] == 0x01)  //发送电量显示
			{
				u8 battery_quantity[20];
				sprintf(battery_quantity, "%d" "%s",ytl_battery_quantity_val,"%");
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,battery_quantity);
			}
			if (cmdBuf[1] == 0x02)  //是否缺水
			{
				if (cmdBuf[2] == 0x00)  //缺水
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#water_shortage");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x01)  //水量正常
				{
					//grf_printf("Normal water content\n");  //水量正常
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
			}
			control_display_time();
		}
		else if(cmdBuf[0] == 0xB0)
		{
			if (cmdBuf[1] == 0x03)  //竖起机身停止清扫
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#upright_the_device");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
			if (cmdBuf[1] == 0x04)  //倾斜机身开始清扫
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#tilt_the_device");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
			control_display_time();
		}
		else if(cmdBuf[0] == 0x9A)  //脏污程度
		{
			if (cmdBuf[1] == 0x01)
			{
				control_display_time();
				if (cmdBuf[2] == 0x00)  //脏污程度(蓝色)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#degree_0_blue");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x01)  //脏污程度(轻度1)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#degree_1_mild_1");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x02)  //脏污程度(轻度2)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#degree_2_mild_2");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x03)  //脏污程度(重度1)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#degree_3_mild_1");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x04)  //脏污程度(重度2)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"#degree_4_mild_2");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
			}
		}
	}
}


void task_create18()
{
	if (engineering_test_mode_task18 == NULL)
	{
		//grf_printf("task_create18\n");

		//获取控件
		engineering_test_mode_label0_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL0_ID);
		engineering_test_mode_label1_pass_fail_name_ID2 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL1_ID);
		engineering_test_mode_label2_key_name_ID3 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL2_ID);
		countdown_arc0_name_ID4 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_ARC0_ID);

		//创建任务
		engineering_test_mode_task18 = grf_task_create(engineering_test_mode_task18_cb,10,NULL);  //创建工程测试模式任务

		//立即执行
		//grf_task_ready(engineering_test_mode_task18);
	}
}


void task_del18(void)
{
	grf_printf("no task_del18\n");

	//grf_task_del(engineering_test_mode_task18);
}
