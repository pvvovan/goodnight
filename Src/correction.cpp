export module correction;

export namespace correction {
	constexpr int hour(unsigned long long epoch) {
		constexpr int MARCH_30 { 31 + 28 + 30 };
		constexpr int OCTOBER_26 {299};
		constexpr int LEAP_YEARS {30};
		const int day = static_cast<int>(epoch % (365 * 24 * 3600) / (24 * 3600)) - LEAP_YEARS;
		if ((MARCH_30 < day) && (day < OCTOBER_26)) {
			return 2;
		} else {
			return 3;
		}
	}
}
