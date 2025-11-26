/*
 * nvm.c
 *
 *  Created on: 2025. 11. 26.
 *      Author: kangc
 */
#include "main.h"

#define FLASH_USER_START_ADDR (ADDR_FLASH_PAGE_15)

static uint8_t ram_buffer[FLASH_PAGE_SIZE];

/**
  * @brief
  * @retval
  */
void nvm_init(void)
{
  for(int i=0; i<FLASH_PAGE_SIZE; i++)
  {
    ram_buffer[i] = (uint8_t)*((uint32_t *)(FLASH_USER_START_ADDR));
  }
}

/**
  * @brief
  * @retval
  */
static uint32_t nvm_get_page(uint32_t address)
{
  return (address - FLASH_BASE) / FLASH_PAGE_SIZE;;
}


/**
  * @brief
  * @retval
  */
static void nvm_flush(void)
{
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Page        = nvm_get_page(FLASH_USER_START_ADDR);
  EraseInitStruct.NbPages     = 1;

  HAL_FLASH_Unlock();

  uint32_t PageError;

  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
  {
    Error_Handler();
  }

  uint32_t Address = FLASH_USER_START_ADDR;
  uint32_t index = 0;

  while (Address < FLASH_USER_START_ADDR + FLASH_PAGE_SIZE) //one page 2K
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)ram_buffer[index]) == HAL_OK)
    {
      Address = Address + 8;  /* increment to next double word*/
      index = index + 8;
    }
    else
    {
      Error_Handler();
    }
  }

  HAL_FLASH_Lock();
}


/**
  * @brief
  * @retval
  */
void nvm_write_byte(uint32_t address, uint8_t byte)
{
  ram_buffer[address] = byte;
  nvm_flush();
}


/**
  * @brief
  * @retval
  */
uint8_t nvm_read_byte(uint32_t address)
{
  return ram_buffer[address];
}















