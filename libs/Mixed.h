#ifndef LIB_MIXED_H_
#define LIB_MIXED_H_

using namespace std;

bool isInt(double num) {
	return (ceilf(num) == num);
}
class GtlangException {
public:
	string msg;
	GtlangException(string str) {
		msg = str;
	}
};
class Mixed;
class Mixed {
public:
	string type = "a";
	string valueStr = "";
	double valueNum = 0.0;
	bool valueBool = false;
	long index = 0;
	vector<pair<string, Mixed*>> valueArray;

	Mixed* get_e(string _k) {
		for (auto _m : this->valueArray) {
			if ((string) _m.first == _k)
				return _m.second;
		}
		throw(new GtlangException("array dont have index: " + _k));
	}
	bool set_e(string _k, const Mixed &_v) {
		Mixed *_new_element = new Mixed(_v);
		long _i = 0;
		bool _flag = false;
		for (auto _m : this->valueArray) {
			if ((string) _m.first == _k) {
				this->valueArray[_i] = { _k, _new_element };
				_flag = true;
			}
			_i++;
		}
		if (!_flag) {
			valueArray.push_back( { _k, _new_element });
		}
		return _flag;
	}
	void add_e(const Mixed &_element_to_add) {
//		string _k;
//		//Mixed *_value;
//		long _max_key = 0;
//		for (auto _m : valueArray) {
//			_k = (string) _m.first;
//			//_value = (string) _m.second;
//			try {
//				long _k_l = tl(_k);
//				if (_max_key < _k_l)
//					_max_key = _k_l;
//			} catch (...) {
//				;
//			}
//		}
		set_e(ts(this->index), _element_to_add);
	}
	bool delete_e(string _k) {
		bool _flag = false;
		for (unsigned long _i = 0; _i < valueArray.size(); _i++) {
			if (valueArray[_i].first == _k) {
				this->valueArray.erase(this->valueArray.begin() + _i);
				_flag = true;
			}
		}
		return _flag;
	}
	void _init() {
		this->type = "a";
		string valueStr = "";
		valueNum = 0.0;
		valueBool = false;
		index = 0;
		valueArray = { };
	}
	Mixed(const Mixed &_1) {
		Mixed *_tmp = new Mixed();
		this->type = _1.type;
		this->valueStr = _1.valueStr;
		this->valueNum = _1.valueNum;
		this->valueBool = _1.valueBool;
		this->index = _1.index;
//		this->valueArray = map<string, Mixed*>(_1.valueArray);
		for (auto const& [_k, _v] : _1.valueArray) {
			_tmp = new Mixed(*((Mixed*) _v));
			this->valueArray.push_back( { (string) _k, _tmp });
		}
	}
	Mixed() {
		_init();
	}
	Mixed(const string value) {
		_init();
		this->valueStr = value;
		this->type = "s";
	}
	Mixed(const char *value) {
		_init();
		this->valueStr = value;
		this->type = "s";
	}
	Mixed(const char value) {
		_init();
		this->valueStr = value;
		this->type = "s";
	}
	Mixed(const long value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const int value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const double value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const bool value) {
		_init();
		this->valueBool = value;
		this->type = "b";
	}
//	template<typename K, typename V>
	Mixed(token value) {
		_init();
		Mixed *newMixed0 = new Mixed(value._0);
		Mixed *newMixed1 = new Mixed(value._1);
		this->valueArray.push_back( { "name", newMixed0 });
		this->valueArray.push_back( { "type", newMixed1 });
		this->index = 2;
		//this->type = "a";
	}

