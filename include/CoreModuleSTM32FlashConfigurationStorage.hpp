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
    beginWrite() {
        return _storage.beginWrite();
    }

    bool
    write(std::size_t address, uint16_t data) {
        return _storage.writeUserData16(address, data);
    }

    bool
    write(std::size_t address, uint32_t data) {
        return _storage.writeUserData32(address, data);
    }

    bool
    endWrite() {
        return _storage.endWrite();
    }

private:
    core::stm32_flash::ConfigurationStorage& _storage;
};

static STM32FlashConfigurationStorage _coreConfigurationStorage(_configurationStorage);

core::mw::CoreConfigurationStorage& Module::configurationStorage = _coreConfigurationStorage;
#endif // ifdef CORE_USE_CONFIGURATION_STORAGE
