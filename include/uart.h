#ifndef UART_H_
#define UART_H_

void init_UART();
void stop_UART();
void send_message(unsigned char *buffer, int size);
unsigned char *receive_message();
double get_temp_(int sub_codigo);
double send_temp_(int sub_codigo);

#endif /* UART_H_ */
