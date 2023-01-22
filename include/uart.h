#ifndef UART_H_
#define UART_H_

void init_UART();
void stop_UART();
void send_message(unsigned char *buffer, int size);
unsigned char *receive_message();
double get_info(int sub_codigo, int codigo);
int set_info(int sub_codigo, int codigo, int value);
#endif /* UART_H_ */
