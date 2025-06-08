/*
 * php2cpp.h
 *
 *  Created on: May 2, 2021
 *      Author: qu
 */

#ifndef SRC_CORE_PHP2CPP_H_
#define SRC_CORE_PHP2CPP_H_

using namespace std;

typedef map<long, string> arr_ls;
typedef map<long, long> arr_ll;
typedef map<long, double> arr_ld;
typedef map<long, map<string, string>> arr_lss;
typedef map<string, map<long, long>> arr_sll;
typedef map<long, map<long, string>> arr_lls;
typedef map<string, string> arr_ss;
typedef map<string, long> arr_sl;
typedef map<long, map<long, long>> arr_lll;

class Mixed;
struct token {
public:
	string _0;
	string _1;
	long _l;
	long _c;
	void init() {
		_0 = "";
		_1 = "";
		_l = 0;
		_c = 0;
	}
	token(string name, string type) {
		init();
		_0 = name;
		_1 = type;
	}
	token(string name, string type, long _starting_line_number,
			long _starting_column_number) {
		_0 = name;
		_1 = type;
		_l = _starting_line_number;
		_c = _starting_column_number;
	}
	token() {
		init();
	}
	bool operator==(const token other_token) const {
		if (_0 == other_token._0 && _1 == other_token._1)
			return true;
		return false;
	}
	token(const token &other) {
		_0 = (other._0);
		_1 = (other._1);
		_l = (other._l);
		_c = (other._c);
	}

};

typedef map<long, token> tokens_line;
typedef map<long, tokens_line> tokens_line_arr;
struct tokens_line1 {
public:
	tokens_line _0;
	long _1; //level
};
typedef map<long, tokens_line1> tokens_line1_arr;
string ts(long _input) {
	return to_string(_input);
}
string ts(unsigned long &_input) {
	return to_string(_input);
}
string ts(int _input) {
	return to_string(_input);
}
string ts(const double &_input) {
	ostringstream out;
	out << fixed << setprecision(6) << _input;
	std::string result = out.str();

	if (result.find('.') != std::string::npos) {
		result.erase(result.find_last_not_of('0') + 1);
		if (result.back() == '.') {
			result.pop_back();
		}
	}

	return result;;
}
string ts(const char &_input) {
	return string(1, _input);
}
long tl(const string &_input) {
	try {
		return (long) stoi(_input);
	} catch (...) {
		return 0;
	}
}
double td(const string &_input) {
	char *endptr;
	return strtod(_input.c_str(), &endptr);
}
template<typename K, typename V>
bool array_search(const map<K, V> &_arr, const V &_needle) {
	for (auto const& [_k, _v] : _arr) {
		if (_needle == _v)
			return true;
	}
	return false;
}

