/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SRC_H_
#define _FSL_SRC_H_

#include "fsl_common.h"

/*! @addtogroup soc_src */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SRC driver version 2.0.0. */
#define FSL_SRC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#define SRC_SLICE_ADDRESS_OFFSET (0x200U)

#define SRC_SLICE_AUTHENTICATION_REGISTER_OFFSET  (0x0U)
#define SRC_SLICE_CONTROL_REGISTER_OFFSET         (0x4U)
#define SRC_SLICE_SETPOINT_CONFIG_REGISTER_OFFSET (0x8U)
#define SRC_SLICE_DOMAIN_CONFIG_REGISTER_OFFSET   (0x0CU)
#define SRC_SLICE_STATUS_REGISTER_OFFSET          (0x10U)

#define SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, registerOffset) \
    (((uint32_t)base) + SRC_SLICE_ADDRESS_OFFSET + ((uint32_t)(sliceName) << 5UL) + (registerOffset))

#define SRC_SLICE_STAT_UNDER_RST_MASK (0x1U)
#define SRC_SLICE_STAT_RST_BY_HW_MASK (0x4U)
#define SRC_SLICE_STAT_RST_BY_SW_MASK (0x8U)

/*!
 * @brief System core.
 */
typedef enum _src_core_name
{
    kSRC_CM7Core = 0x1U, /*!< System Core CM4. */
    kSRC_CM4Core = 0x2U, /*!< System Core CM7. */
} src_core_name_t;

/*!
 * @brief The enumeration of the boot fuse selection.
 */
typedef enum _src_boot_fuse_selection
{
    kSRC_SerialDownloaderBootFlow = 0U, /*!< The Boot flow jumps directly to the serial downloader. */
    kSRC_NormalBootFlow           = 1U  /*!< The Boot flow follows the Normal Boot flow. */
} src_boot_fuse_selection_t;

/*!
 * @brief The enumeration of global system reset sources.
 */
typedef enum _src_global_system_reset_source
{
    kSRC_WdogReset         = 0U,  /*!< WDOG triggers the global system reset. */
    kSRC_Wdog3Reset        = 2U,  /*!< WDOG3 triggers the global system reset. */
    kSRC_Wdog4Reset        = 4U,  /*!< WODG4 triggers the global system reset. */
    kSRC_M4LockUpReset     = 6U,  /*!< M4 core lockup triggers the global system reset. */
    kSRC_M7LockUpReset     = 8U,  /*!< M7 core lockup triggers the global system reset. */
    kSRC_M4RequestReset    = 10U, /*!< M4 core request triggers the global system reset. */
    kSRC_M7RequestReset    = 12U, /*!< M7 core request triggers the global system reset. */
    kSRC_TempsenseReset    = 14U, /*!< Tempsense trigggers the global system reset. */
    kSRC_CSUReset          = 16U, /*!< CSU triggers the global system reset. */
    kSRC_JageSoftwareReset = 18U, /*!< JATG software triggers the global system reset. */
    kSRC_OverVoltageReset  = 20U, /*!< Over voltage triggers the global system reset. */
} src_global_system_reset_source_t;

/*!
 * @brief The enumeration of reset status flags.
 */
enum _src_global_system_reset_status_flags
{
    kSRC_M7CoreIppResetFlag       = 1UL << 0UL,  /*!< The M7 Core reset is the result of ipp_reset_b pin. */
    kSRC_M7CoreM7RequestResetFlag = 1UL << 1UL,  /*!< The M7 Core reset is the result of M7 core reset request. */
    kSRC_M7CoreM7LockUpResetFlag  = 1UL << 2UL,  /*!< The M7 Core reset is the result of M7 core lock up. */
    kSRC_M7CoreCSUResetFlag       = 1UL << 3UL,  /*!< The M7 Core reset is the result of csu_reset_b input. */
    kSRC_M7CoreIppUserResetFlag   = 1UL << 4UL,  /*!< The M7 Core reset is the result of
                                                     ipp_user_reset_b qualified reset. */
    kSRC_M7CoreWdogResetFlag      = 1UL << 5UL,  /*!< The M7 Core reset is the result of the watchdog time-out event. */
    kSRC_M7CoreJtagResetFlag      = 1UL << 6UL,  /*!< The M7 Core reset is the result of HIGH-Z reset from JTAG. */
    kSRC_M7CoreJtagSWResetFlag    = 1UL << 7UL,  /*!< The M7 Core reset is the result of software reset from JTAG. */
    kSRC_M7CoreWdog3ResetFlag     = 1UL << 8UL,  /*!< The M7 Core reset is the result of watchdog3 time-out event. */
    kSRC_M7CoreWdog4ResetFlag     = 1UL << 9UL,  /*!< The M7 Core reset is the result of watchdog4 time-out event. */
    kSRC_M7CoreTempsenseResetFlag = 1UL << 10UL, /*!< The M7 Core reset is the result of on-chip temperature sensor. */
    kSRC_M7CoreM4RequestResetFlag = 1UL << 11UL, /*!< The M7 Core reset is the result of M4 CPU reset request. */
    kSRC_M7CoreM4LockUpResetFlag  = 1UL << 12UL, /*!< The M7 Core reset is the result of M4 CPU lock up. */
    kSRC_M7CoreOverVoltageResetFlag = 1UL << 13UL, /*!< The M7 Core reset is the result of over voltage. */
    kSRC_M7CoreCdogResetFlag        = 1UL << 14UL, /*!< The M7 Core reset is the result of Cdog. */

