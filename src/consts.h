#include <stdio.h>
#include <string.h>

// HTTP Headers
const char *const headers[] = {
    "GET /", "POST /GponForm/LoginForm",
    "XWebPageName=index&username=admin&password=admin"
    "Authorization: Basic "};

// Recognize by
const char *const recognizeList[] = {"GPON Home Gateway", "url=/login.html",
                                     "TPLINK"};

// Vendor List
const char *const vendorList[] = {"UNKNOWN", "Ericsson GPON OLD",
                                  "TP-LINK OLD"
                                  "TOMATO UNIFIED OLD"};

// Credentials
const char *const users[] = {"admin", "root", "Admin"};

const char *const passwords[] = {"admin", "password", "1234",
                                 "root",  "Admin",    "12345"};