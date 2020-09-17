#include <stddef.h>
#include <stdint.h>

#include "lcd.h"

#define LCD_COLUMN_NUMBER 128
#define LCD_LINE_NUMBER 64

#define LCD_PAGE_NUMBER (LCD_LINE_NUMBER / 8)
#define LCD_COMMAND_NUMBER 13

unsigned char READ_BACK[32];  ////一个汉字最大返回32个字节
// unsigned char CHAR_DATA[32];
const unsigned char LCD_init_cmd[LCD_COMMAND_NUMBER] = {
    0xe2,  //软复位
    0x2c,  //升压步聚1
    0x2e,  //升压步聚2
    0x2f,  //升压步聚3
#ifndef RC
    0x26,  //粗调对比度，可设置范围0x20～0x27
#else
    0x25,  //粗调对比度，可设置范围0x20～0x27
#endif
    0x81,  //微调对比度
    0x18,  //微调对比度的值，可设置范围0x00～0x3f
    0xa2,  // 1/9 偏压比（bias）
    0xA0,  //列扫描顺序：从左到右
    0xc8,  //行扫描顺序：反序
    0xa6,  //正显
    0x40,  //起始行：第一行开始
    0xaf,  //开显示
};

uint8_t SPI_SendByte(uint8_t data) {
    SPI_SCK_0;
    for (size_t i = 0; i < 8; i++) {
        if ((data & 0x80) == 0) {
            SPI_SDA_0;
        } else {
            SPI_SDA_1;
        }
        SPI_SCK_1;
        data <<= 1;
        if (SPI_FSO) {
            data |= 0x01;
        }
        SPI_SCK_0;
    }
    return data;
}

void Send4Byte(unsigned long cmd) {
    cmd |= 0x03000000;
    for (size_t i = 0; i < 4; i++) {
        SPI_SendByte((cmd >> (24 - (i * 8))) & 0xff);
    }
}

void LCD_send_cmd(unsigned char o_command) {
    SPI_DC_0;
    SPI_CS_0;
    SPI_SendByte(o_command);
    SPI_CS_1;
}
void LCD_send_data(unsigned char o_data) {
    SPI_DC_1;
    SPI_CS_0;
    SPI_SendByte(o_data);
    SPI_CS_1;
}

void lcd_address(uint8_t page, uint8_t column) {
    //设置页地址，每8 行为一页，全屏共64 行，被分成8 页
    LCD_send_cmd(0xb0 + page);
    LCD_send_cmd(0x10 + (column >> 4 & 0x0f));  //设置列地址的高4 位
    LCD_send_cmd(column & 0x0f);                //设置列地址的低4 位
}

void LCD_clear(void) {
    for (size_t page = 0; page < LCD_PAGE_NUMBER; page++) {  // page loop
        lcd_address(page, 0);
        for (size_t column = 0; column < LCD_COLUMN_NUMBER;
             column++) {  // column loop
            LCD_send_data(0x00);
        }
    }
}
void LCD_full(void) {
    for (size_t page = 0; page < LCD_PAGE_NUMBER; page++) {  // page loop
        lcd_address(page, 0);
        for (size_t column = 0; column < LCD_COLUMN_NUMBER;
             column++) {  // column loop
            LCD_send_data(0xff);
        }
    }
}
void LCD_init(void) {
    for (size_t i = 0; i < LCD_COMMAND_NUMBER; i++) {
        LCD_send_cmd(LCD_init_cmd[i]);
    }
}

void Picture_display(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
                     const unsigned char *ptr_pic) {
    for (size_t page = 0; page < height / 8; page++) {  // page loop
        lcd_address(page + y, x);
        for (size_t column = 0; column < width; column++) {  // column loop
            LCD_send_data(*ptr_pic++);
        }
    }
}
void Picture_ReverseDisplay(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
                            const unsigned char *ptr_pic) {
    size_t data;
    for (size_t page = 0; page < height / 8; page++) {  // page loop
        lcd_address(page + y, x);
        for (size_t column = 0; column < width; column++) {  // column loop
            data = *ptr_pic++;
            data = ~data;
            LCD_send_data(data);
        }
    }
}

unsigned char r_dat_bat(unsigned long address, unsigned char byte_long,
                        unsigned char *p_arr) {
    SPI_CS2_0;
    Send4Byte(address);
#ifdef AF_SDA
    SET_SDA_IN;
#endif
    for (size_t j = 0; j < byte_long; j++) {
        p_arr[j] = SPI_SendByte(0x00);
    }
#ifdef AF_SDA
    SET_SDA_OUT;
#endif
    SPI_CS2_1;
    return p_arr[0];
}

/****************************************
ASCII 调用
ASCIICode：表示ASCII 码（8bits）
BaseAdd：说明该套字库在芯片中的起始地址。
r_dat_bat： 是读点阵数据函数。
READ_BACK：是保存读出的点阵数据的数组。
****************************************/
unsigned char ASCII_GetData(unsigned char ASCIICode, unsigned long BaseAdd) {
    if ((ASCIICode >= 0x20) && (ASCIICode <= 0x7e)) {
        switch (BaseAdd) {
            case 0x3bfc0:
                r_dat_bat((ASCIICode - 0x20) * 8L + BaseAdd, 8,
                          READ_BACK);  // 5X7
                break;
            case 0x66c0:
                r_dat_bat((ASCIICode - 0x20) * 8L + BaseAdd, 8,
                          READ_BACK);  // 7X8
                break;
            case 0x3b7c0:
                r_dat_bat((ASCIICode - 0x20) * 16L + BaseAdd, 16,
                          READ_BACK);  // 8X16 A
                break;
            case 0x3cf80:
                r_dat_bat((ASCIICode - 0x20) * 16L + BaseAdd, 16,
                          READ_BACK);  // 8X16 F
                break;
            case 0x3c2c0:
                r_dat_bat((ASCIICode - 0x20) * 34L + BaseAdd + 2L, 32,
                          READ_BACK);  // 16X16 Arial
                break;
            case 0x3d580:
                r_dat_bat((ASCIICode - 0x20) * 34L + BaseAdd + 2L, 32,
                          READ_BACK);  // 16X16 T
                break;
            default:
                break;
        }
        return 1;
    } else
        return 0;
}

