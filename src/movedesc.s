.text
.thumb
.align 2

.include "asm_defines.s"
.include "macrotext.s"

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
.word ROOST_description
.word GRAVITY_description
.word MIRACLE_EYE_description
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
.word UTURN_description
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
.word COPYCAT_description
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
.word NIGHT_SLASH_description
.word AQUA_TAIL_description
.word SEED_BOMB_description
.word AIR_SLASH_description
.word XSCISSOR_description
.word BUG_BUZZ_description
.word DRAGON_PULSE_description
.word DRAGON_RUSH_description
.word POWER_GEM_description
.word DRAIN_PUNCH_description
.word VACUUM_WAVE_description
.word FOCUS_BLAST_description
.word ENERGY_BALL_description
.word BRAVE_BIRD_description
.word EARTH_POWER_description
.word SWITCHEROO_description
.word GIGA_IMPACT_description
.word NASTY_PLOT_description
.word BULLET_PUNCH_description
.word AVALANCHE_description
.word ICE_SHARD_description
.word SHADOW_CLAW_description
.word THUNDER_FANG_description
.word ICE_FANG_description
.word FIRE_FANG_description
.word SHADOW_SNEAK_description
.word MUD_BOMB_description
.word PSYCHO_CUT_description
.word ZEN_HEADBUTT_description
.word MIRROR_SHOT_description
.word FLASH_CANNON_description
.word ROCK_CLIMB_description
.word DEFOG_description
.word TRICK_ROOM_description
.word DRACO_METEOR_description
.word DISCHARGE_description
.word LAVA_PLUME_description
.word LEAF_STORM_description
.word POWER_WHIP_description
.word ROCK_WRECKER_description
.word CROSS_POISON_description
.word GUNK_SHOT_description
.word IRON_HEAD_description
.word MAGNET_BOMB_description
.word STONE_EDGE_description
.word CAPTIVATE_description
.word STEALTH_ROCK_description
.word GRASS_KNOT_description
.word CHATTER_description
.word JUDGMENT_description
.word BUG_BITE_description
.word CHARGE_BEAM_description
.word WOOD_HAMMER_description
.word AQUA_JET_description
.word ATTACK_ORDER_description
.word DEFEND_ORDER_description
.word HEAL_ORDER_description
.word HEAD_SMASH_description
.word DOUBLE_HIT_description
.word ROAR_OF_TIME_description
.word SPACIAL_REND_description
.word LUNAR_DANCE_description
.word CRUSH_GRIP_description
.word MAGMA_STORM_description
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
.word VOLT_SWITCH_description
.word STRUGGLE_BUG_description
.word BULLDOZE_description
.word FROST_BREATH_description
.word DRAGON_TAIL_description
.word WORK_UP_description
.word ELECTROWEB_description
.word WILD_CHARGE_description
.word DRILL_RUN_description
.word DUAL_CHOP_description
.word HEART_STAMP_description
.word HORN_LEECH_description
.word SACRED_SWORD_description
.word RAZOR_SHELL_description
.word HEAT_CRASH_description
.word LEAF_TORNADO_description
.word STEAMROLLER_description
.word COTTON_GUARD_description
.word NIGHT_DAZE_description
.word PSYSTRIKE_description
.word TAIL_SLAP_description
.word HURRICANE_description
.word HEAD_CHARGE_description
.word GEAR_GRIND_description
.word SEARING_SHOT_description
.word TECHNO_BLAST_description
.word RELIC_SONG_description
.word SECRET_SWORD_description
.word GLACIATE_description
.word BOLT_STRIKE_description
.word BLUE_FLARE_description
.word FIERY_DANCE_description
.word FREEZE_SHOCK_description
.word ICE_BURN_description
.word SNARL_description
.word ICICLE_CRASH_description
.word VCREATE_description
.word FUSION_FLARE_description
.word FUSION_BOLT_description
.word FLYING_PRESS_description
.word MAT_BLOCK_description
.word BELCH_description
.word ROTOTILLER_description
.word STICKY_WEB_description
.word FELL_STINGER_description
.word PHANTOM_FORCE_description
.word TRICKORTREAT_description
.word NOBLE_ROAR_description
.word ION_DELUGE_description
.word PARABOLIC_CHARGE_description
.word FORESTS_CURSE_description
.word PETAL_BLIZZARD_description
.word FREEZEDRY_description
.word DISARMING_VOICE_description
.word PARTING_SHOT_description
.word TOPSYTURVY_description
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
.word HOLD_BACK_description
.word INFESTATION_description
.word POWERUP_PUNCH_description
.word OBLIVION_WING_description
.word THOUSAND_ARROWS_description
.word THOUSAND_WAVES_description
.word LANDS_WRATH_description
.word LIGHT_OF_RUIN_description
.word ORIGINE_PULSE_description
.word PRECIPICE_BLADES_description
.word DRAGON_ASCENT_description
.word HYPERSPACE_FURY_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description
.word NOTHING_description

.align 2
ROOST_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 l_ a_ n_ d_ s_ 0 a_ n_ d_ 0xFE r_ e_ s_ t_ s_ 0 i_ t_ s_
dispsent 0 b_ o_ d_ y_ Dot 0xFF

GRAVITY_description:
dispsent I_ n_ t_ e_ n_ s_ i_ f_ i_ e_ s_ 0 t_ h_ e_ 0 g_ r_ a_ v_ i_ t_ y_ 0 a_ n_ d_ 0xFE
dispsent r_ e_ m_ o_ v_ e_ s_ 0 i_ m_ m_ u_ n_ i_ t_ y_ 0 t_ o_ 0 g_ r_ o_ u_ n_ d_ Dot 0xFF

MIRACLE_EYE_description:
dispsent E_ n_ a_ b_ l_ e_ s_ 0 P_ s_ y_ c_ h_ i_ c_ 0 t_ o_ 0 h_ i_ t_ 0 D_ a_ r_ k_ 0xFE
dispsent t_ y_ p_ e_ s_ Dot 0 R_ e_ m_ o_ v_ e_ s_ 0 t_ h_ e_ 0 e_ v_ a_ s_ i_ o_ n_ Dot 0xFF

WAKE_UP_SLAP_description:
dispsent P_ o_ w_ e_ r_ f_ u_ l_ 0 a_ g_ a_ i_ n_ s_ t_ 0 a_ s_ l_ e_ e_ p_ 0xFE
dispsent f_ o_ e_ s_ Comma 0 b_ u_ t_ 0 a_ l_ s_ o_ 0 h_ e_ a_ l_ s_ 0 t_ h_ e_ m_ Dot 0xFF

HAMMER_ARM_description:
dispsent A_ 0 s_ t_ r_ o_ n_ g_ 0 a_ n_ d_ 0 h_ e_ a_ v_ y_ 0 f_ i_ s_ t_ 0xFE t_ h_ a_ t_ 0
dispsent l_ o_ w_ e_ r_ s_ 0 s_ p_ e_ e_ d_ Dot 0xFF

GYRO_BALL_description:
dispsent D_ e_ a_ l_ s_ 0 g_ r_ e_ a_ t_ 0 d_ a_ m_ a_ g_ e_ 0 i_ f_ 0 t_ h_ e_ 0xFE
dispsent u_ s_ e_ r_ 0 i_ s_ 0 s_ l_ o_ w_ e_ r_ 0 t_ h_ a_ n_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

HEALING_WISH_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

BRINE_description:
dispsent D_ e_ a_ l_ s_ 0 d_ o_ u_ b_ l_ e_ 0 d_ a_ m_ a_ g_ e_ 0 w_ h_ e_ n_ 0xFE
dispsent t_ a_ r_ g_ e_ t_ Apos s_ 0 H_ P_ 0 i_ s_ 0 h_ a_ l_ f_ 0 o_ r_ 0 l_ e_ s_ s_ Dot 0xFF

NATURAL_GIFT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ r_ a_ w_ s_ 0 p_ o_ w_ e_ r_ 0 t_ o_ 0xFE
dispsent a_ t_ t_ a_ c_ k_ 0 u_ s_ i_ n_ g_ 0 i_ t_ 0 h_ e_ l_ d_ 0 B_ e_ r_ r_ y_ Dot 0xFF

FEINT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

PLUCK_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

TAILWIND_description:
dispsent W_ h_ i_ p_ s_ 0 u_ p_ 0 a_ 0 t_ u_ r_ b_ u_ l_ e_ n_ t_ 0 s_ w_ i_ r_ l_ 0xFE
dispsent t_ h_ a_ t_ 0 u_ p_ s_ 0 t_ e_ a_ m_ Apos s_ 0 s_ p_ e_ e_ d_ Dot 0xFF

ACUPRESSURE_description:
dispsent P_ r_ e_ s_ s_ u_ r_ e_ s_ 0 s_ t_ r_ e_ s_ s_ 0 p_ o_ i_ n_ t_ s_ 0xFE
dispsent s_ h_ a_ r_ p_ l_ y_ 0 b_ o_ o_ s_ t_ i_ n_ g_ 0 a_ 0 s_ t_ a_ t_ Dot 0xFF

METAL_BURST_description:
dispsent R_ e_ t_ a_ l_ i_ a_ t_ e_ s_ 0 a_ n_ y_ 0 h_ i_ t_ 0 w_ i_ t_ h_ 0xFE
dispsent m_ o_ r_ e_ 0 p_ o_ w_ e_ r_ 0 Dot 0xFF

UTURN_description:
dispsent A_ t_ t_ a_ c_ k_ s_ 0 a_ n_ d_ 0 t_ h_ e_ n_ 0 s_ w_ i_ t_ c_ h_ e_ s_ 0xFE p_ l_ a_ c_ e_ 0 w_
dispsent i_ t_ h_ 0 a_ 0 p_ a_ r_ t_ y_ 0 m_ e_ m_ b_ e_ r_ Dot 0xFF

CLOSE_COMBAT_description:
dispsent F_ i_ g_ h_ t_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 i_ n_ 0 c_ l_ o_ s_ e_ 0xFE
dispsent w_ i_ t_ h_ o_ u_ t_ 0 g_ u_ a_ r_ d_ i_ n_ g_ 0 i_ t_ s_ e_ l_ f_ Dot 0xFF

PAYBACK_description:
dispsent P_ o_ w_ e_ r_ 0 i_ s_ 0 d_ o_ u_ b_ l_ e_ d_ 0 i_ f_ 0 t_ h_ e_ 0xFE
dispsent u_ s_ e_ r_ 0 m_ o_ v_ e_ s_ 0 a_ f_ t_ e_ r_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

ASSURANCE_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

EMBARGO_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

FLING_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

PSYCHO_SHIFT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

TRUMP_CARD_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

HEAL_BLOCK_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

WRING_OUT_description:
dispsent P_ o_ w_ e_ r_ f_ u_ l_ l_ y_ 0 w_ r_ i_ n_ g_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE 
dispsent i_ f_ 0 i_ t_ s_ 0 H_ P_ 0 a_ r_ e_ 0 h_ i_ g_ h_ Dot 0xFF

POWER_TRICK_description:
dispsent U_ s_ e_ s_ 0 p_ s_ y_ c_ h_ i_ c_ 0 p_ o_ w_ e_ r_ 0 t_ o_ 0xFE
dispsent s_ w_ i_ t_ c_ h_ 0 A_ t_ t_ a_ c_ k_ 0 a_ n_ d_ 0 D_ e_ f_ e_ n_ s_ e_ Dot 0xFF

GASTRO_ACID_description:
dispsent A_ f_ f_ l_ i_ c_ t_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 w_ i_ t_ h_ 0xFE
dispsent m_ u_ c_ u_ s_ Comma 0 r_ e_ m_ o_ v_ e_ s_ 0 i_ t_ s_ 0 a_ b_ i_ l_ i_ t_ y_ Dot 0xFF

