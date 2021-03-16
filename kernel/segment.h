#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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

#define PREVILEGE_LEVEL_ZERO  0x0
#define PREVILEGE_LEVEL_THREE 0x3

#define DEFAULT_16_BIT_SEG 0x0
#define DEFAULT_32_BIT_SEG 0x1

#define GRANULARITY_1B  0x0
#define GRANULARITY_4KB 0x1

//! Structure that describes the segment descriptors in GDT
//!
//! The size of this structure must be known by the GDT in order
//! for GDT to instantiate the object statically
//!
//! Use the supplied functions instead of manipulating the object directly for safety
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

bool segment_clear(segment_descriptor_t *);
bool segment_set_base(segment_descriptor_t *, uint32_t);
bool segment_set_limit(segment_descriptor_t *, uint32_t);
bool segment_set_segment_type(segment_descriptor_t *, uint8_t);
bool segment_set_descriptor_type(segment_descriptor_t *, uint8_t);
bool segment_set_descriptor_previlge_level(segment_descriptor_t *, uint8_t);
bool segment_set_segment_present(segment_descriptor_t *, bool);
bool segment_set_segment_is_64_bit(segment_descriptor_t *, bool);
bool segment_set_default_operation_size(segment_descriptor_t *, uint8_t);
bool segment_set_granularity(segment_descriptor_t *, uint8_t);

#endif
