#include <stdio.h>
#include <stdint.h>

typedef struct {
	uint8_t* buf;
	uint8_t* head;
	uint8_t* tail;
	uint32_t length;
}q_buffer_t;
q_buffer_t q_buffer[1];

int main(void) {
	while (1)
	{
		
	}
	return 0;
}

void qbufferInit(q_buffer_t* p_node, uint32_t len)
{
	p_node->head = 0;
	p_node->tail = 0;
	p_node->buf = 0;
	p_node->length = len;
}
bool qbufferWrite(uint8_t * p_buf, uint32_t len);
{

}
