#include <stdio.h>

#include "apr_hooks.h"
#include "httpd.h"

#include "http_config.h"
#include "http_request.h"

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
    write_dump_file("/usr/local/apache2/dump.first.txt", "tc_handle_first::arp_hook_first\n");
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
