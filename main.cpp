/*
 * main.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: q
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <libs.h>

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
Mixed array_merge(Mixed _arr, tokens_line _arr1) {
	for (auto [_key, _value] : _arr1) {
		_arr.push(_value);
	}
	return _arr;
}
//Mixed array_merge(Mixed _arr, Mixed _arr1) {
//	for (auto [_key, _value] : _arr1.valueArray) {
//		_arr.push(*((Mixed*) _value));
//	}
//	return _arr;
//}
bool is_az(string _inp) {
	long _i1;
	bool _is_matches;
	for (_i1 = 0; _i1 < strlen(_inp); _i1++) {
		_is_matches = php_preg_match("/[a-zA-Z]/", php_to_string(_inp.at(_i1)));
		if (_is_matches)
			return true;
	}
	return false;
}
Mixed get_1st_ele(Mixed _arr) {
	tokens_line1 _ele;
	_arr.resetKeys();
	if (!_arr.valueArray.empty())
		return _arr[0];
	return Mixed();
}
tokens_line1 get_last_ele(tokens_line1_arr _arr) {
	tokens_line1 _ele;
	if (!_arr.empty())
		return _arr.rbegin()->second;
	return tokens_line1();
}
string remove_from_string(string _str, long _start, long _stop) {
	if (_start >= _stop || _stop > strlen(_str))
		return _str;
	_str = substr(_str, 0, _start) + " " + substr(_str, _stop);
	return _str;
}
long get_first_pos_or_end_of_str(string _content, string _str,
		long _start_pos) {
	long _pos_end;
	_pos_end = strpos(_content, _str, _start_pos);
	if (_pos_end == -1)
		_pos_end = strlen(_content);
	else
		_pos_end += strlen(_str);
	return _pos_end;
}
string remove_comment_blocks(string _content) {
	long _len;
	long _i;
	long _last_pos;
	_len = strlen(_content);
	_i = 0;
	while (_i < _len - 1) {
		if (ts(_content.at(_i)) + ts(_content.at(_i + 1)) == "/*") {
			_last_pos = get_first_pos_or_end_of_str(_content, "*/", _i);
			_content = remove_from_string(_content, _i, _last_pos);
			_len = strlen(_content);
		}
		_i++;
	}
	return _content;
}
string remove_inline_comments(string _content) {
	arr_ls _arr;
//	long _k;
	string _v;
	long _pos;
	_arr = explode("\n", _content);
	for (auto [_k, _v] : _arr) {
		if ((_pos = strpos((string) _v, "//")) != -1)
			_arr[_k] = substr((string) _v, 0, _pos);
	}
	return implode("\n", _arr);
}
string remove_comments(string _content) {
	_content = remove_inline_comments(_content);
	_content = remove_comment_blocks(_content);
	return _content;
}
string rtrim_all_lines(string _content) {
	arr_ls _arr;
//	long _k;
	string _v;
	_arr = explode("\n", _content);
	for (auto [_k, _v] : _arr) {
		_arr[_k] = rtrim(_v);
	}
	return implode("\n", _arr);
}
tokens_line1_arr rtrim_all_lines_arr(tokens_line1_arr _content) {
//	long _k0;
	tokens_line1 _line;
//	long _k1;
	token _token;
	long _kx;
	for (auto [_k0, _line] : _content) {
		for (auto [_k1, _token] : ((tokens_line1) _line)._0) {
			if (_token._1 != "spaces") {
				_kx = _k1;
				break;
			}
			_content[_k0]._0 = array_slice(((tokens_line1) _line)._0, _kx,
					gt_sizeof(((tokens_line1) _line)._0));
		}
	}
	return _content;
}
string tokens_arr_to_str1(tokens_line _tokens_line1_arr) {
	string _return;
	token _token;
	_return = "";
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		_return += _token._0;
	}
	return _return;
}
tokens_line_arr explode_tokens(token _del, tokens_line _tokens_line1_arr) {
	tokens_line_arr _return;
	long _k;
	token _token;
	_return = { { 0, { } } };
	_k = 0;
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		if ((token) _token == _del) {
			_k++;
			_return[_k] = { };
		} else {
			array_push(_return[_k], _token);
		}
	}
	return _return;
}
tokens_line_arr explode_tokens(string _del, tokens_line _tokens_line1_arr) {
	tokens_line_arr _return;
	long _k;
	token _token;
	_return = { { 0, { } } };
	_k = 0;
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		if (_token._0 == _del) {
			_k++;
			_return[_k] = { };
		} else {
			array_push(_return[_k], _token);
		}
	}
	return _return;
}
arr_ll array_search_multi(token _search, tokens_line _arr) {
	arr_ll _return;
//	long _k;
	token _v;
	_return = { };
	for (auto [_k, _v] : _arr) {
		if (_search == _v)
			array_push(_return, _k);
	}
	return _return;
}

tokens_line remove_spaces_from_tokens_arr(tokens_line _tokens_line1_arr) {
	tokens_line _return;
	token _token;
	_return = { };
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		if ((_token._1 != "") && _token._1 != "spaces")
			array_push(_return, _token);
	}
	return _return;
}
Mixed remove_spaces_from_tokens_arr(Mixed _tokens_line1_arr) {
	Mixed _return;
	for (auto [_key_rtt, _token] : _tokens_line1_arr.valueArray) {
		if (!(_token[1] == "") && !(_token[1] == "spaces"))
			_return.push(_token);
	}
	return _return;
}
// ========================================================================================;
// ========================================================================================;
// ========================================================================================;
Mixed parse_expression(tokens_line tokens_arr);
bool is_blank_str(string _str) {
	for (long _i = 0; _i < strlen(_str); _i++)
		if (to_string(_str.at(_i)) != " " && to_string(_str.at(_i)) != "\t")
			return false;
	return true;
}
string remove_blank_lines(string _content) {
	arr_ls _arr;
	string _v;
	_arr = explode("\n", _content);
	for (auto [_k, _v] : _arr) {
		if (is_blank_str(_v))
			_arr.erase(_k);
	}
	return implode("\n", _arr);
}
string process_first_line(string _content) {
	arr_ls _arr;
	string _first_line;
	_arr = explode("\n", _content);
	_first_line = trim(_arr[0]);
	if (strpos(_first_line, "#") == 0)
		array_shift(_arr);
	return implode("\n", _arr);
}
void new_line(tokens_line1_arr &_arr, long &_line) {
	_line++;
	if (!isset(_arr, _line))
		_arr[_line] = { { }, 0 };
}
tokens_line1_arr tokenize(string _content) {
	//cout << _content;
	//exit(0);
	tokens_line1_arr _output_arr;
	long _len;
	long _line;
	long _block_lv;
	long _i = 0;
	long _i1 = 0;
	string _extracted_str;
	bool _matches;
	string _;
	string _answer_var;
	string _list_params;
//	long _char_count;
	tokens_line _operators;
	string _operator;
	string _output_line;
	_content = process_first_line(_content);
	//_output_arr = { };
	_content = remove_comments(_content);
	_content = remove_blank_lines(_content);
	_content = string("\n") + rtrim_all_lines(_content);
	_len = strlen(_content);
	_line = 0;
	_block_lv = 0;
	for (_i = 0; _i < _len; _i++) {
// new_line ( _output_arr, _line );
// if (! isset ( _output_arr [_line] ))
// _output_arr [_line] = [ 0 => Mixed(),1 => 0
// ];
		_i1 = 0;
		_ = php_to_string(_content.at(_i));
		if (strlen(_content) > _i + 1 && php_to_string(_content.at(_i)) == "\n"
				&& strlen(_content) > _i
				&& php_to_string(_content.at(_i + 1)) == "\n") {
			_i += 1;
			continue;
		} else if (substr(_content, _i, 3) == "...") {
			_i += 2;
		} else if (php_to_string(_content.at(_i)) == "\n"
				&& substr(_content, _i - 3, 3) == "...") {
			_i += 3;
		} else if (php_to_string(_content.at(_i)) == ":") {
			new_line(_output_arr, _line);
		} else if (php_to_string(_content.at(_i)) == "\n") {
			new_line(_output_arr, _line);
// ignore first tabs and spaces;
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (php_to_string(_content.at(_i + _i1)) != " "
						&& php_to_string(_content.at(_i + _i1)) != "\t")
					break;
			}
			_extracted_str = substr(_content, _i + 1, _i1 - 1);
			_extracted_str = str_ireplace("\t", "    ", _extracted_str);
			_block_lv = round(strlen(_extracted_str) / 4);
			_output_arr[_line]._1 = _block_lv;
			_i += _i1 - 1;
		} else if (php_to_string(_content.at(_i)) == " "
				|| php_to_string(_content.at(_i)) == "\t") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (php_to_string(_content.at(_i + _i1)) != " ")
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			array_push(_output_arr[_line]._0, { _extracted_str, "spaces" });
		} else if (php_to_string(_content.at(_i)) == " "
				|| php_to_string(_content.at(_i)) == "\t") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (php_to_string(_content.at(_i + _i1)) != " ")
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			array_push(_output_arr[_line]._0, { _extracted_str, "spaces" });
		} else if (php_to_string(_content.at(_i)) == "\\"
				&& strlen(_content) > _i) {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
// if (strlen ( _extracted_str ) == 1)
// throw  ( "wrong string format" );
			array_push(_output_arr[_line]._0, { _extracted_str, "string" });
			_i += _i1 - 1;
		} else if (php_to_string(_content.at(_i)) == "$"
				&& php_to_string(_content.at(_i + 1)) == "?") {
			array_push(_output_arr[_line]._0, { "_answer_var", "var" });
			_i += 1;
			continue;
		} else if (php_to_string(_content.at(_i)) == "$"
				&& php_to_string(_content.at(_i + 1)) == "@") {
			array_push(_output_arr[_line]._0, { "_list_params", "var" });
			_i += 1;
			continue;
		} else if (php_to_string(_content.at(_i)) == "$"
				&& php_to_string(_content.at(_i + 1)) == "$") {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw new GtlangException("wrong var format");
			array_push(_output_arr[_line]._0, { _extracted_str, "var_global" });
			_i += _i1 - 1;
		} else if (_content[_i] == '$') {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw new GtlangException("wrong var format");
			array_push(_output_arr[_line]._0, { _extracted_str, "var" });
			_i += _i1 - 1;
		} else if (_content[_i] == '@' && _content[_i + 1] == '@') {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(php_to_string(_extracted_str.at(1))))
				throw new GtlangException("wrong function format @_");
			array_push(_output_arr[_line]._0,
					{ _extracted_str, "function_self" });
			_i += _i1 - 1;
		} else if (php_to_string(_content.at(_i)) == "@"
				&& php_to_string(_content.at(_i + 1)) == "$") {
			for (_i1 = 2; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(php_to_string(_extracted_str.at(1))))
				throw new GtlangException("wrong function format @_");
			array_push(_output_arr[_line]._0,
					{ _extracted_str, "function_var" });
			_i += _i1 - 1;
		} else if (_content[_i] == '@' && _content[_i + 1] != '@') {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1
					|| is_numeric(php_to_string(_extracted_str.at(1))))
				throw new GtlangException("wrong function format");
			array_push(_output_arr[_line]._0, { _extracted_str, "function" });
			_i += _i1 - 1;
		} else if (_content[_i] == '^') {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (strlen(_extracted_str) == 1)
				throw new GtlangException("wrong class format");
			array_push(_output_arr[_line]._0, { _extracted_str, "class" });
			_i += _i1 - 1;
		} else if (is_numeric(php_to_string(_content.at(_i)))) {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[0-9.]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (substr_count(_extracted_str, ".") > 1)
				throw new GtlangException(
						"wrong number format, more than 1 point");
			array_push(_output_arr[_line]._0, { _extracted_str, "number" });
			_i += _i1 - 1;
		} else if (php_to_string(_content.at(_i)) == "\"") {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (php_to_string(_content.at(_i + _i1)) == "\""
						&& php_to_string(_content.at(_i + _i1)) != "\\")
					break;
			}
			_extracted_str = substr(_content, _i + 1, _i1 - 1);
