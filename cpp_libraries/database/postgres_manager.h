#include "database.h"

namespace database
{
    class postgres_manager : public database
    {
    public:
        postgres_manager();
        virtual ~postgres_manager();

    public:
        database_types database_type(void) override;
        bool connect(const wstring& connect_string) override;
        bool create_query(const wstring& query_string) override;
        unsigned int insert_query(const wstring& query_string) override;
        unsigned int update_query(const wstring& query_string) override;
        unsigned int delete_query(const wstring& query_string) override;
#ifndef __USE_TYPE_CONTAINER__
        shared_ptr<json::value> select_query(const wstring& query_string) override;
#else
        shared_ptr<container::value_container> select_query(const wstring& query_string) override;
#endif
        bool disconnect(void) override;

    private:
        void* query_result(const wstring& query_string);

    private:
        void *_connection;
    };
};