// Copyright (C) 2025-2026 Arief Satria
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef UI_TABLE_H
#define UI_TABLE_H

#include "../theme/theme.h"
#include <QTableWidget>

namespace ui {

class Table : public QTableWidget {
  Q_OBJECT

public:
  explicit Table(QWidget *parent = nullptr);
  Table(int rows, int columns, QWidget *parent = nullptr);
  ~Table() override = default;

private slots:
  void applyThemeStyles();
};

} // namespace ui

#endif // UI_TABLE_H

