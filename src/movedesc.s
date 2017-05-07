.text
.thumb

.include "asm_defines.s"

.align 2
move_desc_table:
.byte 0xC1, 0x81, 0x61, 0x08
.byte 0xE7, 0x81, 0x61, 0x08
.byte 0x19, 0x82, 0x61, 0x08
.byte 0x40, 0x82, 0x61, 0x08
.byte 0x69, 0x82, 0x61, 0x08
.byte 0x96, 0x82, 0x61, 0x08
.byte 0xC9, 0x82, 0x61, 0x08
.byte 0xEE, 0x82, 0x61, 0x08
.byte 0x14, 0x83, 0x61, 0x08
.byte 0x44, 0x83, 0x61, 0x08
.byte 0x68, 0x83, 0x61, 0x08
.byte 0x97, 0x83, 0x61, 0x08
.byte 0xC9, 0x83, 0x61, 0x08
.byte 0xFD, 0x83, 0x61, 0x08
.byte 0x2A, 0x84, 0x61, 0x08
.byte 0x57, 0x84, 0x61, 0x08
.byte 0x90, 0x84, 0x61, 0x08
.byte 0xB8, 0x84, 0x61, 0x08
.byte 0xEA, 0x84, 0x61, 0x08
.byte 0x22, 0x85, 0x61, 0x08
.byte 0x4F, 0x85, 0x61, 0x08
.byte 0x7A, 0x85, 0x61, 0x08
.byte 0xA8, 0x85, 0x61, 0x08
.byte 0xDF, 0x85, 0x61, 0x08
.byte 0x13, 0x86, 0x61, 0x08
.byte 0x42, 0x86, 0x61, 0x08
.byte 0x77, 0x86, 0x61, 0x08
.byte 0xA0, 0x86, 0x61, 0x08
.byte 0xD8, 0x86, 0x61, 0x08
.byte 0x03, 0x87, 0x61, 0x08
.byte 0x22, 0x87, 0x61, 0x08
.byte 0x53, 0x87, 0x61, 0x08
.byte 0x86, 0x87, 0x61, 0x08
.byte 0xB0, 0x87, 0x61, 0x08
.byte 0xDB, 0x87, 0x61, 0x08
.byte 0x14, 0x88, 0x61, 0x08
.byte 0x47, 0x88, 0x61, 0x08
.byte 0x79, 0x88, 0x61, 0x08
.byte 0xA9, 0x88, 0x61, 0x08
.byte 0xD3, 0x88, 0x61, 0x08
.byte 0x05, 0x89, 0x61, 0x08
.byte 0x31, 0x89, 0x61, 0x08
.byte 0x5E, 0x89, 0x61, 0x08
.byte 0x8E, 0x89, 0x61, 0x08
.byte 0xBD, 0x89, 0x61, 0x08
.byte 0xE7, 0x89, 0x61, 0x08
.byte 0x0D, 0x8A, 0x61, 0x08
.byte 0x40, 0x8A, 0x61, 0x08
.byte 0x74, 0x8A, 0x61, 0x08
.byte 0xAB, 0x8A, 0x61, 0x08
.byte 0xD8, 0x8A, 0x61, 0x08
.byte 0x07, 0x8B, 0x61, 0x08
.byte 0x33, 0x8B, 0x61, 0x08
.byte 0x63, 0x8B, 0x61, 0x08
.byte 0x95, 0x8B, 0x61, 0x08
.byte 0xB6, 0x8B, 0x61, 0x08
.byte 0xE4, 0x8B, 0x61, 0x08
.byte 0x1A, 0x8C, 0x61, 0x08
.byte 0x4E, 0x8C, 0x61, 0x08
.byte 0x81, 0x8C, 0x61, 0x08
.byte 0xB0, 0x8C, 0x61, 0x08
.byte 0xE0, 0x8C, 0x61, 0x08
.byte 0x14, 0x8D, 0x61, 0x08
.byte 0x4A, 0x8D, 0x61, 0x08
.byte 0x74, 0x8D, 0x61, 0x08
.byte 0xAB, 0x8D, 0x61, 0x08
.byte 0xDA, 0x8D, 0x61, 0x08
.byte 0x0C, 0x8E, 0x61, 0x08
.byte 0x3F, 0x8E, 0x61, 0x08
.byte 0x6E, 0x8E, 0x61, 0x08
.byte 0x99, 0x8E, 0x61, 0x08
.byte 0xCB, 0x8E, 0x61, 0x08
.byte 0xFD, 0x8E, 0x61, 0x08
.byte 0x31, 0x8F, 0x61, 0x08
.byte 0x60, 0x8F, 0x61, 0x08
.byte 0x95, 0x8F, 0x61, 0x08
.byte 0xC8, 0x8F, 0x61, 0x08
.byte 0xF9, 0x8F, 0x61, 0x08
.byte 0x26, 0x90, 0x61, 0x08
.byte 0x59, 0x90, 0x61, 0x08
.byte 0x8B, 0x90, 0x61, 0x08
.byte 0xBA, 0x90, 0x61, 0x08
.byte 0xF1, 0x90, 0x61, 0x08
.byte 0x23, 0x91, 0x61, 0x08
.byte 0x53, 0x91, 0x61, 0x08
.byte 0x89, 0x91, 0x61, 0x08
.byte 0xBC, 0x91, 0x61, 0x08
.byte 0xE9, 0x91, 0x61, 0x08
.byte 0x0F, 0x92, 0x61, 0x08
.byte 0x43, 0x92, 0x61, 0x08
.byte 0x76, 0x92, 0x61, 0x08
.byte 0xAD, 0x92, 0x61, 0x08
.byte 0xD9, 0x92, 0x61, 0x08
.byte 0x04, 0x93, 0x61, 0x08
.byte 0x36, 0x93, 0x61, 0x08
.byte 0x60, 0x93, 0x61, 0x08
.byte 0x91, 0x93, 0x61, 0x08
.byte 0xBA, 0x93, 0x61, 0x08
.byte 0xEE, 0x93, 0x61, 0x08
.byte 0x1D, 0x94, 0x61, 0x08
.byte 0x4F, 0x94, 0x61, 0x08
.byte 0x7E, 0x94, 0x61, 0x08
.byte 0xAF, 0x94, 0x61, 0x08
.byte 0xE4, 0x94, 0x61, 0x08
.byte 0x12, 0x95, 0x61, 0x08
.byte 0x3D, 0x95, 0x61, 0x08
.byte 0x6C, 0x95, 0x61, 0x08
.byte 0x9C, 0x95, 0x61, 0x08
.byte 0xCD, 0x95, 0x61, 0x08
.byte 0xF3, 0x95, 0x61, 0x08
.byte 0x2C, 0x96, 0x61, 0x08
.byte 0x5E, 0x96, 0x61, 0x08
.byte 0x8D, 0x96, 0x61, 0x08
.byte 0xC1, 0x96, 0x61, 0x08
.byte 0xF8, 0x96, 0x61, 0x08
.byte 0x2F, 0x97, 0x61, 0x08
.byte 0x5E, 0x97, 0x61, 0x08
.byte 0x8E, 0x97, 0x61, 0x08
.byte 0xC2, 0x97, 0x61, 0x08
.byte 0xF0, 0x97, 0x61, 0x08
.byte 0x21, 0x98, 0x61, 0x08
.byte 0x47, 0x98, 0x61, 0x08
.byte 0x7E, 0x98, 0x61, 0x08
.byte 0xAA, 0x98, 0x61, 0x08
.byte 0xDF, 0x98, 0x61, 0x08
.byte 0x0F, 0x99, 0x61, 0x08
.byte 0x44, 0x99, 0x61, 0x08
.byte 0x74, 0x99, 0x61, 0x08
.byte 0xA1, 0x99, 0x61, 0x08
.byte 0xCA, 0x99, 0x61, 0x08
.byte 0xFC, 0x99, 0x61, 0x08
.byte 0x2C, 0x9A, 0x61, 0x08
.byte 0x59, 0x9A, 0x61, 0x08
.byte 0x8D, 0x9A, 0x61, 0x08
.byte 0xB4, 0x9A, 0x61, 0x08
.byte 0xDF, 0x9A, 0x61, 0x08
.byte 0x14, 0x9B, 0x61, 0x08
.byte 0x46, 0x9B, 0x61, 0x08
.byte 0x7D, 0x9B, 0x61, 0x08
.byte 0xAE, 0x9B, 0x61, 0x08
.byte 0xDB, 0x9B, 0x61, 0x08
.byte 0x0C, 0x9C, 0x61, 0x08
.byte 0x41, 0x9C, 0x61, 0x08
.byte 0x76, 0x9C, 0x61, 0x08
.byte 0xAB, 0x9C, 0x61, 0x08
.byte 0xDF, 0x9C, 0x61, 0x08
.byte 0x0A, 0x9D, 0x61, 0x08
.byte 0x3F, 0x9D, 0x61, 0x08
.byte 0x74, 0x9D, 0x61, 0x08
.byte 0xA6, 0x9D, 0x61, 0x08
.byte 0xD6, 0x9D, 0x61, 0x08
.byte 0x0A, 0x9E, 0x61, 0x08
.byte 0x40, 0x9E, 0x61, 0x08
.byte 0x71, 0x9E, 0x61, 0x08
.byte 0xA5, 0x9E, 0x61, 0x08
.byte 0xD1, 0x9E, 0x61, 0x08
.byte 0x07, 0x9F, 0x61, 0x08
.byte 0x37, 0x9F, 0x61, 0x08
.byte 0x66, 0x9F, 0x61, 0x08
.byte 0x93, 0x9F, 0x61, 0x08
.byte 0xC5, 0x9F, 0x61, 0x08
.byte 0xF2, 0x9F, 0x61, 0x08
.byte 0x27, 0xA0, 0x61, 0x08
.byte 0x5F, 0xA0, 0x61, 0x08
.byte 0x93, 0xA0, 0x61, 0x08
.byte 0xCF, 0xA0, 0x61, 0x08
.byte 0xF7, 0xA0, 0x61, 0x08
.byte 0x2D, 0xA1, 0x61, 0x08
.byte 0x60, 0xA1, 0x61, 0x08
.byte 0x97, 0xA1, 0x61, 0x08
.byte 0xCE, 0xA1, 0x61, 0x08
.byte 0x00, 0xA2, 0x61, 0x08
.byte 0x2F, 0xA2, 0x61, 0x08
.byte 0x61, 0xA2, 0x61, 0x08
.byte 0x8F, 0xA2, 0x61, 0x08
.byte 0xC0, 0xA2, 0x61, 0x08
.byte 0xF4, 0xA2, 0x61, 0x08
.byte 0x28, 0xA3, 0x61, 0x08
.byte 0x59, 0xA3, 0x61, 0x08
.byte 0x8A, 0xA3, 0x61, 0x08
.byte 0xB9, 0xA3, 0x61, 0x08
.byte 0xEF, 0xA3, 0x61, 0x08
.byte 0x22, 0xA4, 0x61, 0x08
.byte 0x55, 0xA4, 0x61, 0x08
.byte 0x8A, 0xA4, 0x61, 0x08
.byte 0xBA, 0xA4, 0x61, 0x08
.byte 0xF0, 0xA4, 0x61, 0x08
.byte 0x17, 0xA5, 0x61, 0x08
.byte 0x4C, 0xA5, 0x61, 0x08
.byte 0x80, 0xA5, 0x61, 0x08
.byte 0xB0, 0xA5, 0x61, 0x08
.byte 0xDB, 0xA5, 0x61, 0x08
.byte 0x11, 0xA6, 0x61, 0x08
.byte 0x44, 0xA6, 0x61, 0x08
.byte 0x77, 0xA6, 0x61, 0x08
.byte 0xA8, 0xA6, 0x61, 0x08
.byte 0xD7, 0xA6, 0x61, 0x08
.byte 0x0A, 0xA7, 0x61, 0x08
.byte 0x3C, 0xA7, 0x61, 0x08
.byte 0x6E, 0xA7, 0x61, 0x08
.byte 0xA0, 0xA7, 0x61, 0x08
.byte 0xD1, 0xA7, 0x61, 0x08
.byte 0x02, 0xA8, 0x61, 0x08
.byte 0x37, 0xA8, 0x61, 0x08
.byte 0x66, 0xA8, 0x61, 0x08
.byte 0x97, 0xA8, 0x61, 0x08
.byte 0xC9, 0xA8, 0x61, 0x08
.byte 0xFB, 0xA8, 0x61, 0x08
.byte 0x26, 0xA9, 0x61, 0x08
.byte 0x57, 0xA9, 0x61, 0x08
.byte 0x8A, 0xA9, 0x61, 0x08
.byte 0xB7, 0xA9, 0x61, 0x08
.byte 0xEC, 0xA9, 0x61, 0x08
.byte 0x1D, 0xAA, 0x61, 0x08
.byte 0x4B, 0xAA, 0x61, 0x08
.byte 0x7F, 0xAA, 0x61, 0x08
.byte 0xB2, 0xAA, 0x61, 0x08
.byte 0xE0, 0xAA, 0x61, 0x08
.byte 0x17, 0xAB, 0x61, 0x08
.byte 0x46, 0xAB, 0x61, 0x08
.byte 0x7C, 0xAB, 0x61, 0x08
.byte 0xAC, 0xAB, 0x61, 0x08
.byte 0xD9, 0xAB, 0x61, 0x08
.byte 0x0F, 0xAC, 0x61, 0x08
.byte 0x3F, 0xAC, 0x61, 0x08
.byte 0x73, 0xAC, 0x61, 0x08
.byte 0xA8, 0xAC, 0x61, 0x08
.byte 0xDE, 0xAC, 0x61, 0x08
.byte 0x12, 0xAD, 0x61, 0x08
.byte 0x42, 0xAD, 0x61, 0x08
.byte 0x69, 0xAD, 0x61, 0x08
.byte 0x9B, 0xAD, 0x61, 0x08
.byte 0xCB, 0xAD, 0x61, 0x08
.byte 0xFC, 0xAD, 0x61, 0x08
.byte 0x2D, 0xAE, 0x61, 0x08
.byte 0x5E, 0xAE, 0x61, 0x08
.byte 0x8F, 0xAE, 0x61, 0x08
.byte 0xB7, 0xAE, 0x61, 0x08
.byte 0xEA, 0xAE, 0x61, 0x08
.byte 0x19, 0xAF, 0x61, 0x08
.byte 0x4C, 0xAF, 0x61, 0x08
.byte 0x7E, 0xAF, 0x61, 0x08
.byte 0xAC, 0xAF, 0x61, 0x08
.byte 0xE3, 0xAF, 0x61, 0x08
.byte 0x15, 0xB0, 0x61, 0x08
.byte 0x3C, 0xB0, 0x61, 0x08
.byte 0x60, 0xB0, 0x61, 0x08
.byte 0x95, 0xB0, 0x61, 0x08
.byte 0xC4, 0xB0, 0x61, 0x08
.byte 0xF3, 0xB0, 0x61, 0x08
.byte 0x2C, 0xB1, 0x61, 0x08
.byte 0x59, 0xB1, 0x61, 0x08
.byte 0x8C, 0xB1, 0x61, 0x08
.byte 0xC2, 0xB1, 0x61, 0x08
.byte 0xE6, 0xB1, 0x61, 0x08
.byte 0x17, 0xB2, 0x61, 0x08
.byte 0x41, 0xB2, 0x61, 0x08
.byte 0x76, 0xB2, 0x61, 0x08
.byte 0xA3, 0xB2, 0x61, 0x08
.byte 0xD8, 0xB2, 0x61, 0x08
.byte 0x02, 0xB3, 0x61, 0x08
.byte 0x30, 0xB3, 0x61, 0x08
.byte 0x60, 0xB3, 0x61, 0x08
.byte 0x93, 0xB3, 0x61, 0x08
.byte 0xC8, 0xB3, 0x61, 0x08
.byte 0xFE, 0xB3, 0x61, 0x08
.byte 0x31, 0xB4, 0x61, 0x08
.byte 0x66, 0xB4, 0x61, 0x08
.byte 0x9A, 0xB4, 0x61, 0x08
.byte 0xC7, 0xB4, 0x61, 0x08
.byte 0xF2, 0xB4, 0x61, 0x08
.byte 0x1A, 0xB5, 0x61, 0x08
.byte 0x4C, 0xB5, 0x61, 0x08
.byte 0x7C, 0xB5, 0x61, 0x08
.byte 0xAE, 0xB5, 0x61, 0x08
.byte 0xE5, 0xB5, 0x61, 0x08
.byte 0x14, 0xB6, 0x61, 0x08
.byte 0x43, 0xB6, 0x61, 0x08
.byte 0x6A, 0xB6, 0x61, 0x08
.byte 0x9C, 0xB6, 0x61, 0x08
.byte 0xD1, 0xB6, 0x61, 0x08
.byte 0x06, 0xB7, 0x61, 0x08
.byte 0x3A, 0xB7, 0x61, 0x08
.byte 0x73, 0xB7, 0x61, 0x08
.byte 0xA5, 0xB7, 0x61, 0x08
.byte 0xD7, 0xB7, 0x61, 0x08
.byte 0x09, 0xB8, 0x61, 0x08
.byte 0x30, 0xB8, 0x61, 0x08
.byte 0x67, 0xB8, 0x61, 0x08
.byte 0x9C, 0xB8, 0x61, 0x08
.byte 0xCA, 0xB8, 0x61, 0x08
.byte 0x01, 0xB9, 0x61, 0x08
.byte 0x38, 0xB9, 0x61, 0x08
.byte 0x6D, 0xB9, 0x61, 0x08
.byte 0x9A, 0xB9, 0x61, 0x08
.byte 0xCC, 0xB9, 0x61, 0x08
.byte 0xFE, 0xB9, 0x61, 0x08
.byte 0x33, 0xBA, 0x61, 0x08
.byte 0x56, 0xBA, 0x61, 0x08
.byte 0x90, 0xBA, 0x61, 0x08
.byte 0xC7, 0xBA, 0x61, 0x08
.byte 0xFC, 0xBA, 0x61, 0x08
.byte 0x2B, 0xBB, 0x61, 0x08
.byte 0x58, 0xBB, 0x61, 0x08
.byte 0x87, 0xBB, 0x61, 0x08
.byte 0xB8, 0xBB, 0x61, 0x08
.byte 0xEE, 0xBB, 0x61, 0x08
.byte 0x24, 0xBC, 0x61, 0x08
.byte 0x5A, 0xBC, 0x61, 0x08
.byte 0x87, 0xBC, 0x61, 0x08
.byte 0xB8, 0xBC, 0x61, 0x08
.byte 0xEB, 0xBC, 0x61, 0x08
.byte 0x1C, 0xBD, 0x61, 0x08
.byte 0x4E, 0xBD, 0x61, 0x08
.byte 0x82, 0xBD, 0x61, 0x08
.byte 0xBA, 0xBD, 0x61, 0x08
.byte 0xED, 0xBD, 0x61, 0x08
.byte 0x22, 0xBE, 0x61, 0x08
.byte 0x4D, 0xBE, 0x61, 0x08
.byte 0x83, 0xBE, 0x61, 0x08
.byte 0xB4, 0xBE, 0x61, 0x08
.byte 0xE5, 0xBE, 0x61, 0x08
.byte 0x15, 0xBF, 0x61, 0x08
.byte 0x44, 0xBF, 0x61, 0x08
.byte 0x74, 0xBF, 0x61, 0x08
.byte 0xA6, 0xBF, 0x61, 0x08
.byte 0xDA, 0xBF, 0x61, 0x08
.byte 0x09, 0xC0, 0x61, 0x08
.byte 0x40, 0xC0, 0x61, 0x08
.byte 0x73, 0xC0, 0x61, 0x08
.byte 0xA1, 0xC0, 0x61, 0x08
.byte 0xD1, 0xC0, 0x61, 0x08
.byte 0xFD, 0xC0, 0x61, 0x08
.byte 0x30, 0xC1, 0x61, 0x08
.byte 0x65, 0xC1, 0x61, 0x08
.byte 0x8D, 0xC1, 0x61, 0x08
.byte 0xBA, 0xC1, 0x61, 0x08
.byte 0xDC, 0xC1, 0x61, 0x08
.byte 0x12, 0xC2, 0x61, 0x08
.byte 0x46, 0xC2, 0x61, 0x08
.byte 0x79, 0xC2, 0x61, 0x08
.byte 0xA1, 0xC2, 0x61, 0x08
.byte 0xD1, 0xC2, 0x61, 0x08
.byte 0x00, 0xC3, 0x61, 0x08
.byte 0x34, 0xC3, 0x61, 0x08
.byte 0x67, 0xC3, 0x61, 0x08
.byte 0x9C, 0xC3, 0x61, 0x08
.byte 0xCD, 0xC3, 0x61, 0x08
.byte 0x01, 0xC4, 0x61, 0x08
.byte 0x2D, 0xC4, 0x61, 0x08
.byte 0x5E, 0xC4, 0x61, 0x08
.byte 0x86, 0xC4, 0x61, 0x08
.byte 0xBA, 0xC4, 0x61, 0x08
.byte 0xEB, 0xC4, 0x61, 0x08
#ROOST
.byte 0x12, 0x95, 0x61, 0x08
.word GRAVITY_description
#MIRACLE EYE
.byte 0x11, 0xA6, 0x61, 0x08
.word WAKE_UP_SLAP_description
.word HAMMER_ARM_description
.word GYRO_BALL_description
.word HEALING_WISH_description
.word BRINE_description
.word NATURAL_GIFT_description
.word FEINT_description
.word PLUCK_description
.word TAILWIND_description
.word ACUPRESSURE_description
.word METAL_BURST_description
.word U_TURN_description
.word CLOSE_COMBAT_description
.word PAYBACK_description
.word ASSURANCE_description
.word EMBARGO_description
.word FLING_description
.word PSYCHO_SHIFT_description
.word TRUMP_CARD_description
.word HEAL_BLOCK_description
.word WRING_OUT_description
.word POWER_TRICK_description
.word GASTRO_ACID_description
.word LUCKY_CHANT_description
.word ME_FIRST_description
#COPYCAT
.byte 0xC2, 0x97, 0x61, 0x08
.word POWER_SWAP_description
.word GUARD_SWAP_description
.word PUNISHMENT_description
.word LAST_RESORT_description
.word WORRY_SEED_description
.word SUCKER_PUNCH_description
.word TOXIC_SPIKES_description
.word HEART_SWAP_description
.word AQUA_RING_description
.word MAGNET_RISE_description
.word FLARE_BLITZ_description
.word FORCE_PALM_description
.word AURA_SPHERE_description
.word ROCK_POLISH_description
.word POISON_JAB_description
.word DARK_PULSE_description
#NIGHT SLASH
.byte 0x27, 0xA0, 0x61, 0x08
.word AQUA_TAIL_description
.word SEED_BOMB_description
.word AIR_SLASH_description
.word X_SCISSOR_description
.word BUG_BUZZ_description
.word DRAGON_PULSE_description
.word DRAGON_RUSH_description
.word POWER_GEM_description
#DRAIN PUNCH
.byte 0xD1, 0xA7, 0x61, 0x08
.word VACUUM_WAVE_description
.word FOCUS_BLAST_description
.word ENERGY_BALL_description
.word BRAVE_BIRD_description
.word EARTH_POWER_description
.word SWITCHEROO_description
#GIGA IMPACT
.byte 0x14, 0x8D, 0x61, 0x08
.word NASTY_PLOT_description
#BULLET PUNCH
.byte 0x22, 0xA4, 0x61, 0x08
#AVALANCHE
.byte 0x6A, 0xB6, 0x61, 0x08
.word ICE_SHARD_description
#SHADOW CLAW
.byte 0x27, 0xA0, 0x61, 0x08
.word THUNDER_FANG_description
.word ICE_FANG_description
.word FIRE_FANG_description
.word SHADOW_SNEAK_description
.word MUD_BOMB_description
.word PSYCHO_CUT_description
#ZEN HEADBUTT
.byte 0xD8, 0x86, 0x61, 0x08
.word MIRROR_SHOT_description
.word FLASH_CANNON_description
.word ROCK_CLIMB_description
.word DEFOG_description
.word TRICK_ROOM_description
#DRACO METEOR
.byte 0x82, 0xBD, 0x61, 0x08
#DISCHARGE
.byte 0xBC, 0x91, 0x61, 0x08
#LAVA PLUME
.word LAVA_PLUME_description
#LEAF STORM
.byte 0x82, 0xBD, 0x61, 0x08
.word POWER_WHIP_description
#ROCK WRECKER
.byte 0xEE, 0xBB, 0x61, 0x08
#CROSS POISON
.byte 0xA1, 0xC2, 0x61, 0x08
.word GUNK_SHOT_description
.word IRON_HEAD_description
.word MAGNET_BOMB_description
.word STONE_EDGE_description
.word CAPTIVATE_description
.word STEALTH_ROCK_description
.word GRASS_KNOT_description
.word CHATTER_description
.word JUDGMENT_description
#BUG BITE
.word PLUCK_description
.word CHARGE_BEAM_description
#WOOD HAMMER
.byte 0xAB, 0x8D, 0x61, 0x08
#AQUA JET
.byte 0xBA, 0x93, 0x61, 0x08
.word ATTACK_ORDER_description
.word DEFEND_ORDER_description
#HEAL ORDER
.byte 0x12, 0x95, 0x61, 0x08
.word HEAD_SMASH_description
.word DOUBLE_HIT_description
#ROAR OF TIME
.byte 0x24, 0xBC, 0x61, 0x08
.word SPACIAL_REND_description
#LUNAR DANCE
.word HEALING_WISH_description
#CRUSH GRIP
.word WRING_OUT_description
#MAGMA STORM
.byte 0xF1, 0x90, 0x61, 0x08
.word DARK_VOID_description
.word SEED_FLARE_description
.word OMINOUS_WIND_description
.word SHADOW_FORCE_description
.word HONE_CLAWS_description
.word WIDE_GUARD_description
.word GUARD_SPLIT_description
.word POWER_SPLIT_description
.word WONDER_ROOM_description
.word PSYSHOCK_description
.word VENOSHOCK_description
.word AUTOTOMIZE_description
.word RAGE_POWDER_description
.word TELEKINESIS_description
.word MAGIC_ROOM_description
.word SMACK_DOWN_description
.word STORM_THROW_description
.word FLAME_BURST_description
.word SLUDGE_WAVE_description
.word QUIVER_DANCE_description
.word HEAVY_SLAM_description
.word SYNCHRONOISE_description
.word ELECTRO_BALL_description
.word SOAK_description
.word FLAME_CHARGE_description
.word COIL_description
.word LOW_SWEEP_description
.word ACID_SPRAY_description
.word FOUL_PLAY_description
.word SIMPLE_BEAM_description
.word ENTRAINMENT_description
.word AFTER_YOU_description
.word ROUND_description
.word ECHOED_VOICE_description
.word CHIP_AWAY_description
.word CLEAR_SMOG_description
.word STORED_POWER_description
.word QUICK_GUARD_description
.word ALLY_SWITCH_description
.word SCALD_description
.word SHELL_SMASH_description
.word HEAL_PULSE_description
.word HEX_description
.word SKY_DROP_description
.word SHIFT_GEAR_description
.word CIRCLE_THROW_description
.word INCINERATE_description
.word QUASH_description
.word ACROBATICS_description
.word REFLECT_TYPE_description
.word RETALIATE_description
.word FINAL_GAMBIT_description
.word BESTOW_description
.word INFERNO_description
.word WATER_PLEDGE_description
.word FIRE_PLEDGE_description
.word GRASS_PLEDGE_description
#VOLT SWITCH
.word U_TURN_description
.word STRUGGLE_BUG_description
.word BULLDOZE_description
#FROST BREATH
.word STORM_THROW_description
#DRAGON TAIL
.word CIRCLE_THROW_description
.word WORK_UP_description
.word ELECTROWEB_description
#WILD CHARGE
.byte 0x14, 0x88, 0x61, 0x08
.word DRILL_RUN_description
.word DUAL_CHOP_description
.word HEART_STAMP_description
#HORN LEECH
.byte 0xD1, 0xA7, 0x61, 0x08
#SACRED SWORD
.word CHIP_AWAY_description
.word RAZOR_SHELL_description
#HEAT CRASH
.word HEAVY_SLAM_description
.word LEAF_TORNADO_description
.word STEAMROLLER_description
.word COTTON_GUARD_description
.word NIGHT_DAZE_description
#PSYSTRIKE
.word PSYSHOCK_description
#TAIL SLAP
.byte 0x19, 0x82, 0x61, 0x08
.word HURRICANE_description
.word HEAD_CHARGE_description
.word GEAR_GRIND_description
#SEARING SHOT
.byte 0x0F, 0x99, 0x61, 0x08
.word TECHNO_BLAST_description
.word RELIC_SONG_description
.word SECRET_SWORD_description
#GLACIATE
.byte 0xA8, 0xA6, 0x61, 0x08
.word BOLT_STRIKE_description
.word BLUE_FLARE_description
.word FIERY_DANCE_description
.word FREEZE_SHOCK_description
.word ICE_BURN_description
.word SNARL_description
.word ICICLE_CRASH_description
.word V_CREATE_description
.word FUSION_FLARE_description
.word FUSION_BOLT_description
.word FLYING_PRESS_description
.word MAT_BLOCK_description
.word BELCH_description
.word ROTOTILLER_description
.word STICKY_WEB_description
.word FELL_STINGER_description
#PHANTOM FORCE
.word SHADOW_FORCE_description
.word TRICK_OR_TREAT_description
.word NOBLE_ROAR_description
.word ION_DELUGE_description
#PARABOLIC CHARGE
.byte 0xCB, 0x8E, 0x61, 0x08
.word FORESTS_CURSE_description
.word PETAL_BLIZZARD_description
.word FREEZE_DRY_description
.word DISARMING_VOICE_description
.word PARTING_SHOT_description
.word TOPSY_TURVY_description
.word DRAINING_KISS_description
.word CRAFTY_SHIELD_description
.word FLOWER_SHIELD_description
.word GRASSY_TERRAIN_description
.word MISTY_TERRAIN_description
.word ELECTRIFY_description
.word PLAY_ROUGH_description
.word FAIRY_WIND_description
.word MOONBLAST_description
.word BOOMBURST_description
.word FAIRY_LOCK_description
.word KINGS_SHIELD_description
.word PLAY_NICE_description
.word CONFIDE_description
.word DIAMOND_STORM_description
.word STEAM_ERUPTION_description
.word HYPERSPACE_HOLE_description
.word WATER_SHURIKEN_description
.word MYSTICAL_FIRE_description
.word SPIKY_SHIELD_description
.word AROMATIC_MIST_description
.word EERIE_IMPULSE_description
.word VENOM_DRENCH_description
.word POWDER_description
.word GEOMANCY_description
.word MAGNETIC_FLUX_description
.word HAPPY_HOUR_description
.word ELECTRIC_TERRAIN_description
.word DAZZLING_GLEAM_description
.word CELEBRATE_description
.word HOLD_HANDS_description
.word BABYDOLL_EYES_description
.word NUZZLE_description
#HOLD BACK
.byte 0x97, 0xA8, 0x61, 0x08
.word INFESTATION_description
.word POWER_UP_PUNCH_description
#OBLIVION WING
.word DRAINING_KISS_description
.word THOUSAND_ARROWS_description
.word THOUSAND_WAVES_description
#LANDS_WRATH_description
.byte 0x0F, 0x92, 0x61, 0x08
.word LIGHT_OF_RUIN_description
.word ORIGIN_PULSE_description
.word PRECIPICE_BLADES_description
#DRAGON ASCENT
.word CLOSE_COMBAT_description
#HYPERSPACE FURY
.word HYPERSPACE_HOLE_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description



