#include "app_main.h"

#include "cdc_uart.hpp"
#include "libxr.hpp"
#include "main.h"
#include "stm32_adc.hpp"
#include "stm32_can.hpp"
#include "stm32_canfd.hpp"
#include "stm32_dac.hpp"
#include "stm32_flash.hpp"
#include "stm32_gpio.hpp"
#include "stm32_i2c.hpp"
#include "stm32_power.hpp"
#include "stm32_pwm.hpp"
#include "stm32_spi.hpp"
#include "stm32_timebase.hpp"
#include "stm32_uart.hpp"
#include "stm32_usb_dev.hpp"
#include "stm32_watchdog.hpp"
#include "flash_map.hpp"
#include "xrobot_main.hpp"

using namespace LibXR;

/* User Code Begin 1 */
/* User Code End 1 */
// NOLINTBEGIN
// clang-format off
/* External HAL Declarations */
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;
extern PCD_HandleTypeDef hpcd_USB_OTG_HS;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi6;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart10;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;

/* DMA Resources */
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint16_t data[128];
} adc1_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& adc1_buf = adc1_buf_storage.data;
#else
alignas(4) static uint16_t adc1_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[32];
} spi2_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& spi2_tx_buf = spi2_tx_buf_storage.data;
#else
alignas(4) static uint8_t spi2_tx_buf[32] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[32];
} spi2_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& spi2_rx_buf = spi2_rx_buf_storage.data;
#else
alignas(4) static uint8_t spi2_rx_buf[32] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[32];
} spi6_tx_buf_storage __attribute__((section(".ram_d3")));
static constexpr auto& spi6_tx_buf = spi6_tx_buf_storage.data;
#else
alignas(4) static uint8_t spi6_tx_buf[32] __attribute__((section(".ram_d3")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} uart5_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& uart5_rx_buf = uart5_rx_buf_storage.data;
#else
alignas(4) static uint8_t uart5_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} uart7_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& uart7_tx_buf = uart7_tx_buf_storage.data;
#else
alignas(4) static uint8_t uart7_tx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} uart7_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& uart7_rx_buf = uart7_rx_buf_storage.data;
#else
alignas(4) static uint8_t uart7_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart1_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart1_tx_buf = usart1_tx_buf_storage.data;
#else
alignas(4) static uint8_t usart1_tx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart1_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart1_rx_buf = usart1_rx_buf_storage.data;
#else
alignas(4) static uint8_t usart1_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart10_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart10_tx_buf = usart10_tx_buf_storage.data;
#else
alignas(4) static uint8_t usart10_tx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart10_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart10_rx_buf = usart10_rx_buf_storage.data;
#else
alignas(4) static uint8_t usart10_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart2_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart2_tx_buf = usart2_tx_buf_storage.data;
#else
alignas(4) static uint8_t usart2_tx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart2_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart2_rx_buf = usart2_rx_buf_storage.data;
#else
alignas(4) static uint8_t usart2_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart3_tx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart3_tx_buf = usart3_tx_buf_storage.data;
#else
alignas(4) static uint8_t usart3_tx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart3_rx_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usart3_rx_buf = usart3_rx_buf_storage.data;
#else
alignas(4) static uint8_t usart3_rx_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[8];
} usb_otg_hs_ep0_in_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usb_otg_hs_ep0_in_buf = usb_otg_hs_ep0_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_otg_hs_ep0_in_buf[8] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[8];
} usb_otg_hs_ep0_out_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usb_otg_hs_ep0_out_buf = usb_otg_hs_ep0_out_buf_storage.data;
#else
alignas(4) static uint8_t usb_otg_hs_ep0_out_buf[8] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usb_otg_hs_ep1_in_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usb_otg_hs_ep1_in_buf = usb_otg_hs_ep1_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_otg_hs_ep1_in_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usb_otg_hs_ep1_out_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usb_otg_hs_ep1_out_buf = usb_otg_hs_ep1_out_buf_storage.data;
#else
alignas(4) static uint8_t usb_otg_hs_ep1_out_buf[128] __attribute__((section(".axi_ram")));
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(__SCB_DCACHE_LINE_SIZE)
{
  uint8_t data[16];
} usb_otg_hs_ep2_in_buf_storage __attribute__((section(".axi_ram")));
static constexpr auto& usb_otg_hs_ep2_in_buf = usb_otg_hs_ep2_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_otg_hs_ep2_in_buf[16] __attribute__((section(".axi_ram")));
#endif

