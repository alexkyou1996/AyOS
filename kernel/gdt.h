#include <stddef.h>
#include <stdint.h>

#ifndef __GDT_H__
#define __GDT_H__

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define DESC_TYPE_SYSTEM 0x0
#define DESC_TYPE_CODE   0x1
#define DESC_TYPE_DATA   0x1

#define PREVILEGE_ZERO  0x0
#define PREVILEGE_THREE 0x3

#define DEFAULT_16_BIT_SEG 0x0
#define DEFAULT_32_BIT_SEG 0x1

#define GRANULARITY_1B  0x0
#define GRANULARITY_4KB 0x1

typedef struct __attribute__((packed)) _segment_descriptor_struct {

    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;

    uint8_t segment_type : 4;
    // 0: system segment
    // 1: code or data segment
    uint8_t descriptor_type : 1;
    uint8_t descriptor_privilege_level : 2;
    uint8_t segment_present : 1;

    uint8_t limit_high : 4;
    uint8_t reserved : 1;
    uint8_t is_64_bit : 1;
    // 0: 16-bit segment
    // 1: 32-bit segment
    uint8_t default_operation_size : 1;
    // 0: limit is in byte increment
    // 1: limit is in 4KB increments
    uint8_t granularity : 1;

    uint8_t base_high;

} segment_descriptor_t;

typedef enum _segment_type_enum {
    SEGMENT_NULL = 0,
    SEGMENT_CODE,
    SEGMENT_DATA,
    SEGMENT_COUNT
} segment_type_t;

typedef struct __attribute__((packed)) _global_descriptor_table_struct {
    uint16_t size;
    segment_descriptor_t descriptors[SEGMENT_COUNT];
} global_descriptor_table_t;


void init_global_descriptor_table();

#endif
