#include <json.h>
#include <eprom.h>
#include <access_point.h>
#include <http.h>

enum Mode {
    ACCESS_POINT,
    HTTP_CLIENT,
};

class EspMode
{
public:
    static Mode espMode;
};

void setupWifiMode();