#include "stdafx.h"
#define SQLITE_HAS_CODEC
#include "sqlite3.h"
#include "database.h"
#include <time.h>

#pragma comment(lib, "sqlite.lib")

#if 0
sqlite3 *pdb = 0;
sqlite3_stmt *pstmt = 0;

int ret;
const char *error = 0;
char *sql = "SELECT sn FROM keys WHERE sn = ?;";

char keyfile[1024] = {0,};
wchar_t _keyfile[1024] = {0};
strcpy(keyfile, moduleFile);
char* p = strrchr(keyfile, '\\');
if(p != NULL)
	strcpy(p+1, "RoLink.dll");
else
	strcpy(keyfile, "RoLink.dll");

MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, keyfile, sizeof(keyfile), _keyfile, 1024);
WideCharToMultiByte(CP_UTF8, 0, _keyfile, -1, keyfile, 1024, NULL, NULL);

ret = sqlite3_open(keyfile, &pdb);
ret = sqlite3_key(pdb, "339D9CF6", 8);
ret = sqlite3_prepare_v2(pdb, sql, strlen(sql), &pstmt, &error);
if (ret != SQLITE_OK)
{
	sqlite3_close(pdb);
	return 1000;
}

ret = sqlite3_bind_text(pstmt, 1, sn, strlen(sn), SQLITE_STATIC);
if (ret == SQLITE_OK)
{
	// Create an array of instant cameras for the found devices and avoid exceeding a maximum number of devices.
	//CInstantCameraArray cameras( min( devices.size(), c_maxCamerasToUse));

	if(SQLITE_ROW != sqlite3_step(pstmt))
	{
		//if(strcmp(devices[index].GetSerialNumber(), (char*)sqlite3_column_text(pstmt, 0)) == 0)
		{
			FCAM_StopCapture(m_hDevice);
			FCAM_ReleaseDevice(m_hDevice);
			m_hDevice = NULL;

			sqlite3_finalize(pstmt);
			sqlite3_close(pdb);
			return 1001;
		}
	}
}

sqlite3_finalize(pstmt);
sqlite3_close(pdb);

void f()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sqlText[4096] = {0,};

	rc = sqlite3_open(":memory:", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	//rc = sqlite3_exec(db, "select sqlite_version(*)", callback, 0, &zErrMsg);
	//if( rc!=SQLITE_OK ){
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	/* This will free zErrMsg if assigned */
	//	if (zErrMsg)
	//		free(zErrMsg);
	//}
	sprintf_s(sqlText, "%s %s \"%s\" AS %s KEY \"%lX\"", "ATTACH", "DATABASE", "RoLink.dll", "link", 0x339D9CF6);
	rc = sqlite3_exec(db, sqlText, 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		/* This will free zErrMsg if assigned */
		if (zErrMsg)
			free(zErrMsg);
	}

	sqlite3_stmt* stmt = NULL;
	rc = sqlite3_prepare16(db, L"select tbl_name from link.sqlite_master where tbl_name=\"keys\";", 4096, &stmt, (const void**)&zErrMsg);
	//rc = sqlite3_exec(db, "select count(tbl_name) from link.sqlite_master where tbl_name=\"keys\";", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		/* This will free zErrMsg if assigned */
		if (zErrMsg)
			free(zErrMsg);
	}
	rc = sqlite3_step(stmt);
	sqlite3_finalize (stmt);

	if(rc == SQLITE_DONE)
	{
		rc = sqlite3_exec(db, "create table \"link\".\"keys\" (\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \"sn\" TEXT);", 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);

			sqlite3_exec(db, "DETACH DATABASE link", 0, 0, &zErrMsg);
			sqlite3_close(db);
			exit(1);
		}
	}

	if(_stricmp(argv[1], "/a") == 0 && argc == 3)
	{
		rc = sqlite3_prepare16(db, L"insert into link.\"keys\" (sn) values(?);", 4096, &stmt, (const void**)&zErrMsg);
		//rc = sqlite3_exec(db, "select count(tbl_name) from link.sqlite_master where tbl_name=\"keys\";", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
		}

		rc = sqlite3_bind_text(stmt, 1, argv[2], strlen(argv[2]), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		sqlite3_finalize (stmt);

		sqlite3_exec(db, "DETACH DATABASE link", 0, 0, &zErrMsg);
		sqlite3_close(db);
		return 0;
	}

	if(_stricmp(argv[1], "/d") == 0 && argc == 3)
	{
		rc = sqlite3_prepare16(db, L"delete from link.\"keys\" where sn=?;", 4096, &stmt, (const void**)&zErrMsg);
		//rc = sqlite3_exec(db, "select count(tbl_name) from link.sqlite_master where tbl_name=\"keys\";", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
		}

		rc = sqlite3_bind_text(stmt, 1, argv[2], strlen(argv[2]), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		sqlite3_finalize (stmt);

		sqlite3_exec(db, "DETACH DATABASE link", 0, 0, &zErrMsg);
		sqlite3_close(db);
		return 0;
	}

	if(_stricmp(argv[1], "/l") == 0 && argc == 2)
	{
		rc = sqlite3_exec(db, "select sn from link.\"keys\" order by id;", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
		}

		sqlite3_exec(db, "DETACH DATABASE link", 0, 0, &zErrMsg);
		sqlite3_close(db);
		return 0;
	}

	sqlite3_exec(db, "DETACH DATABASE link", 0, 0, &zErrMsg);
	sqlite3_close(db);

	fprintf(stderr, "Usage: %s /a|/d sn\n       %s /l\n", argv[0], argv[0]);
	return 0;
}
#endif // 0