    kSRC_M4CoreIppResetFlag       = 1UL << 16UL, /*!< The M4 Core reset is the result of ipp_reset_b pin. */
    kSRC_M4CoreM4RequestResetFlag = 1UL << 17UL, /*!< The M4 Core reset is the result of M4 core reset request. */
    kSRC_M4CoreM4LockUpResetFlag  = 1UL << 18UL, /*!< The M4 Core reset is the result of M4 core lock up. */
    kSRC_M4CoreCSUResetFlag       = 1UL << 19UL, /*!< The M4 Core reset is the result of csu_reset_b input. */
    kSRC_M4CoreIppUserResetFlag   = 1UL << 20UL, /*!< The M4 Core reset is the result of
                                                    ipp_user_reset_b qualified reset. */
    kSRC_M4CoreWdogResetFlag      = 1UL << 21UL, /*!< The M4 Core reset is the result of the watchdog time-out event. */
    kSRC_M4CoreJtagResetFlag      = 1UL << 22UL, /*!< The M4 Core reset is the result of HIGH-Z reset from JTAG. */
    kSRC_M4CoreJtagSWResetFlag    = 1UL << 23UL, /*!< The M4 Core reset is the result of software reset from JTAG. */
    kSRC_M4CoreWdog3ResetFlag     = 1UL << 24UL, /*!< The M4 Core reset is the result of watchdog3 time-out event. */
    kSRC_M4CoreWdog4ResetFlag     = 1UL << 25UL, /*!< The M4 Core reset is the result of watchdog4 time-out event. */
    kSRC_M4CoreTempsenseResetFlag = 1UL << 26UL, /*!< The M4 Core reset is the result of on-chip temperature sensor. */
    kSRC_M4CoreM7RequestResetFlag = 1UL << 27UL, /*!< The M4 Core reset is the result of M7 CPU reset request. */
    kSRC_M4CoreM7LockUpResetFlag  = 1UL << 28UL, /*!< The M4 Core reset is the result of M7 CPU lock up. */
    kSRC_M4CoreOverVoltageResetFlag = 1UL << 29UL, /*!< The M4 Core reset is the result of over voltage. */
    kSRC_M4CoreCdogResetFlag        = 1UL << 30UL, /*!< The M4 Core reset is the result of Cdog. */
};

/*!
 * @brief The enumeration of global system reset mode.
 */
typedef enum _src_global_system_reset_mode
{
    kSRC_ResetSystem      = 0x0U, /*!< Generate the global system reset. */
    kSRC_DoNotResetSystem = 0x3U, /*!< Do not generate the global system reset. */
} src_global_system_reset_mode_t;

/*!
 * @brief The enumeration of the slice name.
 */
typedef enum _src_reset_slice_name
{
    kSRC_MegaSlice    = 0x0U, /*!< Megamix reset slice. */
    kSRC_DisplaySlice = 0x1U, /*!< Displaymix reset slice. */
    kSRC_WakeUpSlice  = 0x2U, /*!< Wakeupmix reset slice. */
    kSRC_LpsrSlice    = 0x3U, /*!< Lpsrmix reset slice. */
    kSRC_M4CoreSlice  = 0x4U, /*!< M4 core reset slice. */
    kSRC_M7CoreSlice  = 0x5U, /*!< M7 core reset slice. */
    kSRC_M4DebugSlice = 0x6U, /*!< M4 debug reset slice. */
    kSRC_M7DebugSlice = 0x7U, /*!< M7 debug reset slice. */
    kSRC_Usbphy1Slice = 0x8U, /*!< USBPHY1 reset slice. */
    kSRC_Usbphy2Slice = 0x9U, /*!< USBPHY2 reset slice. */
} src_reset_slice_name_t;