// if (strlen ( _extracted_str ) == 1 || is_numeric ( _extracted_str ._1 ))
// throw  ( "wrong string format" );
			array_push(_output_arr[_line]._0, { _extracted_str, "string" });
			_i += _i1;
		} else if (_content[_i] == '\'') {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				if (php_to_string(_content.at(_i + _i1)) == "'"
						&& php_to_string(_content.at(_i + _i1)) != "\\")
					break;
			}
			_extracted_str = substr(_content, _i, _i1 - 1);
// if (strlen ( _extracted_str ) == 1 || is_numeric ( _extracted_str ._1 ))
// throw  ( "wrong string format" );
			array_push(_output_arr[_line]._0, { _extracted_str, "string" });
			_i += _i1;
		} else if (is_az(php_to_string(_content.at(_i)))) {
			for (_i1 = 1; _i1 < _len - _i; _i1++) {
				_matches = php_preg_match("/[a-zA-Z0-9_]/",
						php_to_string(_content.at(_i + _i1)));
				if (!_matches)
					break;
			}
			_extracted_str = substr(_content, _i, _i1);
			if (in_array(_extracted_str, __keywords))
				array_push(_output_arr[_line]._0,
						{ l(_extracted_str), "keyword" });
			else if (in_array(_extracted_str, __modifiers))
				array_push(_output_arr[_line]._0, { l(_extracted_str),
						"modifier" });
			else
				array_push(_output_arr[_line]._0, { _extracted_str, "string" });
			_i += _i1 - 1;
		} else if (in_array(php_to_string(_content.at(_i)),
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
						array_push(_output_arr[_line]._0,
								{ substr(_content, _i, _char_count), "operator" });
						_i += _char_count - 1;
						check = true;
						break;
					}
					if (check)
						break;
				}
			}
			if (!check)
				array_push(_output_arr[_line]._0,
						{ php_to_string(_content.at(_i)), "other0" });
		} else {
			array_push(_output_arr[_line]._0, { php_to_string(_content.at(_i)),
					"other" });
		}
	}
	for (auto [_i, _output_line] : _output_arr) {
		//echo("hi");
		if (((tokens_line1) _output_line)._0.empty())
			_output_arr.erase((long) _i);
	}
	_output_arr = array_values(_output_arr);
	return _output_arr;
}
//lll
tokens_line ltrim_arr(tokens_line _arr) {
//	long _k;
	token _v;
	for (auto [_k, _v] : _arr) {
		if (!is_blank_str(_v._0))
			break;
		_arr.erase(_k);
	}
	return array_values(_arr);
}
bool in_array_lv2_0(string _ele, tokens_line _arr) {
	token _ele_tmp;

	for (auto [_key_rtt, _ele_tmp] : _arr) {
		if (_ele == _ele_tmp._0)
			return true;
	}
	return false;
}
bool in_array_lv2_1(string _ele, tokens_line _arr) {
	token _ele_tmp;

	for (auto [_key_rtt, _ele_tmp] : _arr) {
		if (_ele == _ele_tmp._1)
			return true;
	}
	return false;
}
Mixed get_arr_between_brackets_mixed(string _open_bracket,
		Mixed _tokens_line1_arr, long _pos_of_open_bracket) {
//	_tokens_line1_arr.printPretty();
	Mixed _return;
	string _close_bracket;
	long _lv;
	long _k1 = 0;
	Mixed _v;
	//long _pos_of_open_bracket;
	_close_bracket = ")";
	if (_open_bracket == "[")
		_close_bracket = "]";
	_lv = 1;
	for (auto [_k_auto, _v_auto] : _tokens_line1_arr.valueArray) {
		_v = (Mixed) *_v_auto;
		if (tl((string) _k_auto) <= _pos_of_open_bracket)
			continue;
		else if (_v[0] == _open_bracket && _v[1] == "operator")
			_lv++;
		else if (_v[0] == _close_bracket && _v[1] == "operator") {
			_lv--;
			if (_lv == 0) {
				_k1 = tl((string) _k_auto);
				break;
			}
		}
	}
	_return = array_slicem(_tokens_line1_arr, _pos_of_open_bracket + 1,
			_k1 - _pos_of_open_bracket - 1);
	return _return;
}
tokens_line get_arr_between_brackets_tl(string _open_bracket,
		tokens_line _tokens_line1_arr, long _pos_of_open_bracket) {
	string _close_bracket;
	long _lv;
	long _k = 0;
	token _v;
	//long _pos_of_open_bracket;
	_close_bracket = ")";
	if (_open_bracket == "[")
		_close_bracket = "]";
	_lv = 1;
	for (auto [_k, _v] : _tokens_line1_arr) {
		if (_k <= _pos_of_open_bracket)
			continue;
		else if (_v._0 == _open_bracket && _v._1 == "operator")
			_lv++;
		else if (_v._0 == _close_bracket && _v._1 == "operator") {
			_lv--;
			if (_lv == 0)
				break;
		}
	}
	return array_slice(_tokens_line1_arr, _pos_of_open_bracket + 1,
			_k - _pos_of_open_bracket - 1);
}
arr_ll find_all_token_at_level0_by_type(string _token_type_to_compare,
		tokens_line _tokens_line1_arr) {
	long _lv1;
	long _lv2;
	arr_ll _return;
	//long _k;
	token _token;
	_lv1 = _lv2 = 0;
	_return = { };
	for (auto [_k, _token] : _tokens_line1_arr) {
//		if (!is_token(_token)) {
//			continue;
//		}
		if (_token._0 == "(" && _token._1 == "operator") {
			_lv1++;
		} else if (_token._0 == "[" && _token._1 == "operator") {
			_lv2++;
		} else if (_token._0 == ")" && _token._1 == "operator") {
			_lv1--;
		} else if (_token._0 == "]" && _token._1 == "operator") {
			_lv2--;
		} else if (_token._1 == _token_type_to_compare && _lv1 == 0
				&& _lv2 == 0) {
			array_push(_return, _k);
		}
	}
	return _return;
}
//struct name_and_params {
//public:
//	string name;
//	arr_lm params;
//	name_and_params() {
//		this->name = "";
//		this->params = { };
//	}
//};
struct two_sides {
public:
	;
	tokens_line _0;
	tokens_line _1;
	two_sides() {
		this->_0 = { };
		this->_1 = { };
	}
};
tokens_line_arr array_cut_by_pos(tokens_line _arr, arr_ll _positions) {
	tokens_line_arr _return;
	//long _i_i = 0;
	long _pos_i = 0;
	long _start;
	long _stop;
	long _len;
	if (_positions.empty()) {
		return { {0,_arr
			}};
	}
	_return = { };
	for (auto [_i, _pos] : _positions) {
		if (isset(_positions, _i - 1))
			_start = _positions[_i - 1] + 1;
		else
			_start = 0;
		if (isset(_positions, _i))
			_stop = (long) _pos;
		else
			_stop = gt_sizeof(_arr) - 1;
		_len = _stop - _start;
		if (_len < 0)
			_len = 0;
		_return[(long) _i] = array_slice(_arr, _start, _len);
		_pos_i = (long) _pos;
	}

	array_push(_return, array_slice(_arr, _pos_i + 1));
	return _return;
}
arr_ll find_all_token_at_level0(token _token_to_compare,
		tokens_line _tokens_line1_arr) {
	long _lv1;
	long _lv2;
	arr_ll _return;
//	long _k;
	//token _token;
	_lv1 = _lv2 = 0;
	_return = { };
	for (auto [_k, _token] : _tokens_line1_arr) {
//		if (!is_token(_token)) {
//			continue;
//		}
		if (_token._0 == "(" && _token._1 == "operator") {
			_lv1++;
		} else if (_token._0 == "[" && _token._1 == "operator") {
			_lv2++;
		} else if (_token._0 == ")" && _token._1 == "operator") {
			_lv1--;
		} else if (_token._0 == "]" && _token._1 == "operator") {
			_lv2--;
		} else if ((token) _token == _token_to_compare && _lv1 == 0
				&& _lv2 == 0) {
			array_push(_return, (long) _k);
		}
	}
	return _return;
}
Mixed get_function_and_params_lv0(tokens_line _tokens_line1_arr) {
	Mixed _return;
	arr_ll _all_func_names_pos;
	tokens_line_arr _two_sides;
	tokens_line_arr _tmp_array;
	arr_ll _left_comma_pos;
	arr_ll _right_comma_pos;
	tokens_line _v;
	_return = Mixed();
	_all_func_names_pos = find_all_token_at_level0_by_type("function",
			_tokens_line1_arr);
	if (gt_sizeof(_all_func_names_pos) != 1)
		return Mixed();
	Mixed m = new Mixed();
	m.type = "a";
	_return.push("name", _tokens_line1_arr[_all_func_names_pos[0]]._0);
	_return.push("params", m);
	_two_sides = array_cut_by_pos(_tokens_line1_arr, _all_func_names_pos);
	reset_keys(_two_sides[0]);
	reset_keys(_two_sides[1]);
	_tmp_array = { };
	_left_comma_pos = find_all_token_at_level0( { ",", "operator" },
			_two_sides[0]);
	_tmp_array = array_cut_by_pos(_two_sides[0], _left_comma_pos);
	_right_comma_pos = find_all_token_at_level0( { ",", "operator" },
			_two_sides[1]);
	_tmp_array = array_merge(_tmp_array,
			array_cut_by_pos(_two_sides[1], _right_comma_pos));
	for (auto [_key_rtt, _v_auto] : _tmp_array) {
		tokens_line _v = (tokens_line) _v_auto;
		_v = trim_tokens_line_once(_v);
		if (!_v.empty())
			_return["params"].push(parse_expression(_v));
	}
	return _return;
}
struct getline_subblock_t {
public:
	long i;
	tokens_line1_arr arr;
	getline_subblock_t() {
		this->i = 0;
		this->arr = { };
	}
};
getline_subblock_t getline_subblock(tokens_line1_arr _tokens_line1_arr,
		long _header_line_i) {
	long _header_lv;
	tokens_line1_arr _tmp_arr;
	long _i;
	tokens_line1 _v;
	getline_subblock_t _return = getline_subblock_t();
	_header_lv = _tokens_line1_arr[_header_line_i]._1;
	_tmp_arr = array_slice(_tokens_line1_arr, _header_line_i);
	_tmp_arr = array_values(_tmp_arr);
	_i = 0;
	for (_i = 0; _i < (long) gt_sizeof(_tmp_arr) - 1; _i++) {
		_v = _tmp_arr[_i + 1];
		if (_v._1 <= _header_lv) {
			_return.i = _i;
			_return.arr = array_slice(_tokens_line1_arr, _header_line_i + 1,
					_i);
			return _return;
		}
	}
	_return.i = _i;
	_return.arr = array_slice(_tokens_line1_arr, _header_line_i + 1);
	return _return;;
}
Mixed parse_array_element(tokens_line _tokens_line1_arr) {
	tokens_line_arr _tmp_arr;
	arr_ll _all_marks_pos;
	_tmp_arr = { };
	_all_marks_pos = find_all_token_at_level0(token("=>", "operator"),
			_tokens_line1_arr);
	_tmp_arr = array_cut_by_pos(_tokens_line1_arr, _all_marks_pos);
	Mixed _return;
	if (gt_sizeof(_tmp_arr) > 2 || gt_sizeof(_tmp_arr) < 1)
		throw new GtlangException("Invalid array declaration.");
	else if (gt_sizeof(_tmp_arr) == 1) {
		_return.push("key", "NULL");
		_return.push("value", parse_expression(_tmp_arr[0]));
		return _return;
	} else if (gt_sizeof(_tmp_arr) == 2) {
		_return.push("key", parse_expression(_tmp_arr[0]));
		_return.push("value", parse_expression(_tmp_arr[1]));
		return _return;
	}
	return _return;
}
Mixed parse_array(tokens_line _tokens_line1_arr) {
	arr_ll _all_commas;
	tokens_line_arr _elements;
	Mixed _return;
	tokens_line_arr _element;

	reset_keys(_tokens_line1_arr);
	_all_commas = find_all_token_at_level0( { ",", "operator" },
			_tokens_line1_arr);
	_elements = array_cut_by_pos(_tokens_line1_arr, _all_commas);
	for (auto [_key_rtt, _element] : _elements) {
		_return.push(parse_array_element(_element));
	}
	_return.push("type", "array");
	_return.push("body", _return);
	return _return;
}
//function is_token(_input) {
//if (isset(_input[0]) && isset(_input[1]) && gt_sizeof(_input) == 2)
//return true;
//return false;
//}
tokens_line remove_all_spaces(tokens_line _tokens_line1_arr) {
	tokens_line _return;
	token _ele;
	_return = { };
	for (auto [_key_rtt, _ele] : _tokens_line1_arr) {
		// if (! is_token ( _tokens_arr ))
		// continue;
		if (_ele._1 != "spaces")
			array_push(_return, _ele);
	}
	return _return;
}
Mixed parse_var(tokens_line _tokens_line1_arr) {
	tokens_line _tokens_arr1;
	long _lv;
	tokens_line_arr _tmp;
	token _token;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	if (_tokens_line1_arr[0]._1 != "var"
			&& _tokens_line1_arr[0]._1 != "var_global")
		throw new GtlangException("not a var");
	_tokens_arr1 = array_slice(_tokens_line1_arr, 1);
	_lv = 0;
// _tmp = Mixed();
	for (auto [_key_rtt, _token] : _tokens_arr1) {
		if (_token == token("[", "operator")) {
			_lv++;
		} else if (_token == token("]", "operator")) {
			_lv--;
		} else if (_lv == 0)
			throw new GtlangException("not valid var");
	}
	return parse_expression(_tokens_line1_arr);
}
Mixed parse_complex_var(tokens_line _tokens_line1_arr) {
	arr_ll _all_dots_pos;
	tokens_line_arr _cutted;
	tokens_line _var;
	_all_dots_pos = find_all_token_at_level0( { ".", "operator" },
			_tokens_line1_arr);
	_cutted = array_cut_by_pos(_tokens_line1_arr, _all_dots_pos);
	for (auto [_key_rtt, _var] : _cutted) {
		try {
			parse_var(_var);
		} catch (...) {
			return Mixed();
		}
	}
	return parse_expression(_tokens_line1_arr);
}
Mixed process_assignment(tokens_line _tokens_line1_arr) {
	arr_ll _pos_of_all_colon;
	Mixed _return, _return1, _return2;
	tokens_line_arr _tmp_arr;
	tokens_line _value;
	tokens_line _tmp_ele;
	long _post_of_1st_colon;
	tokens_line _left;
	tokens_line _right;
	arr_ll _left_commas_lv0;
	arr_ll _right_commas_lv0;
	Mixed _tmp;
	tokens_line_arr _left_slided;
	tokens_line_arr _right_slided;
//	long _i;
	Mixed _one_var;
	tokens_line _one_value;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	_pos_of_all_colon = find_all_token_at_level0( { ":", "operator" },
			_tokens_line1_arr);
	if (gt_sizeof(_pos_of_all_colon) == 0) {
		return Mixed(false);
	} else if (gt_sizeof(_pos_of_all_colon) > 1) {
		_tmp_arr = array_cut_by_pos(_tokens_line1_arr, _pos_of_all_colon);
		_value = array_pop(_tmp_arr);
		for (auto& [_key_rtt, _tmp_ele] : _tmp_arr) {
			array_push(_tmp_ele, token(":", "operator"));
			_tmp_ele = array_merge(_tmp_ele, _value);
			_return.push(process_assignment(_tmp_ele));
		}
		_return1.push("type", "inline_block");
		_return1.push("body", _return);
		return _return1;
	}
	_post_of_1st_colon = _pos_of_all_colon[0];
	_left = array_slice(_tokens_line1_arr, 0, _post_of_1st_colon);
	_right = array_slice(_tokens_line1_arr, _post_of_1st_colon + 1);
	_left_commas_lv0 = find_all_token_at_level0( { ",", "operator" }, _left);
	_right_commas_lv0 = find_all_token_at_level0( { ",", "operator" }, _right);
	if (gt_sizeof(_left_commas_lv0) != gt_sizeof(_right_commas_lv0))
		throw new GtlangException("not valid assignment size");
	if (_left_commas_lv0.empty()) {
		_tmp = parse_expression(_right);
		_return1.push("type", "assignment");
		_return1.push("left", parse_complex_var(_left));
		_return1.push("right", _tmp);
		_return1.push("return", _tmp);
		return _return1;
	} else {
		_left_slided = array_cut_by_pos(_left, _left_commas_lv0);
		_right_slided = array_cut_by_pos(_right, _right_commas_lv0);
		Mixed _return1;
		for (auto [_i, _one_var] : _left_slided) {
			_one_value = _right_slided[_i];
			Mixed _return;
			_return.push("type", "assignment");
			_return.push("left", parse_complex_var(_one_var));
			_return.push("right", parse_expression(_one_value));
			_return1.push(_return);
		}
		_return2.push("type", "inline_block");
		_return2.push("body", _return);
		return _return2;
	}
}
struct operator1 {
public:
	long _0;
	string _1;
	operator1() {
		this->_0 = 0;
		this->_1 = "";
	}
	operator1(long _long, string _string) {
		this->_0 = _long;
		this->_1 = _string;
	}
};
typedef map<long, operator1> arr_lo1;