LUCKY_CHANT_description:
dispsent P_ r_ e_ v_ e_ n_ t_ s_ 0 c_ r_ i_ t_ i_ c_ a_ l_ 0 h_ i_ t_ s_ 0 f_ r_ o_ m_ 0xFE
dispsent l_ a_ n_ d_ i_ n_ g_ 0 o_ n_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 t_ e_ a_ m_ Dot 0xFF

ME_FIRST_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

COPYCAT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

POWER_SWAP_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

GUARD_SWAP_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

PUNISHMENT_description:
dispsent T_ h_ e_ 0 m_ o_ v_ e_ Apos s_ 0 p_ o_ w_ e_ r_ 0 i_ s_ 0 g_ r_ e_ a_ t_ e_ r_ 0xFE
dispsent w_ h_ e_ n_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 i_ s_ 0 b_ o_ o_ s_ t_ e_ d_ Dot 0xFF

LAST_RESORT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

WORRY_SEED_description:
dispsent A_ f_ f_ l_ i_ c_ t_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent s_ l_ e_ e_ p_ n_ e_ s_ s_ 0 c_ o_ n_ d_ i_ t_ i_ o_ n_ Dot 0xFF

SUCKER_PUNCH_description:
dispsent T_ h_ e_ 0 m_ o_ v_ e_ 0 f_ a_ i_ l_ s_ 0 i_ f_ 0 t_ h_ e_ 0xFE t_ a_ r_ g_ e_ t_ 0 i_ s_
dispsent 0 n_ o_ t_ 0 a_ t_ t_ a_ c_ k_ i_ n_ g_ Dot 0xFF

TOXIC_SPIKES_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

HEART_SWAP_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

AQUA_RING_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

MAGNET_RISE_description:
dispsent M_ a_ k_ e_ s_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0 l_ e_ v_ i_ t_ a_ t_ e_ 0xFE
dispsent w_ i_ t_ h_ 0 e_ l_ e_ c_ t_ r_ o_ m_ a_ g_ n_ e_ t_ i_ s_ m_ Dot 0xFF

FLARE_BLITZ_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ l_ o_ a_ k_ s_ 0 i_ t_ s_ e_ l_ f_ 0xFE i_ n_ 0 f_ i_ r_ e_ 0
dispsent a_ n_ d_ 0 c_ h_ a_ r_ g_ e_ s_ Dot 0xFF

FORCE_PALM_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 i_ s_ 0 a_ t_ t_ a_ c_ k_ e_ d_ 0xFE
dispsent w_ i_ t_ h_ 0 a_ 0 s_ h_ o_ c_ k_ 0 w_ a_ v_ e_ Dot 0xFF

AURA_SPHERE_description:
dispsent A_ 0 b_ l_ a_ s_ t_ 0 o_ f_ 0 a_ u_ r_ a_ 0 f_ r_ o_ m_ 0xFE
dispsent d_ e_ e_ p_ 0 w_ i_ t_ h_ i_ n_ Dot 0xFF

ROCK_POLISH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 p_ o_ l_ i_ s_ h_ e_ s_ 0 i_ t_ s_ 0 b_ o_ d_ y_ 0xFE
dispsent t_ o_ 0 r_ e_ d_ u_ c_ e_ 0 d_ r_ a_ g_ Dot 0xFF

POISON_JAB_description:
dispsent A_ 0 t_ e_ n_ t_ a_ c_ l_ e_ 0 o_ r_ 0 a_ r_ m_ 0xFE
dispsent s_ t_ e_ e_ p_ e_ d_ 0 i_ n_ 0 p_ o_ i_ s_ o_ n_ Dot 0xFF

DARK_PULSE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 r_ e_ l_ e_ a_ s_ e_ s_ 0xFE
dispsent h_ o_ r_ r_ i_ b_ l_ e_ 0 d_ a_ r_ k_ 0 t_ h_ o_ u_ g_ h_ t_ s_ Dot 0xFF

NIGHT_SLASH_description:
dispsent S_ l_ a_ s_ h_ e_ s_ 0 t_ h_ e_ 0 t_ r_ a_ g_ e_ t_ 0 w_ h_ i_ l_ e_ 0 i_ t_ s_ 0xFE
dispsent a_ t_ t_ e_ n_ t_ i_ o_ n_ 0 i_ s_ 0 d_ i_ v_ e_ r_ t_ e_ d_ Dot 0xFF

AQUA_TAIL_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ w_ i_ n_ g_ s_ 0 i_ t_ s_ 0 t_ a_ i_ l_ s_ 0xFE
dispsent l_ i_ k_ e_ 0 a_ 0 w_ a_ v_ e_ 0 i_ n_ 0 a_ 0 s_ t_ o_ r_ m_ Dot 0xFF

SEED_BOMB_description:
dispsent S_ l_ a_ m_ s_ 0 a_ 0 b_ a_ r_ r_ a_ g_ e_ 0 o_ f_ 0 h_ a_ r_ d_ Dash 0xFE
dispsent s_ h_ e_ l_ l_ e_ d_ 0 s_ e_ e_ d_ s_ 0 o_ n_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

AIR_SLASH_description:
dispsent A_ 0 b_ l_ a_ d_ e_ 0 o_ f_ 0 a_ i_ r_ 0 t_ h_ a_ t_ 0xFE
dispsent s_ l_ i_ c_ e_ s_ 0 e_ v_ e_ n_ 0 t_ h_ e_ 0 s_ k_ y_ Dot 0xFF

XSCISSOR_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ l_ a_ s_ h_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE
dispsent b_ y_ 0 c_ r_ o_ s_ s_ i_ n_ g_ 0 i_ t_ s_ 0 s_ c_ y_ t_ h_ e_ s_ Dot 0xFF

BUG_BUZZ_description:
dispsent V_ i_ b_ r_ a_ t_ e_ s_ 0 i_ t_ s_ 0 w_ i_ n_ g_ s_ 0 t_ o_ 0xFE
dispsent g_ e_ n_ e_ r_ a_ t_ e_ 0 a_ 0 s_ o_ u_ n_ d_ 0 w_ a_ v_ e_ Dot 0xFF

DRAGON_PULSE_description:
dispsent A_ 0 s_ h_ o_ c_ k_ 0 w_ a_ v_ e_ 0 g_ e_ n_ e_ r_ a_ t_ e_ d_ 0 b_ y_ 0xFE
dispsent t_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 g_ a_ p_ i_ n_ g_ 0 m_ o_ u_ t_ h_ Dot 0xFF

DRAGON_RUSH_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

POWER_GEM_description:
dispsent T_ h_ e_ 0 S_ p_ a_ r_ k_ l_ e_ s_ 0 l_ o_ o_ k_ 0xFE
dispsent s_ i_ m_ i_ l_ a_ r_ 0 t_ o_ 0 g_ e_ m_ s_ t_ o_ n_ e_ s_ Dot 0xFF

DRAIN_PUNCH_description:
dispsent A_ n_ 0 e_ n_ e_ r_ g_ y_ Dash d_ r_ a_ i_ n_ i_ n_ g_ 0 p_ u_ n_ c_ h_ Dot 0xFF

VACUUM_WAVE_description:
dispsent A_ 0 w_ a_ v_ e_ 0 o_ f_ 0 p_ u_ r_ e_ 0 v_ a_ c_ u_ u_ m_ 0xFE
dispsent t_ h_ r_ o_ u_ g_ h_ 0 a_ 0 f_ i_ s_ t_ 0 w_ h_ i_ r_ l_ Dot 0xFF

FOCUS_BLAST_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 u_ n_ l_ e_ a_ s_ h_ e_ s_ 0xFE
dispsent s_ t_ r_ o_ n_ g_ 0 m_ e_ n_ t_ a_ l_ 0 p_ o_ w_ e_ r_ Dot 0xFF

ENERGY_BALL_description:
dispsent D_ r_ a_ w_ s_ 0 p_ o_ w_ e_ r_ 0 f_ r_ o_ m_ 0 n_ a_ t_ u_ r_ e_ 0xFE
dispsent a_ n_ d_ 0 f_ i_ r_ e_ s_ 0 i_ t_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

BRAVE_BIRD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ h_ a_ r_ g_ e_ s_ 0 f_ r_ o_ m_ 0 a_ 0xFE
dispsent l_ o_ w_ 0 a_ l_ t_ i_ t_ u_ d_ e_ Dot 0xFF

EARTH_POWER_description:
dispsent G_ r_ o_ u_ n_ d_ 0 u_ n_ d_ e_ r_ 0 t_ h_ e_ 0 f_ o_ e_ 0 a_ n_ d_ 0xFE
dispsent e_ r_ u_ p_ t_ s_ 0 w_ i_ t_ h_ 0 p_ o_ w_ e_ r_ Dot 0xFF

SWITCHEROO_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

GIGA_IMPACT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

NASTY_PLOT_description:
dispsent S_ t_ i_ m_ u_ l_ a_ t_ e_ s_ 0 i_ t_ s_ 0 b_ r_ a_ i_ n_ 0 b_ y_ 0xFE
dispsent t_ h_ i_ n_ k_ i_ n_ g_ 0 b_ a_ d_ 0 t_ h_ o_ u_ g_ h_ t_ s_ Dot 0xFF

BULLET_PUNCH_description:
dispsent A_ 0 t_ o_ u_ g_ h_ 0 p_ u_ n_ c_ h_ 0 a_ s_ 0xFE
dispsent f_ a_ s_ t_ 0 a_ s_ 0 a_ 0 b_ u_ l_ l_ e_ t_ Dot 0xFF

AVALANCHE_description:
dispsent A_ n_ 0 a_ t_ t_ a_ c_ k_ 0 t_ h_ a_ t_ 0 g_ a_ i_ n_ s_ 0 p_ o_ w_ e_ r_ 0xFE
dispsent i_ f_ 0 i_ n_ j_ u_ r_ e_ d_ 0 b_ y_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

ICE_SHARD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 h_ u_ r_ l_ s_ 0 c_ h_ u_ n_ k_ s_ 0xFE
dispsent o_ f_ 0 i_ c_ e_ 0 o_ n_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

SHADOW_CLAW_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ l_ a_ s_ h_ e_ s_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent s_ h_ a_ r_ p_ 0 c_ l_ a_ w_ 0 m_ a_ d_ e_ 0 o_ f_ 0 s_ h_ a_ d_ o_ w_ s_ Dot 0xFF

THUNDER_FANG_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ i_ t_ e_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent e_ l_ e_ c_ t_ r_ i_ f_ i_ e_ d_ 0 f_ a_ n_ g_ s_ Dot 0xFF

ICE_FANG_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ i_ t_ e_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent c_ o_ l_ d_ Dash i_ n_ f_ u_ s_ e_ d_ 0 f_ a_ n_ g_ s_ Dot 0xFF

FIRE_FANG_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ i_ t_ e_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent f_ l_ a_ m_ e_ Dash c_ l_ o_ a_ k_ e_ d_ 0 f_ a_ n_ g_ s_ Dot 0xFF

SHADOW_SNEAK_description:
dispsent E_ x_ t_ e_ n_ d_ s_ 0 i_ t_ s_ 0 s_ h_ a_ d_ o_ w_ 0 t_ o_ 0xFE
dispsent a_ t_ t_ a_ c_ k_ 0 t_ h_ e_ 0 f_ o_ e_ 0 f_ r_ o_ m_ 0 b_ e_ h_ i_ n_ d_ Dot 0xFF

MUD_BOMB_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

PSYCHO_CUT_description:
dispsent T_ e_ a_ r_ s_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0 b_ l_ a_ d_ e_ s_ 0xFE
dispsent f_ o_ r_ m_ e_ d_ 0 b_ y_ 0 p_ s_ y_ c_ h_ i_ c_ 0 p_ o_ w_ e_ r_ Dot 0xFF

