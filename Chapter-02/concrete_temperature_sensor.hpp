#ifndef CHAPTER_02_CONCRETE_TEMPERATURE_SENSOR_HPP
#define CHAPTER_02_CONCRETE_TEMPERATURE_SENSOR_HPP

#include "temperature_sensors.hpp"

#include <string>

namespace ct {

class ConcreteTemperatureSensor : public TempSensor {
    std::string m_id;

    // This would probably have some extra metadata for
    // where the temperature data would be read from.
    // For instance, on Unix based systems, this could
    // be a device file

public:

    ConcreteTemperatureSensor(std::string id) noexcept
        : m_id{std::move(id)} {}

    ~ConcreteTemperatureSensor() override;

    [[nodiscard]] std::string_view id() const noexcept override;

    [[nodiscard]] float temperature_kelvin() const noexcept override;
};


}

#endif //CHAPTER_02_CONCRETE_TEMPERATURE_SENSOR_HPP