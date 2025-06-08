/*
 * commons.h
 *
 *  Created on: May 25, 2025
 *      Author: t
 */

#ifndef CORE_COMMONS_H_
#define CORE_COMMONS_H_

Mixed parse_expression(Mixed &_tokens_line_arr);
Mixed structurelize(tokens_line1_arr _arr);
int main_exec(int argc, const arr_ls &args);
void array_push(map<long, thread> &_arr, thread _ele) {
	if (_arr.size() == 0) {
		_arr[0] = move(_ele);
		return;
	}
	long _max_key = (_arr.rbegin()->first);
	_arr[_max_key + 1] = move(_ele);
}
Mixed parse_expression(const tokens_line &_tokens_line1_arr) {
	Mixed _mixed1 = Mixed(_tokens_line1_arr);
	return parse_expression(_mixed1);
}
tokens_line1_arr tokenize(const string &_content);
Mixed find_operator_in_expr(Mixed _expr);
Mixed gt_do(const string &_opt, const token &_params, long _opt_pos);
Mixed gt_do(const string &_opt, const Mixed &_params, long _opt_pos);
Mixed create_array_var(const Mixed &_parsed);
Mixed get_value(const Mixed &_value);
Mixed register_class(Mixed _new_class);
Mixed get_var_global_value(const Mixed &_value);
Mixed call_function(Mixed _parsed);
Mixed call_method(Mixed _parsed);
Mixed assign_var(const Mixed &_var, const Mixed &_value);
Mixed assign_array(const Mixed &_input);
Mixed gt_eval(const Mixed &_parsed);
gt_exec_rs gt_exec(const Mixed &_parsed);
string get_name(const Mixed &_1);
#endif /* CORE_COMMONS_H_ */
