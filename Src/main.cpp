import <iostream>;
import powerctl;
import ntp;

int main()
{
	ntp::client ntp_cl{};
	std::cout << ntp_cl.get_time() << std::endl;
	power::off();
}
