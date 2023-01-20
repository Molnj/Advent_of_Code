/* 
 * Header file containing standard AUTOSAR types
 * source: https://www.autosar.org/fileadmin/user_upload/standards/classic/4-3/AUTOSAR_SWS_StandardTypes.pdf (chapter 8)
 * 2022.06.11.
*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

typedef uint8_t Std_ReturnType;	/* Standard API return type which is shared between the RTE and the BSW modules */
#define E_OK        0x00u		/* OK return value */
#define E_NOT_OK    0x01u		/* NOK return value */

#define STD_HIGH    0x01u		/* Physical state 5V or 3.3V */
#define STD_LOW     0x00u		/* Physical state 0V */

#define STD_ACTIVE  0x01u		/* Logical state active */
#define STD_IDLE    0x00u		/* Logical state idle */

#define STD_ON      0x01u		/**/
#define STD_OFF     0x00u		/**/

#endif /* STD_TYPES_H */