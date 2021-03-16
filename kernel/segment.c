#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "klib.h"
#include "segment.h"

bool segment_clear(segment_descriptor_t *segment)
{
    if (!segment) {
        return false;
    }
    memset((unsigned char *)segment, 0, sizeof(segment_descriptor_t));
    return true;
}

bool segment_set_base(segment_descriptor_t *segment, uint32_t base)
{
    if (!segment) {
        return false;
    }
    segment->base_low = (base & 0xFFFF);
    segment->base_middle = ((base >> 16) & 0xFF);
    segment->base_high = ((base >> 24) & 0xFF);
    return true;
}

bool segment_set_limit(segment_descriptor_t *segment, uint32_t limit)
{
    if (!segment) {
        return false;
    }
    segment->limit_low = (limit & 0xFFFF);
    segment->limit_high = ((limit >> 16) & 0x0F);
    return true;
}

bool segment_set_segment_type(segment_descriptor_t *segment, uint8_t segment_type)
{
    if (!segment || segment_type > 0x0F) {
        return false;
    }
    segment->segment_type = (segment_type & 0x0F);
    return true;
}

bool segment_set_descriptor_type(segment_descriptor_t *segment, uint8_t descriptor_type)
{
    if (!segment) {
        return false;
    }
    if (descriptor_type != DESC_TYPE_SYSTEM && 
            descriptor_type != DESC_TYPE_CODE && 
            descriptor_type != DESC_TYPE_DATA) {
        return false;
    }
    segment->descriptor_type = (descriptor_type & 0x01);
    return true;
}

bool segment_set_descriptor_previlge_level(segment_descriptor_t *segment,
        uint8_t previlege_level)
{
    if (!segment || previlege_level > PREVILEGE_LEVEL_THREE) {
        return false;
    }
    segment->descriptor_privilege_level = (previlege_level  & (1 << 0 | 1 << 1));
    return true;
}

bool segment_set_segment_present(segment_descriptor_t *segment, bool is_present)
{
    if (!segment) {
        return false;
    }
    segment->segment_present = (is_present) ? 1 : 0;
    return true;
}

bool segment_set_segment_is_64_bit(segment_descriptor_t *segment, bool is_64_bit)
{
    if (!segment) {
        return false;
    }
    segment->is_64_bit = (is_64_bit) ? 1 : 0;
    return true;
}

bool segment_set_default_operation_size(segment_descriptor_t *segment,
        uint8_t operation_size)
{
    if (!segment || (operation_size != DEFAULT_16_BIT_SEG && 
                operation_size != DEFAULT_32_BIT_SEG) ) {
        return false;
    }
    segment->default_operation_size = (operation_size & 0x01);
    return true;
}

bool segment_set_granularity(segment_descriptor_t *segment, uint8_t granularity)
{
    if (!segment || (granularity != GRANULARITY_1B && granularity != GRANULARITY_4KB) ) {
        return false;
    }
    segment->granularity = (granularity & 0x01);
    return true;
}
