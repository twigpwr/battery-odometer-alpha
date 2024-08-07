/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_LPUART0RXSRC_0b0 0x00u  /*!<@brief LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_0b00 0x00u /*!<@brief LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLPUART(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTC19 (number 48), J1[3]/U3[4]/D2/CS/PWR_LATCH/PWR_LATCH/PROP_ACT_SW
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_BTN_FGPIO FGPIOC              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_BTN_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define BOARD_BTN_GPIO_PIN_MASK (1U << 19U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_BTN_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_BTN_PIN 19U                   /*!<@brief PORT pin number */
#define BOARD_BTN_PIN_MASK (1U << 19U)      /*!<@brief PORT pin mask */
                                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitButtonsPins(void);

/*! @name PORTB0 (number 16), J2[10]/U11[4]/D15/I2C_SCL_FXOS8700CQ/M1_LED/M1_LED/M1_LED
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_VDD_5V_EN_FGPIO FGPIOB             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_VDD_5V_EN_GPIO GPIOB               /*!<@brief GPIO peripheral base pointer */
#define BOARD_VDD_5V_EN_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_VDD_5V_EN_PORT PORTB               /*!<@brief PORT peripheral base pointer */
#define BOARD_VDD_5V_EN_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_VDD_5V_EN_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

/*! @name PORTC1 (number 37), LED_R/SPI1_CLK
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI1_CLK_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI1_CLK_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_SPI1_CLK_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                /* @} */

/*! @name PORTC2 (number 38), SW3/SPI1_MOSI
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI1_MOSI_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI1_MOSI_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_SPI1_MOSI_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                 /* @} */

/*! @name PORTC3 (number 39), SPI1_MISO
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI1_MISO_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI1_MISO_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_SPI1_MISO_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                                 /* @} */

/*! @name PORTC4 (number 40), SPI1_CS
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI1_CS_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI1_CS_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_SPI1_CS_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                               /* @} */

/*! @name PORTC16 (number 45), SPI0_CLK
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI0_CLK_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI0_CLK_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_SPI0_CLK_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                 /* @} */

/*! @name PORTC17 (number 46), SPI0_MOSI
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI0_MOSI_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI0_MOSI_PIN 17U                   /*!<@brief PORT pin number */
#define BOARD_SPI0_MOSI_PIN_MASK (1U << 17U)      /*!<@brief PORT pin mask */
                                                  /* @} */

/*! @name PORTC18 (number 47), SPI0_MISO
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI0_MISO_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI0_MISO_PIN 18U                   /*!<@brief PORT pin number */
#define BOARD_SPI0_MISO_PIN_MASK (1U << 18U)      /*!<@brief PORT pin mask */
                                                  /* @} */

/*! @name PORTA0 (number 1), SPI0_CS
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_SPI0_CS_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_SPI0_CS_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_SPI0_CS_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSPIPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCANPins(void);

/*! @name PORTA19 (number 7), J2[3]/U11[11]/D10/INT1_COMBO/PWR_WAKE_READ/PWR_WAKE_READ/MODE_SW
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_BATT_T2_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_BATT_T2_PIN 19U                   /*!<@brief PORT pin number */
#define BOARD_BATT_T2_PIN_MASK (1U << 19U)      /*!<@brief PORT pin mask */
                                                /* @} */

/*! @name PORTB2 (number 18), LED_B/J4[3]/Q3[1]/A2/LEDRGB_BLUE/ETS_PWR_MEAS_MCU/ADC2/ETS_PWR_MEAS_MCU/ADC2/ETS_PWR_MEAS_MCU/ADC2
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_BATT_V_PORT PORTB               /*!<@brief PORT peripheral base pointer */
#define BOARD_BATT_V_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_BATT_V_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                              /* @} */

/*! @name PORTB3 (number 19), LED/J4[4]/Q4[1]/A3/LED3/MTR_TMP0_MCU/ADC3/MTR_TMP0_MCU/ADC3/MTR_TMP0_MCU/ADC3
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_BATT_T1_PORT PORTB               /*!<@brief PORT peripheral base pointer */
#define BOARD_BATT_T1_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_BATT_T1_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                               /* @} */

/*! @name PORTB1 (number 17), J2[9]/U11[6]/D14/I2C_SDA_FXOS8700CQ/VDD_5V_MCU/VDD_5V_MCU/ETSB_MCU/ADC1
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_BATT_I_PORT PORTB               /*!<@brief PORT peripheral base pointer */
#define BOARD_BATT_I_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_BATT_I_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                              /* @} */

/*! @name PORTB18 (number 23), SW2/J4[2]/A1/SW2/VREG_12V_IMON_MCU/VREG_12V_IMON_MCU/TKS0_MCU/ADC4
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_VSENSE_PORT PORTB                /*!<@brief PORT peripheral base pointer */
#define BOARD_VSENSE_PIN 18U                   /*!<@brief PORT pin number */
#define BOARD_VSENSE_PIN_MASK (1U << 18U)      /*!<@brief PORT pin mask */
                                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitADCPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
