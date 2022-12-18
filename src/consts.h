#include <stdio.h>
#include <string.h>

// Vendor list
#define UNKNOWN 0
#define ERICSSON_GPON_OLD 1
#define TPLINK_OLD 2
#define TOMATO_UNIFIED_OLD 3
#define ZYXEL_OLD 4
#define DLINK_OLD 5
#define HIKVISION_CAM_OLD 5

// HTTP Headers
const char *const headers[] = {
    "GET /", "POST /GponForm/LoginForm",
    "XWebPageName=index&username=admin&password=admin"
    "Authorization: Basic "};

// Recognize by
const char *const recognizeList[] = {"GPON Home Gateway", "url=/login.html",
                                     "TPLINK"};

// Credentials
const char *const users[] = {"admin", "root", "Admin"};
const char *const passwords[] = {"admin", "password", "1234",
                                 "root",  "Admin",    "12345"};