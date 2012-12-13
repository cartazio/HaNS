
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#ifdef __linux__
#include <linux/if.h>
#include <linux/if_tun.h>
#endif

int init_tap_device(char *name) {
	int fd;

#ifdef __linux__
        int ret;
	struct ifreq ifr;
#endif

	if(name == NULL) {
		return -1;
	}

	fd = open("/dev/net/tun", O_RDWR);
	if(fd < 0) {
		return -2;
	}

#ifdef __linux__        
	memset(&ifr, 0x0, sizeof(struct ifreq));

	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
	strncpy(ifr.ifr_name, name, IFNAMSIZ);
	ret = ioctl(fd, TUNSETIFF, (void*) &ifr);
	if(ret != 0) {
		close(fd);
		return -3;
	}
#endif

	return fd;
}
