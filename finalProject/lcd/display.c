/*
 * display.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Stefan
 */
#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <arm_math.h>
#include "arm_const_structs.h"
#include "ButtonConfig.h"

extern Graphics_Context g_sContext;


void LCD_configure(void){
/* Initializes display */
    Crystalfontz128x128_Init();
/* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
/* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
/* Set default screen colors */
    Graphics_setForegroundColor(&g_sContext, ClrWhite);
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);
    Graphics_setFont(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
    Graphics_flushBuffer(&g_sContext);
    Delay1();
}

void clearSlide(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);
}

void welcomeScreen(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Welcome to ", GRAPHICS_AUTO_STRING_LENGTH, 64, 15, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Buff Bikes", GRAPHICS_AUTO_STRING_LENGTH, 64, 35, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Tap your RFID", GRAPHICS_AUTO_STRING_LENGTH, 64, 75, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Below", GRAPHICS_AUTO_STRING_LENGTH, 64, 95, GRAPHICS_TRANSPARENT_TEXT);
}

void registerStudent(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Register your", GRAPHICS_AUTO_STRING_LENGTH, 64, 20, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Student ID below", GRAPHICS_AUTO_STRING_LENGTH, 64, 35, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Using the", GRAPHICS_AUTO_STRING_LENGTH, 64, 85, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"joystick", GRAPHICS_AUTO_STRING_LENGTH, 64, 95, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"- and -", GRAPHICS_AUTO_STRING_LENGTH, 64, 105, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"buttons", GRAPHICS_AUTO_STRING_LENGTH, 64, 115, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawLine(&g_sContext, 0, Graphics_getDisplayHeight(&g_sContext) - 1, Graphics_getDisplayWidth(&g_sContext) - 1, Graphics_getDisplayHeight(&g_sContext) - 1);
    Graphics_drawLine(&g_sContext, 0, 0, Graphics_getDisplayWidth(&g_sContext) - 1, 0);
    Graphics_drawLine(&g_sContext, 0, 0, 0, Graphics_getDisplayHeight(&g_sContext) - 1);
    Graphics_drawLine(&g_sContext, Graphics_getDisplayWidth(&g_sContext) - 1, 0, Graphics_getDisplayWidth(&g_sContext) - 1, Graphics_getDisplayHeight(&g_sContext) - 1);
}

void checkout(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Checkout", GRAPHICS_AUTO_STRING_LENGTH, 64, 5, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawLine(&g_sContext, 32, 12, 96, 12);
    Graphics_drawLine(&g_sContext, 32, 0, 32, 12);
    Graphics_drawLine(&g_sContext, 96, 0, 96, 12);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"How long do", GRAPHICS_AUTO_STRING_LENGTH, 64, 35, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"you need it?", GRAPHICS_AUTO_STRING_LENGTH, 64, 55, GRAPHICS_TRANSPARENT_TEXT);
}

void thankYou(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Thank you for", GRAPHICS_AUTO_STRING_LENGTH, 64, 30, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"your time!", GRAPHICS_AUTO_STRING_LENGTH, 64, 40, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Your Bike is", GRAPHICS_AUTO_STRING_LENGTH, 64, 80, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"buzzing for you", GRAPHICS_AUTO_STRING_LENGTH, 64, 95, GRAPHICS_TRANSPARENT_TEXT);
}

void noBikes(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"We're sorry!", GRAPHICS_AUTO_STRING_LENGTH, 64, 10, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)":'(", GRAPHICS_AUTO_STRING_LENGTH, 64, 25, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"There are no", GRAPHICS_AUTO_STRING_LENGTH, 64, 60, GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"bikes available", GRAPHICS_AUTO_STRING_LENGTH, 64, 75, GRAPHICS_TRANSPARENT_TEXT);
}

void error(void){
    Graphics_flushBuffer(&g_sContext);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, ClrWhite);//ClrBlack
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);//ClrWhite
    Graphics_drawStringCentered(&g_sContext, (int8_t *)"Error: 404", GRAPHICS_AUTO_STRING_LENGTH, 64, 64, GRAPHICS_TRANSPARENT_TEXT);
}





