#include "../grf_hw.h"
#include "../../apps.h"
//#include "../../../libs/appscc/grf_prj_cc.h"
#if GRF_HW_ENABLE
#include "grf_hw_uart.h"


#define HEAD_FH 0xA5
#define HEAD_FL 0x5A
#define SEQ 0x00
#define REG_LEN 0x800 //2048
static u8 ctrlreg[REG_LEN] = {0};


#define UART_LASTBUFF 1
#if UART_LASTBUFF
#define RX_BUF_LEN   1024
static u8 RX_HAND_BUF[RX_BUF_LEN];
#endif


static u8 filePath[256];
static u8 filePath_sound[256];


//自定义静态变量
static grf_bool get_battery_quantity = GRF_FALSE;  //开机检查是否收到电量值
static grf_bool get_main_view  = GRF_FALSE;  //开机检查是否收到进入主界面指令
static grf_bool get_charging_view = GRF_FALSE;  //开机检查是否收到进入充电界面指令


//自定义全局变量
u8 cmdBuf[EXTERNAL_BUFFER_SIZE];  //获取指定需要的数据
u8 isCmdCompletedBuf[EXTERNAL_BUFFER_SIZE];  //控制不让程序重复执行
u8 ytl_view_get_cur_id = GRF_VIEW02_CLEANING_ID;  //发生故障界面的视图ID
u8 ytl_volume = 70;  //音量大小

//view1
grf_bool ytl_Power = GRF_FALSE;   //电源键
grf_bool ytl_back = GRF_FALSE;  //返回键
grf_bool ytl_confirmation = GRF_FALSE;   //进入/确认键
grf_bool ytl_right = GRF_FALSE;   //右键
static u8 ytl_right_v = 0;   //快速点击右键,计算前后两次按键的间隔(连续接受串口太快,丢掉太快的串口)
grf_bool ytl_self_cleaning = GRF_FALSE;   //自清洁键
grf_bool ytl_mute = GRF_FALSE;   //静音键
grf_bool ytl_help = GRF_FALSE;   //帮助键

//view2
grf_bool ytl_erected = GRF_FALSE;  //是否竖起，GRF_FALSE竖起，GRF_TRUE倾斜
u8 ytl_dirty_degree = 0; //脏污程度，0蓝色、1轻度1、2轻度2、3重度1、4重度2

//view3
u8 ytl2_voice_image_val = 2;  //"语言音量2":音量图标0关1低2中3高

//view4电池电量和清水溶液显示全局变量
u8 ytl_battery_quantity_val = 101;  //电量信息值
grf_bool ytl1_cleaning_method = GRF_FALSE;  //"清洁方式1"：GRF_FALSE清水或GRF_TRUE溶液
grf_bool ytl_water_shortage_val = GRF_TRUE;  //GRF_FALSE缺水或GRF_TRUE水量正常

//view9
u8 ytl_mode_select_uart = 0;  //模式选择变量:0智能除菌1快速2超强

//view11
u8 ytl_fault[EXTERNAL_BUFFER_SIZE];  //0没有故障,1请安装清水箱,2请安装污水箱,3请清理滚刷,4请加清水,5请清理污水箱,6风机故障
u8 ytl_fault_val = 0;  //故障值变量

//view17
grf_bool ytl0_roller_brush_lighting = GRF_TRUE;  //"滚刷照明0"GRF_FALSE关GRF_TRUE开
u8 ytl3_switch_language = 1;  //"切换语言3":0简体中文(ch)、1英文(en)、2土耳其语（tu）、3俄语（ru）


//自定义全局数组
u8 *languageBuf[EXTERNAL_BUFFER_SIZE_languageBuf] = {"ch","en","tu","ru"};  //语言数组


//void tr660r_wavplay(char filename[],int volume){}


//切换语言音频
void switch_language_pack(u8 filename[])
{
	char sound_array[255];
	sprintf(sound_array,"/rodata/sound/%s/%s_%s.wav", languageBuf[ytl3_switch_language],filename,languageBuf[ytl3_switch_language]);
#if RTOS_EXECUTEBUFF
	tr660r_wavplay(sound_array,ytl_volume);  //语音播报
#endif
}
//按键音
void key_sound_tr660r_wavplay(u8 filename[])
{
	char sound_array[255];
	sprintf(sound_array,"/rodata/sound/%s.wav", filename);
#if RTOS_EXECUTEBUFF
	tr660r_wavplay(sound_array,ytl_volume);  //按键音效
#endif
}


