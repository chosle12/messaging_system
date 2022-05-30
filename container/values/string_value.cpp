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

#include "string_value.h"

#ifdef __USE_TYPE_CONTAINER__

#include "converting.h"

namespace container
{
	using namespace converting;

	string_value::string_value(void)
		: value()
	{
		_type = value_types::string_value;
	}

	string_value::string_value(const wstring& name, const wstring& value)
		: string_value()
	{
		wstring temp = value;
		converter::replace(temp, L"\r", L"</0x0A;>");
		converter::replace(temp, L"\n", L"</0x0B;>");
		converter::replace(temp, L" ", L"</0x0C;>");
		converter::replace(temp, L"\t", L"</0x0D;>");

		vector<unsigned char> data = converter::to_array(temp);

		_name = name;
		set_data(data.data(), data.size(), value_types::string_value);
	}

	string_value::~string_value(void)
	{
	}

	wstring string_value::to_string(const bool& original) const
	{
		if (!original)
		{
			return converter::to_wstring(_data);
		}

		wstring temp = converter::to_wstring(_data);
		converter::replace(temp, L"</0x0A;>", L"\r");
		converter::replace(temp, L"</0x0B;>", L"\n");
		converter::replace(temp, L"</0x0C;>", L" ");
		converter::replace(temp, L"</0x0D;>", L"\t");

		return temp;
	}
}

#endif