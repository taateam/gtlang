/*
 * tokenize.h
 *
 *  Created on: May 25, 2025
 *      Author: t
 */

#ifndef CORE_TOKEN_H_
#define CORE_TOKEN_H_

string get_body(const Mixed &_1);
string get_name(const Mixed &_1);
Mixed array_merge(Mixed _arr, const tokens_line &_arr1) {
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
bool is_az(const string &_inp) {
	return (php_is_preg_match("/[a-zA-Z]/", _inp, false)
			|| php_is_preg_match("/[\\p{L}]+/u", _inp, true));
}
Mixed get_1st_ele(const Mixed &_arr) {
	for (auto [_k, _v] : _arr.valueArray) {
		return *_v;
	}
	return Mixed();
}
template<typename V>
V get_last_ele(const map<long, V> &_arr) {
	if (!_arr.empty())
		return _arr.rbegin()->second;
	return V();
}
string remove_from_string(string _str, long _start, long _stop) {
	if (_start >= _stop || _stop > strlen(_str))
		return _str;
	_str = substr(_str, 0, _start) + " " + substr(_str, _stop);
	return _str;
}
long get_first_pos_or_end_of_str(const string &_content, const string &_str,
		long _start_pos) {
	long _pos_end;
	_pos_end = strpos(_content, _str, _start_pos);
	if (_pos_end == -1)
		_pos_end = strlen(_content);
	else
		_pos_end += strlen(_str);
	return _pos_end;
}
tokens_line rtrim_tokens_line(tokens_line _input) {
	reset_keys(_input);
	long _size = gt_sizeof(_input);
	for (long _i = 0; _i < _size; _i++) {
		token _tmp = _input[_size - _i - 1];
		if (_tmp._1 == "spaces")
			_input.erase(_size - _i - 1);
		else
			break;
	}
	return _input;
}
arr_ll get_line_and_column_number(long _starting_pos, const string &_content) {
//	echo("\n========\n");
	arr_ls _lines = explode("\n", _content);
	long _j = 0;
	long _len;
//	long _len0 = strlen(_content);
	for (auto [_i, _line] : _lines) {
		_len = strlen(_line);
//		echo("j:" + ts(_j));
//		echo("\n");
//		echo("len:" + ts(_len));
//		echo("\n");
		if (_j + _len + 1 > _starting_pos) {
			return { {0,_i+1}, {1,_starting_pos-_j+1}};
		}
		_j += _len + 1;
	}
	return { {0,-1}, {1,-1}};
}
void tokens_push(tokens_line &_arr, token _ele, long _starting_pos,
		const string &_content) {
	arr_ll _pos = get_line_and_column_number(_starting_pos, _content);
	_ele._l = _pos[0];
	_ele._c = _pos[1];
	if (_arr.size() == 0) {
		_arr[0] = _ele;
		return;
	}
	long _max_key = (_arr.rbegin()->first);
	_arr[_max_key + 1] = _ele;
}
void tokens_pushl(tokens_line &_arr, token _ele, long _starting_pos,
		const string &_content) {
	_ele._0 = l(_ele._0);
	tokens_push(_arr, _ele, _starting_pos, _content);
}
void tokens_pushlv(tokens_line &_arr, token _ele, long _starting_pos,
		const string &_content) {
	string _tmp = substr(_ele._0, 1);
	_ele._0 = "$" + l(_tmp);
	tokens_push(_arr, _ele, _starting_pos, _content);
}
void tokens_pushlf(tokens_line &_arr, token _ele, long _starting_pos,
		const string &_content) {
	string _tmp = substr(_ele._0, 1);
	_ele._0 = "@" + l(_tmp);
	tokens_push(_arr, _ele, _starting_pos, _content);
}
//string remove_comment_blocks(string _content) {
//	long _len;
//	long _i;
//	long _last_pos;
//	_len = strlen(_content);
//	_i = 0;
//	while (_i < _len - 1) {
//		if (ts(_content.at(_i)) + ts(_content.at(_i + 1)) == "/*") {
//			_last_pos = get_first_pos_or_end_of_str(_content, "*/", _i);
//			_content = remove_from_string(_content, _i, _last_pos);
//			_len = strlen(_content);
//		}
//		_i++;
//	}
//	return _content;
//}
//string remove_inline_comments(string _content) {
//	arr_ls _arr;
////	long _k;
//	string _v;
//	long _pos;
//	_arr = explode("\n", _content);
//	for (auto [_k, _v] : _arr) {
//		if ((_pos = strpos((string) _v, "//")) != -1)
//			_arr[_k] = substr((string) _v, 0, _pos);
//	}
//	return implode("\n", _arr);
//}
//string remove_comments(string _content) {
//	_content = remove_inline_comments(_content);
//	_content = remove_comment_blocks(_content);
//	return _content;
//}
//string rtrim_all_lines(string _content) {
//	arr_ls _arr;
////	long _k;
//	string _v;
//	_arr = explode("\n", _content);
//	for (auto [_k, _v] : _arr) {
//		_arr[_k] = rtrim(_v);
//	}
//	return implode("\n", _arr);
//}
void rtrim_all_lines_arr(tokens_line1_arr &_content) {
//	long _k0;
	tokens_line1 _line;
//	long _k1;
	token _token;
	long _kx = 0;
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
	return;
}
string tokens_arr_to_str1(const tokens_line &_tokens_line1_arr) {
	string _return;
	token _token;
	_return = "";
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		_return += _token._0;
	}
	return _return;
}
Mixed explode_tokens(const token &_del, const tokens_line &_tokens_line1_arr) {
	Mixed _return;
	long _k;
	_k = 0;
	Mixed _tmp;
	for (const auto& [_key_rtt, _token] : _tokens_line1_arr) {
		if (_token == _del) {
			_return.push(_k, _tmp);
			_k++;
			_tmp = Mixed();
		} else {
			_tmp.push(Mixed(_token));
		}
	}
	if (!_tmp.empty())
		_return.push(_k, _tmp);
	return _return;
}
Mixed explode_tokens(const string &_del, const tokens_line &_tokens_line1_arr) {
	Mixed _return;
	long _k;
	_k = 0;
	Mixed _tmp;
	for (const auto& [_key_rtt, _token] : _tokens_line1_arr) {
		if (_token._0 == _del) {
			_return.push(_k, _tmp);
			_k++;
			_tmp = Mixed();
		} else {
			_tmp.push(Mixed(_token));
		}
	}
	if (!_tmp.empty())
		_return.push(_k, _tmp);
	return _return;
}
//tokens_line_arr explode_tokens(token _del, tokens_line _tokens_line1_arr) {
//	tokens_line_arr _return;
//	long _k;
//	token _token;
//	_return = { { 0, { } } };
//	_k = 0;
//	for (const auto& [_key_rtt, _token] : _tokens_line1_arr) {
//		if (_token == _del) {
//			_k++;
//			_return[_k] = { };
//		} else {
//			array_push(_return[_k], _token);
//		}
//	}
//	return _return;
//}
//tokens_line_arr explode_tokens(string _del, tokens_line _tokens_line1_arr) {
//	tokens_line_arr _return;
//	long _k;
//	token _token;
//	_return = { { 0, { } } };
//	_k = 0;
//	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
//		if (_token._0 == _del) {
//			_k++;
//			_return[_k] = { };
//		} else {
//			array_push(_return[_k], _token);
//		}
//	}
//	return _return;
//}
arr_ll array_search_multi(const token &_search, const tokens_line &_arr) {
	arr_ll _return;
//	long _k;
	token _v;
	_return = { };
	for (const auto& [_k, _v] : _arr) {
		if (_search == _v)
			array_push(_return, _k);
	}
	return _return;
}

