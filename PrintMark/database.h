#ifndef database_h__
#define database_h__

namespace _Database
{
	bool check(const char* sn, time_t& t);		// return datetime in qint64
	bool deposit(const char*sn);
	bool count(__int64& c);
	bool purge();
	const char* getmsg();
};

#endif // database_h__
