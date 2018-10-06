#ifndef PACKET_RECEIPT_HPP
#define PACKET_RECEIPT_HPP
/**
 * Packet reception module.
 *
 * Packets are pulled in an event-based way, and dequed once processed.
 * These packets are provided as start/end iterator pairs of type byte_type*.
 * Packets are only provided once they are complete, according to
 *  policy provided by a lambda.
 */

// TODO:
// Think about creating interfaces in platform/base.hpp, which are equivalent
//  to the lambdas.
// Handle erroneous conditions with some policy management system.
// Think about how destruction must work.
// Think about how the platform interface for networking must work.

namespace packet { class reception; }
class packet::reception
{
public:
	/*********************
	 ** CONSTANTS/TYPES **
	 *********************/

	using size_type = unsigned long;
	using byte_type = unsigned char;
	static constexpr size_type BUFFER_SIZE = 2048;

	/***************
	 ** CALLBACKS **
	 ***************/

	/* Policy interface: Returns end of complete packet, or 0. */
	using completed = size_type(*)(const char* begin, const char* end) noexcept;

	/* Synchronous wait on a read: -1 on error, 0 on close, or bytes read. */
	using sync_read = long(*)(const char* begin, unsigned long cap) noexcept;

	/***************
	 ** CTOR/DTOR **
	 ***************/
	reception() = delete;
	reception(completed cpl_test, sync_read pkt_read) :
		_buffer_data{cpl_test},
		_is_complete{pkt_read}
		{}

	/*************
	 ** METHODS **
	 *************/


	int block_read_packet(char*& begin, char*& end);

private:
	void      _reset(size_type remaining_start, size_type remaining_length);
	size_type _completed() { return _is_complete(_buffer, _buf_end()); }
	size_type _remaining() { return _buf_end() - _sec_end();           }

	/*
	 * Start and end of the logical section, which contains buffered data.
	 */
	char*     _sec_begin() { return _buffer + _start;       }
	char*     _sec_end()   { return _sec_begin() + _length; }
	char*     _buf_end()   { return _buffer + BUFFER_SIZE;  } /* End of buf. */
	char*     _buf_begin() { return _buffer;                }

	sync_read _buffer_data;
	completed _is_complete;

	bool      _needs_reset = false;
	size_type _start  = 0; /* Start of logical area.  */
	size_type _length = 0; /* Length of logical area. */
	byte_type _buffer[BUFFER_SIZE];
};

#endif /* PACKET_RECEIPT_HPP */
