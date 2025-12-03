module;
#include <sys/reboot.h>

export module powerctl;
import <iostream>;

namespace power {

export void off()
{
	::reboot(RB_POWER_OFF);
	std::cout << "Good night!!!" << std::endl;
}

} /* power */