/*!
 * @brief The enumeration of the domain mode.
 */
enum _src_domain_mode_selection
{
    kSRC_Cpu0RunModeAssertReset     = 1UL << 0UL, /*!< CPU0 in run mode will assert slice reset. */
    kSRC_Cpu0WaitModeAssertReset    = 1UL << 1UL, /*!< CPU0 in wait mode will assert reset. */
    kSRC_Cpu0StopModeAssertReset    = 1UL << 2UL, /*!< CPU0 in stop mode will assert reset. */
    kSRC_Cpu0SuspendModeAssertReset = 1UL << 3UL, /*!< CPU0 in suspend mode will assert reset. */
    kSRC_Cpu1RunModeAssertReset     = 1UL << 4UL, /*!< CPU1 in run mode will assert slice reset. */
    kSRC_Cpu1WaitModeAssertReset    = 1UL << 5UL, /*!< CPU1 in wait mode will assert reset. */
    kSRC_Cpu1StopModeAssertReset    = 1UL << 6UL, /*!< CPU1 in stop mode will assert reset. */
    kSRC_Cpu1SuspendModeAssertReset = 1UL << 7UL, /*!< CPU1 in suspend mode will assert reset. */
};

/*!
 * @brief The enumeration of setpoint.
 */
enum _src_setpoint_selection
{
    kSRC_SetPoint0AssertReset  = 1UL << 0UL,  /*!< In setpoint0 will assert slice reset. */
    kSRC_SetPoint1AssertReset  = 1UL << 1UL,  /*!< In setpoint1 will assert slice reset. */
    kSRC_SetPoint2AssertReset  = 1UL << 2UL,  /*!< In setpoint2 will assert slice reset. */
    kSRC_SetPoint3AssertReset  = 1UL << 3UL,  /*!< In setpoint3 will assert slice reset. */
    kSRC_SetPoint4AssertReset  = 1UL << 4UL,  /*!< In setpoint4 will assert slice reset. */
    kSRC_SetPoint5AssertReset  = 1UL << 5UL,  /*!< In setpoint5 will assert slice reset. */
    kSRC_SetPoint6AssertReset  = 1UL << 6UL,  /*!< In setpoint6 will assert slice reset. */
    kSRC_SetPoint7AssertReset  = 1UL << 7UL,  /*!< In setpoint7 will assert slice reset. */
    kSRC_SetPoint8AssertReset  = 1UL << 8UL,  /*!< In setpoint8 will assert slice reset. */
    kSRC_SetPoint9AssertReset  = 1UL << 9UL,  /*!< In setpoint9 will assert slice reset. */
    kSRC_SetPoint10AssertReset = 1UL << 10UL, /*!< In setpoint10 will assert slice reset. */
    kSRC_SetPoint11AssertReset = 1UL << 11UL, /*!< In setpoint11 will assert slice reset. */
    kSRC_SetPoint12AssertReset = 1UL << 12UL, /*!< In setpoint12 will assert slice reset. */
    kSRC_SetPoint13AssertReset = 1UL << 13UL, /*!< In setpoint13 will assert slice reset. */
    kSRC_SetPoint14AssertReset = 1UL << 14UL, /*!< In setpoint14 will assert slice reset. */
    kSRC_SetPoint15AssertReset = 1UL << 15UL, /*!< In setpoint15 will assert slice reset. */
};

/*!
 * @brief The structure of setpoint authentication.
 */
typedef struct _src_setpoint_authentication
{
    bool enableSetpointTranferReset; /*!< Control whether reset slice is in setpoint mode.
                                        - \b true Slice hardware reset will be triggered by set point transition.
                                        - \b false Slice hardware reset will not be trigged by set point transition.
                                      */
    uint32_t whiteList;              /*!< Select the core to access set point control register.
                                          The logic OR'ed value of @ref src_core_name_t enumeration.  */
    bool lockWhiteList;              /*!< Control whether lock the value in white list */
    bool lockSetting;                /*!< Control whether lock the setpoint access setting. */
    bool allowNonSecureModeAccess;   /*!< Allow both secure and non-secure modes to config setpoint. */
    bool allowUserModeAccess;        /*!< Allow both privilege and user modes to config setpoint. */
} src_setpoint_authentication_t;

