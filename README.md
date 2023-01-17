# TinyCache - Apache 2 Module

<<<<<<< HEAD
<img src="https://user-images.githubusercontent.com/296714/212981638-054dd8d2-d3f5-4280-b509-6f301299a414.png" height="200">
=======
<p align="center">
<img src="https://user-images.githubusercontent.com/296714/212981638-054dd8d2-d3f5-4280-b509-6f301299a414.png" height="200">
</p>
>>>>>>> b6ce894fe141d5c905bb4a54c7131f54e2579bad

**General intentions with this module**

The aim for this project is to provide a simple caching module that taps 
directly into Apache 2. It hooks before and after request and stores raw HTML
into Memcached Server.

Memcached has been chosen due to it's simplicity, but maybe Redis could
also be added.

**Notice: This project is still work in progress!**

## Local development

- Docker with Docker Compose for testing purposes.
- One of the newest Clang or GCC compiler.

This was tested on Fedora 37.

```sh
sudo dnf install \
  httpd-devel httpd openssl-devel libmemcached-awesome-devel
```

```sh
# This will compile the module and save .so file into the .libs subfolder
# which will be created automatically.
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

- [Developer Documentation for the Apache HTTP Server 2.4](https://httpd.apache.org/docs/2.4/developer/)
- [Developing modules for the Apache HTTP Server 2.4](https://httpd.apache.org/docs/2.4/developer/modguide.html)
- [Hook Functions in the Apache HTTP Server 2.x](https://httpd.apache.org/docs/2.4/developer/hooks.html)
