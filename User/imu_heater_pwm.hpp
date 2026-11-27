#pragma once

#include <algorithm>
#include <cmath>

#include "adc.hpp"
#include "pwm.hpp"

/**
 * @brief 供电电压自适应且限功率的 IMU 加热 PWM 封装。
 *        Supply-voltage-adaptive and power-capped PWM wrapper for the IMU heater.
 */
class ImuHeaterPWM : public LibXR::PWM
{
 public:
  /**
   * @brief 构造 ImuHeaterPWM 实例，默认参数对应 MC02 板载加热电路。
   *        Construct an ImuHeaterPWM wrapper with defaults for the MC02 heater.
   *
   * @param pwm 底层 PWM 外设。
   *            Underlying PWM output.
   * @param vbat_adc 采样 VCC_IN 分压后的 ADC 通道。
   *                 ADC channel sensing the divided VCC_IN rail.
   * @param resistance_ohm 加热电阻等效阻值（欧姆）。
   *                       Equivalent heater resistance in ohms.
   * @param max_power_w 允许的最大连续加热功率（瓦特）。
   *                    Maximum allowed continuous heating power in watts.
   * @param divider_ratio VCC_IN 到 ADC 的分压比（V_in / V_adc）。
   *                      Resistor divider ratio (V_in / V_adc).
   * @param min_valid_v 判定供电有效的最低电压阈值（伏特）。
   *                    Minimum valid supply voltage threshold in volts.
   * @param max_valid_v 判定供电有效的最高电压阈值（伏特）。
   *                    Maximum valid supply voltage threshold in volts.
   */
  ImuHeaterPWM(LibXR::PWM& pwm, LibXR::ADC& vbat_adc,
               float resistance_ohm = 47.0f, float max_power_w = 0.5f,
               float divider_ratio = 11.0f, float min_valid_v = 3.5f,
               float max_valid_v = 30.0f)
      : pwm_(pwm),
        vbat_adc_(vbat_adc),
        resistance_ohm_(resistance_ohm),
        max_power_w_(max_power_w),
        divider_ratio_(divider_ratio),
        min_valid_v_(min_valid_v),
        max_valid_v_(max_valid_v)
  {
  }

  LibXR::ErrorCode SetDutyCycle(float value) override
  {
    const float v_in = vbat_adc_.Read() * divider_ratio_;
    last_voltage_ = v_in;

    if (!std::isfinite(value) || value <= 0.0f || !std::isfinite(v_in) ||
        v_in < min_valid_v_ || v_in > max_valid_v_)
    {
      last_duty_ = 0.0f;
      return pwm_.SetDutyCycle(0.0f);
    }

    const float norm_u = std::clamp(value, 0.0f, 1.0f);
    const float max_duty =
        std::clamp((max_power_w_ * resistance_ohm_) / (v_in * v_in), 0.0f, 1.0f);
    last_duty_ = norm_u * max_duty;
    return pwm_.SetDutyCycle(last_duty_);
  }

  LibXR::ErrorCode SetConfig(Configuration config) override
  {
    return pwm_.SetConfig(config);
  }

  LibXR::ErrorCode Enable() override
  {
    pwm_.SetDutyCycle(0.0f);
    return pwm_.Enable();
  }

  LibXR::ErrorCode Disable() override
  {
    pwm_.SetDutyCycle(0.0f);
    return pwm_.Disable();
  }

  float GetLastVoltage() const { return last_voltage_; }
  float GetLastDuty() const { return last_duty_; }

 private:
  LibXR::PWM& pwm_;
  LibXR::ADC& vbat_adc_;
  float resistance_ohm_;
  float max_power_w_;
  float divider_ratio_;
  float min_valid_v_;
  float max_valid_v_;
  float last_voltage_ = 0.0f;
  float last_duty_ = 0.0f;
};
