deps_config := \
	/Users/gianpy86/esp/esp-idf/components/bt/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/esp32/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/ethernet/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/freertos/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/log/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/lwip/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/mbedtls/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/spi_flash/Kconfig \
	/Users/gianpy86/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/Users/gianpy86/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/Users/gianpy86/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/Users/gianpy86/esp/WiFiTest/main/Kconfig.projbuild \
	/Users/gianpy86/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
