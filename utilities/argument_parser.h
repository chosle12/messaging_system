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

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace argument_parser
{
	class argument_manager
	{
	public:
		argument_manager(void);
		argument_manager(const string& arguments);
		argument_manager(const wstring& arguments);
		argument_manager(int argc, char* argv[]);
		argument_manager(int argc, wchar_t* argv[]);

	public:
		wstring to_string(const wstring& key);

	public:
		bool to_bool(const wstring& key);
		short to_short(const wstring& key);
		unsigned short to_ushort(const wstring& key);
		int to_int(const wstring& key);
		unsigned int to_uint(const wstring& key);
#ifdef _WIN32
		long long to_llong(const wstring& key);
		unsigned long long to_ullong(const wstring& key);
#else
		long to_long(const wstring& key);
		unsigned long to_ulong(const wstring& key);
#endif

	protected:
		map<wstring, wstring> parse(int argc, char* argv[]);
		map<wstring, wstring> parse(int argc, wchar_t* argv[]);

	private:
		map<wstring, wstring> parse(const vector<wstring>& arguments);

	private:
		map<wstring, wstring> _arguments;
	};
}

