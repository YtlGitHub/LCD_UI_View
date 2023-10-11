#ifndef __VIEW04_BATTERY_WATER_H_
#define __VIEW04_BATTERY_WATER_H_

typedef enum {
	VIEW04_BATTERY_WATER_NULL,
	VIEW04_BATTERY_WATER_IMAGE0_ID = 2,
	VIEW04_BATTERY_WATER_IMAGE1_ID = 3,
	VIEW04_BATTERY_WATER_ARC0_ID = 1,
	VIEW04_BATTERY_WATER_LABEL2_ID = 6,
	VIEW04_BATTERY_WATER_LABEL0_ID = 4
} view04_battery_water_ctrls_id_e;

void view04_battery_water_init(void);
void view04_battery_water_entry(void);
void view04_battery_water_exit(void);
//.c文件里面自定义函数
void task_create04();
void task_del04();

#endif
