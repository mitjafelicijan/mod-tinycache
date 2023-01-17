all: mod_tinycache.so

mod_tinycache.so: mod_tinycache.c
	apxs -c -o mod_tinycache.so mod_tinycache.c -lcrypto -lmemcached

clean:
	rm -Rf *.lo *.slo *.la .libs/

run:
	docker-compose -f devel.yaml up --no-deps --build --remove-orphans --force-recreate

spellcheck:
	hunspell -d en_US README.md
