import <iostream>;
import powerctl;
import ntp;
import mclock;

int main()
{
	ntp::client ntp_cl{};
	std::cout << mclock::hours(ntp_cl.get_epoch()) << std::endl;
	power::off();
}
