#ifndef __VIEW17_SYSTEM_SETTING_H_
#define __VIEW17_SYSTEM_SETTING_H_

typedef enum {
	VIEW17_SYSTEM_SETTING_NULL,
	VIEW17_SYSTEM_SETTING_LABEL1_ID = 7,
	VIEW17_SYSTEM_SETTING_LABEL0_ID = 6,
	VIEW17_SYSTEM_SETTING_CONTAINER0_ID = 1,
	VIEW17_SYSTEM_SETTING_LABEL2_ID = 9,
	VIEW17_SYSTEM_SETTING_IMAGE4_ID = 8,
	VIEW17_SYSTEM_SETTING_LABEL3_ID = 10,
	VIEW17_SYSTEM_SETTING_LABEL5_ID = 12,
	VIEW17_SYSTEM_SETTING_LABEL4_ID = 11,
	VIEW17_SYSTEM_SETTING_IMAGE1_ID = 3,
	VIEW17_SYSTEM_SETTING_IMAGE2_ID = 4,
	VIEW17_SYSTEM_SETTING_IMAGE0_ID = 2
} view17_system_setting_ctrls_id_e;


void view17_system_setting_init(void);
void view17_system_setting_entry(void);
void view17_system_setting_exit(void);
void key_task17_cb();
void task_create17();
void task_del17();


extern u8 mute_key_voice;


#endif