ZEN_HEADBUTT_description:
dispsent A_ 0 h_ e_ a_ d_ b_ u_ t_ t_ 0 m_ a_ d_ e_ 0 o_ f_ 0xFE
dispsent s_ t_ r_ o_ n_ g_ 0 w_ i_ l_ l_ p_ o_ w_ e_ r_ Dot 0xFF

MIRROR_SHOT_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

FLASH_CANNON_description:
dispsent G_ a_ t_ h_ e_ r_ s_ 0 l_ i_ g_ h_ t_ 0 e_ n_ e_ r_ g_ y_ 0 a_ n_ d_ 0xFE
dispsent r_ e_ l_ e_ a_ s_ e_ s_ 0 i_ t_ 0 a_ t_ 0 o_ n_ c_ e_ Dot 0xFF

ROCK_CLIMB_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

DEFOG_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

TRICK_ROOM_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

DRACO_METEOR_description:
dispsent C_ o_ m_ e_ t_ s_ 0 a_ r_ e_ 0 s_ u_ m_ m_ o_ n_ e_ d_ 0 d_ o_ w_ n_ 0xFE
dispsent f_ r_ o_ m_ 0 t_ h_ e_ 0 s_ k_ y_ Dot 0xFF

DISCHARGE_description:
dispsent S_ t_ r_ i_ k_ e_ s_ 0 b_ y_ 0 l_ e_ t_ t_ i_ n_ g_ 0 l_ o_ o_ s_ e_ 0xFE
dispsent a_ 0 f_ l_ a_ r_ e_ 0 o_ f_ 0 e_ l_ e_ c_ t_ r_ i_ c_ i_ t_ y_ Dot 0xFF

LAVA_PLUME_description:
dispsent S_ c_ a_ r_ l_ e_ t_ 0 f_ l_ a_ m_ e_ s_ 0 t_ o_ r_ c_ h_ e_ s_ 0xFE
dispsent e_ v_ e_ r_ y_ t_ h_ i_ n_ g_ 0 a_ r_ o_ u_ n_ d_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Dot 0xFF

LEAF_STORM_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

POWER_WHIP_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 v_ i_ o_ l_ e_ n_ t_ l_ y_ 0 w_ h_ i_ r_ l_ s_ 0xFE
dispsent i_ t_ s_ 0 v_ i_ n_ e_ s_ 0 o_ r_ 0 t_ e_ n_ t_ a_ c_ l_ e_ s_ Dot 0xFF

ROCK_WRECKER_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 l_ a_ u_ n_ c_ h_ e_ s_ 0 a_ 0 h_ u_ g_ e_ 0xFE
dispsent b_ o_ u_ l_ d_ e_ r_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

CROSS_POISON_description:
dispsent A_ 0 s_ l_ a_ s_ h_ i_ n_ g_ 0 a_ t_ t_ a_ c_ k_ 0 t_ h_ a_ t_ 0xFE
dispsent m_ a_ y_ 0 p_ o_ i_ s_ o_ n_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF

GUNK_SHOT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ h_ o_ o_ t_ s_ 0 f_ i_ l_ t_ h_ y_ 0xFE
dispsent g_ a_ r_ b_ a_ g_ e_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

IRON_HEAD_description:
dispsent S_ l_ a_ m_ s_ 0 i_ t_ s_ 0 t_ a_ r_ g_ e_ t_ s_ 0 w_ i_ t_ h_ 0 i_ t_ s_ 0xFE
dispsent s_ t_ e_ e_ l_ Dash h_ a_ r_ d_ 0 h_ e_ a_ d_ Dot 0xFF

MAGNET_BOMB_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 l_ a_ u_ n_ c_ h_ e_ s_ 0 a_ 0 s_ t_ e_ e_ l_ 0xFE
dispsent b_ o_ m_ b_ 0 t_ h_ a_ t_ 0 n_ e_ v_ e_ r_ 0 m_ i_ s_ s_ e_ s_ Dot 0xFF

STONE_EDGE_description:
dispsent S_ t_ a_ b_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent s_ h_ a_ r_ p_ e_ n_ e_ d_ 0 s_ t_ o_ n_ e_ Dot 0xFF
CAPTIVATE_description:
dispsent I_ f_ 0 t_ h_ e_ 0 f_ o_ e_ 0 i_ s_ 0 o_ p_ p_ o_ s_ i_ t_ e_ 0 s_ e_ x_ Comma 0xFE
dispsent i_ t_ 0 i_ s_ 0 c_ h_ a_ r_ m_ e_ d_ Comma 0 l_ o_ w_ e_ r_ i_ n_ g_ 0 S_ p_ Dot A_ 0xFF

STEALTH_ROCK_description:
dispsent S_ t_ o_ n_ e_ s_ 0 a_ r_ e_ 0 l_ a_ i_ d_ 0 o_ u_ t_ 0 t_ o_ 0 h_ u_ r_ t_ 0xFE
dispsent f_ o_ e_ s_ 0 s_ w_ i_ t_ c_ h_ e_ d_ 0 i_ n_ t_ o_ 0 b_ a_ t_ t_ l_ e_ Dot 0xFF

GRASS_KNOT_description:
dispsent H_ e_ a_ v_ i_ e_ r_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 i_ s_ Comma 0xFE
dispsent g_ r_ e_ a_ t_ e_ r_ 0 t_ h_ e_ 0 m_ o_ v_ e_ Apos s_ 0 p_ o_ w_ e_ r_ Dot 0xFF

CHATTER_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent c_ h_ a_ t_ t_ e_ r_ Dot 0 C_ o_ n_ f_ u_ s_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

JUDGMENT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 r_ e_ l_ e_ a_ s_ e_ s_ 0 s_ h_ o_ t_ s_ 0 o_ f_ 0xFE
dispsent l_ i_ g_ h_ t_ Comma 0 b_ a_ s_ e_ d_ 0 o_ n_ 0 h_ e_ l_ d_ 0 P_ l_ a_ t_ e_ Dot 0xFF

BUG_BITE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ i_ t_ e_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFE
dispsent E_ a_ t_ s_ 0 a_ n_ y_ 0 h_ e_ l_ d_ 0 i_ t_ e_ m_ Dot 0xFF

CHARGE_BEAM_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent c_ h_ a_ r_ g_ e_ Dot 0 M_ a_ y_ 0 r_ a_ i_ s_ e_ 0 S_ p_ Dot 0 A_ t_ k_ Dot 0xFF

WOOD_HAMMER_description:
dispsent A_ 0 s_ t_ r_ o_ n_ g_ 0 a_ n_ d_ 0 h_ e_ a_ v_ y_ 0 f_ i_ s_ t_ 0xFE
dispsent t_ h_ a_ t_ 0 l_ o_ w_ e_ r_ s_ 0 s_ p_ e_ e_ d_ Dot 0xFF

AQUA_JET_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ w_ i_ f_ t_ l_ y_ 0xFE
dispsent l_ u_ n_ g_ e_ s_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

ATTACK_ORDER_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 u_ n_ d_ e_ r_ l_ i_ n_ g_ s_ 0 p_ u_ m_ m_ e_ l_ 0xFE
dispsent t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0 M_ a_ y_ 0 b_ e_ 0 c_ r_ i_ t_ i_ c_ a_ l_ Dot 0xFF

DEFEND_ORDER_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 u_ n_ d_ e_ r_ l_ i_ n_ g_ s_ 0 m_ a_ k_ e_ 0 a_ 0xFE
dispsent s_ h_ i_ e_ l_ d_ Comma 0 r_ a_ i_ s_ i_ n_ g_ 0 D_ e_ f_ 0 a_ n_ d_ 0 S_ p_ Dot D_ 0xFF

HEAL_ORDER_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 u_ n_ d_ e_ r_ l_ i_ n_ g_ s_ 0 h_ e_ a_ l_ 0xFE
dispsent i_ t_ 0 u_ p_ 0 t_ o_ 0 h_ a_ l_ f_ 0 o_ f_ 0 i_ t_ s_ 0 m_ a_ x_ 0 H_ P_ Dot 0xFF

HEAD_SMASH_description:
dispsent A_ 0 l_ i_ f_ e_ Dash e_ n_ d_ a_ n_ g_ e_ r_ i_ n_ g_ 0 h_ e_ a_ d_ 0 b_ u_ t_ t_ 0xFE
dispsent a_ t_ 0 f_ u_ l_ l_ 0 p_ o_ w_ e_ r_ Dot 0xFF

DOUBLE_HIT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ l_ a_ m_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE
dispsent t_ w_ i_ c_ e_ Dot 0xFF

ROAR_OF_TIME_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ l_ a_ s_ t_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0xFE
dispsent p_ o_ w_ e_ r_ 0 t_ h_ a_ t_ 0 d_ i_ s_ t_ o_ r_ t_ s_ 0 t_ i_ m_ e_ Dot 0xFF

SPACIAL_REND_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 t_ e_ a_ r_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 l_ o_ n_ g_ 0xFE
dispsent w_ i_ t_ h_ 0 t_ h_ e_ 0 s_ p_ a_ c_ e_ 0 a_ r_ o_ u_ n_ d_ 0 i_ t_ Dot 0xFF

LUNAR_DANCE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 f_ a_ i_ n_ t_ s_ 0 t_ o_ 0xFE
dispsent r_ e_ s_ t_ o_ r_ e_ 0 a_ n_ 0 a_ l_ l_ y_ Dot 0xFF

CRUSH_GRIP_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF

MAGMA_STORM_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 b_ e_ c_ o_ m_ e_ s_ 0 t_ r_ a_ p_ p_ e_ d_ 0xFE
dispsent w_ i_ t_ h_ i_ n_ 0 a_ 0 m_ a_ e_ l_ s_ t_ r_ o_ m_ 0 o_ f_ 0 f_ i_ r_ e_ Dot 0xFF

DARK_VOID_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 i_ s_ 0 d_ r_ a_ g_ g_ e_ d_ 0 i_ n_ t_ o_ 0 a_ 0xFE
dispsent w_ o_ r_ l_ d_ 0 o_ f_ 0 t_ o_ t_ a_ l_ 0 d_ a_ r_ k_ n_ e_ s_ s_ Dot 0xFF

SEED_FLARE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 g_ e_ n_ e_ r_ a_ t_ e_ s_ 0 a_ 0 s_ h_ o_ c_ k_ Dash 0xFE
dispsent w_ a_ v_ e_ 0 f_ r_ o_ m_ 0 w_ i_ t_ h_ i_ n_ 0 i_ t_ s_ 0 b_ o_ d_ y_ Dot 0xFF

OMINOUS_WIND_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ r_ e_ a_ t_ e_ s_ 0 a_ 0 r_ e_ p_ u_ l_ s_ i_ v_ e_ 0xFE
dispsent w_ i_ n_ d_ Dot 0 M_ a_ y_ 0 r_ i_ s_ e_ 0 a_ l_ l_ 0 s_ t_ a_ t_ s_ Dot 0xFF

SHADOW_FORCE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ i_ s_ a_ p_ p_ e_ a_ r_ s_ Comma 0 s_ t_ r_ i_ k_ e_ s_ 0xFE
dispsent t_ h_ e_ 0 f_ o_ e_ 0 o_ n_ 0 t_ h_ e_ 0 s_ e_ c_ o_ n_ d_ 0 t_ u_ r_ n_ Dot 0xFF

HONE_CLAWS_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ h_ a_ r_ p_ e_ n_ s_ 0 i_ t_ s_ 0 c_ l_ a_ w_ s_ 0xFE
dispsent t_ o_ 0 r_ a_ i_ s_ e_ 0 A_ t_ k_ 0 a_ n_ d_ 0 a_ c_ c_ u_ r_ a_ c_ y_ Dot 0xFF

