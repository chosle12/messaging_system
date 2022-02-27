#include "file_manager.h"

#include "value.h"
#include "values/bool_value.h"
#include "values/ushort_value.h"
#include "values/ullong_value.h"
#include "values/string_value.h"

file_manager::file_manager(void)
{

}

file_manager::~file_manager(void)
{

}

bool file_manager::set(const wstring& indication_id, const vector<wstring>& file_list)
{
	auto target = _transferring_list.find(indication_id);
	if (target != _transferring_list.end())
	{
		return false;
	}

	_transferring_list.insert({ indication_id, file_list });
	_transferred_list.insert({ indication_id, vector<wstring>() });
	_failed_list.insert({ indication_id, vector<wstring>() });
	_transferred_percentage.insert({ indication_id, 0 });

	return true;
}

#ifndef __USE_TYPE_CONTAINER__
shared_ptr<json::value> file_manager::received(const wstring& target_id, const wstring& target_sub_id,
	const wstring& indication_id, const wstring& file_path)
#else
shared_ptr<container::value_container> file_manager::received(const wstring& target_id, const wstring& target_sub_id,
	const wstring& indication_id, const wstring& file_path)
#endif
{
	auto source = _transferring_list.find(indication_id);
	if (source == _transferring_list.end())
	{
		return nullptr;
	}

	auto target = _transferred_list.find(indication_id);
	if (target == _transferred_list.end())
	{
		return nullptr;
	}

	auto fail = _failed_list.find(indication_id);
	if (fail == _failed_list.end())
	{
		return nullptr;
	}

	auto percentage = _transferred_percentage.find(indication_id);
	if (percentage == _transferred_percentage.end())
	{
		return nullptr;
	}

	if (file_path.empty())
	{
		fail->second.push_back(file_path);
	}
	else
	{
		target->second.push_back(file_path);
	}

	unsigned short temp = (unsigned short)(((double)target->second.size() / (double)source->second.size()) * 100);
	if (percentage->second != temp)
	{
		percentage->second = temp;

		if (temp == 100)
		{
			_transferring_list.erase(source);
			_transferred_list.erase(target);
			_failed_list.erase(fail);
			_transferred_percentage.erase(percentage);
		}

#ifndef __USE_TYPE_CONTAINER__
		shared_ptr<json::value> container = make_shared<json::value>();

		(*container)[L"header"][L"target_id"] = json::value::string(target_id);
		(*container)[L"header"][L"target_sub_id"] = json::value::string(target_sub_id);
		(*container)[L"header"][L"message_type"] = json::value::string(L"transfer_condition");

		(*container)[L"data"][L"indication_id"] = json::value::string(indication_id);
		(*container)[L"data"][L"percentage"] = json::value::number(temp);

		return container;
#else
		return make_shared<container::value_container>(target_id, target_sub_id, L"transfer_condition",
			vector<shared_ptr<container::value>> {
				make_shared<container::string_value>(L"indication_id", indication_id),
				make_shared<container::ushort_value>(L"percentage", temp)
		});
#endif
	}
	
	if (source->second.size() == (target->second.size() + fail->second.size()))
	{
		size_t completed = target->second.size();
		size_t failed = fail->second.size();

		_transferring_list.erase(source);
		_transferred_list.erase(target);
		_failed_list.erase(fail);
		_transferred_percentage.erase(percentage);

#ifndef __USE_TYPE_CONTAINER__
		shared_ptr<json::value> container = make_shared<json::value>();

		(*container)[L"header"][L"target_id"] = json::value::string(target_id);
		(*container)[L"header"][L"target_sub_id"] = json::value::string(target_sub_id);
		(*container)[L"header"][L"message_type"] = json::value::string(L"transfer_condition");

		(*container)[L"data"][L"indication_id"] = json::value::string(indication_id);
		(*container)[L"data"][L"percentage"] = json::value::number(temp);
		(*container)[L"data"][L"completed_count"] = json::value::number(completed);
		(*container)[L"data"][L"failed_count"] = json::value::number(failed);
		(*container)[L"data"][L"completed"] = json::value::boolean(true);

		return container;
#else
		return make_shared<container::value_container>(target_id, target_sub_id, L"transfer_condition",
			vector<shared_ptr<container::value>> {
				make_shared<container::string_value>(L"indication_id", indication_id),
				make_shared<container::ushort_value>(L"percentage", temp),
				make_shared<container::ullong_value>(L"completed_count", completed),
				make_shared<container::ullong_value>(L"failed_count", failed),
				make_shared<container::bool_value>(L"completed", true)
		});
#endif
	}

	return nullptr;
}