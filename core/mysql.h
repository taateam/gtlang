/*
 * mysql.h
 *
 *  Created on: Jun 3, 2025
 *      Author: t
 */

#ifndef CORE_MYSQL_H_
#define CORE_MYSQL_H_

long mysql_connect(string &_host, string &_port, string &_user, string &_pass,
		string &_db) {
	try {
		sql::Connection *_conn = driver->connect("tcp://" + _host + ":" + _port,
				_user, _pass);
		_conn->setSchema(_db);
		return array_push(__mysql_connections, _conn);
	} catch (sql::SQLException &e) {
		throw GtlangInnerFunctionException("MysqlException",
				lr("Cannot connect to mysql server: ") + e.what());
	}
}

Mixed mysql_query(long _conn_id, string &_query) {
	_query = trim(_query);
	sql::Connection *_conn = __mysql_connections.at(_conn_id);
	sql::Statement *_stmt = nullptr;
	sql::ResultSet *_res = nullptr;
	sql::PreparedStatement *_pstmt = nullptr;
	Mixed _return;
	try {
		//=======================================
		if (stripos(_query, "select") == 0) {
			_stmt = _conn->createStatement();
			_res = _stmt->executeQuery(_query);
			arr_ls collumn_name;
			sql::ResultSetMetaData *_res_meta;
			_res_meta = _res->getMetaData();
			long _columns_count = _res_meta->getColumnCount();
			//Mixed _return;
			long _i = 0;
			while (_res->next()) {
				_return.push(_i, Mixed());
				for (long _j = 1; _j <= _columns_count; _j++) {
					string _column_name = _res_meta->getColumnLabel(_j);
					string _value = _res->getString(_column_name);
					_return[_i].push(_column_name, _value);
				}
				_i++;
			}
		} else {
			sql::PreparedStatement *_pstmt = _conn->prepareStatement(_query);
			long _affected_rows = _pstmt->executeUpdate();
			_return = Mixed(_affected_rows);
			delete _pstmt;
		}
		//=======================================
		delete _stmt;
		delete _res;
		return _return;
	} catch (sql::SQLException &e) {
		if (_res)
			delete _res;
		if (_stmt)
			delete _stmt;
		if (_pstmt)
			delete _pstmt;
		throw GtlangInnerFunctionException("MysqlException",
				lr("Error when executing mysql query: ") + e.what());
	}
}

bool mysql_close(long _conn_id) {
	if (!__mysql_connections.contains(_conn_id))
		return false;
	sql::Connection *_conn = __mysql_connections[_conn_id];
	if (_conn) {
		_conn->close();
		delete _conn;
		__mysql_connections.erase(_conn_id);
		return true;
	}
	return false;
}
Mixed gt_mysql_connect(const Mixed &_input) {
	if (gt_sizeof(_input) < 5)
		throw GtlangInnerFunctionException("MysqlException",
				"Do not have enough params");
	string _host = _input[0];
	string _port = _input[1];
	string _user = _input[2];
	string _pass = _input[3];
	string _db = _input[4];
	long _id = mysql_connect(_host, _port, _user, _pass, _db);
	__mysql_locks.emplace(_id, new mutex);
	return _id;
}
Mixed gt_mysql_query(const Mixed &_input) {
	long _id = tl(_input[0]);
	if (!__mysql_connections.contains(_id))
		throw GtlangInnerFunctionException("MysqlException", "no connection");
	string _query = _input[1];
	Mixed _return;
	__mysql_locks[_id]->lock();
	try {
		_return = mysql_query(_id, _query);
		__mysql_locks[_id]->unlock();
	} catch (GtlangInnerFunctionException &_e) {
		__mysql_locks[_id]->unlock();
		throw _e;
	}
	return _return;
}
Mixed gt_mysql_close(const Mixed &_input) {
	long _id = tl(_input[0]);
	if (!isset(__mysql_connections, _id))
		throw GtlangInnerFunctionException("MysqlException", "no connection");
	__mysql_locks[_id]->lock();
	__mysql_locks[_id]->unlock();
	Mixed _return = mysql_close(_id);
	if (__mysql_locks.contains(_id)) {
		if (__mysql_locks[_id])
			delete __mysql_locks[_id];
		__mysql_locks.erase(_id);
	}
	return _return;
}

#endif /* CORE_MYSQL_H_ */