WIDE_GUARD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ n_ d_ 0 a_ l_ l_ i_ e_ s_ 0 a_ r_ e_ 0xFE
dispsent p_ r_ o_ t_ e_ c_ t_ e_ d_ 0 f_ r_ o_ m_ 0 w_ i_ d_ e_ 0 a_ t_ t_ a_ c_ k_ s_ Dot 0xFF

GUARD_SPLIT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ v_ e_ r_ a_ g_ e_ s_ 0 i_ t_ s_ 0 D_ e_ f_ 0xFE
dispsent a_ n_ d_ 0 S_ p_ Dot D_ 0 s_ t_ a_ t_ s_ 0 w_ i_ t_ h_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

POWER_SPLIT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ v_ e_ r_ a_ g_ e_ s_ 0 i_ t_ s_ 0 A_ t_ k_ 0xFE
dispsent a_ n_ d_ 0 S_ p_ Dot A_ 0 s_ t_ a_ t_ s_ 0 w_ i_ t_ h_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

WONDER_ROOM_description:
dispsent T_ h_ e_ 0 D_ e_ f_ 0 a_ n_ d_ 0 S_ p_ Dot 0 D_ e_ f_ 0 s_ t_ a_ t_ s_ 0xFE
dispsent a_ r_ e_ 0 s_ w_ a_ p_ p_ e_ d_ 0 f_ o_ r_ 0 f_ i_ v_ e_ 0 t_ u_ r_ n_ s_ Dot 0xFF

PSYSHOCK_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 m_ a_ t_ e_ r_ i_ a_ l_ i_ z_ e_ s_ 0 a_ n_ 0 o_ d_ d_ 0xFE
dispsent p_ s_ y_ c_ h_ i_ c_ 0 w_ a_ v_ e_ 0 f_ o_ r_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

VENOSHOCK_description:
dispsent I_ f_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 i_ s_ 0 p_ o_ i_ s_ o_ n_ e_ d_ Comma 0xFE
dispsent d_ o_ u_ b_ l_ e_ s_ 0 t_ h_ e_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

AUTOTOMIZE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ h_ e_ d_ s_ 0 p_ a_ r_ t_ 0 o_ f_ 0 i_ t_ s_ 0xFE
dispsent b_ o_ d_ y_ Comma 0 r_ a_ i_ s_ i_ n_ g_ 0 i_ t_ s_ 0 S_ p_ e_ e_ d_ Dot 0xFF

RAGE_POWDER_description:
dispsent F_ o_ e_ s_ 0 a_ i_ m_ 0 t_ o_ 0 a_ t_ t_ a_ c_ k_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0xFE
dispsent o_ n_ l_ y_ Dot 0xFF

TELEKINESIS_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 f_ l_ o_ a_ t_ s_ 0 f_ o_ r_ 0 t_ h_ r_ e_ e_ 0xFE
dispsent t_ u_ r_ n_ s_ Comma 0 e_ a_ s_ i_ e_ r_ 0 t_ o_ 0 h_ i_ t_ Dot 0xFF

MAGIC_ROOM_description:
dispsent U_ s_ e_ r_ 0 d_ i_ s_ a_ b_ l_ e_ s_ 0 t_ h_ e_ 0 u_ s_ e_ 0 o_ f_ 0xFE
dispsent h_ e_ l_ d_ 0 i_ t_ e_ m_ s_ 0 f_ o_ r_ 0 f_ i_ v_ e_ 0 t_ u_ r_ n_ s_ Dot 0xFF

SMACK_DOWN_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 t_ h_ r_ o_ w_ s_ 0 a_ 0 s_ t_ o_ n_ e_ Dot 0xFE
dispsent G_ r_ o_ u_ n_ d_ s_ 0 a_ 0 f_ l_ y_ i_ n_ g_ 0 P_ o_ k_ Poke_e m_ o_ n_ Dot 0xFF

STORM_THROW_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ t_ r_ i_ k_ e_ s_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent f_ i_ e_ r_ c_ e_ 0 c_ r_ i_ t_ i_ c_ a_ l_ 0 h_ i_ t_ Dot 0xFF

FLAME_BURST_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0xFE
dispsent b_ u_ r_ s_ t_ i_ n_ g_ 0 f_ l_ a_ m_ e_ Dot 0xFF

SLUDGE_WAVE_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0 s_ l_ u_ d_ g_ e_ 0xFE
dispsent w_ a_ v_ e_ Dot 0 M_ a_ y_ 0 p_ o_ i_ s_ o_ n_ 0 t_ a_ r_ g_ e_ t_ s_ Dot 0xFF

QUIVER_DANCE_description:
dispsent A_ 0 b_ e_ a_ u_ t_ i_ f_ u_ l_ 0 a_ n_ d_ 0 m_ y_ s_ t_ i_ c_ 0xFE
dispsent d_ a_ n_ c_ e_ Dot 0xFF

HEAVY_SLAM_description:
dispsent U_ s_ e_ r_ 0 s_ l_ a_ m_ s_ 0 i_ n_ t_ o_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFE
dispsent G_ r_ e_ a_ t_ e_ r_ 0 w_ e_ i_ g_ h_ t_ Comma 0 m_ o_ r_ e_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

SYNCHRONOISE_description:
dispsent U_ s_ e_ r_ 0 i_ n_ f_ l_ i_ c_ t_ s_ 0 d_ a_ m_ a_ g_ e_ 0 o_ n_ 0 f_ o_ e_ s_ 0xFE
dispsent w_ i_ t_ h_ 0 t_ h_ e_ 0 s_ a_ m_ e_ 0 t_ y_ p_ e_ Dot 0xFF

ELECTRO_BALL_description:
dispsent T_ h_ e_ 0 f_ a_ s_ t_ e_ r_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0 i_ s_ 0 t_ h_ a_ n_ 0xFE
dispsent t_ h_ e_ 0 f_ o_ e_ Comma 0 g_ r_ e_ a_ t_ e_ r_ 0 t_ h_ e_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

SOAK_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ h_ a_ n_ g_ e_ s_ 0 t_ h_ e_ 0xFE
dispsent t_ a_ r_ g_ e_ t_ Apos s_ 0 t_ y_ p_ e_ 0 t_ o_ 0 W_ a_ t_ e_ r_ Dot 0xFF

FLAME_CHARGE_description:
dispsent C_ l_ o_ a_ k_ s_ 0 i_ t_ s_ e_ l_ f_ 0 i_ n_ 0 f_ l_ a_ m_ e_ s_ 0xFE
dispsent a_ n_ d_ 0 a_ t_ t_ a_ c_ k_ s_ Dot 0xFF

COIL_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ o_ i_ l_ s_ 0 u_ p_ 0xFE
dispsent a_ n_ d_ 0 c_ o_ n_ c_ e_ n_ t_ r_ a_ t_ e_ s_ Dot 0xFF

LOW_SWEEP_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 t_ a_ r_ g_ e_ t_ s_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0xFE
dispsent l_ e_ g_ s_ Comma 0 r_ e_ d_ u_ c_ i_ n_ g_ 0 i_ t_ s_ 0 S_ p_ e_ e_ d_ Dot 0xFF

ACID_SPRAY_description:
dispsent U_ s_ e_ r_ 0 s_ p_ i_ t_ s_ 0 f_ l_ u_ i_ d_ 0 t_ o_ 0 h_ a_ r_ s_ h_ l_ y_ 0xFE
dispsent l_ o_ w_ e_ r_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Apos s_ 0 S_ p_ Dot 0 D_ e_ f_ Dot 0xFF

FOUL_PLAY_description:
dispsent T_ h_ e_ 0 h_ i_ g_ h_ e_ r_ 0 t_ h_ e_ 0 e_ n_ e_ m_ y_ Apos s_ 0xFE
dispsent A_ t_ t_ a_ c_ k_ Comma 0 t_ h_ e_ 0 g_ r_ e_ a_ t_ e_ r_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

SIMPLE_BEAM_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ h_ a_ n_ g_ e_ s_ 0 t_ h_ e_ 0xFE
dispsent t_ a_ r_ g_ e_ t_ Apos s_ 0 A_ b_ i_ l_ i_ t_ y_ 0 t_ o_ 0 S_ i_ m_ p_ l_ e_ Dot 0xFF

ENTRAINMENT_description:
dispsent T_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Apos s_ 0 a_ b_ i_ l_ i_ t_ y_ 0 i_ s_ 0xFE
dispsent c_ h_ a_ n_ g_ e_ d_ 0 t_ o_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Apos s_ Dot 0xFF

AFTER_YOU_description:
dispsent H_ e_ l_ p_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 m_ o_ v_ e_ 0 r_ i_ g_ h_ t_ 0xFE
dispsent a_ f_ t_ e_ r_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Dot 0xFF

ROUND_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0 s_ o_ n_ g_ Dot 0xFE
dispsent O_ t_ h_ e_ r_ s_ 0 c_ a_ n_ 0 j_ o_ i_ n_ 0 f_ o_ r_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

ECHOED_VOICE_description:
dispsent A_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ n_ 0 e_ c_ h_ o_ i_ n_ g_ 0xFE
dispsent v_ o_ i_ c_ e_ Dot 0 G_ r_ e_ a_ t_ e_ r_ 0 e_ a_ c_ h_ 0 t_ u_ r_ n_ Dot 0xFF

CHIP_AWAY_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ t_ r_ i_ k_ e_ s_ 0 r_ e_ p_ e_ a_ t_ e_ d_ l_ y_ Comma 0xFE
dispsent w_ i_ t_ h_ o_ u_ t_ 0 r_ e_ g_ a_ r_ d_ 0 t_ o_ 0 s_ t_ a_ t_ s_ Dot 0xFF

CLEAR_SMOG_description:
dispsent U_ s_ e_ r_ 0 t_ h_ r_ o_ w_ s_ 0 a_ 0 c_ l_ u_ m_ p_ 0 o_ f_ 0 m_ u_ d_ Dot 0xFE
dispsent A_ l_ l_ 0 s_ t_ a_ t_ 0 c_ h_ a_ n_ g_ e_ s_ 0 a_ r_ e_ 0 r_ e_ s_ e_ t_ Dot 0xFF

STORED_POWER_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 s_ t_ o_ r_ e_ d_ 0xFE
dispsent p_ o_ w_ e_ r_ Comma 0 b_ a_ s_ e_ d_ 0 o_ n_ 0 r_ a_ i_ s_ e_ d_ 0 s_ t_ a_ t_ s_ Dot 0xFF

QUICK_GUARD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 p_ r_ o_ t_ e_ c_ t_ s_ 0 i_ t_ s_ e_ l_ f_ 0 a_ n_ d_ 0xFE
dispsent a_ l_ l_ i_ e_ s_ 0 f_ r_ o_ m_ 0 p_ r_ i_ o_ r_ i_ t_ y_ 0 m_ o_ v_ e_ s_ Dot 0xFF

ALLY_SWITCH_description:
dispsent U_ s_ e_ r_ 0 t_ e_ l_ e_ p_ o_ r_ t_ s_ 0 a_ n_ d_ 0 s_ w_ i_ t_ c_ h_ e_ s_ 0xFE
dispsent w_ i_ t_ h_ 0 o_ n_ e_ 0 o_ f_ 0 i_ t_ s_ 0 a_ l_ l_ i_ e_ s_ Dot 0xFF

SCALD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ h_ o_ o_ t_ s_ 0 b_ o_ i_ l_ i_ n_ g_ 0xFE
dispsent w_ a_ t_ e_ r_ 0 a_ t_ 0 i_ t_ s_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF

SHELL_SMASH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 b_ r_ e_ a_ k_ s_ 0 i_ t_ s_ 0 s_ h_ e_ l_ l_ 0xFE
dispsent a_ n_ d_ 0 t_ r_ a_ d_ e_ s_ 0 b_ u_ l_ k_ 0 f_ o_ r_ 0 p_ o_ w_ e_ r_ Dot 0xFF

