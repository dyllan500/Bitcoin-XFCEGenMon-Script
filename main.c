#include <stdlib.h>
#include <stdio.h>
#include "json-c/json.h"
#include "curl/curl.h"
#include <string.h>

int main() {


    CURL *curl;
    FILE *fp;
    char buffer[1024000];
    struct json_object *parsed_json;
    struct json_object *market;
    struct json_object *result;
    struct  json_object *rtwo;
    struct json_object *amount;
    int try;
    size_t n;
    size_t i;
    const char *m;
    char *color;
    color="#ffd700";
    fp = fopen("/home/dyllan/CLionProjects/bitcoin/cmake-build-debug/bit.json", "wb");
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "https://bittrex.com/api/v1.1/public/getmarketsummaries");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    try = curl_easy_perform(curl);
    fclose(fp);
    fp = fopen("/home/dyllan/CLionProjects/bitcoin/cmake-build-debug/bit.json", "r");
    fread(buffer, 1024000, 1, fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "result", &result);
    n = json_object_array_length(result);
    for(i=0;i<n;i++){
        rtwo = json_object_array_get_idx(result, i);
        json_object_get_object(rtwo);
        json_object_object_get_ex(rtwo, "MarketName", &market);
        m = json_object_get_string(market);
        if (strncmp(m, "USD-BTC", 7) == 0){
            json_object_object_get_ex(rtwo, "Last", &amount);
            printf("<txt><span color='%s'>$%.2lf</span></txt>",color,json_object_get_double(amount));
        }

    }
    fclose(fp);

    return 0;
}