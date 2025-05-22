#ifndef TOF_H_
#define TOF_H_

#include "IfxStdIf_DPipe.h"

#define ISR_PRIORITY_ASCLIN0_TX      16                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN0_RX      9                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN0_ER      24                                      /* Priority for interrupt ISR Errors    */
#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */

void ToF_Init(void);
//static int verifyCheckSum (unsigned char data[]);
//static int checkTofStrength (unsigned char data[]);
int getTofDistance(void);
int data(void);


#endif /* TOF_H_ */
