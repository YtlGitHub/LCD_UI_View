#ifndef __VIEW08_CHARGING_H_
#define __VIEW08_CHARGING_H_

typedef enum {
	VIEW08_CHARGING_NULL,
	VIEW08_CHARGING_IMAGE4_ID = 5,
	VIEW08_CHARGING_IMAGE3_ID = 4,
	VIEW08_CHARGING_LABEL1_ID = 7,
	VIEW08_CHARGING_LABEL0_ID = 6
} view08_charging_ctrls_id_e;

void view08_charging_init(void);
void view08_charging_entry(void);
void view08_charging_exit(void);

#endif