//快速按选择键时,控制太快的按键失灵掉
void control_key_failure(void)
{
	if (ytl_right_v <= 2) {
		ytl_right_v++;
		ytl_right = GRF_FALSE;
	}
	else if (ytl_right_v > 2 && ytl_right) {
		ytl_right_v = 0;
	}
}

s32 read_data_para(u16 addr,u8* databuf,u32 len)
{
	const u8* cfgfile = filePath;
	u32 reallen = 0;
	s8 ret = 0;

	FILE*   datafp=NULL;
	datafp = fopen(cfgfile,"rb");
	if(datafp==NULL)
	{
		grf_printf("open data.bin fail\n");
		fclose(datafp);
		return 0;
	}
	ret =fseek(datafp,addr,SEEK_SET);
	if(ret==0){//寻址成功
		reallen = fread(databuf,1,len,datafp);
	}
	else{
		grf_printf("The location exceeds the file size,addr=0x%04x\n",addr);
	}
	fclose(datafp);

	return reallen;
}

s32 write_data_para(u16 addr,u8* databuf,u32 len)
{
    s8 ret = 0;
	u32 reallen = 0;
	FILE*   datafp=NULL;
	const u8* cfgfile = filePath;

	datafp = fopen(cfgfile,"wb");
	//grf_printf("addr=%d,databuf=%x,len=%d\n",addr,databuf,len);
//	if(datafp == NULL){
//	//首先认为文件没有创建
//		datafp = fopen(cfgfile,"wb");
//	}
	if(datafp==NULL)
	{
		grf_printf("create tgus_para.bin fail\n");
		fclose(datafp);
		return GRF_FALSE;
	}
	else{
		//grf_printf("create %s success!\n",filePath);
	}
	ret = fseek(datafp,addr,SEEK_SET);
	if(ret!=0){//如果写入的地址超过了文件的总大小,先用0扩大文件,然后再写入数据
		u32 endlen,offset;
		u8 *data_p=NULL;
		fseek(datafp,0,SEEK_END);
		endlen = ftell(datafp);
		offset = addr-endlen;
		data_p = malloc(offset);
		if(!data_p){
			grf_printf("data_p malloc fail\n");
		}
		else{
            memset(data_p,0, offset);
		    fwrite(data_p,1,offset,datafp);
		}
		free(data_p);
		//grf_printf("endlen=%d offset=%d \n",endlen,offset);
	}
	reallen = fwrite(databuf,1,len,datafp);
	fclose(datafp);
	return reallen;
}

void volume_size(void)  //音量大小
{
    if (ytl2_voice_image_val == 0) {
		ytl_volume = 0;
	}
    else if (ytl2_voice_image_val == 1) {
    	ytl_volume = 65;
	}
    else if (ytl2_voice_image_val == 2) {
    	ytl_volume = 70;
	}
    else if (ytl2_voice_image_val == 3) {
    	ytl_volume = 75;
	}
}

//开机
void power_on(void)
{
	u8 readdatabuf[4] = {1,0,2,3};  //下标为：0滚刷照明（0关1开），1清洁方式（0清水1溶液），2语言音量（0关1低2中3高），3切换语言（0中文1英语2土耳其语3俄语）
	FILE *pFile=NULL;

    sprintf(filePath, "%s" "%s", grf_dir_get_ddisk(),"Myfile.bin");
    //grf_printf("filePath == %s\n",filePath);

    /*
    pFile = fopen(filePath , "rb"); //打开文件读操作
    fread(read , 1 , sizeof(read) , pFile); //从文件中读数据
     */
    read_data_para(0,readdatabuf,sizeof(readdatabuf)/sizeof(u8));//读取bin保存的数据

    ytl0_roller_brush_lighting = readdatabuf[0];
	ytl1_cleaning_method = readdatabuf[1];
	ytl2_voice_image_val = readdatabuf[2];
	ytl3_switch_language = readdatabuf[3];

	//切换语言
	grf_lang_set(languageBuf[ytl3_switch_language]);
    volume_size();  //音量大小
    mute_key_voice = ytl2_voice_image_val;
}

