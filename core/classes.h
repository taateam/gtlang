/*
 * classes.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_CLASSES_H_
#define CORE_CLASSES_H_

Mixed convert_expr_to_complex_value(const Mixed &_object_tmp) {
	//return _object_tmp;
	Mixed _tmp = _object_tmp;
	Mixed _tmp1, _tmp2, _tmp3, _return;
	while (true) {
		//print_r(_tmp);
		if (!isset(_tmp, "body")) {
			//print_r(_tmp);
			break;
		}
		if (get_name(_tmp["body"][1]) == ">>") {
			_tmp1.push(Mixed(token(get_name(_tmp["body"][2]), "string")));
			_tmp1.push(Mixed(token("properties", "string")));
		} else {
			_tmp1.push(Mixed(token(_tmp["body"][2])));
		}
		_tmp3 = _tmp["body"][0];
		_tmp = _tmp3;
//		_tmp = _tmp["body"][0];
		//	_tmp3 = _tmp["body"][0];	print_r(_tmp);
	}
	string _object_name = get_name(_tmp);
	long _size_tmp1 = gt_sizeof(_tmp1);
	for (long _i = 0; _i < _size_tmp1; _i++) {
		_tmp2.push(_tmp1[_size_tmp1 - _i - 1]);
	}
	_return.push("name", _object_name);
	_return.push("type", "complex_value");
	_return.push("indexes", _tmp2);
	return _return;
}
Mixed get_method_and_params_lv0(Mixed &_tokens_line1_arr) {
	Mixed _return;
	arr_ll _all_methods_calls_pos;
	Mixed _two_sides;
	Mixed _tmp_array, _tmp_array1;
	arr_ll _left_comma_pos;
	arr_ll _right_comma_pos;
	tokens_line _v;
	_return = Mixed();
	_all_methods_calls_pos = find_all_method_calls_at_level_0(
			_tokens_line1_arr);
	if (gt_sizeof(_all_methods_calls_pos) != 1)
		return Mixed();
	long _method_call_pos = _all_methods_calls_pos[0];
	_return.push("type", "method_call");
	_return.push("name", get_name(_tokens_line1_arr[_method_call_pos + 1]));
	Mixed _object_tmp = (_tokens_line1_arr[_method_call_pos - 1]);
	if (get_type(_object_tmp) == "expr")
		_object_tmp = convert_expr_to_complex_value(_object_tmp);
	_return.push("object", _object_tmp);
	_return.push("args", Mixed());
	_two_sides = get_two_sides_of_method_call(_tokens_line1_arr,
			_method_call_pos);
	_two_sides[0].resetKeys();
	_two_sides[1].resetKeys();
//	_tmp_array = Mixed();
	_left_comma_pos = find_all_token_at_level_0( { ",", "operator" },
			_two_sides[0]);
	_tmp_array = array_cut_by_pos(_two_sides[0], _left_comma_pos);
	_right_comma_pos = find_all_token_at_level_0( { ",", "operator" },
			_two_sides[1]);
	_tmp_array1 = array_cut_by_pos(_two_sides[1], _right_comma_pos);
	_tmp_array = array_merge(_tmp_array, _tmp_array1);
	_tmp_array = remove_empty_elements(_tmp_array);
	for (auto& [_key_rtt, _v_auto] : _tmp_array.valueArray) {
		Mixed _v = (Mixed) * _v_auto;
		_v = trim_tokens_line_once(_v);
		if (!_v.empty())
			_return["args"].push(parse_expression(_v));
	}
//	print_r(_return);
	add_pos_of_1st_token_to_mix(_return, _tokens_line1_arr);
	return _return;
}
bool is_new_clause(Mixed _tokens_line1_arr) {
	Mixed _token;
	_tokens_line1_arr = remove_all_spaces(_tokens_line1_arr);
	if (gt_sizeof(_tokens_line1_arr) < 2)
		return false;
	for (auto& [_key_rtt, _token] : _tokens_line1_arr.valueArray) {
		if (*_token == token(l("new"), "keyword"))
			return true;
	}
	return false;
}
Mixed is_class_def(Mixed _tokens) {
	Mixed _return;
	long _last_token_i;
	Mixed _list;
	_return.push("class", "");
	_return.push("extends", Mixed());
	_tokens = remove_all_spaces(_tokens);
	_last_token_i = gt_sizeof(_tokens) - 1;
	if (get_type(_tokens[0]) != "class")
		return Mixed();
	if (_tokens[_last_token_i] != token(":", "assignment"))
		return Mixed();
// /================
	if (gt_sizeof(_tokens) == 2) {
		_return["class"] = get_name(_tokens[0]);
		_return.valueBool = true;
		return _return;
	}
	if (gt_sizeof(_tokens) < 2 || gt_sizeof(_tokens) == 3) {
		return false;
	}
	if (_tokens[1] != token("<<", "operator")) {
		return false;
	}
	_list = is_list(array_slice(_tokens, 2, _last_token_i - 2), "class");
	if (_list.empty()) {
		return false;
	}
	_return["class"] = get_name(_tokens[0]);
	_return["extends"] = get_each_element_from_array(_list, 0);
	_return.valueBool = true;
	return _return;
	return false;
}
Mixed parse_property(Mixed _tokens_line1_arr) {
	arr_ls _modifiers;
	long _start_vars_section;
	Mixed _return;
//	long _i;
	token _token;
	Mixed _vars_section;
	arr_ll _all_colons;
	Mixed _two_sides;
	Mixed _tmp;
	Mixed _list_vars;
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
		for (auto [_i, _token_auto] : _tokens_line1_arr.valueArray) {
			Mixed _token = (Mixed) * _token_auto;
			if (get_type(_token) == "modifier") {
				array_push(_modifiers, get_name(_token));
			} else {
				_start_vars_section = tl(_i);
				break;
			}
		}
		if (_modifiers.empty())
			_modifiers = { { 0, "public" } };
		if (_start_vars_section == -1)
			throw GreenTeaException("SyntaxErrorException",
					"non-var in property", _tokens_line1_arr[0]);
		_vars_section = array_slice(_tokens_line1_arr, _start_vars_section);
		_all_colons = find_all_token_at_level_0(token(":", "operator"),
				_vars_section);
		if (gt_sizeof(_all_colons) > 1) {
			throw GreenTeaException("SyntaxErrorException",
					"too many colons in property", _tokens_line1_arr[0]);
		} else if (gt_sizeof(_all_colons) == 1) {
			_two_sides = array_cut_by_pos(_vars_section, _all_colons);
			if (gt_sizeof(
					find_all_token_at_level_0(token(",", "operator"),
							_two_sides[0]))
					!= gt_sizeof(
							find_all_token_at_level_0(token(",", "operator"),
									_two_sides[1])))
				throw GreenTeaException("SyntaxErrorException",
						"colons count not balance in property",
						_tokens_line1_arr[0]);
			if (!(_list_vars = is_list(_two_sides[0], "var")).empty()) {
				for (auto [_key_rtt, _var] : _list_vars.valueArray) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", get_name(*_var));
					_tmp.push("modifiers", _modifiers);
					_return.push(_tmp);
				}
			} else {
				throw GreenTeaException("SyntaxErrorException",
						"not valid property declare", _tokens_line1_arr[0]);
			}
			// ======================
			_commas_pos = find_all_token_at_level_0(token(",", "operator"),
					_two_sides[1]);
			_values_arr = array_cut_by_pos(_two_sides[1], _commas_pos);
			for (auto [_i, _values_tokens] : _values_arr.valueArray) {
				_return[stol(_i)]["value"] = parse_expression(*_values_tokens);
			}
			// ======================
			return _return;
		} else {
			if (!(_list_vars = is_list(_vars_section, "var")).empty()) {
				for (auto [_key_rtt, _var] : _list_vars.valueArray) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", get_name(*_var));
					_tmp.push("modifiers", _modifiers);
					_return.push(_tmp);
				}
			} else
				throw GreenTeaException("SyntaxErrorException",
						"not valid property", _tokens_line1_arr[0]);
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
Mixed is_method_def(const tokens_line &_tokens_line1_arr) {
	arr_ls _modifiers;
	long _start_func_section;
	Mixed _return;
	token _token;
	tokens_line _func_section;
	_start_func_section = -1;
	for (auto [_i, _token_auto] : _tokens_line1_arr) {
		if (_token._1 == "modifier") {
			array_push(_modifiers, _token._0);
		} else {
			_start_func_section = _i;
			break;
		}
	}
	if (_start_func_section == -1)
		throw GreenTeaException("SyntaxErrorException",
				"non-function in method", _tokens_line1_arr.at(0));
	_func_section = array_slice(_tokens_line1_arr, _start_func_section);
	_return = is_function_def(_func_section);
	if (!_return)
		return false;
	if (!_modifiers.empty())
		_return[2] = _modifiers;
	else {
		Mixed _tmp = Mixed("public");
		Mixed _tmp1;
		_tmp1.push(_tmp);
		_return.push(2, _tmp1);
	}
	return _return;
}
Mixed parse_borrow(const tokens_line &_tokens_line1_arr_tl) {
	Mixed _tokens_line1_arr = Mixed(_tokens_line1_arr_tl);
	Mixed _return;
	if (_tokens_line1_arr[0] != token("borrow", "keyword"))
		return Mixed();
	long _len = gt_sizeof(_tokens_line1_arr);
	Mixed _last_token = _tokens_line1_arr[_len - 1];
	Mixed _semi_last_token = _tokens_line1_arr[_len - 2];
	if (get_type(_last_token) != "class")
		return Mixed();
	if (_semi_last_token != token("from", "keyword"))
		return Mixed();
	Mixed _mid_tokens = array_slice(_tokens_line1_arr, 1, _len - 3);
	_mid_tokens.resetKeys();
	arr_ll _commas_pos = find_all_token_at_level_0( { ",", "operator" },
			_mid_tokens);
	Mixed _cutted = array_cut_by_pos(_mid_tokens, _commas_pos);
	for (auto [_k, _v] : _cutted.valueArray) {
		Mixed _tokens = *_v;
		if (gt_sizeof(_tokens) > 1)
			throw GreenTeaException("SyntaxErrorException",
					"Invalid single method string", _tokens[0]);
		Mixed _token = get_1st_ele(_tokens);
		if (get_type(_token) != "function")
			throw GreenTeaException("SyntaxErrorException",
					"Invalid borrow type", _token);
		Mixed _tmp;
		_tmp.push("name", get_name(_token));
		_tmp.push("origin", get_name(_last_token));
		add_pos_to_mix(_tmp, _token);
		_return.push(_tmp);
	}
	_return.valueBool = true;
	return _return;
}
Mixed parse_class(tokens_line1_arr _class_def_block) {
	Mixed _return, _properties, _methods, _borrows;
	long _i;
	tokens_line1 _line;
	Mixed _result;
	Mixed _result1;
	_class_def_block = array_values(_class_def_block);
	for (_i = 0; _i < gt_sizeof(_class_def_block); _i++) {
		_line = _class_def_block[_i];
		_result = parse_property(_line._0);
		if (!(_result.valueArray.empty())) {
			for (auto [_key_rtt, _property] : _result.valueArray) {
				_properties.push(get_name(*_property), *_property);
			}
			continue;
		}
		_result = is_method_def(_line._0);
		if (_result) {
			_result1 = process_user_function_def(_i, _class_def_block, _result,
					true);
			_result1["type"] = "method";
			_result1.push("modifiers", _result[2]);
			add_pos_of_1st_token_to_mix(_result1, _class_def_block[0]._0);
			_methods.push((string) _result1["name"], _result1);
			continue;
		}
		_result = parse_borrow(_line._0);
		if (_result) {
			_borrows = array_merge(_borrows, _result);
			continue;
		}
		throw GreenTeaException("SyntaxErrorException", "wrong class internal",
				_line._0[0]);
	}
	_return.push("properties", _properties);
	_return.push("methods", _methods);
	_return.push("borrows", _borrows);
	_return.push("l", _borrows);
	_return.push("c", _borrows);
	return _return;
}
Mixed process_class_def(long &_line_num,
		const tokens_line1_arr &_tokens_line1_arr, const Mixed &_class_name) {
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _class_def_block;
	Mixed _tmp, _result;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_class_def_block = _getline_subblock.arr;
	_result = parse_class(_class_def_block);
	_result.push("type", "class_def");
	_result.push("name", _class_name["class"]);
	_result.push("extends", _class_name["extends"]);
	return _result;
}
bool class_exists(const string &_class_name) {
	return get_classes().contains(_class_name);
}
Mixed register_class(Mixed _new_class) {
	string _class_name = (string) _new_class["name"];
	log("register_class() start: " + _class_name + ": ");
	if (class_exists(_class_name)) {
		return Mixed();
		throw GreenTeaException("ClassExistsException",
				"class already exists: " + _class_name, _new_class);
	}
	_new_class.delete_e("name");
	_new_class.delete_e("type");
	Mixed _backup_properties = _new_class["properties"];
	Mixed _backup_methods = _new_class["methods"];
	Mixed _properties;
	Mixed _methods;
	//extend
//	if (_class_name == "^DivisionByZeroException") {
//		echo(1);
//	}
	if (isset(_new_class["extends"], 0)) {
		string _extend = _new_class["extends"][0];
		if (!isset(get_classes(), _extend))
			throw GreenTeaException("ClassNotFoundException",
					"invalid extend class: " + _extend, _new_class);
		Mixed _tmp_extend, _extends;
		Mixed _parent_class = get_classes()[_extend];
		_tmp_extend.push(_extend);
		_extends = array_merge(_tmp_extend, _parent_class["extends"]);
		_new_class.replace("extends", _extends);
		_properties = _parent_class["properties"];
		_methods = _parent_class["methods"];
	}
	//borrow
	for (auto [_k, _v] : _new_class["borrows"].valueArray) {
		Mixed _borrow = *_v;
		string _borrowed_method_name = (string) _borrow["name"];
		string _borrowed_method_origin = (string) _borrow["origin"];
		if (!isset(get_classes(), _borrowed_method_origin))
			throw GreenTeaException("ClassNotFoundException",
					"Cannot find original class to borrow", _borrow);
		if (!isset(get_classes()[_borrowed_method_origin]["methods"],
				_borrowed_method_name))
			throw GreenTeaException("MethodNotFoundException",
					"Cannot find method in original class to borrow", _borrow);
		Mixed _borrowed_method =
				get_classes()[_borrowed_method_origin]["methods"][_borrowed_method_name];
		_methods.update(_borrowed_method_name, _borrowed_method);
	}
	for (auto const& [_k, _v] : _backup_properties.valueArray) {
		_properties.update(_k, *_v);
	}
	for (auto const& [_k, _v] : _backup_methods.valueArray) {
		_methods.update(_k, *_v);
	}
	_new_class.replace("properties", _properties);
	_new_class.replace("methods", _methods);
	get_classes().push(_class_name, _new_class);
	return Mixed();
}
Mixed call_user_method(const string &_class_name, Mixed &_properties,
		const Mixed &_parsed) {
	Mixed _function = Mixed();
	Mixed _defined_func;
	arr_ls _params_str_arr;
	Mixed _tmp;
	Mixed _i;
//	Mixed _arg;
	string _params_str;
	Mixed _result, _return;
	unsigned long _count_required_params;
	Mixed _var;
	Mixed _value;
//	unsigned long _k = 0;
//	unsigned long _j = 0;
	Mixed _passed_vars_value;
	Mixed _passed_value;
// count required params;
	for (auto [_key_rtt, _defined_func_auto] : get_classes()[_class_name]["methods"].valueArray) {
		_defined_func = (Mixed) * _defined_func_auto;
		if (_defined_func["name"] == _parsed["name"]) {
			_function = _defined_func;
			break;
		}
	}
	if (gt_sizeof(_function) < 1) {
		throw GtLangFunctionNotFound(
				"user_method not found: " + _class_name + ": "
						+ (string) _parsed["name"] + "()");
	}
	if (gt_sizeof(_parsed["args"]) < _function["params"].valueNum) {
		throw GreenTeaException("FunctionParamsCountException",
				"method call can not have more params than function define",
				_parsed);
	}
	_count_required_params = 0;
	for (auto& [_key_rtt, _var] : _function["params"].valueArray) {
		if (isset(_var, "1"))
			break;
		_count_required_params++;
	}
	if (((unsigned long) gt_sizeof(_parsed["args"])) < _count_required_params)
		throw GreenTeaException("function call do not have enough params",
				_parsed);
// assign called params
	for (auto& [_k, _arg_auto] : _parsed["args"].valueArray) {
		Mixed _arg = (Mixed) * _arg_auto;
		if (_function["params"][_k]["type"] != "assignment") {
			_var = _function["params"][_k];
			assign_var(_var, gt_eval(_arg));
		} else {
			_var = _function["params"][_k]["left"];
			if (!isset(_parsed["args"], _k))
				_value = gt_eval(_function["params"][_k]["right"]);
			else if (isset(_parsed["args"], _k))
				_value = gt_eval(_parsed["args"][_k]);
			else
				throw GreenTeaException("FunctionParamsCountException",
						"Insufficient params", _parsed);
			assign_var(_var, _value);
		}
	}
// assign default un-called params
//	if ((long) _k < gt_sizeof(_function["params"])) {
//		for (_j = _k; (long) _j < gt_sizeof(_function["params"]); _j++) {
//			_passed_vars_value.push(_function["params"][_j][1]);
//		}
//	}
	for (auto const& [_j, _v] : _properties.valueArray) {
		Mixed _property = *_v;
		Mixed _var_name_token = Mixed(token(_j, "var"));
		assign_var(_var_name_token, _property);
	}
	for (auto const& [_j, _passed_value] : _passed_vars_value.valueArray) {
		assign_var(_function["params"][_j]["0"], _passed_value);
	}
	Mixed _method_return = gt_exec(_function["body"])._value;
	for (auto [_k, _v] : _properties.valueArray) {
		_properties.replace(_k, get_local_vars()[_k]);
	}
	_return.push("properties", _properties);
	_return.push("return", _method_return);
	return _return;
}
void assign_properties(Mixed *_object, const Mixed &_properties) {
	_object->replace("properties", _properties);
}
Mixed call_method(Mixed _parsed) {
	Mixed *_object = get_ref(_parsed["object"]);
	string _class_name = (string)(*(_object->get_e("class")));
	Mixed _properties = (*_object)["properties"];
	log(
			"call_method() " + _class_name + ": " + (string) _parsed["name"]
					+ "()");
	Mixed _params;
	Mixed _return;
	Mixed _local_vars_backup = get_local_vars();
	for (auto const& [_k, _v] : _parsed["args"].valueArray) {
		Mixed _sub_parsed = (Mixed) * _v;
		_params.push(gt_eval(_sub_parsed));
	}
//_parsed.del("args");
	_parsed.replace("args", _params);
	long _current_func_lv_bk = get_current_func_lv();
	add1_current_func_lv();
	try {
		_return = call_user_method(_class_name, _properties, _parsed);
		assign_properties(_object, _return["properties"]);
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
		return _return["return"];
	} catch (GtLangFunctionNotFound _e) {
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
	}
	throw GreenTeaException("MethodNotFoundException",
			"Cannot find the method anywhere", _parsed);
}
//======================================================================
Mixed gt_new(const Mixed &_input) {
	Mixed _return;
	log("gt_new(): ");
	if (!isset(_input, 0) || get_type(_input[0]) != "class")
		throw GreenTeaException("ClassNotFoundException",
				"Cannot find class for instantiation", _input[0]);
	string _class_name = get_name(_input[0]);
	if (!isset(get_classes(), _class_name))
		throw GreenTeaException("ClassNotFoundException",
				"Class does not exist for instantiation", _input[0]);
	Mixed _constructor_params;
	for (auto [_k, _v_auto] : _input.valueArray) {
		if (tl(_k) < 1)
			continue;
		Mixed _v = (Mixed) * _v_auto;
		_constructor_params.push(_v);
	}
	Mixed _class = get_classes()[_class_name];
	Mixed _properties = _class["properties"];
	Mixed _properties_with_values;
	long _i = 1;
	for (auto [_k, _v_auto] : _properties.valueArray) {
		Mixed _property = *_v_auto;
		if (isset(_input, _i))
			_properties_with_values.push(get_name(_property), _input[_i]);
		else
			_properties_with_values.push(get_name(_property), Mixed(0));
		_i++;
	}
	_return.push("class", _class_name);
	_return.push("properties", _properties_with_values);
	return _return;
}
#endif /* CORE_CLASSES_H_ */