GRAVITY_description:
.byte G_, r_, a_, v_, i_, t_, y_, Space, i_, s_, Space, i_, n_, t_, e_, n_, s_, i_, f_, i_, e_, d_, Comma, JumpLine
.byte n_, e_, g_, a_, t_, i_, n_, g_, Space, l_, e_, v_, i_, t_, a_, t_, i_, o_, n_, Dot, Termin


WAKE_UP_SLAP_description:
.byte P_, o_, w_, e_, r_, f_, u_, l_, Space, a_, g_, a_, i_, n_, s_, t_, Space, s_, l_, e_, e_, p_, i_, n_, g_, JumpLine
.byte f_, o_, e_, s_, Comma, Space, b_, u_, t_, Space, a_, l_, s_, o_, Space, h_, e_, a_, l_, s_, Space, t_, h_, e_, m_, Dot, Termin


HAMMER_ARM_description:
.byte A_, Space, s_, w_, i_, n_, g_, i_, n_, g_, Space, f_, i_, s_, t_, Space, a_, t_, t_, a_, c_, k_, JumpLine
.byte t_, h_, a_, t_, Space, a_, l_, s_, o_, Space, l_, o_, w_, e_, r_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


GYRO_BALL_description:
.byte A_, Space, h_, i_, g_, h_, Dash, s_, p_, e_, e_, d_, Space, s_, p_, i_, n_, Space, t_, h_, a_, t_, Space, d_, o_, e_, s_, JumpLine
.byte m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, t_, o_, Space, f_, a_, s_, t_, e_, r_, Space, f_, o_, e_, s_, Dot, Termin


