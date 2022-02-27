﻿#include "job.h"

#include "logging.h"
#include "job_pool.h"
#include "converting.h"
#include "folder_handler.h"
#include "file_handler.h"

#ifndef __USE_TYPE_CONTAINER__
#include "cpprest/json.h"
#else
#include "container.h"
#include "values/string_value.h"
#endif

#include "fmt/xchar.h"
#include "fmt/format.h"

#include <future>

#ifdef __USE_CHAKRA_CORE__
#include "ChakraCore.h"
#endif

#ifdef __OSX__
#include <uuid/uuid.h>
#else
#include "crossguid/guid.hpp"
#endif

namespace threads
{
	using namespace logging;

#ifndef __USE_TYPE_CONTAINER__
	using namespace web;
#else
	using namespace container;
#endif

	using namespace converting;
	using namespace file_handler;
	using namespace folder_handler;

	job::job(const priorities& priority)
		: _priority(priority), _working_callback(nullptr), _working_callback2(nullptr), _temporary_stored(false), _temporary_stored_path(L""), _is_async_callback(false)
	{
	}

	job::job(const priorities& priority, const vector<unsigned char>& data, const bool& is_async_callback)
		: _priority(priority), _data(data), _working_callback(nullptr), _working_callback2(nullptr), _temporary_stored(false), _temporary_stored_path(L""), _is_async_callback(is_async_callback)
	{
	}

	job::job(const priorities& priority, const function<bool(void)>& working_callback, const bool& is_async_callback)
		: _priority(priority), _working_callback(working_callback), _working_callback2(nullptr), _temporary_stored(false), _temporary_stored_path(L""), _is_async_callback(is_async_callback)
	{
	}

	job::job(const priorities& priority, const vector<unsigned char>& data, const function<bool(const vector<unsigned char>&)>& working_callback, const bool& is_async_callback)
		: _priority(priority), _data(data), _working_callback(nullptr), _working_callback2(working_callback), _temporary_stored(false), _temporary_stored_path(L""), _is_async_callback(is_async_callback)
	{
	}

	job::~job(void)
	{
	}

	shared_ptr<job> job::get_ptr(void)
	{
		return shared_from_this();
	}

	const priorities job::priority(void)
	{
		return _priority;
	}

	void job::set_job_pool(shared_ptr<job_pool> job_pool)
	{
		_job_pool = job_pool;
	}

	bool job::work(const priorities& worker_priority)
	{
		load();

		if (_working_callback != nullptr)
		{
			if (_is_async_callback)
			{
				logger::handle().write(logging_level::sequence,
					fmt::format(L"attempt to call async callback function without value on job: job priority[{}], worker priority[{}]", (int)_priority, (int)worker_priority));

				async(launch::async, _working_callback);

				return true;
			}

			bool result = _working_callback();

			logger::handle().write(logging_level::sequence, 
				fmt::format(L"completed working callback function without value on job: job priority[{}], worker priority[{}]", (int)_priority, (int)worker_priority));

			return result;
		}

		if (_working_callback2 != nullptr)
		{
			if (_is_async_callback)
			{
				logger::handle().write(logging_level::sequence,
					fmt::format(L"attempt to call async callback function with value on job: job priority[{}], worker priority[{}]", (int)_priority, (int)worker_priority));

				async(launch::async, _working_callback2, _data);

				return true;
			}

			bool result = _working_callback2(_data);

			logger::handle().write(logging_level::sequence, 
				fmt::format(L"completed working callback function with value on job: job priority[{}], worker priority[{}]", (int)_priority, (int)worker_priority));

			return result;
		}

		if (!working(worker_priority))
		{
			logger::handle().write(logging_level::sequence, 
				fmt::format(L"cannot complete working function on job: job priority[{}], worker priority[{}]", (int)_priority, (int)worker_priority));

			return false;
		}

		return true;
	}

	void job::save(void)
	{
		_temporary_stored = true;

#ifdef __OSX__
		uuid_t uuidObj;
		uuid_generate(uuidObj);
		_temporary_stored_path = fmt::format(L"{}{}.job", folder::get_temporary_folder(), converter::to_wstring(string(uuidObj, uuidObj + 16)));
#else
		_temporary_stored_path = fmt::format(L"{}{}.job", folder::get_temporary_folder(), converter::to_wstring(xg::newGuid().str()));
#endif

		file::save(_temporary_stored_path, _data);
		_data.clear();
	}

	bool job::working(const priorities& worker_priority)
	{
#ifdef __USE_CHAKRA_CORE__
		auto start = logger::handle().chrono_start();

		shared_ptr<value_container> source_data = make_shared<value_container>(_data);
		if (source_data == nullptr)
		{
			return false;
		}

		wstring script = source_data->get_value(L"scripts")->to_string();
		if (script.empty())
		{
			logger::handle().write(logging_level::information, do_script(converter::to_wstring(_data)), start);

			return true;
		}

		if (source_data->message_type() == L"data_container")
		{
			logger::handle().write(logging_level::information, do_script(script), start);
		}
		else
		{
			shared_ptr<job_pool> current_job_pool = _job_pool.lock();
			if (current_job_pool != nullptr)
			{
				shared_ptr<value_container> target_data = source_data->copy(false);
				target_data->swap_header();
				target_data->add(make_shared<string_value>(L"script_result", do_script(script)));

				current_job_pool->push(make_shared<job>(_priority, target_data->serialize_array()));
				current_job_pool.reset();
			}
		}

		return true;
#else
		return false;
#endif
	}

	wstring job::do_script(const wstring& script)
	{
		try
		{
#ifdef __USE_CHAKRA_CORE__
			JsRuntimeHandle runtime;
			JsContextRef context;
			JsValueRef result;
			unsigned currentSourceContext = 0;

			JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);

			JsCreateContext(runtime, &context);
			JsSetCurrentContext(context);

			JsRunScript(script.c_str(), currentSourceContext++, L"", &result);

			JsValueRef resultJSString;
			JsConvertValueToString(result, &resultJSString);

			const wchar_t* resultWC;
			size_t stringLength;
			JsStringToPointer(resultJSString, &resultWC, &stringLength);

			wstring resultW(resultWC);

			JsSetCurrentContext(JS_INVALID_REFERENCE);
			JsDisposeRuntime(runtime);

			return resultW;
#else
			return L"";
#endif
		}
		catch (...)
		{
			return L"";
		}
	}

	void job::load(void)
	{
		if (!_temporary_stored)
		{
			return;
		}

		_data = file::load(_temporary_stored_path);
		file::remove(_temporary_stored_path);
	}
}