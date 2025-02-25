#include "csapp.h"

static const char *uidname(uid_t uid) {
  struct passwd *pwd = getpwuid(uid);
  return pwd->pw_name;
}

static const char *gidname(gid_t gid) {
  struct group *grp = getgrgid(gid);
  return grp->gr_name;
}

static int getid(uid_t *uid_p, gid_t *gid_p, gid_t **gids_p) {
  gid_t *gids = NULL;
  //int ngid = 2;
  int groups;
  *uid_p = getuid();
  *gid_p = getgid();
  groups = getgroups(0, NULL);
  gids = malloc(groups * sizeof(gid_t));
  if (getgroups(groups, gids) == -1) {
    perror("groups error");
  }
  *gids_p = gids;
  return groups;
}

int main(void) {
  uid_t uid;
  gid_t *gids, gid;
  int groups = getid(&uid, &gid, &gids);

  printf("uid=%d(%s) gid=%d(%s) ", uid, uidname(uid), gid, gidname(gid));
  printf("groups=%d(%s)", gids[0], gidname(gids[0]));
  for (int i = 1; i < groups; i++)
    printf(",%d(%s)", gids[i], gidname(gids[i]));
  putchar('\n');

  free(gids);

  return 0;
}
