#include <stdio.h>

#include "httpd.h"

#include "http_config.h"
#include "http_request.h"

static int tc_before_request(request_rec *r)
{
    printf("Hi Apache 2 Module!\n");
    return OK;
}

static void tc_register_hooks(apr_pool_t *pool)
{
    ap_hook_handler(tc_before_request, NULL, NULL, APR_HOOK_FIRST);
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