HEALING_WISH_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, f_, a_, i_, n_, t_, s_, Space, t_, o_, Space, h_, e_, a_, l_, Space, u_, p_, JumpLine
.byte t_, h_, e_, Space, r_, e_, c_, i_, p_, i_, e_, n_, t_, Dot, Termin


BRINE_description:
.byte D_, o_, e_, s_, Space, d_, o_, u_, b_, l_, e_, Space, d_, a_, m_, a_, g_, e_, Space, t_, o_, Space, f_, o_, e_, s_, JumpLine
.byte w_, i_, t_, h_, Space, h_, a_, l_, f_, Space, H_, P_, Dot, Termin


NATURAL_GIFT_description:
.byte T_, h_, e_, Space, e_, f_, f_, e_, c_, t_, i_, v_, e_, n_, e_, s_, s_, Space, v_, a_, r_, i_, e_, s_, JumpLine
.byte w_, i_, t_, h_, Space, t_, h_, e_, Space, h_, e_, l_, d_, Space, B_, e_, r_, r_, y_, Dot, Termin


FEINT_description:
.byte A_, n_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, h_, i_, t_, s_, Space, f_, o_, e_, s_, JumpLine
.byte u_, s_, i_, n_, g_, Space, m_, o_, v_, e_, s_, Space, l_, i_, k_, e_, Space, P_, r_, o_, t_, e_, c_, t_, Dot, Termin


PLUCK_description:
.byte E_, a_, t_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, h_, e_, l_, d_, Space, B_, e_, r_, r_, y_, Comma, JumpLine
.byte g_, a_, i_, n_, i_, n_, g_, Space, i_, t_, s_, Space, e_, f_, f_, e_, c_, t_, Dot, Termin


TAILWIND_description:
.byte W_, h_, i_, p_, s_, Space, u_, p_, Space, a_, Space, t_, u_, r_, b_, u_, l_, e_, n_, t_, Space, b_, r_, e_, e_, z_, e_, JumpLine
.byte t_, h_, a_, t_, Space, r_, a_, i_, s_, e_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


ACUPRESSURE_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, s_, h_, a_, r_, p_, l_, y_, Space, r_, a_, i_, s_, e_, s_, JumpLine
.byte o_, n_, e_, Space, o_, f_, Space, i_, t_, s_, Space, s_, t_, a_, t_, s_, Dot, Termin


METAL_BURST_description:
.byte R_, e_, t_, a_, l_, i_, a_, t_, e_, s_, Space, a_, n_, y_, Space, h_, i_, t_, Space, w_, i_, t_, h_, JumpLine
.byte g_, r_, e_, a_, t_, e_, r_, Space, p_, o_, w_, e_, r_, Dot, Termin


U_TURN_description:
.byte D_, o_, e_, s_, Space, d_, a_, m_, a_, g_, e_, Space, t_, h_, e_, n_, Space, s_, w_, i_, t_, c_, h_, e_, s_, JumpLine
.byte o_, u_, t_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


CLOSE_COMBAT_description:
.byte A_, Space, s_, t_, r_, o_, n_, g_, Space, a_, t_, t_, a_, c_, k_, Space, b_, u_, t_, Space, l_, o_, w_, e_, r_, s_, JumpLine
.byte t_, h_, e_, Space, d_, e_, f_, e_, n_, s_, i_, v_, e_, Space, s_, t_, a_, t_, s_, Dot, Termin


PAYBACK_description:
.byte A_, n_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, g_, a_, i_, n_, s_, Space, p_, o_, w_, e_, r_, JumpLine
.byte i_, f_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Space, m_, o_, v_, e_, s_, Space, l_, a_, s_, t_, Dot, Termin


ASSURANCE_description:
.byte A_, n_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, g_, a_, i_, n_, s_, Space, p_, o_, w_, e_, r_, JumpLine
.byte i_, f_, Space, t_, h_, e_, Space, f_, o_, e_, Space, h_, a_, s_, Space, b_, e_, e_, n_, Space, h_, u_, r_, t_, Dot, Termin


EMBARGO_description:
.byte P_, r_, e_, v_, e_, n_, t_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, f_, r_, o_, m_, JumpLine
.byte u_, s_, i_, n_, g_, Space, a_, n_, y_, Space, i_, t_, e_, m_, s_, Dot, Termin


FLING_description:
.byte T_, h_, e_, Space, e_, f_, f_, e_, c_, t_, i_, v_, e_, n_, e_, s_, s_, Space, v_, a_, r_, i_, e_, s_, JumpLine
.byte w_, i_, t_, h_, Space, t_, h_, e_, Space, h_, e_, l_, d_, Space, i_, t_, e_, m_, Dot, Termin


PSYCHO_SHIFT_description:
.byte T_, r_, a_, n_, s_, f_, e_, r_, s_, Space, s_, t_, a_, t_, u_, s_, Space, p_, r_, o_, b_, l_, e_, m_, s_, JumpLine
.byte t_, o_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


TRUMP_CARD_description:
.byte T_, h_, e_, Space, l_, e_, s_, s_, Space, P_, P_, Space, t_, h_, e_, Space, m_, o_, v_, e_, Space, h_, a_, s_, Comma, JumpLine
.byte t_, h_, e_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, t_, Space, d_, o_, e_, s_, Dot, Termin


HEAL_BLOCK_description:
.byte P_, r_, e_, v_, e_, n_, t_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, f_, r_, o_, m_, JumpLine
.byte r_, e_, c_, o_, v_, e_, r_, i_, n_, g_, Space, a_, n_, y_, Space, H_, P_, Dot, Termin


WRING_OUT_description:
.byte T_, h_, e_, Space, h_, i_, g_, h_, e_, r_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, H_, P_, Comma, JumpLine
.byte t_, h_, e_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, c_, a_, u_, s_, e_, d_, Dot, Termin


POWER_TRICK_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, s_, w_, a_, p_, s_, Space, i_, t_, s_, Space, A_, t_, t_, a_, c_, k_, JumpLine
.byte a_, n_, d_, Space, D_, e_, f_, e_, n_, s_, e_, Space, s_, t_, a_, t_, s_, Dot, Termin


GASTRO_ACID_description:
.byte S_, t_, o_, m_, a_, c_, h_, Space, a_, c_, i_, d_, Space, s_, u_, p_, p_, r_, e_, s_, s_, e_, s_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, a_, b_, i_, l_, i_, t_, y_, Dot, Termin


LUCKY_CHANT_description:
.byte P_, r_, e_, v_, e_, n_, t_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, f_, r_, o_, m_, JumpLine
.byte l_, a_, n_, d_, i_, n_, g_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Space, h_, i_, t_, s_, Dot, Termin


ME_FIRST_description:
.byte E_, x_, e_, c_, u_, t_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, a_, t_, t_, a_, c_, k_, JumpLine
.byte w_, i_, t_, h_, Space, g_, r_, e_, a_, t_, e_, r_, Space, p_, o_, w_, e_, r_, Dot, Termin


POWER_SWAP_description:
.byte S_, w_, a_, p_, s_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, o_, Space, A_, t_, t_, a_, c_, k_, JumpLine
.byte a_, n_, d_, Space, S_, p_, Dot, Space, A_, t_, k_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


