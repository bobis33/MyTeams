#include "step1.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // disable printf buffering for stdout.
  // do not remove please.
  setvbuf(stdout, NULL, _IONBF, 0);

  /**
   * EXAMPLE CODE WHICH WILL NOT WORK ...
   * PLEASE PATCH IT ;-)
   */
  char buffer[MAX_COMMAND_LENGTH + 1] = {0};
  int status = 0;
  do {
    memset(buffer, 0, MAX_COMMAND_LENGTH);
    status = read(0, buffer, MAX_COMMAND_LENGTH);
    if (status == -1) {
      perror("read()");
      return EPI_EXIT_FAILURE;
    } else {
        fd_set rfds;
        rv_select = select(1, &rfds, NULL, NULL, NULL);
        if (rv_select == -1) {
            perror("select()");
            return EPI_EXIT_FAILURE;
        } else {

        }
      if (on_command(buffer) == false) {
        return EPI_EXIT_FAILURE;
      }
    }
  } while (status);
  return EPI_EXIT_SUCCESS;
}
