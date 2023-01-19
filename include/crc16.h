/*
 * crc16.h
 *
 *  Created on: 18/03/2014
 *      Author: Renato Coral Sampaio
 *
 */

#ifndef CRC16_H_
#define CRC16_H_


short CRC16(unsigned short crc, char data);
short calculate_crc(unsigned char *commands, int size);
void conf_crc(unsigned char *buffer, int size);
bool verify_crc(unsigned char * buffer, int size);

#endif /* CRC16_H_ */