#include <stdint.h>

const unsigned char picture_tab[] = {
    /*------------------------------------------------------------------------------
;  列行式，低位在前，阴码
;  宽×高（像素）: 128×64
------------------------------------------------------------------------------*/
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x44, 0x08, 0x00, 0x18, 0x48, 0x28, 0xC8, 0x08,
    0x28, 0x48, 0x18, 0x00, 0x40, 0x40, 0xFC, 0x40, 0x40, 0xFC, 0x00, 0x00,
    0xF8, 0x00, 0x00, 0xFC, 0x00, 0x40, 0x40, 0xA0, 0x90, 0x88, 0x84, 0x88,
    0x90, 0x20, 0x40, 0x40, 0x00, 0x00, 0x40, 0x44, 0xD8, 0x20, 0xF0, 0xAC,
    0xA8, 0xE8, 0xB8, 0xA8, 0xE0, 0x00, 0x00, 0x00, 0xC0, 0x7C, 0x54, 0x54,
    0x54, 0x54, 0x54, 0x54, 0x7C, 0x40, 0x40, 0x00, 0x00, 0xF0, 0x90, 0x90,
    0x90, 0xFC, 0x90, 0x90, 0x90, 0xF0, 0x00, 0x00, 0x00, 0x80, 0x88, 0x88,
    0x88, 0x88, 0x88, 0xE8, 0xA8, 0x98, 0x8C, 0x88, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
    0x3E, 0x01, 0x10, 0x11, 0x09, 0x05, 0x3F, 0x05, 0x09, 0x11, 0x11, 0x00,
    0x08, 0x18, 0x0F, 0x24, 0x14, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x3F,
    0x00, 0x20, 0x22, 0x2A, 0x32, 0x22, 0x3F, 0x22, 0x32, 0x2A, 0x22, 0x20,
    0x00, 0x00, 0x20, 0x10, 0x0F, 0x10, 0x28, 0x24, 0x23, 0x20, 0x2F, 0x28,
    0x2A, 0x2C, 0x00, 0x30, 0x0F, 0x04, 0x3D, 0x25, 0x15, 0x15, 0x0D, 0x15,
    0x2D, 0x24, 0x24, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x1F, 0x24, 0x24,
    0x24, 0x27, 0x20, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x81, 0x41, 0x21, 0x21, 0x61, 0x01, 0x01, 0x21, 0xE1,
    0xE1, 0x01, 0xE1, 0xE1, 0x21, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x21, 0xE1, 0x21, 0x21, 0x21, 0x61, 0x01, 0x01, 0x21, 0x21, 0xE1, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xC1, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x21,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0x10, 0x20, 0x24, 0x1C, 0x04, 0x00, 0x20, 0x3F, 0x01, 0x3E, 0x01, 0x3F,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x22, 0x22,
    0x27, 0x30, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, 0x1E,
    0x25, 0x25, 0x25, 0x16, 0x00, 0x00, 0x1E, 0x21, 0x21, 0x21, 0x13, 0x00,
    0x01, 0x01, 0x1F, 0x21, 0x21, 0x00, 0x00, 0x00, 0x21, 0x3F, 0x22, 0x21,
    0x01, 0x00, 0x00, 0x1E, 0x21, 0x21, 0x21, 0x1E, 0x00, 0x21, 0x3F, 0x22,
    0x01, 0x01, 0x3E, 0x20, 0x00, 0x21, 0x21, 0x3F, 0x20, 0x20, 0x00, 0x00,
    0x1E, 0x21, 0x21, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x08, 0x04, 0x04, 0x04,
    0x0C, 0x00, 0xF0, 0x08, 0x04, 0x04, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0xFC, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x04, 0xFC, 0x04,
    0x0C, 0x00, 0x04, 0xFC, 0x04, 0x04, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x81, 0x82, 0x84, 0x84, 0x84, 0x82, 0x80, 0x81, 0x82,
    0x84, 0x84, 0x82, 0x81, 0x80, 0x80, 0x86, 0x86, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x85, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x84, 0x87, 0x84, 0x84,
    0x84, 0x86, 0x80, 0x80, 0x80, 0x84, 0x87, 0x84, 0x80, 0x80, 0x84, 0x87,
    0x84, 0x84, 0x82, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0xFF

};
const uint8_t battery_start[] = {0x3e, 0x22, 0x7f, 0x41};
const uint8_t battery_end[] = {0x41, 0x7f};

const uint8_t signal[] = {0x04, 0x02, 0x12, 0x09, 0x49, 0x09, 0x12, 0x02, 0x04};
const uint8_t nosignal[] = {0x05, 0x02, 0x12, 0x0D, 0x49,
                            0x19, 0x12, 0x22, 0x44};
const uint8_t ppm[] = {0x00, 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00};
const uint8_t noppm[] = {0x01, 0x02, 0x7F, 0x0D, 0x09, 0x19, 0x26, 0x40};
const uint8_t chan[] = {0xFF, 0x01, 0x01, 0x01, 0x01, 0xFF,
                        0x7F, 0x40, 0x40, 0x40, 0x40, 0x7F};
const uint8_t high[] = {0x2B, 0x3F, 0x3F, 0x2B, 0x40, 0x40, 0x40, 0x40};
const uint8_t mid[] = {0xA1, 0xE1, 0xE1, 0xA1, 0x42, 0x43, 0x43, 0x42};
const uint8_t low[] = {0x01, 0x01, 0x01, 0x01, 0x6A, 0x7E, 0x7E, 0x6A};