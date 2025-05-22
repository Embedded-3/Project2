#ifndef BSW_ETC_ISR_PRIORITY_H_
#define BSW_ETC_ISR_PRIORITY_H_


/* Definition of the interrupt priorities */
#define ISR_PRIORITY_ASCLIN_TX      8                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN_RX      4                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_ER      12                                      /* Priority for interrupt ISR Errors    */

#define ISR_PRIORITY_ASCLIN_TOF_TX  30                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_TOF_RX  31                                      /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_TOF_ER  32                                       /* Priority for interrupt ISR Receive   */

#endif /* BSW_ETC_ISR_PRIORITY_H_ */