extern "C" void app_main(void) {
  // clang-format on
  // NOLINTEND
  /* User Code Begin 2 */
  /* User Code End 2 */
  // clang-format off
  // NOLINTBEGIN
  static STM32TimerTimebase timebase(&htim4);
  PlatformInit(2, 1024);
  static STM32PowerManager power_manager;

  /* GPIO Configuration */
  static STM32GPIO PA15(GPIOA, GPIO_PIN_15);
  static STM32GPIO LCD_BLK(LCD_BLK_GPIO_Port, LCD_BLK_Pin);
  static STM32GPIO LCD_RES(LCD_RES_GPIO_Port, LCD_RES_Pin);
  static STM32GPIO ACC_CS(ACC_CS_GPIO_Port, ACC_CS_Pin);
  static STM32GPIO POWER_24V_2(POWER_24V_2_GPIO_Port, POWER_24V_2_Pin);
  static STM32GPIO PC14(GPIOC, GPIO_PIN_14);
  static STM32GPIO POWER_5V(POWER_5V_GPIO_Port, POWER_5V_Pin);
  static STM32GPIO GYRO_CS(GYRO_CS_GPIO_Port, GYRO_CS_Pin);
  static STM32GPIO ACC_INT(ACC_INT_GPIO_Port, ACC_INT_Pin, EXTI15_10_IRQn);
  static STM32GPIO W25Q64_CS(W25Q64_CS_GPIO_Port, W25Q64_CS_Pin);
  static STM32GPIO GYRO_INT(GYRO_INT_GPIO_Port, GYRO_INT_Pin, EXTI15_10_IRQn);
  static STM32GPIO LCD_CS(LCD_CS_GPIO_Port, LCD_CS_Pin);

  static STM32ADC adc1(&hadc1, adc1_buf, {ADC_CHANNEL_4, ADC_CHANNEL_19}, 3.3);
  static auto& adc1_adc_channel_4 = adc1.GetChannel(0);
  UNUSED(adc1_adc_channel_4);
  static auto& adc1_adc_channel_19 = adc1.GetChannel(1);
  UNUSED(adc1_adc_channel_19);

  static STM32PWM pwm_tim1_ch1(&htim1, TIM_CHANNEL_1, false);
  static STM32PWM pwm_tim1_ch3(&htim1, TIM_CHANNEL_3, false);

  static STM32PWM pwm_tim12_ch2(&htim12, TIM_CHANNEL_2, false);

  static STM32PWM pwm_tim2_ch1(&htim2, TIM_CHANNEL_1, false);
  static STM32PWM pwm_tim2_ch3(&htim2, TIM_CHANNEL_3, false);

  static STM32PWM pwm_tim3_ch4(&htim3, TIM_CHANNEL_4, false);

  static STM32DAC dac1_out2(&hdac1, DAC_CHANNEL_2, 0.0, 3.3);

  static STM32SPI spi2(&hspi2, spi2_rx_buf, spi2_tx_buf, 3);

  static STM32SPI spi6(&hspi6, {nullptr, 0}, spi6_tx_buf, 3);

  static STM32UART uart5(&huart5,
              uart5_rx_buf, {nullptr, 0}, 5);

  static STM32UART uart7(&huart7,
              uart7_rx_buf, uart7_tx_buf, 5);

  static STM32UART usart1(&huart1,
              usart1_rx_buf, usart1_tx_buf, 5);

  static STM32UART usart10(&huart10,
              usart10_rx_buf, usart10_tx_buf, 5);

  static STM32UART usart2(&huart2,
              usart2_rx_buf, usart2_tx_buf, 5);

  static STM32UART usart3(&huart3,
              usart3_rx_buf, usart3_tx_buf, 5);

  static STM32CANFD fdcan1(&hfdcan1, 5);

  static STM32CANFD fdcan2(&hfdcan2, 5);

  static STM32CANFD fdcan3(&hfdcan3, 5);

  static constexpr auto USB_OTG_HS_LANG_PACK = LibXR::USB::DescriptorStrings::MakeLanguagePack(LibXR::USB::DescriptorStrings::Language::EN_US, "QDU-Future", "MainCtrl", "QDU-Future-MainCtrl-89ABCDEF0123456701234567");
  static LibXR::USB::CDCUart usb_otg_hs_cdc(LibXR::USB::Endpoint::EPNumber::EP1, LibXR::USB::Endpoint::EPNumber::EP1, LibXR::USB::Endpoint::EPNumber::EP2, 128, 128, 3);

  static STM32USBDeviceOtgHS usb_hs(
      &hpcd_USB_OTG_HS,
      256,
      {usb_otg_hs_ep0_out_buf, usb_otg_hs_ep1_out_buf},
      {{usb_otg_hs_ep0_in_buf, 8}, {usb_otg_hs_ep1_in_buf, 128}, {usb_otg_hs_ep2_in_buf, 16}},
      USB::DeviceDescriptor::PacketSize0::SIZE_8,
      0x16D0, 0x1492, 0xF407,
      {&USB_OTG_HS_LANG_PACK},
      {{&usb_otg_hs_cdc}},
      {reinterpret_cast<void *>(UID_BASE), 12}
  );
  usb_hs.Init(false);
  usb_hs.Start(false);

  /* Terminal Configuration */
  STDIO::read_ = usb_otg_hs_cdc.read_port_;
  STDIO::write_ = usb_otg_hs_cdc.write_port_;

  static RamFS ramfs("XRobot");
  static Terminal<32, 32, 5, 5> terminal(ramfs);
  static LibXR::Thread term_thread;
  term_thread.Create(&terminal, terminal.ThreadFun, "terminal", 2048,
                     static_cast<LibXR::Thread::Priority>(2));

  XR_REGISTER(power_manager, LibXR::PowerManager);
  XR_REGISTER(LCD_BLK, LibXR::GPIO);
  XR_REGISTER(LCD_RES, LibXR::GPIO);
  XR_REGISTER(ACC_CS, LibXR::GPIO);
  XR_REGISTER(POWER_24V_2, LibXR::GPIO);
  XR_REGISTER(POWER_5V, LibXR::GPIO);
  XR_REGISTER(ACC_INT, LibXR::GPIO);
  XR_REGISTER(W25Q64_CS, LibXR::GPIO);
  XR_REGISTER(GYRO_INT, LibXR::GPIO);
  XR_REGISTER(LCD_CS, LibXR::GPIO);
  XR_REGISTER(pwm_tim1_ch1, LibXR::PWM);
  XR_REGISTER(pwm_tim1_ch3, LibXR::PWM);
  XR_REGISTER(pwm_tim12_ch2, LibXR::PWM);
  XR_REGISTER(pwm_tim2_ch1, LibXR::PWM);
  XR_REGISTER(pwm_tim2_ch3, LibXR::PWM);
  XR_REGISTER(pwm_tim3_ch4, LibXR::PWM);
  XR_REGISTER(adc1_adc_channel_4, LibXR::ADC);
  XR_REGISTER(adc1_adc_channel_19, LibXR::ADC);
  XR_REGISTER(dac1_out2, LibXR::DAC);
  XR_REGISTER(spi2, LibXR::SPI);
  XR_REGISTER(spi6, LibXR::SPI);
  XR_REGISTER(uart5, LibXR::UART);
  XR_REGISTER(uart7, LibXR::UART);
  XR_REGISTER(usart1, LibXR::UART);
  XR_REGISTER(usart10, LibXR::UART);
  XR_REGISTER(usart2, LibXR::UART);
  XR_REGISTER(usart3, LibXR::UART);
  XR_REGISTER(fdcan1, LibXR::FDCAN);
  XR_REGISTER(fdcan2, LibXR::FDCAN);
  XR_REGISTER(fdcan3, LibXR::FDCAN);
  XR_REGISTER(usb_otg_hs_cdc, LibXR::UART);
  XR_REGISTER(ramfs, LibXR::RamFS);
  XR_REGISTER(terminal, LibXR::Terminal<32, 32, 5, 5>);
  XR_REGISTER(PA15, LibXR::GPIO);
  XR_REGISTER(PC14, LibXR::GPIO);
  XR_REGISTER(GYRO_CS, LibXR::GPIO);

  // clang-format on
  // NOLINTEND
  /* User Code Begin 3 */
  static STM32Flash flash(FLASH_SECTORS, FLASH_SECTOR_NUMBER);
  static LibXR::DatabaseRaw<32> database(flash);

  XR_REGISTER(database, LibXR::Database);
  XROBOT_MAIN();
  /* User Code End 3 */
}