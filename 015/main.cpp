// essential system
#include <stdio.h>
#include <stdint.h>

// customized system
#include <unistd.h>
#include <stdlib.h>
#include <pcap/pcap.h>

// essential user 
#include "debug/debug.h"

// customized user

void pcap_loop_callback(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes)
{
	printf("user:\n");
}

int pcap(void)
{
	int ret = 0;
	char errbuf[PCAP_ERRBUF_SIZE] = {};

	printf("%s\n", pcap_lib_version());
	/** after libpcap 1.10 pcap_init is available 
	ret = pcap_init(PCAP_CHAR_ENC_UTF_8, errbuf);
	if (0 != ret) {
		printf("pcap_init err:%s\n", errbuf);
		return ret;
	}*/

	/*get all pcap devices*/
	pcap_if_t *pcap_alldev = nullptr;
	pcap_if_t *pcap_dev = nullptr;
	ret = pcap_findalldevs(&pcap_alldev, errbuf);
	if (0 != ret) {
		printf("pcap_findalldevs err:%s\n", errbuf);
		return ret;
	}
	for (pcap_dev=pcap_alldev; nullptr!=pcap_dev; pcap_dev=pcap_dev->next) {
		printf("interface name: %s\n", pcap_dev->name);		
	}
	pcap_freealldevs(pcap_alldev);

	/*start capture */
	pcap_t *pcap_fd = nullptr;
	pcap_fd = pcap_create("ens33", errbuf);
	if (nullptr == pcap_fd) {
		printf("pcap_create err:%s\n", errbuf);
		return -1;
	}

	ret = pcap_set_immediate_mode(pcap_fd, 1);
	if (0 != ret) {
		printf("pcap_set_immediate_mode err:%d\n", ret);
	}
	ret = pcap_activate(pcap_fd);
	if (0 != ret) {
		printf("pcap_activate err:%d\n", ret);
		switch (ret)
		{
			case PCAP_ERROR_PERM_DENIED:
				printf("The process doesn't have permission to open the capture source\n");
				break;
			default:
				break;
		}
		pcap_close(pcap_fd);
		return ret;
	}
	

	printf("before pcap_loop\n");
	ret = pcap_loop(pcap_fd, 10, pcap_loop_callback, nullptr);
	printf("pcap_loop return %d\n", ret);


	pcap_close(pcap_fd);
	return 0;
}

int main(void)
{
	// after debug_init, only when receive signal DEBUG_QUIT_SIG
	// g_debug_quit turns to true
	debug_init();


	pcap();
	// all threads should end it's process
	// when g_debug_quit is true or receive signal DEBUG_QUIT_SIG
	printf("enter loop\n");

	g_debug_quit = true;
	while (!g_debug_quit) {
		pause();
	}
	printf("all clean up\n");
	return 0;
}
