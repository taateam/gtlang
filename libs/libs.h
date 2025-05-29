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
#include <boost/algorithm/string.hpp>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <csignal>
#include <boost/algorithm/string/replace.hpp>
#include <libs/php2cpp.h>
#include <libs/Mixed.h>
#include <thread>
#include <mutex>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#endif
#include <curl/curl.h>

bool php_is_array(Mixed _mixed) {
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
				"]" } };
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
		{ "|&", { { 0, 2 }, { 1, 8 } } }, { "<<", { { 0, 2 }, { 1, 10 } } } };
arr_ls __keywords = { { 0, "if" }, { 1, "else" }, { 2, "class" }, { 3, "do" }, {
		4, "while" }, { 5, "break" }, { 6, "use" }, { 7, "switch" },
		{ 8, "new" }, { 9, "continue" }, { 10, "return" }, { 11, "include" }, {
				12, "throw" }, { 13, "try" }, { 14, "catch" },
		{ 15, "finally" }, { 16, "defcat" }, { 17, "deffin" }, { 18, "elif" }, {
				19, "new" }, { 20, "do" }, { 21, "case" }, { 22, "continue" }, {
				23, "for" }, { 24, "times" }, { 25, "from" }, { 26, "to" }, {
				27, "foreach" }, { 28, "as" }, { 29, "at" }, { 30, "borrow" }, {
				31, "from" } };
arr_sl __keywords_reversed;
arr_ls __modifiers = { { 0, "private" }, { 1, "public" }, { 2, "static" } };
arr_sl __modifiers_reversed;
arr_ls __args;
const string PHP_EOL = "\n";
const string CPP_EOL = "\n";
Mixed __funcs, __main;
typedef Mixed (*GTBuiltinFunction)(Mixed _args);
map<string, GTBuiltinFunction> __b_funcs;
void init_translation() {
	for (auto [_k, _v] : __keywords) {
		__keywords_reversed[_v] = _k;
	}
	for (auto [_k, _v] : __modifiers) {
		__modifiers_reversed[_v] = _k;
	};
}
string l(string _original) {
	// translate code from languages. Ex: Eng -> Rus.
	try {
		long _k = __keywords_reversed[_original];
		return __keywords[_k];
	} catch (...) {
	}
	try {
		long _k = __modifiers_reversed[_original];
		return __modifiers[_k];
	} catch (...) {
	}
	throw("invalid keyword/modifier");
}

long __LOG_LV = 2;
Mixed __answer_var;
Mixed __global_vars, __local_vars, __thread_vars, __classes,
		__multi_threads_data;
map<string, thread> __threads;
string __main_thread_id;
mutex __general_thread_lock;
long __current_func_lv = 0;
arr_lls __default_exception_classes =
		{ { 0, { { 0, "Exception" }, { 1, "" } } }, { 1, { { 0,
				"SyntaxErrorException" }, { 1, "Exception" } } }, { 2, { { 0,
				"OtherException" }, { 1, "Exception" } } }, { 3, { { 0,
				"RuntimeErrorException" }, { 1, "Exception" } } }, { 4, { { 0,
				"IOErrorException" }, { 1, "Exception" } } }, { 5, { { 0,
				"ThreadingException" }, { 1, "Exception" } } }, { 6, { { 0,
				"ImportException" }, { 1, "Exception" } } }, { 7, { { 0,
				"ChatGPTException" }, { 1, "Exception" } } }, { 8, { { 0,
				"InternalCompilerException" }, { 1, "Exception" } } }, { 9, { {
				0, "TypeErrorException" }, { 1, "RuntimeErrorException" } } }, {
				10, { { 0, "NullReferenceException" }, { 1,
						"RuntimeErrorException" } } },
				{ 11, { { 0, "IndexOutOfBoundsException" }, { 1,
						"RuntimeErrorException" } } }, { 12, { { 0,
						"UndefinedVariableException" }, { 1,
						"RuntimeErrorException" } } }, { 13, { { 0,
						"FunctionNotFoundException" }, { 1,
						"RuntimeErrorException" } } }, { 14, { { 0,
						"LanguageFileException" },
						{ 1, "RuntimeErrorException" } } }, { 15, { { 0,
						"MathException" }, { 1, "RuntimeErrorException" } } }, {
						16, { { 0, "OutOfMemoryException" }, { 1,
								"RuntimeErrorException" } } }, { 17, { { 0,
						"ClassNotFoundException" },
						{ 1, "RuntimeErrorException" } } }, { 18,
						{ { 0, "ClassExistException" }, { 1,
								"RuntimeErrorException" } } }, { 19, { { 0,
						"MethodNotFoundException" }, { 1,
						"RuntimeErrorException" } } }, { 20, { { 0,
						"PropertyNotFoundException" }, { 1,
						"RuntimeErrorException" } } }, { 21, { { 0,
						"FunctionParamsCountException" }, { 1,
						"RuntimeErrorException" } } },
				{ 22, { { 0, "RequestException" },
						{ 1, "RuntimeErrorException" } } }, { 23, { { 0,
						"DivisionByZeroException" }, { 1, "MathException" } } },
				{ 24, { { 0, "NegativeSqrtException" }, { 1, "MathException" } } },
				{ 25, { { 0, "InvalidLogarithmException" },
						{ 1, "MathException" } } }, { 26, { { 0,
						"MathOverflowException" }, { 1, "MathException" } } }, {
						27, { { 0, "FileNotFoundException" }, { 1,
								"IOErrorException" } } }, { 28,
						{ { 0, "PermissionDeniedException" }, { 1,
								"IOErrorException" } } }, { 29,
						{ { 0, "ThreadNotFoundException" }, { 1,
								"ThreadingException" } } }, { 30,
						{ { 0, "ThreadTimeoutException" }, { 1,
								"ThreadingException" } } }, { 31, { { 0,
						"ThreadExecutionException" },
						{ 1, "ThreadingException" } } } };

void log(string _message, long _lv = 1) {
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

void _log(string _message, long _lv = 1) {
	;
}
#endif /* LIBS_LIBS_H_ */
