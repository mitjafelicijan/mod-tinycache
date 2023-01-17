FROM httpd:2.4-alpine

COPY .libs/mod_tiny_cache.so /usr/local/apache2/modules/mod_tiny_cache.so
RUN apk add --no-cache libmemcached-libs libmemcached-dev
RUN echo "LoadModule tiny_cache_module modules/mod_tiny_cache.so" >> /usr/local/apache2/conf/httpd.conf
