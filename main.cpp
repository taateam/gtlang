#include <core.h>
int main_exec(int _argc, const arr_ls &_args) {
	//prepare;
	log("main() starting...");
	//process
	__args = _args;
	prepare();
	string _input_file = "test.gtc";
	if (_argc > 1)
		_input_file = _args.at(0);

	string _content;
	try {
		_content = file_get_contents(_input_file);
	} catch (...) {
		echo("Cannot read input file.\n");
		return (1);
	}
	try {
		init_translation(_content);
	} catch (GtLanguageFileException &_e) {
		echo("LanguageFileError: " + _e.msg);
		return 1;
	}
	tokens_line1_arr _tokens = tokenize(_content + "\n");
	log("tokens: ");
	print_rl(_tokens);
	Mixed _structure = structurelize(_tokens);
	//_structure.printPretty();
	log("structure: ");
	log(_structure.create_pretty_str());
	gt_exec(_structure);
	return 0;
}
int main(int argc, char *argv[]) {
	__main_thread_id = get_thread_id_str();
	vector<string> _args_vector = vector<string>(argv, argv + argc);
	arr_ls _args;
	for (unsigned long _i = 1; _i < _args_vector.size(); _i++) {
		_args[_i - 1] = _args_vector[_i];
	}
	int _return = -1;
	try {
		_return = main_exec(argc, _args);
	} catch (GreenTeaException &_e) {
		if (isset(_e.obj, "properties"))
			echo(
					lr("GTError: ") + lr((string) _e.obj["properties"]["$msg"])
							+ " [" + lr("token: ")
							+ ((string) _e.obj["properties"]["$token"])
							+ lr(" at line ")
							+ ((string) _e.obj["properties"]["$line"])
							+ lr(" column ")
							+ ((string) _e.obj["properties"]["$column"])
							+ "]\n");
		else
			echo("GTError: " + lr((string) _e.obj));
		return 1;
	} catch (InternalException &_e) {
		echo("InternalError: " + _e.msg);
		return 1;
	} catch (const char *_e) {
		echo("GTlang compiler Error : " + (string) _e);
		return 1;
	}
//	catch (out_of_range *_e) {
//		echo("GTlang compiler Error : ");
//		cout << _e->what();
//		return 1;
//	}
//	catch (...) {
//		cout << "Oops!!!";
//	}
	finalize();
	return _return;
}
