/*
 * main.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: n
 */

#include <libs/libs.h>
#include <core/commons.h>
#include <core/io.h>
#include <core/token.h>
#include <core/structures.h>
#include <core/exec.h>
#include <core/ifs.h>
#include <core/functions.h>
#include <core/loops.h>
#include <core/classes.h>
#include <core/threads.h>
#include <core/maths.h>
#include <core/exceptions.h>
#include <core/mysql.h>
#include <core/requests.h>

using namespace std;

//string array_reconstruct(Mixed _arr, long _level) {
//	string _tab;
//	long _i;
//	string _k1;
//	Mixed _e1;
//	_tab = "";
//	for (_i = 0; _i < _level; _i++)
//		_tab += "\t";
//	for (auto  [_k1, _e1] : _arr.valueArray) {
//		if (((Mixed) _e1).type != "a")
//			_arr[_k1] = _tab+""\""+_k1+""\" => \"_e1\"";
//		else
//			_arr[_k1] = "_tab\"_k1\" => " + array_reconstruct(_e1, _level + 1);
//	}
//
//	return "[" + PHP_EOL + implode("," + PHP_EOL, _arr.valueArray) + PHP_EOL
//			+ _tab + "]";
//}

// ========================================================================================;
// ========================================================================================;
// ========================================================================================;
tokens_line1_arr tokenize(const string &_content) {
//cout << _content;
//exit(0);
	tokens_line1_arr _output_arr, _output_arr1;
	long _len;
	long _line;
	long _block_lv;
	long _i = 0;
	long _i1 = 0;
	string _extracted_str;
	bool _matches;
	string _char_i, __;
	string _answer_var;
	string _list_params;
//	long _char_count;
	tokens_line _operators;
	string _operator;
	// string _output_line;
//	_content = process_first_line(_content);
//_output_arr = { };
//	_content = remove_comments(_content);
//	_content = remove_blank_lines(_content);
	//_content = rtrim_all_lines(_content);
	//_content = _content + "\n";
	_len = strlen(_content);
	_line = 0;
	_block_lv = 0;
	for (_i = 0; _i < _len; _i++) {
// new_line ( _output_arr, _line );
// if (! isset ( _output_arr [_line] ))
// _output_arr [_line] = [ 0 => Mixed(),1 => 0
// ];
		_i1 = 0;
		_char_i = get_char_at_utf8(_content, _i);
		//continue;
		if (get_char_at_utf8(_content, _i) == "\n") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				__ = get_char_at_utf8(_content, _i + _i1);
				if (get_char_at_utf8(_content, _i + _i1) == " "
						|| get_char_at_utf8(_content, _i + _i1) == "\t") {
					continue;
				} else if (get_char_at_utf8(_content, _i + _i1) == "\n") {
					_i += _i1;
				} else {
					break;
				}
			}
			// continue;
			// ignore first tabs and spaces;
			_output_arr[_line]._0 = rtrim_tokens_line(_output_arr[_line]._0);
			new_line(_output_arr, _line);
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (get_char_at_utf8(_content, _i + _i1) != " "
						&& get_char_at_utf8(_content, _i + _i1) != "\t")
					break;
			}
			_extracted_str = substr(_content, _i + 1, _i1 - 1);
			_extracted_str = str_ireplace("\t", "    ", _extracted_str);
			_block_lv = round(strlen(_extracted_str) / 4);
			_output_arr[_line]._1 = _block_lv;
			_i += _i1 - 1;
		} else if (substr(_content, _i, 1) == ";") {
			long _old_lv = _output_arr[_line]._1;
			new_line(_output_arr, _line);
			_output_arr[_line]._1 = _old_lv;
		} else if (substr(_content, _i, 3) == "...") {
			_i += 2;
		} else if (get_char_at_utf8(_content, _i) == "\n"
				&& substr(_content, _i - 3, 3) == "...") {
			_i += 3;
		} else if (get_char_at_utf8(_content, _i) == ":"
				&& get_char_at_utf8(_content, _i + 1) != ":"//new_line(_output_arr, _line);
						) {
			tokens_push(_output_arr[_line]._0, { ":", "assignment" }, _i,
					_content);
		} else if (get_char_at_utf8(_content, _i) == " "
				|| get_char_at_utf8(_content, _i) == "\t") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (get_char_at_utf8(_content, _i + _i1) != " ")
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			tokens_push(_output_arr[_line]._0, { _extracted_str, "spaces" }, _i,
					_content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "\\"
				&& strlen(_content) > _i) {
			if (get_char_at_utf8(_content, _i + 1) == "n") {
				_extracted_str += "\n";
				_i += 1;
			} else if (get_char_at_utf8(_content, _i + 1) == "t") {
				_extracted_str += "\t";
				_i += 1;
			} else if (get_char_at_utf8(_content, _i + 1) != "") {
				_extracted_str += get_char_at_utf8(_content, _i + 1);
				_i += 1;
			}
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (get_char_at_utf8(_content, _i + _i1) == "\\") {
					if (get_char_at_utf8(_content, _i + _i1 + 1) == "n") {
						_extracted_str += "\n";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1)
							== "t") {
						_extracted_str += "\t";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1) != "") {
						_extracted_str += get_char_at_utf8(_content, _i + _i1);
						_i1 += 1;
					}
				} else {
					_matches = is_name_tag(
							get_char_at_utf8(_content, _i + _i1));
					if (!_matches)
						break;
					_extracted_str += get_char_at_utf8(_content, _i + _i1);
				}
			}
			//_extracted_str = substr(_content, _i + 1, _i1);
			// if (strlen ( _extracted_str ) == 1)
			// throw  ( "wrong string format" );
			tokens_push(_output_arr[_line]._0, { _extracted_str, "string" }, _i,
					_content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "$"
				&& get_char_at_utf8(_content, _i + 1) == "?") {
			tokens_push(_output_arr[_line]._0, { "answer_var", "var" }, _i,
					_content);
			_i += 1;
			continue;
		} else if (get_char_at_utf8(_content, _i) == "$"
				&& get_char_at_utf8(_content, _i + 1) == "@") {
			tokens_push(_output_arr[_line]._0, { "_list_params", "var" }, _i,
					_content);
			_i += 1;
			continue;
		} else if (get_char_at_utf8(_content, _i) == "$"
				&& get_char_at_utf8(_content, _i + 1) == "$") {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw GreenTeaException("SyntaxErrorException",
						"wrong var format", _extracted_str, _i, _content);
			tokens_push(_output_arr[_line]._0, { _extracted_str, "var_global" },
					_i, _content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "$") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw GreenTeaException("SyntaxErrorException",
						"wrong var format", _extracted_str, _i, _content);
			tokens_pushlv(_output_arr[_line]._0, { _extracted_str, "var" }, _i,
					_content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "@"
				&& get_char_at_utf8(_content, _i + 1) == "@") {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(php_to_string(_extracted_str.at(1))))
				throw GreenTeaException("SyntaxErrorException",
						"wrong function format @_", _extracted_str, _i,
						_content);
			tokens_push(_output_arr[_line]._0,
					{ _extracted_str, "function_self" }, _i, _content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "@"
				&& get_char_at_utf8(_content, _i + 1) == "$") {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(get_char_at_utf8(_extracted_str, 1)))
				throw GreenTeaException("SyntaxErrorException",
						"wrong function format @_", _extracted_str, _i,
						_content);
			tokens_push(_output_arr[_line]._0,
					{ _extracted_str, "function_var" }, _i, _content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "@"
				&& get_char_at_utf8(_content, _i + 1) != "@") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(php_to_string(_extracted_str.at(1))))
				throw GreenTeaException("SyntaxErrorException",
						"wrong function format", _extracted_str, _i, _content);
			tokens_pushlf(_output_arr[_line]._0, { _extracted_str, "function" },
					_i, _content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "^") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw GreenTeaException("SyntaxErrorException",
						"wrong class format", _extracted_str, _i, _content);
			tokens_pushl(_output_arr[_line]._0, { _extracted_str, "class" }, _i,
					_content);
			_i += _i1 - 1;
		} else if (is_numeric(get_char_at_utf8(_content, _i))) {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_is_preg_match("/[0-9.]+/",
						get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (substr_count(_extracted_str, ".") > 1)
				throw GreenTeaException("SyntaxErrorException",
						"wrong number format, more than 1 point",
						_extracted_str, _i, _content);
			tokens_push(_output_arr[_line]._0, { _extracted_str, "number" }, _i,
					_content);
			_i += _i1 - 1;
		} else if (get_char_at_utf8(_content, _i) == "\"") {
			_extracted_str = "";
			bool _flag = false;
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (get_char_at_utf8(_content, _i + _i1) == "\\") {
					if (get_char_at_utf8(_content, _i + _i1 + 1) == "n") {
						_extracted_str += "\n";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1)
							== "t") {
						_extracted_str += "\t";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1)
							== "\\") {
						_extracted_str += "\\";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1)
							== "\"") {
						_extracted_str += "\"";
						_i1 += 1;
					} else {
						_extracted_str += "\\";
					}
				} else if (get_char_at_utf8(_content, _i + _i1) == "\"") {
					//_extracted_str += php_to_string(_content.at(_i + _i1));
					_flag = true;
					break;
				} else {
					_extracted_str += get_char_at_utf8(_content, _i + _i1);
				}
			}
			// if (strlen ( _extracted_str ) == 1 || is_numeric ( _extracted_str ._1 ))
