# TinyCache - Apache 2 Module

The aim for this project is to provide a simple caching module that taps 
directly into Apache 2. It hooks before and after request and stores raw HTML
into Memcached Server.

Memcached has been chosen due to it's simplicity, but maybe Redis could
also be added.

**⚠️ This project is still work in progress!**

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

## Development resources

- [Developer Documentation for the Apache HTTP Server 2.4](https://httpd.apache.org/docs/2.4/developer/)
- [Developing modules for the Apache HTTP Server 2.4](https://httpd.apache.org/docs/2.4/developer/modguide.html)
- [Hook Functions in the Apache HTTP Server 2.x](https://httpd.apache.org/docs/2.4/developer/hooks.html)
