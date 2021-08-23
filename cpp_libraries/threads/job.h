#pragma once

#include "job_priorities.h"

#include <memory>
#include <vector>
#include <functional>

namespace threads
{
	class job_pool;
	class job : public std::enable_shared_from_this<job>
	{
	public:
		job(const priorities& priority);
		job(const priorities& priority, const std::vector<unsigned char>& data);
		job(const priorities& priority, const std::function<bool(void)>& working_callback);
		job(const priorities& priority, const std::vector<unsigned char>& data, const std::function<bool(const std::vector<unsigned char>&)>& working_callback);
		~job(void);

	public:
		std::shared_ptr<job> get_ptr(void);

	public:
		const priorities priority(void);

	public:
		void set_job_pool(std::shared_ptr<job_pool> job_pool);

	public:
		bool work(const priorities& worker_priority);

	protected:
		virtual bool working(const priorities& worker_priority);

	private:
		std::wstring do_script(const std::wstring& script);

	private:
		priorities _priority;
		std::vector<unsigned char> _data;
		std::weak_ptr<job_pool> _job_pool;
		std::function<bool(void)> _working_callback;
		std::function<bool(const std::vector<unsigned char>&)> _working_callback2;
	};
}