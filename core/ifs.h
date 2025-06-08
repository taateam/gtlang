/*
 * ifs.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_IFS_H_
#define CORE_IFS_H_

Mixed process_if(long &_line_num, const tokens_line1_arr &_tokens_line1_arr) {
	tokens_line _if_line;
	getline_subblock_t _getline_subblock;
	map<long, tokens_line1_arr> _if_blocks;
	map<long, Mixed> _if_conditions;
	tokens_line1_arr _else_block;
	Mixed _return, _tmp;

	_if_line = _tokens_line1_arr.at(_line_num)._0;
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	array_push(_if_blocks, _getline_subblock.arr);
	array_push(_if_conditions, parse_expression(array_slice(_if_line, 1)));
	while (true) {
		if (isset(_tokens_line1_arr, _line_num + 1)
				&& _tokens_line1_arr.at(_line_num + 1)._0.at(0)._0 == l("elif")
				&& _tokens_line1_arr.at(_line_num + 1)._0.at(0)._1
						== "keyword") {
			_line_num++;

			_if_line = _tokens_line1_arr.at(_line_num + 1)._0;
			_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
			_line_num += _getline_subblock.i;
			array_push(_if_blocks, _getline_subblock.arr);
			array_push(_if_conditions,
					parse_expression(array_slice(_if_line, 1)));
		} else {
			break;
		}
	}
	_return.push("type", "ifs");
	_return.push("ifs", Mixed());
	if (isset(_tokens_line1_arr, _line_num + 1)
			&& _tokens_line1_arr.at(_line_num + 1)._0.at(0)._0 == l("else")
			&& _tokens_line1_arr.at(_line_num + 1)._0.at(0)._1 == "keyword"
			&& gt_sizeof(_tokens_line1_arr.at(_line_num + 1)._0) == 1) {
		_line_num++;
		_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
		_line_num += _getline_subblock.i;
		_else_block = _getline_subblock.arr;
	} else {
		_else_block = { };
	}
	for (long k = 0; k < gt_sizeof(_if_blocks); k++) {
		_tmp = Mixed();
		_tmp.push("condition", _if_conditions[k]);
		_tmp.push("body", structurelize(_if_blocks[k]));
		_return["ifs"].push(to_string(k), _tmp);
	}
// cout << 5;
	_return.push("else", structurelize(_else_block));
	return _return;
}
bool is_inline_conditional_expr(const Mixed &_tokens_line) {
	arr_ll _pos_of_all_question_mark = find_all_token_at_level_0( { "?",
			"operator" }, _tokens_line);
	if (gt_sizeof(_pos_of_all_question_mark) == 1)
		return true;
	return false;
}
Mixed parse_inline_conditional_expr(const Mixed &_tokens_outside_brackets) {
	Mixed _condition, _value_if_true, _value_if_false, _return;
	_condition.push("type", "expr");
	_condition.push("body", Mixed());
	_value_if_true.push("type", "expr");
	_value_if_true.push("body", Mixed());
	_value_if_false.push("type", "expr");
	_value_if_false.push("body", Mixed());
	//_tokens_outside_brackets.resetKeys()// resetted outside;
	long _i = 0;
	for (; _i < gt_sizeof(_tokens_outside_brackets); _i++) {
		Mixed _v = _tokens_outside_brackets[_i];
		if (_v == token("?", "operator")) {
			break;
		} else {
			_condition["body"].push(_v);
		}
	}
	for (_i++; _i < gt_sizeof(_tokens_outside_brackets); _i++) {
		Mixed _v = _tokens_outside_brackets[_i];
		if (_v == token("?", "operator")) {
			throw GreenTeaException("SyntaxErrorException",
					"invalid operator ? ", _v);
		} else if (_v == token("::", "operator")) {
			break;
		} else {
			_value_if_true["body"].push(_v);
		}
	}
	for (_i++; _i < gt_sizeof(_tokens_outside_brackets); _i++) {
		Mixed _v = _tokens_outside_brackets[_i];
		if (_v == token("?", "operator")) {
			throw GreenTeaException("SyntaxErrorException",
					"invalid operator ? ", _v);
		} else if (_v == token("::", "operator")) {
			throw GreenTeaException("SyntaxErrorException",
					"invalid operator :: ", _v);
		} else {
			_value_if_false["body"].push(_v);
		}
	}
	_return.push("type", "inline_if");
	_return.push("condition", _condition);
	_return.push("value_if_true", _value_if_true);
	_return.push("value_if_false", _value_if_false);
	add_pos_of_1st_token_to_mix(_return, _tokens_outside_brackets);
	return _return;
}
#endif /* CORE_IFS_H_ */
