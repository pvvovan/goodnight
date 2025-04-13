#include <thread>
import <iostream>;
import powerctl;
import ntp;
import mclock;

namespace pc {
	class supervisor {
		public:
			static void run() {
				std::thread th { [] () -> void {
						ntp::client ntp_cl{};
						for ( ; ; ) {
							std::this_thread::sleep_for(std::chrono::seconds(5));
							const int hh = mclock::hours(ntp_cl.get_epoch());
							if (hh >= 23) {
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
