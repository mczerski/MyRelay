#include "BL0942RequestableValue.h"

namespace mys_toolkit {

BL0942RequestableValue::BL0942RequestableValue(HardwareSerial &serial, uint8_t sensorId, Duration interval)
  : RequestableValue<float, float, float>(
      sensorId,
      {V_WATT, V_CURRENT, V_VOLTAGE},
      S_POWER,
      interval,
      {0.05, 0.05, 0.05}
    ),
    bl0942_(serial)
{
}

void BL0942RequestableValue::update_()
{
  bl0942_.update();
}

BL0942RequestableValue::Values BL0942RequestableValue::readValuesCb_()
{
  auto p_rms = std::abs(bl0942_.getPRms());
  auto i_rms = bl0942_.getIRms();
  auto v_rms = bl0942_.getVRms();
  p_rms = p_rms >= 0.2 ? p_rms : 0;
  i_rms = i_rms >= 0.01 ? i_rms : 0;
  v_rms = v_rms >= 0.1 ? v_rms : 0;
  return std::make_tuple(p_rms, i_rms, v_rms);
}

Duration BL0942RequestableValue::startMeasurementCb_()
{
  bl0942_.startMeasurement();
  return Duration(50);
}

void BL0942RequestableValue::begin2_()
{
  bl0942_.begin();
}

} //mys_toolkit
