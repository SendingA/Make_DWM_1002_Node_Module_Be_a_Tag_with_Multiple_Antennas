// Terms and conditions of usage are described in detail in NORDIC
// SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
//
// Licensees are granted free, non-transferable use of the information. NO
// WARRANTY of ANY KIND is provided. This heading must NOT be removed from
// the file.

/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef MAC_MLME_COMM_STATUS_H_INCLUDED
#define MAC_MLME_COMM_STATUS_H_INCLUDED

#include <stdint.h>
#include "mac_common.h"

/** @file
 * The MAC Comm Status module declares the MAC communication status indication routine and
 * necessary types/macros according to the MAC specification.
 *
 * @defgroup mac_comm_status MAC MLME Comm Status API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Comm Status API.
 * @details The MAC Comm Status module declares communication status indication MLME routine and necessary
 * macros/types according to the MAC specification. MAC MLME Comm Status indication is declared as
 * mlme_comm_status_ind().
 */

/**
 * @brief   MLME-COMM-STATUS.indication
 *
 * @details The MLME-COMM-STATUS.indication primitive allows the MLME to indicate a
 * communication status.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.12.1
 */
typedef struct
{
    /**
     * The 16-bit PAN identifier of the device from which the frame was received or to
     * which the frame was being sent.
     */
    uint16_t            pan_id;

    /**
     * The source addressing mode for this primitive. This value can take one of the
     * following values:
     * @ref mac_addr_mode_t
     * 0x00 = no address (addressing fields omitted).
     * 0x01 = reserved.
     * 0x02 = 16-bit short address.
     * 0x03 = 64-bit extended address.
     */
    mac_addr_mode_t     src_addr_mode;

    /**
     * The individual device address of the entity from which the frame causing the error
     * originated.
     */
    mac_addr_t          src_addr;

    /**
     * The destination addressing mode for this primitive.
     * According to 7.1.12.1.1, Table 69.
     */
    mac_addr_mode_t     dst_addr_mode;

    /** The individual device address of the device for which the frame was intended. */
    mac_addr_t          dst_addr;

    /** The communications status. */
    mac_status_t        status;

    uint8_t             security_level;         /**< Security level. */
    uint8_t             key_id_mode;            /**< Key ID mode. */
    uint64_t            key_source;             /**< Key source. */
    uint8_t             key_index;              /**< Key index. */
} mlme_comm_status_ind_t;


/**
 * @brief   MLME-COMM-STATUS.indication handler
 *
 * @details The MLME-COMM-STATUS.indication primitive is generated by the MLME and issued to its next higher
 * layer either following a transmission instigated through a response primitive or on receipt of a frame that
 * generates an error in its security processing (see 7.5.8.2.3).
 *
 * @param ind MLME-COMM-STATUS.indication structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.12.1
 */
extern void mlme_comm_status_ind(mlme_comm_status_ind_t * ind);

/** @} */

#endif // MAC_MLME_COMM_STATUS_H_INCLUDED