Mixed tokens_to_name_and_type_format(token _input) {
	Mixed _return;
	_return.push("name", _input._0);
	_return.push("type", _input._1);
	return _return;
}
Mixed tokens_arr_to_name_and_type_format(tokens_line _input) {
	Mixed _return;
	for (auto [_k, _v] : _input) {
		_return.push((long) _k, tokens_to_name_and_type_format((token) _v));
	}
	return _return;
}
Mixed tokens_arr_to_name_and_type_format(Mixed _input) {
	Mixed _return;
	for (auto [_k, _v] : _input.valueArray) {
		_return.push((string) _k, (Mixed) *_v);
	}
	return _return;
}
string get_type(Mixed _1) {
	string _return = "";
	if (isset(_1, "type"))
		return (string) _1["type"];
	else if (isset(_1, "1")) {
		return (string) _1["1"];
	}
	return _return;
}
Mixed process_multiple_operators(tokens_line _tokens_line1_arr_input) {
	arr_lo1 _arr_operators;
//	long _k;
	Mixed _tokens_arr_tmp;
	token _token;
	long _min;
	long _highest_operator_pos;
	string _highest_operator;
	token _operator;
	Mixed _return, _tmp, _tmp1;
	Mixed _tokens_line1_arr = Mixed(_tokens_line1_arr_input);
	while (true) {
		_arr_operators = { };
		//_tokens_line1_arr.printPretty(0);
		for (auto [_k, _token] : _tokens_line1_arr.valueArray) {
			if (get_type((Mixed) *_token) == "operator") {
				array_push(_arr_operators,
						(operator1(stoi(_k), ((Mixed) *_token)[0].valueStr)));
			}
		}
		if (gt_sizeof(_arr_operators) <= 1) {
			_tmp.push("type", "expr");
			_tmp.push("body",
					tokens_arr_to_name_and_type_format(_tokens_line1_arr));
			return _tmp;
		}
		_min = 30;
		_highest_operator_pos = -1;
		_highest_operator = "";
		for (auto [_key_rtt, _operator] : _arr_operators) {
			if (isset(__real_operators, _operator._1)
					&& __real_operators.at(_operator._1).at(1) < _min) {
				_highest_operator_pos = _operator._0;
				_highest_operator = _operator._1;
				_min = __real_operators.at(_operator._1).at(1);
			}
		}
		if (_highest_operator_pos == -1)
			break;
		if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 0) {
			_return = array_slice(_tokens_line1_arr, 0, _highest_operator_pos);
			_tmp.push("type", "expr");
			_tmp1.push(0, _tokens_line1_arr[_highest_operator_pos]);
			_tmp1.push(1, _tokens_line1_arr[_highest_operator_pos + 1]);
			_tmp.push("body", _tmp1);
			_tokens_arr_tmp = array_slice(_tokens_line1_arr,
					_highest_operator_pos + 2, gt_sizeof(_tokens_line1_arr));
			_return = array_merge(_return, _tokens_arr_tmp);
		} else if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 1) {
			_return = array_slice(_tokens_line1_arr, 0,
					_highest_operator_pos - 1);
			_tmp = Mixed();
			_tmp.push("type", "expr");
			_tmp1 = Mixed();
			_tmp1.push(0, _tokens_line1_arr[_highest_operator_pos - 1]);
			_tmp1.push(1, _tokens_line1_arr[_highest_operator_pos]);
			_tmp.push("body", _tmp1);
			_return.push(_tmp);
			_tokens_arr_tmp = array_slice(_tokens_line1_arr,
					_highest_operator_pos + 1, gt_sizeof(_tokens_line1_arr));
			_return = array_merge(_return, _tokens_arr_tmp);
		} else if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 2) {
			_return = array_slice(_tokens_line1_arr, 0,
					_highest_operator_pos - 1);
			_tmp = Mixed();
			_tmp.push("type", Mixed("expr"));
			_tmp1 = Mixed();
			_tmp1.push(0, _tokens_line1_arr[_highest_operator_pos - 1]);
			_tmp1.push(1, _tokens_line1_arr[_highest_operator_pos]);
			_tmp1.push(2, _tokens_line1_arr[_highest_operator_pos + 1]);
			_tmp.push("body", _tmp1);
			_return.push(_tmp);
			_tmp = array_slice(_tokens_line1_arr, _highest_operator_pos + 2);
			_return.merge(_tmp);
		}
		_tokens_line1_arr = _return;
	}
	_tmp = Mixed();
	_tmp.push("type", "expr");
	_tmp["body"] = tokens_arr_to_name_and_type_format(_return);
	return _tmp;
}
bool is_new_clause(tokens_line _tokens_line1_arr) {
	token _token;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	if (gt_sizeof(_tokens_line1_arr) < 2)
		return false;
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		if (_token._0 == l("new") && _token._1 == "keyword")
			return true;
	}
	return false;
}
string get_body(Mixed _1) {
	string _return = "";
	if (isset(_1, "body"))
		return (string) _1["0"];
	else if (isset(_1, "0")) {
		return (string) _1["0"];
	}
	return _return;
}
string get_name(Mixed _1) {
	string _return = "";
	if (isset(_1, "name"))
		return (string) _1["name"];
	else if (isset(_1, "0")) {
		return (string) _1["0"];
	}
	return _return;
}
tokens_line tokens_arr_trim1(tokens_line &_tokens_line1_arr) {
	reset_keys(_tokens_line1_arr);
	if (isset(_tokens_line1_arr, gt_sizeof(_tokens_line1_arr) - 1)
			&& get_type(
					_tokens_line1_arr[(long) gt_sizeof(_tokens_line1_arr) - 1])
					== "spaces")
		array_pop_no_return(_tokens_line1_arr);
	if (isset(_tokens_line1_arr, 0l)
			&& get_type(_tokens_line1_arr[0]) == "spaces") {
		array_shift_no_return(_tokens_line1_arr);
		reset_keys(_tokens_line1_arr);
	}
	return _tokens_line1_arr;
}
tokens_line tokens_arr_trim(tokens_line &_tokens_line1_arr) {
//Mixed _token_array_trimmed;
//	_token_array_trimmed = _tokens_line1_arr;
	tokens_line _token_array_trimmed = tokens_arr_trim1(_tokens_line1_arr);
	while (gt_sizeof(_tokens_line1_arr) > gt_sizeof(_token_array_trimmed)) {
		_tokens_line1_arr = _token_array_trimmed;
		_token_array_trimmed = tokens_arr_trim1(_tokens_line1_arr);
	}
	return _token_array_trimmed;
}
tokens_line convert_spaces_to_concat_operators(tokens_line _tokens_line1_arr) {
	arr_ll _spaces_poses;
	tokens_line _return;
//	long _pos;
	token _token;
	string _type;
	string _name;
	long _spaces_pos;
	token _before;
	token _after;
	string _before_type;
	string _after_type;
	arr_ls _concat_types;
	Mixed _token_1;
	tokens_line _tokens_line1_arr1 = tokens_arr_trim(_tokens_line1_arr);
// _spaces_poses = find_all_token_at_level0_by_type ( "spaces", _tokens_arr );
	for (auto [_pos, _token] : _tokens_line1_arr1) {
		_token_1 = (token) _token;
		_type = get_type(_token_1);
		if (_type != "spaces") {
			array_push(_return, (token) _token);
			continue;
		}
		_name = _token._0;
		_spaces_pos = (long) _pos;
		_before = _tokens_line1_arr1.at(_spaces_pos - 1);
		_after = _tokens_line1_arr1.at(_spaces_pos + 1);
		_before_type = get_type(_before);
		_after_type = get_type(_after);
		_concat_types = { { 0, "var" }, { 1, "number" }, { 2, "string" } };
		if (in_array(_before_type, _concat_types)
				&& in_array(_after_type, _concat_types)) {
			array_push(_return, token(".", "operator"));
			array_push(_return, token(_name, "string"));
			array_push(_return, token(".", "operator"));
		}
	}
	return _return;
}
token token_to_name_and_type_format(Mixed _token) {
// if (! is_token ( _token ))
// return _token;
	return token(_token[0], _token[1]);
}

