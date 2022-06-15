﻿/*****************************************************************************
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

#include "compressing.h"

#include "logging.h"
#include "converting.h"
#include "file_handler.h"
#include "folder_handler.h"

#include "lz4.h"

#include "fmt/format.h"
#include "fmt/xchar.h"

#include <algorithm>
#include <filesystem>

namespace compressing
{
	using namespace logging;
	using namespace converting;
	using namespace file_handler;
	using namespace folder_handler;

	vector<uint8_t> compressor::compression(const vector<uint8_t>& original_data, const unsigned short& block_bytes)
	{
		if (original_data.empty())
		{
			return original_data;
		}

		LZ4_stream_t lz4Stream_body;
		size_t read_index = 0;
		int source_buffer_index = 0;

		vector<vector<char>> source_buffer;
		source_buffer.push_back(vector<char>());
		source_buffer.push_back(vector<char>());
		source_buffer[0].reserve(block_bytes);
		source_buffer[1].reserve(block_bytes);

		int compress_size = LZ4_COMPRESSBOUND(block_bytes);
		vector<char> compress_buffer;
		compress_buffer.reserve(compress_size);
		vector<uint8_t> compressed_data;

		char compress_size_data[4];

		LZ4_resetStream(&lz4Stream_body);

		while (true) {
			char* const source_buffer_pointer = source_buffer[source_buffer_index].data();
			memset(source_buffer_pointer, 0, sizeof(char) * block_bytes);

			const size_t inpBytes = ((original_data.size() - read_index) > block_bytes) ? block_bytes : (original_data.size() - read_index);
			if (0 == inpBytes) {
				break;
			}

			memcpy(source_buffer_pointer, original_data.data() + read_index, sizeof(char) * inpBytes);

			{
				char* const compress_buffer_pointer = compress_buffer.data();
				memset(compress_buffer_pointer, 0, sizeof(char) * compress_size);

				const int compressed_size = LZ4_compress_fast_continue(&lz4Stream_body, (const char*)source_buffer_pointer, (char*)compress_buffer_pointer, (int)inpBytes, compress_size, 1);
				if (compressed_size <= 0) {
					break;
				}

				memcpy(compress_size_data, &compressed_size, sizeof(int));

				compressed_data.insert(compressed_data.end(), compress_size_data, compress_size_data + sizeof(int));
				compressed_data.insert(compressed_data.end(), compress_buffer_pointer, compress_buffer_pointer + compressed_size);
			}

			read_index += inpBytes;
			source_buffer_index = (source_buffer_index + 1) % 2;
		}

		source_buffer[0].clear();
		source_buffer[1].clear();
		source_buffer.clear();
		
		if (compressed_data.size() == 0)
		{
			logger::handle().write(logging_level::error, L"cannot complete to compress data");

			return vector<uint8_t>();
		}
		
		logger::handle().write(logging_level::sequence, fmt::format(L"compressing(buffer {}): ({} -> {} : {:.2f} %)", 
			block_bytes, original_data.size(), compressed_data.size(), (((double)compressed_data.size() / (double)original_data.size()) * 100)));

		return compressed_data;
	}

	vector<uint8_t> compressor::decompression(const vector<uint8_t>& compressed_data, const unsigned short& block_bytes)
	{
		if (compressed_data.empty())
		{
			return compressed_data;
		}

		LZ4_streamDecode_t lz4StreamDecode_body;

		int read_index = 0;
		int compressed_size = 0;

		int target_buffer_index = 0;

		vector<vector<char>> target_buffer;
		target_buffer.push_back(vector<char>());
		target_buffer.push_back(vector<char>());
		target_buffer[0].reserve(block_bytes);
		target_buffer[1].reserve(block_bytes);

		int compress_size = LZ4_COMPRESSBOUND(block_bytes);
		vector<char> compress_buffer;
		compress_buffer.reserve(compress_size);
		vector<uint8_t> decompressed_data;

		LZ4_setStreamDecode(&lz4StreamDecode_body, NULL, 0);

		while (true) {
			char* const compress_buffer_pointer = compress_buffer.data();

			memset(compress_buffer_pointer, 0, sizeof(char) * compress_size);
			if ((compressed_data.size() - read_index) < 1) {
				break;
			}

			memcpy(&compressed_size, compressed_data.data() + read_index, sizeof(int));
			if (0 >= compressed_size) {
				break;
			}

			read_index += sizeof(int);
			memcpy(compress_buffer_pointer, compressed_data.data() + read_index, sizeof(char) * compressed_size);
			read_index += compressed_size;
			
			char* const target_buffer_pointer = target_buffer[target_buffer_index].data();
			const int decompressed_size = LZ4_decompress_safe_continue(&lz4StreamDecode_body, (const char*)compress_buffer_pointer, 
				(char*)target_buffer_pointer, compressed_size, block_bytes);
			if (decompressed_size <= 0) {
				break;
			}

			decompressed_data.insert(decompressed_data.end(), target_buffer_pointer, target_buffer_pointer + decompressed_size);

			target_buffer_index = (target_buffer_index + 1) % 2;
		}

		target_buffer[0].clear();
		target_buffer[1].clear();
		target_buffer.clear();
		
		if (decompressed_data.size() == 0)
		{
			logger::handle().write(logging_level::error, L"cannot complete to decompress data");

			return vector<uint8_t>();
		}

		logger::handle().write(logging_level::sequence, fmt::format(L"decompressing(buffer {}): ({} -> {} : {:.2f} %)",
			block_bytes, compressed_data.size(), decompressed_data.size(), (((double)compressed_data.size() / (double)decompressed_data.size()) * 100)));

		return decompressed_data;
	}
	
	bool compressor::compression_folder(const wstring& target_file, const wstring& root_path, const wstring& folder_path, 
		const bool& contain_sub_folder, const unsigned short& block_bytes, const wstring& file_header,
		const function<void(vector<uint8_t>&, const wstring&, const vector<uint8_t>&)>& compression_rule)
	{
		logger::handle().write(logging_level::parameter,
			fmt::format(L"attempt to compress folder: {} -> {}", folder_path, target_file)
		);

		if(target_file.empty())
		{
			return false;
		}
		
		if(!filesystem::exists(root_path))
		{
			return false;
		}

		wstring temp;
		vector<uint8_t> result;

		if(root_path == folder_path)
		{
			auto header = converter::to_array(file_header);
			result.insert(result.end(), header.begin(), header.end());
		}

		auto files = folder::get_files(folder_path, false);
		for (auto& file : files)
		{
			temp = file;
			converter::replace(temp, root_path, L"");
#ifdef _WIN32
			converter::replace(temp, L"\\", L"/");
#endif

			vector<uint8_t> temp_buffer;
			if(compression_rule == nullptr)
			{
				append_binary(temp_buffer, converter::to_array(temp));
				append_binary(temp_buffer, file::load(file));
			}
			else
			{
				compression_rule(temp_buffer, temp, file::load(file));
			}

			append_binary(result, compression(temp_buffer, block_bytes));
		}

		if (!result.empty())
		{
			file::append(target_file, result);
		}

		if (!contain_sub_folder)
		{
			return true;
		}

		auto folders = folder::get_folders(folder_path);
		for (auto& folder : folders)
		{
			compression_folder(target_file, root_path, folder, contain_sub_folder, block_bytes, file_header, compression_rule);
		}

		return true;
	}
	
	bool compressor::decompression_folder(const wstring& source_path, const wstring& target_path, const unsigned short& block_bytes,
		const wstring& file_header, const function<void(const vector<uint8_t>&, const wstring&, wstring&, vector<uint8_t>&)>& decompression_rule)
	{
		logger::handle().write(logging_level::parameter,
			fmt::format(L"attempt to decompress folder: {} -> {}", source_path, target_path)
		);

		if (!folder::create_folder(target_path))
		{
			logger::handle().write(logging_level::sequence,
				fmt::format(L"created folder: {}", target_path)
			);

			return false;
		}

		auto source = file::load(source_path);
		if (source.empty())
		{
			return false;
		}

		auto header = converter::to_array(file_header);
		if (!equal(source.begin(), source.begin() + header.size(), header.begin()))
		{
			return false;
		}

		wstring file_path;
		vector<uint8_t> file_data;
		size_t index = header.size();
		size_t count = source.size();
		while (index < count)
		{
			vector<uint8_t> temp;
			temp = devide_binary(source, index);
			temp = decompression(temp, block_bytes);

			if(decompression_rule == nullptr)
			{
				size_t index2 = 0;
				file_path = fmt::format(L"{}{}", target_path, converter::to_wstring(devide_binary(temp, index2)));
				file_data = devide_binary(temp, index2);
			}
			else
			{
				file_path = L"";
				file_data.clear();
				decompression_rule(temp, target_path, file_path, file_data);
			}

			file::save(file_path, file_data);
		}

		return true;
	}

	void compressor::append_binary(vector<uint8_t>& result, const vector<uint8_t>& source)
	{
		size_t temp;
		const int size = sizeof(size_t);
		char temp_size[size];

		temp = source.size();
		memcpy(temp_size, (char*)&temp, size);
		result.insert(result.end(), temp_size, temp_size + size);
		if (temp == 0)
		{
			return;
		}

		result.insert(result.end(), source.begin(), source.end());
	}

	vector<uint8_t> compressor::devide_binary(const vector<uint8_t>& source, size_t& index)
	{
		if (source.empty())
		{
			return vector<uint8_t>();
		}

		size_t temp;
		const int size = sizeof(size_t);

		if (source.size() < index + size)
		{
			return vector<uint8_t>();
		}

		memcpy(&temp, source.data() + index, size);
		index += size;

		if (temp == 0 || source.size() < index + temp)
		{
			return vector<uint8_t>();
		}

		vector<uint8_t> result;
		result.insert(result.end(), source.begin() + index, source.begin() + index + temp);
		index += temp;

		return result;
	}
}