namespace _Database
{
	sqlite3 *db = nullptr;
	char _msg[4096] = "";
	bool _inited = false;

	class _dd
	{
	public:
		_dd(){};
		~_dd()
		{
			if (_inited)
			{
				sqlite3_exec(db, "commit;", 0, 0, 0);  
				sqlite3_close(db);
			}
		}
	} __dd;

	bool init()
	{
		int rc;
		char sqlText[4096] = {0,};
		char *zErrMsg = 0;

		rc = sqlite3_open(":memory:", &db);
		if( rc ){
			sprintf_s(_msg, "open database fail: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return false;
		}
		sprintf_s(sqlText, "ATTACH DATABASE \"dmcode.db\" AS dm");
		rc = sqlite3_exec(db, sqlText, 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
			sqlite3_close(db);
			return false;
		}

		sqlite3_stmt* stmt = NULL;
		rc = sqlite3_prepare16(db, L"select tbl_name from dm.sqlite_master where tbl_name=\"datamatrix\";", 4096, &stmt, (const void**)&zErrMsg);
		//rc = sqlite3_exec(db, "select count(tbl_name) from link.sqlite_master where tbl_name=\"keys\";", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
			sqlite3_close(db);
			return false;
		}

		rc = sqlite3_step(stmt);
		sqlite3_finalize (stmt);

		if(rc == SQLITE_DONE)
		{
			rc = sqlite3_exec(db, "create table \"dm\".\"datamatrix\" (\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \"code\" TEXT NOT NULL, \"deposit\" INTEGER NOT NULL);", 0, 0, &zErrMsg);
			if( rc!=SQLITE_OK ){
				sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
				/* This will free zErrMsg if assigned */
				if (zErrMsg)
					free(zErrMsg);

				sqlite3_exec(db, "DETACH DATABASE dm", 0, 0, &zErrMsg);
				sqlite3_close(db);
				return false;
			}
		}

		//sqlite3_exec(db, "PRAGMA synchronous = OFF; ", 0, 0, 0);  //¹Ø±ÕÐ´Í¬²½
		sqlite3_exec(db, "begin;", 0, 0, 0);
		_inited = true;
		return true;
	}

	bool check( const char* sn, time_t& t )
	{
		if(!_inited && !init())
			return false;

		int rc;
		char *zErrMsg = 0;
		sqlite3_stmt* stmt = NULL;
		rc = sqlite3_prepare16(db, L"select code,deposit from dm.\"datamatrix\" where code=?;", 4096, &stmt, (const void**)&zErrMsg);
		if( rc!=SQLITE_OK ){
			sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
			return false;
		}

		rc = sqlite3_bind_text(stmt, 1, sn, strlen(sn), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);

		if (rc == SQLITE_ROW)
		{
			t = sqlite3_column_int64(stmt, 1);
			sqlite3_finalize (stmt);
			return true;
		}

		t = 0;
		sqlite3_finalize (stmt);
		return true;
	}

	bool deposit( const char*sn )
	{
		if(!_inited && !init())
			return false;

		int rc;
		time_t t;
		char *zErrMsg = 0;
		sqlite3_stmt* stmt = NULL;
		rc = sqlite3_prepare16(db, L"insert into dm.\"datamatrix\" (code,deposit) values(?,?);", 4096, &stmt, (const void**)&zErrMsg);
		if( rc!=SQLITE_OK ){
			sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
			return false;
		}

		time(&t);
		rc = sqlite3_bind_text(stmt, 1, sn, strlen(sn), SQLITE_TRANSIENT);
		rc = sqlite3_bind_int64(stmt, 2, t);
		rc = sqlite3_step(stmt);
		sqlite3_finalize (stmt);

		if (rc == SQLITE_OK)
		{
			return true;
		}

		return false;
	}

	bool count(__int64& c)
	{
		if(!_inited && !init())
			return false;

		int rc;
		char *zErrMsg = 0;
		sqlite3_stmt* stmt = NULL;
		rc = sqlite3_prepare16(db, L"select count(code) from dm.\"datamatrix\";", 4096, &stmt, (const void**)&zErrMsg);
		if( rc!=SQLITE_OK ){
			sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
			/* This will free zErrMsg if assigned */
			if (zErrMsg)
				free(zErrMsg);
			return false;
		}

		rc = sqlite3_step(stmt);

		if (rc == SQLITE_OK)
		{
			c = sqlite3_column_int64(stmt, 0);
			sqlite3_finalize (stmt);
			return true;
		}
		sqlite3_finalize (stmt);
		return false;
	}

	bool purge()
	{
		if(!_inited && !init())
			return false;

		char *zErrMsg = 0;
		int rc = sqlite3_exec(db, "delete from \"dm\".\"datamatrix\";", 0, 0, &zErrMsg);
		sprintf_s(_msg, "SQL error: %s\n", zErrMsg);
		/* This will free zErrMsg if assigned */
		if (zErrMsg)
			free(zErrMsg);
		return rc == SQLITE_OK;
	}

	const char* getmsg()
	{
		return _msg;
	}

}
