/*
 * $Id: $
 *
 *  Module:  CRYPTO_DIGEST -- Hash and HMAC Externals for GT.M
 *  Created: 12-AUG-2009 14:40
 *  Author:  tmr
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

#include <openssl/evp.h>
#include <openssl/hmac.h>


char * Crypto_Digest_MakeHexDigest (unsigned char * md_value, int md_len) {

  int i;
  char * buf = (char *) malloc (((2 * md_len) +1) * sizeof (char));
  char * beg;

  *buf = '\0'; beg = buf;
  for (i = 0; i < md_len; i++)
    buf += snprintf (buf, sizeof (buf), "%s%02x", buf, md_value [i]);

  return beg;
}

char * Crypto_Digest_Hash (int count, char * algoName, char * data) {

  count = count;
  EVP_MD_CTX mdctx;
  const EVP_MD *md;
  unsigned char md_value [EVP_MAX_MD_SIZE];
  unsigned int md_len;

  OpenSSL_add_all_digests ();
  md = EVP_get_digestbyname (algoName);
  if (!md) return "";

  EVP_MD_CTX_init (&mdctx);
  EVP_DigestInit_ex (&mdctx, md, NULL);
  EVP_DigestUpdate (&mdctx, data, strlen (data));
  EVP_DigestFinal_ex (&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup (&mdctx);

  return Crypto_Digest_MakeHexDigest (md_value, md_len);
}

char * Crypto_Digest_HMAC (int count, char * algoName,
                           char * data, char * key) {

  count = count;
  HMAC_CTX ctx;
  const EVP_MD *md;
  unsigned char hmac_value [EVP_MAX_MD_SIZE];
  unsigned int hmac_len;

  OpenSSL_add_all_digests ();
  md = EVP_get_digestbyname (algoName);
  if (!md) return "";

  HMAC_CTX_init (&ctx);
  HMAC_Init_ex (&ctx, key, strlen (key), md, NULL);
  HMAC_Update (&ctx, (unsigned char *) data, strlen (data));
  HMAC_Final (&ctx, hmac_value, &hmac_len);
  HMAC_CTX_cleanup (&ctx);

  return Crypto_Digest_MakeHexDigest (hmac_value, hmac_len);;
}

/* -- TEST ------ */
#ifdef _CRYPTO_DIGEST_C_TEST
#include <stdio.h>

#define HASH(A,M)       (Crypto_Digest_Hash (0, (A), (M)))
#define PHASH(A,M)      printf ("%-12s (%s) --> %-50s\n", A, M, HASH(A,M))
#define HMAC(A,M,K)     (Crypto_Digest_HMAC (0, (A), (M), (K)))
#define PHMAC(A,M,K)    printf ("%-12s (%s; %s) --> %-50s\n", A, K, M, HMAC(A,M,K))

int main () {
  PHASH ("SHA1", "AHOJ");
  PHASH ("SHA1a", "AHOJ");  /* Unknown algorithm -> empty string */
  PHASH ("SHA256", "AHOJ");
  PHASH ("SHA512", "AHOJ");
  PHASH ("RIPEMD160", "AHOJ");
  PHASH ("MD5", "AHOJ");

  PHMAC ("SHA1", "AHOJ", "SECRET");
  PHMAC ("SHA1a", "AHOJ", "SECRET");  // Unknown algorithm -> empty string
  PHMAC ("SHA256", "AHOJ", "SECRET");
  PHMAC ("SHA512", "AHOJ", "SECRET");
  PHMAC ("RIPEMD160", "AHOJ", "SECRET");
  PHMAC ("MD5", "AHOJ", "SECRET");

  return 0;
}
#endif

// vim: fdm=syntax:fdn=1:tw=74:ts=2:syn=c
