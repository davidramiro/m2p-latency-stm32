#pragma once
#include <stdint.h>
#include "usbd_hid.h"
#include "usb_device.h"

#define HID_REPORT_SIZE 4

extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t HID_IsIdle(const USBD_HandleTypeDef *pdev);
uint32_t startMouseAction();
void stopMouseAction();