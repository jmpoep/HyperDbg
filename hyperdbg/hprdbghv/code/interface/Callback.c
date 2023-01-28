/**
 * @file Callback.c
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief VMM callback interface routines
 * @details
 *
 * @version 0.2
 * @date 2023-01-29
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

/**
 * @brief routines callback to trigger events
 * @param EventType
 * @param CallingStage
 * @param Context
 * @param PostEventRequired
 * @param Regs
 *
 * @return VMM_CALLBACK_TRIGGERING_EVENT_STATUS_TYPE
 */
VMM_CALLBACK_TRIGGERING_EVENT_STATUS_TYPE
VmmCallbackTriggerEvents(VMM_EVENT_TYPE_ENUM                   EventType,
                         VMM_CALLBACK_EVENT_CALLING_STAGE_TYPE CallingStage,
                         PVOID                                 Context,
                         BOOLEAN *                             PostEventRequired,
                         GUEST_REGS *                          Regs)
{
    if (g_Callbacks.VmmCallbackTriggerEvents == NULL)
    {
        return VMM_CALLBACK_TRIGGERING_EVENT_STATUS_SUCCESSFUL_NO_INITIALIZED;
    }

    return g_Callbacks.VmmCallbackTriggerEvents(EventType, CallingStage, Context, PostEventRequired, Regs);
}

/**
 * @brief routine callback to set last error
 * @param LastError
 *
 * @return VOID
 */
VOID
VmmCallbackSetLastError(UINT32 LastError)
{
    if (g_Callbacks.VmmCallbackSetLastError == NULL)
    {
        //
        // Ignore setting the last error
        //
        return;
    }

    g_Callbacks.VmmCallbackSetLastError(LastError);
}

/**
 * @brief routine callback to handle external VMCALLs
 *
 * @param CoreId
 * @param VmcallNumber
 * @param OptionalParam1
 * @param OptionalParam2
 * @param OptionalParam3
 *
 * @return BOOLEAN
 */
BOOLEAN
VmmCallbackVmcallHandler(UINT32 CoreId,
                         UINT64 VmcallNumber,
                         UINT64 OptionalParam1,
                         UINT64 OptionalParam2,
                         UINT64 OptionalParam3)
{
    if (g_Callbacks.VmmCallbackVmcallHandler == NULL)
    {
        //
        // Ignore handling external VMCALLs
        //
        return;
    }

    return g_Callbacks.VmmCallbackVmcallHandler(CoreId, VmcallNumber, OptionalParam1, OptionalParam2, OptionalParam3);
}

/**
 * @brief routine callback to handle breakpoint exception
 *
 * @param CoreId
 *
 * @return BOOLEAN
 */
BOOLEAN
DebuggingCallbackHandleBreakpointException(UINT32 CoreId)
{
    if (g_Callbacks.DebuggingCallbackHandleBreakpointException == NULL)
    {
        //
        // re-inject it to not disrupt system normal execution
        //
        return FALSE;
    }

    return g_Callbacks.DebuggingCallbackHandleBreakpointException(CoreId);
}

/**
 * @brief routine callback to handle debug breakpoint exception
 *
 * @param CoreId
 *
 * @return BOOLEAN
 */
BOOLEAN
DebuggingCallbackHandleDebugBreakpointException(UINT32 CoreId)
{
    if (g_Callbacks.DebuggingCallbackHandleDebugBreakpointException == NULL)
    {
        //
        // re-inject it to not disrupt system normal execution
        //
        return FALSE;
    }

    return g_Callbacks.DebuggingCallbackHandleDebugBreakpointException(CoreId);
}
