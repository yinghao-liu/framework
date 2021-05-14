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
	printf("user:%p, pcap_pkhdr:%p, byte:%p\n", user, h, bytes);
	if (nullptr == h || nullptr == bytes)
	{
		return;
	}
	printf("caplen:%u, len:%u\n", h->caplen, h->len);
	uint32_t index = 0;
	for (index=0; index<h->caplen; index++) {
		if (0 == index%8 && 0 != index) {
			printf("  ");
		}
		if (0 == index%16 && 0 != index) {
			printf("\n");
		}
		printf("%02x ", bytes[index]);
	}
	printf("\n");
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
	pcap_fd = pcap_create("lo", errbuf);
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
	
	/*********** link-layer header type *************/
	int *link_type = nullptr;
	ret = pcap_list_datalinks(pcap_fd, &link_type);
	if (ret <= 0) {
		printf("pcap_list_datalinks error %s\n", pcap_geterr(pcap_fd));
		pcap_close(pcap_fd);
		return ret;
	}
	printf("ret:%d\n", ret);
	printf("link_type:%p\n", link_type);
	for (int i=0; i<ret; i++) {
		printf("link_type:%d:%s\n", *(link_type+i), pcap_datalink_val_to_name(*(link_type+i)));
	}
	pcap_free_datalinks(link_type);

	/*********** Reading packets *************/
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
