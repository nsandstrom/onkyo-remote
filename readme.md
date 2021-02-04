## Led pin.

GPIO4 = Pin marked D2 on board

## Commands

### Upload

pio run -t upload

### Serial monitor

pio device monitor -b 115200

### Upload and monitor

pio run -t upload && pio device monitor -b 115200
