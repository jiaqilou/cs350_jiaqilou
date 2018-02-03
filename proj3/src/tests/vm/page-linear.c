/* Encrypts, then decrypts, 2 MB of memory and verifies that the
   values are as they should be. */

#include <string.h>
#include "tests/arc4.h"
#include "tests/lib.h"
#include "tests/main.h"
#include <stdio.h>
#define SIZE (2 * 1024 * 1024)

static char buf[SIZE];

void
test_main (void)
{
  struct arc4 arc4;
  size_t i;

  /* Initialize to 0x5a. */
  msg ("initialize");
  //printf (" checkpomint1 %p \n", &buf);
  memset (buf, 0x5a, sizeof buf);
 // printf (" checkpomint222  \n");
  /* Check that it's all 0x5a. */
  msg ("read pass");
  for (i = 0; i < SIZE; i++) {
    //printf (" i  %d \n", i);
    if (buf[i] != 0x5a)
      fail ("byte %zu != 0x5a", i);
  }

  /* Encrypt zeros. */
  msg ("read/modify/write pass one");
  arc4_init (&arc4, "foobar", 6);
  arc4_crypt (&arc4, buf, SIZE);

  /* Decrypt back to zeros. */
  msg ("read/modify/write pass two");
  arc4_init (&arc4, "foobar", 6);
  arc4_crypt (&arc4, buf, SIZE);

  /* Check that it's all 0x5a. */
  msg ("read pass");
  for (i = 0; i < SIZE; i++)
    if (buf[i] != 0x5a)
      fail ("byte %zu != 0x5a", i);
}
