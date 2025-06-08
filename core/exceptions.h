/*
 * exceptions.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_EXCEPTIONS_H_
#define CORE_EXCEPTIONS_H_

Mixed is_catch_line(long _line, const tokens_line1_arr &_tokens_line1_arr) {
	Mixed _return;
	tokens_line _line_tokens;
	string __e;
	_line_tokens = remove_spaces_from_tokens_arr(
			_tokens_line1_arr.at(_line)._0);
	if (_line_tokens[0]._0 == l("catch") && _line_tokens[0]._1 == "keyword") {
		if (gt_sizeof(_line_tokens) == 1) {
			_return.push("catch");
			_return.push("^Exception");
			_return.push("$_e");
			return _return;
		} else if (gt_sizeof(_line_tokens) == 2
				&& _line_tokens[1]._1 == "class") {
			_return.push("catch");
			_return.push(_line_tokens[1]._0);
			_return.push("$_e");
			return _return;
		} else if (gt_sizeof(_line_tokens) == 3 && _line_tokens[1]._1 == "class"
				&& _line_tokens[2]._1 == "var") {
			_return.push("catch");
			_return.push(_line_tokens[1]._0);
			_return.push(_line_tokens[2]._0);
			return _return;
		} else
			throw GreenTeaException("SyntaxErrorException", "invalid catch",
					_line_tokens[0]);
	}
	return Mixed();
}
bool is_finally_line(long _line, const tokens_line1_arr &_tokens_line1_arr) {
	tokens_line _line_tokens;
	_line_tokens = remove_spaces_from_tokens_arr(
			_tokens_line1_arr.at(_line)._0);
	if (_line_tokens[0]._0 == l("finally") && _line_tokens[0]._1 == "keyword") {
		if (gt_sizeof(_line_tokens) == 1)
			return true;
		else
			throw GreenTeaException("SyntaxErrorException", "invalid finally",
					_line_tokens[0]);
	}
	return false;
}
Mixed process_try(long &_line, const tokens_line1_arr &_tokens_line1_arr) {
	Mixed _return;
	long _tabs_lv;
	Mixed _blocks_type, _tmp, _tmp1;
	long _block_num;
	map<long, tokens_line1_arr> _blocks;
	long _i;
	Mixed _catch_line_parsed;
	tokens_line _catch_line;
	Mixed _catches;
	Mixed _gt_try;
	long _try_count;
	Mixed _gt_finally;
	long _finally_count;
	_tabs_lv = _tokens_line1_arr.at(_line)._1;
	_tmp.push("try");
	_blocks_type.push(_tmp);
	_block_num = 0;
	_tmp = Mixed();
	for (_i = _line + 1; _i < (long) gt_sizeof(_tokens_line1_arr); _i++) {
		if (_tokens_line1_arr.at(_i)._1 < _tabs_lv)
			break;
		if (_tokens_line1_arr.at(_i)._1 == _tabs_lv && !(_catch_line_parsed =
				is_catch_line(_i, _tokens_line1_arr)).empty()) {
// _catch_line = remove_all_spaces ( _tokens_arr [_i] ._0 );
			_block_num++;
			add_pos_of_1st_token_to_mix(_catch_line_parsed,
					_tokens_line1_arr.at(_line)._0);
			_blocks_type.push(_catch_line_parsed);
		} else if (_tokens_line1_arr.at(_i)._1 == _tabs_lv
				&& is_finally_line(_i, _tokens_line1_arr)) {
			_block_num++;
			_blocks[_block_num] = { };
			_tmp = Mixed();
			_tmp.push("finally");
			add_pos_of_1st_token_to_mix(_tmp, _tokens_line1_arr.at(_line)._0);
			_blocks_type.push(_tmp);
		} else if (_tokens_line1_arr.at(_i)._1 == _tabs_lv) {
			break;
		} else if (_tokens_line1_arr.at(_i)._1 > _tabs_lv) {
			if (!isset(_blocks, _block_num))
				_blocks[_block_num] = { };
			array_push(_blocks[_block_num], _tokens_line1_arr.at(_i));
		}
	}
	_line = _i - 1;
	_catches = Mixed();
	_gt_try = Mixed();
	_try_count = 0;
	_gt_finally = Mixed();
	_finally_count = 0;
	for (_i = 0; _i < (long) gt_sizeof(_blocks_type); _i++) {
		if (_blocks_type[_i][0] == "catch") {
			_tmp.push("exception_class", _blocks_type[_i][1]);
			_tmp.push("catch_var", _blocks_type[_i][2]);
			_tmp.push("body", structurelize(_blocks[_i]));
			_catches.push(_tmp);
		} else if (_blocks_type[_i][0] == "try") {
			_try_count++;
//			if (_try_count > 1)
//				throw GtlangException("SyntaxErrorException",
//						"multiple try blocks");
			_gt_try = structurelize(_blocks[_i]);
		} else if (_blocks_type[_i][0] == "finally") {
			_finally_count++;
			if (_finally_count > 1)
				throw GreenTeaException("SyntaxErrorException",
						"multiple finally blocks", _blocks_type[_i]);
			_gt_finally = structurelize(_blocks[_i]);
		}
	}
	if (gt_sizeof(_catches) < 1) {
		token _tmp_t = get_last_ele(_tokens_line1_arr.at(_line)._0);
		throw GreenTeaException("SyntaxErrorException", "try but no catch",
				_tmp_t);
	}
	_return.push("type", "try");
	_return.push("body", _gt_try);
	_return.push("catch", _catches);
	_return.push("finally", _gt_finally);
	return _return;
}
Mixed process_defcat(long &_line, const tokens_line1_arr &_tokens_line1_arr) {
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
	_tabs_lv = _tokens_line1_arr.at(_line)._1;
	_is_in_deffin = false;
	for (_i = _line + 1; _i < (long) gt_sizeof(_tokens_line1_arr); _i++) {
		if (_tokens_line1_arr.at(_i)._1 < _tabs_lv) {
			break;
		} else if (_tokens_line1_arr.at(_i)._1 == _tabs_lv
				&& _tokens_line1_arr.at(_i)._0.at(0)._0 == "deffin") {
			_is_in_deffin = true;
		} else if (_tokens_line1_arr.at(_i)._1 == _tabs_lv
				&& _tokens_line1_arr.at(_i)._0.at(0)._0 != "deffin") {
			break;
		} else if (_tokens_line1_arr.at(_i)._1 > _tabs_lv) {
			if (_is_in_deffin)
				array_push(_deffin, _tokens_line1_arr.at(_i));
			else
				array_push(_defcat, _tokens_line1_arr.at(_i));
		}
	}
	if (_defcat.empty())
		return false;
	_line = _i;
	_defcat_blocks = { };
	_defcat_blocks_i = -1;
	_defcat_exception_classes = { };
	rtrim_all_lines_arr(_defcat);
	for (_i = 0; _i < (long) gt_sizeof(_defcat); _i++) {
		if (_defcat[_i]._1 == (_tabs_lv + 1))
			if (gt_sizeof(_defcat[0]._0) == 1
					&& _defcat[0]._0[0]._1 == "class") {
				if (in_array(_defcat[_i]._0[0]._0, _defcat_exception_classes))
					throw GreenTeaException("SyntaxErrorException",
							"This class has already been catched",
							get_1st_ele(_defcat[_i]._0));
				array_push(_defcat_exception_classes, _defcat[_i]._0[0]._0);
				_defcat_blocks_i++;
			} else
				throw GreenTeaException("SyntaxErrorException",
						"Invalid defcat exception class",
						get_1st_ele(_defcat[0]._0));
		else if (_defcat[_i]._1 > (_tabs_lv + 1)) {
			if (!isset(_defcat_blocks, _defcat_blocks_i))
				_defcat_blocks[_defcat_blocks_i] = { };
			array_push(_defcat_blocks[_defcat_blocks_i], _defcat[_i]);
		}
	}
//	for (auto [_k, _v] : _defcat_exception_classes) {
//		if (in_array(_v, _tmp_classes))
//			throw GtlangException("SyntaxErrorException",
//					"Non unique catch in defcat",
//					get_1st_ele(get_1st_ele(_defcat_blocks[_k])._0));
//		array_push(_tmp_classes, _v);
//	}
//
	_defcat_rs = Mixed();
	for (auto [_i, _defcat_block] : _defcat_blocks) {
		_defcat_blocks1[_i] = structurelize(_defcat_block);
		_tmp.push("exception_class", _defcat_exception_classes[_i]);
		_tmp.push("catch_var", "$_e");
		_tmp.push("body", _defcat_blocks1[_i]);
		_defcat_rs.push(_tmp);
	}
	_return.push("type", "defcat");
	_return.push("body", _defcat_rs);
	_return.push("deffin", structurelize(_deffin));
	return _return;
}
void init_a_exception_class(const string &_class_name, const string &_parent) {
	Mixed _tmp_class;
	_tmp_class.push("type", "class");
	_tmp_class.push("name", "^" + _class_name);
	Mixed _tmp_parent;
	if (_parent != "")
		_tmp_parent.push("^" + _parent);
	Mixed _tmp_property;
	_tmp_class.push("extends", _tmp_parent);
	_tmp_class.push("borrows", Mixed());
	_tmp_property.push("$msg");
	_tmp_class.push("properties", _tmp_property);
	_tmp_class.push("methods", Mixed());
	register_class(_tmp_class);
}
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
						"MysqlException" }, { 1, "RuntimeErrorException" } } },
				{ 24,
						{ { 0, "DivisionByZeroException" },
								{ 1, "MathException" } } }, { 25, { { 0,
						"NegativeSqrtException" }, { 1, "MathException" } } }, {
						26, { { 0, "InvalidLogarithmException" }, { 1,
								"MathException" } } }, { 27, { { 0,
						"MathOverflowException" }, { 1, "MathException" } } }, {
						28, { { 0, "FileNotFoundException" }, { 1,
								"IOErrorException" } } }, { 29,
						{ { 0, "PermissionDeniedException" }, { 1,
								"IOErrorException" } } }, { 30,
						{ { 0, "ThreadNotFoundException" }, { 1,
								"ThreadingException" } } }, { 31,
						{ { 0, "ThreadTimeoutException" }, { 1,
								"ThreadingException" } } }, { 32, { { 0,
						"ThreadExecutionException" },
						{ 1, "ThreadingException" } } } };

void init_exception_classes() {
	for (auto [_k, _v] : __default_exception_classes) {
		init_a_exception_class(_v[0], _v[1]);
	}
}
#endif /* CORE_EXCEPTIONS_H_ */