/*!
 * @brief The stucture of domain mode authentication.
 */
typedef struct _src_domain_mode_authentication
{
    bool enableDomainModeTransferReset; /*!< Control whether reset slice is in domaim mode.
                                        - \b true Slice hardware reset will be triggered by cpu power mode transition.
                                        - \b false Slice hardware reset will not be trigged by cpu power mode
                                        transition.  */
    uint32_t assignList; /*!< Select the core that reset of slice would be subject to the selected core status
                            transition. The logic OR'ed value of @ref src_core_name_t enumeration. */
    bool lockAssignList; /*!< Control whether lock the value in Assign list. */
} src_domain_mode_authentication_t;

/*!
 * @brief The enumeration of the reset source of each slice.
 */
enum _src_slice_reset_source
{
    kSRC_SoftwareReset          = SRC_SLICE_STAT_RST_BY_SW_MASK, /*!< Reset is caused by software setting. */
    kSRC_PowerModeTransferReset = SRC_SLICE_STAT_RST_BY_HW_MASK, /*!< Reset is caused by the power mode transfer. */
};

/*!
 * @brief The enumeration of the reset state of each slice.
 */
typedef enum _src_slice_reset_state
{
    kSRC_SliceResetFinished  = 0U, /*!< The reset is finished. */
    kSRC_SliceResetInProcess = 1U, /*!< The reset is in process. */
} src_slice_reset_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Core Reset release
 * @{
 */

/*!
 * @brief Releases related core reset operation.
 *
 * The core reset will be held until the boot core to release it.
 *
 * @param base SRC peripheral base address.
 * @param coreName The name of the reset core to be released.
 */
void SRC_ReleaseCoreReset(SRC_Type *base, src_core_name_t coreName);

/*! @} */

/*!
 * @name Latched Boot Arguments Related Interfaces
 * @{
 */

/*!
 * @brief Gets Boot configuration.
 *
 * @param base SRC peripheral base address.
 * @return Boot configuration. Please refer to fusemap.
 */
static inline uint32_t SRC_GetBootConfig(SRC_Type *base)
{
    return base->SBMR1;
}

/*!
 * @brief Gets the latched state of the BOOT_MODE1 and BOOT_MODE0 signals.
 *
 * @param base SRC peripheral base address.
 * @return Boot mode. Please refer to the Boot mode pin setting section of System Boot.
 */
static inline uint8_t SRC_GetBootMode(SRC_Type *base)
{
    return (uint8_t)((base->SBMR2 & SRC_SBMR2_BMOD_MASK) >> SRC_SBMR2_BMOD_SHIFT);
}

/*!
 * @brief Gets the state of the BT_FUSE_SEL fuse.
 *
 * @param base SRC peripheral base address.
 * @return The state of the BT_FUSE_SEL fuse, please refer to fusemap for more information.
 */
static inline src_boot_fuse_selection_t SRC_GetBootFuseSelection(SRC_Type *base)
{
    return (src_boot_fuse_selection_t)(uint32_t)((base->SBMR2 & SRC_SBMR2_BT_FUSE_SEL_MASK) >>
                                                 SRC_SBMR2_BT_FUSE_SEL_SHIFT);
}

/*!
 * @brief Gets the state of the SECCONFIG[1] fuse.
 *
 * @param base SRC peripheral base address.
 * @return The state of the SECCONFIG[1] fuse. Please refer to fusemap for more information.
 */
static inline uint8_t SRC_GetSECConfigFuseState(SRC_Type *base)
{
    return (uint8_t)((base->SBMR2 & SRC_SBMR2_SEC_CONFIG_MASK) >> SRC_SBMR2_SEC_CONFIG_SHIFT);
}

/* ! @} */

/*!
 * @name Global System Related Interfaces
 * @{
 */

/*!
 * @brief Sets the reset mode of global system reset source.
 *
 * This function sets the selected mode of the input global system reset sources.
 *
 * @param base SRC peripheral base address.
 * @param resetSource The global system reset source. See @ref src_global_system_reset_source_t for more details.
 * @param resetMode The reset mode of each reset source. See @ref src_global_system_reset_mode_t for more details.
 */
void SRC_SetGlobalSystemResetMode(SRC_Type *base,
                                  src_global_system_reset_source_t resetSource,
                                  src_global_system_reset_mode_t resetMode);

/*!
 * @brief Gets global system reset status flags.
 *
 * @param base SRC peripheral base address.
 * @return The status of global system reset status. See @ref _src_global_system_reset_status_flags for more details.
 */
static inline uint32_t SRC_GetResetStatusFlags(SRC_Type *base)
{
    return base->SRSR;
}

/*!
 * @brief Clears the status of global reset.
 *
 * @param base SRC peripheral base address.
 * @param mask The reset status flag to be cleared. See @ref _src_global_system_reset_status_flags for more details.
 */
static inline void SRC_ClearGlobalSystemResetStatus(SRC_Type *base, uint32_t mask)
{
    base->SRSR = mask;
}

/*! @} */

/*!
 * @name Slice Software Reset Related Interfaces
 * @{
 */

/*!
 * @brief Asserts software reset for the selected slice.
 *
 * @note This function will return as soon as the resset is finished.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The slice to be reset. See @ref src_reset_slice_name_t for more details.
 */
void SRC_AssertSliceSoftwareReset(SRC_Type *base, src_reset_slice_name_t sliceName);

/*! @} */

/*!
 * @name Slice Low-Power Mode Transition Related Interfaces
 * @{
 */

/*!
 * @brief Sets setpoint authentication for the selected reset slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 * @param authentication Pointer to the structure. See @ref src_setpoint_authentication_t for more details.
 */
void SRC_SetSliceSetPointAuthentication(SRC_Type *base,
                                        src_reset_slice_name_t sliceName,
                                        src_setpoint_authentication_t *authentication);

/*!
 * @brief Sets setpoint configuration for the selected reset slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 * @param setPointConfig The logic OR'ed value of @ref _src_setpoint_selection enumeration. When the system in the
 * selected setpoint slice reset will be assert.
 */
void SRC_SetSliceSetPointConfig(SRC_Type *base, src_reset_slice_name_t sliceName, uint32_t setpointConfig);

/*!
 * @brief Sets domain mode authentication for the selected reset slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 * @param authentication Pointer to the structure. See @ref src_domain_mode_authentication_t for more details.
 */
void SRC_SetSliceDomainModeAuthentication(SRC_Type *base,
                                          src_reset_slice_name_t sliceName,
                                          src_domain_mode_authentication_t *authentication);

/*!
 * @brief Sets domain mode configuration for the selected reset slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 * @param setPointConfig The logic OR'ed value of @ref _src_domain_mode_selection enumerations.
 */
void SRC_SetSliceDomainModeConfig(SRC_Type *base, src_reset_slice_name_t sliceName, uint32_t domainConfig);

/*!
 * @brief Locks the value of SETPOINT_MODE and DOMAIN_MODE for the selected reset slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 */
void SRC_LockSliceMode(SRC_Type *base, src_reset_slice_name_t sliceName);

/*! @} */

/*!
 * @name Get/Clear Slice Reset Status Flags
 * @{
 */

/*!
 * @brief Gets the reset status flags of the selected slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The slice to be reset. See @ref src_reset_slice_name_t for more details.
 * @return The reset status flags for the selected slice. Please refer to @ref _src_slice_reset_source for details.
 */
static inline uint32_t SRC_GetSliceResetStatusFlags(SRC_Type *base, src_reset_slice_name_t sliceName)
{
    return (*(volatile uint32_t *)(SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_STATUS_REGISTER_OFFSET)) &
            (SRC_SLICE_STAT_RST_BY_HW_MASK | SRC_SLICE_STAT_RST_BY_SW_MASK));
}

/*!
 * @brief Clears the reset status flags of the selected slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected slice. See @ref src_reset_slice_name_t for more details.
 * @param mask The reset status flags to be cleared. Please refer to @ref _src_slice_reset_source for more details.
 */
static inline void SRC_ClearSliceResetStatusFlags(SRC_Type *base, src_reset_slice_name_t sliceName, uint32_t mask)
{
    *(volatile uint32_t *)SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_STATUS_REGISTER_OFFSET) = mask;
}

/* @} */

/*!
 * @name Get Slice Reset State
 * @{
 */

/*!
 * @brief Gets the reset state of the selected slice.
 *
 * @param base SRC peripheral base address.
 * @param sliceName The selected slice. See @ref src_reset_slice_name_t for more details.
 * @retval kSRC_SliceResetInProcess The reset is in process.
 * @retval kSRC_SliceResetFinished  The reset is finished.
 */
src_slice_reset_state_t SRC_GetSliceResetState(SRC_Type *base, src_reset_slice_name_t sliceName);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_SRC_H_ */
