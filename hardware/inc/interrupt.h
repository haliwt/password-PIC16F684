#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "../../main.h"


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptEnable();
 */
#define INTERRUPT_GlobalInterruptEnable()   (INTCONbits.GIE = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptDisable();
 */
#define INTERRUPT_GlobalInterruptDisable()    (INTCONbits.GIE = 0)
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable peripheral interrupts.
 * @Example
    INTERRUPT_PeripheralInterruptEnable();
 */
#define INTERRUPT_PeripheralInterruptEnable()     (INTCONbits.PEIE = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable peripheral interrupts.
 * @Example
    INTERRUPT_PeripheralInterruptDisable();
 */
#define INTERRUPT_PeripheralInterruptDisable()      (INTCONbits.PEIE = 0)

void interrupt INT(void);  

#endif  // INTERRUPT_MANAGER_H
/**
 End of File
*/














