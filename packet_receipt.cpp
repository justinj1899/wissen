#include "packet_receipt.hpp"

#include <cassert.h>
#include <cstdlib.h>

void packet::reception::_reset(size_type start, size_type len)
{
	assert(len <= BUFFER_SIZE - _start);

	/* Move the read portion to the front if necessary. */
	if (start >= BUFFER_SIZE / 2) {
		memmove(_buf_start(), _buffer_start() + start, len);
		_start  = 0;
		_length = len;
	}
}

int packet::reception::block_read_packet(char*& begin, char*& end)
{
	/* We may need to reorganize the buffer if there remains content on it. */
	if (_needs_reset) this->reset(_start, _length);

	long chunk_end;
	switch (chunk_end = _buffer_data(_sec_end(), _buf_end())) {
	case -1: return -1; /* ERROR */
	case  0: return  0; /* Connection closed */
	default:            /* Successful read of N bytes. */
	{
		assert(chunk_amnt > 0);
		assert(chunk_amnt <= _remaining());

		_length += chunk_amnt;

		auto logical_end = _completed();
		if (packet_end) {

			/* Publish the packet. */
			begin = _sec_begin();
			end   = _sec_begin() + logical_end;

			/*
			 * Leave the remainder in the buffer, and reorganize the buffer
			 *  when control is yielded back to this function.
			 */

			/* The end of this logical unit, is the start of the next one. */
			this->_start += logical_end;

			/*
			 * Once the packet is published,
			 * we have less data left for processing.
			 */
			this->_length -= logical_end;
			_needs_reset = true;
		}

	}
		break;
	}
}
