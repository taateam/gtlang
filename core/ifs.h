/*
 * ifs.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_IFS_H_
#define CORE_IFS_H_

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
				&& _tokens_line1_arr[_line_num + 1]._0[0]._0 == l("elif")
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
	_return.push("type", "ifs");
	_return.push("ifs", Mixed());
	if (_tokens_line1_arr[_line_num + 1]._0[0]._0 == l("else")
			&& _tokens_line1_arr[_line_num + 1]._0[0]._1 == "keyword"
			&& gt_sizeof(_tokens_line1_arr[_line_num + 1]._0) == 1) {
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
#endif /* CORE_IFS_H_ */
