#
#  Copyright (C) 2009 Tomas Morstein, IDEA Systems <tmr&idea.cz>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

OS!=uname -m
CC=gcc
SED=sed
PWD!=pwd
INC=
LIB=

# -- XXX: For x86_64 with GT.M x86
#CC:=$(CC) -m32
#INC=-I$(PWD)/openssl-0.9.8k/include
#LIB=-L$(PWD)/openssl-0.9.8k
# --
INC+=-I/usr/include/openssl

CFLAGS+=-O3 -W -Wall -I${gtm_dist} $(INC) #-O0 -ggdb
LDFLAGS+=$(LIB) -lssl -lcrypto 
XCFIL="`echo $@ | tr '[:lower:]' '[:upper:]'`"
EXTLOAD=extload
EXTRTNS=$(PWD)

TARGETS=crypto

all:	$(TARGETS) mkxcloader

# Test program w/debugging...
test:
	gcc -m32 crypto_digest.c -O0 -ggdb3 -W -Wall -I${gtm_dist} \
	  -Iopenssl-0.9.8k/include -Lopenssl-0.9.8k -lssl -lcrypto \
	  -o test_digest.bin -D_CRYPTO_DIGEST_C_TEST
	gcc -m32 crypto_digest.c crypto_rand.c -O0 -ggdb3 -W -Wall -I${gtm_dist} \
	  -Iopenssl-0.9.8k/include -Lopenssl-0.9.8k -lssl -lcrypto \
	  -o test_rand.bin -D_CRYPTO_RAND_C_TEST

crypto:
	@echo "Building $@..."
	$(CC) $(CFLAGS) -c -fPIC $@_*.c
	@echo "Linking $@..."
	$(CC) crypto_*.o $(LDFLAGS) -o lib$@.so -shared
	@echo "Creating XC index..."
	@$(SED) -e 's,@@SHRLIB@@,$(PWD)/lib$@.so,g' $(XCFIL).xc.in > $(XCFIL).xc

mkxcloader:
	@echo -n "Creating XC loader scripts..."
	@echo -n " csh"
	@ls -1 *.xc | tr '[:lower:]' '[:upper:]' | \
	  awk -F'.XC' '{ print "setenv GTMXC_"$$1" $(EXTRTNS)/"$$1".xc" }' \
	  > $(EXTLOAD).csh
	@echo -n " sh"
	@ls -1 *.xc | tr '[:lower:]' '[:upper:]' | \
	  awk -F'.XC' '{ print "export GTMXC_"$$1"=$(EXTRTNS)/"$$1".xc" }' \
	  > $(EXTLOAD).sh
	@echo "."

clean:
	@echo "Cleanup..."
	@rm -f *.o *.so *.xc $(EXTLOAD)
