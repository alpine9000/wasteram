#include <stdlib.h>
#include <proto/exec.h>


static const char*
ramTypeToStr(ULONG ramType)
{
  switch (ramType) {
  case MEMF_CHIP:
    return "CHIP";
  case MEMF_FAST:
    return "FAST";
  case 0:
    return "ANY";
  default:
    return "UNKNOWN";
  }
}


static void
usage(char* name, char* error)
{
  fprintf(stderr, "%s\nusage: %s: size (in bytes) [CHIP/FAST/ANY]\n", error, name);
  exit(1);
}


int
main(int argc, char** argv)
{
  ULONG userSignal = SIGBREAKF_CTRL_C, ramType = 0;
  int done = 0, size = 0;

  if (argc < 2 || argc > 3) {
    usage(argv[0], "wrong number of arguments");
  }

  if (argc >= 2) {
    if (sscanf(argv[1], "%d", &size) != 1) {
      usage(argv[0], "invalid size specified");
    }
  }

  if (argc == 3) {
    if (strcmp(argv[2], "CHIP") == 0) {
      ramType = MEMF_CHIP;
    } else if (strcmp(argv[2], "FAST") == 0) {
      ramType = MEMF_FAST;
    } else if (strcmp(argv[2], "ANY") == 0) {
      ramType = MEMF_ANY;
    } else {
      usage(argv[0], "invalid type (CHIP/FAST/ANY) specified");
    }
  }

  printf("Allocating %d bytes - ctrl-c to exit\n", size);
  void* waste = AllocMem(size, ramType);

  if (!waste) {
    fprintf(stderr, "failed to allocated %d bytes of type %s\n", size, ramTypeToStr(ramType));
    exit(1);
  }

  while (!done) {
    ULONG signals = Wait(userSignal);

    if (signals & userSignal) {
        printf("User Ctrl-C Abort\n");
	done = 1;
    }
  }

  if (waste) {
    FreeMem(waste, size);
  }

  return 0;
}