GUARD_SWAP_description:
.byte S_, w_, a_, p_, s_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, o_, Space, D_, e_, f_, e_, n_, s_, e_, JumpLine
.byte a_, n_, d_, Space, S_, p_, Dot, Space, D_, e_, f_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


PUNISHMENT_description:
.byte D_, o_, e_, s_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Space, h_, a_, s_, Space, p_, o_, w_, e_, r_, e_, d_, Space, u_, p_, Dot, Termin


LAST_RESORT_description:
.byte C_, a_, n_, Space, o_, n_, l_, y_, Space, b_, e_, Space, u_, s_, e_, d_, Space, i_, f_, Space, e_, v_, e_, r_, y_, JumpLine
.byte o_, t_, h_, e_, r_, Space, m_, o_, v_, e_, Space, h_, a_, s_, Space, b_, e_, e_, n_, Space, u_, s_, e_, d_, Dot, Termin


WORRY_SEED_description:
.byte P_, l_, a_, n_, t_, s_, Space, a_, Space, s_, e_, e_, d_, Space, o_, n_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, JumpLine
.byte g_, i_, v_, i_, n_, g_, Space, i_, t_, Space, I_, n_, s_, o_, m_, n_, i_, a_, Dot, Termin


SUCKER_PUNCH_description:
.byte S_, t_, r_, i_, k_, e_, s_, Space, f_, i_, r_, s_, t_, Space, i_, f_, Space, t_, h_, e_, Space, f_, o_, e_, JumpLine
.byte i_, s_, Space, p_, r_, e_, p_, a_, r_, i_, n_, g_, Space, a_, n_, Space, a_, t_, t_, a_, c_, k_, Dot, Termin


TOXIC_SPIKES_description:
.byte S_, e_, t_, s_, Space, s_, p_, i_, k_, e_, s_, Space, t_, h_, a_, t_, Space, p_, o_, i_, s_, o_, n_, Space, a_, JumpLine
.byte f_, o_, e_, Space, s_, w_, i_, t_, c_, h_, i_, n_, g_, Space, i_, n_, Dot, Termin


HEART_SWAP_description:
.byte S_, w_, a_, p_, s_, Space, a_, n_, y_, Space, s_, t_, a_, t_, Space, c_, h_, a_, n_, g_, e_, s_, JumpLine
.byte w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


AQUA_RING_description:
.byte F_, o_, r_, m_, s_, Space, a_, Space, v_, e_, i_, l_, Space, o_, f_, Space, w_, a_, t_, e_, r_, JumpLine
.byte t_, h_, a_, t_, Space, r_, e_, s_, t_, o_, r_, e_, s_, Space, H_, P_, Dot, Termin


MAGNET_RISE_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, l_, e_, v_, i_, t_, a_, t_, e_, s_, Space, w_, i_, t_, h_, JumpLine
.byte e_, l_, e_, c_, t_, r_, o_, m_, a_, g_, n_, e_, t_, i_, s_, m_, Dot, Termin


FLARE_BLITZ_description:
.byte A_, Space, c_, h_, a_, r_, g_, e_, Space, t_, h_, a_, t_, Space, m_, a_, y_, Space, b_, u_, r_, n_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Dot, Space, A_, l_, s_, o_, Space, h_, u_, r_, t_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


FORCE_PALM_description:
.byte A_, Space, s_, h_, o_, c_, k_, Space, w_, a_, v_, e_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, JumpLine
.byte m_, a_, y_, Space, p_, a_, r_, a_, l_, y_, z_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


AURA_SPHERE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, n_, Space, a_, u_, r_, a_, Space, b_, l_, a_, s_, t_, JumpLine
.byte t_, h_, a_, t_, Space, c_, a_, n_, n_, o_, t_, Space, b_, e_, Space, e_, v_, a_, d_, e_, d_, Dot, Termin


ROCK_POLISH_description:
.byte P_, o_, l_, i_, s_, h_, e_, s_, Space, t_, h_, e_, Space, b_, o_, d_, y_, Space, t_, o_, JumpLine
.byte s_, h_, a_, r_, p_, l_, y_, Space, r_, a_, i_, s_, e_, Space, S_, p_, e_, e_, d_, Dot, Termin


POISON_JAB_description:
.byte A_, Space, s_, t_, a_, b_, b_, i_, n_, g_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, JumpLine
.byte m_, a_, y_, Space, p_, o_, i_, s_, o_, n_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


DARK_PULSE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, h_, o_, r_, r_, i_, b_, l_, e_, JumpLine
.byte a_, u_, r_, a_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


AQUA_TAIL_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, s_, w_, i_, n_, g_, s_, Space, i_, t_, s_, Space, t_, a_, i_, l_, JumpLine
.byte l_, i_, k_, e_, Space, a_, Space, w_, a_, v_, e_, Space, t_, o_, Space, a_, t_, t_, a_, c_, k_, Dot, Termin


SEED_BOMB_description:
.byte A_, Space, b_, a_, r_, r_, a_, g_, e_, Space, o_, f_, Space, h_, a_, r_, d_, Space, s_, e_, e_, d_, s_, JumpLine
.byte i_, s_, Space, f_, i_, r_, e_, d_, Space, a_, t_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


AIR_SLASH_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, b_, l_, a_, d_, e_, Space, o_, f_, JumpLine
.byte a_, i_, r_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


X_SCISSOR_description:
.byte S_, l_, a_, s_, h_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, c_, r_, o_, s_, s_, e_, d_, JumpLine
.byte s_, c_, y_, t_, h_, e_, s_, Comma, Space, c_, l_, a_, w_, s_, Comma, Space, e_, t_, c_, Dot, Termin


BUG_BUZZ_description:
.byte A_, Space, d_, a_, m_, a_, g_, i_, n_, g_, Space, s_, o_, u_, n_, d_, Space, w_, a_, v_, e_, Space, t_, h_, a_, t_, JumpLine
.byte m_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


DRAGON_PULSE_description:
.byte G_, e_, n_, e_, r_, a_, t_, e_, s_, Space, a_, Space, s_, h_, o_, c_, k_, Space, w_, a_, v_, e_, Space, t_, o_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


DRAGON_RUSH_description:
.byte T_, a_, c_, k_, l_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, m_, e_, n_, a_, c_, e_, Dot, JumpLine
.byte M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


POWER_GEM_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, r_, a_, y_, s_, Space, o_, f_, Space, l_, i_, g_, h_, t_, JumpLine
.byte t_, h_, a_, t_, Space, s_, p_, a_, r_, k_, l_, e_, Space, l_, i_, k_, e_, Space, d_, i_, a_, m_, o_, n_, d_, s_, Dot, Termin


VACUUM_WAVE_description:
.byte W_, h_, i_, r_, l_, s_, Space, i_, t_, s_, Space, f_, i_, s_, t_, s_, Space, t_, o_, Space, s_, e_, n_, d_, JumpLine
.byte a_, Space, w_, a_, v_, e_, Space, t_, h_, a_, t_, Space, s_, t_, r_, i_, k_, e_, s_, Space, f_, i_, r_, s_, t_, Dot, Termin


FOCUS_BLAST_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, a_, t_, Space, f_, u_, l_, l_, Space, p_, o_, w_, e_, r_, Dot, JumpLine
.byte M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


ENERGY_BALL_description:
.byte D_, r_, a_, w_, s_, Space, p_, o_, w_, e_, r_, Space, f_, r_, o_, m_, Space, n_, a_, t_, u_, r_, e_, Space, t_, o_, JumpLine
.byte a_, t_, t_, a_, c_, k_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


BRAVE_BIRD_description:
.byte A_, Space, l_, o_, w_, Space, a_, l_, t_, i_, t_, u_, d_, e_, Space, c_, h_, a_, r_, g_, e_, Space, t_, h_, a_, t_, JumpLine
.byte a_, l_, s_, o_, Space, h_, u_, r_, t_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


EARTH_POWER_description:
.byte M_, a_, k_, e_, s_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Space, e_, r_, u_, p_, t_, Space, w_, i_, t_, h_, JumpLine
.byte p_, o_, w_, e_, r_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


SWITCHEROO_description:
.byte S_, w_, a_, p_, s_, Space, i_, t_, e_, m_, s_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, JumpLine
.byte f_, a_, s_, t_, e_, r_, Space, t_, h_, a_, n_, Space, t_, h_, e_, Space, e_, y_, e_, Space, c_, a_, n_, Space, s_, e_, e_, Dot, Termin


NASTY_PLOT_description:
.byte T_, h_, i_, n_, k_, s_, Space, b_, a_, d_, Space, t_, h_, o_, u_, g_, h_, t_, s_, Space, t_, o_, JumpLine
.byte s_, h_, a_, r_, p_, l_, y_, Space, b_, o_, o_, s_, t_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


ICE_SHARD_description:
.byte H_, u_, r_, l_, s_, Space, a_, Space, c_, h_, u_, n_, k_, Space, o_, f_, Space, i_, c_, e_, Space, t_, h_, a_, t_, JumpLine
.byte a_, l_, w_, a_, y_, s_, Space, s_, t_, r_, i_, k_, e_, Space, f_, i_, r_, s_, t_, Dot, Termin


THUNDER_FANG_description:
.byte M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Space, o_, r_, JumpLine
.byte l_, e_, a_, v_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Space, p_, a_, r_, a_, l_, y_, z_, e_, d_, Dot, Termin


ICE_FANG_description:
.byte M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Space, o_, r_, JumpLine
.byte l_, e_, a_, v_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Space, f_, r_, o_, z_, e_, n_, Dot, Termin


FIRE_FANG_description:
.byte M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Space, o_, r_, JumpLine
.byte l_, e_, a_, v_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, a_, Space, b_, u_, r_, n_, Dot, Termin


SHADOW_SNEAK_description:
.byte E_, x_, t_, e_, n_, d_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Apos, s_, Space, s_, h_, a_, d_, o_, w_, JumpLine
.byte t_, o_, Space, s_, t_, r_, i_, k_, e_, Space, f_, i_, r_, s_, t_, Dot, Termin


MUD_BOMB_description:
.byte T_, h_, r_, o_, w_, s_, Space, a_, Space, b_, l_, o_, b_, Space, o_, f_, Space, m_, u_, d_, Space, t_, o_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, a_, n_, d_, Space, c_, u_, t_, Space, a_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


PSYCHO_CUT_description:
.byte T_, e_, a_, r_, s_, Space, w_, i_, t_, h_, Space, p_, s_, y_, c_, h_, i_, c_, Space, b_, l_, a_, d_, e_, s_, Dot, JumpLine
.byte H_, i_, g_, h_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Dash, h_, i_, t_, Space, r_, a_, t_, i_, o_, Dot, Termin


MIRROR_SHOT_description:
.byte E_, m_, i_, t_, s_, Space, a_, Space, f_, l_, a_, s_, h_, Space, o_, f_, Space, e_, n_, e_, r_, g_, y_, Space, t_, o_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, a_, n_, d_, Space, c_, u_, t_, Space, a_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


FLASH_CANNON_description:
.byte R_, e_, l_, e_, a_, s_, e_, s_, Space, a_, Space, b_, l_, a_, s_, t_, Space, o_, f_, Space, l_, i_, g_, h_, t_, JumpLine
.byte t_, h_, a_, t_, Space, m_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


ROCK_CLIMB_description:
.byte A_, Space, c_, h_, a_, r_, g_, i_, n_, g_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, m_, a_, y_, JumpLine
.byte c_, o_, n_, f_, u_, s_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


DEFOG_description:
.byte R_, e_, m_, o_, v_, e_, s_, Space, o_, b_, s_, t_, a_, c_, l_, e_, s_, Space, a_, n_, d_, JumpLine
.byte l_, o_, w_, e_, r_, s_, Space, e_, v_, a_, s_, i_, o_, n_, Dot, Termin


TRICK_ROOM_description:
.byte S_, l_, o_, w_, e_, r_, Space, P_, o_, k_, Poke_e, m_, o_, n_, Space, g_, e_, t_, Space, t_, o_, Space, m_, o_, v_, e_, JumpLine
.byte f_, i_, r_, s_, t_, Space, f_, o_, r_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Termin


POWER_WHIP_description:
.byte V_, i_, o_, l_, e_, n_, t_, l_, y_, Space, l_, a_, s_, h_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, JumpLine
.byte w_, i_, t_, h_, Space, v_, i_, n_, e_, s_, Space, o_, r_, Space, t_, e_, n_, t_, a_, c_, l_, e_, s_, Dot, Termin


GUNK_SHOT_description:
.byte S_, h_, o_, o_, t_, s_, Space, f_, i_, l_, t_, h_, y_, Space, g_, a_, r_, b_, a_, g_, e_, Space, a_, t_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Dot, Space, M_, a_, y_, Space, a_, l_, s_, o_, Space, p_, o_, i_, s_, o_, n_, Dot, Termin


IRON_HEAD_description:
.byte S_, l_, a_, m_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, a_, Space, h_, a_, r_, d_, JumpLine
.byte h_, e_, a_, d_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


MAGNET_BOMB_description:
.byte L_, a_, u_, n_, c_, h_, e_, s_, Space, a_, Space, m_, a_, g_, n_, e_, t_, Space, t_, h_, a_, t_, JumpLine
.byte s_, t_, r_, i_, k_, e_, s_, Space, w_, i_, t_, h_, o_, u_, t_, Space, f_, a_, i_, l_, Dot, Termin


STONE_EDGE_description:
.byte S_, t_, a_, b_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, s_, t_, o_, n_, e_, s_, Dot, JumpLine
.byte H_, i_, g_, h_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Dash, h_, i_, t_, Space, r_, a_, t_, i_, o_, Dot, Termin


