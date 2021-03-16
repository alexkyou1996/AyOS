#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "segment.h"
#include "klib.h"
#include "gdt.h"

extern void load_gdt(void *, uint16_t size);
extern void reload_segment_registers();

static void gdt_set_segment_size();
static void gdt_init_null_segment_descriptor();
static void gdt_init_code_segment_descriptor();
static void gdt_init_data_segment_descriptor();

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

global_descriptor_table_t gdt;

//////////////////////
// PUBLIC FUNCTIONS //
//////////////////////
void init_global_descriptor_table()
{
    gdt_set_segment_size();
    gdt_init_null_segment_descriptor();
    gdt_init_code_segment_descriptor();
    gdt_init_data_segment_descriptor();
    load_gdt(gdt.descriptors, gdt.size);
    reload_segment_registers();
}

///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////
static void gdt_set_segment_size()
{
    gdt.size = SEGMENT_COUNT * sizeof(segment_descriptor_t);
}

static void gdt_init_null_segment_descriptor()
{
    segment_clear(&gdt.descriptors[SEGMENT_NULL]);
}
static void gdt_init_code_segment_descriptor()
{
    segment_descriptor_t *code_descriptor = &gdt.descriptors[SEGMENT_CODE];

    segment_set_base(code_descriptor, 0);
    segment_set_limit(code_descriptor, 0x000FFFFF);
    segment_set_segment_type(code_descriptor, SEG_CODE_EXRD);
    segment_set_descriptor_type(code_descriptor, DESC_TYPE_CODE);
    segment_set_descriptor_previlge_level(code_descriptor, PREVILEGE_LEVEL_ZERO);
    segment_set_segment_present(code_descriptor, true);
    segment_set_segment_is_64_bit(code_descriptor, false);
    segment_set_default_operation_size(code_descriptor, DEFAULT_32_BIT_SEG);
    segment_set_granularity(code_descriptor, GRANULARITY_4KB);
}
static void gdt_init_data_segment_descriptor()
{
    segment_descriptor_t *data_descriptor = &gdt.descriptors[SEGMENT_DATA];

    segment_set_base(data_descriptor, 0);
    segment_set_limit(data_descriptor, 0x000FFFFF);
    segment_set_segment_type(data_descriptor, SEG_DATA_RDWR);
    segment_set_descriptor_type(data_descriptor, DESC_TYPE_DATA);
    segment_set_descriptor_previlge_level(data_descriptor, PREVILEGE_LEVEL_ZERO);
    segment_set_segment_present(data_descriptor, true);
    segment_set_segment_is_64_bit(data_descriptor, false);
    segment_set_default_operation_size(data_descriptor, DEFAULT_32_BIT_SEG);
    segment_set_granularity(data_descriptor, GRANULARITY_4KB);
}



