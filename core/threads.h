/*
 * threads.h
 *
 *  Created on: May 24, 2025
 *      Author: t
 */

#ifndef CORE_THREADS_H_
#define CORE_THREADS_H_

Mixed gt_get_args(const Mixed &_input) {
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
void thread_exec(const string &_file_name) {
	arr_ls _args;
	_args[0] = _file_name;
	__general_thread_lock.lock();
	__general_thread_lock.unlock();
	try {
		main_exec(2, _args);
	} catch (ThreadReturnException &_e) {
		return;
	} catch (GreenTeaException &_e) {
		string _thread_id = get_thread_id_str();
//		__g[_thread_id].delete_e("global_vars");
//		__g[_thread_id].delete_e("local_vars");
//		__g[_thread_id].delete_e("answer_var");
//		__g[_thread_id].delete_e("func_lv");
//		__g[_thread_id].delete_e("funcs");
//		__g[_thread_id].delete_e("classes");
		__multi_threads_data[_thread_id]["output"] = Mixed(false);
		echo(
				lr("ThreadExecutionException: ")
						+ lr((string) _e.obj["properties"]["$msg"]) + " ["
						+ lr("token: ")
						+ ((string) _e.obj["properties"]["$token"])
						+ lr(" at line ")
						+ ((string) _e.obj["properties"]["$line"])
						+ lr(" column ")
						+ ((string) _e.obj["properties"]["$column"]) + "]\n");
		return;
	}
}
Mixed gt_thread_return(const Mixed &_input) {
	if (is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"cannot return in main class");
	string _thread_id = get_thread_id_str();
	__multi_threads_data[_thread_id]["output"] = _input[0];
	throw ThreadReturnException("");
	return Mixed();
}
Mixed gt_thread_start(const Mixed &_input) {
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
	__g.push(_id, Mixed());
	__g[_id].push("global_vars", __global_vars);
	__g[_id].push("local_vars", Mixed());
	__g[_id].push("answer_var", Mixed());
	__g[_id].push("func_lv", 0);
	__g[_id].push("funcs", Mixed());
	__g[_id].push("classes", Mixed());
	__general_thread_lock.unlock();
	return Mixed(_id);
}
Mixed gt_thread_get_args(const Mixed &_not_used) {
	if (is_main_thread())
		throw GtlangInnerFunctionException("ThreadExecutionException",
				"not in sub thread to thread_get_args()");
	string _thread_id = get_thread_id_str();
	return __multi_threads_data[_thread_id]["input"];
}
Mixed gt_thread_get_result(const Mixed &_id) {
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
	__g[_thread_id].delete_e("global_vars");
	__g[_thread_id].delete_e("local_vars");
	__g[_thread_id].delete_e("answer_var");
	__g[_thread_id].delete_e("func_lv");
	__g[_thread_id].delete_e("funcs");
	__g[_thread_id].delete_e("classes");
	__multi_threads_data.delete_e(_thread_id);
	__threads.erase(_thread_id);
	if (__threads.empty()) {
		for (auto [_k, _v] : __g.valueArray)
			__g.delete_e((string) _k);
	}
//=========;
	return _return;
}
Mixed gt_sleep(const Mixed &_milli_seconds) {
	int _ms = (int) _milli_seconds[0];
	std::this_thread::sleep_for(std::chrono::milliseconds(_ms));
	return Mixed();
}
#endif /* CORE_THREADS_H_ */
