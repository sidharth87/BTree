/*
 * join
 * Copyright (c) Sidharth Kumar, et al, see License.md
 */



#ifndef PARALLEL_JOIN_H
#define PARALLEL_JOIN_H


class parallel_join: public parallel_RA {

private:

    relation* join_input0_table;
    int join_input0_graph_type;

    relation* join_input1_table;
    int join_input1_graph_type;

    relation* join_output_table;

    std::vector<int> projection_reorder_index_array;
    int projection_reorder_index_array_length;

public:
    parallel_join()
    {
        RA_type = JOIN;
    }

    parallel_join(relation* output, relation* G, int G_type, relation* T, int T_type, std::vector<int> projection_reorder_index_array)
        : join_input0_table(G), join_input0_graph_type(G_type), join_input1_table(T), join_input1_graph_type(T_type), join_output_table(output), projection_reorder_index_array(projection_reorder_index_array)  {
        RA_type = JOIN;
    }


    relation* get_join_input0() {return join_input0_table;}
    int get_join_input0_graph_type()    {return join_input0_graph_type;}
    relation* get_join_input1() {return join_input1_table;}
    int get_join_input1_graph_type()    {return join_input1_graph_type;}
    relation* get_join_output() {return join_output_table;}
    void get_join_projection_index(std::vector<int>* projection_reorder_index_array)    {*projection_reorder_index_array = this->projection_reorder_index_array; }


    void local_join(int join_order,
                    u32 buckets,
                    int input0_buffer_size, int input0_buffer_width, u64 *input0_buffer,
                    google_relation **input1, u32 i1_size, int input1_buffer_width,
                    std::vector<int> reorder_map_array,
                    relation* output,
                    all_to_all_buffer& join_buffer,
                    int counter,
                    int join_colun_count,
                    u32* local_join_duplicates,
                    u32* local_join_inserts);
};


#endif
