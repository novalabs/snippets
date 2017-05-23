/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

// ----------------------------------------------------------------------------
// CoreModule HW specific implementation
// ----------------------------------------------------------------------------

void
core::mw::CoreModule::Led::toggle()
{
    _led.toggle();
}

void
core::mw::CoreModule::Led::write(
    unsigned on
)
{
    _led.write(on);
}

void
core::mw::CoreModule::reset()
{
#ifdef CORE_USE_BOOTLOADER
    core::hw::IWDG_::woof();
#endif
}

void
core::mw::CoreModule::keepAlive()
{
#ifdef CORE_USE_BOOTLOADER
    core::hw::IWDG_::reload();
#endif
}

void
core::mw::CoreModule::disableBootloader()
{
    RTC->BKP0R = 0x55AA55AA; // TODO: wrap it somewhere.
}

void
core::mw::CoreModule::enableBootloader()
{
    RTC->BKP0R = 0xB0BAFE77; // TODO: wrap it somewhere.
}

const core::mw::CoreModule::UID&
core::mw::CoreModule::uid()
{
    static uint32_t tmp = 0xB0BAFE77;

    return tmp;
}

const char*
core::mw::CoreModule::name()
{
#if CORE_USE_CONFIGURATION_STORAGE
    if (_configurationStorage.isValid()) {
        return _configurationStorage.getModuleConfiguration()->name;
    }
#endif

    return ModuleConfiguration::MODULE_NAME;
}

uint8_t
core::mw::CoreModule::canID()
{
#ifdef MODULE_ID
    return MODULE_ID & 0xFF;

#else
#if CORE_USE_CONFIGURATION_STORAGE
    if (_configurationStorage.isValid()) {
        return _configurationStorage.getModuleConfiguration()->canID;
    }
#endif

    return UID();
#endif
}