	Mixed(tokens_line input) {
		_init();
		Mixed *newMixed;
		token _tk;
		for (auto [_k, _v] : input) {
			_tk = (token) _v;
			newMixed = new Mixed(_tk);
			this->valueArray.push_back( { ts((long) _k), newMixed });
			this->index = ((long) _k) + 1;
		}
		//this->type = "a";
	}
	Mixed(const arr_ls value) {
		_init();
		for (auto [_k, _v] : value) {
			this->valueArray.push_back(
					{ to_string(_k), new Mixed((string) _v) });
			this->index = ((long) _k) + 1;
		}
	}
	Mixed(const tokens_line1 value) {
		_init();
		this->valueArray.push_back( { "0", new Mixed(value._0) });
		this->valueArray.push_back( { "1", new Mixed(value._1) });
		this->type = "a";
		this->index = 2;
	}
	Mixed(const tokens_line1_arr value) {
		_init();
		for (auto [_k, _v] : value) {
			this->valueArray.push_back(
					{ to_string(_k), new Mixed((tokens_line1) _v) });
			this->index = ((long) _k) + 1;
		}
		this->type = "a";
	}
	long getInt() {
		return (long) this->valueNum;
	}
	long getLen() {
		return this->valueArray.size();
	}
	token to_token() {
		token _return;
		try {
			_return._0 = get_e("0")->valueStr;
			_return._1 = get_e("1")->valueStr;
		} catch (...) {
			_return._0 = get_e("name")->valueStr;
			_return._1 = get_e("type")->valueStr;
		}
		return _return;
	}
//	Mixed(const Mixed &value) {
//		this = value;
//	}
	void setStr(const string value) {
		this->valueStr = value;
		this->type = "s";
	}

	void setNum(const long value) {
		this->valueStr = value;
		this->type = "n";
	}

	void setNum(const double value) {
		this->valueStr = value;
		this->type = "n";
	}

	void setBool(bool value) {
		this->valueBool = value;
		this->type = "b";
	}

	void setArray(vector<pair<string, Mixed*>> value) {
		this->valueArray = value;
		this->type = "a";
	}

