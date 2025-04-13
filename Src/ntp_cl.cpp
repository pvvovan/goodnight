module;
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

export module ntp;

namespace ntp {
	struct packet {
		uint8_t Mode: 3; // Association mode
		uint8_t VN: 3; // Version Number, NTP version number, typically 4
		uint8_t LI: 2; // Leap Indicator, Warning of leap second insertion or deletion
		uint8_t Stratum: 8; // Indicates the distance from the reference clock
		uint8_t Poll: 8; // Maximum interval between successive messages, in log₂(seconds). Typical range is 6 to 10.
		uint8_t Precision: 8; // Signed log₂(seconds) of system clock precision (e.g., –18 ≈ 1 microsecond)

		uint32_t RootDelay; // Total round-trip delay to the reference clock, in NTP short format.
		uint32_t RootDispersion; // Total dispersion to the reference clock, in NTP short format.
		uint32_t ReferenceID; // Identifies the specific server or reference clock; interpretation depends on Stratum.

		uint64_t ReferenceTimestamp; // Time when the system clock was last set or corrected, in NTP timestamp format.
		uint64_t OriginTimestamp; // Time at the client when the request departed, in NTP timestamp format.
		uint64_t ReceiveTimestamp; // Time at the server when the request arrived, in NTP timestamp format.
		uint64_t TransmitTimestamp; // Time at the server when the response left, in NTP timestamp format.
	};
	export class client {
		public:
		unsigned long long get_time() {
			packet pkt { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			pkt.LI = 0; // no warning
			pkt.VN = 0b011; // ntp version number 3
			pkt.Mode = 0b011; // client

			addrinfo hints{};
			addrinfo* result;
			addrinfo* rp;

			hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
			hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
			hints.ai_flags = 0;
			hints.ai_protocol = 0;          /* Any protocol */

			int s = ::getaddrinfo("0.pool.ntp.org", "123", &hints, &result);
			if (s != 0)
				::exit(EXIT_FAILURE);

			int sfd = -1;
			timeval timeout_time_value{};
			timeout_time_value.tv_sec = 1; // timeout in seconds
			for (rp = result; rp != NULL; rp = rp->ai_next) {
				sfd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
				if (sfd == -1)
					continue;

				::setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout_time_value, sizeof(timeout_time_value));
				if (::connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
					break; /* Success */
				}

				::close(sfd);
			}
			::freeaddrinfo(result); /* No longer needed */

			if (rp == nullptr) /* No address succeeded */
				::exit(EXIT_FAILURE);

			ssize_t nwrite = ::write(sfd, &pkt, sizeof(pkt));
			if (nwrite != sizeof(pkt)) {
				::exit(EXIT_FAILURE);
			}

			ssize_t nread = ::read(sfd, &pkt, sizeof(pkt));
			if (nread == -1) {
				::exit(EXIT_FAILURE);
			}

			::close(sfd);

			return ::ntohl(static_cast<uint32_t>(pkt.TransmitTimestamp));
		}
	};
}
