#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "klib.h"
#include "segment.h"

void segment_clear(segment_descriptor_t *segment)
{
    memset((unsigned char *)segment, 0, sizeof(segment_descriptor_t));
}

void segment_set_base(segment_descriptor_t *segment, uint32_t base)
{
    segment->base_low = (base & 0xFFFF);
    segment->base_middle = ((base >> 16) & 0xFF);
    segment->base_high = ((base >> 24) & 0xFF);
}

void segment_set_limit(segment_descriptor_t *segment, uint32_t limit)
{
    segment->limit_low = (limit & 0xFFFF);
    segment->limit_high = ((limit >> 16) & 0x0F);
}

void segment_set_segment_type(segment_descriptor_t *segment, uint8_t segment_type)
{
    segment->segment_type = (segment_type & 0x0F);
}

void segment_set_descriptor_type(segment_descriptor_t *segment, uint8_t descriptor_type)
{
    segment->descriptor_type = (descriptor_type & 0x01);
}

void segment_set_descriptor_previlge_level(segment_descriptor_t *segment,
        uint8_t previlege_level)
{
    segment->descriptor_privilege_level = (previlege_level  & (1 << 0 | 1 << 1));
}

void segment_set_segment_present(segment_descriptor_t *segment, bool is_present)
{
    segment->segment_present = (is_present) ? 1 : 0;
}

void segment_set_segment_is_64_bit(segment_descriptor_t *segment, bool is_64_bit)
{
    segment->is_64_bit = (is_64_bit) ? 1 : 0;
}

void segment_set_default_operation_size(segment_descriptor_t *segment,
        uint8_t operation_size)
{
    segment->default_operation_size = (operation_size & 0x01);
}

void segment_set_granulariy(segment_descriptor_t *segment, uint8_t granularity)
{
    segment->granularity = (granularity & 0x01);
}