tokens_line remove_spaces_from_tokens_arr(
		const tokens_line &_tokens_line1_arr) {
	tokens_line _return;
	token _token;
	_return = { };
	for (auto [_key_rtt, _token] : _tokens_line1_arr) {
		if ((_token._1 != "") && _token._1 != "spaces")
			array_push(_return, _token);
	}
	return _return;
}
Mixed remove_spaces_from_tokens_arr(const Mixed &_tokens_line1_arr) {
	Mixed _return;
	for (auto [_key_rtt, _token_auto] : _tokens_line1_arr.valueArray) {
		Mixed _token = (Mixed) * _token_auto;
		if ((get_type(_token) != "spaces"))
			_return.push(_token);
	}
	return _return;
}
bool is_blank_str(const string &_str) {
	for (long _i = 0; _i < strlen(_str); _i++)
		if (to_string(_str.at(_i)) != " " && to_string(_str.at(_i)) != "\t")
			return false;
	return true;
}
//string remove_blank_lines(string _content) {
//	arr_ls _arr;
//	string _v;
//	_arr = explode("\n", _content);
//	for (auto [_k, _v] : _arr) {
//		if (is_blank_str(_v))
//			_arr.erase(_k);
//	}
//	return implode("\n", _arr);
//}
//string process_first_line(string _content) {
//	arr_ls _arr;
//	string _first_line;
//	_arr = explode("\n", _content);
//	_first_line = trim(_arr[0]);
//	if (strpos(_first_line, "#") == 0)
//		array_shift(_arr);
//	return implode("\n", _arr);
//}
void new_line(tokens_line1_arr &_arr, long &_line) {
	_line++;
	if (!isset(_arr, _line))
		_arr[_line] = { { }, 0 };
}
tokens_line ltrim_arr(const tokens_line &_arr) {
//	long _k;
	token _v;
	tokens_line _return;
	for (auto [_k, _v] : _arr) {
		if (is_blank_str(_v._0))
			continue;
		else
			array_push(_return, _v);
	}
	return _return;
}
bool in_array_lv2_0(const string &_ele, const tokens_line &_arr) {
	token _ele_tmp;

	for (auto [_key_rtt, _ele_tmp] : _arr) {
		if (_ele == _ele_tmp._0)
			return true;
	}
	return false;
}
bool in_array_lv2_1(const string &_ele, const tokens_line &_arr) {
	token _ele_tmp;

	for (auto [_key_rtt, _ele_tmp] : _arr) {
		if (_ele == _ele_tmp._1)
			return true;
	}
	return false;
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
Mixed tokens_arr_trim1(Mixed &_tokens_line1_arr) {
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
Mixed tokens_arr_trim(Mixed &_tokens_line1_arr) {
//Mixed _token_array_trimmed;
//	_token_array_trimmed = _tokens_line1_arr;
	Mixed _token_array_trimmed = tokens_arr_trim1(_tokens_line1_arr);
	while (gt_sizeof(_tokens_line1_arr) > gt_sizeof(_token_array_trimmed)) {
		_tokens_line1_arr = _token_array_trimmed;
		_token_array_trimmed = tokens_arr_trim1(_tokens_line1_arr);
	}
	return _token_array_trimmed;
}
token token_to_name_and_type_format(const Mixed &_token) {
// if (! is_token ( _token ))
// return _token;
	return token(_token[0], _token[1]);
}
string process_string(const string &_str) {
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
tokens_line1_arr merge_strings(const tokens_line1_arr &_tokens_line1_arr) {
	tokens_line1_arr _return;
//	long _k;
	tokens_line1 _tokens_line, _tmp;
	string _current_str;
//	long _k1;
	token _token;
	_return = { };
	for (auto [_k, _tokens_line] : _tokens_line1_arr) {
		_tmp._0 = { };
		_tmp._1 = _tokens_line1_arr.at(_k)._1;
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
Mixed array_merge_unique(Mixed &_arr, const Mixed &_arr1) {
	Mixed _ele1, _tmp, _return;
	for (auto [_key_rtt, _ele1] : _arr1.valueArray) {
		if (!in_array(_ele1, _arr))
			_arr.push(_ele1);
	}
	return _arr;
}
Mixed find_all_unique_types_non_block_in_body(const string &_type,
		const Mixed &_input) {
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
bool find_an_obj_in_body(const Mixed &_obj, const Mixed &_input) {
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
string array_remove_each(Mixed &_arr, const Mixed &_arr1) {
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
void parse(const string &_path) {
	string _content;
	tokens_line1_arr _tokens_line1_arr;
	Mixed _structure_arr;
	_content = file_get_contents(_path);
	_tokens_line1_arr = tokenize(_content);
	_tokens_line1_arr = merge_strings(_tokens_line1_arr);
	_structure_arr = structurelize(_tokens_line1_arr);
	__main = _structure_arr;
}

#endif /* CORE_TOKEN_H_ */
