#include <assert.h>

#include <segment.h>
void segment_clear_test();
void segment_set_base_test();
void segment_set_limit_test();
void segment_set_segment_type_test();
void segment_set_descriptor_type_test();
void segment_set_descriptor_previlge_level_test();
void segment_set_segment_present_test();
void segment_set_segment_is_64_bit_test();
void segment_set_default_operation_size_test();
void segment_set_granularity_test();

int main(int argc, char *argv[])
{
    assert(sizeof(segment_descriptor_t) == 8);

    segment_clear_test();
    segment_set_base_test();
    segment_set_limit_test();
    segment_set_segment_type_test();
    segment_set_descriptor_type_test();
    segment_set_descriptor_previlge_level_test();
    segment_set_segment_present_test();
    segment_set_segment_is_64_bit_test();
    segment_set_default_operation_size_test();
    segment_set_granularity_test();
}

void segment_clear_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(NULL) == false);
    assert(segment_clear(&segment));
    assert(segment.limit_low == 0);
    assert(segment.base_low == 0);
    assert(segment.base_middle == 0);
    assert(segment.segment_type == 0);
    assert(segment.descriptor_type == 0);
    assert(segment.descriptor_privilege_level == 0);
    assert(segment.segment_present == 0);
    assert(segment.limit_high == 0);
    assert(segment.reserved == 0);
    assert(segment.is_64_bit == 0);
    assert(segment.default_operation_size == 0);
    assert(segment.granularity == 0);
    assert(segment.base_high == 0);
}
void segment_set_base_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_base(NULL, 0) == false);
    assert(segment_set_base(&segment, 0x12345678));
    assert(segment.base_low == 0x5678);
    assert(segment.base_middle == 0x34);
    assert(segment.base_high == 0x12);
    assert(segment.limit_low == 0);
    assert(segment.segment_type == 0);
    assert(segment.descriptor_type == 0);
    assert(segment.descriptor_privilege_level == 0);
    assert(segment.segment_present == 0);
    assert(segment.limit_high == 0);
    assert(segment.reserved == 0);
    assert(segment.is_64_bit == 0);
    assert(segment.default_operation_size == 0);
    assert(segment.granularity == 0);
}
void segment_set_limit_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_limit(NULL, 0) == false);
    assert(segment_set_limit(&segment, 0x00012345));
    assert(segment.limit_low == 0x2345);
    assert(segment.base_low == 0);
    assert(segment.base_middle == 0);
    assert(segment.segment_type == 0);
    assert(segment.descriptor_type == 0);
    assert(segment.descriptor_privilege_level == 0);
    assert(segment.segment_present == 0);
    assert(segment.limit_high == 0x1);
    assert(segment.reserved == 0);
    assert(segment.is_64_bit == 0);
    assert(segment.default_operation_size == 0);
    assert(segment.granularity == 0);
    assert(segment.base_high == 0);

    assert(segment_clear(&segment));

    assert(segment_set_limit(&segment, 0x12345678));
    assert(segment.limit_low == 0x5678);
    assert(segment.base_low == 0);
    assert(segment.base_middle == 0);
    assert(segment.segment_type == 0);
    assert(segment.descriptor_type == 0);
    assert(segment.descriptor_privilege_level == 0);
    assert(segment.segment_present == 0);
    assert(segment.limit_high == 0x4);
    assert(segment.reserved == 0);
    assert(segment.is_64_bit == 0);
    assert(segment.default_operation_size == 0);
    assert(segment.granularity == 0);
    assert(segment.base_high == 0);
}
void segment_set_segment_type_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_segment_type(NULL, 0x0) == false);
    assert(segment_set_segment_type(&segment, SEG_CODE_EXRDCA));
    assert(segment.segment_type = SEG_CODE_EXRDCA);

}
void segment_set_descriptor_type_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_descriptor_type(NULL, 0x0) == false);
    assert(segment_set_descriptor_type(&segment, DESC_TYPE_CODE));
    assert(segment.descriptor_type == DESC_TYPE_CODE);

    assert(segment_clear(&segment));
    assert(segment_set_descriptor_type(&segment, 0xFF) == false);
}
void segment_set_descriptor_previlge_level_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_descriptor_previlge_level(NULL, 0x0) == false);
    assert(segment_set_descriptor_previlge_level(&segment, PREVILEGE_LEVEL_ZERO));
    assert(segment.descriptor_privilege_level == 0);
    assert(segment_set_descriptor_previlge_level(&segment, PREVILEGE_LEVEL_THREE));
    assert(segment.descriptor_privilege_level == 0x3);
    assert(segment_set_descriptor_previlge_level(&segment, 0x4) == false);
}
void segment_set_segment_present_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_segment_present(NULL, false) == false);
    assert(segment_set_segment_present(&segment, false));
    assert(segment.segment_present == 0x0);
    assert(segment_set_segment_present(&segment, true));
    assert(segment.segment_present == 0x1);
}
void segment_set_segment_is_64_bit_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_segment_is_64_bit(NULL, false) == false);
    assert(segment_set_segment_is_64_bit(&segment, false));
    assert(segment.is_64_bit == 0x0);
    assert(segment_set_segment_is_64_bit(&segment, true));
    assert(segment.is_64_bit == 0x1);
}
void segment_set_default_operation_size_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_default_operation_size(NULL, false) == false);
    assert(segment_set_default_operation_size(&segment, DEFAULT_16_BIT_SEG));
    assert(segment.default_operation_size == DEFAULT_16_BIT_SEG);
    assert(segment_set_default_operation_size(&segment, DEFAULT_32_BIT_SEG));
    assert(segment.default_operation_size == DEFAULT_32_BIT_SEG);
    assert(segment_set_default_operation_size(&segment, 0x4) == false);
}
void segment_set_granularity_test()
{
    segment_descriptor_t segment;

    assert(segment_clear(&segment));

    assert(segment_set_granularity(NULL, false) == false);
    assert(segment_set_granularity(&segment, GRANULARITY_1B));
    assert(segment.granularity == GRANULARITY_1B);
    assert(segment_set_granularity(&segment, GRANULARITY_4KB));
    assert(segment.granularity == GRANULARITY_4KB);
    assert(segment_set_default_operation_size(&segment, 0x4) == false);
}

