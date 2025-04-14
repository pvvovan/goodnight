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
							const int hh = human_time::hours(ntp_cl.get_epoch());
							const int mm = human_time::minutes(ntp_cl.get_epoch());
							if ((hh >= 23) && (mm >= 30)) {
								power::off();
							}
						}
					}
				};
				th.join();
			}
	};
}

int main()
{
	pc::supervisor::run();
}
