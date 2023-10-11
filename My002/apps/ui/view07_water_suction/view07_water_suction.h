#ifndef __VIEW07_WATER_SUCTION_H_
#define __VIEW07_WATER_SUCTION_H_

typedef enum {
	VIEW07_WATER_SUCTION_NULL,
	VIEW07_WATER_SUCTION_IMAGE0_ID = 2,
	VIEW07_WATER_SUCTION_LABEL0_ID = 1
} view07_water_suction_ctrls_id_e;

void view07_water_suction_init(void);
void view07_water_suction_entry(void);
void view07_water_suction_exit(void);

#endif
