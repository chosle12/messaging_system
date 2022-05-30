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

#include "llong_value.h"

#ifdef __USE_TYPE_CONTAINER__

#include "fmt/xchar.h"
#include "fmt/format.h"

namespace container
{
	llong_value::llong_value(void)
		: value()
	{
		_type = value_types::llong_value;
	}

	llong_value::llong_value(const wstring& name, const long long& value)
		: llong_value()
	{
		_name = name;
		set_data((const unsigned char*)&value, sizeof(long long), value_types::llong_value);
	}

	llong_value::~llong_value(void)
	{
	}

	short llong_value::to_short(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<short>(temp);
	}

	unsigned short llong_value::to_ushort(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<unsigned short>(temp);
	}

	int llong_value::to_int(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<int>(temp);
	}

	unsigned int llong_value::to_uint(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<unsigned int>(temp);
	}

	long llong_value::to_long(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<long>(temp);
	}

	unsigned long llong_value::to_ulong(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<unsigned long>(temp);
	}

	long long llong_value::to_llong(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<long long>(temp);
	}

	unsigned long long llong_value::to_ullong(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<unsigned long long>(temp);
	}

	float llong_value::to_float(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<float>(temp);
	}

	double llong_value::to_double(void) const
	{
		long long temp = 0;
		memcpy(&temp, _data.data(), _size);

		return static_cast<double>(temp);
	}

	wstring llong_value::to_string(const bool&) const
	{
		return fmt::format(L"{}", to_llong());
	}
}

#endif