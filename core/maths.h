/*
 * maths.h
 *
 *  Created on: Jun 3, 2025
 *      Author: t
 */

#ifndef CORE_MATHS_H_
#define CORE_MATHS_H_

Mixed gt_abs(const Mixed & _input ) {
	return abs((double) _input[0]);
}

Mixed gt_sqrt(const Mixed & _input ) {
	return sqrt((double) _input[0]);
}

Mixed gt_pow(const Mixed & _input ) {
	return pow((double) _input[0], (double) _input[1]);
}

Mixed gt_exp(const Mixed & _input ) {
	return exp((double) _input[0]);
}

Mixed gt_log(const Mixed & _input ) {
	return log((double) _input[0]);
}

Mixed gt_log10(const Mixed & _input ) {
	return log10((double) _input[0]);
}
Mixed gt_sin(const Mixed & _input ) {
	return sin((double) _input[0]);
}

Mixed gt_cos(const Mixed & _input ) {
	return cos((double) _input[0]);
}

Mixed gt_tan(const Mixed & _input ) {
	return tan((double) _input[0]);
}

Mixed gt_asin(const Mixed & _input ) {
	return asin((double) _input[0]);
}

Mixed gt_acos(const Mixed & _input ) {
	return acos((double) _input[0]);
}

Mixed gt_atan(const Mixed & _input ) {
	return atan((double) _input[0]);
}

Mixed gt_round(const Mixed & _input ) {
	return round((double) _input[0]);
}

Mixed gt_floor(const Mixed & _input ) {
	return floor((double) _input[0]);
}

Mixed gt_ceil(const Mixed & _input ) {
	return ceil((double) _input[0]);
}

Mixed gt_trunc(const Mixed & _input ) {
	return trunc((double) _input[0]);
}

void gt_init_random() {
	srand(time(nullptr));
	//return Mixed();
}

Mixed gt_rand_int(const Mixed & _input ) {
	srand(time(nullptr));
	return rand() % ((long) _input[1] - (long) _input[0] + 1) + (long) _input[0];
}

Mixed gt_rand_float(const Mixed & _unused ) {
	srand(time(nullptr));
	return static_cast<double>(rand()) / RAND_MAX;
}
Mixed gt_echo_current_time(const Mixed & _input ) {
	string _separator = ":";
	if (isset(_input, 0))
		_separator = (string) _input[0];
	time_t now = time(nullptr);
	tm *local = localtime(&now);

	string _return = ts(local->tm_hour) + _separator + ts(local->tm_min)
			+ _separator + ts(local->tm_sec);
	return _return;
}
Mixed gt_echo_current_date(const Mixed & _input ) {
	string _separator = "-";
	if (isset(_input, 0))
		_separator = (string) _input[0];
	time_t now = time(nullptr);
	tm *local = localtime(&now);
	string _return = ts(local->tm_year + 1900) + _separator
			+ ts(local->tm_mon + 1) + _separator + ts(local->tm_mday);
	return Mixed();
}
Mixed gt_time(const Mixed & _input ) {
	time_t _time;
	if (isset(_input, 0)) {
		_time = static_cast<std::time_t>(long(_input[0]));
	} else {
		_time = time(nullptr);
	}
	tm *local = localtime(&_time);
	Mixed _return;
	_return.push("hour", (local->tm_hour));
	_return.push("min", (local->tm_min));
	_return.push("sec", (local->tm_sec));
	_return.push("year", (local->tm_year + 1900));
	_return.push("month", (local->tm_mon + 1));
	_return.push("day", (local->tm_mday));
	_return.push("weekday", (local->tm_wday)); // 0 = Sunday, 1 = Mon, ...
	_return.push("yearday", (local->tm_yday));   // 0-365

	int wday = (local->tm_wday == 0) ? 7 : local->tm_wday; // ISO: 1 = Mon, 7 = Sun
	int week = (local->tm_yday + 7 - wday) / 7 + 1;
	_return.push("week", ts(week));
	return _return;
}
Mixed gt_diff_time(const Mixed & _input ) {
	return gt_time((long) _input[1] - (long) _input[0]);
}
Mixed gt_format_time(const Mixed & _input ) {
	string _format = "%Y-%m-%d %H:%M:%S";
	if (isset(_input, 1)) {
		_format = string(_input[1]);
	}
	time_t now = time(nullptr);
	if (isset(_input, 0) && _input[0] != "") {
		now = static_cast<std::time_t>((long) _input[0]);
	}
	tm *tm_now = localtime(&now);

	std::ostringstream oss;
	oss << std::put_time(tm_now, _format.c_str());

	string _return = oss.str();
	return _return;
}
Mixed gt_timestamp_now(const Mixed & _unused ) {
	return static_cast<long>(time(nullptr));
}
#endif /* CORE_MATHS_H_ */
