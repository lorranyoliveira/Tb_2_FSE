#ifndef LOG_H_
#define LOG_H_

#include <string>

void create_file_log();
void close_file_log();
void write_in_file_log(float temp_interna, float temp_ambiente, float temp_referencia);

#endif /* PID_H_ */