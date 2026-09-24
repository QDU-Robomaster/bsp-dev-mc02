#pragma once
// xrobot-stamp: config=xrobot.yaml sha256=daaf7e46ebf62348999688571efd6179e48d22520ac320d5026ce363a264b4f5
// xrobot-stamp: lock=../xrobot.lock sha256=bc6224bfec2306003ed064ba01fb706f2602abffcf27ef4054d39e0154d297e8
// xrobot-stamp: tool=xrobot 0.3.1

#include <memory>
#include <type_traits>
#include <utility>
#include "libxr.hpp"
#include "thread.hpp"
#include "BuzzerAlarm.hpp"

namespace xrobot_generated {
template <typename...> struct TypeList {};
template <typename Source, typename... Views>
struct RegistrationMatches
    : std::bool_constant<(!std::is_reference<Views>::value && ...) &&
                         (std::is_convertible<Source*, Views*>::value && ...)> {};

}  // namespace xrobot_generated

// Force only this entry inline in optimized Clang builds.
#if defined(__clang__) && defined(__OPTIMIZE__) && !defined(LIBXR_DEBUG_BUILD) && \
    ((defined(XROBOT_OPTIMIZED_BUILD) && XROBOT_OPTIMIZED_BUILD) || \
     (!defined(XROBOT_OPTIMIZED_BUILD) && defined(NDEBUG)))
#define XR_XROBOT_MAIN_INLINE [[gnu::always_inline]] inline
#else
#define XR_XROBOT_MAIN_INLINE inline
#endif

[[noreturn]] XR_XROBOT_MAIN_INLINE void XRobotMain(
    LibXR::PWM& pwm_tim12_ch2) {
  // modules[0]: buzzer
  static BuzzerAlarm buzzer(
      static_cast<LibXR::PWM&>(pwm_tim12_ch2)
      , 1500
      , 300
      , 300
  );
  static_assert(std::is_void_v<decltype(buzzer.OnMonitor())>, "buzzer.OnMonitor() must return void");
  for (;;) {
    buzzer.OnMonitor();
    LibXR::Thread::Sleep(1000);
  }
}

#undef XR_XROBOT_MAIN_INLINE

/* User Code Begin XRobotMain */
/* User Code End XRobotMain */
// clang-format off
// NOLINTBEGIN
#define XR_REGISTER_DETAIL_power_manager(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PowerManager>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(power_manager)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_PA15(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(PA15)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_LCD_BLK(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(LCD_BLK)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_LCD_RES(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(LCD_RES)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_ACC_CS(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(ACC_CS)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_POWER_24V_2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(POWER_24V_2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_PC14(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(PC14)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_POWER_5V(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(POWER_5V)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_GYRO_CS(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(GYRO_CS)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_ACC_INT(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(ACC_INT)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_W25Q64_CS(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(W25Q64_CS)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_GYRO_INT(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(GYRO_INT)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_LCD_CS(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(LCD_CS)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim1_ch1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim1_ch1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim1_ch3(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim1_ch3)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim12_ch2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim12_ch2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim2_ch1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim2_ch1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim2_ch3(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim2_ch3)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim3_ch4(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim3_ch4)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_adc1_adc_channel_4(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::ADC>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(adc1_adc_channel_4)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_adc1_adc_channel_19(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::ADC>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(adc1_adc_channel_19)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_dac1_out2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::DAC>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(dac1_out2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_spi2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::SPI>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(spi2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_spi6(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::SPI>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(spi6)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_uart5(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(uart5)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_uart7(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(uart7)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usart1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usart1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usart10(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usart10)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usart2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usart2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usart3(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usart3)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_fdcan1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::FDCAN>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(fdcan1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_fdcan2(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::FDCAN>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(fdcan2)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_fdcan3(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::FDCAN>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(fdcan3)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usb_otg_hs_cdc(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usb_otg_hs_cdc)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_ramfs(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::RamFS>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(ramfs)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_terminal(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::Terminal<32, 32, 5, 5>>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(terminal)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_database(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::Database>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(database)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER(name, ...) XR_REGISTER_DETAIL_##name(__VA_ARGS__)

#define XROBOT_MAIN() ::XRobotMain(pwm_tim12_ch2)

// NOLINTEND
// clang-format on