CAPTIVATE_description:
.byte M_, a_, k_, e_, s_, Space, t_, h_, e_, Space, o_, p_, p_, o_, s_, i_, t_, e_, Space, g_, e_, n_, d_, e_, r_, JumpLine
.byte s_, h_, a_, r_, p_, l_, y_, Space, r_, e_, d_, u_, c_, e_, Space, i_, t_, s_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


STEALTH_ROCK_description:
.byte S_, e_, t_, s_, Space, f_, l_, o_, a_, t_, i_, n_, g_, Space, s_, t_, o_, n_, e_, s_, Space, t_, h_, a_, t_, JumpLine
.byte h_, u_, r_, t_, Space, a_, Space, f_, o_, e_, Space, s_, w_, i_, t_, c_, h_, i_, n_, g_, Space, i_, n_, Dot, Termin


GRASS_KNOT_description:
.byte A_, Space, s_, n_, a_, r_, e_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, d_, o_, e_, s_, JumpLine
.byte m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, t_, o_, Space, h_, e_, a_, v_, i_, e_, r_, Space, f_, o_, e_, s_, Dot, Termin


CHATTER_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, s_, o_, u_, n_, d_, Space, w_, a_, v_, e_, JumpLine
.byte t_, h_, a_, t_, Space, c_, a_, u_, s_, e_, s_, Space, c_, o_, n_, f_, u_, s_, i_, o_, n_, Dot, Termin


JUDGMENT_description:
.byte T_, h_, e_, Space, t_, y_, p_, e_, Space, v_, a_, r_, i_, e_, s_, Space, w_, i_, t_, h_, Space, t_, h_, e_, JumpLine
.byte k_, i_, n_, d_, Space, o_, f_, Space, P_, l_, a_, t_, e_, Space, h_, e_, l_, d_, Dot, Termin


CHARGE_BEAM_description:
.byte F_, i_, r_, e_, s_, Space, a_, Space, b_, e_, a_, m_, Space, o_, f_, Space, e_, l_, e_, c_, t_, r_, i_, c_, i_, t_, y_, Dot, JumpLine
.byte M_, a_, y_, Space, r_, a_, i_, s_, e_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


ATTACK_ORDER_description:
.byte U_, n_, d_, e_, r_, l_, i_, n_, g_, s_, Space, p_, u_, m_, m_, e_, l_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, JumpLine
.byte H_, i_, g_, h_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Dash, h_, i_, t_, Space, r_, a_, t_, i_, o_, Dot, Termin


DEFEND_ORDER_description:
.byte R_, a_, i_, s_, e_, s_, Space, D_, e_, f_, e_, n_, s_, e_, Space, a_, n_, d_, Space, S_, p_, Dot, Space, D_, e_, f_, JumpLine
.byte w_, i_, t_, h_, Space, a_, Space, l_, i_, v_, i_, n_, g_, Space, s_, h_, i_, e_, l_, d_, Dot, Termin


HEAD_SMASH_description:
.byte A_, Space, l_, i_, f_, e_, Dash, r_, i_, s_, k_, i_, n_, g_, Space, h_, e_, a_, d_, b_, u_, t_, t_, Space, t_, h_, a_, t_, JumpLine
.byte s_, e_, r_, i_, o_, u_, s_, l_, y_, Space, h_, u_, r_, t_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


DOUBLE_HIT_description:
.byte S_, l_, a_, m_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, a_, Space, t_, a_, i_, l_, Comma, JumpLine
.byte e_, t_, c_, Dot, Space, S_, t_, r_, i_, k_, e_, s_, Space, t_, w_, i_, c_, e_, Dot, Termin


SPACIAL_REND_description:
.byte T_, e_, a_, r_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, a_, n_, d_, Space, s_, p_, a_, c_, e_, Dot, JumpLine
.byte H_, i_, g_, h_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Dash, h_, i_, t_, Space, r_, a_, t_, i_, o_, Dot, Termin


DARK_VOID_description:
.byte D_, r_, a_, g_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, n_, t_, o_, Space, t_, o_, t_, a_, l_, JumpLine
.byte d_, a_, r_, k_, n_, e_, s_, s_, Comma, Space, i_, n_, d_, u_, c_, i_, n_, g_, Space, S_, l_, e_, e_, p_, Dot, Termin


SEED_FLARE_description:
.byte G_, e_, n_, e_, r_, a_, t_, e_, s_, Space, a_, Space, s_, h_, o_, c_, k_, Space, w_, a_, v_, e_, Space, t_, h_, a_, t_, JumpLine
.byte s_, h_, a_, r_, p_, l_, y_, Space, r_, e_, d_, u_, c_, e_, s_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


OMINOUS_WIND_description:
.byte A_, Space, r_, e_, p_, u_, l_, s_, i_, v_, e_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, m_, a_, y_, JumpLine
.byte r_, a_, i_, s_, e_, Space, a_, l_, l_, Space, s_, t_, a_, t_, s_, Dot, Termin


SHADOW_FORCE_description:
.byte V_, a_, n_, i_, s_, h_, e_, s_, Space, o_, n_, Space, t_, h_, e_, Space, f_, i_, r_, s_, t_, Space, t_, u_, r_, n_, Comma, JumpLine
.byte t_, h_, e_, n_, Space, s_, t_, r_, i_, k_, e_, s_, Space, t_, h_, e_, Space, n_, e_, x_, t_, Space, t_, u_, r_, n_, Dot, Termin


HONE_CLAWS_description:
.byte S_, h_, a_, r_, p_, e_, n_, s_, Space, i_, t_, s_, Space, c_, l_, a_, w_, s_, Space, t_, o_, Space, r_, a_, i_, s_, e_, JumpLine
.byte A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, Space, A_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


WIDE_GUARD_description:
.byte E_, v_, a_, d_, e_, s_, Space, w_, i_, d_, e_, Dash, r_, a_, n_, g_, i_, n_, g_, Space, a_, t_, t_, a_, c_, k_, s_, JumpLine
.byte f_, o_, r_, Space, o_, n_, e_, Space, t_, u_, r_, n_, Dot, Termin


GUARD_SPLIT_description:
.byte A_, v_, e_, r_, a_, g_, e_, s_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, o_, Space, D_, e_, f_, e_, n_, s_, e_, JumpLine
.byte a_, n_, d_, Space, S_, p_, Dot, Space, D_, e_, f_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


POWER_SPLIT_description:
.byte A_, v_, e_, r_, a_, g_, e_, s_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, o_, Space, A_, t_, t_, a_, c_, k_, JumpLine
.byte a_, n_, d_, Space, S_, p_, Dot, Space, A_, t_, k_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


WONDER_ROOM_description:
.byte D_, e_, f_, e_, n_, s_, e_, Space, a_, n_, d_, Space, S_, p_, Dot, Space, D_, e_, f_, Space, s_, t_, a_, t_, s_, JumpLine
.byte a_, r_, e_, Space, s_, w_, a_, p_, p_, e_, d_, Space, f_, o_, r_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Termin


PSYSHOCK_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, p_, s_, y_, c_, h_, i_, c_, Space, w_, a_, v_, e_, JumpLine
.byte t_, h_, a_, t_, Space, d_, o_, e_, s_, Space, p_, h_, y_, s_, i_, c_, a_, l_, Space, d_, a_, m_, a_, g_, e_, Dot, Termin


VENOSHOCK_description:
.byte D_, o_, e_, s_, Space, d_, o_, u_, b_, l_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Space, i_, s_, Space, p_, o_, i_, s_, o_, n_, e_, d_, Dot, Termin


AUTOTOMIZE_description:
.byte S_, h_, e_, d_, s_, Space, a_, d_, d_, i_, t_, i_, o_, n_, a_, l_, Space, w_, e_, i_, g_, h_, t_, Space, t_, o_, JumpLine
.byte s_, h_, a_, r_, p_, l_, y_, Space, b_, o_, o_, s_, t_, Space, S_, p_, e_, e_, d_, Dot, Termin


RAGE_POWDER_description:
.byte S_, c_, a_, t_, t_, e_, r_, s_, Space, p_, o_, w_, d_, e_, r_, Space, t_, o_, Space, m_, a_, k_, e_, JumpLine
.byte f_, o_, e_, s_, Space, a_, t_, t_, a_, c_, k_, Space, o_, n_, l_, y_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


TELEKINESIS_description:
.byte M_, a_, k_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, f_, l_, o_, a_, t_, Dot, Space, I_, t_, Space, i_, s_, JumpLine
.byte e_, a_, s_, i_, e_, r_, Space, t_, o_, Space, h_, i_, t_, Space, f_, o_, r_, Space, 0xA4, Space, t_, u_, r_, n_, s_, Dot, Termin


MAGIC_ROOM_description:
.byte H_, o_, l_, d_, Space, i_, t_, e_, m_, s_, Space, l_, o_, s_, e_, Space, t_, h_, e_, i_, r_, JumpLine
.byte e_, f_, f_, e_, c_, t_, s_, Space, f_, o_, r_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Termin


SMACK_DOWN_description:
.byte T_, h_, r_, o_, w_, s_, Space, a_, Space, r_, o_, c_, k_, Space, t_, o_, Space, k_, n_, o_, c_, k_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Space, d_, o_, w_, n_, Space, t_, o_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Dot, Termin


STORM_THROW_description:
.byte T_, h_, i_, s_, Space, a_, t_, t_, a_, c_, k_, Space, a_, l_, w_, a_, y_, s_, Space, r_, e_, s_, u_, l_, t_, s_, JumpLine
.byte i_, n_, Space, a_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Space, h_, i_, t_, Dot, Termin


FLAME_BURST_description:
.byte A_, Space, b_, u_, r_, s_, t_, i_, n_, g_, Space, f_, l_, a_, m_, e_, Space, t_, h_, a_, t_, Space, d_, o_, e_, s_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, t_, o_, Space, a_, l_, l_, Space, f_, o_, e_, s_, Dot, Termin


SLUDGE_WAVE_description:
.byte S_, w_, a_, m_, p_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, a_, Space, w_, a_, v_, e_, JumpLine
.byte o_, f_, Space, s_, l_, u_, d_, g_, e_, Dot, Space, M_, a_, y_, Space, a_, l_, s_, o_, Space, p_, o_, i_, s_, o_, n_, Dot, Termin


QUIVER_DANCE_description:
.byte D_, a_, n_, c_, e_, s_, Space, t_, o_, Space, r_, a_, i_, s_, e_, Space, S_, p_, Dot, Space, A_, t_, k_, Comma, JumpLine
.byte S_, p_, Dot, Space, D_, e_, f_, Space, a_, n_, d_, Space, S_, p_, e_, e_, d_, Dot, Termin


HEAVY_SLAM_description:
.byte D_, o_, e_, s_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, t_, h_, e_, JumpLine
.byte u_, s_, e_, r_, Space, o_, u_, t_, w_, e_, i_, g_, h_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


SYNCHRONOISE_description:
.byte A_, n_, Space, o_, d_, d_, Space, s_, h_, o_, c_, k_, Space, w_, a_, v_, e_, Space, t_, h_, a_, t_, Space, o_, n_, l_, y_, JumpLine
.byte d_, a_, m_, a_, g_, e_, s_, Space, s_, a_, m_, e_, Dash, t_, y_, p_, e_, Space, f_, o_, e_, s_, Dot, Termin


ELECTRO_BALL_description:
.byte H_, u_, r_, l_, s_, Space, a_, n_, Space, o_, r_, b_, Space, t_, h_, a_, t_, Space, d_, o_, e_, s_, Space, m_, o_, r_, e_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, t_, o_, Space, s_, l_, o_, w_, e_, r_, Space, f_, o_, e_, s_, Dot, Termin


SOAK_description:
.byte S_, p_, r_, a_, y_, s_, Space, w_, a_, t_, e_, r_, Space, a_, t_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, JumpLine
.byte m_, a_, k_, i_, n_, g_, Space, i_, t_, Space, W_, a_, t_, e_, r_, Dash, t_, y_, p_, e_, Dot, Termin


FLAME_CHARGE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, i_, n_, Space, a_, Space, c_, l_, o_, a_, k_, Space, o_, f_, JumpLine
.byte f_, l_, a_, m_, e_, s_, Dot, Space, R_, a_, i_, s_, e_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


COIL_description:
.byte C_, o_, i_, l_, s_, Space, u_, p_, Space, t_, o_, Space, r_, a_, i_, s_, e_, Space, A_, t_, t_, a_, c_, k_, Comma, JumpLine
.byte D_, e_, f_, e_, n_, s_, e_, Space, a_, n_, d_, Space, A_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


LOW_SWEEP_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, l_, e_, g_, s_, Comma, JumpLine
.byte l_, o_, w_, e_, r_, i_, n_, g_, Space, i_, t_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


ACID_SPRAY_description:
.byte S_, p_, r_, a_, y_, s_, Space, a_, Space, h_, i_, d_, e_, Dash, m_, e_, l_, t_, i_, n_, g_, Space, a_, c_, i_, d_, Dot, JumpLine
.byte S_, h_, a_, r_, p_, l_, y_, Space, r_, e_, d_, u_, c_, e_, s_, Space, S_, p_, Dot, Space, D_, e_, f_, Dot, Termin


FOUL_PLAY_description:
.byte T_, h_, e_, Space, h_, i_, g_, h_, e_, r_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, A_, t_, t_, a_, c_, k_, Comma, JumpLine
.byte t_, h_, e_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, c_, a_, u_, s_, e_, d_, Dot, Termin


SIMPLE_BEAM_description:
.byte A_, Space, b_, e_, a_, m_, Space, t_, h_, a_, t_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Apos, s_, Space, a_, b_, i_, l_, i_, t_, y_, Space, t_, o_, Space, S_, i_, m_, p_, l_, e_, Dot, Termin


