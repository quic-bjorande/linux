/* SPDX-License-Identifier: GPL-2.0 */
/*
 * glue.h - DesignWare USB3 DRD glue header
 */

#ifndef __DRIVERS_USB_DWC3_GLUE_H
#define __DRIVERS_USB_DWC3_GLUE_H

#include <linux/types.h>
#include "core.h"

int dwc3_init(struct dwc3 *dwc, struct resource *res, bool ignore_clocks_and_resets);
void dwc3_uninit(struct dwc3 *dwc);

int dwc3_runtime_suspend(struct dwc3 *dwc);
int dwc3_runtime_resume(struct dwc3 *dwc);
int dwc3_runtime_idle(struct dwc3 *dwc);
int dwc3_suspend(struct dwc3 *dwc);
int dwc3_resume(struct dwc3 *dwc);
void dwc3_complete(struct dwc3 *dwc);

#endif
