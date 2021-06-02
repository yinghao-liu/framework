# 016
program with socket

## Description
> man 7 socket

```c
#include <sys/socket.h>
struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}

struct sockaddr_storage;

struct sockaddr_storage is  large  enough  and is aligned properly,(In particular, it is large enough to hold IPv6 socket addresses.)  
The structure includes the following  field, which  can  be  used  to  identify the type of socket address actually stored in the structure:
    sa_family_t ss_family;
The sockaddr_storage structure is useful in programs that  must  handle  socket  addresses  in  a  generic  way  
(e.g., programs that must deal with both IPv4 and IPv6 socket addresses).
```

## ip
Linux IPv4 protocol implementation
> man 7 ip

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
raw_socket = socket(AF_INET, SOCK_RAW, protocol);
       
struct sockaddr_in {
   sa_family_t    sin_family; /* address family: AF_INET */
   in_port_t      sin_port;   /* port in network byte order */
   struct in_addr sin_addr;   /* internet address */
};

/* Internet address. */
struct in_addr {
   uint32_t       s_addr;     /* address in network byte order */
};
```

## ipv6
Linux IPv6 protocol implementation
> man 7 ipv6

```c
#include <sys/socket.h>
#include <netinet/in.h>

tcp6_socket = socket(AF_INET6, SOCK_STREAM, 0);
raw6_socket = socket(AF_INET6, SOCK_RAW, protocol);
udp6_socket = socket(AF_INET6, SOCK_DGRAM, protocol);
struct sockaddr_in6 {
   sa_family_t     sin6_family;   /* AF_INET6 */
   in_port_t       sin6_port;     /* port number */
   uint32_t        sin6_flowinfo; /* IPv6 flow information */
   struct in6_addr sin6_addr;     /* IPv6 address */
   uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
};

struct in6_addr {
   unsigned char   s6_addr[16];   /* IPv6 address */
};
```


## unix
sockets for local interprocess communication
> man 7 unix

```c
#include <sys/socket.h>
#include <sys/un.h>

unix_socket = socket(AF_UNIX, type, 0);
error = socketpair(AF_UNIX, type, 0, int *sv);

struct sockaddr_un {
   sa_family_t sun_family;               /* AF_UNIX */
   char        sun_path[108];            /* Pathname */
};
```

## netlink
communication between kernel and user space (AF_NETLINK)
> man 7 netlink

```c
#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

netlink_socket = socket(AF_NETLINK, socket_type, netlink_family);
struct sockaddr_nl {
   sa_family_t     nl_family;  /* AF_NETLINK */
   unsigned short  nl_pad;     /* Zero */
   pid_t           nl_pid;     /* Port ID */
   __u32           nl_groups;  /* Multicast groups mask */
};
```




## packet
packet interface on device level
> man 7 packet

```c
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */

packet_socket = socket(AF_PACKET, int socket_type, int protocol);

struct sockaddr_ll {
   unsigned short sll_family;   /* Always AF_PACKET */
   unsigned short sll_protocol; /* Physical-layer protocol */
   int            sll_ifindex;  /* Interface number */
   unsigned short sll_hatype;   /* ARP hardware type */
   unsigned char  sll_pkttype;  /* Packet type */
   unsigned char  sll_halen;    /* Length of address */
   unsigned char  sll_addr[8];  /* Physical-layer address */
};
```



## Notes


## reference
