/*
 * exec.h
 *
 *  Created on: May 25, 2025
 *      Author: t
 */

#ifndef CORE_EXEC_H_
#define CORE_EXEC_H_

Mixed gt_eval_body(Mixed &_parsed) {
	_parsed.resetKeys();
	Mixed _tmp;
	_tmp.push("type", "expr");
	_tmp.push("body", _parsed);
	return gt_eval(_tmp);
}
Mixed* get_ref(const Mixed &name, const Mixed &key);
Mixed* get_ref(const Mixed &name);
Mixed assign_var(const Mixed &_var, const Mixed &_value) {
	log("assign_var(): " + ((string) _var["name"]) + ": " + _value.valueStr);
//	print_r(_value);
	string _var_name;
	Mixed _return;
	if (_var["type"] == "var" && _var["name"] != "answer_var") {
		_var_name = _var["name"].valueStr;
		if (get_current_func_lv() == 0) {
			_return = (_value);
			set_global_var_i(_var_name, _value);
			set_answer_var(_value);
			return _return;
		} else {
			_return = (_value);
			set_local_var_i(_var_name, _value);
			return _return;
		}
	} else if (_var["type"] == "var_global") {
		_var_name = _var["name"].valueStr;
		if (isset(get_global_vars(), (string) _var_name)) {
			_return = (_value);
			set_global_var_i(_var_name, _value);
			set_answer_var(_value);
			return _return;
		} else
			throw GreenTeaException("UndefinedVariableException",
					"no global var", _var);
	} else if (_var["type"] == "complex_value") {
		Mixed *_ref = get_ref(_var);
		*_ref = _value;
		set_answer_var(_value);
		return _return;
	} else if (_var["type"] == "var" && _var["name"] == "answer_var") {
		set_answer_var(_value);
		return _return;
	}
	throw GreenTeaException("SyntaxErrorException",
			"not valid left side of assignment", _var);
}
Mixed assign_array(const Mixed &_input) {
	Mixed _left = _input["left"];
	Mixed _right = _input["right"]["body"][0]["body"];
	Mixed _array;
//	print_r(_right);
	for (auto const& [_k, _v] : _right.valueArray) {
//		if (isset((*_v), "key")) {
		Mixed _right_item = (Mixed) * _v;
		arr_ll _right_arrow_pos = find_all_token_at_level_0(
				{ "=>", "operator" }, _right_item["body"]);
//		if (gt_sizeof(_right_arrow_pos) > 1) {
//			throw GtlangException("SyntaxErrorException",
//					"more than 1 arrow operators", _input);
//		} else
		if (gt_sizeof(_right_arrow_pos) == 1) {
			Mixed _cutted = array_cut_by_pos(_right_item["body"],
					_right_arrow_pos);
			Mixed _before_arrow = gt_eval_body(_cutted[0]);
			Mixed _after_arrow = gt_eval_body(_cutted[1]);
			_array.push(_before_arrow.valueStr, _after_arrow);
		} else {
			Mixed _element = gt_eval(_right_item);
			_array.push(_k, _element);
		}
		//print_r(_element);
//		}
	}
	string _var_type = get_type(_left);
	if (_var_type == "var" && get_current_func_lv() > 0) {
		set_local_var_i(_left["name"].valueStr, _array);
	} else if (_var_type == "global_var"
			|| (get_current_func_lv() == 0 && _var_type == "var")) {
		set_global_var_i(_left["name"].valueStr, _array);
	} else if (_var_type == "complex_value" && get_current_func_lv() >= 0) {
		Mixed *_ref = get_ref(_left);
		_ref->unset_r();
		*_ref = _array;
	} else {
		throw InternalException("__current_func_lv < 0");
	}
	return _array;
}
Mixed* get_ref(const Mixed &_var_token) {
	string _var_name = get_name(_var_token);
	string _var_type = get_type(_var_token);
	log("get_ref() start: " + _var_name + ": ");
	Mixed _var;
	try {
		if (_var_type == "var" && get_current_func_lv() > 0) {
			if (is_main_thread())
				return __local_vars.get_ref(_var_name);
			else {
				string _id = get_thread_id_str();
				return __g.get_ref(_id)->get_ref("local_var")->get_ref(
						_var_name);
			}
		} else if (_var_type == "global_var"
				|| (get_current_func_lv() == 0 && _var_type == "var")) {
			if (is_main_thread())
				return __global_vars.get_ref(_var_name);
			else {
				string _id = get_thread_id_str();
				return __g.get_ref(_id)->get_ref("global_var")->get_ref(
						_var_name);
			}
		} else if (_var_type == "complex_value") {
			Mixed *_ref = get_ref(Mixed(token(_var_name, "var")));
			for (auto const& [_k, _v] : _var_token["indexes"].valueArray) {
				Mixed _actual_index = (Mixed) * _v;
				string _actual_index_str = (string) gt_eval(_actual_index);
				if (get_type(*_v) == "null") {
					_ref->push(Mixed());
					_ref = _ref->get_ref(ts(_ref->index - 1));
					continue;
				}
				try {
					_ref = _ref->get_ref(_actual_index_str);
				} catch (InternalException _e) {
					_ref->push(_actual_index_str, Mixed());
					_ref = _ref->get_ref(_actual_index_str);
				}
			}
			return _ref;
		}
	} catch (InternalException _e) {
		throw GreenTeaException("UndefinedVariableException",
				"Cannot find var ref", _var_token);
	}
	throw GreenTeaException("UndefinedVariableException", "Cannot find var ref",
			_var_token);
}
Mixed* get_ref(const Mixed &_var_token, const Mixed &key) {
	Mixed _tmp, _tmp1;
	_tmp.push("name", get_name(_var_token));
	_tmp.push("type", "complex_value");
	_tmp1.push(0, key.valueStr);
	_tmp.push("indexed", _tmp1);
	return get_ref(_tmp);
}
Mixed call_builtin_function(const Mixed &_parsed);
Mixed get_value(const Mixed &_value) {
	log("get_value() start: " + ((string) _value) + ": ");
	string _var_name;
	Mixed _return;
	Mixed _result;
	if (_value["type"] == "var") {
		if (_value["name"] == "answer_var")
			return get_answer_var();
		_var_name = _value["name"].valueStr;
		if (get_current_func_lv() == 0) {
			if (!isset(get_global_vars(), _var_name))
				throw GreenTeaException("UndefinedVariableException",
						"cannot find global var", _value);
			_return = get_global_vars()[_var_name];
			return _return;
		}
//		else if (get_current_func_lv() < 0)
//			get_current_func_lv() = 0;
		else {
			if (!isset(get_local_vars(), _var_name))
				throw GreenTeaException("UndefinedVariableException",
						"cannot find local var", _value);
			_return = get_local_vars()[_var_name];
			return _return;
		}
	} else if (_value["type"] == "complex_value") {
		_result = gt_eval(_value["name"]);
		return _result[gt_eval(_value["key"]).valueStr];
	}
	return Mixed();
}
Mixed find_operator_in_expr(Mixed _expr) {
//	long _k;
	Mixed _obj;
	for (auto [_k, _obj_auto] : _expr["body"].valueArray) {
		Mixed _obj = (Mixed) * _obj_auto;
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
Mixed gt_do(const string &_opt, const token &_params, long _opt_pos) {
	return gt_do(_opt, Mixed(_params), _opt_pos);
}
Mixed get_var_global_value(const Mixed &_parsed) {
	return get_global_vars()[_parsed["name"].valueStr];
}
//Mixed get_var_local_value(Mixed _parsed) {
//	return __local_vars[_parsed["name"].valueStr];
//}
//Mixed replace_get_ele_with_complex_value(Mixed _expr) {
////long _k;
//	Mixed _v;
//	if (!php_is_array(_expr))
//		return _expr;
//	if (isset(_expr["body"], "1") && _expr["body"]["1"]["name"] == "get_ele"
//			&& _expr["body"]["1"]["type"] == "operator"
//			&& (_expr["body"].getLen()) == 3) {
//		_expr["type"] = "complex_value";
//		_expr["name"] = _expr["body"]["0"];
//		_expr["key"] = _expr["body"]["2"];
//	}
//// if (isset ( _expr ["body"] ))
//	for (auto [_k, _v] : _expr.valueArray) {
//		_expr[_k] = replace_get_ele_with_complex_value((Mixed) _v);
//	}
//	return _expr;
//}
Mixed eval(const string &_content) {
	tokens_line1_arr _tokens = tokenize(_content);
	Mixed _structure = structurelize(_tokens);
	return gt_exec(_structure)._value;
}
Mixed create_array_var(const Mixed &_parsed) {
	Mixed _return = Mixed();
	Mixed _element;
	Mixed _parsed_body = _parsed["body"];
	string _key = "-1";
	for (auto [_k, _element_auto] : _parsed_body.valueArray) {
		_element = (Mixed) * _element_auto;
		_key = ts(tl(_key) + 1);
		if (isset(_element, "key"))
			_key = gt_eval(_element["key"]).valueStr;
		_return.push(_key, gt_eval(_element));
	}
	return _return;
}
Mixed gt_include(const Mixed &_input) {
	if (get_current_func_lv() > 0)
		throw GtlangInnerFunctionException("SyntaxErrorException",
				"cannot call include() in function.");
	string _filename = (string) _input[0];
	arr_ls _args = { { 0, _filename } };
	int _rs = main_exec(1, _args);
	return Mixed(_rs);;
}
#endif /* CORE_EXEC_H_ */