//void array_push(arr_ss &_arr, string _key, string _value) {
////	long _max_key = 1;
////	if (!_arr.empty())
////		_max_key = (--_arr.end())->first;
//	_arr.insert(pair<string, string>(_key, _value));
//}
//void array_push(arr_lss &_arr, map<string, string> _ele) {
//	long _max_key = 1;
//	if (!_arr.empty())
//		_max_key = (--_arr.end())->first;
//	_arr.insert(pair<long, map<string, string>>(_max_key + 1, _ele));
//}
//void array_push(arr_l2 &_arr, dual _ele) {
//	long _max_key = 1;
//	if (!_arr.empty())
//		_max_key = (--_arr.end())->first;
//	_arr.insert(pair<long, dual>(_max_key + 1, _ele));
//}
//void array_push(arr_lls &_arr, arr_ls _ele) {
//	long _max_key = 1;
//	if (!_arr.empty())
//		_max_key = (--_arr.end())->first;
//	_arr.insert(pair<long, arr_ls>(_max_key + 1, _ele));
//}
//void array_push(arr_lll &_arr, arr_ll _ele) {
//	long _max_key = 1;
//	if (!_arr.empty())
//		_max_key = (--_arr.end())->first;
//	_arr.insert(pair<long, arr_ll>(_max_key + 1, _ele));
//}
template<typename V>
long array_push(map<long, V> &_arr, const V &_ele) {
	if (_arr.size() == 0) {
		_arr[0] = _ele;
		return 0;
	}
	long _max_key = (_arr.rbegin()->first);
	_arr[_max_key + 1] = _ele;
	return _max_key + 1;
}
long array_push(arr_ls &_arr, const char *_ele) {
	if (_arr.size() == 0) {
		_arr[0] = (string) _ele;
		return 0;
	}
	long _max_key = (_arr.rbegin()->first);
	_arr[_max_key + 1] = (string) _ele;
	return _max_key + 1;
}
template<class V>
void array_push(unordered_map<long, V> &_arr, const V &_ele) {
	long _max_key = 0;
	for (auto const& [_k, _v] : _arr) {
		if (_k > _max_key)
			_max_key = _k;
	}
	_arr[_max_key + 1] = _ele;
}
//template<class V>
//void array_push(mp<V> &_arr, V _ele) {
//_arr.push(_ele);
//}
arr_ls explode(const string &_del, const string &_str) {
	arr_ls _tokens;
	size_t _prev = 0, _pos = 0;
//	if (_str == "")
//		return arr_ls_zero;
	if (_del == "") {
		throw 43;
	}
	do {
		_pos = _str.find(_del, _prev);
		if (_pos == string::npos)
			_pos = _str.length();
		string _token = _str.substr(_prev, _pos - _prev);
		//if (!_token.empty())
		array_push(_tokens, _token);
		_prev = _pos + _del.length();
	} while (_pos < _str.length() && _prev < _str.length());
	return _tokens;
}
template<typename K, typename V>
bool isset(const map<K, V> &_arr, const K &_find) {
	if (_arr.find(_find) == _arr.end())
		return false;
	return true;
}
template<typename K, typename V>
bool isset(map<K, V*> _arr, const K &_find) {
	if (_arr.find(_find) == _arr.end())
		return false;
	return true;
}
template<typename K, typename V>
bool isset(const unordered_map<K, V> &_arr, const K &_find) {
	if (_arr.find(_find) == _arr.end())
		return false;
	return true;
}
//template<typename K, typename V>
//bool isset(unordered_map<K, V*> _arr, K _find) {
//	if (_arr.find(_find) == _arr.end())
//		return false;
//	return true;
//}
void print_r(const arr_ls &_vector_input) {
	cout << "[" << endl;
	for (unsigned long _i = 0; _i < _vector_input.size(); _i++)
		cout << "\t" << _i << " => \"" << _vector_input.at(_i) << "\"," << endl;
	cout << "]" << endl;
}

void print_r(const arr_ll &_vector_input) {
	cout << "[" << endl;
	for (unsigned long _i = 0; _i < _vector_input.size(); _i++)
		cout << "\t" << _i << " => " << _vector_input.at(_i) << "," << endl;
	cout << "]" << endl;
}

void print_r(const arr_lss &_input) {
	cout << "[" << endl;
	for (auto const& [_key0, _val0] : _input) {
		cout << "\t[" << endl;
		for (auto const& [_key, _val] : _val0)
			cout << "\t\t" << _key << " => \"" << _val << "\"," << endl;
		cout << "\t]," << endl;
	}
	cout << "]" << endl;
}
template<typename T>
void print_r(const arr_ss &_input) {
	cout << "[" << endl;
	for (auto const& [_key0, _val0] : _input) {
		cout << "\t" << _key0 << " => " << _val0;
		cout << "\t," << endl;
	}
	cout << "]" << endl;
}
void print_r(const arr_sl &_input) {
	cout << "[" << endl;
	for (auto const& [_key0, _val0] : _input) {
		cout << "\t" << _key0 << " => " << _val0;
		cout << "\t," << endl;
	}
	cout << "]" << endl;
}
void print_r(const arr_ld &_input) {
	cout << "[" << endl;
	for (auto const& [_key0, _val0] : _input) {
		cout << "\t" << _key0 << " => " << _val0;
		cout << "\t," << endl;
	}
	cout << "]" << endl;
}
void print_r(const arr_lll &_input) {
	cout << "[" << endl;
	for (auto const& [_key0, _val0] : _input) {
		cout << "\t" << _key0 << " => " "\n";
		for (auto const& [_key1, _val1] : _val0) {
			cout << "\t\t" << _key1 << " => " << _val1 << "\n";
		}
		cout << "\t," << endl;
	}
	cout << "]" << endl;
}

