/* SPDX-License-Identifier: GPL-2.0 */
/*
 * NOTE: This file has been modified by Sony Corporation.
 * Modifications are Copyright 2021 Sony Corporation,
 * and licensed under the license of the file.
 */
#ifndef BMI160_H_
#define BMI160_H_

#include <linux/iio/iio.h>

struct bmi160_data {
	struct regmap *regmap;
	struct iio_trigger *trig;
	/*
	 * Ensure natural alignment for timestamp if present.
	 * Max length needed: 2 * 3 channels + 4 bytes padding + 8 byte ts.
	 * If fewer channels are enabled, less space may be needed, as
	 * long as the timestamp is still aligned to 8 bytes.
	 */
	__le16 buf[12] __aligned(8);
};

extern const struct regmap_config bmi160_regmap_config;

int bmi160_core_probe(struct device *dev, struct regmap *regmap,
		      const char *name, bool use_spi);

int bmi160_enable_irq(struct regmap *regmap, bool enable);

int bmi160_probe_trigger(struct iio_dev *indio_dev, int irq, u32 irq_type);

#endif  /* BMI160_H_ */
