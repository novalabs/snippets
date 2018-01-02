/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

// ----------------------------------------------------------------------------
// CoreModule HW specific implementation
// ----------------------------------------------------------------------------

#ifdef STM32F4XX
#define UID_BASE (0x1FFF7A10u)
#else
#define UID_BASE (0x1FFFF7ACu)
#endif


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
    RTC->BKP0R = 0xBAADF00D; // TODO: wrap it somewhere.
}

void
core::mw::CoreModule::enableBootloader()
{
    RTC->BKP0R = 0xB0BAFE77; // TODO: wrap it somewhere.
}

#include <core/stm32_crc/CRC.hpp>

const core::mw::CoreModule::UID&
core::mw::CoreModule::uid()
{
    static core::mw::CoreModule::UID _uid;
    static bool initialized = false;

    if (!initialized) {
        core::stm32_crc::CRC::init();
        core::stm32_crc::CRC::setPolynomialSize(core::stm32_crc::CRC::PolynomialSize::POLY_32);
        core::stm32_crc::CRC::reset();
        _uid = core::stm32_crc::CRC::CRCBlock(reinterpret_cast<uint32_t*>(UID_BASE), 12 / sizeof(uint32_t));
        initialized = true;
    }

    return _uid;
}

const char*
core::mw::CoreModule::name()
{
#ifdef OVERRIDE_MODULE_NAME
#warning "Overriding module Name"
    return OVERRIDE_MODULE_NAME;
#else
#if CORE_USE_CONFIGURATION_STORAGE
    if (_configurationStorage.isValid()) {
        return _configurationStorage.getModuleConfiguration()->name;
    }
#endif

    return ModuleConfiguration::MODULE_NAME;
#endif
}

uint8_t
core::mw::CoreModule::canID()
{
#ifdef OVERRIDE_MODULE_ID
#warning "Overriding module ID"
    return OVERRIDE_MODULE_ID & 0xFF;
#else
#if CORE_USE_CONFIGURATION_STORAGE
    if (_configurationStorage.isValid()) {
        return _configurationStorage.getModuleConfiguration()->canID;
    }
#endif

    return uid();
#endif
} // core::mw::CoreModule::canID
