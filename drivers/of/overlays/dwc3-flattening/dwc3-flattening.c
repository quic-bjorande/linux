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
};

static const struct of_device_id dwc3_flatten_of_match[] = {
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

static int dwc3_flattening_init(void)
{
	const struct dwc3_overlay_data *data;
	const struct of_device_id *match;
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

	return ret;
}
postcore_initcall(dwc3_flattening_init);
