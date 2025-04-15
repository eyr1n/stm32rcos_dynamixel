# stm32rcos_dynamixel

## 使い方

### CMakeLists.txt

```cmake
# ~略~

# ファイル末尾に以下を追記

include(FetchContent)
FetchContent_Declare(stm32rcos
  GIT_REPOSITORY https://github.com/eyr1n/stm32rcos.git
)
FetchContent_Declare(stm32rcos_dynamixel
  GIT_REPOSITORY https://github.com/eyr1n/stm32rcos_dynamixel.git
)
FetchContent_MakeAvailable(stm32rcos stm32rcos_dynamixel)

target_link_libraries(${PROJECT_NAME}
    stm32rcos
    stm32rcos::f446xx  # MCUの型番に応じて変更する
    stm32rcos_dynamixel
)
```

### C++

```cpp
#include <dynamixel_sdk.h>

#include <stm32rcos/peripheral.hpp>
#include <stm32rcos_dynamixel/port_handler.hpp>

// ~略~

// Dynamixelを制御するルーチンにてPortHandlerを初期化

stm32rcos::peripheral::UART_IT uart1(&huart1);
stm32rcos_dynamixel::PortHandler stm32rcos_dynamixel_port_handler(uart1);
dynamixel::PortHandler *portHandler = &stm32rcos_dynamixel_port_handler;

// 以降、portHandlerを公式サンプルどおりに操作できる
```