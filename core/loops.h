/*
 * loops.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_LOOPS_H_
#define CORE_LOOPS_H_

Mixed for_parse(tokens_line _for_tokens) {
//	long __time;
	Mixed _return;
//	echo("");
	if (isset(_for_tokens, 2) && _for_tokens.at(2)._1 == "number"
			&& isset(_for_tokens, 4) && _for_tokens.at(4)._1 == "var"
			&& array_search(token(",", "operator"), _for_tokens) == -1) {
		_return.push(tokenize(_for_tokens.at(4)._0 + ":0").at(0)._0);
		_return.push(
				tokenize(_for_tokens.at(4)._0 + "<" + _for_tokens.at(2)._0).at(
						0)._0);
		_return.push(tokenize(_for_tokens.at(4)._0 + "++").at(0)._0);
		return _return;
	} else if (isset(_for_tokens, 4) && _for_tokens.at(2)._1 == "number"
			&& _for_tokens.at(4)._0 == l("times")
			&& _for_tokens.at(4)._1 == "keyword") {
		_return.push(tokenize("$_time:0")[0]._0);
		_return.push(tokenize("$_time<" + _for_tokens.at(2)._0).at(0)._0);
		_return.push(tokenize("$_time++")[0]._0);
		return _return;
	}
	array_shift(_for_tokens);
	_return = explode_tokens(token(",", "operator"), _for_tokens);
	if (gt_sizeof(_return) != 3)
		throw GreenTeaException("SyntaxErrorException", "invalid for line",
				get_1st_ele(_for_tokens));
	return _return;
}
Mixed process_foreach(long &_line_num,
		const tokens_line1_arr &_tokens_line1_arr) {
	Mixed _return, _arr, _k, _v;
	Mixed _foreach_line = trim_tokens_line_once(
			_tokens_line1_arr.at(_line_num)._0);
	array_shift_no_return(_foreach_line);
	getline_subblock_t _getline_subblock = getline_subblock(_tokens_line1_arr,
			_line_num);
	_line_num += _getline_subblock.i;
	//========================================================
	_return.push("type", "foreach");
	_foreach_line.resetKeys();
	arr_ll _all_at_pos = find_all_token_at_level_0(token("as", "keyword"),
			_foreach_line);
	if (gt_sizeof(_all_at_pos) > 1)
		throw GreenTeaException("SyntaxErrorException",
				"Invalid foreach 1st line", get_1st_ele(_tokens_line1_arr)._0);
	_k = Mixed(token("$_key", "var"));
	_v = Mixed(token("$_value", "var"));
	if (gt_sizeof(_all_at_pos) == 1) {
		Mixed _2_sides = array_cut_by_pos(_foreach_line, _all_at_pos);
		Mixed _before = _2_sides[0];
		Mixed _after = _2_sides[1];
		_arr = parse_expression(_before);
		_after.resetKeys();
		for (auto [_k, _v_c] : _after.valueArray) {
			Mixed _v = *_v_c;
			if (!odd(tl(_k)) && get_type(_v) != "spaces")
				throw GreenTeaException("SyntaxErrorException",
						"Invalid foreach 1st line", _v);
		}
		if (gt_sizeof(_after) > 2 || gt_sizeof(_after) < 1) {
			GreenTeaException("SyntaxErrorException",
					"Invalid foreach 1st line after at",
					get_1st_ele(_foreach_line));
		}
		if (gt_sizeof(_after) == 2) {
			_v = _after[1];
			if (!is_a_var(_v))
				throw GreenTeaException("SyntaxErrorException", "Not a var",
						_v);
		} else if (gt_sizeof(_after) == 4) {
			_k = _after[1];
			if (!is_a_var(_k))
				throw GreenTeaException("SyntaxErrorException", "Not a var",
						_k);
			_v = _after[3];
			if (!is_a_var(_v))
				throw GreenTeaException("SyntaxErrorException", "Not a var",
						_v);
		} else
			throw GreenTeaException("SyntaxErrorException",
					"Invalid foreach 1st line", get_1st_ele(_foreach_line));
	} else {
		_arr = parse_expression(_foreach_line);
	}
	_return.push("arr", _arr);
	_return.push("k", _k);
	_return.push("v", _v);
	_return.push("body", structurelize(_getline_subblock.arr));
	add_pos_of_1st_token_to_mix(_return, get_1st_ele(_tokens_line1_arr)._0);
	return _return;
}
Mixed process_for(long &_line_num, const tokens_line1_arr &_tokens_line1_arr) {
	tokens_line _for_line;
	getline_subblock_t _getline_subblock;
	tokens_line1_arr _for_block;
	Mixed _for_parse;
	Mixed _return;
	_for_line = _tokens_line1_arr.at(_line_num)._0;
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
	add_pos_of_1st_token_to_mix(_return, _for_line);
	return _return;
}
Mixed process_while(long &_line_num,
		const tokens_line1_arr &_tokens_line1_arr) {
	tokens_line _while_line;
	Mixed _return;
//	long _while_lv;
	tokens_line1_arr _while_block;
	getline_subblock_t _getline_subblock;
	Mixed _for_parse;
	_while_line = _tokens_line1_arr.at(_line_num)._0;
// _while_lv = _tokens_arr [_line_num] ._1;
	_while_block = { };
	_getline_subblock = getline_subblock(_tokens_line1_arr, _line_num);
	_line_num += _getline_subblock.i;
	_while_block = _getline_subblock.arr;
// _for_parse = for_parse ( array_slice ( _while_line, 0, gt_sizeof ( _while_line ) ) );
	_return.push("type", "while");
	_return.push("condition", parse_expression(array_slice(_while_line, 1)));
	_return.push("body", structurelize(_while_block));
	add_pos_of_1st_token_to_mix(_return, _while_line);
	return _return;
}
#endif /* CORE_LOOPS_H_ */