//保存系统设置变量
void save_system_settings_var(void)
{
	u8 writedatabuf[4] = {0};  //保存数据  //下标为：0滚刷照明，1清洁方式，2语言音量，3切换语言
	writedatabuf[0] = ytl0_roller_brush_lighting;
	writedatabuf[1] = ytl1_cleaning_method;
	writedatabuf[2] = ytl2_voice_image_val;
	writedatabuf[3] = ytl3_switch_language;

	/*
	const u8* cfgfile = filePath;
    pFile = fopen(cfgfile , "wb");  //打开文件写操作
    fwrite(writedatabuf , 1 , sizeof(writedatabuf)/sizeof(u8) , pFile);  //把数据写到文件 myfile.bin
    fclose(pFile);  //关闭文件
    */

	write_data_para(0,writedatabuf,sizeof(writedatabuf)/sizeof(u8));  //写数据到bin
}

//void WR_test()
//{
//    u8 readdatabuf[12] = {0};
//    u8 writedatabuf[12] = {'h','e','l','l','o','g','i','r','a','f','f','e'};
//
//    sprintf(filePath, "%s" "%s", grf_dir_get_ddisk(),"grf_app/res/Myfile.bin");
//    grf_printf("filePath == %s\n",filePath);
//
//    write_data_para(0,&writedatabuf,12);//写数据到bin
//	read_data_para(0,&readdatabuf,12);//读取bin保存的数据
//    for(int i=0;i<12;i++)
//    {
//        grf_printf("databuf[%d]=0x%2x\n",i, readdatabuf[i]);
//    }
//}


//*********write reg**********
//TX - FL FH seq len cmd data0 data1
//     A5 5A 01  04  80
//RX - 无

//*********read reg**********
//TX -  FH FL len cmd addr reglen
//      5A A5 04  83  0001  02
//RX -  FH FL len cmd addr reglen data0 data1
//      5A A5 08  82  0001  02    FFFF  FFFF

//*********YuKe**********
//      FH FL seq len cmd data1 data2 crc
//      A5 5A 01  05  F0    01   14  0A

s32 grf_reg_com_send(u8 len, u8 cmd, u8 date0, u8 date1, u8 date2)
{
	//grf_printf("grf_reg_com_send:\nlen == %02x,\ncmd == %02x,\ndate0 == %02x,\ndate1 == %02x,\ndate2 == %02x\n", len, cmd, date0, date1, date2);
    u8 txdata[EXTERNAL_BUFFER_SIZE] = {0};
    u32 i=0,j=0,sum=0;;
    txdata[i++] = HEAD_FH;
    txdata[i++] = HEAD_FL;
    txdata[i++] = SEQ;
    txdata[i++] = len;
    txdata[i++] = cmd;
    txdata[i++] = date0;
    txdata[i++] = date1;
    txdata[i++] = date2;


	for (j; j < len + 2; j++)
	{
		sum += txdata[j];
	}
	txdata[j] = sum % 256;  //校验和除以256取余
	/*  打印发送串口信息
    for (u8 i = 0; i < len+3; ++i) {
    	 grf_printf("txdata[%d] == 0x%02x\n",i,txdata[i]);
	}
	*/
    grf_drv_uart_send(txdata,j+1);
}

//s32 grf_reg_com_send(u16 addr,u16 len)
//{
//    u8 txdata[257] = {0};
//    u32 i=0,j=0;
//    txdata[i++] = HEAD_FH;
//    txdata[i++] = HEAD_FL;
//    txdata[i++] = 0;
//    txdata[i++] = addr>>8;
//    txdata[i++] = (addr&0x00ff);
//    txdata[i++] = len;
//    for(j=0;j<len;j++){
//        txdata[i++] = (ctrlreg[addr+j]>>8);
//        txdata[i++] = (ctrlreg[addr+j]&0x00ff);
//    }
//    grf_drv_uart_send(txdata,i);
//}


