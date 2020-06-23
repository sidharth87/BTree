#include "../parallel_RA_inc.h"

void parallel_join::local_join( u32 buckets,
                int input0_buffer_size, int input0_buffer_width, u64 *input0_buffer, int join_order,
                google_relation *input1, u32 i1_size, int input1_buffer_width,
                std::vector<int> reorder_map_array,
                relation* output,
                all_to_all_buffer& join_buffer,
                int counter,
                int join_column_count,
                u32* local_join_duplicates,
                u32* local_join_inserts)
{
    int projection_column_count = 0;
    for (int x : reorder_map_array)
        if (x == -1)
            projection_column_count++;
    join_buffer.ra_size[counter] = input0_buffer_width + input1_buffer_width - join_column_count - projection_column_count;

    google_relation deduplicate;
    u32* output_sub_bucket_count = output->get_sub_bucket_per_bucket_count();
    u32** output_sub_bucket_rank = output->get_sub_bucket_rank();

    for (int k1 = 0; k1 < input0_buffer_size; k1 = k1 + input0_buffer_width)  {
        std::vector<u64> prefix;
        for (int jc=0; jc < join_column_count; jc++)
            prefix.push_back(input0_buffer[k1 + jc]);

        u64 bucket_id = tuple_hash(input0_buffer + k1, join_column_count) % buckets;
        input1[bucket_id].as_all_to_all_join_buffer(prefix, join_buffer,input0_buffer + k1,input0_buffer_width,counter, buckets, output_sub_bucket_count, output_sub_bucket_rank, reorder_map_array, projection_column_count, join_column_count, deduplicate, local_join_duplicates, local_join_inserts);
    }

    deduplicate.remove_tuple();

    return;
}