ENTRAINMENT_description:
.byte M_, a_, k_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, m_, i_, m_, i_, c_, Space, t_, h_, e_, JumpLine
.byte u_, s_, e_, r_, Comma, Space, g_, a_, i_, n_, i_, n_, g_, Space, i_, t_, s_, Space, a_, b_, i_, l_, i_, t_, y_, Dot, Termin


AFTER_YOU_description:
.byte H_, e_, l_, p_, s_, Space, o_, u_, t_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, l_, e_, t_, t_, i_, n_, g_, JumpLine
.byte i_, t_, Space, m_, o_, v_, e_, Space, n_, e_, x_, t_, Dot, Termin


ROUND_description:
.byte A_, Space, s_, o_, n_, g_, Space, t_, h_, a_, t_, Space, i_, n_, f_, l_, i_, c_, t_, s_, Space, d_, a_, m_, a_, g_, e_, Dot, JumpLine
.byte O_, t_, h_, e_, r_, s_, Space, c_, a_, n_, Space, j_, o_, i_, n_, Space, i_, n_, Space, t_, o_, o_, Dot, Termin


ECHOED_VOICE_description:
.byte D_, o_, e_, s_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, e_, v_, e_, r_, y_, Space, t_, u_, r_, n_, JumpLine
.byte i_, t_, Space, i_, s_, Space, u_, s_, e_, d_, Dot, Termin


CHIP_AWAY_description:
.byte S_, t_, r_, i_, k_, e_, s_, Space, t_, h_, r_, o_, u_, g_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, JumpLine
.byte s_, t_, a_, t_, Space, c_, h_, a_, n_, g_, e_, s_, Dot, Termin


CLEAR_SMOG_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, w_, h_, i_, t_, e_, Space, h_, a_, z_, e_, Space, t_, h_, a_, t_, JumpLine
.byte e_, l_, i_, m_, i_, n_, a_, t_, e_, s_, Space, a_, l_, l_, Space, s_, t_, a_, t_, Space, c_, h_, a_, n_, g_, e_, s_, Dot, Termin


STORED_POWER_description:
.byte T_, h_, e_, Space, h_, i_, g_, h_, e_, r_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Apos, s_, Space, s_, t_, a_, t_, s_, Comma, JumpLine
.byte t_, h_, e_, Space, m_, o_, r_, e_, Space, d_, a_, m_, a_, g_, e_, Space, c_, a_, u_, s_, e_, d_, Dot, Termin


QUICK_GUARD_description:
.byte E_, v_, a_, d_, e_, s_, Space, p_, r_, i_, o_, r_, i_, t_, y_, Space, a_, t_, t_, a_, c_, k_, s_, JumpLine
.byte f_, o_, r_, Space, o_, n_, e_, Space, t_, u_, r_, n_, Dot, Termin


ALLY_SWITCH_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, s_, w_, i_, t_, c_, h_, e_, s_, Space, p_, l_, a_, c_, e_, s_, JumpLine
.byte w_, i_, t_, h_, Space, i_, t_, s_, Space, p_, a_, r_, t_, n_, e_, r_, Dot, Termin


SCALD_description:
.byte S_, h_, o_, o_, t_, s_, Space, b_, o_, i_, l_, i_, n_, g_, Space, w_, a_, t_, e_, r_, Space, a_, t_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Dot, Space, M_, a_, y_, Space, i_, n_, f_, l_, i_, c_, t_, Space, a_, Space, b_, u_, r_, n_, Dot, Termin


SHELL_SMASH_description:
.byte R_, a_, i_, s_, e_, s_, Space, o_, f_, f_, e_, n_, s_, i_, v_, e_, Space, s_, t_, a_, t_, s_, Comma, Space, b_, u_, t_, JumpLine
.byte l_, o_, w_, e_, r_, s_, Space, d_, e_, f_, e_, n_, s_, i_, v_, e_, Space, s_, t_, a_, t_, s_, Dot, Termin


HEAL_PULSE_description:
.byte R_, e_, c_, o_, v_, e_, r_, s_, Space, u_, p_, Space, t_, o_, Space, h_, a_, l_, f_, Space, t_, h_, e_, JumpLine
.byte t_, a_, r_, g_, e_, t_, Apos, s_, Space, m_, a_, x_, i_, m_, u_, m_, Space, H_, P_, Dot, Termin


HEX_description:
.byte D_, o_, e_, s_, Space, d_, o_, u_, b_, l_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Space, h_, a_, s_, Space, a_, Space, s_, t_, a_, t_, u_, s_, Space, p_, r_, o_, b_, l_, e_, m_, Dot, Termin


SKY_DROP_description:
.byte T_, a_, k_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, n_, t_, o_, Space, t_, h_, e_, Space, s_, k_, y_, Comma, JumpLine
.byte t_, h_, e_, n_, Space, d_, r_, o_, p_, s_, Space, i_, t_, Space, t_, h_, e_, Space, n_, e_, x_, t_, Space, t_, u_, r_, n_, Dot, Termin


SHIFT_GEAR_description:
.byte R_, o_, t_, a_, t_, e_, s_, Space, i_, t_, s_, Space, g_, e_, a_, r_, s_, Space, t_, o_, Space, r_, a_, i_, s_, e_, JumpLine
.byte A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, Space, S_, p_, e_, e_, d_, Dot, Termin


CIRCLE_THROW_description:
.byte K_, n_, o_, c_, k_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, a_, w_, a_, y_, Space, t_, o_, Space, e_, n_, d_, JumpLine
.byte t_, h_, e_, Space, b_, a_, t_, t_, l_, e_, Dot, Termin


INCINERATE_description:
.byte B_, u_, r_, n_, s_, Space, u_, p_, Space, B_, e_, r_, r_, i_, e_, s_, Space, a_, n_, d_, Space, G_, e_, m_, s_, Comma, JumpLine
.byte p_, r_, e_, v_, e_, n_, t_, i_, n_, g_, Space, t_, h_, e_, i_, r_, Space, u_, s_, e_, Dot, Termin


QUASH_description:
.byte S_, u_, p_, p_, r_, e_, s_, s_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, m_, a_, k_, i_, n_, g_, JumpLine
.byte i_, t_, Space, m_, o_, v_, e_, Space, l_, a_, s_, t_, Dot, Termin


ACROBATICS_description:
.byte D_, o_, e_, s_, Space, d_, o_, u_, b_, l_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, t_, h_, e_, JumpLine
.byte u_, s_, e_, r_, Space, h_, a_, s_, Space, n_, o_, Space, i_, t_, e_, m_, Dot, Termin


REFLECT_TYPE_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, r_, e_, f_, l_, e_, c_, t_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, JumpLine
.byte t_, y_, p_, e_, Comma, Space, c_, o_, p_, y_, i_, n_, g_, Space, i_, t_, Dot, Termin


RETALIATE_description:
.byte A_, n_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, d_, o_, e_, s_, Space, m_, o_, r_, e_, JumpLine
.byte d_, a_, m_, a_, g_, e_, Space, i_, f_, Space, a_, n_, Space, a_, l_, l_, y_, Space, f_, a_, i_, n_, t_, e_, d_, Dot, Termin


FINAL_GAMBIT_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, f_, a_, i_, n_, t_, s_, Space, t_, o_, Space, d_, a_, m_, a_, g_, e_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Space, e_, q_, u_, a_, l_, Space, t_, o_, Space, i_, t_, s_, Space, H_, P_, Dot, Termin


BESTOW_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, g_, i_, v_, e_, s_, Space, i_, t_, s_, Space, h_, e_, l_, d_, JumpLine
.byte i_, t_, e_, m_, Space, t_, o_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


INFERNO_description:
.byte P_, o_, w_, e_, r_, f_, u_, l_, Space, a_, n_, d_, Space, s_, u_, r_, e_, Space, t_, o_, Space, i_, n_, f_, l_, i_, c_, t_, JumpLine
.byte a_, Space, b_, u_, r_, n_, Comma, Space, b_, u_, t_, Space, i_, n_, a_, c_, c_, u_, r_, a_, t_, e_, Dot, Termin


WATER_PLEDGE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, c_, o_, l_, u_, m_, n_, Space, o_, f_, JumpLine
.byte w_, a_, t_, e_, r_, Dot, Space, M_, a_, y_, Space, m_, a_, k_, e_, Space, a_, Space, r_, a_, i_, n_, b_, o_, w_, Dot, Termin


FIRE_PLEDGE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, c_, o_, l_, u_, m_, n_, Space, o_, f_, JumpLine
.byte f_, i_, r_, e_, Dot, Space, M_, a_, y_, Space, b_, u_, r_, n_, Space, t_, h_, e_, Space, g_, r_, a_, s_, s_, Dot, Termin


GRASS_PLEDGE_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, Space, c_, o_, l_, u_, m_, n_, Space, o_, f_, JumpLine
.byte g_, r_, a_, s_, s_, Dot, Space, M_, a_, y_, Space, c_, r_, e_, a_, t_, e_, Space, a_, Space, s_, w_, a_, m_, p_, Dot, Termin


STRUGGLE_BUG_description:
.byte R_, e_, s_, i_, s_, t_, i_, n_, g_, Comma, Space, t_, h_, e_, Space, u_, s_, e_, r_, Space, a_, t_, t_, a_, c_, k_, s_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Dot, Space, L_, o_, w_, e_, r_, s_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


BULLDOZE_description:
.byte S_, t_, o_, m_, p_, s_, Space, d_, o_, w_, n_, Space, o_, n_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Dot, JumpLine
.byte L_, o_, w_, e_, r_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


WORK_UP_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, i_, s_, Space, r_, o_, u_, s_, e_, d_, Dot, JumpLine
.byte U_, p_, s_, Space, A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


ELECTROWEB_description:
.byte S_, n_, a_, r_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, a_, n_, JumpLine
.byte e_, l_, e_, c_, t_, r_, i_, c_, Space, n_, e_, t_, Dot, Space, L_, o_, w_, e_, r_, s_, Space, S_, p_, e_, e_, d_, Dot, Termin


DRILL_RUN_description:
.byte S_, p_, i_, n_, s_, Space, i_, t_, s_, Space, b_, o_, d_, y_, Space, l_, i_, k_, e_, Space, a_, Space, d_, r_, i_, l_, l_, Dot, JumpLine
.byte H_, i_, g_, h_, Space, c_, r_, i_, t_, i_, c_, a_, l_, Dash, h_, i_, t_, Space, r_, a_, t_, i_, o_, Dot, Termin


DUAL_CHOP_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, b_, r_, u_, t_, a_, l_, Space, h_, i_, t_, s_, JumpLine
.byte t_, h_, a_, t_, Space, s_, t_, r_, i_, k_, e_, Space, t_, w_, i_, c_, e_, Dot, Termin


HEART_STAMP_description:
.byte A_, Space, s_, u_, d_, d_, e_, n_, Space, b_, l_, o_, w_, Space, a_, f_, t_, e_, r_, Space, a_, Space, c_, u_, t_, e_, JumpLine
.byte a_, c_, t_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


RAZOR_SHELL_description:
.byte T_, e_, a_, r_, s_, Space, a_, t_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, s_, h_, a_, r_, p_, JumpLine
.byte s_, h_, e_, l_, l_, s_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, D_, e_, f_, e_, n_, s_, e_, Dot, Termin


LEAF_TORNADO_description:
.byte C_, i_, r_, c_, l_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, l_, e_, a_, v_, e_, s_, JumpLine
.byte t_, o_, Space, d_, a_, m_, a_, g_, e_, Space, a_, n_, d_, Space, c_, u_, t_, Space, a_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


STEAMROLLER_description:
.byte C_, r_, u_, s_, h_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, w_, i_, t_, h_, Space, i_, t_, s_, JumpLine
.byte b_, o_, d_, y_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


COTTON_GUARD_description:
.byte W_, r_, a_, p_, s_, Space, i_, t_, s_, Space, b_, o_, d_, y_, Space, i_, n_, Space, c_, o_, t_, t_, o_, n_, Dot, JumpLine
.byte D_, r_, a_, s_, t_, i_, c_, a_, l_, l_, y_, Space, r_, a_, i_, s_, e_, s_, Space, D_, e_, f_, e_, n_, s_, e_, Dot, Termin


NIGHT_DAZE_description:
.byte L_, o_, o_, s_, e_, s_, Space, a_, Space, p_, i_, t_, c_, h_, Dash, b_, l_, a_, c_, k_, Space, s_, h_, o_, c_, k_, JumpLine
.byte w_, a_, v_, e_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, a_, c_, c_, u_, r_, a_, c_, y_, Dot, Termin


HURRICANE_description:
.byte T_, r_, a_, p_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, n_, Space, a_, Space, f_, i_, e_, r_, c_, e_, JumpLine
.byte w_, i_, n_, d_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, c_, o_, n_, f_, u_, s_, i_, o_, n_, Dot, Termin


HEAD_CHARGE_description:
.byte A_, Space, c_, h_, a_, r_, g_, e_, Space, u_, s_, i_, n_, g_, Space, g_, u_, a_, r_, d_, Space, h_, a_, i_, r_, Dot, JumpLine
.byte I_, t_, Space, h_, u_, r_, t_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Space, a_, Space, l_, i_, t_, t_, l_, e_, Dot, Termin


GEAR_GRIND_description:
.byte T_, h_, r_, o_, w_, s_, Space, t_, w_, o_, Space, s_, t_, e_, e_, l_, Space, g_, e_, a_, r_, s_, JumpLine
.byte t_, h_, a_, t_, Space, s_, t_, r_, i_, k_, e_, Space, t_, w_, i_, c_, e_, Dot, Termin