static void USARTy_IRQHandler(u8* databuf)
{
	cmdBuf[0] = databuf[4];
	cmdBuf[1] = databuf[5];
	cmdBuf[2] = databuf[6];
	cmdBuf[3] = databuf[7];

	memset(isCmdCompletedBuf, GRF_TRUE, sizeof(isCmdCompletedBuf)/sizeof(u8));

	//检查是否有故障
	if (cmdBuf[0] == 0xE0 ||
		cmdBuf[0] == 0xB0 ||
		cmdBuf[0] == 0xF0 ||
		cmdBuf[0] == 0xD0 ||
		cmdBuf[0] == 0x9A ||
		(cmdBuf[0] == 0x80 && cmdBuf[1] != 0x04) &&
		(cmdBuf[0] == 0x80 && cmdBuf[1] != 0x07))
	{
		//grf_printf("如果是按得这几个键，就按实际的命令发送，否则就检查是否有故障，有故障就执行故障界面，没有就按实际的界面跳转\n");
	}
	else
	{
		//在充电界面或者自清洁完毕完在请清理污水箱界面有故障按自清洁键把ytl_self_cleaning = GRF_TRUE;才能跳转到自清洁模式选择界面
		if ((cmdBuf[0] == 0x80 && cmdBuf[1] == 0x07))
		{
			if (ytl_view_get_cur_id == GRF_VIEW08_CHARGING_ID ||
				ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
			{
				ytl_self_cleaning = GRF_TRUE;
			}
		}
		for (u8 i = 1; i < 7; ++i)
		{
			if(ytl_fault[i])
			{
				cmdBuf[0] = 0xE0;
				cmdBuf[1] = i;
				break;
			}
		}
	}
	switch(cmdBuf[0])
	{
		case 0x80:
			if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID)
			{
				ytl_Power = GRF_FALSE;   //电源键
				ytl_back = GRF_FALSE;  //返回键
				ytl_confirmation = GRF_FALSE;   //进入/确认键
				ytl_right = GRF_FALSE;   //右键即选择键
				ytl_self_cleaning = GRF_FALSE;   //自清洁键
				ytl_mute = GRF_FALSE;   //静音键
				ytl_help = GRF_FALSE;   //帮助键
				if (ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID)
				{
					key_sound_tr660r_wavplay("du");  //按键音效
				}
				else
				{
					if (cmdBuf[1] == 0x03 || (cmdBuf[1] == 0x08 && cmdBuf[2] == 0x03))
					{
						key_sound_tr660r_wavplay("du");  //按键音效
					}
					else if (cmdBuf[1] == 0x07)
					{
						if (ytl_view_get_cur_id == GRF_VIEW08_CHARGING_ID ||
							ytl_view_get_cur_id == GRF_VIEW09_SELF_CLEANING_MODE_ID ||
							ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
						{
							key_sound_tr660r_wavplay("du");  //按键音效
						}
					}
				}

				if (cmdBuf[1] == 0x01)
				{
					if (cmdBuf[2] == 0x00)
					{
						switch_language_pack("00_02_power_off");  //已关机,请放回底座自清洁
					}
					else if (cmdBuf[2] == 0x01)
					{
						//开机
					}
				}
				else if (cmdBuf[1] == 0x03)
				{
					//grf_printf("UART:right key\n");
					ytl_right = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x04)
				{
					//grf_printf("UART:back key\n");
					ytl_back = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x05)
				{
					//grf_printf("UART:help key\n");
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
						ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
						ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID)
					{
						grf_view_set_dis_view(GRF_VIEW12_HELP_ID);
					}
				}
				else if (cmdBuf[1] == 0x06)
				{
					//grf_printf("UART:confirm key\n");
					ytl_confirmation = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x07)
				{
					//grf_printf("UART:self-cleaning key\n");
					//如果是脱离充电状态,按自清洁键,就语音播报:"请放回底座自清洁"
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
						ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
						ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID)
					{
						//语音播报:"请放回底座自清洁"
						switch_language_pack("08_02_self_cleaning_key");
					}
					else {
						ytl_self_cleaning = GRF_TRUE;
					}
				}
				else if (cmdBuf[1] == 0x08)
				{
					if (cmdBuf[2] == 0x01)
					{
						//grf_printf("UART:mute key\n");
						ytl_mute = GRF_TRUE;
						key_task17_cb();  //语音音量
					}
					else if(cmdBuf[2] == 0x03)
					{
						if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
							ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
							ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID)
						{
							grf_view_set_dis_view(GRF_VIEW19_RESTORE_FACTORY_SETTINGS_ID);  //恢复出厂设置
						}
					}
				}
				//进入工程测试模式
				else if (cmdBuf[1] == 0x09)
				{
					//grf_printf("UART:engineering test mode\n");
					//设置只能在清扫界面,发送工程测试模式指令才可以进入工程测试模式
					grf_view_set_dis_view(GRF_VIEW18_ENGINEERING_TEST_MODE_ID);
					//语音播报:"已进入工程测试模式。"
					switch_language_pack("18_00_engineering_mode");
				}
			}
			break;
		case 0x81:  //语言选择
			grf_lang_set(languageBuf[cmdBuf[1]]);
			break;
		case 0xB0:
			if (cmdBuf[1] == 0x01)
			{
				//grf_printf("UART1:B0-0x01\n");
				get_charging_view = GRF_TRUE;
				get_main_view = GRF_FALSE;
				if (get_battery_quantity) {
					//grf_printf("UART2:B0-0x01\n");
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
						ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
						ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID ||
						//ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID ||
						ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID ||
						ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID)
					{
						grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
					}
				}
			}
			else if (cmdBuf[1] == 0x02)
			{
				//grf_printf("UART1:B0-0x02\n");
				get_main_view = GRF_TRUE;
				get_charging_view = GRF_FALSE;
				if (get_battery_quantity)
				{
					//grf_printf("UART2:B0-0x02\n");
					if (ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID) {
						grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
					}
				}
			}
			else if (cmdBuf[1] == 0x03)
			{
				//grf_printf("UART:B0-0x03\n");
				if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
					//grf_printf("UART:B0-0x03(竖起停止工作)\n");
					ytl_erected = GRF_FALSE;
				}
			}
			else if (cmdBuf[1] == 0x04)
			{
				//grf_printf("UART:B0-0x04\n");
				if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
					//grf_printf("UART:B0-0x04(倾斜开始工作)\n");
					ytl_erected = GRF_TRUE;
				}
			}
			//发送串口数据
			grf_reg_com_send(0x05, cmdBuf[0], cmdBuf[1], 0x00, 0x00);
			break;
		case 0x9A:
			if (cmdBuf[1] == 0x01)
			{
				if (cmdBuf[2] == 0x00)
				{
					//grf_printf("UART:Degree: 0 blue\n");
					ytl_dirty_degree = 0;
				}
				else if (cmdBuf[2] == 0x01)
				{
					//grf_printf("UART:Degree: 1 mild 1\n");
					ytl_dirty_degree = 1;
				}
				else if (cmdBuf[2] == 0x02)
				{
					//grf_printf("UART:Degree: 2 mild 2\n");
					ytl_dirty_degree = 2;
				}
				else if (cmdBuf[2] == 0x03)
				{
					//grf_printf("UART:Degree: 3 severe 1\n");
					ytl_dirty_degree = 3;
				}
				else if (cmdBuf[2] == 0x04)
				{
					//grf_printf("UART:Degree: 4 severe 2\n");
					ytl_dirty_degree = 4;
				}
			}
			grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
			break;
		case 0xE0:
			if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID && ytl_view_get_cur_id != GRF_VIEW19_RESTORE_FACTORY_SETTINGS_ID) {
				if (cmdBuf[1] == 0x00)
				{
					ytl_fault[cmdBuf[2]] = GRF_FALSE;
					//故障修复指令:Host -> 屏

					grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
					for (u8 i = 1; i < 7; ++i)
					{
						if(ytl_fault[i])
						{
							ytl_fault_val = i;
							break;
						}
					}
				}
				else if(cmdBuf[1] >= 0x01 && cmdBuf[1] <= 0x06)
				{
					if (cmdBuf[1] == 0x02)  //取下污水箱就修复污水箱已满故障
					{
						ytl_fault[5] = GRF_FALSE;
					}
					if (cmdBuf[1] == 0x01)  //取下清水箱就修复缺水故障
					{
						ytl_fault[4] = GRF_FALSE;
						ytl_water_shortage_val = GRF_TRUE;
					}
					ytl_fault[cmdBuf[1]] = GRF_TRUE;
					ytl_fault[11] = GRF_FALSE;
					ytl_fault[12] = GRF_FALSE;
					ytl_fault[13] = GRF_FALSE;
					ytl_fault[14] = GRF_FALSE;
					ytl_fault[15] = GRF_FALSE;
					ytl_fault[16] = GRF_FALSE;
					ytl_fault_val = cmdBuf[1];

					//如果在自清洁请清理污水箱避免异味界面,取下污水桶就直接跳转到充电界面
					if (ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
					{
						if (cmdBuf[1] == 0x02)
						{
							grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
						}
						else {
							grf_view_set_dis_view(GRF_VIEW11_FAULT_ID);
						}
					}
					//如果不在充电界面就可以跳转到故障界面,否则在充电界面就不跳转故障界面,
					else if (ytl_view_get_cur_id != GRF_VIEW08_CHARGING_ID && !under_testing_var)
					{
						grf_view_set_dis_view(GRF_VIEW11_FAULT_ID);
					}
				}
				else
				{
					grf_printf("ERROR! Invalid command:cmdBuf[1] == %2x\n",cmdBuf[1]);
				}
			}
			break;
		case 0xF0:
			if (cmdBuf[1] == 0x01)
			{
				isCmdCompletedBuf[88] = GRF_FALSE;
				if (cmdBuf[2] >= 0 && cmdBuf[2] <= 100)
				{
					//获取电量
					ytl_battery_quantity_val = cmdBuf[2];
					get_battery_quantity = GRF_TRUE;
					//grf_printf("ytl_battery_quantity_val ==================================== %d\n",ytl_battery_quantity_val);
					//判断进入智能除菌还是充电界面
					if (ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID)
					{
						if (get_main_view)
						{
							get_main_view = GRF_FALSE;
							grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
						}
						else if (get_charging_view)
						{
							get_charging_view = GRF_FALSE;
							grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
						}
					}
					//语音播报
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
						ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
						ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID ||
						ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID)
					{
						if (ytl_battery_quantity_val == 20) {
							switch_language_pack("04_01_20%");  //电池电量不足
						}
						else if (ytl_battery_quantity_val == 10) {
							switch_language_pack("04_02_10%");  //电量过低请充电
						}
					}
				}
				else
				{
					grf_printf("ERROR! ytl_battery_quantity_val == %d%\n",cmdBuf[2]);
				}
			}
			if (cmdBuf[1] == 0x02)
			{
				if (ytl_view_get_cur_id != GRF_VIEW08_CHARGING_ID &&
					ytl_view_get_cur_id != GRF_VIEW09_SELF_CLEANING_MODE_ID &&
					ytl_view_get_cur_id != GRF_VIEW10_SELF_CLEANING_ID &&
					ytl_view_get_cur_id != GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
				{
					if (ytl_water_shortage_val)  //如果接收到了，语音播报:清水箱缺水,请加水。后面在接受，语音播报:清水箱缺水,请加水。就不再语音播报缺水了
					{
						if (cmdBuf[2] == 0x00)
						{
							ytl_water_shortage_val = GRF_FALSE;
							switch_language_pack("04_03_water_shortage");  //语音播报:清水箱缺水,请加水。
						}
					}
					else
					{
						if(cmdBuf[2] == 0x01)
						{
							ytl_water_shortage_val = GRF_TRUE;
						}
					}
				}
			}
			grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
			break;
	}
}


