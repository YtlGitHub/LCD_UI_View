#ifndef __VIEW05_STERILIZATION_FLUID_PREPARATION_H_
#define __VIEW05_STERILIZATION_FLUID_PREPARATION_H_

typedef enum {
	VIEW05_STERILIZATION_FLUID_PREPARATION_NULL,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE3_ID = 6,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE0_ID = 3,
	VIEW05_STERILIZATION_FLUID_PREPARATION_LABEL0_ID = 1,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE1_ID = 4,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE2_ID = 5,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE4_ID = 8,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE6_ID = 9,
	VIEW05_STERILIZATION_FLUID_PREPARATION_CONTAINER0_ID = 2,
	VIEW05_STERILIZATION_FLUID_PREPARATION_CONTAINER1_ID = 10,
	VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE7_ID = 12
} view05_sterilization_fluid_preparation_ctrls_id_e;

void view05_sterilization_fluid_preparation_init(void);
void view05_sterilization_fluid_preparation_entry(void);
void view05_sterilization_fluid_preparation_exit(void);
//.c文件里面自定义函数
void task_create05();
void task_del05();

#endif