TECHNO_BLAST_description:
.byte T_, h_, e_, Space, t_, y_, p_, e_, Space, v_, a_, r_, i_, e_, s_, Space, w_, i_, t_, h_, Space, t_, h_, e_, JumpLine
.byte k_, i_, n_, d_, Space, o_, f_, Space, D_, r_, i_, v_, e_, Space, h_, e_, l_, d_, Dot, Termin


RELIC_SONG_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, a_, n_, Space, a_, n_, c_, i_, e_, n_, t_, JumpLine
.byte s_, o_, n_, g_, Dot, Space, M_, a_, y_, Space, i_, n_, d_, u_, c_, e_, Space, s_, l_, e_, e_, p_, Dot, Termin


SECRET_SWORD_description:
.byte C_, u_, t_, s_, Space, w_, i_, t_, h_, Space, a_, Space, l_, o_, n_, g_, Space, h_, o_, r_, n_, Space, t_, h_, a_, t_, JumpLine
.byte d_, o_, e_, s_, Space, p_, h_, y_, s_, i_, c_, a_, l_, Space, d_, a_, m_, a_, g_, e_, Dot, Termin


BOLT_STRIKE_description:
.byte S_, t_, r_, i_, k_, e_, s_, Space, w_, i_, t_, h_, Space, a_, Space, g_, r_, e_, a_, t_, Space, a_, m_, o_, u_, n_, t_, JumpLine
.byte o_, f_, Space, l_, i_, g_, h_, t_, n_, i_, n_, g_, Dot, Space, M_, a_, y_, Space, p_, a_, r_, a_, l_, y_, z_, e_, Dot, Termin


BLUE_FLARE_description:
.byte E_, n_, g_, u_, l_, f_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, n_, Space, a_, Space, b_, l_, u_, e_, JumpLine
.byte f_, l_, a_, m_, e_, Dot, Space, M_, a_, y_, Space, i_, n_, f_, l_, i_, c_, t_, Space, a_, Space, b_, u_, r_, n_, Dot, Termin


FIERY_DANCE_description:
.byte D_, a_, n_, c_, e_, s_, Space, c_, l_, o_, a_, k_, e_, d_, Space, i_, n_, Space, f_, l_, a_, m_, e_, s_, Dot, JumpLine
.byte M_, a_, y_, Space, r_, a_, i_, s_, e_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


FREEZE_SHOCK_description:
.byte A_, Space, p_, o_, w_, e_, r_, f_, u_, l_, Space, 0xA3, Dash, t_, u_, r_, n_, Space, m_, o_, v_, e_, Space, t_, h_, a_, t_, JumpLine
.byte m_, a_, y_, Space, p_, a_, r_, a_, l_, y_, z_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


ICE_BURN_description:
.byte A_, Space, p_, o_, w_, e_, r_, f_, u_, l_, Space, 0xA3, Dash, t_, u_, r_, n_, Space, m_, o_, v_, e_, Space, t_, h_, a_, t_, JumpLine
.byte m_, a_, y_, Space, i_, n_, f_, l_, i_, c_, t_, Space, a_, Space, b_, u_, r_, n_, Dot, Termin


SNARL_description:
.byte Y_, e_, l_, l_, s_, Space, a_, n_, d_, Space, r_, a_, n_, t_, s_, Space, a_, t_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, JumpLine
.byte l_, o_, w_, e_, r_, i_, n_, g_, Space, i_, t_, s_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


ICICLE_CRASH_description:
.byte D_, r_, o_, p_, s_, Space, l_, a_, r_, g_, e_, Space, i_, c_, i_, c_, l_, e_, s_, Space, o_, n_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, l_, i_, n_, c_, h_, i_, n_, g_, Dot, Termin


V_CREATE_description:
.byte V_, e_, r_, y_, Space, p_, o_, w_, e_, r_, f_, u_, l_, Comma, Space, b_, u_, t_, Space, l_, o_, w_, e_, r_, s_, JumpLine
.byte D_, e_, f_, e_, n_, s_, e_, Comma, Space, S_, p_, Dot, Space, D_, e_, f_, Space, a_, n_, d_, Space, S_, p_, e_, e_, d_, Dot, Termin


FUSION_FLARE_description:
.byte S_, u_, m_, m_, o_, n_, s_, Space, a_, Space, f_, i_, r_, e_, b_, a_, l_, l_, Dot, Space, W_, o_, r_, k_, s_, JumpLine
.byte w_, e_, l_, l_, Space, w_, i_, t_, h_, Space, a_, Space, t_, h_, u_, n_, d_, e_, r_, b_, o_, l_, t_, Dot, Termin


FUSION_BOLT_description:
.byte S_, u_, m_, m_, o_, n_, s_, Space, a_, Space, t_, h_, u_, n_, d_, e_, r_, b_, o_, l_, t_, Dot, JumpLine
.byte W_, o_, r_, k_, s_, Space, w_, e_, l_, l_, Space, w_, i_, t_, h_, Space, a_, Space, f_, i_, r_, e_, b_, a_, l_, l_, Dot, Termin


FLYING_PRESS_description:
.byte T_, h_, i_, s_, Space, a_, t_, t_, a_, c_, k_, Space, d_, o_, e_, s_, Space, F_, i_, g_, h_, t_, i_, n_, g_, Dash, JumpLine
.byte a_, n_, d_, Space, F_, l_, y_, i_, n_, g_, Dash, t_, y_, p_, e_, Space, d_, a_, m_, a_, g_, e_, Dot, Termin


MAT_BLOCK_description:
.byte E_, v_, a_, d_, e_, s_, Space, d_, a_, m_, a_, g_, i_, n_, g_, Space, m_, o_, v_, e_, s_, JumpLine
.byte f_, o_, r_, Space, o_, n_, e_, Space, t_, u_, r_, n_, Dot, Termin


BELCH_description:
.byte L_, e_, t_, s_, Space, o_, u_, t_, Space, a_, Space, l_, o_, u_, d_, Space, b_, e_, l_, c_, h_, Dot, JumpLine
.byte M_, u_, s_, t_, Space, e_, a_, t_, Space, a_, Space, B_, e_, r_, r_, y_, Space, t_, o_, Space, u_, s_, e_, Space, i_, t_, Dot, Termin


ROTOTILLER_description:
.byte U_, p_, s_, Space, t_, h_, e_, Space, A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, Space, S_, p_, Dot, Space, A_, t_, k_, JumpLine
.byte o_, f_, Space, G_, r_, a_, s_, s_, Dash, t_, y_, p_, e_, Space, P_, o_, k_, Poke_e, m_, o_, n_, Dot, Termin


STICKY_WEB_description:
.byte W_, e_, a_, v_, e_, s_, Space, a_, Space, s_, t_, i_, c_, k_, y_, Space, n_, e_, t_, Space, t_, h_, a_, t_, JumpLine
.byte s_, l_, o_, w_, s_, Space, f_, o_, e_, s_, Space, s_, w_, i_, t_, c_, h_, i_, n_, g_, Space, i_, n_, Dot, Termin


FELL_STINGER_description:
.byte I_, f_, Space, i_, t_, Space, k_, n_, o_, c_, k_, s_, Space, o_, u_, t_, Space, a_, Space, f_, o_, e_, Comma, JumpLine
.byte t_, h_, e_, Space, A_, t_, t_, a_, c_, k_, Space, s_, t_, a_, t_, Space, i_, s_, Space, r_, a_, i_, s_, e_, d_, Dot, Termin


TRICK_OR_TREAT_description:
.byte G_, o_, e_, s_, Space, t_, r_, i_, c_, k_, Dash, o_, r_, Dash, t_, r_, e_, a_, t_, i_, n_, g_, Comma, JumpLine
.byte m_, a_, k_, i_, n_, g_, Space, t_, h_, e_, Space, f_, o_, e_, Space, G_, h_, o_, s_, t_, Dash, t_, y_, p_, e_, Dot, Termin


NOBLE_ROAR_description:
.byte I_, n_, t_, i_, m_, i_, d_, a_, t_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, t_, o_, Space, c_, u_, t_, JumpLine
.byte A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


ION_DELUGE_description:
.byte E_, l_, e_, c_, t_, r_, i_, f_, i_, e_, s_, Space, N_, o_, r_, m_, a_, l_, Dash, t_, y_, p_, e_, JumpLine
.byte m_, o_, v_, e_, s_, Space, w_, i_, t_, h_, Space, c_, h_, a_, r_, g_, e_, d_, Space, a_, t_, o_, m_, s_, Dot, Termin


FORESTS_CURSE_description:
.byte P_, u_, t_, s_, Space, a_, Space, c_, u_, r_, s_, e_, Space, o_, n_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, JumpLine
.byte m_, a_, k_, i_, n_, g_, Space, t_, h_, e_, Space, f_, o_, e_, Space, G_, r_, a_, s_, s_, Dash, t_, y_, p_, e_, Dot, Termin


PETAL_BLIZZARD_description:
.byte S_, t_, i_, r_, s_, Space, u_, p_, Space, a_, Space, v_, i_, o_, l_, e_, n_, t_, Space, s_, t_, o_, r_, m_, JumpLine
.byte o_, f_, Space, p_, e_, t_, a_, l_, s_, Space, t_, o_, Space, a_, t_, t_, a_, c_, k_, Dot, Termin


FREEZE_DRY_description:
.byte S_, u_, p_, e_, r_, Space, e_, f_, f_, e_, c_, t_, i_, v_, e_, Space, o_, n_, Space, W_, a_, t_, e_, r_, Dash, JumpLine
.byte t_, y_, p_, e_, s_, Dot, Space, M_, a_, y_, Space, c_, a_, u_, s_, e_, Space, f_, r_, e_, e_, z_, i_, n_, g_, Dot, Termin


DISARMING_VOICE_description:
.byte L_, e_, t_, s_, Space, o_, u_, t_, Space, a_, Space, c_, h_, a_, r_, m_, i_, n_, g_, Space, c_, r_, y_, JumpLine
.byte t_, h_, a_, t_, Space, c_, a_, n_, n_, o_, t_, Space, b_, e_, Space, e_, v_, a_, d_, e_, d_, Dot, Termin


PARTING_SHOT_description:
.byte L_, o_, w_, e_, r_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, A_, t_, t_, a_, c_, k_, Space, a_, n_, d_, JumpLine
.byte S_, p_, Dot, Space, A_, t_, k_, Comma, Space, t_, h_, e_, n_, Space, s_, w_, i_, t_, c_, h_, e_, s_, Space, o_, u_, t_, Dot, Termin


TOPSY_TURVY_description:
.byte S_, w_, a_, p_, s_, Space, a_, l_, l_, Space, s_, t_, a_, t_, Space, c_, h_, a_, n_, g_, e_, s_, Space, t_, h_, a_, t_, JumpLine
.byte a_, f_, f_, e_, c_, t_, Space, t_, h_, e_, Space, t_, a_, r_, g_, e_, t_, Dot, Termin


DRAINING_KISS_description:
.byte A_, n_, Space, a_, t_, t_, a_, c_, k_, Space, t_, h_, a_, t_, Space, a_, b_, s_, o_, r_, b_, s_, Space, o_, v_, e_, r_, JumpLine
.byte h_, a_, l_, f_, Space, t_, h_, e_, Space, d_, a_, m_, a_, g_, e_, Space, i_, n_, f_, l_, i_, c_, t_, e_, d_, Dot, Termin


CRAFTY_SHIELD_description:
.byte E_, v_, a_, d_, e_, s_, Space, s_, t_, a_, t_, u_, s_, Space, m_, o_, v_, e_, s_, Space, f_, o_, r_, JumpLine
.byte o_, n_, e_, Space, t_, u_, r_, n_, Dot, Termin


FLOWER_SHIELD_description:
.byte R_, a_, i_, s_, e_, s_, Space, t_, h_, e_, Space, D_, e_, f_, e_, n_, s_, e_, Space, o_, f_, JumpLine
.byte G_, r_, a_, s_, s_, Dash, t_, y_, p_, e_, Space, P_, o_, k_, Poke_e, m_, o_, n_, Dot, Termin


GRASSY_TERRAIN_description:
.byte T_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Space, t_, u_, r_, n_, s_, Space, t_, o_, Space, g_, r_, a_, s_, s_, JumpLine
.byte f_, o_, r_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Space, R_, e_, s_, t_, o_, r_, e_, s_, Space, H_, P_, Dot, Termin


MISTY_TERRAIN_description:
.byte C_, o_, v_, e_, r_, s_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Space, w_, i_, t_, h_, Space, m_, i_, s_, t_, JumpLine
.byte f_, o_, r_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Space, B_, l_, o_, c_, k_, s_, Space, s_, t_, a_, t_, u_, s_, Dot, Termin


ELECTRIFY_description:
.byte E_, l_, e_, c_, t_, r_, i_, f_, i_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, m_, a_, k_, i_, n_, g_, JumpLine
.byte i_, t_, s_, Space, n_, e_, x_, t_, Space, m_, o_, v_, e_, Space, E_, l_, e_, c_, t_, r_, i_, c_, Dash, t_, y_, p_, e_, Dot, Termin


PLAY_ROUGH_description:
.byte P_, l_, a_, y_, s_, Space, r_, o_, u_, g_, h_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, JumpLine
.byte M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, A_, t_, t_, a_, c_, k_, Dot, Termin


