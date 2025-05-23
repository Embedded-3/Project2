#ifndef MAIN_H
#define MAIN_H


#define ON_OFF_SW_PIN         &MODULE_P33, 6
#define ADAS_LED_PIN          &MODULE_P22, 2

#define BRAKE_PIN             &MODULE_P11, 6

// d49 d51 d53
#define YELLOW_SPEED_SW_PIN   &MODULE_P21, 0
#define GREEN_SPEED_SW_PIN    &MODULE_P33, 12
#define BLUE_SPEED_SW_PIN     &MODULE_P33, 7


typedef enum {
    ON_OFF = 0,
    SPEED_BLUE = 1,
    SPEED_GREEN = 2,
    SPEED_YELLOW = 3,
} SwitchType; //SpeedType;



void AppTask1ms(void);
void AppTask10ms(void);
void AppTask100ms(void);
void AppTask1000ms(void);

//#define print(...) tx_uart_pc_debug(__VA_ARGS__)

#endif