HEAL_PULSE_description:
dispsent U_ s_ e_ r_ 0 e_ m_ i_ t_ s_ 0 a_ 0 h_ e_ a_ l_ i_ n_ g_ 0 p_ u_ l_ s_ e_ Comma 0xFE
dispsent r_ e_ s_ t_ o_ r_ i_ n_ g_ 0 u_ p_ 0 t_ o_ 0 h_ a_ l_ f_ 0 o_ f_ 0 H_ P_ Dot 0xFF

HEX_description:
dispsent D_ o_ e_ s_ 0 m_ a_ s_ s_ i_ v_ e_ 0 d_ a_ m_ a_ g_ e_ 0 t_ o_ 0 f_ o_ e_ s_ 0xFE
dispsent a_ f_ f_ e_ c_ t_ e_ d_ 0 b_ y_ 0 a_ 0 s_ t_ a_ t_ u_ s_ 0 e_ f_ f_ e_ c_ t_ Dot 0xFF

SKY_DROP_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 t_ a_ k_ e_ s_ 0 f_ o_ e_ 0 i_ n_ t_ o_ 0 t_ h_ e_ 0xFE
dispsent s_ k_ y_ 0 a_ n_ d_ 0 d_ r_ o_ p_ s_ 0 o_ n_ 0 n_ e_ x_ t_ 0 t_ u_ r_ n_ Dot 0xFF

SHIFT_GEAR_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 r_ o_ t_ a_ t_ e_ s_ 0 i_ t_ s_ 0 g_ e_ a_ r_ s_ Comma 0xFE
dispsent r_ a_ i_ s_ i_ n_ g_ 0 i_ t_ s_ 0 A_ t_ k_ 0 a_ n_ d_ 0 S_ p_ e_ e_ d_ Dot 0xFF

CIRCLE_THROW_description:
dispsent T_ a_ r_ g_ e_ t_ 0 i_ s_ 0 s_ w_ i_ t_ c_ h_ e_ d_ 0 o_ u_ t_ Dot 0 I_ n_ 0xFE
dispsent t_ h_ e_ 0 w_ i_ l_ d_ Comma 0 t_ h_ e_ 0 b_ a_ t_ t_ l_ e_ 0 i_ s_ 0 o_ v_ e_ r_ Dot 0xFF

INCINERATE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE
dispsent w_ i_ t_ h_ 0 a_ 0 d_ e_ v_ a_ s_ t_ a_ t_ i_ n_ g_ 0 f_ i_ r_ e_ Dot 0xFF

QUASH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ u_ p_ p_ r_ e_ s_ s_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE
dispsent a_ n_ d_ 0 m_ a_ k_ e_ s_ 0 i_ t_ s_ 0 m_ o_ v_ e_ 0 g_ o_ 0 l_ a_ s_ t_ Dot 0xFF

ACROBATICS_description:
dispsent I_ f_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0 i_ s_ n_ Apos t_ 0 h_ o_ l_ d_ i_ n_ g_ 0 a_ n_ 0xFE
dispsent i_ t_ e_ m_ Comma 0 t_ h_ e_ 0 a_ t_ t_ a_ c_ k_ 0 i_ s_ 0 m_ a_ s_ s_ i_ v_ e_ Dot 0xFF

REFLECT_TYPE_description:
dispsent I_ f_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0 i_ s_ n_ Apos t_ 0 h_ o_ l_ d_ i_ n_ g_ 0 a_ n_ 0xFE
dispsent i_ t_ e_ m_ Comma 0 t_ h_ e_ 0 a_ t_ t_ a_ c_ k_ 0 i_ s_ 0 m_ a_ s_ s_ i_ v_ e_ Dot 0xFF

RETALIATE_description:
dispsent I_ f_ 0 a_ n_ 0 a_ l_ l_ y_ 0 f_ a_ i_ n_ t_ e_ d_ 0 l_ a_ s_ t_ 0xFE
dispsent t_ u_ r_ n_ Comma 0 t_ h_ i_ s_ 0 m_ o_ v_ e_ Apos s_ 0 p_ o_ w_ e_ r_ f_ u_ l_ Dot 0xFF

FINAL_GAMBIT_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 f_ a_ i_ n_ t_ s_ 0 b_ u_ t_ 0 d_ o_ e_ s_ 0xFE
dispsent d_ a_ m_ a_ g_ e_ 0 e_ q_ u_ a_ l_ 0 t_ o_ 0 i_ t_ s_ 0 H_ P_ Dot 0xFF

BESTOW_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 p_ a_ s_ s_ e_ s_ 0 i_ t_ s_ 0 h_ e_ l_ d_ 0xFE
dispsent i_ t_ e_ m_ 0 t_ o_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF

INFERNO_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 e_ n_ g_ u_ l_ f_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0xFE
dispsent w_ i_ t_ h_ 0 f_ i_ r_ e_ Dot 0 L_ e_ a_ v_ e_ s_ 0 a_ 0 b_ u_ r_ n_ Dot 0xFF

WATER_PLEDGE_description:
dispsent A_ 0 c_ o_ l_ u_ m_ n_ 0 o_ f_ 0 w_ a_ t_ e_ r_ 0 s_ t_ r_ i_ k_ e_ s_ 0xFE
dispsent t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF

FIRE_PLEDGE_description:
dispsent A_ 0 c_ o_ l_ u_ m_ n_ 0 o_ f_ 0 f_ i_ r_ e_ 0 h_ i_ t_ s_ 0xFE
dispsent o_ p_ p_ o_ s_ i_ n_ g_ 0 P_ o_ k_ Poke_e m_ o_ n_ Dot 0xFF

GRASS_PLEDGE_description:
dispsent A_ 0 c_ o_ l_ u_ m_ n_ 0 o_ f_ 0 g_ r_ a_ s_ s_ 0 h_ i_ t_ s_ 0 t_ h_ e_ 0xFE
dispsent t_ a_ r_ g_ e_ t_ Dot 0xFF

VOLT_SWITCH_description:
dispsent A_ t_ t_ a_ c_ k_ s_ 0 a_ n_ d_ 0 t_ h_ e_ n_ 0 s_ w_ i_ t_ c_ h_ e_ s_ 0xFE
dispsent p_ l_ a_ c_ e_ 0 w_ i_ t_ h_ 0 a_ 0 p_ a_ r_ t_ y_ 0 m_ e_ m_ b_ e_ r_ Dot 0xFF

STRUGGLE_BUG_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ h_ i_ l_ e_ 0xFE
dispsent r_ e_ s_ i_ s_ t_ i_ n_ g_ Dot 0 L_ o_ w_ e_ r_ s_ 0 S_ p_ Dot 0 A_ t_ k_ Dot 0xFF

BULLDOZE_description:
dispsent S_ t_ o_ m_ p_ s_ 0 d_ o_ w_ n_ 0 o_ n_ 0 t_ h_ e_ 0 g_ r_ o_ u_ n_ d_ 0xFE
dispsent a_ n_ d_ 0 a_ t_ t_ a_ c_ k_ s_ 0 e_ v_ e_ r_ y_ t_ h_ i_ n_ g_ Dot 0xFF

FROST_BREATH_description:
dispsent U_ s_ e_ r_ 0 b_ l_ o_ w_ s_ 0 c_ o_ l_ d_ 0 b_ r_ e_ a_ t_ h_ 0 o_ n_ 0xFE
dispsent t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0 A_ l_ w_ a_ y_ s_ 0 c_ r_ i_ t_ s_ Dot 0xFF

DRAGON_TAIL_description:
dispsent T_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 i_ s_ 0 s_ w_ i_ t_ c_ h_ e_ d_ 0 o_ u_ t_ Dot 0xFE
dispsent I_ n_ 0 w_ i_ l_ d_ Comma 0 t_ h_ e_ 0 b_ a_ t_ t_ l_ e_ 0 e_ n_ d_ s_ Dot 0xFF

WORK_UP_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 i_ s_ 0 r_ o_ u_ s_ e_ d_ Comma 0 a_ n_ d_ 0 i_ t_ s_ 0xFE
dispsent A_ t_ t_ a_ c_ k_ 0 a_ n_ d_ 0 S_ p_ Dot 0 A_ t_ k_ 0 i_ n_ c_ r_ e_ a_ s_ e_ Dot 0xFF

ELECTROWEB_description:
dispsent F_ o_ e_ 0 i_ s_ 0 c_ a_ p_ t_ u_ r_ e_ d_ 0 i_ n_ 0 a_ n_ 0xFE
dispsent e_ l_ e_ c_ t_ r_ i_ c_ 0 n_ e_ t_ Dot 0 L_ o_ w_ e_ r_ s_ 0 S_ p_ e_ e_ d_ Dot 0xFF

WILD_CHARGE_description:
dispsent S_ h_ r_ o_ u_ d_ e_ d_ 0 i_ n_ 0 e_ l_ e_ c_ t_ r_ i_ c_ i_ t_ y_ Comma 0xFE
dispsent u_ s_ e_ r_ 0 s_ m_ a_ s_ h_ e_ s_ 0 i_ n_ t_ o_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF

DRILL_RUN_description:
dispsent U_ s_ e_ r_ 0 c_ r_ a_ s_ h_ e_ s_ 0 i_ n_ t_ o_ 0 t_ h_ e_ 0 f_ o_ e_ 0xFE
dispsent w_ h_ i_ l_ e_ 0 r_ o_ t_ a_ t_ i_ n_ g_ 0 l_ i_ k_ e_ 0 a_ 0 d_ r_ i_ l_ l_ Dot 0xFF

DUAL_CHOP_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 b_ r_ u_ t_ a_ l_ 0xFE
dispsent s_ t_ r_ i_ k_ e_ s_ Dot 0 A_ t_ t_ a_ c_ k_ s_ 0 t_ w_ i_ c_ e_ Dot 0xFF

HEART_STAMP_description:
dispsent U_ s_ e_ r_ 0 u_ n_ l_ e_ a_ s_ h_ e_ s_ 0 a_ 0 b_ l_ o_ w_ 0 a_ f_ t_ e_ r_ 0xFE
dispsent a_ c_ t_ i_ n_ g_ 0 c_ u_ t_ e_ Dot 0 M_ a_ y_ 0 f_ l_ i_ n_ c_ h_ Dot 0xFF

HORN_LEECH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ r_ a_ i_ n_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0xFE
dispsent i_ t_ s_ 0 h_ o_ r_ n_ s_ Comma 0 r_ e_ s_ t_ o_ r_ i_ n_ g_ 0 H_ P_ Dot 0xFF

SACRED_SWORD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 b_ y_ 0 s_ l_ i_ c_ i_ n_ g_ 0xFE
dispsent w_ i_ t_ h_ 0 a_ 0 l_ o_ n_ g_ 0 h_ o_ r_ n_ Dot 0xFF

RAZOR_SHELL_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ u_ t_ s_ 0 i_ t_ s_ 0 t_ a_ r_ g_ e_ t_ 0xFE
dispsent w_ i_ t_ h_ 0 s_ h_ a_ r_ p_ 0 s_ h_ e_ l_ l_ s_ Dot 0xFF

HEAT_CRASH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ l_ a_ m_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0xFE
dispsent i_ t_ Apos s_ 0 f_ l_ a_ m_ e_ Dash c_ o_ v_ e_ r_ e_ d_ 0 b_ o_ d_ y_ Dot 0xFF

LEAF_TORNADO_description:
dispsent F_ o_ e_ 0 i_ s_ 0 e_ n_ c_ i_ r_ c_ l_ e_ d_ 0 i_ n_ 0 s_ h_ a_ r_ p_ 0xFE
dispsent l_ e_ a_ v_ e_ s_ Dot 0 M_ a_ y_ 0 l_ o_ w_ e_ r_ 0 a_ c_ c_ u_ r_ a_ c_ y_ Dot 0xFF

