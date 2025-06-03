/*
 * threads.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_THREADS_H_
#define CORE_THREADS_H_

Mixed gt_get_args(Mixed _input) {
	log("gt_get_args(): ");
	Mixed _return;
	for (auto [_k, _v] : __args) {
		_return.push(_v);
	}
	return _return;
}
string get_thread_id_str() {
	ostringstream oss;
	oss << this_thread::get_id();
	return oss.str();
}
bool is_main_thread() {
	return get_thread_id_str() == __main_thread_id;
}
class ThreadReturnException {
public:
	string msg;
	ThreadReturnException(string str) {
		msg = str;
	}
};
void thread_exec(string _file_name) {
	arr_ls _args;
	_args[0] = _file_name;
	try {
		main_exec(2, _args);
	} catch (ThreadReturnException _e) {
		return;
	}
}
Mixed gt_thread_return(Mixed _input) {
	if (is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"cannot return in main class");
	string _thread_id = get_thread_id_str();
	__multi_threads_data[_thread_id]["output"] = _input[0];
	throw ThreadReturnException("");
	return Mixed();
}
Mixed gt_thread_start(Mixed _input) {
	if (!is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"not in main class to wait sub threads");
	Mixed _tmp;
	if (gt_sizeof(_input) < 1)
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"gt_thread_start() not enough args");
	string _file_name = _input[0];
//array_shift_no_return(_input);
	Mixed _thread_input_var = Mixed();
	if (isset(_input, 1))
		_thread_input_var = _input[1];
//	Mixed _args;
//	if (!isset(_input, 2)) {
//		_args = _input[2];
//		_args.resetKeys();
//	}
////
//	long _i = __threads.rbegin()->first + 1;
//prepare_var
	_tmp.push("input", _thread_input_var);
	_tmp.push("output", Mixed());
//============
	__general_thread_lock.lock();
	thread _thread = thread(thread_exec, _file_name);
	ostringstream oss;
	oss << _thread.get_id();
	string _id = oss.str();
	__threads[_id] = move(_thread);
	__multi_threads_data.push(_id, _tmp);
	__thread_vars.push(_id, __global_vars);
	__general_thread_lock.unlock();
	return Mixed(_id);
}
Mixed gt_thread_get_args(Mixed _not_used) {
	if (is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"not in sub thread to thread_get_args()");
	string _thread_id = get_thread_id_str();
	return __multi_threads_data[_thread_id]["input"];
}
Mixed gt_thread_get_result(Mixed _id) {
	if (!is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"not in main class to wait sub threads");
	string _id_str = (string) _id[0];
	if (!__threads.contains(_id_str))
		throw GreenTeaException("ThreadNotFoundException",
				"There is no thread with this id: " + _id_str, _id[0]);
	string _thread_id = get_name(_id);
	__threads[_thread_id].join();
	Mixed _return = __multi_threads_data[_thread_id]["output"];
	//clean;
	__thread_vars.delete_e(_thread_id);
	__multi_threads_data.delete_e(_thread_id);
	__threads.erase(_thread_id);
	//=========;
	return _return;
}
Mixed gt_sleep(Mixed _milli_seconds) {
	int _ms = (int) _milli_seconds[0];
	std::this_thread::sleep_for(std::chrono::milliseconds(_ms));
	return Mixed();
}
#endif /* CORE_THREADS_H_ */
