/*
 * $Id: $
 *
 * Module:  CRYPTO_DIGEST -- description
 * Created: 28-AUG-2009 20:00
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

#ifndef _CRYPTO_DIGEST_H_
#define _CRYPTO_DIGEST_H_

char * Crypto_Digest_HMAC (int count, char * algoName,
                           char * data, char * key);
char * Crypto_Digest_Hash (int count, char * algoName, char * data);
char * Crypto_Digest_MakeHexDigest (unsigned char * md_value, int md_len);

#endif

// vim: fdm=syntax:fdn=1:tw=74:ts=2:syn=c