STEAMROLLER_description:
dispsent U_ s_ e_ r_ 0 r_ o_ l_ l_ s_ 0 o_ v_ e_ r_ 0 t_ h_ e_ 0 f_ o_ e_ 0 t_ o_ 0xFE
dispsent c_ r_ u_ s_ h_ 0 i_ t_ Dot 0 M_ a_ y_ 0 f_ l_ i_ n_ c_ h_ Dot 0xFF

COTTON_GUARD_description:
dispsent U_ s_ e_ r_ 0 w_ r_ a_ p_ s_ 0 i_ t_ s_ e_ l_ f_ 0 i_ n_ 0 s_ o_ f_ t_ 0xFE
dispsent c_ o_ t_ t_ o_ n_ Comma 0 r_ a_ i_ s_ i_ n_ g_ 0 D_ e_ f_ e_ n_ s_ e_ Dot 0xFF

NIGHT_DAZE_description:
dispsent A_ 0 b_ l_ a_ c_ k_ 0 s_ h_ o_ c_ k_ 0 w_ a_ v_ e_ 0 i_ s_ 0 l_ e_ t_ 0xFE
dispsent l_ o_ o_ s_ e_ Dot 0 M_ a_ y_ 0 l_ o_ w_ e_ r_ 0 a_ c_ c_ u_ r_ a_ c_ y_ Dot 0xFF

PSYSTRIKE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 m_ a_ t_ e_ r_ i_ a_ l_ i_ z_ e_ s_ 0 a_ n_ 0 o_ d_ d_ 0xFE
dispsent p_ s_ y_ c_ h_ i_ c_ 0 w_ a_ v_ e_ 0 a_ t_ t_ a_ c_ k_ Dot 0xFF

TAIL_SLAP_description:
dispsent U_ s_ e_ r_ 0 s_ t_ r_ i_ k_ e_ s_ 0 w_ i_ t_ h_ 0 i_ t_ s_ 0 h_ a_ r_ d_ 0xFE
dispsent t_ a_ i_ l_ 0 t_ w_ o_ 0 t_ o_ 0 f_ i_ v_ e_ 0 t_ i_ m_ e_ s_ Dot 0xFF

HURRICANE_description:
dispsent A_ 0 f_ i_ e_ r_ c_ e_ 0 w_ i_ n_ d_ 0 t_ h_ a_ t_ 0 f_ l_ i_ e_ s_ 0xFE
dispsent u_ p_ 0 i_ n_ t_ o_ 0 t_ h_ e_ 0 s_ k_ y_ Dot 0xFF

HEAD_CHARGE_description:
dispsent U_ s_ e_ r_ 0 c_ h_ a_ r_ g_ e_ s_ 0 i_ t_ s_ 0 h_ e_ a_ d_ 0 i_ n_ t_ o_ 0xFE
dispsent t_ h_ e_ 0 f_ o_ e_ Dot 0 M_ a_ y_ 0 d_ a_ m_ a_ g_ e_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Dot 0xFF

GEAR_GRIND_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 b_ y_ 0 t_ h_ r_ o_ w_ i_ n_ g_ 0xFE
dispsent s_ t_ e_ e_ l_ 0 g_ e_ a_ r_ s_ 0 t_ w_ i_ c_ e_ Dot 0xFF 

SEARING_SHOT_description:
dispsent U_ s_ e_ r_ 0 t_ o_ r_ c_ h_ e_ s_ 0 a_ l_ l_ 0 w_ i_ t_ h_ 0 a_ n_ 0xFE
dispsent i_ n_ f_ e_ r_ n_ o_ Dot 0 M_ a_ y_ 0 b_ u_ r_ n_ 0 t_ h_ e_ 0 f_ o_ e_ s_ Dot 0xFF 

TECHNO_BLAST_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 f_ i_ r_ e_ s_ 0 a_ 0 b_ e_ a_ m_ Dot 0 M_ o_ v_ e_ 0xFE
dispsent t_ y_ p_ e_ 0 b_ a_ s_ e_ d_ 0 o_ n_ 0 h_ e_ l_ d_ 0 D_ r_ i_ v_ e_ r_ Dot 0xFF 

RELIC_SONG_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ i_ n_ g_ s_ 0 a_ n_ 0 a_ n_ c_ i_ e_ n_ t_ 0xFE
dispsent s_ o_ n_ g_ 0 t_ h_ a_ t_ 0 m_ a_ y_ 0 i_ n_ d_ u_ c_ e_ 0 s_ l_ e_ e_ p_ Dot 0xFF 

SECRET_SWORD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 c_ u_ t_ s_ 0 w_ i_ t_ h_ 0 i_ t_ s_ 0 l_ o_ n_ g_ 0xFE
dispsent h_ o_ r_ n_ 0 f_ o_ r_ 0 p_ h_ y_ s_ i_ c_ a_ l_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF 

GLACIATE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 c_ o_ l_ d_ 0xFE
dispsent a_ i_ r_ Dot 0 L_ o_ w_ e_ r_ s_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 S_ p_ e_ e_ d_ Dot 0xFF 

BOLT_STRIKE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent e_ l_ e_ c_ t_ r_ i_ c_ i_ t_ y_ Dot 0 M_ a_ y_ 0 p_ a_ r_ a_ l_ y_ z_ e_ Dot 0xFF 

BLUE_FLARE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0 b_ l_ u_ e_ 0xFE
dispsent f_ l_ a_ m_ e_ Dot 0 M_ a_ y_ 0 b_ u_ r_ n_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF 

FIERY_DANCE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ a_ n_ c_ e_ s_ 0 a_ n_ d_ 0 f_ l_ a_ p_ s_ 0xFE
dispsent i_ t_ s_ 0 w_ i_ n_ g_ s_ Dot 0 M_ a_ y_ 0 r_ a_ i_ s_ e_ 0 S_ p_ Dot 0 A_ t_ k_ Dot 0xFF 

FREEZE_SHOCK_description:
dispsent O_ n_ 0 t_ h_ e_ 0 n_ e_ x_ t_ 0 t_ u_ r_ n_ Comma 0 h_ i_ t_ s_ 0 w_ i_ t_ h_ 0xFE
dispsent c_ h_ a_ r_ g_ e_ d_ 0 i_ c_ e_ Dot 0 M_ a_ y_ 0 p_ a_ r_ a_ l_ y_ z_ e_ Dot 0xFF 

ICE_BURN_description:
dispsent O_ n_ 0 t_ h_ e_ 0 s_ e_ c_ o_ n_ d_ 0 t_ u_ r_ n_ Comma 0 l_ e_ a_ v_ e_ s_ 0 a_ 0xFE
dispsent c_ h_ i_ l_ l_ i_ n_ g_ 0 w_ i_ n_ d_ 0 t_ h_ a_ t_ 0 m_ a_ y_ 0 b_ u_ r_ n_ Dot 0xFF 

SNARL_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 y_ e_ l_ l_ s_ Comma 0 l_ o_ w_ e_ r_ i_ n_ g_ 0 t_ h_ e_ 0xFE
dispsent S_ p_ Dot 0 A_ t_ t_ a_ c_ k_ 0 o_ f_ 0 a_ l_ l_ 0 f_ o_ e_ s_ Dot 0xFF 

ICICLE_CRASH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 h_ a_ r_ s_ h_ l_ y_ 0 d_ r_ o_ p_ s_ 0 a_ n_ 0xFE
dispsent i_ c_ i_ c_ l_ e_ 0 o_ n_ t_ o_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0xFF

VCREATE_description:
dispsent U_ s_ e_ r_ 0 h_ u_ r_ l_ s_ 0 i_ t_ s_ e_ l_ f_ 0 a_ t_ 0 t_ h_ e_ 0xFE
dispsent f_ o_ e_ Dot 0 L_ o_ w_ e_ r_ s_ 0 s_ t_ a_ t_ s_ Dot 0xFF

FUSION_FLARE_description:
dispsent U_ s_ e_ r_ 0 t_ h_ r_ o_ w_ s_ 0 a_ 0 t_ h_ u_ n_ d_ e_ r_ b_ o_ l_ t_ 0xFE
dispsent I_ n_ f_ l_ u_ e_ n_ c_ e_ d_ 0 b_ y_ 0 a_ 0 b_ i_ g_ 0 f_ l_ a_ m_ e_ Dot 0xFF

FUSION_BOLT_description:
dispsent U_ s_ e_ r_ 0 t_ h_ r_ o_ w_ s_ 0 d_ o_ w_ n_ 0 a_ 0 f_ l_ a_ m_ e_ 0xFE
dispsent I_ n_ f_ l_ u_ e_ n_ c_ e_ d_ 0 b_ y_ 0 a_ 0 t_ h_ u_ n_ d_ e_ r_ b_ o_ l_ t_ Dot 0xFF 

FLYING_PRESS_description:
dispsent U_ s_ e_ r_ 0 d_ i_ v_ e_ s_ 0 d_ o_ w_ n_ 0 o_ n_ 0 t_ a_ r_ g_ e_ t_ 0xFE 
dispsent T_ h_ e_ 0 m_ o_ v_ e_ 0 i_ s_ 0 F_ l_ y_ i_ n_ g_ Slash F_ i_ g_ h_ t_ i_ n_ g_ Dot 0xFF

MAT_BLOCK_description:
dispsent P_ r_ o_ t_ e_ c_ t_ s_ 0 u_ s_ e_ r_ 0 a_ n_ d_ 0 a_ l_ l_ i_ e_ s_ 0xFE
dispsent f_ r_ o_ m_ 0 d_ a_ m_ a_ g_ i_ n_ g_ 0 m_ o_ v_ e_ s_ 0 o_ n_ l_ y_ Dot 0xFF 

BELCH_description:
dispsent U_ s_ e_ r_ 0 m_ u_ s_ t_ 0 e_ a_ t_ 0 a_ 0 b_ e_ r_ r_ y_ Comma 0 b_ u_ t_ 0xFE
dispsent l_ e_ t_ Apos s_ 0 o_ u_ t_ 0 a_ 0 d_ a_ m_ a_ g_ i_ n_ g_ 0 b_ e_ l_ c_ h_ Dot 0xFF 

ROTOTILLER_description:
dispsent U_ s_ e_ r_ 0 t_ i_ l_ l_ s_ 0 t_ h_ e_ 0 s_ o_ i_ l_ 0 t_ o_ 0 r_ a_ i_ s_ e_ 0xFE
dispsent A_ t_ k_ 0 a_ n_ d_ 0 S_ p_ Dot 0 A_ 0 o_ f_ 0 G_ r_ a_ s_ s_ Dash t_ y_ p_ e_ s_ Dot 0xFF 

STICKY_WEB_description:
dispsent U_ s_ e_ r_ 0 w_ e_ a_ v_ e_ s_ 0 a_ 0 s_ t_ i_ c_ k_ y_ 0 n_ e_ t_ Comma 0xFE
dispsent l_ o_ w_ e_ r_ i_ n_ g_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 S_ p_ e_ e_ d_ Dot 0xFF

FELL_STINGER_description:
dispsent W_ h_ e_ n_ 0 a_ 0 f_ o_ e_ 0 i_ s_ 0 k_ n_ o_ c_ k_ e_ d_ 0 o_ u_ t_ Comma 0xFE
dispsent u_ s_ e_ r_ Apos s_ 0 A_ t_ t_ a_ c_ k_ 0 i_ s_ 0 r_ a_ i_ s_ e_ d_ Dot 0xFF

PHANTOM_FORCE_description:
dispsent U_ s_ e_ r_ 0 v_ a_ n_ i_ s_ h_ e_ s_ 0 s_ o_ m_ e_ w_ h_ e_ r_ e_ 0 t_ o_ 0xFE
dispsent s_ t_ r_ i_ k_ e_ 0 o_ n_ 0 t_ h_ e_ 0 n_ e_ x_ t_ 0 t_ u_ r_ n_ Dot 0xFF

