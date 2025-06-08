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
Mixed gt_echo(const Mixed &_input) {
	log("gt_echo(): ");
//	print_r(_input);
	for (auto [_k, _v_auto] : _input.valueArray) {
		Mixed _v = (Mixed) * _v_auto;
//		print_r(_v);
		echo((string) _v);
	}
	echo("\n");
	return Mixed();
}
Mixed gt_print(const Mixed &_input) {
	log("gt_print(): ");
//	print_r(_input);
	if (!isset(_input, 0))
		throw GtlangInnerFunctionException("FunctionParamsCountException",
				"print requires 1 arg");
	print_r(_input[0]);
	return Mixed();
}
Mixed gt_input(const Mixed &_input) {
	string _return;
	getline(cin, _return);
	return Mixed(_return);
}

Mixed use_language_file(const Mixed &_input) {
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
Mixed gt_merge(const Mixed &_input) {
	Mixed _return = Mixed();
	for (auto [_k, _v] : _input.valueArray) {
		_return.merge(*_v);
	}
	return _return;
}
Mixed gt_explode(const Mixed &_input) {
	Mixed _return = Mixed();
	string _needle = (string) _input[0];
	string _haystack = (string) _input[1];
	arr_ls _result = explode(_needle, _haystack);
	for (auto [_k, _v] : _result) {
		_return.push(Mixed(_v));
	}
	return _return;
}
Mixed gt_implode(const Mixed &_input) {
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
Mixed gt_reset_keys(const Mixed &_input) {
	Mixed _return = _input[0];
	_return.resetKeys();
	return _return;
}
Mixed gt_sizeof1(const Mixed &_input) {
	Mixed _return = _input[0];
	return Mixed(gt_sizeof(_return));
}
Mixed gt_find(const Mixed &_input) {
	Mixed _return;
	Mixed _arr = _input[0];
	Mixed _find = _input[1];
	for (auto [_k, _v] : _arr.valueArray) {
		if (*_v == _find)
			_return.push(_k);
	}
	return _return;
}
Mixed gt_contains(const Mixed &_input) {
	string _return = get_name(_input[0]);
	string _find = get_name(_input[1]);
	return Mixed(str_contains(_return, _find));
}
Mixed gt_length(const Mixed &_input) {
	string _str = (string) _input[0];
	long _len = (long) _str.size();
	return Mixed(_len);
}
Mixed gt_sub_str(const Mixed &_input) {
	Mixed _str = _input[0];
	long _start = (int) _input[1];
	long _len = (int) _input[2];
	return Mixed(substr(_str, _start, _len));
}
Mixed gt_str_m_pos(const Mixed &_input) {
	string _haystack = (string) _input[0];
	string _needle = (string) _input[1];
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)) + 1; _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			_return.push(_i);
	}
	return _return;
}
Mixed gt_str_pos(const Mixed &_input) {
	string _haystack = (string) _input[0];
	string _needle = (string) _input[1];
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)) + 1; _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			return Mixed(_i);
	}
	return Mixed(-1);
}
Mixed gt_str_m_i_pos(const Mixed &_input) {
	string _haystack = strtolower((string) _input[0]);
	string _needle = strtolower((string) _input[1]);
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)) + 1; _i++) {
		if (substr(_haystack, _i, strlen(_needle)) == _needle)
			_return.push(_i);
	}
	return _return;
}
Mixed gt_str_i_pos(const Mixed &_input) {
	string _haystack = strtolower((string) _input[0]);
	string _needle = strtolower((string) _input[1]);
	Mixed _return;
	for (long _i = 0; _i < (strlen(_haystack) - strlen(_needle)) + 1; _i++) {
		string _tmp = substr(_haystack, _i, strlen(_needle));
		if (_tmp == _needle)
			return Mixed(_i);
	}
	return Mixed(-1);
}
Mixed gt_str_to_upper(const Mixed &_input) {
	string _str = (string) _input[0];
	string _upper_str = strtoupper(_str);
	return Mixed(_upper_str);
}
Mixed gt_str_to_lower(const Mixed &_input) {
	string _str = (string) _input[0];
	string _upper_str = strtolower(_str);
	return Mixed(_upper_str);
}
Mixed gt_shell(const Mixed &_input) {
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
	int _rs_out = pipe(out_pipe);
	int _rs_err = pipe(err_pipe);

	if (_rs_out == 1 || _rs_err == -1)
		return false;
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
Mixed gt_file_read(const Mixed &_input) {
	string _file_name = (string) _input[0];
	try {
		return file_get_contents(_file_name);
	} catch (int e) {
		throw GreenTeaException("IOErrorException", "Cannot open file",
				_input[0]);
	}
}
Mixed gt_file_init(const Mixed &_input) {
	string _file_name = (string) _input[0];
	if (create_empty_file(_file_name))
		return Mixed(true);
	else
		throw GreenTeaException("IOErrorException", "Cannot create file",
				_input[0]);
}
Mixed gt_file_write(const Mixed &_input) {
	string _file_name = (string) _input[0];
	string _content = (string) _input[1];
	if (!file_exists(_file_name))
		create_empty_file(_file_name);
	append_to_file(_file_name, _content);
	return Mixed(true);
}
Mixed gt_file_exists(const Mixed &_input) {
	string _file_name = (string) _input[0];
	return Mixed(file_exists(_file_name));
}
Mixed gt_mkdir(const Mixed &_input) {
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
Mixed gt_delete_path(const Mixed &_input) {
	string _file_name = (string) _input[0];
	if (delete_path(_file_name))
		return Mixed(true);
	else
		throw GreenTeaException("IOErrorException", "Cannot delete file/folder",
				_input[0]);
}
size_t WriteCallback(void *contents, const size_t &size, const size_t &nmemb,
		void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}

Mixed gt_is_preg_match(const Mixed &_input) {
	string _pattern = _input[0];
	string _str = _input[1];
	bool _utf8 = _input[2];
	bool _return = php_is_preg_match(_pattern, _str, _utf8);
	return _return;
}
Mixed gt_preg_match_all(const Mixed &_input) {
	Mixed _return;
	string _pattern = _input[0];
	string _str = _input[1];
	bool _utf8 = _input[2];
	arr_ls _res = php_preg_match_all(_pattern, _str, _utf8);
	for (auto [_k, _v] : _res) {
		_return.push(_v);
	}
	return _return;
}
Mixed gt_preg_replace_all(const Mixed &_input) {
	string _pattern = _input[0];
	string _replace = _input[1];
	string _str = _input[2];
	bool _utf8 = _input[3];
	return php_preg_replace_all(_pattern, _replace, _str, _utf8);
}
;
#endif /* CORE_IO_H_ */