FAIRY_WIND_description:
.byte S_, t_, i_, r_, s_, Space, u_, p_, Space, a_, Space, f_, a_, i_, r_, y_, Space, w_, i_, n_, d_, Space, t_, o_, JumpLine
.byte s_, t_, r_, i_, k_, e_, Space, t_, h_, e_, Space, f_, o_, e_, Dot, Termin


MOONBLAST_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, w_, i_, t_, h_, Space, t_, h_, e_, Space, p_, o_, w_, e_, r_, Space, o_, f_, JumpLine
.byte t_, h_, e_, Space, m_, o_, o_, n_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


BOOMBURST_description:
.byte A_, t_, t_, a_, c_, k_, s_, Space, e_, v_, e_, r_, y_, t_, h_, i_, n_, g_, Space, w_, i_, t_, h_, Space, a_, JumpLine
.byte d_, e_, s_, t_, r_, u_, c_, t_, i_, v_, e_, Space, s_, o_, u_, n_, d_, Space, w_, a_, v_, e_, Dot, Termin


FAIRY_LOCK_description:
.byte L_, o_, c_, k_, s_, Space, d_, o_, w_, n_, Space, t_, h_, e_, Space, b_, a_, t_, t_, l_, e_, f_, i_, e_, l_, d_, Comma, JumpLine
.byte p_, r_, e_, v_, e_, n_, t_, i_, n_, g_, Space, e_, s_, c_, a_, p_, e_, Space, n_, e_, x_, t_, Space, t_, u_, r_, n_, Dot, Termin


KINGS_SHIELD_description:
.byte E_, v_, a_, d_, e_, s_, Space, d_, a_, m_, a_, g_, e_, Comma, Space, a_, n_, d_, Space, s_, h_, a_, r_, p_, l_, y_, JumpLine
.byte r_, e_, d_, u_, c_, e_, s_, Space, A_, t_, t_, a_, c_, k_, Space, i_, f_, Space, s_, t_, r_, u_, c_, k_, Dot, Termin


PLAY_NICE_description:
.byte B_, e_, f_, r_, i_, e_, n_, d_, Space, t_, h_, e_, Space, f_, o_, e_, Comma, Space, l_, o_, w_, e_, r_, i_, n_, g_, JumpLine
.byte i_, t_, s_, Space, A_, t_, t_, a_, c_, k_, Space, w_, i_, t_, h_, o_, u_, t_, Space, f_, a_, i_, l_, Dot, Termin


CONFIDE_description:
.byte S_, h_, a_, r_, e_, s_, Space, a_, Space, s_, e_, c_, r_, e_, t_, Space, w_, i_, t_, h_, Space, t_, h_, e_, JumpLine
.byte f_, o_, e_, Comma, Space, l_, o_, w_, e_, r_, i_, n_, g_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


DIAMOND_STORM_description:
.byte W_, h_, i_, p_, s_, Space, u_, p_, Space, a_, Space, s_, t_, o_, r_, m_, Space, o_, f_, JumpLine
.byte d_, i_, a_, m_, o_, n_, d_, s_, Dot, Space, M_, a_, y_, Space, u_, p_, Space, D_, e_, f_, e_, n_, s_, e_, Dot, Termin


STEAM_ERUPTION_description:
.byte I_, m_, m_, e_, r_, s_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, n_, Space, h_, e_, a_, t_, e_, d_, JumpLine
.byte s_, t_, e_, a_, m_, Dot, Space, M_, a_, y_, Space, i_, n_, f_, l_, i_, c_, t_, Space, a_, Space, b_, u_, r_, n_, Dot, Termin


HYPERSPACE_HOLE_description:
.byte U_, s_, e_, s_, Space, a_, Space, w_, a_, r_, p_, Space, h_, o_, l_, e_, Space, t_, o_, Space, a_, t_, t_, a_, c_, k_, Dot, JumpLine
.byte C_, a_, n_, Apos, t_, Space, b_, e_, Space, e_, v_, a_, d_, e_, d_, Dot, Termin


WATER_SHURIKEN_description:
.byte T_, h_, r_, o_, w_, s_, Space, 0xA3, Space, t_, o_, Space, 0xA6, Space, s_, t_, a_, r_, s_, Space, t_, h_, a_, t_, JumpLine
.byte a_, r_, e_, Space, s_, u_, r_, e_, Space, t_, o_, Space, s_, t_, r_, i_, k_, e_, Space, f_, i_, r_, s_, t_, Dot, Termin


MYSTICAL_FIRE_description:
.byte B_, r_, e_, a_, t_, h_, e_, s_, Space, a_, Space, s_, p_, e_, c_, i_, a_, l_, Comma, Space, h_, o_, t_, JumpLine
.byte f_, i_, r_, e_, Dot, Space, M_, a_, y_, Space, l_, o_, w_, e_, r_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


SPIKY_SHIELD_description:
.byte E_, v_, a_, d_, e_, s_, Space, a_, t_, t_, a_, c_, k_, Comma, Space, a_, n_, d_, Space, d_, a_, m_, a_, g_, e_, s_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Space, i_, f_, Space, s_, t_, r_, u_, c_, k_, Dot, Termin


AROMATIC_MIST_description:
.byte R_, a_, i_, s_, e_, s_, Space, t_, h_, e_, Space, S_, p_, Dot, Space, D_, e_, f_, Space, o_, f_, Space, a_, JumpLine
.byte p_, a_, r_, t_, n_, e_, r_, Space, P_, o_, k_, Poke_e, m_, o_, n_, Dot, Termin


EERIE_IMPULSE_description:
.byte E_, x_, p_, o_, s_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, t_, o_, Space, a_, Space, p_, u_, l_, s_, e_, JumpLine
.byte t_, h_, a_, t_, Space, s_, h_, a_, r_, p_, l_, y_, Space, c_, u_, t_, s_, Space, S_, p_, Dot, Space, A_, t_, k_, Dot, Termin


VENOM_DRENCH_description:
.byte L_, o_, w_, e_, r_, s_, Space, t_, h_, e_, Space, A_, t_, t_, a_, c_, k_, Comma, Space, S_, p_, Dot, Space, A_, t_, k_, JumpLine
.byte a_, n_, d_, Space, S_, p_, e_, e_, d_, Space, o_, f_, Space, a_, Space, p_, o_, i_, s_, o_, n_, e_, d_, Space, f_, o_, e_, Dot, Termin


POWDER_description:
.byte D_, a_, m_, a_, g_, e_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Space, i_, f_, Space, i_, t_, Space, u_, s_, e_, s_, JumpLine
.byte a_, Space, F_, i_, r_, e_, Dash, t_, y_, p_, e_, Space, m_, o_, v_, e_, Dot, Termin


GEOMANCY_description:
.byte R_, a_, i_, s_, e_, s_, Space, S_, p_, Dot, Space, A_, t_, k_, Comma, Space, S_, p_, Dot, Space, D_, e_, f_, Space, a_, n_, d_, JumpLine
.byte S_, p_, e_, e_, d_, Space, o_, n_, Space, t_, h_, e_, Space, 0xA3, n_, d_, Space, t_, u_, r_, n_, Dot, Termin


MAGNETIC_FLUX_description:
.byte B_, o_, o_, s_, t_, s_, Space, t_, h_, e_, Space, d_, e_, f_, e_, n_, s_, e_, s_, Space, o_, f_, JumpLine
.byte t_, h_, o_, s_, e_, Space, w_, i_, t_, h_, Space, P_, l_, u_, s_, Space, o_, r_, Space, M_, i_, n_, u_, s_, Dot, Termin


HAPPY_HOUR_description:
.byte D_, o_, u_, b_, l_, e_, s_, Space, t_, h_, e_, Space, a_, m_, o_, u_, n_, t_, Space, o_, f_, JumpLine
.byte P_, r_, i_, z_, e_, Space, M_, o_, n_, e_, y_, Space, r_, e_, c_, e_, i_, v_, e_, d_, Dot, Termin


ELECTRIC_TERRAIN_description:
.byte E_, l_, e_, c_, t_, r_, i_, f_, i_, e_, s_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Space, f_, o_, r_, JumpLine
.byte 0xA6, Space, t_, u_, r_, n_, s_, Dot, Space, P_, r_, e_, v_, e_, n_, t_, s_, Space, s_, l_, e_, e_, p_, Dot, Termin


DAZZLING_GLEAM_description:
.byte D_, a_, m_, a_, g_, e_, s_, Space, f_, o_, e_, s_, Space, b_, y_, Space, e_, m_, i_, t_, t_, i_, n_, g_, JumpLine
.byte a_, Space, b_, r_, i_, g_, h_, t_, Space, f_, l_, a_, s_, h_, Dot, Termin


CELEBRATE_description:
.byte C_, o_, n_, g_, r_, a_, t_, u_, l_, a_, t_, e_, s_, Space, y_, o_, u_, Space, o_, n_, Space, y_, o_, u_, r_, JumpLine
.byte s_, p_, e_, c_, i_, a_, l_, Space, d_, a_, y_, Exclam, Termin


HOLD_HANDS_description:
.byte T_, h_, e_, Space, u_, s_, e_, r_, Space, a_, n_, d_, Space, a_, l_, l_, y_, Space, h_, o_, l_, d_, Space, h_, a_, n_, d_, s_, Comma, JumpLine
.byte m_, a_, k_, i_, n_, g_, Space, t_, h_, e_, m_, Space, h_, a_, p_, p_, y_, Dot, Termin


BABYDOLL_EYES_description:
.byte L_, o_, w_, e_, r_, s_, Space, t_, h_, e_, Space, f_, o_, e_, Apos, s_, Space, A_, t_, t_, a_, c_, k_, JumpLine
.byte b_, e_, f_, o_, r_, e_, Space, i_, t_, Space, c_, a_, n_, Space, m_, o_, v_, e_, Dot, Termin


NUZZLE_description:
.byte R_, u_, b_, s_, Space, i_, t_, s_, Space, c_, h_, e_, e_, c_, k_, s_, Space, a_, g_, a_, i_, n_, s_, t_, JumpLine
.byte t_, h_, e_, Space, f_, o_, e_, Comma, Space, p_, a_, r_, a_, l_, y_, z_, i_, n_, g_, Space, i_, t_, Dot, Termin


INFESTATION_description:
.byte T_, h_, e_, Space, f_, o_, e_, Space, i_, s_, Space, i_, n_, f_, e_, s_, t_, e_, d_, Space, a_, n_, d_, JumpLine
.byte a_, t_, t_, a_, c_, k_, e_, d_, Space, f_, o_, r_, Space, 0xA3, Space, t_, o_, Space, 0xA6, Space, t_, u_, r_, n_, s_, Dot, Termin


POWER_UP_PUNCH_description:
.byte A_, Space, h_, a_, r_, d_, Space, p_, u_, n_, c_, h_, Space, t_, h_, a_, t_, Space, r_, a_, i_, s_, e_, s_, JumpLine
.byte t_, h_, e_, Space, u_, s_, e_, r_, Apos, s_, Space, A_, t_, t_, a_, c_, k_, Dot, Termin


THOUSAND_ARROWS_description:
.byte C_, a_, n_, Space, h_, i_, t_, Space, F_, l_, y_, i_, n_, g_, Space, f_, o_, e_, s_, Comma, Space, t_, h_, e_, n_, JumpLine
.byte k_, n_, o_, c_, k_, s_, Space, t_, h_, e_, m_, Space, t_, o_, Space, t_, h_, e_, Space, g_, r_, o_, u_, n_, d_, Dot, Termin


THOUSAND_WAVES_description:
.byte T_, h_, o_, s_, e_, Space, h_, i_, t_, Space, b_, y_, Space, t_, h_, e_, Space, w_, a_, v_, e_, Space, c_, a_, n_, JumpLine
.byte n_, o_, Space, l_, o_, n_, g_, e_, r_, Space, e_, s_, c_, a_, p_, e_, Dot, Termin


LIGHT_OF_RUIN_description:
.byte F_, i_, r_, e_, s_, Space, a_, Space, g_, r_, e_, a_, t_, Space, b_, e_, a_, m_, Space, o_, f_, Space, l_, i_, g_, h_, t_, JumpLine
.byte t_, h_, a_, t_, Space, a_, l_, s_, o_, Space, h_, u_, r_, t_, s_, Space, t_, h_, e_, Space, u_, s_, e_, r_, Dot, Termin


ORIGIN_PULSE_description:
.byte B_, e_, a_, m_, s_, Space, o_, f_, Space, g_, l_, o_, w_, i_, n_, g_, Space, b_, l_, u_, e_, Space, l_, i_, g_, h_, t_, JumpLine
.byte b_, l_, a_, s_, t_, Space, b_, o_, t_, h_, Space, f_, o_, e_, s_, Dot, Termin


PRECIPICE_BLADES_description:
.byte F_, e_, a_, r_, s_, o_, m_, e_, Space, b_, l_, a_, d_, e_, s_, Space, o_, f_, Space, s_, t_, o_, n_, e_, JumpLine
.byte a_, t_, t_, a_, c_, k_, Space, b_, o_, t_, h_, Space, f_, o_, e_, s_, Dot, Termin


LAVA_PLUME_description:
.byte S_, c_, a_, r_, l_, e_, t_, 0, f_, l_, a_, m_, e_, s_, 0, t_, o_, r_, c_, h_, e_, s_, 0xFE
.byte e_, v_, e_, r_, y_, t_, h_, i_, n_, g_, 0, a_, r_, o_, u_, n_, d_, 0, t_, h_, e_, 0, u_, s_, e_, r_, Dot, 0xFF

NOTHING_description:
.byte N_, o_, t_, h_, i_, n_, g_, Space, f_, o_, r_, Space, n_, o_, w_, Dot, Termin
.word 0x0
.word 0xFFFFFFFF
