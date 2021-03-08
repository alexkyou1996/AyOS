#include "klib.h"
#include "gdt.h"

static void gdt_set_null_segment_descriptor();
static void gdt_set_code_segment_desciprtor();
static void gdt_set_data_segment_desciprtor();

static void gdt_set_base(int gdt_index, uint32_t base);
static void gdt_set_limit(int gdt_index, uint32_t limit);
static void gdt_set_segment_type(int gdt_index, uint8_t segment_type);
static void gdt_set_descriptor_type(int gdt_index, uint8_t descriptor_type);
static void gdt_set_descriptor_previlge_level(int gdt_index, uint8_t previlege_level);
static void gdt_set_segment_present(int gdt_index, bool is_present);
static void gdt_set_segment_is_64_bit(int gdt_index, bool is_64_bit);
static void gdt_set_default_operation_size(int gdt_index, uint8_t operation_size);
static void gdt_set_granulariy(int gdt_index, uint8_t granularity);

global_descriptor_table_t gdt;

void init_global_descriptor_table()
{
    gdt.segment_descriptor_count = SEGMENT_COUNT;

    gdt_set_null_segment_descriptor();
    gdt_set_code_segment_desciprtor();
    gdt_set_data_segment_desciprtor();

    load_gdt(gdt.descriptors[SEGMENT_NULL]);
    reload_segment_register();
}

///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////

static void gdt_set_null_segment_descriptor()
{
    gdt_set_base(SEGMENT_NULL, 0);
    gdt_set_limit(SEGMENT_NULL, 0);
    gdt_set_segment_type(SEGMENT_NULL, 0);
    gdt_set_descriptor_type(SEGMENT_NULL, 0);
    gdt_set_descriptor_previlge_level(SEGMENT_NULL, 0);
    gdt_set_segment_present(SEGMENT_NULL, false);
    gdt_set_segment_is_64_bit(SEGMENT_NULL, false);
    gdt_set_default_operation_size(SEGMENT_NULL, 0);
    gdt_set_granulariy(SEGMENT_NULL, 0);
}
static void gdt_set_code_segment_desciprtor()
{
    gdt_set_base(SEGMENT_CODE, 0);
    gdt_set_limit(SEGMENT_CODE, 0x000FFFFF);
    gdt_set_segment_type(SEGMENT_CODE, SEG_CODE_EXRD);
    gdt_set_descriptor_type(SEGMENT_CODE, DESC_TYPE_CODE);
    gdt_set_descriptor_previlge_level(SEGMENT_CODE, PREVILEGE_ZERO);
    gdt_set_segment_present(SEGMENT_CODE, true);
    gdt_set_segment_is_64_bit(SEGMENT_CODE, false);
    gdt_set_default_operation_size(SEGMENT_CODE, DEFAULT_32_BIT_SEG);
    gdt_set_granulariy(SEGMENT_CODE, GRANULARITY_4KB);
}
static void gdt_set_data_segment_desciprtor()
{
    gdt_set_base(SEGMENT_DATA, 0);
    gdt_set_limit(SEGMENT_DATA, 0x000FFFFF);
    gdt_set_segment_type(SEGMENT_DATA, SEG_DATA_RDWR);
    gdt_set_descriptor_type(SEGMENT_DATA, DESC_TYPE_DATA);
    gdt_set_descriptor_previlge_level(SEGMENT_DATA, PREVILEGE_ZERO);
    gdt_set_segment_present(SEGMENT_DATA, true);
    gdt_set_segment_is_64_bit(SEGMENT_DATA, false);
    gdt_set_default_operation_size(SEGMENT_DATA, DEFAULT_32_BIT_SEG);
    gdt_set_granulariy(SEGMENT_DATA, GRANULARITY_4KB);
}

static void gdt_set_base(int gdt_index, uint32_t base)
{
    gdt.descriptors[gdt_index].base_low = (base & 0xFFFF);
    gdt.descriptors[gdt_index].base_middle = ((base >> 16) & 0xFF);
    gdt.descriptors[gdt_index].base_high = ((base >> 24) & 0xFF);
}

static void gdt_set_limit(int gdt_index, uint32_t limit)
{
    gdt.descriptors[gdt_index].limit_low = (limit & 0xFFFF);
    gdt.descriptors[gdt_index].limit_high = ((limit >> 16) & 0x0F);
}

static void gdt_set_segment_type(int gdt_index, uint8_t segment_type)
{
    gdt.descriptors[gdt_index].segment_type = (segment_type & 0x0F);
}

static void gdt_set_descriptor_type(int gdt_index, uint8_t descriptor_type)
{
    gdt.descriptors[gdt_index].descriptor_type = (descriptor_type & 0x01);
}

static void gdt_set_descriptor_previlge_level(int gdt_index, uint8_t previlege_level)
{
    gdt.descriptors[gdt_index].descriptor_privilege_level = (descriptor_type & (1 << 0 | 1 << 1));
}

static void gdt_set_segment_present(int gdt_index, bool is_present)
{
    gdt.descriptors[gdt_index].segment_present = (is_present) ? 1 : 0;
}

static void gdt_set_segment_is_64_bit(int gdt_index, bool is_64_bit)
{
    gdt.descriptors[gdt_index].is_64_bit = (is_64_bit) ? 1 : 0;
}

static void gdt_set_default_operation_size(int gdt_index, uint8_t operation_size)
{
    gdt.descriptors[gdt_index].default_operation_size = (operation_size & 0x01);
}

static void gdt_set_granulariy(int gdt_index, uint8_t granularity)
{
    gdt.descriptors[gdt_index].granularity = (granularity & 0x01);
}
