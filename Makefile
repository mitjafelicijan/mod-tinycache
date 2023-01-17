all: mod_tinycache.so

mod_tinycache.so: main.c
	apxs -c -o mod_tiny_cache.so main.c -lcrypto -lmemcached

clean:
	rm -Rf *.lo *.slo *.la .libs/

run:
	docker-compose -f devel.yaml up --no-deps --build --remove-orphans --force-recreate

spellcheck:
	hunspell -d en_US README.md
