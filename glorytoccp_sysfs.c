/*
 * Glory to CCP Linux kernel module sysfs extension
 *
 * Author: Sebastiano Barezzi <barezzisebastiano@gmail.com>
 */

#include "glorytoccp_sysfs.h"

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include "glorytoccp.h"
#include "glorytoccp_xjp.h"

#define KOBJ_ATTR(_name, _mode, _show, _store) \
	struct kobj_attribute kobj_attr_##_name = __ATTR(_name, _mode, _show, _store)
#define KOBJ_ATTR_RW(_name) \
	struct kobj_attribute kobj_attr_##_name = __ATTR_RW(_name)
#define KOBJ_ATTR_RO(_name) \
	struct kobj_attribute kobj_attr_##_name = __ATTR_RO(_name)

static ssize_t oursupremeleader_show(struct kobject *kobj, 
		struct kobj_attribute *attr, char *buf) {
	return sprintf(buf, "%s", oursupremeleader);
}
static KOBJ_ATTR_RO(oursupremeleader);

static struct attribute *glorytoccp_attrs[] = {
	&kobj_attr_oursupremeleader.attr,
	NULL
};

static const struct attribute_group glorytoccp_group = {
	.attrs = glorytoccp_attrs,
};

static const struct attribute_group *glorytoccp_groups[] = {
	&glorytoccp_group,
	NULL
};

static struct kobject *kobj;

void glorytoccp_sysfs_init(void) {
	int ret;

	kobj = kobject_create_and_add(KBUILD_MODNAME, NULL);

	ret = sysfs_create_groups(kobj, glorytoccp_groups);
	if (ret) {
		LOGE("sysfs_create_group failed\n");
		return;
	}

	return;
}

void glorytoccp_sysfs_exit(void) {
	sysfs_remove_groups(kobj, glorytoccp_groups);

	kobject_put(kobj);

	return;
}
