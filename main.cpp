#include <core.h>
int main_exec(int _argc, arr_ls _args) {
	//prepare;
	log("main() starting...");
	init_translation();
	init_builtin_functions();
	init_exception_classes();
	string _operator1;
	long _len;
	for (auto const& [_k, _v1] : __operators) {
		string _v = (string) _v1;
		array_push(__operator_1st_chars, ts(_v.at(0)));
	}
	for (auto const& [_k, _operator] : __operators) {
		_len = strlen((string) _operator);
		if (array_search(_operator, __operators_by_chars_count[_len]) == -1)
			array_push(__operators_by_chars_count[_len], _operator);
	}
// ! prepare =========================================================================

	string _input_file = "test.gtc";
	if (_argc > 1)
		_input_file = _args[0];
	__args = _args;
	string _content;
	try {
		_content = file_get_contents(_input_file);
	} catch (...) {
		echo("Cannot read input file.\n");
		return (1);
	}
	//process
	try {
		tokens_line1_arr _tokens = tokenize(_content);
		log("tokens: ");
		//print_r(_tokens);
		Mixed _structure = structurelize(_tokens);
		//_structure.printPretty();
		log("structure: ");
		log(_structure.create_pretty_str());
		gt_exec(_structure);
	} catch (GtlangException &_e) {
		if (isset(_e.obj, "properties"))
			echo(
					"GTError: " + ((string) _e.obj["properties"]["$msg"])
							+ "[token:"
							+ ((string) _e.obj["properties"]["$token"])
							+ " at line "
							+ ((string) _e.obj["properties"]["$line"])
							+ " column "
							+ ((string) _e.obj["properties"]["$column"]) + "]");
		else
			echo("GTError: " + ((string) _e.obj));
		return 1;
	} catch (GtlangException *_e) {
		if (isset(_e->obj, "properties"))
			echo(
					"GTError: " + ((string) _e->obj["properties"]["$msg"])
							+ "[token:"
							+ ((string) _e->obj["properties"]["$token"])
							+ " at line "
							+ ((string) _e->obj["properties"]["$line"])
							+ " column"
							+ ((string) _e->obj["properties"]["$column"])
							+ "]");
		else
			echo("GTError : " + ((string) _e->obj));
		return 1;
	} catch (InternalException &_e) {
		echo("InternalError: " + _e.msg);
		return 1;
	} catch (InternalException *_e) {
		echo("InternalError : " + _e->msg);
		return 1;
	} catch (const char *_e) {
		echo("GTlang compiler Error : " + (string) _e);
		return 1;
	} catch (out_of_range *_e) {
		echo("GTlang compiler Error : ");
		cout << _e->what();
		return 1;
	}
	return 0;
}
int main(int argc, char *argv[]) {
//	tokens_line1_arr _t = tokenize(" $i : 0 ");
//	tokens_line _t1 = _t[0]._0;
//	Mixed _m1 = Mixed(_t1);
//	parse_expression_inner(_m1);
//	exit(0);
	__main_thread_id = get_thread_id_str();
	vector<string> _args_vector = vector<string>(argv, argv + argc);
	arr_ls _args;
	for (unsigned long _i = 1; _i < _args_vector.size(); _i++) {
		_args[_i - 1] = _args_vector[_i];
	}
	int _return = main_exec(argc, _args);
	bool _flag = false;
	for (auto& [_k, _v] : __threads) {
		if (_v.joinable()) {
			_flag = true;
		}
		if (_flag)
			echo("Warning: waiting for unfinished threads.");
		for (auto& [_k, _v] : __threads) {
			if (_v.joinable()) {
				_v.join();
			}
		}
	}
//	__funcs.unset_r();
//	__main.unset_r();
//	__answer_var.unset_r();
//	__global_vars.unset_r();
//	__local_vars.unset_r();
//	__thread_vars.unset_r();
//	__classes.unset_r();
	return _return;
}
