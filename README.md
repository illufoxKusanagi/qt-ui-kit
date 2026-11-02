# Qt UI-Kit (`ui-kit`)

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt 6 / Qt 5](https://img.shields.io/badge/Qt-6%20%7C%205-41CD52.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-purple.svg)
![Shadcn-Inspired](https://img.shields.io/badge/Design-Shadcn%20UI-9b44f9.svg)

A modern, zero-dependency **Shadcn-inspired component library for Qt 6 and Qt 5 Widgets** written in clean C++17.

`ui-kit` brings the crisp visual hierarchy, semantic token architecture, and smooth micro-interactions of modern web design systems to native C++ desktop applications—without QML overhead or third-party dependencies.

> **Using an AI coding assistant?** Point your agent directly at [**`AI_AGENT_GUIDE.md`**](AI_AGENT_GUIDE.md) for machine-actionable CMake instructions, QSS scoping rules, and a complete 30-component API contract.

---

## Key Features

- **Zero External Non-Qt Dependencies**: Built strictly on `Qt::Core`, `Qt::Widgets`, and `Qt::Svg`.
- **Reactive Light, Dark & System Themes**: Instant runtime theme switching via `ui::Theme::instance()` with automatic OS dark-mode detection (`ui::ThemeMode::System`).
- **Tokenized Design System**: Semantic `ColorTokens` (26 semantic color roles), `RadiusTokens`, `SpacingTokens`, and `TypographyTokens` (including `rem`-based font scaling via `fontRem(double)`).
- **30 Self-Contained Components**: Buttons, forms, searchable comboboxes, popovers, menus, dialogs, toasts, tables, collapsible sidebars, splitters, and more.
- **Keyboard & Screen-Reader Accessible**: Native focus rings, buddy labels, `accessibleName`/`accessibleDescription` propagation, and keyboard navigation (`Enter`, `Escape`, arrow keys, `Shift+F10`).
- **Built-In Interactive Showcase (`ui::DemoPage`)**: Embed `ui::DemoPage` in any window or build the standalone `ui_kit_demo` executable to inspect every component live.

---

## Table of Contents

1. [Project Architecture & Directory Layout](#1-project-architecture--directory-layout)
2. [Prerequisites & Requirements](#2-prerequisites--requirements)
3. [Installation & CMake Integration](#3-installation--cmake-integration)
4. [Quick Start & Reactive Widget Pattern](#4-quick-start--reactive-widget-pattern)
5. [Theme & Design Token Reference](#5-theme--design-token-reference)
6. [Complete 30-Component Catalog & API Summary](#6-complete-30-component-catalog--api-summary)
7. [Building & Running (`ui_kit_demo` & VS Code Setup)](#7-building--running-ui_kit_demo--vs-code-setup)
8. [Best Practices & Common Qt/QSS Pitfalls](#8-best-practices--common-qtqss-pitfalls)
9. [AI Agent Integration](#9-ai-agent-integration)

---

## 1. Project Architecture & Directory Layout

`ui-kit` is structured as a self-contained static library target (`ui_kit`) with an optional standalone showcase executable (`ui_kit_demo`). Every symbol lives inside `namespace ui`.

```text
ui-kit/
├── CMakeLists.txt              # Static library target `ui_kit` + optional `ui_kit_demo`
├── README.md                   # Complete developer guide & reference manual
├── AI_AGENT_GUIDE.md           # Machine-actionable integration guide for AI coding agents
├── theme/                      # Centralized design tokens, theme singleton, & helpers
│   ├── tokens.h                # ColorTokens, RadiusTokens, SpacingTokens, TypographyTokens, ThemeMode
│   ├── theme.h / theme.cpp     # Singleton `ui::Theme::instance()` with `themeChanged` signal
│   ├── style_helper.h          # QColor/QSS utilities (`toHexString`, `toRgbaString`, `tint`, `hoverColor`)
│   ├── animation_helper.h      # Standard durations (`DurationFast`, `DurationNormal`) & easing curves
│   └── icon_helper.h/.cpp      # Dynamic SVG color tinting (`ui::Icon::get`, `ui::Icon::pixmap`)
├── components/                 # 30 self-contained Shadcn-inspired Qt Widgets components
│   ├── accordion.h/.cpp        # Collapsible section with animated height
│   ├── alert.h/.cpp            # Persistent inline status banner (Info, Success, Warning, Destructive)
│   ├── avatar.h/.cpp           # Circular user/entity badge with initials, image, and status dot
│   ├── badge.h/.cpp            # Pill-shaped category/status tag
│   ├── button.h/.cpp           # Push button with 6 variants, 4 sizes, and built-in loading spinner
│   ├── card.h/.cpp             # Elevated surface container with header, content, and footer layouts
│   ├── checkbox.h/.cpp         # Custom-painted checkbox with tri-state & error state support
│   ├── combobox.h/.cpp         # Searchable dropdown selector with filterable popover list
│   ├── dialog.h/.cpp           # Modal dialog with scrollable description & static confirm/info helpers
│   ├── empty_state.h/.cpp      # Placeholder panel with icon, title, description, and optional CTA
│   ├── form_field.h/.cpp       # Wrapper adding label, required indicator, description, and error text
│   ├── input.h/.cpp            # Single-line text input with prefix/suffix labels, clear button, & error state
│   ├── menu.h/.cpp             # Themed QMenu (`ui::Menu`, `ui::DropdownMenu`, `ui::ContextMenu`)
│   ├── number_input.h/.cpp     # Integer (`ui::NumberInput`) & floating-point (`ui::DecimalInput`) spinboxes
│   ├── popover.h/.cpp          # Anchored floating container with automatic outside-click/Escape dismissal
│   ├── progress.h/.cpp         # Animated progress bar with determinate & indeterminate modes
│   ├── radio_group.h/.cpp      # Exclusive radio button group with vertical/horizontal orientation
│   ├── scroll_area.h/.cpp      # Custom-styled QScrollArea with minimalist themed scrollbars
│   ├── select.h/.cpp           # Non-searchable themed QComboBox
│   ├── separator.h/.cpp        # 1px horizontal or vertical divider line
│   ├── sidebar.h/.cpp          # Collapsible vertical navigation rail with icon + label items
│   ├── slider.h/.cpp           # Themed horizontal/vertical range slider
│   ├── spinner.h/.cpp          # Animated vector arc loading indicator
│   ├── splitter.h/.cpp         # Resizable multi-pane QSplitter with focusable handle indicator
│   ├── switch.h/.cpp           # Animated toggle switch (`QAbstractButton` subclass)
│   ├── table.h/.cpp            # Themed QTableWidget with row selection and flat header styling
│   ├── tabs.h/.cpp             # Tab bar + stacked page container (`Underline` and `Segmented` variants)
│   ├── textarea.h/.cpp         # Multi-line plain-text editor (`QPlainTextEdit`) with error state
│   ├── toast.h/.cpp            # Self-dismissing floating notification overlay
│   └── tooltip.h/.cpp          # Global QToolTip stylesheet installer & widget helper
└── demo/                       # Interactive component showcase
    ├── demo_page.h/.cpp        # Reusable `ui::DemoPage` widget demonstrating all 30 components
    └── main.cpp                # Standalone showcase entry point (`ui_kit_demo`)
```

---

## 2. Prerequisites & Requirements

- **C++17 Compiler**:
  - GCC 9+ (Linux / MinGW)
  - Clang 10+ (Linux / macOS)
  - MSVC 2019+ (Windows)
- **Build System**:
  - CMake 3.16 or newer
  - Ninja (recommended) or Make / MSBuild
- **Qt Framework**:
  - **Qt 6** (6.2+ recommended; native OS color-scheme detection works automatically on Qt 6.5+) or **Qt 5** (5.15+)
  - Required Qt modules: `Core`, `Widgets`, `Svg`

---

## 3. Installation & CMake Integration

### Option A: Local Subdirectory or Git Submodule (`add_subdirectory`)

Place `ui-kit/` inside your project and include it in your root `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyDesktopApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg)

# Optionally disable the standalone demo executable in your production build:
# set(UI_KIT_BUILD_DEMO OFF CACHE BOOL "" FORCE)
add_subdirectory(ui-kit)

add_executable(MyDesktopApp
    main.cpp
    resources/icons.qrc
)

# Links ui_kit and transitively links Qt::Core, Qt::Widgets, and Qt::Svg
target_link_libraries(MyDesktopApp PRIVATE ui_kit)
```

### Option B: CMake `FetchContent`

```cmake
include(FetchContent)
FetchContent_Declare(
    ui_kit
    GIT_REPOSITORY https://github.com/your-org/ui-kit.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(ui_kit)

target_link_libraries(MyDesktopApp PRIVATE ui_kit)
```

### CMake Options

| Option | Default | Description |
| :--- | :--- | :--- |
| `UI_KIT_BUILD_DEMO` | `ON` | Builds the standalone `ui_kit_demo` showcase executable (`demo/main.cpp`). Note: `ui::DemoPage` (`demo/demo_page.cpp`) is always compiled into `ui_kit` so it can be embedded in host apps regardless of this flag. |

### Header Include Conventions

`ui_kit` exports its root directory (`${CMAKE_CURRENT_SOURCE_DIR}`) as a `PUBLIC` include path:
- Standard includes: `#include "theme/theme.h"`, `#include "components/button.h"`, `#include "demo/demo_page.h"`
- If your parent project also adds the repository root to its include path, `#include "ui-kit/components/button.h"` works as well.

### Required `.qrc` Arrow Icon Resources & Runtime SVG Tinting

#### 1. QSS Arrow Icons (`Select`, `NumberInput`, `DecimalInput`)
Qt stylesheets (`QComboBox::down-arrow`, `QSpinBox::up-arrow`, `QSpinBox::down-arrow`) cannot dynamically recolor inline SVGs via QSS alone, so `ui::Select`, `ui::NumberInput`, and `ui::DecimalInput` reference 4 vector arrow paths from your application's `.qrc` resource file depending on the active theme mode:

| Resource Path | Active Theme Mode | Used By |
| :--- | :--- | :--- |
| `:/icons/icons/arrow-up.svg` | Dark (`isDark() == true`) | `ui::NumberInput`, `ui::DecimalInput` up-step arrow (light stroke) |
| `:/icons/icons/arrow-up-black.svg` | Light (`isDark() == false`) | `ui::NumberInput`, `ui::DecimalInput` up-step arrow (dark stroke) |
| `:/icons/icons/arrow-down.svg` | Dark (`isDark() == true`) | `ui::Select`, `ui::NumberInput`, `ui::DecimalInput` down arrow (light stroke) |
| `:/icons/icons/arrow-down-black.svg` | Light (`isDark() == false`) | `ui::Select`, `ui::NumberInput`, `ui::DecimalInput` down arrow (dark stroke) |

Ensure your application's `.qrc` file mounts these four files under `<qresource prefix="/icons">`:

```xml
<RCC>
    <qresource prefix="/icons">
        <file>icons/arrow-up.svg</file>
        <file>icons/arrow-up-black.svg</file>
        <file>icons/arrow-down.svg</file>
        <file>icons/arrow-down-black.svg</file>
    </qresource>
</RCC>
```

#### 2. Dynamic Runtime SVG Tinting via `ui::Icon`
For all other icons (buttons, sidebar items, tabs, empty states), you only need a single SVG asset. Use `ui::Icon` (`theme/icon_helper.h`) to dynamically recolor any SVG resource at runtime using semantic theme tokens:

```cpp
#include "theme/icon_helper.h"
#include "theme/theme.h"

const auto &c = ui::Theme::instance().colors();
QIcon folderIcon = ui::Icon::get(":/icons/icons/folder.svg", c.foreground, QSize(18, 18));
myButton->setIcon(folderIcon);
```

---

## 4. Quick Start & Reactive Widget Pattern

### Complete `main.cpp` Entry Point

```cpp
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include "theme/theme.h"
#include "components/card.h"
#include "components/input.h"
#include "components/form_field.h"
#include "components/button.h"
#include "components/toast.h"
#include "components/tooltip.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // 1. Initialize Theme Mode (System follows OS Dark/Light preference)
  ui::Theme::instance().setMode(ui::ThemeMode::System);

  // 2. Keep global QToolTip popups synchronized with theme changes
  ui::Tooltip::applyGlobalStyle();
  QObject::connect(&ui::Theme::instance(), &ui::Theme::themeChanged, []() {
    ui::Tooltip::applyGlobalStyle();
  });

  QMainWindow window;
  window.setWindowTitle("Qt UI-Kit Quick Start");
  window.resize(480, 320);

  auto *card = new ui::Card("Project Settings",
                            "Configure your workspace preferences", &window);

  auto *nameInput = new ui::Input("my-awesome-app", card);
  nameInput->setClearButtonEnabled(true);
  auto *field = new ui::FormField("Workspace Name", nameInput, card);
  field->setRequired(true);
  field->setDescription("Lowercase letters, numbers, and hyphens only.");
  card->contentLayout()->addWidget(field);

  auto *saveBtn = new ui::Button("Save Changes", ui::ButtonVariant::Primary,
                                 ui::ButtonSize::Default, card);
  QObject::connect(saveBtn, &QPushButton::clicked, &window, [&window, nameInput, field]() {
    if (nameInput->text().trimmed().isEmpty()) {
      nameInput->setError(true);
      field->setError("Workspace name cannot be empty.");
      return;
    }
    nameInput->setError(false);
    field->clearError();
    ui::Toast::show(&window, "Saved", "Workspace preferences updated.",
                    ui::ToastVariant::Success);
  });
  card->footerLayout()->addStretch();
  card->footerLayout()->addWidget(saveBtn);

  window.setCentralWidget(card);
  window.show();
  return app.exec();
}
```

### Writing Reactive Custom Host Widgets

All built-in `ui::*` components automatically restyle themselves when `ui::Theme::instance().themeChanged` fires. When creating your own custom pages or container widgets in your host application, connect to `ui::Theme::themeChanged` and query semantic tokens instead of hardcoding colors or pixel sizes:

```cpp
#include "theme/theme.h"
#include "theme/style_helper.h"

MyCustomPage::MyCustomPage(QWidget *parent) : QWidget(parent) {
  setObjectName("myCustomPage");
  setAttribute(Qt::WA_StyledBackground, true);

  setupUi();

  // Re-apply token styles whenever Light / Dark / System mode changes
  connect(&ui::Theme::instance(), &ui::Theme::themeChanged,
          this, &MyCustomPage::applyThemeStyles);
  applyThemeStyles();
}

void MyCustomPage::applyThemeStyles() {
  const auto &c = ui::Theme::instance().colors();
  const auto &r = ui::Theme::instance().radius();
  const auto &t = ui::Theme::instance().typography();

  m_titleLabel->setFont(t.font(t.sizeLg, QFont::Bold));
  m_subtitleLabel->setFont(t.fontRem(0.875, QFont::Normal));

  setStyleSheet(QString(
      "QWidget#myCustomPage {"
      "  background-color: %1;"
      "  border: 1px solid %2;"
      "  border-radius: %3px;"
      "}")
      .arg(ui::StyleHelper::toHexString(c.background))
      .arg(ui::StyleHelper::toHexString(c.border))
      .arg(r.md));

  m_titleLabel->setStyleSheet(
      QString("color: %1; background: transparent;")
          .arg(ui::StyleHelper::toHexString(c.foreground)));
}
```

---

## 5. Theme & Design Token Reference

All theme state and design tokens are managed by `ui::Theme::instance()` (`theme/theme.h` & `theme/tokens.h`).

### `ui::Theme` Singleton API (`theme/theme.h`)

| Method / Signal | Signature | Description |
| :--- | :--- | :--- |
| `instance()` | `static Theme &instance()` | Accesses the global theme singleton. |
| `mode()` | `ThemeMode mode() const` | Returns current mode (`ThemeMode::Light`, `ThemeMode::Dark`, `ThemeMode::System`). |
| `isDark()` | `bool isDark() const` | Returns `true` if the effective active theme is Dark. |
| `isSystemDark()` | `bool isSystemDark() const` | Detects whether the host OS is currently using a dark color scheme. |
| `setMode()` | `void setMode(ThemeMode mode)` | Sets the theme mode and emits `themeChanged` if the effective appearance changed. |
| `toggleMode()` | `void toggleMode()` | Toggles directly between `ThemeMode::Light` and `ThemeMode::Dark`. |
| `colors()` | `const ColorTokens &colors() const` | Returns the active `ColorTokens` palette (Light or Dark). |
| `radius()` | `const RadiusTokens &radius() const` | Returns the `RadiusTokens` struct. |
| `spacing()` | `const SpacingTokens &spacing() const` | Returns the `SpacingTokens` struct. |
| `typography()` | `const TypographyTokens &typography() const` | Returns the `TypographyTokens` struct. |
| `setPrimaryColor()` | `void setPrimaryColor(const QColor &primary, const QColor &primaryForeground = QColor())` | Overrides the brand primary & focus ring color at runtime and emits `themeChanged`. |
| `setFontFamily()` | `void setFontFamily(const QString &fontFamily)` | Overrides the global CSS-style font stack and emits `themeChanged`. |
| `themeChanged` | `void themeChanged(ui::ThemeMode mode)` | Signal emitted whenever theme mode, OS dark mode, brand color, or font stack changes. |

### `ui::ColorTokens` (`theme/tokens.h` — All 26 Semantic Fields)

| Token Field | Light Default | Dark Default | Semantic Role |
| :--- | :--- | :--- | :--- |
| `background` | `#ffffff` | `#09090b` | Primary window and page canvas background |
| `foreground` | `#09090b` | `#fafafa` | Primary body text and heading color |
| `card` | `#ffffff` | `#18181b` | Elevated card surface (`ui::Card`, `ui::Table`, `ui::EmptyState`) |
| `cardForeground` | `#09090b` | `#fafafa` | Text rendered directly on `card` surfaces |
| `popover` | `#ffffff` | `#18181b` | Floating overlay surface (`ui::Popover`, `ui::Menu`, `ui::Toast`, `ui::Combobox` popup) |
| `popoverForeground` | `#09090b` | `#fafafa` | Text inside floating overlays and menus |
| `primary` | `#9b44f9` | `#a78bfa` | Primary brand accent (`ButtonVariant::Primary`, active switches, sliders, links) |
| `primaryForeground` | `#ffffff` | `#09090b` | High-contrast text/icons on top of `primary` surfaces |
| `secondary` | `#f4f4f5` | `#27272a` | Subtle secondary surface (`ButtonVariant::Secondary`, `BadgeVariant::Secondary`) |
| `secondaryForeground` | `#09090b` | `#fafafa` | Text on top of `secondary` surfaces |
| `muted` | `#f4f4f5` | `#27272a` | Muted background tracks (`Segmented` tabs, `Progress` track, disabled fills) |
| `mutedForeground` | `#71717a` | `#a1a1aa` | De-emphasized text, placeholders, captions, and secondary icons |
| `accent` | `#f4f4f5` | `#27272a` | Hover highlight surface for ghost buttons, menu items, and sidebar rows |
| `accentForeground` | `#09090b` | `#fafafa` | Text/icons on hovered `accent` items |
| `destructive` | `#ef4444` | `#ef4444` | Danger actions, validation error borders, and error text |
| `destructiveForeground` | `#ffffff` | `#ffffff` | Text on `ButtonVariant::Destructive` and `BadgeVariant::Destructive` |
| `border` | `#e4e4e7` | `#27272a` | Hairline container, card, table, and separator borders |
| `input` | `#e4e4e7` | `#27272a` | Default resting border color for form controls (`Input`, `Select`, `Textarea`) |
| `ring` | `#9b44f9` | `#a78bfa` | Keyboard focus ring and active input border highlight |
| `success` | `#15803d` | `#4ade80` | Success status accent border/icon (`AlertVariant::Success`, `ToastVariant::Success`) |
| `successForeground` | `#166534` | `#bbf7d0` | Text rendered on `successSurface` |
| `successSurface` | `#f0fdf4` | `#052e16` | Subtle tinted background surface for success alerts |
| `warning` | `#a16207` | `#facc15` | Warning status accent border/icon (`AlertVariant::Warning`, `ToastVariant::Warning`) |
| `warningForeground` | `#854d0e` | `#fef08a` | Text rendered on `warningSurface` |
| `warningSurface` | `#fefce8` | `#422006` | Subtle tinted background surface for warning alerts |
| `info` | `#0369a1` | `#38bdf8` | Informational status accent border/icon (`AlertVariant::Info`) |
| `infoForeground` | `#075985` | `#bae6fd` | Text rendered on `infoSurface` |
| `infoSurface` | `#f0f9ff` | `#082f49` | Subtle tinted background surface for informational alerts |

### `ui::RadiusTokens` & `ui::SpacingTokens` (`theme/tokens.h`)

| `RadiusTokens` Field | Value (`px`) | Typical Usage | `SpacingTokens` Field | Value (`px`) |
| :--- | :--- | :--- | :--- | :--- |
| `none` | `0` | Flush edges, square cells | `space0` | `0` |
| `sm` | `4` | Small buttons, checkboxes, inner tabs | `space1` | `4` |
| `md` | `6` | Inputs, selects, comboboxes, default buttons | `space2` | `8` |
| `lg` | `8` | Popovers, alerts, toasts, cards | `space3` | `12` |
| `xl` | `12` | Modal dialogs, large feature cards | `space4` | `16` |
| `full` | `9999` | Pills (`Badge`, `Switch`, `Avatar`) | `space5` | `20` |
| — | — | — | `space6` | `24` |
| — | — | — | `space8` | `32` |
| — | — | — | `space10` | `40` |
| — | — | — | `space12` | `48` |

### `ui::TypographyTokens` (`theme/tokens.h`)

| Member / Method | Default / Signature | Description |
| :--- | :--- | :--- |
| `fontFamily` | `"Segoe UI, Inter, -apple-system, Roboto, sans-serif"` | Comma-separated fallback font stack split via `QFont::setFamilies()`. |
| `rootPx` | `16` | Base pixel size for `1.0rem` (`remPx(double)`). |
| `sizeXs` .. `size3Xl` | `sizeXs=11`, `sizeSm=12`, `sizeBase=14`, `sizeLg=16`, `sizeXl=18`, `size2Xl=24`, `size3Xl=30` | Standard pixel font scale. |
| `font(px, weight)` | `QFont font(int pixelSize, QFont::Weight weight = QFont::Normal) const` | Builds a `QFont` configured with `fontFamily`, pixel size, and weight. |
| `fontRem(rem, weight)` | `QFont fontRem(double rem, QFont::Weight weight = QFont::Normal) const` | Builds a `QFont` scaled relative to `rootPx` (e.g., `0.875rem` = `14px`). |

### Utility Helpers (`StyleHelper`, `AnimationHelper`, `Icon`)

| Class & Header | Static Methods / Constants |
| :--- | :--- |
| `ui::StyleHelper` (`theme/style_helper.h`) | `toHexString(c)` (`#rrggbb`), `toRgbaString(c)` (`rgba(r, g, b, a)`), `withAlpha(c, int 0..255)`, `withAlphaF(c, qreal 0..1)`, `lighten(c, amount=10)`, `darken(c, amount=10)`, `hoverColor(c, isDark)`, `tint(surface, accent, ratio)` |
| `ui::AnimationHelper` (`theme/animation_helper.h`) | `DurationInstant = 0`, `DurationFast = 150`, `DurationNormal = 200`, `DurationSlow = 300`, `standardEasing()` (`OutCubic`), `smoothEasing()` (`InOutQuad`) |
| `ui::Icon` (`theme/icon_helper.h`) | `Icon::get(resourcePath, color, size = QSize(20, 20))` (`QIcon`), `Icon::pixmap(resourcePath, color, size)` (`QPixmap`), `Icon::pixmap(resourcePath, color, width, height)` (`QPixmap`) |

---

## 6. Complete 30-Component Catalog & API Summary

### Component Selection Matrix

| # | Component | Header | Base Class | Variants / Enums | Key Methods & Signals |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | `ui::Accordion` | `components/accordion.h` | `QWidget` | — | `setTitle`, `setExpanded(bool, animated)`, `toggleExpanded()`, `setContentWidget(QWidget*)`, `toggled(bool)` |
| 2 | `ui::Alert` | `components/alert.h` | `QFrame` | `AlertVariant` (`Info`, `Success`, `Warning`, `Destructive`) | `setTitle`, `setDescription`, `setVariant` |
| 3 | `ui::Avatar` | `components/avatar.h` | `QWidget` | `AvatarSize` (`Small`, `Default`, `Large`), `AvatarStatus` (`None`, `Online`, `Offline`, `Busy`, `Away`) | `setInitials`, `setImage(QPixmap)`, `setSize`, `setStatus` |
| 4 | `ui::Badge` | `components/badge.h` | `QLabel` | `BadgeVariant` (`Default`, `Secondary`, `Outline`, `Destructive`) | `setVariant`, `setText` |
| 5 | `ui::Button` | `components/button.h` | `QPushButton` | `ButtonVariant` (`Primary`, `Secondary`, `Outline`, `Ghost`, `Destructive`, `Link`), `ButtonSize` (`Small`, `Default`, `Large`, `Icon`) | `setVariant`, `setSize`, `setLoading(bool)`, `setLoadingText(QString)`, `clicked()` |
| 6 | `ui::Card` | `components/card.h` | `QFrame` | — | `setTitle`, `setDescription`, `contentLayout()`, `footerLayout()`, `setContentWidget`, `setFooterWidget` |
| 7 | `ui::Checkbox` | `components/checkbox.h` | `QCheckBox` | — | `setError(bool)`, `hasError()`, `setChecked(bool)`, `setTristate(bool)`, `toggled(bool)` |
| 8 | `ui::Combobox` | `components/combobox.h` | `QWidget` | — | `setItems(QStringList)`, `addItem(text, data)`, `setCurrentIndex`, `currentText()`, `currentData()`, `setPlaceholderText`, `setError(bool)`, `currentIndexChanged(int)` |
| 9 | `ui::Dialog` | `components/dialog.h` | `QDialog` | — | `Dialog::confirm(...)`, `Dialog::info(...)`, `setTitle`, `setDescription`, `setContentWidget`, `setConfirmText`, `setCancelText`, `setDestructive(bool)` |
| 10 | `ui::EmptyState` | `components/empty_state.h` | `QFrame` | — | `setTitle`, `setDescription`, `setIcon(QIcon)`, `setActionText(QString)`, `actionButton()`, `actionTriggered()` |
| 11 | `ui::FormField` | `components/form_field.h` | `QWidget` | — | `setLabel`, `setRequired(bool)`, `setDescription`, `setError(QString)`, `clearError()`, `setControl(QWidget*)` |
| 12 | `ui::Input` | `components/input.h` | `QWidget` | — | `text()`, `setText`, `setPlaceholderText`, `setPrefixText`, `setSuffixText`, `setClearButtonEnabled(bool)`, `setReadOnly(bool)`, `setError(bool)`, `textChanged(QString)` |
| 13 | `ui::Menu` / `DropdownMenu` / `ContextMenu` | `components/menu.h` | `QMenu` | Aliases: `DropdownMenu`, `ContextMenu` | `addAction`, `addSeparator`, `addMenu`, `popup(QPoint)` |
| 14 | `ui::NumberInput` | `components/number_input.h` | `QSpinBox` | — | `setRange(int, int)`, `setValue(int)`, `setSingleStep(int)`, `setPrefix`, `setSuffix`, `setError(bool)`, `valueChanged(int)` |
| 15 | `ui::DecimalInput` | `components/number_input.h` | `QDoubleSpinBox` | — | `setDecimals(int)`, `setRange(double, double)`, `setSingleStep(double)`, `setValue(double)`, `setError(bool)`, `valueChanged(double)` |
| 16 | `ui::Popover` | `components/popover.h` | `QFrame` | — | `contentLayout()`, `openFor(QWidget *anchor)`, `closePopover()`, `opened()`, `closed()` |
| 17 | `ui::Progress` | `components/progress.h` | `QWidget` | `ProgressSize` (`Small`, `Default`, `Large`) | `setValue(int, animated)`, `setRange(min, max)`, `setIndeterminate(bool)`, `setSize(ProgressSize)` |
| 18 | `ui::RadioGroup` | `components/radio_group.h` | `QWidget` | `Qt::Orientation` (`Vertical`, `Horizontal`) | `addOption(text, id)`, `setCheckedId(int)`, `checkedId()`, `setOrientation`, `selectionChanged(int)` |
| 19 | `ui::ScrollArea` | `components/scroll_area.h` | `QScrollArea` | — | `setWidget(QWidget*)`, `setWidgetResizable(bool)` |
| 20 | `ui::Select` | `components/select.h` | `QComboBox` | — | `addItems(QStringList)`, `setCurrentIndex(int)`, `currentText()`, `currentIndexChanged(int)` |
| 21 | `ui::Separator` | `components/separator.h` | `QFrame` | `Qt::Orientation` (`Horizontal`, `Vertical`) | `setOrientation(Qt::Orientation)` |
| 22 | `ui::Sidebar` | `components/sidebar.h` | `QFrame` | — | `setTitle(title, icon)`, `addItem(text, icon, id)`, `setCurrentIndex(int)`, `setCollapsed(bool, animated)`, `toggleCollapsed()`, `setFooterWidget(QWidget*)`, `itemSelected(int id, int index)` |
| 23 | `ui::Slider` | `components/slider.h` | `QSlider` | `Qt::Orientation` (`Horizontal`, `Vertical`) | `setRange(int, int)`, `setValue(int)`, `valueChanged(int)` |
| 24 | `ui::Spinner` | `components/spinner.h` | `QWidget` | — | `setSpinnerSize(int)`, `setColor(QColor)`, `start()`, `stop()`, `isSpinning()` |
| 25 | `ui::Splitter` | `components/splitter.h` | `QSplitter` | `Qt::Orientation` (`Horizontal`, `Vertical`) | `addWidget(QWidget*)`, `setSizes(QList<int>)`, `setStretchFactor(int, int)` |
| 26 | `ui::Switch` | `components/switch.h` | `QAbstractButton` | — | `setChecked(bool)`, `isChecked()`, `toggled(bool)` |
| 27 | `ui::Table` | `components/table.h` | `QTableWidget` | — | `setRowCount`, `setColumnCount`, `setHorizontalHeaderLabels`, `setItem(row, col, item)` |
| 28 | `ui::Tabs` | `components/tabs.h` | `QWidget` | `TabVariant` (`Underline`, `Segmented`) | `setVariant(TabVariant)`, `addTab(text, icon, page)`, `setCurrentIndex(int)`, `widget(int)`, `currentChanged(int)` |
| 29 | `ui::Textarea` | `components/textarea.h` | `QPlainTextEdit` | — | `setPlaceholderText`, `toPlainText()`, `setPlainText`, `setError(bool)`, `hasError()` |
| 30 | `ui::Toast` | `components/toast.h` | `QFrame` | `ToastVariant` (`Default`, `Success`, `Warning`, `Destructive`) | `Toast::show(parent, title, description, variant, durationMs)`, `dismiss()` |
| 31 | `ui::Tooltip` | `components/tooltip.h` | Utility class | — | `Tooltip::attach(widget, text)`, `Tooltip::applyGlobalStyle()` |
| — | `ui::DemoPage` | `demo/demo_page.h` | `QWidget` | — | `DemoPage(QWidget *parent = nullptr)` — Full interactive 30-component showcase |

---

### Code Examples by Category

#### 1. Buttons & Actions (`Button`, `Menu` / `DropdownMenu` / `ContextMenu`, `Popover`)
```cpp
#include "components/button.h"
#include "components/menu.h"
#include "components/popover.h"
#include "components/input.h"

// Button with variants (Primary, Secondary, Outline, Ghost, Destructive, Link) & loading state
auto *btn = new ui::Button("Export", ui::ButtonVariant::Primary, ui::ButtonSize::Default, parent);
btn->setLoadingText("Exporting...");
btn->setLoading(true); // Renders inline animated spinner and locks width

// DropdownMenu / ContextMenu
auto *menu = new ui::DropdownMenu(btn);
menu->addAction("Export as PNG");
menu->addSeparator();
menu->addAction("Reset Defaults");
btn->setMenu(menu);

// Anchored Popover
auto *popover = new ui::Popover(btn);
popover->contentLayout()->addWidget(new ui::Input("Filter value...", popover));
popover->openFor(btn);
```

#### 2. Text & Numeric Inputs (`Input`, `Textarea`, `NumberInput`, `DecimalInput`, `FormField`)
```cpp
#include "components/input.h"
#include "components/textarea.h"
#include "components/number_input.h"
#include "components/form_field.h"

auto *input = new ui::Input("Enter filename...", parent);
input->setPrefixText("img_");
input->setSuffixText(".webp");
input->setClearButtonEnabled(true);

auto *field = new ui::FormField("Output Filename", input, parent);
field->setRequired(true);
field->setDescription("Used for batch exports");

auto *notes = new ui::Textarea("Add export metadata notes...", parent);

auto *quality = new ui::NumberInput(parent);
quality->setRange(1, 100);
quality->setSuffix(" %");
quality->setValue(85);

auto *scale = new ui::DecimalInput(parent);
scale->setDecimals(2);
scale->setRange(0.25, 4.0);
scale->setSingleStep(0.25);
scale->setSuffix("x");
scale->setValue(1.50);
```

#### 3. Selection Controls (`Select`, `Combobox`, `Checkbox`, `RadioGroup`, `Switch`, `Slider`)
```cpp
#include "components/select.h"
#include "components/combobox.h"
#include "components/checkbox.h"
#include "components/radio_group.h"
#include "components/switch.h"
#include "components/slider.h"

// Fixed dropdown
auto *select = new ui::Select({"PNG", "JPEG", "WEBP", "TIFF"}, parent);

// Searchable filter combobox
auto *combo = new ui::Combobox(parent);
combo->addItem("PNG (Lossless)", "png");
combo->addItem("WEBP (Modern Web)", "webp");
combo->setPlaceholderText("Search formats...");

// Checkbox & RadioGroup
auto *check = new ui::Checkbox("Preserve EXIF metadata", parent);
auto *radios = new ui::RadioGroup({"Standard", "Balanced", "Maximum"}, parent);
radios->setCheckedId(1);

// Animated Switch & Slider
auto *toggle = new ui::Switch(true, parent);
auto *slider = new ui::Slider(Qt::Horizontal, parent);
slider->setRange(0, 100);
slider->setValue(75);
```

#### 4. Feedback & Overlays (`Alert`, `Badge`, `Toast`, `Dialog`, `Progress`, `Spinner`, `Tooltip`)
```cpp
#include "components/alert.h"
#include "components/badge.h"
#include "components/toast.h"
#include "components/dialog.h"
#include "components/progress.h"
#include "components/spinner.h"
#include "components/tooltip.h"

// Persistent inline alert (Info, Success, Warning, Destructive)
auto *alert = new ui::Alert("Batch Ready", "12 images queued for conversion.",
                            ui::AlertVariant::Info, parent);

// Status Badge
auto *badge = new ui::Badge("Lossless", ui::BadgeVariant::Secondary, parent);

// Floating Toast notification
ui::Toast::show(parent, "Conversion Complete", "Saved 12 files to disk.",
                ui::ToastVariant::Success);

// Modal Dialog (Confirm / Info)
if (ui::Dialog::confirm(parent, "Overwrite Files?",
                        "Existing files in the output folder will be replaced.",
                        "Overwrite", /*isDestructive=*/true)) {
  // Proceed...
}

// Progress & Spinner
auto *progress = new ui::Progress(65, parent);
auto *spinner = new ui::Spinner(24, parent);
spinner->start();

// Tooltip
ui::Tooltip::attach(badge, "PNG compression preserves 100% pixel fidelity");
```

#### 5. Containers & Data Display (`Card`, `Accordion`, `Avatar`, `Table`, `EmptyState`)
```cpp
#include "components/card.h"
#include "components/accordion.h"
#include "components/avatar.h"
#include "components/table.h"
#include "components/empty_state.h"

// Card container
auto *card = new ui::Card("Compression Summary", "Recent batch statistics", parent);

// Collapsible Accordion
auto *accordion = new ui::Accordion("Advanced Color Quantization", detailsWidget, parent);

// User/Entity Avatar
auto *avatar = new ui::Avatar("IK", ui::AvatarSize::Default, parent);
avatar->setStatus(ui::AvatarStatus::Online);

// Themed Data Table
auto *table = new ui::Table(3, 3, parent);
table->setHorizontalHeaderLabels({"File", "Format", "Status"});

// EmptyState placeholder
auto *empty = new ui::EmptyState("No Files Queued",
                                 "Drag and drop images here to begin.", parent);
empty->setActionText("Browse Files");
```

#### 6. Navigation & Layout (`Tabs`, `Sidebar`, `ScrollArea`, `Splitter`, `Separator`)
```cpp
#include "components/tabs.h"
#include "components/sidebar.h"
#include "components/scroll_area.h"
#include "components/splitter.h"
#include "components/separator.h"

// Tabs (TabVariant::Underline or TabVariant::Segmented)
auto *tabs = new ui::Tabs(ui::TabVariant::Underline, parent);
tabs->addTab("Image Converter", QIcon(), imagePage);
tabs->addTab("PDF Compression", QIcon(), pdfPage);

// Collapsible Sidebar
auto *sidebar = new ui::Sidebar(parent);
sidebar->setTitle("Workspace");
sidebar->addItem("Convert", QIcon(), 0);
sidebar->addItem("Showcase", QIcon(), 1);

// ScrollArea, Splitter & Separator
auto *scroll = new ui::ScrollArea(parent);
auto *splitter = new ui::Splitter(Qt::Horizontal, parent);
auto *divider = new ui::Separator(Qt::Horizontal, parent);
```

---

## 7. Building & Running (`ui_kit_demo` & VS Code Setup)

`ui-kit` includes a standalone demo application (`ui_kit_demo`) powered by `ui::DemoPage` (`demo/demo_page.h`), showcasing all 30 components with live Light, Dark, and System theme switching.

### Command Line (CLI)

#### Build & Run from the `ui-kit/` Directory (Standalone)
```bash
cmake -B build -G Ninja -DUI_KIT_BUILD_DEMO=ON
cmake --build build --parallel
./build/ui_kit_demo
```

#### Build & Run from a Parent Project
```bash
cmake -B build -G Ninja -DUI_KIT_BUILD_DEMO=ON
cmake --build build --target ui_kit_demo --parallel
./build/ui-kit/ui_kit_demo
```

### Building & Running in VS Code (CMake Tools Extension)

1. **Open Folder**: Open either the `ui-kit/` directory (standalone) or your parent workspace folder in VS Code with the **CMake Tools** extension installed (`ms-vscode.cmake-tools`).
2. **Select a Kit**: Press `Ctrl+Shift+P` (`Cmd+Shift+P` on macOS) → run **CMake: Select a Kit** and choose your C++17 compiler (e.g., GCC, Clang, or MSVC with Qt 6 / Qt 5 on PATH).
3. **Configure**: Run **CMake: Configure** from the Command Palette.
4. **Select Launch Target**:
   - Click the **Launch Target** selector in the VS Code bottom status bar (or run **CMake: Set Launch/Debug Target**).
   - Select **`ui_kit_demo`**.
5. **Run or Debug**:
   - Press **`Ctrl+F5`** (or click the status bar **Launch** play button) to build and run `ui_kit_demo` without debugging.
   - Press **`Shift+F5`** (or run **CMake: Debug**) to launch `ui_kit_demo` under GDB/LLDB/MSVC debugger.

> **Troubleshooting `[cpack] CPack Error: CPack generator not specified`**:
> Do **not** click **"Package"** or run **CMake: Run CPack** to start the demo. `ui-kit` is a source-level static library without `include(CPack)`, so invoking CPack will fail with `CPack generator not specified`. Always use **CMake: Run Without Debugging (`Ctrl+F5`)** or **CMake: Debug (`Shift+F5`)** with the launch target set to `ui_kit_demo`.

### Embedding `ui::DemoPage` Inside Your Existing App

Because `demo/demo_page.cpp` is compiled directly into the `ui_kit` static library, you can embed the full interactive showcase inside any window, tab, or dialog in two lines of code:

```cpp
#include "demo/demo_page.h"

tabs->addTab("Component Showcase", QIcon(), new ui::DemoPage(this));
```

---

## 8. Best Practices & Common Qt/QSS Pitfalls

### Rule A: Never Use Unscoped `QFrame` QSS Selectors
In Qt's widget inheritance hierarchy, **`QLabel` inherits from `QFrame`** (`class QLabel : public QFrame`).
- **Pitfall**: Applying an unscoped `QFrame { border: 1px solid ...; }` stylesheet to a container widget will draw an unwanted border box around every child `QLabel` inside that container.
- **Solution**: Always scope stylesheets to the explicit class selector (`ui--Card`, `ui--Alert`, `ui--Toast`) or assign an `objectName` and enable `Qt::WA_StyledBackground`:
  ```cpp
  panel->setObjectName("settingsPanel");
  panel->setAttribute(Qt::WA_StyledBackground, true);
  panel->setStyleSheet("QWidget#settingsPanel { background: #18181b; border: 1px solid #27272a; }");
  ```

### Rule B: Qt Parent-Child Memory Ownership vs. `ui::Toast::show`
- Always pass a valid `QWidget *parent` pointer when constructing `ui::*` widgets so Qt's object tree cleans them up automatically.
- **Exception**: `ui::Toast::show(parent, title, description, variant, durationMs)` creates a transient floating notification anchored to `parent`'s top-level window and automatically calls `deleteLater()` when its fade-out animation finishes. Never manually `delete` the pointer returned by `ui::Toast::show`.

### Rule C: `QSignalBlocker` Discipline for Synchronized Controls
When two controls represent the same underlying state (e.g., a `ui::Slider` paired with a `ui::NumberInput`), wrap programmatic updates in `QSignalBlocker` to avoid recursive signal loops:

```cpp
connect(slider, &QSlider::valueChanged, this, [spinBox](int val) {
  const QSignalBlocker blocker(spinBox);
  spinBox->setValue(val);
});
connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [slider](int val) {
  const QSignalBlocker blocker(slider);
  slider->setValue(val);
});
```

### Rule D: Use Built-In `ui::Button::setLoading(bool)`
Instead of manually hiding a button or swapping in a separate `ui::Spinner` during background tasks, use `ui::Button`'s built-in loading state. It disables interaction, renders an inline animated spinner matching the button's foreground token, prevents layout width collapse, and restores the original text, icon, and enabled state when finished:

```cpp
exportBtn->setLoadingText("Processing...");
exportBtn->setLoading(true);
// When background task completes:
exportBtn->setLoading(false);
```

---

## 9. AI Agent Integration

See [**`AI_AGENT_GUIDE.md`**](AI_AGENT_GUIDE.md) for machine-actionable architectural rules, `.qrc` resource contracts, QSS scoping requirements, and exact C++17 constructor/method signatures designed for AI coding assistants.
