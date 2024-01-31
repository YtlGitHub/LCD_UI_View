#ifndef __GRF_HW_UART_H_
#define __GRF_HW_UART_H_

#define EXTERNAL_BUFFER_SIZE_languageBuf 4
extern u8 *languageBuf[EXTERNAL_BUFFER_SIZE_languageBuf];
extern u8 cmdBuf[];
extern u8 isCmdCompletedBuf[];
#define EXTERNAL_BUFFER_SIZE 100 //100
#define RTOS_EXECUTEBUFF 0


void grf_uart_init(void);
s32 grf_reg_com_send(u8 len, u8 cmd, u8 date0, u8 date1, u8 date2);
extern u8 ytl_view_get_cur_id;
extern u8 ytl_volume;
void switch_language_pack(char filename[]);
void key_sound_tr660r_wavplay(char filename[]);
void control_key_failure(void);
void power_on(void);
void save_system_settings_var(void);
void volume_size(void);


//extern void tr660r_wavplay(char filename[],int volume);


//自声明
//view1
extern grf_bool ytl_Power;
extern grf_bool ytl_back;
extern grf_bool ytl_confirmation;
extern grf_bool ytl_right;
extern grf_bool ytl_self_cleaning;
extern grf_bool ytl_mute;
extern grf_bool ytl_help;

//view2
extern grf_bool ytl_erected;
extern u8 ytl_dirty_degree;

//view3
extern u8 ytl2_voice_image_val;

//view4
extern u8 ytl_battery_quantity_val;
extern grf_bool ytl1_cleaning_method;
extern grf_bool ytl_water_shortage_val;

//view9
extern u8 ytl_mode_select_uart;  //模式选择变量判断进入的是智能除菌,还是自清洁的智能除菌

//view11
extern u8 ytl_fault[EXTERNAL_BUFFER_SIZE];
extern u8 ytl_fault_val;

//view17
extern grf_bool ytl0_roller_brush_lighting;
extern u8 ytl3_switch_language;

#endif
