#include <stdio.h>
#include <string.h>

// Vendor list
#define UNKNOWN 0
#define ERICSSON_GPON_OLD 1
#define TPLINK_OLD 2
#define TOMATO_UNIFIED_OLD 3
#define ZYXEL_OLD 4
#define DLINK_OLD 5
#define HIKVISION_CAM_OLD 6

// Detect by
#define ERICSSONOLD_TITLE "GPON Home Gateway"
#define ERICSSONOLD_LOGINHTML "url=/login.html"
#define TPLINKOLD_TITLE "TPLINK"

// HTTP Headers
#define GET "GET /"
#define POST_ERICGPON "POST /GponForm/LoginForm"
#define WEBFORM_USER_PASS "XWebPageName=index&username=admin&password=admin"
#define AUTH_BASIC "Authorization: Basic "

// Credentials
const char *const users[] = {"admin", "root", "Admin"};
const char *const passwords[] = {"admin", "password", "1234",
                                 "root",  "Admin",    "12345"};