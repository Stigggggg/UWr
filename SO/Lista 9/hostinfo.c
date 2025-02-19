#include "csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  char buf[MAXLINE], srv[MAXLINE];
  int rc, flags;
  char *domain, *service;
  if (argc == 2) {
    domain = argv[1];
    service = NULL;
  } else if (argc == 3) {
    domain = argv[1];
    service = argv[2];
  } else {
    app_error("usage: %s <domain name>\n", argv[0]);
  }

  /* Get a list of addrinfo records */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; //v4 and v6
  hints.ai_socktype = SOCK_STREAM; 
  /* Connections only */
  if ((rc = getaddrinfo(domain, service, &hints, &listp)) != 0)
    gai_error(rc, "getaddrinfo");

  /* Walk the list and display each IP address */
  flags = NI_NUMERICHOST | NI_NUMERICSERV; /* Display address string instead of domain name */
  for (p = listp; p; p = p->ai_next) {
    Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, srv, MAXLINE, flags);
    if (service && p->ai_family == AF_INET6)
      printf("[%s]:%s\n", buf, srv);
    else if (service)
      printf("%s:%s\n", buf, srv);
    else 
      printf("%s\n", buf);
  }

  /* Clean up */
  freeaddrinfo(listp);

  return EXIT_SUCCESS;
}
