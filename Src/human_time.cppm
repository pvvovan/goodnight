export module human_time;
import correction;

export namespace human_time {

constexpr int hours(unsigned long long epoch) {
	return static_cast<int>(epoch / 3600 % 24) + correction::hour(epoch);
}

constexpr int minutes(unsigned long long epoch) {
	return static_cast<int>(epoch / 60 % 60);
}

} /* human_time */
