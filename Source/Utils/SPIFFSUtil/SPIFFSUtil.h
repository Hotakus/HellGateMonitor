#ifndef HELLGATEMONITOR_SPIFFSUTIL_H
#define HELLGATEMONITOR_SPIFFSUTIL_H

#include <Arduino.h>
#include <SPIFFS.h>

#define IS_HGM 1
#if IS_HGM == 1
#include "../../HgmApp/HotakusMemUtil.h"
#define SPIFFS_ALLOC hotakusAlloc
#define SPIFFS_FREE hotakusFree
#else
#define SPIFFS_ALLOC malloc
#define SPIFFS_FREE free
#endif

#ifndef ARDUINOJSON_VERSION_MAJOR
#define ARDUINOJSON_VERSION_MAJOR 0
#endif

#if ARDUINOJSON_VERSION_MAJOR != 0
#if IS_HGM == 1
#include "../../HgmApp/HgmJsonUtil.h"
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
#endif
#include <ArduinoJson.h>
#endif


namespace spiffsutil {
    class Sfu
    {
    private:
        
    public:

        Sfu() = default;
        ~Sfu() = default;

        static bool begin() {
            return SPIFFS.begin();
        }
        static void end() {
            SPIFFS.end();
        }

        static bool exists(const String& path) {
            return SPIFFS.exists(path);
        }

        static bool existsNoZero(const String& path) {
            if (SPIFFS.exists(path)) {
                File file = SPIFFS.open(path);
                if (file.size()) {
                    file.close();
                    return true;
                }
                file.close();
            }
            return false;
        }

        static size_t fileSize(const String& path) {
            if (!exists(path)) return false;
            File file = SPIFFS.open(path);
            size_t s = file.size();
            file.close();
            return s;
        }

    private:
        static bool _write(const String& path, uint8_t* wBuf, size_t size) {
            if (!exists(path)) return false;
            File file = SPIFFS.open(path, FILE_WRITE);
            if (file.write(wBuf, size) != size) {
                file.close();
                return false;
            }
            file.close();
            return true;
        }

    public:
        static bool write(const String& path, const String& wBuf) {
            return _write(path, (uint8_t*)wBuf.c_str(), wBuf.length());
        }

        static bool write(const String& path, uint8_t* wBuf, size_t size) {
            return _write(path, wBuf, size);
        }

        static size_t read(const String& path, uint8_t* rBuf, size_t size = 0) {
            if (!exists(path)) return false;
            File file = SPIFFS.open(path);
            size_t s = file.readBytes((char*)rBuf, size ? size : file.size());
            file.close();
            return s;
        }

#if ARDUINOJSON_VERSION_MAJOR != 0
        template <class T>
        static bool readJson(const String& path, T& doc) {
            if (!exists(path)) return false;
            DeserializationError err;
            File file = SPIFFS.open(path);
            if (file.size() > 1024) {
                uint8_t* buf = (uint8_t*)SPIFFS_ALLOC(sizeof(uint8_t) * (file.size() + 1024));
                file.readBytes((char*)buf, file.size());
                err = deserializeJson(doc, buf);
                SPIFFS_FREE(buf);
            } else {
                String str = file.readString();
                Serial.println(str);
                err = deserializeJson(doc, str);
            }
            file.close();

            if (err != DeserializationError::Code::Ok)
                return false;
            return true;
        }
#endif

    };
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_SPIFFSUTIL_H