void grf_reg_set_user(u8* data)
{
	//user code
	USARTy_IRQHandler(data);
}

/*
static s32 grf_reg_s_set(u8 addr,u8* data,u8 len)
{
    if(addr>REG_LEN){
        return GRF_FAIL;
    }
    u8 i=0;
    for(i=0;i<len;i++){
    	ctrlreg[addr+i] = data[i];
        //grf_printf("ctrlreg[%d] = %02X\n",addr+i,ctrlreg[addr+i]);
    }
    grf_reg_set_user(ctrlreg+addr);
    return GRF_OK;
}
*/


static s32 grf_comm_handle(u8* data)
{
	/*
	u8 len = data[3]+3;
	u8 addr = (data[2]);
    if(addr>REG_LEN){
        return GRF_FAIL;
    }
    */
    //grf_reg_s_set(addr,data,len);

	//打印接收串口信息
//	for (u8 j = 0; j < data[3]+3; j++)
//	{
//		grf_printf("data[%d] == 0x%02x\n",j,data[j]);
//	}

	//求校验和
	u8 crc = 0;
	for (u8 j = 0; j < data[3]+2; j++)
	{
		crc += data[j];
	}
	//校验和除256求余
	crc %= 256;
	//grf_printf("crc == 0x%02x\n",crc);

	if (data[data[3]+2]==crc)
	{
		//grf_printf("crc == 0x%02x\n",crc);
		grf_reg_set_user(data);
		return GRF_OK;
	}
	else
	{
		return GRF_FAIL;
	}
}


