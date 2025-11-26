/*
 * nvm.h
 *
 *  Created on: 2025. 11. 26.
 *      Author: kangc
 */

#ifndef INC_NVM_H_
#define INC_NVM_H_

extern void nvm_init(void);
extern void nvm_write_byte(uint32_t address, uint8_t byte);
extern uint8_t nvm_read_byte(uint32_t address);

#endif /* INC_NVM_H_ */
