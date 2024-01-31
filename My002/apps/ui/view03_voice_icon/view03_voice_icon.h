#ifndef __VIEW03_VOICE_ICON_H_
#define __VIEW03_VOICE_ICON_H_

typedef enum {
	VIEW03_VOICE_ICON_NULL,
	VIEW03_VOICE_ICON_IMAGE2_ID = 3,
	VIEW03_VOICE_ICON_IMAGE1_ID = 2,
	VIEW03_VOICE_ICON_IMAGE0_ID = 1
} view03_voice_icon_ctrls_id_e;

void view03_voice_icon_init(void);
void view03_voice_icon_entry(void);
void view03_voice_icon_exit(void);
//.c文件里面自定义函数
void task_create03();
void task_del03();

void control_ytl_mute_v_away(void);

#endif
