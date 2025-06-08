#ifndef LIB_MIXED_H_
#define LIB_MIXED_H_

#include <iterator>
#include <exception>
using namespace std;

bool isInt(const double &num) {
	return (ceilf(num) == num);
}
class InternalException {
public:
	string msg;
	InternalException(string str) {
		msg = str;
	}
};
class Mixed;
void print_r(Mixed &_input, long _tab_lv);
class Mixed {
public:
	// a: array, s: string, n: number, b: boolean;
	string type = "a";
	string valueStr = "";
	double valueNum = 0.0;
	bool valueBool = false;
	long index = 0;
	vector<pair<string, Mixed*>> valueArray;

	Mixed* get_e(string _k) const {
		for (auto _m : this->valueArray) {
			if ((string) _m.first == _k)
				return _m.second;
		}
		throw InternalException("array does not have index: " + _k);
	}
	bool set_e(string _k, const Mixed &_v) {
		if (this->type != "a")
			throw "not an array to push";
		bool _flag = false;
		for (size_t i = 0; i < this->valueArray.size(); i++) {
			if (this->valueArray[i].first == _k) {
				this->valueArray[i].second->unset_r();
				delete this->valueArray[i].second;

				Mixed *_new_element = new Mixed(_v);
				this->valueArray[i].second = _new_element;
				_flag = true;
				break;
			}
		}
		if (!_flag) {
			Mixed *_new_element = new Mixed(_v);
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
		for (unsigned long _i = 0; _i < valueArray.size(); _i++) {
			if (valueArray[_i].first == _k) {
				valueArray[_i].second->unset_r();
				delete valueArray[_i].second;
				this->valueArray.erase(this->valueArray.begin() + _i);
				return true;
			}
		}
		return false;
	}
	void _init() {
		this->type = "a";
		string valueStr = "";
		valueNum = 0.0;
		valueBool = false;
		index = 0;
		unset_r();
		valueArray = { };
	}
	Mixed(const Mixed &_1) {
		_init();
		this->type = _1.type;
		this->valueStr = _1.valueStr;
		this->valueNum = _1.valueNum;
		this->valueBool = _1.valueBool;
		this->index = _1.index;
		for (auto const& [_k, _v] : _1.valueArray) {
			Mixed *_tmp = new Mixed(*_v);
			this->valueArray.push_back( { _k, _tmp });
		}
	}
	void unset_r() {
		string _k;
		Mixed *_v;
		map<string, Mixed*>::iterator it;
		for (auto it : valueArray) {
			_k = it.first;
			_v = it.second;
			//if (_v->type == "a")
			(*_v).unset_r();
			delete _v;
		}
		this->valueArray.clear();
	}
	~Mixed() {
		unset_r();
	}
	Mixed() {
		_init();
	}
	Mixed(const string value) {
		_init();
		this->valueStr = value;
		this->type = "s";
		this->valueNum = td(this->valueStr);
		if (value != "" && value != "false" && value != "0")
			this->valueBool = true;
	}
	Mixed(const char *value) {
		_init();
		this->valueStr = value;
		this->type = "s";
		this->valueNum = td(this->valueStr);
		if (valueStr != "" && valueStr != "false" && valueStr != "0")
			this->valueBool = true;
	}
	Mixed(const char value) {
		_init();
		this->valueStr = value;
		this->type = "s";
		if (valueStr != "" && valueStr != "false" && valueStr != "0")
			this->valueBool = true;
	}
	Mixed(const long value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
		this->valueStr = ts(this->valueNum);
		if (value > 0)
			this->valueBool = true;
	}
	Mixed(const int value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
		this->valueStr = ts(this->valueNum);
		if (value > 0)
			this->valueBool = true;
	}
	Mixed(const double value) {
		_init();
		this->valueNum = (double) value;
		this->type = "n";
		this->valueStr = ts(this->valueNum);
		if (value > 0)
			this->valueBool = true;
	}
	Mixed(const bool value) {
		_init();
		this->valueBool = value;
		this->type = "b";
		if (value) {
			this->valueStr = "1";
			this->valueNum = 1;
		}
	}
//	template<typename K, typename V>
	Mixed(token value) {
		_init();
		Mixed *newMixed0 = new Mixed(value._0);
		Mixed *newMixed1 = new Mixed(value._1);
		Mixed *newMixedToken = new Mixed(value._0);
		Mixed *newMixedL = new Mixed(value._l);
		Mixed *newMixedC = new Mixed(value._c);
		this->valueArray.push_back( { "name", newMixed0 });
		this->valueArray.push_back( { "type", newMixed1 });
		this->valueArray.push_back( { "token", newMixedToken });
		this->valueArray.push_back( { "l", newMixedL });
		this->valueArray.push_back( { "c", newMixedC });
		this->index = 4;
		this->valueBool = true;
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
		if (this->index > 0)
			this->valueBool = true;
		//this->type = "a";
	}
	Mixed(const arr_ls value) {
		_init();
		for (auto [_k, _v] : value) {
			this->valueArray.push_back( { ts(_k), new Mixed((string) _v) });
			this->index = ((long) _k) + 1;
		}
		if (this->index > 0)
			this->valueBool = true;
	}
	Mixed(const tokens_line1 value) {
		_init();
		this->valueArray.push_back( { "0", new Mixed(value._0) });
		this->valueArray.push_back( { "1", new Mixed(value._1) });
		this->type = "a";
		this->index = 2;
		this->valueBool = true;
	}
	Mixed(const tokens_line1_arr value) {
		_init();
		for (auto [_k, _v] : value) {
			this->valueArray.push_back(
					{ ts(_k), new Mixed((tokens_line1) _v) });
			this->index = ((long) _k) + 1;
		}
		if (this->index > 0)
			this->valueBool = true;
		//this->type = "a";
	}
	long getInt() {
		return (long) this->valueNum;
	}
	long getLen() {
		return this->valueArray.size();
	}
	token to_token() {
		token _return;
		if (contains("0") && contains("1")) {
			_return._0 = get_e("0")->valueStr;
			_return._1 = get_e("1")->valueStr;
		} else if (contains("name") && contains("type")) {
			_return._0 = get_e("name")->valueStr;
			_return._1 = get_e("type")->valueStr;
		} else {
			throw InternalException("this mix not a valid token");
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
			throw "not an array to push sV";
		//Mixed *elementPointer = new Mixed(element);
		set_e(key, element);
		this->index++;
		if (index <= tl(key))
			index = tl(key) + 1;
	}
//	template<typename V>
//	void push(const char *key, V element) {
//		set_e(key, element);
//		this->index++;
//	}
	template<typename V>
	void push(int key, V element) {
		set_e(ts(key), element);
		this->index++;
		if (index <= key)
			index = key + 1;
	}
	void push(const Mixed element) {
		add_e(element);
		this->index++;
	}
	void push(const string element) {
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const char *element) {
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(long element) {
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const double element) {
		set_e(ts(this->index), element);
		this->index++;
	}
	void push(const bool element) {
		set_e(ts(this->index), element);
		this->index++;
	}

	template<typename V>
	void replace(int key, V element) {
		string key_str = ts(key);
		this->delete_e(key_str);
		this->push(key_str, element);
	}
	template<typename V>
	void replace(string key, V element) {
		this->delete_e(key);
		this->push(key, element);
	}

	bool contains(string _k) const {
		for (auto _m : this->valueArray) {
			if ((string) _m.first == _k) {
				return true;
				break;
			}
		}
		return false;
	}

	template<typename V>
	void update(int _k, V _v) {
		if (this->contains(ts(_k)))
			this->replace(_k, _v);
		else
			this->push(_k, _v);
	}
	template<typename V>
	void update(string _k, V _v) {
		if (this->contains(_k))
			this->replace(_k, _v);
		else
			this->push(_k, _v);
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
		long _current_pos = 0;
		vector<pair<string, Mixed*>> _newArray;

		for (auto& [_k, _v] : this->valueArray) {
			bool keep = false;
			if (_len > 0)
				keep = (_current_pos >= _pos && _current_pos < (_pos + _len));
			else
				keep = (_current_pos >= _pos);

			if (keep) {
				_newArray.push_back( { _k, new Mixed(*_v) });
			} else {
				_v->unset_r();
				delete _v;
			}
			_current_pos++;
		}

		this->unset_r();
		this->type = "a";
		this->valueArray = _newArray;
		return *this;
	}
	Mixed& operator=(const Mixed &_1) {
		if (this == &_1)  // Check self-assignment
			return *this;
		unset_r();
		this->type = _1.type;
		this->valueStr = _1.valueStr;
		this->valueNum = _1.valueNum;
		this->valueBool = _1.valueBool;
		this->index = _1.index;
//		this->valueArray = map<string, Mixed*>(_1.valueArray);
		for (auto const& [_k, _v] : _1.valueArray) {
			Mixed *_tmp = new Mixed(*_v);
			this->valueArray.push_back( { (string) _k, _tmp });
		}
		return *this;
	}
	int operator=(int number) {
		this->valueNum = (int) number;
		this->type = "n";
		this->valueStr = "";
		this->valueBool = false;
		unset_r();
		return this->valueNum;
	}
	long operator=(long number) {
		this->valueNum = (long) number;
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
	Mixed& operator[](string key) const {
		if (this->type != "a")
			throw InternalException("Getting element of non-array object s.");
		if (contains(key)) {
			return *get_e(key);
		} else {
			//Mixed *_return = new Mixed("");
//			set_e(key, _return);
			//return *_return;
			throw InternalException("Element not exist s: " + key);
		}
		//return new Mixed();
	}
	Mixed& operator[](const char *key) const {
		string _key_str = key;
		return operator[](_key_str);
	}
	Mixed& operator[](int key) const {
		return operator[](ts(key));
	}
	Mixed& operator[](long key) const {
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
	Mixed& operator[](unsigned long key) const {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object l";
		try {
			_return = get_e(ts(key));
		} catch (...) {
			throw "Element not exist l.";
		}
		return *_return;
	}
	Mixed& operator[](float key) const {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = get_e(ts(key));
		} catch (...) {
			throw "Element not exist f.";
		}
		return *_return;
	}
//	void operator=(Mixed &arr) {
//		this->valueNum = 0;
//		this->type = "a";
//		this->valueStr = "";
//		this->valueBool = false;
//		unset_r();
//		this->valueArray = arr.valueArray;
//	}
	operator int() const {
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
	operator long() const {
		if (this->type == "n")
			return (long) this->valueNum;
		if (this->type == "s") {
			try {
				return stoi(this->valueStr);
				return (long) stof(this->valueStr);
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
	operator float() const {
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
	operator string() const {
		if (this->type == "n")
			return ts(this->valueNum);
		if (this->type == "s") {
			return this->valueStr;
		}
		if (this->type == "b") {
			if (this->valueBool)
				return "true";
			else
				return "false";
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return "array";
			else
				return "";
		}
		return "";
	}
	operator bool() const {
		return this->valueBool;
	}
	operator token() const {
		token _return;
		try {
			_return._0 = (string) *get_e("0");
			_return._1 = (string) *get_e("1");
			return _return;
		} catch (...) {
			return token();
		}
		return token();
	}
	tokens_line to_tokens_line() const {
		tokens_line _return;
		string _k;
		Mixed _v;
		try {
			for (auto [_ka, _va] : this->valueArray) {
				_k = (string) _ka;
				_v = *((Mixed*) _va);
				_return[stol(_k)] = token(_v["name"], _v["type"]);
			}
			return _return;
		} catch (...) {
			throw "cannot convert to tokens_line";
		}
		return {};
	}
	arr_ls to_ls() const {
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
	Mixed* get_ref(string key) {
		if (this->type != "a")
			throw InternalException("not an array to get ref");
		return (get_e(key));
	}
//	Mixed* get_ref_add(string key) {
//		if (this->type != "a")
//			throw InternalException("not an array to get ref");
//		if (this->contains(key))
//			return (get_e(key));
//		else
//			this->push(key, Mixed());
//	}
	bool operator==(string _compare) const {
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
	Mixed operator-(Mixed _peer) const {
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
	Mixed operator*(Mixed _peer) const {
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
	bool operator==(Mixed v) const {
		if (this->type == "s" && v.type == "s") {
			return this->valueStr == v.valueStr;
		} else if (this->type == "n" && v.type == "n") {
			return this->valueNum == v.valueNum;
		} else if (this->type == "b" && v.type == "b") {
			return this->valueBool == v.valueBool;
		} else if (this->type == "s" && v.type == "n") {
			return trim(this->valueStr) == ts(v.valueNum);
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
	bool operator!=(Mixed v) const {
		return !operator==(v);
	}
	bool operator==(const char *_str) const {
		return operator==((string) _str);
	}
	bool operator==(token _v) const {
		if (this->type != "a")
			return false;
		if (contains("0")) {
			if (this->operator[]("0") == _v._0
					&& this->operator[]("1") == _v._1) {
				return true;
			}
		} else if (contains("name")) {
			if (this->operator[]("name") == _v._0
					&& this->operator[]("type") == _v._1) {
				return true;
			}
		}
		return false;
	}
	bool operator!=(const char *v) const {
		return !operator==(v);
	}
	const Mixed* at(string _key) const {
		if (!contains(_key))
			throw InternalException("key not found");
		return get_e(_key);
	}
	const Mixed* at(const char *_key_chars) const {
		string _key = (string) _key_chars;
		return at(_key);
	}
	void printPretty(long _tab_lv = 0) const {
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
	string pretty() const {
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
			_return += _v->pretty();
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
			_tmp_valueArray.push_back( { ts(_i), _v });
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
	string get_string() const {
		return this->valueStr;
	}
	string generate_ident(long _tab_lv = 0) const {
		string _return;
		for (long _i = 0; _i < _tab_lv; _i++)
			_return += "\t";
		return _return;
	}
	string create_str(long _tab_lv = 0) const {
		string _return;
		if (this->type == "s") {
			_return += this->valueStr;
			return _return;
		}
		if (this->type == "n") {
			_return += ts(this->valueNum);
			return _return;
		}
		if (this->type == "b") {
			if (this->valueBool)
				_return += "TRUE";
			else
				_return += "FALSE";
			return _return;
		}

		// array, type == a

		_return += "arr: ";
		_return += "\n";
		_return += generate_ident(_tab_lv);
		_return += "[";
		_return += "\n";
		for (auto& [_key0, _val0] : this->valueArray) {
			//ident
			_return += generate_ident(_tab_lv + 1);
			_return += _key0;
			_return += " => ";
			_return += (*_val0).create_str(_tab_lv + 1);
			_return += "\n";
		}
		_return += generate_ident(_tab_lv);
		_return += "]";
		return _return;
	}
	string create_pretty_str(long _tab_lv = 0) const {
		string _return;
		if (this->type == "s") {
			_return += this->valueStr;
			return _return;
		}
		if (this->type == "n") {
			_return += ts(this->valueNum);
			return _return;
		}
		if (this->type == "b") {
			if (this->valueBool)
				_return += "TRUE";
			else
				_return += "FALSE";
			return _return;
		}

		// array, type == a

		_return += "arr: ";
		if (contains("token"))
			_return += (string) operator[]("token");
		_return += " ";
		if (contains("l"))
			_return += (string) operator[]("l");
		_return += " ";
		if (contains("c"))
			_return += (string) operator[]("c");
		_return += "\n";
		_return += generate_ident(_tab_lv);
		_return += "[";
		_return += "\n";
		for (auto& [_key0, _val0] : this->valueArray) {
			if (_key0 == "l" || _key0 == "token" || _key0 == "c")		//ident
				continue;
			_return += generate_ident(_tab_lv + 1);
			_return += _key0;
			_return += " => ";
			_return += (*_val0).create_pretty_str(_tab_lv + 1);
			_return += "\n";
		}
		_return += generate_ident(_tab_lv);
		_return += "]";
		return _return;
	}
	void print_r() const {
		echo(create_pretty_str());
	}
}
;
bool isset(const Mixed &_arr, const string &_k) {
	if (_arr.contains(_k))
		return true;
	return false;
}
bool isset(const Mixed &_arr, long _kl) {
	string _k = ts(_kl);
	if (!_arr.contains(ts(_kl)))
		return false;
	return true;
}
string get_name(const Mixed &_1);
string get_type(const Mixed &_1);
arr_ll get_line_and_column_number(long _starting_pos, const string &_content);
class GreenTeaException {
public:
	Mixed obj;
	GreenTeaException(Mixed &_e) {
		obj = _e;
	}
	GreenTeaException(const char *_e_str) {
		obj = Mixed(string(_e_str));
	}
//	GtlangException(const char *_class_name, const char *_e_str) {
//		obj = Mixed();
//		obj.push("class", "^" + string(_class_name));
//		Mixed _property = Mixed();
//		_property.push("$msg", string(_e_str));
//		obj.push("properties", _property);
//	}
	GreenTeaException(string _class_name, string _e_str) {
		obj = Mixed();
		obj.push("class", "^" + string(_class_name));
		Mixed _property = Mixed();
		_property.push("$msg", string(_e_str));
		_property.push("$token", "");
		_property.push("$line", -1);
		_property.push("$column", -1);
		obj.push("properties", _property);
	}
	GreenTeaException(string _class_name, string _e_str, string _token,
			long _token_pos, string _content) {
		obj = Mixed();
		obj.push("class", "^" + string(_class_name));
		Mixed _property = Mixed();
		_property.push("$msg", string(_e_str));
		_property.push("$token", _token);
		arr_ll _pos = get_line_and_column_number(_token_pos, _content);
		_property.push("$line", _pos[0]);
		_property.push("$column", _pos[1]);
		obj.push("properties", _property);
	}
	GreenTeaException(string _class_name, string _e_str, token _token) {
		obj = Mixed();
		obj.push("class", "^" + string(_class_name));
		Mixed _property = Mixed();
		_property.push("$msg", string(_e_str));
		_property.push("$token", _token._0);
		_property.push("$line", _token._l);
		_property.push("$column", _token._c);
		obj.push("properties", _property);
	}
	GreenTeaException(string _class_name, string _e_str, Mixed _token) {
		obj = Mixed();
		obj.push("class", "^" + string(_class_name));
		Mixed _property = Mixed();
		_property.push("$msg", string(_e_str));
		if (isset(_token, "l") && isset(_token, "c")) {
			_property.push("$token", _token["token"]);
			_property.push("$line", _token["l"]);
			_property.push("$column", _token["c"]);
		} else {
			_property.push("$token", "");
			_property.push("$line", -1);
			_property.push("$column", -1);
		}
		obj.push("properties", _property);
	}
	GreenTeaException(string _e_str) {
		obj = Mixed(_e_str);
	}
};
class GtlangInnerFunctionException: public GreenTeaException {
public:
	GtlangInnerFunctionException(string _class_name, string _e_str) :
			GreenTeaException(_class_name, _e_str) {
	}
	;
};
class GtLangFunctionNotFound {
public:
	string msg;
	GtLangFunctionNotFound(string str) {
		msg = str;
	}
};
void add_pos_to_mix(Mixed &_input, const token &_token) {
	_input.push("token", _token._0);
	_input.push("l", _token._l);
	_input.push("c", _token._c);
}
void add_pos_to_mix(Mixed &_input, const Mixed &_token) {
	_input.push("token", _token["token"]);
	_input.push("l", _token["l"]);
	_input.push("c", _token["c"]);
}
void add_pos_of_1st_token_to_mix(Mixed &_input, const tokens_line &_tokens) {
	add_pos_to_mix(_input, get_1st_ele(_tokens));
}
Mixed get_1st_ele(const Mixed &_arr);
void add_pos_of_1st_token_to_mix(Mixed &_input, const Mixed &_tokens) {
	add_pos_to_mix(_input, get_1st_ele(_tokens));
}
long gt_sizeof(const Mixed &_mixed) {
	return _mixed.valueArray.size();
}

tokens_line to_tokens_line(Mixed &_1) {
	tokens_line _return;
	Mixed _tmp;
	for (auto [_k, _v] : _1.valueArray) {
		_tmp = ((Mixed) *_v);
		_return[tl((string) _k)] = _tmp.to_token();
	}
	return _return;
}
bool is_token(const Mixed &_arr) {
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
//token reset(Mixed _arr) {
//	return (token) *(_arr.valueArray.begin()->second);
//}
void array_shift_no_return(tokens_line &_arr) {
	_arr.erase(_arr.begin());
}
void array_pop_no_return(tokens_line &_arr) {
	_arr.erase(--(_arr.end()));
}

void array_shift_no_return(Mixed &_arr) {
	if (_arr.empty())
		return;
	auto it = (_arr.valueArray.begin());
	_arr.delete_e(it->first);
}
void array_pop_no_return(Mixed &_arr) {
	if (_arr.empty())
		return;
	auto it = --(_arr.valueArray.end());
	_arr.delete_e(it->first);
}

Mixed array_pop(Mixed &_arr) {
	if (_arr.empty())
		return Mixed();
	if (_arr.getType() != "a")
		throw InternalException("not an array to array_pop");
	auto it = (--_arr.valueArray.end());
	Mixed _return = it->second;
	_arr.delete_e(it->first);
	_arr.index--;
	return _return;
}
Mixed array_slicem(const Mixed &_arr, long _pos, long _len = 0) {
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
void reset(Mixed &tokens_arr) {
	tokens_arr.resetKeys();
	//tokens_arr;
}
Mixed array_merge(const Mixed &_1, const Mixed &_2) {
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
		const Mixed &_complex_expr_arr) {
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
			array_push(_return, token(ts(i), "placeholder"));
			_map_placeholders.insert( { _k, _item });
		}
		i++;
	}
	return mixed_to_tokens_line_with_place_holders_rs(_return,
			_map_placeholders);
}
bool in_array(const Mixed &_find, const Mixed &_arr) {
	for (const auto& [_i, _v] : _arr.valueArray) {
		if ((Mixed) _v == _find)
			return true;
	}
	return false;
}
Mixed array_values(const Mixed &_arr) {
	Mixed _return;
	long _i = 0;
	for (auto const& [_k, _v] : _arr.valueArray) {
		_return.push(_i, (*_v));
		_i++;
	}
	return _return;
}
//Mixed array_slice(Mixed _arr, long _pos, long _len = -1) {
////Mixed _return;
//	long _current_pos = 0;
//	if (_len >= 0) {
//		for (auto const& [_ka, _va] : _arr.valueArray) {
//			if (_current_pos < _pos) {
//				((Mixed) *_va).unset_r();
//				_arr.valueArray.erase(_arr.valueArray.begin());
//			} else if (_current_pos >= (_pos + _len)) {
//				((Mixed) *_va).unset_r();
//				_arr.valueArray.erase(_arr.valueArray.begin() + _len);
//			}
//			_current_pos++;
//		}
//	} else {
//		for (auto const& [_ka, _va] : _arr.valueArray) {
//			if (_current_pos < _pos) {
//				((Mixed) *_va).unset_r();
//				_arr.valueArray.erase(_arr.valueArray.begin());
//			} else {
//				break;
//			}
//			_current_pos++;
//		}
//	}
//	_arr.resetKeys();
//	return _arr;
//}
Mixed array_slice(const Mixed &_arr, long _start_pos, long _len = -1) {
	Mixed _return;
	long _end_pos = 0;
	if (_len > -1)
		_end_pos = _start_pos + _len;
	else
		_end_pos = gt_sizeof(_arr);
	long _current_pos = -1;
	for (auto const& [_ka, _va] : _arr.valueArray) {
		_current_pos++;
		if (_current_pos < _start_pos) {
			continue;
		} else if (_current_pos < _end_pos) {
			_return.push(_ka, *_va);
		} else {
			break;
		}

	}
//_arr.resetKeys();
	return _return;
}
string get_type(const Mixed &_1);
//Mixed replace_placeholders_recruisively(Mixed _arr,
//		map<string, Mixed> _map_placeholders) {
//	for (const auto& [_k, _v] : _arr.valueArray) {
////		bool a = is_token((Mixed) *_v);
//		//bool b = (get_type(((Mixed) *_v)) == "placeholder");
//		if (get_type(((Mixed) *_v)) == "placeholder") {
////			if (_v->contains("0"))
//			_arr[(string) _k] = _map_placeholders[(string) _k];
////			else if (_v->contains("name"))
////				_arr[(string) _k] = _map_placeholders["name"];
//		} else if (((Mixed) _v).type == "a") {
//			_arr[_k] = replace_placeholders_recruisively((Mixed) _v,
//					_map_placeholders);
//		}
//	}
//	return _arr;
//}

template<typename K, typename V>
long gt_sizeof(const map<K, V> &_um) {
	return _um.size();
}
Mixed trim_tokens_line_once(Mixed _input) {
	Mixed _return;
	_input.resetKeys();
	for (auto const& [_k_str, _v] : _input.valueArray) {
		long _k = tl(_k_str);
		if ((_k == 0 || _k == (gt_sizeof(_input) - 1))
				&& get_type(*_v) == "spaces")
			continue;
		else
			_return.push(*_v);
	}
	return _return;
}
//template<typename K, typename V>
//long gt_sizeof(const map<K, V> & _um ) {
//	return _um.size();
//}

void reset_keys(Mixed &_1) {
	_1.resetKeys();
}
Mixed remove_empty_elements(Mixed &_input) {
	if (_input.type != "a")
		return _input;
	Mixed _return;
	for (auto const& [_k, _v] : _input.valueArray) {
		if (!((Mixed) *_v).empty())
			_return.push(_k, *_v);
	}
	return _return;
}
void print_r(Mixed &_input, long _tab_lv = 0) {
	_input.print_r();
}
#endif //LIB_MIXED_H_

