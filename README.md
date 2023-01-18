# TinyCache - Apache 2 Module

### General intentions with this module

The aim for this project is to provide a simple caching module that taps 
directly into Apache 2. It hooks before and after request and stores raw HTML
into [Memcached Server](https://www.memcached.org/).

[Memcached](https://www.memcached.org/) has been chosen due to it's simplicity, 
but maybe [Redis](https://redis.io/) could also be added.

**Notice: This project is still work in progress!**

## Local development

- [Docker with Docker Compose](https://www.docker.com/) for testing purposes.
- One of the newest [Clang](https://clang.llvm.org/) or [GCC](https://gcc.gnu.org/) compiler.

This was tested on Fedora 37.

```sh
sudo dnf install \
  httpd-devel httpd openssl-devel libmemcached-awesome-devel
```

```sh
# This will compile the module and save .so file into the .libs subfolder
# which will be created automatically.

# This will also ran Docker stack with Apache 2 and Memcached.
# You can find more about this in file `devel.yaml` and `Makefile`.
make all run
```

Additional paths provided for Clangd LSP in `compile_flags.txt`.

### Debugging the module

After making a first request couple of new files are available in the Docker
container.

Files are named based a APR hooks:

- APR_HOOK_FIRST
- APR_HOOK_MIDDLE (Is not being used!)
- APR_HOOK_LAST

Read more about about hooks on [Apache Portable Runtime
](https://apr.apache.org/docs/apr/trunk/group___a_p_r___util___hook.html)
website.

```sh
# Check contents of the created files.
docker exec -it CONTAINER_NAME /bin/cat /usr/local/apache2/first.md5.txt
docker exec -it CONTAINER_NAME /bin/cat /usr/local/apache2/last.md5.txt
docker exec -it CONTAINER_NAME /bin/cat /usr/local/apache2/dump.md5.txt

# To check if the MD5 checksum is the same we use `Howdy!` as input string.
# Results from cat Docker `dump.md5.txt` should be the same.
echo -n Howdy! | md5sum

# Check file status (created/modified dates).
docker exec -it CONTAINER_NAME /bin/stat /usr/local/apache2/first.md5.txt
docker exec -it CONTAINER_NAME /bin/stat /usr/local/apache2/last.md5.txt
docker exec -it CONTAINER_NAME /bin/stat /usr/local/apache2/dump.md5.txt
```

## Development resources

- [Developer Documentation for the Apache 2.4](https://httpd.apache.org/docs/2.4/developer/)
- [Developing Modules for the Apache 2.4](https://httpd.apache.org/docs/2.4/developer/modguide.html)
- [Hook Functions in the Apache 2.4](https://httpd.apache.org/docs/2.4/developer/hooks.html)
- [Basic Apache 2 Module Examples](https://people.apache.org/~humbedooh/mods/examples/)
- [Memcached Tutotial and Examples](https://www.tutorialspoint.com/memcached/)
- [Request Processing in Apache](http://www.apachetutor.org/dev/request)
