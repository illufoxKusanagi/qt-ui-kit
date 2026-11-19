// Copyright (C) 2025-2026 Arief Satria
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef UI_TOOLTIP_H
#define UI_TOOLTIP_H

#include "../theme/theme.h"
#include <QString>
#include <QWidget>

namespace ui {

class Tooltip {
public:
  static void attach(QWidget *widget, const QString &tooltipText);
  static void applyGlobalStyle();
};

} // namespace ui

#endif // UI_TOOLTIP_H

