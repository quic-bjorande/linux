// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2025, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#define pr_fmt(fmt) "dwc3-flattening: " fmt

#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/slab.h>
#include "dwc3-flattening.h"

struct dwc3_overlay_symbol {
	const char *symbol;
	const char *path;
};

struct dwc3_overlay_data {
	const void *fdt;
	const void *end;
	const char *migrate_match;
	struct dwc3_overlay_symbol *symbols;
};

static const struct dwc3_overlay_data dwc3_qcom_apq8094_overlay = {
	.fdt = __dtb_dwc3_qcom_apq8094_begin,
	.end = __dtb_dwc3_qcom_apq8094_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@f9000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_apq8096_overlay = {
	.fdt = __dtb_dwc3_qcom_apq8096_begin,
	.end = __dtb_dwc3_qcom_apq8096_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb2_id", "/usb2-id" },
		{ "usb3_id", "/usb3-id" },
		{ "usb3phy", "/soc@0/phy@7410000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_apq8096_inforce_ifc6640_overlay = {
	.fdt = __dtb_dwc3_qcom_apq8096_inforce_ifc6640_begin,
	.end = __dtb_dwc3_qcom_apq8096_inforce_ifc6640_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb3phy", "/soc@0/phy@7410000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq4018_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq4018_begin,
	.end = __dtb_dwc3_qcom_ipq4018_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "usb2_hs_phy", "/soc/usb-phy@a8000" },
		{ "usb3_hs_phy", "/soc/usb-phy@a6000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq4018_8dev_jalapeno_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq4018_8dev_jalapeno_begin,
	.end = __dtb_dwc3_qcom_ipq4018_8dev_jalapeno_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "usb2_hs_phy", "/soc/usb-phy@a8000" },
		{ "usb3_hs_phy", "/soc/usb-phy@a6000" },
		{ "usb3_ss_phy", "/soc/usb-phy@9a000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq4019_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq4019_begin,
	.end = __dtb_dwc3_qcom_ipq4019_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "usb2_hs_phy", "/soc/usb-phy@a8000" },
		{ "usb3_hs_phy", "/soc/usb-phy@a6000" },
		{ "usb3_ss_phy", "/soc/usb-phy@9a000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq5018_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq5018_begin,
	.end = __dtb_dwc3_qcom_ipq5018_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "usbphy0", "/soc@0/phy@5b000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq5332_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq5332_begin,
	.end = __dtb_dwc3_qcom_ipq5332_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "usbphy0", "/soc@0/phy@7b000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq5424_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq5424_begin,
	.end = __dtb_dwc3_qcom_ipq5424_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "qusb_phy_0", "/soc@0/phy@7b000" },
		{ "qusb_phy_1", "/soc@0/phy@71000" },
		{ "ssphy_0", "/soc@0/phy@7d000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq6018_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq6018_begin,
	.end = __dtb_dwc3_qcom_ipq6018_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "qusb_phy_0", "/soc@0/qusb@79000" },
		{ "qusb_phy_1", "/soc@0/qusb@59000" },
		{ "ssphy_0", "/soc@0/ssphy@78000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq8064_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq8064_begin,
	.end = __dtb_dwc3_qcom_ipq8064_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hs_phy_0", "/soc/phy@100f8800" },
		{ "hs_phy_1", "/soc/phy@110f8800" },
		{ "ss_phy_0", "/soc/phy@100f8830" },
		{ "ss_phy_1", "/soc/phy@110f8830" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq8074_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq8074_begin,
	.end = __dtb_dwc3_qcom_ipq8074_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "qusb_phy_0", "/soc@0/phy@79000" },
		{ "qusb_phy_1", "/soc@0/phy@59000" },
		{ "ssphy_0", "/soc@0/phy@78000" },
		{ "ssphy_1", "/soc@0/phy@58000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_ipq9574_overlay = {
	.fdt = __dtb_dwc3_qcom_ipq9574_begin,
	.end = __dtb_dwc3_qcom_ipq9574_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "usb_0_qmpphy", "/soc@0/phy@7d000" },
		{ "usb_0_qusbphy", "/soc@0/phy@7b000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8953_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8953_begin,
	.end = __dtb_dwc3_qcom_msm8953_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy", "/soc@0/phy@79000" },
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8992_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8992_begin,
	.end = __dtb_dwc3_qcom_msm8992_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@f9000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8994_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8994_begin,
	.end = __dtb_dwc3_qcom_msm8994_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@f9000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_begin,
	.end = __dtb_dwc3_qcom_msm8996_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb3phy", "/soc@0/phy@7410000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_oneplus_oneplus3_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_oneplus_oneplus3_begin,
	.end = __dtb_dwc3_qcom_msm8996_oneplus_oneplus3_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_oneplus_oneplus3t_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_oneplus_oneplus3t_begin,
	.end = __dtb_dwc3_qcom_msm8996_oneplus_oneplus3t_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_sony_dora_row_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_sony_dora_row_begin,
	.end = __dtb_dwc3_qcom_msm8996_sony_dora_row_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb3_id", "/usb3-id" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_sony_kagura_row_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_sony_kagura_row_begin,
	.end = __dtb_dwc3_qcom_msm8996_sony_kagura_row_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb3_id", "/usb3-id" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_sony_keyaki_row_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_sony_keyaki_row_begin,
	.end = __dtb_dwc3_qcom_msm8996_sony_keyaki_row_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "usb3_id", "/usb3-id" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_xiaomi_gemini_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_xiaomi_gemini_begin,
	.end = __dtb_dwc3_qcom_msm8996_xiaomi_gemini_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "typec", "/soc@0/i2c@75b7000/typec@47" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_xiaomi_natrium_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_xiaomi_natrium_begin,
	.end = __dtb_dwc3_qcom_msm8996_xiaomi_natrium_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "typec", "/soc@0/i2c@75b7000/typec@47" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8996_xiaomi_scorpio_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8996_xiaomi_scorpio_begin,
	.end = __dtb_dwc3_qcom_msm8996_xiaomi_scorpio_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy1", "/soc@0/phy@7411000" },
		{ "hsusb_phy2", "/soc@0/phy@7412000" },
		{ "intc", "/soc@0/interrupt-controller@9bc0000" },
		{ "typec", "/soc@0/i2c@75b7000/typec@47" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_begin,
	.end = __dtb_dwc3_qcom_msm8998_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{ "usb3phy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_fxtec_pro1_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_fxtec_pro1_begin,
	.end = __dtb_dwc3_qcom_msm8998_fxtec_pro1_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{ "usb3phy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_oneplus_cheeseburger_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_oneplus_cheeseburger_begin,
	.end = __dtb_dwc3_qcom_msm8998_oneplus_cheeseburger_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_oneplus_dumpling_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_oneplus_dumpling_begin,
	.end = __dtb_dwc3_qcom_msm8998_oneplus_dumpling_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_sony_xperia_lilac_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_sony_xperia_lilac_begin,
	.end = __dtb_dwc3_qcom_msm8998_sony_xperia_lilac_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{ "usb3phy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_sony_xperia_maple_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_sony_xperia_maple_begin,
	.end = __dtb_dwc3_qcom_msm8998_sony_xperia_maple_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{ "usb3phy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_sony_xperia_poplar_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_sony_xperia_poplar_begin,
	.end = __dtb_dwc3_qcom_msm8998_sony_xperia_poplar_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{ "usb3phy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_msm8998_xiaomi_sagit_overlay = {
	.fdt = __dtb_dwc3_qcom_msm8998_xiaomi_sagit_begin,
	.end = __dtb_dwc3_qcom_msm8998_xiaomi_sagit_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy", "/soc@0/phy@c012000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qcm2290_overlay = {
	.fdt = __dtb_dwc3_qcom_qcm2290_begin,
	.end = __dtb_dwc3_qcom_qcm2290_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "mpm", "/remoteproc/interrupt-controller" },
		{ "usb_hsphy", "/soc@0/phy@1613000" },
		{ "usb_qmpphy", "/soc@0/phy@1615000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qcm6490_overlay = {
	.fdt = __dtb_dwc3_qcom_qcm6490_begin,
	.end = __dtb_dwc3_qcom_qcm6490_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qcs404_overlay = {
	.fdt = __dtb_dwc3_qcom_qcs404_begin,
	.end = __dtb_dwc3_qcom_qcs404_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{ "usb2_phy_prim", "/soc@0/phy@7a000" },
		{ "usb2_phy_sec", "/soc@0/phy@7c000" },
		{ "usb3_phy", "/soc@0/phy@78000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qcs615_overlay = {
	.fdt = __dtb_dwc3_qcom_qcs615_begin,
	.end = __dtb_dwc3_qcom_qcs615_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_hsphy_2", "/soc@0/phy@88e3000" },
		{ "usb_qmpphy", "/soc@0/phy@88e6000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qcs8300_overlay = {
	.fdt = __dtb_dwc3_qcom_qcs8300_begin,
	.end = __dtb_dwc3_qcom_qcs8300_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@8904000" },
		{ "usb_2_hsphy", "/soc@0/phy@8906000" },
		{ "usb_qmpphy", "/soc@0/phy@8907000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qdu1000_overlay = {
	.fdt = __dtb_dwc3_qcom_qdu1000_begin,
	.end = __dtb_dwc3_qcom_qdu1000_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17200000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e5000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_qru1000_overlay = {
	.fdt = __dtb_dwc3_qcom_qru1000_begin,
	.end = __dtb_dwc3_qcom_qru1000_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17200000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e5000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sa8155p_overlay = {
	.fdt = __dtb_dwc3_qcom_sa8155p_begin,
	.end = __dtb_dwc3_qcom_sa8155p_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb2phy_ac_en1_default", "/soc@0/pinctrl@3100000/usb2phy-ac-en1-default-state" },
		{ "usb2phy_ac_en2_default", "/soc@0/pinctrl@3100000/usb2phy-ac-en2-default-state" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sa8540p_overlay = {
	.fdt = __dtb_dwc3_qcom_sa8540p_begin,
	.end = __dtb_dwc3_qcom_sa8540p_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_0_hsphy", "/soc@0/phy@88e5000" },
		{ "usb_0_qmpphy", "/soc@0/phy@88eb000" },
		{ "usb_1_hsphy", "/soc@0/phy@8902000" },
		{ "usb_1_qmpphy", "/soc@0/phy@8903000" },
		{ "usb_2_hsphy0", "/soc@0/phy@88e7000" },
		{ "usb_2_hsphy1", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy2", "/soc@0/phy@88e9000" },
		{ "usb_2_hsphy3", "/soc@0/phy@88ea000" },
		{ "usb_2_qmpphy0", "/soc@0/phy@88ef000" },
		{ "usb_2_qmpphy1", "/soc@0/phy@88f1000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sa8775p_overlay = {
	.fdt = __dtb_dwc3_qcom_sa8775p_begin,
	.end = __dtb_dwc3_qcom_sa8775p_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_0_hsphy", "/soc@0/phy@88e4000" },
		{ "usb_0_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e6000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88ea000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e7000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sar2130p_overlay = {
	.fdt = __dtb_dwc3_qcom_sar2130p_begin,
	.end = __dtb_dwc3_qcom_sar2130p_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17200000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_dp_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sc7180_overlay = {
	.fdt = __dtb_dwc3_qcom_sc7180_begin,
	.end = __dtb_dwc3_qcom_sc7180_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sc7280_overlay = {
	.fdt = __dtb_dwc3_qcom_sc7280_begin,
	.end = __dtb_dwc3_qcom_sc7280_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sc8180x_overlay = {
	.fdt = __dtb_dwc3_qcom_sc8180x_begin,
	.end = __dtb_dwc3_qcom_sc8180x_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_mp_hsphy0", "/soc@0/phy@88e4000" },
		{ "usb_mp_hsphy1", "/soc@0/phy@88e5000" },
		{ "usb_mp_qmpphy0", "/soc@0/phy@88eb000" },
		{ "usb_mp_qmpphy1", "/soc@0/phy@88ec000" },
		{ "usb_prim_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_prim_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_sec_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_sec_qmpphy", "/soc@0/phy@88ee000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sc8280xp_overlay = {
	.fdt = __dtb_dwc3_qcom_sc8280xp_begin,
	.end = __dtb_dwc3_qcom_sc8280xp_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_0_hsphy", "/soc@0/phy@88e5000" },
		{ "usb_0_qmpphy", "/soc@0/phy@88eb000" },
		{ "usb_1_hsphy", "/soc@0/phy@8902000" },
		{ "usb_1_qmpphy", "/soc@0/phy@8903000" },
		{ "usb_2_hsphy0", "/soc@0/phy@88e7000" },
		{ "usb_2_hsphy1", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy2", "/soc@0/phy@88e9000" },
		{ "usb_2_hsphy3", "/soc@0/phy@88ea000" },
		{ "usb_2_qmpphy0", "/soc@0/phy@88ef000" },
		{ "usb_2_qmpphy1", "/soc@0/phy@88f1000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sc8280xp_microsoft_blackrock_overlay = {
	.fdt = __dtb_dwc3_qcom_sc8280xp_microsoft_blackrock_begin,
	.end = __dtb_dwc3_qcom_sc8280xp_microsoft_blackrock_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_0_hsphy", "/soc@0/phy@88e5000" },
		{ "usb_0_qmpphy", "/soc@0/phy@88eb000" },
		{ "usb_1_hsphy", "/soc@0/phy@8902000" },
		{ "usb_1_qmpphy", "/soc@0/phy@8903000" },
		{ "usb_2_hsphy0", "/soc@0/phy@88e7000" },
		{ "usb_2_qmpphy0", "/soc@0/phy@88ef000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sda660_overlay = {
	.fdt = __dtb_dwc3_qcom_sda660_begin,
	.end = __dtb_dwc3_qcom_sda660_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy0", "/soc@0/phy@c012000" },
		{ "qusb2phy1", "/soc@0/phy@c014000" },
		{ "usb3_qmpphy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm450_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm450_begin,
	.end = __dtb_dwc3_qcom_sdm450_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy", "/soc@0/phy@79000" },
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm630_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm630_begin,
	.end = __dtb_dwc3_qcom_sdm630_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy0", "/soc@0/phy@c012000" },
		{ "qusb2phy1", "/soc@0/phy@c014000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm632_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm632_begin,
	.end = __dtb_dwc3_qcom_sdm632_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "hsusb_phy", "/soc@0/phy@79000" },
		{ "intc", "/soc@0/interrupt-controller@b000000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm636_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm636_begin,
	.end = __dtb_dwc3_qcom_sdm636_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy0", "/soc@0/phy@c012000" },
		{ "qusb2phy1", "/soc@0/phy@c014000" },
		{ "usb3_qmpphy", "/soc@0/phy@c010000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm660_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm660_begin,
	.end = __dtb_dwc3_qcom_sdm660_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "extcon_usb", "/extcon-usb" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "qusb2phy0", "/soc@0/phy@c012000" },
		{ "qusb2phy1", "/soc@0/phy@c014000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm670_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm670_begin,
	.end = __dtb_dwc3_qcom_sdm670_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_begin,
	.end = __dtb_dwc3_qcom_sdm845_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_lenovo_yoga_c630_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_lenovo_yoga_c630_begin,
	.end = __dtb_dwc3_qcom_sdm845_lenovo_yoga_c630_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_lg_judyln_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_lg_judyln_begin,
	.end = __dtb_dwc3_qcom_sdm845_lg_judyln_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_lg_judyp_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_lg_judyp_begin,
	.end = __dtb_dwc3_qcom_sdm845_lg_judyp_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_qcom_sdm845_mtp_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_qcom_sdm845_mtp_begin,
	.end = __dtb_dwc3_qcom_sdm845_qcom_sdm845_mtp_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_samsung_starqltechn_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_samsung_starqltechn_begin,
	.end = __dtb_dwc3_qcom_sdm845_samsung_starqltechn_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_samsung_w737_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_samsung_w737_begin,
	.end = __dtb_dwc3_qcom_sdm845_samsung_w737_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_shift_axolotl_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_shift_axolotl_begin,
	.end = __dtb_dwc3_qcom_sdm845_shift_axolotl_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_thundercomm_db845c_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_thundercomm_db845c_begin,
	.end = __dtb_dwc3_qcom_sdm845_thundercomm_db845c_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_xiaomi_beryllium_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_xiaomi_beryllium_begin,
	.end = __dtb_dwc3_qcom_sdm845_xiaomi_beryllium_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdm845_xiaomi_beryllium_ebbg_overlay = {
	.fdt = __dtb_dwc3_qcom_sdm845_xiaomi_beryllium_ebbg_begin,
	.end = __dtb_dwc3_qcom_sdm845_xiaomi_beryllium_ebbg_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc_intc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdx55_overlay = {
	.fdt = __dtb_dwc3_qcom_sdx55_begin,
	.end = __dtb_dwc3_qcom_sdx55_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc/iommu@15000000" },
		{ "intc", "/soc/interrupt-controller@17800000" },
		{ "pdc", "/soc/interrupt-controller@b210000" },
		{ "usb_hsphy", "/soc/phy@ff4000" },
		{ "usb_qmpphy", "/soc/phy@ff6000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdx65_overlay = {
	.fdt = __dtb_dwc3_qcom_sdx65_begin,
	.end = __dtb_dwc3_qcom_sdx65_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc/iommu@15000000" },
		{ "intc", "/soc/interrupt-controller@17800000" },
		{ "pdc", "/soc/interrupt-controller@b210000" },
		{ "usb_hsphy", "/soc/phy@ff4000" },
		{ "usb_qmpphy", "/soc/phy@ff6000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sdx75_overlay = {
	.fdt = __dtb_dwc3_qcom_sdx75_begin,
	.end = __dtb_dwc3_qcom_sdx75_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17200000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_hsphy", "/soc@0/phy@ff4000" },
		{ "usb_qmpphy", "/soc@0/phy@ff6000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm4250_overlay = {
	.fdt = __dtb_dwc3_qcom_sm4250_begin,
	.end = __dtb_dwc3_qcom_sm4250_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "usb_hsphy", "/soc@0/phy@1613000" },
		{ "usb_qmpphy", "/soc@0/phy@1615000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm4250_oneplus_billie2_overlay = {
	.fdt = __dtb_dwc3_qcom_sm4250_oneplus_billie2_begin,
	.end = __dtb_dwc3_qcom_sm4250_oneplus_billie2_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "usb_hsphy", "/soc@0/phy@1613000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm6115_overlay = {
	.fdt = __dtb_dwc3_qcom_sm6115_begin,
	.end = __dtb_dwc3_qcom_sm6115_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "usb_hsphy", "/soc@0/phy@1613000" },
		{ "usb_qmpphy", "/soc@0/phy@1615000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm6115_lenovo_j606f_overlay = {
	.fdt = __dtb_dwc3_qcom_sm6115_lenovo_j606f_begin,
	.end = __dtb_dwc3_qcom_sm6115_lenovo_j606f_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "usb_hsphy", "/soc@0/phy@1613000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm6125_overlay = {
	.fdt = __dtb_dwc3_qcom_sm6125_begin,
	.end = __dtb_dwc3_qcom_sm6125_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "extcon_usb", "/extcon-usb" },
		{ "hsusb_phy1", "/soc@0/phy@1613000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm6350_overlay = {
	.fdt = __dtb_dwc3_qcom_sm6350_begin,
	.end = __dtb_dwc3_qcom_sm6350_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm6375_overlay = {
	.fdt = __dtb_dwc3_qcom_sm6375_begin,
	.end = __dtb_dwc3_qcom_sm6375_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@c600000" },
		{ "intc", "/soc@0/interrupt-controller@f200000" },
		{ "mpm", "/interrupt-controller" },
		{ "usb_1_hsphy", "/soc@0/phy@162b000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm7125_overlay = {
	.fdt = __dtb_dwc3_qcom_sm7125_begin,
	.end = __dtb_dwc3_qcom_sm7125_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm7225_overlay = {
	.fdt = __dtb_dwc3_qcom_sm7225_begin,
	.end = __dtb_dwc3_qcom_sm7225_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm7325_overlay = {
	.fdt = __dtb_dwc3_qcom_sm7325_begin,
	.end = __dtb_dwc3_qcom_sm7325_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8150_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8150_begin,
	.end = __dtb_dwc3_qcom_sm8150_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e2000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8250_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8250_begin,
	.end = __dtb_dwc3_qcom_sm8250_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8250_xiaomi_elish_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8250_xiaomi_elish_begin,
	.end = __dtb_dwc3_qcom_sm8250_xiaomi_elish_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8350_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8350_begin,
	.end = __dtb_dwc3_qcom_sm8350_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8350_qcom_sm8350_hdk_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8350_qcom_sm8350_hdk_begin,
	.end = __dtb_dwc3_qcom_sm8350_qcom_sm8350_hdk_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17a00000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e4000" },
		{ "usb_2_qmpphy", "/soc@0/phy@88eb000" },
		{ "usb_hub_enabled_state", "/soc@0/pinctrl@f100000/usb-hub-enabled-state" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8450_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8450_begin,
	.end = __dtb_dwc3_qcom_sm8450_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17100000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_1_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8550_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8550_begin,
	.end = __dtb_dwc3_qcom_sm8550_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17100000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_dp_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_sm8650_overlay = {
	.fdt = __dtb_dwc3_qcom_sm8650_begin,
	.end = __dtb_dwc3_qcom_sm8650_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17100000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_hsphy", "/soc@0/phy@88e3000" },
		{ "usb_dp_qmpphy", "/soc@0/phy@88e8000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_x1e80100_overlay = {
	.fdt = __dtb_dwc3_qcom_x1e80100_begin,
	.end = __dtb_dwc3_qcom_x1e80100_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17000000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_ss0_hsphy", "/soc@0/phy@fd3000" },
		{ "usb_1_ss0_qmpphy", "/soc@0/phy@fd5000" },
		{ "usb_1_ss1_hsphy", "/soc@0/phy@fd9000" },
		{ "usb_1_ss1_qmpphy", "/soc@0/phy@fda000" },
		{ "usb_1_ss2_hsphy", "/soc@0/phy@fde000" },
		{ "usb_1_ss2_qmpphy", "/soc@0/phy@fdf000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e0000" },
		{ "usb_mp_hsphy0", "/soc@0/phy@88e1000" },
		{ "usb_mp_hsphy1", "/soc@0/phy@88e2000" },
		{ "usb_mp_qmpphy0", "/soc@0/phy@88e3000" },
		{ "usb_mp_qmpphy1", "/soc@0/phy@88e5000" },
		{}
	}
};

static const struct dwc3_overlay_data dwc3_qcom_x1e80100_hp_omnibook_x14_overlay = {
	.fdt = __dtb_dwc3_qcom_x1e80100_hp_omnibook_x14_begin,
	.end = __dtb_dwc3_qcom_x1e80100_hp_omnibook_x14_end,
	.migrate_match = "qcom,dwc3",
	.symbols = (struct dwc3_overlay_symbol[]) {
		{ "apps_smmu", "/soc@0/iommu@15000000" },
		{ "intc", "/soc@0/interrupt-controller@17000000" },
		{ "pdc", "/soc@0/interrupt-controller@b220000" },
		{ "usb_1_ss0_hsphy", "/soc@0/phy@fd3000" },
		{ "usb_1_ss0_qmpphy", "/soc@0/phy@fd5000" },
		{ "usb_1_ss1_hsphy", "/soc@0/phy@fd9000" },
		{ "usb_1_ss1_qmpphy", "/soc@0/phy@fda000" },
		{ "usb_1_ss2_hsphy", "/soc@0/phy@fde000" },
		{ "usb_1_ss2_qmpphy", "/soc@0/phy@fdf000" },
		{ "usb_2_hsphy", "/soc@0/phy@88e0000" },
		{ "usb_mp_hsphy0", "/soc@0/phy@88e1000" },
		{ "usb_mp_qmpphy0", "/soc@0/phy@88e3000" },
		{}
	}
};

static const struct of_device_id dwc3_flatten_of_match[] = {
	{ .compatible = "8dev,jalapeno", .data = &dwc3_qcom_ipq4018_8dev_jalapeno_overlay },
	{ .compatible = "fxtec,pro1", .data = &dwc3_qcom_msm8998_fxtec_pro1_overlay },
	{ .compatible = "hp,omnibook-x14", .data = &dwc3_qcom_x1e80100_hp_omnibook_x14_overlay },
	{ .compatible = "inforce,ifc6640", .data = &dwc3_qcom_apq8096_inforce_ifc6640_overlay },
	{ .compatible = "lenovo,j606f", .data = &dwc3_qcom_sm6115_lenovo_j606f_overlay },
	{ .compatible = "lenovo,yoga-c630", .data = &dwc3_qcom_sdm845_lenovo_yoga_c630_overlay },
	{ .compatible = "lg,judyln", .data = &dwc3_qcom_sdm845_lg_judyln_overlay },
	{ .compatible = "lg,judyp", .data = &dwc3_qcom_sdm845_lg_judyp_overlay },
	{ .compatible = "microsoft,blackrock", .data = &dwc3_qcom_sc8280xp_microsoft_blackrock_overlay },
	{ .compatible = "oneplus,billie2", .data = &dwc3_qcom_sm4250_oneplus_billie2_overlay },
	{ .compatible = "oneplus,cheeseburger", .data = &dwc3_qcom_msm8998_oneplus_cheeseburger_overlay },
	{ .compatible = "oneplus,dumpling", .data = &dwc3_qcom_msm8998_oneplus_dumpling_overlay },
	{ .compatible = "oneplus,oneplus3", .data = &dwc3_qcom_msm8996_oneplus_oneplus3_overlay },
	{ .compatible = "oneplus,oneplus3t", .data = &dwc3_qcom_msm8996_oneplus_oneplus3t_overlay },
	{ .compatible = "qcom,apq8094", .data = &dwc3_qcom_apq8094_overlay },
	{ .compatible = "qcom,apq8096", .data = &dwc3_qcom_apq8096_overlay },
	{ .compatible = "qcom,ipq4018", .data = &dwc3_qcom_ipq4018_overlay },
	{ .compatible = "qcom,ipq4019", .data = &dwc3_qcom_ipq4019_overlay },
	{ .compatible = "qcom,ipq5018", .data = &dwc3_qcom_ipq5018_overlay },
	{ .compatible = "qcom,ipq5332", .data = &dwc3_qcom_ipq5332_overlay },
	{ .compatible = "qcom,ipq5424", .data = &dwc3_qcom_ipq5424_overlay },
	{ .compatible = "qcom,ipq6018", .data = &dwc3_qcom_ipq6018_overlay },
	{ .compatible = "qcom,ipq8064", .data = &dwc3_qcom_ipq8064_overlay },
	{ .compatible = "qcom,ipq8074", .data = &dwc3_qcom_ipq8074_overlay },
	{ .compatible = "qcom,ipq9574", .data = &dwc3_qcom_ipq9574_overlay },
	{ .compatible = "qcom,msm8953", .data = &dwc3_qcom_msm8953_overlay },
	{ .compatible = "qcom,msm8992", .data = &dwc3_qcom_msm8992_overlay },
	{ .compatible = "qcom,msm8994", .data = &dwc3_qcom_msm8994_overlay },
	{ .compatible = "qcom,msm8996", .data = &dwc3_qcom_msm8996_overlay },
	{ .compatible = "qcom,msm8998", .data = &dwc3_qcom_msm8998_overlay },
	{ .compatible = "qcom,qcm2290", .data = &dwc3_qcom_qcm2290_overlay },
	{ .compatible = "qcom,qcm6490", .data = &dwc3_qcom_qcm6490_overlay },
	{ .compatible = "qcom,qcs404", .data = &dwc3_qcom_qcs404_overlay },
	{ .compatible = "qcom,qcs615", .data = &dwc3_qcom_qcs615_overlay },
	{ .compatible = "qcom,qcs8300", .data = &dwc3_qcom_qcs8300_overlay },
	{ .compatible = "qcom,qdu1000", .data = &dwc3_qcom_qdu1000_overlay },
	{ .compatible = "qcom,qru1000", .data = &dwc3_qcom_qru1000_overlay },
	{ .compatible = "qcom,sa8155p", .data = &dwc3_qcom_sa8155p_overlay },
	{ .compatible = "qcom,sa8540p", .data = &dwc3_qcom_sa8540p_overlay },
	{ .compatible = "qcom,sa8775p", .data = &dwc3_qcom_sa8775p_overlay },
	{ .compatible = "qcom,sar2130p", .data = &dwc3_qcom_sar2130p_overlay },
	{ .compatible = "qcom,sc7180", .data = &dwc3_qcom_sc7180_overlay },
	{ .compatible = "qcom,sc7280", .data = &dwc3_qcom_sc7280_overlay },
	{ .compatible = "qcom,sc8180x", .data = &dwc3_qcom_sc8180x_overlay },
	{ .compatible = "qcom,sc8280xp", .data = &dwc3_qcom_sc8280xp_overlay },
	{ .compatible = "qcom,sda660", .data = &dwc3_qcom_sda660_overlay },
	{ .compatible = "qcom,sdm450", .data = &dwc3_qcom_sdm450_overlay },
	{ .compatible = "qcom,sdm630", .data = &dwc3_qcom_sdm630_overlay },
	{ .compatible = "qcom,sdm632", .data = &dwc3_qcom_sdm632_overlay },
	{ .compatible = "qcom,sdm636", .data = &dwc3_qcom_sdm636_overlay },
	{ .compatible = "qcom,sdm660", .data = &dwc3_qcom_sdm660_overlay },
	{ .compatible = "qcom,sdm670", .data = &dwc3_qcom_sdm670_overlay },
	{ .compatible = "qcom,sdm845", .data = &dwc3_qcom_sdm845_overlay },
	{ .compatible = "qcom,sdm845-mtp", .data = &dwc3_qcom_sdm845_qcom_sdm845_mtp_overlay },
	{ .compatible = "qcom,sdx55", .data = &dwc3_qcom_sdx55_overlay },
	{ .compatible = "qcom,sdx65", .data = &dwc3_qcom_sdx65_overlay },
	{ .compatible = "qcom,sdx75", .data = &dwc3_qcom_sdx75_overlay },
	{ .compatible = "qcom,sm4250", .data = &dwc3_qcom_sm4250_overlay },
	{ .compatible = "qcom,sm6115", .data = &dwc3_qcom_sm6115_overlay },
	{ .compatible = "qcom,sm6125", .data = &dwc3_qcom_sm6125_overlay },
	{ .compatible = "qcom,sm6350", .data = &dwc3_qcom_sm6350_overlay },
	{ .compatible = "qcom,sm6375", .data = &dwc3_qcom_sm6375_overlay },
	{ .compatible = "qcom,sm7125", .data = &dwc3_qcom_sm7125_overlay },
	{ .compatible = "qcom,sm7225", .data = &dwc3_qcom_sm7225_overlay },
	{ .compatible = "qcom,sm7325", .data = &dwc3_qcom_sm7325_overlay },
	{ .compatible = "qcom,sm8150", .data = &dwc3_qcom_sm8150_overlay },
	{ .compatible = "qcom,sm8250", .data = &dwc3_qcom_sm8250_overlay },
	{ .compatible = "qcom,sm8350", .data = &dwc3_qcom_sm8350_overlay },
	{ .compatible = "qcom,sm8350-hdk", .data = &dwc3_qcom_sm8350_qcom_sm8350_hdk_overlay },
	{ .compatible = "qcom,sm8450", .data = &dwc3_qcom_sm8450_overlay },
	{ .compatible = "qcom,sm8550", .data = &dwc3_qcom_sm8550_overlay },
	{ .compatible = "qcom,sm8650", .data = &dwc3_qcom_sm8650_overlay },
	{ .compatible = "qcom,x1e80100", .data = &dwc3_qcom_x1e80100_overlay },
	{ .compatible = "samsung,starqltechn", .data = &dwc3_qcom_sdm845_samsung_starqltechn_overlay },
	{ .compatible = "samsung,w737", .data = &dwc3_qcom_sdm845_samsung_w737_overlay },
	{ .compatible = "shift,axolotl", .data = &dwc3_qcom_sdm845_shift_axolotl_overlay },
	{ .compatible = "sony,dora-row", .data = &dwc3_qcom_msm8996_sony_dora_row_overlay },
	{ .compatible = "sony,kagura-row", .data = &dwc3_qcom_msm8996_sony_kagura_row_overlay },
	{ .compatible = "sony,keyaki-row", .data = &dwc3_qcom_msm8996_sony_keyaki_row_overlay },
	{ .compatible = "sony,xperia-lilac", .data = &dwc3_qcom_msm8998_sony_xperia_lilac_overlay },
	{ .compatible = "sony,xperia-maple", .data = &dwc3_qcom_msm8998_sony_xperia_maple_overlay },
	{ .compatible = "sony,xperia-poplar", .data = &dwc3_qcom_msm8998_sony_xperia_poplar_overlay },
	{ .compatible = "thundercomm,db845c", .data = &dwc3_qcom_sdm845_thundercomm_db845c_overlay },
	{ .compatible = "xiaomi,beryllium", .data = &dwc3_qcom_sdm845_xiaomi_beryllium_overlay },
	{ .compatible = "xiaomi,beryllium-ebbg", .data = &dwc3_qcom_sdm845_xiaomi_beryllium_ebbg_overlay },
	{ .compatible = "xiaomi,elish", .data = &dwc3_qcom_sm8250_xiaomi_elish_overlay },
	{ .compatible = "xiaomi,gemini", .data = &dwc3_qcom_msm8996_xiaomi_gemini_overlay },
	{ .compatible = "xiaomi,natrium", .data = &dwc3_qcom_msm8996_xiaomi_natrium_overlay },
	{ .compatible = "xiaomi,sagit", .data = &dwc3_qcom_msm8998_xiaomi_sagit_overlay },
	{ .compatible = "xiaomi,scorpio", .data = &dwc3_qcom_msm8996_xiaomi_scorpio_overlay },
	{}
};

static int dwc3_flattening_copy_snps_properties(struct of_changeset *ocs,
						struct device_node *np,
						struct device_node *dwc3)
{
	struct property *prop;
	int ret = 0;

	for_each_property_of_node(dwc3, prop) {
		if (strncmp(prop->name, "snps,", 5) &&
		    strcmp(prop->name, "usb-role-switch") &&
		    strcmp(prop->name, "dr_mode") &&
		    strcmp(prop->name, "tx-fifo-resize") &&
		    strcmp(prop->name, "maximum-speed"))
			continue;

		ret = of_changeset_add_prop_copy(ocs, np, prop);
		if (ret)
			break;
	}

	return ret;
}

static int dwc3_flattening_copy_ports_tree(struct of_changeset *ocs,
					   struct device_node *new_parent,
					   struct device_node *old_node)
{
	struct device_node *new_node;
	struct property *prop;
	int ret;

	new_node = of_changeset_create_node(ocs, new_parent, old_node->full_name);
	if (!new_node)
		return -ENOMEM;

	for_each_property_of_node(old_node, prop) {
		of_changeset_add_prop_copy(ocs, new_node, prop);
	}

	for_each_child_of_node_scoped(old_node, child) {
		ret = dwc3_flattening_copy_ports_tree(ocs, new_node, child);
		if (ret)
			return ret;
	}

	return of_changeset_detach_node(ocs, old_node);
}

static int dwc3_flattening_migrate(struct of_changeset *ocs,
				   struct device_node *np)
{
	struct device_node *ports;
	struct device_node *dwc3;
	int ret;

	dwc3 = of_get_compatible_child(np, "snps,dwc3");
	if (!dwc3)
		return 0;

	ret = dwc3_flattening_copy_snps_properties(ocs, np, dwc3);
	if (ret) {
		pr_err("failed to copy properties of %pOF", dwc3);
		goto out;
	}

	ports = of_get_child_by_name(dwc3, "ports");
	if (ports) {
		ret = dwc3_flattening_copy_ports_tree(ocs, np, ports);
		of_node_put(ports);
		if (ret) {
			pr_err("failed to clone ports child of %pOF", dwc3);
			goto out;
		}
	}

	ret = of_changeset_detach_node(ocs, dwc3);

out:
	of_node_put(dwc3);

	return ret;
}

static int dwc3_flattening_ensure_symbols(struct of_changeset *ocs,
					  const struct dwc3_overlay_symbol *symbols)
{
	const struct dwc3_overlay_symbol *s;
	struct device_node *symbols_np;
	int ret;

	symbols_np = of_find_node_by_path("/__symbols__");
	of_node_put(symbols_np);
	if (symbols_np)
		return 0;

	symbols_np = of_changeset_create_node(ocs, of_root, "__symbols__");
	if (!symbols_np)
		return -ENOMEM;

	for (s = symbols; s->symbol; s++) {
		ret = of_changeset_add_prop_string(ocs, symbols_np, s->symbol, s->path);
		if (ret)
			return ret;
	}

	return 0;
}

static int dwc3_flattening_init(void)
{
	const struct dwc3_overlay_data *data;
	const struct of_device_id *match;
	struct of_changeset symbols_ocs;
	struct of_changeset migrate_ocs;
	struct device_node *np;
	int overlay_ovcs;
	int ret;

	/* TODO: Remove kill-switch as dwc3-qcom is migrated to qcom,snps-dwc */
	return 0;

	match = of_match_node(dwc3_flatten_of_match, of_root);
	if (!match)
		return 0;

	data = match->data;

	np = of_find_compatible_node(NULL, NULL, data->migrate_match);
	if (!np) {
		pr_debug("already applied\n");
		return 0;
	}
	of_node_put(np);

	of_changeset_init(&symbols_ocs);
	ret = dwc3_flattening_ensure_symbols(&symbols_ocs, data->symbols);
	if (ret < 0)
		goto out_destroy_symbols;

	ret = of_changeset_apply(&symbols_ocs);
	if (ret < 0)
		goto out_destroy_symbols;

	of_changeset_init(&migrate_ocs);
	for_each_compatible_node(np, NULL, data->migrate_match) {
		ret = dwc3_flattening_migrate(&migrate_ocs, np);
		if (ret < 0) {
			of_node_put(np);
			goto out_migrate_destroy;
		}
	}

	ret = of_changeset_apply(&migrate_ocs);
	if (ret < 0)
		goto out_migrate_destroy;

	ret = of_overlay_fdt_apply(data->fdt, data->end - data->fdt, &overlay_ovcs, NULL);
	if (ret < 0) {
		of_overlay_remove(&overlay_ovcs);
		of_changeset_revert(&migrate_ocs);
	}

out_migrate_destroy:
	of_changeset_destroy(&migrate_ocs);
	of_changeset_revert(&symbols_ocs);
out_destroy_symbols:
	of_changeset_destroy(&symbols_ocs);

	return ret;
}
postcore_initcall(dwc3_flattening_init);
