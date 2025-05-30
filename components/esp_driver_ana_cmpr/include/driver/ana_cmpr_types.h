/*
 * SPDX-FileCopyrightText: 2023-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include "soc/soc_caps.h"
#include "soc/clk_tree_defs.h"
#include "hal/ana_cmpr_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Analog comparator unit
 */
typedef int ana_cmpr_unit_t;

#define ANA_CMPR_UNIT_0     0       /*!< @deprecated Analog comparator unit 0 */

/**
 * @brief Analog comparator reference source
 */
typedef enum {
    ANA_CMPR_REF_SRC_INTERNAL,      /*!< Analog Comparator reference voltage comes from internal, divided from VDD */
    ANA_CMPR_REF_SRC_EXTERNAL,      /*!< Analog Comparator reference voltage comes from external pin, e.g. `ANA_CMPR0_EXT_REF_GPIO` */
} ana_cmpr_ref_source_t;

/**
 * @brief Analog comparator channel type
 */
typedef enum {
    ANA_CMPR_SOURCE_CHAN,           /*!< Analog Comparator source channel, which is used to input the signal that to be compared */
    ANA_CMPR_EXT_REF_CHAN,          /*!< Analog Comparator external reference channel, which is used as the reference signal */
} ana_cmpr_channel_type_t;

/**
 * @brief Analog comparator unit handle
 */
typedef struct ana_cmpr_t *ana_cmpr_handle_t;

#if SOC_ANA_CMPR_SUPPORTED
/**
 * @brief Analog comparator clock source
 */
typedef soc_periph_ana_cmpr_clk_src_t ana_cmpr_clk_src_t;
#else
/**
 * @brief Analog comparator clock source
 */
typedef int ana_cmpr_clk_src_t;
#endif

/**
 * @brief Analog comparator cross event data
 */
typedef struct {
    ana_cmpr_cross_type_t cross_type;   /*!< The cross type of the target signal to the reference signal.
                                         *   Will either be ANA_CMPR_CROSS_POS or ANA_CMPR_CROSS_NEG
                                         *   Always be ANA_CMPR_CROSS_ANY if target does not support independent interrupt (like ESP32H2) */
} ana_cmpr_cross_event_data_t;

/**
 * @brief Prototype of Analog comparator event callback
 * @param[in] cmpr  Analog Comparator handle, created from `ana_cmpr_new_unit()`
 * @param[in] edata Point to Analog Comparator event data. The lifecycle of this pointer memory is inside this function,
 *                  user should copy it into static memory if used outside this function. (Currently not use)
 * @param[in] user_ctx User registered context, passed from `ana_cmpr_register_event_callbacks()`
 *
 * @return Whether a high priority task has been waken up by this callback function
 */
typedef bool (*ana_cmpr_cross_cb_t)(ana_cmpr_handle_t cmpr, const ana_cmpr_cross_event_data_t *edata, void *user_ctx);

#ifdef __cplusplus
}
#endif
