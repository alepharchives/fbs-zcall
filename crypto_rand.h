/*
 * $Id: $
 *
 * Module:  CRYPTO_RAND -- description
 * Created: 28-AUG-2009 19:59
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

#ifndef _CRYPTO_RAND_H_
#define _CRYPTO_RAND_H_

char * Crypto_Rand_PRNG (int count, int len);
char * Crypto_Rand_CSPRNG (int count, int len);

#endif

// vim: fdm=syntax:fdn=1:tw=74:ts=2:syn=c
