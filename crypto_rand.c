/*
 * $Id: $
 *
 * Module:  CRYPTO_RAND -- PRNG Externals for GT.M
 * Created: 12-AUG-2009 14:40
 * Author:  tmr
 */

/*
 *  Copyright (C) 2009 Tomas Morstein, IDEA Systems <tmr&idea.cz>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <openssl/rand.h>

#include "crypto_digest.h"
#include "crypto_rand.h"


/* Bridge between ext-calls and OpenSSL */
char * Crypto_Rand_BasePRNG (int len, bool cs) {

  unsigned char buf [len-1];
  int r;

  for (r = 0; r < len; r++) buf [r] = '\0';

  if (cs) r = RAND_bytes (buf, len);
  else    r = RAND_pseudo_bytes (buf, len);

  return (char *) Crypto_Digest_MakeHexDigest (buf, len);
}

/* Common PRNG */
char * Crypto_Rand_PRNG (int count, int len)
  { count = count; return Crypto_Rand_BasePRNG (len, false); }

/* Cryptographically Secure/Strong PRNG */
char * Crypto_Rand_CSPRNG (int count, int len)
  { count = count; return Crypto_Rand_BasePRNG (len, true); }


/* -- TEST ------ */
#ifdef _CRYPTO_RAND_C_TEST
#include <stdio.h>

#define PRNG(N)       (Crypto_Rand_PRNG (0, (N)))
#define PPRNG(I,N)    printf ("%d --> %s\n", I, PRNG(N))
#define CSPRNG(N)     (Crypto_Rand_CSPRNG (0, (N)))
#define PCSPRNG(I,N)  printf ("%d --> %s\n", I, CSPRNG(N))

#define TEST_LEN      1024

int main () {

  int i;

  for (i = 1; i <= 10; i++) PPRNG (i, TEST_LEN);
  for (i = 1; i <= 10; i++) PCSPRNG (i, TEST_LEN);

  return 0;
}
#endif

// vim: fdm=syntax:fdn=1:tw=74:ts=2:syn=c
