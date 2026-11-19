# Third-Party Licenses & Notices

This document lists the third-party software libraries, assets, and design references used by or referenced in **Qt UI-Kit (`ui-kit`)**.

> Note: `ui-kit` itself is licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0-or-later)**. See [`LICENSE`](LICENSE) for the full license text.

---

## 1. Qt 6 / Qt 5 (`Qt::Core`, `Qt::Widgets`, `Qt::Svg`)

- **Project**: The Qt Company Ltd. — [https://www.qt.io/](https://www.qt.io/)
- **Modules Used**: `Qt::Core`, `Qt::Widgets`, `Qt::Svg`
- **License**: GNU Lesser General Public License v3.0 (LGPLv3)
- **Full License Text**: [https://www.gnu.org/licenses/lgpl-3.0.html](https://www.gnu.org/licenses/lgpl-3.0.html)
- **Qt Open-Source Licensing Overview**: [https://www.qt.io/licensing/open-source-lgpl-obligations](https://www.qt.io/licensing/open-source-lgpl-obligations)

### Dynamic Linking & Relinking Notice

`ui-kit` is designed to be linked dynamically against the Qt 6 or Qt 5 libraries (`Qt::Core`, `Qt::Widgets`, and `Qt::Svg`) in accordance with the terms of the GNU Lesser General Public License v3.0 (LGPLv3).

In compliance with Section 4 of the LGPLv3:
- Users and downstream recipients have the right to modify, rebuild, replace, or relink the Qt shared libraries (`Qt6Core`/`Qt5Core`, `Qt6Widgets`/`Qt5Widgets`, `Qt6Svg`/`Qt5Svg`) with a modified or interface-compatible version of Qt and run applications built with `ui-kit` against those replaced libraries.
- Source code for Qt is available from the official Qt project repositories at [https://code.qt.io/](https://code.qt.io/) and [https://download.qt.io/](https://download.qt.io/).
- Applications distributing Qt binaries alongside `ui-kit` must preserve Qt's copyright notices and provide a copy of the LGPLv3 (and GPLv3, as referenced by LGPLv3) together with the application.

---

## 2. Lucide Icons

- **Project**: Lucide Icons — [https://lucide.dev/](https://lucide.dev/) ([https://github.com/lucide-icons/lucide](https://github.com/lucide-icons/lucide))
- **Usage**: Default SVG icon set referenced via Qt resource paths (`:/icons/*.svg`) by interactive `ui-kit` components (such as `Button`, `Combobox`, `Dialog`, `Input`, `Sidebar`, `Toast`, etc.).
- **License**: ISC License (with portions derived from Feather Icons licensed under the MIT License)
- **Upstream License URL**: [https://github.com/lucide-icons/lucide/blob/main/LICENSE](https://github.com/lucide-icons/lucide/blob/main/LICENSE)

### Verbatim Lucide ISC License & Copyright Notice

```text
ISC License

Copyright (c) for portions of Lucide are held by Cole Bemis 2013-2022 as part of Feather (MIT). All other copyright (c) for Lucide are held by Lucide Contributors 2022.

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```

### Feather Icons (MIT License) — Portions Derived From Feather

Portions of Lucide are derived from [Feather Icons](https://feathericons.com/) by Cole Bemis under the MIT License:

```text
The MIT License (MIT)

Copyright (c) 2013-present Cole Bemis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 3. Design Inspiration: shadcn/ui

- **Project**: shadcn/ui — [https://ui.shadcn.com/](https://ui.shadcn.com/)
- **Acknowledgment**: `ui-kit` draws visual design inspiration and semantic design-token naming conventions (such as `background`, `foreground`, `card`, `popover`, `muted`, `accent`, `destructive`, and `ring`) from **shadcn/ui**. This acknowledgment is for design and architectural inspiration only; no source code, stylesheets, or assets from `shadcn/ui` were copied into `ui-kit`.
