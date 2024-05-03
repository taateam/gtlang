#ifndef LIBS_LIBS_H_
#define LIBS_LIBS_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
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
#include <php2cpp.h>
#include <Mixed.h>

bool php_is_array(Mixed _mixed) {
	return (_mixed.type == "a");
}
pair<long, long> T;
typedef map<long, Mixed> arr_lm;
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
		{ ".:", { { 0, 2 }, { 1, 6 } } }, { "[]", { { 0, 0 }, { 1, 0 } } }, {
				"*:", { { 0, 2 }, { 1, 6 } } },
		{ "/:", { { 0, 2 }, { 1, 6 } } }, { "%:", { { 0, 2 }, { 1, 6 } } }, {
				"<>", { { 0, 2 }, { 1, 5 } } },
		{ "&&", { { 0, 2 }, { 1, 7 } } }, { "||", { { 0, 2 }, { 1, 9 } } }, {
				"|&", { { 0, 2 }, { 1, 8 } } } };
arr_ls __keywords = { { 0, "if" }, { 1, "else" }, { 2, "class" }, { 3, "do" }, {
		4, "while" }, { 5, "break" }, { 6, "use" }, { 7, "switch" },
		{ 8, "new" }, { 9, "continue" }, { 10, "return" }, { 11, "include" }, {
				12, "throw" }, { 13, "try" }, { 14, "catch" },
		{ 15, "finally" }, { 16, "defcat" }, { 17, "deffin" },
		{ 18, "else if" }, { 19, "new" }, { 20, "do" }, { 21, "case" }, { 22,
				"continue" }, { 23, "for" }, { 24, "times" }, { 25, "from" }, {
				26, "to" }, { 27, "foreach" }, { 28, "as" }, { 29, "at" } };
arr_sl __keywords_reversed;
arr_ls __modifiers = { { 0, "private" }, { 1, "public" }, { 2, "static" } };
arr_sl __modifiers_reversed;
const string PHP_EOL = "\n";
const string CPP_EOL = "\n";
Mixed __funcs, __classes, __main;
typedef Mixed (*GTBuiltinFunction)(Mixed _args);
map<string, GTBuiltinFunction> __b_funcs;
//=============================================================================================
Mixed gt_echo(Mixed _input) {
	long _i = 0;
	long _size = gt_sizeof(_input);
	for (auto [_k, _v] : _input.valueArray) {
		Mixed _mv = (Mixed) *_v;
		echo(_mv.valueStr);
		_i++;
		if (_i < _size)
			echo(" ");
	}
	return Mixed();
}
Mixed use_language_file(Mixed _input) {
	string _lang_file = _input[0]["name"].valueStr;
	string _lang_content;
	try {
		_lang_content = file_get_contents(_lang_file);
	} catch (int _e) {
		echo("Warning: cannot access language file");
		return Mixed();
	}
	arr_ls _pairs = explode("\n", _lang_content);
	arr_ls _used_words;
	for (auto [_k, _pair] : _pairs) {
		if (substr_count(_pair, "=") != 1)
			continue;
		arr_ls _two_side = explode(" ", _pair);
		string _left = _two_side[0];
		string _right = _two_side[1];
		for (auto [_k, _word] : __keywords) {
			if (in_array(_right, _used_words))
				throw new GtlangException("language file has duplicate words");
			if (_word == _left) {
				array_push(_used_words, _right);
				__keywords[_k] = _right;
				continue;
			}
		}
		for (auto [_k, _word] : __modifiers) {
			if (in_array(_right, _used_words))
				throw new GtlangException("language file has duplicate words");
			if (_word == _left) {
				array_push(_used_words, _right);
				__modifiers[_k] = _right;
				continue;
			}
		}
		throw new GtlangException("language file has invalid words");
	}
	return Mixed();
}
//==============================================================================================

void init_translation() {
	for (auto [_k, _v] : __keywords) {
		__keywords_reversed[_v] = _k;
	}
	for (auto [_k, _v] : __modifiers) {
		__modifiers_reversed[_v] = _k;
	};
}
string l(string _original) {
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
void init_builtin_functions() {
	map<string, GTBuiltinFunction> _tmp;
	//---------------------------------------------
	_tmp["echo"] = gt_echo;
	_tmp["use_language_file"] = use_language_file;
	//---------------------------------------------
	for (auto [_k, _v] : _tmp) {
		__b_funcs["@" + _k] = _v;
	}
}
;

#endif /* LIBS_LIBS_H_ */
