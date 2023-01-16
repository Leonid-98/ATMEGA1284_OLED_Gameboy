/**
 * Private configuration file for the SSD1306 library.
 * This example is configured for STM32F0, I2C and including all fonts.
 */

#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

#define SSD1306_I2C_ADDR        0x3C
#define SSD1306_WIDTH           128
#define SSD1306_HEIGHT          64
#define SSD1306_BUFFER_SIZE     SSD1306_WIDTH *SSD1306_HEIGHT / 8

#ifdef SSD1306_X_OFFSET
#define SSD1306_X_OFFSET_LOWER (SSD1306_X_OFFSET & 0x0F)
#define SSD1306_X_OFFSET_UPPER ((SSD1306_X_OFFSET >> 4) & 0x07)
#else
#define SSD1306_X_OFFSET_LOWER 0
#define SSD1306_X_OFFSET_UPPER 0
#endif

//#define SSD1306_INCLUDE_FONT_6x8
//#define SSD1306_INCLUDE_FONT_7x10
//#define SSD1306_INCLUDE_FONT_11x18
//#define SSD1306_INCLUDE_FONT_16x26

// #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ
// #define SSD1306_INVERSE_COLOR

#endif /* __SSD1306_CONF_H__ */
