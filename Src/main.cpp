import powerctl;
import ntp;

int main()
{
	ntp::client ntp_cl{};
	ntp_cl.get_time();
	power::off();
}
