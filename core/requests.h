/*
 * requests.h
 *
 *  Created on: Jun 3, 2025
 *      Author: t
 */

#ifndef CORE_REQUESTS_H_
#define CORE_REQUESTS_H_

string escapeString(const string &s) {
	string out = "\"";
	for (char c : s) {
		if (c == '"')
			out += "\\\"";
		else if (c == '\\')
			out += "\\\\";
		else
			out += c;
	}
	out += "\"";
	return out;
}
string to_json(Mixed &_m) {
	if (_m.type == "s")
		return escapeString(_m.valueStr);
	if (_m.type == "n")
		return ts(_m.valueNum);
	if (_m.type == "b")
		return _m.valueBool ? "true" : "false";
	if (_m.type == "a") {
		string _result = "";
		_result += "{";
		for (auto [_k, _v] : _m.valueArray) {
			_result += escapeString(_k) + ": " + to_json(*_v);
			_result += ", ";
		}
		_result = substr(_result, 0, strlen(_result) - 2);
		_result += "}";
		return _result;
	}
	return "";
}
Mixed gt_fetch_url(const Mixed & _input ) {
	Mixed _return;
	string url = (string) _input[0];
	CURL *curl;
	CURLcode res;
	string readBuffer;

	curl = curl_easy_init();
	if (!curl) {
		throw GreenTeaException("RequestException", "Error initializing curl ",
				_input[0]);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		curl_easy_cleanup(curl);
		throw GreenTeaException("RequestException", "Error getting URL",
				_input[0]);
	}

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
	curl_easy_cleanup(curl);

	if (http_code != 200) {
		;
	}

	_return.push("response", readBuffer);
	_return.push("code", http_code);
	return _return;
}

struct RestAPIResult {
public:
	string _response;
	long _code;
	RestAPIResult() {
		_response = "";
		_code = 0;
	}
	RestAPIResult(string _str, long _long) {
		_response = _str;
		_code = _long;
	}
};
RestAPIResult send_rest_api(const std::string &url, const std::string &method =
		"GET", const std::string &data = "",
		const std::vector<std::string> &headersList = { },
		bool verifySSL = true) {
	CURL *curl;
	CURLcode res;
	std::string response;

	curl_global_init (CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	long http_code = 0;
	if (curl) {
		// Set URL
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Set headers
		struct curl_slist *headers = nullptr;
		for (const auto &h : headersList) {
			headers = curl_slist_append(headers, h.c_str());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		if (method == "POST") {
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		} else if (method == "PUT") {
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		} else if (method == "DELETE") {
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		} else if (method != "GET") {
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, verifySSL ? 1L : 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, verifySSL ? 2L : 0L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			throw GtlangInnerFunctionException("RequestException",
					"Failed to call REST API");
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
	return RestAPIResult(move(response), http_code);
}

Mixed gt_call_restapi(const Mixed & _input ) {
	string _url = _input[0];
	string _method = _input[1];
	Mixed _body_m = _input[2];
	string _body;
	if (_body_m.type == "a")
		_body = to_json(_body_m);
	else
		_body = (string) _body_m;
	Mixed _headers_mixed = _input[4];
	vector < string > _headers;
	Mixed _return;
	_return.push("response", "");
	_return.push("code", 0);
	for (auto [_k, _v] : _headers_mixed.valueArray) {
		_headers.push_back((string) * _v);
	}
	bool _require_ssl = false;
	if (isset(_input, 5))
		_require_ssl = _input[5];
	RestAPIResult _res;
	try {
		_res = send_rest_api(_url, strtoupper(_method), _body, _headers,
				_require_ssl);
	} catch (GtlangInnerFunctionException) {
		return _return;
	}
	_return["response"] = _res._response;
	_return["code"] = _res._code;
	return _return;
}
#endif /* CORE_REQUESTS_H_ */
