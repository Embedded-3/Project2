#ifndef MAIN_H
#define MAIN_H

typedef struct{
    int on_off;
    int y;
    int g;
    int b;
} switch_t;

typedef enum {
    ON_OFF = 0,
    SPEED_YELLOW = 1,
    SPEED_GREEN = 2,
    SPEED_BLUE = 3,
} SpeedType;

void AppTask1ms(void);
void AppTask10ms(void);
void AppTask100ms(void);
void AppTask1000ms(void);

//#define print(...) tx_uart_pc_debug(__VA_ARGS__)

#endif