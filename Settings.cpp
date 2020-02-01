#include "Settings.h"
#include <iostream>

Settings* Settings::s_instance = NULL;

Settings* Settings::createSettings()
{
    if (s_instance == NULL) {
        s_instance = new Settings();
    }

    return s_instance;
}
