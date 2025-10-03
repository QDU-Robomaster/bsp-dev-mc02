#pragma once
// Auto-generated Flash Layout Map
// MCU: STM32H723VGT6

#include "main.h"

#include "stm32_flash.hpp"

constexpr LibXR::FlashSector FLASH_SECTORS[] = {
  {0x08000000, 0x00020000},
  {0x08020000, 0x00020000},
  {0x08040000, 0x00020000},
  {0x08060000, 0x00020000},
  {0x08080000, 0x00020000},
  {0x080A0000, 0x00020000},
  {0x080C0000, 0x00020000},
  {0x080E0000, 0x00020000},
};

constexpr size_t FLASH_SECTOR_NUMBER = sizeof(FLASH_SECTORS) / sizeof(LibXR::FlashSector);