Mixed parse_expression(Mixed &_tokens_line1_arr) {
	arr_ls _value_types;
	token _tk_tmp;
	array_push(_value_types, "string");
	array_push(_value_types, "number");
	array_push(_value_types, "expr");
	array_push(_value_types, "var");
	array_push(_value_types, "array");
	array_push(_value_types, "complex_value");
	Mixed _complex_expr_arr, _previous_token_type;
	Mixed _first_token;
	bool _is_complex_expr;
//	long _k;
	Mixed _token, _tmp, _tmp1, _body_tmp;
	Mixed _result_arr;
	Mixed _parsed;
	Mixed _function_and_params;
	string _function_name;
	Mixed _function_args;
	long _operators_count;
	tokens_line _tokens_arr1;
//	long _j;
	Mixed _return, _return0, _return1;
	arr_ls _classes;
//	long _l;
	Mixed _param;
	string _type;
	string _name;
	if (isset(_tokens_line1_arr, "type")) {
		Mixed _type_m = _tokens_line1_arr["type"];
		if (_type_m == ((string) "expr"))
			_tokens_line1_arr = (Mixed) _tokens_line1_arr["data"];
		_complex_expr_arr = Mixed();
	}
//	reset(_tokens_arr);
//Mixed _xxx;
//_xxx = tokens_arr_trim1(_tokens_line1_arr);
	if (gt_sizeof(_tokens_line1_arr) == 1) {
		if (is_token(get_1st_ele(_tokens_line1_arr))) {
			if (in_array((string) get_1st_ele(_tokens_line1_arr)[1], { { 0,
					"string" }, { 1, "number" }, { 2, "var" }, { 3, "class" }, {
					4, "array" }, { 5, "expr" } })) {
				_first_token = get_1st_ele(_tokens_line1_arr);
				_return.push("type", _first_token[1]);
				_return.push("name", _first_token[0]);
				return _return;
			}
		} else {
			_return = get_1st_ele(_tokens_line1_arr);
			return _return;
		}
	}
// brackets expr
	_tokens_line1_arr.resetKeys();
	while (true) {
		for (long _k = 1; _k < gt_sizeof(_tokens_line1_arr); _k++) {
			Mixed _token = _tokens_line1_arr[_k];
			if (isset(_tokens_line1_arr[_k - 1], 1))
				_previous_token_type = _tokens_line1_arr[_k - 1][1];
			else
				_previous_token_type = _tokens_line1_arr[_k - 1]["type"];
			if (in_array((string) _previous_token_type, _value_types)
					&& get_name(_token) == "["
					&& get_type(_token) == "operator") {
				_result_arr = get_arr_between_brackets_mixed("[",
						_tokens_line1_arr, _k);
				_tmp = array_slicem(_tokens_line1_arr, 0, _k);
				_tk_tmp = token("get_ele", "operator");
				_tmp1 = Mixed(_tk_tmp);
				_tmp.push(_tmp1);
				Mixed _parsed_expression = parse_expression(_result_arr);
				_tmp.push((Mixed) _parsed_expression);
				_tmp = array_merge(_tmp,
						array_slicem(_tokens_line1_arr,
								_k + sizeof(_result_arr) + 2));
				_tokens_line1_arr = _tmp;
				continue;
			}
		}
		break;
	}
	_is_complex_expr = false;
	_tokens_line1_arr.resetKeys();
	for (long _k = 0l; _k < gt_sizeof(_tokens_line1_arr); _k++) {
		_token = _tokens_line1_arr[_k];
		if (_token.contains("type")) {
			_complex_expr_arr.push((Mixed) _token);
			continue;
		}
		if (_token[0] == "(" && _token[1] == "operator") {
			_is_complex_expr = true;
			_result_arr = get_arr_between_brackets_mixed("(", _tokens_line1_arr,
					_k);
			_complex_expr_arr.push(parse_expression(_result_arr));
			_k += gt_sizeof(_result_arr) + 2;
		} else if (_token[0] == "[" && _token[1] == "operator") {
			_is_complex_expr = true;
			_result_arr = get_arr_between_brackets_mixed("[", _tokens_line1_arr,
					_k);
			//Mixed j = _result_arr.to_tokens_line();
			_complex_expr_arr.push(parse_array(_result_arr.to_tokens_line()));
			_k += gt_sizeof(_result_arr) + 2;
		} else if (_token[0] == ")" && _token[1] == "operator") {
			throw new GtlangException("not valid close round bracket");
		} else if (_token[0] == "]" && _token[1] == "operator") {
			throw new GtlangException("not valid close square bracket");
		} else {
			_complex_expr_arr.push(_token);
		}
	}
	mixed_to_tokens_line_with_place_holders_rs complex_tokens_line_rs =
			mixed_to_tokens_line_with_place_holders(_complex_expr_arr);
	tokens_line complex_tokens_line = complex_tokens_line_rs._0;
	map<string, Mixed> _map_placeholders = complex_tokens_line_rs._1;
	if (_is_complex_expr) {
		_parsed = parse_expression(_complex_expr_arr);
		if (in_array(_parsed["type"], { { 0, "array" }, { 1, "expr" }, { 2,
				"assignment" }, { 3, "function" } }))
			return replace_placeholders_recruisively(_parsed, _map_placeholders);
		else {
			_return0.push("type", "expr");
			_return0.push("body", _return1);
			return replace_placeholders_recruisively(_return0,
					_map_placeholders);
		}
	}
// assignment expr
	for (auto [_k, _token] : _tokens_line1_arr.valueArray) {
		if (_token[0] == ":" && _token[1] == "operator") {
			_return0 = process_assignment(complex_tokens_line);
			return replace_placeholders_recruisively(_return0,
					_map_placeholders);
		}
	}
// simple function
	_function_and_params = get_function_and_params_lv0(
			to_tokens_line(_complex_expr_arr));
	if (!_function_and_params.valueArray.empty()
			&& isset(_function_and_params, "name")) {
		_function_name = (string) _function_and_params["name"];
		_function_args = _function_and_params["params"];
		_return0.push("type", "function");
		_return0.push("name", _function_name);
		_return0.push("args", _function_args);
		return replace_placeholders_recruisively(_return0, _map_placeholders);
	}
// multiple operator but no brackets expr
	complex_tokens_line = convert_spaces_to_concat_operators(
			complex_tokens_line);
	_operators_count = 0;
	for (auto [_key_rtt, _token] : complex_tokens_line) {
		if (_token._1 == "operator")
			_operators_count++;
	}
	if (_operators_count > 1) {
		_return0 = process_multiple_operators(complex_tokens_line);
		return replace_placeholders_recruisively(_return0, _map_placeholders);
	}
// new object of class
	if (is_new_clause(complex_tokens_line)) {
		_tokens_arr1 = complex_tokens_line;
		for (auto [_j, _token] : complex_tokens_line) {
			if (_token._0 == l("new") && _token._1 == "keyword")
				_tokens_arr1[(long) _j] = token("@new", "function");
		}
		_return = get_function_and_params_lv0(_tokens_arr1);
		_classes = { };
		for (auto [_l, _param] : _return["params"].valueArray) {
			if (isset(*_param, "type"))
				_type = (string) (Mixed) (*_param)["type"];
			else
				_type = (string) (Mixed) (*_param)[1];
			if (_type == "class") {
				if (isset(*_param, "name"))
					_type = (string) (Mixed) (*_param)["name"];
				else
					_type = (string) (Mixed) (*_param)[0];
				array_push(_classes, _name);
				_return["params"].delete_e(_l);
			}
		}
		if (gt_sizeof(_classes) != 1)
			throw new GtlangException("new but no/multi class");
		reset(_return["params"]);
		_return.push("type", "new");
		_return.push("class", _classes[0]);
		_return.push("params", _return["params"]);
		return _return;
	}
// simple single operator expr
	_return.push("type", "expr");
	_body_tmp = tokens_arr_to_name_and_type_format(complex_tokens_line);
	_return.push("body",
			replace_placeholders_recruisively(_body_tmp, _map_placeholders));
	return _return;
}
Mixed parse_expression(tokens_line _tokens_line1_arr) {
	Mixed _mixed1 = Mixed(_tokens_line1_arr);
	return parse_expression(_mixed1);
}
Mixed structurelize(tokens_line1_arr _arr);
Mixed process_if(long &_line_num, tokens_line1_arr _tokens_line1_arr) {
	tokens_line _if_line;
	getline_subblock_t _getline_subblock;
	map<long, tokens_line1_arr> _if_blocks;
	map<long, Mixed> _if_conditions;
	tokens_line1_arr _else_block;
	Mixed _return, _tmp;

	_if_line = _tokens_line1_arr[_line_num]._0;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	array_push(_if_blocks, _getline_subblock.arr);
	array_push(_if_conditions, parse_expression(array_slice(_if_line, 1)));
	while (true) {
		if (isset(_tokens_line1_arr[_line_num + 1], 0)
				&& _tokens_line1_arr[_line_num + 1]._0[0]._0 == l("else if")
				&& _tokens_line1_arr[_line_num + 1]._0[0]._1 == "keyword") {
			_line_num++;

			_if_line = _tokens_line1_arr[_line_num]._0;
			_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
			_line_num += _getline_subblock.i;
			array_push(_if_blocks, _getline_subblock.arr);
			array_push(_if_conditions,
					parse_expression(array_slice(_if_line, 1)));
		} else {
			break;
		}
	}
	if (_tokens_line1_arr[_line_num + 1]._0[0]._0 == l("else")
			&& _tokens_line1_arr[_line_num + 1]._0[0]._1 == "keyword"
			&& gt_sizeof(_tokens_line1_arr[_line_num + 1]._0) == 1) {
		_line_num++;
		_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
		_line_num += _getline_subblock.i;
		_else_block = _getline_subblock.arr;
	} else {
		_else_block = { };
		_return.push("type", "ifs");
		_return.push("ifs", Mixed());
		for (long k = 0; k < gt_sizeof(_if_blocks); k++) {
			_tmp = Mixed();
			_tmp.push("condition", _if_conditions[k]);
			_tmp.push("body", structurelize(_if_blocks[k]));
			_return["ifs"].push(to_string(k), _tmp);
		}
		_return.push("else", structurelize(_else_block));
		return _return;
	}
	return _return;
}
Mixed for_parse(tokens_line _for_tokens) {
//	long __time;
	Mixed _return;
//	echo("");
	if (_for_tokens[2]._1 == "number" && isset(_for_tokens, 4)
			&& _for_tokens[4]._1 == "var"
			&& array_search(token(",", "operator"), _for_tokens) == false) {
		_return.push(tokenize(_for_tokens[4]._0 + ":1")[0]._0);
		_return.push(
				tokenize(_for_tokens[4]._0 + "<=" + _for_tokens[2]._0)[0]._0);
		_return.push(tokenize(_for_tokens[4]._0 + "++")[0]._0);
		return _return;
	} else if (isset(_for_tokens, 4) && _for_tokens[2]._1 == "number"
			&& _for_tokens[4]._0 == l("times")
			&& _for_tokens[4]._1 == "keyword")
		_return.push(tokenize("__time:1")[0]._0);
	_return.push(tokenize("__time<=" + _for_tokens[2]._0)[0]._0);
	_return.push(tokenize("__time++")[0]._0);
	return _return;
	array_shift(_for_tokens);
	_return = explode_tokens(token(",", "operator"), _for_tokens);
	if (gt_sizeof(_return) != 3)
		throw new GtlangException("invalid for line");
	return _return;
}
Mixed foreach_parse(tokens_line _foreach_tokens) {
	Mixed _return, _return1, _return2;
	string __k;
	string __v;
	array_shift(_foreach_tokens);
	_return = explode_tokens(",", _foreach_tokens);
	if (gt_sizeof(_return) == 3)
		return _return;
	if (gt_sizeof(_return) == 2) {
		_return1.push("0", "__k");
		_return1.push("1", "var");
		_return.push(2, _return[1]);
		_return[1] = _return1;
		return _return;
	}
	if (gt_sizeof(_return) == 1) {
		_return1.push("0", "__k");
		_return1.push("1", "var");
		_return.push("1", _return1);
		_return2.push("0", "__v");
		_return2.push("1", "var");
		_return.push("2", _return2);
		return _return;
	}
	return _return;
}
Mixed process_for(long &_line_num, tokens_line1_arr _tokens_line1_arr) {
	tokens_line _for_line;
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _for_block;
	Mixed _for_parse;
	Mixed _return;
	_for_line = _tokens_line1_arr[_line_num]._0;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_for_block = _getline_subblock.arr;
	_for_parse = for_parse(_for_line);
	_return.push("type", "for");
	_return.push("init", parse_expression(_for_parse[0]));
	if (isset(_for_parse, 2))
		_return.push("increment", parse_expression(_for_parse[2]));
	else
		_return.push("increment", Mixed());
	_return.push("terminate", parse_expression(_for_parse[1]));
	_return.push("body", structurelize(_for_block));
	return _return;
}
Mixed process_while(long _line_num, tokens_line1_arr _tokens_line1_arr) {
	tokens_line _while_line;
	Mixed _return;
//	long _while_lv;
	tokens_line1_arr _while_block;
	getline_subblock_t _getline_subblock;
	Mixed _for_parse;
	_while_line = _tokens_line1_arr[_line_num]._0;
// _while_lv = _tokens_arr [_line_num] ._1;
	_while_block = { };
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_while_block = _getline_subblock.arr;
// _for_parse = for_parse ( array_slice ( _while_line, 0, gt_sizeof ( _while_line ) ) );
	_return.push("type" "while");
	_return.push("condition", parse_expression(array_slice(_while_line, 1)));
	_return.push("body", structurelize(_while_block));
	return _return;
}
Mixed is_function_def(tokens_line _tokens) {
	bool _check;
	token _token;
	Mixed _function_name;
	Mixed _function_vars;
	long _function_vars_i;
	long _i;
	Mixed _vars1, _return, _return1;
	tokens_line _arr_between_brackets;
//	long _k;
	tokens_line _vars;
	Mixed _value_tokens;
	Mixed _value_expr;
	if (_tokens[gt_sizeof(_tokens) - 1]._0 != ":"
			|| _tokens[gt_sizeof(_tokens) - 1]._1 != "operator")
		return false;
	_check = false;
// /================
	for (auto [_key_rtt, _token] : _tokens) {
		if (_token._1 == "function") {
			_check = true;
			break;
		}
	}
	if (_check == false)
		return false;
// =================
	array_pop(_tokens);
	_function_name = "";
	_function_vars = Mixed();
	_function_vars_i = 0;
	for (_i = 0; _i < count(_tokens); _i++) {
		_token = _tokens[(long) _i];
		if (_token._1 == "function")
			if (_function_name == "") {
				_function_name = _token._0;
				if ((int) _function_vars_i > 0)
					_function_vars_i++;
			} else
				throw new GtlangException("function declare has multiple name");
// else if (_token ._1 != "var" && _token ._1 != "spaces" && _token ._0 != ",")
// throw  ( "non-var not allowed function declare" );
		else if (_token._1 == "var") {
			_function_vars[_function_vars_i].push(_token);
		} else if (_token._0 == "[" && _token._1 == "operator") {
			_arr_between_brackets = get_arr_between_brackets_tl("[", _tokens,
					_i);
			_function_vars[_function_vars_i].push(
					parse_expression(_arr_between_brackets));
			_i += gt_sizeof(_arr_between_brackets);
		} else if (_token._0 == "(" && _token._1 == "operator") {
			_arr_between_brackets = get_arr_between_brackets_tl("(", _tokens,
					_i);
			_function_vars[_function_vars_i].push(
					parse_expression(_arr_between_brackets));
			_i += gt_sizeof(_arr_between_brackets);
		} else if (_token._0 == "," && _token._1 == "operator") {
			_function_vars_i++;
			_function_vars[_function_vars_i] = Mixed();
		} else {
// _function_vars_i ++;
			_function_vars[_function_vars_i].push(_token);
		}
	}
	if (_function_vars.valueArray.empty())
		_function_vars = Mixed();
// validate function_vars
	for (auto& [_k, _vars] : _function_vars.valueArray) {
		_vars1 = Mixed();
		_function_vars[_k] = remove_spaces_from_tokens_arr(_vars);
		_vars1 = _function_vars[_k];
		if (gt_sizeof(_vars1) == 2)
			throw new GtlangException("function declare invalid arg");
		if ((string) _vars1[0][1] != "var")
			throw new GtlangException("function declare no var");
		if (gt_sizeof(_vars1) >= 3
				&& ((string) _vars1[1][0] != ":"
						|| (string) _vars1[1][1] != "operator"))
			throw new GtlangException("function var declare no :");
		_value_tokens = array_slicem(_vars1, 2);
		_value_expr = parse_expression(_value_tokens);
		_return1.push(0, _vars1[0][0]);
		_function_vars.push(_k, _return1);
		if (gt_sizeof(_vars1) >= 3)
			_function_vars[_k].push(1, _value_expr);
	}
	_return.push(_function_name);
	_return.push(_function_vars);
	return _return;
}
tokens_line is_list(tokens_line _tokens, arr_ls _types, token _delimiter =
		token(",", "operator")) {
	tokens_line _return;
	bool _is_delimiter;
	token _token;
	Mixed _return1;
	_is_delimiter = true;
	for (auto [_key_rtt, _token] : _tokens) {
		_is_delimiter = !_is_delimiter;
		if (_is_delimiter) {
			if (!(_token == _delimiter)) {
				return tokens_line();
			}
		} else {
			if (!in_array(_token._1, _types))
				return tokens_line();
			array_push(_return, _token);
		}
	}
	return _return;
}
tokens_line is_list(tokens_line _tokens, string _type,
		token _delimiter = token(",", "operator")) {
	return is_list(_tokens, { { 0, _type } }, _delimiter);
}
arr_ls get_each_element_from_array(tokens_line _arr, long _num = 1) {
	arr_ls _return;
//	long _k;
	token _token;
	_return = { };
	for (auto [_k, _token] : _arr) {
		if (_num == 0) {
			_return[_k] = ((token) _token)._0;
		} else if (_num == 1) {
			_return[_k] = ((token) _token)._1;
		}
	}
	return _return;
}
Mixed is_class_def(tokens_line _tokens) {
	Mixed _return;
	long _last_token_i;
	tokens_line _list;
	_return.push("class", "");
	_return.push("extends", Mixed());
	_tokens = remove_all_spaces(_tokens);
	_last_token_i = gt_sizeof(_tokens) - 1;
	if (!isset(_tokens, 0) || _tokens[0]._1 != "class")
		return Mixed();
	if (_tokens[_last_token_i]._0 != ":"
			|| _tokens[_last_token_i]._1 != "operator")
		return Mixed();
// /================
	if (gt_sizeof(_tokens) == 2) {
		_return["class"] = _tokens[0]._0;
		return _return;
	} else if (gt_sizeof(_tokens) < 2 || gt_sizeof(_tokens) == 3) {
		return false;
	} else if (_tokens[1]._0 != "<<" || _tokens[1]._1 != "operator") {
		return false;
	} else if (!(_list = is_list(array_slice(_tokens, 2, _last_token_i - 2),
			"class")).empty()) {
		return false;
	} else {
		_return["class"] = _tokens[0]._0;
		_return["extends"] = get_each_element_from_array(_list, 0);
		return _return;
	}
	return false;
}
Mixed process_function_def(long _line_num, tokens_line1_arr _tokens_line1_arr,
		Mixed _func_declare, bool _is_method = false) {
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _func_def_block;
	Mixed _return, _tmp;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_func_def_block = _getline_subblock.arr;
	if (!_is_method) {
		_tmp.push("type", "func_def");
		_tmp.push("name", _func_declare[0]);
		_tmp.push("vars", _func_declare[1]);
		_tmp.push("body", structurelize(_func_def_block));
		__funcs.push(_tmp);
		return Mixed();
	} else {
		_return.push("type", "func_def");
		_return.push("name", _func_declare[0]);
		_return.push("vars", _func_declare[1]);
		_return.push("body", structurelize(_func_def_block));
		return _return;
	}
}
Mixed parse_property(tokens_line _tokens_line1_arr) {
	arr_ls _modifiers;
	long _start_vars_section;
	Mixed _return;
//	long _i;
	token _token;
	tokens_line _vars_section;
	arr_ll _all_colons;
	tokens_line_arr _two_sides;
	Mixed _tmp;
	tokens_line _list_vars;
	Mixed _var;
	arr_ll _commas_pos;
	Mixed _values_arr;
	tokens_line _values_tokens;
	string _vars;
	try {
		_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
		_modifiers = { };
		_start_vars_section = -1;
		_return = Mixed();
		for (auto [_i, _token] : _tokens_line1_arr) {
			if (_token._1 == "modifier") {
				array_push(_modifiers, _token._0);
			} else {
				_start_vars_section = _i;
				break;
			}
		}
		if (_modifiers.empty())
			_modifiers = { { 0, "public" } };
		if (_start_vars_section == -1)
			throw new GtlangException("non-var in property");
		_vars_section = array_slice(_tokens_line1_arr, _start_vars_section);
		_all_colons = find_all_token_at_level0(token(":", "operator"),
				_vars_section);
		if (gt_sizeof(_all_colons) > 1) {
			throw new GtlangException("too many colons in property");
		} else if (gt_sizeof(_all_colons) == 1) {
			_two_sides = array_cut_by_pos(_vars_section, _all_colons);
			if (gt_sizeof(
					find_all_token_at_level0(token(",", "operator"),
							_two_sides[0]))
					!= gt_sizeof(
							find_all_token_at_level0(token(",", "operator"),
									_two_sides[1])))
				throw new GtlangException(
						"colons count not balance in property");
			if (!(_list_vars = is_list(_two_sides[0], "var")).empty()) {
				for (auto [_key_rtt, _var] : _list_vars) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", _var._0);
					_tmp.push("modifiers", _modifiers);
					_return.push(_tmp);
				}
			} else {
				throw new GtlangException("not valid property declare");
			}
			// ======================
			_commas_pos = find_all_token_at_level0(token(",", "operator"),
					_two_sides[1]);
			_values_arr = array_cut_by_pos(_two_sides[1], _commas_pos);
			for (auto [_i, _values_tokens] : _values_arr.valueArray) {
				_return[stol(_i)]["value"] = parse_expression(*_values_tokens);
			}
			// ======================
			return _return;
		} else {
			if (!(_list_vars = is_list(_vars_section, "var")).empty()) {
				for (auto [_key_rtt, _var] : _list_vars) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", _var._0);
					_tmp.push("modifiers", _modifiers);
					_return.push(_tmp);
				}
			} else
				throw new GtlangException("not valid property");
			// for( auto  [_key_rtt, _var ]: _list_vars) {
			// // if (gt_sizeof ( _vars ) != 1)
			// // throw  ( "not valid property declare1" );
			// _return [] = [ "type" => "property","name" => _var ._0,"modifiers" => _modifiers
			// ];
			// }
			return _return;
		}
	} catch (...) {
		return false;
	}
}
Mixed is_method_def(tokens_line _tokens_line1_arr) {
	arr_ls _modifiers;
	long _start_func_section;
	Mixed _return;
	token _token;
	tokens_line _func_section;
	_start_func_section = -1;
	for (auto [_i, _token] : _tokens_line1_arr) {
		if (_token._1 == "modifier") {
			array_push(_modifiers, _token._0);
		} else {
			_start_func_section = _i;
			break;
		}
	}
	if (_start_func_section == -1)
		throw new GtlangException("non-function in method");
	_func_section = array_slice(_tokens_line1_arr, _start_func_section);
	_return = is_function_def(_func_section);
	if (!_return)
		return false;
	if (!_modifiers.empty())
		_return[2] = _modifiers;
	else
		_return[2] = { { 0, "public" } };
	return _return;
}
Mixed parse_class(tokens_line1_arr _class_def_block) {
	Mixed _return;
	long _i;
	tokens_line1 _line;
	Mixed _result;
	Mixed _property;
	Mixed _result1;
	_class_def_block = array_values(_class_def_block);
	for (_i = 0; _i < gt_sizeof(_class_def_block); _i++) {
		_line = _class_def_block[_i];
		_result = parse_property(_line._0);
		if (!(_result.valueArray.empty())) {
			for (auto [_key_rtt, _property] : _result.valueArray) {
				_return.push(_property);
			}
		} else if (_result = is_method_def(_line._0)) { // @suppress("Assignment in condition")
			_result1 = process_function_def(_i, _class_def_block, _result,
					true);
			_result1["type"] = "method";
			_result1["modifiers"] = _result[2];
			_return.push(_result1);
		} else {
			throw new GtlangException("wrong class internal");
		}
	}
	_return.push("type", "block");
	_return.push("body", _return);
	return _return;
}
Mixed process_class_def(long _line_num, tokens_line1_arr _tokens_line1_arr,
		Mixed _class_name) {
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _class_def_block;
	Mixed _tmp;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_class_def_block = _getline_subblock.arr;
	_tmp.push("type", "class_def");
	_tmp.push("name", _class_name["class"]);
	_tmp.push("extends", _class_name["extends"]);
	_tmp.push("body", parse_class(_class_def_block));
	__classes.push(_tmp);
	return Mixed();
}
Mixed is_catch_line(long _line, tokens_line1_arr _tokens_line1_arr) {
	Mixed _return;
	tokens_line _line_tokens;
	string __e;
	_line_tokens = remove_spaces_from_tokens_arr(_tokens_line1_arr[_line]._0);
	if (_line_tokens[0]._0 == l("catch") && _line_tokens[0]._1 == "keyword") {
		if (gt_sizeof(_line_tokens) == 1) {
			_return.push("catch");
			_return.push("^Exception");
			_return.push("__e");
			return _return;
		} else if (gt_sizeof(_line_tokens) == 2
				&& _line_tokens[1]._1 == "class") {
			_return.push("catch");
			_return.push(_line_tokens[1]._0);
			_return.push("__e");
			return _return;
		} else if (gt_sizeof(_line_tokens) == 3 && _line_tokens[1]._1 == "class"
				&& _line_tokens[2]._1 == "var") {
			_return.push("catch");
			_return.push(_line_tokens[1]._0);
			_return.push(_line_tokens[2]._0);
			return _return;
		} else
			throw new GtlangException("invalid catch");
	}
	return Mixed();
}
bool is_finally_line(long _line, tokens_line1_arr _tokens_line1_arr) {
	tokens_line _line_tokens;
	_line_tokens = remove_spaces_from_tokens_arr(_tokens_line1_arr[_line]._0);
	if (_line_tokens[0]._0 == l("finally") && _line_tokens[0]._1 == "keyword") {
		if (gt_sizeof(_line_tokens) == 1)
			return true;
		else
			throw new GtlangException("invalid finally");
	}
	return false;
}
Mixed process_try(long _line, tokens_line1_arr _tokens_line1_arr) {
	Mixed _return;
	long _tabs_lv;
	Mixed _blocks_type, _tmp, _tmp1;
	long _block_num;
	map<long, tokens_line1_arr> _blocks;
	long _i;
	Mixed _catch_line_parsed;
	tokens_line _catch_line;
	Mixed _catches;
	Mixed _try;
	long _try_count;
	Mixed _finally;
	long _finally_count;
	_tabs_lv = _tokens_line1_arr[_line]._1;
	_tmp.push("try");
	_blocks_type.push(_tmp);
	_block_num = 0;
	_tmp = Mixed();
	for (_i = _line + 1; _i < (long) gt_sizeof(_tokens_line1_arr); _i++) {
		if (_tokens_line1_arr[_i]._1 < _tabs_lv)
			break;
		if (_tokens_line1_arr[_i]._1 == _tabs_lv && !(_catch_line_parsed =
				is_catch_line(_i, _tokens_line1_arr)).empty()) {
// _catch_line = remove_all_spaces ( _tokens_arr [_i] ._0 );
			_block_num++;
			_blocks_type.push(_catch_line_parsed);
		} else if (_tokens_line1_arr[_i]._1 == _tabs_lv
				&& is_finally_line(_i, _tokens_line1_arr)) {
			_block_num++;
			_blocks[_block_num] = { };
			_tmp = Mixed();
			_tmp.push("finally");
			_blocks_type.push(_tmp);
		} else if (_tokens_line1_arr[_i]._1 == _tabs_lv) {
			break;
		} else if (_tokens_line1_arr[_i]._1 > _tabs_lv) {
			if (!isset(_blocks, _block_num))
				_blocks[_block_num] = { };
			array_push(_blocks[_block_num], _tokens_line1_arr[_i]);
		}
	}
	_line = _i - 1;
	_catches = Mixed();
	_try = Mixed();
	_try_count = 0;
	_finally = Mixed();
	_finally_count = 0;
	for (_i = 0; _i < (long) gt_sizeof(_blocks_type); _i++) {
		if (_blocks_type[_i][0] == "catch") {
			_tmp.push("exception_class", _blocks_type[_i][1]);
			_tmp.push("catch_var", _blocks_type[_i][2]);
			_tmp.push("body", structurelize(_blocks[_i]));
			_catches.push(_tmp);
		} else if (_blocks_type[_i][0] == "try") {
			_try_count++;
			if (_try_count > 1)
				throw new GtlangException("multiple try blocks");
			_try = structurelize(_blocks[_i]);
		} else if (_blocks_type[_i][0] == "finally") {
			_finally_count++;
			if (_finally_count > 1)
				throw new GtlangException("multiple try blocks");
			_finally = structurelize(_blocks[_i]);
		}
	}
	if (gt_sizeof(_catches) < 1)
		throw new GtlangException("try but no catch");
	_return.push("type", "try");
	_return.push("body", _try);
	_return.push("catch", _catches);
	_return.push("finally", _finally);
	return _return;
}
Mixed process_defcat(long _line, tokens_line1_arr _tokens_line1_arr) {
	long _tabs_lv;
	tokens_line1_arr _defcat;
	tokens_line1_arr _deffin;
	bool _is_in_deffin;
	long _i;
	map<long, tokens_line1_arr> _defcat_blocks;
	map<long, Mixed> _defcat_blocks1;
	long _defcat_blocks_i;
	arr_ls _defcat_exception_classes;
	Mixed _defcat_rs, _return, _tmp;
	Mixed _defcat_block;
	string __e;
	_tabs_lv = _tokens_line1_arr[_line]._1;
	_is_in_deffin = false;
	for (_i = _line + 1; _i < (long) gt_sizeof(_tokens_line1_arr); _i++) {
		if (_tokens_line1_arr[_i]._1 < _tabs_lv) {
			break;
		} else if (_tokens_line1_arr[_i]._1 == _tabs_lv
				&& _tokens_line1_arr[_i]._0[0]._0 == "deffin") {
			_is_in_deffin = true;
		} else if (_tokens_line1_arr[_i]._1 == _tabs_lv
				&& _tokens_line1_arr[_i]._0[0]._0 != "deffin") {
			break;
		} else if (_tokens_line1_arr[_i]._1 > _tabs_lv) {
			if (_is_in_deffin)
				array_push(_deffin, _tokens_line1_arr[_i]);
			else
				array_push(_defcat, _tokens_line1_arr[_i]);
		}
	}
	if (_defcat.empty())
		return false;
	_line = _i;
	_defcat_blocks = { };
	_defcat_blocks_i = -1;
	_defcat_exception_classes = { };
	_defcat = rtrim_all_lines_arr(_defcat);
	for (_i = 0; _i < (long) gt_sizeof(_defcat); _i++) {
		if (_defcat[_i]._1 == (_tabs_lv + 1))
			if (gt_sizeof(_defcat[0]._0) == 1
					&& _defcat[0]._0[0]._1 == "class") {
				array_push(_defcat_exception_classes, _defcat[_i]._0[0]._0);
				_defcat_blocks_i++;
			} else
				throw new GtlangException("Invalid defcat exception class");
		else if (_defcat[_i]._1 > (_tabs_lv + 1)) {
			if (!isset(_defcat_blocks, _defcat_blocks_i))
				_defcat_blocks[_defcat_blocks_i] = { };
			array_push(_defcat_blocks[_defcat_blocks_i], _defcat[_i]);
		}
	}
	if (gt_sizeof(array_unique(_defcat_exception_classes))
			!= gt_sizeof(_defcat_exception_classes))
		throw new GtlangException("Non unique catch in defcat");
	_defcat_rs = Mixed();
	for (auto [_i, _defcat_block] : _defcat_blocks) {
		_defcat_blocks1[_i] = structurelize(_defcat_block);
		_tmp.push("exception_class", _defcat_exception_classes[_i]);
		_tmp.push("catch_var", "__e");
		_tmp.push("body", _defcat_blocks1[_i]);
		_defcat_rs.push(_tmp);
	}
	_return.push("type", "defcat");
	_return.push("body", _defcat_rs);
	_return.push("deffin", structurelize(_deffin));
	return _return;
}
Mixed structurelize(tokens_line1_arr _tokens_line1_arr) {
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
	for (_line = 0; _line < (long) gt_sizeof(_tokens_line1_arr); _line++) {
		_tokens_n_lv = _tokens_line1_arr[_line];
		_tokens = ltrim_arr(_tokens_n_lv._0);
// _block_lv = _tokens_n_lv ._1;
		if (_tokens[0]._0 == l("if") && _tokens[0]._1 == "keyword") {
			_line_rs = process_if(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("for") && _tokens[0]._1 == "keyword") {
			_line_rs = process_for(_line, _tokens_line1_arr);
		} else if (_tokens[0]._0 == l("while") && _tokens[0]._1 == "keyword") {
			_line_rs = process_while(_line, _tokens_line1_arr);
		} else if ((bool) (_func_declare = is_function_def(_tokens))) {
			_line_rs = process_function_def(_line, _tokens_line1_arr,
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
		_return_tmp.push(_line_rs);
	}
	if (!_defcat_rs.empty()) {
		_tmp1.push("type", "block");
		_tmp1.push("body", _return_tmp);
		_tmp.push("type", "try");
		_tmp.push("body", _tmp1);
		_tmp.push("catch", _defcat_rs["body"]);
		_tmp.push("finally", _defcat_rs["deffin"]);
		_tmp2.push(_tmp);
		_return.push("type", "block");
		_return.push("body", _tmp2);
		return _return;
	}
	_return.push("type", "block");
	_return.push("body", _return_tmp);
	return _return;
}
string process_string(string _str) {
	arr_ls _arr;
	arr_ls _return;
	long _k;
	string _v;
	_arr = str_split(_str);
	_return = { };
	for (_k = 0; _k < (long) gt_sizeof(_arr); _k++) {
		_v = _arr[_k];
		if (_v == "\\" && isset(_arr, _k + 1)) {
			array_push(_return, _arr[_k + 1]);
			_k++;
		} else {
			array_push(_return, _v);
		}
	}
	return implode((string) "", _return);
}
tokens_line1_arr merge_strings(tokens_line1_arr _tokens_line1_arr) {
	tokens_line1_arr _return;
//	long _k;
	tokens_line1 _tokens_line, _tmp;
	string _current_str;
//	long _k1;
	token _token;
	_return = { };
	for (auto [_k, _tokens_line] : _tokens_line1_arr) {
		_tmp._0 = { };
		_tmp._1 = _tokens_line1_arr[_k]._1;
		_return[_k] = _tmp;
		_current_str = "";
		for (auto [_k1, _token] : _tokens_line._0) {
			if (_token._1 == "string") {
				_current_str += _token._0;
				continue;
			} else if (_token._1 == "spaces") {
				if (!_current_str.empty()) {
					_current_str += _token._0;
					continue;
				} else {
					array_push(_return[_k]._0, _token);
				}
			} else {
				if (!_current_str.empty()) {
					array_push(_return[_k]._0,
							token(trim(_current_str), "string"));
					if (_tokens_line._0[_k1 - 1]._1 == "spaces")
						array_push(_return[_k]._0, _tokens_line._0[_k1 - 1]);
				}
				_current_str = "";
				array_push(_return[_k]._0, _token);
			}
		}
		if (!_current_str.empty()) {
			array_push(_return[_k]._0, token(trim(_current_str), "string"));
			if (_tokens_line._0[gt_sizeof(_tokens_line._0) - 1]._1 == "spaces")
				array_push(_return[_k]._0,
						_tokens_line._0[gt_sizeof(_tokens_line._0) - 1]);
		}
	}
	for (auto [_k, _tokens_line] : _return) {
		for (auto [_k1, _token] : _tokens_line._0) {
			if (_token._1 == "string")
				_return[_k]._0[_k1]._0 = process_string(_return[_k]._0[_k1]._0);
		}
	}
	return _return;
}
Mixed array_merge_unique(Mixed &_arr, Mixed _arr1) {
	Mixed _ele1, _tmp, _return;
	for (auto [_key_rtt, _ele1] : _arr1.valueArray) {
		if (!in_array(_ele1, _arr))
			_arr.push(_ele1);
	}
	return _arr;
}
Mixed find_all_unique_types_non_block_in_body(string _type, Mixed _input) {
	Mixed _return;
	Mixed _clause;
	if (!_input.contains("body")) {
		if (isset(_input, "name") && _input["type"] == _type) {
			_return.push(_input);
			return _return;
		} else
			return Mixed();
	} else {
		_return = Mixed();
		for (auto [_key_rtt, _clause] : _input["body"].valueArray) {
			array_merge_unique(_return,
					find_all_unique_types_non_block_in_body(_type, _clause));
		}
		return _return;
	}
}
bool find_an_obj_in_body(Mixed _obj, Mixed _input) {
	Mixed _clause;
	if (_input.contains("name") && _input.contains("type")
			&& _input["name"] == _obj["name"]
			&& _input["type"] == _obj["type"]) {
		return true;
	} else if (_input.contains("body")) {
		for (auto [_key_rtt, _clause] : _input["body"].valueArray) {
			if (find_an_obj_in_body(_obj, _clause))
				return true;
		}
		return false;
	}
	return false;
}
string array_remove_each(Mixed &_arr, Mixed _arr1) {
//	long _k;
	Mixed _ele;
	Mixed _ele1;
	for (auto [_k, _ele] : _arr.valueArray) {
		for (auto [_key_rtt, _ele1] : _arr1.valueArray) {
			if (_ele == _ele1)
				_arr.del(_k);
		}
		_arr = array_values(_arr);
	}
	return _arr;
}
Mixed find_all_vars_in_function_def(Mixed _function) {
	Mixed _inner_vars;
	_inner_vars = find_all_unique_types_non_block_in_body("var",
			_function["body"]);
	array_remove_each(_inner_vars, _function["vars"]);
	return _inner_vars;
}
bool find_return_in_body(Mixed _body) {
	Mixed _tmp1;
	_tmp1.push("name", "@return");
	_tmp1.push("type", "function");
	return find_an_obj_in_body(_tmp1, _body);
}
void parse(string _path) {
	string _content;
	tokens_line1_arr _tokens_line1_arr;
	Mixed _structure_arr;
	_content = file_get_contents(_path);
	_tokens_line1_arr = tokenize(_content);
	_tokens_line1_arr = merge_strings(_tokens_line1_arr);
	_structure_arr = structurelize(_tokens_line1_arr);
	__main = _structure_arr;
}

//==================================================================================================================================================================
Mixed __answer_var, __all_global_vars, __all_local_vars;
void assign_var(string var, Mixed value) {
//TODO:
	;
}
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
Mixed __global_vars, __local_vars;
long __current_func_lv = 0;
long __break, __continue = 0;
Mixed find_operator_in_expr(Mixed _expr);
Mixed gt_do(string _opt, token _params, long _opt_pos);
Mixed gt_do(string _opt, Mixed _params, long _opt_pos);
Mixed create_array_var(Mixed _parsed);
Mixed get_value(Mixed _value);
Mixed get_var_global_value(Mixed _value);
Mixed call_function(Mixed _parsed);
Mixed gt_eval(Mixed _parsed) {
	Mixed _find_result;
	Mixed _result;
	Mixed _backup_vars;
	if (!php_is_array(_parsed))
		return _parsed;
	if (in_array(_parsed["type"], { { 0, "number" }, { 1, "string" } }))
		return _parsed["name"];
	if (_parsed["type"] == "expr") {
		if (gt_sizeof(_parsed["body"]) == 1) {
			return gt_eval(_parsed["body"][0]);
		} else {
			_find_result = find_operator_in_expr(_parsed);
			if (gt_sizeof(_find_result) == 0)
				return _result;
			_result = gt_do(_find_result["operator"].valueStr,
					token(_find_result["expr"]),
					_find_result["opt_pos"].valueNum);
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
	if (_parsed["type"] == "function") {
		_backup_vars = __local_vars;
		// _current_func_lv ++;
		_result = call_function(_parsed);
		__local_vars = _backup_vars;
		// _current_func_lv --;
		return _result;
	}
	if (_parsed["type"] == "array") {
		return create_array_var(_parsed);
	}
	if (_parsed["type"] == "assignment") {
		assign_var(_parsed["left"], _result = gt_eval(_parsed["right"]));
		return _result;
	}
	if (_parsed["type"] == "complex_value") {
		_result = get_value(_parsed);
		return _result;
	}
	throw new GtlangException("unsupported expr");
}

Mixed& get_ref(Mixed name, Mixed key);
Mixed assign_var(Mixed _var, Mixed _value) {
	string _var_name;
	Mixed _return;
	Mixed _ref;
	if (_var["type"] == "var" && _var["name"] != "answer_var") {
		_var_name = _var["name"].valueStr;
		if (__current_func_lv == 0) {
			_return = __global_vars[_var_name] = (_value);
			return _return;
		} else {
			_return = __local_vars[_var_name] = (_value);
			return _return;
		}
	} else if (_var["type"] == "var_global") {
		_var_name = _var["name"].valueStr;
		if (isset(__global_vars, (string) _var_name)) {
			_return = __global_vars[_var_name] = (_value);
			return _return;
		} else
			throw new GtlangException("no global var _var_name");
	} else if (_var["type"] == "complex_value") {
		_ref = get_ref(_var["name"], gt_eval(_var["key"]));
		_ref = _value;
		return _return;
	} else if (_var["type"] == "var" && _var["name"] == "answer_var") {
		__answer_var = _value;
		return _return;
	}
	throw new GtlangException("not valid left side of assignment");
}
Mixed& get_ref(Mixed name, Mixed key) {
	if (name["type"] == "var" && __current_func_lv > 0) {
		return __local_vars[name["name"].valueStr].get_ref(
				gt_eval(key).valueStr);
	} else if (name["type"] == "global_var"
			|| (__current_func_lv == 0 && name["type"] == "var")) {
		return __global_vars[name["name"].valueStr].get_ref(
				gt_eval(key).valueStr);
	} else if (name["type"] == "complex_value") {
		return get_ref(name["name"], name["key"]).get_ref(gt_eval(key).valueStr);
	}
	throw new GtlangException("no var");
}
Mixed get_value(Mixed _value) {
	string _var_name;
	Mixed _return;
	Mixed _result;
	if (_value["type"] == "var") {
		_var_name = _value["name"].valueStr;
		if (__current_func_lv == 0) {
			_return = __global_vars[_var_name];
			return _return;
		} else {
			_return = __local_vars[_var_name];
			return _return;
		}
	} else if (_value["type"] == "complex_value") {
		_result = gt_eval(_value["name"]);
		return _result[gt_eval(_value["key"]).valueStr];
	}
	return Mixed();
}
int gt_exec(Mixed _parsed) {
	Mixed _cmd;
	Mixed _if;
	Mixed _is_catched;
	Mixed _e;
	Mixed _answer_var;
	if (_parsed["type"] == "block" || _parsed["type"] == "inline_block") {
		for (auto& [_key_rtt, _auto_cmd] : _parsed["body"].valueArray) {
			if (__break > 0 || __continue > 0) {
				// _break --;
				return 1;
			}
			_cmd = (Mixed) *_auto_cmd;
			if (_cmd["type"] == "block"
					|| _cmd["type"].valueStr == "inline_block") {
				gt_exec(_cmd);
				continue;
			} else if (_cmd["type"] == "ifs") {
				for (auto& [_key_rtt, _if] : _cmd["ifs"].valueArray) {
					if (gt_eval(((Mixed) _if)["condition"])) {
						gt_exec(((Mixed) _if)["body"]);
						break;
					}
				}
				gt_exec(_cmd["else"]);
			} else if (_cmd["type"] == "for") {
				gt_eval(_cmd["init"]);
				while (true) {
					if (__break > 0) {
						__break = 0;
						break;
					}
					if (__continue > 1) {
						__continue--;
						break;
					}
					if (__continue == 1) {
						__break--;
						continue;
					}
					gt_eval(_cmd["increment"]);
					gt_exec(_cmd["body"]);
					if (!gt_eval(_cmd["terminate"]))
						break;
				}
			} else if (_cmd["type"] == "while") {
				while (true) {
					if (!gt_eval(_cmd["condition"]))
						break;
					if (__break > 0) {
						__break--;
						break;
					}
					if (__continue > 1) {
						__continue--;
						break;
					}
					if (__continue == 1) {
						__break--;
						continue;
					}
					gt_exec(_cmd["body"]);
				}
			} else if (_cmd["type"] == "try") {
				try {
					gt_exec(_cmd["body"]);
				} catch (GtlangException &_e) {
					_is_catched = false;
					for (auto [_key_rtt, _catch_auto] : _cmd["catch"].valueArray) {
						Mixed _catch = (Mixed) _catch_auto;
						if (strpos(_e.msg,
								_catch["exception_class"].valueStr + ":")
								== 0) {
							assign_var(_catch["catch_var"], _e.msg);
							gt_exec(_catch["body"]);
							_is_catched = true;
							break;
						}
					}
					if (!_is_catched)
						throw new GtlangException("not catched");
				}
			} else if (isset(_cmd, "body")
					&& _cmd["body"][0] == token("break", "keyword")) {
				if (gt_sizeof(_cmd["body"]) == 1) {
					__break = 1;
					return 0;
				} else if (gt_sizeof(_cmd["body"]) == 2
						&& _cmd["body"][1]["type"] == "number") {
					__break = _cmd["body"]["1"]["name"].getInt();
					return 0;
				} else
					throw new GtlangException("incorrect break");
			} else if (isset(_cmd, "body")
					&& _cmd["body"][0] == token("continue", "keyword")) {
				if ((_cmd["body"].getLen()) == 1) {
					__continue = 1;
					return 0;
				} else if (gt_sizeof(_cmd["body"]) == 2
						&& _cmd["body"]["1"]["type"] == "number") {
					__break = _cmd["body"]["1"]["name"].getInt();
					return 0;
				} else
					throw new GtlangException("incorrect break");
			} else {
				return assign_var(Mixed(token("answer_var", "var")),
						gt_eval(_cmd));
			}
		}
	}
	return 0;
}
Mixed find_operator_in_expr(Mixed _expr) {
//	long _k;
	Mixed _obj;
	for (auto [_k, _obj_auto] : _expr["body"].valueArray) {
		Mixed _obj = (Mixed) *_obj_auto;
		if (_obj["type"] == "operator") {
			_expr["body"].del(_k);
			Mixed _return = Mixed();
			_return.push("operator", _obj["name"]);
			_return.push("expr", array_values(_expr["body"]));
			_return.push("opt_pos", _k);
			return _return;
		}
	}
	return Mixed();
}
Mixed gt_do(string _opt, Mixed _params, long _opt_pos) {
	Mixed _return1;
	Mixed _return0;
	Mixed _return = Mixed();
	double _return_num;
	long _return_int;
	string return_str;
	if (_opt == "+") {
		_return_num = gt_eval(_params["0"]).valueNum
				+ gt_eval(_params["1"]).valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "-") {
		_return_num = gt_eval(_params["0"]).valueNum
				- gt_eval(_params["1"]).valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "*") {
		_return_num = gt_eval(_params["0"]).valueNum
				* gt_eval(_params["1"]).valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "/") {
		_return_num = gt_eval(_params["0"]).valueNum
				/ gt_eval(_params["1"]).valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "%") {
		_return_int = gt_eval(_params["0"]).getInt()
				+ gt_eval(_params["1"]).getInt();
		_return = Mixed(_return_int);
		return _return;
	} else if (_opt == "**") {
		_return_num = gt_eval(_params["0"]).valueNum
				+ gt_eval(_params["1"]).valueNum;
		_return = Mixed(_return_num);
		return _return;
	} else if (_opt == "&&") {
		return gt_eval(_params["0"]).valueBool
				&& gt_eval(_params["1"]).valueBool;
	} else if (_opt == "||") {
		return gt_eval(_params["0"]).valueBool
				|| gt_eval(_params["1"]).valueBool;
	} else if (_opt == "!") {
		return !gt_eval(_params["0"]).valueBool;
	} else if (_opt == "===") {
		return gt_eval(_params["0"]) == gt_eval(_params["1"])
				&& _params["0"]["type"];
	} else if (_opt == "==") {
		return gt_eval(_params["0"]) == gt_eval(_params["1"]);
	} else if (_opt == "<") {
		return gt_eval(_params["0"]).valueNum < gt_eval(_params["1"]).valueNum;
	} else if (_opt == "<=") {
		return gt_eval(_params["0"]).valueNum <= gt_eval(_params["1"]).valueNum;
	} else if (_opt == ">") {
		return gt_eval(_params["0"]).valueNum > gt_eval(_params["1"]).valueNum;
	} else if (_opt == ">=") {
		return gt_eval(_params["0"]).valueNum >= gt_eval(_params["1"]).valueNum;
	} else if (_opt == "!=") {
		return gt_eval(_params["0"]).valueNum != gt_eval(_params["1"]).valueNum;
	} else if (_opt == "++") {
		_return0 = _params["0"];
		assign_var(_params["0"]["name"],
				_return1 = Mixed(gt_eval(_params["0"]).valueNum + 1));
		if (_opt_pos == 0)
			return _return0;
		else
			return _return1;
	} else if (_opt == "--") {
		_return0 = _params["0"];
		assign_var(_params["0"]["name"],
				_return1 = Mixed(gt_eval(_params["0"]).valueNum - 1));
		if (_opt_pos == 0)
			return _return0;
		else
			return _return1;
	} else if (_opt == "+:") {
		assign_var(_params["0"]["name"],
				_return = gt_eval(_params["0"]) + gt_eval(_params["1"]));
		return _return;
	} else if (_opt == "-:") {
		assign_var(_params["0"]["name"],
				_return = gt_eval(_params["0"]) - gt_eval(_params["1"]));
		return _return;
	} else if (_opt == "*:") {
		assign_var(_params["0"]["name"],
				_return = gt_eval(_params["0"]) * gt_eval(_params["1"]));
		return _return;
	} else if (_opt == "/:") {
		assign_var(_params["0"]["name"],
				_return = gt_eval(_params["0"]) / gt_eval(_params["1"]));
		return _return;
	} else if (_opt == "%:") {
		assign_var(_params["0"]["name"],
				_return = gt_eval(_params["0"]) % gt_eval(_params["1"]));
		return _return;
	} else {
		throw new GtlangException("unknown operator");
	}
}
Mixed gt_do(string _opt, token _params, long _opt_pos) {
	return gt_do(_opt, Mixed(_params), _opt_pos);
}
Mixed get_var_global_value(Mixed _parsed) {
	return __global_vars[_parsed["name"].valueStr];
}
Mixed get_var_local_value(Mixed _parsed) {
	return __local_vars[_parsed["name"].valueStr];
}
Mixed replace_get_ele_with_complex_value(Mixed _expr) {
//long _k;
	Mixed _v;
	if (!php_is_array(_expr))
		return _expr;
	if (isset(_expr["body"], "1") && _expr["body"]["1"]["name"] == "get_ele"
			&& _expr["body"]["1"]["type"] == "operator"
			&& (_expr["body"].getLen()) == 3) {
		_expr["type"] = "complex_value";
		_expr["name"] = _expr["body"]["0"];
		_expr["key"] = _expr["body"]["2"];
	}
// if (isset ( _expr ["body"] ))
	for (auto [_k, _v] : _expr.valueArray) {
		_expr[_k] = replace_get_ele_with_complex_value((Mixed) _v);
	}
	return _expr;
}
void eval(string _input) {
	;
}

Mixed call_builtin_function(Mixed _parsed) {
	Mixed _function = Mixed();
	GTBuiltinFunction _defined_func;
	arr_ls _params_str_arr;
	Mixed _tmp;
	Mixed _i;
	Mixed _arg;
	string _params_str;
	Mixed _result;
//	unsigned long _count_required_params;
	Mixed _var;
//	unsigned long _k = 0;
//	unsigned long _j = 0;
	Mixed _passed_vars_value;
	Mixed _passed_value;
// count required params;
	for (auto [_key_rtt, _defined_func_auto] : __b_funcs) {
		_defined_func = (GTBuiltinFunction) _defined_func_auto;
		if (_key_rtt == _parsed["name"]) {
			try {
				_result = (*_defined_func)(_parsed["args"]);
			} catch (GtlangException *_e) {
				echo("Error : " + _e->msg);
				exit(0);
			}
			return _result;
		}
	}
	throw new GtlangException("built in function not defined");
}
Mixed call_custom_function(Mixed _parsed) {
	Mixed _function = Mixed();
	Mixed _defined_func;
	arr_ls _params_str_arr;
	Mixed _tmp;
	Mixed _i;
	Mixed _arg;
	string _params_str;
	Mixed _result;
	unsigned long _count_required_params;
	Mixed _var;
	unsigned long _k = 0;
	unsigned long _j = 0;
	Mixed _passed_vars_value;
	Mixed _passed_value;
// count required params;
	for (auto [_key_rtt, _defined_func_auto] : __funcs.valueArray) {
		_defined_func = (Mixed) _defined_func_auto;
		if (_defined_func["name"] == _parsed["name"]) {
			_function = _defined_func;
			break;
		}
	}
	if (!_function) {
		throw new GtlangException("custom function not defined");
	}
	if (gt_sizeof(_parsed["args"]) < _function["vars"].valueNum) {
		throw new GtlangException(
				"function call dont more params than function define");
	}
	_count_required_params = 0;
	for (auto& [_key_rtt, _var] : _function["vars"].valueArray) {
		if (isset(_var, "1"))
			break;
		_count_required_params++;
	}
	if (((unsigned long) gt_sizeof(_parsed["args"])) < _count_required_params)
		throw new GtlangException("function call dont have enough params");
// assign called params
	for (auto& [_k, _arg] : _parsed["args"].valueArray) {
		_var = _function["vars"][_k];
		assign_var(_var, gt_eval(_arg));
	}
// assign default un-called params
	if ((long) _k < gt_sizeof(_function["vars"])) {
		for (_j = _k; (long) _j < gt_sizeof(_function["vars"]); _j++) {
			_passed_vars_value.push(_function["vars"][_j][1]);
		}
	}
	__current_func_lv++;
	for (auto const& [_j, _passed_value] : _passed_vars_value.valueArray) {
		assign_var(_function["vars"][_j]["0"], _passed_value);
	}
	gt_exec(_function["body"]);
	__current_func_lv--;
	return Mixed();
}
Mixed call_function(Mixed _parsed) {
	try {
		return call_builtin_function(_parsed);
	} catch (...) {
		;
	}
	try {
		return call_custom_function(_parsed);
	} catch (...) {
		;
	}
	throw new GtlangException("Cannot find the function anywhere");
}
Mixed create_array_var(Mixed parsed) {
	Mixed _return = Mixed();
	Mixed _element;
	for (auto [_k, _element_auto] : parsed["body"].valueArray) {
		_element = (Mixed) _element_auto;
		_return[gt_eval(_element["key"]).valueStr] = gt_eval(_element["value"]);
	}
	return _return;
}
int main1() {
	Mixed a, b;
	a.push(1l);
	a.push(2l);
	a.push(a);
	a[2] = Mixed("g");
	return b;
}
int main(int argc, char *argv[]) {
//prepare;
	init_translation();
	init_builtin_functions();
	string _operator1;
	long _len;
	for (auto const& [_k, _v1] : __operators) {
		string _v = (string) _v1;
		array_push(__operator_1st_chars, ts(_v.at(0)));
	}
	for (auto const& [_k, _operator] : __operators) {
		_len = strlen((string) _operator);
		if (array_search(_operator, __operators_by_chars_count[_len]) == -1)
			array_push(__operators_by_chars_count[_len], _operator);
	}
// ! prepare

	string _input_file = "test.gtc";
	try {
		if (argc > 1)
			_input_file = argv[1];
	} catch (...) {
		;
	}
	string _content;
	try {
		_content = file_get_contents(_input_file);
	} catch (...) {
		echo("Cannot read input file.");
	}
	//process
	try {
		tokens_line1_arr _tokens = tokenize(_content);
		Mixed _structure = structurelize(_tokens);
		//_structure.printPretty();
		gt_exec(_structure);

	} catch (const GtlangException &_e) {
		echo("Error: " + _e.msg);
		return 1;
	} catch (const GtlangException *_e) {
		echo("Error : " + _e->msg);
		return 1;
	}
	return 0;
}
;
