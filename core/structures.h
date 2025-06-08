/*
 * structures.h
 *
 *  Created on: May 25, 2025
 *      Author: t
 */

#ifndef CORE_STRUCTURES_H_
#define CORE_STRUCTURES_H_

Mixed get_arr_between_brackets_mixed(const string &_open_bracket,
		const Mixed &_tokens_line1_arr, long _pos_of_open_bracket) {
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
		_v = (Mixed) * _v_auto;
		if (tl((string) _k_auto) <= _pos_of_open_bracket)
			continue;
		else if (_v["name"] == _open_bracket && _v["type"] == "operator")
			_lv++;
		else if (_v["name"] == _close_bracket && _v["type"] == "operator") {
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
tokens_line get_arr_between_brackets_tl(const string &_open_bracket,
		const tokens_line &_tokens_line1_arr, long _pos_of_open_bracket) {
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
arr_ll find_all_token_at_level0_by_type(const string &_token_type_to_compare,
		const Mixed &_tokens_line1_arr) {
	long _lv1;
	long _lv2;
	arr_ll _return;
//long _k;
	Mixed _token;
	_lv1 = _lv2 = 0;
	_return = { };
	for (auto [_k, _token_auto] : _tokens_line1_arr.valueArray) {
//		if (!is_token(_token)) {
//			continue;
//		}
		_token = (Mixed) * _token_auto;
		if (_token == token("(", "operator")) {
			_lv1++;
		} else if (_token == token(")", "operator")) {
			_lv2++;
		} else if (_token == token("[", "operator")) {
			_lv1--;
		} else if (_token == token("]", "operator")) {
			_lv2--;
		} else if (get_type(_token) == _token_type_to_compare && _lv1 == 0
				&& _lv2 == 0) {
			array_push(_return, tl(_k));
		}
	}
	return _return;
}
string get_body(const Mixed &_1) {
	string _return = "";
	if (isset(_1, "body"))
		return (string) _1["0"];
	else if (isset(_1, "0")) {
		return (string) _1["0"];
	}
	return _return;
}
string get_name(const Mixed &_1) {
	string _return = "";
	if (isset(_1, "body"))
		return "complex";
	if (isset(_1, "name"))
		return (string) _1["name"];
	else if (isset(_1, "0")) {
		return (string) _1["0"];
	}
	return _return;
}
Mixed find_previous_non_spaces_token(const Mixed &_tokens_line1_arr,
		long _pos) {
	if (isset(_tokens_line1_arr, _pos - 1)) {
		Mixed _tmp = _tokens_line1_arr[_pos - 1];
		if (get_name(_tmp) != "spaces")
			return _tmp;
	}
	if (isset(_tokens_line1_arr, _pos - 2)) {
		Mixed _tmp = _tokens_line1_arr[_pos - 2];
		if (get_name(_tmp) != "spaces")
			return _tmp;
	}
	return Mixed(token("", ""));
}
Mixed find_next_non_spaces_token(const Mixed &_tokens_line1_arr, long _pos) {
	if (isset(_tokens_line1_arr, _pos + 1)) {
		Mixed _tmp = _tokens_line1_arr[_pos + 1];
		if (get_name(_tmp) != "spaces")
			return _tmp;
	}
	if (isset(_tokens_line1_arr, _pos + 2)) {
		Mixed _tmp = _tokens_line1_arr[_pos + 2];
		if (get_name(_tmp) != "spaces")
			return _tmp;
	}
	return Mixed(token("", ""));
}
Mixed find_next_next_non_spaces_token(const Mixed &_tokens_line1_arr,
		long _pos) {
	long _first_pos = 0;
	if (isset(_tokens_line1_arr, _pos + 1)) {
		Mixed _tmp = _tokens_line1_arr[_pos + 1];
		if (get_name(_tmp) != "spaces")
			_first_pos = _pos + 1;
	} else if (isset(_tokens_line1_arr, _pos + 2)) {
		Mixed _tmp = _tokens_line1_arr[_pos + 2];
		if (get_name(_tmp) != "spaces")
			_first_pos = _pos + 2;
	}
	return find_next_non_spaces_token(_tokens_line1_arr, _first_pos);
}
arr_ll find_all_method_calls_at_level_0(const Mixed &_tokens_line1_arr) {
	arr_ll _return;
	for (auto [_k_auto, _v] : _tokens_line1_arr.valueArray) {
		Mixed _token = *_v;
		long _k = tl(_k_auto);
		if (_token == token(">>", "operator")) {
			Mixed _previous_token = find_previous_non_spaces_token(
					_tokens_line1_arr, _k);
			string _previous_type = get_type(_previous_token);
			if (_previous_type != "var" && _previous_type != "expr")
				continue;
			Mixed _next_token = find_next_non_spaces_token(_tokens_line1_arr,
					_k);
			string _next_type = get_type(_next_token);
			if (_next_type != "function")
				continue;
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
tokens_line_arr array_cut_by_pos(const tokens_line &_arr,
		const arr_ll &_positions) {
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
			_start = _positions.at(_i - 1) + 1;
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
Mixed array_cut_by_pos(const Mixed &_arr, const arr_ll &_positions) {
	Mixed _return;
//long _i_i = 0;
	long _last_delimiter_pos = 0;
	long _start;
	long _stop;
	long _len;
	if (_positions.empty()) {
		Mixed _tmp = Mixed();
		_tmp.push("0", _arr);
		return _tmp;
	}
	_return = Mixed();
	for (auto [_i, _pos] : _positions) {
		if (isset(_positions, _i - 1))
			_start = _positions.at(_i - 1) + 1;
		else
			_start = 0;
		if (isset(_positions, _i))
			_stop = (long) _pos;
		else
			_stop = gt_sizeof(_arr) - 1;
		_len = _stop - _start;
		if (_len < 0)
			_len = 0;
//		_arr.resetKeys();
		_return.push((long) _i, array_slice(_arr, _start, _len));
		_last_delimiter_pos = (long) _pos;
	}

	_return.push(array_slice(_arr, _last_delimiter_pos + 1));
	return _return;
}
arr_ll find_all_token_type_at_level_0(const string &_token_type_to_compare,
		const Mixed &_tokens_line1_arr) {
	long _lv1;
	long _lv2;
	arr_ll _return;
//	long _k;
	Mixed _token;
	_lv1 = _lv2 = 0;
	_return = { };
	for (const auto& [_k, _token_auto] : _tokens_line1_arr.valueArray) {
//		if (!is_token(_token)) {
//			continue;
//		}
		_token = (Mixed) * _token_auto;
		if (_token == token("(", "operator")) {
			_lv1++;
		} else if (_token == token("[", "operator")) {
			_lv2++;
		} else if (_token == token(")", "operator")) {
			_lv1--;
		} else if (_token == token("]", "operator")) {
			_lv2--;
		} else if (get_type(_token) == _token_type_to_compare && _lv1 == 0
				&& _lv2 == 0) {
			array_push(_return, tl(_k));
		}
	}
	return _return;
}
arr_ll find_all_token_at_level_0(const token &_token_to_compare,
		const Mixed &_tokens_line1_arr) {
	long _lv1;
	long _lv2;
	arr_ll _return;
//	long _k;
	Mixed _token;
	_lv1 = _lv2 = 0;
	_return = { };
	for (const auto& [_k, _token_auto] : _tokens_line1_arr.valueArray) {
//		if (!is_token(_token)) {
//			continue;
//		}
		_token = (Mixed) * _token_auto;
		if (_token == token("(", "operator")) {
			_lv1++;
		} else if (_token == token("[", "operator")) {
			_lv2++;
		} else if (_token == token(")", "operator")) {
			_lv1--;
		} else if (_token == token("]", "operator")) {
			_lv2--;
		} else if (_token == _token_to_compare && _lv1 == 0 && _lv2 == 0) {
			array_push(_return, tl(_k));
		}
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
getline_subblock_t getline_subblock(const tokens_line1_arr &_tokens_line1_arr,
		long _header_line_i) {
	long _header_lv;
	tokens_line1_arr _tmp_arr;
	long _i;
	tokens_line1 _v;
	getline_subblock_t _return = getline_subblock_t();
	_header_lv = _tokens_line1_arr.at(_header_line_i)._1;
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
Mixed parse_array_element(const Mixed &_tokens_line1_arr) {
	Mixed _tmp_arr;
	arr_ll _all_marks_pos;
//	_tmp_arr = ;
	_all_marks_pos = find_all_token_at_level_0(token("=>", "operator"),
			_tokens_line1_arr);
	_tmp_arr = array_cut_by_pos(_tokens_line1_arr, _all_marks_pos);
	Mixed _return;
	if (gt_sizeof(_tmp_arr) > 2 || gt_sizeof(_tmp_arr) < 1)
		throw GreenTeaException("SyntaxErrorException",
				"Invalid array declaration.", get_1st_ele(_tokens_line1_arr));
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
//Mixed parse_array(tokens_line _tokens_line1_arr) {
//	arr_ll _all_commas;
//	tokens_line_arr _elements;
//	Mixed _return;
//	tokens_line_arr _element;
//
//	reset_keys(_tokens_line1_arr);
//	_all_commas = find_all_token_at_level_0( { ",", "operator" },
//			_tokens_line1_arr);
//	_elements = array_cut_by_pos(_tokens_line1_arr, _all_commas);
//	for (auto [_key_rtt, _element] : _elements) {
//		_return.push(parse_array_element(_element));
//	}
//	_return.push("type", "array");
//	_return.push("body", _return);
//	add_pos_of_1st_token_to_mix(_return, _tokens_line1_arr);
//	return _return;
//}
//function is_token(_input) {
//if (isset(_input[0]) && isset(_input[1]) && gt_sizeof(_input) == 2)
//return true;
//return false;
//}
Mixed remove_all_spaces(const Mixed &_tokens_line1_arr) {
	Mixed _return;
	Mixed _ele;
//_return = ;
	for (auto [_key_rtt, _ele_auto] : _tokens_line1_arr.valueArray) {
		// if (! is_token ( _tokens_arr ))
		// continue;
		_ele = (Mixed) * _ele_auto;
		if (get_type(_ele) != "spaces")
			_return.push(_ele);
	}
	return _return;
}
Mixed parse_var(Mixed _tokens_line1_arr) {
	Mixed _tokens_arr1;
	long _lv;
	Mixed _tmp;
	Mixed _token;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	if (get_type(_tokens_line1_arr[0]) != "var"
			&& get_type(_tokens_line1_arr[0]) != "var_global")
		throw GreenTeaException("SyntaxErrorException", "not a var",
				_tokens_line1_arr[0]);
	_tokens_arr1 = array_slice(_tokens_line1_arr, 1);
	_lv = 0;
// _tmp = Mixed();
	for (const auto& [_key_rtt, _token_auto] : _tokens_arr1.valueArray) {
		_token = (Mixed) * _token_auto;
		if (_token == token("[", "operator")) {
			_lv++;
		} else if (_token == token("]", "operator")) {
			_lv--;
		} else if (_lv == 0)
			throw GreenTeaException("SyntaxErrorException", "not valid var",
					_token);
	}
	return parse_expression(_tokens_line1_arr);
}
//Mixed parse_complex_var(const Mixed & _tokens_line1_arr ) {
//	arr_ll _all_dots_pos;
//	Mixed _cutted;
//	Mixed _var;
//	_all_dots_pos = find_all_token_at_level0( { ".", "operator" },
//			_tokens_line1_arr);
//	_cutted = array_cut_by_pos(_tokens_line1_arr, _all_dots_pos);
//	for (auto [_key_rtt, _var_auto] : _cutted.valueArray) {
//		_var = (Mixed) *_var_auto;
//		try {
//			parse_var(_var);
//		} catch (...) {
//			return Mixed();
//		}
//	}
//	return parse_expression(_tokens_line1_arr);
//}
bool is_a_value_or_a_function(const Mixed &_complex_token) {
	string _type = get_type(_complex_token);
	return in_array(_type, { { 0, "string" }, { 1, "var" }, { 2, "number" }, {
			3, "array" }, { 4, "object" }, { 5, "expr" }, { 6, "global_var" }, {
			7, "object" }, { 8, "function_call" }, { 9, "method_call" }, { 10,
			"array" }, { 11, "bool" } });
}
bool is_a_class(const Mixed &_complex_token) {
	string _type = get_type(_complex_token);
	return in_array(_type, { { 0, "class" } });
}
bool is_a_var(const Mixed &_complex_token) {
	string _type = get_type(_complex_token);
	return in_array(_type, { { 0, "var" }, { 1, "global_var" } });
}
bool is_an_array(const Mixed &_complex_token) {
	string _type = get_type(_complex_token);
	return in_array(_type, { { 0, "array" } });
}
bool is_a_class_or_a_var(const Mixed &_complex_token) {
	return is_a_class(_complex_token) || is_a_var(_complex_token);
}
//bool get_type_deep_in_expr_is_var(Mixed _complex_token) {
//	if (get_type(_complex_token) == "expr")
//		return get_type_deep_in_expr_is_var(_complex_token["body"][0]);
//	if (get_type(_complex_token) == "var")
//		return true;
//	else
//		return false;
//}
bool _is_array_square_brackets(const Mixed &_tokens_line1_arr,
		long _open_bracket_pos) {
	if (!isset(_tokens_line1_arr, _open_bracket_pos - 1))
		return true;
	string _type = _tokens_line1_arr[_open_bracket_pos - 1]["type"];
	if (in_array(_tokens_line1_arr[_open_bracket_pos - 1]["type"], {
			{ 0, "var" }, { 1, "number" }, { 2, "string" } })) {
		return false;
	}
	if (_tokens_line1_arr[_open_bracket_pos - 1] == token("]", "operator")
			|| _tokens_line1_arr[_open_bracket_pos - 1]
					== token(")", "operator"))
		return false;
	return true;
}
Mixed parse_complex_var(const Mixed &_tokens_line1_arr) {
	arr_ll _commas_pos;
	Mixed _values_arr;
	if (gt_sizeof(_tokens_line1_arr) < 2) {
		return _tokens_line1_arr[0];
	}
	Mixed _expr_left_body;
	for (long _k = 0; _k < gt_sizeof(_tokens_line1_arr); _k++) {
		Mixed _token = _tokens_line1_arr[_k];
		if (_token == token("(", "operator")) {
			Mixed _expr_in_brackets_arr = get_arr_between_brackets_mixed("(",
					_tokens_line1_arr, _k);
			Mixed _expr_in_brackets_result = parse_expression(
					_expr_in_brackets_arr);
			_k += gt_sizeof(_expr_in_brackets_arr) + 1;
			_expr_left_body.push(_expr_in_brackets_result);
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
				_expr_left_body.push(_results);
			} else {
				Mixed _expr_in_brackets_result = parse_expression(
						_expr_in_brackets_arr);
				//				print_r(_expr_in_brackets_arr);
				_expr_left_body.push(token("[]", "operator"));
				_expr_left_body.push(_expr_in_brackets_result);
			}
			_k += gt_sizeof(_expr_in_brackets_arr) + 1;
			continue;
		}
		if (_token == token(")", "operator")) {
			throw GreenTeaException("SyntaxErrorException", "Invalid ')'",
					_token);
		}
		if (_token == token("]", "operator")) {
			throw GreenTeaException("SyntaxErrorException", "Invalid ']'",
					_token);
		}
		_expr_left_body.push(_token);
	}
	_expr_left_body.resetKeys();
	if (get_type(_expr_left_body[0]) != "var") {
		throw GreenTeaException("SyntaxErrorException",
				"Cannot get element of a non var.", _expr_left_body[0]);
	} else {
		Mixed _return;
		_return.push("name", _expr_left_body[0]["name"].valueStr);
		_return.push("type", "complex_value");
		//validate complex_value
		for (auto const& [_k_auto, _v] : _expr_left_body.valueArray) {
			long _k = tl(_k_auto);
			Mixed _complex_token = (Mixed) * _v;
			if (odd(_k)) {
				if (_complex_token != token("[]", "operator")
						&& _complex_token != token(">>", "operator")) {
					throw GreenTeaException("SyntaxErrorException",
							"Invalid array substitution operator.",
							_complex_token);
				}
			} else {
				if (!is_a_value_or_a_function(_complex_token)) {
					throw GreenTeaException("SyntaxErrorException",
							"Invalid array substitution index.",
							_complex_token);
				}
			};
		}

		Mixed _sub_indexes_parsed;
		bool _is_class_substitution = false;
		for (auto [_k, _v] : _expr_left_body.valueArray) {
			if (odd(tl(_k)) && tl(_k) > 0) {
				if (get_name(*_v) == ">>")
					_is_class_substitution = true;
				else if (get_name(*_v) == "[]") {
					_is_class_substitution = false;
					if (tl(_k) >= gt_sizeof(_expr_left_body) - 1
							&& !odd(gt_sizeof(_expr_left_body))) {
						_sub_indexes_parsed.push(
								token("null", "null", (long) (*_v)["l"],
										(long) (*_v)["c"]));
					}
				} else
					throw GreenTeaException("SyntaxErrorException",
							"Invalid array subtitution.", *_v);
			}
			if (!odd(tl(_k)) && tl(_k) > 0) {
				Mixed _sub_index_parsed = *_v;
				if (_is_class_substitution) {
					_sub_indexes_parsed.push(token("properties", "string"));
					_sub_index_parsed.replace("type", "string");
					_sub_indexes_parsed.push(_sub_index_parsed);
				} else {
					_sub_indexes_parsed.push(_sub_index_parsed);
				}
			}
		}
		_return.push("indexes", _sub_indexes_parsed);
		return _return;
	};
}
Mixed process_assignment(Mixed _tokens_line1_arr) {
	arr_ll _pos_of_all_colons;
	Mixed _return, _return1, _return2;
	Mixed _tmp_arr;
	Mixed _value;
	Mixed _tmp_ele;
	long _post_of_1st_colon;
	Mixed _left;
	Mixed _right;
	arr_ll _left_commas_lv0;
	arr_ll _right_commas_lv0;
	Mixed _tmp;
	Mixed _left_slided;
	Mixed _right_slided;
//	long _i;
	Mixed _one_var;
	Mixed _one_value;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	_pos_of_all_colons = find_all_token_at_level_0( { ":", "assignment" },
			_tokens_line1_arr);
	if (gt_sizeof(_pos_of_all_colons) == 0) {
		throw GreenTeaException("SyntaxErrorException",
				"process_assignment(): Invalid assignment: no colon",
				get_1st_ele(_tokens_line1_arr));
	} else if (gt_sizeof(_pos_of_all_colons) > 1) {
		_tmp_arr = array_cut_by_pos(_tokens_line1_arr, _pos_of_all_colons);
		_value = array_pop(_tmp_arr);
		for (auto& [_key_rtt, _tmp_ele_auto] : _tmp_arr.valueArray) {
			Mixed __tmp_ele = (Mixed) * _tmp_ele_auto;
			_tmp_ele.push(Mixed(token(":", "operator")));
			_tmp_ele = array_merge(_tmp_ele, _value);
			_return.push(process_assignment(_tmp_ele));
		}
		_return1.push("type", "inline_block");
		_return1.push("body", _return);
		return _return1;
	}
	_post_of_1st_colon = _pos_of_all_colons[0];
	_left = array_slice(_tokens_line1_arr, 0, _post_of_1st_colon);
	_right = array_slice(_tokens_line1_arr, _post_of_1st_colon + 1);
//	_left_commas_lv0 = find_all_token_at_level_0( { ",", "operator" }, _left);
//	_right_commas_lv0 = find_all_token_at_level_0( { ",", "operator" }, _right);
//	if (gt_sizeof(_left_commas_lv0) != gt_sizeof(_right_commas_lv0))
//		throw GtlangException("SyntaxErrorException","not valid assignment size");
//	if (_left_commas_lv0.empty()) {
	_tmp = parse_expression(_right);
	_return1.push("type", "assignment");
	_return1.push("left", parse_complex_var(_left));
	_return1.push("right", _tmp);
	_return1.push("return", _tmp);
	return _return1;
//	} else {
//		_left_slided = array_cut_by_pos(_left, _left_commas_lv0);
//		_right_slided = array_cut_by_pos(_right, _right_commas_lv0);
//		Mixed _return1;
//		for (auto [_i, _one_var_auto] : _left_slided.valueArray) {
//			Mixed _one_var = (Mixed) *_one_var_auto;
//			_one_value = _right_slided[_i];
//			Mixed _return;
//			_return.push("type", "assignment");
//			_return.push("left", parse_complex_var(_one_var));
//			_return.push("right", parse_expression(_one_value));
//			_return1.push(_return);
//		}
//		_return2.push("type", "inline_block");
//		_return2.push("body", _return);
//		return _return2;
//	}
}
struct operator1 {
public:
	long _0;		//position
	string _1;		//operator, like "+"
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

Mixed tokens_to_name_and_type_format(const token &_input) {
	Mixed _return;
	_return.push("name", _input._0);
	_return.push("type", _input._1);
	return _return;
}
Mixed tokens_arr_to_name_and_type_format(const tokens_line &_input) {
	Mixed _return;
	for (auto [_k, _v] : _input) {
		_return.push((long) _k, tokens_to_name_and_type_format((token) _v));
	}
	return _return;
}
//Mixed tokens_arr_to_name_and_type_format(Mixed _input) {
//	Mixed _return;
//	for (auto [_k, _v] : _input.valueArray) {
//		_return.push((string) _k, (Mixed) *_v);
//	}
//	return _return;
//}
string get_type(const Mixed &_1) {
	string _return = "";
	if (isset(_1, "type"))
		return (string) _1["type"];
	else if (isset(_1, "1")) {
		return (string) _1["1"];
	}
	return _return;
}
Mixed process_multiple_operators(const Mixed &_tokens_line1_arr_input) {
	arr_lo1 _arr_operators;
//	long _k;
	Mixed _tokens_arr_tmp;
	token _token;
	long _min;
	long _highest_operator_pos;
	string _highest_operator;
	token _operator;
	Mixed _return, _tmp, _tmp1;
	Mixed _tokens_line1_arr = _tokens_line1_arr_input;
	while (true) {
		_tmp = Mixed();		// reset on each loop;
		_arr_operators = { };
		//_tokens_line1_arr.printPretty(0);
		for (auto [_k, _token] : _tokens_line1_arr.valueArray) {
			if (get_type((Mixed) * _token) == "operator") {
				array_push(_arr_operators,
						(operator1(stoi(_k), get_name((Mixed) * _token))));
			}
		}
		//this function not run recursively, but it will run until complex expr become 1 operator, simple expr
		if (gt_sizeof(_arr_operators) <= 1) {
			_tmp.push("type", "expr");
			_tmp.push("body", _tokens_line1_arr);
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
		// not sure it could happen
		if (_highest_operator_pos == -1)
			break;
		// Operator with 1 object , ex: ! $a;
		if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 1) {
			_return = array_slice(_tokens_line1_arr, 0, _highest_operator_pos);
			_return.resetKeys();
			if (!isset(_tokens_line1_arr, _highest_operator_pos + 1))
				throw GreenTeaException("SyntaxErrorException",
						"Insufficient arguments type 0",
						_tokens_line1_arr[_highest_operator_pos]);
			if (!is_a_value_or_a_function(
					_tokens_line1_arr[_highest_operator_pos + 1]))
				throw GreenTeaException("SyntaxErrorException",
						"Incorrect arguments 0 type 0",
						_tokens_line1_arr[_highest_operator_pos + 1]);
			_tmp.push("type", "expr");
			_tmp1.push(0, _tokens_line1_arr[_highest_operator_pos]);
			_tmp1.push(1, _tokens_line1_arr[_highest_operator_pos + 1]);
			_tmp.push("body", _tmp1);
			_tokens_arr_tmp = array_slice(_tokens_line1_arr,
					_highest_operator_pos + 2, gt_sizeof(_tokens_line1_arr));
			_return = array_merge(_return, _tokens_arr_tmp);
			// operator with 1 object , ex: $a ++;
		} else if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 0) {
			_return = array_slice(_tokens_line1_arr, 0,
					_highest_operator_pos - 1);
			_return.resetKeys();
			if (!isset(_tokens_line1_arr, _highest_operator_pos - 1))
				throw GreenTeaException("SyntaxErrorException",
						"Insufficient arguments type 1",
						_tokens_line1_arr[_highest_operator_pos]);
			if (!is_a_value_or_a_function(
					_tokens_line1_arr[_highest_operator_pos - 1]))
				throw GreenTeaException("SyntaxErrorException",
						"Incorrect arguments 1 type 1",
						_tokens_line1_arr[_highest_operator_pos - 1]);
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
			// operator with 2 object , ex: $a + $b;
		} else if (isset(__real_operators, _highest_operator)
				&& __real_operators.at(_highest_operator).at(0) == 2) {
			_return = array_slice(_tokens_line1_arr, 0,
					_highest_operator_pos - 1);
			_return.resetKeys();
			if (!isset(_tokens_line1_arr, _highest_operator_pos - 1)
					|| !isset(_tokens_line1_arr, _highest_operator_pos + 1))
				throw GreenTeaException("SyntaxErrorException",
						"Insufficient arguments type 2",
						_tokens_line1_arr[_highest_operator_pos]);
			if (!is_a_value_or_a_function(
					_tokens_line1_arr[_highest_operator_pos - 1])) {
//				if (is_a_class(_tokens_line1_arr[_highest_operator_pos - 1])
//						&& _highest_operator != "<<")
//					continue;
				throw GreenTeaException("SyntaxErrorException",
						"Incorrect arguments 0 type 2",
						_tokens_line1_arr[_highest_operator_pos - 1]);
			}
			if (!is_a_value_or_a_function(
					_tokens_line1_arr[_highest_operator_pos + 1])) {
//				if (is_a_class(_tokens_line1_arr[_highest_operator_pos + 1])
//						&& _highest_operator != "<<")
//					continue;
				throw GreenTeaException("SyntaxErrorException",
						"Incorrect arguments 2 type 2",
						_tokens_line1_arr[_highest_operator_pos + 1]);
			}
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
//		print_r(_return);
		_tokens_line1_arr = _return;
	}
//	_tmp = Mixed();
//	_tmp.push("type", "expr");
//	_tmp["body"] = _return;
//	return _tmp;
	throw InternalException("process_multiple_operators() should not be here");
	return Mixed();
}
void validate_single_operator(Mixed _tokens_line1_arr_input) {
	string _operator_str;
	_tokens_line1_arr_input.resetKeys();
	Mixed _operator_token;
	for (auto [_k, _token] : _tokens_line1_arr_input.valueArray) {
		_operator_token = *_token;
		if (get_type(_operator_token) == "operator") {
			_operator_str = get_name(_operator_token);
			break;
		}
	}
	if (!__real_operators.contains(_operator_str))
		throw GreenTeaException("SyntaxErrorException", "Invalid operator",
				_operator_token);
	long _operator_type = __real_operators.at(_operator_str).at(0);
	if (_operator_type == 0) {
		if (gt_sizeof(_tokens_line1_arr_input) < 2)
			throw GreenTeaException("SyntaxErrorException",
					"Insufficient arguments type 0 (b)", _operator_token);
		if (!is_a_value_or_a_function(_tokens_line1_arr_input[0]))
			throw GreenTeaException("SyntaxErrorException",
					"Incorrect arguments 0 type 0 (b)", _operator_token);
	} else if (_operator_type == 1) {
		if (gt_sizeof(_tokens_line1_arr_input) < 2)
			throw GreenTeaException("SyntaxErrorException",
					"Insufficient arguments type 1 (b)");
		if (!is_a_value_or_a_function(_tokens_line1_arr_input[1]))
			throw GreenTeaException("SyntaxErrorException",
					"Incorrect arguments 1 type 1 (b)", _operator_token);
	} else if ((_operator_str == "-" || _operator_str == "+")
			&& gt_sizeof(_tokens_line1_arr_input) == 2) {
		if (!is_a_value_or_a_function(_tokens_line1_arr_input[1]))
			throw GreenTeaException("SyntaxErrorException",
					"Insufficient arguments type 2 (b)", _operator_token);
		return;
	} else if (_operator_type == 2) {
		if (gt_sizeof(_tokens_line1_arr_input) < 3)
			throw GreenTeaException("SyntaxErrorException",
					"Insufficient arguments type 2 (b)", _operator_token);
		if (!is_a_value_or_a_function(_tokens_line1_arr_input[0]))
//			if (!is_a_var(_tokens_line1_arr_input[0]) || _operator_str != "<<")
			throw GreenTeaException("SyntaxErrorException",
					"Incorrect arguments 0 type 2 (b)", _operator_token);
		if (!is_a_value_or_a_function(_tokens_line1_arr_input[2]))
//			if (!is_a_class(_tokens_line1_arr_input[2])
//					|| _operator_str != "<<")
			throw GreenTeaException("SyntaxErrorException",
					"Incorrect arguments 2 type 2 (b)", _operator_token);
	}
}
tokens_line1 convert_spaces_to_concat_operators(
		tokens_line1 _tokens_line1_arr) {
	arr_ll _spaces_poses;
	tokens_line1 _return;
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
	tokens_line _tokens_line1_arr1 = tokens_arr_trim(_tokens_line1_arr._0);
// _spaces_poses = find_all_token_at_level0_by_type ( "spaces", _tokens_arr );
	if (_tokens_line1_arr1[0] == token("for", "keyword"))
		return _tokens_line1_arr;
	if (_tokens_line1_arr1[0] == token("foreach", "keyword"))
		return _tokens_line1_arr;
	for (auto [_pos, _token_auto] : _tokens_line1_arr1) {
		token _token1 = (token) _token_auto;
		_type = _token1._1;
		if (_type != "spaces") {
			array_push(_return._0, _token1);
			continue;
		}
		_name = get_name(_token1);		// should be string of spaces;
		_spaces_pos = _pos;
		_before = _tokens_line1_arr1[_spaces_pos - 1];// starting space has been removed, so this should exists;
		_after = _tokens_line1_arr1[_spaces_pos + 1];// ending space has been removed, so this should exists;
		_before_type = get_type(_before);
		_after_type = get_type(_after);
		_concat_types = { { 0, "var" }, { 1, "number" }, { 2, "string" } };
		if (in_array(_before_type, _concat_types)
				&& in_array(_after_type, _concat_types)) {
			array_push(_return._0, token(".", "operator"));
			array_push(_return._0, token(_name, "string"));
			array_push(_return._0, token(".", "operator"));
		}
	}
	_return._1 = _tokens_line1_arr._1;
	return _return;
}
Mixed convert_spaces_to_concat_operators(Mixed &_tokens_line1_arr) {
	arr_ll _spaces_poses;
	Mixed _return;
//	long _pos;
	token _token;
	string _type;
	string _name;
	long _spaces_pos;
	token _before;
	token _after;
	string _before_type;
	string _after_type;
	arr_ls _concat_types, _primitive_types, _var_types;
	Mixed _token_1;
	Mixed _tokens_line1_arr1 = _tokens_line1_arr;
	tokens_arr_trim(_tokens_line1_arr1);
// _spaces_poses = find_all_token_at_level0_by_type ( "spaces", _tokens_arr );
	for (auto [_pos, _token_auto] : _tokens_line1_arr1.valueArray) {
		Mixed _token1 = (Mixed) * _token_auto;
		_type = get_type(_token_1);
		if (_type != "spaces") {
			_return.push(_token1);
			continue;
		}
		_name = get_name(_token1);	// should be string of spaces;
		_spaces_pos = tl(_pos);
		_before = _tokens_line1_arr1[_spaces_pos - 1];// starting space has been removed, so this should exists;
		_after = _tokens_line1_arr1[_spaces_pos + 1];// ending space has been removed, so this should exists;
		_before_type = get_type(_before);
		_after_type = get_type(_after);
		_primitive_types = { { 0, "number" }, { 1, "string" } };
		_var_types = { { 0, "var" }, { 1, "global_var" } };
		_concat_types = array_merge(_primitive_types, _var_types);
		if (in_array(_before_type, _concat_types)) {
			if (in_array(_after_type, _primitive_types)) {
				_return.push(token(".", "operator"));
				_return.push(token(_name, "string"));
				_return.push(token(".", "operator"));
			} else if (in_array(_after_type, _var_types)) {
				Mixed _after = find_next_non_spaces_token(_tokens_line1_arr1,
						tl(_pos));
				Mixed _after2 = find_next_next_non_spaces_token(
						_tokens_line1_arr1, tl(_pos));
				if ((_after = token(">>", "operator"))
						&& get_type(_after2) == "function")
					//if it is a method call, do not add concat and spaces before the object var;
					continue;
				// if is not a method call;
				_return.push(token(".", "operator"));
				_return.push(token(_name, "string"));
				_return.push(token(".", "operator"));
				;
			}
		}
	}
	return _return;
}
Mixed is_list(const Mixed &_tokens, const arr_ls &_types,
		const Mixed &_delimiter = token(",", "operator")) {
	Mixed _return;
	bool _is_delimiter;
	token _token;
	Mixed _return1;
	_is_delimiter = true;
	for (const auto& [_key_rtt, _token] : _tokens.valueArray) {
		_is_delimiter = !_is_delimiter;
		if (_is_delimiter) {
			if (!(*_token == _delimiter)) {
				return tokens_line();
			}
		} else {
			if (!in_array(get_type(*_token), _types))
				return tokens_line();
			_return.push(*_token);
		}
	}
	return _return;
}
Mixed is_list(const Mixed &_tokens, const string &_type,
		const Mixed &_delimiter = token(",", "operator")) {
	return is_list(_tokens, { { 0, _type } }, _delimiter);
}
Mixed get_each_element_from_array(const Mixed &_arr, long _num = 1) {
	Mixed _return;
//	long _k;
	Mixed _token;
	for (auto [_k_auto, _token_auto] : _arr.valueArray) {
		_token = (Mixed) * _token_auto;
		//long _k = tl(_k_auto);
		if (_num == 0) {
			_return.push(_k_auto, get_name(_token));
		} else if (_num == 1) {
			_return.push(_k_auto, get_type(_token));
		}
	}
	return _return;
}
#endif /* CORE_STRUCTURES_H_ */
