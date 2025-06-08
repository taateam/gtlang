#ifndef LIBS_LIBS_H_
#define LIBS_LIBS_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <chrono>
#include <variant>
#include <algorithm>
#include <regex>
#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#include <array>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
#include <boost/algorithm/string.hpp>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <csignal>
#include <boost/algorithm/string/replace.hpp>
#include <thread>
#include <mutex>
#include <boost/interprocess/sync/file_lock.hpp>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#endif
#include <curl/curl.h>
#include <unicode/unistr.h>
#include <unicode/regex.h>
#include <mysql/mysql.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <libs/php2cpp.h>
#include <libs/Mixed.h>

bool php_is_array(const Mixed &_mixed) {
	return (_mixed.type == "a");
}
// pair<long, long> T;
typedef map<long, Mixed> arr_lm;
struct gt_exec_rs {
public:
	string _type;
	Mixed _value;
	gt_exec_rs(const string &_1, const Mixed &_2) {
		this->_type = _1;
		this->_value = _2;
	}
	gt_exec_rs(const string &_1, long &_2) {
		this->_type = _1;
		this->_value = Mixed(_2);
	}
	gt_exec_rs(const string &_1, double &_2) {
		this->_type = _1;
		this->_value = Mixed(_2);
	}
	gt_exec_rs(const string &_1, string &_2) {
		this->_type = _1;
		this->_value = Mixed(_2);
	}
	gt_exec_rs() {
		this->_type = "";
		this->_value = Mixed();
	}
};
arr_ls __operators = { { 0, ":" }, { 1, "::" }, { 2, "=" }, { 3, "==" }, { 4,
		">" }, { 5, "<" }, { 6, "==" }, { 7, "!==" }, { 8, "." }, { 9, "," }, {
		10, ":" }, { 11, "+" }, { 12, ">=" }, { 13, "<=" }, { 14, "!=" }, { 15,
		"!" }, { 16, "-" }, { 17, "*" }, { 18, "/" }, { 19, "%" }, { 20, "+:" },
		{ 21, "++" }, { 22, "-:" }, { 23, "--" }, { 24, ".:" }, { 25, "[]" }, {
				26, "*:" }, { 27, "/:" }, { 28, "%:" }, { 29, "<>" },
		{ 30, "?" }, { 31, "=>" }, { 32, "->" }, { 33, ">>" }, { 34, "<<" }, {
				35, ".." }, { 36, "&&" }, { 37, "||" }, { 38, "|&" },
		{ 39, "(" }, { 40, ")" }, { 41, "{" }, { 42, "}" }, { 43, "[" }, { 44,
				"]" }, { 45, "**" } };
arr_ls __operator_1st_chars;
arr_lls __operators_by_chars_count = { { 3, { } }, { 2, { } }, { 1, { } } };
// 0 -> type  ( 0: $a++, 1: !$a, 2: $a+$b );
// 1 -> priority, 0 is highest;
const arr_sll __real_operators = { { "=", { { 0, 2 }, { 1, 3 } } }, { "==", { {
		0, 2 }, { 1, 5 } } }, { ">", { { 0, 2 }, { 1, 4 } } }, { "<", {
		{ 0, 2 }, { 1, 4 } } }, { "!==", { { 0, 2 }, { 1, 5 } } }, { ".", { { 0,
		2 }, { 1, 3 } } }, { ",", { { 0, 2 }, { 1, 3 } } }, { "+", { { 0, 2 }, {
		1, 3 } } }, { ">=", { { 0, 2 }, { 1, 4 } } }, { "<=", { { 0, 2 },
		{ 1, 4 } } }, { "!=", { { 0, 2 }, { 1, 5 } } }, { "!", { { 0, 1 }, { 1,
		1 } } }, { "-", { { 0, 2 }, { 1, 3 } } },
		{ "*", { { 0, 2 }, { 1, 2 } } }, { "/", { { 0, 2 }, { 1, 2 } } }, { "%",
				{ { 0, 2 }, { 1, 2 } } }, { ":", { { 0, 2 }, { 1, 6 } } }, {
				"+:", { { 0, 2 }, { 1, 6 } } },
		{ "++", { { 0, 0 }, { 1, 3 } } }, { "-:", { { 0, 2 }, { 1, 3 } } }, {
				"--", { { 0, 0 }, { 1, 6 } } },
		{ ".:", { { 0, 2 }, { 1, 6 } } }, { "[]", { { 0, 2 }, { 1, 0 } } }, {
				"*:", { { 0, 2 }, { 1, 6 } } },
		{ "/:", { { 0, 2 }, { 1, 6 } } }, { "%:", { { 0, 2 }, { 1, 6 } } }, {
				"<>", { { 0, 2 }, { 1, 5 } } },
		{ "&&", { { 0, 2 }, { 1, 7 } } }, { "||", { { 0, 2 }, { 1, 9 } } }, {
				"|&", { { 0, 2 }, { 1, 8 } } },
		{ "=>", { { 0, 2 }, { 1, 10 } } }, { "|&", { { 0, 2 }, { 1, 8 } } }, {
				">>", { { 0, 2 }, { 1, 10 } } },
		{ "|&", { { 0, 2 }, { 1, 8 } } }, { "<<", { { 0, 2 }, { 1, 10 } } }, {
				"**", { { 0, 2 }, { 1, 2 } } } };