TRICKORTREAT_description:
dispsent T_ r_ i_ c_ k_ 0 o_ r_ 0 t_ r_ e_ a_ t_ Interro 0 T_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0xFE
dispsent b_ e_ c_ o_ m_ e_ s_ 0 a_ 0 G_ h_ o_ s_ t_ Dash t_ y_ p_ e_ Dot 0xFF

NOBLE_ROAR_description:
dispsent W_ i_ t_ h_ 0 a_ 0 n_ o_ b_ l_ e_ 0 r_ o_ a_ r_ Comma 0 l_ o_ w_ e_ r_ s_ 0xFE
dispsent f_ o_ e_ Apos s_ 0 A_ t_ t_ a_ c_ k_ 0 a_ n_ d_ 0 S_ p_ Dot 0 A_ t_ t_ a_ c_ k_ Dot 0xFF

ION_DELUGE_description:
dispsent C_ h_ a_ n_ g_ e_ s_ 0 N_ o_ r_ m_ a_ l_ Dash t_ y_ p_ e_ 0 m_ o_ v_ e_ s_ 0xFE
dispsent i_ n_ t_ o_ 0 E_ l_ e_ c_ t_ r_ i_ c_ Dash t_ y_ p_ e_ Dot 0xFF

PARABOLIC_CHARGE_description:
dispsent U_ s_ e_ r_ 0 h_ i_ t_ s_ 0 e_ v_ e_ r_ y_ t_ h_ i_ n_ g_ Dot 0 H_ P_ 0 i_ s_ 0xFE
dispsent r_ e_ s_ t_ o_ r_ e_ d_ 0 b_ a_ s_ e_ d_ 0 o_ n_ 0 d_ a_ m_ a_ g_ e_ Dot 0xFF

FORESTS_CURSE_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 r_ e_ c_ e_ i_ v_ e_ s_ 0 a_ 0 c_ u_ r_ s_ e_ Comma 0xFE
dispsent m_ a_ k_ i_ n_ g_ 0 i_ t_ 0 G_ r_ a_ s_ s_ Dash t_ y_ p_ e_ Dot 0xFF

PETAL_BLIZZARD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ t_ i_ r_ s_ 0 u_ p_ 0 a_ 0xFE
dispsent v_ i_ o_ l_ e_ n_ t_ 0 P_ e_ t_ a_ l_ 0 B_ l_ i_ z_ z_ a_ r_ d_ Dot 0xFF

FREEZEDRY_description:
dispsent M_ a_ y_ 0 f_ r_ e_ e_ z_ e_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Dot 0 S_ u_ p_ e_ r_ 0xFE
dispsent e_ f_ f_ e_ c_ t_ i_ v_ e_ 0 o_ n_ 0 W_ a_ t_ e_ r_ Dash t_ y_ p_ e_ s_ Dot 0xFF

DISARMING_VOICE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ o_ e_ s_ 0 e_ m_ o_ t_ i_ o_ n_ a_ l_ 0xFE
dispsent d_ a_ m_ a_ g_ e_ 0 u_ s_ i_ n_ g_ 0 a_ 0 c_ h_ a_ r_ m_ i_ n_ g_ 0 c_ r_ y_ Dot 0xFF

PARTING_SHOT_description:
dispsent A_ t_ k_ 0 a_ n_ d_ 0 S_ p_ Dot A_ t_ k_ 0 a_ r_ e_ 0 l_ o_ w_ e_ r_ e_ d_ 0xFE
dispsent t_ h_ e_ n_ 0 f_ o_ e_ 0 i_ s_ 0 s_ w_ i_ t_ c_ h_ e_ d_ 0 o_ u_ t_ Dot 0xFF

TOPSYTURVY_description:
dispsent A_ l_ l_ 0 s_ t_ a_ t_ 0 c_ h_ a_ n_ g_ e_ s_ 0 a_ f_ f_ e_ c_ t_ i_ n_ g_ 0xFE
dispsent t_ h_ e_ 0 f_ o_ e_ 0 b_ e_ c_ o_ m_ e_ 0 o_ p_ p_ o_ s_ i_ t_ e_ Dot 0xFF

DRAINING_KISS_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ t_ e_ a_ l_ s_ 0 t_ h_ e_ 0xFE
dispsent t_ a_ r_ g_ e_ t_ Apos s_ 0 e_ n_ e_ r_ g_ y_ 0 w_ i_ t_ h_ 0 a_ 0 k_ i_ s_ s_ Dot 0xFF

CRAFTY_SHIELD_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ n_ d_ 0 a_ l_ l_ i_ e_ s_ 0 a_ r_ e_ 0xFE
dispsent p_ r_ o_ t_ e_ c_ t_ e_ d_ 0 f_ r_ o_ m_ 0 s_ t_ a_ t_ u_ s_ 0 m_ o_ v_ e_ s_ Dot 0xFF
 
FLOWER_SHIELD_description:
dispsent T_ h_ e_ 0 D_ e_ f_ e_ n_ s_ e_ 0 s_ t_ a_ t_ 0 i_ s_ 0 r_ a_ i_ s_ e_ d_ 0xFE
dispsent f_ o_ r_ 0 a_ l_ l_ 0 G_ r_ a_ s_ s_ Dash t_ y_ p_ e_ s_ 0 P_ o_ k_ Poke_e m_ o_ n_ Dot 0xFF
 
GRASSY_TERRAIN_description:
dispsent G_ r_ o_ u_ n_ d_ e_ d_ 0 p_ o_ k_ Poke_e m_ o_ n_ 0 r_ e_ g_ a_ i_ n_ 0xFE
dispsent h_ e_ a_ l_ t_ h_ 0 f_ o_ r_ 0 f_ i_ v_ e_ 0 t_ u_ r_ n_ s_ Dot 0xFF
 
MISTY_TERRAIN_description:
dispsent P_ r_ e_ v_ e_ n_ t_ s_ 0 s_ t_ a_ t_ u_ s_ 0 e_ f_ f_ e_ c_ t_ s_ 0xFE
dispsent f_ o_ r_ 0 t_ h_ e_ 0 g_ r_ o_ u_ n_ d_ e_ d_ 0 p_ o_ k_ Poke_e m_ o_ n_ Dot 0xFF
 
ELECTRIFY_description:
dispsent T_ h_ e_ 0 f_ o_ e_ Apos s_ 0 n_ e_ x_ t_ 0 m_ o_ v_ e_ 0 t_ h_ a_ t_ 0xFE
dispsent t_ u_ r_ n_ 0 b_ e_ c_ o_ m_ e_ s_ 0 E_ l_ e_ c_ t_ r_ i_ c_ Dash t_ y_ p_ e_ Dot 0xFF
 
PLAY_ROUGH_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 p_ l_ a_ y_ s_ 0 r_ o_ u_ g_ h_ Comma 0 w_ h_ i_ c_ h_ 0xFE
dispsent m_ a_ y_ 0 l_ o_ w_ e_ r_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 A_ t_ t_ a_ c_ k_ Dot 0xFF
 
FAIRY_WIND_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 s_ t_ i_ r_ s_ 0 u_ p_ 0 a_ 0 f_ a_ i_ r_ y_ 0xFE
dispsent w_ i_ n_ d_ 0 a_ n_ d_ 0 s_ t_ r_ i_ k_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF
 
MOONBLAST_description:
dispsent T_ h_ e_ 0 m_ o_ o_ n_ Apos s_ 0 p_ o_ w_ e_ r_ 0 i_ s_ 0 b_ o_ r_ r_ o_ w_ e_ d_ 0xFE
dispsent t_ o_ 0 l_ o_ w_ e_ r_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 S_ p_ Dot 0 A_ t_ k_ Dot 0xFF
 
BOOMBURST_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 e_ v_ e_ r_ y_ t_ h_ i_ n_ g_ 0xFE
dispsent a_ r_ o_ u_ n_ d_ 0 i_ t_ 0 w_ i_ t_ h_ 0 a_ 0 l_ o_ u_ d_ 0 s_ o_ u_ n_ d_ Dot 0xFF
 
FAIRY_LOCK_description:
dispsent B_ y_ 0 l_ o_ c_ k_ i_ n_ g_ 0 t_ h_ e_ 0 b_ a_ t_ t_ l_ e_ f_ i_ e_ l_ d_ Comma 0xFE
dispsent k_ e_ e_ p_ s_ 0 a_ l_ l_ 0 f_ o_ e_ s_ 0 f_ r_ o_ m_ 0 f_ l_ e_ e_ i_ n_ g_ Dot 0xFF
 
KINGS_SHIELD_description:
dispsent S_ t_ r_ i_ k_ i_ n_ g_ 0 t_ h_ e_ 0 u_ s_ e_ r_ 0 w_ i_ l_ l_ 0 l_ o_ w_ e_ r_ 0xFE
dispsent t_ h_ e_ 0 a_ t_ t_ a_ c_ k_ e_ r_ Apos s_ 0 A_ t_ t_ a_ c_ k_ 0 s_ t_ a_ t_ Dot 0xFF
 
PLAY_NICE_description:
dispsent U_ s_ e_ r_ 0 a_ n_ d_ 0 f_ o_ e_ 0 b_ e_ c_ o_ m_ e_ 0 f_ r_ i_ e_ n_ d_ s_ Comma 0xFE
dispsent l_ o_ w_ e_ r_ i_ n_ g_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 A_ t_ t_ a_ c_ k_ Dot 0xFF
 
CONFIDE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 t_ e_ l_ l_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 a_ 0xFE
dispsent s_ e_ c_ r_ e_ t_ 0 w_ h_ i_ c_ h_ 0 m_ a_ y_ 0 l_ o_ w_ e_ r_ 0 S_ p_ Dot A_ Dot 0xFF
 
DIAMOND_STORM_description:
dispsent U_ s_ e_ r_ 0 w_ h_ i_ p_ s_ 0 u_ p_ 0 a_ 0 s_ t_ o_ r_ m_ 0 o_ f_ 0xFE
dispsent d_ i_ a_ m_ o_ n_ d_ s_ Dot 0 M_ a_ y_ 0 r_ a_ i_ s_ e_ 0 D_ e_ f_ e_ n_ s_ e_ Dot 0xFF
 
STEAM_ERUPTION_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 i_ s_ 0 l_ e_ f_ t_ 0 i_ n_ 0 a_ 0 s_ t_ e_ a_ m_ Dot 0xFE
dispsent T_ h_ i_ s_ 0 m_ i_ g_ h_ t_ 0 b_ u_ r_ n_ 0 t_ h_ e_ 0 f_ o_ e_ Dot 0xFF
 
HYPERSPACE_HOLE_description:
dispsent T_ r_ a_ v_ e_ l_ s_ 0 t_ h_ r_ o_ u_ g_ h_ 0 h_ y_ p_ e_ r_ s_ p_ a_ c_ e_ 0xFE
dispsent a_ n_ d_ 0 s_ t_ r_ i_ k_ e_ s_ 0 t_ h_ r_ o_ u_ g_ h_ 0 P_ r_ o_ t_ e_ c_ t_ Dot 0xFF
 
WATER_SHURIKEN_description:
dispsent U_ s_ e_ r_ 0 t_ h_ r_ o_ w_ s_ 0 s_ t_ a_ r_ s_ 0 t_ w_ o_ 0 t_ o_ 0xFE
dispsent f_ i_ v_ e_ 0 t_ i_ m_ e_ s_ Dot 0 S_ t_ r_ i_ k_ e_ s_ 0 f_ i_ r_ s_ t_ Dot 0xFF
 
