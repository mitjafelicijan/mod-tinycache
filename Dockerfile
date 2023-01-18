FROM alpine:3.17

# Some predefined arguments and setting for this build.
# https://docs.docker.com/engine/reference/builder/#arg
ARG DOCUMENT_ROOT=/var/www/localhost/htdocs
ARG AP_CONFIG_FILE=/etc/apache2/httpd.conf
ARG AP_MODULE_DIR=/usr/lib/apache2

# Install needed packages.
RUN apk add --no-cache bash 
RUN apk add --no-cache apache2 php php-apache2
RUN apk add --no-cache libmemcached-libs libmemcached-dev

# Copy Apache2 module and some testing files.
COPY .libs/mod_tinycache.so ${AP_MODULE_DIR}/mod_tinycache.so
COPY info.php ${DOCUMENT_ROOT}/info.php

# Load Apache module by adding `LoadModule` directive to config file.
RUN echo "LoadModule tinycache_module ${AP_MODULE_DIR}/mod_tinycache.so" >> ${AP_CONFIG_FILE}

# Start Apache webserver in forgound mode so we can see all the logs in console.
CMD ["/usr/sbin/httpd", "-DFOREGROUND"]
