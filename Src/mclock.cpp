export module mclock;
import correction;

export namespace mclock {
	constexpr int hours(unsigned long long epoch) {
		return static_cast<int>(epoch / 3600 % 24) + correction::hour(epoch);
	}
}