	string getType() {
		return this->type;
	}
	template<typename V>
	void push(string key, V element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(key, element);
		this->index++;
	}
	template<typename V>
	void push(const char *key, V element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(key, element);
		this->index++;
	}
	template<typename V>
	void push(int key, V element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(key), element);
		this->index++;
	}
	void push(const Mixed element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		add_e(element);
		this->index++;
	}
	void push(const string element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const char *element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(long element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const double element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const bool element) {
		if (this->type != "a")
			throw "not an array to push";
		//Mixed *elementPointer = new Mixed(element);
		set_e(ts(this->index), element);
		this->index++;
	}
	void merge(Mixed _1) {
		Mixed _return = Mixed();
//		for (auto [_k, _element] : valueArray) {
//			_return.push((Mixed) *_element);
//		}
		for (auto [_k, _element] : _1.valueArray) {
			push((Mixed) *_element);
		}
		resetKeys();
//		return _return;
	}
	Mixed slice(long _pos, long _len = -1) {
//		Mixed _return;
		long _current_pos = 0;
		if (_len > 0) {
			for (auto const& [_ka, _va] : this->valueArray) {
				if (_current_pos < _pos || _current_pos >= (_pos + _len)) {
					((Mixed) *_va).unset_r();
					this->valueArray.erase(
							this->valueArray.begin() + _current_pos);
				}
				_current_pos++;
			}
		} else {
			for (auto const& [_ka, _va] : this->valueArray) {
				if (_current_pos < _pos) {
					((Mixed) *_va).unset_r();
					this->valueArray.erase(
							this->valueArray.begin() + _current_pos);
				}
				_current_pos++;
			}
		}
		return *this;
	}
	Mixed operator=(const Mixed &_1) {
//
//		Mixed *_tmp;
//		if (mixed1.type != "a") {
//			_return->type = mixed1.type;
//			_return->valueStr = mixed1.valueStr;
//			_return->valueNum = mixed1.valueNum;
//			_return->valueBool = mixed1.valueBool;
//			_return->index = mixed1.index;
//			_return->valueArray = { };
//		} else {
//			_return->type = "a";
//			_return->valueStr = mixed1.valueStr;
//			_return->valueNum = mixed1.valueNum;
//			_return->valueBool = mixed1.valueBool;
//			_return->index = mixed1.index;
//			_return->valueArray = { };
//			for (auto& [_k, _v] : mixed1.valueArray) {
//				_tmp = new Mixed(*((Mixed*) _v));
//				_return->valueArray[(string) _k] = _tmp;
//			}
////			_tmp = mixed1.valueArray;
////			_return.valueArray = _tmp;
////			return _return;
//		}
//		return *_return;
//		Mixed *_return = new Mixed();
//		Mixed *_tmp = new Mixed();
//		_return->type = mixed1.type;
//		_return->valueStr = mixed1.valueStr;
//		_return->valueNum = mixed1.valueNum;
//		_return->valueBool = mixed1.valueBool;
//		for (auto& [_k, _v] : mixed1.valueArray) {
//			_tmp = new Mixed(*((Mixed*) _v));
//			_return->valueArray[(string) _k] = _tmp;
//		}
//		//delete _tmp;
//		return *_return;
		unset_r();
		Mixed *_tmp = new Mixed();
		this->type = _1.type;
		this->valueStr = _1.valueStr;
		this->valueNum = _1.valueNum;
		this->valueBool = _1.valueBool;
		this->index = _1.index;
//		this->valueArray = map<string, Mixed*>(_1.valueArray);
		for (auto const& [_k, _v] : _1.valueArray) {
			_tmp = new Mixed(*((Mixed*) _v));
			this->valueArray.push_back( { (string) _k, _tmp });
		}
		return *this;
	}
	int operator=(int number) {
		this->valueNum = (double) number;
		this->type = "n";
		this->valueStr = "";
		this->valueBool = false;
		unset_r();
		return this->valueNum;
	}
	float operator=(float number) {
		this->valueNum = (double) number;
		this->type = "n";
		this->valueStr = "";
		this->valueBool = false;
		unset_r();
		return this->valueNum;
	}
	Mixed operator=(const char *str) {
		this->valueNum = 0;
		this->type = "s";
		this->valueStr = str;
		this->valueBool = false;
		unset_r();
		return *this;
	}
	Mixed operator=(string str) {
		this->valueNum = 0;
		this->type = "s";
		this->valueStr = str;
		this->valueBool = false;
		unset_r();
		return *this;
	}
	Mixed operator=(bool tf) {
		this->valueNum = 0;
		this->type = "b";
		this->valueStr = "";
		this->valueBool = tf;
		unset_r();
		return *this;
	}
	template<typename V>
	Mixed operator=(map<long, V> _arr) {
		//		Mixed _return;
		try {
			unset_r();
			this->type = "a";
			string valueStr = "";
			valueNum = 0.0;
			valueBool = false;
			index = 0;
			for (auto [_k, _v] : _arr) {
				set_e(ts((long) _k), new Mixed((V) _v));
			}
			return *this;
		} catch (...) {
			throw "error convert to Mixed";
		}
	}
//	template<typename V>
//	void push(map<long, V> _arr) {
//		this->valueArray[to_string()];
//	}
//	Mixed(const token value) {
//		this->type = "a";
//		this->valueArray.insert( { "0", new Mixed(value._0) });
//		this->valueArray.insert( { "1", new Mixed(value._1) });
//	}
	bool contains(string _k) {
		bool _flag = false;
		for (auto _m : this->valueArray) {
			if ((string) _m.first == _k) {
				_flag = true;
				break;
			}
		}
		return _flag;
	}
	Mixed& operator[](string key) {
		if (this->type != "a")
			throw "Getting element of non-array object";
		if (contains(key)) {
			return *get_e(key);
		} else {
			//Mixed *_return = new Mixed("");
//			set_e(key, _return);
			//return *_return;
			throw "Element not exist";
		}
		//return new Mixed();
	}
	Mixed& operator[](const char *key) {
		return operator[]((string) key);
	}
	Mixed& operator[](int key) {
		return operator[](ts(key));
	}
	Mixed& operator[](long key) {
//		Mixed *_return = new Mixed();
//		if (this->type != "a")
//			throw "Getting element of non-array object";
//		try {
		return operator[](ts(key));
//		Mixed _return = operator[](ts(key));
//		return _return;
//		} catch (...) {
//			throw "Element not exist";
//		}
//		return *_return;
	}
	Mixed& operator[](unsigned long key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = get_e(to_string(key));
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	Mixed& operator[](float key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = get_e(to_string(key));
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	void unset_r() {
		string _k;
		Mixed *_v;
		map<string, Mixed*>::iterator it;
		for (auto it : valueArray) {
			_k = it.first;
			_v = it.second;
			if (_v->type == "a")
				(*_v).unset_r();
			else
				delete _v;
		}
		this->valueArray.clear();
	}

//	void operator=(Mixed &arr) {
//		this->valueNum = 0;
//		this->type = "a";
//		this->valueStr = "";
//		this->valueBool = false;
//		unset_r();
//		this->valueArray = arr.valueArray;
//	}
	operator int() {
		if (this->type == "n")
			return (int) this->valueNum;
		if (this->type == "s") {
			try {
				return stoi(this->valueStr);
				return (int) stof(this->valueStr);
			} catch (...) {
				if (this->valueStr.size() > 0)
					return 1;
				return 0;
			}
		}
		if (this->type == "b") {
			if (this->valueBool)
				return 1;
			else
				return 0;
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return 1;
			else if (this->valueStr.size() > 0)
				return 1;
			return 0;
		}
		return 0;
	}
	operator float() {
		if (this->type == "n")
			return (float) this->valueNum;
		if (this->type == "s") {
			try {
//				return stoi(this->valueStr);
				return (float) stof(this->valueStr);
			} catch (...) {
				if (this->valueStr.size() > 0)
					return 1;
				return 0;
			}
		}
		if (this->type == "b") {
			if (this->valueBool)
				return 1;
			else
				return 0;
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return 1;
			else
				return 0;
		}
		return 0;
	}
	operator string() {
		if (this->type == "n")
			return to_string(this->valueNum);
		if (this->type == "s") {
			return this->valueStr;
		}
		if (this->type == "b") {
			if (this->valueBool)
				return "true";
			else
				return "";
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return "array";
			else
				return "";
		}
		return "";
	}
	operator bool() {
		return this->valueBool;
	}
	operator token() {
		token _return;
		try {
			_return._0 = (string) * get_e("0");
			_return._1 = (string) * get_e("1");
			return _return;
		} catch (...) {
			return token();
		}
		return token();
	}
	tokens_line to_tokens_line() {
		tokens_line _return;
		string _k;
		Mixed _v;
		try {
			for (auto [_ka, _va] : this->valueArray) {
				_k = (string) _ka;
				_v = *((Mixed*) _va);
				_return[stol(_k)] = token(_v[0], _v[1]);
			}
			return _return;
		} catch (...) {
			throw "cannot convert to ls";
		}
		return {};
	}
	arr_ls to_ls() {
		arr_ls _return;
		try {
			for (auto [_k, _v] : this->valueArray) {
				_return[stol((string) _k)] = (string) (Mixed) _v;
			}
			return _return;
		} catch (...) {
			throw "cannot convert to ls";
		}
		return {};
	}
	void del(string _k) {
		get_e(_k)->unset_r();
		delete_e(_k);
	}
	Mixed& get_ref(string key) {
		if (this->type != "a")
			throw "not an array to get ref";
		return *(get_e(key));
	}
	bool operator==(string _compare) {
//		cout << this->valueStr;
		//exit(0);
		return (this->valueStr == _compare);
	}
	Mixed operator+(Mixed _peer) {
		if (this->type == "n" && _peer.type == "n") {
			return Mixed(this->valueNum + _peer.valueNum);
		}
		if (this->type == "s" && _peer.type == "s") {
			return Mixed(this->valueStr + _peer.valueStr);
		}
		if (this->type == "s" && _peer.type == "n") {
			return Mixed(this->valueNum + _peer.valueNum);
		}
		if (this->type == "n" && _peer.type == "s") {
			return Mixed(this->valueNum + _peer.valueNum);
		}
		if (this->type == "a" && _peer.type == "a") {
			this->merge(_peer);
			return *this;
		}
		throw("Cannot plus");
	}
	Mixed operator-(Mixed _peer) {
		if (this->type == "n" && _peer.type == "n") {
			return Mixed(this->valueNum - _peer.valueNum);
		}
		if (this->type == "s" && _peer.type == "s") {
			return Mixed(this->valueNum - _peer.valueNum);
		}
		if (this->type == "s" && _peer.type == "n") {
			return Mixed(this->valueNum + _peer.valueNum);
		}
		if (this->type == "n" && _peer.type == "s") {
			return Mixed(this->valueNum + _peer.valueNum);
		}
		throw("Cannot subtract");
	}
	Mixed operator*(Mixed _peer) {
		if (this->type == "n" && _peer.type == "n") {
			return Mixed(this->valueNum * _peer.valueNum);
		}
		if (this->type == "s" && _peer.type == "s") {
			return Mixed(this->valueNum * _peer.valueNum);
		}
		if (this->type == "s" && _peer.type == "n") {
			return Mixed(this->valueNum * _peer.valueNum);
		}
		if (this->type == "n" && _peer.type == "s") {
			return Mixed(this->valueNum * _peer.valueNum);
		}
		throw("Cannot multiply");
	}
	Mixed operator/(Mixed _peer) {
		try {
			if (this->type == "n" && _peer.type == "n") {
				return Mixed(this->valueNum / _peer.valueNum);
			}
			if (this->type == "s" && _peer.type == "s") {
				return Mixed(this->valueNum / _peer.valueNum);
			}
			if (this->type == "s" && _peer.type == "n") {
				return Mixed(this->valueNum / _peer.valueNum);
			}
			if (this->type == "n" && _peer.type == "s") {
				return Mixed(this->valueNum / _peer.valueNum);
			}
			if (this->type == "a" && _peer.type == "a") {
				this->merge(_peer);
				return *this;
			}
		} catch (...) {
			return 0;
			//throw("Divided by zero");
		}
		throw("Cannot divine");
	}
	bool operator==(Mixed v) {
		if (this->type == "s" && v.type == "s") {
			return this->valueStr == v.valueStr;
		} else if (this->type == "n" && v.type == "n") {
			return this->valueNum == v.valueNum;
		} else if (this->type == "b" && v.type == "b") {
			return this->valueBool == v.valueBool;
		} else if (this->type == "s" && v.type == "n") {
			return trim(this->valueStr) == to_string(v.valueNum);
		} else if (this->type == "s" && v.type == "b") {
			if (v.valueBool && this->valueStr != "")
				return true;
			if (!v.valueBool && this->valueStr == "")
				return true;
			return false;
		} else if (this->type == "n" && v.type == "b") {
			if (v.valueBool && this->valueNum != 0)
				return true;
			if (!v.valueBool && this->valueNum == 0)
				return true;
			return false;
		}
		//==== array ================================================
		else if (this->type == "a" && v.type == "a") {
			if (this->valueArray.size() != v.valueArray.size())
				return false;
			for (auto [_k, _v] : valueArray) {
				if (!(v[(string) _k] == (Mixed) _v))
					return false;
			}
			return true;
		} else if (this->type == "a" && v.type == "s") {
			if (v.valueStr == "" && this->valueArray.size() == 0)
				return true;
			return false;
		} else if (this->type == "a" && v.type == "n") {
			if (v.valueNum == 0 && this->valueArray.size() == 0)
				return true;
			return false;
		} else if (this->type == "a" && v.type == "b") {
			if (v.valueBool && this->valueArray.size() != 0)
				return true;
			if (!v.valueBool && this->valueArray.size() == 0)
				return true;
			return false;
		}
		return false;
	}
	bool operator!=(Mixed v) {
		return !operator==(v);
	}
	bool operator==(const char *_str) {
		return operator==((string) _str);
	}
	bool operator==(token _v) {
		if (this->type != "a")
			return false;
		try {
			if (this->operator[]("0") == _v._0
					&& this->operator[]("1") == _v._1) {
				return true;
			}
		} catch (...) {
			;
		}
		try {
			if (this->operator[]("name") == _v._0
					&& this->operator[]("value") == _v._1) {
				return true;
			}
		} catch (...) {
			;
		}
		return false;
	}
	bool operator!=(const char *v) {
		return !operator==(v);
	}
	const Mixed* at(string _key) {
		if (!contains(_key))
			throw new GtlangException("key not found");
		return get_e(_key);
	}
	const Mixed* at(const char *_key_chars) {
		string _key = (string) _key_chars;
		return at(_key);
	}
	void printPretty(long _tab_lv = 0) {
		if (type == "s") {
			echo("\"" + valueStr + "\"");
			return;
		}
		if (type != "a") {
			echo(valueStr);
			return;
		}
//		string _return = "[";
		echo("\n");
		echo_tabs(_tab_lv);
		echo("[");
		echo("\n");
		bool check = false;
		for (auto const& [_k, _v] : valueArray) {
			if (!check) {
				check = !check;
			} else {
				echo(",\n");
			}
			echo_tabs(_tab_lv + 1);
			echo((string) _k);
			echo(" = ");
			((Mixed*) _v)->printPretty(_tab_lv + 1);
		}
		echo("\n");
		echo_tabs(_tab_lv);
		echo("]");
//		_return += "]";
//		return _return;
	}
	string pretty() {
		if (type == "s") {
			return ("\"" + valueStr + "\"");
		}
		if (type != "a") {
//			cout << valueStr;
			return valueStr;
		}
		string _return = "[";
//		cout << "[";
		bool check = false;
		for (auto const& [_k, _v] : valueArray) {
//			cout << (string) _k;
			if (!check) {
				check = !check;
			} else {
				_return += ",";
			}
			_return += ((Mixed*) _v)->pretty();
		}
//		cout << "]";
		_return += "]";
		return _return;
	}
//	template<typename V>
//	bool operator==(V v) {
//		Mixed s = Mixed(v);
//		if (*this == s)
//			return true;
//		else
//			return false;
//	}
	void resetKeys() {
		vector<pair<string, Mixed*>> _tmp_valueArray;
		long _i = 0;
		for (auto [_k, _v] : this->valueArray) {
			_tmp_valueArray.push_back( { ts(_i), (Mixed*) _v });
			_i++;
		}
		this->valueArray = _tmp_valueArray;
		this->index = _i;
	}
	bool empty() {
		if (this->type == "a" && this->valueArray.size() == 0)
			return true;
		return false;
	}
}
;
tokens_line to_tokens_line(Mixed _1) {
	tokens_line _return;
	Mixed _tmp;
	for (auto [_k, _v] : _1.valueArray) {
		_tmp = ((Mixed) *_v);
		_return[tl((string) _k)] = _tmp.to_token();
	}
	return _return;
}
bool is_token(Mixed _arr) {
	if (_arr.valueArray.size() != 2)
		return false;
	if (!_arr.contains((string) "0"))
		return false;
	if (!_arr.contains((string) "1"))
		return false;
	if (_arr["0"].type != "s")
		return false;
	if (_arr["1"].type != "s")
		return false;
	return true;
}
bool isset(Mixed _arr, string _k) {
	if (_arr.contains(_k))
		return true;
	return false;
}
bool isset(Mixed _arr, long _kl) {
	string _k = ts(_kl);
	if (!_arr.contains(ts(_kl)))
		return false;
	return true;
}
//token reset(Mixed _arr) {
//	return (token) *(_arr.valueArray.begin()->second);
//}
void array_shift_no_return(tokens_line &_arr) {
	_arr.erase(_arr.begin());
}
void array_pop_no_return(tokens_line &_arr) {
	_arr.erase(prev(_arr.end()));
}

Mixed array_slicem(Mixed _arr, long _pos, long _len = 0) {
	Mixed _return;
	long _current_pos = 0;
	if (_len > 0) {
		for (auto const& [_ka, _va] : _arr.valueArray) {
			if (_current_pos >= _pos && _current_pos < (_pos + _len))
				_return.push((string) _ka, *((Mixed*) _va));
			_current_pos++;
		}
	} else {
		for (auto const& [_ka, _va] : _arr.valueArray) {
			if (_current_pos >= _pos)
				_return.push((string) _ka, *((Mixed*) _va));
			_current_pos++;
		}
	}
	return _return;
}
Mixed reset(Mixed tokens_arr) {
	tokens_arr.resetKeys();
	return tokens_arr;
}
Mixed array_merge(Mixed _1, Mixed _2) {
	Mixed _return = Mixed();
	for (auto [_k, _element] : _1.valueArray) {
		_return.push((Mixed) *_element);
	}
	for (auto [_k, _element] : _2.valueArray) {
		_return.push((Mixed) *_element);
	}
	_return.resetKeys();
	return _return;
}
struct mixed_to_tokens_line_with_place_holders_rs {
public:
	tokens_line _0;
	map<string, Mixed> _1;
	mixed_to_tokens_line_with_place_holders_rs() {
		;
	}
	mixed_to_tokens_line_with_place_holders_rs(tokens_line _tl,
			map<string, Mixed> _map_placeholders) {
		_0 = _tl;
		_1 = _map_placeholders;
	}
}
;
mixed_to_tokens_line_with_place_holders_rs mixed_to_tokens_line_with_place_holders(
		Mixed _complex_expr_arr) {
	tokens_line _return;
	token _tmp;
	map<string, Mixed> _map_placeholders;
	long i = 0;
	for (const auto& [_k, _item_tmp] : _complex_expr_arr.valueArray) {
		Mixed _item = *((Mixed*) _item_tmp);
		if (is_token(_item)) {
			_tmp = token((string) _item[0], (string) _item[1]);
			array_push(_return, _tmp);
		} else {
			array_push(_return, token(to_string(i), "placeholder"));
			_map_placeholders.insert( { _k, _item });
		}
		i++;
	}
	return mixed_to_tokens_line_with_place_holders_rs(_return,
			_map_placeholders);
}
bool in_array(Mixed _find, Mixed _arr) {
	for (const auto& [_i, _v] : _arr.valueArray) {
		if ((Mixed) _v == _find)
			return true;
	}
	return false;
}
Mixed array_values(Mixed _arr) {
	Mixed _return;
	return _return;
}
Mixed array_slice(Mixed _arr, long _pos, long _len = -1) {
//Mixed _return;
	long _current_pos = 0;
	if (_len >= 0) {
		for (auto const& [_ka, _va] : _arr.valueArray) {
			if (_current_pos < _pos) {
				((Mixed) *_va).unset_r();
				_arr.valueArray.erase(_arr.valueArray.begin());
			} else if (_current_pos >= (_pos + _len)) {
				((Mixed) *_va).unset_r();
				_arr.valueArray.erase(_arr.valueArray.begin() + _len);
			}
			_current_pos++;
		}
	} else {
		for (auto const& [_ka, _va] : _arr.valueArray) {
			if (_current_pos < _pos) {
				((Mixed) *_va).unset_r();
				_arr.valueArray.erase(_arr.valueArray.begin());
			} else {
				break;
			}
			_current_pos++;
		}
	}
	_arr.resetKeys();
	return _arr;
}
string get_type(Mixed _1);
Mixed replace_placeholders_recruisively(Mixed _arr,
		map<string, Mixed> _map_placeholders) {
	for (const auto& [_k, _v] : _arr.valueArray) {
//		bool a = is_token((Mixed) *_v);
		//bool b = (get_type(((Mixed) *_v)) == "placeholder");
		if (get_type(((Mixed) *_v)) == "placeholder") {
//			if (_v->contains("0"))
			_arr[(string) _k] = _map_placeholders[(string) _k];
//			else if (_v->contains("name"))
//				_arr[(string) _k] = _map_placeholders["name"];
		} else if (((Mixed) _v).type == "a") {
			_arr[_k] = replace_placeholders_recruisively((Mixed) _v,
					_map_placeholders);
		}
	}
	return _arr;
}
template<typename K, typename V>
long gt_sizeof(map<K, V> _um) {
	return _um.size();
}
//template<typename K, typename V>
//long gt_sizeof(map<K, V> _um) {
//	return _um.size();
//}
long gt_sizeof(Mixed _mixed) {
	return _mixed.valueArray.size();
}
#endif //LIB_MIXED_H_