static void recive_data_handle(u8* databuf,u32 datalen)
{

//	打印接收串口信息长度
//	grf_printf("recive_data_handle datalen =aaaaaaaaaaaaaaaaaaa= %d\n",datalen);
//	for(u16 i=0;i<15;i++)
//	{
//		grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
//	}

	u16 i=0;
	static u16 last_data_num=0;
#if UART_LASTBUFF
	if(last_data_num + datalen > RX_BUF_LEN){
		datalen = datalen-last_data_num;
	}
	if(last_data_num){
		memcpy(RX_HAND_BUF+last_data_num,databuf,datalen);  //把接收到的指令添加到RX_HAND_BUF后面
		databuf=RX_HAND_BUF;  //再把添加完的全部指令赋值给databuf去执行下面的通讯协议
		datalen+=last_data_num;
		last_data_num = 0;
	}
	else {
		memcpy(RX_HAND_BUF,databuf,datalen);  //拷贝接收到的指令给RX_HAND_BUF，这样就不会把多余的错误的指令去执行
		databuf=RX_HAND_BUF;  //再把需要执行的数组赋值给databuf去执行下面的通讯协议
	}
#endif

#if UART_LASTBUFF

//  打印接收串口信息
//	grf_printf("datalen =dddddddddddddddddddddddddddddd= %d\n",datalen);
//	for(u16 i=0;i<15;i++)
//	{
//		grf_printf("databuf[%d]=0x%02x RX_HAND_BUF[%d]=0x%02x\n\n",i,databuf[i],i,RX_HAND_BUF[i]);
//	}

	for(i=0;datalen-i>=7;i++)  //最短的指令为7个
	{
		if(databuf[i]==HEAD_FH && databuf[i+1]==HEAD_FL && grf_comm_handle(databuf+i)==GRF_OK)
		{
			i += (databuf[i+3])+2;
		}
		else {
			break;
		}
	}
	last_data_num = datalen-i;
#endif

#if UART_LASTBUFF
	if(last_data_num<=27 && last_data_num!=0)
	{
		u8  last_data_buf[256] = {0};
		memcpy(last_data_buf,databuf+i,last_data_num);
		memcpy(RX_HAND_BUF,last_data_buf,last_data_num);
	}else{
		last_data_num=0;
		memset(RX_HAND_BUF, 0, sizeof(RX_HAND_BUF)/sizeof(u8));  //利用memset函数清空数组里面的所有元素把值都设为0
	}
#endif
}


void grf_uart_init(void)
{
    grf_uart_cfg_t cfg_t = {0};
    cfg_t.port = 11;
    cfg_t.speed_e = UART_SPEED_115200;
    cfg_t.bit_e = UART_BIT_8;
    cfg_t.parity_e = UART_PARITY_NONE;
    cfg_t.stop_e = UART_STOP_1;
    s32 ret = grf_drv_uart_open(cfg_t);
    grf_printf("ret == %d\n",ret);
    if(ret == GRF_OK)
    {
        grf_drv_uart_rev_set_bfun(recive_data_handle,1024);
    }
}


#endif



