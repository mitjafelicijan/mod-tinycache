FROM httpd:2.4-alpine

COPY .libs/mod_tinycache.so /usr/local/apache2/modules/mod_tinycache.so
RUN apk add --no-cache libmemcached-libs libmemcached-dev
RUN echo "LoadModule tinycache_module modules/mod_tinycache.so" >> /usr/local/apache2/conf/httpd.conf
