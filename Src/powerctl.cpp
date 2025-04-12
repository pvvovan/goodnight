export module powerctl;
import <iostream>;
#include <sys/reboot.h>    /* Definition of RB_* constants */
#include <unistd.h>

namespace power {
	export void off()
	{
		::reboot(RB_POWER_OFF);
		std::cout << "Good night!!!" << std::endl;
	}
}