void echo(const string &_input);
void print_r(const tokens_line1_arr &_input) {
	echo("token:\n");
	for (auto [_k, _v] : _input) {
		echo(ts(_k) + "(" + ts(_v._1) + "): ");
		for (auto [_k1, _v1] : _v._0)
			echo(
					"[" + _v1._1 + " " + ts(_v1._l) + "|" + ts(_v1._c) + " "
							+ _v1._0 + "] ");
		echo("\n");
	}
}
bool file_overwrite(const string &_file, const string &_str) {
	try {
		ofstream out(_file);
		out << _str;
		out.close();
		return true;
	} catch (...) {
		return false;
	}
}
bool file_append(const string &_file, const string &_str) {
	try {
		ofstream out(_file, ios_base::app);
		out << _str;
		out.close();
		return true;
	} catch (...) {
		return false;
	}
}
arr_ll array_keys_with_value(const arr_ls &_arr, const string &_find_after) {
	arr_ll _res = { };
	for (unsigned long _i = 0; _i < _arr.size(); _i++) {
		if (_find_after == _arr.at(_i))
			array_push(_res, (long) _i);
	}
	return _res;
}
template<typename T>
unordered_map<long, T> array_slice(const unordered_map<long, T> &_arr,
		long _start, long _len = -1) {
	unordered_map<long, T> _return;
	if (_len == -1)
		_len = _arr.size();
	long _i = -1;
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i > (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
unordered_map<long, string> array_slice(const unordered_map<long, string> &_arr,
		long _start, long _len = -1) {
	unordered_map<long, string> _return;
	if (_len == -1)
		_len = _arr.size();
	long _i = -1;
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i > (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
template<typename T>
map<long, T> array_slice(const map<long, T> &_arr, long _start,
		long _len = -1) {
	map<long, T> _return;
	long _i = -1;
	if (_len == -1)
		_len = _arr.size();
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i >= (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
map<long, string> array_slice(const map<long, string> &_arr, long _start,
		long _len = -1) {
	map<long, string> _return;
	long _i = -1;
	if (_len == -1)
		_len = _arr.size();
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i > (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
template<typename K, typename V>
map<K, V> array_sliceu(const unordered_map<K, V> &_arr, long _start, long _len =
		-1) {
	unordered_map<K, V> _return;
	long _i = -1;
	if (_len == -1)
		_len = _arr.size();
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i > (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
unordered_map<long, string> array_sliceu(const map<long, string> &_arr,
		long _start, long _len = -1) {
	unordered_map<long, string> _return;
	long _i = -1;
	if (_len == -1)
		_len = _arr.size();
	for (auto const& [_k, _v] : _arr) {
		_i++;
		if (_i < _start)
			continue;
		if (_i > (_start + _len))
			break;
		_return[_k] = _v;
	}
	return _return;
}
double microtime(bool i = true) {
	using namespace std::chrono;
	long long _d = duration_cast < nanoseconds
			> (system_clock::now().time_since_epoch()).count();
	double _res = (double) _d / 1000000000.f;
	return _res;
}
long time_php() {
	return (long) floor(microtime());
}
void echo(int _input) {
	cout.precision(17);
	cout << _input;
	cout.flush();
}
void echo(long _input) {
	cout.precision(17);
	cout << _input;
	cout.flush();
}
void echo(const double &_input) {
	cout.precision(17);
	cout << _input;
	cout.flush();
}
void echo(const string &_input) {
	cout.precision(17);
	cout << _input;
	cout.flush();
}
void echo(const char &_input) {
	cout << _input;
	cout.flush();
}
//void echo(bool _input) {
//	if (_input)
//		cout << "true";
//	else
//		cout << "false";
//}
//long count(arr_lc _arr) {
//	return _arr.size();
//}
template<typename K, typename V>
long count(const map<K, V> &_arr) {
	return _arr.size();
}
string implode(const string &_glue, const arr_ls &_arr) {
	if (_arr.empty())
		return "";
	string _res = "";
	long _max_k = _arr.size() - 1;
	long _k = 0;
	for (auto const& [_i, _v] : _arr) {
		if (_k < _max_k)
			_res += _v + _glue;
		_k++;
	}
	_res += _arr.rbegin()->second;
	return _res;
}
string implode(const string &_glue, const arr_ll &_arr) {
	if (_arr.empty())
		return "";
	string _res = "";
	for (unsigned long _i = 0; _i < (_arr.size() - 1); _i++) {
		_res += ts(_arr.at(_i)) + _glue;
	}
//TODO: use rbegin;
	_res += ts(_arr.at(_arr.size() - 1));
	return _res;
}
string rtrim(const string &_str, const string &_sub) {
	arr_ls _tmp = explode(_sub, _str);
	for (long _i = 0; _i < (long) _tmp.size(); _i++) {
		if (_tmp[_i] != "")
			break;
		_tmp.erase(_i);
	}
	return implode(_sub, _tmp);
}
string ltrim(const string &_str, const string &_sub) {
	arr_ls _tmp = explode(_sub, _str);
	for (long _i = _tmp.size() - 1; _i >= 0; _i--) {
		if (_tmp[_i] != "")
			break;
		_tmp.erase(_i);
	}
	return implode(_sub, _tmp);
}
string trim(const string &_str, const string &_sub) {
	return rtrim(ltrim(_str, _sub), _sub);
}
string rtrim(string _str) {
	boost::trim_right(_str);
	return _str;
}
string ltrim(string _str) {
	boost::trim_left(_str);
	return _str;
}
string trim(string _str) {
	boost::trim(_str);
	return _str;
}
string strtolower(string _str) {
	boost::to_lower(_str);
	return _str;
}
string strtoupper(string _str) {
	boost::to_upper(_str);
	return _str;
}
bool str_contains(const string &_haystack, const string &_needle) {
	if (_haystack.find(_needle) != string::npos) {
		//.. found.
		return true;
	}
	return false;
}
long strpos(const string &_haystack, const string &_needle) {
	size_t _pos = _haystack.find(_needle);
	if (_pos == string::npos)
		return -1;
	else
		return (long) _pos;
}
long strpos(const string &_haystack, const string &_needle, long _start) {
	if (_start > (long) _haystack.length())
		return -1;
	string _tmp_str = _haystack.substr(_start);
	size_t _pos = _tmp_str.find(_needle);
	if (_pos == string::npos)
		return -1;
	else
		return (long) _pos + _start;
}
long stripos(const string &_haystack, const string &_needle) {
	return strpos(strtolower(_haystack), strtolower(_needle));
}
template<typename T>
arr_ll array_keys(const map<long, T> &_arr) {
	arr_ll _res;
	for (auto const& [_key0, _val0] : _arr) {
		_res[_res.size()] = _key0;
	}
	return _res;
}
arr_ll array_keys(const arr_ls &_arr, const string &_str = "") {
	arr_ll _res;
	for (auto const& [_key0, _val0] : _arr) {
		if (_str == "" || _val0 == _str)
			_res[_res.size()] = _key0;
	}
	return _res;
}
//arr_ll array_keys(arr_lc _arr) {
//	arr_ll _res;
//	for (auto const& [_key0, _val0] : _arr) {
//		array_push(_res, _key0);
//	}
//	return _res;
//}
arr_ls array_keys(const arr_ss &_arr) {
	arr_ls _res;
	for (auto const& [_key0, _val0] : _arr) {
		array_push(_res, _key0);
	}
	return _res;
}
//arr_ls array_values(arr_ss _arr) {
//	arr_ls _res;
//	for (auto const& [_key0, _val0] : _arr) {
//		array_push(_res, _val0);
//	}
//	return _res;
//}
arr_ls array_reverse(const arr_ls &_arr) {
	if (_arr.size() < 2)
		return _arr;
	arr_ls _tmp = _arr;
	arr_ls _res;
	map<long, string>::const_iterator _forwardIt = _tmp.begin();
	map<long, string>::const_reverse_iterator _reverseIt = _tmp.rbegin();
	for (; _forwardIt != _tmp.end(); ++_forwardIt, ++_reverseIt) {
		_res[_forwardIt->first] = _reverseIt->second;
	}
	return _res;
}
bool is_numeric(const string &_str) {
	try {
		stol(_str);
		return true;
	} catch (...) {
		;
	}
	try {
		stod(_str);
		return true;
	} catch (...) {
		;
	}
	return false;
}
//long ceil(double _num) {
//	return (long) ceil(_num);
//}
//long floor(double _num) {
//	return (long) floor(_num);
//}
long strlen(const string &_str) {
	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(_str);
	return ustr.countChar32();
}
string str_replace(const string &_search, const string &_replace,
		const string &_input) {
	string _output = _input;
	boost::replace_all(_output, _search, _replace);
	return _output;
}
long substr_count(const string &_haystack1, const string &_needle) {
	long _occurrences = 0;
	string _haystack = _haystack1;
	string::size_type _pos = 0;
	while ((_pos = _haystack.find(_needle, _pos)) != string::npos) {
		++_occurrences;
		_pos += _needle.length();
	}
	return _occurrences;
}
string str_replace(const string &_search, const string &_replace,
		const string &_input, long &_count) {
	_count = substr_count(_input, _search);
	return regex_replace(_input, regex(_search), _replace);
}
string str_ireplace(const string &_search, const string &_replace,
		const string &_input) {
	string _input1 = _input;
	boost::ireplace_all(_input1, _search, _replace);
	return _input1;
}
string add0(const string &_str) {
	if (_str.length() < 2)
		return "0" + _str;
	return _str;
}
string date(const string &_format = "d-m-Y H:i:s") {
	string _str = _format;

	time_t t = time(NULL);
	tm *timePtr = localtime(&t);

	long _seconds = timePtr->tm_sec;
	long _minutes = timePtr->tm_min;
	long _hours = timePtr->tm_hour;
	long _day_of_month = timePtr->tm_mday;
	long _month_of_year = timePtr->tm_mon;
	long _year = timePtr->tm_year + 1900;
//	long _weekday = timePtr->tm_wday;
//	long _day_of_year = timePtr->tm_yday;
//	long daylight_savings = timePtr->tm_isdst;
	_str = str_replace("d", add0(to_string(_day_of_month)), _str);
	_str = str_replace("m", add0(to_string(_month_of_year)), _str);
	_str = str_replace("Y", to_string(_year), _str);
	_str = str_replace("H", add0(to_string(_hours)), _str);
	_str = str_replace("i", add0(to_string(_minutes)), _str);
	_str = str_replace("s", add0(to_string(_seconds)), _str);
	return _str;
}
bool mkdir(const string &_path) {
	filesystem::path _path1 = (filesystem::path) _path;
	return filesystem::create_directory(_path1);
}
bool delete_path(const std::string &path) {
	try {
		return std::filesystem::remove_all(path) > 0;
	} catch (const std::filesystem::filesystem_error &e) {
		return false;
	}
}
string get_env(const string &_name) {
	const char *pPath = getenv(_name.c_str());
	if (pPath != nullptr) {
		return string(pPath);
	}
	return "";
}
string substr(const string &_str, long _start, long _length = -1) {
	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(_str);
	long total = ustr.countChar32();

	if (_start < 0)
		_start = 0;
	if (_start >= total)
		return "";

	if (_length < 0 || (_start + _length > total)) {
		_length = total - _start;
	}

	int32_t start16 = ustr.moveIndex32(0, _start);
	int32_t end16 = ustr.moveIndex32(start16, _length);

	icu::UnicodeString substr = ustr.tempSubStringBetween(start16, end16);
	std::string result;
	substr.toUTF8String(result);
	return result;
}
arr_ls str_split(const string &_str, long _num = 1) {
	arr_ls _return;
	long _len = strlen(_str) - 1;
	string _tmp_str;
	long _i = 0;
	while (_i < _len) {
		_tmp_str = substr(_str, _i, _num);
		array_push(_return, _tmp_str);
		_i += strlen(_tmp_str);
	}
	return _return;
}
//long array_last_key(arr_lc _arr) {
//	long _largest = 0;
//	for (auto const& [_key, _value] : _arr) {
//		if (_key > _largest)
//			_largest = _key;
//	}
//	return _largest;
//}

long random_int(long _start, long _end) {
	srand (time(NULL));long _minus = _end - _start + 1;
	return (rand() % _minus + _start);
}
string shell_exec(const string &cmd) {
	array<char, 128> buffer;
	string result;

	unique_ptr<FILE, int (*)(FILE*)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) {
		throw runtime_error("popen() failed!");
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	return result;
}
template<typename T>
bool in_array(const T &_find, const map<long, T> &_arr) {
	for (auto const& [_i, _v] : _arr) {
		if (_find == (T) _v)
			return true;
	}
	return false;
}
//template<typename T>
//bool in_array(T _find, mp<T> _arr1) {
//	map<long, T> _arr = _arr1.get_map();
//	for (auto const& [_i, _v] : _arr) {
//		if (_find == _v)
//			return true;
//	}
//	return false;
//}
bool in_array(const string &_find, const arr_ss &_arr) {
	for (auto const& [_i, _v] : _arr) {
		if (_v == _find)
			return true;
	}
	return false;
}
//bool in_array(string _find, arr_ls_ts _arr) {
//	return in_array(_find, _arr.get_map());
//}
//long array_search(long _find, arr_ll _arr) {
//	for (auto const& [_i, _v] : _arr) {
//		if (_v == _find)
//			return true;
//	}
//	return false;
//}
//long array_search(arr_ll _find, arr_lll _arr) {
//	for (auto const& [_i, _v] : _arr) {
//		if (_v == _find)
//			return true;
//	}
//	return false;
//}
//long array_search(string _find, arr_ls _arr) {
//	for (auto const& [_i, _v] : _arr) {
//		if (_v == _find)
//			return _i;
//	}
//	return -1;
//}
template<typename K, typename V>
K array_search(const V &_find, const map<K, V> &_arr) {
	for (auto const& [_i, _v] : _arr) {
		if (_v == _find)
			return _i;
	}
	return -1;
}
string array_search(const string &_find, const arr_ss &_arr) {
	for (auto const& [_i, _v] : _arr) {
		if (_v == _find)
			return _i;
	}
	return "";
}
template<typename T>
map<long, T> array_values(const map<long, T> &_arr) {
	map<long, T> _return_arr;
//_return_arr[0] = 1;
	for (auto const& [_k, _v] : _arr)
		_return_arr[_return_arr.size()] = _v;
	return _return_arr;
}
void array_unshift(long _ele, arr_ll &_arr) {
	long _key = _arr.begin()->first;
	_arr[_key - 1] = _ele;
	_arr = array_values(_arr);
}
template<typename K, typename V>
void array_shift(map<K, V> &_arr) {
	_arr.erase(_arr.begin()->first);
}
string array_shift(arr_ls &_arr) {
	if (_arr.empty())
		return "";
	string _return = _arr.begin()->second;
	_arr.erase(_arr.begin()->first);
	return _return;
}
string array_shift(arr_ss &_arr) {
	if (_arr.empty())
		return "";
	string _return = _arr.begin()->second;
	_arr.erase(_arr.begin()->first);
	return _return;
}
//arr_ss array_shift(arr_lss &_arr) {
//	if (_arr.empty())
//		return arr_ss_zero;
//	arr_ss _return = _arr.begin()->second;
//	_arr.erase(_arr.begin()->first);
//	return _return;
//}
//void array_shift(arr_lc &_arr) {
//	_arr.erase(_arr.begin());
//}
string file_get_contents(const string &_file) {
//	int _n = _file.length();
//	char _char_array[_n + 1];
//	strcpy(_char_array, _file.c_str());
	//echo(_file);
	if (!filesystem::exists(_file)) { // @suppress("Invalid arguments")
		//echo("Cannot read input file.");
		throw 404;
	}
	ifstream _ifs(_file);
	string _content((istreambuf_iterator<char>(_ifs)),
			(istreambuf_iterator<char>()));
	return _content;
}
bool mk_dir(const string &_folder) {
	ostringstream cmd;
	cmd << "mkdir -p \"" << _folder << "\"";
	int ret = system(cmd.str().c_str());
	return (ret == 0);
}
bool make_parent_dirs(const string &_filepath) {
	size_t _pos = _filepath.rfind('/');
	if (_pos == string::npos)
		return true;
	string _dir = _filepath.substr(0, _pos);
	return mk_dir(_dir);
}

bool create_empty_file(const string &filepath) {
	if (!make_parent_dirs(filepath)) {
		return false;
	}
	std::ofstream ensure_file(filepath, std::ios::app);
	if (!ensure_file.is_open())
		return false;
	boost::interprocess::file_lock f_lock(filepath.c_str());
	f_lock.lock();
	ofstream file(filepath, ios::trunc);
	if (!file.is_open()) {
		f_lock.unlock();
		return false;
	}
	file.close();
	f_lock.unlock();
	return true;
}
bool append_to_file(const string &filepath, const string &content) {
	if (!filesystem::exists(filepath))
		return false;
	boost::interprocess::file_lock f_lock(filepath.c_str());
	f_lock.lock();

	ofstream file(filepath, ios::app);
	if (!file.is_open()) {
		f_lock.unlock();
		return false;
	}

	file << content;
	file.close();
	f_lock.unlock();
	return true;
}
bool file_exists(const std::string &filename) {
	return filesystem::exists(filename);
}
bool php_is_preg_match(string _pattern, const string &_subject,
		bool _is_unicode = false) {
//echo(substr(_subject, 1, _subject.size() - 2));
	if (!_is_unicode) {
		return regex_search(_subject,
				regex(substr(_pattern, 1, _pattern.size() - 2)));
		//return _return;
	} else {
		_pattern = substr(_pattern, 1, _pattern.size() - 3);
		UErrorCode status = U_ZERO_ERROR;

		string raw_pattern = _pattern;
		if (raw_pattern.size() >= 2 && raw_pattern.front() == '/'
				&& raw_pattern.back() == '/')
			raw_pattern = raw_pattern.substr(1, raw_pattern.size() - 2);

		icu::UnicodeString uPattern(raw_pattern.c_str(), "UTF-8");
		icu::UnicodeString uSubject = icu::UnicodeString::fromUTF8(_subject);
		icu::RegexPattern *regex = icu::RegexPattern::compile(uPattern, 0,
				status);
		if (U_FAILURE(status))
			return false;
		icu::RegexMatcher *matcher = regex->matcher(uSubject, status);
		if (U_FAILURE(status)) {
			delete regex;
			return false;
		}
		bool result = matcher->find();
		delete matcher;
		delete regex;
		return result;
	}
}
arr_ls php_preg_match_all(const string &_pattern, const string &_subject,
		bool _is_unicode = false) {
	map<long, string> matches;

	if (!_is_unicode) {
		string cleaned = _pattern.substr(1, _pattern.size() - 2); // remove /.../
		regex re(cleaned);
		smatch sm;
		long index = 0;
		auto words_begin = std::sregex_iterator(_subject.begin(),
				_subject.end(), re);
		auto words_end = std::sregex_iterator();

		for (auto it = words_begin; it != words_end; ++it) {
			smatch sm = *it;
			matches[index++] = sm.str();
		}
	} else {
		if (_pattern.size() < 3)
			return matches;
		string cleaned = _pattern.substr(1, _pattern.size() - 3); // remove /.../u

		UErrorCode status = U_ZERO_ERROR;
		icu::UnicodeString uPattern = icu::UnicodeString::fromUTF8(cleaned);
		icu::UnicodeString uSubject = icu::UnicodeString::fromUTF8(_subject);

		icu::RegexPattern *regex = icu::RegexPattern::compile(uPattern, 0,
				status);
		if (U_FAILURE(status))
			return matches;

		icu::RegexMatcher *matcher = regex->matcher(uSubject, status);
		if (U_FAILURE(status)) {
			delete regex;
			return matches;
		}

		long index = 0;
		while (matcher->find()) {
			int groupCount = matcher->groupCount();
			for (int i = 0; i <= groupCount; ++i) {
				icu::UnicodeString ustr = matcher->group(i, status);
				std::string utf8;
				ustr.toUTF8String(utf8);
				matches[index++] = utf8;
			}
		}
		delete matcher;
		delete regex;
	}

	return matches;
}
string php_preg_replace_all(const string &_pattern, const string &_replacement,
		const string &_subject, bool _is_unicode = false) {
	if (!_is_unicode) {
		if (_pattern.size() < 2)
			return _subject;
		string cleaned = _pattern.substr(1, _pattern.size() - 2);
		return regex_replace(_subject, regex(cleaned), _replacement);
	} else {
		if (_pattern.size() < 3)
			return _subject;
		string cleaned = _pattern.substr(1, _pattern.size() - 3); // remove /.../u

		UErrorCode status = U_ZERO_ERROR;

		icu::UnicodeString uPattern = icu::UnicodeString::fromUTF8(cleaned);
		icu::UnicodeString uReplacement = icu::UnicodeString::fromUTF8(
				_replacement);
		icu::UnicodeString uSubject = icu::UnicodeString::fromUTF8(_subject);

		icu::RegexPattern *regex = icu::RegexPattern::compile(uPattern, 0,
				status);
		if (U_FAILURE(status))
			return _subject;

		icu::RegexMatcher *matcher = regex->matcher(uSubject, status);
		if (U_FAILURE(status)) {
			delete regex;
			return _subject;
		}

		icu::UnicodeString result = matcher->replaceAll(uReplacement, status);
		delete matcher;
		delete regex;

		if (U_FAILURE(status))
			return _subject;

		std::string out;
		result.toUTF8String(out);
		return out;
	}
}
bool is_name_tag(const string &_str) {
	bool _return0 = (php_is_preg_match("/[a-zA-Z0-9_]+/", _str, false));
	bool _return1 = php_is_preg_match("/[\\p{L}\\p{N}_]+/u", _str, true);
	return _return0 || _return1;
}
long gt_max(long _1, long _2, long _3, long _4, long _5) {
	return max(max(max(_1, _2), max(_3, _4)), _5);
}
arr_ll array_top(const arr_ll &_arr, long _count) {
	arr_ll _arr1 = _arr;
	arr_ll _res;
	if ((long) _arr.size() <= _count)
		return _arr;
	for (long _i = 0; _i < _count; _i++) {
		long _tmp_key = 0;
		long _tmp_value = -2147483648;
		for (auto const& [_k, _v] : _arr1) {
			if (_v >= _tmp_value) {
				_tmp_key = _k;
				_tmp_value = _v;
			}
		}
		_res[_tmp_key] = _tmp_value;
		_arr1.erase(_tmp_key);

	}
	return _res;
}
arr_ld array_top(const arr_ld &_arr, long _count) {
	arr_ld _arr1 = _arr;
	arr_ld _res;
	if ((long) _arr.size() <= _count)
		return _arr;
	for (long _i = 0; _i < _count; _i++) {
		long _tmp_key = 0;
		double _tmp_value = -8888.88;
		for (auto const& [_k, _v] : _arr1) {
			if (_v > _tmp_value) {
				_tmp_key = _k;
				_tmp_value = _v;
			}
		}
		_res[_tmp_key] = _tmp_value;
		_arr1.erase(_tmp_key);

	}
	return _res;
}
arr_ll array_tail(const arr_ll &_arr, long _count) {
	arr_ll _arr1 = _arr;
	arr_ll _res;
	for (long _i = 0; _i < _count; _i++) {
		for (auto const& [_k, _v] : _arr1) {
			long _tmp_key = 0;
			long _tmp_value = 2147483647;
			if (_v <= _tmp_value) {
				_tmp_key = _k;
				_tmp_value = _v;
			}
			_res.insert(pair<long, long>(_tmp_key, _tmp_value));
			_arr1.erase(_tmp_key);
		}
	}
	return _res;
}
arr_ld array_tail(const arr_ld &_arr, long _count) {
	arr_ld _arr1 = _arr;
	arr_ld _res;
	for (long _i = 0; _i < _count; _i++) {
		for (auto const& [_k, _v] : _arr1) {
			long _tmp_key = 0;
			double _tmp_value = 88888.88;
			if (_v <= _tmp_value) {
				_tmp_key = _k;
				_tmp_value = _v;
			}
			_res.insert(pair<long, double>(_tmp_key, _tmp_value));
			_arr1.erase(_tmp_key);
		}
	}
	return _res;
}
arr_lll array_chunk(const arr_ll &_arr, long _num) {
	arr_lll _res;
	long _i = 0;
	for (auto const& [_k, _v] : _arr) {
		_res[_i / _num][_i % _num] = _v;
		_i++;
	}
	return _res;
}
arr_ll array_unique(const arr_ll &_arr) {
	arr_ll _res;
	for (auto const& [_k, _v] : _arr) {
		if (!in_array(_v, _res))
			array_push(_res, _v);
	}
	return _res;
}
arr_ls array_unique(const arr_ls &_arr) {
	arr_ls _res;
	for (auto const& [_k, _v] : _arr) {
		if (!in_array(_v, _res))
			array_push(_res, _v);
	}
	return _res;
}
arr_ls array_unique(const arr_ss &_arr) {
	arr_ls _res;
	for (auto const& [_k, _v] : _arr) {
		if (!in_array(_v, _res))
			array_push(_res, _v);
	}
	return _res;
}
template<typename T>
map<long, T> array_merge(map<long, T> arr1, const map<long, T> &arr2) {
	for (auto const& [_k, _v] : arr2) {
		array_push(arr1, _v);
	}
	return arr1;
}
string readline(const string &_message = "") {
	echo(_message);
	string _to;
	cin >> _to;
	return _to;
}
string php_to_string(const char &_c) {
	string _str = "";
	_str += _c;
	return _str;
}

string get_char_at_utf8(const string &_str, int i) {
	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(_str);
	if (i >= 0 && i < ustr.countChar32()) {
		int32_t index = ustr.moveIndex32(0, i);
		UChar32 c = ustr.char32At(index);

		icu::UnicodeString oneChar(c);
		string _result;
		oneChar.toUTF8String(_result);
		return _result;
	}
	return "";
}
template<typename T>
void reset_keys(map<long, T> &_1) {
	map<long, T> _tmp;
	for (auto const& [_k, _v] : _1) {
		array_push(_tmp, (T) _v);
	}
	_1 = _tmp;
}
void echo_tabs(long tab_lv) {
	for (long i = 0; i <= tab_lv; i++) {
		cout << ("\t");
	}
}
template<typename V>
V array_pop(map<long, V> &_arr) {
	V _return;
	long _max_key = (_arr.rbegin()->first);
	_return = _arr[_max_key];
	_arr.erase(_max_key);
	return _return;
}
void signal_handler(int _signal_num) {
	cout << "Signal (" << _signal_num << ").\n";
// end;
	throw _signal_num;
//terminate();
}

tokens_line trim_tokens_line_once(tokens_line _input) {
	tokens_line _return;
	reset_keys(_input);
	for (auto const& [_k, _v] : _input) {
		if ((_k == 0 || (unsigned long) _k == (_input.size() - 1))
				&& _v._1 == "spaces")
			continue;
		else
			array_push(_return, _v);
	}
	return _return;
}

bool odd(long _input) {
	return (_input % 2 != 0);
}
//string strtoupper(const string &_input) {
//	string _result = _input;
//	transform(_result.begin(), _result.end(), _result.begin(),
//			[](unsigned char c) {
//				return toupper(c);
//			});
//	return _result;
//}
//string strtolower(const string &_input) {
//	string _result = _input;
//	transform(_result.begin(), _result.end(), _result.begin(),
//			[](unsigned char c) {
//				return tolower(c);
//			});
//	return _result;
//}
template<typename T>
void arr_remove(map<long, T> &_arr, long _i) {
	_arr.erase(_i);
	reset_keys(_arr);
}
template<typename K, typename V>
V get_1st_ele(const map<K, V> &_arr) {
	for (auto [_k, _v] : _arr) {
		return _v;
	}
	return V();
}
#endif /* SRC_CORE_PHP2CPP_H_ */