arr_ls __keywords = { { 0, "if" }, { 1, "else" }, { 2, "class" }, { 3, "do" }, {
		4, "while" }, { 5, "break" }, { 6, "use" }, { 7, "switch" },
		{ 8, "new" }, { 9, "continue" }, { 10, "return" }, { 11, "include" }, {
				12, "throw" }, { 13, "try" }, { 14, "catch" },
		{ 15, "finally" }, { 16, "defcat" }, { 17, "deffin" }, { 18, "elif" }, {
				19, "new" }, { 20, "do" }, { 21, "case" }, { 22, "continue" }, {
				23, "for" }, { 24, "times" }, { 25, "from" }, { 26, "to" }, {
				27, "foreach" }, { 28, "as" }, { 29, "at" }, { 30, "borrow" }, {
				31, "from" } };
//arr_sl __keywords_reversed;
arr_ls __modifiers = { { 0, "private" }, { 1, "public" }, { 2, "static" } };
//arr_sl __modifiers_reversed;
arr_ls __args;
const string PHP_EOL = "\n";
const string CPP_EOL = "\n";
Mixed __funcs, __main;
Mixed __g;
arr_ss __translations_to_en, __translations_from_en;
typedef Mixed (*GTBuiltinFunction)(const Mixed &_args);
map<string, GTBuiltinFunction> __b_funcs;
class GtLanguageFileException {
public:
	string msg;
	GtLanguageFileException(string _input) {
		msg = _input;
	}
};
void init_translation(const string &_content) {
	__translations_to_en.clear();
	__translations_from_en.clear();
	arr_ls _lines = explode("\n", _content);
	string _2nd_line = _lines[1];
	if (strpos(_2nd_line, "#language_file ") != 0)
		return;
	string _file_name = trim(str_replace("#language_file ", "", _2nd_line));
	string _language_content = "";
	try {
		_language_content = file_get_contents(_file_name);
	} catch (...) {
		echo("Cannot access language file");
		return;
	}
	arr_ls _pair_strs = explode("\n", _language_content);
	for (auto [_k, _v] : _pair_strs) {
//		if (strpos(_v, " ") > -1 || strpos(_v, "\t") > -1)
//			throw GtLanguageFileException(
//					"Language file error: found space in line " + ts(_k)
//							+ " in file" + _file_name);
		arr_ls _pair = explode("=", _v);
		if (gt_sizeof(_pair) != 2)
			throw GtLanguageFileException(
					"Language file error: invalid line " + ts(_k + 1)
							+ " in file " + _file_name);
		string _english = _pair[0];
		string _foreign = _pair[1];
		if (__translations_to_en.contains(_foreign))
			throw GtLanguageFileException(
					"Language file error: duplicated 2nd part of line "
							+ ts(_k + 1) + " in file " + _file_name);
		if (in_array(_english, __translations_to_en))
			throw GtLanguageFileException(
					"Language file error: duplicated 1st part of line "
							+ ts(_k + 1) + " in file " + _file_name);
		__translations_to_en[_foreign] = _english;
		__translations_from_en[_english] = _foreign;
	}
}
string l(const string &_foreign) {
	if (__translations_to_en.contains(_foreign))
		return __translations_to_en[_foreign];
	else
		return _foreign;
}

