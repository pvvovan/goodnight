#include <thread>
import <iostream>;
import powerctl;
import ntp;
import human_time;

namespace pc {

class supervisor {
public:
	static void run() {
		std::thread th { [] () -> void {
				ntp::client ntp_cl{};
				for ( ; ; ) {
					std::this_thread::sleep_for(std::chrono::minutes(5));
					auto epoch = ntp_cl.get_epoch();
					const int hh = human_time::hours(epoch);
					const int mm = human_time::minutes(epoch);
					if ((hh >= 22) && (mm >= 30)) {
						power::off();
					}
				}
			}
		};
		th.join();
	}
};

} /* pc */

int main()
{
	pc::supervisor::run();
}
