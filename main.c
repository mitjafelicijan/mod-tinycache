// clang-format off
#include <stdio.h>
#include <openssl/evp.h>
#include <libmemcached/memcached.h>
#include "httpd.h"
#include "http_config.h"
#include "http_request.h"
#include "apr_hooks.h"
// clang-format on

#define MEMCACHED_SERVER_IP "192.168.64.113"
#define MEMCACHED_SERVER_PORT 11211

void memcached_set_key(const char *key, const char *value)
{
    memcached_st *memc;
    memcached_return rc;

    // FIXME: Fix connection, it shouldn't connect to Memcached every request!
    memc = memcached_create(NULL);
    memcached_server_add(memc, MEMCACHED_SERVER_IP, MEMCACHED_SERVER_PORT);

    // FIXME: Add proper error handling if something goes wrong and write
    //        write errors to a separate error log file for this module.
    rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
    if (rc != MEMCACHED_SUCCESS)
    {
        printf("Error setting value: %s\n", memcached_strerror(memc, rc));
    }

    // Freeing some memory.
    memcached_free(memc);
}

char *memcached_get_key(const char *key, const char *value)
{
    memcached_st *memc;
    memcached_return rc;

    // FIXME: Fix connection, it shouldn't connect to Memcached every request!
    memc = memcached_create(NULL);
    memcached_server_add(memc, MEMCACHED_SERVER_IP, MEMCACHED_SERVER_PORT);

    // Get the value from Memcache.
    size_t value_len;
    uint32_t flags;

    // FIXME: Add proper error handling if something goes wrong and write
    //        write errors to a separate error log file for this module.
    char *result = memcached_get(memc, key, strlen(key), &value_len, &flags, &rc);
    if (rc != MEMCACHED_SUCCESS)
    {
        printf("Error getting value: %s\n", memcached_strerror(memc, rc));
        return NULL;
    }

    // Freeing some memory.
    memcached_free(memc);

    // Return back to caller.
    return result;
}

char *md5sum(const char *input_string)
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;
    unsigned char digest[EVP_MAX_MD_SIZE];

    // Generate MD5 digest of input string.
    md = EVP_md5();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input_string, strlen(input_string));
    EVP_DigestFinal_ex(mdctx, digest, &md_len);
    EVP_MD_CTX_free(mdctx);

    // Convert to characters.
    static char md5hex[33];
    for (int i = 0; i < 16; ++i)
    {
        sprintf(&md5hex[i * 2], "%02x", (unsigned int)digest[i]);
    }

    return md5hex;
}

void write_dump_file(const char *filename, const char *content)
{
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        fwrite(content, sizeof(char), strlen(content), file);
        fclose(file);
    }
}

static int tc_handler_first(request_rec *r)
{
    // Generate MD5 checksum from string.
    char *md5hex = md5sum("Howdy!");

    // Store something in the Memcached server.
    memcached_set_key("howdy", "dandy");

    write_dump_file("/usr/local/apache2/dump.first.txt", "tc_handle_first::arp_hook_first\n");
    write_dump_file("/usr/local/apache2/dump.md5.txt", md5hex);
    return OK;
}

static int tc_handler_last(request_rec *r)
{
    write_dump_file("/usr/local/apache2/dump.last.txt", "tc_handle_last::arp_hook_last\n");
    return OK;
}

static void tc_register_hooks(apr_pool_t *pool)
{
    ap_hook_fixups(tc_handler_first, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_fixups(tc_handler_last, NULL, NULL, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA tiny_cache_module = {
    STANDARD20_MODULE_STUFF,
    NULL,             /* Per-directory configuration handler */
    NULL,             /* Merge handler for per-directory configurations */
    NULL,             /* Per-server configuration handler */
    NULL,             /* Merge handler for per-server configurations */
    NULL,             /* Any directives we may have for httpd */
    tc_register_hooks /* Our hook registering function */
};