string lr(const string &_english) {
	if (__translations_from_en.contains(_english))
		return __translations_from_en[_english];
	else
		return _english;
}

//==========================================
//==========================================
//==========================================
//==========================================
long __LOG_LV = 2;
//==========================================
//==========================================
//==========================================
//==========================================

Mixed __answer_var;
Mixed __global_vars, __local_vars, __classes, __multi_threads_data;
map<string, thread> __threads;
string __main_thread_id;
mutex __general_thread_lock;
long __current_func_lv = 0;
void log(const string &_message, long _lv = 1) {
	if (__LOG_LV > _lv)
		return;
	time_t t = time(nullptr);
	tm *now = localtime(&t);
	ostringstream oss;
	oss << put_time(now, "%Y/%m/%d %H:%M:%S");
	string _time_str = oss.str();
	string _lv_str;
	switch (_lv) {
	case 0:
		_lv_str = "trace";
		break;
	case 1:
		_lv_str = "debug";
		break;
	case 2:
		_lv_str = "info";
		break;
	case 3:
		_lv_str = "warn";
		break;
	case 4:
		_lv_str = "error";
		break;
	case 5:
		_lv_str = "fatal";
		break;
	default:
		_lv_str = "unknown";
	}
	cout << endl;
	echo(_time_str + " [" + _lv_str + "] " + _message);
}

void print_rl(const tokens_line1_arr &_input, long _lv = 1) {
	if (__LOG_LV > _lv)
		return;
	print_r(_input);
}
void _log(const string &_message, long _lv = 1) {
	;
}
string get_thread_id_str();
bool is_main_thread();
long get_current_func_lv() {
	if (is_main_thread())
		return __current_func_lv;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["func_lv"];
}
void set_current_func_lv(long _lv) {
	if (is_main_thread())
		__current_func_lv = _lv;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["func_lv"] = _lv;
	}
}
void add1_current_func_lv() {
	if (is_main_thread())
		__current_func_lv++;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["func_lv"] = (long) __g[_thread_id]["func_lv"] + 1;
	}
}
Mixed& get_local_vars() {
	if (is_main_thread())
		return __local_vars;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["local_vars"];
}
void set_local_vars(const Mixed &_v) {
	if (is_main_thread())
		__local_vars = _v;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["local_vars"] = _v;
	}
}
void set_local_var_i(const string &_k, const Mixed &_v) {
	if (is_main_thread())
		__local_vars.push(_k, _v);
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["local_vars"].push(_k, _v);
	}
}
Mixed& get_global_vars() {
	if (is_main_thread())
		return __global_vars;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["local_vars"];
}
void set_global_vars(const Mixed &_v) {
	if (is_main_thread())
		__global_vars = _v;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["local_vars"] = _v;
	}
}
void set_global_var_i(const string &_k, const Mixed &_v) {
	if (is_main_thread())
		__global_vars.push(_k, _v);
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["local_vars"].push(_k, _v);
	}
}
Mixed& get_answer_var() {
	if (is_main_thread())
		return __answer_var;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["answer_var"];
}
void set_answer_var(const Mixed &_x) {
	if (is_main_thread())
		__answer_var = _x;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["answer_var"] = _x;
	}
}
void set_functions(const Mixed &_v) {
	if (is_main_thread())
		__funcs = _v;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["funcs"] = _v;
	}
}
void set_function_i(const string &_k, const Mixed &_v) {
	if (is_main_thread())
		__funcs.push(_k, _v);
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["funcs"].push(_k, _v);
	}
}
Mixed& get_functions() {
	if (is_main_thread())
		return __funcs;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["funcs"];
}
void set_classes(const Mixed &_v) {
	if (is_main_thread())
		__classes = _v;
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["classes"] = _v;
	}
}
void set_class_i(const string &_k, const Mixed &_v) {
	if (is_main_thread())
		__classes.push(_k, _v);
	else {
		string _thread_id = get_thread_id_str();
		__g[_thread_id]["classes"].push(_k, _v);
	}
}
Mixed& get_classes() {
	if (is_main_thread())
		return __classes;
	string _thread_id = get_thread_id_str();
	return __g[_thread_id]["classes"];
}
#endif /* LIBS_LIBS_H_ */
