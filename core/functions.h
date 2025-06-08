/*
 * functions.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_FUNCTIONS_H_
#define CORE_FUNCTIONS_H_

bool is_method_lv0(const Mixed &_tokens_line1_arr, long _func_name_pos) {
	return (get_name(
			find_previous_non_spaces_token(_tokens_line1_arr, _func_name_pos))
			== ">>");
}
Mixed get_two_sides_of_method_call(const Mixed &_tokens_line1_arr,
		long _method_call_pos) {
	Mixed _return;
	_return.push(array_slice(_tokens_line1_arr, 0, _method_call_pos - 1));
	_return.push(array_slice(_tokens_line1_arr, _method_call_pos + 2));
	return _return;
}
Mixed get_function_and_params_lv0(const Mixed &_tokens_line1_arr) {
	Mixed _return;
	arr_ll _all_func_names_pos;
	Mixed _two_sides;
	Mixed _tmp_array, _tmp_array1;
	arr_ll _left_comma_pos;
	arr_ll _right_comma_pos;
	tokens_line _v;
	_return = Mixed();
	//_tokens_line1_arr.resetKeys();
	_all_func_names_pos = find_all_token_at_level0_by_type("function",
			_tokens_line1_arr);
	if (gt_sizeof(_all_func_names_pos) != 1)
		return Mixed();
	// fix (@func 1)
//	long _pos = get_1st_ele(_all_func_names_pos);
//	if (isset(_tokens_line1_arr[_pos], "args"))
//		return Mixed();
	//==============
	long _func_name_pos = _all_func_names_pos[0];
	if (is_method_lv0(_tokens_line1_arr, _func_name_pos))
		return Mixed();
	Mixed _m = Mixed();
//	_m.type = "a";
	_return.push("name", get_name(_tokens_line1_arr[_func_name_pos]));
	_return.push("params", _m);
	_two_sides = array_cut_by_pos(_tokens_line1_arr, _all_func_names_pos);
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
			_return["params"].push(parse_expression(_v));
	}
//	print_r(_return);
	return _return;
}
Mixed is_function_def(const tokens_line &_tokens) {
	token _last_token = get_last_ele(_tokens);
	if (_tokens.at(0)._1 != "function" || _last_token._0 != ":"
			|| _last_token._1 != "assignment")
		return Mixed(false);
	Mixed _return;
	tokens_line _function_name_params = _tokens;
	arr_ll _function_names_pos = find_all_token_type_at_level_0("function",
			_function_name_params);
	if (gt_sizeof(_function_names_pos) != 1)
		throw GreenTeaException("SyntaxErrorException",
				"Invalid function token count.", get_1st_ele(_tokens));
	long _function_name_pos = _function_names_pos[0];
	string _function_name = get_name(_function_name_params[_function_name_pos]);
	tokens_line _params = _function_name_params;
	arr_remove(_params, _function_name_pos);
	arr_remove(_params, gt_sizeof(_params) - 1);
	arr_ll _commas_pos = find_all_token_at_level_0(token(",", "operator"),
			_params);
	tokens_line_arr _params_arr = array_cut_by_pos(_params, _commas_pos);
	Mixed _list_of_params;
	for (auto [_k, _v] : _params_arr) {
		if (gt_sizeof(_v) < 1)
			continue;
		else if (gt_sizeof(_v) == 1) {
			reset_keys(_v);
			_list_of_params.push(_v[0]);
		} else {
			_list_of_params.push(process_assignment(_v));
		}
	}
	_return.push("name", _function_name);
	_return.push("params", _list_of_params);
	_return.valueBool = true;
	return _return;
}
Mixed process_user_function_def(long &_line_num,
		const tokens_line1_arr &_tokens_line1_arr, const Mixed &_func_declare,
		bool _is_method = false) {
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _func_def_block;
	Mixed _return, _tmp;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_func_def_block = _getline_subblock.arr;
	if (!_is_method) {
		_tmp.push("type", "func_def");
		_tmp.push("name", _func_declare["name"]);
		_tmp.push("params", _func_declare["params"]);
		_tmp.push("body", structurelize(_func_def_block));
		// __funcs.push(_tmp);
		return _tmp;
	} else {
		_return.push("type", "func_def");
		_return.push("name", _func_declare["name"]);
		_return.push("params", _func_declare["params"]);
		_return.push("body", structurelize(_func_def_block));
		return _return;
	}
}
long register_function(const Mixed &_parsed) {
	log("register_function() start");
	get_functions().push(_parsed);
	return get_functions().index;
}
Mixed call_builtin_function(const Mixed &_parsed) {
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
//  count required params;
	string _function_name = _parsed["name"].get_string();
	for (auto [_key_rtt, _defined_func_auto] : __b_funcs) {
		_defined_func = (GTBuiltinFunction) _defined_func_auto;
		if (_key_rtt == _function_name) {
			try {
				_result = (*_defined_func)(_parsed["args"]);
			} catch (InternalException *_e) {
				echo("Error : " + _e->msg);
				exit(0);
			} catch (GtlangInnerFunctionException _e) {
				GreenTeaException _e1 = GreenTeaException(
						substr(_e.obj["class"], 1),
						_e.obj["properties"]["$msg"], _parsed);
				throw _e1;
			}
			//_result.valueBool = true;
			return _result;
		}
	}
	throw GtLangFunctionNotFound(
			"builtin_function not found: " + (string) _parsed["name"]);
}
Mixed call_user_function(const Mixed &_parsed) {
	Mixed _function = Mixed();
	Mixed _defined_func;
	arr_ls _params_str_arr;
	Mixed _tmp;
	Mixed _i;
//	Mixed _arg;
	string _params_str;
	Mixed _result;
	unsigned long _count_required_params;
	Mixed _var;
	Mixed _value;
//	unsigned long _k = 0;
//	unsigned long _j = 0;
	Mixed _passed_vars_value;
	Mixed _passed_value;
// count required params;
	for (auto [_key_rtt, _defined_func_auto] : get_functions().valueArray) {
		_defined_func = (Mixed) * _defined_func_auto;
		if (_defined_func["name"] == _parsed["name"]) {
			_function = _defined_func;
			break;
		}
	}
	if (gt_sizeof(_function) < 1) {
		throw GtLangFunctionNotFound(
				"user_function not found: " + (string) _parsed["name"]);
	}
	if (gt_sizeof(_parsed["args"]) < _function["params"].valueNum) {
		throw GreenTeaException("FunctionParamsCountException",
				"function call should not have more params than function define",
				_parsed);
	}
	_count_required_params = 0;
	for (auto& [_key_rtt, _var] : _function["params"].valueArray) {
		if (isset(_var, "1"))
			break;
		_count_required_params++;
	}
	if (((unsigned long) gt_sizeof(_parsed["args"])) < _count_required_params)
		throw GreenTeaException("FunctionParamsCountException",
				"function call do not have enough params", _parsed);
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
	for (auto const& [_j, _passed_value] : _passed_vars_value.valueArray) {
		assign_var(_function["params"][_j]["0"], _passed_value);
	}
	Mixed _return = gt_exec(_function["body"])._value;
	return _return;
}
Mixed call_function(Mixed _parsed) {
	log("call_function() " + _parsed["name"].valueStr);
	Mixed _params;
	Mixed _return;
	Mixed _local_vars_backup = get_local_vars();
	for (auto const& [_k, _v] : _parsed["args"].valueArray) {
		Mixed _sub_parsed = (Mixed) * _v;
		_params.push(gt_eval(_sub_parsed));
	}
// _parsed.del("args");
	_parsed.replace("args", _params);
	long _current_func_lv_bk = get_current_func_lv();
	add1_current_func_lv();
	try {
		_return = call_builtin_function(_parsed);
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
		return _return;
	} catch (GtLangFunctionNotFound _e) {
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
	}
	_current_func_lv_bk = get_current_func_lv();
	add1_current_func_lv();
	try {
		_return = call_user_function(_parsed);
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
		return _return;
	} catch (GtLangFunctionNotFound _e) {
		set_local_vars(_local_vars_backup);
		set_current_func_lv(_current_func_lv_bk);
	}
	throw GreenTeaException("FunctionNotFoundException",
			"Cannot find the function anywhere", _parsed);
}
#endif /* CORE_FUNCTIONS_H_ */
