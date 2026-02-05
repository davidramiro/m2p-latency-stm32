#include <stdint.h>
#include "../Inc/main.h"
#include "../Inc/usb.h"

uint8_t hid_report[HID_REPORT_SIZE] = {0};

uint32_t startMouseAction() {
    HAL_TIM_Base_Stop_IT(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    HAL_TIM_Base_Start_IT(&htim2);

    if (mainMenuIndex == CLICK) {
        hid_report[0] = 1;
        hid_report[1] = 0;
        hid_report[2] = 0;;
    } else if (mainMenuIndex == MOVE) {
        hid_report[0] = 0;
        hid_report[1] = 127;
        hid_report[2] = 127;;
    }

    while (!HID_IsIdle(&hUsbDeviceFS)) {
    }
    USBD_HID_SendReport(&hUsbDeviceFS, hid_report, HID_REPORT_SIZE);

    return TIM2->CNT;
}

void stopMouseAction() {
    if (mainMenuIndex == CLICK) {
        hid_report[0] = 0;
        hid_report[1] = 0;
        hid_report[2] = 0;
    } else {
        hid_report[0] = 0;
        hid_report[1] = -127;
        hid_report[2] = -127;
    }
    while (!HID_IsIdle(&hUsbDeviceFS)) {
    }
    USBD_HID_SendReport(&hUsbDeviceFS, hid_report, HID_REPORT_SIZE);
}

uint8_t HID_IsIdle(const USBD_HandleTypeDef *pdev) {
    return ((USBD_HID_HandleTypeDef *) pdev->pClassData)->state == USBD_HID_IDLE;
}