MYSTICAL_FIRE_description:
dispsent U_ s_ e_ r_ 0 a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 a_ 0 b_ r_ e_ a_ t_ h_ 0xFE
dispsent o_ f_ 0 f_ i_ r_ e_ Dot 0 L_ o_ w_ e_ r_ s_ 0 f_ o_ e_ Apos s_ 0 S_ p_ Dot A_ Dot 0xFF
 
SPIKY_SHIELD_description:
dispsent P_ r_ o_ t_ e_ c_ t_ s_ 0 a_ l_ l_ i_ e_ s_ 0 a_ n_ d_ 0 d_ a_ m_ a_ g_ e_ s_ 0xFE
dispsent f_ o_ e_ s_ 0 t_ h_ a_ t_ 0 a_ t_ t_ a_ c_ k_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Dot 0xFF
 
AROMATIC_MIST_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 r_ a_ i_ s_ e_ s_ 0 a_ n_ 0 a_ l_ l_ y_ Apos s_ 0xFE
dispsent S_ p_ Dot 0 D_ e_ f_ 0 s_ t_ a_ t_ 0 w_ i_ t_ h_ 0 a_ n_ 0 a_ r_ o_ m_ a_ Dot 0xFF
 
EERIE_IMPULSE_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 e_ e_ r_ i_ e_ 0 i_ m_ p_ u_ l_ s_ e_ 0xFE
dispsent l_ o_ w_ e_ r_ s_ 0 t_ h_ e_ 0 f_ o_ e_ Apos s_ 0 S_ p_ Dot 0 A_ t_ t_ a_ c_ k_ Dot 0xFF
 
VENOM_DRENCH_description:
dispsent F_ o_ e_ 0 d_ r_ e_ n_ c_ h_ e_ d_ 0 w_ i_ t_ h_ 0 a_ 0 p_ o_ i_ s_ o_ n_ Dot 0xFE
dispsent L_ o_ w_ e_ r_ s_ 0 A_ t_ k_ Comma 0 S_ p_ Dot A_ Comma 0 a_ n_ d_ 0 S_ p_ e_ e_ d_ Dot 0xFF
 
POWDER_description:
dispsent F_ o_ e_ 0 c_ o_ v_ e_ r_ e_ d_ 0 i_ n_ 0 p_ o_ w_ d_ e_ r_ Dot 0 H_ u_ r_ t_ s_ 0xFE
dispsent f_ o_ e_ 0 i_ f_ 0 F_ i_ r_ e_ Dash t_ y_ p_ e_ 0 m_ o_ v_ e_ 0 u_ s_ e_ d_ Dot 0xFF
 
GEOMANCY_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ b_ s_ o_ r_ b_ s_ 0 e_ n_ e_ r_ g_ y_ Comma 0xFE
dispsent r_ a_ i_ s_ i_ n_ g_ 0 S_ p_ A_ Comma 0 S_ p_ D_ Comma 0 a_ n_ d_ 0 S_ p_ e_ e_ d_ Dot 0xFF
 
MAGNETIC_FLUX_description:
dispsent R_ a_ i_ s_ e_ s_ 0 t_ h_ e_ 0 D_ e_ f_ 0 a_ n_ d_ 0 S_ p_ Dot D_ 0 o_ f_ 0xFE
dispsent a_ l_ l_ i_ e_ s_ 0 w_ i_ t_ h_ 0 P_ l_ u_ s_ 0 o_ r_ 0 M_ i_ n_ u_ s_ Dot 0xFF
 
HAPPY_HOUR_description:
dispsent D_ o_ u_ b_ l_ e_ s_ 0 t_ h_ e_ 0 a_ m_ o_ u_ n_ t_ 0 o_ f_ 0 p_ r_ i_ z_ e_ 0xFE
dispsent m_ o_ n_ e_ y_ 0 r_ e_ c_ e_ i_ v_ e_ d_ 0 a_ f_ t_ e_ r_ 0 b_ a_ t_ t_ l_ e_ Dot 0xFF
 
ELECTRIC_TERRAIN_description:
dispsent P_ r_ e_ v_ e_ n_ t_ s_ 0 s_ l_ e_ e_ p_ i_ n_ g_ 0 f_ o_ r_ 0 f_ i_ v_ e_ 0xFE
dispsent t_ u_ r_ n_ s_ 0 w_ i_ t_ h_ 0 s_ h_ a_ r_ p_ 0 s_ t_ a_ t_ i_ c_ Dot 0xFF
 
DAZZLING_GLEAM_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 d_ a_ m_ a_ g_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 b_ y_ 0xFE
dispsent e_ m_ i_ t_ t_ i_ n_ g_ 0 a_ 0 p_ o_ w_ e_ r_ f_ u_ l_ 0 f_ l_ a_ s_ h_ Dot 0xFF
 
CELEBRATE_description:
dispsent T_ h_ e_ 0 P_ o_ k_ Poke_e m_ o_ n_ 0 c_ o_ n_ g_ r_ a_ t_ u_ l_ a_ t_ e_ s_ 0xFE
dispsent y_ o_ u_ 0 o_ n_ 0 y_ o_ u_ r_ 0 s_ p_ e_ c_ i_ a_ l_ 0 d_ a_ y_ Exclam 0xFF
 
HOLD_HANDS_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 a_ n_ d_ 0 a_ n_ 0 a_ l_ l_ y_ 0 h_ o_ l_ d_ 0xFE
dispsent h_ a_ n_ d_ s_ Comma 0 m_ a_ k_ i_ n_ g_ 0 t_ h_ e_ m_ 0 h_ a_ p_ p_ y_ Dot 0xFF
 
BABYDOLL_EYES_description:
dispsent S_ t_ a_ r_ e_ s_ 0 a_ t_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0xFE
dispsent b_ a_ b_ y_ Dash d_ o_ l_ l_ 0 e_ y_ e_ s_ Dot 0 L_ o_ w_ e_ r_ s_ 0 A_ t_ k_ Dot 0xFF
 
NUZZLE_description:
dispsent E_ l_ e_ c_ t_ r_ i_ f_ i_ e_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ Comma 0xFE
dispsent w_ h_ i_ c_ h_ 0 r_ e_ s_ u_ l_ t_ 0 i_ n_ 0 a_ 0 p_ a_ r_ a_ l_ y_ z_ i_ s_ 0xFF
 
HOLD_BACK_description:
dispsent T_ h_ e_ 0 u_ s_ e_ r_ 0 h_ o_ l_ d_ s_ 0 b_ a_ c_ k_ 0 a_ n_ d_ 0xFE
dispsent l_ e_ a_ v_ e_ s_ 0 t_ h_ e_ 0 f_ o_ e_ 0 w_ i_ t_ h_ 0 o_ n_ e_ 0 H_ P_ Dot 0xFF

INFESTATION_description:
dispsent T_ h_ e_ 0 f_ o_ e_ 0 i_ s_ 0 i_ n_ f_ e_ s_ t_ e_ d_ 0 f_ o_ r_ 0xFE
dispsent s_ e_ v_ e_ r_ a_ l_ 0 t_ u_ r_ n_ s_ 0 a_ n_ d_ 0 c_ a_ n_ Apos t_ 0 f_ l_ e_ e_ Dot 0xFF
 
POWERUP_PUNCH_description:
dispsent S_ u_ c_ c_ e_ s_ s_ f_ u_ l_ 0 h_ i_ t_ s_ 0 w_ i_ l_ l_ 0 r_ a_ i_ s_ e_ 0xFE
dispsent t_ h_ e_ 0 u_ s_ e_ r_ Apos s_ 0 a_ t_ t_ a_ c_ k_ Dot 0xFF
 
OBLIVION_WING_description:
dispsent D_ r_ a_ i_ n_ s_ 0 t_ h_ e_ 0 t_ a_ r_ g_ e_ t_ 0 o_ f_ 0 l_ i_ f_ e_ 0xFE
dispsent a_ n_ d_ 0 r_ e_ s_ t_ o_ r_ e_ s_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Apos s_ Dot 0xFF
 
THOUSAND_ARROWS_description:
dispsent S_ t_ r_ i_ k_ e_ s_ 0 d_ o_ w_ n_ 0 a_ n_ y_ 0 e_ n_ e_ m_ i_ e_ s_ 0
dispsent t_ h_ a_ t_ 0 a_ r_ e_ 0 i_ n_ 0 t_ h_ e_ 0 a_ i_ r_ Dot 0xFF
 
THOUSAND_WAVES_description:
dispsent U_ s_ e_ r_ 0 s_ e_ n_ d_ s_ 0 a_ 0 w_ a_ v_ e_ 0 o_ f_ 0 p_ a_ i_ n_ Dot 0xFE
dispsent F_ o_ e_ 0 c_ a_ n_ Apos t_ 0 f_ l_ e_ e_ 0 f_ r_ o_ m_ 0 b_ a_ t_ t_ l_ e_ Dot 0xFF
 
LANDS_WRATH_description:
dispsent G_ a_ t_ h_ e_ r_ s_ 0 t_ h_ e_ 0 e_ n_ e_ r_ g_ y_ 0 o_ f_ 0 t_ h_ e_ 0xFE
dispsent l_ a_ n_ d_ 0 f_ o_ r_ 0 a_ 0 p_ o_ w_ e_ r_ f_ u_ l_ 0 s_ t_ r_ i_ k_ e_ Dot 0xFF
 
LIGHT_OF_RUIN_description:
dispsent F_ i_ r_ e_ s_ 0 a_ 0 p_ o_ w_ e_ r_ f_ u_ l_ 0 b_ e_ a_ m_ 0 o_ f_ 0xFE
dispsent l_ i_ g_ h_ t_ Dot 0 A_ l_ s_ o_ 0 h_ u_ r_ t_ s_ 0 t_ h_ e_ 0 u_ s_ e_ r_ Dot 0xFF
 
ORIGINE_PULSE_description:
dispsent S_ e_ n_ d_ s_ 0 o_ u_ t_ 0 c_ o_ u_ n_ t_ l_ e_ s_ s_ 0 b_ e_ a_ m_ s_ 0 o_ f_ 0xFE
dispsent l_ i_ g_ h_ t_ 0 f_ o_ r_ 0 a_ 0 r_ a_ d_ i_ a_ n_ t_ 0 a_ t_ t_ a_ c_ k_ Dot 0xFF
 
PRECIPICE_BLADES_description:
dispsent M_ a_ n_ i_ f_ e_ s_ t_ s_ 0 t_ h_ e_ 0 p_ o_ w_ e_ r_ 0 o_ f_ 0 t_ h_ e_ 0xFE
dispsent l_ a_ n_ d_ 0 f_ o_ r_ 0 a_ 0 f_ e_ a_ r_ s_ o_ m_ e_ 0 a_ t_ t_ a_ c_ k_ Dot 0xFF
 
DRAGON_ASCENT_description:
dispsent S_ o_ a_ r_ s_ 0 u_ p_ w_ a_ r_ d_ 0 t_ h_ e_ n_ 0 d_ r_ o_ p_ s_ 0 d_ o_ w_ n_ 0xFE
dispsent f_ o_ r_ 0 a_ 0 d_ e_ v_ a_ s_ t_ a_ t_ i_ n_ g_ 0 b_ l_ o_ w_ Dot 0xFF
 
HYPERSPACE_FURY_description:
dispsent U_ n_ l_ e_ a_ s_ h_ e_ s_ 0 a_ 0 b_ a_ r_ r_ a_ g_ e_ 0 o_ f_ 0xFE
dispsent a_ t_ t_ a_ c_ k_ s_ 0 w_ i_ t_ h_ 0 i_ t_ s_ 0 m_ a_ n_ y_ 0 a_ r_ m_ s_ Dot 0xFF

NOTHING_description:
dispsent N_ o_ t_ h_ i_ n_ g_ 0 f_ o_ r_ 0 n_ o_ w_ Dot 0xFF
.word 0x0
.word 0xFFFFFFFF
.word 0x0


