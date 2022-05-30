/*****************************************************************************
BSD 3-Clause License

Copyright (c) 2021, 🍀☀🌕🌥 🌊
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#pragma once

#include "data_modes.h"
#include "data_lengths.h"

#include <vector>
#include <system_error>

#include "asio.hpp"

using namespace std;

namespace network
{
	class data_handling
	{
	public:
		data_handling(const unsigned char& start_code_value, const unsigned char& end_code_value);
		~data_handling(void);

	protected:
		void read_start_code(weak_ptr<asio::ip::tcp::socket> socket);
		void read_packet_code(weak_ptr<asio::ip::tcp::socket> socket);
		void read_length_code(const data_modes& packet_mode, weak_ptr<asio::ip::tcp::socket> socket);
		void read_data(const data_modes& packet_mode, const size_t& remained_length, weak_ptr<asio::ip::tcp::socket> socket);
		void read_end_code(const data_modes& packet_mode, weak_ptr<asio::ip::tcp::socket> socket);

	protected:
		bool send_on_tcp(weak_ptr<asio::ip::tcp::socket> socket, const data_modes& data_mode, const vector<unsigned char>& data);
		virtual void receive_on_tcp(const data_modes& data_mode, const vector<unsigned char>& data) = 0;

	protected:
		virtual void disconnected(void) = 0;

	protected:
		void append_binary_on_packet(vector<unsigned char>& result, const vector<unsigned char>& source);
		vector<unsigned char> devide_binary_on_packet(const vector<unsigned char>& source, size_t& index);

	private:
		char _start_code_tag[start_code];
		char _end_code_tag[end_code];
		char _receiving_buffer[buffer_size];
		vector<unsigned char> _received_data;
	};
}