// throw  ( "wrong string format" );
			tokens_push(_output_arr[_line]._0, { _extracted_str, "string" }, _i,
					_content);
			_i += _i1;
			if (!_flag)
				throw GreenTeaException("SyntaxErrorException",
						"Unexpected EOF", _extracted_str, _i, _content);
		} else if (get_char_at_utf8(_content, _i) == "'") {
			_extracted_str = "";
			bool _flag = false;
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (get_char_at_utf8(_content, _i + _i1) == "\\") {
					if (get_char_at_utf8(_content, _i + _i1 + 1) == "\\") {
						_extracted_str += "\\";
						_i1 += 1;
					} else if (get_char_at_utf8(_content, _i + _i1 + 1)
							== "'") {
						_extracted_str += "'";
						_i1 += 1;
					} else {
						_extracted_str += "\\";
					}
				} else if (get_char_at_utf8(_content, _i + _i1) == "'") {
					//_extracted_str += php_to_string(_content.at(_i + _i1));
					_flag = true;
					break;
				} else {
					_extracted_str += get_char_at_utf8(_content, _i + _i1);
				}
			}
			// if (strlen ( _extracted_str ) == 1 || is_numeric ( _extracted_str ._1 ))
			// throw  ( "wrong string format" );
			tokens_push(_output_arr[_line]._0, { _extracted_str, "string" }, _i,
					_content);
			_i += _i1;
			if (!_flag)
				throw GreenTeaException("SyntaxErrorException",
						"Unexpected EOF", _extracted_str, _i, _content);
		} else if (substr(_content, _i, 1) == "#") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (substr(_content, _i + _i1, 1) == "\n")
					break;
			}
			_i += _i1 - 1;
		} else if (substr(_content, _i, 2) == "//") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (substr(_content, _i + _i1, 1) == "\n")
					break;
			}
			_i += _i1 - 1;
		} else if (substr(_content, _i, 2) == "/*") {
			for (_i1 = 1; _i1 < _len - _i - 1; _i1++) {
				if (substr(_content, _i + _i1, 2) == "*/")
					break;
			}
			_i += _i1 + 1;
		} else if (is_az(get_char_at_utf8(_content, _i))) {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = is_name_tag(get_char_at_utf8(_content, _i + _i1));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			string _gf = l(_extracted_str);
			if (in_array(l(_extracted_str), __keywords))
				tokens_pushl(_output_arr[_line]._0,
						{ _extracted_str, "keyword" }, _i, _content);
			else if (in_array(l(_extracted_str), __modifiers))
				tokens_pushl(_output_arr[_line]._0,
						{ _extracted_str, "modifier" }, _i, _content);
			else if (l(_extracted_str) == "true")
				tokens_push(_output_arr[_line]._0, { "true", "bool" }, _i,
						_content);
			else if (l(_extracted_str) == "false")
				tokens_push(_output_arr[_line]._0, { "false", "bool" }, _i,
						_content);
			else {
				for (; _i1 < _len - _i; _i1++) {
					if (get_char_at_utf8(_content, _i + _i1) == "\\") {
						if (get_char_at_utf8(_content, _i + _i1 + 1) == "n") {
							_extracted_str += "\n";
							_i1 += 1;
						} else if (get_char_at_utf8(_content, _i + _i1 + 1)
								== "t") {
							_extracted_str += "\t";
							_i1 += 1;
						} else if (get_char_at_utf8(_content, _i + _i1 + 1)
								!= "") {
							_extracted_str += get_char_at_utf8(_content,
									_i + _i1 + 1);
							_i1 += 1;
						}
					} else {
						_matches = is_name_tag(
								get_char_at_utf8(_content, _i + _i1));
						if (!_matches)
							break;
						_extracted_str += get_char_at_utf8(_content, _i + _i1);
					}
				}
				tokens_push(_output_arr[_line]._0, { _extracted_str, "string" },
						_i, _content);
			}
			_i += _i1 - 1;
		} else if (in_array(get_char_at_utf8(_content, _i),
				__operator_1st_chars)) {
			bool check = false;
			long _char_count;
			arr_ls _operators;
			for (_char_count = gt_sizeof(__operators_by_chars_count);
					_char_count > 0; _char_count--) {
				_operators = __operators_by_chars_count[_char_count];
				for (auto [_key_rtt, _operator] : _operators) {
					_operator = (string) _operator;
					if (substr(_content, _i, _char_count) == _operator) {
						tokens_push(_output_arr[_line]._0,
								{ substr(_content, _i, _char_count), "operator" },
								_i, _content);
						_i += _char_count - 1;
						check = true;
						break;
					}
//					if (check)
//						break;
				}
				if (check)
					break;
			}
			if (!check)
				tokens_push(_output_arr[_line]._0,
						{ get_char_at_utf8(_content, _i), "other0" }, _i,
						_content);
		} else {
			tokens_push(_output_arr[_line]._0, { get_char_at_utf8(_content, _i),
					"other" }, _i, _content);
		}
	}
	for (auto [_k, _output_line] : _output_arr) {
		//echo("hi");
		if (!((tokens_line1) _output_line)._0.empty())
			_output_arr1[(long) _k] = _output_line;
	}
	_output_arr = array_values(_output_arr1);
	return _output_arr;
}
Mixed parse_expression_inner(Mixed &_tokens_line_arr) {
	/* parse 1 line, only an 2 dimensions tokens array */
//	if (gt_sizeof(_tokens_line_arr) < 2)
//		return _tokens_line_arr;
	Mixed _return;
	Mixed _tokens_line1_arr = array_values(_tokens_line_arr);
	Mixed _tokens_outside_brackets = Mixed();
// scan for ( ) and  [ ];
	arr_ll _commas_pos;
	Mixed _values_arr;
	_tokens_line1_arr = convert_spaces_to_concat_operators(_tokens_line1_arr);
	_tokens_line1_arr = remove_spaces_from_tokens_arr(_tokens_line1_arr);
	for (long _k = 0; _k < gt_sizeof(_tokens_line1_arr); _k++) {
		Mixed _token = _tokens_line1_arr[_k];
		if (_token == token("(", "operator")) {
			Mixed _expr_in_brackets_arr = get_arr_between_brackets_mixed("(",
					_tokens_line1_arr, _k);
			Mixed _expr_in_brackets_result = parse_expression(
					_expr_in_brackets_arr);
			_k += gt_sizeof(_expr_in_brackets_arr) + 1;
			_tokens_outside_brackets.push(_expr_in_brackets_result);
			continue;
		}
		if (_token == token("[", "operator")) {
			Mixed _expr_in_brackets_arr = get_arr_between_brackets_mixed("[",
					_tokens_line1_arr, _k);
			bool _is_array = _is_array_square_brackets(_tokens_line1_arr, _k);
			if (_is_array) {
				_expr_in_brackets_arr.resetKeys();
				_commas_pos = find_all_token_at_level_0(token(",", "operator"),
						_expr_in_brackets_arr);
				_values_arr = array_cut_by_pos(_expr_in_brackets_arr,
						_commas_pos);
				Mixed _results, _tmp_list_results;
				_results.push("type", "array");
				for (auto [_i, _values_tokens] : _values_arr.valueArray) {
					_tmp_list_results.push(_i,
							parse_expression(*_values_tokens));
				}
				_results.push("body", _tmp_list_results);
				add_pos_of_1st_token_to_mix(_results, get_1st_ele(_values_arr));
				_tokens_outside_brackets.push(_results);
			} else {
				Mixed _expr_in_brackets_result = parse_expression(
						_expr_in_brackets_arr);
//				print_r(_expr_in_brackets_arr);
				_tokens_outside_brackets.push(token("[]", "operator"));
				_tokens_outside_brackets.push(_expr_in_brackets_result);
			}
			_k += gt_sizeof(_expr_in_brackets_arr) + 1;
			continue;
		}
		if (_token == token(")", "operator")) {
			throw GreenTeaException("SyntaxErrorException", "Invalid ')'",
					_tokens_line_arr[_k]);
		}
		if (_token == token("]", "operator")) {
			throw GreenTeaException("SyntaxErrorException", "Invalid ']'",
					_tokens_line_arr[_k]);
		}
		_tokens_outside_brackets.push(_token);
	}
//throw expression
	if (_tokens_outside_brackets[0] == token("throw", "keyword")) {
		if (gt_sizeof(_tokens_outside_brackets) < 2)
			throw GreenTeaException("SyntaxErrorException",
					"Throw must be followed by value");
		Mixed _expr_after_throw = array_slice(_tokens_outside_brackets, 1, -1);
		Mixed _exception_obj = parse_expression(_expr_after_throw);
		_return.push("type", "throw");
		_return.push("object", _exception_obj);
		return _return;
	}
// assignment expr
// if there is a assignment in tokens_arr then this is an assignment, not complexed expr
//	print_r(_tokens_outside_brackets);
	for (auto& [_k, _auto_token] : _tokens_outside_brackets.valueArray) {
		Mixed _token(*_auto_token);
		if (_token == token(":", "assignment")) {
			_log("assignment expr:");
			Mixed _return0 = process_assignment(_tokens_outside_brackets);
			return _return0;
		}
	}
// simple function, not including method;
// if there is a function call ((not a method call) in tokens_arr then this is an function call, not complexed expr
	Mixed _function_and_params = get_function_and_params_lv0(
			_tokens_outside_brackets);
	if (!_function_and_params.valueArray.empty()
			&& isset(_function_and_params, "name")) {
		_log("function expr:");
		string _function_name = (string) _function_and_params["name"];
		Mixed _function_args = _function_and_params["params"];
		Mixed _return0;
		_return0.push("type", "function_call");
		_return0.push("name", _function_name);
		_return0.push("args", _function_args);
		//		_return = replace_placeholders_recruisively(_return0,
		//				_map_placeholders);
		//		print_r(_return0);
		return _return0;
	}
// simple method;
// if there is a method call in tokens_arr then this is an function call, not complexed expr
	Mixed _method_and_params = get_method_and_params_lv0(
			_tokens_outside_brackets);
	if (!_method_and_params.valueArray.empty()
			&& isset(_method_and_params, "name")) {
		_log("method expr:");
		return _method_and_params;
	}
// multiple operator but no brackets expr

//	_tokens_outside_brackets = convert_spaces_to_concat_operators(
//			_tokens_outside_brackets);
//	_tokens_outside_brackets = remove_spaces_from_tokens_arr(
//			_tokens_outside_brackets);
	long _operators_count = 0;
	for (auto [_key_rtt, _token] : _tokens_outside_brackets.valueArray) {
		if (get_type(*_token) == "operator")
			_operators_count++;
	}
	if (is_inline_conditional_expr(_tokens_outside_brackets)) {
		return parse_inline_conditional_expr(_tokens_outside_brackets);
	}
	// new object of class
	if (_operators_count > 1) {
		Mixed _return0 = process_multiple_operators(_tokens_outside_brackets);
//		echo("hihi");
//		print_r(_return0);
		return _return0;
	}
// single [] expr
	if (gt_sizeof(_tokens_outside_brackets) == 1
			&& get_1st_ele(_tokens_outside_brackets)
					== token("[]", "operator")) {
		_return.push("type", "array");
		_return.push("body", Mixed());
		return _return;
	}
	// single operator but no brackets expr
	if (_operators_count == 1
			&& get_type(get_1st_ele(_tokens_outside_brackets)) != "keyword") {
		validate_single_operator(_tokens_outside_brackets);
//		echo("hihi");
//		print_r(_return0);
		_return.push("type", "expr");
		_return.push("body", _tokens_outside_brackets);
		return _return;
	}
//? if
	if (is_new_clause(_tokens_outside_brackets)) {
		Mixed _tokens_arr1 = _tokens_outside_brackets;
		for (auto [_j, _token] : _tokens_outside_brackets.valueArray) {
			if (get_name(*_token) == l("new") && get_type(*_token) == "keyword")
				_tokens_arr1[(string) _j] = Mixed(token("@new", "function"));
		}
		_return = get_function_and_params_lv0(_tokens_arr1);
		Mixed _classes;
		for (auto [_l, _param] : _return["params"].valueArray) {
			string _type;
			if (isset(*_param, "type"))
				_type = (string) (Mixed) (*_param)["type"];
			else
				_type = (string) (Mixed) (*_param)[1];
			if (_type == "class") {
				string _name;
				if (isset(*_param, "name"))
					_name = (string) (Mixed) (*_param)["name"];
				else
					_name = (string) (Mixed) (*_param)[0];
				_classes.push(_name);
				_return["params"].delete_e(_l);
			}
		}
		if (gt_sizeof(_classes) != 1)
			throw GreenTeaException("SyntaxErrorException",
					"new but no/multi class");
		reset(_return["params"]);
		_return.push("type", "new");
		_return.push("class", _classes[0]);
		_return.push("params", _return["params"]);
		return _return;
	}
// simple single operator expr
	Mixed _body_tmp = _tokens_outside_brackets;
//	if (gt_sizeof(_body_tmp) < 2)
//		return _body_tmp[0];
	_return.push("type", "expr");
	_return.push("body", _body_tmp);
	return _return;
}
Mixed parse_expression(Mixed &_tokens_line_arr) {
	Mixed _return = parse_expression_inner(_tokens_line_arr);
	add_pos_of_1st_token_to_mix(_return, (_tokens_line_arr));
	return _return;
}
//Mixed parse_expression1(Mixed &_tokens_line1_arr) {
//	arr_ls _value_types;
//	token _tk_tmp;
//	array_push(_value_types, "string");
//	array_push(_value_types, "number");
//	array_push(_value_types, "expr");
//	array_push(_value_types, "var");
//	array_push(_value_types, "array");
//	array_push(_value_types, "complex_value");
//	Mixed _complex_expr_arr, _previous_token_type;
//	Mixed _first_token;
//	bool _is_complex_expr;
////	long _k;
//	Mixed _token, _tmp, _tmp1, _body_tmp;
//	Mixed _result_arr;
//	Mixed _parsed;
//	Mixed _function_and_params;
//	string _function_name;
//	Mixed _function_args;
//	long _operators_count;
//	tokens_line _tokens_arr1;
////	long _j;
//	Mixed _return, _return0, _return1;
//	arr_ls _classes;
////	long _l;
//	Mixed _param;
//	string _type;
//	string _name;
//// _log("parse_expression():");
//// print_r(_tokens_line1_arr);
//	if (isset(_tokens_line1_arr, "type")) {
//		Mixed _type_m = _tokens_line1_arr["type"];
//		if (_type_m == ((string) "expr"))
//			_tokens_line1_arr = (Mixed) _tokens_line1_arr["data"];
//		_complex_expr_arr = Mixed();
//	}
////	reset(_tokens_arr);
////Mixed _xxx;
////_xxx = tokens_arr_trim1(_tokens_line1_arr);
//	if (gt_sizeof(_tokens_line1_arr) == 1) {
//		if (is_token(get_1st_ele(_tokens_line1_arr))) {
//			if (in_array((string) get_1st_ele(_tokens_line1_arr)[1], { { 0,
//					"string" }, { 1, "number" }, { 2, "var" }, { 3, "class" }, {
//					4, "array" }, { 5, "expr" } })) {
//				_first_token = get_1st_ele(_tokens_line1_arr);
//				_return.push("type", _first_token[1]);
//				_return.push("name", _first_token[0]);
//				return _return;
//			}
//		} else {
//			_return = get_1st_ele(_tokens_line1_arr);
//			return _return;
//		}
//	}
//// brackets expr
//	_tokens_line1_arr.resetKeys();
//	while (true) {
//		for (long _k = 1; _k < gt_sizeof(_tokens_line1_arr); _k++) {
//			Mixed _token = _tokens_line1_arr[_k];
//			if (isset(_tokens_line1_arr[_k - 1], 1))
//				_previous_token_type = _tokens_line1_arr[_k - 1][1];
//			else
//				_previous_token_type = _tokens_line1_arr[_k - 1]["type"];
//			if (in_array((string) _previous_token_type, _value_types)
//					&& get_name(_token) == "["
//					&& get_type(_token) == "operator") {
//				_result_arr = get_arr_between_brackets_mixed("[",
//						_tokens_line1_arr, _k);
//				_tmp = array_slicem(_tokens_line1_arr, 0, _k);
//				_tk_tmp = token("get_ele", "operator");
//				_tmp1 = Mixed(_tk_tmp);
//				_tmp.push(_tmp1);
//				Mixed _parsed_expression = parse_expression(_result_arr);
//				_tmp.push((Mixed) _parsed_expression);
//				_tmp = array_merge(_tmp,
//						array_slicem(_tokens_line1_arr,
//								_k + sizeof(_result_arr) + 2));
//				_tokens_line1_arr = _tmp;
//				continue;
//			}
//		}
//		break;
//	}
//	_is_complex_expr = false;
//	_tokens_line1_arr.resetKeys();
//	for (long _k = 0; _k < gt_sizeof(_tokens_line1_arr); _k++) {
//		_token = _tokens_line1_arr[_k];
//		if (get_name(_token) != "(" && get_name(_token) != "[") {
//			_complex_expr_arr.push((Mixed) _token);
//			continue;
//		}
//		if (get_name(_token) == "(" && get_type(_token) == "operator") {
//			_is_complex_expr = true;
//			_result_arr = get_arr_between_brackets_mixed("(", _tokens_line1_arr,
//					_k);
//			_complex_expr_arr.push(parse_expression(_result_arr));
//			_k += gt_sizeof(_result_arr) + 2;
//		} else if (_token[0] == "[" && _token[1] == "operator") {
//			_is_complex_expr = true;
//			_result_arr = get_arr_between_brackets_mixed("[", _tokens_line1_arr,
//					_k);
//			//Mixed j = _result_arr.to_tokens_line();
//			_complex_expr_arr.push(parse_array(_result_arr.to_tokens_line()));
//			_k += gt_sizeof(_result_arr) + 2;
//		} else if (_token[0] == ")" && _token[1] == "operator") {
//			throw GtlangException("SyntaxErrorException","not valid close round bracket");
//		} else if (_token[0] == "]" && _token[1] == "operator") {
//			throw GtlangException("SyntaxErrorException","not valid close square bracket");
//		} else {
//			_complex_expr_arr.push(_token);
//		}
//	}
//	mixed_to_tokens_line_with_place_holders_rs complex_tokens_line_rs =
//			mixed_to_tokens_line_with_place_holders(_complex_expr_arr);
//	tokens_line complex_tokens_line = complex_tokens_line_rs._0;
//	map<string, Mixed> _map_placeholders = complex_tokens_line_rs._1;
//	if (_is_complex_expr) {
//		_parsed = parse_expression(_complex_expr_arr);
//		if (in_array(_parsed["type"], { { 0, "array" }, { 1, "expr" }, { 2,
//				"assignment" }, { 3, "function" } }))
//			return replace_placeholders_recruisively(_parsed, _map_placeholders);
//		else {
//			_return0.push("type", "expr");
//			_return0.push("body", _return1);
//			return replace_placeholders_recruisively(_return0,
//					_map_placeholders);
//		}
//	}
//// assignment expr
//	for (auto& [_k, _auto_token] : _tokens_line1_arr.valueArray) {
//		Mixed _token(*_auto_token);
//		if (isset(_token, "name") && _token["name"] == ":"
//				&& _token["type"] == "assignment") {
//			_log("assignment expr:");
//			_return0 = process_assignment(_tokens_line1_arr.to_tokens_line());
//			return replace_placeholders_recruisively(_return0,
//					_map_placeholders);
//		}
//	}
//// simple function
//	_function_and_params = get_function_and_params_lv0(
//			to_tokens_line(_complex_expr_arr));
//	if (!_function_and_params.valueArray.empty()
//			&& isset(_function_and_params, "name")) {
//		_log("function expr:");
//		_function_name = (string) _function_and_params["name"];
//		_function_args = _function_and_params["params"];
//		_return0.push("type", "function");
//		_return0.push("name", _function_name);
//		_return0.push("args", _function_args);
//		_return = replace_placeholders_recruisively(_return0,
//				_map_placeholders);
////		print_r(_return0);
//		return _return;
//	}
//// multiple operator but no brackets expr
//	complex_tokens_line = convert_spaces_to_concat_operators(
//			complex_tokens_line);
//	_operators_count = 0;
//	for (auto [_key_rtt, _token] : complex_tokens_line) {
//		if (_token._1 == "operator")
//			_operators_count++;
//	}
//	if (_operators_count > 1) {
//		_return0 = process_multiple_operators(complex_tokens_line);
//		return replace_placeholders_recruisively(_return0, _map_placeholders);
//	}
//// new object of class
//	if (is_new_clause(complex_tokens_line)) {
//		_tokens_arr1 = complex_tokens_line;
//		for (auto [_j, _token] : complex_tokens_line) {
//			if (_token._0 == l("new") && _token._1 == "keyword")
//				_tokens_arr1[(long) _j] = token("@new", "function");
//		}
//		_return = get_function_and_params_lv0(_tokens_arr1);
//		_classes = { };
//		for (auto [_l, _param] : _return["params"].valueArray) {
//			if (isset(*_param, "type"))
//				_type = (string) (Mixed) (*_param)["type"];
//			else
//				_type = (string) (Mixed) (*_param)[1];
//			if (_type == "class") {
//				if (isset(*_param, "name"))
//					_type = (string) (Mixed) (*_param)["name"];
//				else
//					_type = (string) (Mixed) (*_param)[0];
//				array_push(_classes, _name);
//				_return["params"].delete_e(_l);
//			}
//		}
//		if (gt_sizeof(_classes) != 1)
//			throw GtlangException"SyntaxErrorException","new but no/multi class");
//		reset(_return["params"]);
//		_return.push("type", "new");
//		_return.push("class", _classes[0]);
//		_return.push("params", _return["params"]);
//		return _return;
//	}
//// simple single operator expr
//	_return.push("type", "expr");
//	_body_tmp = tokens_arr_to_name_and_type_format(complex_tokens_line);
//	_return.push("body",
//			replace_placeholders_recruisively(_body_tmp, _map_placeholders));
//	return _return;
//}
//}
//Mixed process_user_function(long &_line_num,
//		tokens_line1_arr _tokens_line1_arr) {
//	Mixed _return;
//	tokens_line _function_name_params = _tokens_line1_arr[_line_num]._0;
//	getline_subblock_t _getline_subblock = getline_subblock(_tokens_line1_arr,
//			_line_num);
//	_line_num += _getline_subblock.i;
//	tokens_line1_arr _body = _getline_subblock.arr;
//	arr_ll _function_names_pos = find_all_token_type_at_level_0("function",
//			_function_name_params);
//	if (gt_sizeof(_function_names_pos) != 1)
//		throw GtlangException("SyntaxErrorException","Invalid function token count.");
//	long _function_name_pos = _function_names_pos[0];
//	string _function_name = get_name(_function_name_params[_function_name_pos]);
//	tokens_line _params = _function_name_params;
//	arr_remove(_params, _function_name_pos);
//	arr_remove(_params, gt_sizeof(_params) - 1);
//	arr_ll _commas_pos = find_all_token_at_level_0(token(",", "operator"),
//			_params);
//	tokens_line_arr _params_arr = array_cut_by_pos(_params, _commas_pos);
//	Mixed _list_of_params;
//	for (auto [_k, _v] : _params_arr) {
//		if (gt_sizeof(_v) < 1)
//			throw("Invalid param without name");
//		else if (gt_sizeof(_v) == 1) {
//			_list_of_params.push(_v);
//		} else {
//			_list_of_params.push(process_assignment(_v));
//		}
//	}
//	_return.push("type", "user_function");
//	_return.push("name", _function_name);
//	_return.push("params", _list_of_params);
//	_return.push("body", structurelize(_body));
//	return _return;;
//}
Mixed structurelize(tokens_line1_arr _tokens_line1_arr) {
	for (auto [_k, _v] : _tokens_line1_arr) {
		_tokens_line1_arr[_k] = convert_spaces_to_concat_operators(_v);
	}
	Mixed _return, _return_tmp, _tmp, _tmp1, _tmp2;
	Mixed _defcat_rs;
	long _line;
	tokens_line1 _tokens_n_lv;
	tokens_line _tokens;
//	long _block_lv;
	Mixed _line_rs;
	Mixed _func_declare;
	Mixed _class_name;
// _tokens_arr = remove_blank_lines ( _tokens_arr );
	_tokens_line1_arr = array_values(_tokens_line1_arr);
	for (_line = 0; _line < gt_sizeof(_tokens_line1_arr); _line++) {
//		_line = _k;
		_tokens_n_lv = _tokens_line1_arr.at(_line);
		_tokens = ltrim_arr(_tokens_n_lv._0);
// _block_lv = _tokens_n_lv ._1;
		if (_tokens[0]._0 == l("if") && _tokens[0]._1 == "keyword") {
			_line_rs = process_if(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("for") && _tokens[0]._1 == "keyword") {
			_line_rs = process_for(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("foreach")
				&& _tokens[0]._1 == "keyword") {
			_line_rs = process_foreach(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("while") && _tokens[0]._1 == "keyword") {
			_line_rs = process_while(_line, _tokens_line1_arr);
		} else if ((bool) (_func_declare = is_function_def(_tokens))) {
			_line_rs = process_user_function_def(_line, _tokens_line1_arr,
					_func_declare);
		} else if ((bool) (_class_name = is_class_def(_tokens))) {
			_line_rs = process_class_def(_line, _tokens_line1_arr, _class_name);
		} else if (_tokens[0]._0 == l("try") && _tokens[0]._1 == "keyword") {
			_line_rs = process_try(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("defcat") && _tokens[0]._1 == "keyword") {
			_defcat_rs = process_defcat(_line, _tokens_line1_arr);
			continue;
		} else
			_line_rs = parse_expression(_tokens_n_lv._0);
		add_pos_of_1st_token_to_mix(_line_rs, _tokens);
		_return_tmp.push(_line_rs);
	}
	if (!_defcat_rs.empty()) {
		_tmp1.push("type", "block");
		_tmp1.push("body", _return_tmp);
		_tmp1.push("token", _line_rs["token"]);
		_tmp1.push("l", _line_rs["l"]);
		_tmp1.push("c", _line_rs["c"]);
		_tmp.push("type", "try");
		_tmp.push("body", _tmp1);
		_tmp.push("catch", _defcat_rs["body"]);
		_tmp.push("finally", _defcat_rs["deffin"]);
		_tmp2.push(_tmp);
		_return.push("type", "block");
		_return.push("body", _tmp2);
		add_pos_of_1st_token_to_mix(_return, _tokens_line1_arr[0]._0);
		return _return;
	}
	_return.push("type", "block");
	_return.push("body", _return_tmp);
	add_pos_of_1st_token_to_mix(_return, _tokens_line1_arr[0]._0);
	return _return;
}
bool _has_class(const Mixed &_obj, const string &_class_name) {
	string _class_of_obj = _obj["class"];
	if (_class_of_obj == _class_name)
		return true;
	Mixed _extends = get_classes()[_class_of_obj]["extends"];
	bool _return = false;
	for (auto [_k, _v] : _extends.valueArray) {
		if (_class_name == (string) *_v) {
			_return = true;
			break;
		}
	}
	return _return;
}
//Mixed find_all_vars_in_function_def(Mixed _function) {
//	Mixed _inner_vars;
//	_inner_vars = find_all_unique_types_non_block_in_body("var",
//			_function["body"]);
//	array_remove_each(_inner_vars, _function["vars"]);
//	return _inner_vars;
//}
//bool find_return_in_body(Mixed _body) {
//	Mixed _tmp1;
//	_tmp1.push("name", "@return");
//	_tmp1.push("type", "function");
//	return find_an_obj_in_body(_tmp1, _body);
//}
//==================================================================================================================================================================
//void assign_var(string var, Mixed value) {
////TODO:
//	;
//}
//Mixed eval(Mixed _expr);
//long exec(Mixed _parsed) {
//	Mixed _v;
//	if (_parsed.type != "block") {
//		throw "not a block";
//	}
//	for (auto [_k, _v] : _parsed.valueArray) {
//		if ((*_v)["type"] == "ifs") {
//			for (auto [_k1, _v1] : (*_v)["ifs"].valueArray) {
//				bool _check = (bool) eval((Mixed) (*_v1)["condition"]);
//				if (_check) {
//					exec((Mixed) (*_v1)["body"]);
//					break;
//				}
//			}
//			exec((Mixed) (*_v)["else"]);
//		} else if ((*_v)["type"] == "try") {
//			try {
//				exec((Mixed) (*_v)["try"]);
//			} catch (GtlangException &_e) {
//				for (auto [_k1, _v1] : (*_v)["catches"].valueArray) {
//					if (_e.msg == (string) _v1["exception_class"]) {
//						assign_var((string) _v1["catch_var"], Mixed(_e.msg));
//						exec(_v1["body"]);
//					}
//				}
//			}
//		} else if ((*_v)["type"] == "for") {
//			;
//		} else if ((*_v)["type"] == "while") {
//			;
//		} else if ((*_v)["type"] == "foreach") {
//			;
//		} else if ((*_v)["type"] == "func_def") {
//			;
//		} else if ((*_v)["type"] == "class_def") {
//			;
//		} else if ((*_v)["type"] == "method") {
//			;
//		} else {
//			eval(_v);
//		}
//	}
//}
//Mixed eval(Mixed _expr) {
//	Mixed _return;
//	return _return;
//}
//long __break, __continue = 0;
Mixed gt_eval(const Mixed &_parsed) {
	log("gt_eval(): ");
//	print_r(_parsed);
	Mixed _find_result;
	Mixed _result;
	Mixed _backup_vars;
	if (!php_is_array(_parsed))
		return _parsed;
	if (get_type(_parsed) == "number") {
		return Mixed(td(get_name(_parsed)));
	}
	if (get_type(_parsed) == "string") {
		return Mixed(get_name(_parsed));
	}
	if (get_type(_parsed) == "class") {
		return _parsed;
	}
	if (get_type(_parsed) == "bool") {
		if (get_name(_parsed) == "true")
			return Mixed(true);
		else if (get_name(_parsed) == "false")
			return Mixed(false);
		else
			throw InternalException("Invalid bool type");
	}
//	return _parsed["name"];
	if (_parsed["type"] == "expr") {
		if (gt_sizeof(_parsed["body"]) == 1) {
			Mixed _tmp = get_1st_ele(_parsed["body"]);
			return gt_eval(_tmp);
		} else {
			_find_result = find_operator_in_expr(_parsed);
			if (gt_sizeof(_find_result) == 0)
				return _result;
			_result = gt_do(_find_result["operator"].valueStr,
					_find_result["expr"], _find_result["opt_pos"].valueNum);
			return _result;
		}
	}
	if (_parsed["type"] == "array") {
		return create_array_var(_parsed);
	}
	if (_parsed["type"] == "var") {
		return get_value(_parsed);
	}
	if (_parsed["type"] == "var_global") {
		return get_var_global_value(_parsed);
	}
	if (_parsed["type"] == "null") {
		return (_parsed);
	}
	if (_parsed["type"] == "function_call") {
		_result = call_function(_parsed);
		return _result;
	}
	if (_parsed["type"] == "method_call") {
		_result = call_method(_parsed);
		return _result;
	}
//	if (_parsed["type"] == "array") {
//		return create_array_var(_parsed);
//	}
	if (_parsed["type"] == "assignment") {
		if (isset(_parsed["right"], "body")
				&& isset(_parsed["right"]["body"], 0)
				&& isset(_parsed["right"]["body"][0], "type")
				&& _parsed["right"]["body"][0]["type"].valueStr == "array") {
			assign_array(_parsed);
			return _result;;
		} else {
			_result = gt_eval(_parsed["right"]);
			assign_var(_parsed["left"], _result);
			return _result;
		}
	}
//array's element;
	if (_parsed["type"] == "complex_value") {
		_result = get_value(_parsed);
		return _result;
	}
	if (_parsed["type"] == "class_def") {
		_result = register_class(_parsed);
		return _result;
	}
	if (_parsed["type"] == "inline_if") {
		if (gt_eval(_parsed["condition"]))
			return gt_eval(_parsed["value_if_true"]);
		return gt_eval(_parsed["value_if_false"]);
	}
	throw GreenTeaException("SyntaxErrorException", "unsupported expr",
			_parsed);
}
gt_exec_rs gt_exec(const Mixed &_cmd) {
	log("gt_exec() start");
//	Mixed _cmd = _parsed;
	Mixed _if;
	bool _is_catched;
	Mixed _e;
	Mixed _answer_var;
//block
	gt_exec_rs _result, _return;
	gt_exec_rs _null("null", 0);
	if (_cmd["type"] == "block" || _cmd["type"] == "inline_block") {
		log(((string) _cmd["type"]) + ": ");
		for (auto& [_key_rtt, _auto_cmd] : _cmd["body"].valueArray) {
			log("gt_exec(): running: ");
//			print_r(*_auto_cmd);
//			if (__break > 0 || __continue > 0) {
//				// _break --;
//				return 1;
//			}
			_result = gt_exec(*_auto_cmd);
			if (_result._type == "break") {
				long _count = _result._value.getInt();
//				if (_count >= 0) {
				return gt_exec_rs("break", _count);
//				}
			} else if (_result._type == "continue") {
				long _count = _result._value.getInt();
//				if (_count >= 0) {
				return gt_exec_rs("continue", _count);
//				}
			} else if (_result._type == "return") {
				return _result;
			}
		}
		return _null;
	}
//single comand
	log("gt_exec() non block: ");
//	print_r(_cmd);
	if (_cmd["type"] == "throw") {
		Mixed _exception = gt_eval(_cmd["object"]);
		throw GreenTeaException(_exception);
	} else if (_cmd["type"] == "ifs") {
		for (auto& [_key_rtt, _if_auto] : _cmd["ifs"].valueArray) {
			Mixed _if = (Mixed) *_if_auto;
			if (gt_eval(_if["condition"])) {
				return gt_exec(((Mixed) _if)["body"]);
			}
		}
		return gt_exec(_cmd["else"]);

	} else if (_cmd["type"] == "for") {
		gt_exec(_cmd["init"]);
		while (true) {
			if (!gt_eval(_cmd["terminate"]))
				break;
			_result = gt_exec(_cmd["body"]);
			if (_result._type == "return")
				return _result;
			else if (_result._type == "break") {
				_result._value.valueNum--;
				if (_result._value.valueNum > 0)
					return _result;
				else if (_result._value.valueNum == 0)
					return _null;
			} else if (_result._type == "continue") {
				_result._value.valueNum--;
				if (_result._value.valueNum > 0)
					return _result;
				else if (_result._value.valueNum == 0) {
					gt_exec(_cmd["increment"]);
					continue;
				}
			}
			gt_exec(_cmd["increment"]);
		}
		return _null;
	} else if (_cmd["type"] == "foreach") {
		Mixed _arr = gt_eval(_cmd["arr"]);
		Mixed _k_var = _cmd["k"];
		Mixed _v_var = _cmd["v"];
		for (auto [_k, _v] : _arr.valueArray) {
			assign_var(_k_var, Mixed(_k));
			assign_var(_v_var, *_v);
			gt_exec(_cmd["body"]);
		}
		return _null;
	} else if (_cmd["type"] == "while") {
		while (true) {
			//print_r(_cmd["condition"]);
			//break;
			if (!gt_eval(_cmd["condition"]))
				break;
			_result = gt_exec(_cmd["body"]);
			if (_result._type == "return")
				return _result;
			else if (_result._type == "break") {
				_result._value = Mixed(_result._value.valueNum - 1);
				if (_result._value.valueNum > 0)
					return _result;
				else if (_result._value.valueNum == 0)
					return _null;
			} else if (_result._type == "continue") {
				_result._value = Mixed(_result._value.valueNum - 1);
				if (_result._value.valueNum > 0)
					return _result;
				else if (_result._value.valueNum == 0)
					continue;
			};
		}
	} else if (_cmd["type"] == "try") {
		try {
			gt_exec(_cmd["body"]);
			if (isset(_cmd["finally"], "body"))
				gt_exec(_cmd["finally"]);
		} catch (GreenTeaException &_e) {
			_is_catched = false;
			for (auto [_key_rtt, _catch_auto] : _cmd["catch"].valueArray) {
				Mixed _catch = (Mixed) *_catch_auto;
				if (_has_class(_e.obj, _catch["exception_class"])) {
					Mixed _catch_var;
					_catch_var.push("name", _catch["catch_var"]);
					_catch_var.push("type", "var");
					assign_var(_catch_var, _e.obj);
					gt_exec(_catch["body"]);
					if (isset(_cmd["finally"], "body"))
						gt_exec(_cmd["finally"]);
					_is_catched = true;
					break;
				}
			}
			if (!_is_catched) {
//				gt_exec(_cmd["finally"]["body"]);
				throw GreenTeaException(_e);
			}
		}
	} else if (isset(_cmd, "body") && isset(_cmd["body"], 0)
			&& _cmd["body"][0] == token("break", "keyword")) {
		if (gt_sizeof(_cmd["body"]) == 1) {
			return gt_exec_rs("break", 1);
		} else if (gt_sizeof(_cmd["body"]) == 2
				&& _cmd["body"][1]["type"] == "number") {
			return gt_exec_rs("break", _cmd["body"][1]["name"].getInt());
		} else
			throw GreenTeaException("SyntaxErrorException", "incorrect break",
					_cmd["body"][0]);
	} else if (isset(_cmd, "body") && isset(_cmd["body"], 0)
			&& _cmd["body"][0] == token("continue", "keyword")) {
		if (gt_sizeof(_cmd["body"]) == 1) {
			return gt_exec_rs("continue", 1);
		} else if (gt_sizeof(_cmd["body"]) == 2
				&& _cmd["body"][1]["type"] == "number") {
			_return = gt_exec_rs("continue", _cmd["body"][1]["name"].getInt());
			return _return;
		} else
			throw GreenTeaException("SyntaxErrorException",
					"incorrect continue", _cmd["body"][0]);
	} else if (isset(_cmd, "body") && isset(_cmd["body"], 0)
			&& _cmd["body"][0] == token("return", "keyword")) {
		if (gt_sizeof(_cmd["body"]) == 1) {
			return gt_exec_rs("return", false);
		} else {
			Mixed _cmd_body = _cmd["body"];
			array_shift_no_return(_cmd_body);
			Mixed _return_expr;
			_return_expr.push("type", "expr");
			_return_expr.push("body", _cmd_body);
			Mixed _return_value = gt_eval(_return_expr);
			return gt_exec_rs("return", _return_value);
		}
	} else if (_cmd["type"] == "func_def") {
		return gt_exec_rs("mixed", register_function(_cmd));
	} else if (_cmd["type"] == "function") {
		{
			_return = gt_exec_rs("mixed", call_function(_cmd));
			assign_var(Mixed(token("answer_var", "var")), _return._value);
			return _return;
		}
	} else if (_cmd["type"] == "method_call") {
		{
			_return = gt_exec_rs("mixed", call_method(_cmd));
			assign_var(Mixed(token("answer_var", "var")), _return._value);
			return _return;
		}
	} else {
		gt_exec_rs _return = gt_exec_rs("mixed", gt_eval(_cmd));
		set_answer_var(_return._value);
		return _return;
	}
	return _null;
}

Mixed gt_do(const string &_opt, const Mixed &_params, long _opt_pos) {
	log("gt_do() starting");
//process _params until they are only non expr types;
//	Mixed _finalized_params;
//	for (auto const& [_k, _v] : _params.valueArray) {
//		Mixed _param = (Mixed) *_v;
//		if (get_type(_param) == "expr") {
//			_finalized_params.push(gt_eval(_param));
//		} else {
//			_finalized_params.push(_param);
//		}
//	}
	Mixed _return1;
	Mixed _return0;
	Mixed _return = Mixed();
	double _return_num;
	long _return_int;
	string return_str;
	Mixed _param0_finalized = gt_eval(_params[0]);
	if (_opt == ">>")
		if (get_type(_params[1]) == "var") {
			return _param0_finalized["properties"][get_name(_params[1])];
		}
	Mixed _param1_finalized;
	if (isset(_params, 1))
		_param1_finalized = gt_eval(_params[1]);
	if (_opt == "[]") {
		try {
			_return = _param0_finalized[(string) _param1_finalized];
		} catch (InternalException _e) {
			throw GreenTeaException("IndexOutOfBoundsException",
					"Cannot find element.", _params[1]);
		}
		return _return;
	} else if (_opt == "+") {
		_return_num = _param0_finalized.valueNum + _param1_finalized.valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "-") {
		if (_opt_pos == 0 && gt_sizeof(_params) == 1) {
			return -(double) _param0_finalized;
		}
		_return_num = _param0_finalized.valueNum - _param1_finalized.valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "*") {
		_return_num = _param0_finalized.valueNum * _param1_finalized.valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "/") {
		if ((double) _param1_finalized == 0)
			throw GreenTeaException("DivisionByZeroException",
					"Cannot devide by zero", _params[1]);
		_return_num = _param0_finalized.valueNum / _param1_finalized.valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "%") {
		_return_int = _param0_finalized.getInt() % _param1_finalized.getInt();
		_return = Mixed(_return_int);
		return _return;
	} else if (_opt == "**") {
		_return_num = pow(_param0_finalized.valueNum,
				_param1_finalized.valueNum);
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "&&") {
		return (bool) _param0_finalized && (bool) _param1_finalized;
	} else if (_opt == "||") {
		return (bool) _param0_finalized || (bool) _param1_finalized;
	} else if (_opt == "!") {
		return !_param0_finalized.valueBool;
	} else if (_opt == "==") {
		return _param0_finalized == _param1_finalized
				&& _param0_finalized.type == _param1_finalized.type;
	} else if (_opt == "=") {
		return _param0_finalized == _param1_finalized;
	} else if (_opt == "<") {
		return _param0_finalized.valueNum < _param1_finalized.valueNum;
	} else if (_opt == "<=") {
		return _param0_finalized.valueNum <= _param1_finalized.valueNum;
	} else if (_opt == ">") {
		return _param0_finalized.valueNum > _param1_finalized.valueNum;
	} else if (_opt == ">=") {
		return _param0_finalized.valueNum >= _param1_finalized.valueNum;
	} else if (_opt == "!=") {
		return _param0_finalized.valueNum != _param1_finalized.valueNum;
	} else if (_opt == "++") {
		_return0 = _params[0];
		assign_var(_params[0],
				_return1 = Mixed(_param0_finalized.valueNum + 1));
		if (_opt_pos == 0)
			return _return0;
		else
			return _return1;
	} else if (_opt == "--") {
		_return0 = _params[0];
		assign_var(_params[0],
				_return1 = Mixed(_param0_finalized.valueNum - 1));
		if (_opt_pos == 0)
			return _return0;
		else
			return _return1;
	} else if (_opt == "+:") {
		assign_var(_params[0], _return = _param0_finalized + _param1_finalized);
		return _return;
	} else if (_opt == "-:") {
		assign_var(_params[0], _return = _param0_finalized - _param1_finalized);
		return _return;
	} else if (_opt == "*:") {
		assign_var(_params[0], _return = _param0_finalized * _param1_finalized);
		return _return;
	} else if (_opt == "/:") {
		if ((double) _param1_finalized == 0)
			throw GreenTeaException("DivisionByZeroException",
					"Cannot devide by zero.", _params[1]);
		assign_var(_params[0], _return = _param0_finalized / _param1_finalized);
		return _return;
	} else if (_opt == "%:") {
		assign_var(_params[0],
				_return = (long) _param0_finalized % (long) _param1_finalized);
		return _return;
	} else if (_opt == ".") {
		_return = (string) _param0_finalized + (string) _param1_finalized;
		return _return;
	} else if (_opt == ".:") {
		assign_var(_params[0],
				_return = (string) _param0_finalized
						+ (string) _param1_finalized);
		return _return;
	} else {
		throw GreenTeaException("SyntaxErrorException", "unknown operator",
				_params[1]);
	}
}
void init_builtin_functions();
void prepare() {
	if (__args[0] == "-v") {
		echo("1.0.8\n");
		exit(0);
	}
	if (__args[0] == "-h") {
		echo("Usage: gtlang <source_file.gtc>\n");
		exit(0);
	}
	init_builtin_functions();
	init_exception_classes();
	string _operator1;
	long _len;
	for (auto const& [_k, _v1] : __operators) {
		string _v = (string) _v1;
		if (!in_array(ts(_v.at(0)), __operator_1st_chars))
			array_push(__operator_1st_chars, ts(_v.at(0)));
	}
	for (auto const& [_k, _operator] : __operators) {
		_len = strlen((string) _operator);
		if (array_search(_operator, __operators_by_chars_count[_len]) == -1)
			array_push(__operators_by_chars_count[_len], _operator);
	}
#ifdef _WIN32
// set console output to UTF-8
	SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);

	////  stdout and stdin to UTF-8 mode (text mode)
	//_setmode(_fileno(stdout), _O_U8TEXT);
	//_setmode(_fileno(stdin), _O_U8TEXT);
#endif
	gt_init_random();
}
void finalize() {
	long _threads_count = 0;
	for (auto& [_k, _v] : __threads) {
		if (_v.joinable()) {
			_threads_count = true;
		}
		if (_threads_count > 0)
			echo(
					lr("Warning: waiting for ") + ts(_threads_count)
							+ lr(" unfinished threads."));
		for (auto& [_k, _v] : __threads) {
			if (_v.joinable()) {
				_v.join();
			}
		}
	}
	for (auto [_k, _v] : __mysql_connections) {
		Mixed _tmp;
		_tmp.push(_k);
		gt_mysql_close(_tmp);
	}
	//echo("\n");
}
//=============================================================================================
void init_builtin_functions() {
	map<string, GTBuiltinFunction> _tmp;
//---------------------------------------------
	_tmp["echo"] = gt_echo;
	_tmp["print"] = gt_print;
	_tmp["get_args"] = gt_get_args;
	_tmp["use_language_file"] = use_language_file;
	_tmp["new"] = gt_new;

	_tmp["thread_start"] = gt_thread_start;
	_tmp["thread_get_args"] = gt_thread_get_args;
	_tmp["thread_return"] = gt_thread_return;
	_tmp["thread_get_result"] = gt_thread_get_result;
	_tmp["sleep"] = gt_sleep;

	_tmp["merge"] = gt_merge;
	_tmp["explode"] = gt_explode;
	_tmp["split"] = gt_explode;
	_tmp["implode"] = gt_implode;
	_tmp["join"] = gt_implode;
	_tmp["reset_keys"] = gt_reset_keys;
	_tmp["size_of"] = gt_sizeof1;
	_tmp["find"] = gt_find;

	_tmp["str_len"] = gt_length;
	_tmp["sub_str"] = gt_sub_str;
	_tmp["contains"] = gt_contains;
	_tmp["str_m_pos"] = gt_str_m_pos;
	_tmp["str_pos"] = gt_str_pos;
	_tmp["str_m_i_pos"] = gt_str_m_i_pos;
	_tmp["str_i_pos"] = gt_str_i_pos;
	_tmp["str_to_upper"] = gt_str_to_upper;
	_tmp["str_to_lower"] = gt_str_to_lower;
	_tmp["is_preg_match"] = gt_is_preg_match;
	_tmp["preg_match_all"] = gt_preg_match_all;
	_tmp["preg_replace_all"] = gt_preg_replace_all;

	_tmp["input"] = gt_input;
	_tmp["read"] = gt_input;
	_tmp["shell"] = gt_shell;

	_tmp["file_read"] = gt_file_read;
	_tmp["file_init"] = gt_file_init;
	_tmp["file_write"] = gt_file_write;
	_tmp["file_exists"] = gt_file_exists;
	_tmp["mkdir"] = gt_mkdir;
	_tmp["delete_path"] = gt_delete_path;
	_tmp["include"] = gt_include;

	_tmp["fetch_url"] = gt_fetch_url;
	_tmp["call_restapi"] = gt_call_restapi;

	_tmp["mysql_connect"] = gt_mysql_connect;
	_tmp["mysql_query"] = gt_mysql_query;
	_tmp["mysql_close"] = gt_mysql_close;

	_tmp["abs"] = gt_abs;
	_tmp["sqrt"] = gt_sqrt;
	_tmp["pow"] = gt_pow;
	_tmp["exp"] = gt_exp;
	_tmp["log"] = gt_log;
	_tmp["log10"] = gt_log10;
	_tmp["sin"] = gt_sin;
	_tmp["cos"] = gt_cos;
	_tmp["tan"] = gt_tan;
	_tmp["asin"] = gt_asin;
	_tmp["acos"] = gt_acos;
	_tmp["atan"] = gt_atan;
	_tmp["round"] = gt_round;
	_tmp["floor"] = gt_floor;
	_tmp["ceil"] = gt_ceil;
	_tmp["trunc"] = gt_trunc;
//	_tmp["init_random"] = gt_init_random;
	_tmp["rand_int"] = gt_rand_int;
	_tmp["rand_float"] = gt_rand_float;

	_tmp["echo_current_time"] = gt_echo_current_time;
	_tmp["echo_current_date"] = gt_echo_current_date;
	_tmp["time"] = gt_time;
	_tmp["diff_time"] = gt_diff_time;
	_tmp["format_time"] = gt_format_time;
	_tmp["now"] = gt_timestamp_now;
//---------------------------------------------
	for (auto [_k, _v] : _tmp) {
		__b_funcs["@" + _k] = _v;
	}
}

//==============================================================================================
//int main1() {
//	Mixed a, b;
//	a.push(1l);
//	a.push(2l);
//	a.push(a);
//	a[2] = Mixed("g");
//	return b;
//}
