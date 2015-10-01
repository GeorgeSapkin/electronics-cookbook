#include <stdint.h>

struct EncState {
  uint8_t       pin;
  long          count;
  unsigned long time;
  uint8_t       sig;
};
