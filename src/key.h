#ifndef KEY_H
#define KEY_H

#ifdef cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    KEY_POWER = 0,
} key_typedef_enum;

typedef enum
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1
} keymode_typedef_enum;

extern uint8_t key_act;

void rc_key_init(void);
void proc_key(void);
/* configure key */
void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum key_mode);
/* return the selected button state */
uint8_t gd_eval_key_state_get(key_typedef_enum keynum);

#ifdef cplusplus
}
#endif

#endif /* KEY_H */