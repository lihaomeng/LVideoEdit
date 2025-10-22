## Quick context

This is a small Qt5-based C++ desktop app. The main executable is built from `LVideoEditor/` and launched from `main.cpp` which instantiates `LVideoEditorMainWindow`.

Key files/directories to inspect first:
- `CMakeLists.txt` (root) — top-level project, adds `LVideoEditor`.
- `LVideoEditor/CMakeLists.txt` — primary build logic for the GUI target, lists `HEADER_FILES`, `CPP_FILES`, `UI_FILES`, `RCC_FILES`.
- `LVideoEditor/main.cpp` — app entrypoint.
- `LVideoEditor/lvideoeditor.*` — main window implementation and UI wiring.
- `LLibraryMoudle/llibraryexport.h` — DLL import/export macro and build-time symbol pattern.

## Big picture / architecture

- Single executable (project name: `LSnap` in the LVideoEditor CMake file). The code is Qt Widgets-based (Qt5::Widgets, Core, Gui).
- UI is split into panels (library, preview, property, timeline) inside `LVideoEditorMainWindow`.
- The CMake lists show many commented-out modules (LSnapGIF, LSnapHistory). The codebase looks trimmed to a minimal runnable shell: adding new modules is done by adding subdirectories and linking them in the top-level CMake.

## Build & developer workflows (Windows / PowerShell)

Requirements: Qt5 development libraries and a working CMake (3.10+). The project uses MSVC-specific compile options when using MSVC.

Typical quick build (choose an appropriate generator for your machine):

PowerShell examples (pick one generator):

1) Visual Studio generator (default multi-config):
```powershell
mkdir build; cmake -S . -B build -G "Visual Studio 17 2022"; cmake --build build --config Debug
```

2) Ninja (single-config):
```powershell
mkdir build; cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release; cmake --build build --config Release
```

Notes:
- If building a DLL that uses `LLIBARYEXPORT`, define `LSNAPGIF_DLL` for that target (see `LLibraryMoudle/llibraryexport.h`). In CMake you can use target_compile_definitions when creating the DLL target.
- UI `.ui` files, resources and moc are handled via CMake variables in `LVideoEditor/CMakeLists.txt` (CMAKE_AUTOMOC/AUTOUIC/AUTORCC). When you add a `.ui` file, also add it to `UI_FILES` so CMake can show it in the project.

## Project-specific conventions and patterns

- CMake-centric file lists: add sources to the explicit lists in `LVideoEditor/CMakeLists.txt` rather than scattering add_executable calls. Look for `HEADER_FILES`, `CPP_FILES`, `UI_FILES`, `RCC_FILES` and add new entries there.
- UTF-8 and MSVC flags: when MSVC is detected the CMake file adds `/Zc:__cplusplus` and `/utf-8` compile options.
- Translation-ready strings: UI strings use `tr("...")` throughout `lvideoeditor.cpp` — follow that for new user-visible text.
- Naming: main window class is `LVideoEditorMainWindow` and source files use lowercase filenames (e.g., `lvideoeditor.cpp/h`). Keep new files following this pattern.
- Export macro: `LLIBARYEXPORT` is defined in `LLibraryMoudle/llibraryexport.h`. When adding or consuming a DLL, honor the `LSNAPGIF_DLL` symbol to control dllexport/dllimport.

## Integration points & external dependencies

- Qt5 (Core, Widgets, Gui) — required at configure time (find_package in CMake).
- Optional modules referenced but disabled: `LSnapGIF`, `LSnapHistory`. Their include paths and link references are present but commented — enabling them requires adding those subdirectories and targets.

## Examples (what to change for common tasks)

- Add a new widget class MyPanel:
  1. Create `lmypanel.h` / `lmypanel.cpp`.
  2. Add `lmypanel.h` to `HEADER_FILES` and `lmypanel.cpp` to `CPP_FILES` in `LVideoEditor/CMakeLists.txt`.
  3. If the widget has a `.ui`, add it to `UI_FILES` and keep the object name consistent with `panel_<name>` if you intend to use the same panel pattern.

- Add an icon resource:
  1. Edit `res/icons.qrc` (or create one) and add the resource path.
  2. Add it to `RCC_FILES` in `LVideoEditor/CMakeLists.txt`.

- Create a DLL target that exports API:
  1. In the DLL's CMakeLists, add target and set `target_compile_definitions(mytarget PRIVATE LSNAPGIF_DLL)`.
  2. Use `LLIBARYEXPORT` on symbols in headers under `LLibraryMoudle/`.

## What an AI coding agent should do first

1. Open `LVideoEditor/CMakeLists.txt` and `LVideoEditor/lvideoeditor.*` to understand the UI structure.
2. Confirm local Qt5 SDK availability and pick an appropriate CMake generator for the developer environment.
3. When proposing edits: always update the CMake file lists for new sources/resources, and keep strings wrapped in `tr()`.

## Where to check for regressions after edits

- Build with the same generator used by the developer; if MSVC is used make sure to test both Debug/Release configs.
- Run the binary from the build output (`build/bin/LSnap.exe` or Visual Studio's output dir) to verify the main window shows.

If you want, I can refine this further (more build variants, CI notes, or add a brief contributor checklist). What would you like next?
