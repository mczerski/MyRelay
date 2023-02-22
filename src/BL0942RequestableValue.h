#ifndef BL0942RequestableValue_h
#define BL0942RequestableValue_h


#include <MySensorsToolkit/Actuator/RequestableValue.h>
#include "BL0942.h"

namespace mys_toolkit {

class BL0942RequestableValue : public RequestableValue<float, float, float> {
public:
  BL0942RequestableValue(HardwareSerial &serial, uint8_t sensorId, Duration interval);

private:
  BL0942 bl0942_;
  void update_() override;
  Values readValuesCb_() override;
  Duration startMeasurementCb_() override;
  void begin2_() override;
};

} //mys_toolkit

#endif //BL0942RequestableValue_h
