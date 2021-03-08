#ifndef _MEM_H_
#define _MEM_H_
#include "types.h"
#include "list.h"



void delete_node(struct list_header *head, struct list_block* delete_node);

void add_node(struct list_header *head, struct list_block *new_node, u32 could_merge);

void delete_node(struct list_header *head, struct list_block* delete_node);

void video_heap_init(struct mem_segment_t * segment);

u32  alloc_video_mem(struct mem_segment_t *segment, u32 size, u32 aligment);

u32  free_video_mem(struct mem_segment_t *segment, u32 aligned_offset);

void dump_segment(struct mem_segment_t *segment);

void init_video_memory(struct dpu_adapter_t *dpu_adapter);

void video_heap_deinit(struct mem_segment_t * segment);

void deinit_video_memory(struct dpu_adapter_t *dpu_adapter);
#endif