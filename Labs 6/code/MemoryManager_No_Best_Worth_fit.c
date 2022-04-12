#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>         // malloc & exit
#include <stdint.h>

#define FIRST_FIT	1
#define BEST_FIT	2
#define WORST_FIT   3

struct MEM_SEGMENT {
	int addr;
	int size;           // size of the segment in Bytes
	int free;           // bool - is segment free
	struct MEM_SEGMENT* next;
};

typedef struct MEM_SEGMENT mem_segment;

uint32_t  Num_segments;          // current number of segments

mem_segment* segment_list = NULL;     // global start of the list

/*
	Utilities:
		- print_segment_list
		- find_segment
		- free_segment
		- alloc_segment
*/

void print_segment_list()
{
	unsigned int num_seg = 1;

	mem_segment* curr_seg = segment_list;
	while (curr_seg)
	{
		printf(" Seg: %2d addr=%5d size=%3d %s \n", num_seg, curr_seg->addr,
			curr_seg->size, (curr_seg->free ? "FREE" : "NOT FREE"));

		curr_seg = curr_seg->next;
		num_seg++;

	}

	printf("\n\n\n");
}


// shared by all methods
mem_segment* find_segment(int size, uint32_t type)
{
	mem_segment* worth_segment = 0;
	mem_segment* best_segment = 0;
	mem_segment* curr_seg = segment_list;

	if (type > WORST_FIT)
	{
		printf("UNDEFINED FIT type: %d \n", type);
		exit(0);
	}

	if (type != FIRST_FIT)
	{
		printf("!!! Currently the only supported allocation policy is FIRST_FIT !!! \n");
	}

	while (curr_seg)
	{
		if ((curr_seg->size >= size) && curr_seg->free)
		{
			if (type == FIRST_FIT)
				return(curr_seg);

			/*
			if (!best_segment)  best_segment = curr_seg;
			else
				if (best_segment->size > curr_seg->size)
					best_segment = curr_seg;

			if (!worth_segment)  worth_segment = curr_seg;
			if (worth_segment->size < curr_seg->size)
				worth_segment = curr_seg;

				*/

		}

		curr_seg = curr_seg->next;
	}


}


void free_segment(mem_segment* seg)
{
	free(seg);
	Num_segments--;

	printf("free_segment: num segments = %d \n", Num_segments);
}

mem_segment* alloc_segment()
{
	mem_segment* new_seg;

	if (!(new_seg = (mem_segment*)malloc(sizeof(mem_segment))))
	{
		printf("alloc_segment: ERROR \n");
		exit(0);
	}

	Num_segments++;

	//  printf("alloc_segment: num segments = %d \n", Num_segments);
	return(new_seg);
}

//////////
void my_free(uint32_t addr)
{
	mem_segment* curr_seg = segment_list;
	mem_segment* prev_seg = NULL;

	while (curr_seg)
	{

		if (curr_seg->addr == addr)
		{
			curr_seg->free = 1;
			/* join with the next & prev
				3 cases:
					- single segment:  no need to join
					- first segment:  with the next (increase size + free the next + update pointers)
					- last one:  only with prev + free ...
			*/
			if (curr_seg->next != NULL)
			{
				// join with next (if free)
				if ((curr_seg->next)->free)
				{
					mem_segment* tmp_seg_ptr = curr_seg->next;   // save the segment to be freed
					curr_seg->size += (curr_seg->next)->size;
					curr_seg->next = (curr_seg->next)->next;
					free_segment(tmp_seg_ptr);
				}

			}

			if (prev_seg != NULL)
			{
				// join with prev (if free)
				if (prev_seg->free)
				{
					mem_segment* tmp_seg_ptr = curr_seg;   // save the segment to be freed
					prev_seg->size += curr_seg->size;
					prev_seg->next = curr_seg->next;
					free_segment(tmp_seg_ptr);
				}


			}

			return;
		}

		prev_seg = curr_seg;
		curr_seg = curr_seg->next;
	}

	printf("ERROR:  segment was not found !!!\n");
	exit(0);
}

//  return address 
int my_alloc(int size, uint32_t alloc_type)
{

	mem_segment* curr_seg;
	mem_segment* new_seg;

	// printf("my_alloc: size = %d type = %d \n", size, alloc_type);
	curr_seg = find_segment(size, alloc_type);

	if (curr_seg)
	{
		// if need add segment
		if (curr_seg->size > size)
		{
			new_seg = alloc_segment();

			// update the new segment
			new_seg->size = curr_seg->size - size;
			new_seg->addr = curr_seg->addr + size;
			new_seg->free = 1;
			new_seg->next = curr_seg->next;

			curr_seg->next = new_seg;
		}

		// update the allocated segment  (!!! this is the OLD segment)
		curr_seg->size = size;
		curr_seg->free = 0;

		return(curr_seg->addr);
	}

	return(0);
}


void main()
{
	unsigned int  curr_free, num_segments, curr_addr, i;
	int curr_size;
	mem_segment* curr_segment = NULL;
	mem_segment* prev_segment = NULL;
	int result_addr;

	// create first Segment 
	segment_list = alloc_segment();
	segment_list->addr = 0;
	segment_list->size = 278;			// according to the array of sizes
	segment_list->free = 1;
	segment_list->next = NULL;

	// static configuration
#define INIT_SEGMENTS   7
	int segment_size[INIT_SEGMENTS] = { 10, 40, 40, 8, 20, 60, 100 };
	int segment_free[INIT_SEGMENTS] = { 1,  0,   1, 0,  1,  0,   1 };
	int segment_addr[INIT_SEGMENTS];

	for (i = 0; i < INIT_SEGMENTS; i++)
	{
		segment_addr[i] = my_alloc(segment_size[i], FIRST_FIT);
	}

	for (i = 0; i < INIT_SEGMENTS; i++)
	{
		if (segment_free[i])
			my_free(segment_addr[i]);
	}

	print_segment_list();


	my_alloc(18, BEST_FIT);
	my_alloc(18, WORST_FIT);


}