/***************************************************
16 点GB2312 标准点阵字库
参数说明：
GBCode表示汉字内码。
MSB 表示汉字内码GBCode 的高8bits。
LSB 表示汉字内码GBCode 的低8bits。
Address 表示汉字或ASCII字符点阵在芯片中的字节地址。
BaseAdd：说明点阵数据在字库芯片中的起始地址。
r_dat_bat 是读点阵数据函数。
READ_BACK是保存读出的点阵数据的数组。
*****************************************************/
void gt_16_GetData(unsigned char MSB, unsigned char LSB) {
    unsigned long BaseAdd = 0L, Address;

    if (MSB == 0xA9 && LSB >= 0xA1)
        Address = (282L + (LSB - 0xA1)) * 32L + BaseAdd;
    else if (MSB >= 0xA1 && MSB <= 0xA3 && LSB >= 0xA1)
        Address = ((MSB - 0xA1) * 94L + (LSB - 0xA1)) * 32L + BaseAdd;
    else if (MSB >= 0xB0 && MSB <= 0xF7 && LSB >= 0xA1)
        Address = ((MSB - 0xB0) * 94L + (LSB - 0xA1) + 846L) * 32L + BaseAdd;
    else
        return;

    r_dat_bat(Address, 32, READ_BACK);
}

/****************************************************
8X16 点国标扩展字符
说明：
BaseAdd：说明本套字库在字库芯片中的起始字节地址。
FontCode：表示字符内码（16bits）.
Address：表示字符点阵在芯片中的字节地址。
r_dat_bat 是读点阵数据函数。
READ_BACK是保存读出的点阵数据的数组。
*****************************************************/
void GB_EXT_816(unsigned int FontCode) {
    unsigned long BaseAdd = 0x3b7d0, Address;
    if (FontCode >= 0xAAA1 && FontCode <= 0xAAFE)
        Address = (FontCode - 0xAAA1) * 16L + BaseAdd;
    else if (FontCode >= 0xABA1 && FontCode <= 0xABC0)
        Address = (FontCode - 0xABA1 + 95L) * 16L + BaseAdd;
    else
        return;
    r_dat_bat(Address, 16, READ_BACK);
}

void display_one_word(unsigned char X_ADD, unsigned char Y_ADD,
                      const unsigned char *chinese_char) {
    gt_16_GetData(*chinese_char, *(chinese_char + 1));
    // #if (LCD_DIS_CHINA_ROT == 90)
    // dis_data_90_();
    // #else
    // for (size_t x = 0; x < 32; x++) {
    //     CHAR_DATA[x] = READ_BACK[x];
    // }
    // #endif
    lcd_address(Y_ADD, X_ADD);
    for (size_t x = 0; x < 16; x++) {
        LCD_send_data(READ_BACK[x]);
    }
    lcd_address(Y_ADD + 1, X_ADD);
    for (size_t x = 16; x < 32; x++) {
        LCD_send_data(READ_BACK[x]);
    }
}

void display_str_word(unsigned char X_ADD, unsigned char Y_ADD,
                      const unsigned char *chinese_str) {
    while ((*chinese_str) != '\0') {
        display_one_word(X_ADD, Y_ADD, chinese_str);
        X_ADD += 16;
        chinese_str += 2;
    }
}

size_t display_one_char(unsigned char X_ADD, unsigned char Y_ADD, fontType ft,
                        char achar) {
    size_t count_col, count_page;
    switch (ft) {
        case font_5X7: {  // 5X7点阵ASCII标准字符
            ASCII_GetData(achar, 0x3bfc0);
            count_col = 5;
            count_page = 1;
        } break;
        case font_7X8: {  // 7X8点阵ASCII标准字符
            ASCII_GetData(achar, 0x66c0);
            count_col = 7;
            count_page = 1;
        } break;
        case font_8X16: {  // 8X16点阵ASCII标准字符
            ASCII_GetData(achar, 0x3b7c0);
            count_col = 8;
            count_page = 2;
        } break;
        case font_8X16_bold: {  // 8X16点阵ASCII粗体字符
            ASCII_GetData(achar, 0x3cf80);
            count_col = 8;
            count_page = 2;
        } break;
        default:
            return 0;
    }
    for (size_t j = 0; j < count_page; j++) {
        lcd_address(Y_ADD + j, X_ADD);
        for (size_t i = 0; i < count_col; i++) {
            LCD_send_data(READ_BACK[i + (8 * j)]);
        }
    }
    return count_col;
}
// length: 输出字符长度，主要用来清屏
void display_str_ascii(unsigned char X_ADD, unsigned char Y_ADD, fontType ft,
                       uint8_t length, const char *str) {
    lcd_address(Y_ADD, X_ADD);
    while ((*str) != '\0') {
        X_ADD += display_one_char(X_ADD, Y_ADD, ft, *str);
        str++;
        length--;
    }
    while (length) {
        for (size_t x = 0; x < length; x++) {
            X_ADD += display_one_char(X_ADD, Y_ADD, ft, ' ');
        }
        length--;
    }
}