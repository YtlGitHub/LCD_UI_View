#ifndef __VIEW16_HELP4_H_
#define __VIEW16_HELP4_H_

typedef enum {
	VIEW16_HELP4_NULL,
	VIEW16_HELP4_QRCODE0_ID = 3,
	VIEW16_HELP4_LABEL0_ID = 2,
	VIEW16_HELP4_IMAGE0_ID = 1
} view16_help4_ctrls_id_e;

void view16_help4_init(void);
void view16_help4_entry(void);
void view16_help4_exit(void);

#endif
