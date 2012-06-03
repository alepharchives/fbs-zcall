EXTCRYPTO ; $Id: $
        ;
        ; Module:      EXTCRYPTO
        ; Created:     13-AUG-2009 11:53
        ; Author:      tmr
        ;
        ;--- DESCRIPTION -------------------------------------------------
        ; CRYPTO external library calls
        ;-----------------------------------------------------------------
        ;
        ; Copyright (C) 2009 Tomas Morstein, IDEA Systems <tmr&idea.cz>
        ;
        ; This program is free software: you can redistribute it and/or
        ; modify it under the terms of the GNU Affero General Public
        ; License as published by the Free Software Foundation, either
        ; version 3 of the License, or (at your option) any later
        ; version.
        ;
        ; This program is distributed in the hope that it will be useful,
        ; but WITHOUT ANY WARRANTY; without even the implied warranty of
        ; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        ; GNU Affero General Public License for more details.
        ;
        ; You should have received a copy of the GNU Affero General
        ; Public License along with this program. If not, see
        ; <http://www.gnu.org/licenses/>.
        Q

        ;-----------------------------------------------------------------
MID()   ; Module ID
        ;-----------------------------------------------------------------
        Q $P($ZPOS,"^",2)

        ;-----------------------------------------------------------------
PRNG(N) ; Generate a pseudo-random sequence of N bytes and return its hexdigest
        ;-----------------------------------------------------------------
        Q $&CRYPTO.PRNG(N)

        ;-----------------------------------------------------------------
CSPRNG(N) ; The same as PRNG() but using Cryptographically Secure PRNG
        ;-----------------------------------------------------------------
        Q $&CRYPTO.CSPRNG(N)

        ;-----------------------------------------------------------------
HASH(A,X) ; Compute a hash of @X string using an algorithm @A
        ;-----------------------------------------------------------------
        ;Q $TR($$CMDPIPE^CMNUTL("openssl "_$$TOLOWER^CMNUTL(A),X),$C(10,13),"")
        Q $&CRYPTO.HASH(A,X)

        ;-----------------------------------------------------------------
HMAC(A,X,K) ; Compute a HMAC of @X string using an algorithm @A and @K key
        ;-----------------------------------------------------------------
        Q $&CRYPTO.HMAC(A,X,K)

        ;-----------------------------------------------------------------
        ; Some shortcuts...
        ;-----------------------------------------------------------------
MD5(X)             Q $$HASH($P($ZPOS,"^",1),X)
SHA1(X)            Q $$HASH($P($ZPOS,"^",1),X)
SHA256(X)          Q $$HASH($P($ZPOS,"^",1),X)
SHA512(X)          Q $$HASH($P($ZPOS,"^",1),X)
RIPEMD160(X)       Q $$HASH($P($ZPOS,"^",1),X)

HMACMD5(X,K)       Q $$HMAC($P($P($ZPOS,"^",1),"HMAC",2),X,K)
HMACSHA1(X,K)      Q $$HMAC($P($P($ZPOS,"^",1),"HMAC",2),X,K)
HMACSHA256(X,K)    Q $$HMAC($P($P($ZPOS,"^",1),"HMAC",2),X,K)
HMACSHA512(X,K)    Q $$HMAC($P($P($ZPOS,"^",1),"HMAC",2),X,K)
HMACRIPEMD160(X,K) Q $$HMAC($P($P($ZPOS,"^",1),"HMAC",2),X,K)

; vim: fdm=syntax:fdn=3:tw=74:ts=2:syn=mumps
