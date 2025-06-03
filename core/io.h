/*
 * io.h
 *
 *  Created on: May 25, 2025
 *      Author: t
 */

#ifndef CORE_IO_H_
#define CORE_IO_H_

sql::Driver *driver = get_driver_instance();
map<long, sql::Connection*> __mysql_connections;
map<long, mutex*> __mysql_locks;
Mixed gt_echo(Mixed _input) {
	log("gt_echo(): ");
//	print_r(_input);
	for (auto [_k, _v_auto] : _input.valueArray) {
		Mixed _v = (Mixed) * _v_auto;
//		print_r(_v);
		echo((string) _v + PHP_EOL);
	}
	return Mixed();
}
Mixed gt_print(Mixed _input) {
	log("gt_print(): ");
//	print_r(_input);
	if (!isset(_input, 0))
		throw GtlangInnerFunctionException("FunctionParamsCountException",
				"print requires 1 arg");
	print_r(_input[0]);
	return Mixed();
}
Mixed gt_input(Mixed _input) {
	string _return;
	getline(cin, _return);
	return Mixed(_return);
}

Mixed use_language_file(Mixed _input) {
	string _lang_file = _input[0]["name"].valueStr;
	string _lang_content;
	try {
		_lang_content = file_get_contents(_lang_file);
	} catch (int _e) {
		echo("Warning: cannot access language file. Using default language.");
		// return Mixed();
	}
	init_translation(_lang_content);
	return Mixed();
}
Mixed gt_merge(Mixed _input) {
	Mixed _return = Mixed();
	for (auto [_k, _v] : _input.valueArray) {
		_return.merge(*_v);
	}
	return _return;
}
Mixed gt_explode(Mixed _input) {
	Mixed _return = Mixed();
	string _needle = (string) _input[0];
	string _haystack = (string) _input[1];
	arr_ls _result = explode(_needle, _haystack);
	for (auto [_k, _v] : _result) {
		_return.push(Mixed(_v));
	}
	return _return;
}
Mixed gt_implode(Mixed _input) {
	string _return;
	long _i = 0;
	if (!isset(_input, 0) || !isset(_input, 1))
		throw GtlangInnerFunctionException("FunctionParamsCountException",
				"implode requires 2 strings");
	for (auto [_k, _v] : _input[1].valueArray) {
		_return += (string) * _v;
		if (_i < gt_sizeof(_input))
			_return += (string) _input[0];
		_i++;
	}
	return Mixed(_return);
}
Mixed gt_reset_keys(Mixed _input) {
	Mixed _return = _input[0];
	_return.resetKeys();
	return _return;
}
Mixed gt_sizeof1(Mixed _input) {
	Mixed _return = _input[0];
	return Mixed(gt_sizeof(_return));
}
Mixed gt_find(Mixed _input) {
	Mixed _return;
	Mixed _arr = _input[0];
	Mixed _find = _input[1];
	for (auto [_k, _v] : _arr.valueArray) {
		if (*_v == _find)
			_return.push(_k);
	}
	return _return;
}
Mixed gt_contains(Mixed _input) {
	Mixed _return = _input[0];
	Mixed _find = get_name(_input[1]);
	return Mixed(_return.contains(_find));
}
Mixed gt_length(Mixed _input) {
	string _str = (string) _input[0];
	long _len = (long) _str.size();
	return Mixed(_len);
}
Mixed gt_sub_str(Mixed _input) {
	Mixed _str = _input[0];
	long _start = (int) _input[1];
	long _len = (int) _input[2];
	return Mixed(substr(_str, _start, _len));
}
Mixed gt_str_m_pos(Mixed _input) {
	string _haystack = (string) _input[0];
	string _needle = (string) _input[1];
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)); _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			_return.push(_i);
	}
	return _return;
}
Mixed gt_str_pos(Mixed _input) {
	string _haystack = (string) _input[0];
	string _needle = (string) _input[1];
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)); _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			return Mixed(_i);
	}
	return Mixed(-1);
}
Mixed gt_str_m_i_pos(Mixed _input) {
	string _haystack = strtolower((string) _input[0]);
	string _needle = strtolower((string) _input[1]);
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)); _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			_return.push(_i);
	}
	return _return;
}
Mixed gt_str_i_pos(Mixed _input) {
	string _haystack = strtolower((string) _input[0]);
	string _needle = strtolower((string) _input[1]);
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)); _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			return Mixed(_i);
	}
	return Mixed(-1);
}
Mixed gt_str_to_upper(Mixed _input) {
	string _str = (string) _input[0];
	string _upper_str = strtoupper(_str);
	return Mixed(_upper_str);
}
Mixed gt_str_to_lower(Mixed _input) {
	string _str = (string) _input[0];
	string _upper_str = strtolower(_str);
	return Mixed(_upper_str);
}
Mixed gt_shell(Mixed _input) {
	if (!isset(_input, 0))
		throw GtlangInnerFunctionException("FunctionParamsCountException",
				"shell requires 1 string");
	string _cmd = (string) _input[0];
	Mixed _result;
#ifdef _WIN32
	HANDLE hStdOutRead, hStdOutWrite;
	HANDLE hStdErrRead, hStdErrWrite;
	SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	CreatePipe(&hStdOutRead, &hStdOutWrite, &saAttr, 0);
	CreatePipe(&hStdErrRead, &hStdErrWrite, &saAttr, 0);

	SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);
	SetHandleInformation(hStdErrRead, HANDLE_FLAG_INHERIT, 0);

	PROCESS_INFORMATION pi = {};
	STARTUPINFOA si = {};
	si.cb = sizeof(STARTUPINFOA);
	si.hStdOutput = hStdOutWrite;
	si.hStdError = hStdErrWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;

	std::string full_cmd = "cmd.exe /C " + _cmd;
	char* cmdline = _strdup(full_cmd.c_str());

	BOOL success = CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	free(cmdline);
	CloseHandle(hStdOutWrite);
	CloseHandle(hStdErrWrite);

	if (!success) {
		CloseHandle(hStdOutRead);
		CloseHandle(hStdErrRead);
		throw std::runtime_error("CreateProcess failed");
	}

	char buffer[4096];
	DWORD bytesRead;
	std::ostringstream out, err;

	while (ReadFile(hStdOutRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
		out.write(buffer, bytesRead);
	while (ReadFile(hStdErrRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
		err.write(buffer, bytesRead);

	CloseHandle(hStdOutRead);
	CloseHandle(hStdErrRead);

	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD exitCode;
	GetExitCodeProcess(pi.hProcess, &exitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_result.push("stdout",out.str());
	_result.push("stderr", err.str());
	_result.push("exit_code", static_cast<int>(exitCode));

#else
	int out_pipe[2], err_pipe[2];
	pipe(out_pipe);
	pipe(err_pipe);

	pid_t pid = fork();
	if (pid == 0) {
		// Child process
		dup2(out_pipe[1], STDOUT_FILENO);
		dup2(err_pipe[1], STDERR_FILENO);

		close(out_pipe[0]);
		close(out_pipe[1]);
		close(err_pipe[0]);
		close(err_pipe[1]);

		execl("/bin/sh", "sh", "-c", _cmd.c_str(), (char*) nullptr);
		_exit(127);
	}

// Parent process
	close(out_pipe[1]);
	close(err_pipe[1]);

	std::ostringstream out_stream, err_stream;
	char buffer[4096];
	ssize_t count;

	while ((count = read(out_pipe[0], buffer, sizeof(buffer))) > 0) {
		out_stream.write(buffer, count);
	}
	while ((count = read(err_pipe[0], buffer, sizeof(buffer))) > 0) {
		err_stream.write(buffer, count);
	}

	close(out_pipe[0]);
	close(err_pipe[0]);

	int status = 0;
	waitpid(pid, &status, 0);

	_result.push("stdout", out_stream.str());
	_result.push("stderr", err_stream.str());
	_result.push("exit_code", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
#endif
	return _result;
}
Mixed gt_file_read(Mixed _input) {
	string _file_name = (string) _input[0];
	try {
		return file_get_contents(_file_name);
	} catch (int e) {
		throw GreenTeaException("IOErrorException", "Cannot open file",
				_input[0]);
	}
}
Mixed gt_file_init(Mixed _input) {
	string _file_name = (string) _input[0];
	if (create_empty_file(_file_name))
		return Mixed(true);
	else
		throw GreenTeaException("IOErrorException", "Cannot create file",
				_input[0]);
}
Mixed gt_file_write(Mixed _input) {
	string _file_name = (string) _input[0];
	string _content = (string) _input[1];
	if (!file_exists(_file_name))
		create_empty_file(_file_name);
	append_to_file(_file_name, _content);
	return Mixed(true);
}
Mixed gt_file_exists(Mixed _input) {
	string _file_name = (string) _input[0];
	return Mixed(file_exists(_file_name));
}
Mixed gt_mkdir(Mixed _input) {
	string _folder_name = (string) _input[0];
	bool _recruisively = true;
	if (isset(_input, 1) && (bool) _input[1] == false)
		_recruisively = false;
	try {
		if (_recruisively) {
			make_parent_dirs(_folder_name);
		} else
			mkdir(_folder_name);
	} catch (...) {
		throw GreenTeaException("IOErrorException", "Cannot create folder",
				_input[0]);
	}

	return Mixed(true);
}
Mixed gt_delete_path(Mixed _input) {
	string _file_name = (string) _input[0];
	if (delete_path(_file_name))
		return Mixed(true);
	else
		throw GreenTeaException("IOErrorException", "Cannot delete file/folder",
				_input[0]);
}
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}

Mixed gt_fetch_url(Mixed _input) {
	Mixed _return;
	string url = (string) _input[0];
	CURL *curl;
	CURLcode res;
	string readBuffer;

	curl = curl_easy_init();
	if (!curl) {
		throw GreenTeaException("RequestException", "Error initializing curl ",
				_input[0]);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		curl_easy_cleanup(curl);
		throw GreenTeaException("RequestException", "Error getting URL",
				_input[0]);
	}

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
	curl_easy_cleanup(curl);

	if (http_code != 200) {
		;
	}

	_return.push("response", readBuffer);
	_return.push("code", http_code);
	return _return;
}
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

Mixed mysql_query(long _conn_id, string _query) {
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
Mixed gt_mysql_connect(Mixed _input) {
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
Mixed gt_mysql_query(Mixed _input) {
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
Mixed gt_mysql_close(Mixed _input) {
	long _id = tl(_input[0]);
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
;
#endif /* CORE_IO_H_ */
