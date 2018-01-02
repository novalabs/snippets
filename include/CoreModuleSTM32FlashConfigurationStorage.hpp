/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

// ----------------------------------------------------------------------------
// CoreModule STM32FlashConfigurationStorage
// ----------------------------------------------------------------------------

#if CORE_USE_CONFIGURATION_STORAGE
#include <core/stm32_flash/ConfigurationStorage.hpp>
#include <core/mw/CoreConfigurationManager.hpp>

static core::stm32_flash::FlashSegment         _configurationBank1(core::stm32_flash::CONFIGURATION1_FLASH_FROM, core::stm32_flash::CONFIGURATION1_FLASH_TO);
static core::stm32_flash::FlashSegment         _configurationBank2(core::stm32_flash::CONFIGURATION2_FLASH_FROM, core::stm32_flash::CONFIGURATION2_FLASH_TO);
static core::stm32_flash::Storage              _userStorage(_configurationBank1, _configurationBank2);
static core::stm32_flash::ConfigurationStorage _configurationStorage(_userStorage);

class STM32FlashConfigurationStorage:
    public core::mw::CoreConfigurationStorage
{
public:
    STM32FlashConfigurationStorage(
        core::stm32_flash::ConfigurationStorage& storage
    ) : _storage(storage) {}

    void*
    data()
    {
        return _storage.getUserConfiguration();
    }

    std::size_t
    size()
    {
        return _storage.userDataSize();
    }

    bool
    beginWrite()
    {
        return _storage.beginWrite();
    }

    bool
    write16(
        std::size_t address,
        uint16_t    data
    )
    {
        return _storage.writeUserData16(address, data);
    }

    bool
    write32(
        std::size_t address,
        uint32_t    data
    )
    {
        return _storage.writeUserData32(address, data);
    }

    bool
    endWrite()
    {
        return _storage.endWrite();
    }

private:
    core::stm32_flash::ConfigurationStorage& _storage;
};

static STM32FlashConfigurationStorage __coreConfigurationStorage(_configurationStorage);
core::mw::CoreConfigurationStorage&   core::mw::CoreModule::_coreConfigurationStorage = __coreConfigurationStorage;
#else // if CORE_USE_CONFIGURATION_STORAGE
#warning "Using /dev/null as storage for module configuration. Load/Save will have no effect."
static core::mw::CoreConfigurationStorage __coreConfigurationStorage;
core::mw::CoreConfigurationStorage&       core::mw::CoreModule::_coreConfigurationStorage = __coreConfigurationStorage;
#endif // ifdef CORE_USE_CONFIGURATION_STORAGE
