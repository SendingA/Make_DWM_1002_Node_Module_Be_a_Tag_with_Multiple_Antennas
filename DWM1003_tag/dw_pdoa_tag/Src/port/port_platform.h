/*! ----------------------------------------------------------------------------
 * @file    port_platform.h
 * @brief   HW specific definitions and functions for portability
 *
 * @author  Decawave 
 *
 * @attention
 *
 * Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 */
 
#ifndef PORT_PLATFORM_H_
#define PORT_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "deca_types.h"
#include "deca_device_api.h"
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "boards.h"
#include "app_error.h"
#include "app_uart.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_rtc.h"

#include "error.h"

extern const nrf_drv_rtc_t rtc;

/*

Note: Antenna Delay Values
The sum of the values is the TX to RX antenna delay, this should be
experimentally determined by a calibration process. Here we use a hard coded
value (expected to be a little low so a positive error will be seen on the
resultant distance estimate. For a real production application, each
device should have its own antenna delay properly calibrated to get good
precision when performing range measurements.
*/

/**< max number of test bytes to be used for tx and rx. */
#define MAX_TEST_DATA_BYTES     (15U)

/* Default antenna delay values for 64 MHz PRF.*/
#define TX_ANT_DLY 16456
#define RX_ANT_DLY 16456

#define DATALEN1 200

#define SPI_0_CS_PIN   17 /**< SPI CS Pin for DW1000 Master Chip A */
#define UART_0_TX_PIN 5  /**< UART Tx Pin for nRF52832 */
#define UART_0_RX_PIN 11 /**< UART Rx Pin for nRF52832 */

#define MASK_40BIT            (0x00FFFFFFFFFFULL)  // DW1000 counter is 40 bits
#define MASK_TXDTS            (0x00FFFFFFFE00ULL)  //The TX timestamp will snap to 8 ns resolution - mask lower 9 bits.

// timeout for UART inactivity to switch it off
#define UART_OFF_TIMEOUT      30000

typedef enum {
    DW_MASTER = 0,
    DW_SLAVE
} dw_name_e;

typedef enum 
{
  DW_HAL_TAG_UNLOCKED  = NRF_SUCCESS,
  DW_HAL_TAG_LOCKED    = NRF_ERROR_BUSY  
} dw_hal_lockTypeDef;


#define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->lock == DW_HAL_TAG_LOCKED)   \
                                    {                                      \
                                       return NRF_ERROR_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->lock = DW_HAL_TAG_LOCKED;    \
                                    }                                      \
                                }while (0U)

 #define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                    (__HANDLE__)->lock = DW_HAL_TAG_UNLOCKED;    \
                                  }while (0U)

typedef enum {
    SPI_SPEED_UNINITIALIZED = 0,
    SPI_SPEED_SLOW =          1,
    SPI_SPEED_FAST =          2,
} spi_speed_e;

/* description of spi interface to DW1000 chip */
typedef struct
{
  nrf_drv_spi_t         spi_inst;
  uint32_t              frequency_slow;
  uint32_t              frequency_fast;
  uint32_t              csPin;
  nrf_drv_spi_config_t  spi_config;
  dw_hal_lockTypeDef    lock;
  spi_speed_e spi_init_stat; // use 1 for slow, use 2 for fast;
}spi_handle_t;

/* description of connection to the DW1000 chip */
typedef struct
{
  uint16_t        irqPin;
  uint16_t        rstPin;
  uint16_t        wkupPin;
  spi_handle_t    *pSpi;
}dw_t;

static volatile bool spi_xfer_done;
extern const dw_t *pDwMaster;
extern const dw_t *pDwSlave;

extern dw_t dw_chip_A;
extern dw_t dw_chip_B;


int readfromspi(uint16 headerLength,
                const uint8 *headerBuffer,
                uint32 readlength,
                uint8 *readBuffer);

int writetospi( uint16 headerLength,
                const uint8 *headerBuffer,
                uint32 bodylength,
                const uint8 *bodyBuffer);

decaIrqStatus_t decamutexon(void);
void decamutexoff(decaIrqStatus_t s);

void dw_rst_pin_irq_cb(void);

/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler_test(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context);

/******************************************************************************/

 /*****************************************************************************
  *
  *                                 Types definitions
  *
  *****************************************************************************/


#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


/******************************************************************************
 *
 *                              port function prototypes
 *
 ******************************************************************************/

void Sleep(uint32_t Delay);
uint32_t portGetTickCount(void);

void port_wakeup_dw1000(void);
error_e port_wakeup_dw1000_fast(void);
void port_disable_wake_init_dw(void);

//void port_set_dw1000_slowrate_first_time(dw_name_e chip_id);
void set_dw_spi_fast_rate(dw_name_e chip_id);
void set_dw_spi_slow_rate(dw_name_e chip_id);

void process_dwRSTn_irq(void);
void process_deca_irq(void);

void init_dw1000_irq(void);
void setup_DW1000RSTnIRQ(int enable);

void reset_DW1000(void);

int inittestapplication(void);
void peripherals_init(void);

void deca_uart_init(void);
void deca_uart_error_handle(app_uart_evt_t * p_event);
void deca_uart_transmit(char *ptr);
void deca_uart_receive(void);
void deca_discard_next_symbol(void);

void low_power(int);
void timer_event_handler(nrf_timer_event_t , void*);
int deca_usb_transmit(char *tx_buffer, int size);
void port_init_dw_chips(void);
void port_reinit_dw_chips(void);
void disable_dw1000_irq(void);
void set_SPI_master(void);
void set_SPI_slave(void);
void enable_dw1000_irq(void);

void port_stop_all_UWB(void);

void port_set_syncenable(int enable);
void port_set_sync(int enable);
void port_set_syncclear(int enable);

void Restart_UART_timer();

void start_timer(uint32_t *p_timestamp);
bool check_timer(uint32_t timestamp, uint32_t time);

#ifdef __cplusplus
}
#endif

#endif /* PORT_PLATFORM_H_ */

