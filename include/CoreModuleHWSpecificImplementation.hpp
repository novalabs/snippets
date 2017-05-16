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
    core::hw::IWDG_::woof();
}

void
core::mw::CoreModule::keepAlive()
{
    core::hw::IWDG_::reload();
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
    if(_configurationStorage.isValid()) {
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
    if(_configurationStorage.isValid()) {
        return _configurationStorage.getModuleConfiguration()->canID;
    }
#endif

    return core::hw::UID_::CPU_UID(0) ^ core::hw::UID_::CPU_UID(2);
#endif
}
